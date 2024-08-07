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

        .def(init<const Point&, const Point&>(), arg("first_point"), arg("second_point"))

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Segment>))
        .def("__repr__", &(shiftToString<Segment>))

        .def("is_defined", &Segment::isDefined)
        .def("is_degenerate", &Segment::isDegenerate)
        .def("intersects", overload_cast<const Plane&>(&Segment::intersects, const_), arg("plane"))
        .def("intersects", overload_cast<const Sphere&>(&Segment::intersects, const_), arg("sphere"))
        .def("intersects", overload_cast<const Ellipsoid&>(&Segment::intersects, const_), arg("ellipsoid"))
        .def("contains", overload_cast<const Point&>(&Segment::contains, const_), arg("point"))

        .def("get_first_point", &Segment::getFirstPoint)
        .def("get_second_point", &Segment::getSecondPoint)
        .def("get_center", &Segment::getCenter)
        .def("get_direction", &Segment::getDirection)
        .def("get_length", &Segment::getLength)
        .def("distance_to", overload_cast<const Point&>(&Segment::distanceTo, const_), arg("point"))
        .def("distance_to", overload_cast<const PointSet&>(&Segment::distanceTo, const_), arg("point_set"))
        .def("intersection_with", overload_cast<const Plane&>(&Segment::intersectionWith, const_), arg("plane"))
        .def("to_line", &Segment::toLine)
        .def("apply_transformation", &Segment::applyTransformation, arg("transformation"))

        .def_static("undefined", &Segment::Undefined);
}
