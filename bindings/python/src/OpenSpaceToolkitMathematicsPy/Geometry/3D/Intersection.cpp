// Copyright © Loft Orbital Solutions Inc.

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Intersection(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::types::Unique;
    using ostk::core::ctnr::Array;

    using ostk::math::geom::d3::Object;
    using ostk::math::geom::d3::objects::Point;
    using ostk::math::geom::d3::objects::PointSet;
    using ostk::math::geom::d3::objects::Line;
    using ostk::math::geom::d3::objects::Ray;
    using ostk::math::geom::d3::objects::Segment;
    using ostk::math::geom::d3::objects::LineString;
    using ostk::math::geom::d3::objects::Polygon;
    using ostk::math::geom::d3::objects::Plane;
    using ostk::math::geom::d3::objects::Sphere;
    using ostk::math::geom::d3::objects::Ellipsoid;
    using ostk::math::geom::d3::objects::Cuboid;
    using ostk::math::geom::d3::objects::Pyramid;
    using ostk::math::geom::d3::objects::Composite;
    using ostk::math::geom::d3::Intersection;

    // scope in_Intersection = class_<Intersection>("Intersection", init<const Array<Unique<Object>>>())
    class_<Intersection> intersection(aModule, "Intersection");

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

        .def("is_defined", &Intersection::isDefined)
        .def("is_empty", &Intersection::isEmpty)
        .def("is_complex", &Intersection::isComplex)

        .def(
            "is_point",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Point>();
            }
        )
        .def(
            "is_point_set",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<PointSet>();
            }
        )
        .def(
            "is_line",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Line>();
            }
        )
        .def(
            "is_ray",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Ray>();
            }
        )
        .def(
            "is_segment",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Segment>();
            }
        )
        .def(
            "is_line_string",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<LineString>();
            }
        )
        .def(
            "is_polygon",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Polygon>();
            }
        )
        .def(
            "is_plane",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Plane>();
            }
        )
        .def(
            "is_sphere",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Sphere>();
            }
        )
        .def(
            "is_ellipsoid",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Ellipsoid>();
            }
        )
        .def(
            "is_pyramid",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Pyramid>();
            }
        )
        .def(
            "is_composite",
            +[](const Intersection& anIntersection) -> bool
            {
                return anIntersection.is<Composite>();
            }
        )

        .def(
            "as_point",
            +[](const Intersection& anIntersection) -> Point
            {
                return anIntersection.as<Point>();
            }
        )
        .def(
            "as_point_set",
            +[](const Intersection& anIntersection) -> PointSet
            {
                return anIntersection.as<PointSet>();
            }
        )
        .def(
            "as_line",
            +[](const Intersection& anIntersection) -> Line
            {
                return anIntersection.as<Line>();
            }
        )
        .def(
            "as_ray",
            +[](const Intersection& anIntersection) -> Ray
            {
                return anIntersection.as<Ray>();
            }
        )
        .def(
            "as_segment",
            +[](const Intersection& anIntersection) -> Segment
            {
                return anIntersection.as<Segment>();
            }
        )
        .def(
            "as_line_string",
            +[](const Intersection& anIntersection) -> LineString
            {
                return anIntersection.as<LineString>();
            }
        )
        .def(
            "as_polygon",
            +[](const Intersection& anIntersection) -> Polygon
            {
                return anIntersection.as<Polygon>();
            }
        )
        .def(
            "as_plane",
            +[](const Intersection& anIntersection) -> Plane
            {
                return anIntersection.as<Plane>();
            }
        )
        .def(
            "as_sphere",
            +[](const Intersection& anIntersection) -> Sphere
            {
                return anIntersection.as<Sphere>();
            }
        )
        .def(
            "as_ellipsoid",
            +[](const Intersection& anIntersection) -> Ellipsoid
            {
                return anIntersection.as<Ellipsoid>();
            }
        )
        .def(
            "as_pyramid",
            +[](const Intersection& anIntersection) -> Pyramid
            {
                return anIntersection.as<Pyramid>();
            }
        )
        .def(
            "as_composite",
            +[](const Intersection& anIntersection) -> Composite
            {
                return anIntersection.as<Composite>();
            }
        )

        // .def("access_composite", &Intersection::accessComposite, return_value_policy<reference_existing_object>())
        .def("access_composite", &Intersection::accessComposite, return_value_policy::reference)

        .def("get_type", &Intersection::getType)

        // Define static methods
        .def_static("undefined", &Intersection::Undefined)
        .def_static("empty", &Intersection::Empty)
        .def_static("point", &Intersection::Point, arg("point"))
        .def_static("point_set", &Intersection::PointSet, arg("point_set"))
        .def_static("line", &Intersection::Line, arg("line"))
        .def_static("ray", &Intersection::Ray, arg("ray"))
        .def_static("segment", &Intersection::Segment, arg("segment"))

        .def_static("string_from_type", &Intersection::StringFromType, arg("type"))

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
