////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           LibraryMathematicsPy/Geometry/Transformations/Rotations/RotationMatrix.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationMatrix.hpp>
#include <Library/Mathematics/Geometry/Transformations/Rotations/Quaternion.hpp>
#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationVector.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_Transformations_Rotations_RotationMatrix ( )
{

    using namespace boost::python ;

    using library::core::types::Real ;
    using library::core::types::String ;
    
    using library::math::obj::Vector3d ;
    using library::math::obj::Matrix3d ;
    using library::math::geom::trf::rot::RotationMatrix ;

    scope in_RotationMatrix = class_<RotationMatrix>("RotationMatrix", init<Matrix3d>())

        .def(self == self)
        .def(self != self)

        .def(self * self)
		.def(self * Vector3d())

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &RotationMatrix::isDefined)

        .def("getRowAt", &RotationMatrix::getRowAt)
        .def("getColumnAt", &RotationMatrix::getColumnAt)
        .def("toTransposed", &RotationMatrix::toTransposed)
        .def("transpose", +[] (RotationMatrix& aRotationMatrix) -> void { aRotationMatrix.transpose() ; })

        .def("Undefined", &RotationMatrix::Undefined).staticmethod("Undefined")
        .def("Unit", &RotationMatrix::Unit).staticmethod("Unit")
        .def("RX", &RotationMatrix::RX).staticmethod("RX")
        .def("RY", &RotationMatrix::RY).staticmethod("RY")
        .def("RZ", &RotationMatrix::RZ).staticmethod("RZ")
        .def("Rows", &RotationMatrix::Rows).staticmethod("Rows")
        .def("Columns", &RotationMatrix::Columns).staticmethod("Columns")
        .def("Quaternion", &RotationMatrix::Quaternion).staticmethod("Quaternion")
        .def("RotationVector", &RotationMatrix::RotationVector).staticmethod("RotationVector")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////