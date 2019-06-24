////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Mathematics
/// @file           LibraryMathematicsPy/Geometry/3D/Objects/Composite.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Intersection.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Composite.hpp>

#include <Library/Core/Types/Shared.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_3D_Objects_Composite ( )
{

    using namespace boost::python ;

    using library::core::types::Shared ;
    using library::core::types::Real ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::PointSet ;
    using library::math::geom::d3::objects::Line ;
    using library::math::geom::d3::objects::Ray ;
    using library::math::geom::d3::objects::Segment ;
    using library::math::geom::d3::objects::LineString ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Plane ;
    using library::math::geom::d3::objects::Sphere ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::d3::objects::Cuboid ;
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::objects::Composite ;
    using library::math::geom::d3::Intersection ;
    using library::math::geom::d3::trf::rot::Quaternion ;

    scope in_Composite = class_<Composite, Shared<Composite>, bases<Object>>("Composite", no_init)

        .def(self == self)
        .def(self == self)

        .def(self + self)
        .def(self += self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &Composite::isDefined)

        .def("isPoint", +[] (const Composite& aComposite) -> bool { return aComposite.is<Point>() ; })
        .def("isPointSet", +[] (const Composite& aComposite) -> bool { return aComposite.is<PointSet>() ; })
        .def("isLine", +[] (const Composite& aComposite) -> bool { return aComposite.is<Line>() ; })
        .def("isRay", +[] (const Composite& aComposite) -> bool { return aComposite.is<Ray>() ; })
        .def("isSegment", +[] (const Composite& aComposite) -> bool { return aComposite.is<Segment>() ; })
        .def("isLineString", +[] (const Composite& aComposite) -> bool { return aComposite.is<LineString>() ; })
        .def("isPolygon", +[] (const Composite& aComposite) -> bool { return aComposite.is<Polygon>() ; })
        .def("isPlane", +[] (const Composite& aComposite) -> bool { return aComposite.is<Plane>() ; })
        .def("isSphere", +[] (const Composite& aComposite) -> bool { return aComposite.is<Sphere>() ; })
        .def("isEllipsoid", +[] (const Composite& aComposite) -> bool { return aComposite.is<Ellipsoid>() ; })
        .def("isPyramid", +[] (const Composite& aComposite) -> bool { return aComposite.is<Pyramid>() ; })
        .def("isComposite", +[] (const Composite& aComposite) -> bool { return aComposite.is<Composite>() ; })

        .def("intersectsObject", +[] (const Composite& aComposite, const Object& anObject) -> bool { return aComposite.intersects(anObject) ; })
        .def("intersectsComposite", +[] (const Composite& aComposite, const Composite& anotherComposite) -> bool { return aComposite.intersects(anotherComposite) ; })
        .def("containsObject", +[] (const Composite& aComposite, const Object& anObject) -> bool { return aComposite.contains(anObject) ; })
        .def("containsComposite", +[] (const Composite& aComposite, const Composite& anotherComposite) -> bool { return aComposite.contains(anotherComposite) ; })

        .def("asPoint", +[] (const Composite& aComposite) -> Point { return aComposite.as<Point>() ; })
        .def("asPointSet", +[] (const Composite& aComposite) -> PointSet { return aComposite.as<PointSet>() ; })
        .def("asLine", +[] (const Composite& aComposite) -> Line { return aComposite.as<Line>() ; })
        .def("asRay", +[] (const Composite& aComposite) -> Ray { return aComposite.as<Ray>() ; })
        .def("asSegment", +[] (const Composite& aComposite) -> Segment { return aComposite.as<Segment>() ; })
        .def("asLineString", +[] (const Composite& aComposite) -> LineString { return aComposite.as<LineString>() ; })
        .def("asPolygon", +[] (const Composite& aComposite) -> Polygon { return aComposite.as<Polygon>() ; })
        .def("asPlane", +[] (const Composite& aComposite) -> Plane { return aComposite.as<Plane>() ; })
        .def("asSphere", +[] (const Composite& aComposite) -> Sphere { return aComposite.as<Sphere>() ; })
        .def("asEllipsoid", +[] (const Composite& aComposite) -> Ellipsoid { return aComposite.as<Ellipsoid>() ; })
        .def("asPyramid", +[] (const Composite& aComposite) -> Pyramid { return aComposite.as<Pyramid>() ; })
        .def("asComposite", +[] (const Composite& aComposite) -> Composite { return aComposite.as<Composite>() ; })

        .def("accessObjectAt", &Composite::accessObjectAt, return_value_policy<reference_existing_object>())
        .def("accessObjects", &Composite::accessObjects, return_value_policy<reference_existing_object>())
        .def("getObjectCount", &Composite::getObjectCount)
        .def("intersectionWithObject", +[] (const Composite& aComposite, const Object& anObject) -> Intersection { return aComposite.intersectionWith(anObject) ; })
        .def("intersectionWithComposite", +[] (const Composite& aComposite, const Composite& anotherComposite) -> Intersection { return aComposite.intersectionWith(anotherComposite) ; })

        .def("applyTransformation", &Composite::applyTransformation)

        .def("Undefined", &Composite::Undefined).staticmethod("Undefined")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
