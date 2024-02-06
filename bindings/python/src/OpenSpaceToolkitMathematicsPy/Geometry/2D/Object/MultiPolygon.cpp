/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/MultiPolygon.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_2D_Object_MultiPolygon(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Integer;
    using ostk::core::container::Array;

    using ostk::mathematics::object::Vector2d;
    using ostk::mathematics::geometry::d2::Object;
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::PointSet;
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::MultiPolygon;

    class_<MultiPolygon, Object>(aModule, "MultiPolygon")

        .def(init<const Array<Polygon>&>(), arg("polygons"))

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<MultiPolygon>))
        .def("__repr__", &(shiftToString<MultiPolygon>))

        .def("is_defined", &MultiPolygon::isDefined)
        .def("contains", overload_cast<const Point&>(&MultiPolygon::contains, const_), arg("point"))
        .def("contains", overload_cast<const PointSet&>(&MultiPolygon::contains, const_), arg("point_set"))

        .def("get_polygon_count", &MultiPolygon::getPolygonCount)
        .def("get_polygons", &MultiPolygon::getPolygons)
        .def("get_convex_hull", &MultiPolygon::getConvexHull)
        .def("union_with", &MultiPolygon::unionWith, arg("multipolygon"))
        .def(
            "to_string",
            &MultiPolygon::toString,
            arg("format") = Object::Format::Standard,
            arg("precision") = Integer::Undefined()
        )
        .def("apply_transformation", &MultiPolygon::applyTransformation, arg("transformation"))

        .def_static("undefined", &MultiPolygon::Undefined)
        .def_static("polygon", &MultiPolygon::Polygon, arg("polygon"))

        ;
}
