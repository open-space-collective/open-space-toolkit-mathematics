// Copyright © Loft Orbital Solutions Inc.

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Transformation.hpp>


inline void                     OpenSpaceToolkitMathematicsPy_Geometry_2D_Transformation ( pybind11::module&        aModule                                     )
{

    using namespace pybind11 ;

    using ostk::math::obj::Vector2d ;
    using ostk::math::obj::Matrix3d ;
    using ostk::math::geom::d2::Transformation ;
    using ostk::math::geom::d2::objects::Point ;

    class_<Transformation> transf(aModule, "Transformation") ;

    transf.def(init<const Matrix3d&>(), arg("matrix"))

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Transformation>))
        .def("__repr__", &(shiftToString<Transformation>))

        .def("is_defined", &Transformation::isDefined)

        .def("get_type", &Transformation::getType)
        .def("get_matrix", &Transformation::getMatrix)
        .def("get_inverse", &Transformation::getInverse)

        .def("apply_to", overload_cast<const Point&>(&Transformation::applyTo, const_), arg("point"))
        .def("apply_to", overload_cast<const Vector2d&>(&Transformation::applyTo, const_), arg("vector"))
        // .def("apply_to", overload_cast<const Unique<Object>&>(&Transformation::applyTo, const_), arg("object"))

        .def_static("undefined", &Transformation::Undefined)
        .def_static("identity", &Transformation::Identity)
        .def_static("translation", &Transformation::Translation, arg("transaction_vector"))
        .def_static("rotation", &Transformation::Rotation, arg("rotation_angle"))
        .def_static("rotation_around", &Transformation::RotationAround, arg("point"), arg("rotation_angle"))

        .def_static("string_from_type", &Transformation::StringFromType, arg("type"))
        .def_static("type_of_matrix", &Transformation::TypeOfMatrix, arg("matrix"))

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

