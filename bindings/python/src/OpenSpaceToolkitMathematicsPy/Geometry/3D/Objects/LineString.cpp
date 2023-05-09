// Copyright © Loft Orbital Solutions Inc.

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/LineString.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_LineString (    pybind11::module& aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d3::Object ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::LineString ;

    class_<LineString, Object>(aModule, "LineString")

        .def(init<const Array<Point>&>(), arg("points"))

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<LineString>))
        .def("__repr__", &(shiftToString<LineString>))

        .def("is_defined", &LineString::isDefined)
        .def("is_empty", &LineString::isEmpty)
        .def("is_near", &LineString::isNear, arg("line_string"), arg("tolerance"))

        .def("access_point_at", &LineString::accessPointAt, arg("index"), return_value_policy::reference)

        .def("get_point_count", &LineString::getPointCount)
        .def("get_point_closest_to", &LineString::getPointClosestTo, arg("point"))
        .def("apply_transformation", &LineString::applyTransformation, arg("transformation"))

        .def_static("empty", &LineString::Empty)
        .def_static("segment", &LineString::Segment, arg("segment"))

        .def("__len__", &LineString::getPointCount)
        .def("__getitem__", +[] (const LineString& aLineString, const size_t anIndex) -> const Point& { return aLineString.accessPointAt(anIndex) ; }, return_value_policy::reference_internal)
        .def("__iter__", [] (const LineString& aLineString) {return make_iterator(aLineString.begin(), aLineString.end()) ; }, keep_alive<0, 1>()) // Keep vector alive while iterator is used

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
