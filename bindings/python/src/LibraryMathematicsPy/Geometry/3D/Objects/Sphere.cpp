////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Mathematics
/// @file           LibraryMathematicsPy/Geometry/3D/Objects/Sphere.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Objects/Sphere.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_3D_Objects_Sphere ( )
{

    using namespace boost::python ;

    using library::core::types::Real ;

    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::PointSet ;
    using library::math::geom::d3::objects::Line ;
    using library::math::geom::d3::objects::Ray ;
    using library::math::geom::d3::objects::Segment ;
    using library::math::geom::d3::objects::Plane ;
    using library::math::geom::d3::objects::Sphere ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::Intersection ;

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
