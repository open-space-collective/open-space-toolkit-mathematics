# Apache License 2.0

import pytest

import ostk.mathematics as mathematics


Object = mathematics.geometry.planetodetic.Object
Spheroid = mathematics.geometry.planetodetic.object.Spheroid


@pytest.fixture
def equatorial_radius_1() -> float:
    return 1.0


@pytest.fixture
def flattening_1() -> float:
    return 0.1


@pytest.fixture
def equatorial_radius_2() -> float:
    return 2.0


@pytest.fixture
def flattening_2() -> float:
    return 0.2


class TestSpheroid:
    def test_from_equatorial_radius_and_flattening_success(
        self,
        equatorial_radius_1: float,
        flattening_1: float,
    ):
        spheroid: Spheroid = Spheroid.from_equatorial_radius_and_flattening(
            equatorial_radius_1, flattening_1
        )

        assert isinstance(spheroid, Spheroid)
        assert isinstance(spheroid, Object)
        assert spheroid.is_defined()

    def test_from_equatorial_radius_and_flattening_failure(
        self,
        equatorial_radius_1: float,
        flattening_1: float,
    ):
        with pytest.raises(Exception):
            Spheroid.from_equatorial_radius_and_flattening(0.0, flattening_1)

        with pytest.raises(Exception):
            Spheroid.from_equatorial_radius_and_flattening(-1.0, flattening_1)

        with pytest.raises(Exception):
            Spheroid.from_equatorial_radius_and_flattening(equatorial_radius_1, 1.0)

        with pytest.raises(Exception):
            Spheroid.from_equatorial_radius_and_flattening(equatorial_radius_1, 2.0)

    def test_sphere_success(
        self,
        equatorial_radius_1: float,
    ):
        spheroid: Spheroid = Spheroid.sphere(equatorial_radius_1)

        assert isinstance(spheroid, Spheroid)
        assert isinstance(spheroid, Object)
        assert spheroid.is_defined()
        assert spheroid.is_sphere()

    def test_sphere_failure(self):
        with pytest.raises(Exception):
            Spheroid.sphere(0.0)

        with pytest.raises(Exception):
            Spheroid.sphere(-1.0)

    def test_undefined_constructor_success(self):
        spheroid: Spheroid = Spheroid.undefined()

        assert isinstance(spheroid, Spheroid)
        assert isinstance(spheroid, Object)
        assert not spheroid.is_defined()

    def test_comparators_success(
        self,
        equatorial_radius_1: float,
        flattening_1: float,
        equatorial_radius_2: float,
        flattening_2: float,
    ):
        spheroid_1: Spheroid = Spheroid.from_equatorial_radius_and_flattening(
            equatorial_radius_1, flattening_1
        )
        spheroid_2: Spheroid = Spheroid.from_equatorial_radius_and_flattening(
            equatorial_radius_1, flattening_1
        )
        spheroid_3: Spheroid = Spheroid.from_equatorial_radius_and_flattening(
            equatorial_radius_2, flattening_1
        )
        spheroid_4: Spheroid = Spheroid.from_equatorial_radius_and_flattening(
            equatorial_radius_1, flattening_2
        )
        spheroid_5: Spheroid = Spheroid.undefined()

        assert spheroid_1 == spheroid_1
        assert spheroid_1 == spheroid_2
        assert spheroid_1 != spheroid_3
        assert spheroid_1 != spheroid_4
        assert spheroid_1 != spheroid_5

    def test_get_equatorial_radius_success(
        self,
        equatorial_radius_1: float,
        flattening_1: float,
    ):
        spheroid: Spheroid = Spheroid.from_equatorial_radius_and_flattening(
            equatorial_radius_1, flattening_1
        )

        assert spheroid.get_equatorial_radius() == equatorial_radius_1

    def test_get_polar_radius_success(
        self,
        equatorial_radius_1: float,
        flattening_1: float,
    ):
        spheroid: Spheroid = Spheroid.from_equatorial_radius_and_flattening(
            equatorial_radius_1, flattening_1
        )

        assert spheroid.get_polar_radius() < spheroid.get_equatorial_radius()

    def test_get_flattening_success(
        self,
        equatorial_radius_1: float,
        flattening_1: float,
    ):
        spheroid: Spheroid = Spheroid.from_equatorial_radius_and_flattening(
            equatorial_radius_1, flattening_1
        )

        assert spheroid.get_flattening() == flattening_1

    def test_get_eccentricity_success(
        self,
        equatorial_radius_1: float,
        flattening_1: float,
    ):
        spheroid: Spheroid = Spheroid.from_equatorial_radius_and_flattening(
            equatorial_radius_1, flattening_1
        )

        assert spheroid.get_eccentricity() > 0.0

    def test_is_oblate_success(
        self,
        equatorial_radius_1: float,
    ):
        spheroid: Spheroid = Spheroid.from_equatorial_radius_and_flattening(
            equatorial_radius_1,
            0.1,
        )
        assert spheroid.is_oblate()
        assert not spheroid.is_prolate()
        assert not spheroid.is_sphere()

    def test_is_prolate_success(
        self,
        equatorial_radius_1: float,
    ):
        spheroid: Spheroid = Spheroid.from_equatorial_radius_and_flattening(
            equatorial_radius_1, -0.1
        )
        assert spheroid.is_prolate()
        assert not spheroid.is_oblate()
        assert not spheroid.is_sphere()

    def test_is_sphere_success(
        self,
        equatorial_radius_1: float,
    ):
        spheroid: Spheroid = Spheroid.sphere(equatorial_radius_1)
        assert spheroid.is_sphere()
        assert not spheroid.is_oblate()
        assert not spheroid.is_prolate()

    def test_str_repr(
        self,
        equatorial_radius_1: float,
        flattening_1: float,
    ):
        spheroid: Spheroid = Spheroid.from_equatorial_radius_and_flattening(
            equatorial_radius_1, flattening_1
        )

        assert len(str(spheroid)) > 0
        assert len(repr(spheroid)) > 0
