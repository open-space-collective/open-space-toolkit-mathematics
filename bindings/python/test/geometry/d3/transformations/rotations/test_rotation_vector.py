################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           bindings/python/test/geometry/d3/transformations/rotations/test_rotation_vector.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import numpy

from Library.Mathematics import Geometry

################################################################################################################################################################

Angle = Geometry.Angle
Quaternion = Geometry.D3.Transformations.Rotations.Quaternion
RotationVector = Geometry.D3.Transformations.Rotations.RotationVector

################################################################################################################################################################

def test_geometry_d3_transformations_rotations_rotation_vector ():

    rv: RotationVector = RotationVector(numpy.array([[0.0], [0.0], [1.0]], dtype=float), Angle.Zero())

    assert (rv == rv) is True
    assert (rv != rv) is False

    assert rv.isDefined() is True

    assert numpy.array_equal(rv.getAxis(), numpy.array([[0.0], [0.0], [1.0]], dtype=float))
    assert rv.getAngle() == Angle.Zero()

    assert RotationVector.Undefined().isDefined() is False
    assert RotationVector.Unit().isDefined() is True
    assert RotationVector.Quaternion(Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion.Format.XYZS)).isDefined() is True
    # assert RotationVector.RotationMatrix().isDefined() is True

################################################################################################################################################################
