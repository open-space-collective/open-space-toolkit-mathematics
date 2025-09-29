/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Transformation.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_2D_Transformation(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::Transformation;
    using ostk::mathematics::object::Matrix3d;
    using ostk::mathematics::object::Vector2d;

    class_<Transformation> transf(aModule, "Transformation");

    transf
        .def(
            init<const Matrix3d&>(),
            R"doc(
                Create a 2D transformation from a 3x3 transformation matrix.

                Args:
                    matrix (Matrix3d): The 3x3 transformation matrix in homogeneous coordinates.

                Example:
                    >>> import numpy as np
                    >>> matrix = np.eye(3)  # Identity matrix
                    >>> transformation = Transformation(matrix)
            )doc",
            arg("matrix")
        )

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Transformation>))
        .def("__repr__", &(shiftToString<Transformation>))

        .def(
            "is_defined",
            &Transformation::isDefined,
            R"doc(
                Check if the transformation is defined.

                Returns:
                    bool: True if the transformation is defined, False otherwise.

                Example:
                    >>> transformation = Transformation.identity()
                    >>> transformation.is_defined()  # True
            )doc"
        )

        .def(
            "get_type",
            &Transformation::getType,
            R"doc(
                Get the type of the transformation.

                Returns:
                    Transformation.Type: The transformation type (Identity, Translation, Rotation, etc.).

                Example:
                    >>> transformation = Transformation.identity()
                    >>> transformation.get_type()  # Transformation.Type.Identity
            )doc"
        )
        .def(
            "get_matrix",
            &Transformation::getMatrix,
            R"doc(
                Get the transformation matrix.

                Returns:
                    Matrix3d: The 3x3 transformation matrix in homogeneous coordinates.

                Example:
                    >>> transformation = Transformation.identity()
                    >>> matrix = transformation.get_matrix()  # 3x3 identity matrix
            )doc"
        )
        .def(
            "get_inverse",
            &Transformation::getInverse,
            R"doc(
                Get the inverse transformation.

                Returns:
                    Transformation: The inverse transformation.

                Example:
                    >>> translation = Transformation.translation([1.0, 2.0])
                    >>> inverse = translation.get_inverse()  # Translation by [-1.0, -2.0]
            )doc"
        )

        .def(
            "apply_to",
            overload_cast<const Point&>(&Transformation::applyTo, const_),
            R"doc(
                Apply the transformation to a point.

                Args:
                    point (Point): The point to transform.

                Returns:
                    Point: The transformed point.

                Example:
                    >>> point = Point(1.0, 2.0)
                    >>> translation = Transformation.translation([1.0, 1.0])
                    >>> transformed = translation.apply_to(point)  # Point(2.0, 3.0)
            )doc",
            arg("point")
        )
        .def(
            "apply_to",
            overload_cast<const Vector2d&>(&Transformation::applyTo, const_),
            R"doc(
                Apply the transformation to a vector.

                Args:
                    vector (Vector2d): The vector to transform.

                Returns:
                    Vector2d: The transformed vector.

                Example:
                    >>> vector = np.array([1.0, 0.0])
                    >>> rotation = Transformation.rotation(Angle.degrees(90.0))
                    >>> transformed = rotation.apply_to(vector)  # [0.0, 1.0]
            )doc",
            arg("vector")
        )
        // .def("apply_to", overload_cast<const Unique<Object>&>(&Transformation::applyTo, const_), arg("object"))

        .def_static(
            "undefined",
            &Transformation::Undefined,
            R"doc(
                Create an undefined transformation.

                Returns:
                    Transformation: An undefined transformation.

                Example:
                    >>> undefined_transform = Transformation.undefined()
                    >>> undefined_transform.is_defined()  # False
            )doc"
        )
        .def_static(
            "identity",
            &Transformation::Identity,
            R"doc(
                Create an identity transformation (no change).

                Returns:
                    Transformation: The identity transformation.

                Example:
                    >>> identity = Transformation.identity()
                    >>> point = Point(1.0, 2.0)
                    >>> identity.apply_to(point)  # Point(1.0, 2.0) - unchanged
            )doc"
        )
        .def_static(
            "translation",
            &Transformation::Translation,
            R"doc(
                Create a translation transformation.

                Args:
                    translation_vector (Vector2d): The translation vector.

                Returns:
                    Transformation: The translation transformation.

                Example:
                    >>> translation = Transformation.translation([1.0, 2.0])
                    >>> point = Point(0.0, 0.0)
                    >>> translation.apply_to(point)  # Point(1.0, 2.0)
            )doc",
            arg("translation_vector")
        )
        .def_static(
            "rotation",
            &Transformation::Rotation,
            R"doc(
                Create a rotation transformation around the origin.

                Args:
                    rotation_angle (Angle): The rotation angle.

                Returns:
                    Transformation: The rotation transformation.

                Example:
                    >>> rotation = Transformation.rotation(Angle.degrees(90.0))
                    >>> point = Point(1.0, 0.0)
                    >>> rotation.apply_to(point)  # Point(0.0, 1.0)
            )doc",
            arg("rotation_angle")
        )
        .def_static(
            "rotation_around",
            &Transformation::RotationAround,
            R"doc(
                Create a rotation transformation around a specific point.

                Args:
                    point (Point): The center point of rotation.
                    rotation_angle (Angle): The rotation angle.

                Returns:
                    Transformation: The rotation transformation around the specified point.

                Example:
                    >>> center = Point(1.0, 1.0)
                    >>> rotation = Transformation.rotation_around(center, Angle.degrees(90.0))
                    >>> point = Point(2.0, 1.0)
                    >>> rotation.apply_to(point)  # Point(1.0, 2.0)
            )doc",
            arg("point"),
            arg("rotation_angle")
        )

        .def_static(
            "string_from_type",
            &Transformation::StringFromType,
            R"doc(
                Get the string representation of a transformation type.

                Args:
                    type (Transformation.Type): The transformation type.

                Returns:
                    str: String representation of the type.

                Example:
                    >>> Transformation.string_from_type(Transformation.Type.Translation)  # "Translation"
            )doc",
            arg("type")
        )
        .def_static(
            "type_of_matrix",
            &Transformation::TypeOfMatrix,
            R"doc(
                Determine the transformation type from a matrix.

                Args:
                    matrix (Matrix3d): The transformation matrix to analyze.

                Returns:
                    Transformation.Type: The detected transformation type.

                Example:
                    >>> import numpy as np
                    >>> matrix = np.eye(3)
                    >>> Transformation.type_of_matrix(matrix)  # Transformation.Type.Identity
            )doc",
            arg("matrix")
        )

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
