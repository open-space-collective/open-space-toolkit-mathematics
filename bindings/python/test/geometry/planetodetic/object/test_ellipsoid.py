# Apache License 2.0

import pytest

import ostk.mathematics as mathematics


Object = mathematics.geometry.planetodetic.Object
Ellipsoid = mathematics.geometry.planetodetic.object.Ellipsoid


@pytest.fixture
def equatorial_radius_a() -> float:
    return 6378137.0


@pytest.fixture
def equatorial_radius_b() -> float:
    return 6378137.0


@pytest.fixture
def polar_radius() -> float:
    return 6356752.3142


@pytest.fixture
def different_equatorial_radius_a() -> float:
    return 7000000.0


@pytest.fixture
def different_equatorial_radius_b() -> float:
    return 6500000.0


@pytest.fixture
def different_polar_radius() -> float:
    return 6000000.0


@pytest.fixture
def flattening() -> float:
    return 1.0 / 298.257223563


class TestEllipsoid:
    def test_constructor_success(
        self,
        equatorial_radius_a: float,
        equatorial_radius_b: float,
        polar_radius: float,
    ):
        ellipsoid: Ellipsoid = Ellipsoid(
            equatorial_radius_a, equatorial_radius_b, polar_radius
        )

        assert isinstance(ellipsoid, Ellipsoid)
        assert isinstance(ellipsoid, Object)
        assert ellipsoid.is_defined()
        assert ellipsoid.get_equatorial_radius_a() == equatorial_radius_a
        assert ellipsoid.get_equatorial_radius_b() == equatorial_radius_b
        assert ellipsoid.get_polar_radius() == polar_radius

    def test_sphere_success(
        self,
        equatorial_radius_a: float,
    ):
        ellipsoid: Ellipsoid = Ellipsoid.sphere(equatorial_radius_a)

        assert isinstance(ellipsoid, Ellipsoid)
        assert isinstance(ellipsoid, Object)
        assert ellipsoid.is_defined()
        assert ellipsoid.get_equatorial_radius_a() == equatorial_radius_a
        assert ellipsoid.get_equatorial_radius_b() == equatorial_radius_a
        assert ellipsoid.get_polar_radius() == equatorial_radius_a

    def test_sphere_failure(self):
        with pytest.raises(RuntimeError):
            Ellipsoid.sphere(0.0)

    def test_spheroid_from_equatorial_radius_and_flattening_success(
        self,
        equatorial_radius_a: float,
        flattening: float,
    ):
        ellipsoid: Ellipsoid = Ellipsoid.spheroid(
            equatorial_radius=equatorial_radius_a, flattening=flattening
        )

        assert isinstance(ellipsoid, Ellipsoid)
        assert isinstance(ellipsoid, Object)
        assert ellipsoid.is_defined()
        assert ellipsoid.get_equatorial_radius_a() == equatorial_radius_a
        assert ellipsoid.get_equatorial_radius_b() == equatorial_radius_a
        assert (
            abs(
                float(ellipsoid.get_polar_radius())
                - equatorial_radius_a * (1.0 - flattening)
            )
            < 1e-6
        )

    def test_spheroid_from_equatorial_radius_and_polar_radius_success(
        self,
        equatorial_radius_a: float,
        polar_radius: float,
    ):
        ellipsoid: Ellipsoid = Ellipsoid.spheroid(
            equatorial_radius=equatorial_radius_a, polar_radius=polar_radius
        )

        assert isinstance(ellipsoid, Ellipsoid)
        assert isinstance(ellipsoid, Object)
        assert ellipsoid.is_defined()
        assert ellipsoid.get_equatorial_radius_a() == equatorial_radius_a
        assert ellipsoid.get_equatorial_radius_b() == equatorial_radius_a
        assert ellipsoid.get_polar_radius() == polar_radius

    def test_spheroid_from_polar_radius_and_flattening_success(
        self,
        polar_radius: float,
        flattening: float,
    ):
        ellipsoid: Ellipsoid = Ellipsoid.spheroid(
            polar_radius=polar_radius, flattening=flattening
        )

        assert isinstance(ellipsoid, Ellipsoid)
        assert isinstance(ellipsoid, Object)
        assert ellipsoid.is_defined()
        expected_equatorial_radius = polar_radius / (1.0 - flattening)
        assert (
            abs(float(ellipsoid.get_equatorial_radius_a()) - expected_equatorial_radius)
            < 1e-6
        )
        assert (
            abs(float(ellipsoid.get_equatorial_radius_b()) - expected_equatorial_radius)
            < 1e-6
        )
        assert ellipsoid.get_polar_radius() == polar_radius

    def test_wgs84_success(self):
        ellipsoid: Ellipsoid = Ellipsoid.wgs84()

        assert isinstance(ellipsoid, Ellipsoid)
        assert isinstance(ellipsoid, Object)
        assert ellipsoid.is_defined()
        assert ellipsoid.get_equatorial_radius_a() == 6378137.0
        assert ellipsoid.get_equatorial_radius_b() == 6378137.0
        assert abs(float(ellipsoid.get_polar_radius()) - 6356752.314245) < 1e-6

    def test_undefined_success(self):
        ellipsoid: Ellipsoid = Ellipsoid.undefined()

        assert isinstance(ellipsoid, Ellipsoid)
        assert isinstance(ellipsoid, Object)
        assert not ellipsoid.is_defined()

    def test_comparators_success(
        self,
        equatorial_radius_a: float,
        equatorial_radius_b: float,
        polar_radius: float,
        different_equatorial_radius_a: float,
        different_equatorial_radius_b: float,
        different_polar_radius: float,
    ):
        ellipsoid_1: Ellipsoid = Ellipsoid(
            equatorial_radius_a, equatorial_radius_b, polar_radius
        )
        ellipsoid_2: Ellipsoid = Ellipsoid(
            equatorial_radius_a, equatorial_radius_b, polar_radius
        )
        ellipsoid_3: Ellipsoid = Ellipsoid(
            different_equatorial_radius_a, equatorial_radius_b, polar_radius
        )
        ellipsoid_4: Ellipsoid = Ellipsoid(
            equatorial_radius_a, different_equatorial_radius_b, polar_radius
        )
        ellipsoid_5: Ellipsoid = Ellipsoid(
            equatorial_radius_a, equatorial_radius_b, different_polar_radius
        )
        ellipsoid_6: Ellipsoid = Ellipsoid.undefined()

        assert ellipsoid_1 == ellipsoid_1
        assert ellipsoid_1 == ellipsoid_2
        assert ellipsoid_1 != ellipsoid_3
        assert ellipsoid_1 != ellipsoid_4
        assert ellipsoid_1 != ellipsoid_5
        assert ellipsoid_1 != ellipsoid_6

    def test_get_equatorial_radius_a_success(
        self,
        equatorial_radius_a: float,
        equatorial_radius_b: float,
        polar_radius: float,
    ):
        ellipsoid: Ellipsoid = Ellipsoid(
            equatorial_radius_a, equatorial_radius_b, polar_radius
        )

        assert ellipsoid.get_equatorial_radius_a() == equatorial_radius_a

    def test_get_equatorial_radius_b_success(
        self,
        equatorial_radius_a: float,
        equatorial_radius_b: float,
        polar_radius: float,
    ):
        ellipsoid: Ellipsoid = Ellipsoid(
            equatorial_radius_a, equatorial_radius_b, polar_radius
        )

        assert ellipsoid.get_equatorial_radius_b() == equatorial_radius_b

    def test_get_polar_radius_success(
        self,
        equatorial_radius_a: float,
        equatorial_radius_b: float,
        polar_radius: float,
    ):
        ellipsoid: Ellipsoid = Ellipsoid(
            equatorial_radius_a, equatorial_radius_b, polar_radius
        )

        assert ellipsoid.get_polar_radius() == polar_radius

    def test_str_repr(
        self,
        equatorial_radius_a: float,
        equatorial_radius_b: float,
        polar_radius: float,
    ):
        ellipsoid: Ellipsoid = Ellipsoid(
            equatorial_radius_a, equatorial_radius_b, polar_radius
        )

        assert len(str(ellipsoid)) > 0
        assert len(repr(ellipsoid)) > 0
