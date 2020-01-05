################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           bindings/python/test/geometry/d3/transformations/rotations/test_quaternion.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import numpy

from ostk.mathematics import geometry

################################################################################################################################################################

Angle = geometry.Angle
Quaternion = geometry.d3.transformations.rotations.Quaternion
RotationVector = geometry.d3.transformations.rotations.RotationVector

################################################################################################################################################################

def test_geometry_d3_transformations_rotations_quaternion ():

    q: Quaternion = Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion.Format.XYZS)

    assert (q == q) is True
    assert (q != q) is False

    assert q.is_defined() is True
    assert q.is_unitary() is True
    assert q.is_near(q, Angle.degrees(0.0)) is True

    assert q.x() == 0.0
    assert q.y() == 0.0
    assert q.z() == 0.0
    assert q.s() == 1.0
    assert numpy.array_equal(q.get_vector_part(), numpy.array([[0.0], [0.0], [0.0]], dtype=float))
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
    assert numpy.array_equal(q.rotate_vector(numpy.array([[0.0], [0.0], [1.0]], dtype=float)), numpy.array([[0.0], [0.0], [1.0]], dtype=float))
    assert numpy.array_equal(q.to_vector(Quaternion.Format.XYZS), numpy.array([[0.0], [0.0], [0.0], [1.0]], dtype=float)) is True
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
    assert Quaternion.rotation_vector(RotationVector(numpy.array([[0.0], [0.0], [1.0]], dtype=float), Angle.zero())).is_defined() is True
    # RotationMatrix
    assert Quaternion.parse("[0.0, 0.0, 0.0, 1.0]", Quaternion.Format.XYZS).is_defined() is True

################################################################################################################################################################
