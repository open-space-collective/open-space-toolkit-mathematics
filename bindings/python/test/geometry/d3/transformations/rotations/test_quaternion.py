################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           bindings/python/test/geometry/d3/transformations/rotations/test_quaternion.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

from ostk.mathematics import geometry

################################################################################################################################################################

Angle = geometry.Angle
Quaternion = geometry.d3.transformations.rotations.Quaternion
RotationVector = geometry.d3.transformations.rotations.RotationVector

################################################################################################################################################################

@pytest.fixture
def quaternion () -> Quaternion:

    return Quaternion.xyzs(0.0, 0.0, 0.0, 1.0)

################################################################################################################################################################

class TestQuaternion:

    def test_misc_success (self):

        q: Quaternion = Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion.Format.XYZS)

        assert q.is_defined() is True
        assert q.is_unitary() is True
        assert q.is_near(q, Angle.degrees(0.0)) is True

        assert q.x() == 0.0
        assert q.y() == 0.0
        assert q.z() == 0.0
        assert q.s() == 1.0
        # assert numpy.array_equal(q.get_vector_part(), numpy.array([[0.0], [0.0], [0.0]], dtype=float))
        assert q.get_scalar_part() == 1.0
        assert q.to_normalized() == q
        assert q.to_conjugate() == q
        assert q.to_inverse() == q
        # print('pow:', q.pow())
        # print('exp:', q.exp())
        # print('log:', q.log())
        assert q.norm() == 1.0
        assert q.cross_multiply(q) == q
        assert q.dot_multiply(q) == q
        # assert numpy.array_equal(q.rotate_vector(numpy.array([[0.0], [0.0], [1.0]], dtype=float)), numpy.array([[0.0], [0.0], [1.0]], dtype=float))
        # assert numpy.array_equal(q.to_vector(Quaternion.Format.XYZS), numpy.array([[0.0], [0.0], [0.0], [1.0]], dtype=float)) is True
        assert q.to_string(Quaternion.Format.XYZS) == "[0.0, 0.0, 0.0, 1.0]"

        q.normalize()

        assert q == q

        q.conjugate()

        assert q.to_string(Quaternion.Format.XYZS) == "[-0.0, -0.0, -0.0, 1.0]"

        q.inverse()

        assert q.to_string(Quaternion.Format.XYZS) == "[0.0, 0.0, 0.0, 1.0]"

        q.rectify()

        assert q.to_string(Quaternion.Format.XYZS) == "[0.0, 0.0, 0.0, 1.0]"

        assert Quaternion.undefined().is_defined() is False
        assert Quaternion.unit().is_defined() is True
        assert Quaternion.xyzs(0.0, 0.0, 0.0, 1.0).is_defined() is True
        # assert Quaternion.rotation_vector(RotationVector(numpy.array([[0.0], [0.0], [1.0]], dtype=float), Angle.zero())).is_defined() is True
        # RotationMatrix
        assert Quaternion.parse("[0.0, 0.0, 0.0, 1.0]", Quaternion.Format.XYZS).is_defined() is True

    def test_operators_success (self, quaternion: Quaternion):

        assert (quaternion == quaternion) is True
        assert (quaternion != quaternion) is False

        assert (quaternion + quaternion) == Quaternion.xyzs(0.0, 0.0, 0.0, 2.0)

        quaternion_2 = quaternion
        quaternion_2 += quaternion
        assert quaternion_2 == Quaternion.xyzs(0.0, 0.0, 0.0, 2.0)

        assert (quaternion * 1.0) == quaternion
        assert (1.0 * quaternion) == quaternion

################################################################################################################################################################
