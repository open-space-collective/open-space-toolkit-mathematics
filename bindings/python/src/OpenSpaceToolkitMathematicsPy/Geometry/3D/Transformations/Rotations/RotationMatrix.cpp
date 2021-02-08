////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformations/Rotations/RotationMatrix.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformations_Rotations_RotationMatrix ( pybind11::module& aModule                  )
{

    using namespace pybind11 ;

    using ostk::core::types::Real ;
    using ostk::core::types::String ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::obj::Matrix3d ;
    using ostk::math::geom::d3::trf::rot::RotationMatrix ;

    class_<RotationMatrix>(aModule, "RotationMatrix")

        // Define constructors
        .def(init<Matrix3d>())

        .def(init<const Real&, const Real&, const Real&, const Real&, const Real&, const Real&, const Real&, const Real&, const Real&>())

        // Define methods
        .def(self == self)
        .def(self != self)

        .def(self * self)
		.def(self * Vector3d())

        .def("__str__", &(shiftToString<RotationMatrix>))
        .def("__repr__", &(shiftToString<RotationMatrix>))

        .def("is_defined", &RotationMatrix::isDefined)

        .def("get_row_at", &RotationMatrix::getRowAt)
        .def("get_column_at", &RotationMatrix::getColumnAt)
        .def("to_transposed", &RotationMatrix::toTransposed)
        .def("transpose", +[] (RotationMatrix& aRotationMatrix) -> void { aRotationMatrix.transpose() ; })

        // Define static methods
        .def_static("undefined", &RotationMatrix::Undefined)
        .def_static("unit", &RotationMatrix::Unit)
        .def_static("rx", &RotationMatrix::RX)
        .def_static("ry", &RotationMatrix::RY)
        .def_static("rz", &RotationMatrix::RZ)
        .def_static("rows", &RotationMatrix::Rows)
        .def_static("columns", &RotationMatrix::Columns)
        .def_static("quaternion", &RotationMatrix::Quaternion)
        .def_static("rotation_vector", &RotationMatrix::RotationVector)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
