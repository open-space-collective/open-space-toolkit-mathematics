/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/PointSet.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_PointSet(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Integer;
    using ostk::core::container::Array;

    using ostk::math::geometry::d2::Object;
    using ostk::math::geometry::d2::objects::Point;
    using ostk::math::geometry::d2::objects::PointSet;

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
        .def(
            "to_string",
            &PointSet::toString,
            arg("format") = Object::Format::Standard,
            arg("precision") = Integer::Undefined()
        )
        .def("apply_transformation", &PointSet::applyTransformation, arg("transformation"))

        .def_static("empty", &PointSet::Empty)

        .def("__len__", &PointSet::getSize)
        .def(
            "__iter__",
            [](const PointSet& aPointSet)
            {
                return make_iterator(aPointSet.begin(), aPointSet.end());
            },
            keep_alive<0, 1>()
        )  // Keep vector alive while iterator is used

        ;
}
