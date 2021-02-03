////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects/Cuboid.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Cuboid.hpp>

#include <OpenSpaceToolkit/Core/Types/Shared.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects_Cuboid (        pybind11::module& aModule                                     )
{

    using namespace pybind11 ;

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

    //     scope in_Cuboid = class_<Cuboid, Shared<Cuboid>, bases<Object>>("Cuboid", no_init)
    class_<Cuboid, Object>(aModule, "Cuboid")

        .def("__init__",
                +[] (const Point& aCenter, const pybind11::list& anAxisList, const pybind11::list& anExtent) -> Shared<Cuboid>
                {

                    const std::array<Vector3d, 3> axes = { pybind11::cast<Vector3d>(anAxisList[0]), pybind11::cast<Vector3d>(anAxisList[1]), pybind11::cast<Vector3d>(anAxisList[2]) } ;
                    const std::array<Real, 3> extent = { pybind11::cast<Real>(anExtent[0]), pybind11::cast<Real>(anExtent[1]), pybind11::cast<Real>(anExtent[2]) } ;

                    return std::make_shared<Cuboid>(aCenter, axes, extent) ;

                }
        )

        // .def(init<const Point&, const std::array<Vector3d, 3>&, const std::array<Real, 3>&>())

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Cuboid>))
        .def("__repr__", &(shiftToString<Cuboid>))

        .def("is_defined", &Cuboid::isDefined)
        .def("is_near", &Cuboid::isNear)
        .def("intersects_point", +[] (const Cuboid& aCuboid, const Point& aPoint) -> bool { return aCuboid.intersects(aPoint) ; })
        .def("intersects_point_set", +[] (const Cuboid& aCuboid, const PointSet& aPointSet) -> bool { return aCuboid.intersects(aPointSet) ; })
        .def("intersects_line", +[] (const Cuboid& aCuboid, const Line& aLine) -> bool { return aCuboid.intersects(aLine) ; })
        .def("intersects_cuboid", +[] (const Cuboid& aFirstCuboid, const Cuboid& aSecondCuboid) -> bool { return aFirstCuboid.intersects(aSecondCuboid) ; })

        .def("get_center", &Cuboid::getCenter)
        .def("get_first_axis", &Cuboid::getFirstAxis)
        .def("get_second_axis", &Cuboid::getSecondAxis)
        .def("get_third_axis", &Cuboid::getThirdAxis)
        .def("get_first_extent", &Cuboid::getFirstExtent)
        .def("get_second_extent", &Cuboid::getSecondExtent)
        .def("get_third_extent", &Cuboid::getThirdExtent)
        .def("get_vertices", &Cuboid::getVertices)
        .def("apply_transformation", &Cuboid::applyTransformation)

        .def_static("undefined", &Cuboid::Undefined)
        .def_static("cube", &Cuboid::Cube)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
