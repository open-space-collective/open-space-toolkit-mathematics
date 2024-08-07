/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Cone.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Cone(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;
    using ostk::core::type::Size;

    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::Intersection;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Ellipsoid;
    using ostk::mathematics::geometry::d3::object::Line;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::geometry::d3::object::Sphere;
    using ostk::mathematics::object::Vector3d;

    class_<Cone, Object>(aModule, "Cone")

        .def(init<const Point&, const Vector3d&, const Angle&>(), arg("apex"), arg("axis"), arg("angle"))

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Cone>))
        .def("__repr__", &(shiftToString<Cone>))

        .def("is_defined", &Cone::isDefined)
        .def(
            "intersects",
            overload_cast<const Sphere&, const Size>(&Cone::intersects, const_),
            arg("sphere"),
            arg("discretization_level") = DEFAULT_DISCRETIZATION_LEVEL
        )
        .def(
            "intersects",
            overload_cast<const Ellipsoid&, const Size>(&Cone::intersects, const_),
            arg("ellipsoid"),
            arg("discretization_level") = DEFAULT_DISCRETIZATION_LEVEL
        )
        .def("contains", overload_cast<const Point&>(&Cone::contains, const_), arg("point"))
        .def("contains", overload_cast<const PointSet&>(&Cone::contains, const_), arg("point_set"))
        .def("contains", overload_cast<const Segment&>(&Cone::contains, const_), arg("segment"))
        .def("contains", overload_cast<const Ray&>(&Cone::contains, const_), arg("ray"))
        .def("contains", overload_cast<const Sphere&>(&Cone::contains, const_), arg("sphere"))
        .def("contains", overload_cast<const Ellipsoid&>(&Cone::contains, const_), arg("ellipsoid"))

        .def("get_apex", &Cone::getApex)
        .def("get_axis", &Cone::getAxis)
        .def("get_angle", &Cone::getAngle)
        .def("get_rays_of_lateral_surface", &Cone::getRaysOfLateralSurface, arg("ray_count") = DEFAULT_RAY_COUNT)
        .def("distance_to", overload_cast<const Point&>(&Cone::distanceTo, const_), arg("point"))
        .def(
            "intersection_with",
            overload_cast<const Sphere&, const bool, const Size>(&Cone::intersectionWith, const_),
            arg("sphere"),
            arg("only_in_sight") = false,
            arg("discretization_level") = DEFAULT_DISCRETIZATION_LEVEL
        )
        .def(
            "intersection_with",
            overload_cast<const Ellipsoid&, const bool, const Size>(&Cone::intersectionWith, const_),
            arg("ellipsoid"),
            arg("only_in_sight") = false,
            arg("discretization_level") = DEFAULT_DISCRETIZATION_LEVEL
        )
        .def("apply_transformation", &Cone::applyTransformation, arg("transformation"))

        .def_static("undefined", &Cone::Undefined);
}
