////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           LibraryMathematicsPy/Geometry/3D/Objects/Ellipsoid.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_3D_Objects_Ellipsoid ( )
{

    using namespace boost::python ;

    using library::core::types::Real ;

    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Segment ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::trf::rot::Quaternion ;

    scope in_Ellipsoid = class_<Ellipsoid, bases<Object>>("Ellipsoid", init<const Point&, const Real&, const Real&, const Real&, const Quaternion&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))
        
        .def("isDefined", &Ellipsoid::isDefined)
        .def("intersects", &Ellipsoid::intersects)
        .def("containsPoint", +[] (const Ellipsoid& anEllipsoid, const Point& aPoint) -> bool { return anEllipsoid.contains(aPoint) ; })
        .def("containsSegment", +[] (const Ellipsoid& anEllipsoid, const Segment& aSegment) -> bool { return anEllipsoid.contains(aSegment) ; })

        .def("getCenter", &Ellipsoid::getCenter)
        .def("getFirstPrincipalSemiAxis", &Ellipsoid::getFirstPrincipalSemiAxis)
        .def("getSecondPrincipalSemiAxis", &Ellipsoid::getSecondPrincipalSemiAxis)
        .def("getThirdPrincipalSemiAxis", &Ellipsoid::getThirdPrincipalSemiAxis)
        .def("getFirstAxis", &Ellipsoid::getFirstAxis)
        .def("getSecondAxis", &Ellipsoid::getSecondAxis)
        .def("getThirdAxis", &Ellipsoid::getThirdAxis)
        .def("getOrientation", &Ellipsoid::getOrientation)
        .def("getMatrix", &Ellipsoid::getMatrix)
        .def("translate", &Ellipsoid::translate)
        .def("rotate", &Ellipsoid::rotate)
        
        .def("Undefined", &Ellipsoid::Undefined).staticmethod("Undefined")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////