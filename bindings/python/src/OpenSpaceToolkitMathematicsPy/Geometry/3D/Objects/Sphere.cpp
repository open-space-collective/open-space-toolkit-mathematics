// Copyright © Loft Orbital Solutions Inc.

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Sphere.hpp>


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

        .def(init<const Point&, const Real&>(), arg("center"), arg("radius"))

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Sphere>))
        .def("__repr__", &(shiftToString<Sphere>))

        .def("is_defined", &Sphere::isDefined)
        .def("is_unitary", &Sphere::isUnitary)

        .def("intersects", overload_cast<const Point&>(&Sphere::intersects, const_), arg("point"))
        .def("intersects", overload_cast<const PointSet&>(&Sphere::intersects, const_), arg("point_set"))
        .def("intersects", overload_cast<const Line&>(&Sphere::intersects, const_), arg("line"))
        .def("intersects", overload_cast<const Ray&>(&Sphere::intersects, const_), arg("ray"))
        .def("intersects", overload_cast<const Segment&>(&Sphere::intersects, const_), arg("segment"))
        .def("intersects", overload_cast<const Plane&>(&Sphere::intersects, const_), arg("plane"))
        .def("contains", overload_cast<const Point&>(&Sphere::contains, const_), arg("point"))
        .def("contains", overload_cast<const PointSet&>(&Sphere::contains, const_), arg("point_set"))

        .def("get_center", &Sphere::getCenter)
        .def("get_radius", &Sphere::getRadius)

        .def("intersection_with", overload_cast<const Line&>(&Sphere::intersectionWith, const_), arg("line"))
        .def("intersection_with", overload_cast<const Ray&, const bool>(&Sphere::intersectionWith, const_), arg("ray"), arg("only_in_sight") = DEFAULT_ONLY_IN_SIGHT)
        .def("apply_transformation", &Sphere::applyTransformation, arg("transformation"))

        .def_static("undefined", &Sphere::Undefined)
        .def_static("unit", &Sphere::Unit, arg("center"))

    ;

}

