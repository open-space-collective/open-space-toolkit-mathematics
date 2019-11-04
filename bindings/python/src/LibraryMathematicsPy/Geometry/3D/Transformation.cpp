////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Mathematics
/// @file           LibraryMathematicsPy/Geometry/3D/Transformation.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Transformation.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_3D_Transformation ( )
{

    using namespace boost::python ;

    using library::math::obj::Vector3d ;
    using library::math::obj::Matrix4d ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::Transformation ;
    using library::math::geom::d3::trf::rot::RotationMatrix ;

    scope in_Transformation = class_<Transformation>("Transformation", init<const Matrix4d&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &Transformation::isDefined)

        .def("getType", &Transformation::getType)
        .def("getMatrix", &Transformation::getMatrix)
        .def("getInverse", &Transformation::getInverse)
        .def("applyToPoint", + [] (const Transformation& aTransformation, const Point& aPoint) -> Point { return aTransformation.applyTo(aPoint) ; })
        .def("applyToVector", + [] (const Transformation& aTransformation, const Vector3d& aVector) -> Vector3d { return aTransformation.applyTo(aVector) ; })

        .def("Undefined", &Transformation::Undefined).staticmethod("Undefined")
        .def("Identity", &Transformation::Identity).staticmethod("Identity")
        .def("Translation", &Transformation::Translation).staticmethod("Translation")
        // .def("Rotation", &Transformation::Rotation).staticmethod("Rotation")
        // .def("Rotation", +[] (const RotationVector& aRotationVector) -> Transformation { return Transformation::Rotation(aRotationVector) ; } )
        .def("Rotation", +[] (const RotationMatrix& aRotationMatrix) -> Transformation { return Transformation::Rotation(aRotationMatrix) ; } )
        .def("RotationAround", &Transformation::RotationAround).staticmethod("RotationAround")

        .def("StringFromType", &Transformation::StringFromType).staticmethod("StringFromType")
        .def("TypeOfMatrix", &Transformation::TypeOfMatrix).staticmethod("TypeOfMatrix")

    ;

    enum_<Transformation::Type>("Type")

        .value("Undefined", Transformation::Type::Undefined)
        .value("Identity", Transformation::Type::Identity)
        .value("Translation", Transformation::Type::Translation)
        .value("Rotation", Transformation::Type::Rotation)
        .value("Scaling", Transformation::Type::Scaling)
        .value("Reflection", Transformation::Type::Reflection)
        .value("Shear", Transformation::Type::Shear)
        .value("Affine", Transformation::Type::Affine)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
