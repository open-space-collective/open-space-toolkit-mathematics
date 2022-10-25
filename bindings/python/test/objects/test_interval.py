################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           bindings/python/test/objects/test_interval.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

import ostk.mathematics as mathematics

from ostk.core.types import Real, String

################################################################################################################################################################

RealInterval = mathematics.objects.RealInterval
Type = RealInterval.Type

################################################################################################################################################################

class TestInterval:

    def test_type (self):

        enum_members = Type.__members__

        assert list(enum_members.keys()) == ['Undefined', 'Closed', 'Open', 'HalfOpenLeft', 'HalfOpenRight']
        assert list(enum_members.values()) == [Type.Undefined, Type.Closed, Type.Open, Type.HalfOpenLeft, Type.HalfOpenRight]

    def test_default_constructor (self):

        # Input types for RealInterval
        interval_1 = RealInterval(-4.31, 1.0, Type.Open)
        interval_2 = RealInterval(-2.0, -1.0, Type.Closed)
        interval_3 = RealInterval(3.5, 4567.35566, Type.HalfOpenRight)
        interval_4 = RealInterval(1.45, 1.45, Type.Open)
        interval_5 = RealInterval(1.45, 1.45, Type.Closed)

        assert isinstance(interval_1, RealInterval)
        assert isinstance(interval_2, RealInterval)
        assert isinstance(interval_3, RealInterval)
        assert isinstance(interval_4, RealInterval)
        assert isinstance(interval_5, RealInterval)
        assert interval_1 is not None
        assert interval_2 is not None
        assert interval_3 is not None
        assert interval_4 is not None
        assert interval_5 is not None

        with pytest.raises(TypeError):

            interval = RealInterval(3.0, 1, Type.Closed)

        interval_6 = RealInterval(Real(-4.31), Real(1.0), Type.Open)
        interval_7 = RealInterval(Real(-2.0), Real(-1.0), Type.Closed)
        interval_8 = RealInterval(Real(3.5), Real(4567.35566), Type.HalfOpenRight)
        interval_9 = RealInterval(Real(1.45), Real(1.45), Type.Open)
        interval_10 = RealInterval(Real(1.45), Real(1.45), Type.Closed)

        assert isinstance(interval_6, RealInterval)
        assert isinstance(interval_7, RealInterval)
        assert isinstance(interval_8, RealInterval)
        assert isinstance(interval_9, RealInterval)
        assert isinstance(interval_10, RealInterval)
        assert interval_6 is not None
        assert interval_7 is not None
        assert interval_8 is not None
        assert interval_9 is not None
        assert interval_10 is not None

        # Interval Bounds
        a = -4.31
        b = 3.0

        # Types of RealInterval
        interval_undefined = RealInterval(a, b, Type.Undefined)
        interval_closed = RealInterval(a, b, Type.Closed)
        interval_open = RealInterval(a, b, Type.Open)
        interval_halfopenleft = RealInterval(a, b, Type.HalfOpenLeft)
        interval_halfopenright = RealInterval(a, b, Type.HalfOpenRight)

        assert isinstance(interval_undefined, RealInterval)
        assert isinstance(interval_closed, RealInterval)
        assert isinstance(interval_open, RealInterval)
        assert isinstance(interval_halfopenleft, RealInterval)
        assert isinstance(interval_halfopenright, RealInterval)

        # Unvalid interval definition

        with pytest.raises(RuntimeError):

            invalid_interval_1 = RealInterval(4.8, 3.5, Type.Open)

        with pytest.raises(RuntimeError):

            invalid_interval_2 = RealInterval(4.8, 3.5, Type.Closed)

        with pytest.raises(RuntimeError):

            invalid_interval_3 = RealInterval(4.8, 3.5, Type.HalfOpenLeft)

        with pytest.raises(RuntimeError):

            invalid_interval_4 = RealInterval(4.8, 3.5, Type.HalfOpenRight)

    def test_undefined_constructor (self):

        undefined_interval = RealInterval.undefined()

        assert isinstance(undefined_interval, RealInterval)
        assert undefined_interval is not None
        assert undefined_interval.is_defined() is False

    def test_closed_constructor (self):

        a = -3.1
        b = 45.6

        closed_interval = RealInterval.closed(a, b)

        assert isinstance(closed_interval, RealInterval)
        assert closed_interval is not None
        assert closed_interval.is_defined()
        assert closed_interval.get_lower_bound() == a
        assert closed_interval.get_upper_bound() == b

    def test_is_defined (self):

        # Interval Bounds
        a = -4.31
        b = 3.0

        # Types of RealInterval
        interval_undefined = RealInterval(a, b, Type.Undefined)
        interval_closed = RealInterval(a, b, Type.Closed)
        interval_open = RealInterval(a, b, Type.Open)
        interval_halfopenleft = RealInterval(a, b, Type.HalfOpenLeft)
        interval_halfopenright = RealInterval(a, b, Type.HalfOpenRight)

        assert interval_undefined.is_defined() is False
        assert interval_closed.is_defined() is True
        assert interval_open.is_defined() is True
        assert interval_halfopenleft.is_defined() is True
        assert interval_halfopenright.is_defined() is True
        assert RealInterval.undefined().is_defined() is False

    # def test_is_degenerate ():

    def test_intersects (self):

        # Interval Bounds
        a = -4.31
        b = 3.0

        # Types of RealInterval
        interval_undefined = RealInterval(a, b, Type.Undefined)
        interval_closed = RealInterval(a, b, Type.Closed)
        interval_open = RealInterval(a, b, Type.Open)
        interval_halfopenleft = RealInterval(a, b, Type.HalfOpenLeft)
        interval_halfopenright = RealInterval(a, b, Type.HalfOpenRight)

        # Define Test Intervals
        interval_left = RealInterval(-5.0, -4.5, Type.Closed)
        interval_intersects_left = RealInterval(-5.0, -4.26, Type.Closed)
        interval_right = RealInterval(4.56, 4.67, Type.Closed)
        interval_intersects_right = RealInterval(2.78, 46.09, Type.Closed)
        interval_between = RealInterval(-3.4, 2.45, Type.Closed)
        interval_bigger = RealInterval(-45.0, 34.12, Type.Closed)

        # Add test cases with contained intervals not Type.Closed...
        # Add test cases with open intervals and half open intervals...

        # Test intersects on undefined

        # with pytest.raises(RuntimeError):

        #     interval_undefined.intersects

        # Test intersects on closed

        assert interval_closed.intersects(interval_left) is False
        assert interval_closed.intersects(interval_intersects_left) is True
        assert interval_closed.intersects(interval_right) is False
        assert interval_closed.intersects(interval_intersects_right) is True
        assert interval_closed.intersects(interval_between) is True
        assert interval_closed.intersects(interval_bigger) is True

        # Test intersects on open

        assert interval_open.intersects(interval_left) is False
        assert interval_open.intersects(interval_intersects_left) is True
        assert interval_open.intersects(interval_right) is False
        assert interval_open.intersects(interval_intersects_right) is True
        assert interval_open.intersects(interval_between) is True
        assert interval_open.intersects(interval_bigger) is True

        # Test intersects on halfopenleft

        assert interval_halfopenleft.intersects(interval_left) is False
        assert interval_halfopenleft.intersects(interval_intersects_left) is True
        assert interval_halfopenleft.intersects(interval_right) is False
        assert interval_halfopenleft.intersects(interval_intersects_right) is True
        assert interval_halfopenleft.intersects(interval_between) is True
        assert interval_halfopenleft.intersects(interval_bigger) is True

        # Test intersects on halfopenright

        assert interval_halfopenright.intersects(interval_left) is False
        assert interval_halfopenright.intersects(interval_intersects_left) is True
        assert interval_halfopenright.intersects(interval_right) is False
        assert interval_halfopenright.intersects(interval_intersects_right) is True
        assert interval_halfopenright.intersects(interval_between) is True
        assert interval_halfopenright.intersects(interval_bigger) is True

    def test_contains_real (self):

        # Interval Bounds
        a = -4.31
        b = 3.0

        # Types of RealInterval
        interval_undefined = RealInterval(a, b, Type.Undefined)
        interval_closed = RealInterval(a, b, Type.Closed)
        interval_open = RealInterval(a, b, Type.Open)
        interval_halfopenleft = RealInterval(a, b, Type.HalfOpenLeft)
        interval_halfopenright = RealInterval(a, b, Type.HalfOpenRight)

        # Define Reals
        real_left = -5.43
        real_right = 3.1
        real_leftbound = a
        real_rightbound = b
        real_between_1 = 2.3
        real_between_2 = 2.999999999

        # Test contains on undefined

        with pytest.raises(RuntimeError):

            interval_undefined.contains(real_left)

        # Test contains on closed

        assert interval_closed.contains(real_left) is False
        assert interval_closed.contains(real_right) is False
        assert interval_closed.contains(real_leftbound) is True
        assert interval_closed.contains(real_rightbound) is True
        assert interval_closed.contains(real_between_1) is True
        assert interval_closed.contains(real_between_2) is True

        # Test contains on open

        assert interval_open.contains(real_left) is False
        assert interval_open.contains(real_right) is False
        assert interval_open.contains(real_leftbound) is False
        assert interval_open.contains(real_rightbound) is False
        assert interval_open.contains(real_between_1) is True
        assert interval_open.contains(real_between_2) is True

        # Test contains on halfopenleft

        assert interval_halfopenleft.contains(real_left) is False
        assert interval_halfopenleft.contains(real_right) is False
        assert interval_halfopenleft.contains(real_leftbound) is False
        assert interval_halfopenleft.contains(real_rightbound) is True
        assert interval_halfopenleft.contains(real_between_1) is True
        assert interval_halfopenleft.contains(real_between_2) is True

        # Test contains on halfopenright

        assert interval_halfopenright.contains(real_left) is False
        assert interval_halfopenright.contains(real_right) is False
        assert interval_halfopenright.contains(real_leftbound) is True
        assert interval_halfopenright.contains(real_rightbound) is False
        assert interval_halfopenright.contains(real_between_1) is True
        assert interval_halfopenright.contains(real_between_2) is True

    def test_contains_interval (self):

        # Interval Bounds
        a = -4.31
        b = 3.0

        # Types of RealInterval
        interval_undefined = RealInterval(a, b, Type.Undefined)
        interval_closed = RealInterval(a, b, Type.Closed)
        interval_open = RealInterval(a, b, Type.Open)
        interval_halfopenleft = RealInterval(a, b, Type.HalfOpenLeft)
        interval_halfopenright = RealInterval(a, b, Type.HalfOpenRight)

        # Define Test Intervals
        interval_left = RealInterval(-5.0, -4.5, Type.Closed)
        interval_intersects_left = RealInterval(-5.0, -4.56, Type.Closed)
        interval_right = RealInterval(4.56, 4.67, Type.Closed)
        interval_intersects_right = RealInterval(2.78, 46.09, Type.Closed)
        interval_between = RealInterval(-3.4, 2.45, Type.Closed)
        interval_bigger = RealInterval(-45.0, 34.12, Type.Closed)

        # Add test cases with contained intervals not Type.Closed...

        # Test contains on undefined

        with pytest.raises(RuntimeError):

            interval_undefined.contains(interval_left)

        # Test contains on closed

        assert interval_closed.contains(interval_left) is False
        assert interval_closed.contains(interval_intersects_left) is False
        assert interval_closed.contains(interval_right) is False
        assert interval_closed.contains(interval_intersects_right) is False
        assert interval_closed.contains(interval_between) is True
        assert interval_closed.contains(interval_bigger) is False

        # Test contains on open

        assert interval_open.contains(interval_left) is False
        assert interval_open.contains(interval_intersects_left) is False
        assert interval_open.contains(interval_right) is False
        assert interval_open.contains(interval_intersects_right) is False
        assert interval_open.contains(interval_between) is True
        assert interval_open.contains(interval_bigger) is False

        # Test contains on halfopenleft

        assert interval_halfopenleft.contains(interval_left) is False
        assert interval_halfopenleft.contains(interval_intersects_left) is False
        assert interval_halfopenleft.contains(interval_right) is False
        assert interval_halfopenleft.contains(interval_intersects_right) is False
        assert interval_halfopenleft.contains(interval_between) is True
        assert interval_halfopenleft.contains(interval_bigger) is False

        # Test contains on halfopenright

        assert interval_halfopenright.contains(interval_left) is False
        assert interval_halfopenright.contains(interval_intersects_left) is False
        assert interval_halfopenright.contains(interval_right) is False
        assert interval_halfopenright.contains(interval_intersects_right) is False
        assert interval_halfopenright.contains(interval_between) is True
        assert interval_halfopenright.contains(interval_bigger) is False

    def test_get_bounds (self):

        # Interval Bounds
        a = -4.31
        b = 3.0

        # Types of RealInterval
        interval_undefined = RealInterval(a, b, Type.Undefined)
        interval_closed = RealInterval(a, b, Type.Closed)
        interval_open = RealInterval(a, b, Type.Open)
        interval_halfopenleft = RealInterval(a, b, Type.HalfOpenLeft)
        interval_halfopenright = RealInterval(a, b, Type.HalfOpenRight)

        # get_lower_bound
        with pytest.raises(RuntimeError):

            interval_undefined.get_lower_bound()

        assert interval_closed.get_lower_bound() == a
        assert interval_open.get_lower_bound() == a
        assert interval_halfopenleft.get_lower_bound() == a
        assert interval_halfopenright.get_lower_bound() == a

        # get_upper_bound
        with pytest.raises(RuntimeError):

            interval_undefined.get_upper_bound()

        assert interval_closed.get_upper_bound() == b
        assert interval_open.get_upper_bound() == b
        assert interval_halfopenleft.get_upper_bound() == b
        assert interval_halfopenright.get_upper_bound() == b

    def test_to_string (self):

        # Interval Bounds
        a = -4.31
        b = 3.0

        # Types of RealInterval
        interval_undefined = RealInterval(a, b, Type.Undefined)
        interval_closed = RealInterval(a, b, Type.Closed)
        interval_open = RealInterval(a, b, Type.Open)
        interval_halfopenleft = RealInterval(a, b, Type.HalfOpenLeft)
        interval_halfopenright = RealInterval(a, b, Type.HalfOpenRight)

        with pytest.raises(RuntimeError):

            interval_undefined.to_string()

        assert isinstance(interval_closed.to_string(), String)
        assert interval_closed.to_string() == '[-4.3099999999999996, 3.0]'
        assert interval_open.to_string() == ']-4.3099999999999996, 3.0['
        assert interval_halfopenleft.to_string() == ']-4.3099999999999996, 3.0]'
        assert interval_halfopenright.to_string() == '[-4.3099999999999996, 3.0['

    def test_get_intersection_with (self):

        test_cases = [
            (RealInterval(0.0, 10.0, Type.HalfOpenLeft),  RealInterval(5.0, 7.0,  Type.HalfOpenLeft),    RealInterval(5.0, 7.0, Type.HalfOpenLeft)),
            (RealInterval(0.0, 10.0, Type.HalfOpenRight), RealInterval(-15.0, 25.0, Type.HalfOpenRight), RealInterval(0.0, 10.0, Type.HalfOpenRight)),
            (RealInterval(0.0, 10.0, Type.Open),          RealInterval(-5.0, 7.0, Type.Open),            RealInterval(0.0, 7.0, Type.Open)),
            (RealInterval(0.0, 10.0, Type.Closed),        RealInterval(5.0, 15.0,  Type.Closed),         RealInterval(5.0, 10.0, Type.Closed)),
        ]

        for test_case in test_cases:
            first_interval = test_case[0]
            second_interval = test_case[1]
            expected_interval = test_case[2]

            assert first_interval.get_intersection_with(second_interval) == expected_interval

    def test_get_union_with (self):

        test_cases = [
            (RealInterval(0.0, 10.0, Type.HalfOpenLeft),  RealInterval(5.0, 7.0, Type.HalfOpenLeft),     RealInterval(0.0, 10.0, Type.HalfOpenLeft)),
            (RealInterval(0.0, 10.0, Type.HalfOpenRight), RealInterval(-15.0, 25.0, Type.HalfOpenRight), RealInterval(-15.0, 25.0, Type.HalfOpenRight)),
            (RealInterval(0.0, 10.0, Type.Open),          RealInterval(-5.0, 7.0, Type.Open),            RealInterval(-5.0, 10.0, Type.Open)),
            (RealInterval(0.0, 10.0, Type.Closed),        RealInterval(5.0, 15.0, Type.Closed),          RealInterval(0.0, 15.0, Type.Closed)),
        ]

        for test_case in test_cases:
            first_interval = test_case[0]
            second_interval = test_case[1]
            expected_interval = test_case[2]

            assert first_interval.get_union_with(second_interval) == expected_interval

################################################################################################################################################################
