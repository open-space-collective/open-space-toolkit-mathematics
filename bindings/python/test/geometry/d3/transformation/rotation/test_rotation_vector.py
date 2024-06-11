# Apache License 2.0

import pytest

import numpy as np

from ostk.mathematics.geometry import Angle
from ostk.mathematics.geometry.d3.transformation.rotation import Quaternion
from ostk.mathematics.geometry.d3.transformation.rotation import RotationVector
from ostk.mathematics.geometry.d3.transformation.rotation import EulerAngle


@pytest.fixture
def rotation_vector() -> RotationVector:
    return RotationVector.unit()


class TestRotationVector:
    def test_constructor_success(self):
        RotationVector(
            axis=(0.0, 0.0, 1.0),
            angle=Angle.zero(),
        )

        RotationVector(
            vector=(0.0, 0.0, 1.0),
            angle_unit=Angle.Unit.Degree,
        )

    def test_operators_success(self, rotation_vector: RotationVector):
        assert (rotation_vector == rotation_vector) is True
        assert (rotation_vector != rotation_vector) is False

    def test_get_angle_success(self, rotation_vector: RotationVector):
        assert rotation_vector.get_angle() == Angle.zero()

    def test_is_defined_success(self, rotation_vector: RotationVector):
        assert rotation_vector.is_defined() is True

    def test_is_defined_success(self, rotation_vector: RotationVector):
        rotation_vector.rectify()

    def test_quaternion_success(self, rotation_vector: RotationVector):
        assert RotationVector.quaternion(Quaternion.unit()) == rotation_vector

    def test_euler_angle_success(self, rotation_vector: RotationVector):
        assert RotationVector.euler_angle(EulerAngle.unit()) == rotation_vector
