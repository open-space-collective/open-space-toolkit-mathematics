/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Interval.hpp>

inline void OpenSpaceToolkitMathematicsPy_Object_Interval(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;

    using ostk::mathematics::object::Interval;

    class_<Interval<Real>> real_interval(aModule, "RealInterval");

    // Define constructor
    real_interval
        .def(
            init<const Real&, const Real&, const Interval<Real>::Type&>(),
            R"doc(
                Create an interval with specified bounds and type.

                Args:
                    lower_bound (float): The lower bound of the interval.
                    upper_bound (float): The upper bound of the interval.
                    type (RealInterval.Type): The type of interval (Closed, Open, HalfOpenLeft, HalfOpenRight).

                Example:
                    >>> interval = RealInterval(0.0, 1.0, RealInterval.Type.Closed)  # [0, 1]
                    >>> interval = RealInterval(0.0, 1.0, RealInterval.Type.Open)    # (0, 1)
            )doc",
            arg("lower_bound"),
            arg("upper_bound"),
            arg("type")
        )

        // Define methods
        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Interval<Real>>))
        .def("__repr__", &(shiftToString<Interval<Real>>))

        .def(
            "is_defined",
            &Interval<Real>::isDefined,
            R"doc(
                Check if the interval is defined.

                Returns:
                    bool: True if the interval is defined, False otherwise.

                Example:
                    >>> interval = RealInterval.closed(0.0, 1.0)
                    >>> interval.is_defined()  # True
            )doc"
        )
        .def(
            "is_degenerate",
            &Interval<Real>::isDegenerate,
            R"doc(
                Check if the interval is degenerate (single point).

                Returns:
                    bool: True if the interval represents a single point, False otherwise.

                Example:
                    >>> interval = RealInterval.closed(1.0, 1.0)
                    >>> interval.is_degenerate()  # True
            )doc"
        )
        .def(
            "intersects",
            &Interval<Real>::intersects,
            R"doc(
                Check if this interval intersects with another interval.

                Args:
                    interval (RealInterval): The interval to check intersection with.

                Returns:
                    bool: True if intervals intersect, False otherwise.

                Example:
                    >>> interval1 = RealInterval.closed(0.0, 2.0)
                    >>> interval2 = RealInterval.closed(1.0, 3.0)
                    >>> interval1.intersects(interval2)  # True
            )doc",
            arg("interval")
        )
        .def(
            "contains",
            overload_cast<const Real&>(&Interval<Real>::contains, const_),
            R"doc(
                Check if the interval contains a real number.

                Args:
                    real (float): The real number to check.

                Returns:
                    bool: True if the interval contains the number, False otherwise.

                Example:
                    >>> interval = RealInterval.closed(0.0, 1.0)
                    >>> interval.contains(0.5)  # True
                    >>> interval.contains(1.5)  # False
            )doc",
            arg("real")
        )
        .def(
            "contains",
            overload_cast<const Interval<Real>&>(&Interval<Real>::contains, const_),
            R"doc(
                Check if this interval contains another interval.

                Args:
                    interval (RealInterval): The interval to check containment for.

                Returns:
                    bool: True if this interval contains the other interval, False otherwise.

                Example:
                    >>> interval1 = RealInterval.closed(0.0, 2.0)
                    >>> interval2 = RealInterval.closed(0.5, 1.5)
                    >>> interval1.contains(interval2)  # True
            )doc",
            arg("interval")
        )
        .def(
            "get_intersection_with",
            &Interval<Real>::getIntersectionWith,
            R"doc(
                Get the intersection of this interval with another interval.

                Args:
                    interval (RealInterval): The interval to intersect with.

                Returns:
                    RealInterval: The intersection interval, or undefined if no intersection.

                Example:
                    >>> interval1 = RealInterval.closed(0.0, 2.0)
                    >>> interval2 = RealInterval.closed(1.0, 3.0)
                    >>> intersection = interval1.get_intersection_with(interval2)
                    >>> # intersection represents [1.0, 2.0]
            )doc",
            arg("interval")
        )
        .def(
            "get_union_with",
            &Interval<Real>::getUnionWith,
            R"doc(
                Get the union of this interval with another interval.

                Args:
                    interval (RealInterval): The interval to union with.

                Returns:
                    RealInterval: The union interval.

                Example:
                    >>> interval1 = RealInterval.closed(0.0, 1.0)
                    >>> interval2 = RealInterval.closed(0.5, 2.0)
                    >>> union = interval1.get_union_with(interval2)
                    >>> # union represents [0.0, 2.0]
            )doc",
            arg("interval")
        )

        .def(
            "get_lower_bound",
            &Interval<Real>::getLowerBound,
            R"doc(
                Get the lower bound of the interval.

                Returns:
                    float: The lower bound value.

                Example:
                    >>> interval = RealInterval.closed(0.0, 1.0)
                    >>> interval.get_lower_bound()  # 0.0
            )doc"
        )
        .def(
            "get_upper_bound",
            &Interval<Real>::getUpperBound,
            R"doc(
                Get the upper bound of the interval.

                Returns:
                    float: The upper bound value.

                Example:
                    >>> interval = RealInterval.closed(0.0, 1.0)
                    >>> interval.get_upper_bound()  # 1.0
            )doc"
        )
        .def(
            "to_string",
            &Interval<Real>::toString,
            R"doc(
                Convert the interval to a string representation.

                Returns:
                    str: String representation of the interval.

                Example:
                    >>> interval = RealInterval.closed(0.0, 1.0)
                    >>> interval.to_string()  # "[0, 1]"
            )doc"
        )

        // Define static methods
        .def_static(
            "undefined",
            &Interval<Real>::Undefined,
            R"doc(
                Create an undefined interval.

                Returns:
                    RealInterval: An undefined interval.

                Example:
                    >>> undefined_interval = RealInterval.undefined()
                    >>> undefined_interval.is_defined()  # False
            )doc"
        )
        .def_static(
            "closed",
            &Interval<Real>::Closed,
            R"doc(
                Create a closed interval [a, b].

                Args:
                    lower_bound (float): The lower bound (inclusive).
                    upper_bound (float): The upper bound (inclusive).

                Returns:
                    RealInterval: A closed interval.

                Example:
                    >>> interval = RealInterval.closed(0.0, 1.0)  # [0, 1]
                    >>> interval.contains(0.0)  # True
                    >>> interval.contains(1.0)  # True
            )doc",
            arg("lower_bound"),
            arg("upper_bound")
        )
        .def_static(
            "open",
            &Interval<Real>::Open,
            R"doc(
                Create an open interval (a, b).

                Args:
                    lower_bound (float): The lower bound (exclusive).
                    upper_bound (float): The upper bound (exclusive).

                Returns:
                    RealInterval: An open interval.

                Example:
                    >>> interval = RealInterval.open(0.0, 1.0)  # (0, 1)
                    >>> interval.contains(0.0)  # False
                    >>> interval.contains(1.0)  # False
                    >>> interval.contains(0.5)  # True
            )doc",
            arg("lower_bound"),
            arg("upper_bound")
        )
        .def_static(
            "half_open_left",
            &Interval<Real>::HalfOpenLeft,
            R"doc(
                Create a half-open interval (a, b].

                Args:
                    lower_bound (float): The lower bound (exclusive).
                    upper_bound (float): The upper bound (inclusive).

                Returns:
                    RealInterval: A half-open left interval.

                Example:
                    >>> interval = RealInterval.half_open_left(0.0, 1.0)  # (0, 1]
                    >>> interval.contains(0.0)  # False
                    >>> interval.contains(1.0)  # True
            )doc",
            arg("lower_bound"),
            arg("upper_bound")
        )
        .def_static(
            "half_open_right",
            &Interval<Real>::HalfOpenRight,
            R"doc(
                Create a half-open interval [a, b).

                Args:
                    lower_bound (float): The lower bound (inclusive).
                    upper_bound (float): The upper bound (exclusive).

                Returns:
                    RealInterval: A half-open right interval.

                Example:
                    >>> interval = RealInterval.half_open_right(0.0, 1.0)  # [0, 1)
                    >>> interval.contains(0.0)  # True
                    >>> interval.contains(1.0)  # False
            )doc",
            arg("lower_bound"),
            arg("upper_bound")
        )
        .def_static(
            "clip",
            &Interval<Real>::Clip,
            R"doc(
                Clip a list of intervals with a clipping interval.

                Args:
                    intervals (list): List of intervals to clip.
                    clipping_interval (RealInterval): The interval to clip with.

                Returns:
                    list: List of clipped intervals.

                Example:
                    >>> intervals = [RealInterval.closed(0.0, 2.0), RealInterval.closed(3.0, 5.0)]
                    >>> clipping = RealInterval.closed(1.0, 4.0)
                    >>> clipped = RealInterval.clip(intervals, clipping)
            )doc",
            arg("intervals"),
            arg("clipping_interval")
        )
        .def_static(
            "sort",
            &Interval<Real>::Sort,
            R"doc(
                Sort a list of intervals.

                Args:
                    intervals (list): List of intervals to sort.
                    by_lower_bound (bool, optional): Sort by lower bound if True, upper bound if False. Defaults to True.
                    ascending (bool, optional): Sort in ascending order if True, descending if False. Defaults to True.

                Returns:
                    list: Sorted list of intervals.

                Example:
                    >>> intervals = [RealInterval.closed(2.0, 3.0), RealInterval.closed(0.0, 1.0)]
                    >>> sorted_intervals = RealInterval.sort(intervals)
            )doc",
            arg("intervals"),
            arg("by_lower_bound") = true,
            arg("ascending") = true
        )
        .def_static(
            "merge",
            &Interval<Real>::Merge,
            R"doc(
                Merge overlapping intervals in a list.

                Args:
                    intervals (list): List of intervals to merge.

                Returns:
                    list: List of merged intervals with no overlaps.

                Example:
                    >>> intervals = [RealInterval.closed(0.0, 2.0), RealInterval.closed(1.0, 3.0)]
                    >>> merged = RealInterval.merge(intervals)  # [RealInterval.closed(0.0, 3.0)]
            )doc",
            arg("intervals")
        )
        .def_static(
            "get_gaps",
            &Interval<Real>::GetGaps,
            R"doc(
                Find gaps between intervals in a list.

                Args:
                    intervals (list): List of intervals to find gaps between.
                    bound (RealInterval, optional): Bounding interval to consider gaps within. Defaults to undefined.

                Returns:
                    list: List of intervals representing gaps.

                Example:
                    >>> intervals = [RealInterval.closed(0.0, 1.0), RealInterval.closed(2.0, 3.0)]
                    >>> gaps = RealInterval.get_gaps(intervals)  # Gap from 1.0 to 2.0
            )doc",
            arg("intervals"),
            arg_v("bound", Interval<Real>::Undefined(), "RealInterval.undefined()")
        )
        .def_static(
            "logical_or",
            &Interval<Real>::LogicalOr,
            R"doc(
                Perform logical OR operation on two lists of intervals.

                Args:
                    intervals_1 (list): First list of intervals.
                    intervals_2 (list): Second list of intervals.

                Returns:
                    list: List of intervals representing the union of both lists.

                Example:
                    >>> intervals1 = [RealInterval.closed(0.0, 1.0)]
                    >>> intervals2 = [RealInterval.closed(2.0, 3.0)]
                    >>> result = RealInterval.logical_or(intervals1, intervals2)
            )doc",
            arg("intervals_1"),
            arg("intervals_2")
        )
        .def_static(
            "logical_and",
            &Interval<Real>::LogicalAnd,
            R"doc(
                Perform logical AND operation on two lists of intervals.

                Args:
                    intervals_1 (list): First list of intervals.
                    intervals_2 (list): Second list of intervals.

                Returns:
                    list: List of intervals representing the intersection of both lists.

                Example:
                    >>> intervals1 = [RealInterval.closed(0.0, 2.0)]
                    >>> intervals2 = [RealInterval.closed(1.0, 3.0)]
                    >>> result = RealInterval.logical_and(intervals1, intervals2)  # [1.0, 2.0]
            )doc",
            arg("intervals_1"),
            arg("intervals_2")
        )

        ;

    // Add other interval types
    // ...

    // Define emuneration type for "real_interval"
    enum_<Interval<Real>::Type>(real_interval, "Type")

        .value("Undefined", Interval<Real>::Type::Undefined)
        .value("Closed", Interval<Real>::Type::Closed)
        .value("Open", Interval<Real>::Type::Open)
        .value("HalfOpenLeft", Interval<Real>::Type::HalfOpenLeft)
        .value("HalfOpenRight", Interval<Real>::Type::HalfOpenRight)

        ;
}
