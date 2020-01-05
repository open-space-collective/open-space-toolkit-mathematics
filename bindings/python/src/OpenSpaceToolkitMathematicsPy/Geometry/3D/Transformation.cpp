////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformation.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformation ( )
{

    using namespace boost::python ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::obj::Matrix4d ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::Transformation ;
    using ostk::math::geom::d3::trf::rot::RotationMatrix ;

    scope in_Transformation = class_<Transformation>("Transformation", init<const Matrix4d&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("is_defined", &Transformation::isDefined)

        .def("get_type", &Transformation::getType)
        .def("get_matrix", &Transformation::getMatrix)
        .def("get_inverse", &Transformation::getInverse)
        .def("apply_to_point", + [] (const Transformation& aTransformation, const Point& aPoint) -> Point { return aTransformation.applyTo(aPoint) ; })
        .def("apply_to_vector", + [] (const Transformation& aTransformation, const Vector3d& aVector) -> Vector3d { return aTransformation.applyTo(aVector) ; })

        .def("undefined", &Transformation::Undefined).staticmethod("undefined")
        .def("identity", &Transformation::Identity).staticmethod("identity")
        .def("translation", &Transformation::Translation).staticmethod("translation")
        // .def("rotation", &Transformation::Rotation).staticmethod("rotation")
        // .def("rotation", +[] (const RotationVector& aRotationVector) -> Transformation { return Transformation::Rotation(aRotationVector) ; } )
        .def("rotation", +[] (const RotationMatrix& aRotationMatrix) -> Transformation { return Transformation::Rotation(aRotationMatrix) ; } )
        .def("rotation_around", &Transformation::RotationAround).staticmethod("rotation_around")

        .def("string_from_type", &Transformation::StringFromType).staticmethod("string_from_type")
        .def("type_of_matrix", &Transformation::TypeOfMatrix).staticmethod("type_of_matrix")

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
