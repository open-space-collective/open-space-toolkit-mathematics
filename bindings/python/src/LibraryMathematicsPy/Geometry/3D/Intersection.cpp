////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkitMathematicsPy/Geometry/3D/Intersection.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Intersection ( )
{

    using namespace boost::python ;

    using ostk::core::types::Unique ;
    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d3::Object ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::PointSet ;
    using ostk::math::geom::d3::objects::Line ;
    using ostk::math::geom::d3::objects::Ray ;
    using ostk::math::geom::d3::objects::Segment ;
    using ostk::math::geom::d3::objects::LineString ;
    using ostk::math::geom::d3::objects::Polygon ;
    using ostk::math::geom::d3::objects::Plane ;
    using ostk::math::geom::d3::objects::Sphere ;
    using ostk::math::geom::d3::objects::Ellipsoid ;
    using ostk::math::geom::d3::objects::Cuboid ;
    using ostk::math::geom::d3::objects::Pyramid ;
    using ostk::math::geom::d3::objects::Composite ;
    using ostk::math::geom::d3::Intersection ;

    // scope in_Intersection = class_<Intersection>("Intersection", init<const Array<Unique<Object>>>())
    scope in_Intersection = class_<Intersection>("Intersection", no_init)

        .def(self == self)
        .def(self != self)

        .def(self + self)
        .def(self += self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &Intersection::isDefined)
        .def("isEmpty", &Intersection::isEmpty)
        .def("isComplex", &Intersection::isComplex)

        .def("isPoint", +[] (const Intersection& anIntersection) -> bool { return anIntersection.is<Point>() ; })
        .def("isPointSet", +[] (const Intersection& anIntersection) -> bool { return anIntersection.is<PointSet>() ; })
        .def("isLine", +[] (const Intersection& anIntersection) -> bool { return anIntersection.is<Line>() ; })
        .def("isRay", +[] (const Intersection& anIntersection) -> bool { return anIntersection.is<Ray>() ; })
        .def("isSegment", +[] (const Intersection& anIntersection) -> bool { return anIntersection.is<Segment>() ; })
        .def("isLineString", +[] (const Intersection& anIntersection) -> bool { return anIntersection.is<LineString>() ; })
        .def("isPolygon", +[] (const Intersection& anIntersection) -> bool { return anIntersection.is<Polygon>() ; })
        .def("isPlane", +[] (const Intersection& anIntersection) -> bool { return anIntersection.is<Plane>() ; })
        .def("isSphere", +[] (const Intersection& anIntersection) -> bool { return anIntersection.is<Sphere>() ; })
        .def("isEllipsoid", +[] (const Intersection& anIntersection) -> bool { return anIntersection.is<Ellipsoid>() ; })
        .def("isPyramid", +[] (const Intersection& anIntersection) -> bool { return anIntersection.is<Pyramid>() ; })
        .def("isComposite", +[] (const Intersection& anIntersection) -> bool { return anIntersection.is<Composite>() ; })

        .def("asPoint", +[] (const Intersection& anIntersection) -> Point { return anIntersection.as<Point>() ; })
        .def("asPointSet", +[] (const Intersection& anIntersection) -> PointSet { return anIntersection.as<PointSet>() ; })
        .def("asLine", +[] (const Intersection& anIntersection) -> Line { return anIntersection.as<Line>() ; })
        .def("asRay", +[] (const Intersection& anIntersection) -> Ray { return anIntersection.as<Ray>() ; })
        .def("asSegment", +[] (const Intersection& anIntersection) -> Segment { return anIntersection.as<Segment>() ; })
        .def("asLineString", +[] (const Intersection& anIntersection) -> LineString { return anIntersection.as<LineString>() ; })
        .def("asPolygon", +[] (const Intersection& anIntersection) -> Polygon { return anIntersection.as<Polygon>() ; })
        .def("asPlane", +[] (const Intersection& anIntersection) -> Plane { return anIntersection.as<Plane>() ; })
        .def("asSphere", +[] (const Intersection& anIntersection) -> Sphere { return anIntersection.as<Sphere>() ; })
        .def("asEllipsoid", +[] (const Intersection& anIntersection) -> Ellipsoid { return anIntersection.as<Ellipsoid>() ; })
        .def("asPyramid", +[] (const Intersection& anIntersection) -> Pyramid { return anIntersection.as<Pyramid>() ; })
        .def("asComposite", +[] (const Intersection& anIntersection) -> Composite { return anIntersection.as<Composite>() ; })

        .def("accessComposite", &Intersection::accessComposite, return_value_policy<reference_existing_object>())

        .def("getType", &Intersection::getType)

        .def("Undefined", &Intersection::Undefined).staticmethod("Undefined")
        .def("Empty", &Intersection::Empty).staticmethod("Empty")
        .def("Point", &Intersection::Point).staticmethod("Point")
        .def("PointSet", &Intersection::PointSet).staticmethod("PointSet")
        .def("Line", &Intersection::Line).staticmethod("Line")
        .def("Ray", &Intersection::Ray).staticmethod("Ray")
        .def("Segment", &Intersection::Segment).staticmethod("Segment")

        .def("StringFromType", &Intersection::StringFromType).staticmethod("StringFromType")

    ;

    enum_<Intersection::Type>("Type")

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
