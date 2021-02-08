################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           bindings/python/test/geometry/d2/objects/test_multipolygon.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

import numpy as np

import ostk.mathematics as mathematics

from ostk.core.types import String

################################################################################################################################################################

Object = mathematics.geometry.d2.Object
Point = mathematics.geometry.d2.objects.Point
PointSet = mathematics.geometry.d2.objects.PointSet
Polygon = mathematics.geometry.d2.objects.Polygon
MultiPolygon = mathematics.geometry.d2.objects.MultiPolygon
LineString = mathematics.geometry.d2.objects.LineString
Segment = mathematics.geometry.d2.objects.Segment
Transformation = mathematics.geometry.d2.Transformation

################################################################################################################################################################

def test_geometry_d2_objects_multipolygon_constructor ():

    def square (center: Point) -> Polygon:
        '''
        Creates and Return a Square centered in center
        and with length 1.0 with no inner rings.
        '''
        point_1: Point = center + [0.5, 0.5]
        point_2: Point = center + [0.5, -0.5]
        point_3: Point = center + [-0.5, -0.5]
        point_4: Point = center + [-0.5, 0.5]

        return Polygon([point_1, point_2, point_3, point_4])

    square_1: Polygon = square(Point(0.0, 0.0))
    square_2: Polygon = square(Point(0.0, 10.0))

    # Construction using a python list of polygons
    multipolygon: MultiPolygon = MultiPolygon([square_1, square_2])

    assert multipolygon is not None
    assert isinstance(multipolygon, MultiPolygon)
    assert isinstance(multipolygon, Object)
    assert multipolygon.is_defined()

    # Construction using a python tuple of polygons
    multipolygon: MultiPolygon = MultiPolygon((square_1, square_2))

    assert multipolygon is not None
    assert isinstance(multipolygon, MultiPolygon)
    assert isinstance(multipolygon, Object)
    assert multipolygon.is_defined()

    # Construction using a python numpy array of polygons
    multipolygon: MultiPolygon = MultiPolygon(np.array((square_1, square_2)))

    assert multipolygon is not None
    assert isinstance(multipolygon, MultiPolygon)
    assert isinstance(multipolygon, Object)
    assert multipolygon.is_defined()

    # Construction using polygon static constructor
    multipolygon: MultiPolygon = MultiPolygon.polygon(square_1)

    assert multipolygon is not None
    assert isinstance(multipolygon, MultiPolygon)
    assert isinstance(multipolygon, Object)
    assert multipolygon.is_defined()

    # Construction using an array of one polygon
    multipolygon: MultiPolygon = MultiPolygon([square_1])

    assert multipolygon is not None
    assert isinstance(multipolygon, MultiPolygon)
    assert isinstance(multipolygon, Object)
    assert multipolygon.is_defined()

def test_geometry_d2_objects_multipolygon_comparators() :

    def square (center: Point) -> Polygon:
        '''
        Creates and Return a Square centered in center
        and with length 1.0 with no inner rings.
        '''
        point_1: Point = center + [0.5, 0.5]
        point_2: Point = center + [0.5, -0.5]
        point_3: Point = center + [-0.5, -0.5]
        point_4: Point = center + [-0.5, 0.5]

        return Polygon([point_1, point_2, point_3, point_4])

    square_1: Polygon = square(Point(0.0, 0.0))
    square_2: Polygon = square(Point(0.0, 10.0))

    # Multiple MultiPolygons
    multipolygon_1: MultiPolygon = MultiPolygon([square_1, square_2])
    multipolygon_2: MultiPolygon = MultiPolygon([square_1])
    multipolygon_3: MultiPolygon = MultiPolygon.polygon(square_1)

    assert multipolygon_1 == multipolygon_1
    assert multipolygon_1 != multipolygon_2
    assert multipolygon_1 != multipolygon_3
    assert multipolygon_2 == multipolygon_3

def test_geometry_d2_objects_multipolygon_undefined ():

    multipolygon: MultiPolygon = MultiPolygon.undefined()

    assert multipolygon is not None
    assert isinstance(multipolygon, MultiPolygon)
    assert isinstance(multipolygon, Object)
    assert multipolygon.is_defined() is False

# def test_geometry_d2_objects_multipoolygon_contains ():

def test_geometry_d2_objects_multipoolygon_getters ():

    def square (center: Point) -> Polygon:
        '''
        Creates and Return a Square centered in center
        and with length 1.0 with no inner rings.
        '''
        point_1: Point = center + [0.5, 0.5]
        point_2: Point = center + [0.5, -0.5]
        point_3: Point = center + [-0.5, -0.5]
        point_4: Point = center + [-0.5, 0.5]

        return Polygon([point_1, point_2, point_3, point_4])

    square_1: Polygon = square(Point(0.0, 0.0))
    square_2: Polygon = square(Point(0.0, 10.0))

    # Multiple Polygons
    multipolygon: MultiPolygon = MultiPolygon([square_1, square_2])

    assert multipolygon.get_polygon_count() == 2
    assert multipolygon.get_polygons()[0] == square_1
    assert multipolygon.get_polygons()[-1] == square_2
    # assert multipolygon.get_convex_hull()

    # One Polygon
    multipolygon: MultiPolygon = MultiPolygon.polygon(square_1)

    assert multipolygon.get_polygon_count() == 1
    assert multipolygon.get_polygons()[0] == square_1
    assert multipolygon.get_convex_hull() == square_1

# def test_geometry_d2_objects_multipolygon_union_with() :

# def test_geometry_d2_objects_multipolygon_to_string ():

# def test_geometry_d2_objects_multipolygon_apply_transformation ():

################################################################################################################################################################
