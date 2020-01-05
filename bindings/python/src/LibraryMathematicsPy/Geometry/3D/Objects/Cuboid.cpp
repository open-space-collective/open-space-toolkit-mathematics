////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Cuboid.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Cuboid.hpp>

#include <OpenSpaceToolkit/Core/Types/Shared.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Cuboid ( )
{

    using namespace boost::python ;

    using ostk::core::types::Shared ;
    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::Object ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::PointSet ;
    using ostk::math::geom::d3::objects::Line ;
    using ostk::math::geom::d3::objects::Ray ;
    using ostk::math::geom::d3::objects::Segment ;
    using ostk::math::geom::d3::objects::Plane ;
    using ostk::math::geom::d3::objects::Sphere ;
    using ostk::math::geom::d3::objects::Cuboid ;
    using ostk::math::geom::d3::objects::Pyramid ;
    using ostk::math::geom::d3::Intersection ;
    using ostk::math::geom::d3::trf::rot::Quaternion ;

    scope in_Cuboid = class_<Cuboid, Shared<Cuboid>, bases<Object>>("Cuboid", no_init)

        .def
        (
            "__init__",
            make_constructor
            (
                +[] (const Point& aCenter, const boost::python::list& anAxisList, const boost::python::list& anExtent) -> Shared<Cuboid>
                {

                    const std::array<Vector3d, 3> axes = { boost::python::extract<Vector3d>(anAxisList[0]), boost::python::extract<Vector3d>(anAxisList[1]), boost::python::extract<Vector3d>(anAxisList[2]) } ;
                    const std::array<Real, 3> extent = { boost::python::extract<Real>(anExtent[0]), boost::python::extract<Real>(anExtent[1]), boost::python::extract<Real>(anExtent[2]) } ;

                    return std::make_shared<Cuboid>(aCenter, axes, extent) ;

                }
            )
        )

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &Cuboid::isDefined)
        .def("isNear", &Cuboid::isNear)
        .def("intersectsPoint", +[] (const Cuboid& aCuboid, const Point& aPoint) -> bool { return aCuboid.intersects(aPoint) ; })
        .def("intersectsPointSet", +[] (const Cuboid& aCuboid, const PointSet& aPointSet) -> bool { return aCuboid.intersects(aPointSet) ; })
        .def("intersectsLine", +[] (const Cuboid& aCuboid, const Line& aLine) -> bool { return aCuboid.intersects(aLine) ; })
        .def("intersectsCuboid", +[] (const Cuboid& aFirstCuboid, const Cuboid& aSecondCuboid) -> bool { return aFirstCuboid.intersects(aSecondCuboid) ; })

        .def("getCenter", &Cuboid::getCenter)
        .def("getFirstAxis", &Cuboid::getFirstAxis)
        .def("getSecondAxis", &Cuboid::getSecondAxis)
        .def("getThirdAxis", &Cuboid::getThirdAxis)
        .def("getFirstExtent", &Cuboid::getFirstExtent)
        .def("getSecondExtent", &Cuboid::getSecondExtent)
        .def("getThirdExtent", &Cuboid::getThirdExtent)
        .def("getVertices", &Cuboid::getVertices)
        .def("applyTransformation", &Cuboid::applyTransformation)

        .def("Undefined", &Cuboid::Undefined).staticmethod("Undefined")
        .def("Cube", &Cuboid::Cube).staticmethod("Cube")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
