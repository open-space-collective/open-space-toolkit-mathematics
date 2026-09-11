# Apache License 2.0

import pytest

import numpy as np

from ostk.mathematics.curve_fitting import Interpolator
from ostk.mathematics.curve_fitting.interpolator import QuinticHermite

# Sampled from f(x) = x^4 - 3 * x^2 + 2, on a ragged and on a uniform grid


@pytest.fixture
def interpolator(
    x: list[float],
    y: list[float],
    dydx: list[float],
    d2ydx2: list[float],
) -> QuinticHermite:
    return QuinticHermite(
        x=x,
        y=y,
        dydx=dydx,
        d2ydx2=d2ydx2,
    )


@pytest.fixture
def x() -> list[float]:
    return [0.0, 1.0, 2.0, 4.0, 5.0, 7.0]


@pytest.fixture
def y() -> list[float]:
    return [2.0, 0.0, 6.0, 210.0, 552.0, 2256.0]


@pytest.fixture
def dydx() -> list[float]:
    return [0.0, -2.0, 20.0, 232.0, 470.0, 1330.0]


@pytest.fixture
def d2ydx2() -> list[float]:
    return [-6.0, 6.0, 42.0, 186.0, 294.0, 582.0]


@pytest.fixture
def x_uniform() -> list[float]:
    return [0.0, 1.0, 2.0, 3.0, 4.0, 5.0]


@pytest.fixture
def y_uniform() -> list[float]:
    return [2.0, 0.0, 6.0, 56.0, 210.0, 552.0]


@pytest.fixture
def dydx_uniform() -> list[float]:
    return [0.0, -2.0, 20.0, 90.0, 232.0, 470.0]


@pytest.fixture
def d2ydx2_uniform() -> list[float]:
    return [-6.0, 6.0, 42.0, 102.0, 186.0, 294.0]


class TestQuinticHermite:
    def test_constructor_success(
        self,
        interpolator: QuinticHermite,
    ):
        assert interpolator is not None
        assert isinstance(interpolator, Interpolator)
        assert isinstance(interpolator, QuinticHermite)

    def test_default_constructor_2(
        self,
        y_uniform: list[float],
        dydx_uniform: list[float],
        d2ydx2_uniform: list[float],
    ):
        assert (
            QuinticHermite(
                y=y_uniform,
                dydx=dydx_uniform,
                d2ydx2=d2ydx2_uniform,
                x_0=0.0,
                h=1.0,
            )
            is not None
        )

    def test_constructor_failure(
        self,
        x: list[float],
        y: list[float],
        dydx: list[float],
        d2ydx2: list[float],
    ):
        with pytest.raises(Exception):
            QuinticHermite(
                x=x[:-1],
                y=y,
                dydx=dydx,
                d2ydx2=d2ydx2,
            )

        with pytest.raises(Exception):
            QuinticHermite(
                x=x,
                y=y,
                dydx=dydx[:-1],
                d2ydx2=d2ydx2,
            )

        with pytest.raises(Exception):
            QuinticHermite(
                x=x,
                y=y,
                dydx=dydx,
                d2ydx2=d2ydx2[:-1],
            )

    def test_get_interpolation_type(
        self,
        interpolator: QuinticHermite,
    ):
        assert interpolator.get_interpolation_type() == Interpolator.Type.QuinticHermite

    def test_evaluate(
        self,
        interpolator: QuinticHermite,
    ):
        assert interpolator.evaluate(1.5) is not None
        assert interpolator.evaluate([1.5, 3.0]) is not None
        assert len(interpolator.evaluate(np.array([1.5, 3.0]))) == 2

    def test_evaluate_out_of_domain(
        self,
        interpolator: QuinticHermite,
    ):
        with pytest.raises(Exception):
            interpolator.evaluate(-1.0)

    def test_compute_derivative(
        self,
        interpolator: QuinticHermite,
    ):
        assert interpolator.compute_derivative(1.5) is not None
        assert len(interpolator.compute_derivative(np.array([1.5, 3.0]))) == 2

    def test_compute_second_derivative(
        self,
        interpolator: QuinticHermite,
    ):
        assert interpolator.compute_second_derivative(1.5) is not None
        assert len(interpolator.compute_second_derivative(np.array([1.5, 3.0]))) == 2

    def test_uniform_nodes(
        self,
        x_uniform: list[float],
        y_uniform: list[float],
        dydx_uniform: list[float],
        d2ydx2_uniform: list[float],
    ):
        # Uniformly spaced nodes are interpolated with the cardinal implementation, which
        # reproduces the same quartic exactly

        interpolator = QuinticHermite(
            x=x_uniform,
            y=y_uniform,
            dydx=dydx_uniform,
            d2ydx2=d2ydx2_uniform,
        )

        assert interpolator.evaluate(1.5) == pytest.approx(0.3125, abs=1e-9)
        assert interpolator.compute_derivative(3.5) == pytest.approx(150.5, abs=1e-9)

        # Both constructors describe the same interpolant

        other = QuinticHermite(
            y=y_uniform,
            dydx=dydx_uniform,
            d2ydx2=d2ydx2_uniform,
            x_0=0.0,
            h=1.0,
        )

        assert other.evaluate(1.5) == pytest.approx(interpolator.evaluate(1.5), abs=1e-12)

    def test_compute_second_derivative_uniform_nodes(
        self,
        x_uniform: list[float],
        y_uniform: list[float],
        dydx_uniform: list[float],
        d2ydx2_uniform: list[float],
    ):
        # The second derivative of uniformly spaced nodes depends on a Boost.Math fix that ships
        # with Boost 1.93. Built against an older Boost, the call raises instead of returning a
        # wrong value.

        interpolator = QuinticHermite(
            x=x_uniform,
            y=y_uniform,
            dydx=dydx_uniform,
            d2ydx2=d2ydx2_uniform,
        )

        try:
            second_derivative = interpolator.compute_second_derivative(3.5)
        except RuntimeError as error:
            assert "Boost 1.93" in str(error)

            with pytest.raises(RuntimeError):
                interpolator.compute_second_derivative(np.array([1.5, 3.5]))
        else:
            assert second_derivative == pytest.approx(141.0, abs=1e-8)
            assert len(interpolator.compute_second_derivative(np.array([1.5, 3.5]))) == 2
