################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           bindings/python/test/geometry/d3/objects/test_linestring.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

import numpy as np
from collections.abc import Iterator, Iterable

import ostk.mathematics as mathematics

from ostk.core.types import String

################################################################################################################################################################

Object = mathematics.geometry.d3.Object
Point = mathematics.geometry.d3.objects.Point
LineString = mathematics.geometry.d3.objects.LineString
Transformation = mathematics.geometry.d3.Transformation

################################################################################################################################################################

def test_geometry_d3_objects_linestring_constructor ():

    point_1: Point = Point(-1.0, 1.0, 1.0)
    point_2: Point = Point(1.0, 1.0, -1.0)
    point_3: Point = Point(1.0, -1.0, 1.0)
    point_4: Point = Point(-1.0, -1.0, 0.0)

    # Construction with Array of Points using python list
    linestring: LineString = LineString([point_1, point_2, point_3, point_4])

    assert linestring is not None
    assert isinstance(linestring, LineString)
    assert isinstance(linestring, Object)
    assert linestring.is_defined()

    # Construction with Array of Points using python tuple
    linestring: LineString = LineString((point_1, point_2, point_3, point_4))

    assert linestring is not None
    assert isinstance(linestring, LineString)
    assert isinstance(linestring, Object)
    assert linestring.is_defined()

    # Construction with Array of Points using python numpy array
    linestring: LineString = LineString(np.array((point_1, point_2, point_3, point_4)))

    assert linestring is not None
    assert isinstance(linestring, LineString)
    assert isinstance(linestring, Object)
    assert linestring.is_defined()

def test_geometry_d3_objects_linestring_empty ():

    linestring: LineString = LineString.empty()

    assert linestring is not None
    assert isinstance(linestring, LineString)
    assert isinstance(linestring, Object)
    assert linestring.is_defined() is False
    assert linestring.is_empty()

def test_geometry_d3_objects_linestring_comparators ():

    point_1: Point = Point(-1.0, 1.0, 0.0)
    point_2: Point = Point(1.0, 1.0, -1.0)

    linestring_1: LineString = LineString([point_1, point_2])
    linestring_2: LineString = LineString((point_1, point_2))
    linestring_3: LineString = LineString(np.array([point_1, point_2]))
    linestring_4: LineString = LineString([point_1])

    assert linestring_1 == linestring_1
    assert linestring_1 == linestring_2
    assert linestring_1 == linestring_3
    assert linestring_1 != linestring_4
    assert linestring_2 != linestring_4
    assert linestring_3 != linestring_4

def test_geometry_d3_objects_linestring_is_near ():

    point_1: Point = Point(-1.0, 1.0, 0.0)
    point_2: Point = Point(1.0, 1.0, 0.0)

    point_3: Point = Point(-0.996, 0.9995, 0.0)
    point_4: Point = Point(0.997, 0.996, 0.0)

    linestring_1: LineString = LineString([point_1, point_2])
    linestring_2: LineString = LineString([point_3, point_4])

    assert linestring_1.is_near(linestring_1, 10.0)
    assert linestring_1.is_near(linestring_1, 0.1)
    assert linestring_1.is_near(linestring_1, 1e-9)

    assert linestring_2.is_near(linestring_2, 10.0)
    assert linestring_2.is_near(linestring_2, 0.1)
    assert linestring_2.is_near(linestring_2, 1e-9)

    assert linestring_1.is_near(linestring_2, 1e-1)
    assert linestring_1.is_near(linestring_2, 1e-2)

    assert linestring_2.is_near(linestring_1, 1e-1)
    assert linestring_2.is_near(linestring_1, 1e-2)

def test_geometry_d3_objects_linestring_getters ():

    point_1: Point = Point(-1.0, 1.0, 0.0)
    point_2: Point = Point(1.0, 1.0, 0.0)

    linestring_1: LineString = LineString([point_1])
    linestring_2: LineString = LineString([point_1, point_2])

    assert LineString.empty().get_point_count() == 0
    assert linestring_1.get_point_count() == 1
    assert linestring_2.get_point_count() == 2

    assert linestring_1.get_point_closest_to(Point(0.0, 0.0, 0.0)) == point_1

    assert linestring_2.get_point_closest_to(Point(0.0, 0.0, 0.0)) == point_1
    assert linestring_2.get_point_closest_to(Point(-0.9, 1.0, 0.0)) == point_1
    assert linestring_2.get_point_closest_to(Point(0.9, 1.0, 0.0)) == point_2

def test_geometry_d3_objects_linestring_len ():

    point_1: Point = Point(-1.0, 1.0, 0.0)
    point_2: Point = Point(1.0, 1.0, 0.0)

    linestring: LineString = LineString([point_1, point_2])

    assert len(linestring) == 2
    assert len(linestring) == linestring.get_point_count()
    assert len(LineString.empty()) == 0

    linestring: LineString = LineString([point_1, point_1])
    assert len(linestring) == 2
    assert len(linestring) == linestring.get_point_count()

def test_geometry_d3_objects_linestring_iter ():

    point_1: Point = Point(-1.0, 1.0, 0.0)
    point_2: Point = Point(1.0, 1.0, 1.0)

    linestring: LineString = LineString([point_1, point_2])

    for point in linestring:

        assert isinstance(point, Point)

    assert iter(linestring) is not None
    assert isinstance(iter(linestring), Iterator)
    assert isinstance(iter(linestring), Iterable)

def test_geometry_d3_objects_linestring_getitem ():

    point_1: Point = Point(-1.0, 1.0, 0.0)
    point_2: Point = Point(1.0, 1.0, 1.0)

    linestring: LineString = LineString([point_1, point_2])

    assert linestring[0] == point_1
    assert linestring[1] == point_2

    assert isinstance(linestring[0], Point)
    assert isinstance(linestring[1], Point)

    with pytest.raises(RuntimeError):

        point = linestring[2]

    linestring_list = list(linestring)

    assert isinstance(linestring_list, list)
    assert isinstance(linestring_list[0], Point)
    assert isinstance(linestring_list[1], Point)
    assert len(linestring_list) == 2

# def test_geometry_d3_objects_linestring_apply_transformation ():

################################################################################################################################################################
