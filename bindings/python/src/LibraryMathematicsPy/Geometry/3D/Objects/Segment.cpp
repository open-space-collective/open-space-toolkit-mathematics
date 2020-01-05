////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           LibraryMathematicsPy/Geometry/3D/Objects/Segment.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Segment.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_3D_Objects_Segment ( )
{

    using namespace boost::python ;

    using ostk::math::geom::d3::Object ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Segment ;
    using ostk::math::geom::d3::objects::Plane ;
    using ostk::math::geom::d3::objects::Sphere ;
    using ostk::math::geom::d3::objects::Ellipsoid ;
    using ostk::math::geom::d3::Intersection ;

    scope in_Segment = class_<Segment, bases<Object>>("Segment", init<const Point&, const Point&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &Segment::isDefined)
        .def("isDegenerate", &Segment::isDegenerate)
        .def("intersectsPlane", +[] (const Segment& aSegment, const Plane& aPlane) -> bool { return aSegment.intersects(aPlane) ; })
        .def("intersectsSphere", +[] (const Segment& aSegment, const Sphere& aSphere) -> bool { return aSegment.intersects(aSphere) ; })
        .def("intersectsEllipsoid", +[] (const Segment& aSegment, const Ellipsoid& anEllipsoid) -> bool { return aSegment.intersects(anEllipsoid) ; })
        .def("containsPoint", +[] (const Segment& aSegment, const Point& aPoint) -> bool { return aSegment.contains(aPoint) ; })

        .def("getFirstPoint", &Segment::getFirstPoint)
        .def("getSecondPoint", &Segment::getSecondPoint)
        .def("getCenter", &Segment::getCenter)
        .def("getDirection", &Segment::getDirection)
        .def("getLength", &Segment::getLength)
        .def("intersectionWithPlane", +[] (const Segment& aSegment, const Plane& aPlane) -> Intersection { return aSegment.intersectionWith(aPlane) ; })
        .def("applyTransformation", &Segment::applyTransformation)

        .def("Undefined", &Segment::Undefined).staticmethod("Undefined")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
