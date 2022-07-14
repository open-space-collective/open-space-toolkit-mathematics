////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Sphere.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Sphere.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Sphere ( pybind11::module&        aModule                                     )
{

    using namespace pybind11 ;

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

    class_<Sphere, Object>(aModule, "Sphere")

        .def(init<const Point&, const Real&>())

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Sphere>))
        .def("__repr__", &(shiftToString<Sphere>))

        .def("is_defined", &Sphere::isDefined)
        .def("is_unitary", &Sphere::isUnitary)

        .def("intersects", overload_cast<const Point&>(&Sphere::intersects, const_))
        .def("intersects", overload_cast<const PointSet&>(&Sphere::intersects, const_))
        .def("intersects", overload_cast<const Line&>(&Sphere::intersects, const_))
        .def("intersects", overload_cast<const Ray&>(&Sphere::intersects, const_))
        .def("intersects", overload_cast<const Segment&>(&Sphere::intersects, const_))
        .def("intersects", overload_cast<const Plane&>(&Sphere::intersects, const_))
        .def("intersects_point", +[] (const Sphere& aSphere, const Point& aPoint) -> bool { return aSphere.intersects(aPoint) ; }) // TBR
        .def("intersects_point_set", +[] (const Sphere& aSphere, const PointSet& aPointSet) -> bool { return aSphere.intersects(aPointSet) ; }) // TBR
        .def("intersects_line", +[] (const Sphere& aSphere, const Line& aLine) -> bool { return aSphere.intersects(aLine) ; }) // TBR
        .def("intersects_ray", +[] (const Sphere& aSphere, const Ray& aRay) -> bool { return aSphere.intersects(aRay) ; }) // TBR
        .def("intersects_segment", +[] (const Sphere& aSphere, const Segment& aSegment) -> bool { return aSphere.intersects(aSegment) ; }) // TBR
        .def("intersects_plane", +[] (const Sphere& aSphere, const Plane& aPlane) -> bool { return aSphere.intersects(aPlane) ; }) // TBR
        .def("contains", overload_cast<const Point&>(&Sphere::contains, const_))
        .def("contains", overload_cast<const PointSet&>(&Sphere::contains, const_))
        .def("contains_point", +[] (const Sphere& aSphere, const Point& aPoint) -> bool { return aSphere.contains(aPoint) ; }) // TBR
        .def("contains_point_set", +[] (const Sphere& aSphere, const PointSet& aPointSet) -> bool { return aSphere.contains(aPointSet) ; }) // TBR

        .def("get_center", &Sphere::getCenter)
        .def("get_radius", &Sphere::getRadius)

        .def("intersection_with", overload_cast<const Line&>(&Sphere::intersectionWith, const_))
        .def("intersection_with", overload_cast<const Ray&, const bool>(&Sphere::intersectionWith, const_), arg("ray"), arg("only_in_sight") = false)
        .def("intersection_with_line", +[] (const Sphere& aSphere, const Line& aLine) -> Intersection { return aSphere.intersectionWith(aLine) ; }) // TBR
        .def("intersection_with_ray", +[] (const Sphere& aSphere, const Ray& aRay) -> Intersection { return aSphere.intersectionWith(aRay) ; }) // TBR
        .def("intersection_with_ray", +[] (const Sphere& aSphere, const Ray& aRay, const bool onlyInSight) -> Intersection { return aSphere.intersectionWith(aRay, onlyInSight) ; }) // TBR
        .def("apply_transformation", &Sphere::applyTransformation)

        .def_static("undefined", &Sphere::Undefined)
        .def_static("unit", &Sphere::Unit)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
