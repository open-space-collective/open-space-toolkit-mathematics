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
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Line;
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::geometry::d3::object::LineString;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Sphere;
    using ostk::mathematics::geometry::d3::object::Ellipsoid;
    using ostk::mathematics::geometry::d3::object::Pyramid;

    // class_<Object, boost::noncopyable>("Object", no_init)
    class_<Object>(aModule, "Object")

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

        .def("is_defined", &Object::isDefined)
        .def(
            "is_point",
            +[](const Object& anObject) -> bool
            {
                return anObject.is<Point>();
            }
        )
        .def(
            "is_point_set",
            +[](const Object& anObject) -> bool
            {
                return anObject.is<PointSet>();
            }
        )
        .def(
            "is_line",
            +[](const Object& anObject) -> bool
            {
                return anObject.is<Line>();
            }
        )
        .def(
            "is_ray",
            +[](const Object& anObject) -> bool
            {
                return anObject.is<Ray>();
            }
        )
        .def(
            "is_segment",
            +[](const Object& anObject) -> bool
            {
                return anObject.is<Segment>();
            }
        )
        .def(
            "is_line_string",
            +[](const Object& anObject) -> bool
            {
                return anObject.is<LineString>();
            }
        )
        .def(
            "is_polygon",
            +[](const Object& anObject) -> bool
            {
                return anObject.is<Polygon>();
            }
        )
        .def(
            "is_plane",
            +[](const Object& anObject) -> bool
            {
                return anObject.is<Plane>();
            }
        )
        .def(
            "is_sphere",
            +[](const Object& anObject) -> bool
            {
                return anObject.is<Sphere>();
            }
        )
        .def(
            "is_ellipsoid",
            +[](const Object& anObject) -> bool
            {
                return anObject.is<Ellipsoid>();
            }
        )
        .def(
            "is_pyramid",
            +[](const Object& anObject) -> bool
            {
                return anObject.is<Pyramid>();
            }
        )
        .def("intersects", &Object::intersects)
        .def("contains", &Object::contains)

        .def(
            "as_point",
            +[](const Object& anObject) -> Point
            {
                return anObject.as<Point>();
            }
        )
        .def(
            "as_point_set",
            +[](const Object& anObject) -> PointSet
            {
                return anObject.as<PointSet>();
            }
        )
        .def(
            "as_line",
            +[](const Object& anObject) -> Line
            {
                return anObject.as<Line>();
            }
        )
        .def(
            "as_ray",
            +[](const Object& anObject) -> Ray
            {
                return anObject.as<Ray>();
            }
        )
        .def(
            "as_segment",
            +[](const Object& anObject) -> Segment
            {
                return anObject.as<Segment>();
            }
        )
        .def(
            "as_line_string",
            +[](const Object& anObject) -> LineString
            {
                return anObject.as<LineString>();
            }
        )
        .def(
            "as_polygon",
            +[](const Object& anObject) -> Polygon
            {
                return anObject.as<Polygon>();
            }
        )
        .def(
            "as_plane",
            +[](const Object& anObject) -> Plane
            {
                return anObject.as<Plane>();
            }
        )
        .def(
            "as_sphere",
            +[](const Object& anObject) -> Sphere
            {
                return anObject.as<Sphere>();
            }
        )
        .def(
            "as_ellipsoid",
            +[](const Object& anObject) -> Ellipsoid
            {
                return anObject.as<Ellipsoid>();
            }
        )
        .def(
            "as_pyramid",
            +[](const Object& anObject) -> Pyramid
            {
                return anObject.as<Pyramid>();
            }
        )

        // .def("intersection_with", &Object::intersectionWith)
        .def("apply_transformation", &Object::applyTransformation, arg("transformation"))

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
