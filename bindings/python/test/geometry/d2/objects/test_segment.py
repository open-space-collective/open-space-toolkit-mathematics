################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           bindings/python/test/geometry/d2/objects/test_segment.py
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
Segment = mathematics.geometry.d2.objects.Segment
Transformation = mathematics.geometry.d2.Transformation

################################################################################################################################################################

def test_geometry_d2_objects_segment_constructor ():

    point_1: Point = Point(-1.0, 1.0)
    point_2: Point = Point(1.0, 1.0)

    segment: Segment = Segment(point_1, point_2)

    assert segment is not None
    assert isinstance(segment, Segment)
    assert isinstance(segment, Object)
    assert segment.is_defined()

    segment: Segment = Segment(point_1, point_1)

    assert segment is not None
    assert isinstance(segment, Segment)
    assert isinstance(segment, Object)
    assert segment.is_defined()

def test_geometry_d2_objects_segment_defined ():

    segment: Segment = Segment.undefined()

    assert segment is not None
    assert isinstance(segment, Segment)
    assert isinstance(segment, Object)
    assert segment.is_defined() is False

def test_geometry_d2_objects_segment_degenerate ():

    point_1: Point = Point(-1.0, 1.0)
    point_2: Point = Point(1.0, 1.0)

    segment_1: Segment = Segment(point_1, point_2)
    segment_2: Segment = Segment(point_1, point_1)

    assert segment_1.is_degenerate() is False
    assert segment_2.is_degenerate() is True

def test_geometry_d2_objects_segment_comparators ():

    point_1: Point = Point(-1.0, 1.0)
    point_2: Point = Point(1.0, 1.0)

    segment_1: Segment = Segment(point_1, point_2)
    segment_2: Segment = Segment(point_1, point_1)

    assert segment_1 == segment_1
    assert segment_1 != segment_2

def test_geometry_d2_objects_segment_getters ():

    point_1: Point = Point(-1.0, 1.0)
    point_2: Point = Point(1.0, 1.0)

    segment: Segment = Segment(point_1, point_2)

    assert isinstance(segment.get_first_point(), Point)
    assert segment.get_first_point() == point_1

    assert isinstance(segment.get_second_point(), Point)
    assert segment.get_second_point() == point_2

    assert isinstance(segment.get_center(), Point)
    assert segment.get_center() == Point(0.0, 1.0)

    assert isinstance(segment.get_direction(), np.ndarray)
    assert np.array_equal(segment.get_direction(), np.array((1.0, 0.0)))

    assert segment.get_length() == 2.0

# def test_geometry_d2_objects_segment_to_string ():

# def test_geometry_d2_objects_segment_apply_transformation ():

################################################################################################################################################################
