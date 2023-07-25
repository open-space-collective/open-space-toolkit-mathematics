# Apache License 2.0

import pytest

import math

import ostk.mathematics as mathematics


Angle = mathematics.geometry.Angle
Unit = Angle.Unit


def test_angle_unit():
    enum_members = Unit.__members__

    list_keys = ["Undefined", "Radian", "Degree", "Arcminute", "Arcsecond", "Revolution"]

    list_values = [
        Unit.Undefined,
        Unit.Radian,
        Unit.Degree,
        Unit.Arcminute,
        Unit.Arcsecond,
        Unit.Revolution,
    ]

    assert list(enum_members.keys()) == list_keys
    assert list(enum_members.values()) == list_values


def test_angle_default_constructor():
    # Default constructor with Degree Unit
    angle: Angle = Angle(12.34, Unit.Degree)

    assert angle is not None
    assert isinstance(angle, Angle)
    assert angle.in_degrees() == 12.34

    angle: Angle = Angle(-12.34, Unit.Degree)

    assert angle is not None
    assert isinstance(angle, Angle)
    assert angle.in_degrees() == -12.34

    angle: Angle = Angle(365.34, Unit.Degree)

    assert angle is not None
    assert isinstance(angle, Angle)
    assert angle.in_degrees() == 365.34

    angle: Angle = Angle(-4000.34, Unit.Degree)

    assert angle is not None
    assert isinstance(angle, Angle)
    assert angle.in_degrees() == -4000.34

    # Default constructor with Radian Unit
    angle: Angle = Angle(3.4, Unit.Radian)

    assert angle is not None
    assert isinstance(angle, Angle)
    assert angle.in_radians() == 3.4

    # Default constructor with Arcminute Unit
    angle: Angle = Angle(3600.0, Unit.Arcminute)

    assert angle is not None
    assert isinstance(angle, Angle)
    assert angle.in_arcminutes() == 3600.0

    # Default constructor with Arcsecond Unit
    angle: Angle = Angle(3600.0, Unit.Arcsecond)

    assert angle is not None
    assert isinstance(angle, Angle)
    assert angle.in_arcseconds() == 3600.0

    # Default constructor with Revolution Unit
    angle: Angle = Angle(18.0, Unit.Revolution)

    assert angle is not None
    assert isinstance(angle, Angle)
    assert angle.in_revolutions() == 18.0

    # Invalid construction
    with pytest.raises(TypeError):
        angle: Angle = Angle(45, Unit.Degree)


def test_angle_undefined_constructor():
    angle: Angle = Angle.undefined()

    assert angle is not None
    assert isinstance(angle, Angle)
    assert angle.is_defined() is False


def test_angle_zero_constructor():
    angle: Angle = Angle.zero()

    assert angle is not None
    assert isinstance(angle, Angle)
    assert angle.is_defined() is True
    assert angle.get_unit() == Unit.Radian
    assert angle.is_zero() is True
    assert angle.in_radians() == 0.0
    assert angle.in_degrees() == 0.0
    assert angle.in_arcminutes() == 0.0
    assert angle.in_arcseconds() == 0.0
    assert angle.in_revolutions() == 0.0


def test_angle_pi_constructors():
    angle: Angle = Angle.half_pi()

    assert angle is not None
    assert isinstance(angle, Angle)
    assert angle.is_defined()
    assert angle.get_unit() == Unit.Radian
    assert angle.in_radians() == math.pi / 2

    angle: Angle = Angle.pi()

    assert angle is not None
    assert isinstance(angle, Angle)
    assert angle.is_defined()
    assert angle.get_unit() == Unit.Radian
    assert angle.in_radians() == math.pi

    angle: Angle = Angle.two_pi()

    assert angle is not None
    assert isinstance(angle, Angle)
    assert angle.is_defined()
    assert angle.get_unit() == Unit.Radian
    assert angle.in_radians() == 2 * math.pi


def test_angle_unit_constructors():
    # Radian
    angle: Angle = Angle.radians(3.4)

    assert angle is not None
    assert isinstance(angle, Angle)
    assert angle.is_defined()
    assert angle.get_unit() == Unit.Radian
    assert angle.in_radians() == 3.4

    # Degree
    angle: Angle = Angle.degrees(-45.0)

    assert angle is not None
    assert isinstance(angle, Angle)
    assert angle.is_defined()
    assert angle.get_unit() == Unit.Degree
    assert angle.in_degrees() == -45.0

    # Arcminutes
    angle: Angle = Angle.arcminutes(60.5)

    assert angle is not None
    assert isinstance(angle, Angle)
    assert angle.is_defined()
    assert angle.get_unit() == Unit.Arcminute
    assert angle.in_arcminutes() == 60.5

    # Arcseconds
    angle: Angle = Angle.arcseconds(60.5)

    assert angle is not None
    assert isinstance(angle, Angle)
    assert angle.is_defined()
    assert angle.get_unit() == Unit.Arcsecond
    assert angle.in_arcseconds() == 60.5

    # Revolutions
    angle: Angle = Angle.revolutions(3.9)

    assert angle is not None
    assert isinstance(angle, Angle)
    assert angle.is_defined()
    assert angle.get_unit() == Unit.Revolution
    assert angle.in_revolutions() == 3.9


def test_angle_unit_conversion():
    angle: Angle = Angle(60.0, Unit.Degree)

    assert angle.in_degrees() == 60.0
    assert angle.in_radians() == (math.pi * 60.0 / 180.0)
    assert angle.in_arcminutes() == 60.0 * 60.0
    assert (angle.in_arcseconds() - 60.0 * 3600.0) <= 1e-10


def test_angle_comparators():
    angle_deg: Angle = Angle(60.0, Unit.Degree)
    angle_rad: Angle = Angle(60.0 * math.pi / 180.0, Unit.Radian)

    assert angle_deg == angle_deg
    assert angle_rad == angle_rad
    assert angle_deg == angle_rad
    assert angle_deg != Angle(59.0, Unit.Degree)


def test_angle_operators():
    angle: Angle = Angle(30.0, Unit.Degree)
    half_angle: Angle = angle / 2.0
    double_angle: Angle = angle * 2.0
    sum_angle: Angle = angle + angle
    diff_angle: Angle = angle - angle
    positive_angle: Angle = +angle
    negative_angle: Angle = -angle

    assert half_angle is not None
    assert isinstance(half_angle, Angle)
    assert double_angle is not None
    assert isinstance(double_angle, Angle)
    assert sum_angle is not None
    assert isinstance(sum_angle, Angle)
    assert diff_angle is not None
    assert isinstance(diff_angle, Angle)
    assert positive_angle is not None
    assert isinstance(positive_angle, Angle)
    assert negative_angle is not None
    assert isinstance(negative_angle, Angle)

    assert half_angle.in_degrees() == 15.0
    assert double_angle.in_degrees() == 60.0
    assert sum_angle.in_degrees() == 60.0
    assert diff_angle.in_degrees() == 0.0
    assert diff_angle.is_zero()
    assert positive_angle.in_degrees() == +30.0
    assert negative_angle.in_degrees() == -30.0

    angle_deg: Angle = Angle(90.0, Unit.Degree)
    angle_rad: Angle = Angle(math.pi / 2, Unit.Radian)

    sum_angle: Angle = angle_rad + angle_deg
    assert sum_angle is not None
    assert isinstance(sum_angle, Angle)
    assert (sum_angle.in_degrees() - 180.0) <= 1e-10

    angle: Angle = Angle(90.0, Unit.Degree)

    angle *= 3.0
    assert angle is not None
    assert isinstance(angle, Angle)
    assert angle.get_unit() == Unit.Degree
    assert angle.in_degrees() == 270.0

    angle /= 3.0
    assert angle is not None
    assert isinstance(angle, Angle)
    assert angle.get_unit() == Unit.Degree
    assert angle.in_degrees() == 90.0


# def test_angle_between_vector2d ():

# def test_angle_between_vector3d ():

# def test_angle_to_string ():


def test_angle_string_from_unit():
    assert Angle.string_from_unit(Unit.Degree) == "Degree"
    assert Angle.string_from_unit(Unit.Radian) == "Radian"
    assert Angle.string_from_unit(Unit.Arcminute) == "Arcminute"
    assert Angle.string_from_unit(Unit.Arcsecond) == "Arcsecond"
    assert Angle.string_from_unit(Unit.Revolution) == "Revolution"


def test_angle_string_symbol_from_unit():
    assert Angle.symbol_from_unit(Unit.Degree) == "deg"
    assert Angle.symbol_from_unit(Unit.Radian) == "rad"
    assert Angle.symbol_from_unit(Unit.Arcminute) == "amin"
    assert Angle.symbol_from_unit(Unit.Arcsecond) == "asec"
    assert Angle.symbol_from_unit(Unit.Revolution) == "rev"


def test_angle_in_radians_reduction():
    angle: Angle = Angle(math.pi * 3 / 2, Unit.Radian)
    assert angle.in_radians(lower_bound=-math.pi, upper_bound=math.pi) == -math.pi / 2

    angle: Angle = Angle(math.pi / 2, Unit.Radian)
    assert angle.in_radians(lower_bound=-math.pi, upper_bound=math.pi) == math.pi / 2

    angle: Angle = Angle(-math.pi, Unit.Radian)
    assert angle.in_radians(-math.pi, math.pi) == -math.pi

    angle: Angle = Angle(math.pi, Unit.Radian)
    assert angle.in_radians(-math.pi, math.pi) == -math.pi


def test_angle_in_degrees_reduction():
    angle: Angle = Angle(359.0, Unit.Degree)
    assert angle.in_degrees(lower_bound=-180.0, upper_bound=180.0) == -1.0

    angle: Angle = Angle(1.0, Unit.Degree)
    assert angle.in_degrees(lower_bound=-180.0, upper_bound=180.0) == 1.0

    angle: Angle = Angle(-180.0, Unit.Degree)
    assert angle.in_degrees(-180.0, 180.0) == -180.0

    angle: Angle = Angle(180.0, Unit.Degree)
    assert angle.in_degrees(-180.0, 180.0) == -180.0


def test_angle_in_arcminutes_reduction():
    angle: Angle = Angle(359.0 * 60.0, Unit.Arcminute)
    assert (
        angle.in_arcminutes(lower_bound=-180.0 * 60.0, upper_bound=180.0 * 60.0) == -60.0
    )

    angle: Angle = Angle(60.0, Unit.Arcminute)
    assert (
        angle.in_arcminutes(lower_bound=-180.0 * 60.0, upper_bound=180.0 * 60.0) == 60.0
    )

    angle: Angle = Angle(-180.0 * 60.0, Unit.Arcminute)
    assert angle.in_arcminutes(-180.0 * 60.0, 180.0 * 60.0) == -180.0 * 60.0

    angle: Angle = Angle(180.0 * 60.0, Unit.Arcminute)
    assert angle.in_arcminutes(-180.0 * 60.0, 180.0 * 60.0) == -180.0 * 60.0


def test_angle_in_arcseconds_reduction():
    angle: Angle = Angle(359.0 * 3600.0, Unit.Arcsecond)
    assert (
        angle.in_arcseconds(lower_bound=-180.0 * 3600.0, upper_bound=180.0 * 3600.0)
        == -3600.0
    )

    angle: Angle = Angle(3600.0, Unit.Arcsecond)
    assert (
        angle.in_arcseconds(lower_bound=-180.0 * 3600.0, upper_bound=180.0 * 3600.0)
        == 3600.0
    )

    angle: Angle = Angle(-180 * 3600.0, Unit.Arcsecond)
    assert angle.in_arcseconds(-180.0 * 3600.0, 180.0 * 3600.0) == -180.0 * 3600.0

    angle: Angle = Angle(180.0 * 3600.0, Unit.Arcsecond)
    assert angle.in_arcseconds(-180.0 * 3600.0, 180.0 * 3600.0) == -180.0 * 3600.0
