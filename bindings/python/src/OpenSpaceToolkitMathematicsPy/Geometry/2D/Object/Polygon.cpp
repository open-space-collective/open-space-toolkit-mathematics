/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Polygon.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_2D_Object_Polygon(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::container::Array;
    using ostk::core::type::Integer;

    using ostk::mathematics::geometry::d2::Object;
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::PointSet;
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::object::Vector2d;

    class_<Polygon, Object>(aModule, "Polygon")

        .def(init<const Array<Point>&, const Array<Array<Point>>&>(), arg("outer_ring"), arg("inner_rings"))

        .def(init<const Array<Point>&>(), arg("outer_ring"))

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Polygon>))
        .def("__repr__", &(shiftToString<Polygon>))

        .def("is_defined", &Polygon::isDefined)
        .def("is_near", &Polygon::isNear, arg("polygon"), arg("tolerance"))
        .def("intersects", overload_cast<const Polygon&>(&Polygon::intersects, const_), arg("polygon"))
        .def("intersection_with", overload_cast<const Polygon&>(&Polygon::intersectionWith, const_), arg("polygon"))
        .def("difference_with", overload_cast<const Polygon&>(&Polygon::differenceWith, const_), arg("polygon"))
        .def("contains", overload_cast<const Point&>(&Polygon::contains, const_), arg("point"))
        .def("contains", overload_cast<const PointSet&>(&Polygon::contains, const_), arg("point_set"))

        .def("get_inner_ring_count", &Polygon::getInnerRingCount)
        .def("get_edge_count", &Polygon::getEdgeCount)
        .def("get_vertex_count", &Polygon::getVertexCount)
        .def("get_outer_ring", &Polygon::getOuterRing)
        .def("get_inner_ring_at", &Polygon::getInnerRingAt, arg("index"))
        .def("get_edge_at", &Polygon::getEdgeAt, arg("index"))
        .def("get_vertex_at", &Polygon::getVertexAt, arg("index"))
        .def("get_edges", &Polygon::getEdges)
        .def("get_vertices", &Polygon::getVertices)
        .def("get_convex_hull", &Polygon::getConvexHull)
        .def("union_with", &Polygon::unionWith, arg("polygon"))
        .def(
            "to_string",
            &Polygon::toString,
            arg("format") = Object::Format::Standard,
            arg("precision") = Integer::Undefined()
        )
        .def("apply_transformation", &Polygon::applyTransformation, arg("transformation"))

        .def_static("undefined", &Polygon::Undefined)

        ;
}
