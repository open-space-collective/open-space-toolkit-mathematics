////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           LibraryMathematicsPy/Geometry/2D/Objects/Point.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <LibraryMathematicsPy/Utilities/IterableConverter.hpp>

#include <Library/Mathematics/Geometry/2D/Objects/Point.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_2D_Objects_Point ( )
{

    using namespace boost::python ;

    using library::core::types::Real ;

    using library::math::obj::Vector2d ;
    using library::math::geom::d2::Object ;
    using library::math::geom::d2::objects::Point ;

    scope in_Point = class_<Point, bases<Object>>("Point", init<const Real&, const Real&>())

        .def(self == self)
        .def(self != self)

        .def(self + other<Vector2d>())
        .def(self - other<Vector2d>())

        .def(self - self)

        .def(self_ns::str(self_ns::self))

        .def("__repr__", +[] (const Point& aPoint) -> std::string { return aPoint.toString() ; })
        
        .def("isDefined", &Point::isDefined)
        .def("isNear", &Point::isNear)
        
        .def("distanceTo", &Point::distanceTo)
        .def("toString", &Point::toString)

        .def("translate", &Point::translate)

        .def("Undefined", &Point::Undefined).staticmethod("Undefined")
        .def("Origin", &Point::Origin).staticmethod("Origin")

    ;

    using library::core::ctnr::Array ;

    IterableConverter()

        .from_python<Array<Point>>()
        .to_python<Array<Point>>()
        
    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////