// Copyright © Loft Orbital Solutions Inc.

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/PointSet.hpp>


inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_PointSet (      pybind11::module& aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d3::Object ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::PointSet ;

    class_<PointSet, Object>(aModule, "PointSet")

        .def(init<const Array<Point>&>(), arg("points"))

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<PointSet>))
        .def("__repr__", &(shiftToString<PointSet>))

        .def("is_defined", &PointSet::isDefined)
        .def("is_empty", &PointSet::isEmpty)
        .def("is_near", &PointSet::isNear, arg("point_set"), arg("tolerance"))

        .def("get_size", &PointSet::getSize)
        .def("distance_to", overload_cast<const Point&>(&PointSet::distanceTo, const_), arg("point"))
        .def("get_point_closest_to", &PointSet::getPointClosestTo, arg("point"))
        .def("apply_transformation", &PointSet::applyTransformation, arg("transformation"))

        .def_static("empty", &PointSet::Empty)

        // .def_static("__iter__", boost::python::range(static_cast<PointSet::ConstIterator (PointSet::*)() const> (&PointSet::begin), static_cast<PointSet::ConstIterator (PointSet::*)() const> (&PointSet::end)))

    ;

}

