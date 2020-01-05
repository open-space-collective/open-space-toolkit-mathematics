////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           LibraryMathematicsPy/Geometry/2D/Objects/Point.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <LibraryMathematicsPy/Utilities/IterableConverter.hpp>

#include <Library/Mathematics/Geometry/2D/Objects/Point.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (LibraryMathematicsPy_Geometry_2D_Objects_Point_toString_overloads, ostk::math::geom::d2::objects::Point::toString, 0, 2)

inline void                     LibraryMathematicsPy_Geometry_2D_Objects_Point ( )
{

    using namespace boost::python ;

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector2d ;
    using ostk::math::geom::d2::Object ;
    using ostk::math::geom::d2::objects::Point ;

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

        .def("x", &Point::x, return_value_policy<reference_existing_object>())
        .def("y", &Point::y, return_value_policy<reference_existing_object>())
        .def("asVector", &Point::asVector)
        .def("distanceTo", &Point::distanceTo)
        .def("toString", &Point::toString, LibraryMathematicsPy_Geometry_2D_Objects_Point_toString_overloads())
        .def("applyTransformation", &Point::applyTransformation)

        .def("Undefined", &Point::Undefined).staticmethod("Undefined")
        .def("Origin", &Point::Origin).staticmethod("Origin")
        .def("Vector", &Point::Vector).staticmethod("Vector")

    ;

    // implicitly_convertible<Point, Vector2d>() ;
    // implicitly_convertible<Vector2d, Point>() ;

    using ostk::core::ctnr::Array ;

    IterableConverter()

        .from_python<Array<Point>>()
        .to_python<Array<Point>>()

        .from_python<Array<Array<Point>>>()
        .to_python<Array<Array<Point>>>()

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
