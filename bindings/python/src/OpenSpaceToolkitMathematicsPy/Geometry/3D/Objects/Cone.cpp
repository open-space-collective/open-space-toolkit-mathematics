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

        .def("is_defined", &Cone::isDefined)
        .def("intersects_ellipsoid", +[] (const Cone& aCone, const Ellipsoid& anEllipsoid) -> bool { return aCone.intersects(anEllipsoid) ; })
        .def("intersects_ellipsoid", +[] (const Cone& aCone, const Ellipsoid& anEllipsoid, const Size aDiscretizationLevel) -> bool { return aCone.intersects(anEllipsoid, aDiscretizationLevel) ; })

        .def("get_apex", &Cone::getApex)
        .def("get_axis", &Cone::getAxis)
        .def("get_angle", &Cone::getAngle)
        .def("get_rays_of_lateral_surface", &Cone::getRaysOfLateralSurface)
        .def("intersection_with_ellipsoid", +[] (const Cone& aCone, const Ellipsoid& anEllipsoid) -> Intersection { return aCone.intersectionWith(anEllipsoid) ; })
        .def("intersection_with_ellipsoid", +[] (const Cone& aCone, const Ellipsoid& anEllipsoid, const bool onlyInSight) -> Intersection { return aCone.intersectionWith(anEllipsoid, onlyInSight) ; })
        .def("intersection_with_ellipsoid", +[] (const Cone& aCone, const Ellipsoid& anEllipsoid, const bool onlyInSight, const Size aDiscretizationLevel) -> Intersection { return aCone.intersectionWith(anEllipsoid, onlyInSight, aDiscretizationLevel) ; })
        .def("apply_transformation", &Cone::applyTransformation)

        .def("undefined", &Cone::Undefined).staticmethod("undefined")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
