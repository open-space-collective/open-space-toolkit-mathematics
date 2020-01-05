////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Ray.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Ray.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Ray ( )
{

    using namespace boost::python ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::Object ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::PointSet ;
    using ostk::math::geom::d3::objects::Ray ;
    using ostk::math::geom::d3::objects::Plane ;
    using ostk::math::geom::d3::objects::Sphere ;
    using ostk::math::geom::d3::objects::Ellipsoid ;
    using ostk::math::geom::d3::Intersection ;

    scope in_Ray = class_<Ray, bases<Object>>("Ray", init<const Point&, const Vector3d&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("is_defined", &Ray::isDefined)
        .def("intersects_point", +[] (const Ray& aRay, const Point& aPoint) -> bool { return aRay.intersects(aPoint) ; })
        .def("intersects_plane", +[] (const Ray& aRay, const Plane& aPlane) -> bool { return aRay.intersects(aPlane) ; })
        .def("intersects_sphere", +[] (const Ray& aRay, const Sphere& aSphere) -> bool { return aRay.intersects(aSphere) ; })
        .def("intersects_ellipsoid", +[] (const Ray& aRay, const Ellipsoid& anEllipsoid) -> bool { return aRay.intersects(anEllipsoid) ; })
        .def("contains_point", +[] (const Ray& aRay, const Point& aPoint) -> bool { return aRay.contains(aPoint) ; })
        .def("contains_point_set", +[] (const Ray& aRay, const PointSet& aPointSet) -> bool { return aRay.contains(aPointSet) ; })

        .def("get_origin", &Ray::getOrigin)
        .def("get_direction", &Ray::getDirection)
        .def("intersection_with_plane", +[] (const Ray& aRay, const Plane& aPlane) -> Intersection { return aRay.intersectionWith(aPlane) ; })
        .def("intersection_with_ellipsoid", +[] (const Ray& aRay, const Ellipsoid& anEllipsoid) -> Intersection { return aRay.intersectionWith(anEllipsoid) ; })
        .def("apply_transformation", &Ray::applyTransformation)

        .def("undefined", &Ray::Undefined).staticmethod("undefined")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
