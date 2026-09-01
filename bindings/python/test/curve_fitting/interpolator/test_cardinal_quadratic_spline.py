# Apache License 2.0

import pytest

import numpy as np

from ostk.mathematics.curve_fitting import Interpolator
from ostk.mathematics.curve_fitting.interpolator import CardinalQuadraticSpline


# Sampled from f(x) = x^2 - 3 * x + 2, on a uniform grid

X: list[float] = [0.0, 1.0, 2.0, 3.0, 4.0, 5.0]
Y: list[float] = [2.0, 0.0, 0.0, 2.0, 6.0, 12.0]


@pytest.fixture
def interpolator() -> CardinalQuadraticSpline:
    return CardinalQuadraticSpline(x=X, y=Y)


class TestCardinalQuadraticSpline:
    def test_constructor_success(self, interpolator: CardinalQuadraticSpline):
        assert interpolator is not None
        assert isinstance(interpolator, Interpolator)
        assert isinstance(interpolator, CardinalQuadraticSpline)

    def test_default_constructor_2(self):
        assert CardinalQuadraticSpline(y=Y, x_0=0.0, h=1.0) is not None

    def test_constructor_failure(self):
        with pytest.raises(Exception):
            CardinalQuadraticSpline(x=X[:2], y=Y[:2])

        with pytest.raises(Exception):
            CardinalQuadraticSpline(x=[0.0, 1.0, 2.0, 4.0, 5.0, 7.0], y=Y)

        with pytest.raises(Exception):
            CardinalQuadraticSpline(y=Y, x_0=0.0, h=0.0)

    def test_get_interpolation_type(self, interpolator: CardinalQuadraticSpline):
        assert (
            interpolator.get_interpolation_type()
            == Interpolator.Type.CardinalQuadraticSpline
        )

    def test_evaluate(self, interpolator: CardinalQuadraticSpline):
        assert interpolator.evaluate(1.5) is not None
        assert interpolator.evaluate([1.5, 3.5]) is not None
        assert len(interpolator.evaluate(np.array([1.5, 3.5]))) == 2

    def test_evaluate_out_of_domain(self, interpolator: CardinalQuadraticSpline):
        with pytest.raises(Exception):
            interpolator.evaluate(-1.0)

    def test_compute_derivative(self, interpolator: CardinalQuadraticSpline):
        assert interpolator.compute_derivative(1.5) is not None
        assert len(interpolator.compute_derivative(np.array([1.5, 3.5]))) == 2

    def test_generate_interpolator(self):
        interpolator = Interpolator.generate_interpolator(
            interpolation_type=Interpolator.Type.CardinalQuadraticSpline, x=X, y=Y
        )

        assert isinstance(interpolator, CardinalQuadraticSpline)
