/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Sphere.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Sphere(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;

    using ostk::mathematics::geometry::d3::Intersection;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Ellipsoid;
    using ostk::mathematics::geometry::d3::object::Line;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::geometry::d3::object::Sphere;

    class_<Sphere, Object>(aModule, "Sphere")

        .def(
            init<const Point&, const Real&>(),
            R"doc(
                Create a 3D sphere with center and radius.

                Args:
                    center (Point): The center point of the sphere.
                    radius (float): The radius of the sphere.

                Example:
                    >>> center = Point(0.0, 0.0, 0.0)
                    >>> sphere = Sphere(center, 1.0)
            )doc",
            arg("center"),
            arg("radius")
        )

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Sphere>))
        .def("__repr__", &(shiftToString<Sphere>))

        .def(
            "is_defined",
            &Sphere::isDefined,
            R"doc(
                Check if the sphere is defined.

                Returns:
                    bool: True if the sphere is defined, False otherwise.

                Example:
                    >>> sphere = Sphere(Point(0.0, 0.0, 0.0), 1.0)
                    >>> sphere.is_defined()  # True
            )doc"
        )
        .def(
            "is_unitary",
            &Sphere::isUnitary,
            R"doc(
                Check if the sphere is a unit sphere (radius = 1).

                Returns:
                    bool: True if the sphere has unit radius, False otherwise.

                Example:
                    >>> sphere = Sphere(Point(0.0, 0.0, 0.0), 1.0)
                    >>> sphere.is_unitary()  # True
            )doc"
        )

        .def("intersects", overload_cast<const Point&>(&Sphere::intersects, const_), arg("point"))
        .def("intersects", overload_cast<const PointSet&>(&Sphere::intersects, const_), arg("point_set"))
        .def("intersects", overload_cast<const Line&>(&Sphere::intersects, const_), arg("line"))
        .def("intersects", overload_cast<const Ray&>(&Sphere::intersects, const_), arg("ray"))
        .def("intersects", overload_cast<const Segment&>(&Sphere::intersects, const_), arg("segment"))
        .def("intersects", overload_cast<const Plane&>(&Sphere::intersects, const_), arg("plane"))
        .def(
            "contains",
            overload_cast<const Point&>(&Sphere::contains, const_),
            R"doc(
                Check if the sphere contains a point.

                Args:
                    point (Point): The point to check.

                Returns:
                    bool: True if the sphere contains the point, False otherwise.

                Example:
                    >>> sphere = Sphere(Point(0.0, 0.0, 0.0), 1.0)
                    >>> sphere.contains(Point(0.5, 0.5, 0.5))  # True
            )doc",
            arg("point")
        )
        .def("contains", overload_cast<const PointSet&>(&Sphere::contains, const_), arg("point_set"))

        .def(
            "get_center",
            &Sphere::getCenter,
            R"doc(
                Get the center point of the sphere.

                Returns:
                    Point: The center point of the sphere.

                Example:
                    >>> sphere = Sphere(Point(1.0, 2.0, 3.0), 1.0)
                    >>> center = sphere.get_center()  # Point(1.0, 2.0, 3.0)
            )doc"
        )
        .def(
            "get_radius",
            &Sphere::getRadius,
            R"doc(
                Get the radius of the sphere.

                Returns:
                    float: The radius of the sphere.

                Example:
                    >>> sphere = Sphere(Point(0.0, 0.0, 0.0), 2.5)
                    >>> radius = sphere.get_radius()  # 2.5
            )doc"
        )

        .def("intersection_with", overload_cast<const Line&>(&Sphere::intersectionWith, const_), arg("line"))
        .def(
            "intersection_with",
            overload_cast<const Ray&, const bool>(&Sphere::intersectionWith, const_),
            arg("ray"),
            arg("only_in_sight") = DEFAULT_ONLY_IN_SIGHT
        )
        .def("apply_transformation", &Sphere::applyTransformation, arg("transformation"))

        .def_static(
            "undefined",
            &Sphere::Undefined,
            R"doc(
                Create an undefined sphere.

                Returns:
                    Sphere: An undefined sphere.

                Example:
                    >>> undefined_sphere = Sphere.undefined()
                    >>> undefined_sphere.is_defined()  # False
            )doc"
        )
        .def_static(
            "unit",
            &Sphere::Unit,
            R"doc(
                Create a unit sphere (radius = 1) at a given center.

                Args:
                    center (Point): The center point of the unit sphere.

                Returns:
                    Sphere: A unit sphere centered at the given point.

                Example:
                    >>> center = Point(1.0, 2.0, 3.0)
                    >>> unit_sphere = Sphere.unit(center)
                    >>> unit_sphere.get_radius()  # 1.0
            )doc",
            arg("center")
        )

        ;
}
