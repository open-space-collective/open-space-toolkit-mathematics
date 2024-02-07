/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Type/Shared.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Composite.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_2D_Object_Composite(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::d2::Object;
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::PointSet;
    using ostk::mathematics::geometry::d2::object::Line;
    using ostk::mathematics::geometry::d2::object::Segment;
    using ostk::mathematics::geometry::d2::object::LineString;
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::Composite;
    using ostk::mathematics::geometry::d2::Intersection;

    class_<Composite, Object>(aModule, "Composite")

        .def(init<const Object&>(), arg("object"))

        .def(self == self)
        .def(self != self)

        .def(self + self)
        .def(self += self)

        .def("__str__", &(shiftToString<Composite>))
        .def("__repr__", &(shiftToString<Composite>))

        .def("is_defined", &Composite::isDefined)
        .def("is_empty", &Composite::isEmpty)

        .def(
            "is_point",
            +[](const Composite& aComposite) -> bool
            {
                return aComposite.is<Point>();
            }
        )
        .def(
            "is_point_set",
            +[](const Composite& aComposite) -> bool
            {
                return aComposite.is<PointSet>();
            }
        )
        .def(
            "is_line",
            +[](const Composite& aComposite) -> bool
            {
                return aComposite.is<Line>();
            }
        )
        .def(
            "is_segment",
            +[](const Composite& aComposite) -> bool
            {
                return aComposite.is<Segment>();
            }
        )
        .def(
            "is_line_string",
            +[](const Composite& aComposite) -> bool
            {
                return aComposite.is<LineString>();
            }
        )
        .def(
            "is_polygon",
            +[](const Composite& aComposite) -> bool
            {
                return aComposite.is<Polygon>();
            }
        )
        .def(
            "is_composite",
            +[](const Composite& aComposite) -> bool
            {
                return aComposite.is<Composite>();
            }
        )

        .def("intersects", overload_cast<const Object&>(&Composite::intersects, const_), arg("object"))
        .def("intersects", overload_cast<const Composite&>(&Composite::intersects, const_), arg("composite"))
        .def("contains", overload_cast<const Object&>(&Composite::contains, const_), arg("object"))
        .def("contains", overload_cast<const Composite&>(&Composite::contains, const_), arg("composite"))
        .def("any_contains", overload_cast<const Object&>(&Composite::anyContains, const_), arg("object"))
        .def("any_contains", overload_cast<const Composite&>(&Composite::anyContains, const_), arg("composite"))

        .def(
            "as_point",
            +[](const Composite& aComposite) -> Point
            {
                return aComposite.as<Point>();
            }
        )
        .def(
            "as_point_set",
            +[](const Composite& aComposite) -> PointSet
            {
                return aComposite.as<PointSet>();
            }
        )
        .def(
            "as_line",
            +[](const Composite& aComposite) -> Line
            {
                return aComposite.as<Line>();
            }
        )
        .def(
            "as_segment",
            +[](const Composite& aComposite) -> Segment
            {
                return aComposite.as<Segment>();
            }
        )
        .def(
            "as_line_string",
            +[](const Composite& aComposite) -> LineString
            {
                return aComposite.as<LineString>();
            }
        )
        .def(
            "as_polygon",
            +[](const Composite& aComposite) -> Polygon
            {
                return aComposite.as<Polygon>();
            }
        )
        .def(
            "as_composite",
            +[](const Composite& aComposite) -> Composite
            {
                return aComposite.as<Composite>();
            }
        )

        .def("access_object_at", &Composite::accessObjectAt, return_value_policy::reference, arg("index"))

        .def("get_object_count", &Composite::getObjectCount)
        // .def("intersection_with", overload_cast<const Object&>(&Composite::intersectionWith, const_))
        // .def("intersection_with", overload_cast<const Composite&>(&Composite::intersectionWith, const_))

        .def("apply_transformation", &Composite::applyTransformation, arg("transformation"))

        .def_static("undefined", &Composite::Undefined)
        .def_static("empty", &Composite::Empty)

        ;
}
