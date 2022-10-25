////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/LineString.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/LineString.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_LineString  (  pybind11::module&  aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::types::Integer ;
    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d2::Object ;
    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::LineString ;

    class_<LineString, Object>(aModule, "LineString")

        .def(init<const Array<Point>&>(), arg("points"))

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<LineString>))
        .def("__repr__", &(shiftToString<LineString>))

        .def("is_defined", &LineString::isDefined)
        .def("is_empty", &LineString::isEmpty)
        .def("is_near", &LineString::isNear, arg("line_string"), arg("tolerance"))

        .def("get_point_count", &LineString::getPointCount)
        .def("get_point_closest_to", &LineString::getPointClosestTo, arg("point"))
        .def("to_string", &LineString::toString, arg("format") = Object::Format::Standard, arg("precision") = Integer::Undefined())

        .def("apply_transformation", &LineString::applyTransformation, arg("transformation"))

        .def_static("empty", &LineString::Empty)

        .def("__len__", &LineString::getPointCount)
        .def("__getitem__", +[] (const LineString& aLineString, const size_t anIndex) -> const Point& { return aLineString.accessPointAt(anIndex) ; }, return_value_policy::reference_internal, arg("index"))
        .def("__iter__", [] (const LineString& aLineString) {return make_iterator(aLineString.begin(), aLineString.end()) ; }, keep_alive<0, 1>()) // Keep vector alive while iterator is used

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
