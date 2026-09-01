# Apache License 2.0

import pytest

import numpy as np

from ostk.mathematics.curve_fitting import Interpolator
from ostk.mathematics.curve_fitting.interpolator import CardinalCubicHermite


# Sampled from f(x) = x^3 - 2 * x^2 + 3 * x - 1, on a uniform grid

X: list[float] = [0.0, 1.0, 2.0, 3.0, 4.0, 5.0]
Y: list[float] = [-1.0, 1.0, 5.0, 17.0, 43.0, 89.0]
DYDX: list[float] = [3.0, 2.0, 7.0, 18.0, 35.0, 58.0]


@pytest.fixture
def interpolator() -> CardinalCubicHermite:
    return CardinalCubicHermite(x=X, y=Y, dydx=DYDX)


class TestCardinalCubicHermite:
    def test_constructor_success(self, interpolator: CardinalCubicHermite):
        assert interpolator is not None
        assert isinstance(interpolator, Interpolator)
        assert isinstance(interpolator, CardinalCubicHermite)

    def test_default_constructor_2(self):
        assert CardinalCubicHermite(y=Y, dydx=DYDX, x_0=0.0, h=1.0) is not None

    def test_constructor_failure(self):
        with pytest.raises(Exception):
            CardinalCubicHermite(x=X, y=Y, dydx=DYDX[:-1])

        with pytest.raises(Exception):
            CardinalCubicHermite(x=[0.0, 1.0, 2.0, 4.0, 5.0, 7.0], y=Y, dydx=DYDX)

        with pytest.raises(Exception):
            CardinalCubicHermite(y=Y, dydx=DYDX, x_0=0.0, h=0.0)

    def test_get_interpolation_type(self, interpolator: CardinalCubicHermite):
        assert (
            interpolator.get_interpolation_type()
            == Interpolator.Type.CardinalCubicHermite
        )

    def test_evaluate(self, interpolator: CardinalCubicHermite):
        assert interpolator.evaluate(1.5) is not None
        assert interpolator.evaluate([1.5, 3.5]) is not None
        assert len(interpolator.evaluate(np.array([1.5, 3.5]))) == 2

    def test_evaluate_out_of_domain(self, interpolator: CardinalCubicHermite):
        with pytest.raises(Exception):
            interpolator.evaluate(-1.0)

    def test_compute_derivative(self, interpolator: CardinalCubicHermite):
        assert interpolator.compute_derivative(1.5) is not None
        assert len(interpolator.compute_derivative(np.array([1.5, 3.5]))) == 2
