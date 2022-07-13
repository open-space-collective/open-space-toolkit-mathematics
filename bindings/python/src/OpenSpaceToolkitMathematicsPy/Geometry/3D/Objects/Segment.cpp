////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Segment.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Segment.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Segment ( pybind11::module&       aModule                                     )
{

    using namespace pybind11;

    using ostk::math::geom::d3::Object ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Segment ;
    using ostk::math::geom::d3::objects::Plane ;
    using ostk::math::geom::d3::objects::Sphere ;
    using ostk::math::geom::d3::objects::Ellipsoid ;
    using ostk::math::geom::d3::Intersection ;

    class_<Segment, Object>(aModule, "Segment")

        .def(init<const Point&, const Point&>())

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Segment>))
        .def("__repr__", &(shiftToString<Segment>))

        .def("is_defined", &Segment::isDefined)
        .def("is_degenerate", &Segment::isDegenerate)
        .def("intersects_plane", +[] (const Segment& aSegment, const Plane& aPlane) -> bool { return aSegment.intersects(aPlane) ; })
        .def("intersects_sphere", +[] (const Segment& aSegment, const Sphere& aSphere) -> bool { return aSegment.intersects(aSphere) ; })
        .def("intersects_ellipsoid", +[] (const Segment& aSegment, const Ellipsoid& anEllipsoid) -> bool { return aSegment.intersects(anEllipsoid) ; })
        .def("contains_point", +[] (const Segment& aSegment, const Point& aPoint) -> bool { return aSegment.contains(aPoint) ; })

        .def("get_first_point", &Segment::getFirstPoint)
        .def("get_second_point", &Segment::getSecondPoint)
        .def("get_center", &Segment::getCenter)
        .def("get_direction", &Segment::getDirection)
        .def("get_length", &Segment::getLength)
        .def("intersection_with_plane", +[] (const Segment& aSegment, const Plane& aPlane) -> Intersection { return aSegment.intersectionWith(aPlane) ; })
        .def("to_line", &Segment::toLine)
        .def("apply_transformation", &Segment::applyTransformation)

        .def_static("undefined", &Segment::Undefined)
    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
