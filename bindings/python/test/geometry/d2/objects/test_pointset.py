################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           bindings/python/test/geometry/d2/objects/test_pointset.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

import numpy as np

import ostk.mathematics as mathematics

################################################################################################################################################################

Object = mathematics.geometry.d2.Object
Point = mathematics.geometry.d2.objects.Point
PointSet = mathematics.geometry.d2.objects.PointSet
Transformation = mathematics.geometry.d2.Transformation

################################################################################################################################################################

def test_geometry_d2_objects_pointset_constructor ():

    point_1: Point = Point(1.0, 2.0)
    point_2: Point = Point(3.0, 4.0)

    # Construction using python list
    pointset: PointSet = PointSet([point_1, point_2])

    assert pointset is not None
    assert isinstance(pointset, PointSet)
    assert isinstance(pointset, Object)
    assert pointset.is_defined()

    # Construction using python tuple
    pointset = PointSet((point_1, point_2))

    assert pointset is not None
    assert isinstance(pointset, PointSet)
    assert isinstance(pointset, Object)
    assert pointset.is_defined()

    pointset = PointSet((point_1,))

    assert pointset is not None
    assert isinstance(pointset, PointSet)
    assert isinstance(pointset, Object)
    assert pointset.is_defined()

def test_geometry_d2_objects_pointset_empty ():

    pointset: Pointset = PointSet.empty()

    assert pointset is not None
    assert isinstance(pointset, PointSet)
    assert isinstance(pointset, Object)
    assert pointset.is_defined() is False
    assert pointset.is_empty()

def test_geometry_d2_objects_pointset_comparators ():

    point_1: Point = Point(1.0, 2.0)
    point_2: Point = Point(3.0, 4.0)

    pointset_1: PointSet = PointSet([point_1, point_2])
    pointset_2: PointSet = PointSet((point_2, point_1))
    pointset_3: PointSet = PointSet([point_2])

    assert pointset_1 == pointset_2
    assert pointset_1 == pointset_2
    assert pointset_3 != pointset_1
    assert pointset_2 != pointset_3

def test_geometry_d2_objects_pointset_get_size ():

    point_1: Point = Point(1.0, 2.0)
    point_2: Point = Point(3.0, 4.0)

    pointset_1: PointSet = PointSet([point_1, point_2])
    pointset_2: PointSet = PointSet((point_2, point_1))
    pointset_3: PointSet = PointSet([point_2])
    pointset_4: PointSet = PointSet.empty()
    pointset_5: PointSet = PointSet([point_1, point_1])

    assert pointset_1.get_size() == 2
    assert pointset_2.get_size() == 2
    assert pointset_3.get_size() == 1
    assert pointset_4.get_size() == 0
    assert pointset_5.get_size() == 1

# def test_geometry_d2_objects_pointset_is_near ():

# def test_geometry_d2_objects_pointset_get_point_closest_to ():

# def test_geometry_d2_objects_pointset_to_string ():

# def test_geometry_d2_objects_pointset_apply_transformation ():

################################################################################################################################################################
