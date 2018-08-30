////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           LibraryMathematicsPy/Geometry/2D/Objects/Segment.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/2D/Objects/Segment.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_2D_Objects_Segment ( )
{

    using namespace boost::python ;

    using library::math::geom::d2::Object ;
    using library::math::geom::d2::objects::Point ;
    using library::math::geom::d2::objects::Segment ;

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
        .def("toString", &Segment::toString)
        .def("translate", &Segment::translate)
        
        .def("Undefined", &Segment::Undefined).staticmethod("Undefined")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////