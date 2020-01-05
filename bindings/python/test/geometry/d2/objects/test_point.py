################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           bindings/python/test/geometry/d2/objects/test_point.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import ostk.mathematics as mathematics

################################################################################################################################################################

Point = mathematics.geometry.d2.objects.Point

################################################################################################################################################################

def test_geometry_d2_objects_point_constructor ():

    point: Point = Point(1.0, 2.0)

    assert point is not None

def test_geometry_d2_objects_point_undefined ():

    assert Point.undefined() is not None

def test_geometry_d2_objects_point_origin ():

    assert Point.origin() is not None

################################################################################################################################################################
