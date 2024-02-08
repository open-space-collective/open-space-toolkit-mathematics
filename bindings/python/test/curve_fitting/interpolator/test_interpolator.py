# Apache License 2.0

import pytest

from ostk.mathematics.curve_fitting import Interpolator


@pytest.fixture
def interpolation_type() -> Interpolator.InterpolationType:
    return Interpolator.InterpolationType.Linear


@pytest.fixture
def interpolator(interpolation_type: Interpolator.InterpolationType) -> Interpolator:
    class MyInterpolator(Interpolator):
        def evaluate(self, x: list[float]) -> list[float]:
            return x

        def evaluate(self, x: float) -> float:
            return x

    return MyInterpolator(interpolation_type)


class TestInterpolator:
    def test_subclass(self, interpolator: Interpolator):
        assert interpolator is not None
        assert isinstance(interpolator, Interpolator)

    def test_get_interpolation_type(
        self,
        interpolator: Interpolator,
        interpolation_type: Interpolator.InterpolationType,
    ):
        assert interpolator.get_interpolation_type() == interpolation_type

    def test_generate_interpolators(self):
        interpolator: Interpolator = Interpolator.generate_interpolator(
            Interpolator.InterpolationType.BarycentricRational,
            x=[0.0, 1.0, 2.0, 4.0, 5.0, 6.0],
            y=[0.0, 3.0, 6.0, 9.0, 17.0, 5.0],
        )

        assert interpolator is not None
        assert isinstance(interpolator, Interpolator)

        interpolator: Interpolator = Interpolator.generate_interpolator(
            Interpolator.InterpolationType.CubicSpline,
            x=[0.0, 1.0, 2.0, 3.0, 4.0, 5.0],
            y=[0.0, 3.0, 6.0, 9.0, 17.0, 5.0],
        )

        assert interpolator is not None
        assert isinstance(interpolator, Interpolator)

        interpolator: Interpolator = Interpolator.generate_interpolator(
            Interpolator.InterpolationType.Linear,
            x=[0.0, 1.0, 2.0, 4.0, 5.0, 6.0],
            y=[0.0, 3.0, 6.0, 9.0, 17.0, 5.0],
        )

        assert interpolator is not None
        assert isinstance(interpolator, Interpolator)
