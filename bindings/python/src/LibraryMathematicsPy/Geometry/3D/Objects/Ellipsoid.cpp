////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Ellipsoid.cpp
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

        .def("isDefined", &Ellipsoid::isDefined)
        .def("intersectsPoint", +[] (const Ellipsoid& anEllipsoid, const Point& aPoint) -> bool { return anEllipsoid.intersects(aPoint) ; })
        .def("intersectsPointSet", +[] (const Ellipsoid& anEllipsoid, const PointSet& aPointSet) -> bool { return anEllipsoid.intersects(aPointSet) ; })
        .def("intersectsLine", +[] (const Ellipsoid& anEllipsoid, const Line& aLine) -> bool { return anEllipsoid.intersects(aLine) ; })
        .def("intersectsRay", +[] (const Ellipsoid& anEllipsoid, const Ray& aRay) -> bool { return anEllipsoid.intersects(aRay) ; })
        .def("intersectsSegment", +[] (const Ellipsoid& anEllipsoid, const Segment& aSegment) -> bool { return anEllipsoid.intersects(aSegment) ; })
        .def("intersectsPlane", +[] (const Ellipsoid& anEllipsoid, const Plane& aPlane) -> bool { return anEllipsoid.intersects(aPlane) ; })
        // .def("intersectsSphere", +[] (const Ellipsoid& anEllipsoid, const Sphere& aSphere) -> bool { return anEllipsoid.intersects(aSphere) ; })
        // .def("intersectsEllipsoid", +[] (const Ellipsoid& anEllipsoid, const Ellipsoid& anOtherEllipsoid) -> bool { return anEllipsoid.intersects(anOtherEllipsoid) ; })
        // .def("intersectsPyramid", +[] (const Ellipsoid& anEllipsoid, const Pyramid& aPyramid) -> bool { return anEllipsoid.intersects(aPyramid) ; })
        .def("containsPoint", +[] (const Ellipsoid& anEllipsoid, const Point& aPoint) -> bool { return anEllipsoid.contains(aPoint) ; })
        .def("containsPointSet", +[] (const Ellipsoid& anEllipsoid, const PointSet& aPointSet) -> bool { return anEllipsoid.contains(aPointSet) ; })
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
        .def("intersectionWithLine", +[] (const Ellipsoid& anEllipsoid, const Line& aLine) -> Intersection { return anEllipsoid.intersectionWith(aLine) ; })
        .def("intersectionWithRay", +[] (const Ellipsoid& anEllipsoid, const Ray& aRay) -> Intersection { return anEllipsoid.intersectionWith(aRay) ; })
        .def("intersectionWithRay", +[] (const Ellipsoid& anEllipsoid, const Ray& aRay, const bool onlyInSight) -> Intersection { return anEllipsoid.intersectionWith(aRay, onlyInSight) ; })
        .def("intersectionWithSegment", +[] (const Ellipsoid& anEllipsoid, const Segment& aSegment) -> Intersection { return anEllipsoid.intersectionWith(aSegment) ; })
        .def("applyTransformation", &Ellipsoid::applyTransformation)

        .def("Undefined", &Ellipsoid::Undefined).staticmethod("Undefined")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
