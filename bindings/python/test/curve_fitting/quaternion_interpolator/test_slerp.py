# Apache License 2.0

import numpy as np
import pytest

from ostk.mathematics.geometry import Angle
from ostk.mathematics.geometry.d3.transformation.rotation import Quaternion
from ostk.mathematics.geometry.d3.transformation.rotation import RotationVector

from ostk.mathematics.curve_fitting.quaternion_interpolator import SLERP


def z_rotation(angle_in_degrees: float) -> Quaternion:
    return Quaternion.rotation_vector(
        RotationVector(np.array((0.0, 0.0, 1.0)), Angle.degrees(angle_in_degrees))
    )


@pytest.fixture
def q0() -> Quaternion:
    return z_rotation(0.0)


@pytest.fixture
def q1() -> Quaternion:
    return z_rotation(90.0)


@pytest.fixture
def interpolator(
    q0: Quaternion,
    q1: Quaternion,
) -> SLERP:
    return SLERP(
        x=np.array([0.0, 1.0]),
        quaternions=[q0, q1],
    )


class TestSLERP:
    def test_constructor_success(
        self,
        interpolator: SLERP,
    ):
        assert interpolator is not None
        assert isinstance(interpolator, SLERP)

    def test_constructor_mismatched_sizes(
        self,
        q0: Quaternion,
        q1: Quaternion,
    ):
        with pytest.raises(RuntimeError):
            SLERP(
                x=np.array([0.0, 1.0, 2.0]),
                quaternions=[q0, q1],
            )

    def test_constructor_too_few_points(
        self,
        q0: Quaternion,
    ):
        with pytest.raises(RuntimeError):
            SLERP(
                x=np.array([0.0]),
                quaternions=[q0],
            )

    def test_constructor_non_monotonic_x(
        self,
        q0: Quaternion,
        q1: Quaternion,
    ):
        with pytest.raises(RuntimeError):
            SLERP(
                x=np.array([0.0, 2.0, 1.0]),
                quaternions=[q0, z_rotation(45.0), q1],
            )

    def test_constructor_duplicate_x(
        self,
        q0: Quaternion,
        q1: Quaternion,
    ):
        with pytest.raises(RuntimeError):
            SLERP(
                x=np.array([0.0, 1.0, 1.0]),
                quaternions=[q0, z_rotation(45.0), q1],
            )

    def test_evaluate_single(
        self,
        interpolator: SLERP,
    ):
        result = interpolator.evaluate(0.5)

        assert result is not None
        assert isinstance(result, Quaternion)
        assert result.is_defined()

    def test_evaluate_endpoints(
        self,
        interpolator: SLERP,
        q0: Quaternion,
        q1: Quaternion,
    ):
        assert interpolator.evaluate(0.0).is_near(q0, Angle.degrees(1e-9))
        assert interpolator.evaluate(1.0).is_near(q1, Angle.degrees(1e-9))

    def test_evaluate_vector(
        self,
        interpolator: SLERP,
    ):
        results = interpolator.evaluate(np.array([0.0, 0.5, 1.0]))

        assert len(results) == 3
        for result in results:
            assert isinstance(result, Quaternion)
            assert result.is_defined()

    def test_get_quaternions(
        self,
        interpolator: SLERP,
    ):
        quaternions = interpolator.get_quaternions()

        assert len(quaternions) == 2
        for quaternion in quaternions:
            assert isinstance(quaternion, Quaternion)
