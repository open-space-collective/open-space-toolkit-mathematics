////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           LibraryMathematicsPy/Geometry/3D/Objects/LineString.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/LineString.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_3D_Objects_LineString ( )
{

    using namespace boost::python ;

    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d3::Object ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::LineString ;

    scope in_LineString = class_<LineString, bases<Object>>("LineString", init<const Array<Point>&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &LineString::isDefined)
        .def("isEmpty", &LineString::isEmpty)
        .def("isNear", &LineString::isNear)

        .def("getPointCount", &LineString::getPointCount)
        .def("getPointClosestTo", &LineString::getPointClosestTo)
        .def("applyTransformation", &LineString::applyTransformation)

        .def("Empty", &LineString::Empty).staticmethod("Empty")

        .def("__iter__", boost::python::range(static_cast<LineString::ConstIterator (LineString::*)() const> (&LineString::begin), static_cast<LineString::ConstIterator (LineString::*)() const> (&LineString::end)))

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
