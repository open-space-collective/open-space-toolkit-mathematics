# Apache License 2.0

import pytest

import ostk.mathematics as mathematics


Object = mathematics.geometry.planetodetic.Object
Angle = mathematics.geometry.Angle
Point = mathematics.geometry.planetodetic.object.Point
Spheroid = mathematics.geometry.planetodetic.object.Spheroid
Polygon = mathematics.geometry.planetodetic.object.Polygon


@pytest.fixture
def point() -> Point:
    return Point(Angle.degrees(0.0), Angle.degrees(0.0))


@pytest.fixture
def spheroid() -> Spheroid:
    return Spheroid.from_equatorial_radius_and_flattening(1.0, 0.01)


@pytest.fixture
def polygon(
    spheroid: Spheroid,
) -> Polygon:
    return Polygon.simple(
        spheroid,
        [
            Point(Angle.degrees(-1.0), Angle.degrees(-1.0)),
            Point(Angle.degrees(-1.0), Angle.degrees(1.0)),
            Point(Angle.degrees(1.0), Angle.degrees(1.0)),
            Point(Angle.degrees(1.0), Angle.degrees(-1.0)),
        ],
    )


class TestObject:
    def test_no_constructor(self):
        with pytest.raises(TypeError):
            Object()

    def test_equals(
        self,
        point: Point,
        polygon: Polygon,
        spheroid: Spheroid,
    ):
        assert point == point
        assert point != polygon
        assert point != spheroid

        assert polygon != point
        assert polygon == polygon
        assert polygon != spheroid

        assert spheroid != point
        assert spheroid != polygon
        assert spheroid == spheroid

    def test_contains(
        self,
        point: Point,
        polygon: Polygon,
        spheroid: Spheroid,
    ):
        with pytest.raises(Exception):
            point.contains(point)
        with pytest.raises(Exception):
            point.contains(polygon)
        with pytest.raises(Exception):
            point.contains(spheroid)

        polygon.contains(point)
        with pytest.raises(Exception):
            polygon.contains(polygon)
        with pytest.raises(Exception):
            polygon.contains(spheroid)

        with pytest.raises(Exception):
            spheroid.contains(point)
        with pytest.raises(Exception):
            spheroid.contains(polygon)
        with pytest.raises(Exception):
            spheroid.contains(spheroid)

    def test_intersects(
        self,
        point: Point,
        polygon: Polygon,
        spheroid: Spheroid,
    ):
        with pytest.raises(Exception):
            point.intersects(point)
        with pytest.raises(Exception):
            point.intersects(polygon)
        with pytest.raises(Exception):
            point.intersects(spheroid)

        with pytest.raises(Exception):
            polygon.intersects(point)
        with pytest.raises(Exception):
            polygon.intersects(polygon)
        with pytest.raises(Exception):
            polygon.intersects(spheroid)

        with pytest.raises(Exception):
            spheroid.intersects(point)
        with pytest.raises(Exception):
            spheroid.intersects(polygon)
        with pytest.raises(Exception):
            spheroid.intersects(spheroid)
