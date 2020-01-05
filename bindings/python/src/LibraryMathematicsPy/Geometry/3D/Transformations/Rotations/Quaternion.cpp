////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           LibraryMathematicsPy/Geometry/3D/Transformations/Rotations/Quaternion.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <LibraryMathematicsPy/Utilities/IterableConverter.hpp>

#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp>
#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_3D_Transformations_Rotations_Quaternion ( )
{

    using namespace boost::python ;

    using library::core::types::Real ;
    using library::core::types::String ;

    using library::math::obj::Vector3d ;
    using library::math::obj::Vector4d ;
    using library::math::geom::d3::trf::rot::Quaternion ;

    scope in_Quaternion = class_<Quaternion>("Quaternion", init<const Real&, const Real&, const Real&, const Real&, const Quaternion::Format&>())

        .def(init<const Vector4d&, const Quaternion::Format&>())
        .def(init<const Vector3d&, const Real&>())

        .def(self == self)
        .def(self != self)

		.def(self * self)
		.def(self * Vector3d())

		.def(self / self)

        .def(self_ns::str(self_ns::self))

        .def("__repr__", +[] (const Quaternion& aQuaternion) -> std::string { return aQuaternion.toString() ; })

        .def("isDefined", &Quaternion::isDefined)
        .def("isUnitary", &Quaternion::isUnitary)
        .def("isNear", &Quaternion::isNear)

        .def("x", &Quaternion::x)
        .def("y", &Quaternion::y)
        .def("z", &Quaternion::z)
        .def("s", &Quaternion::s)
        .def("getVectorPart", &Quaternion::getVectorPart)
        .def("getScalarPart", &Quaternion::getScalarPart)
        .def("toNormalized", &Quaternion::toNormalized)
        .def("toConjugate", &Quaternion::toConjugate)
        .def("toInverse", &Quaternion::toInverse)
        // .def("pow", &Quaternion::pow)
        // .def("exp", &Quaternion::exp)
        // .def("log", &Quaternion::log)
        .def("norm", &Quaternion::norm)
        .def("crossMultiply", &Quaternion::crossMultiply)
        .def("dotMultiply", &Quaternion::dotMultiply)
        .def("rotateVector", &Quaternion::rotateVector)
        .def("toVector", &Quaternion::toVector)
        .def("toString", +[] (const Quaternion& aQuaternion) -> String { return aQuaternion.toString() ; })
        .def("toString", +[] (const Quaternion& aQuaternion, const Quaternion::Format aFormat) -> String { return aQuaternion.toString(aFormat) ; })
        .def("normalize", +[] (Quaternion& aQuaternion) -> void { aQuaternion.normalize() ; })
        .def("conjugate", +[] (Quaternion& aQuaternion) -> void { aQuaternion.conjugate() ; })
        .def("inverse", +[] (Quaternion& aQuaternion) -> void { aQuaternion.inverse() ; })
        .def("rectify", +[] (Quaternion& aQuaternion) -> void { aQuaternion.rectify() ; })
        .def("angularDifferenceWith", &Quaternion::angularDifferenceWith)

        .def("Undefined", &Quaternion::Undefined).staticmethod("Undefined")
        .def("Unit", &Quaternion::Unit).staticmethod("Unit")
        .def("XYZS", &Quaternion::XYZS).staticmethod("XYZS")
        .def("RotationVector", &Quaternion::RotationVector).staticmethod("RotationVector")
        .def("RotationMatrix", &Quaternion::RotationMatrix).staticmethod("RotationMatrix")
        .def("Parse", &Quaternion::Parse).staticmethod("Parse")

    ;

    enum_<Quaternion::Format>("Format")

        .value("XYZS", Quaternion::Format::XYZS)
        .value("SXYZ", Quaternion::Format::SXYZ)

    ;

    using library::core::ctnr::Array ;

    IterableConverter()

        .from_python<Array<Quaternion>>()
        .to_python<Array<Quaternion>>()

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
