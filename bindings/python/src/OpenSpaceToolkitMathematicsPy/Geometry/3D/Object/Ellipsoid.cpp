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
            R"doc(
                Create an ellipsoid with specified center and semi-axes.

                Args:
                    center (Point): The center point of the ellipsoid.
                    first_principal_semi_axis (float): The first principal semi-axis length.
                    second_principal_semi_axis (float): The second principal semi-axis length.
                    third_principal_semi_axis (float): The third principal semi-axis length.

                Example:
                    >>> center = Point(0.0, 0.0, 0.0)
                    >>> ellipsoid = Ellipsoid(center, 2.0, 1.5, 1.0)
            )doc",
            arg("center"),
            arg("first_principal_semi_axis"),
            arg("second_principal_semi_axis"),
            arg("third_principal_semi_axis")
        )

        .def(
            init<const Point&, const Real&, const Real&, const Real&, const Quaternion&>(),
            R"doc(
                Create an ellipsoid with specified center, semi-axes, and orientation.

                Args:
                    center (Point): The center point of the ellipsoid.
                    first_principal_semi_axis (float): The first principal semi-axis length.
                    second_principal_semi_axis (float): The second principal semi-axis length.
                    third_principal_semi_axis (float): The third principal semi-axis length.
                    orientation (Quaternion): The orientation of the ellipsoid.

                Example:
                    >>> center = Point(0.0, 0.0, 0.0)
                    >>> orientation = Quaternion.unit()
                    >>> ellipsoid = Ellipsoid(center, 2.0, 1.5, 1.0, orientation)
            )doc",
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

        .def(
            "is_defined",
            &Ellipsoid::isDefined,
            R"doc(
                Check if the ellipsoid is defined.

                Returns:
                    bool: True if the ellipsoid is defined, False otherwise.

                Example:
                    >>> ellipsoid = Ellipsoid(center, 2.0, 1.5, 1.0)
                    >>> ellipsoid.is_defined()  # True
            )doc"
        )

        .def("intersects", overload_cast<const Point&>(&Ellipsoid::intersects, const_), arg("point"))
        .def("intersects", overload_cast<const PointSet&>(&Ellipsoid::intersects, const_), arg("point_set"))
        .def("intersects", overload_cast<const Line&>(&Ellipsoid::intersects, const_), arg("line"))
        .def("intersects", overload_cast<const Ray&>(&Ellipsoid::intersects, const_), arg("ray"))
        .def("intersects", overload_cast<const Segment&>(&Ellipsoid::intersects, const_), arg("segment"))
        .def("intersects", overload_cast<const Plane&>(&Ellipsoid::intersects, const_), arg("plane"))
        .def(
            "contains",
            overload_cast<const Point&>(&Ellipsoid::contains, const_),
            R"doc(
                Check if the ellipsoid contains a point.

                Args:
                    point (Point): The point to check.

                Returns:
                    bool: True if the ellipsoid contains the point, False otherwise.

                Example:
                    >>> ellipsoid = Ellipsoid(Point(0.0, 0.0, 0.0), 2.0, 1.5, 1.0)
                    >>> ellipsoid.contains(Point(0.5, 0.5, 0.5))  # True if inside
            )doc",
            arg("point")
        )
        .def("contains", overload_cast<const PointSet&>(&Ellipsoid::contains, const_), arg("point_set"))
        .def("contains", overload_cast<const Segment&>(&Ellipsoid::contains, const_), arg("segment"))

        .def(
            "get_center",
            &Ellipsoid::getCenter,
            R"doc(
                Get the center point of the ellipsoid.

                Returns:
                    Point: The center point of the ellipsoid.

                Example:
                    >>> ellipsoid = Ellipsoid(Point(1.0, 2.0, 3.0), 2.0, 1.5, 1.0)
                    >>> center = ellipsoid.get_center()  # Point(1.0, 2.0, 3.0)
            )doc"
        )
        .def(
            "get_first_principal_semi_axis",
            &Ellipsoid::getFirstPrincipalSemiAxis,
            R"doc(
                Get the first principal semi-axis length.

                Returns:
                    float: The length of the first principal semi-axis.

                Example:
                    >>> ellipsoid = Ellipsoid(center, 2.0, 1.5, 1.0)
                    >>> first_axis = ellipsoid.get_first_principal_semi_axis()  # 2.0
            )doc"
        )
        .def(
            "get_second_principal_semi_axis",
            &Ellipsoid::getSecondPrincipalSemiAxis,
            R"doc(
                Get the second principal semi-axis length.

                Returns:
                    float: The length of the second principal semi-axis.

                Example:
                    >>> ellipsoid = Ellipsoid(center, 2.0, 1.5, 1.0)
                    >>> second_axis = ellipsoid.get_second_principal_semi_axis()  # 1.5
            )doc"
        )
        .def(
            "get_third_principal_semi_axis",
            &Ellipsoid::getThirdPrincipalSemiAxis,
            R"doc(
                Get the third principal semi-axis length.

                Returns:
                    float: The length of the third principal semi-axis.

                Example:
                    >>> ellipsoid = Ellipsoid(center, 2.0, 1.5, 1.0)
                    >>> third_axis = ellipsoid.get_third_principal_semi_axis()  # 1.0
            )doc"
        )
        .def("get_first_axis", &Ellipsoid::getFirstAxis)
        .def("get_second_axis", &Ellipsoid::getSecondAxis)
        .def("get_third_axis", &Ellipsoid::getThirdAxis)
        .def(
            "get_orientation",
            &Ellipsoid::getOrientation,
            R"doc(
                Get the orientation quaternion of the ellipsoid.

                Returns:
                    Quaternion: The orientation quaternion of the ellipsoid.

                Example:
                    >>> ellipsoid = Ellipsoid(center, 2.0, 1.5, 1.0, orientation)
                    >>> quat = ellipsoid.get_orientation()
            )doc"
        )
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

        .def_static(
            "undefined",
            &Ellipsoid::Undefined,
            R"doc(
                Create an undefined ellipsoid.

                Returns:
                    Ellipsoid: An undefined ellipsoid object.

                Example:
                    >>> undefined_ellipsoid = Ellipsoid.undefined()
                    >>> undefined_ellipsoid.is_defined()  # False
            )doc"
        )

        ;
}
