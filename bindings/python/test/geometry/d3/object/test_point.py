# Apache License 2.0

import pytest

import math

import numpy as np

import ostk.mathematics as mathematics

Object = mathematics.geometry.d3.Object
Point = mathematics.geometry.d3.object.Point
Transformation = mathematics.geometry.d3.Transformation


def test_geometry_d3_object_point_constructor():
    point: Point = Point(1.0, 2.0, 3.0)

    assert point is not None
    assert isinstance(point, Point)
    assert isinstance(point, Object)
    assert point.is_defined()


def test_geometry_d3_object_point_undefined():
    point: Point = Point.undefined()

    assert point is not None
    assert isinstance(point, Point)
    assert isinstance(point, Object)
    assert point.is_defined() is False


def test_geometry_d3_object_point_origin():
    point: Point = Point.origin()

    assert point is not None
    assert isinstance(point, Point)
    assert isinstance(point, Object)
    assert point.is_defined()
    assert point.x() == 0.0
    assert point.y() == 0.0
    assert point.z() == 0.0


def test_geometry_d3_object_point_vector():
    # Construction using a python list
    point: Point = Point.vector([3.4, -6.7, 1.0])

    assert point is not None
    assert isinstance(point, Point)
    assert isinstance(point, Object)
    assert point.is_defined()
    assert (point.x() - 3.4) <= 1e-15
    assert (point.y() + 6.7) <= 1e-15
    assert (point.z() - 1.0) <= 1e-15

    # Construction using a python tuple
    point: Point = Point.vector((3.4, -6.7, 1.0))

    assert point is not None
    assert isinstance(point, Point)
    assert isinstance(point, Object)
    assert point.is_defined()
    assert (point.x() - 3.4) <= 1e-15
    assert (point.y() + 6.7) <= 1e-15
    assert (point.z() - 1.0) <= 1e-15

    # Construction using a python numpy array
    point: Point = Point.vector(np.array((3.4, -6.7, 1.0)))

    assert point is not None
    assert isinstance(point, Point)
    assert isinstance(point, Object)
    assert point.is_defined()
    assert (point.x() - 3.4) <= 1e-15
    assert (point.y() + 6.7) <= 1e-15
    assert (point.z() - 1.0) <= 1e-15


def test_geometry_d3_object_point_comparators():
    point_1: Point = Point(3.4, -6.7, 1.0)
    point_2: Point = Point.vector([3.4, -6.7, 1.0])
    point_3: Point = Point(3.3, -6.5, 1.0)
    point_4: Point = Point.vector(
        (
            3.4,
            -6.7,
            1.0,
        )
    )
    point_5: Point = Point.vector(np.array((3.4, -6.7, 1.0)))

    assert point_1 == point_1
    assert point_1 == point_2
    assert point_1 != point_3
    assert point_2 != point_3
    assert point_1 == point_4
    assert point_1 == point_5
    assert point_2 == point_4
    assert point_2 == point_5
    assert point_3 != point_4


def test_geometry_d3_object_point_operators():
    point_1: Point = Point(3.4, -6.7, 1.0)
    point_2: Point = Point.vector([3.4, -6.7, 1.0])
    point_3: Point = Point.vector((3.4, -6.7, 1.0))
    point_4: Point = Point.vector(np.array((3.3, -6.5, 1.0)))

    point: Point = point_1 + [3.4, -6.7, 1.0]

    assert point is not None
    assert isinstance(point, Point)
    assert point.is_defined()
    assert point.x() == point_1.x() + point_2.x()
    assert point.y() == point_1.y() + point_2.y()
    assert point.z() == point_1.z() + point_2.z()

    point: Point = point_3 + [3.4, -6.7, 1.0]

    assert point is not None
    assert isinstance(point, Point)
    assert point.is_defined()
    assert point.x() == point_3.x() + point_2.x()
    assert point.y() == point_3.y() + point_2.y()
    assert point.z() == point_3.z() + point_2.z()

    point: Point = point_1 + (3.3, -6.5, 1.0)

    assert point is not None
    assert isinstance(point, Point)
    assert point.is_defined()
    assert point.x() == point_1.x() + point_4.x()
    assert point.y() == point_1.y() + point_4.y()
    assert point.z() == point_1.z() + point_4.z()

    point: Point = point_1 + (0.0, 0.0, 0.0)

    assert point is not None
    assert isinstance(point, Point)
    assert point.is_defined()
    assert point == point_1

    point: Point = point_1 + [0.0, 0.0, 0.0]

    assert point is not None
    assert isinstance(point, Point)
    assert point.is_defined()
    assert point == point_1

    point: Point = point_1 + np.array((0.0, 0.0, 0.0))

    assert point is not None
    assert isinstance(point, Point)
    assert point.is_defined()
    assert point == point_1

    # point: Point = point_1 - point_1

    # assert point is not None
    # assert isinstance(point, Point)
    # assert isinstance(point, Object)
    # assert point.is_defined()
    # assert point.x == 0.0
    # assert point.y == 0.0
    # assert point == Point.origin()


def test_geometry_d3_object_point_is_defined():
    point: Point = Point(3.5, 5.6, 4.3)

    assert point.is_defined()
    assert Point.undefined().is_defined() is False


def test_geometry_d3_object_point_is_near():
    point_1: Point = Point(3.5, 5.6, 4.3)
    point_2: Point = Point(3.4999999999, 5.5999999999, 4.30000000000001)

    assert point_1.is_near(point_2, 1e-8)
    assert point_2.is_near(point_1, 1e-8)
    assert point_1.is_near(point_2, 1e-11) is False
    assert point_1.is_near(point_2, 1e-9) is True


def test_geometry_d3_object_point_components():
    point: Point = Point(4.5, 34.5, 3.9)

    assert point.x() == 4.5
    assert point.y() == 34.5
    assert point.z() == 3.9


def test_geometry_d3_object_point_as_vector():
    point: Point = Point(3.4, -3.5, 1.0)
    vec: np.ndarray = point.as_vector()

    assert vec is not None
    assert isinstance(vec, np.ndarray)
    assert (vec[0] - 3.4) <= 1e-12
    assert (vec[1] + 3.5) <= 1e-12
    assert (vec[2] - 1.0) <= 1e-12


def test_geometry_d3_object_point_distance_to():
    point_1: Point = Point(0.0, 4.0, 0.0)
    point_2: Point = Point(0.0, 3.0, 0.0)
    point_3: Point = Point(3.0, 0.0, 0.0)
    point_4: Point = Point(1.1, 1.0, 0.0)

    assert point_1.distance_to(point_2) - 1.0 <= 1e-12
    assert point_2.distance_to(point_1) - 1.0 <= 1e-12

    assert point_1.distance_to(point_3) - 5.0 <= 1e-12
    assert point_3.distance_to(point_1) - 5.0 <= 1e-12

    assert point_1.distance_to(point_4) == math.sqrt((1.1 * 1.1) + 9.0)
    assert point_4.distance_to(point_1) == math.sqrt((1.1 * 1.1) + 9.0)

    with pytest.raises(TypeError):
        point_1.distance_to((0.0, 0.0, 0.0))


# def test_geometry_d3_object_point_to_string ():

#     point: Point = Point(3.0, 5.0, 1.0)

#     assert isinstance(point.to_string(), String)
#     assert point.to_string() == '[3.0, 5.0, 1.0]'

# def test_geometry_d3_object_point_apply_transformation ():

#     point: Point = Point(4.5, 5.4, 3.1)
