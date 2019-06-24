# coding=utf-8

################################################################################################################################################################

# @project        Library ▸ Mathematics
# @file           LibraryMathematicsPy/Geometry/D3/Transformations/Rotations/Geometry.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import numpy

from Library.Core import Types

from LibraryMathematicsPy import Geometry

Angle = Geometry.Angle
Quaternion = Geometry.D3.Transformations.Rotations.Quaternion
RotationVector = Geometry.D3.Transformations.Rotations.RotationVector

################################################################################################################################################################

q = Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion.Format.XYZS)

assert (q == q) is True
assert (q != q) is False

print('q:', q)

assert q.isDefined() is True
assert q.isUnitary() is True
assert q.isNear(q, Angle.Degrees(0.0)) is True

assert q.x() == 0.0
assert q.y() == 0.0
assert q.z() == 0.0
assert q.s() == 1.0
assert numpy.array_equal(q.getVectorPart(), numpy.array([[0.0], [0.0], [0.0]], dtype=float))
assert q.getScalarPart() == 1.0
assert q.toNormalized() == q
assert q.toConjugate() == q
assert q.toInverse() == q
# print('pow:', q.pow())
# print('exp:', q.exp())
# print('log:', q.log())
assert q.norm() == 1.0
assert q.crossMultiply(q) == q
assert q.dotMultiply(q) == q
assert numpy.array_equal(q.rotateVector(numpy.array([[0.0], [0.0], [1.0]], dtype=float)), numpy.array([[0.0], [0.0], [1.0]], dtype=float))
assert numpy.array_equal(q.toVector(Quaternion.Format.XYZS), numpy.array([[0.0], [0.0], [0.0], [1.0]], dtype=float)) is True
assert q.toString(Quaternion.Format.XYZS) == "[0.0, 0.0, 0.0, 1.0]"

q.normalize()

assert q == q

q.conjugate()

assert q.toString(Quaternion.Format.XYZS) == "[-0.0, -0.0, -0.0, 1.0]"

q.inverse()

assert q.toString(Quaternion.Format.XYZS) == "[0.0, 0.0, 0.0, 1.0]"

q.rectify()

assert q.toString(Quaternion.Format.XYZS) == "[0.0, 0.0, 0.0, 1.0]"

assert Quaternion.Undefined().isDefined() is False
assert Quaternion.Unit().isDefined() is True
assert Quaternion.XYZS(0.0, 0.0, 0.0, 1.0).isDefined() is True
assert Quaternion.RotationVector(RotationVector(numpy.array([[0.0], [0.0], [1.0]], dtype=float), Angle.Zero())).isDefined() is True
# RotationMatrix
assert Quaternion.Parse("[0.0, 0.0, 0.0, 1.0]", Quaternion.Format.XYZS).isDefined() is True

################################################################################################################################################################
