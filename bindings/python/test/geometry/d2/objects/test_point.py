################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           bindings/python/test/geometry/d2/objects/test_point.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import Library.Mathematics as Mathematics

################################################################################################################################################################

Point = Mathematics.Geometry.D2.Objects.Point

################################################################################################################################################################

def test_geometry_d2_objects_point_constructor ():

    point: Point = Point(1.0, 2.0)

    assert point is not None

def test_geometry_d2_objects_point_undefined ():

    assert Point.Undefined() is not None

def test_geometry_d2_objects_point_origin ():

    assert Point.Origin() is not None

################################################################################################################################################################
