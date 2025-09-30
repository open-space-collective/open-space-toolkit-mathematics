/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Line.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Line(pybind11::module& aModule)
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
    using ostk::mathematics::geometry::d3::object::Sphere;
    using ostk::mathematics::object::Vector3d;

    class_<Line, Object>(
        aModule,
        "Line",
        R"doc(
                An infinite line in 3D space.

                A Line is defined by an origin point and a direction vector.

                Example:
                    >>> line = Line.points(Point(0.0, 0.0), Point(1.0, 0.0))
                    >>> line.is_defined()  # True
            )doc"
    )

        .def(
            init<const Point&, const Vector3d&>(),
            arg("origin"),
            arg("direction"),
            R"doc(
                Construct a line from an origin point and direction vector.

                Args:
                    origin (Point): A point on the line.
                    direction (numpy.ndarray): The direction vector of the line.

                Example:
                    >>> line = Line.points(Point(0.0, 0.0), Point(1.0, 0.0))
                    >>> line.is_defined()  # True
            )doc"
        )

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Line>))
        .def("__repr__", &(shiftToString<Line>))

        .def(
            "is_defined",
            &Line::isDefined,
            R"doc(
                Check if the line is defined.

                Returns:
                    bool: True if the line is defined.

                Example:
                    >>> line = Line.points(Point(0.0, 0.0), Point(1.0, 0.0))
                    >>> line.is_defined()  # True
            )doc"
        )
        .def(
            "intersects",
            overload_cast<const Point&>(&Line::intersects, const_),
            arg("point"),
            R"doc(
                Check if the line intersects a point.

                Args:
                    point (Point): The point to check intersection with.

                Returns:
                    bool: True if the line intersects the point.

                Example:
                    >>> line = Line.points(Point(0.0, 0.0), Point(1.0, 0.0))
                    >>> line.intersects(Point(0.5, 0.5))  # True
            )doc"
        )
        .def(
            "intersects",
            overload_cast<const Plane&>(&Line::intersects, const_),
            arg("plane"),
            R"doc(
                Check if the line intersects a plane.

                Args:
                    plane (Plane): The plane to check intersection with.

                Returns:
                    bool: True if the line intersects the plane.

                Example:
                    >>> line = Line.points(Point(0.0, 0.0), Point(1.0, 0.0))
                    >>> plane = Plane(Point(1.0, 0.0, 0.0), Vector3d(0.0, 0.0, 1.0))
                    >>> line.intersects(plane)  # True
            )doc"
        )
        .def(
            "intersects",
            overload_cast<const Sphere&>(&Line::intersects, const_),
            arg("sphere"),
            R"doc(
                Check if the line intersects a sphere.

                Args:
                    sphere (Sphere): The sphere to check intersection with.

                Returns:
                    bool: True if the line intersects the sphere.

                Example:
                    >>> line = Line.points(Point(0.0, 0.0), Point(1.0, 0.0))
                    >>> sphere = Sphere(Point(1.0, 0.0, 0.0), 1.0)
                    >>> line.intersects(sphere)  # True
            )doc"
        )
        .def(
            "intersects",
            overload_cast<const Ellipsoid&>(&Line::intersects, const_),
            arg("ellipsoid"),
            R"doc(
                Check if the line intersects an ellipsoid.

                Args:
                    ellipsoid (Ellipsoid): The ellipsoid to check intersection with.

                Returns:
                    bool: True if the line intersects the ellipsoid.

                Example:
                    >>> line = Line.points(Point(0.0, 0.0), Point(1.0, 0.0))
                    >>> ellipsoid = Ellipsoid(Point(2.0, 0.0, 0.0), 1.0, 1.0, 1.0)
                    >>> line.intersects(ellipsoid)  # True
            )doc"
        )
        .def(
            "contains",
            overload_cast<const Point&>(&Line::contains, const_),
            arg("point"),
            R"doc(
                Check if the line contains a point.

                Args:
                    point (Point): The point to check.

                Returns:
                    bool: True if the line contains the point.

                Example:
                    >>> line = Line.points(Point(0.0, 0.0), Point(1.0, 0.0))
                    >>> line.contains(Point(0.5, 0.5))  # True
            )doc"
        )
        .def(
            "contains",
            overload_cast<const PointSet&>(&Line::contains, const_),
            arg("point_set"),
            R"doc(
                Check if the line contains all points in a point set.

                Args:
                    point_set (PointSet): The point set to check.

                Returns:
                    bool: True if the line contains all points.
                
                Example:
                    >>> line = Line.points(Point(0.0, 0.0), Point(1.0, 0.0))
                    >>> points = PointSet([Point(0.5, 0.5), Point(0.25, 0.25)])
                    >>> line.contains(points)  # True
            )doc"
        )

        .def(
            "get_origin",
            &Line::getOrigin,
            R"doc(
                Get the origin point of the line.

                Returns:
                    Point: The origin point.

                Example:
                    >>> line = Line.points(Point(0.0, 0.0), Point(1.0, 0.0))
                    >>> origin = line.get_origin()  # Point(0.0, 0.0, 0.0)
            )doc"
        )
        .def(
            "get_direction",
            &Line::getDirection,
            R"doc(
                Get the direction vector of the line.

                Returns:
                    numpy.ndarray: The direction vector.
                
                Example:
                    >>> line = Line.points(Point(0.0, 0.0), Point(1.0, 0.0))
                    >>> direction = line.get_direction()  # [1.0, 0.0, 0.0]
            )doc"
        )
        .def(
            "distance_to",
            overload_cast<const Point&>(&Line::distanceTo, const_),
            arg("point"),
            R"doc(
                Calculate the distance from the line to a point.

                Args:
                    point (Point): The point to measure distance to.

                Returns:
                    float: The distance to the point.

                Example:
                    >>> line = Line.points(Point(0.0, 0.0), Point(1.0, 0.0))
                    >>> distance = line.distance_to(Point(0.5, 1.0))  # 1.0
            )doc"
        )
        .def(
            "intersection_with",
            overload_cast<const Plane&>(&Line::intersectionWith, const_),
            arg("plane"),
            R"doc(
                Compute the intersection of the line with a plane.

                Args:
                    plane (Plane): The plane to intersect with.

                Returns:
                    Intersection: The intersection result.

                Example:
                    >>> line = Line.points(Point(0.0, 0.0), Point(1.0, 0.0))
                    >>> plane = Plane(Point(1.0, 0.0, 0.0), Vector3d(0.0, 0.0, 1.0))
                    >>> intersection = line.intersection_with(plane)
                    >>> intersection.get_point()  # Point(1.0, 0.0, 0.0)
            )doc"
        )
        .def(
            "apply_transformation",
            &Line::applyTransformation,
            arg("transformation"),
            R"doc(
                Apply a transformation to the line in place.

                Args:
                    transformation (Transformation): The transformation to apply.

                Example:
                    >>> line = Line.points(Point(0.0, 0.0), Point(1.0, 0.0))
                    >>> transformation = Translation([1.0, 1.0])
                    >>> line.apply_transformation(transformation)
            )doc"
        )

        .def_static(
            "undefined",
            &Line::Undefined,
            R"doc(
                Create an undefined line.

                Returns:
                    Line: An undefined line.
                
                Example:
                    >>> undefined_line = Line.undefined()
                    >>> undefined_line.is_defined()  # False
            )doc"
        )
        .def_static(
            "points",
            &Line::Points,
            arg("first_point"),
            arg("second_point"),
            R"doc(
                Create a line passing through two points.

                Args:
                    first_point (Point): The first point.
                    second_point (Point): The second point.

                Returns:
                    Line: A line passing through both points.

                Example:
                    >>> point1 = Point(0.0, 0.0)
                    >>> point2 = Point(1.0, 1.0)
                    >>> line = Line.points(point1, point2)
                    >>> line.is_defined()  # True
            )doc"
        )

        ;
}
