////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformations/Rotations/RotationMatrix.cpp
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
