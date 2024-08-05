/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ray.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Ray(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::mathematics::geometry::d3::Intersection;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Ellipsoid;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Sphere;
    using ostk::mathematics::object::Vector3d;

    class_<Ray, Object>(aModule, "Ray")

        .def(init<const Point&, const Vector3d&>(), arg("origin"), arg("direction"))

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Ray>))
        .def("__repr__", &(shiftToString<Ray>))

        .def("is_defined", &Ray::isDefined)
        .def("intersects", overload_cast<const Point&>(&Ray::intersects, const_), arg("point"))
        .def("intersects", overload_cast<const Plane&>(&Ray::intersects, const_), arg("plane"))
        .def("intersects", overload_cast<const Sphere&>(&Ray::intersects, const_), arg("sphere"))
        .def("intersects", overload_cast<const Ellipsoid&>(&Ray::intersects, const_), arg("ellipsoid"))
        .def("contains", overload_cast<const Point&>(&Ray::contains, const_), arg("point"))
        .def("contains", overload_cast<const PointSet&>(&Ray::contains, const_), arg("point_set"))

        .def("get_origin", &Ray::getOrigin)
        .def("get_direction", &Ray::getDirection)
        .def("distance_to", overload_cast<const Point&>(&Ray::distanceTo, const_), arg("point"))
        .def("intersection_with", overload_cast<const Plane&>(&Ray::intersectionWith, const_), arg("plane"))
        .def(
            "intersection_with",
            overload_cast<const Sphere&, const bool>(&Ray::intersectionWith, const_),
            arg("sphere"),
            arg("only_in_sight") = DEFAULT_ONLY_IN_SIGHT
        )
        .def(
            "intersection_with",
            overload_cast<const Ellipsoid&, const bool>(&Ray::intersectionWith, const_),
            arg("ellipsoid"),
            arg("only_in_sight") = DEFAULT_ONLY_IN_SIGHT
        )
        .def("apply_transformation", &Ray::applyTransformation, arg("transformation"))

        .def_static("undefined", &Ray::Undefined)

        ;
}
