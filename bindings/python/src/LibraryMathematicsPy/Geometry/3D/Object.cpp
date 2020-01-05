////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           LibraryMathematicsPy/Geometry/3D/Object.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_3D_Object     ( )
{

    using namespace boost::python ;

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
    using ostk::math::geom::d3::objects::Pyramid ;

    scope in_Object = class_<Object, boost::noncopyable>("Object", no_init)

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &Object::isDefined)
        .def("isPoint", +[] (const Object& anObject) -> bool { return anObject.is<Point>() ; })
        .def("isPointSet", +[] (const Object& anObject) -> bool { return anObject.is<PointSet>() ; })
        .def("isLine", +[] (const Object& anObject) -> bool { return anObject.is<Line>() ; })
        .def("isRay", +[] (const Object& anObject) -> bool { return anObject.is<Ray>() ; })
        .def("isSegment", +[] (const Object& anObject) -> bool { return anObject.is<Segment>() ; })
        .def("isLineString", +[] (const Object& anObject) -> bool { return anObject.is<LineString>() ; })
        .def("isPolygon", +[] (const Object& anObject) -> bool { return anObject.is<Polygon>() ; })
        .def("isPlane", +[] (const Object& anObject) -> bool { return anObject.is<Plane>() ; })
        .def("isSphere", +[] (const Object& anObject) -> bool { return anObject.is<Sphere>() ; })
        .def("isEllipsoid", +[] (const Object& anObject) -> bool { return anObject.is<Ellipsoid>() ; })
        .def("isPyramid", +[] (const Object& anObject) -> bool { return anObject.is<Pyramid>() ; })
        .def("intersects", &Object::intersects)
        .def("contains", &Object::contains)

        .def("asPoint", +[] (const Object& anObject) -> Point { return anObject.as<Point>() ; })
        .def("asPointSet", +[] (const Object& anObject) -> PointSet { return anObject.as<PointSet>() ; })
        .def("asLine", +[] (const Object& anObject) -> Line { return anObject.as<Line>() ; })
        .def("asRay", +[] (const Object& anObject) -> Ray { return anObject.as<Ray>() ; })
        .def("asSegment", +[] (const Object& anObject) -> Segment { return anObject.as<Segment>() ; })
        .def("asLineString", +[] (const Object& anObject) -> LineString { return anObject.as<LineString>() ; })
        .def("asPolygon", +[] (const Object& anObject) -> Polygon { return anObject.as<Polygon>() ; })
        .def("asPlane", +[] (const Object& anObject) -> Plane { return anObject.as<Plane>() ; })
        .def("asSphere", +[] (const Object& anObject) -> Sphere { return anObject.as<Sphere>() ; })
        .def("asEllipsoid", +[] (const Object& anObject) -> Ellipsoid { return anObject.as<Ellipsoid>() ; })
        .def("asPyramid", +[] (const Object& anObject) -> Pyramid { return anObject.as<Pyramid>() ; })

        // .def("intersectionWith", &Object::intersectionWith)
        .def("applyTransformation", &Object::applyTransformation)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
