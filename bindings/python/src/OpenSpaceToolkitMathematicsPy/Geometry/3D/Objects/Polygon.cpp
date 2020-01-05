////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Polygon.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Polygon.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Polygon ( )
{

    using namespace boost::python ;

    using ostk::math::obj::Vector3d ;
    using Polygon2d = ostk::math::geom::d2::objects::Polygon ;
    using ostk::math::geom::d3::Object ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Polygon ;

    scope in_Polygon = class_<Polygon, bases<Object>>("Polygon", init<const Polygon2d&, const Point&, const Vector3d&, const Vector3d&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("is_defined", &Polygon::isDefined)
        .def("is_near", &Polygon::isNear)

        .def("get_polygon2d", &Polygon::getPolygon2d)
        .def("get_origin", &Polygon::getOrigin)
        .def("get_x_axis", &Polygon::getXAxis)
        .def("get_y_axis", &Polygon::getYAxis)
        .def("get_normal_vector", &Polygon::getNormalVector)
        .def("apply_transformation", &Polygon::applyTransformation)

        .def("undefined", &Polygon::Undefined).staticmethod("undefined")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
