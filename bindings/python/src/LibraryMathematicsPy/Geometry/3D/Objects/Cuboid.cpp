////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           LibraryMathematicsPy/Geometry/3D/Objects/Cuboid.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Intersection.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Cuboid.hpp>

#include <Library/Core/Types/Shared.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_3D_Objects_Cuboid ( )
{

    using namespace boost::python ;

    using library::core::types::Shared ;
    using library::core::types::Real ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::PointSet ;
    using library::math::geom::d3::objects::Line ;
    using library::math::geom::d3::objects::Ray ;
    using library::math::geom::d3::objects::Segment ;
    using library::math::geom::d3::objects::Plane ;
    using library::math::geom::d3::objects::Sphere ;
    using library::math::geom::d3::objects::Cuboid ;
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::Intersection ;
    using library::math::geom::d3::trf::rot::Quaternion ;

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
