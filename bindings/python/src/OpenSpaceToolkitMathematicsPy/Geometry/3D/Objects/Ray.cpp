////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Ray.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Ray.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Ray ( pybind11::module&           aModule                                     )
{

    using namespace pybind11 ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::Object ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::PointSet ;
    using ostk::math::geom::d3::objects::Ray ;
    using ostk::math::geom::d3::objects::Plane ;
    using ostk::math::geom::d3::objects::Sphere ;
    using ostk::math::geom::d3::objects::Ellipsoid ;
    using ostk::math::geom::d3::Intersection ;

    class_<Ray, Object>(aModule, "Ray")

        .def(init<const Point&, const Vector3d&>())

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Ray>))
        .def("__repr__", &(shiftToString<Ray>))

        .def("is_defined", &Ray::isDefined)
        .def("intersects", overload_cast<const Point&>(&Ray::intersects, const_))
        .def("intersects", overload_cast<const Plane&>(&Ray::intersects, const_))
        .def("intersects", overload_cast<const Sphere&>(&Ray::intersects, const_))
        .def("intersects", overload_cast<const Ellipsoid&>(&Ray::intersects, const_))
        .def("intersects_point", +[] (const Ray& aRay, const Point& aPoint) -> bool { return aRay.intersects(aPoint) ; }) // TBR
        .def("intersects_plane", +[] (const Ray& aRay, const Plane& aPlane) -> bool { return aRay.intersects(aPlane) ; }) // TBR
        .def("intersects_sphere", +[] (const Ray& aRay, const Sphere& aSphere) -> bool { return aRay.intersects(aSphere) ; }) // TBR
        .def("intersects_ellipsoid", +[] (const Ray& aRay, const Ellipsoid& anEllipsoid) -> bool { return aRay.intersects(anEllipsoid) ; }) // TBR
        .def("contains", overload_cast<const Point&>(&Ray::contains, const_))
        .def("contains", overload_cast<const PointSet&>(&Ray::contains, const_))
        .def("contains_point", +[] (const Ray& aRay, const Point& aPoint) -> bool { return aRay.contains(aPoint) ; }) // TBR
        .def("contains_point_set", +[] (const Ray& aRay, const PointSet& aPointSet) -> bool { return aRay.contains(aPointSet) ; }) // TBR

        .def("get_origin", &Ray::getOrigin)
        .def("get_direction", &Ray::getDirection)
        .def("intersection_with", overload_cast<const Plane&>(&Ray::intersectionWith, const_))
        .def("intersection_with", overload_cast<const Sphere&, const bool>(&Ray::intersectionWith, const_), arg("sphere"), arg("only_in_sight") = false)
        .def("intersection_with", overload_cast<const Ellipsoid&, const bool>(&Ray::intersectionWith, const_), arg("ellipsoid"), arg("only_in_sight") = false)
        .def("intersection_with_plane", +[] (const Ray& aRay, const Plane& aPlane) -> Intersection { return aRay.intersectionWith(aPlane) ; }) // TBR
        .def("intersection_with_ellipsoid", +[] (const Ray& aRay, const Ellipsoid& anEllipsoid) -> Intersection { return aRay.intersectionWith(anEllipsoid) ; }) // TBR
        .def("apply_transformation", &Ray::applyTransformation)

        .def_static("undefined", &Ray::Undefined)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
