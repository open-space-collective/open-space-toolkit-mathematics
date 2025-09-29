/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/LineString.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_LineString(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::container::Array;

    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::LineString;
    using ostk::mathematics::geometry::d3::object::Point;

    class_<LineString, Object>(
        aModule,
        "LineString",
        R"doc(
                A sequence of connected line segments in 3D space.

                A LineString is an ordered sequence of points forming a polyline.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0)]
                    >>> line_string = LineString(points)
                    >>> line_string.is_defined()  # True
            )doc"
    )

        .def(
            init<const Array<Point>&>(),
            R"doc(
                Construct a line string from an array of points.
                
                Args:
                points (list[Point]): Array of 3D points defining the line string.
                
                Example:
                >>> points = [Point(0.0, 0.0), Point(1.0, 1.0)]
                >>> line_string = LineString(points)
                >>> line_string.is_defined()  # True
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
                    bool: True if the line string is defined.

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
                Check if the line string is empty.

                Returns:
                    bool: True if the line string contains no points.

                Example:
                    >>> line_string = LineString.empty()
                    >>> line_string.is_empty()  # True
            )doc"
        )
        .def(
            "is_near",
            &LineString::isNear,
            R"doc(
                Check if another line string is near this one within a tolerance.
                
                Args:
                line_string (LineString): The line string to compare against.
                tolerance (float): The maximum distance for points to be considered near.
                
                Returns:
                bool: True if the line strings are near each other.
                
                Example:
                >>> line_string = LineString(points)
                >>> line_string.is_near(LineString(points), 0.1)  # True
            )doc",
            arg("line_string"),
            arg("tolerance")
        )

        .def(
            "access_point_at",
            &LineString::accessPointAt,
            return_value_policy::reference,
            R"doc(
                Access a point at a given index.

                Args:
                    index (int): The index of the point.

                Returns:
                    Point: Reference to the point at the index.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0)]
                    >>> line_string = LineString(points)
                    >>> line_string.access_point_at(0)  # Point(0.0, 0.0)
            )doc",
            arg("index")
        )

        .def(
            "get_point_count",
            &LineString::getPointCount,
            R"doc(
                Get the number of points in the line string.

                Returns:
                    int: The number of points.
                
                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0)]
                    >>> line_string = LineString(points)
                    >>> line_string.get_point_count()  # 2
            )doc"
        )
        .def(
            "get_point_closest_to",
            &LineString::getPointClosestTo,
            R"doc(
                Get the point in the line string closest to a given point.

                Args:
                    point (Point): The reference point.

                Returns:
                    Point: The closest point in the line string.
                
                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0)]
                    >>> line_string = LineString(points)
                    >>> line_string.get_point_closest_to(Point(0.5, 0.5))  # Point(0.5, 0.5)
            )doc",
            arg("point")
        )
        .def(
            "apply_transformation",
            &LineString::applyTransformation,
            R"doc(
                Apply a transformation to all points in the line string.
                
                Args:
                    transformation (Transformation): The transformation to apply.
                
                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0)]
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
                    >>> line_string = LineString.empty()
                    >>> line_string.is_empty()  # True
            )doc"
        )
        .def_static(
            "segment",
            &LineString::Segment,
            R"doc(
                Create a line string from a segment.

                Args:
                    segment (Segment): The segment to convert.

                Returns:
                    LineString: A line string representing the segment.
                
                Example:
                    >>> segment = Segment(Point(0.0, 0.0, 0.0), Point(1.0, 1.0, 1.0))
                    >>> line_string = LineString.segment(segment)
                    >>> line_string.is_defined()  # True
            )doc",
            arg("segment")
        )

        .def("__len__", &LineString::getPointCount)
        .def(
            "__getitem__",
            +[](const LineString& aLineString, const size_t anIndex) -> const Point&
            {
                return aLineString.accessPointAt(anIndex);
            },
            return_value_policy::reference_internal,
            arg("index")
        )
        .def(
            "__iter__",
            [](const LineString& aLineString)
            {
                return make_iterator(aLineString.begin(), aLineString.end());
            },
            keep_alive<0, 1>()
        )  // Keep vector alive while iterator is used

        ;
}
