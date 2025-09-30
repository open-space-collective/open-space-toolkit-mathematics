/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Segment.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Segment(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::mathematics::geometry::d3::Intersection;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Ellipsoid;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::geometry::d3::object::Sphere;

    class_<Segment, Object>(aModule, "Segment")

        .def(
            init<const Point&, const Point&>(),
            R"doc(
                Create a 3D segment between two points.

                Args:
                    first_point (Point): The first endpoint of the segment.
                    second_point (Point): The second endpoint of the segment.

                Example:
                    >>> point1 = Point(0.0, 0.0, 0.0)
                    >>> point2 = Point(1.0, 1.0, 1.0)
                    >>> segment = Segment(point1, point2)
            )doc",
            arg("first_point"),
            arg("second_point")
        )

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Segment>))
        .def("__repr__", &(shiftToString<Segment>))

        .def(
            "is_defined",
            &Segment::isDefined,
            R"doc(
                Check if the segment is defined.

                Returns:
                    bool: True if the segment is defined, False otherwise.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0, 0.0), Point(1.0, 1.0, 1.0))
                    >>> segment.is_defined()  # True
            )doc"
        )
        .def(
            "is_degenerate",
            &Segment::isDegenerate,
            R"doc(
                Check if the segment is degenerate (both endpoints are the same).

                Returns:
                    bool: True if the segment is degenerate, False otherwise.

                Example:
                    >>> point = Point(0.0, 0.0, 0.0)
                    >>> degenerate_segment = Segment(point, point)
                    >>> degenerate_segment.is_degenerate()  # True
            )doc"
        )
        .def(
            "intersects",
            overload_cast<const Plane&>(&Segment::intersects, const_),
            R"doc(
                Check if the segment intersects a plane.

                Args:
                    plane (Plane): The plane to check intersection with.

                Returns:
                    bool: True if the segment intersects the plane.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0, 0.0), Point(2.0, 0.0, 0.0))
                    >>> segment.intersects(Plane(Point(1.0, 0.0, 0.0), Vector3d(0.0, 0.0, 1.0)))  # True
            )doc",
            arg("plane")
        )
        .def(
            "intersects",
            overload_cast<const Sphere&>(&Segment::intersects, const_),
            R"doc(
                Check if the segment intersects a sphere.

                Args:
                    sphere (Sphere): The sphere to check intersection with.

                Returns:
                    bool: True if the segment intersects the sphere.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0, 0.0), Point(2.0, 0.0, 0.0))
                    >>> segment.intersects(Sphere(Point(1.0, 0.0, 0.0), 1.0))  # True
            )doc",
            arg("sphere")
        )
        .def(
            "intersects",
            overload_cast<const Ellipsoid&>(&Segment::intersects, const_),
            R"doc(
                Check if the segment intersects an ellipsoid.

                Args:
                    ellipsoid (Ellipsoid): The ellipsoid to check intersection with.

                Returns:
                    bool: True if the segment intersects the ellipsoid.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0, 0.0), Point(2.0, 0.0, 0.0))
                    >>> segment.intersects(Ellipsoid(Point(1.0, 0.0, 0.0), 1.0, 1.0, 1.0))  # True
            )doc",
            arg("ellipsoid")
        )
        .def(
            "contains",
            overload_cast<const Point&>(&Segment::contains, const_),
            R"doc(
                Check if the segment contains a point.

                Args:
                    point (Point): The point to check.

                Returns:
                    bool: True if the segment contains the point, False otherwise.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0, 0.0), Point(2.0, 0.0, 0.0))
                    >>> segment.contains(Point(1.0, 0.0, 0.0))  # True (midpoint)
            )doc",
            arg("point")
        )

        .def(
            "get_first_point",
            &Segment::getFirstPoint,
            R"doc(
                Get the first endpoint of the segment.

                Returns:
                    Point: The first endpoint of the segment.

                Example:
                    >>> segment = Segment(Point(1.0, 2.0, 3.0), Point(4.0, 5.0, 6.0))
                    >>> first_point = segment.get_first_point()  # Point(1.0, 2.0, 3.0)
            )doc"
        )
        .def(
            "get_second_point",
            &Segment::getSecondPoint,
            R"doc(
                Get the second endpoint of the segment.

                Returns:
                    Point: The second endpoint of the segment.

                Example:
                    >>> segment = Segment(Point(1.0, 2.0, 3.0), Point(4.0, 5.0, 6.0))
                    >>> second_point = segment.get_second_point()  # Point(4.0, 5.0, 6.0)
            )doc"
        )
        .def(
            "get_center",
            &Segment::getCenter,
            R"doc(
                Get the center point of the segment.

                Returns:
                    Point: The midpoint of the segment.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0, 0.0), Point(2.0, 2.0, 2.0))
                    >>> center = segment.get_center()  # Point(1.0, 1.0, 1.0)
            )doc"
        )
        .def(
            "get_direction",
            &Segment::getDirection,
            R"doc(
                Get the direction vector of the segment.

                Returns:
                    Vector3d: The normalized direction vector from first to second point.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0, 0.0), Point(1.0, 0.0, 0.0))
                    >>> direction = segment.get_direction()  # [1.0, 0.0, 0.0]
            )doc"
        )
        .def(
            "get_length",
            &Segment::getLength,
            R"doc(
                Get the length of the segment.

                Returns:
                    float: The distance between the two endpoints.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0, 0.0), Point(3.0, 4.0, 0.0))
                    >>> length = segment.get_length()  # 5.0
            )doc"
        )
        .def(
            "distance_to",
            overload_cast<const Point&>(&Segment::distanceTo, const_),
            R"doc(
                Calculate the distance from the segment to a point.

                Args:
                    point (Point): The point to calculate distance to.

                Returns:
                    float: The distance from the segment to the point.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0, 0.0), Point(2.0, 0.0, 0.0))
                    >>> distance = segment.distance_to(Point(1.0, 0.0, 0.0))  # 1.0
            )doc",
            arg("point")
        )
        .def(
            "distance_to",
            overload_cast<const PointSet&>(&Segment::distanceTo, const_),
            R"doc(
                Calculate the distance from the segment to a point set.

                Args:
                    point_set (PointSet): The point set to calculate distance to.

                Returns:
                    float: The distance from the segment to the point set.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0, 0.0), Point(2.0, 0.0, 0.0))
                    >>> points = PointSet([Point(1.0, 0.0, 0.0), Point(3.0, 0.0, 0.0)])
                    >>> distance = segment.distance_to(points)  # 1.0
            )doc",
            arg("point_set")
        )
        .def(
            "intersection_with",
            overload_cast<const Plane&>(&Segment::intersectionWith, const_),
            R"doc(
                Calculate the intersection of the segment with a plane.

                Args:
                    plane (Plane): The plane to calculate intersection with.

                Returns:
                    Intersection: The intersection of the segment with the plane.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0, 0.0), Point(2.0, 0.0, 0.0))
                    >>> plane = Plane(Point(1.0, 0.0, 0.0), Vector3d(0.0, 0.0, 1.0))
                    >>> intersection = segment.intersection_with(plane)
                    >>> intersection.get_point()  # Point(1.0, 0.0, 0.0)
            )doc",
            arg("plane")
        )
        .def(
            "to_line",
            &Segment::toLine,
            R"doc(
                Convert the segment to a line.

                Returns:
                    Line: A line passing through the segment's endpoints.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0, 0.0), Point(1.0, 1.0, 1.0))
                    >>> line = segment.to_line()
            )doc"
        )
        .def(
            "apply_transformation",
            &Segment::applyTransformation,
            R"doc(
                Apply a transformation to the segment in place.

                Args:
                    transformation (Transformation): The transformation to apply.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0, 0.0), Point(1.0, 1.0, 1.0))
                    >>> transformation = Translation([1.0, 1.0, 1.0])
                    >>> segment.apply_transformation(transformation)
            )doc",
            arg("transformation")
        )

        .def_static(
            "undefined",
            &Segment::Undefined,
            R"doc(
                Create an undefined segment.

                Returns:
                    Segment: An undefined segment object.

                Example:
                    >>> undefined_segment = Segment.undefined()
                    >>> undefined_segment.is_defined()  # False
            )doc"
        );
}
