# Apache License 2.0

import pytest

import ostk.mathematics as mathematics


Object = mathematics.geometry.planetodetic.Object
Angle = mathematics.geometry.Angle
Ellipsoid = mathematics.geometry.planetodetic.object.Ellipsoid
Point = mathematics.geometry.planetodetic.object.Point
Polygon = mathematics.geometry.planetodetic.object.Polygon


@pytest.fixture
def point() -> Point:
    return Point(Angle.degrees(0.0), Angle.degrees(0.0))


@pytest.fixture
def ellipsoid() -> Ellipsoid:
    return Ellipsoid.spheroid(equatorial_radius=1.0, flattening=0.01)


@pytest.fixture
def polygon(
    ellipsoid: Ellipsoid,
) -> Polygon:
    return Polygon.simple(
        ellipsoid,
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
        ellipsoid: Ellipsoid,
    ):
        assert point == point
        assert point != polygon
        assert point != ellipsoid

        assert polygon != point
        assert polygon == polygon
        assert polygon != ellipsoid

        assert ellipsoid != point
        assert ellipsoid != polygon
        assert ellipsoid == ellipsoid

    def test_contains(
        self,
        point: Point,
        polygon: Polygon,
        ellipsoid: Ellipsoid,
    ):
        with pytest.raises(Exception):
            point.contains(point)
        with pytest.raises(Exception):
            point.contains(polygon)
        with pytest.raises(Exception):
            point.contains(ellipsoid)

        polygon.contains(point)
        with pytest.raises(Exception):
            polygon.contains(polygon)
        with pytest.raises(Exception):
            polygon.contains(ellipsoid)

        with pytest.raises(Exception):
            ellipsoid.contains(point)
        with pytest.raises(Exception):
            ellipsoid.contains(polygon)
        with pytest.raises(Exception):
            ellipsoid.contains(ellipsoid)

    def test_intersects(
        self,
        point: Point,
        polygon: Polygon,
        ellipsoid: Ellipsoid,
    ):
        with pytest.raises(Exception):
            point.intersects(point)
        with pytest.raises(Exception):
            point.intersects(polygon)
        with pytest.raises(Exception):
            point.intersects(ellipsoid)

        with pytest.raises(Exception):
            polygon.intersects(point)
        with pytest.raises(Exception):
            polygon.intersects(polygon)
        with pytest.raises(Exception):
            polygon.intersects(ellipsoid)

        with pytest.raises(Exception):
            ellipsoid.intersects(point)
        with pytest.raises(Exception):
            ellipsoid.intersects(polygon)
        with pytest.raises(Exception):
            ellipsoid.intersects(ellipsoid)
