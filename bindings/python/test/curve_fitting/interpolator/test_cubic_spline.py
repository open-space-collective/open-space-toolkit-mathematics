# Apache License 2.0

import pytest

import numpy as np

from ostk.mathematics.curve_fitting.interpolator import CubicSpline


class TestCubicSpline:
    def test_default_constructor(self):
        CubicSpline(x=[0.0, 1.0, 2.0, 3.0, 4.0, 5.0], y=[0.0, 3.0, 6.0, 9.0, 17.0, 5.0])

    def test_default_constructor_2(self):
        CubicSpline(y=[0.0, 3.0, 6.0, 9.0, 17.0, 5.0], x_0=0.0, h=1.0)

    def test_evaluate(self):
        y: list[float] = [
            -4.632122947015880607e06,
            -4.638362755234977230e06,
            -4.644761115514834411e06,
            -4.650595795951002277e06,
            -4.655866062354639173e06,
            -4.660571249500595033e06,
            -4.664710761221675202e06,
            -4.668284070493859239e06,
            -4.671290719512360170e06,
            -4.673730319758670405e06,
        ]
        spline = CubicSpline(y, 0.0, 10.0)

        for i in range(10):
            assert pytest.approx(spline.evaluate(i * 10.0)) == y[i]

        assert pytest.approx(spline.evaluate(np.linspace(0.0, 90.0, 10))) == y
