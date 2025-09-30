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
                    outer_ring (list[Point]): List of points defining the outer boundary.
                    inner_rings (list[list[Point]]): List of lists of points defining holes.

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
                    outer_ring (list[Point]): List of points defining the polygon boundary.

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
        .def(
            "intersects",
            overload_cast<const Polygon&>(&Polygon::intersects, const_),
            R"doc(
                Check if the polygon intersects another polygon.

                Args:
                    polygon (Polygon): The polygon to check intersection with.

                Returns:
                    bool: True if the polygons intersect, False otherwise.

                Example:
                    >>> polygon1 = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0)])
                    >>> polygon2 = Polygon([Point(0.01, 0.01), Point(1.01, 0.01), Point(1.01, 1.01)])
                    >>> polygon1.intersects(polygon2)  # True
            )doc",
            arg("polygon")
        )
        .def(
            "intersection_with",
            overload_cast<const Polygon&>(&Polygon::intersectionWith, const_),
            R"doc(
                Get the intersection of the polygon with another polygon.

                Args:
                    polygon (Polygon): The polygon to check intersection with.

                Returns:
                    Intersection: The intersection of the polygon with another polygon.

                Example:
                    >>> polygon1 = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0)])
                    >>> polygon2 = Polygon([Point(0.01, 0.01), Point(1.01, 0.01), Point(1.01, 1.01)])
                    >>> polygon1.intersection_with(polygon2)  # Intersection
            )doc",
            arg("polygon")
        )
        .def(
            "difference_with",
            overload_cast<const Polygon&>(&Polygon::differenceWith, const_),
            R"doc(
                Get the difference of the polygon with another polygon.

                Args:
                    polygon (Polygon): The polygon to check difference with.

                Returns:
                    Intersection: The difference of the polygon with another polygon.

                Example:
                    >>> polygon1 = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0)])
                    >>> polygon2 = Polygon([Point(0.01, 0.01), Point(1.01, 0.01), Point(1.01, 1.01)])
                    >>> polygon1.difference_with(polygon2)  # Intersection
            )doc",
            arg("polygon")
        )
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
        .def(
            "contains",
            overload_cast<const PointSet&>(&Polygon::contains, const_),
            R"doc(
                Check if the polygon contains a point set.

                Args:
                    point_set (PointSet): The point set to check.

                Returns:
                    bool: True if the polygon contains the point set, False otherwise.

                Example:
                    >>> polygon = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0), Point(0.0, 1.0)])
                    >>> point_set = PointSet([Point(0.5, 0.5), Point(1.5, 0.5), Point(1.5, 1.5)])
                    >>> polygon.contains(point_set)  # True
            )doc",
            arg("point_set")
        )

        .def(
            "get_inner_ring_count",
            &Polygon::getInnerRingCount,
            R"doc(
                Get the number of inner rings in the polygon.

                Returns:
                    int: The number of inner rings.

                Example:
                    >>> polygon = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0), Point(0.0, 1.0)])
                    >>> polygon.get_inner_ring_count()  # 0
            )doc"
        )
        .def(
            "get_edge_count",
            &Polygon::getEdgeCount,
            R"doc(
                Get the number of edges in the polygon.

                Returns:
                    int: The number of edges.

                Example:
                    >>> polygon = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0), Point(0.0, 1.0)])
                    >>> polygon.get_edge_count()  # 4
            )doc"
        )
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
        .def(
            "get_outer_ring",
            &Polygon::getOuterRing,
            R"doc(
                Get the outer ring of the polygon.

                Returns:
                    Polygon.Ring: The outer ring of the polygon.

                Example:
                    >>> polygon = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0), Point(0.0, 1.0)])
                    >>> polygon.get_outer_ring()
            )doc"
        )
        .def(
            "get_inner_ring_at",
            &Polygon::getInnerRingAt,
            R"doc(
                Get the inner ring at the given index.

                Args:
                    index (int): The index of the inner ring.

                Returns:
                    Polygon.Ring: The inner ring at the given index.

                Example:
                    >>> polygon = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0), Point(0.0, 1.0)])
                    >>> polygon.get_inner_ring_at(0)
            )doc"
        )
        .def(
            "get_edge_at",
            &Polygon::getEdgeAt,
            R"doc(
                Get the edge at the given index.

                Args:
                    index (int): The index of the edge.

                Returns:
                    Polygon.Edge: The edge at the given index.

                Example:
                    >>> polygon = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0), Point(0.0, 1.0)])
                    >>> polygon.get_edge_at(0)
            )doc",
            arg("index")
        )
        .def(
            "get_vertex_at",
            &Polygon::getVertexAt,
            R"doc(
                Get the vertex at the given index.

                Args:
                    index (int): The index of the vertex.

                Returns:
                    Polygon.Vertex: The vertex at the given index.

                Example:
                    >>> polygon = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0), Point(0.0, 1.0)])
                    >>> polygon.get_vertex_at(0)
            )doc",
            arg("index")
        )
        .def(
            "get_edges",
            &Polygon::getEdges,
            R"doc(
                Get all edges of the polygon.

                Returns:
                    list: List of all edges in the polygon.

                Example:
                    >>> polygon = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0), Point(0.0, 1.0)])
                    >>> polygon.get_edges()
            )doc"
        )
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
        .def(
            "get_convex_hull",
            &Polygon::getConvexHull,
            R"doc(
                Get the convex hull of the polygon.

                Returns:
                    Polygon: The convex hull of the polygon.

                Example:
                    >>> polygon = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0), Point(0.0, 1.0)])
                    >>> polygon.get_convex_hull()
            )doc"
        )
        .def(
            "union_with",
            &Polygon::unionWith,
            R"doc(
                Get the union of the polygon with another polygon.

                Args:
                    polygon (Polygon): The polygon to union with.

                Returns:
                    Polygon: The union of the polygon with another polygon.

                Example:
                    >>> polygon1 = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0), Point(0.0, 1.0)])
                    >>> polygon2 = Polygon([Point(0.01, 0.01), Point(1.01, 0.01), Point(1.01, 1.01), Point(0.01, 1.01)])
                    >>> polygon1.union_with(polygon2)
            )doc",
            arg("polygon")
        )
        .def(
            "to_string",
            &Polygon::toString,
            R"doc(
                Get the string representation of the polygon.

                Args:
                    format (Object.Format, optional): The output format. Defaults to Standard.
                    precision (int, optional): The precision for floating point numbers. Defaults to undefined.

                Returns:
                    str: String representation of the polygon.

                Example:
                    >>> polygon = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0), Point(0.0, 1.0)])
                    >>> polygon.to_string()
            )doc",
            arg("format") = Object::Format::Standard,
            arg("precision") = Integer::Undefined()
        )
        .def(
            "apply_transformation",
            &Polygon::applyTransformation,
            R"doc(
                Apply a transformation to the polygon in place.

                Args:
                    transformation (Transformation): The transformation to apply.

                Example:
                    >>> polygon = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0), Point(0.0, 1.0)])
                    >>> transformation = Translation([1.0, 1.0])
                    >>> polygon.apply_transformation(transformation)
            )doc",
            arg("transformation")
        )

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
