////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Line.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Line.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Line ( )
{

    using namespace boost::python ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::Object ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Line ;
    using ostk::math::geom::d3::objects::Plane ;
    using ostk::math::geom::d3::objects::Sphere ;
    using ostk::math::geom::d3::objects::Ellipsoid ;
    using ostk::math::geom::d3::Intersection ;

    scope in_Line = class_<Line, bases<Object>>("Line", init<const Point&, const Vector3d&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("is_defined", &Line::isDefined)
        .def("intersects_point", +[] (const Line& aLine, const Point& aPoint) -> bool { return aLine.intersects(aPoint) ; })
        .def("intersects_plane", +[] (const Line& aLine, const Plane& aPlane) -> bool { return aLine.intersects(aPlane) ; })
        .def("intersects_sphere", +[] (const Line& aLine, const Sphere& aSphere) -> bool { return aLine.intersects(aSphere) ; })
        .def("intersects_ellipsoid", +[] (const Line& aLine, const Ellipsoid& anEllipsoid) -> bool { return aLine.intersects(anEllipsoid) ; })
        .def("contains_point", +[] (const Line& aLine, const Point& aPoint) -> bool { return aLine.contains(aPoint) ; })

        .def("get_origin", &Line::getOrigin)
        .def("get_direction", &Line::getDirection)
        .def("intersection_with_plane", +[] (const Line& aLine, const Plane& aPlane) -> Intersection { return aLine.intersectionWith(aPlane) ; })
        .def("apply_transformation", &Line::applyTransformation)

        .def("undefined", &Line::Undefined).staticmethod("undefined")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
