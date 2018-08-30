////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           LibraryMathematicsPy/Geometry/2D/Objects/Point.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <LibraryMathematicsPy/Utilities/IterableConverter.hpp>

#include <Library/Mathematics/Geometry/2D/Objects/Point.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (LibraryMathematicsPy_Geometry_2D_Objects_Point_toString_overloads, library::math::geom::d2::objects::Point::toString, 0, 2)

inline void                     LibraryMathematicsPy_Geometry_2D_Objects_Point ( )
{

    using namespace boost::python ;

    using library::core::types::Real ;

    using library::math::obj::Vector2d ;
    using library::math::geom::d2::Object ;
    using library::math::geom::d2::objects::Point ;

    scope in_Point = class_<Point, bases<Object>>("Point", init<const Real&, const Real&>())

        .def(init<const Vector2d&>())

        .def(self == self)
        .def(self != self)

        .def(self + other<Vector2d>())
        .def(self - other<Vector2d>())

        .def(self - self)

        .def(self_ns::str(self_ns::self))

        .def("__repr__", +[] (const Point& aPoint) -> std::string { return aPoint.toString() ; })
        
        .def("isDefined", &Point::isDefined)
        .def("isNear", &Point::isNear)
        
        .def("x", +[] (const Point& aPoint) -> double { return aPoint.x() ; })
        .def("y", +[] (const Point& aPoint) -> double { return aPoint.y() ; })
        .def("distanceTo", &Point::distanceTo)
        .def("toString", &Point::toString, LibraryMathematicsPy_Geometry_2D_Objects_Point_toString_overloads())

        .def("translate", &Point::translate)

        .def("Undefined", &Point::Undefined).staticmethod("Undefined")
        .def("Origin", &Point::Origin).staticmethod("Origin")

    ;

    implicitly_convertible<Point, Vector2d>() ;
    implicitly_convertible<Vector2d, Point>() ;

    using library::core::ctnr::Array ;

    IterableConverter()

        .from_python<Array<Point>>()
        .to_python<Array<Point>>()
        
    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////