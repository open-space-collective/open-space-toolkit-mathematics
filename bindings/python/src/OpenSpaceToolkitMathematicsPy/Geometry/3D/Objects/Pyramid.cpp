////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Pyramid.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Pyramid.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Pyramid                     (      pybind11::module&  aModule                )
{

    using namespace pybind11 ;

    using ostk::core::types::Size ;
    using ostk::core::types::Real ;

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
    using ostk::math::geom::d3::objects::Pyramid ;
    using ostk::math::geom::d3::Intersection ;
    using ostk::math::geom::d3::trf::rot::Quaternion ;

    class_<Pyramid, Object>(aModule, "Pyramid")

        .def(init<const Polygon&, const Point&>())

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shift_to_string<Pyramid>))
        .def("__repr__", &(shift_to_string<Pyramid>))

        .def("is_defined", &Pyramid::isDefined)
        .def("intersects_ellipsoid", +[] (const Pyramid& aPyramid, const Ellipsoid& anEllipsoid) -> bool { return aPyramid.intersects(anEllipsoid) ; })
        .def("intersects_ellipsoid", +[] (const Pyramid& aPyramid, const Ellipsoid& anEllipsoid, const Size aDiscretizationLevel) -> bool { return aPyramid.intersects(anEllipsoid, aDiscretizationLevel) ; })
        .def("contains_point", +[] (const Pyramid& aPyramid, const Point& aPoint) -> bool { return aPyramid.contains(aPoint) ; })
        .def("contains_ellipsoid", +[] (const Pyramid& aPyramid, const Ellipsoid& anEllipsoid) -> bool { return aPyramid.contains(anEllipsoid) ; })

        .def("get_base", &Pyramid::getBase)
        .def("get_apex", &Pyramid::getApex)
        .def("get_lateral_face_count", &Pyramid::getLateralFaceCount)
        .def("get_lateral_face_at", &Pyramid::getLateralFaceAt)
        .def("get_rays_of_lateral_face_at", &Pyramid::getRaysOfLateralFaceAt)
        .def("get_rays_of_lateral_faces", &Pyramid::getRaysOfLateralFaces)
        .def("intersection_with_ellipsoid", +[] (const Pyramid& aPyramid, const Ellipsoid& anEllipsoid) -> Intersection { return aPyramid.intersectionWith(anEllipsoid) ; })
        .def("intersection_with_ellipsoid", +[] (const Pyramid& aPyramid, const Ellipsoid& anEllipsoid, const bool onlyInSight) -> Intersection { return aPyramid.intersectionWith(anEllipsoid, onlyInSight) ; })
        .def("intersection_with_ellipsoid", +[] (const Pyramid& aPyramid, const Ellipsoid& anEllipsoid, const bool onlyInSight, const Size aDiscretizationLevel) -> Intersection { return aPyramid.intersectionWith(anEllipsoid, onlyInSight, aDiscretizationLevel) ; })
        .def("apply_transformation", &Pyramid::applyTransformation)

        .def_static("undefined", &Pyramid::Undefined)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
