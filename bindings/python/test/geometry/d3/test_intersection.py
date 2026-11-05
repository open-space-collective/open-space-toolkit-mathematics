# Apache License 2.0

import ostk.mathematics as mathematics

from ostk.mathematics.geometry.d3 import Intersection
from ostk.mathematics.geometry.d3.object import Point


class TestIntersection:
    def test_empty(self):
        intersection: Intersection = Intersection.empty()

        assert intersection.is_empty()
        assert intersection.get_type() == Intersection.Type.Empty

    def test_point(self):
        intersection: Intersection = Intersection.point(Point(1.0, 2.0, 3.0))

        assert intersection.is_point()
        assert intersection.get_type() == Intersection.Type.Point
        assert intersection.as_point() == Point(1.0, 2.0, 3.0)
