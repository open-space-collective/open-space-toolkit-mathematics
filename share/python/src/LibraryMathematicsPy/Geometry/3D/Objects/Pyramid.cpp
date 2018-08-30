////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           LibraryMathematicsPy/Geometry/3D/Objects/Pyramid.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Intersection.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Pyramid.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_3D_Objects_Pyramid ( )
{

    using namespace boost::python ;

    using library::core::types::Size ;
    using library::core::types::Real ;

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
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::Intersection ;
    using library::math::geom::trf::rot::Quaternion ;

    scope in_Pyramid = class_<Pyramid, bases<Object>>("Pyramid", init<const Polygon&, const Point&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))
        
        .def("isDefined", &Pyramid::isDefined)
        .def("intersectsEllipsoid", +[] (const Pyramid& anPyramid, const Ellipsoid& anEllipsoid) -> bool { return anPyramid.intersects(anEllipsoid) ; })
        .def("intersectsEllipsoid", +[] (const Pyramid& anPyramid, const Ellipsoid& anEllipsoid, const Size aDiscretizationLevel) -> bool { return anPyramid.intersects(anEllipsoid, aDiscretizationLevel) ; })
        .def("containsEllipsoid", +[] (const Pyramid& anPyramid, const Ellipsoid& anEllipsoid) -> bool { return anPyramid.contains(anEllipsoid) ; })

        .def("getBase", &Pyramid::getBase)
        .def("getApex", &Pyramid::getApex)
        .def("getLateralFaceCount", &Pyramid::getLateralFaceCount)
        .def("getLateralFaceAt", &Pyramid::getLateralFaceAt)
        .def("getRaysOfLateralFaceAt", &Pyramid::getRaysOfLateralFaceAt)
        .def("getRaysOfLateralFaces", &Pyramid::getRaysOfLateralFaces)
        .def("intersectionWithEllipsoid", +[] (const Pyramid& anPyramid, const Ellipsoid& anEllipsoid) -> Intersection { return anPyramid.intersectionWith(anEllipsoid) ; })
        .def("intersectionWithEllipsoid", +[] (const Pyramid& anPyramid, const Ellipsoid& anEllipsoid, const bool onlyInSight) -> Intersection { return anPyramid.intersectionWith(anEllipsoid, onlyInSight) ; })
        .def("intersectionWithEllipsoid", +[] (const Pyramid& anPyramid, const Ellipsoid& anEllipsoid, const bool onlyInSight, const Size aDiscretizationLevel) -> Intersection { return anPyramid.intersectionWith(anEllipsoid, onlyInSight, aDiscretizationLevel) ; })
        .def("translate", &Pyramid::translate)
        .def("rotate", &Pyramid::rotate)
        
        .def("Undefined", &Pyramid::Undefined).staticmethod("Undefined")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////