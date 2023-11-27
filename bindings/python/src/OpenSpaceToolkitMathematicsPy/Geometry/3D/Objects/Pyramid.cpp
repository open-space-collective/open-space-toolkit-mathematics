/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Pyramid.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Pyramid(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::types::Size;
    using ostk::core::types::Real;

    using ostk::math::geometry::d3::Object;
    using ostk::math::geometry::d3::objects::Point;
    using ostk::math::geometry::d3::objects::PointSet;
    using ostk::math::geometry::d3::objects::Segment;
    using ostk::math::geometry::d3::objects::Line;
    using ostk::math::geometry::d3::objects::Ray;
    using ostk::math::geometry::d3::objects::Segment;
    using ostk::math::geometry::d3::objects::Plane;
    using ostk::math::geometry::d3::objects::Polygon;
    using ostk::math::geometry::d3::objects::Sphere;
    using ostk::math::geometry::d3::objects::Ellipsoid;
    using ostk::math::geometry::d3::objects::Pyramid;
    using ostk::math::geometry::d3::Intersection;
    using ostk::math::geometry::d3::transformations::rotations::Quaternion;

    class_<Pyramid, Object>(aModule, "Pyramid")

        .def(init<const Polygon&, const Point&>(), arg("base"), arg("apex"))

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Pyramid>))
        .def("__repr__", &(shiftToString<Pyramid>))

        .def("is_defined", &Pyramid::isDefined)
        .def(
            "intersects",
            overload_cast<const Ellipsoid&, const Size>(&Pyramid::intersects, const_),
            arg("ellipsoid"),
            arg("discretization_level") = DEFAULT_DISCRETIZATION_LEVEL
        )
        .def("contains", overload_cast<const Point&>(&Pyramid::contains, const_), arg("point"))
        .def("contains", overload_cast<const PointSet&>(&Pyramid::contains, const_), arg("point_set"))
        .def("contains", overload_cast<const Segment&>(&Pyramid::contains, const_), arg("segment"))
        .def("contains", overload_cast<const Ellipsoid&>(&Pyramid::contains, const_), arg("ellipsoid"))

        .def("get_base", &Pyramid::getBase)
        .def("get_apex", &Pyramid::getApex)
        .def("get_lateral_face_count", &Pyramid::getLateralFaceCount)
        .def("get_lateral_face_at", &Pyramid::getLateralFaceAt)
        .def(
            "get_rays_of_lateral_face_at",
            &Pyramid::getRaysOfLateralFaceAt,
            arg("lateral_face_index"),
            arg("ray_count") = 2
        )
        .def("get_rays_of_lateral_faces", &Pyramid::getRaysOfLateralFaces, arg("ray_count") = 0)
        .def(
            "intersection_with",
            overload_cast<const Sphere&, const bool, const Size>(&Pyramid::intersectionWith, const_),
            arg("sphere"),
            arg("only_in_sight") = DEFAULT_ONLY_IN_SIGHT,
            arg("discretization_level") = DEFAULT_DISCRETIZATION_LEVEL
        )
        .def(
            "intersection_with",
            overload_cast<const Ellipsoid&, const bool, const Size>(&Pyramid::intersectionWith, const_),
            arg("ellipsoid"),
            arg("only_in_sight") = DEFAULT_ONLY_IN_SIGHT,
            arg("discretization_level") = DEFAULT_DISCRETIZATION_LEVEL
        )
        .def("apply_transformation", &Pyramid::applyTransformation, arg("transformation"))

        .def_static("undefined", &Pyramid::Undefined)

        ;
}
