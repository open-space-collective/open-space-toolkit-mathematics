////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Plane.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Plane.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Plane ( )
{

    using namespace boost::python ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::Object ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::PointSet ;
    using ostk::math::geom::d3::objects::Plane ;
    using ostk::math::geom::d3::objects::Line ;
    using ostk::math::geom::d3::objects::Ray ;
    using ostk::math::geom::d3::objects::Segment ;
    using ostk::math::geom::d3::Intersection ;

    scope in_Plane = class_<Plane, bases<Object>>("Plane", init<const Point&, const Vector3d&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("is_defined", &Plane::isDefined)
        .def("intersects_point", +[] (const Plane& aPlane, const Point& aPoint) -> bool { return aPlane.intersects(aPoint) ; })
        .def("intersects_point_set", +[] (const Plane& aPlane, const PointSet& aPointSet) -> bool { return aPlane.intersects(aPointSet) ; })
        .def("intersects_line", +[] (const Plane& aPlane, const Line& aLine) -> bool { return aPlane.intersects(aLine) ; })
        .def("intersects_ray", +[] (const Plane& aPlane, const Ray& aRay) -> bool { return aPlane.intersects(aRay) ; })
        .def("intersects_segment", +[] (const Plane& aPlane, const Segment& aSegment) -> bool { return aPlane.intersects(aSegment) ; })
        .def("contains_point", +[] (const Plane& aPlane, const Point& aPoint) -> bool { return aPlane.contains(aPoint) ; })
        .def("contains_point_set", +[] (const Plane& aPlane, const PointSet& aPointSet) -> bool { return aPlane.contains(aPointSet) ; })
        .def("contains_line", +[] (const Plane& aPlane, const Line& aLine) -> bool { return aPlane.contains(aLine) ; })
        .def("contains_ray", +[] (const Plane& aPlane, const Ray& aRay) -> bool { return aPlane.contains(aRay) ; })
        .def("contains_segment", +[] (const Plane& aPlane, const Segment& aSegment) -> bool { return aPlane.contains(aSegment) ; })

        .def("get_point", &Plane::getPoint)
        .def("get_normal_vector", &Plane::getNormalVector)
        .def("intersection_with_point", +[] (const Plane& aPlane, const Point& aPoint) -> Intersection { return aPlane.intersectionWith(aPoint) ; })
        .def("intersection_with_point_set", +[] (const Plane& aPlane, const PointSet& aPointSet) -> Intersection { return aPlane.intersectionWith(aPointSet) ; })
        .def("intersection_with_line", +[] (const Plane& aPlane, const Line& aLine) -> Intersection { return aPlane.intersectionWith(aLine) ; })
        .def("intersection_with_ray", +[] (const Plane& aPlane, const Ray& aRay) -> Intersection { return aPlane.intersectionWith(aRay) ; })
        .def("intersection_with_segment", +[] (const Plane& aPlane, const Segment& aSegment) -> Intersection { return aPlane.intersectionWith(aSegment) ; })
        .def("apply_transformation", &Plane::applyTransformation)

        .def("undefined", &Plane::Undefined).staticmethod("undefined")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
