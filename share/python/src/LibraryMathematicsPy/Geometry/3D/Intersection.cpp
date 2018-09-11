////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           LibraryMathematicsPy/Geometry/3D/Intersection.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Intersection.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_3D_Intersection ( )
{

    using namespace boost::python ;

    using library::core::types::Unique ;
    using library::core::ctnr::Array ;

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
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::Intersection ;

    // scope in_Intersection = class_<Intersection>("Intersection", init<const Array<Unique<Object>>>())
    scope in_Intersection = class_<Intersection>("Intersection", no_init)

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &Intersection::isDefined)
        .def("isEmpty", &Intersection::isEmpty)
        .def("isComplex", &Intersection::isComplex)

        .def("accessComposite", &Intersection::accessComposite, return_value_policy<reference_existing_object>())

        .def("getType", &Intersection::getType)
        
        .def("Undefined", &Intersection::Undefined).staticmethod("Undefined")
        .def("Empty", &Intersection::Empty).staticmethod("Empty")
        .def("Point", &Intersection::Point).staticmethod("Point")
        .def("PointSet", &Intersection::PointSet).staticmethod("PointSet")
        
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