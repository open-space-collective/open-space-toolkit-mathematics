# Apache License 2.0

import pytest

import numpy as np

from ostk.mathematics.geometry import Angle
from ostk.mathematics.geometry.d3.transformation.rotation import Quaternion
from ostk.mathematics.geometry.d3.transformation.rotation import RotationVector
from ostk.mathematics.geometry.d3.transformation.rotation import RotationMatrix
from ostk.mathematics.geometry.d3.transformation.rotation import EulerAngle


@pytest.fixture
def euler_angle() -> EulerAngle:
    return EulerAngle.unit()


class TestEulerAngle:
    def test_constructor_success(self):
        EulerAngle(
            phi=Angle.zero(),
            theta=Angle.zero(),
            psi=Angle.zero(),
            axis_sequence=EulerAngle.AxisSequence.ZYX,
        )

        EulerAngle(
            vector=(0.0, 0.0, 0.0),
            angle_unit=Angle.Unit.Degree,
            axis_sequence=EulerAngle.AxisSequence.ZYX,
        )

    def test_operators_success(self, euler_angle: EulerAngle):
        assert (euler_angle == euler_angle) is True
        assert (euler_angle != euler_angle) is False

    def test_str_success(self, euler_angle: EulerAngle):
        assert str(euler_angle) is not None

    def test_repr_success(self, euler_angle: EulerAngle):
        assert repr(euler_angle) is not None

    def test_is_defined_success(self, euler_angle: EulerAngle):
        assert euler_angle.is_defined()

    def test_is_unitary_success(self, euler_angle: EulerAngle):
        assert euler_angle.is_unitary()

    def test_is_near_success(self, euler_angle: EulerAngle):
        assert euler_angle.is_near(
            euler_angle=euler_angle,
            angular_tolerance=Angle.zero(),
        )

    def test_properties_success(self, euler_angle: EulerAngle):
        assert euler_angle.phi == Angle.degrees(0.0)
        assert euler_angle.theta == Angle.degrees(0.0)
        assert euler_angle.psi == Angle.degrees(0.0)
        assert euler_angle.axis_sequence == EulerAngle.AxisSequence.ZYX

    def test_to_vector_success(self, euler_angle: EulerAngle):
        assert np.array_equal(
            euler_angle.to_vector(angle_unit=Angle.Unit.Degree), np.array((0.0, 0.0, 0.0))
        )

    def test_to_string_success(self, euler_angle: EulerAngle):
        assert euler_angle.to_string() == "[0, 0, 0] (ZYX)"
        assert euler_angle.to_string(angle_unit=Angle.Unit.Degree) == "[0, 0, 0] (ZYX)"

    def test_undefined_success(self):
        assert not EulerAngle.undefined().is_defined()

    def test_unit_success(self, euler_angle: EulerAngle):
        assert EulerAngle.unit() == euler_angle

    def test_xyz_success(self):
        assert EulerAngle.xyz(
            phi=Angle.zero(),
            theta=Angle.zero(),
            psi=Angle.zero(),
        ) == EulerAngle(
            phi=Angle.zero(),
            theta=Angle.zero(),
            psi=Angle.zero(),
            axis_sequence=EulerAngle.AxisSequence.XYZ,
        )

    def test_zxy_success(self):
        assert EulerAngle.zxy(
            phi=Angle.zero(),
            theta=Angle.zero(),
            psi=Angle.zero(),
        ) == EulerAngle(
            phi=Angle.zero(),
            theta=Angle.zero(),
            psi=Angle.zero(),
            axis_sequence=EulerAngle.AxisSequence.ZXY,
        )

    def test_zyx_success(self):
        assert EulerAngle.zyx(
            phi=Angle.zero(),
            theta=Angle.zero(),
            psi=Angle.zero(),
        ) == EulerAngle(
            phi=Angle.zero(),
            theta=Angle.zero(),
            psi=Angle.zero(),
            axis_sequence=EulerAngle.AxisSequence.ZYX,
        )

    def test_quaternion_success(self):
        assert (
            EulerAngle.quaternion(
                quaternion=Quaternion.unit(),
                axis_sequence=EulerAngle.AxisSequence.ZYX,
            )
            == EulerAngle.unit()
        )

    def test_rotation_vector_success(self):
        assert (
            EulerAngle.rotation_vector(
                rotation_vector=RotationVector.unit(),
                axis_sequence=EulerAngle.AxisSequence.ZYX,
            )
            == EulerAngle.unit()
        )

    def test_rotation_matrix_success(self):
        assert (
            EulerAngle.rotation_matrix(
                rotation_matrix=RotationMatrix.unit(),
                axis_sequence=EulerAngle.AxisSequence.ZYX,
            )
            == EulerAngle.unit()
        )
