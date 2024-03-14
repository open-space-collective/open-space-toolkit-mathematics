# Apache License 2.0

import pytest

import numpy as np

from ostk.mathematics.geometry import Angle
from ostk.mathematics.geometry.d2.object import Point as Point2d
from ostk.mathematics.geometry.d2.object import Polygon as Polygon2d
from ostk.mathematics.geometry.d3 import Object as Object
from ostk.mathematics.geometry.d3.object import Composite as Composite
from ostk.mathematics.geometry.d3.object import Point
from ostk.mathematics.geometry.d3.object import PointSet
from ostk.mathematics.geometry.d3.object import Line
from ostk.mathematics.geometry.d3.object import Ray
from ostk.mathematics.geometry.d3.object import Segment
from ostk.mathematics.geometry.d3.object import LineString
from ostk.mathematics.geometry.d3.object import Polygon
from ostk.mathematics.geometry.d3.object import Plane
from ostk.mathematics.geometry.d3.object import Sphere
from ostk.mathematics.geometry.d3.object import Ellipsoid
from ostk.mathematics.geometry.d3.object import Pyramid
from ostk.mathematics.geometry.d3.object import Cone


@pytest.fixture
def point() -> Point:
    return Point(1.0, 2.0, 1.0)


@pytest.fixture
def point_set(point: Point) -> PointSet:
    return PointSet([point])


@pytest.fixture
def direction() -> np.ndarray:
    return np.array([1.0, 0.0, 0.0])


@pytest.fixture
def line(point: Point, direction: np.ndarray) -> Line:
    return Line(point, direction)


@pytest.fixture
def ray(point: Point, direction: np.ndarray) -> Ray:
    return Ray(point, direction)


@pytest.fixture
def segment():
    point_1: Point = Point(1.0, 2.0, 1.0)
    point_2: Point = Point(1.0, 1.0, 1.0)
    return Segment(point_1, point_2)


@pytest.fixture
def line_string() -> LineString:
    point_1: Point = Point(1.0, 2.0, 1.0)
    point_2: Point = Point(1.0, 1.0, 1.0)
    return LineString([point_1, point_2])


@pytest.fixture
def polygon2d() -> Polygon2d:
    point_1: Point2d = Point2d(-1.0, 1.0)
    point_2: Point2d = Point2d(1.0, 1.0)
    point_3: Point2d = Point2d(1.0, -1.0)
    point_4: Point2d = Point2d(-1.0, -1.0)
    return Polygon2d([point_1, point_2, point_3, point_4])


@pytest.fixture
def polygon(point: Point, polygon2d: Polygon2d) -> Polygon:
    vector_1 = (1.0, 0.0, 0.0)
    vector_2 = (0.0, 1.0, 0.0)
    return Polygon(polygon2d, point, vector_1, vector_2)


@pytest.fixture
def plane(point: Point, direction: np.ndarray) -> Plane:
    return Plane(point, direction)


@pytest.fixture
def sphere(point: Point) -> Sphere:
    return Sphere(point, 1.0)


@pytest.fixture
def ellipsoid(point: Point) -> Ellipsoid:
    return Ellipsoid(point, 1.0, 1.0, 1.0)


@pytest.fixture
def pyramid(polygon: Polygon, point: Point) -> Pyramid:
    return Pyramid(polygon, point)


@pytest.fixture
def cone(point: Point, direction: np.ndarray) -> Cone:
    return Cone(point, direction, Angle.degrees(5.0))


@pytest.fixture
def composite_with_polygon(segment: Segment, polygon: Polygon) -> Composite:
    composite_1 = Composite(segment)
    return composite_1 + Composite(polygon)


class Test3DComposite:
    @pytest.mark.parametrize(
        "geometry_name",
        [
            ("point"),
            ("point_set"),
            ("line"),
            ("ray"),
            ("segment"),
            ("line_string"),
            ("polygon"),
            ("plane"),
            ("sphere"),
            ("ellipsoid"),
            ("pyramid"),
            ("cone"),
        ],
    )
    def test_geometry_d3_object_composite_constructor(self, geometry_name: str, request):
        geometry = request.getfixturevalue(geometry_name)
        composite: Composite = Composite(geometry)

        assert composite is not None
        assert isinstance(composite, Composite)
        assert composite.is_defined()

    def test_geometry_d3_object_composite_empty(self):
        composite: Composite = Composite.empty()

        assert composite is not None
        assert isinstance(composite, Composite)
        assert isinstance(composite, Object)
        assert composite.is_defined()
        assert composite.is_empty()

    def test_geometry_d3_object_composite_comparators(self):
        point_1: Point = Point(1.0, 2.0, 1.0)
        point_2: Point = Point(1.0, 1.0, 1.0)
        point_3: Point = Point(1.0, 4.0, 1.0)

        segment_1: Segment = Segment(point_1, point_2)
        segment_2: Segment = Segment(point_1, point_3)
        segment_3: Segment = Segment(point_2, point_1)

        composite_1 = Composite(segment_1)
        composite_2 = Composite(segment_2)
        composite_3 = Composite(segment_3)

        assert composite_1 == composite_3
        assert composite_1 != composite_2
        assert composite_2 != composite_3

    def tes_geometry_d3_object_composite_addition_operator(self):
        point_1: Point = Point(1.0, 2.0, 1.0)
        point_2: Point = Point(1.0, 1.0, 1.0)
        point_3: Point = Point(1.0, 4.0, 1.0)

        segment_1: Segment = Segment(point_1, point_2)
        segment_2: Segment = Segment(point_1, point_3)

        composite_1 = Composite(segment_1)
        composite_2 = Composite(segment_2)

        composite_3 = composite_1 + composite_2

        assert composite_3 is not None
        assert isinstance(composite_3, Composite)
        assert composite_3.is_defined()
        assert composite_3.get_object_count() == 2

        with pytest.raises(RuntimeError):
            composite = Composite.undefined() + composite_1

        with pytest.raises(RuntimeError):
            composite = composite_1 + Composite.undefined()

        composite_3 += composite_1

        assert isinstance(composite_3, Composite)
        assert composite_3.is_defined()
        assert composite_3.get_object_count() == 3

        with pytest.raises(RuntimeError):
            composite_3 += Composite.undefined()

    def test_geometry_d3_object_composite_access_object_at(
        self,
        composite_with_polygon: Composite,
    ):
        object: Object = composite_with_polygon.access_object_at(0)

        assert object is not None
        assert isinstance(object, Object)
        assert isinstance(object, Segment)

        object_2: Object = composite_with_polygon.access_object_at(1)

        assert object_2 is not None
        assert isinstance(object_2, Object)
        assert isinstance(object_2, Polygon)

        with pytest.raises(RuntimeError):
            composite_with_polygon.access_object_at(2)

    @pytest.mark.parametrize(
        "geometry_name",
        [
            ("point"),
            ("point_set"),
            ("line"),
            ("ray"),
            ("segment"),
            ("line_string"),
            ("polygon"),
            ("plane"),
            ("sphere"),
            ("ellipsoid"),
            ("pyramid"),
            ("cone"),
        ],
    )
    def test_geometry_d3_object_composite_is(self, geometry_name: str, request):
        geometry = request.getfixturevalue(geometry_name)
        composite: Composite = Composite(geometry)

        assert composite.is_defined()
        assert getattr(composite, f"is_{geometry_name}")()

    @pytest.mark.parametrize(
        "geometry_name",
        [
            ("point"),
            ("point_set"),
            ("line"),
            ("ray"),
            ("segment"),
            ("line_string"),
            ("polygon"),
            ("plane"),
            ("sphere"),
            ("ellipsoid"),
            ("pyramid"),
            ("cone"),
        ],
    )
    def test_geometry_d3_object_composite_as(self, geometry_name: str, request):
        geometry = request.getfixturevalue(geometry_name)
        composite: Composite = Composite(geometry)

        assert composite.is_defined()
        assert getattr(composite, f"as_{geometry_name}")().is_defined()
