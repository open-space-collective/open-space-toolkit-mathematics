////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           LibraryMathematicsPy/Geometry/3D/Objects/Polygon.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Objects/Polygon.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_3D_Objects_Polygon ( )
{

    using namespace boost::python ;

    using library::math::obj::Vector3d ;
    using Polygon2d = library::math::geom::d2::objects::Polygon ;
    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;

    scope in_Polygon = class_<Polygon, bases<Object>>("Polygon", init<const Polygon2d&, const Point&, const Vector3d&, const Vector3d&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))
        
        .def("isDefined", &Polygon::isDefined)
        .def("isNear", &Polygon::isNear)

        .def("getPolygon2d", &Polygon::getPolygon2d)
        .def("getOrigin", &Polygon::getOrigin)
        .def("getXAxis", &Polygon::getXAxis)
        .def("getYAxis", &Polygon::getYAxis)
        .def("getNormalVector", &Polygon::getNormalVector)
        .def("applyTransformation", &Polygon::applyTransformation)
        
        .def("Undefined", &Polygon::Undefined).staticmethod("Undefined")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////