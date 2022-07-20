////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformations/Rotations/Quaternion.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::ctnr::Array ;
using ostk::math::geom::d3::trf::rot::Quaternion ;

void                            set_quaternion_array                        (   const   Array<Quaternion>&          anArray                                     )
{

    (void) anArray ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformations_Rotations_Quaternion ( pybind11::module& aModule                      )
{
    using namespace pybind11 ;

    using ostk::core::types::Real ;
    using ostk::core::types::String ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::obj::Vector4d ;
    using ostk::math::geom::d3::trf::rot::Quaternion ;

    class_<Quaternion> quaternion(aModule, "Quaternion") ;

    quaternion.def(init<const Real&, const Real&, const Real&, const Real&, const Quaternion::Format&>())

        .def(init<const Vector4d&, const Quaternion::Format&>())
        .def(init<const Vector3d&, const Real&>())

        .def(self == self)
        .def(self != self)

		.def(self + self)
		.def(self * self)
		.def(self * Vector3d())

		.def(self / self)

        .def("__str__", &(shiftToString<Quaternion>))
        .def("__repr__", +[] (const Quaternion& aQuaternion) -> std::string { return aQuaternion.toString() ; })

        .def("is_defined", &Quaternion::isDefined)
        .def("is_unitary", &Quaternion::isUnitary)
        .def("is_near", &Quaternion::isNear)

        .def("x", &Quaternion::x)
        .def("y", &Quaternion::y)
        .def("z", &Quaternion::z)
        .def("s", &Quaternion::s)
        .def("get_vector_part", &Quaternion::getVectorPart)
        .def("get_scalar_part", &Quaternion::getScalarPart)
        .def("to_normalized", &Quaternion::toNormalized)
        .def("to_conjugate", &Quaternion::toConjugate)
        .def("to_inverse", &Quaternion::toInverse)
        // .def("pow", &Quaternion::pow)
        // .def("exp", &Quaternion::exp)
        // .def("log", &Quaternion::log)
        .def("norm", &Quaternion::norm)
        .def("cross_multiply", &Quaternion::crossMultiply)
        .def("dot_multiply", &Quaternion::dotMultiply)
        .def("rotate_vector", &Quaternion::rotateVector)
        .def("to_vector", &Quaternion::toVector)
        .def("to_string", +[] (const Quaternion& aQuaternion) -> String { return aQuaternion.toString() ; })
        .def("to_string", +[] (const Quaternion& aQuaternion, const Quaternion::Format aFormat) -> String { return aQuaternion.toString(aFormat) ; })
        .def("normalize", +[] (Quaternion& aQuaternion) -> void { aQuaternion.normalize() ; })
        .def("conjugate", +[] (Quaternion& aQuaternion) -> void { aQuaternion.conjugate() ; })
        .def("inverse", +[] (Quaternion& aQuaternion) -> void { aQuaternion.inverse() ; })
        .def("rectify", +[] (Quaternion& aQuaternion) -> void { aQuaternion.rectify() ; })
        .def("angular_difference_with", &Quaternion::angularDifferenceWith)

        .def_static("undefined", &Quaternion::Undefined)
        .def_static("unit", &Quaternion::Unit)
        .def_static("xyzs", &Quaternion::XYZS)
        .def_static("rotation_vector", &Quaternion::RotationVector)
        .def_static("rotation_matrix", &Quaternion::RotationMatrix)
        .def_static("parse", &Quaternion::Parse)

    ;

    enum_<Quaternion::Format>(quaternion, "Format")

        .value("XYZS", Quaternion::Format::XYZS)
        .value("SXYZ", Quaternion::Format::SXYZ)

    ;

    aModule.def("set_quaternion_array", overload_cast<const Array<Quaternion>&>(&set_quaternion_array));

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
