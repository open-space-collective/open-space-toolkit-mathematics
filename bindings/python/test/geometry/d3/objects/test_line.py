################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           bindings/python/test/geometry/d3/objects/test_line.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

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

    def test_undefined_success (self):

        line = Line.undefined()

        assert line is not None
        assert isinstance(line, Point)
        assert isinstance(line, Object)
        assert line.is_defined() is False

    def test_contains_point_set_success (self):

        line = Line(
            Point(1.0, 2.0, 3.0),
            np.array((1.0, 1.0, 1.0)),
        )

        point_set = PointSet([
            Point(1.0, 2.0, 3.0),
            Point(2.0, 3.0, 4.0),
        ])

        assert line.contains_point_set(point_set) is True

    def test_distance_to_point_success (self):

        line = Line(
            Point(1.0, 2.0, 3.0),
            np.array((1.0, 1.0, 1.0)),
        )

        assert line.distance_to_point(Point(2.0, 3.0, 4.0)) == 0.0

################################################################################################################################################################
