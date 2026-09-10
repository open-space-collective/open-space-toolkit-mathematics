# Apache License 2.0

import pytest

import numpy as np

from ostk.mathematics.curve_fitting import Interpolator
from ostk.mathematics.curve_fitting.interpolator import QuinticSpline

# Sampled from f(x) = x^4 - 3 * x^2 + 2, on a uniform and on a ragged grid. At least 8 points
# are required.

X: list[float] = [0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0]
Y: list[float] = [2.0, 0.0, 6.0, 56.0, 210.0, 552.0, 1190.0, 2256.0, 3906.0, 6320.0]

NON_UNIFORM_X: list[float] = [0.0, 0.5, 1.0, 2.5, 3.0, 5.0, 5.5, 7.0, 8.0, 10.0]
NON_UNIFORM_Y: list[float] = [
    2.0,
    1.3125,
    0.0,
    22.3125,
    56.0,
    552.0,
    826.3125,
    2256.0,
    3906.0,
    9702.0,
]


@pytest.fixture
def interpolator() -> QuinticSpline:
    return QuinticSpline(x=X, y=Y)


class TestQuinticSpline:
    def test_constructor_success(self, interpolator: QuinticSpline):
        assert interpolator is not None
        assert isinstance(interpolator, Interpolator)
        assert isinstance(interpolator, QuinticSpline)

    def test_default_constructor_2(self):
        assert QuinticSpline(y=Y, x_0=0.0, h=1.0) is not None

    def test_constructor_failure(self):
        # At least 8 data points are required

        with pytest.raises(Exception):
            QuinticSpline(x=X[:7], y=Y[:7])

        with pytest.raises(Exception):
            QuinticSpline(x=[0.0, 1.0, 2.0, 4.0, 3.0, 5.0, 6.0, 7.0, 8.0, 9.0], y=Y)

        with pytest.raises(Exception):
            QuinticSpline(y=Y, x_0=0.0, h=0.0)

    def test_get_interpolation_type(self, interpolator: QuinticSpline):
        assert interpolator.get_interpolation_type() == Interpolator.Type.QuinticSpline

    def test_evaluate(self, interpolator: QuinticSpline):
        assert interpolator.evaluate(1.5) is not None
        assert interpolator.evaluate([1.5, 3.5]) is not None
        assert len(interpolator.evaluate(np.array([1.5, 3.5]))) == 2

    def test_evaluate_out_of_domain(self, interpolator: QuinticSpline):
        with pytest.raises(Exception):
            interpolator.evaluate(-1.0)

    def test_compute_derivative(self, interpolator: QuinticSpline):
        assert interpolator.compute_derivative(1.5) is not None
        assert len(interpolator.compute_derivative(np.array([1.5, 3.5]))) == 2

    def test_compute_second_derivative(self, interpolator: QuinticSpline):
        assert interpolator.compute_second_derivative(1.5) is not None
        assert len(interpolator.compute_second_derivative(np.array([1.5, 3.5]))) == 2

    def test_generate_interpolator(self):
        interpolator = Interpolator.generate_interpolator(
            interpolation_type=Interpolator.Type.QuinticSpline, x=X, y=Y
        )

        assert isinstance(interpolator, QuinticSpline)

    def test_non_uniform_nodes(self):
        # Nodes that are not uniformly spaced are interpolated with the general
        # implementation, which reproduces the same quartic exactly

        interpolator = QuinticSpline(x=NON_UNIFORM_X, y=NON_UNIFORM_Y)

        assert interpolator.evaluate(1.5) == pytest.approx(0.3125, abs=1e-7)
        assert interpolator.evaluate(4.0) == pytest.approx(210.0, abs=1e-7)
        assert interpolator.compute_derivative(4.0) == pytest.approx(232.0, abs=1e-6)
        assert interpolator.compute_second_derivative(4.0) == pytest.approx(
            186.0, abs=1e-5
        )
