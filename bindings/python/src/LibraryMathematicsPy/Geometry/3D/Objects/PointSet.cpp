////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/PointSet.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/PointSet.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_PointSet ( )
{

    using namespace boost::python ;

    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d3::Object ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::PointSet ;

    scope in_PointSet = class_<PointSet, bases<Object>>("PointSet", init<const Array<Point>&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &PointSet::isDefined)
        .def("isEmpty", &PointSet::isEmpty)
        .def("isNear", &PointSet::isNear)

        .def("getSize", &PointSet::getSize)
        .def("getPointClosestTo", &PointSet::getPointClosestTo)
        .def("applyTransformation", &PointSet::applyTransformation)

        .def("Empty", &PointSet::Empty).staticmethod("Empty")

        .def("__iter__", boost::python::range(static_cast<PointSet::ConstIterator (PointSet::*)() const> (&PointSet::begin), static_cast<PointSet::ConstIterator (PointSet::*)() const> (&PointSet::end)))

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
