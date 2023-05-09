// Copyright © Loft Orbital Solutions Inc.

#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/Objects/Interval.hpp>

inline void OpenSpaceToolkitMathematicsPy_Objects_Interval(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::types::Real;

    using ostk::math::obj::Interval;

    class_<Interval<Real>> real_interval(aModule, "RealInterval");

    // Define constructor
    real_interval
        .def(
            init<const Real&, const Real&, const Interval<Real>::Type&>(),
            arg("lower_bound"),
            arg("upper_bound"),
            arg("type")
        )

        // Define methods
        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Interval<Real>>))
        .def("__repr__", &(shiftToString<Interval<Real>>))

        .def("is_defined", &Interval<Real>::isDefined)
        .def("is_degenerate", &Interval<Real>::isDegenerate)
        .def("intersects", &Interval<Real>::intersects, arg("interval"))
        .def("contains", overload_cast<const Real&>(&Interval<Real>::contains, const_), arg("real"))
        .def("contains", overload_cast<const Interval<Real>&>(&Interval<Real>::contains, const_), arg("interval"))
        .def("get_intersection_with", &Interval<Real>::getIntersectionWith, arg("interval"))
        .def("get_union_with", &Interval<Real>::getUnionWith, arg("interval"))

        .def("get_lower_bound", &Interval<Real>::getLowerBound)
        .def("get_upper_bound", &Interval<Real>::getUpperBound)
        .def("to_string", &Interval<Real>::toString)

        // Define static methods
        .def_static("undefined", &Interval<Real>::Undefined)
        .def_static("closed", &Interval<Real>::Closed, arg("lower_bound"), arg("upper_bound"));

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
