# Apache License 2.0

import pytest

import ostk.mathematics as mathematics


Object = mathematics.geometry.planetodetic.Object
Angle = mathematics.geometry.Angle
Ellipsoid = mathematics.geometry.planetodetic.object.Ellipsoid
Point = mathematics.geometry.planetodetic.object.Point
Polygon = mathematics.geometry.planetodetic.object.Polygon


@pytest.fixture
def ellipsoid() -> Ellipsoid:
    return Ellipsoid.spheroid(1.0, 0.01)


@pytest.fixture
def another_ellipsoid() -> Ellipsoid:
    return Ellipsoid.sphere(1.5)


@pytest.fixture
def outer_ring() -> list[Point]:
    return [
        Point(Angle.degrees(-10.0), Angle.degrees(-10.0)),
        Point(Angle.degrees(-10.0), Angle.degrees(10.0)),
        Point(Angle.degrees(10.0), Angle.degrees(10.0)),
        Point(Angle.degrees(10.0), Angle.degrees(-10.0)),
    ]


@pytest.fixture
def another_outer_ring() -> list[Point]:
    return [
        Point(Angle.degrees(-12.0), Angle.degrees(-10.0)),
        Point(Angle.degrees(-12.0), Angle.degrees(10.0)),
        Point(Angle.degrees(15.0), Angle.degrees(10.0)),
        Point(Angle.degrees(15.0), Angle.degrees(-10.0)),
    ]


@pytest.fixture
def polygon(
    ellipsoid: Ellipsoid,
    outer_ring: list[Point],
) -> Polygon:
    return Polygon.simple(ellipsoid, outer_ring)


class TestPolygon:
    def test_simple_constructor_success_list(
        self,
        ellipsoid: Ellipsoid,
        outer_ring: list[Point],
    ):
        polygon: Polygon = Polygon.simple(
            ellipsoid,
            outer_ring,
        )

        assert isinstance(polygon, Polygon)
        assert isinstance(polygon, Object)
        assert polygon.is_defined()

    def test_simple_constructor_with_tuple_success(
        self,
        ellipsoid: Ellipsoid,
    ):
        outer_ring = (
            Point(Angle.degrees(-1.0), Angle.degrees(-1.0)),
            Point(Angle.degrees(-1.0), Angle.degrees(1.0)),
            Point(Angle.degrees(1.0), Angle.degrees(1.0)),
            Point(Angle.degrees(1.0), Angle.degrees(-1.0)),
        )

        polygon: Polygon = Polygon.simple(
            ellipsoid,
            outer_ring,
        )

        assert isinstance(polygon, Polygon)
        assert isinstance(polygon, Object)
        assert polygon.is_defined()

    def test_simple_constructor_failure_too_few_vertices(
        self,
        ellipsoid: Ellipsoid,
    ):
        with pytest.raises(Exception):
            Polygon.simple(
                ellipsoid,
                [
                    Point(Angle.degrees(-10.0), Angle.degrees(-10.0)),
                    Point(Angle.degrees(-10.0), Angle.degrees(10.0)),
                ],
            )

    def test_simple_constructor_failure_collinear_vertices(
        self,
        ellipsoid: Ellipsoid,
    ):
        with pytest.raises(Exception):
            Polygon.simple(
                ellipsoid,
                [
                    Point(Angle.degrees(0.0), Angle.degrees(0.0)),
                    Point(Angle.degrees(0.0), Angle.degrees(120.0)),
                    Point(Angle.degrees(0.0), Angle.degrees(240.0)),
                ],
            )

    def test_simple_constructor_failure_undefined_vertex(
        self,
        ellipsoid: Ellipsoid,
    ):
        with pytest.raises(Exception):
            Polygon.simple(
                ellipsoid,
                [
                    Point.undefined(),
                    Point(Angle.degrees(0.0), Angle.degrees(1.0)),
                    Point(Angle.degrees(1.0), Angle.degrees(0.0)),
                ],
            )

    def test_simple_constructor_failure_intersecting_vertices(
        self,
        ellipsoid: Ellipsoid,
    ):
        with pytest.raises(Exception):
            Polygon.simple(
                ellipsoid,
                [
                    Point(Angle.degrees(-1.0), Angle.degrees(-1.0)),
                    Point(Angle.degrees(1.0), Angle.degrees(1.0)),
                    Point(Angle.degrees(-1.0), Angle.degrees(1.0)),
                    Point(Angle.degrees(1.0), Angle.degrees(-1.0)),
                ],
            )

    def test_undefined_constructor_success(self):
        polygon: Polygon = Polygon.undefined()

        assert isinstance(polygon, Polygon)
        assert isinstance(polygon, Object)
        assert polygon.is_defined() is False

    def test_comparators_success(
        self,
        ellipsoid: Ellipsoid,
        outer_ring: list[Point],
        another_ellipsoid: Ellipsoid,
        another_outer_ring: list[Point],
    ):
        polygon_1: Polygon = Polygon.simple(ellipsoid, outer_ring)
        polygon_2: Polygon = Polygon.simple(ellipsoid, outer_ring)
        polygon_3: Polygon = Polygon.simple(another_ellipsoid, outer_ring)
        polygon_4: Polygon = Polygon.simple(ellipsoid, another_outer_ring)
        polygon_5: Polygon = Polygon.simple(another_ellipsoid, another_outer_ring)
        polygon_6: Polygon = Polygon.undefined()

        assert polygon_1 == polygon_1
        assert polygon_1 == polygon_2
        assert polygon_1 != polygon_3
        assert polygon_1 != polygon_4
        assert polygon_1 != polygon_5
        assert polygon_1 != polygon_6

    def test_get_ellipsoid_success(
        self,
        ellipsoid: Ellipsoid,
        outer_ring: list[Point],
    ):
        polygon: Polygon = Polygon.simple(ellipsoid, outer_ring)

        assert polygon.get_ellipsoid() == ellipsoid

    def test_get_vertex_count_success(
        self,
        ellipsoid: Ellipsoid,
        outer_ring: list[Point],
    ):
        polygon: Polygon = Polygon.simple(ellipsoid, outer_ring)
        assert polygon.get_vertex_count() == len(outer_ring)

    def test_get_vertices_success(
        self,
        ellipsoid: Ellipsoid,
        outer_ring: list[Point],
    ):
        polygon: Polygon = Polygon.simple(ellipsoid, outer_ring)

        assert len(polygon.get_vertices()) == len(outer_ring)
        for input_vertex, output_vertex in zip(polygon.get_vertices(), outer_ring):
            assert input_vertex == output_vertex

    def test_contains_point_success(
        self,
        ellipsoid: Ellipsoid,
        outer_ring: list[Point],
    ):
        polygon: Polygon = Polygon.simple(ellipsoid, outer_ring)

        assert polygon.contains(Point(Angle.degrees(0.0), Angle.degrees(0.0)))
        assert not polygon.contains(Point(Angle.degrees(20.0), Angle.degrees(20.0)))

    def test_str_repr(self):
        ellipsoid: Ellipsoid = Ellipsoid.sphere(6378137.0)
        outer_ring = [
            Point(Angle.degrees(0.0), Angle.degrees(0.0)),
            Point(Angle.degrees(0.0), Angle.degrees(1.0)),
            Point(Angle.degrees(1.0), Angle.degrees(0.0)),
        ]
        polygon: Polygon = Polygon.simple(ellipsoid, outer_ring)

        assert len(str(polygon)) > 0
        assert len(repr(polygon)) > 0
