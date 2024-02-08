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

@pytest.mark.parametrize("interpolation_type, x, y", [
    (Interpolator.InterpolationType.BarycentricRational, [0.0, 1.0, 2.0, 4.0, 5.0, 6.0], [0.0, 3.0, 6.0, 9.0, 17.0, 5.0]),
    (Interpolator.InterpolationType.CubicSpline, [0.0, 1.0, 2.0, 3.0, 4.0, 5.0], [0.0, 3.0, 6.0, 9.0, 17.0, 5.0]),
    (Interpolator.InterpolationType.Linear, [0.0, 1.0, 2.0, 4.0, 5.0, 6.0], [0.0, 3.0, 6.0, 9.0, 17.0, 5.0])
])
def test_generate_interpolators(self, interpolation_type: Interpolator.Type, x: list[float], y: list[float]):
    interpolator: Interpolator = Interpolator.generate_interpolator(
        interpolator_type=interpolator_type,
        x=x,
        y=y,
    )

    assert interpolator is not None
    assert isinstance(interpolator, Interpolator)
