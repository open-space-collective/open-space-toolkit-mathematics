# Apache License 2.0

import pytest

from ostk.mathematics.curve_fitting import Interpolator
from ostk.mathematics.curve_fitting.interpolator import Linear


@pytest.fixture
def interpolator() -> Linear:
    return Linear(x=[0.0, 1.0, 2.0, 4.0, 5.0, 6.0], y=[0.0, 3.0, 6.0, 9.0, 17.0, 5.0])


class TestLinear:
    def test_constructor_success(self, interpolator: Linear):
        assert interpolator is not None
        assert isinstance(interpolator, Interpolator)
        assert isinstance(interpolator, Linear)

    def test_evaluate(self):
        interpolator = Linear(
            x=[0.0, 1.0, 2.0, 4.0, 5.0, 6.0], y=[0.0, 3.0, 6.0, 9.0, 17.0, 5.0]
        )

        assert interpolator.evaluate(0.0) == 0.0
        assert interpolator.evaluate(1.0) == 3.0
        assert interpolator.evaluate(2.0) == 6.0
        assert interpolator.evaluate(4.0) == 9.0
        assert interpolator.evaluate(5.0) == 17.0
        assert interpolator.evaluate(6.0) == 5.0

        assert (
            interpolator.evaluate(x=[0.0, 1.0, 2.0, 4.0, 5.0, 6.0])
            == [0.0, 3.0, 6.0, 9.0, 17.0, 5.0]
        ).all()
