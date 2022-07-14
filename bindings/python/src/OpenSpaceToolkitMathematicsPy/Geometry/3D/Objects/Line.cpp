////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Line.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Line.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Line (         pybind11::module&  aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::Object ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::PointSet ;
    using ostk::math::geom::d3::objects::Line ;
    using ostk::math::geom::d3::objects::Plane ;
    using ostk::math::geom::d3::objects::Sphere ;
    using ostk::math::geom::d3::objects::Ellipsoid ;
    using ostk::math::geom::d3::Intersection ;

    class_<Line, Object>(aModule, "Line")

        .def(init<const Point&, const Vector3d&>())

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Line>))
        .def("__repr__", &(shiftToString<Line>))

        .def("is_defined", &Line::isDefined)
        .def("intersects", overload_cast<const Point&>(&Line::intersects, const_))
        .def("intersects", overload_cast<const Plane&>(&Line::intersects, const_))
        .def("intersects", overload_cast<const Sphere&>(&Line::intersects, const_))
        .def("intersects", overload_cast<const Ellipsoid&>(&Line::intersects, const_))
        .def("intersects_point", +[] (const Line& aLine, const Point& aPoint) -> bool { return aLine.intersects(aPoint) ; }) // TBR
        .def("intersects_plane", +[] (const Line& aLine, const Plane& aPlane) -> bool { return aLine.intersects(aPlane) ; }) // TBR
        .def("intersects_sphere", +[] (const Line& aLine, const Sphere& aSphere) -> bool { return aLine.intersects(aSphere) ; }) // TBR
        .def("intersects_ellipsoid", +[] (const Line& aLine, const Ellipsoid& anEllipsoid) -> bool { return aLine.intersects(anEllipsoid) ; }) // TBR
        .def("contains", overload_cast<const Point&>(&Line::contains, const_))
        .def("contains", overload_cast<const PointSet&>(&Line::contains, const_))
        .def("contains_point", +[] (const Line& aLine, const Point& aPoint) -> bool { return aLine.contains(aPoint) ; }) // TBR
        .def("contains_point_set", +[] (const Line& aLine, const PointSet& aPointSet) -> bool { return aLine.contains(aPointSet) ; }) // TBR

        .def("get_origin", &Line::getOrigin)
        .def("get_direction", &Line::getDirection)
        .def("distance_to", overload_cast<const Point&>(&Line::distanceTo, const_))
        .def("intersection_with", overload_cast<const Plane&>(&Line::intersectionWith, const_))
        .def("intersection_with_plane", +[] (const Line& aLine, const Plane& aPlane) -> Intersection { return aLine.intersectionWith(aPlane) ; }) // TBR
        .def("apply_transformation", &Line::applyTransformation)

        .def_static("undefined", &Line::Undefined)
        .def_static("points", &Line::Points)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
