# Apache License 2.0

import pytest

import numpy as np

from ostk.mathematics.curve_fitting import Interpolator
from ostk.mathematics.curve_fitting.interpolator import CardinalQuinticSpline


# Sampled from f(x) = x^4 - 3 * x^2 + 2, on a uniform grid. At least 8 points are required.

X: list[float] = [0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0]
Y: list[float] = [2.0, 0.0, 6.0, 56.0, 210.0, 552.0, 1190.0, 2256.0, 3906.0, 6320.0]


@pytest.fixture
def interpolator() -> CardinalQuinticSpline:
    return CardinalQuinticSpline(x=X, y=Y)


class TestCardinalQuinticSpline:
    def test_constructor_success(self, interpolator: CardinalQuinticSpline):
        assert interpolator is not None
        assert isinstance(interpolator, Interpolator)
        assert isinstance(interpolator, CardinalQuinticSpline)

    def test_default_constructor_2(self):
        assert CardinalQuinticSpline(y=Y, x_0=0.0, h=1.0) is not None

    def test_constructor_failure(self):
        # At least 8 data points are required

        with pytest.raises(Exception):
            CardinalQuinticSpline(x=X[:7], y=Y[:7])

        with pytest.raises(Exception):
            CardinalQuinticSpline(
                x=[0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0], y=Y
            )

        with pytest.raises(Exception):
            CardinalQuinticSpline(y=Y, x_0=0.0, h=0.0)

    def test_get_interpolation_type(self, interpolator: CardinalQuinticSpline):
        assert (
            interpolator.get_interpolation_type()
            == Interpolator.Type.CardinalQuinticSpline
        )

    def test_evaluate(self, interpolator: CardinalQuinticSpline):
        assert interpolator.evaluate(1.5) is not None
        assert interpolator.evaluate([1.5, 3.5]) is not None
        assert len(interpolator.evaluate(np.array([1.5, 3.5]))) == 2

    def test_evaluate_out_of_domain(self, interpolator: CardinalQuinticSpline):
        with pytest.raises(Exception):
            interpolator.evaluate(-1.0)

    def test_compute_derivative(self, interpolator: CardinalQuinticSpline):
        assert interpolator.compute_derivative(1.5) is not None
        assert len(interpolator.compute_derivative(np.array([1.5, 3.5]))) == 2

    def test_compute_second_derivative(self, interpolator: CardinalQuinticSpline):
        assert interpolator.compute_second_derivative(1.5) is not None
        assert len(interpolator.compute_second_derivative(np.array([1.5, 3.5]))) == 2

    def test_generate_interpolator(self):
        interpolator = Interpolator.generate_interpolator(
            interpolation_type=Interpolator.Type.CardinalQuinticSpline, x=X, y=Y
        )

        assert isinstance(interpolator, CardinalQuinticSpline)
