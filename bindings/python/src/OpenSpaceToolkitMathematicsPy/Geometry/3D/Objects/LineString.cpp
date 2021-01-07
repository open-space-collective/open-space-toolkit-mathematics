////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/LineString.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/LineString.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_LineString                     (           pybind11::module& aModule         )
{

    using namespace pybind11 ;

    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d3::Object ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::LineString ;

    class_<LineString, Object>(aModule, "LineString")

        .def(init<const Array<Point>&>())

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shift_to_string<LineString>))
        .def("__repr__", &(shift_to_string<LineString>))

        .def("is_defined", &LineString::isDefined)
        .def("is_empty", &LineString::isEmpty)
        .def("is_near", &LineString::isNear)

        .def("get_point_count", &LineString::getPointCount)
        .def("get_point_closest_to", &LineString::getPointClosestTo)
        .def("apply_transformation", &LineString::applyTransformation)

        .def_static("empty", &LineString::Empty)

        // .def("__iter__", boost::python::range(static_cast<LineString::ConstIterator (LineString::*)() const> (&LineString::begin), static_cast<LineString::ConstIterator (LineString::*)() const> (&LineString::end)))

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
