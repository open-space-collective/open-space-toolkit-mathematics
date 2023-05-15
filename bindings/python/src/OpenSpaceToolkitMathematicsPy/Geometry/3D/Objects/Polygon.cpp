/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Polygon.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Polygon(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::math::obj::Vector3d;
    using Polygon2d = ostk::math::geom::d2::objects::Polygon;
    using ostk::math::geom::d3::Object;
    using ostk::math::geom::d3::objects::Point;
    using ostk::math::geom::d3::objects::Polygon;

    class_<Polygon, Object>(aModule, "Polygon")

        .def(
            init<const Polygon2d&, const Point&, const Vector3d&, const Vector3d&>(),
            arg("polygon"),
            arg("origin"),
            arg("x_axis"),
            arg("y_axis")
        )

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Polygon>))
        .def("__repr__", &(shiftToString<Polygon>))

        .def("is_defined", &Polygon::isDefined)
        .def("is_near", &Polygon::isNear, arg("polygon"), arg("tolerance"))

        .def("get_polygon2d", &Polygon::getPolygon2d)
        .def("get_origin", &Polygon::getOrigin)
        .def("get_x_axis", &Polygon::getXAxis)
        .def("get_y_axis", &Polygon::getYAxis)
        .def("get_normal_vector", &Polygon::getNormalVector)
        .def("get_edge_count", &Polygon::getEdgeCount)
        .def("get_vertex_count", &Polygon::getVertexCount)
        .def("get_edge_at", &Polygon::getEdgeAt, arg("index"))
        .def("get_vertex_at", &Polygon::getVertexAt, arg("index"))
        .def("get_vertices", &Polygon::getVertices)
        .def("apply_transformation", &Polygon::applyTransformation, arg("transformation"))

        .def_static("undefined", &Polygon::Undefined)

        ;
}
