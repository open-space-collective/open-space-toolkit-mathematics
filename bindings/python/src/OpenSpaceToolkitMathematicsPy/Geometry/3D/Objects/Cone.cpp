////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Cone.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Cone.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Cone ( )
{

    using namespace boost::python ;

    using ostk::core::types::Size ;
    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::Angle ;
    using ostk::math::geom::d3::Object ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::PointSet ;
    using ostk::math::geom::d3::objects::Line ;
    using ostk::math::geom::d3::objects::Ray ;
    using ostk::math::geom::d3::objects::Segment ;
    using ostk::math::geom::d3::objects::Plane ;
    using ostk::math::geom::d3::objects::Polygon ;
    using ostk::math::geom::d3::objects::Sphere ;
    using ostk::math::geom::d3::objects::Ellipsoid ;
    using ostk::math::geom::d3::objects::Cone ;
    using ostk::math::geom::d3::Intersection ;

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
