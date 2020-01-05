////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           LibraryMathematicsPy/Geometry/3D/Objects/Plane.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Plane.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_3D_Objects_Plane ( )
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

        .def("isDefined", &Plane::isDefined)
        .def("intersectsPoint", +[] (const Plane& aPlane, const Point& aPoint) -> bool { return aPlane.intersects(aPoint) ; })
        .def("intersectsPointSet", +[] (const Plane& aPlane, const PointSet& aPointSet) -> bool { return aPlane.intersects(aPointSet) ; })
        .def("intersectsLine", +[] (const Plane& aPlane, const Line& aLine) -> bool { return aPlane.intersects(aLine) ; })
        .def("intersectsRay", +[] (const Plane& aPlane, const Ray& aRay) -> bool { return aPlane.intersects(aRay) ; })
        .def("intersectsSegment", +[] (const Plane& aPlane, const Segment& aSegment) -> bool { return aPlane.intersects(aSegment) ; })
        .def("containsPoint", +[] (const Plane& aPlane, const Point& aPoint) -> bool { return aPlane.contains(aPoint) ; })
        .def("containsPointSet", +[] (const Plane& aPlane, const PointSet& aPointSet) -> bool { return aPlane.contains(aPointSet) ; })
        .def("containsLine", +[] (const Plane& aPlane, const Line& aLine) -> bool { return aPlane.contains(aLine) ; })
        .def("containsRay", +[] (const Plane& aPlane, const Ray& aRay) -> bool { return aPlane.contains(aRay) ; })
        .def("containsSegment", +[] (const Plane& aPlane, const Segment& aSegment) -> bool { return aPlane.contains(aSegment) ; })

        .def("getPoint", &Plane::getPoint)
        .def("getNormalVector", &Plane::getNormalVector)
        .def("intersectionWithPoint", +[] (const Plane& aPlane, const Point& aPoint) -> Intersection { return aPlane.intersectionWith(aPoint) ; })
        .def("intersectionWithPointSet", +[] (const Plane& aPlane, const PointSet& aPointSet) -> Intersection { return aPlane.intersectionWith(aPointSet) ; })
        .def("intersectionWithLine", +[] (const Plane& aPlane, const Line& aLine) -> Intersection { return aPlane.intersectionWith(aLine) ; })
        .def("intersectionWithRay", +[] (const Plane& aPlane, const Ray& aRay) -> Intersection { return aPlane.intersectionWith(aRay) ; })
        .def("intersectionWithSegment", +[] (const Plane& aPlane, const Segment& aSegment) -> Intersection { return aPlane.intersectionWith(aSegment) ; })
        .def("applyTransformation", &Plane::applyTransformation)

        .def("Undefined", &Plane::Undefined).staticmethod("Undefined")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
