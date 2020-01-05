////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Sphere.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Sphere.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Sphere ( )
{

    using namespace boost::python ;

    using ostk::core::types::Real ;

    using ostk::math::geom::d3::Object ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::PointSet ;
    using ostk::math::geom::d3::objects::Line ;
    using ostk::math::geom::d3::objects::Ray ;
    using ostk::math::geom::d3::objects::Segment ;
    using ostk::math::geom::d3::objects::Plane ;
    using ostk::math::geom::d3::objects::Sphere ;
    using ostk::math::geom::d3::objects::Ellipsoid ;
    using ostk::math::geom::d3::objects::Pyramid ;
    using ostk::math::geom::d3::Intersection ;

    scope in_Sphere = class_<Sphere, bases<Object>>("Sphere", init<const Point&, const Real&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &Sphere::isDefined)
        .def("isUnitary", &Sphere::isUnitary)

        .def("intersectsPoint", +[] (const Sphere& aSphere, const Point& aPoint) -> bool { return aSphere.intersects(aPoint) ; })
        .def("intersectsPointSet", +[] (const Sphere& aSphere, const PointSet& aPointSet) -> bool { return aSphere.intersects(aPointSet) ; })
        .def("intersectsLine", +[] (const Sphere& aSphere, const Line& aLine) -> bool { return aSphere.intersects(aLine) ; })
        .def("intersectsRay", +[] (const Sphere& aSphere, const Ray& aRay) -> bool { return aSphere.intersects(aRay) ; })
        .def("intersectsSegment", +[] (const Sphere& aSphere, const Segment& aSegment) -> bool { return aSphere.intersects(aSegment) ; })
        .def("intersectsPlane", +[] (const Sphere& aSphere, const Plane& aPlane) -> bool { return aSphere.intersects(aPlane) ; })
        .def("containsPoint", +[] (const Sphere& aSphere, const Point& aPoint) -> bool { return aSphere.contains(aPoint) ; })
        .def("containsPointSet", +[] (const Sphere& aSphere, const PointSet& aPointSet) -> bool { return aSphere.contains(aPointSet) ; })

        .def("getCenter", &Sphere::getCenter)
        .def("getRadius", &Sphere::getRadius)
        .def("intersectionWithLine", +[] (const Sphere& aSphere, const Line& aLine) -> Intersection { return aSphere.intersectionWith(aLine) ; })
        .def("intersectionWithRay", +[] (const Sphere& aSphere, const Ray& aRay) -> Intersection { return aSphere.intersectionWith(aRay) ; })
        .def("intersectionWithRay", +[] (const Sphere& aSphere, const Ray& aRay, const bool onlyInSight) -> Intersection { return aSphere.intersectionWith(aRay, onlyInSight) ; })
        .def("applyTransformation", &Sphere::applyTransformation)

        .def("Undefined", &Sphere::Undefined).staticmethod("Undefined")
        .def("Unit", &Sphere::Unit).staticmethod("Unit")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
