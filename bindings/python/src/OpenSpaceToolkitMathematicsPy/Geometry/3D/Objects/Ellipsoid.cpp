////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Ellipsoid.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Ellipsoid ( )
{

    using namespace boost::python ;

    using ostk::core::types::Real ;

    using ostk::math::geom::d3::Object ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::PointSet ;
    using ostk::math::geom::d3::objects::Line ;
    using ostk::math::geom::d3::objects::Ray ;
    using ostk::math::geom::d3::objects::Segment ;
    using ostk::math::geom::d3::objects::Plane ;
    using ostk::math::geom::d3::objects::Sphere ;
    using ostk::math::geom::d3::objects::Ellipsoid ;
    using ostk::math::geom::d3::objects::Pyramid ;
    using ostk::math::geom::d3::Intersection ;
    using ostk::math::geom::d3::trf::rot::Quaternion ;

    scope in_Ellipsoid = class_<Ellipsoid, bases<Object>>("Ellipsoid", init<const Point&, const Real&, const Real&, const Real&, const Quaternion&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("is_defined", &Ellipsoid::isDefined)
        .def("intersects_point", +[] (const Ellipsoid& anEllipsoid, const Point& aPoint) -> bool { return anEllipsoid.intersects(aPoint) ; })
        .def("intersects_point_set", +[] (const Ellipsoid& anEllipsoid, const PointSet& aPointSet) -> bool { return anEllipsoid.intersects(aPointSet) ; })
        .def("intersects_line", +[] (const Ellipsoid& anEllipsoid, const Line& aLine) -> bool { return anEllipsoid.intersects(aLine) ; })
        .def("intersects_ray", +[] (const Ellipsoid& anEllipsoid, const Ray& aRay) -> bool { return anEllipsoid.intersects(aRay) ; })
        .def("intersects_segment", +[] (const Ellipsoid& anEllipsoid, const Segment& aSegment) -> bool { return anEllipsoid.intersects(aSegment) ; })
        .def("intersects_plane", +[] (const Ellipsoid& anEllipsoid, const Plane& aPlane) -> bool { return anEllipsoid.intersects(aPlane) ; })
        // .def("intersects_sphere", +[] (const Ellipsoid& anEllipsoid, const Sphere& aSphere) -> bool { return anEllipsoid.intersects(aSphere) ; })
        // .def("intersects_ellipsoid", +[] (const Ellipsoid& anEllipsoid, const Ellipsoid& anOtherEllipsoid) -> bool { return anEllipsoid.intersects(anOtherEllipsoid) ; })
        // .def("intersects_pyramid", +[] (const Ellipsoid& anEllipsoid, const Pyramid& aPyramid) -> bool { return anEllipsoid.intersects(aPyramid) ; })
        .def("contains_point", +[] (const Ellipsoid& anEllipsoid, const Point& aPoint) -> bool { return anEllipsoid.contains(aPoint) ; })
        .def("contains_point_set", +[] (const Ellipsoid& anEllipsoid, const PointSet& aPointSet) -> bool { return anEllipsoid.contains(aPointSet) ; })
        .def("contains_segment", +[] (const Ellipsoid& anEllipsoid, const Segment& aSegment) -> bool { return anEllipsoid.contains(aSegment) ; })

        .def("get_center", &Ellipsoid::getCenter)
        .def("get_first_principal_semi_axis", &Ellipsoid::getFirstPrincipalSemiAxis)
        .def("get_second_principal_semi_axis", &Ellipsoid::getSecondPrincipalSemiAxis)
        .def("get_third_principal_semi_axis", &Ellipsoid::getThirdPrincipalSemiAxis)
        .def("get_first_axis", &Ellipsoid::getFirstAxis)
        .def("get_second_axis", &Ellipsoid::getSecondAxis)
        .def("get_third_axis", &Ellipsoid::getThirdAxis)
        .def("get_orientation", &Ellipsoid::getOrientation)
        .def("get_matrix", &Ellipsoid::getMatrix)
        .def("intersection_with_line", +[] (const Ellipsoid& anEllipsoid, const Line& aLine) -> Intersection { return anEllipsoid.intersectionWith(aLine) ; })
        .def("intersection_with_ray", +[] (const Ellipsoid& anEllipsoid, const Ray& aRay) -> Intersection { return anEllipsoid.intersectionWith(aRay) ; })
        .def("intersection_with_ray", +[] (const Ellipsoid& anEllipsoid, const Ray& aRay, const bool onlyInSight) -> Intersection { return anEllipsoid.intersectionWith(aRay, onlyInSight) ; })
        .def("intersection_with_segment", +[] (const Ellipsoid& anEllipsoid, const Segment& aSegment) -> Intersection { return anEllipsoid.intersectionWith(aSegment) ; })
        .def("apply_transformation", &Ellipsoid::applyTransformation)

        .def("undefined", &Ellipsoid::Undefined).staticmethod("undefined")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
