# Apache License 2.0

"""Types bound by ostk.core crossing into and out of ostk.mathematics.

Both extension modules must use the same nanobind version and ABI for these to resolve.
"""

import sys

import ostk.core as core
from ostk.core.type import Real
from ostk.core.type import String

import ostk.mathematics as mathematics

Angle = mathematics.geometry.Angle
RealInterval = mathematics.object.RealInterval
Quaternion = mathematics.geometry.d3.transformation.rotation.Quaternion


def test_core_is_imported_by_mathematics():
    # ostk/mathematics/__init__.py imports ostk.core first, so core's types are registered before use.
    assert "ostk.core.OpenSpaceToolkitCorePy" in sys.modules or "ostk.core" in sys.modules
    assert core.type.String is String


def test_core_string_argument():
    quaternion = Quaternion.parse(String("[0.0, 0.0, 0.0, 1.0]"), Quaternion.Format.XYZS)

    assert quaternion == Quaternion.unit()


def test_str_argument_converts_implicitly_to_core_string():
    # The str -> String implicit conversion is registered by ostk.core, and applies in ostk.mathematics.
    quaternion = Quaternion.parse("[0.0, 0.0, 0.0, 1.0]", Quaternion.Format.XYZS)

    assert quaternion == Quaternion.unit()


def test_core_string_return_value():
    string = RealInterval.closed(0.0, 1.0).to_string()

    assert type(string) is String
    assert string == String("[0.0, 1.0]")
    assert str(string) == "[0.0, 1.0]"
    assert String("Interval: ") + string == String("Interval: [0.0, 1.0]")


def test_core_real_argument_converts_to_float():
    # Real is deprecated in core 6, but still converts through Real.__float__.
    interval = RealInterval(Real(1.0), Real(2.0), RealInterval.Type.Closed)

    assert interval.get_lower_bound() == 1.0
    assert Angle.degrees(Real(90.0)) == Angle.degrees(90.0)
