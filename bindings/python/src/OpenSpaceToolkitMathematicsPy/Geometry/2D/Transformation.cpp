////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/2D/Transformation.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Transformation.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_2D_Transformation   (     pybind11::module&  aModule                                     )
{

    using namespace pybind11 ;

    using ostk::math::obj::Vector2d ;
    using ostk::math::obj::Matrix3d ;
    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::Transformation ;

    class_<Transformation> transf(aModule, "Transformation") ;

    transf.def(init<const Matrix3d&>())

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Transformation>))
        .def("__repr__", &(shiftToString<Transformation>))

        .def("is_defined", &Transformation::isDefined)

        .def("get_type", &Transformation::getType)
        .def("get_matrix", &Transformation::getMatrix)
        .def("get_inverse", &Transformation::getInverse)
        .def("apply_to_point", + [] (const Transformation& aTransformation, const Point& aPoint) -> Point { return aTransformation.applyTo(aPoint) ; })
        .def("apply_to_vector", + [] (const Transformation& aTransformation, const Vector2d& aVector) -> Vector2d { return aTransformation.applyTo(aVector) ; })

        .def_static("undefined", &Transformation::Undefined)
        .def_static("identity", &Transformation::Identity)
        .def_static("translation", &Transformation::Translation)
        .def_static("rotation", &Transformation::Rotation)
        .def_static("rotation_around", &Transformation::RotationAround)

        .def_static("string_from_type", &Transformation::StringFromType)
        .def_static("type_of_matrix", &Transformation::TypeOfMatrix)

    ;

    enum_<Transformation::Type>(transf, "Type")

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
