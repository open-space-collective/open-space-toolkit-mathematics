# Apache License 2.0

import pytest

import math

import numpy as np

import ostk.mathematics as mathematics

from ostk.core.type import String


Object = mathematics.geometry.d2.Object
Point = mathematics.geometry.d2.object.Point


class TestPoint:
    def test_constructor_success(self):
        point: Point = Point(1.0, 2.0)

        assert point is not None
        assert isinstance(point, Point)
        assert isinstance(point, Object)
        assert point.is_defined()

    def test_undefined_constructor_success(self):
        point: Point = Point.undefined()

        assert point is not None
        assert isinstance(point, Point)
        assert isinstance(point, Object)
        assert point.is_defined() is False

    def test_origin_constructor_success(self):
        point: Point = Point.origin()

        assert point is not None
        assert isinstance(point, Point)
        assert isinstance(point, Object)
        assert point.is_defined()
        assert point.x() - 0.0 <= 1e-12
        assert point.y() - 0.0 <= 1e-12

    def test_vector_constructor_success(self):
        # Construction using a python list
        point: Point = Point.vector([3.4, -6.7])

        assert point is not None
        assert isinstance(point, Point)
        assert isinstance(point, Object)
        assert point.is_defined()
        assert (point.x() - 3.4) <= 1e-15
        assert (point.y() + 6.7) <= 1e-15

        # Construction using a python tuple
        point: Point = Point.vector((3.4, -6.7))

        assert point is not None
        assert isinstance(point, Point)
        assert isinstance(point, Object)
        assert point.is_defined()
        assert (point.x() - 3.4) <= 1e-15
        assert (point.y() + 6.7) <= 1e-15

        # Construction using a python numpy array
        point: Point = Point.vector(np.array((3.4, -6.7)))

        assert point is not None
        assert isinstance(point, Point)
        assert isinstance(point, Object)
        assert point.is_defined()
        assert (point.x() - 3.4) <= 1e-15
        assert (point.y() + 6.7) <= 1e-15

    def test_comparators_success(self):
        point_1: Point = Point(3.4, -6.7)
        point_2: Point = Point.vector([3.4, -6.7])
        point_3: Point = Point(3.3, -6.5)
        point_4: Point = Point.vector(
            (
                3.4,
                -6.7,
            )
        )
        point_5: Point = Point.vector(np.array((3.4, -6.7)))

        assert point_1 == point_1
        assert point_1 == point_2
        assert point_1 != point_3
        assert point_2 != point_3
        assert point_1 == point_4
        assert point_1 == point_5
        assert point_2 == point_4
        assert point_2 == point_5
        assert point_3 != point_4

    def test_operators_success(self):
        point_1: Point = Point(3.4, -6.7)
        point_2: Point = Point.vector([3.4, -6.7])
        point_3: Point = Point.vector((3.4, -6.7))
        point_4: Point = Point.vector(np.array((3.3, -6.5)))

        point: Point = point_1 + [3.4, -6.7]

        assert point is not None
        assert isinstance(point, Point)
        assert point.is_defined()
        assert point.x() - (point_1.x() + point_2.x()) <= 1e-12
        assert point.y() - (point_1.y() + point_2.y()) <= 1e-12

        point: Point = point_3 + [3.4, -6.7]

        assert point is not None
        assert isinstance(point, Point)
        assert point.is_defined()
        assert point.x() - (point_3.x() + point_2.x()) <= 1e-12
        assert point.y() - (point_3.y() + point_2.y()) <= 1e-12

        point: Point = point_1 + (3.3, -6.5)

        assert point is not None
        assert isinstance(point, Point)
        assert point.is_defined()
        assert point.x() - (point_1.x() + point_4.x()) <= 1e-12
        assert point.y() - (point_1.y() + point_4.y()) <= 1e-12

        point: Point = point_1 + (0.0, 0.0)

        assert point is not None
        assert isinstance(point, Point)
        assert point.is_defined()
        assert point == point_1

        point: Point = point_1 + [0.0, 0.0]

        assert point is not None
        assert isinstance(point, Point)
        assert point.is_defined()
        assert point == point_1

        point: Point = point_1 + np.array((0.0, 0.0))

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

    def test_is_defined(self):
        point: Point = Point(3.5, 5.6)

        assert point.is_defined()
        assert Point.undefined().is_defined() is False

    def test_is_near(self):
        point_1: Point = Point(3.5, 5.6)
        point_2: Point = Point(3.4999999999, 5.5999999999)

        assert point_1.is_near(point_2, 1e-8) is True
        assert point_2.is_near(point_1, 1e-8) is True
        assert point_1.is_near(point_2, 1e-11) is False
        assert point_1.is_near(point_2, 1e-9) is True

    def test_coordinates(self):
        point: Point = Point(4.5, 34.5)

        assert point.x() == 4.5
        assert point.y() == 34.5

    def test_as_vector(self):
        point: Point = Point(3.4, -3.5)
        vec: np.ndarray = point.as_vector()

        assert vec is not None
        assert isinstance(vec, np.ndarray)

    def test_distance_to(self):
        point_1: Point = Point(0.0, 4.0)
        point_2: Point = Point(0.0, 3.0)
        point_3: Point = Point(3.0, 0.0)
        point_4: Point = Point(1.1, 1.0)

        assert point_1.distance_to(point_2) == 1.0
        assert point_2.distance_to(point_1) == 1.0

        assert point_1.distance_to(point_3) == 5.0
        assert point_3.distance_to(point_1) == 5.0

        assert point_1.distance_to(point_4) == math.sqrt((1.1 * 1.1) + 9.0)
        assert point_4.distance_to(point_1) == math.sqrt((1.1 * 1.1) + 9.0)

        with pytest.raises(TypeError):
            point_1.distance_to((0.0, 0.0))

    def test_to_string(self):
        point: Point = Point(3.0, 5.0)

        assert isinstance(point.to_string(), String)
        assert point.to_string() == "[3.0, 5.0]"

    # def test_apply_transformation_success (self):

    #     point: Point = Point(4.5, 5.4)
