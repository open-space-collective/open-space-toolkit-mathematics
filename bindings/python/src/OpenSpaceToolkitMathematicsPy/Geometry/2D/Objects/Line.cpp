/// Apache License 2.0 

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Line.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_Line(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::types::Real;

    using ostk::math::obj::Vector2d;
    using ostk::math::geom::d2::Object;
    using ostk::math::geom::d2::objects::Point;
    using ostk::math::geom::d2::objects::PointSet;
    using ostk::math::geom::d2::objects::Line;

    class_<Line, Object>(aModule, "Line")

        .def(init<const Point&, const Vector2d&>(), arg("point"), arg("direction"))

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Line>))
        .def("__repr__", &(shiftToString<Line>))

        .def("is_defined", &Line::isDefined)
        .def("intersects", overload_cast<const Point&>(&Line::intersects, const_), arg("point"))
        .def("contains", overload_cast<const Point&>(&Line::contains, const_), arg("point"))
        .def("contains", overload_cast<const PointSet&>(&Line::contains, const_), arg("point_set"))

        .def("get_origin", &Line::getOrigin)
        .def("get_direction", &Line::getDirection)
        .def("distance_to", overload_cast<const Point&>(&Line::distanceTo, const_), arg("point"))
        .def("apply_transformation", &Line::applyTransformation, arg("transformation"))

        .def_static("undefined", &Line::Undefined)
        .def_static("points", &Line::Points, arg("first_point"), arg("second_point"))

        ;
}
