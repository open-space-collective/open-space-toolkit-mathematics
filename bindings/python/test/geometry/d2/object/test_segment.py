# Apache License 2.0

import pytest

import numpy as np

import ostk.mathematics as mathematics


Object = mathematics.geometry.d2.Object
Point = mathematics.geometry.d2.object.Point
PointSet = mathematics.geometry.d2.object.PointSet
Segment = mathematics.geometry.d2.object.Segment
Line = mathematics.geometry.d2.object.Line


class TestSegment:
    def test_constructor_success(self):
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

    def test_defined_success(self):
        segment: Segment = Segment.undefined()

        assert segment is not None
        assert isinstance(segment, Segment)
        assert isinstance(segment, Object)
        assert segment.is_defined() is False

    def test_degenerate_success(self):
        point_1: Point = Point(-1.0, 1.0)
        point_2: Point = Point(1.0, 1.0)

        segment_1: Segment = Segment(point_1, point_2)
        segment_2: Segment = Segment(point_1, point_1)

        assert segment_1.is_degenerate() is False
        assert segment_2.is_degenerate() is True

    def test_comparators_success(self):
        point_1: Point = Point(-1.0, 1.0)
        point_2: Point = Point(1.0, 1.0)

        segment_1: Segment = Segment(point_1, point_2)
        segment_2: Segment = Segment(point_1, point_1)

        assert segment_1 == segment_1
        assert segment_1 != segment_2

    def test_getters_success(self):
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

    def test_distance_to_success_point(
        self,
        segment: Segment,
    ):
        assert segment.distance_to(Point(0.0, 0.0)) == 0.0

    def test_distance_to_success_point_set(
        self,
        segment: Segment,
    ):
        assert segment.distance_to(PointSet([Point(0.0, 0.0), Point(1.0, 0.0)])) == 0.0

    def test_to_line_success(
        self,
        segment: Segment,
    ):
        assert segment.to_line() == Line(Point(0.0, 0.0), np.array((0.0, 1.0)))

    # def test_to_string_success (self):

    # def test_apply_transformation_success (self):
