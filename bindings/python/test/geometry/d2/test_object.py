# Apache License 2.0

import pytest

import ostk.mathematics as mathematics


Object = mathematics.geometry.d2.Object
Format = Object.Format


def test_geometry_d2_object_format():
    enum_members = Format.__members__

    list_keys = ["Undefined", "Standard", "WKT"]

    list_values = [Format.Undefined, Format.Standard, Format.WKT]

    assert list(enum_members.keys()) == list_keys
    assert list(enum_members.values()) == list_values


def test_geometry_d2_object_no_constructor():
    with pytest.raises(TypeError):
        ob = Object()
