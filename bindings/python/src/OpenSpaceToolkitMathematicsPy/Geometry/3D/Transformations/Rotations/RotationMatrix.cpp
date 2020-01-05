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

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformations_Rotations_RotationMatrix ( )
{

    using namespace boost::python ;

    using ostk::core::types::Real ;
    using ostk::core::types::String ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::obj::Matrix3d ;
    using ostk::math::geom::d3::trf::rot::RotationMatrix ;

    scope in_RotationMatrix = class_<RotationMatrix>("RotationMatrix", init<Matrix3d>())

        .def(init<const Real&, const Real&, const Real&, const Real&, const Real&, const Real&, const Real&, const Real&, const Real&>())

        .def(self == self)
        .def(self != self)

        .def(self * self)
		.def(self * Vector3d())

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("is_defined", &RotationMatrix::isDefined)

        .def("get_row_at", &RotationMatrix::getRowAt)
        .def("get_column_at", &RotationMatrix::getColumnAt)
        .def("to_transposed", &RotationMatrix::toTransposed)
        .def("transpose", +[] (RotationMatrix& aRotationMatrix) -> void { aRotationMatrix.transpose() ; })

        .def("undefined", &RotationMatrix::Undefined).staticmethod("undefined")
        .def("unit", &RotationMatrix::Unit).staticmethod("unit")
        .def("rx", &RotationMatrix::RX).staticmethod("rx")
        .def("ry", &RotationMatrix::RY).staticmethod("ry")
        .def("rz", &RotationMatrix::RZ).staticmethod("rz")
        .def("rows", &RotationMatrix::Rows).staticmethod("rows")
        .def("columns", &RotationMatrix::Columns).staticmethod("columns")
        .def("quaternion", &RotationMatrix::Quaternion).staticmethod("quaternion")
        .def("rotation_vector", &RotationMatrix::RotationVector).staticmethod("rotation_vector")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
