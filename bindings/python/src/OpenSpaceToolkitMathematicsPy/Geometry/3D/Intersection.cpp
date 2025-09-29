/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Intersection(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::container::Array;
    using ostk::core::type::Unique;

    using ostk::mathematics::geometry::d3::Intersection;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Composite;
    using ostk::mathematics::geometry::d3::object::Cuboid;
    using ostk::mathematics::geometry::d3::object::Ellipsoid;
    using ostk::mathematics::geometry::d3::object::Line;
    using ostk::mathematics::geometry::d3::object::LineString;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::geometry::d3::object::Sphere;

    // scope in_Intersection = class_<Intersection>("Intersection", init<const Array<Unique<Object>>>())
    class_<Intersection> intersection(
        aModule,
        "Intersection",
        R"doc(
            Represents the intersection of 3D geometric objects.

            An Intersection can contain various geometric types resulting from intersecting two objects.
        )doc"
    );

    // Define constructor
    // intersection.def("__init__",
    //     [] (Intersection& anIntersection, const pybind11::list& anObjectList)
    //         {

    //             Array<Unique<Object>> anObjectArray = {} ;
    //             int length = anObjectList.size() ;

    //             for (int i = 0 ; i < length ; i++ )
    //             {

    //                 Unique<Object> ptr = std::make_unique<Object>(anObjectList[i]) ;
    //                 anObjectArray.add(unique_ptr) ;

    //             }

    //             anIntersection = std::move(anObjectArray) ;
    //             // new (&anIntersection) Intersection(anObjectArray) ;

    //         }
    // ) ;

    // Define methods
    intersection.def(self == self)
        .def(self != self)

        .def(self + self)
        .def(self += self)

        .def("__str__", &(shiftToString<Intersection>))
        .def("__repr__", &(shiftToString<Intersection>))

        .def(
            "is_defined",
            &Intersection::isDefined,
            R"doc(
                Check if the intersection is defined.

                Returns:
                    bool: True if the intersection is defined.
            )doc"
        )
        .def(
            "is_empty",
            &Intersection::isEmpty,
            R"doc(
                Check if the intersection is empty.

                Returns:
                    bool: True if the intersection contains no objects.
            )doc"
        )
        .def(
            "is_complex",
            &Intersection::isComplex,
            R"doc(
                Check if the intersection is complex (contains multiple objects).

                Returns:
                    bool: True if the intersection contains multiple objects.
            )doc"
        )

        .def(
            "is_point",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Point>();
            },
            R"doc(
                Check if the intersection is a point.

                Returns:
                    bool: True if the intersection contains a single point.
            )doc"
        )
        .def(
            "is_point_set",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<PointSet>();
            },
            R"doc(
                Check if the intersection is a point set.

                Returns:
                    bool: True if the intersection contains a point set.
            )doc"
        )
        .def(
            "is_line",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Line>();
            },
            R"doc(
                Check if the intersection is a line.

                Returns:
                    bool: True if the intersection contains a line.
            )doc"
        )
        .def(
            "is_ray",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Ray>();
            },
            R"doc(
                Check if the intersection is a ray.

                Returns:
                    bool: True if the intersection contains a ray.
            )doc"
        )
        .def(
            "is_segment",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Segment>();
            },
            R"doc(
                Check if the intersection is a segment.

                Returns:
                    bool: True if the intersection contains a segment.
            )doc"
        )
        .def(
            "is_line_string",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<LineString>();
            },
            R"doc(
                Check if the intersection is a line string.

                Returns:
                    bool: True if the intersection contains a line string.
            )doc"
        )
        .def(
            "is_polygon",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Polygon>();
            },
            R"doc(
                Check if the intersection is a polygon.

                Returns:
                    bool: True if the intersection contains a polygon.
            )doc"
        )
        .def(
            "is_plane",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Plane>();
            },
            R"doc(
                Check if the intersection is a plane.

                Returns:
                    bool: True if the intersection contains a plane.
            )doc"
        )
        .def(
            "is_sphere",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Sphere>();
            },
            R"doc(
                Check if the intersection is a sphere.

                Returns:
                    bool: True if the intersection contains a sphere.
            )doc"
        )
        .def(
            "is_ellipsoid",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Ellipsoid>();
            },
            R"doc(
                Check if the intersection is an ellipsoid.

                Returns:
                    bool: True if the intersection contains an ellipsoid.
            )doc"
        )
        .def(
            "is_pyramid",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Pyramid>();
            },
            R"doc(
                Check if the intersection is a pyramid.

                Returns:
                    bool: True if the intersection contains a pyramid.
            )doc"
        )
        .def(
            "is_composite",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Composite>();
            },
            R"doc(
                Check if the intersection is a composite.

                Returns:
                    bool: True if the intersection contains a composite object.
            )doc"
        )

        .def(
            "as_point",
            +[](const Intersection& anIntersection) -> Point
            {
                return anIntersection.as<Point>();
            },
            R"doc(
                Convert the intersection to a point.

                Returns:
                    Point: The intersection as a point.
            )doc"
        )
        .def(
            "as_point_set",
            +[](const Intersection& anIntersection) -> PointSet
            {
                return anIntersection.as<PointSet>();
            },
            R"doc(
                Convert the intersection to a point set.

                Returns:
                    PointSet: The intersection as a point set.
            )doc"
        )
        .def(
            "as_line",
            +[](const Intersection& anIntersection) -> Line
            {
                return anIntersection.as<Line>();
            },
            R"doc(
                Convert the intersection to a line.

                Returns:
                    Line: The intersection as a line.
            )doc"
        )
        .def(
            "as_ray",
            +[](const Intersection& anIntersection) -> Ray
            {
                return anIntersection.as<Ray>();
            },
            R"doc(
                Convert the intersection to a ray.

                Returns:
                    Ray: The intersection as a ray.
            )doc"
        )
        .def(
            "as_segment",
            +[](const Intersection& anIntersection) -> Segment
            {
                return anIntersection.as<Segment>();
            },
            R"doc(
                Convert the intersection to a segment.

                Returns:
                    Segment: The intersection as a segment.
            )doc"
        )
        .def(
            "as_line_string",
            +[](const Intersection& anIntersection) -> LineString
            {
                return anIntersection.as<LineString>();
            },
            R"doc(
                Convert the intersection to a line string.

                Returns:
                    LineString: The intersection as a line string.
            )doc"
        )
        .def(
            "as_polygon",
            +[](const Intersection& anIntersection) -> Polygon
            {
                return anIntersection.as<Polygon>();
            },
            R"doc(
                Convert the intersection to a polygon.

                Returns:
                    Polygon: The intersection as a polygon.
            )doc"
        )
        .def(
            "as_plane",
            +[](const Intersection& anIntersection) -> Plane
            {
                return anIntersection.as<Plane>();
            },
            R"doc(
                Convert the intersection to a plane.

                Returns:
                    Plane: The intersection as a plane.
            )doc"
        )
        .def(
            "as_sphere",
            +[](const Intersection& anIntersection) -> Sphere
            {
                return anIntersection.as<Sphere>();
            },
            R"doc(
                Convert the intersection to a sphere.

                Returns:
                    Sphere: The intersection as a sphere.
            )doc"
        )
        .def(
            "as_ellipsoid",
            +[](const Intersection& anIntersection) -> Ellipsoid
            {
                return anIntersection.as<Ellipsoid>();
            },
            R"doc(
                Convert the intersection to an ellipsoid.

                Returns:
                    Ellipsoid: The intersection as an ellipsoid.
            )doc"
        )
        .def(
            "as_pyramid",
            +[](const Intersection& anIntersection) -> Pyramid
            {
                return anIntersection.as<Pyramid>();
            },
            R"doc(
                Convert the intersection to a pyramid.

                Returns:
                    Pyramid: The intersection as a pyramid.
            )doc"
        )
        .def(
            "as_composite",
            +[](const Intersection& anIntersection) -> Composite
            {
                return anIntersection.as<Composite>();
            },
            R"doc(
                Convert the intersection to a composite.

                Returns:
                    Composite: The intersection as a composite object.
            )doc"
        )

        // .def("access_composite", &Intersection::accessComposite, return_value_policy<reference_existing_object>())
        .def(
            "access_composite",
            &Intersection::accessComposite,
            return_value_policy::reference,
            R"doc(
                Access the composite object in the intersection.

                Returns:
                    Composite: Reference to the composite object.
            )doc"
        )

        .def(
            "get_type",
            &Intersection::getType,
            R"doc(
                Get the type of the intersection.

                Returns:
                    Intersection.Type: The type of the intersection.
            )doc"
        )

        // Define static methods
        .def_static(
            "undefined",
            &Intersection::Undefined,
            R"doc(
                Create an undefined intersection.

                Returns:
                    Intersection: An undefined intersection.
            )doc"
        )
        .def_static(
            "empty",
            &Intersection::Empty,
            R"doc(
                Create an empty intersection.

                Returns:
                    Intersection: An empty intersection.
            )doc"
        )
        .def_static(
            "point",
            &Intersection::Point,
            arg("point"),
            R"doc(
                Create an intersection from a point.

                Args:
                    point (Point): The point.

                Returns:
                    Intersection: An intersection containing the point.
            )doc"
        )
        .def_static(
            "point_set",
            &Intersection::PointSet,
            arg("point_set"),
            R"doc(
                Create an intersection from a point set.

                Args:
                    point_set (PointSet): The point set.

                Returns:
                    Intersection: An intersection containing the point set.
            )doc"
        )
        .def_static(
            "line",
            &Intersection::Line,
            arg("line"),
            R"doc(
                Create an intersection from a line.

                Args:
                    line (Line): The line.

                Returns:
                    Intersection: An intersection containing the line.
            )doc"
        )
        .def_static(
            "ray",
            &Intersection::Ray,
            arg("ray"),
            R"doc(
                Create an intersection from a ray.

                Args:
                    ray (Ray): The ray.

                Returns:
                    Intersection: An intersection containing the ray.
            )doc"
        )
        .def_static(
            "segment",
            &Intersection::Segment,
            arg("segment"),
            R"doc(
                Create an intersection from a segment.

                Args:
                    segment (Segment): The segment.

                Returns:
                    Intersection: An intersection containing the segment.
            )doc"
        )

        .def_static(
            "string_from_type",
            &Intersection::StringFromType,
            arg("type"),
            R"doc(
                Convert an intersection type to a string.

                Args:
                    type (Intersection.Type): The intersection type.

                Returns:
                    str: The string representation of the type.
            )doc"
        )

        ;

    // Define Intersection types
    enum_<Intersection::Type>(intersection, "Type")

        .value("Undefined", Intersection::Type::Undefined)
        .value("Empty", Intersection::Type::Empty)
        .value("Point", Intersection::Type::Point)
        .value("PointSet", Intersection::Type::PointSet)
        .value("Line", Intersection::Type::Line)
        .value("Ray", Intersection::Type::Ray)
        .value("Segment", Intersection::Type::Segment)
        .value("Plane", Intersection::Type::Plane)
        .value("Sphere", Intersection::Type::Sphere)
        .value("Ellipsoid", Intersection::Type::Ellipsoid)
        .value("Complex", Intersection::Type::Complex)

        ;
}
