################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           bindings/python/test/geometry/d3/objects/test_point_set.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

import numpy as np

import ostk.mathematics as mathematics

################################################################################################################################################################

Object = mathematics.geometry.d3.Object
Point = mathematics.geometry.d3.objects.Point
PointSet = mathematics.geometry.d3.objects.PointSet
Transformation = mathematics.geometry.d3.Transformation

################################################################################################################################################################

def test_geometry_d3_objects_point_set_constructor ():

    point_1: Point = Point(1.0, 2.0, 1.0)
    point_2: Point = Point(3.0, 4.0, 1.0)

    # Construction using python list
    point_set: PointSet = PointSet([point_1, point_2])

    assert point_set is not None
    assert isinstance(point_set, PointSet)
    assert isinstance(point_set, Object)
    assert point_set.is_defined()

    # Construction using python tuple
    point_set = PointSet((point_1, point_2))

    assert point_set is not None
    assert isinstance(point_set, PointSet)
    assert isinstance(point_set, Object)
    assert point_set.is_defined()

    point_set = PointSet((point_1,))

    assert point_set is not None
    assert isinstance(point_set, PointSet)
    assert isinstance(point_set, Object)
    assert point_set.is_defined()

def test_geometry_d3_objects_point_set_empty ():

    point_set: Pointset = PointSet.empty()

    assert point_set is not None
    assert isinstance(point_set, PointSet)
    assert isinstance(point_set, Object)
    assert point_set.is_defined() is False
    assert point_set.is_empty()

def test_geometry_d3_objects_point_set_comparators ():

    point_1: Point = Point(1.0, 2.0, 1.0)
    point_2: Point = Point(3.0, 4.0, 1.0)

    point_set_1: PointSet = PointSet([point_1, point_2])
    point_set_2: PointSet = PointSet((point_2, point_1))
    point_set_3: PointSet = PointSet([point_2])

    assert point_set_1 == point_set_2
    assert point_set_1 == point_set_2
    assert point_set_3 != point_set_1
    assert point_set_2 != point_set_3

def test_geometry_d3_objects_point_set_get_size ():

    point_1: Point = Point(1.0, 2.0, 1.0)
    point_2: Point = Point(3.0, 4.0, 1.0)

    point_set_1: PointSet = PointSet([point_1, point_2])
    point_set_2: PointSet = PointSet((point_2, point_1))
    point_set_3: PointSet = PointSet([point_2])
    point_set_4: PointSet = PointSet.empty()
    point_set_5: PointSet = PointSet([point_1, point_1])

    assert point_set_1.get_size() == 2
    assert point_set_2.get_size() == 2
    assert point_set_3.get_size() == 1
    assert point_set_4.get_size() == 0
    assert point_set_5.get_size() == 1

# def test_geometry_d3_objects_point_set_is_near ():

# def test_geometry_d3_objects_point_set_get_point_closest_to ():

# def test_geometry_d3_objects_point_set_to_string ():

# def test_geometry_d3_objects_point_set_apply_transformation ():

################################################################################################################################################################
