////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           LibraryMathematicsPy/Geometry/3D/Objects/Cone.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Intersection.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Cone.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_3D_Objects_Cone ( )
{

    using namespace boost::python ;

    using library::core::types::Size ;
    using library::core::types::Real ;

    using library::math::obj::Vector3d ;
    using library::math::geom::Angle ;
    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::PointSet ;
    using library::math::geom::d3::objects::Line ;
    using library::math::geom::d3::objects::Ray ;
    using library::math::geom::d3::objects::Segment ;
    using library::math::geom::d3::objects::Plane ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Sphere ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::d3::objects::Cone ;
    using library::math::geom::d3::Intersection ;

    scope in_Cone = class_<Cone, bases<Object>>("Cone", init<const Point&, const Vector3d&, const Angle&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))
        
        .def("isDefined", &Cone::isDefined)
        .def("intersectsEllipsoid", +[] (const Cone& aCone, const Ellipsoid& anEllipsoid) -> bool { return aCone.intersects(anEllipsoid) ; })
        .def("intersectsEllipsoid", +[] (const Cone& aCone, const Ellipsoid& anEllipsoid, const Size aDiscretizationLevel) -> bool { return aCone.intersects(anEllipsoid, aDiscretizationLevel) ; })

        .def("getApex", &Cone::getApex)
        .def("getAxis", &Cone::getAxis)
        .def("getAngle", &Cone::getAngle)
        .def("getRaysOfLateralSurface", &Cone::getRaysOfLateralSurface)
        .def("intersectionWithEllipsoid", +[] (const Cone& aCone, const Ellipsoid& anEllipsoid) -> Intersection { return aCone.intersectionWith(anEllipsoid) ; })
        .def("intersectionWithEllipsoid", +[] (const Cone& aCone, const Ellipsoid& anEllipsoid, const bool onlyInSight) -> Intersection { return aCone.intersectionWith(anEllipsoid, onlyInSight) ; })
        .def("intersectionWithEllipsoid", +[] (const Cone& aCone, const Ellipsoid& anEllipsoid, const bool onlyInSight, const Size aDiscretizationLevel) -> Intersection { return aCone.intersectionWith(anEllipsoid, onlyInSight, aDiscretizationLevel) ; })
        .def("applyTransformation", &Cone::applyTransformation)
        
        .def("Undefined", &Cone::Undefined).staticmethod("Undefined")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////