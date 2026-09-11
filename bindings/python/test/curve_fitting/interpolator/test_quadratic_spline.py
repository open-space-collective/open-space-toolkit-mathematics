# Apache License 2.0

import pytest

import numpy as np

from ostk.mathematics.curve_fitting import Interpolator
from ostk.mathematics.curve_fitting.interpolator import QuadraticSpline

# Sampled from f(x) = x^2 - 3 * x + 2, on a uniform and on a ragged grid


@pytest.fixture
def interpolator(
    x: list[float],
    y: list[float],
) -> QuadraticSpline:
    return QuadraticSpline(
        x=x,
        y=y,
    )


@pytest.fixture
def x() -> list[float]:
    return [0.0, 1.0, 2.0, 3.0, 4.0, 5.0]


@pytest.fixture
def y() -> list[float]:
    return [2.0, 0.0, 0.0, 2.0, 6.0, 12.0]


@pytest.fixture
def x_non_uniform() -> list[float]:
    return [0.0, 1.0, 2.0, 4.0, 5.0, 7.0]


@pytest.fixture
def y_non_uniform() -> list[float]:
    return [2.0, 0.0, 0.0, 6.0, 12.0, 30.0]


class TestQuadraticSpline:
    def test_constructor_success(
        self,
        interpolator: QuadraticSpline,
    ):
        assert interpolator is not None
        assert isinstance(interpolator, Interpolator)
        assert isinstance(interpolator, QuadraticSpline)

    def test_default_constructor_2(
        self,
        y: list[float],
    ):
        assert (
            QuadraticSpline(
                y=y,
                x_0=0.0,
                h=1.0,
            )
            is not None
        )

    def test_constructor_failure(
        self,
        x: list[float],
        y: list[float],
    ):
        with pytest.raises(Exception):
            QuadraticSpline(
                x=x[:2],
                y=y[:2],
            )

        with pytest.raises(Exception):
            QuadraticSpline(
                x=[0.0, 2.0, 1.0, 3.0, 4.0, 5.0],
                y=y,
            )

        with pytest.raises(Exception):
            QuadraticSpline(
                y=y,
                x_0=0.0,
                h=0.0,
            )

    def test_get_interpolation_type(
        self,
        interpolator: QuadraticSpline,
    ):
        assert interpolator.get_interpolation_type() == Interpolator.Type.QuadraticSpline

    def test_evaluate(
        self,
        interpolator: QuadraticSpline,
    ):
        assert interpolator.evaluate(1.5) is not None
        assert interpolator.evaluate([1.5, 3.5]) is not None
        assert len(interpolator.evaluate(np.array([1.5, 3.5]))) == 2

    def test_evaluate_out_of_domain(
        self,
        interpolator: QuadraticSpline,
    ):
        with pytest.raises(Exception):
            interpolator.evaluate(-1.0)

    def test_compute_derivative(
        self,
        interpolator: QuadraticSpline,
    ):
        assert interpolator.compute_derivative(1.5) is not None
        assert len(interpolator.compute_derivative(np.array([1.5, 3.5]))) == 2

    def test_generate_interpolator(
        self,
        x: list[float],
        y: list[float],
    ):
        interpolator = Interpolator.generate_interpolator(
            interpolation_type=Interpolator.Type.QuadraticSpline,
            x=x,
            y=y,
        )

        assert isinstance(interpolator, QuadraticSpline)

    def test_non_uniform_nodes(
        self,
        x_non_uniform: list[float],
        y_non_uniform: list[float],
    ):
        # Nodes that are not uniformly spaced are interpolated with the general
        # implementation, which reproduces the same quadratic exactly

        interpolator = QuadraticSpline(
            x=x_non_uniform,
            y=y_non_uniform,
        )

        assert interpolator.evaluate(1.5) == pytest.approx(-0.25, abs=1e-9)
        assert interpolator.evaluate(6.5) == pytest.approx(24.75, abs=1e-9)
        assert interpolator.compute_derivative(6.5) == pytest.approx(10.0, abs=1e-9)
