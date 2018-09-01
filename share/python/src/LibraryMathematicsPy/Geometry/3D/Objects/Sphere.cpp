////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           LibraryMathematicsPy/Geometry/3D/Objects/Sphere.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Objects/Sphere.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_3D_Objects_Sphere ( )
{

    using namespace boost::python ;

    using library::core::types::Real ;

    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Sphere ;

    scope in_Sphere = class_<Sphere, bases<Object>>("Sphere", init<const Point&, const Real&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))
        
        .def("isDefined", &Sphere::isDefined)
        .def("isUnitary", &Sphere::isUnitary)

        .def("getCenter", &Sphere::getCenter)
        .def("getRadius", &Sphere::getRadius)
        .def("applyTransformation", &Sphere::applyTransformation)
        
        .def("Undefined", &Sphere::Undefined).staticmethod("Undefined")
        .def("Unit", &Sphere::Unit).staticmethod("Unit")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////