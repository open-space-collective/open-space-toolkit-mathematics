////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           LibraryMathematicsPy/Geometry/2D/Objects/Segment.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <LibraryMathematicsPy/Utilities/IterableConverter.hpp>

#include <Library/Mathematics/Geometry/2D/Objects/Segment.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (LibraryMathematicsPy_Geometry_2D_Objects_Segment_toString_overloads, ostk::math::geom::d2::objects::Segment::toString, 0, 2)

inline void                     LibraryMathematicsPy_Geometry_2D_Objects_Segment ( )
{

    using namespace boost::python ;

    using ostk::math::geom::d2::Object ;
    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::Segment ;

    scope in_Segment = class_<Segment, bases<Object>>("Segment", init<const Point&, const Point&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &Segment::isDefined)
        .def("isDegenerate", &Segment::isDegenerate)

        .def("getFirstPoint", &Segment::getFirstPoint)
        .def("getSecondPoint", &Segment::getSecondPoint)
        .def("getCenter", &Segment::getCenter)
        .def("getDirection", &Segment::getDirection)
        .def("getLength", &Segment::getLength)
        .def("toString", &Segment::toString, LibraryMathematicsPy_Geometry_2D_Objects_Segment_toString_overloads())
        .def("applyTransformation", &Segment::applyTransformation)

        .def("Undefined", &Segment::Undefined).staticmethod("Undefined")

    ;

    using ostk::core::ctnr::Array ;

    IterableConverter()

        .from_python<Array<Segment>>()
        .to_python<Array<Segment>>()

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
