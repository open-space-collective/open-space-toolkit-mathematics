/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ellipsoid.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Ellipsoid(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;

    using ostk::mathematics::geometry::d3::Intersection;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Ellipsoid;
    using ostk::mathematics::geometry::d3::object::Line;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::geometry::d3::object::Sphere;
    using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;

    class_<Ellipsoid, Object>(aModule, "Ellipsoid")

        .def(
            init<const Point&, const Real&, const Real&, const Real&>(),
            arg("center"),
            arg("first_principal_semi_axis"),
            arg("second_principal_semi_axis"),
            arg("third_principal_semi_axis")
        )

        .def(
            init<const Point&, const Real&, const Real&, const Real&, const Quaternion&>(),
            arg("center"),
            arg("first_principal_semi_axis"),
            arg("second_principal_semi_axis"),
            arg("third_principal_semi_axis"),
            arg("orientation")
        )

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Ellipsoid>))
        .def("__repr__", &(shiftToString<Ellipsoid>))

        .def("is_defined", &Ellipsoid::isDefined)

        .def("intersects", overload_cast<const Point&>(&Ellipsoid::intersects, const_), arg("point"))
        .def("intersects", overload_cast<const PointSet&>(&Ellipsoid::intersects, const_), arg("point_set"))
        .def("intersects", overload_cast<const Line&>(&Ellipsoid::intersects, const_), arg("line"))
        .def("intersects", overload_cast<const Ray&>(&Ellipsoid::intersects, const_), arg("ray"))
        .def("intersects", overload_cast<const Segment&>(&Ellipsoid::intersects, const_), arg("segment"))
        .def("intersects", overload_cast<const Plane&>(&Ellipsoid::intersects, const_), arg("plane"))
        .def("contains", overload_cast<const Point&>(&Ellipsoid::contains, const_), arg("point"))
        .def("contains", overload_cast<const PointSet&>(&Ellipsoid::contains, const_), arg("point_set"))
        .def("contains", overload_cast<const Segment&>(&Ellipsoid::contains, const_), arg("segment"))

        .def("get_center", &Ellipsoid::getCenter)
        .def("get_first_principal_semi_axis", &Ellipsoid::getFirstPrincipalSemiAxis)
        .def("get_second_principal_semi_axis", &Ellipsoid::getSecondPrincipalSemiAxis)
        .def("get_third_principal_semi_axis", &Ellipsoid::getThirdPrincipalSemiAxis)
        .def("get_first_axis", &Ellipsoid::getFirstAxis)
        .def("get_second_axis", &Ellipsoid::getSecondAxis)
        .def("get_third_axis", &Ellipsoid::getThirdAxis)
        .def("get_orientation", &Ellipsoid::getOrientation)
        .def("get_matrix", &Ellipsoid::getMatrix)
        .def("intersection", overload_cast<const Line&>(&Ellipsoid::intersectionWith, const_), arg("line"))
        .def(
            "intersection",
            overload_cast<const Ray&, const bool>(&Ellipsoid::intersectionWith, const_),
            arg("ray"),
            arg("only_in_sight")
        )
        .def("intersection", overload_cast<const Segment&>(&Ellipsoid::intersectionWith, const_), arg("segment"))
        .def(
            "intersection",
            overload_cast<const Pyramid&, const bool>(&Ellipsoid::intersectionWith, const_),
            arg("pyramid"),
            arg("only_in_sight")
        )
        .def(
            "intersection",
            overload_cast<const Cone&, const bool>(&Ellipsoid::intersectionWith, const_),
            arg("cone"),
            arg("only_in_sight")
        )
        .def("apply_transformation", &Ellipsoid::applyTransformation, arg("transformation"))

        .def_static("undefined", &Ellipsoid::Undefined)

        ;
}
