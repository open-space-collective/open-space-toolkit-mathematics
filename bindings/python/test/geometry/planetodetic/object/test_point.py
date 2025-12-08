# Apache License 2.0

import pytest

import ostk.mathematics as mathematics


Object = mathematics.geometry.planetodetic.Object
Angle = mathematics.geometry.Angle
Point = mathematics.geometry.planetodetic.object.Point


@pytest.fixture
def latitude_1() -> Angle:
    return Angle.degrees(45.0)


@pytest.fixture
def longitude_1() -> Angle:
    return Angle.degrees(-122.0)


@pytest.fixture
def latitude_2() -> Angle:
    return Angle.degrees(30.0)


@pytest.fixture
def longitude_2() -> Angle:
    return Angle.degrees(100.0)


class TestPoint:
    def test_constructor_success(
        self,
        latitude_1: Angle,
        longitude_1: Angle,
    ):
        point: Point = Point(latitude_1, longitude_1)

        assert isinstance(point, Point)
        assert isinstance(point, Object)
        assert point.is_defined()

    def test_constructor_failure(
        self,
        longitude_1: Angle,
    ):
        with pytest.raises(Exception):
            Point(Angle.degrees(91.0), longitude_1)

        with pytest.raises(Exception):
            Point(Angle.degrees(-91.0), longitude_1)

    def test_undefined_constructor_success(self):
        point: Point = Point.undefined()

        assert isinstance(point, Point)
        assert isinstance(point, Object)
        assert point.is_defined() is False

    def test_comparators_success(
        self,
        latitude_1: Angle,
        longitude_1: Angle,
        latitude_2: Angle,
        longitude_2: Angle,
    ):
        point_1: Point = Point(latitude_1, longitude_1)
        point_2: Point = Point(latitude_1, longitude_1)
        point_3: Point = Point(latitude_1, longitude_2)
        point_4: Point = Point(latitude_2, longitude_1)
        point_5: Point = Point(latitude_1, longitude_1 + Angle.degrees(360.0))
        point_6: Point = Point.undefined()

        assert point_1 == point_1
        assert point_1 == point_2
        assert point_1 != point_3
        assert point_1 != point_4
        assert point_1 == point_5
        assert point_1 != point_6

    def test_get_latitude_success(
        self,
        latitude_1: Angle,
        longitude_1: Angle,
    ):
        point: Point = Point(latitude_1, longitude_1)
        assert point.get_latitude() == latitude_1

    def test_get_longitude_success(
        self,
        latitude_1: Angle,
        longitude_1: Angle,
    ):
        point: Point = Point(latitude_1, longitude_1)
        assert point.get_longitude() == longitude_1

    def test_is_collinear_success(
        self,
    ):
        point_1: Point = Point(Angle.degrees(0.0), Angle.degrees(0.0))
        point_2: Point = Point(Angle.degrees(0.0), Angle.degrees(90.0))
        point_3: Point = Point(Angle.degrees(0.0), Angle.degrees(180.0))
        point_4: Point = Point(Angle.degrees(45.0), Angle.degrees(90.0))

        assert point_1.is_collinear(point_2, point_3)
        assert not point_1.is_collinear(point_2, point_4)

    def test_str_repr(
        self,
        latitude_1: Angle,
        longitude_1: Angle,
    ):
        point: Point = Point(latitude_1, longitude_1)

        assert len(str(point)) > 0
        assert len(repr(point)) > 0
