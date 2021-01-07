////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/3D/Object.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Object                     (    pybind11::module&                     aModule        )
{

    using namespace pybind11 ;

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

    // class_<Object, boost::noncopyable>("Object", no_init)
    class_<Object>(aModule, "Object")

        // no init

        // Define methods
        // .def(self == self)
        // .def(self != self)
        .def("__eq__", [](const Object &self, const Object &other){ return self == other; })
        .def("__ne__", [](const Object &self, const Object &other){ return self != other; })

        .def("__str__", &(shift_to_string<Object>))
        .def("__repr__", &(shift_to_string<Object>))

        .def("is_defined", &Object::isDefined)
        .def("is_point", +[] (const Object& anObject) -> bool { return anObject.is<Point>() ; })
        .def("is_point_set", +[] (const Object& anObject) -> bool { return anObject.is<PointSet>() ; })
        .def("is_line", +[] (const Object& anObject) -> bool { return anObject.is<Line>() ; })
        .def("is_ray", +[] (const Object& anObject) -> bool { return anObject.is<Ray>() ; })
        .def("is_segment", +[] (const Object& anObject) -> bool { return anObject.is<Segment>() ; })
        .def("is_line_string", +[] (const Object& anObject) -> bool { return anObject.is<LineString>() ; })
        .def("is_polygon", +[] (const Object& anObject) -> bool { return anObject.is<Polygon>() ; })
        .def("is_plane", +[] (const Object& anObject) -> bool { return anObject.is<Plane>() ; })
        .def("is_sphere", +[] (const Object& anObject) -> bool { return anObject.is<Sphere>() ; })
        .def("is_ellipsoid", +[] (const Object& anObject) -> bool { return anObject.is<Ellipsoid>() ; })
        .def("is_pyramid", +[] (const Object& anObject) -> bool { return anObject.is<Pyramid>() ; })
        .def("intersects", &Object::intersects)
        .def("contains", &Object::contains)

        .def("as_point", +[] (const Object& anObject) -> Point { return anObject.as<Point>() ; })
        .def("as_point_set", +[] (const Object& anObject) -> PointSet { return anObject.as<PointSet>() ; })
        .def("as_line", +[] (const Object& anObject) -> Line { return anObject.as<Line>() ; })
        .def("as_ray", +[] (const Object& anObject) -> Ray { return anObject.as<Ray>() ; })
        .def("as_segment", +[] (const Object& anObject) -> Segment { return anObject.as<Segment>() ; })
        .def("as_line_string", +[] (const Object& anObject) -> LineString { return anObject.as<LineString>() ; })
        .def("as_polygon", +[] (const Object& anObject) -> Polygon { return anObject.as<Polygon>() ; })
        .def("as_plane", +[] (const Object& anObject) -> Plane { return anObject.as<Plane>() ; })
        .def("as_sphere", +[] (const Object& anObject) -> Sphere { return anObject.as<Sphere>() ; })
        .def("as_ellipsoid", +[] (const Object& anObject) -> Ellipsoid { return anObject.as<Ellipsoid>() ; })
        .def("as_pyramid", +[] (const Object& anObject) -> Pyramid { return anObject.as<Pyramid>() ; })

        // .def("intersection_with", &Object::intersectionWith)
        .def("apply_transformation", &Object::applyTransformation)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
