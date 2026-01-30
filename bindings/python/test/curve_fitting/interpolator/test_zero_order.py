# Apache License 2.0

import pytest

from ostk.mathematics.curve_fitting import Interpolator
from ostk.mathematics.curve_fitting.interpolator import ZeroOrder


@pytest.fixture
def interpolator() -> ZeroOrder:
    return ZeroOrder(x=[0.0, 1.0, 2.0, 3.0, 4.0, 5.0], y=[0.0, 3.0, 5.0, 6.0, 9.0, 15.0])


class TestZeroOrder:
    def test_constructor_success(self, interpolator: ZeroOrder):
        assert interpolator is not None
        assert isinstance(interpolator, Interpolator)
        assert isinstance(interpolator, ZeroOrder)

    def test_evaluate_at_data_points(self):
        interpolator = ZeroOrder(
            x=[0.0, 1.0, 2.0, 3.0, 4.0, 5.0], y=[0.0, 3.0, 5.0, 6.0, 9.0, 15.0]
        )

        # At exact data points, should return the value at that point
        assert interpolator.evaluate(0.0) == 0.0
        assert interpolator.evaluate(1.0) == 3.0
        assert interpolator.evaluate(2.0) == 5.0
        assert interpolator.evaluate(3.0) == 6.0
        assert interpolator.evaluate(4.0) == 9.0
        assert interpolator.evaluate(5.0) == 15.0

    def test_evaluate_between_data_points(self):
        interpolator = ZeroOrder(
            x=[0.0, 1.0, 2.0, 3.0, 4.0, 5.0], y=[0.0, 3.0, 5.0, 6.0, 9.0, 15.0]
        )

        # Between data points, should return the previous point's value
        assert interpolator.evaluate(0.5) == 0.0
        assert interpolator.evaluate(1.5) == 3.0
        assert interpolator.evaluate(2.5) == 5.0
        assert interpolator.evaluate(3.5) == 6.0
        assert interpolator.evaluate(4.5) == 9.0

    def test_evaluate_beyond_range(self):
        interpolator = ZeroOrder(
            x=[0.0, 1.0, 2.0, 3.0, 4.0, 5.0], y=[0.0, 3.0, 5.0, 6.0, 9.0, 15.0]
        )

        # Beyond last point should return last point's value
        assert interpolator.evaluate(6.0) == 15.0
        assert interpolator.evaluate(100.0) == 15.0

        # Before first point should return first point's value
        assert interpolator.evaluate(-1.0) == 0.0

    def test_evaluate_vector(self):
        interpolator = ZeroOrder(
            x=[0.0, 1.0, 2.0, 3.0, 4.0, 5.0], y=[0.0, 3.0, 5.0, 6.0, 9.0, 15.0]
        )

        result = interpolator.evaluate(x=[0.5, 1.5, 2.5, 3.5, 4.5])
        assert (result == [0.0, 3.0, 5.0, 6.0, 9.0]).all()

    def test_compute_derivative(self):
        interpolator = ZeroOrder(
            x=[0.0, 1.0, 2.0, 3.0, 4.0, 5.0], y=[0.0, 3.0, 5.0, 6.0, 9.0, 15.0]
        )

        # Derivative of step function should always be 0
        assert interpolator.compute_derivative(0.5) == 0.0
        assert interpolator.compute_derivative(1.5) == 0.0
        assert interpolator.compute_derivative(2.5) == 0.0

    def test_compute_derivative_vector(self):
        interpolator = ZeroOrder(
            x=[0.0, 1.0, 2.0, 3.0, 4.0, 5.0], y=[0.0, 3.0, 5.0, 6.0, 9.0, 15.0]
        )

        result = interpolator.compute_derivative([0.5, 1.5, 2.5])
        assert (result == [0.0, 0.0, 0.0]).all()

    def test_get_interpolation_type(self, interpolator: ZeroOrder):
        assert interpolator.get_interpolation_type() == Interpolator.Type.ZeroOrder

    def test_generate_interpolator(self):
        interpolator = Interpolator.generate_interpolator(
            Interpolator.Type.ZeroOrder,
            x=[0.0, 1.0, 2.0],
            y=[0.0, 2.0, 4.0],
        )

        assert interpolator is not None
        assert interpolator.get_interpolation_type() == Interpolator.Type.ZeroOrder
        assert interpolator.evaluate(0.5) == 0.0
        assert interpolator.evaluate(1.5) == 2.0
