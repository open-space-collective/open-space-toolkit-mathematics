/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Polygon.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Polygon(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::mathematics::object::Vector3d;
    using Polygon2d = ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;

    class_<Polygon, Object>(
        aModule,
        "Polygon",
        R"doc(
                A polygon in 3D space.

                A Polygon is a planar figure defined by a 2D polygon and its position and orientation in 3D space.
            )doc"
    )

        .def(
            init<const Polygon2d&, const Point&, const Vector3d&, const Vector3d&>(),
            arg("polygon"),
            arg("origin"),
            arg("x_axis"),
            arg("y_axis"),
            R"doc(
                Construct a 3D polygon from a 2D polygon and coordinate frame.

                Args:
                    polygon (Polygon2d): The 2D polygon.
                    origin (Point): The origin of the polygon in 3D space.
                    x_axis (numpy.ndarray): The x-axis direction of the polygon's local frame.
                    y_axis (numpy.ndarray): The y-axis direction of the polygon's local frame.
            )doc"
        )

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Polygon>))
        .def("__repr__", &(shiftToString<Polygon>))

        .def(
            "is_defined",
            &Polygon::isDefined,
            R"doc(
                Check if the polygon is defined.

                Returns:
                    bool: True if the polygon is defined.
            )doc"
        )
        .def(
            "is_near",
            &Polygon::isNear,
            arg("polygon"),
            arg("tolerance"),
            R"doc(
                Check if another polygon is near this one within a tolerance.

                Args:
                    polygon (Polygon): The polygon to compare against.
                    tolerance (float): The maximum distance for polygons to be considered near.

                Returns:
                    bool: True if the polygons are near each other.
            )doc"
        )

        .def(
            "get_polygon2d",
            &Polygon::getPolygon2d,
            R"doc(
                Get the 2D polygon representation.

                Returns:
                    Polygon2d: The 2D polygon.
            )doc"
        )
        .def(
            "get_origin",
            &Polygon::getOrigin,
            R"doc(
                Get the origin point of the polygon.

                Returns:
                    Point: The origin point.
            )doc"
        )
        .def(
            "get_x_axis",
            &Polygon::getXAxis,
            R"doc(
                Get the x-axis direction of the polygon's local frame.

                Returns:
                    numpy.ndarray: The x-axis vector.
            )doc"
        )
        .def(
            "get_y_axis",
            &Polygon::getYAxis,
            R"doc(
                Get the y-axis direction of the polygon's local frame.

                Returns:
                    numpy.ndarray: The y-axis vector.
            )doc"
        )
        .def(
            "get_normal_vector",
            &Polygon::getNormalVector,
            R"doc(
                Get the normal vector of the polygon's plane.

                Returns:
                    numpy.ndarray: The normal vector.
            )doc"
        )
        .def(
            "get_edge_count",
            &Polygon::getEdgeCount,
            R"doc(
                Get the number of edges in the polygon.

                Returns:
                    int: The number of edges.
            )doc"
        )
        .def(
            "get_vertex_count",
            &Polygon::getVertexCount,
            R"doc(
                Get the number of vertices in the polygon.

                Returns:
                    int: The number of vertices.
            )doc"
        )
        .def(
            "get_edge_at",
            &Polygon::getEdgeAt,
            arg("index"),
            R"doc(
                Get the edge at a given index.

                Args:
                    index (int): The index of the edge.

                Returns:
                    Segment: The edge segment.
            )doc"
        )
        .def(
            "get_vertex_at",
            &Polygon::getVertexAt,
            arg("index"),
            R"doc(
                Get the vertex at a given index.

                Args:
                    index (int): The index of the vertex.

                Returns:
                    Point: The vertex point.
            )doc"
        )
        .def(
            "get_vertices",
            &Polygon::getVertices,
            R"doc(
                Get all vertices of the polygon.

                Returns:
                    list[Point]: Array of vertex points.
            )doc"
        )
        .def(
            "apply_transformation",
            &Polygon::applyTransformation,
            arg("transformation"),
            R"doc(
                Apply a transformation to the polygon.

                Args:
                    transformation (Transformation): The transformation to apply.
            )doc"
        )

        .def_static(
            "undefined",
            &Polygon::Undefined,
            R"doc(
                Create an undefined polygon.

                Returns:
                    Polygon: An undefined polygon.
            )doc"
        )

        ;
}
