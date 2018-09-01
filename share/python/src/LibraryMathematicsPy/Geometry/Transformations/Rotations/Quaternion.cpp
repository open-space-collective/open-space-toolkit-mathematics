////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           LibraryMathematicsPy/Geometry/Transformations/Rotations/Quaternion.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/Transformations/Rotations/Quaternion.hpp>
#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationMatrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (LibraryMathematicsPy_Geometry_Transformations_Rotations_Quaternion_toString_overloads, library::math::geom::trf::rot::Quaternion::toString, 0, 2)

inline void                     LibraryMathematicsPy_Geometry_Transformations_Rotations_Quaternion ( )
{

    using namespace boost::python ;

    using library::core::types::Real ;
    using library::core::types::String ;
    
    using library::math::obj::Vector3d ;
    using library::math::obj::Vector4d ;
    using library::math::geom::trf::rot::Quaternion ;

    scope in_Quaternion = class_<Quaternion>("Quaternion", init<Real, Real, Real, Real, Quaternion::Format>())

        .def(init<Vector4d, Quaternion::Format>())
        .def(init<Vector3d, Real>())

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
        .def("toString", +[] (const Quaternion& aQuaternion, const Quaternion::Format aFormat) -> String { return aQuaternion.toString(aFormat) ; })
        // .def("toString", &Quaternion::toString(), LibraryMathematicsPy_Geometry_Transformations_Rotations_Quaternion_toString_overloads())
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

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////