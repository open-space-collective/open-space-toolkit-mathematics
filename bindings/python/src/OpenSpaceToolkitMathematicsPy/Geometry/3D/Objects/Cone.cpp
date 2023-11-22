/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Cone.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Cone(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::types::Size;
    using ostk::core::types::Real;

    using ostk::math::object::Vector3d;
    using ostk::math::geometry::Angle;
    using ostk::math::geometry::d3::Object;
    using ostk::math::geometry::d3::objects::Point;
    using ostk::math::geometry::d3::objects::PointSet;
    using ostk::math::geometry::d3::objects::Line;
    using ostk::math::geometry::d3::objects::Ray;
    using ostk::math::geometry::d3::objects::Segment;
    using ostk::math::geometry::d3::objects::Ray;
    using ostk::math::geometry::d3::objects::Plane;
    using ostk::math::geometry::d3::objects::Polygon;
    using ostk::math::geometry::d3::objects::Sphere;
    using ostk::math::geometry::d3::objects::Ellipsoid;
    using ostk::math::geometry::d3::objects::Cone;
    using ostk::math::geometry::d3::Intersection;

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
