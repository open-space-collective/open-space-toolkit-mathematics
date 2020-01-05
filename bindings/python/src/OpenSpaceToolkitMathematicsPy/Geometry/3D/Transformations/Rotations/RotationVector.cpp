////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformations/Rotations/RotationVector.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformations_Rotations_RotationVector ( )
{

    using namespace boost::python ;

    using ostk::core::types::Integer ;
    using ostk::core::types::Real ;
    using ostk::core::types::String ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::Angle ;
    using ostk::math::geom::d3::trf::rot::RotationVector ;

    scope in_RotationVector = class_<RotationVector>("RotationVector", init<const Vector3d&, const Angle&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &RotationVector::isDefined)

        .def("getAxis", &RotationVector::getAxis)
        .def("getAngle", &RotationVector::getAngle)
        .def("toString", +[] (const RotationVector& aRotationVector) -> String { return aRotationVector.toString() ; })
        .def("toString", +[] (const RotationVector& aRotationVector, const Integer& aPrecision) -> String { return aRotationVector.toString(aPrecision) ; })

        .def("Undefined", &RotationVector::Undefined)
        .def("Unit", &RotationVector::Unit).staticmethod("Unit")
        .def("X", &RotationVector::X).staticmethod("X")
        .def("Y", &RotationVector::Y).staticmethod("Y")
        .def("Z", &RotationVector::Z).staticmethod("Z")
        .def("Quaternion", &RotationVector::Quaternion).staticmethod("Quaternion")
        .def("RotationMatrix", &RotationVector::RotationMatrix).staticmethod("RotationMatrix")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////