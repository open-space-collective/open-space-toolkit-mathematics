# Apache License 2.0

import pytest

from ostk.mathematics.geometry.d3.transformation.rotation import Quaternion
from ostk.mathematics.geometry.d3.transformation.rotation import RotationMatrix
from ostk.mathematics.geometry.d3.transformation.rotation import EulerAngle


@pytest.fixture
def rotation_matrix() -> RotationMatrix:
    return RotationMatrix.unit()


class TestRotationMatrix:
    def test_is_defined_success(self, rotation_matrix: RotationMatrix):
        assert rotation_matrix.is_defined() is True

    def test_quaternion_success(self, rotation_matrix: RotationMatrix):
        assert RotationMatrix.quaternion(Quaternion.unit()) == rotation_matrix

    def test_euler_angle_success(self, rotation_matrix: RotationMatrix):
        assert RotationMatrix.euler_angle(EulerAngle.unit()) == rotation_matrix

    def test_getters(self, rotation_matrix: RotationMatrix):

        assert rotation_matrix.get_column_at(0) is not None
        assert rotation_matrix.get_row_at(1) is not None
        assert rotation_matrix.get_matrix() is not None
