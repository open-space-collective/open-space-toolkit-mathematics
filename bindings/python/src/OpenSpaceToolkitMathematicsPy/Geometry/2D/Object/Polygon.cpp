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

        .def(
            init<const Array<Point>&, const Array<Array<Point>>&>(),
            R"doc(
                Create a polygon with outer ring and inner rings (holes).

                Args:
                    outer_ring (list): List of points defining the outer boundary.
                    inner_rings (list): List of lists of points defining holes.

                Example:
                    >>> outer = [Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0), Point(0.0, 1.0)]
                    >>> inner = [[Point(0.2, 0.2), Point(0.8, 0.2), Point(0.8, 0.8), Point(0.2, 0.8)]]
                    >>> polygon = Polygon(outer, inner)
            )doc",
            arg("outer_ring"),
            arg("inner_rings")
        )

        .def(
            init<const Array<Point>&>(),
            R"doc(
                Create a simple polygon with just an outer ring.

                Args:
                    outer_ring (list): List of points defining the polygon boundary.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0), Point(0.0, 1.0)]
                    >>> polygon = Polygon(points)
            )doc",
            arg("outer_ring")
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
                    bool: True if the polygon is defined, False otherwise.

                Example:
                    >>> polygon = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0)])
                    >>> polygon.is_defined()  # True
            )doc"
        )
        .def(
            "is_near",
            &Polygon::isNear,
            R"doc(
                Check if this polygon is near another polygon within tolerance.

                Args:
                    polygon (Polygon): The polygon to compare with.
                    tolerance (float): The tolerance for comparison.

                Returns:
                    bool: True if polygons are within tolerance, False otherwise.

                Example:
                    >>> polygon1 = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0)])
                    >>> polygon2 = Polygon([Point(0.01, 0.01), Point(1.01, 0.01), Point(1.01, 1.01)])
                    >>> polygon1.is_near(polygon2, 0.1)  # True
            )doc",
            arg("polygon"),
            arg("tolerance")
        )
        .def("intersects", overload_cast<const Polygon&>(&Polygon::intersects, const_), arg("polygon"))
        .def("intersection_with", overload_cast<const Polygon&>(&Polygon::intersectionWith, const_), arg("polygon"))
        .def("difference_with", overload_cast<const Polygon&>(&Polygon::differenceWith, const_), arg("polygon"))
        .def(
            "contains",
            overload_cast<const Point&>(&Polygon::contains, const_),
            R"doc(
                Check if the polygon contains a point.

                Args:
                    point (Point): The point to check.

                Returns:
                    bool: True if the polygon contains the point, False otherwise.

                Example:
                    >>> polygon = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0), Point(0.0, 1.0)])
                    >>> polygon.contains(Point(0.5, 0.5))  # True
            )doc",
            arg("point")
        )
        .def("contains", overload_cast<const PointSet&>(&Polygon::contains, const_), arg("point_set"))

        .def("get_inner_ring_count", &Polygon::getInnerRingCount)
        .def("get_edge_count", &Polygon::getEdgeCount)
        .def(
            "get_vertex_count",
            &Polygon::getVertexCount,
            R"doc(
                Get the total number of vertices in the polygon.

                Returns:
                    int: The number of vertices.

                Example:
                    >>> polygon = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0), Point(0.0, 1.0)])
                    >>> polygon.get_vertex_count()  # 4
            )doc"
        )
        .def("get_outer_ring", &Polygon::getOuterRing)
        .def("get_inner_ring_at", &Polygon::getInnerRingAt, arg("index"))
        .def("get_edge_at", &Polygon::getEdgeAt, arg("index"))
        .def("get_vertex_at", &Polygon::getVertexAt, arg("index"))
        .def("get_edges", &Polygon::getEdges)
        .def(
            "get_vertices",
            &Polygon::getVertices,
            R"doc(
                Get all vertices of the polygon.

                Returns:
                    list: List of all vertices in the polygon.

                Example:
                    >>> polygon = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0)])
                    >>> vertices = polygon.get_vertices()
            )doc"
        )
        .def("get_convex_hull", &Polygon::getConvexHull)
        .def("union_with", &Polygon::unionWith, arg("polygon"))
        .def(
            "to_string",
            &Polygon::toString,
            arg("format") = Object::Format::Standard,
            arg("precision") = Integer::Undefined()
        )
        .def("apply_transformation", &Polygon::applyTransformation, arg("transformation"))

        .def_static(
            "undefined",
            &Polygon::Undefined,
            R"doc(
                Create an undefined polygon.

                Returns:
                    Polygon: An undefined polygon.

                Example:
                    >>> undefined_polygon = Polygon.undefined()
                    >>> undefined_polygon.is_defined()  # False
            )doc"
        )

        ;
}
