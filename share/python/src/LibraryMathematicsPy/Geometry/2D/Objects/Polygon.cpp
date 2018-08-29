////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           LibraryMathematicsPy/Geometry/2D/Objects/Polygon.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/2D/Objects/Polygon.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_2D_Objects_Polygon ( )
{

    using namespace boost::python ;

    using library::core::ctnr::Array ;

    using library::math::obj::Vector2d ;
    using library::math::geom::d2::Object ;
    using library::math::geom::d2::objects::Point ;
    using library::math::geom::d2::objects::Polygon ;

    scope in_Polygon = class_<Polygon, bases<Object>>("Polygon", init<const Array<Point>&, const Array<Array<Point>>&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))
        
        .def("isDefined", &Polygon::isDefined)

        .def("getVertices", &Polygon::getVertices)
        .def("toString", &Polygon::toString)
        .def("translate", &Polygon::translate)
        
        .def("Undefined", &Polygon::Undefined).staticmethod("Undefined")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////