/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Line.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Line(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::types::Real;

    using ostk::math::object::Vector3d;
    using ostk::math::geometry::d3::Object;
    using ostk::math::geometry::d3::objects::Point;
    using ostk::math::geometry::d3::objects::PointSet;
    using ostk::math::geometry::d3::objects::Line;
    using ostk::math::geometry::d3::objects::Plane;
    using ostk::math::geometry::d3::objects::Sphere;
    using ostk::math::geometry::d3::objects::Ellipsoid;
    using ostk::math::geometry::d3::Intersection;

    class_<Line, Object>(aModule, "Line")

        .def(init<const Point&, const Vector3d&>(), arg("origin"), arg("direction"))

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Line>))
        .def("__repr__", &(shiftToString<Line>))

        .def("is_defined", &Line::isDefined)
        .def("intersects", overload_cast<const Point&>(&Line::intersects, const_), arg("point"))
        .def("intersects", overload_cast<const Plane&>(&Line::intersects, const_), arg("plane"))
        .def("intersects", overload_cast<const Sphere&>(&Line::intersects, const_), arg("sphere"))
        .def("intersects", overload_cast<const Ellipsoid&>(&Line::intersects, const_), arg("ellipsoid"))
        .def("contains", overload_cast<const Point&>(&Line::contains, const_), arg("point"))
        .def("contains", overload_cast<const PointSet&>(&Line::contains, const_), arg("point_set"))

        .def("get_origin", &Line::getOrigin)
        .def("get_direction", &Line::getDirection)
        .def("distance_to", overload_cast<const Point&>(&Line::distanceTo, const_), arg("point"))
        .def("intersection_with", overload_cast<const Plane&>(&Line::intersectionWith, const_), arg("plane"))
        .def("apply_transformation", &Line::applyTransformation, arg("transformation"))

        .def_static("undefined", &Line::Undefined)
        .def_static("points", &Line::Points, arg("first_point"), arg("second_point"))

        ;
}
