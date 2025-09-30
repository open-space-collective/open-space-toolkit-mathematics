/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/LineString.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_2D_Object_LineString(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::container::Array;
    using ostk::core::type::Integer;

    using ostk::mathematics::geometry::d2::Object;
    using ostk::mathematics::geometry::d2::object::LineString;
    using ostk::mathematics::geometry::d2::object::Point;

    class_<LineString, Object>(aModule, "LineString")

        .def(
            init<const Array<Point>&>(),
            R"doc(
                Create a 2D line string from a sequence of points.

                Args:
                    points (list): A list of Point objects defining the line string.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0), Point(2.0, 0.0)]
                    >>> line_string = LineString(points)
            )doc",
            arg("points")
        )

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<LineString>))
        .def("__repr__", &(shiftToString<LineString>))

        .def(
            "is_defined",
            &LineString::isDefined,
            R"doc(
                Check if the line string is defined.

                Returns:
                    bool: True if the line string is defined, False otherwise.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0)]
                    >>> line_string = LineString(points)
                    >>> line_string.is_defined()  # True
            )doc"
        )
        .def(
            "is_empty",
            &LineString::isEmpty,
            R"doc(
                Check if the line string is empty (has no points).

                Returns:
                    bool: True if the line string is empty, False otherwise.

                Example:
                    >>> empty_line = LineString.empty()
                    >>> empty_line.is_empty()  # True
            )doc"
        )
        .def(
            "is_near",
            &LineString::isNear,
            R"doc(
                Check if the line string is near another line string.

                Args:
                    line_string (LineString): The line string to check.
                    tolerance (float): The tolerance.

                Returns:
                    bool: True if the line string is near another line string, False otherwise.

                Example:
                    >>> line_string = LineString(points)
                    >>> line_string.is_near(LineString(points), 0.1)  # True
            )doc",
            arg("line_string"),
            arg("tolerance")
        )

        .def(
            "get_point_count",
            &LineString::getPointCount,
            R"doc(
                Get the number of points in the line string.

                Returns:
                    int: The number of points.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0), Point(2.0, 0.0)]
                    >>> line_string = LineString(points)
                    >>> line_string.get_point_count()  # 3
            )doc"
        )
        .def(
            "get_point_closest_to",
            &LineString::getPointClosestTo,
            R"doc(
                Get the point on the line string closest to a given point.

                Args:
                    point (Point): The reference point.

                Returns:
                    Point: The closest point on the line string.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0), Point(2.0, 0.0)]
                    >>> line_string = LineString(points)
                    >>> closest = line_string.get_point_closest_to(Point(0.5, 0.5))
            )doc",
            arg("point")
        )
        .def(
            "to_string",
            &LineString::toString,
            R"doc(
                Convert the line string to a string representation.

                Args:
                    format (Object.Format, optional): The output format. Defaults to Standard.
                    precision (int, optional): The precision for floating point numbers. Defaults to undefined.

                Returns:
                    str: String representation of the line string.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0)]
                    >>> line_string = LineString(points)
                    >>> line_string.to_string()
            )doc",
            arg("format") = Object::Format::Standard,
            arg("precision") = Integer::Undefined()
        )

        .def(
            "apply_transformation",
            &LineString::applyTransformation,
            R"doc(
                Apply a transformation to the line string in place.

                Args:
                    transformation (Transformation): The transformation to apply.

                Example:
                    >>> line_string = LineString(points)
                    >>> transformation = Transformation.translation([1.0, 0.0])
                    >>> line_string.apply_transformation(transformation)
            )doc",
            arg("transformation")
        )

        .def_static(
            "empty",
            &LineString::Empty,
            R"doc(
                Create an empty line string.

                Returns:
                    LineString: An empty line string.

                Example:
                    >>> empty_line = LineString.empty()
                    >>> empty_line.is_empty()  # True
            )doc"
        )

        .def(
            "__len__",
            &LineString::getPointCount,
            R"doc(
                Get the number of points in the line string (Python len() function).

                Returns:
                    int: The number of points.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0)]
                    >>> line_string = LineString(points)
                    >>> len(line_string)  # 2
            )doc"
        )
        .def(
            "__getitem__",
            +[](const LineString& aLineString, const size_t anIndex) -> const Point&
            {
                return aLineString.accessPointAt(anIndex);
            },
            R"doc(
                Access a point by index (Python indexing support).

                Args:
                    index (int): The index of the point to access.

                Returns:
                    Point: The point at the specified index.

                Raises:
                    IndexError: If the index is out of range.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0)]
                    >>> line_string = LineString(points)
                    >>> first_point = line_string[0]  # Point(0.0, 0.0)
            )doc",
            return_value_policy::reference_internal,
            arg("index")
        )
        .def(
            "__iter__",
            [](const LineString& aLineString)
            {
                return make_iterator(aLineString.begin(), aLineString.end());
            },
            R"doc(
                Make the line string iterable (Python for loop support).

                Returns:
                    iterator: An iterator over the points in the line string.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0)]
                    >>> line_string = LineString(points)
                    >>> for point in line_string:
                    ...     print(point)
            )doc",
            keep_alive<0, 1>()
        )  // Keep vector alive while iterator is used

        ;
}
