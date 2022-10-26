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

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformations_Rotations_RotationVector ( pybind11::module& aModule                  )
{

    using namespace pybind11 ;

    using ostk::core::types::Integer ;
    using ostk::core::types::Real ;
    using ostk::core::types::String ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::Angle ;
    using ostk::math::geom::d3::trf::rot::RotationVector ;

    class_<RotationVector>(aModule, "RotationVector")

        // Define constructor
        .def(init<const Vector3d&, const Angle&>(), arg("axis"), arg("angle"))

        // Define methods
        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<RotationVector>))
        .def("__repr__", &(shiftToString<RotationVector>))

        .def("is_defined", &RotationVector::isDefined)

        .def("get_axis", &RotationVector::getAxis)
        .def("get_angle", &RotationVector::getAngle)
        .def("to_string", +[] (const RotationVector& aRotationVector) -> String { return aRotationVector.toString() ; })
        .def("to_string", +[] (const RotationVector& aRotationVector, const Integer& aPrecision) -> String { return aRotationVector.toString(aPrecision) ; })

        // Define static methods
        .def_static("undefined", &RotationVector::Undefined)
        .def_static("unit", &RotationVector::Unit)
        .def_static("x", &RotationVector::X, arg("angle"))
        .def_static("y", &RotationVector::Y, arg("angle"))
        .def_static("z", &RotationVector::Z, arg("angle"))
        .def_static("quaternion", &RotationVector::Quaternion, arg("quaternion"))
        .def_static("rotation_matrix", &RotationVector::RotationMatrix, arg("rotation_matrix"))

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
