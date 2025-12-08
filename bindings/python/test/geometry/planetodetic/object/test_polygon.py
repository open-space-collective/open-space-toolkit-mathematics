# Apache License 2.0

import pytest

import ostk.mathematics as mathematics


Object = mathematics.geometry.planetodetic.Object
Angle = mathematics.geometry.Angle
Point = mathematics.geometry.planetodetic.object.Point
Spheroid = mathematics.geometry.planetodetic.object.Spheroid
Polygon = mathematics.geometry.planetodetic.object.Polygon


@pytest.fixture
def spheroid() -> Spheroid:
    return Spheroid.from_equatorial_radius_and_flattening(1.0, 0.01)


@pytest.fixture
def another_spheroid() -> Spheroid:
    return Spheroid.sphere(1.5)


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
    spheroid: Spheroid,
    outer_ring: list[Point],
) -> Polygon:
    return Polygon.simple(spheroid, outer_ring)


class TestPolygon:
    def test_simple_constructor_success_list(
        self,
        spheroid: Spheroid,
        outer_ring: list[Point],
    ):
        polygon: Polygon = Polygon.simple(
            spheroid,
            outer_ring,
        )

        assert isinstance(polygon, Polygon)
        assert isinstance(polygon, Object)
        assert polygon.is_defined()

    def test_simple_constructor_with_tuple_success(
        self,
        spheroid: Spheroid,
    ):
        outer_ring = (
            Point(Angle.degrees(-1.0), Angle.degrees(-1.0)),
            Point(Angle.degrees(-1.0), Angle.degrees(1.0)),
            Point(Angle.degrees(1.0), Angle.degrees(1.0)),
            Point(Angle.degrees(1.0), Angle.degrees(-1.0)),
        )

        polygon: Polygon = Polygon.simple(
            spheroid,
            outer_ring,
        )

        assert isinstance(polygon, Polygon)
        assert isinstance(polygon, Object)
        assert polygon.is_defined()

    def test_simple_constructor_failure_too_few_vertices(
        self,
        spheroid: Spheroid,
    ):
        with pytest.raises(Exception):
            Polygon.simple(
                spheroid,
                [
                    Point(Angle.degrees(-10.0), Angle.degrees(-10.0)),
                    Point(Angle.degrees(-10.0), Angle.degrees(10.0)),
                ],
            )

    def test_simple_constructor_failure_collinear_vertices(
        self,
        spheroid: Spheroid,
    ):
        with pytest.raises(Exception):
            Polygon.simple(
                spheroid,
                [
                    Point(Angle.degrees(0.0), Angle.degrees(0.0)),
                    Point(Angle.degrees(0.0), Angle.degrees(120.0)),
                    Point(Angle.degrees(0.0), Angle.degrees(240.0)),
                ],
            )

    def test_simple_constructor_failure_undefined_vertex(
        self,
        spheroid: Spheroid,
    ):
        with pytest.raises(Exception):
            Polygon.simple(
                spheroid,
                [
                    Point.undefined(),
                    Point(Angle.degrees(0.0), Angle.degrees(1.0)),
                    Point(Angle.degrees(1.0), Angle.degrees(0.0)),
                ],
            )

    def test_simple_constructor_failure_intersecting_vertices(
        self,
        spheroid: Spheroid,
    ):
        with pytest.raises(Exception):
            Polygon.simple(
                spheroid,
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
        spheroid: Spheroid,
        outer_ring: list[Point],
        another_spheroid: Spheroid,
        another_outer_ring: list[Point],
    ):
        polygon_1: Polygon = Polygon.simple(spheroid, outer_ring)
        polygon_2: Polygon = Polygon.simple(spheroid, outer_ring)
        polygon_3: Polygon = Polygon.simple(another_spheroid, outer_ring)
        polygon_4: Polygon = Polygon.simple(spheroid, another_outer_ring)
        polygon_5: Polygon = Polygon.simple(another_spheroid, another_outer_ring)
        polygon_6: Polygon = Polygon.undefined()

        assert polygon_1 == polygon_1
        assert polygon_1 == polygon_2
        assert polygon_1 != polygon_3
        assert polygon_1 != polygon_4
        assert polygon_1 != polygon_5
        assert polygon_1 != polygon_6

    def test_get_spheroid_success(
        self,
        spheroid: Spheroid,
        outer_ring: list[Point],
    ):
        polygon: Polygon = Polygon.simple(spheroid, outer_ring)

        assert polygon.get_spheroid() == spheroid

    def test_get_vertex_count_success(
        self,
        spheroid: Spheroid,
        outer_ring: list[Point],
    ):
        polygon: Polygon = Polygon.simple(spheroid, outer_ring)
        assert polygon.get_vertex_count() == len(outer_ring)

    def test_get_vertices_success(
        self,
        spheroid: Spheroid,
        outer_ring: list[Point],
    ):
        polygon: Polygon = Polygon.simple(spheroid, outer_ring)

        for input_vertex, output_vertex in zip(
            polygon.get_vertices(), outer_ring, strict=True
        ):
            assert input_vertex == output_vertex

    def test_contains_point_success(
        self,
        spheroid: Spheroid,
        outer_ring: list[Point],
    ):
        polygon: Polygon = Polygon.simple(spheroid, outer_ring)

        assert polygon.contains(Point(Angle.degrees(0.0), Angle.degrees(0.0)))
        assert not polygon.contains(Point(Angle.degrees(20.0), Angle.degrees(20.0)))

    def test_str_repr(self):
        spheroid: Spheroid = Spheroid.sphere(6378137.0)
        outer_ring = [
            Point(Angle.degrees(0.0), Angle.degrees(0.0)),
            Point(Angle.degrees(0.0), Angle.degrees(1.0)),
            Point(Angle.degrees(1.0), Angle.degrees(0.0)),
        ]
        polygon: Polygon = Polygon.simple(spheroid, outer_ring)

        assert len(str(polygon)) > 0
        assert len(repr(polygon)) > 0
