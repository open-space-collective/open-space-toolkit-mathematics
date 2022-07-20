################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           bindings/python/test/geometry/d3/transformations/rotations/test_quaternion.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

import numpy as np

from ostk.mathematics import geometry

################################################################################################################################################################

Angle = geometry.Angle
Quaternion = geometry.d3.transformations.rotations.Quaternion
RotationVector = geometry.d3.transformations.rotations.RotationVector
RotationMatrix = geometry.d3.transformations.rotations.RotationMatrix

################################################################################################################################################################

@pytest.fixture
def quaternion () -> Quaternion:

    return Quaternion.xyzs(0.0, 0.0, 0.0, 1.0)

################################################################################################################################################################

class TestQuaternion:

    def test_constructors_success (self, quaternion: Quaternion):

        assert Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion.Format.XYZS) == quaternion
        assert Quaternion(np.array((0.0, 0.0, 0.0, 1.0)), Quaternion.Format.XYZS) == quaternion
        assert Quaternion(np.array((0.0, 0.0, 0.0)), 1.0) == quaternion
        assert Quaternion(quaternion) == quaternion

    def test_operators_success (self, quaternion: Quaternion):

        assert (quaternion == quaternion) is True
        assert (quaternion != quaternion) is False

        assert (quaternion + quaternion) == Quaternion.xyzs(0.0, 0.0, 0.0, 2.0)

        quaternion_2 = Quaternion(quaternion)
        quaternion_2 += quaternion
        assert quaternion_2 == Quaternion.xyzs(0.0, 0.0, 0.0, 2.0)

        assert (quaternion * 1.0) == quaternion
        assert (1.0 * quaternion) == quaternion

        assert (quaternion ** 1.0) == quaternion

    def test_is_defined_success (self, quaternion: Quaternion):

        assert quaternion.is_defined() is True

    def test_is_unitary_success (self, quaternion: Quaternion):

        assert quaternion.is_unitary() is True

    def test_is_near_success (self, quaternion: Quaternion):

        assert quaternion.is_near(quaternion, Angle.zero()) is True

    def test_getter_success (self, quaternion: Quaternion):

        assert quaternion.x() == 0.0
        assert quaternion.y() == 0.0
        assert quaternion.z() == 0.0
        assert quaternion.s() == 1.0

    def test_get_vector_part_success (self, quaternion: Quaternion):

        assert np.array_equal(quaternion.get_vector_part(), np.array((0.0, 0.0, 0.0))) is True

    def test_get_scalar_part_success (self, quaternion: Quaternion):

        assert quaternion.get_scalar_part() == 1.0

    def test_to_normalized_success (self, quaternion: Quaternion):

        assert quaternion.to_normalized() == quaternion

    def test_to_conjugate_success (self, quaternion: Quaternion):

        assert quaternion.to_conjugate() == quaternion

    def test_to_inverse_success (self, quaternion: Quaternion):

        assert quaternion.to_inverse() == quaternion

    def test_exp_success (self, quaternion: Quaternion):

        assert quaternion.exp() == quaternion

    def test_log_success (self, quaternion: Quaternion):

        assert quaternion.log() == Quaternion.xyzs(0.0, 0.0, 0.0, 0.0)

    def test_pow_success (self, quaternion: Quaternion):

        assert quaternion.pow(1.0) == quaternion

    def test_norm_success (self, quaternion: Quaternion):

        assert quaternion.norm() == 1.0

    def test_cross_multiply_success (self, quaternion: Quaternion):

        assert quaternion.cross_multiply(quaternion) == quaternion

    def test_dot_multiply_success (self, quaternion: Quaternion):

        assert quaternion.dot_multiply(quaternion) == quaternion

    def test_dot_product_success (self, quaternion: Quaternion):

        assert quaternion.dot_product(quaternion) == 1.0

    def test_rotate_vector_success (self, quaternion: Quaternion):

        assert np.array_equal(quaternion.rotate_vector(np.array((0.0, 0.0, 1.0))), np.array((0.0, 0.0, 1.0)))

    def test_to_vector_success (self, quaternion: Quaternion):

        assert np.array_equal(quaternion.to_vector(Quaternion.Format.XYZS), np.array((0.0, 0.0, 0.0, 1.0))) is True

    def test_to_string_success (self, quaternion: Quaternion):

        assert quaternion.to_string() == '[0.0, 0.0, 0.0, 1.0]'

    def test_to_string_success_with_format (self, quaternion: Quaternion):

        assert quaternion.to_string(Quaternion.Format.XYZS) == '[0.0, 0.0, 0.0, 1.0]'

    def test_normalize_success (self, quaternion: Quaternion):

        quaternion_2 = Quaternion(quaternion)
        quaternion_2.normalize()
        assert quaternion_2 == quaternion

    def test_conjugate_success (self, quaternion: Quaternion):

        quaternion_2 = Quaternion(quaternion)
        quaternion_2.conjugate()
        assert quaternion_2 == quaternion

    def test_inverse_success (self, quaternion: Quaternion):

        quaternion_2 = Quaternion(quaternion)
        quaternion_2.inverse()
        assert quaternion_2 == quaternion

    def test_rectify_success (self, quaternion: Quaternion):

        quaternion_2 = Quaternion(quaternion)
        quaternion_2.rectify()
        assert quaternion_2 == quaternion

    def test_angular_difference_with_success (self, quaternion: Quaternion):

        assert quaternion.angular_difference_with(quaternion) == Angle.zero()

    def test_undefined_success (self):

        assert Quaternion.undefined().is_defined() is False

    def test_unit_success (self, quaternion: Quaternion):

        assert Quaternion.unit() == quaternion

    def test_xyzs_success (self, quaternion: Quaternion):

        assert Quaternion.xyzs(0.0, 0.0, 0.0, 1.0) == quaternion

    def test_rotation_vector_success (self, quaternion: Quaternion):

        assert Quaternion.rotation_vector(RotationVector(np.array((0.0, 0.0, 1.0)), Angle.zero())) == quaternion

    def test_rotation_matrix_success (self, quaternion: Quaternion):

        assert Quaternion.rotation_matrix(RotationMatrix.rz(Angle.zero())) == quaternion

    def test_parse_success (self, quaternion: Quaternion):

        assert Quaternion.parse("[0.0, 0.0, 0.0, 1.0]", Quaternion.Format.XYZS) == quaternion

    def test_shortest_rotation_success (self, quaternion: Quaternion):

        assert Quaternion.shortest_rotation(np.array((1.0, 0.0, 0.0)), np.array((1.0, 0.0, 0.0))) == quaternion

    def test_lerp_success (self, quaternion: Quaternion):

        assert Quaternion.lerp(quaternion, quaternion, 0.0) == quaternion

    def test_nlerp_success (self, quaternion: Quaternion):

        assert Quaternion.nlerp(quaternion, quaternion, 0.0) == quaternion

    def test_slerp_success (self, quaternion: Quaternion):

        assert Quaternion.slerp(quaternion, quaternion, 0.0) == quaternion

################################################################################################################################################################
