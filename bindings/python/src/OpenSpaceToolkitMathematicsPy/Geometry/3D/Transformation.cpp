/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>

#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformations/Rotations.cpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformation(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::object::Matrix4d;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::Transformation;
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix;

    class_<Transformation> transformation(aModule, "Transformation");

    // Define constructor
    transformation.def(init<const Matrix4d&>(), arg("matrix"));

    // Define methods
    transformation.def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Transformation>))
        .def("__repr__", &(shiftToString<Transformation>))

        .def("is_defined", &Transformation::isDefined)

        .def("get_type", &Transformation::getType)
        .def("get_matrix", &Transformation::getMatrix)
        .def("get_inverse", &Transformation::getInverse)
        .def("apply_to", overload_cast<const Point&>(&Transformation::applyTo, const_), arg("point"))
        .def("apply_to", overload_cast<const Vector3d&>(&Transformation::applyTo, const_), arg("vector"))

        .def_static("undefined", &Transformation::Undefined)
        .def_static("identity", &Transformation::Identity)
        .def_static("translation", &Transformation::Translation, arg("translation_vector"))
        .def_static("rotation", overload_cast<const RotationVector&>(&Transformation::Rotation), arg("rotation_vector"))
        .def_static("rotation", overload_cast<const RotationMatrix&>(&Transformation::Rotation), arg("rotation_matrix"))
        .def_static("rotation_around", &Transformation::RotationAround, arg("point"), arg("rotation_vector"))

        .def_static("string_from_type", &Transformation::StringFromType, arg("type"))
        .def_static("type_of_matrix", &Transformation::TypeOfMatrix, arg("matrix"))

        ;

    // Define enumeration type for a transformation
    enum_<Transformation::Type>(transformation, "Type")

        .value("Undefined", Transformation::Type::Undefined)
        .value("Identity", Transformation::Type::Identity)
        .value("Translation", Transformation::Type::Translation)
        .value("Rotation", Transformation::Type::Rotation)
        .value("Scaling", Transformation::Type::Scaling)
        .value("Reflection", Transformation::Type::Reflection)
        .value("Shear", Transformation::Type::Shear)
        .value("Affine", Transformation::Type::Affine)

        ;

    // Create "transformation" python submodule
    auto transformation = aModule.def_submodule("transformation");

    // Add __path__ attribute for "transformation" submodule
    transformation.attr("__path__") = "ostk.mathematics.geometry.d3.transformation";

    // Add object to python "transformation" submodules
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformations_Rotations(transformation);
}
