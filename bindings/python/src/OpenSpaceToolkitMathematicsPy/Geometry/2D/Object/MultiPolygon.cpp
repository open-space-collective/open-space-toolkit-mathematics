/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/MultiPolygon.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_2D_Object_MultiPolygon(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::container::Array;
    using ostk::core::type::Integer;

    using ostk::mathematics::geometry::d2::Object;
    using ostk::mathematics::geometry::d2::object::MultiPolygon;
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::PointSet;
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::object::Vector2d;

    class_<MultiPolygon, Object>(aModule, "MultiPolygon")

        .def(
            init<const Array<Polygon>&>(),
            R"doc(
                Create a multi-polygon from an array of polygons.

                Args:
                    polygons (list): List of Polygon objects to combine into a multi-polygon.

                Example:
                    >>> polygon1 = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0)])
                    >>> polygon2 = Polygon([Point(2.0, 2.0), Point(3.0, 2.0), Point(3.0, 3.0)])
                    >>> multi_polygon = MultiPolygon([polygon1, polygon2])
            )doc",
            arg("polygons")
        )

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<MultiPolygon>))
        .def("__repr__", &(shiftToString<MultiPolygon>))

        .def(
            "is_defined",
            &MultiPolygon::isDefined,
            R"doc(
                Check if the multi-polygon is defined.

                Returns:
                    bool: True if the multi-polygon is defined, False otherwise.

                Example:
                    >>> polygon = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0)])
                    >>> multi_polygon = MultiPolygon([polygon])
                    >>> multi_polygon.is_defined()  # True
            )doc"
        )
        .def(
            "contains",
            overload_cast<const Point&>(&MultiPolygon::contains, const_),
            R"doc(
                Check if the multi-polygon contains a point.

                Args:
                    point (Point): The point to check for containment.

                Returns:
                    bool: True if any polygon in the multi-polygon contains the point, False otherwise.

                Example:
                    >>> polygon = Polygon([Point(0.0, 0.0), Point(2.0, 0.0), Point(2.0, 2.0)])
                    >>> multi_polygon = MultiPolygon([polygon])
                    >>> multi_polygon.contains(Point(1.0, 1.0))  # True
                    >>> multi_polygon.contains(Point(3.0, 3.0))  # False
            )doc",
            arg("point")
        )
        .def(
            "contains",
            overload_cast<const PointSet&>(&MultiPolygon::contains, const_),
            R"doc(
                Check if the multi-polygon contains all points in a point set.

                Args:
                    point_set (PointSet): The point set to check for containment.

                Returns:
                    bool: True if the multi-polygon contains all points in the set, False otherwise.

                Example:
                    >>> polygon = Polygon([Point(0.0, 0.0), Point(3.0, 0.0), Point(3.0, 3.0)])
                    >>> multi_polygon = MultiPolygon([polygon])
                    >>> points = PointSet([Point(1.0, 1.0), Point(2.0, 2.0)])
                    >>> multi_polygon.contains(points)  # True
            )doc",
            arg("point_set")
        )

        .def(
            "get_polygon_count",
            &MultiPolygon::getPolygonCount,
            R"doc(
                Get the number of polygons in the multi-polygon.

                Returns:
                    int: The number of polygons contained in the multi-polygon.

                Example:
                    >>> polygon1 = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0)])
                    >>> polygon2 = Polygon([Point(2.0, 2.0), Point(3.0, 2.0), Point(3.0, 3.0)])
                    >>> multi_polygon = MultiPolygon([polygon1, polygon2])
                    >>> multi_polygon.get_polygon_count()  # 2
            )doc"
        )
        .def(
            "get_polygons",
            &MultiPolygon::getPolygons,
            R"doc(
                Get all polygons contained in the multi-polygon.

                Returns:
                    list: List of Polygon objects contained in the multi-polygon.

                Example:
                    >>> polygon1 = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0)])
                    >>> polygon2 = Polygon([Point(2.0, 2.0), Point(3.0, 2.0), Point(3.0, 3.0)])
                    >>> multi_polygon = MultiPolygon([polygon1, polygon2])
                    >>> polygons = multi_polygon.get_polygons()
                    >>> len(polygons)  # 2
            )doc"
        )
        .def(
            "get_convex_hull",
            &MultiPolygon::getConvexHull,
            R"doc(
                Compute the convex hull of all polygons in the multi-polygon.

                Returns:
                    Polygon: A polygon representing the convex hull of all vertices.

                Example:
                    >>> polygon1 = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0)])
                    >>> polygon2 = Polygon([Point(2.0, 2.0), Point(3.0, 2.0), Point(3.0, 3.0)])
                    >>> multi_polygon = MultiPolygon([polygon1, polygon2])
                    >>> convex_hull = multi_polygon.get_convex_hull()
            )doc"
        )
        .def(
            "union_with",
            &MultiPolygon::unionWith,
            R"doc(
                Compute the union of this multi-polygon with another multi-polygon.

                Args:
                    multipolygon (MultiPolygon): The multi-polygon to union with.

                Returns:
                    MultiPolygon: A new multi-polygon representing the union.

                Example:
                    >>> polygon1 = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0)])
                    >>> polygon2 = Polygon([Point(0.5, 0.5), Point(1.5, 0.5), Point(1.5, 1.5)])
                    >>> multi1 = MultiPolygon([polygon1])
                    >>> multi2 = MultiPolygon([polygon2])
                    >>> union_result = multi1.union_with(multi2)
            )doc",
            arg("multipolygon")
        )
        .def(
            "to_string",
            &MultiPolygon::toString,
            R"doc(
                Convert the multi-polygon to a string representation.

                Args:
                    format (Object.Format, optional): The output format. Defaults to Standard.
                    precision (int, optional): The precision for floating point numbers. Defaults to undefined.

                Returns:
                    str: String representation of the multi-polygon.

                Example:
                    >>> polygon = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0)])
                    >>> multi_polygon = MultiPolygon([polygon])
                    >>> multi_polygon.to_string()
            )doc",
            arg("format") = Object::Format::Standard,
            arg("precision") = Integer::Undefined()
        )
        .def(
            "apply_transformation",
            &MultiPolygon::applyTransformation,
            R"doc(
                Apply a transformation to all polygons in the multi-polygon in place.

                Args:
                    transformation (Transformation): The 2D transformation to apply.

                Example:
                    >>> polygon = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0)])
                    >>> multi_polygon = MultiPolygon([polygon])
                    >>> transformation = Translation([1.0, 1.0])
                    >>> multi_polygon.apply_transformation(transformation)
            )doc",
            arg("transformation")
        )

        .def_static(
            "undefined",
            &MultiPolygon::Undefined,
            R"doc(
                Create an undefined multi-polygon.

                Returns:
                    MultiPolygon: An undefined multi-polygon object.

                Example:
                    >>> undefined_multi_polygon = MultiPolygon.undefined()
                    >>> undefined_multi_polygon.is_defined()  # False
            )doc"
        )
        .def_static(
            "polygon",
            &MultiPolygon::Polygon,
            R"doc(
                Create a multi-polygon from a single polygon.

                Args:
                    polygon (Polygon): The polygon to wrap in a multi-polygon.

                Returns:
                    MultiPolygon: A multi-polygon containing the single polygon.

                Example:
                    >>> polygon = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0)])
                    >>> multi_polygon = MultiPolygon.polygon(polygon)
                    >>> multi_polygon.get_polygon_count()  # 1
            )doc",
            arg("polygon")
        )

        ;
}
