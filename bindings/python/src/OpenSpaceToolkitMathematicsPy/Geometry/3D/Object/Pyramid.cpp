/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Pyramid.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Pyramid(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Size;
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::geometry::d3::object::Line;
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Sphere;
    using ostk::mathematics::geometry::d3::object::Ellipsoid;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::Intersection;
    using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;

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
