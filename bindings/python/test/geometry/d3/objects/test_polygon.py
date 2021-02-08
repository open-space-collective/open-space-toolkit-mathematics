################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           bindings/python/test/geometry/d3/objects/test_polygon.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

import numpy as np

import ostk.mathematics as mathematics

from ostk.core.types import String

################################################################################################################################################################

Point3d = mathematics.geometry.d3.objects.Point
Point2d = mathematics.geometry.d2.objects.Point
Polygon3d = mathematics.geometry.d3.objects.Polygon
Object3d = mathematics.geometry.d3.Object
Polygon2d = mathematics.geometry.d2.objects.Polygon
Transformation = mathematics.geometry.d3.Transformation

################################################################################################################################################################

def test_geometry_d3_objects_polygon ():

    ## Constructors

    # Construct a Polygon2d
    point_1: Point2d = Point2d(-1.0, 1.0)
    point_2: Point2d = Point2d(1.0, 1.0)
    point_3: Point2d = Point2d(1.0, -1.0)
    point_4: Point2d = Point2d(-1.0, -1.0)

    polygon2d: Polygon2d = Polygon2d([point_1, point_2, point_3, point_4])

    assert polygon2d is not None
    assert isinstance(polygon2d, Polygon2d)
    assert polygon2d.is_defined()

    # Construct a Polygon3d using python list constructors for vectors
    point_5: Point3d =  Point3d(1.0, 1.0, 1.0)
    vector_1 = [1.0, 0.0, 0.0]
    vector_2 = [0.0, 1.0, 0.0]

    polygon3d_1: Polygon3d = Polygon3d(polygon2d, point_5, vector_1, vector_2)

    assert polygon3d_1 is not None
    assert isinstance(polygon3d_1, Polygon3d)
    assert isinstance(polygon3d_1, Object3d)
    assert polygon3d_1.is_defined()

    # Construct a Polygon3d using python tuple constructors for vectors
    point_5: Point3d =  Point3d(1.0, 1.0, 1.0)
    vector_1 = (1.0, 0.0, 0.0)
    vector_2 = (0.0, 1.0, 0.0)

    polygon3d_2: Polygon3d = Polygon3d(polygon2d, point_5, vector_1, vector_2)

    assert polygon3d_2 is not None
    assert isinstance(polygon3d_2, Polygon3d)
    assert isinstance(polygon3d_2, Object3d)
    assert polygon3d_2.is_defined()

    # Construct a Polygon3d using python numpy array constructors for vectors
    point_5: Point3d =  Point3d(1.0, 1.0, 1.0)
    vector_3 = np.array((1.0, 0.0, 0.0))
    vector_4 = (0.0, 1.0, 1.0)

    polygon3d_3: Polygon3d = Polygon3d(polygon2d, point_5, vector_3, vector_4)

    assert polygon3d_3 is not None
    assert isinstance(polygon3d_3, Polygon3d)
    assert isinstance(polygon3d_3, Object3d)
    assert polygon3d_3.is_defined()

    # Construct using the static "undefined" method
    polygon3d_4: Polygon3d = Polygon3d.undefined()

    assert polygon3d_4 is not None
    assert isinstance(polygon3d_4, Polygon3d)
    assert isinstance(polygon3d_4, Object3d)
    assert polygon3d_4.is_defined() is False

    ## Comparators

    assert polygon3d_1 == polygon3d_1
    assert polygon3d_2 == polygon3d_2
    assert polygon3d_3 == polygon3d_3
    assert polygon3d_1 == polygon3d_2
    assert polygon3d_3 != polygon3d_1
    assert polygon3d_3 != polygon3d_2

    ## get_polygon2d

    polygon2d_1: Polygon2d = polygon3d_1.get_polygon2d()
    polygon2d_2: Polygon2d = polygon3d_2.get_polygon2d()
    polygon2d_3: Polygon2d = polygon3d_2.get_polygon2d()

    assert polygon2d_1 is not None
    assert polygon2d_2 is not None
    assert polygon2d_3 is not None

    assert isinstance(polygon2d_1, Polygon2d)
    assert isinstance(polygon2d_2, Polygon2d)
    assert isinstance(polygon2d_3, Polygon2d)

    assert polygon2d_1 == polygon2d_2
    assert polygon2d_2 == polygon2d_3

    ## get_origin

    origin_1: Point3d = polygon3d_1.get_origin()
    origin_2: Point3d = polygon3d_2.get_origin()
    origin_3: Point3d = polygon3d_3.get_origin()

    assert origin_1 == point_5
    assert origin_2 == point_5
    assert origin_3 == point_5

    ## get_x_axis

    xaxis_1: np.ndarray = polygon3d_1.get_x_axis()
    xaxis_2: np.ndarray = polygon3d_2.get_x_axis()
    xaxis_3: np.ndarray = polygon3d_3.get_x_axis()

    assert np.array_equal(xaxis_1, np.array(vector_1))
    assert np.array_equal(xaxis_2, np.array(vector_1))
    assert np.array_equal(xaxis_3, np.array(vector_3))

    ## get_y_axis

    yaxis_1: np.ndarray = polygon3d_1.get_y_axis()
    yaxis_2: np.ndarray = polygon3d_2.get_y_axis()
    yaxis_3: np.ndarray = polygon3d_3.get_y_axis()

    assert np.array_equal(yaxis_1, np.array(vector_2))
    assert np.array_equal(yaxis_2, np.array(vector_2))
    assert np.array_equal(yaxis_3, np.array(vector_4) / np.linalg.norm(np.array(vector_4)))

    ## is_near

    ## get_normal_vector

    ## apply_transformation

################################################################################################################################################################
