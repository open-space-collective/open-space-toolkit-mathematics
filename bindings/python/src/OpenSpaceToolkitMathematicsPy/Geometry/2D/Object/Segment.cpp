/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Segment.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_2D_Object_Segment(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Integer;

    using ostk::mathematics::geometry::d2::Object;
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::PointSet;
    using ostk::mathematics::geometry::d2::object::Segment;

    class_<Segment, Object>(aModule, "Segment")

        .def(
            init<const Point&, const Point&>(),
            R"doc(
                Create a 2D segment defined by two endpoints.

                Args:
                    start_point (Point): The starting point of the segment.
                    end_point (Point): The ending point of the segment.

                Example:
                    >>> start = Point(0.0, 0.0)
                    >>> end = Point(1.0, 1.0)
                    >>> segment = Segment(start, end)
            )doc",
            arg("start_point"),
            arg("end_point")
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
                    >>> segment = Segment(Point(0.0, 0.0), Point(1.0, 1.0))
                    >>> segment.is_defined()  # True
            )doc"
        )
        .def(
            "is_degenerate",
            &Segment::isDegenerate,
            R"doc(
                Check if the segment is degenerate (start and end points are the same).

                Returns:
                    bool: True if the segment is degenerate, False otherwise.

                Example:
                    >>> segment = Segment(Point(1.0, 1.0), Point(1.0, 1.0))
                    >>> segment.is_degenerate()  # True
                    >>> segment2 = Segment(Point(0.0, 0.0), Point(1.0, 1.0))
                    >>> segment2.is_degenerate()  # False
            )doc"
        )

        .def(
            "get_first_point",
            &Segment::getFirstPoint,
            R"doc(
                Get the first (starting) point of the segment.

                Returns:
                    Point: The starting point of the segment.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0), Point(1.0, 1.0))
                    >>> start = segment.get_first_point()  # Point(0.0, 0.0)
            )doc"
        )
        .def(
            "get_second_point",
            &Segment::getSecondPoint,
            R"doc(
                Get the second (ending) point of the segment.

                Returns:
                    Point: The ending point of the segment.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0), Point(1.0, 1.0))
                    >>> end = segment.get_second_point()  # Point(1.0, 1.0)
            )doc"
        )
        .def(
            "get_center",
            &Segment::getCenter,
            R"doc(
                Get the center (midpoint) of the segment.

                Returns:
                    Point: The center point of the segment.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0), Point(2.0, 2.0))
                    >>> center = segment.get_center()  # Point(1.0, 1.0)
            )doc"
        )
        .def(
            "get_direction",
            &Segment::getDirection,
            R"doc(
                Get the direction vector of the segment (from start to end, normalized).

                Returns:
                    Vector2d: The normalized direction vector of the segment.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0), Point(3.0, 4.0))
                    >>> direction = segment.get_direction()  # [0.6, 0.8]
            )doc"
        )
        .def(
            "get_length",
            &Segment::getLength,
            R"doc(
                Get the length of the segment.

                Returns:
                    float: The length of the segment.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0), Point(3.0, 4.0))
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
                    float: The minimum distance from the segment to the point.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0), Point(2.0, 0.0))
                    >>> distance = segment.distance_to(Point(1.0, 1.0))  # 1.0
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
                    float: The minimum distance from the segment to any point in the set.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0), Point(2.0, 0.0))
                    >>> points = PointSet([Point(1.0, 1.0), Point(3.0, 1.0)])
                    >>> distance = segment.distance_to(points)  # 1.0
            )doc",
            arg("point_set")
        )
        .def(
            "to_line",
            &Segment::toLine,
            R"doc(
                Convert the segment to an infinite line.

                Returns:
                    Line: A line that passes through both endpoints of the segment.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0), Point(1.0, 1.0))
                    >>> line = segment.to_line()
            )doc"
        )
        .def(
            "to_string",
            &Segment::toString,
            R"doc(
                Convert the segment to a string representation.

                Args:
                    format (Object.Format, optional): The output format. Defaults to Standard.
                    precision (int, optional): The precision for floating point numbers. Defaults to undefined.

                Returns:
                    str: String representation of the segment.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0), Point(1.0, 1.0))
                    >>> segment.to_string()
            )doc",
            arg("format") = Object::Format::Standard,
            arg("precision") = Integer::Undefined()
        )
        .def(
            "apply_transformation",
            &Segment::applyTransformation,
            R"doc(
                Apply a transformation to the segment in place.

                Args:
                    transformation (Transformation): The 2D transformation to apply.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0), Point(1.0, 1.0))
                    >>> transformation = Translation([1.0, 1.0])
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
        )

        ;
}
