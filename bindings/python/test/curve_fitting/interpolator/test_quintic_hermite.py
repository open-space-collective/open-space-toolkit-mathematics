# Apache License 2.0

import pytest

import numpy as np

from ostk.mathematics.curve_fitting import Interpolator
from ostk.mathematics.curve_fitting.interpolator import QuinticHermite

# Sampled from f(x) = x^4 - 3 * x^2 + 2, on a ragged and on a uniform grid

X: list[float] = [0.0, 1.0, 2.0, 4.0, 5.0, 7.0]
Y: list[float] = [2.0, 0.0, 6.0, 210.0, 552.0, 2256.0]
DYDX: list[float] = [0.0, -2.0, 20.0, 232.0, 470.0, 1330.0]
D2YDX2: list[float] = [-6.0, 6.0, 42.0, 186.0, 294.0, 582.0]

UNIFORM_X: list[float] = [0.0, 1.0, 2.0, 3.0, 4.0, 5.0]
UNIFORM_Y: list[float] = [2.0, 0.0, 6.0, 56.0, 210.0, 552.0]
UNIFORM_DYDX: list[float] = [0.0, -2.0, 20.0, 90.0, 232.0, 470.0]
UNIFORM_D2YDX2: list[float] = [-6.0, 6.0, 42.0, 102.0, 186.0, 294.0]


@pytest.fixture
def interpolator() -> QuinticHermite:
    return QuinticHermite(x=X, y=Y, dydx=DYDX, d2ydx2=D2YDX2)


class TestQuinticHermite:
    def test_constructor_success(self, interpolator: QuinticHermite):
        assert interpolator is not None
        assert isinstance(interpolator, Interpolator)
        assert isinstance(interpolator, QuinticHermite)

    def test_default_constructor_2(self):
        assert (
            QuinticHermite(
                y=UNIFORM_Y,
                dydx=UNIFORM_DYDX,
                d2ydx2=UNIFORM_D2YDX2,
                x_0=0.0,
                h=1.0,
            )
            is not None
        )

    def test_constructor_failure(self):
        with pytest.raises(Exception):
            QuinticHermite(x=X[:-1], y=Y, dydx=DYDX, d2ydx2=D2YDX2)

        with pytest.raises(Exception):
            QuinticHermite(x=X, y=Y, dydx=DYDX[:-1], d2ydx2=D2YDX2)

        with pytest.raises(Exception):
            QuinticHermite(x=X, y=Y, dydx=DYDX, d2ydx2=D2YDX2[:-1])

    def test_get_interpolation_type(self, interpolator: QuinticHermite):
        assert interpolator.get_interpolation_type() == Interpolator.Type.QuinticHermite

    def test_evaluate(self, interpolator: QuinticHermite):
        assert interpolator.evaluate(1.5) is not None
        assert interpolator.evaluate([1.5, 3.0]) is not None
        assert len(interpolator.evaluate(np.array([1.5, 3.0]))) == 2

    def test_evaluate_out_of_domain(self, interpolator: QuinticHermite):
        with pytest.raises(Exception):
            interpolator.evaluate(-1.0)

    def test_compute_derivative(self, interpolator: QuinticHermite):
        assert interpolator.compute_derivative(1.5) is not None
        assert len(interpolator.compute_derivative(np.array([1.5, 3.0]))) == 2

    def test_compute_second_derivative(self, interpolator: QuinticHermite):
        assert interpolator.compute_second_derivative(1.5) is not None
        assert len(interpolator.compute_second_derivative(np.array([1.5, 3.0]))) == 2

    def test_uniform_nodes(self):
        # Uniformly spaced nodes are interpolated with the cardinal implementation, which
        # reproduces the same quartic exactly

        interpolator = QuinticHermite(
            x=UNIFORM_X, y=UNIFORM_Y, dydx=UNIFORM_DYDX, d2ydx2=UNIFORM_D2YDX2
        )

        assert interpolator.evaluate(1.5) == pytest.approx(0.3125, abs=1e-9)
        assert interpolator.compute_derivative(3.5) == pytest.approx(150.5, abs=1e-9)
        assert interpolator.compute_second_derivative(3.5) == pytest.approx(
            141.0, abs=1e-8
        )

        # Both constructors describe the same interpolant

        other = QuinticHermite(
            y=UNIFORM_Y, dydx=UNIFORM_DYDX, d2ydx2=UNIFORM_D2YDX2, x_0=0.0, h=1.0
        )

        assert other.evaluate(1.5) == pytest.approx(interpolator.evaluate(1.5), abs=1e-12)
