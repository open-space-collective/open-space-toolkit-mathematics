################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           bindings/python/test/geometry/d3/objects/test_segment.py
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
Segment = mathematics.geometry.d3.objects.Segment
Line = mathematics.geometry.d3.objects.Line
Plane = mathematics.geometry.d3.objects.Plane
Sphere = mathematics.geometry.d3.objects.Sphere
Ellipsoid = mathematics.geometry.d3.objects.Ellipsoid
Intersection = mathematics.geometry.d3.Intersection
Transformation = mathematics.geometry.d3.Transformation

################################################################################################################################################################

@pytest.fixture
def segment () -> Segment:

    return Segment(
        Point(0.0, 0.0, 0.0),
        Point(0.0, 0.0, 2.0),
    )

################################################################################################################################################################

class TestSegment:

    def test_constructor_success (self):

        point_1: Point = Point(-1.0, 1.0, 0.0)
        point_2: Point = Point(1.0, 1.0, 1.0)

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

    def test_comparators_success (self):

        point_1: Point = Point(-1.0, 1.0, 0.0)
        point_2: Point = Point(1.0, 1.0, 0.0)

        segment_1: Segment = Segment(point_1, point_2)
        segment_2: Segment = Segment(point_1, point_1)

        assert segment_1 == segment_1
        assert segment_1 != segment_2

    def test_getters_success (self):

        point_1: Point = Point(-1.0, 1.0, 0.0)
        point_2: Point = Point(1.0, 1.0, 0.0)

        segment: Segment = Segment(point_1, point_2)

        assert isinstance(segment.get_first_point(), Point)
        assert segment.get_first_point() == point_1

        assert isinstance(segment.get_second_point(), Point)
        assert segment.get_second_point() == point_2

        assert isinstance(segment.get_center(), Point)
        assert segment.get_center() == Point(0.0, 1.0, 0.0)

        assert isinstance(segment.get_direction(), np.ndarray)
        assert np.array_equal(segment.get_direction(), np.array((1.0, 0.0, 0.0)))

        assert segment.get_length() == 2.0

    def test_is_defined_success (self, segment: Segment):

        assert segment.is_defined() is True

    def test_is_degenerate_success (self, segment: Segment):

        assert segment.is_degenerate() is False

    def test_intersects_success_plane (self, segment: Segment):

        assert segment.intersects(Plane(Point(0.0, 0.0, 0.0), np.array((1.0, 0.0, 0.0)))) is True

    def test_intersects_success_sphere (self, segment: Segment):

        assert segment.intersects(Sphere(Point(0.0, 0.0, 0.0), 1.0)) is True

    def test_intersects_success_ellipsoid (self, segment: Segment):

        assert segment.intersects(Ellipsoid(Point(0.0, 0.0, 0.0), 0.5, 0.5, 0.5)) is True

    def test_contains_success_point (self, segment: Segment):

        assert segment.contains(Point(0.0, 0.0, 0.0)) is True

    def test_get_length_success (self, segment: Segment):

        assert segment.get_length() == 2.0

    def test_distance_to_success_point (self, segment: Segment):

        assert segment.distance_to(Point(0.0, 0.0, 0.0)) == 0.0

    def test_distance_to_success_point_set (self, segment: Segment):

        assert segment.distance_to(PointSet([Point(0.0, 0.0, 0.0), Point(1.0, 0.0, 0.0)])) == 0.0

    def test_intersection_with_success_plane (self, segment: Segment):

        assert segment.intersection_with(Plane(Point(0.0, 0.0, 0.0), np.array((0.0, 0.0, 1.0)))) == Intersection.point(Point(0.0, 0.0, 0.0))

    def test_to_line_success (self, segment: Segment):

        assert segment.to_line() == Line(Point(0.0, 0.0, 0.0), np.array((0.0, 0.0, 1.0)))

    # def test_apply_transformation_success (self):

################################################################################################################################################################
