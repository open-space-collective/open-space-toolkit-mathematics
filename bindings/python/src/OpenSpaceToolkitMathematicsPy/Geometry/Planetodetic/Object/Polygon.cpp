/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/Planetodetic/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/Planetodetic/Object/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/Planetodetic/Object/Spheroid.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_Planetodetic_Object_Polygon(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Integer;
    using ostk::core::type::Size;
    using ostk::core::type::String;

    using ostk::mathematics::geometry::planetodetic::Object;
    using ostk::mathematics::geometry::planetodetic::object::Point;
    using ostk::mathematics::geometry::planetodetic::object::Polygon;
    using ostk::mathematics::geometry::planetodetic::object::Spheroid;

    class_<Polygon, Object>(aModule, "Polygon")

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Polygon>))
        .def(
            "__repr__",
            +[](const Polygon& aPolygon) -> std::string
            {
                return aPolygon.toString();
            }
        )

        .def(
            "is_defined",
            &Polygon::isDefined,
            R"doc(
                Check if the polygon is defined.

                Returns:
                    bool: True if the polygon is defined, False otherwise.

                Example:
                    >>> spheroid = Spheroid.sphere(6378137.0)
                    >>> points = [
                    ...     Point(Angle.degrees(-1.0), Angle.degrees(-1.0)),
                    ...     Point(Angle.degrees(-1.0), Angle.degrees(1.0)),
                    ...     Point(Angle.degrees(1.0), Angle.degrees(1.0))
                    ... ]
                    >>> polygon = Polygon.simple(spheroid, points)
                    >>> polygon.is_defined()  # True
            )doc"
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
                    >>> spheroid = Spheroid.sphere(6378137.0)
                    >>> points = [
                    ...     Point(Angle.degrees(-10.0), Angle.degrees(-10.0)),
                    ...     Point(Angle.degrees(-10.0), Angle.degrees(10.0)),
                    ...     Point(Angle.degrees(10.0), Angle.degrees(10.0)),
                    ...     Point(Angle.degrees(10.0), Angle.degrees(-10.0))
                    ... ]
                    >>> polygon = Polygon.simple(spheroid, points)
                    >>> test_point = Point(Angle.degrees(0.0), Angle.degrees(0.0))
                    >>> polygon.contains(test_point)  # True
            )doc",
            arg("point")
        )

        .def(
            "get_spheroid",
            &Polygon::getSpheroid,
            R"doc(
                Get the reference spheroid of the polygon.

                Returns:
                    Spheroid: The reference spheroid.

                Example:
                    >>> spheroid = Spheroid.sphere(6378137.0)
                    >>> points = [Point(Angle.degrees(0.0), Angle.degrees(0.0)),
                    ...           Point(Angle.degrees(0.0), Angle.degrees(1.0)),
                    ...           Point(Angle.degrees(1.0), Angle.degrees(0.0))]
                    >>> polygon = Polygon.simple(spheroid, points)
                    >>> polygon.get_spheroid() == spheroid  # True
            )doc"
        )

        .def(
            "get_vertex_count",
            &Polygon::getVertexCount,
            R"doc(
                Get the number of vertices in the polygon.

                Returns:
                    int: The number of vertices.

                Example:
                    >>> spheroid = Spheroid.sphere(6378137.0)
                    >>> points = [Point(Angle.degrees(0.0), Angle.degrees(0.0)),
                    ...           Point(Angle.degrees(0.0), Angle.degrees(1.0)),
                    ...           Point(Angle.degrees(1.0), Angle.degrees(0.0))]
                    >>> polygon = Polygon.simple(spheroid, points)
                    >>> polygon.get_vertex_count()  # 3
            )doc"
        )

        .def(
            "get_vertices",
            &Polygon::getVertices,
            R"doc(
                Get the vertices of the polygon.

                Returns:
                    list[Point]: The list of vertices.

                Example:
                    >>> spheroid = Spheroid.sphere(6378137.0)
                    >>> points = [Point(Angle.degrees(0.0), Angle.degrees(0.0)),
                    ...           Point(Angle.degrees(0.0), Angle.degrees(1.0)),
                    ...           Point(Angle.degrees(1.0), Angle.degrees(0.0))]
                    >>> polygon = Polygon.simple(spheroid, points)
                    >>> vertices = polygon.get_vertices()
                    >>> len(vertices)  # 3
            )doc"
        )

        .def_static(
            "simple",
            &Polygon::Simple,
            R"doc(
                Create a simple polygon from its outer ring vertices.

                The "inside" of the polygon is defined as the area to the left when
                traversing the outer ring vertices in a counter-clockwise direction.

                Args:
                    spheroid (Spheroid): The reference spheroid.
                    outer_ring (list[Point]): The list of vertices defining the outer ring (at least 3 non-collinear points).

                Returns:
                    Polygon: The constructed polygon.

                Example:
                    >>> spheroid = Spheroid.sphere(6378137.0)
                    >>> outer_ring = [
                    ...     Point(Angle.degrees(-1.0), Angle.degrees(-1.0)),
                    ...     Point(Angle.degrees(-1.0), Angle.degrees(1.0)),
                    ...     Point(Angle.degrees(1.0), Angle.degrees(1.0)),
                    ...     Point(Angle.degrees(1.0), Angle.degrees(-1.0))
                    ... ]
                    >>> polygon = Polygon.simple(spheroid, outer_ring)
            )doc",
            arg("spheroid"),
            arg("outer_ring")
        )

        .def_static(
            "undefined",
            &Polygon::Undefined,
            R"doc(
                Create an undefined polygon.

                Returns:
                    Polygon: An undefined polygon.

                Example:
                    >>> polygon = Polygon.undefined()
                    >>> polygon.is_defined()  # False
            )doc"
        )

        ;
}
