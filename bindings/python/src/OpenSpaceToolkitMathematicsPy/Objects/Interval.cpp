////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Objects/Interval.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Objects/Interval.hpp>

#include <OpenSpaceToolkit/Core/Types/Real.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Objects_Interval       ( )
{

    using namespace boost::python ;

    using ostk::core::types::Real ;

    using ostk::math::obj::Interval ;

    scope in_RealInterval = class_<Interval<Real>>("RealInterval", init<const Real&, const Real&, const Interval<Real>::Type&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("is_defined", &Interval<Real>::isDefined)
        .def("is_degenerate", &Interval<Real>::isDegenerate)
        .def("intersects", &Interval<Real>::intersects)
        .def("contains_real", +[] (const Interval<Real>& anInterval, const Real& aReal) -> bool { return anInterval.contains(aReal) ; })
        .def("contains_interval", +[] (const Interval<Real>& anInterval, const Interval<Real>& anOtherInterval) -> bool { return anInterval.contains(anOtherInterval) ; })

        .def("get_lower_bound", &Interval<Real>::getLowerBound)
        .def("get_upper_bound", &Interval<Real>::getUpperBound)
        .def("to_string", &Interval<Real>::toString)

        .def("undefined", &Interval<Real>::Undefined).staticmethod("undefined")
        .def("closed", &Interval<Real>::Closed).staticmethod("closed")

    ;

    enum_<Interval<Real>::Type>("Type")

        .value("Undefined", Interval<Real>::Type::Undefined)
        .value("Closed", Interval<Real>::Type::Closed)
        .value("Open", Interval<Real>::Type::Open)
        .value("HalfOpenLeft", Interval<Real>::Type::HalfOpenLeft)
        .value("HalfOpenRight", Interval<Real>::Type::HalfOpenRight)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
