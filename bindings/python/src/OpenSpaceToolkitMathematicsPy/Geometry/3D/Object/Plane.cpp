/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Plane.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Plane(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::mathematics::geometry::d3::Intersection;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Line;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::object::Vector3d;

    class_<Plane, Object>(aModule, "Plane")

        .def(
            init<const Point&, const Vector3d&>(),
            R"doc(
                Create a 3D plane from a point and normal vector.

                Args:
                    point (Point): A point on the plane.
                    normal_vector (Vector3d): The normal vector to the plane.

                Example:
                    >>> point = Point(0.0, 0.0, 0.0)
                    >>> normal = Vector3d([0.0, 0.0, 1.0])
                    >>> plane = Plane(point, normal)
            )doc",
            arg("point"),
            arg("normal_vector")
        )

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Plane>))
        .def("__repr__", &(shiftToString<Plane>))

        .def(
            "is_defined",
            &Plane::isDefined,
            R"doc(
                Check if the plane is defined.

                Returns:
                    bool: True if the plane is defined, False otherwise.

                Example:
                    >>> plane = Plane(Point(0.0, 0.0, 0.0), Vector3d([0.0, 0.0, 1.0]))
                    >>> plane.is_defined()  # True
            )doc"
        )

        .def("intersects", overload_cast<const Point&>(&Plane::intersects, const_), arg("point"))
        .def("intersects", overload_cast<const PointSet&>(&Plane::intersects, const_), arg("point_set"))
        .def("intersects", overload_cast<const Line&>(&Plane::intersects, const_), arg("line"))
        .def("intersects", overload_cast<const Ray&>(&Plane::intersects, const_), arg("ray"))
        .def("intersects", overload_cast<const Segment&>(&Plane::intersects, const_), arg("segment"))
        .def(
            "contains",
            overload_cast<const Point&>(&Plane::contains, const_),
            R"doc(
                Check if the plane contains a point.

                Args:
                    point (Point): The point to check.

                Returns:
                    bool: True if the plane contains the point, False otherwise.

                Example:
                    >>> plane = Plane(Point(0.0, 0.0, 0.0), Vector3d([0.0, 0.0, 1.0]))
                    >>> plane.contains(Point(1.0, 1.0, 0.0))  # True (z=0 plane)
            )doc",
            arg("point")
        )
        .def("contains", overload_cast<const PointSet&>(&Plane::contains, const_), arg("point_set"))
        .def("contains", overload_cast<const Line&>(&Plane::contains, const_), arg("line"))
        .def("contains", overload_cast<const Ray&>(&Plane::contains, const_), arg("ray"))
        .def("contains", overload_cast<const Segment&>(&Plane::contains, const_), arg("segment"))

        .def(
            "get_point",
            &Plane::getPoint,
            R"doc(
                Get a reference point on the plane.

                Returns:
                    Point: A point on the plane.

                Example:
                    >>> plane = Plane(Point(1.0, 2.0, 3.0), Vector3d([0.0, 0.0, 1.0]))
                    >>> point = plane.get_point()
            )doc"
        )
        .def(
            "get_normal_vector",
            &Plane::getNormalVector,
            R"doc(
                Get the normal vector of the plane.

                Returns:
                    Vector3d: The normal vector to the plane.

                Example:
                    >>> plane = Plane(Point(0.0, 0.0, 0.0), Vector3d([0.0, 0.0, 1.0]))
                    >>> normal = plane.get_normal_vector()  # [0.0, 0.0, 1.0]
            )doc"
        )
        .def("intersection_with", overload_cast<const Point&>(&Plane::intersectionWith, const_), arg("point"))
        .def("intersection_with", overload_cast<const PointSet&>(&Plane::intersectionWith, const_), arg("point_set"))
        .def("intersection_with", overload_cast<const Line&>(&Plane::intersectionWith, const_), arg("line"))
        .def("intersection_with", overload_cast<const Ray&>(&Plane::intersectionWith, const_), arg("ray"))
        .def("intersection_with", overload_cast<const Segment&>(&Plane::intersectionWith, const_), arg("segment"))
        .def("apply_transformation", &Plane::applyTransformation, arg("transformation"))

        .def_static(
            "undefined",
            &Plane::Undefined,
            R"doc(
                Create an undefined plane.

                Returns:
                    Plane: An undefined plane.

                Example:
                    >>> undefined_plane = Plane.undefined()
                    >>> undefined_plane.is_defined()  # False
            )doc"
        )

        ;
}
