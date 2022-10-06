################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           bindings/python/test/geometry/d2/conftest.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

import numpy as np

import ostk.mathematics as mathematics

################################################################################################################################################################

Point = mathematics.geometry.d2.objects.Point
PointSet = mathematics.geometry.d2.objects.PointSet
Line = mathematics.geometry.d2.objects.Line
Segment = mathematics.geometry.d2.objects.Segment
Polygon = mathematics.geometry.d2.objects.Polygon
Composite = mathematics.geometry.d2.objects.Composite

################################################################################################################################################################

@pytest.fixture
def point () -> Point:

    return Point(-2.0, 5.0)

@pytest.fixture
def point_set () -> PointSet:

    return PointSet([Point(1.0, 2.0), Point(2.0, 3.0)])

@pytest.fixture
def line () -> Line:

    return Line(Point(1.0, 2.0), np.array((1.0, 1.0)))

@pytest.fixture
def segment () -> Segment:

    return Segment(Point(0.0, 0.0), Point(0.0, 2.0))

@pytest.fixture
def polygon () -> Polygon:

    point_1: Point = Point(-1.0, 1.0)
    point_2: Point = Point(1.0, 1.0)
    point_3: Point = Point(1.0, -1.0)
    point_4: Point = Point(-1.0, -1.0)

    return Polygon([point_1, point_2, point_3, point_4])

def square (center: Point) -> Polygon:

    point_1: Point = center + [0.5, 0.5]
    point_2: Point = center + [0.5, -0.5]
    point_3: Point = center + [-0.5, -0.5]
    point_4: Point = center + [-0.5, 0.5]

    return Polygon([point_1, point_2, point_3, point_4])

@pytest.fixture
def square_1 () -> Polygon:

    return square(Point(0.0, 0.0))

@pytest.fixture
def square_2 () -> Polygon:

    return square(Point(0.0, 10.0))

@pytest.fixture
def square_3 () -> Polygon:

    return square(Point(0.5, 0.0))

@pytest.fixture
def square_4 () -> Polygon:

    return square(Point(1.0, 0.0))

@pytest.fixture
def composite (
    polygon: Polygon,
    point: Point
) -> Composite:

    composite = Composite(polygon)
    composite += Composite(point)

    return composite

################################################################################################################################################################
