/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Line.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_2D_Object_Line(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;

    using ostk::mathematics::geometry::d2::Object;
    using ostk::mathematics::geometry::d2::object::Line;
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::PointSet;
    using ostk::mathematics::object::Vector2d;

    class_<Line, Object>(aModule, "Line")

        .def(
            init<const Point&, const Vector2d&>(),
            R"doc(
                Create a 2D line with a point and direction vector.

                Args:
                    point (Point): A point on the line.
                    direction (Vector2d): The direction vector of the line.

                Example:
                    >>> point = Point(0.0, 0.0)
                    >>> direction = Vector2d([1.0, 1.0])
                    >>> line = Line(point, direction)
            )doc",
            arg("point"),
            arg("direction")
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
                    bool: True if the line is defined, False otherwise.

                Example:
                    >>> line = Line.points(Point(0.0, 0.0), Point(1.0, 1.0))
                    >>> line.is_defined()  # True
            )doc"
        )
        .def(
            "intersects",
            overload_cast<const Point&>(&Line::intersects, const_),
            R"doc(
                Check if the line intersects with a point.

                Args:
                    point (Point): The point to check intersection with.

                Returns:
                    bool: True if the line intersects with the point, False otherwise.

                Example:
                    >>> line = Line.points(Point(0.0, 0.0), Point(1.0, 1.0))
                    >>> line.intersects(Point(0.5, 0.5))  # True
            )doc",
            arg("point")
        )
        .def(
            "contains",
            overload_cast<const Point&>(&Line::contains, const_),
            R"doc(
                Check if the line contains a point.

                Args:
                    point (Point): The point to check.

                Returns:
                    bool: True if the line contains the point, False otherwise.

                Example:
                    >>> line = Line.points(Point(0.0, 0.0), Point(1.0, 1.0))
                    >>> line.contains(Point(0.5, 0.5))  # True
            )doc",
            arg("point")
        )
        .def(
            "contains",
            overload_cast<const PointSet&>(&Line::contains, const_),
            R"doc(
                Check if the line contains all points in a point set.

                Args:
                    point_set (PointSet): The set of points to check.

                Returns:
                    bool: True if the line contains all points in the set, False otherwise.

                Example:
                    >>> line = Line.points(Point(0.0, 0.0), Point(1.0, 1.0))
                    >>> points = PointSet([Point(0.5, 0.5), Point(0.25, 0.25)])
                    >>> line.contains(points)
            )doc",
            arg("point_set")
        )

        .def(
            "get_origin",
            &Line::getOrigin,
            R"doc(
                Get the origin point of the line.

                Returns:
                    Point: The origin point of the line.

                Example:
                    >>> line = Line.points(Point(1.0, 2.0), Point(3.0, 4.0))
                    >>> origin = line.get_origin()
            )doc"
        )
        .def(
            "get_direction",
            &Line::getDirection,
            R"doc(
                Get the direction vector of the line.

                Returns:
                    Vector2d: The direction vector of the line.

                Example:
                    >>> line = Line.points(Point(0.0, 0.0), Point(1.0, 1.0))
                    >>> direction = line.get_direction()
            )doc"
        )
        .def(
            "distance_to",
            overload_cast<const Point&>(&Line::distanceTo, const_),
            R"doc(
                Calculate the distance from the line to a point.

                Args:
                    point (Point): The point to calculate distance to.

                Returns:
                    float: The distance from the line to the point.

                Example:
                    >>> line = Line.points(Point(0.0, 0.0), Point(1.0, 0.0))
                    >>> distance = line.distance_to(Point(0.5, 1.0))  # 1.0
            )doc",
            arg("point")
        )
        .def(
            "apply_transformation",
            &Line::applyTransformation,
            R"doc(
                Apply a transformation to the line.

                Args:
                    transformation (Transformation): The transformation to apply.

                Returns:
                    Line: The transformed line.

                Example:
                    >>> line = Line.points(Point(0.0, 0.0), Point(1.0, 0.0))
                    >>> transformation = Translation([1.0, 1.0])
                    >>> transformed = line.apply_transformation(transformation)
            )doc",
            arg("transformation")
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
            )doc",
            arg("first_point"),
            arg("second_point")
        )

        ;
}
