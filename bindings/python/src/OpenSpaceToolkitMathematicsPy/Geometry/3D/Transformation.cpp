////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformation.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformation             (    pybind11::module&                     aModule        )
{

    using namespace pybind11 ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::obj::Matrix4d ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::Transformation ;
    using ostk::math::geom::d3::trf::rot::RotationMatrix ;

    class_<Transformation> transformation(aModule, "Transformation") ;

    // Define constructor
    transformation.def(init<const Matrix4d&>()) ;

        // Define methods
    transformation.def(self == self)
        .def(self != self)

        .def("__str__", &(shift_to_string<Transformation>))
        .def("__repr__", &(shift_to_string<Transformation>))

        .def("is_defined", &Transformation::isDefined)

        .def("get_type", &Transformation::getType)
        .def("get_matrix", &Transformation::getMatrix)
        .def("get_inverse", &Transformation::getInverse)
        .def("apply_to_point", + [] (const Transformation& aTransformation, const Point& aPoint) -> Point { return aTransformation.applyTo(aPoint) ; })
        .def("apply_to_vector", + [] (const Transformation& aTransformation, const Vector3d& aVector) -> Vector3d { return aTransformation.applyTo(aVector) ; })

        .def_static("undefined", &Transformation::Undefined)
        .def_static("identity", &Transformation::Identity)
        .def_static("translation", &Transformation::Translation)
        // .def_static("rotation", &Transformation::Rotation)
        // .def("rotation", +[] (const RotationVector& aRotationVector) -> Transformation { return Transformation::Rotation(aRotationVector) ; } )
        .def("rotation", +[] (const RotationMatrix& aRotationMatrix) -> Transformation { return Transformation::Rotation(aRotationMatrix) ; } )
        .def_static("rotation_around", &Transformation::RotationAround)

        .def_static("string_from_type", &Transformation::StringFromType)
        .def_static("type_of_matrix", &Transformation::TypeOfMatrix)

    ;

    // Define enumeration type for a transformation
    enum_<Transformation::Type> (transformation, "Type")

        .value("Undefined", Transformation::Type::Undefined)
        .value("Identity", Transformation::Type::Identity)
        .value("Translation", Transformation::Type::Translation)
        .value("Rotation", Transformation::Type::Rotation)
        .value("Scaling", Transformation::Type::Scaling)
        .value("Reflection", Transformation::Type::Reflection)
        .value("Shear", Transformation::Type::Shear)
        .value("Affine", Transformation::Type::Affine)
        .export_values()

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
