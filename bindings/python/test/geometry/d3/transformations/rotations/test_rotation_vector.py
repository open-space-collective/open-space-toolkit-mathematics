################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           bindings/python/test/geometry/d3/transformations/rotations/test_rotation_vector.py
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

def test_geometry_d3_transformations_rotations_rotation_vector ():

    rv: RotationVector = RotationVector(numpy.array([[0.0], [0.0], [1.0]], dtype=float), Angle.zero())

    assert (rv == rv) is True
    assert (rv != rv) is False

    assert rv.is_defined() is True

    # assert numpy.array_equal(rv.get_axis(), numpy.array([[0.0], [0.0], [1.0]], dtype=float))
    assert rv.get_angle() == Angle.zero()

    assert RotationVector.undefined().is_defined() is False
    assert RotationVector.unit().is_defined() is True
    assert RotationVector.quaternion(Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion.Format.XYZS)).is_defined() is True
    # assert RotationVector.RotationMatrix().is_defined() is True

################################################################################################################################################################
