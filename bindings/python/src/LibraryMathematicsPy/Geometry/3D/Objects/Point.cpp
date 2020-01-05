////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Point.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkitMathematicsPy/Utilities/IterableConverter.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Point.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Point ( )
{

    using namespace boost::python ;

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::Object ;
    using ostk::math::geom::d3::objects::Point ;

    scope in_Point = class_<Point, bases<Object>>("Point", init<const Real&, const Real&, const Real&>())

        .def(self == self)
        .def(self != self)

        .def(self + other<Vector3d>())
        .def(self - other<Vector3d>())

        .def(self - self)

        .def(self_ns::str(self_ns::self))

        .def("__repr__", +[] (const Point& aPoint) -> std::string { return aPoint.toString() ; })

        .def("isDefined", &Point::isDefined)
        .def("isNear", &Point::isNear)

        .def("x", &Point::x, return_value_policy<reference_existing_object>())
        .def("y", &Point::y, return_value_policy<reference_existing_object>())
        .def("z", &Point::z, return_value_policy<reference_existing_object>())
        .def("asVector", &Point::asVector)
        .def("distanceTo", &Point::distanceTo)
        .def("applyTransformation", &Point::applyTransformation)

        .def("Undefined", &Point::Undefined).staticmethod("Undefined")
        .def("Origin", &Point::Origin).staticmethod("Origin")
        .def("Vector", &Point::Vector).staticmethod("Vector")

    ;

    // implicitly_convertible<Point, Vector3d>() ;
    // implicitly_convertible<Vector3d, Point>() ;

    using ostk::core::ctnr::Array ;

    IterableConverter()

        .from_python<Array<Point>>()
        .to_python<Array<Point>>()

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
