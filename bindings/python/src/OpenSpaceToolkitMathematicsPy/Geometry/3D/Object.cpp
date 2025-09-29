/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object.hpp>

#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Object/Composite.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Object/Cone.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Object/Cuboid.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Object/Ellipsoid.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Object/Line.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Object/LineString.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Object/Plane.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Object/Point.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Object/PointSet.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Object/Polygon.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Object/Pyramid.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Object/Ray.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Object/Segment.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Object/Sphere.cpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Object(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Cone;
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

    // class_<Object, boost::noncopyable>("Object", no_init)
    class_<Object>(
        aModule,
        "Object",
        R"doc(
                Base class for 3D geometric objects.

                Object is the abstract base class for all 3D geometric primitives and shapes.
            )doc"
    )

        // no init

        // Define methods
        .def(
            "__eq__",
            [](const Object& self, const Object& other)
            {
                return self == other;
            }
        )
        .def(
            "__ne__",
            [](const Object& self, const Object& other)
            {
                return self != other;
            }
        )

        .def("__str__", &(shiftToString<Object>))
        .def("__repr__", &(shiftToString<Object>))

        .def(
            "is_defined",
            &Object::isDefined,
            R"doc(
                Check if the object is defined.

                Returns:
                    bool: True if the object is defined.

                Example:
                    >>> object = Point(1.0, 2.0, 3.0)
                    >>> object.is_defined()  # True
            )doc"
        )
        .def(
            "is_point",
            +[](const Object& anObject) -> bool
            {
                return anObject.is<Point>();
            },
            R"doc(
                Check if the object is a point.

                Returns:
                    bool: True if the object is a point.
            )doc"
        )
        .def(
            "is_point_set",
            +[](const Object& anObject) -> bool
            {
                return anObject.is<PointSet>();
            },
            R"doc(
                Check if the object is a point set.

                Returns:
                    bool: True if the object is a point set.
            )doc"
        )
        .def(
            "is_line",
            +[](const Object& anObject) -> bool
            {
                return anObject.is<Line>();
            },
            R"doc(
                Check if the object is a line.

                Returns:
                    bool: True if the object is a line.
            )doc"
        )
        .def(
            "is_ray",
            +[](const Object& anObject) -> bool
            {
                return anObject.is<Ray>();
            },
            R"doc(
                Check if the object is a ray.

                Returns:
                    bool: True if the object is a ray.
            )doc"
        )
        .def(
            "is_segment",
            +[](const Object& anObject) -> bool
            {
                return anObject.is<Segment>();
            },
            R"doc(
                Check if the object is a segment.

                Returns:
                    bool: True if the object is a segment.
            )doc"
        )
        .def(
            "is_line_string",
            +[](const Object& anObject) -> bool
            {
                return anObject.is<LineString>();
            },
            R"doc(
                Check if the object is a line string.

                Returns:
                    bool: True if the object is a line string.
            )doc"
        )
        .def(
            "is_polygon",
            +[](const Object& anObject) -> bool
            {
                return anObject.is<Polygon>();
            },
            R"doc(
                Check if the object is a polygon.

                Returns:
                    bool: True if the object is a polygon.
            )doc"
        )
        .def(
            "is_plane",
            +[](const Object& anObject) -> bool
            {
                return anObject.is<Plane>();
            },
            R"doc(
                Check if the object is a plane.

                Returns:
                    bool: True if the object is a plane.
            )doc"
        )
        .def(
            "is_sphere",
            +[](const Object& anObject) -> bool
            {
                return anObject.is<Sphere>();
            },
            R"doc(
                Check if the object is a sphere.

                Returns:
                    bool: True if the object is a sphere.
            )doc"
        )
        .def(
            "is_ellipsoid",
            +[](const Object& anObject) -> bool
            {
                return anObject.is<Ellipsoid>();
            },
            R"doc(
                Check if the object is an ellipsoid.

                Returns:
                    bool: True if the object is an ellipsoid.
            )doc"
        )
        .def(
            "is_pyramid",
            +[](const Object& anObject) -> bool
            {
                return anObject.is<Pyramid>();
            },
            R"doc(
                Check if the object is a pyramid.

                Returns:
                    bool: True if the object is a pyramid.
            )doc"
        )
        .def(
            "is_cone",
            +[](const Object& anObject) -> bool
            {
                return anObject.is<Cone>();
            },
            R"doc(
                Check if the object is a cone.

                Returns:
                    bool: True if the object is a cone.
            )doc"
        )
        .def(
            "intersects",
            &Object::intersects,
            R"doc(
                Check if this object intersects another object.

                Args:
                    object (Object): The object to check intersection with.

                Returns:
                    bool: True if the objects intersect.

                Example:
                    >>> object = Cone(Point(1.0, 2.0, 3.0), [0.0, 0.0, 1.0], Angle.degrees(30.0))
                    >>> other_object = Point(1.0, 2.0, 3.1)
                    >>> object.intersects(other_object)  # True
            )doc"
        )
        .def(
            "contains",
            &Object::contains,
            R"doc(
                Check if this object contains another object.

                Args:
                    object (Object): The object to check containment of.

                Returns:
                    bool: True if this object contains the other object.

                Example:
                    >>> object = Cone(Point(1.0, 2.0, 3.0), [0.0, 0.0, 1.0], Angle.degrees(30.0))
                    >>> other_object = Point(1.0, 2.0, 3.1)
                    >>> object.contains(other_object)  # True
            )doc"
        )

        .def(
            "as_point",
            +[](const Object& anObject) -> Point
            {
                return anObject.as<Point>();
            },
            R"doc(
                Convert the object to a point.

                Returns:
                    Point: The point.
            )doc"
        )
        .def(
            "as_point_set",
            +[](const Object& anObject) -> PointSet
            {
                return anObject.as<PointSet>();
            },
            R"doc(
                Convert the object to a point set.

                Returns:
                    PointSet: The point set.
            )doc"
        )
        .def(
            "as_line",
            +[](const Object& anObject) -> Line
            {
                return anObject.as<Line>();
            },
            R"doc(
                Convert the object to a line.

                Returns:
                    Line: The line.
            )doc"
        )
        .def(
            "as_ray",
            +[](const Object& anObject) -> Ray
            {
                return anObject.as<Ray>();
            },
            R"doc(
                Convert the object to a ray.

                Returns:
                    Ray: The ray.
            )doc"
        )
        .def(
            "as_segment",
            +[](const Object& anObject) -> Segment
            {
                return anObject.as<Segment>();
            },
            R"doc(
                Convert the object to a segment.

                Returns:
                    Segment: The segment.
            )doc"
        )
        .def(
            "as_line_string",
            +[](const Object& anObject) -> LineString
            {
                return anObject.as<LineString>();
            },
            R"doc(
                Convert the object to a line string.

                Returns:
                    LineString: The line string.
            )doc"
        )
        .def(
            "as_polygon",
            +[](const Object& anObject) -> Polygon
            {
                return anObject.as<Polygon>();
            },
            R"doc(
                Convert the object to a polygon.

                Returns:
                    Polygon: The polygon.
            )doc"
        )
        .def(
            "as_plane",
            +[](const Object& anObject) -> Plane
            {
                return anObject.as<Plane>();
            },
            R"doc(
                Convert the object to a plane.

                Returns:
                    Plane: The plane.
            )doc"
        )
        .def(
            "as_sphere",
            +[](const Object& anObject) -> Sphere
            {
                return anObject.as<Sphere>();
            },
            R"doc(
                Convert the object to a sphere.

                Returns:
                    Sphere: The sphere.
            )doc"
        )
        .def(
            "as_ellipsoid",
            +[](const Object& anObject) -> Ellipsoid
            {
                return anObject.as<Ellipsoid>();
            },
            R"doc(
                Convert the object to an ellipsoid.

                Returns:
                    Ellipsoid: The ellipsoid.
            )doc"
        )
        .def(
            "as_pyramid",
            +[](const Object& anObject) -> Pyramid
            {
                return anObject.as<Pyramid>();
            },
            R"doc(
                Convert the object to a pyramid.

                Returns:
                    Pyramid: The pyramid.
            )doc"
        )
        .def(
            "as_cone",
            +[](const Object& anObject) -> Cone
            {
                return anObject.as<Cone>();
            },
            R"doc(
                Convert the object to a cone.

                Returns:
                    Cone: The cone.
            )doc"
        )

        // .def("intersection_with", &Object::intersectionWith)
        .def(
            "apply_transformation",
            &Object::applyTransformation,
            arg("transformation"),
            R"doc(
                Apply a transformation to the object in place

                Args:
                    transformation (Transformation): The transformation to apply.
            )doc"
        )

        ;

    // Create "object" python submodule
    auto object = aModule.def_submodule("object");

    // Add object to python "object" submodules
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Point(object);
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_PointSet(object);
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Line(object);
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Ray(object);
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Segment(object);
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_LineString(object);
    // OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_MultiLineString(object) ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Plane(object);
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Polygon(object);
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Cuboid(object);
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Sphere(object);
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Ellipsoid(object);
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Pyramid(object);
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Cone(object);
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Composite(object);
}
