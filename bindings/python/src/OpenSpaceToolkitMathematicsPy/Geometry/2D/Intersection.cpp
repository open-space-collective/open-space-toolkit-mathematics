/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Intersection.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_2D_Intersection(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::container::Array;
    using ostk::core::type::Unique;

    using ostk::mathematics::geometry::d2::Intersection;
    using ostk::mathematics::geometry::d2::Object;
    using ostk::mathematics::geometry::d2::object::Composite;
    using ostk::mathematics::geometry::d2::object::Line;
    using ostk::mathematics::geometry::d2::object::LineString;
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::PointSet;
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::Segment;

    class_<Intersection> intersection(aModule, "Intersection");

    intersection

        .def(self == self)
        .def(self != self)

        .def(self + self)
        .def(self += self)

        .def("__str__", &(shiftToString<Intersection>))
        .def("__repr__", &(shiftToString<Intersection>))

        .def(
            "is_defined",
            &Intersection::isDefined,
            R"doc(
                Check if the intersection is defined.

                Returns:
                    bool: True if the intersection is defined, False otherwise.

                Example:
                    >>> intersection = Intersection.point(Point(1.0, 2.0))
                    >>> intersection.is_defined()  # True
            )doc"
        )
        .def(
            "is_empty",
            &Intersection::isEmpty,
            R"doc(
                Check if the intersection is empty (no geometric objects).

                Returns:
                    bool: True if the intersection is empty, False otherwise.

                Example:
                    >>> empty_intersection = Intersection.empty()
                    >>> empty_intersection.is_empty()  # True
            )doc"
        )
        .def(
            "is_complex",
            &Intersection::isComplex,
            R"doc(
                Check if the intersection is complex (contains multiple different types).

                Returns:
                    bool: True if the intersection is complex, False otherwise.

                Example:
                    >>> # Complex intersections contain multiple geometric types
                    >>> intersection.is_complex()
            )doc"
        )

        .def(
            "is_point",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Point>();
            },
            R"doc(
                Check if the intersection contains a Point.

                Returns:
                    bool: True if the intersection contains a Point, False otherwise.

                Example:
                    >>> intersection = Intersection.point(Point(1.0, 2.0))
                    >>> intersection.is_point()  # True
            )doc"
        )
        .def(
            "is_point_set",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<PointSet>();
            },
            R"doc(
                Check if the intersection contains a PointSet.

                Returns:
                    bool: True if the intersection contains a PointSet, False otherwise.

                Example:
                    >>> points = PointSet([Point(1.0, 2.0), Point(3.0, 4.0)])
                    >>> intersection = Intersection.point_set(points)
                    >>> intersection.is_point_set()  # True
            )doc"
        )
        .def(
            "is_line",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Line>();
            },
            R"doc(
                Check if the intersection contains a Line.

                Returns:
                    bool: True if the intersection contains a Line, False otherwise.

                Example:
                    >>> line = Line(Point(0.0, 0.0), np.array([1.0, 1.0]))
                    >>> intersection = Intersection.line(line)
                    >>> intersection.is_line()  # True
            )doc"
        )
        .def(
            "is_segment",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Segment>();
            },
            R"doc(
                Check if the intersection contains a Segment.

                Returns:
                    bool: True if the intersection contains a Segment, False otherwise.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0), Point(1.0, 1.0))
                    >>> intersection = Intersection.segment(segment)
                    >>> intersection.is_segment()  # True
            )doc"
        )
        .def(
            "is_line_string",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<LineString>();
            },
            R"doc(
                Check if the intersection contains a LineString.

                Returns:
                    bool: True if the intersection contains a LineString, False otherwise.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0), Point(2.0, 2.0)]
                    >>> line_string = LineString(points)
                    >>> # intersection = Intersection.line_string(line_string)
                    >>> # intersection.is_line_string()  # True
            )doc"
        )
        .def(
            "is_polygon",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Polygon>();
            },
            R"doc(
                Check if the intersection contains a Polygon.

                Returns:
                    bool: True if the intersection contains a Polygon, False otherwise.

                Example:
                    >>> vertices = [Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0)]
                    >>> polygon = Polygon(vertices)
                    >>> # intersection = Intersection.polygon(polygon)
                    >>> # intersection.is_polygon()  # True
            )doc"
        )
        .def(
            "is_composite",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Composite>();
            },
            R"doc(
                Check if the intersection contains a Composite.

                Returns:
                    bool: True if the intersection contains a Composite, False otherwise.

                Example:
                    >>> composite = Composite(Point(1.0, 2.0))
                    >>> # intersection = Intersection.composite(composite)
                    >>> # intersection.is_composite()  # True
            )doc"
        )

        .def(
            "as_point",
            +[](const Intersection& anIntersection) -> Point
            {
                return anIntersection.as<Point>();
            },
            R"doc(
                Convert the intersection to a Point.

                Returns:
                    Point: The point contained in the intersection.

                Raises:
                    RuntimeError: If the intersection does not contain a Point.

                Example:
                    >>> intersection = Intersection.point(Point(1.0, 2.0))
                    >>> point = intersection.as_point()
            )doc"
        )
        .def(
            "as_point_set",
            +[](const Intersection& anIntersection) -> PointSet
            {
                return anIntersection.as<PointSet>();
            },
            R"doc(
                Convert the intersection to a PointSet.

                Returns:
                    PointSet: The point set contained in the intersection.

                Raises:
                    RuntimeError: If the intersection does not contain a PointSet.

                Example:
                    >>> points = PointSet([Point(1.0, 2.0), Point(3.0, 4.0)])
                    >>> intersection = Intersection.point_set(points)
                    >>> point_set = intersection.as_point_set()
            )doc"
        )
        .def(
            "as_line",
            +[](const Intersection& anIntersection) -> Line
            {
                return anIntersection.as<Line>();
            },
            R"doc(
                Convert the intersection to a Line.

                Returns:
                    Line: The line contained in the intersection.

                Raises:
                    RuntimeError: If the intersection does not contain a Line.

                Example:
                    >>> line = Line(Point(0.0, 0.0), np.array([1.0, 1.0]))
                    >>> intersection = Intersection.line(line)
                    >>> extracted_line = intersection.as_line()
            )doc"
        )
        .def(
            "as_segment",
            +[](const Intersection& anIntersection) -> Segment
            {
                return anIntersection.as<Segment>();
            },
            R"doc(
                Convert the intersection to a Segment.

                Returns:
                    Segment: The segment contained in the intersection.

                Raises:
                    RuntimeError: If the intersection does not contain a Segment.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0), Point(1.0, 1.0))
                    >>> intersection = Intersection.segment(segment)
                    >>> extracted_segment = intersection.as_segment()
            )doc"
        )
        .def(
            "as_line_string",
            +[](const Intersection& anIntersection) -> LineString
            {
                return anIntersection.as<LineString>();
            },
            R"doc(
                Convert the intersection to a LineString.

                Returns:
                    LineString: The line string contained in the intersection.

                Raises:
                    RuntimeError: If the intersection does not contain a LineString.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0), Point(2.0, 2.0)]
                    >>> line_string = LineString(points)
                    >>> # intersection = Intersection.line_string(line_string)
                    >>> # extracted_line_string = intersection.as_line_string()
            )doc"
        )
        .def(
            "as_polygon",
            +[](const Intersection& anIntersection) -> Polygon
            {
                return anIntersection.as<Polygon>();
            },
            R"doc(
                Convert the intersection to a Polygon.

                Returns:
                    Polygon: The polygon contained in the intersection.

                Raises:
                    RuntimeError: If the intersection does not contain a Polygon.

                Example:
                    >>> vertices = [Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0)]
                    >>> polygon = Polygon(vertices)
                    >>> # intersection = Intersection.polygon(polygon)
                    >>> # extracted_polygon = intersection.as_polygon()
            )doc"
        )
        .def(
            "as_composite",
            +[](const Intersection& anIntersection) -> Composite
            {
                return anIntersection.as<Composite>();
            },
            R"doc(
                Convert the intersection to a Composite.

                Returns:
                    Composite: The composite contained in the intersection.

                Raises:
                    RuntimeError: If the intersection does not contain a Composite.

                Example:
                    >>> composite = Composite(Point(1.0, 2.0))
                    >>> # intersection = Intersection.composite(composite)
                    >>> # extracted_composite = intersection.as_composite()
            )doc"
        )

        .def(
            "access_composite",
            &Intersection::accessComposite,
            R"doc(
                Access the composite representation of the intersection.

                Returns:
                    Composite: Reference to the composite containing all intersection objects.

                Example:
                    >>> intersection = Intersection.point(Point(1.0, 2.0))
                    >>> composite = intersection.access_composite()
            )doc",
            return_value_policy::reference
        )

        .def(
            "get_type",
            &Intersection::getType,
            R"doc(
                Get the type of the intersection.

                Returns:
                    Intersection.Type: The type of geometry contained in the intersection.

                Example:
                    >>> intersection = Intersection.point(Point(1.0, 2.0))
                    >>> intersection.get_type()  # Intersection.Type.Point
            )doc"
        )

        // Define static methods
        .def_static(
            "undefined",
            &Intersection::Undefined,
            R"doc(
                Create an undefined intersection.

                Returns:
                    Intersection: An undefined intersection.

                Example:
                    >>> undefined_intersection = Intersection.undefined()
                    >>> undefined_intersection.is_defined()  # False
            )doc"
        )
        .def_static(
            "empty",
            &Intersection::Empty,
            R"doc(
                Create an empty intersection.

                Returns:
                    Intersection: An empty intersection containing no geometry.

                Example:
                    >>> empty_intersection = Intersection.empty()
                    >>> empty_intersection.is_empty()  # True
            )doc"
        )
        .def_static(
            "point",
            &Intersection::Point,
            R"doc(
                Create an intersection containing a single point.

                Args:
                    point (Point): The point to include in the intersection.

                Returns:
                    Intersection: An intersection containing the point.

                Example:
                    >>> point = Point(1.0, 2.0)
                    >>> intersection = Intersection.point(point)
            )doc",
            arg("point")
        )
        .def_static(
            "point_set",
            &Intersection::PointSet,
            R"doc(
                Create an intersection containing a point set.

                Args:
                    point_set (PointSet): The point set to include in the intersection.

                Returns:
                    Intersection: An intersection containing the point set.

                Example:
                    >>> points = PointSet([Point(1.0, 2.0), Point(3.0, 4.0)])
                    >>> intersection = Intersection.point_set(points)
            )doc",
            arg("point_set")
        )
        .def_static(
            "line",
            &Intersection::Line,
            R"doc(
                Create an intersection containing a line.

                Args:
                    line (Line): The line to include in the intersection.

                Returns:
                    Intersection: An intersection containing the line.

                Example:
                    >>> line = Line(Point(0.0, 0.0), np.array([1.0, 1.0]))
                    >>> intersection = Intersection.line(line)
            )doc",
            arg("line")
        )
        .def_static(
            "segment",
            &Intersection::Segment,
            R"doc(
                Create an intersection containing a segment.

                Args:
                    segment (Segment): The segment to include in the intersection.

                Returns:
                    Intersection: An intersection containing the segment.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0), Point(1.0, 1.0))
                    >>> intersection = Intersection.segment(segment)
            )doc",
            arg("segment")
        )

        .def_static(
            "string_from_type",
            &Intersection::StringFromType,
            R"doc(
                Get the string representation of an intersection type.

                Args:
                    type (Intersection.Type): The intersection type.

                Returns:
                    str: String representation of the type.

                Example:
                    >>> Intersection.string_from_type(Intersection.Type.Point)  # "Point"
            )doc",
            arg("type")
        )

        ;

    // Define Intersection types
    enum_<Intersection::Type>(intersection, "Type")

        .value("Undefined", Intersection::Type::Undefined)
        .value("Empty", Intersection::Type::Empty)
        .value("Point", Intersection::Type::Point)
        .value("PointSet", Intersection::Type::PointSet)
        .value("Line", Intersection::Type::Line)
        .value("LineString", Intersection::Type::LineString)
        .value("Segment", Intersection::Type::Segment)
        .value("Polygon", Intersection::Type::Polygon)
        .value("Complex", Intersection::Type::Complex)

        ;
}
