# Apache License 2.0

import pytest

from ostk.mathematics.curve_fitting import Interpolator
from ostk.mathematics.curve_fitting.interpolator import BarycentricRational


@pytest.fixture
def interpolator() -> BarycentricRational:
    return BarycentricRational(
        x=[0.0, 1.0, 2.0, 4.0, 5.0, 6.0], y=[0.0, 3.0, 6.0, 9.0, 17.0, 5.0]
    )


class TestBarycentricRational:
    def test_constructor_success(self, interpolator: BarycentricRational):
        assert interpolator is not None
        assert isinstance(interpolator, Interpolator)
        assert isinstance(interpolator, BarycentricRational)

    def test_evaluate(self, interpolator: BarycentricRational):

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
