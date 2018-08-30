////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           LibraryMathematicsPy/Geometry/3D/Objects/Point.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <LibraryMathematicsPy/Utilities/IterableConverter.hpp>

#include <Library/Mathematics/Geometry/3D/Objects/Point.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_3D_Objects_Point ( )
{

    using namespace boost::python ;

    using library::core::types::Real ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;

    scope in_Point = class_<Point, bases<Object>>("Point", init<const Real&, const Real&, const Real&>())

        .def(init<const Vector3d&>())

        .def(self == self)
        .def(self != self)

        .def(self + other<Vector3d>())
        .def(self - other<Vector3d>())

        .def(self - self)

        .def(self_ns::str(self_ns::self))

        .def("__repr__", +[] (const Point& aPoint) -> std::string { return aPoint.toString() ; })
        
        .def("isDefined", &Point::isDefined)
        .def("isNear", &Point::isNear)
        
        .def("distanceTo", &Point::distanceTo)

        .def("translate", &Point::translate)
        .def("rotate", &Point::rotate)

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