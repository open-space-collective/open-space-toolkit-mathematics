# Apache License 2.0

import pytest

from ostk.mathematics.curve_fitting import Interpolator


@pytest.fixture
def interpolation_type() -> Interpolator.Type:
    return Interpolator.Type.Linear


@pytest.fixture
def interpolator(interpolation_type: Interpolator.Type) -> Interpolator:
    class MyInterpolator(Interpolator):
        def evaluate(self, x: list[float]) -> list[float]:
            return x

        def evaluate(self, x: float) -> float:
            return x

    return MyInterpolator(interpolation_type=interpolation_type)


class TestInterpolator:
    def test_subclass(self, interpolator: Interpolator):
        assert interpolator is not None
        assert isinstance(interpolator, Interpolator)

    def test_get_interpolation_type(
        self,
        interpolator: Interpolator,
        interpolation_type: Interpolator.Type,
    ):
        assert interpolator.get_interpolation_type() == interpolation_type

    @pytest.mark.parametrize(
        "parametrized_interpolation_type, x, y",
        [
            (
                Interpolator.Type.BarycentricRational,
                [0.0, 1.0, 2.0, 4.0, 5.0, 6.0],
                [0.0, 3.0, 6.0, 9.0, 17.0, 5.0],
            ),
            (
                Interpolator.Type.CubicSpline,
                [0.0, 1.0, 2.0, 3.0, 4.0, 5.0],
                [0.0, 3.0, 6.0, 9.0, 17.0, 5.0],
            ),
            (
                Interpolator.Type.Linear,
                [0.0, 1.0, 2.0, 4.0, 5.0, 6.0],
                [0.0, 3.0, 6.0, 9.0, 17.0, 5.0],
            ),
        ],
    )
    def test_generate_interpolators(
        self,
        parametrized_interpolation_type: Interpolator.Type,
        x: list[float],
        y: list[float],
    ):
        interpolator: Interpolator = Interpolator.generate_interpolator(
            interpolation_type=parametrized_interpolation_type,
            x=x,
            y=y,
        )

        assert interpolator is not None
        assert isinstance(interpolator, Interpolator)
        assert interpolator.get_interpolation_type() == parametrized_interpolation_type
