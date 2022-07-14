################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           bindings/python/test/geometry/d3/objects/test_line.py
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
Line = mathematics.geometry.d3.objects.Line

################################################################################################################################################################

class TestLine:

    def test_constructor_success (self):

        line = Line(
            Point(1.0, 2.0, 3.0),
            np.array((3.4, -6.7, 1.0)),
        )

        assert line is not None
        assert isinstance(line, Line)
        assert isinstance(line, Object)
        assert line.is_defined()

    def test_contains_success_point_set (self):

        line = Line(
            Point(1.0, 2.0, 3.0),
            np.array((1.0, 1.0, 1.0)),
        )

        point_set = PointSet([
            Point(1.0, 2.0, 3.0),
            Point(2.0, 3.0, 4.0),
        ])

        assert line.contains(point_set) is True

    def test_distance_to_success_point (self):

        line = Line(
            Point(1.0, 2.0, 3.0),
            np.array((1.0, 1.0, 1.0)),
        )

        assert float(line.distance_to(Point(2.0, 3.0, 4.0))) == pytest.approx(0.0, 1e-10)

    def test_undefined_success (self):

        line = Line.undefined()

        assert line is not None
        assert isinstance(line, Line)
        assert isinstance(line, Object)
        assert line.is_defined() is False

    def test_points_success (self):

        line = Line.points(
            Point(1.0, 2.0, 3.0),
            Point(2.0, 4.0, 4.0),
        )

        assert line is not None
        assert isinstance(line, Line)
        assert isinstance(line, Object)
        assert line.is_defined() is True

################################################################################################################################################################
