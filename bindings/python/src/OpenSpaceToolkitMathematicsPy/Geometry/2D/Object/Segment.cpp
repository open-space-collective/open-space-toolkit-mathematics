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

        .def(init<const Point&, const Point&>(), arg("start_point"), arg("end_point"))

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Segment>))
        .def("__repr__", &(shiftToString<Segment>))

        .def("is_defined", &Segment::isDefined)
        .def("is_degenerate", &Segment::isDegenerate)

        .def("get_first_point", &Segment::getFirstPoint)
        .def("get_second_point", &Segment::getSecondPoint)
        .def("get_center", &Segment::getCenter)
        .def("get_direction", &Segment::getDirection)
        .def("get_length", &Segment::getLength)
        .def("distance_to", overload_cast<const Point&>(&Segment::distanceTo, const_), arg("point"))
        .def("distance_to", overload_cast<const PointSet&>(&Segment::distanceTo, const_), arg("point_set"))
        .def("to_line", &Segment::toLine)
        .def(
            "to_string",
            &Segment::toString,
            arg("format") = Object::Format::Standard,
            arg("precision") = Integer::Undefined()
        )
        .def("apply_transformation", &Segment::applyTransformation, arg("transformation"))

        .def_static("undefined", &Segment::Undefined)

        ;
}
