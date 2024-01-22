/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Intersection.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_2D_Intersection(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::types::Unique;
    using ostk::core::ctnr::Array;

    using ostk::mathematics::geometry::d2::Object;
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::PointSet;
    using ostk::mathematics::geometry::d2::object::Line;
    using ostk::mathematics::geometry::d2::object::Segment;
    using ostk::mathematics::geometry::d2::object::LineString;
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::Composite;
    using ostk::mathematics::geometry::d2::Intersection;

    class_<Intersection> intersection(aModule, "Intersection");

    intersection

        .def(self == self)
        .def(self != self)

        .def(self + self)
        .def(self += self)

        .def("__str__", &(shiftToString<Intersection>))
        .def("__repr__", &(shiftToString<Intersection>))

        .def("is_defined", &Intersection::isDefined)
        .def("is_empty", &Intersection::isEmpty)
        .def("is_complex", &Intersection::isComplex)

        .def(
            "is_point",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Point>();
            }
        )
        .def(
            "is_point_set",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<PointSet>();
            }
        )
        .def(
            "is_line",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Line>();
            }
        )
        .def(
            "is_segment",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Segment>();
            }
        )
        .def(
            "is_line_string",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<LineString>();
            }
        )
        .def(
            "is_polygon",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Polygon>();
            }
        )
        .def(
            "is_composite",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Composite>();
            }
        )

        .def(
            "as_point",
            +[](const Intersection& anIntersection) -> Point
            {
                return anIntersection.as<Point>();
            }
        )
        .def(
            "as_point_set",
            +[](const Intersection& anIntersection) -> PointSet
            {
                return anIntersection.as<PointSet>();
            }
        )
        .def(
            "as_line",
            +[](const Intersection& anIntersection) -> Line
            {
                return anIntersection.as<Line>();
            }
        )
        .def(
            "as_segment",
            +[](const Intersection& anIntersection) -> Segment
            {
                return anIntersection.as<Segment>();
            }
        )
        .def(
            "as_line_string",
            +[](const Intersection& anIntersection) -> LineString
            {
                return anIntersection.as<LineString>();
            }
        )
        .def(
            "as_polygon",
            +[](const Intersection& anIntersection) -> Polygon
            {
                return anIntersection.as<Polygon>();
            }
        )
        .def(
            "as_composite",
            +[](const Intersection& anIntersection) -> Composite
            {
                return anIntersection.as<Composite>();
            }
        )

        .def("access_composite", &Intersection::accessComposite, return_value_policy::reference)

        .def("get_type", &Intersection::getType)

        // Define static methods
        .def_static("undefined", &Intersection::Undefined)
        .def_static("empty", &Intersection::Empty)
        .def_static("point", &Intersection::Point, arg("point"))
        .def_static("point_set", &Intersection::PointSet, arg("point_set"))
        .def_static("line", &Intersection::Line, arg("line"))
        .def_static("segment", &Intersection::Segment, arg("segment"))

        .def_static("string_from_type", &Intersection::StringFromType)

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
