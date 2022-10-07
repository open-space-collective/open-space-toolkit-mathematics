################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           bindings/python/test/geometry/d2/objects/test_line.py
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
Line = mathematics.geometry.d2.objects.Line

################################################################################################################################################################

class TestLine:

    def test_constructor_success (self):

        line = Line(
            Point(1.0, 2.0),
            np.array((3.4, 1.0)),
        )

        assert line is not None
        assert isinstance(line, Line)
        assert isinstance(line, Object)
        assert line.is_defined()

    def test_contains_success_point_set(
        self,
        line: Line,
        point_set: PointSet,
    ):

        assert line.contains(point_set) is True

    def test_distance_to_success_point (
        self,
        line: Line,
    ):

        assert float(line.distance_to(Point(2.0, 3.0))) == pytest.approx(0.0, 1e-5)
        assert float(line.distance_to(Point(1.0, 5.0))) == pytest.approx(2.12132, 1e-5)

    def test_undefined_success (self):

        line = Line.undefined()

        assert line is not None
        assert isinstance(line, Line)
        assert isinstance(line, Object)
        assert line.is_defined() is False

    def test_points_success (
        self,
        line: Line,
    ):

        assert line is not None
        assert isinstance(line, Line)
        assert isinstance(line, Object)
        assert line.is_defined() is True

################################################################################################################################################################
