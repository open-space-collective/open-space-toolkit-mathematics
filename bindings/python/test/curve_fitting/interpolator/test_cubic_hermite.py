# Apache License 2.0

import pytest

import numpy as np

from ostk.mathematics.curve_fitting import Interpolator
from ostk.mathematics.curve_fitting.interpolator import CubicHermite


# Sampled from f(x) = x^3 - 2 * x^2 + 3 * x - 1, on a non-uniform grid

X: list[float] = [0.0, 1.0, 2.0, 4.0, 5.0, 7.0]
Y: list[float] = [-1.0, 1.0, 5.0, 43.0, 89.0, 265.0]
DYDX: list[float] = [3.0, 2.0, 7.0, 35.0, 58.0, 122.0]


@pytest.fixture
def interpolator() -> CubicHermite:
    return CubicHermite(x=X, y=Y, dydx=DYDX)


class TestCubicHermite:
    def test_constructor_success(self, interpolator: CubicHermite):
        assert interpolator is not None
        assert isinstance(interpolator, Interpolator)
        assert isinstance(interpolator, CubicHermite)

    def test_constructor_failure(self):
        with pytest.raises(Exception):
            CubicHermite(x=X[:-1], y=Y, dydx=DYDX)

        with pytest.raises(Exception):
            CubicHermite(x=X, y=Y, dydx=DYDX[:-1])

    def test_get_interpolation_type(self, interpolator: CubicHermite):
        assert interpolator.get_interpolation_type() == Interpolator.Type.CubicHermite

    def test_evaluate(self, interpolator: CubicHermite):
        assert interpolator.evaluate(1.5) is not None
        assert interpolator.evaluate([1.5, 3.0]) is not None
        assert len(interpolator.evaluate(np.array([1.5, 3.0]))) == 2

    def test_evaluate_out_of_domain(self, interpolator: CubicHermite):
        with pytest.raises(Exception):
            interpolator.evaluate(-1.0)

    def test_compute_derivative(self, interpolator: CubicHermite):
        assert interpolator.compute_derivative(1.5) is not None
        assert len(interpolator.compute_derivative(np.array([1.5, 3.0]))) == 2
