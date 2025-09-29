/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>

#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformation/Rotation.cpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformation(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::Transformation;
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix;
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;
    using ostk::mathematics::object::Matrix4d;
    using ostk::mathematics::object::Vector3d;

    class_<Transformation> transformation(
        aModule,
        "Transformation",
        R"doc(
            Represents a 3D geometric transformation.

            A Transformation can represent translation, rotation, scaling, reflection, shear, or general affine transformations.
        )doc"
    );

    // Define constructor
    transformation.def(
        init<const Matrix4d&>(),
        arg("matrix"),
        R"doc(
            Construct a transformation from a 4x4 matrix.

            Args:
                matrix (numpy.ndarray): A 4x4 transformation matrix.
        )doc"
    );

    // Define methods
    transformation.def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Transformation>))
        .def("__repr__", &(shiftToString<Transformation>))

        .def(
            "is_defined",
            &Transformation::isDefined,
            R"doc(
                Check if the transformation is defined.

                Returns:
                    bool: True if the transformation is defined.
            )doc"
        )

        .def(
            "get_type",
            &Transformation::getType,
            R"doc(
                Get the type of the transformation.

                Returns:
                    Transformation.Type: The transformation type.
            )doc"
        )
        .def(
            "get_matrix",
            &Transformation::getMatrix,
            R"doc(
                Get the transformation matrix.

                Returns:
                    numpy.ndarray: The 4x4 transformation matrix.
            )doc"
        )
        .def(
            "get_inverse",
            &Transformation::getInverse,
            R"doc(
                Get the inverse transformation.

                Returns:
                    Transformation: The inverse transformation.
            )doc"
        )
        .def(
            "apply_to",
            overload_cast<const Point&>(&Transformation::applyTo, const_),
            arg("point"),
            R"doc(
                Apply the transformation to a point.

                Args:
                    point (Point): The point to transform.

                Returns:
                    Point: The transformed point.
            )doc"
        )
        .def(
            "apply_to",
            overload_cast<const Vector3d&>(&Transformation::applyTo, const_),
            arg("vector"),
            R"doc(
                Apply the transformation to a vector.

                Args:
                    vector (numpy.ndarray): The vector to transform.

                Returns:
                    numpy.ndarray: The transformed vector.
            )doc"
        )

        .def_static(
            "undefined",
            &Transformation::Undefined,
            R"doc(
                Create an undefined transformation.

                Returns:
                    Transformation: An undefined transformation.
            )doc"
        )
        .def_static(
            "identity",
            &Transformation::Identity,
            R"doc(
                Create an identity transformation.

                Returns:
                    Transformation: An identity transformation.
            )doc"
        )
        .def_static(
            "translation",
            &Transformation::Translation,
            arg("translation_vector"),
            R"doc(
                Create a translation transformation.

                Args:
                    translation_vector (numpy.ndarray): The translation vector.

                Returns:
                    Transformation: A translation transformation.
            )doc"
        )
        .def_static(
            "rotation",
            overload_cast<const RotationVector&>(&Transformation::Rotation),
            arg("rotation_vector"),
            R"doc(
                Create a rotation transformation from a rotation vector.

                Args:
                    rotation_vector (RotationVector): The rotation vector.

                Returns:
                    Transformation: A rotation transformation.
            )doc"
        )
        .def_static(
            "rotation",
            overload_cast<const RotationMatrix&>(&Transformation::Rotation),
            arg("rotation_matrix"),
            R"doc(
                Create a rotation transformation from a rotation matrix.

                Args:
                    rotation_matrix (RotationMatrix): The rotation matrix.

                Returns:
                    Transformation: A rotation transformation.
            )doc"
        )
        .def_static(
            "rotation_around",
            &Transformation::RotationAround,
            arg("point"),
            arg("rotation_vector"),
            R"doc(
                Create a rotation transformation around a point.

                Args:
                    point (Point): The point to rotate around.
                    rotation_vector (RotationVector): The rotation vector.

                Returns:
                    Transformation: A rotation transformation around the point.
            )doc"
        )

        .def_static(
            "string_from_type",
            &Transformation::StringFromType,
            arg("type"),
            R"doc(
                Convert a transformation type to a string.

                Args:
                    type (Transformation.Type): The transformation type.

                Returns:
                    str: The string representation of the type.
            )doc"
        )
        .def_static(
            "type_of_matrix",
            &Transformation::TypeOfMatrix,
            arg("matrix"),
            R"doc(
                Determine the type of a transformation matrix.

                Args:
                    matrix (numpy.ndarray): The 4x4 transformation matrix.

                Returns:
                    Transformation.Type: The type of the transformation.
            )doc"
        )

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
    auto transformation_module = aModule.def_submodule("transformation");

    // Add object to python "transformation" submodules
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformation_Rotation(transformation_module);
}
