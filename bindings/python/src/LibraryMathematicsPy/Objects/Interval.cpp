////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           LibraryMathematicsPy/Objects/Interval.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Objects/Interval.hpp>

#include <OpenSpaceToolkit/Core/Types/Real.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Objects_Interval       ( )
{

    using namespace boost::python ;

    using ostk::core::types::Real ;

    using ostk::math::obj::Interval ;

    scope in_RealInterval = class_<Interval<Real>>("RealInterval", init<const Real&, const Real&, const Interval<Real>::Type&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &Interval<Real>::isDefined)
        .def("isDegenerate", &Interval<Real>::isDegenerate)
        .def("intersects", &Interval<Real>::intersects)
        .def("containsReal", +[] (const Interval<Real>& anInterval, const Real& aReal) -> bool { return anInterval.contains(aReal) ; })
        .def("containsInterval", +[] (const Interval<Real>& anInterval, const Interval<Real>& anOtherInterval) -> bool { return anInterval.contains(anOtherInterval) ; })

        .def("getLowerBound", &Interval<Real>::getLowerBound)
        .def("getUpperBound", &Interval<Real>::getUpperBound)
        .def("toString", &Interval<Real>::toString)

        .def("Undefined", &Interval<Real>::Undefined).staticmethod("Undefined")
        .def("Closed", &Interval<Real>::Closed).staticmethod("Closed")

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
