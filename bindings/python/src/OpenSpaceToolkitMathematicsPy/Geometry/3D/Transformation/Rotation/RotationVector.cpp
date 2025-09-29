/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationMatrix.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformation_Rotation_RotationVector(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Integer;
    using ostk::core::type::Real;
    using ostk::core::type::String;

    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;
    using ostk::mathematics::object::Vector3d;

    class_<RotationVector>(aModule, "RotationVector")

        // Define constructor
        .def(
            init<const Vector3d&, const Angle&>(),
            R"doc(
                Create a rotation vector from axis and angle.

                Args:
                    axis (np.array): The rotation axis (will be normalized).
                    angle (Angle): The rotation angle around the axis.

                Example:
                    >>> axis = np.array([0.0, 0.0, 1.0])
                    >>> angle = Angle.degrees(90.0)
                    >>> rot_vector = RotationVector(axis, angle)
            )doc",
            arg("axis"),
            arg("angle")
        )
        .def(
            init<const Vector3d&, const Angle::Unit&>(),
            R"doc(
                Create a rotation vector from a vector representation.

                Args:
                    vector (np.array): The rotation vector (magnitude represents angle).
                    angle_unit (Angle.Unit): The unit of the angle in the vector magnitude.

                Example:
                    >>> vector = np.array([0.0, 0.0, 1.5708])  # π/2 in z-axis
                    >>> rot_vector = RotationVector(vector, Angle.Unit.Radian)
            )doc",
            arg("vector"),
            arg("angle_unit")
        )

        // Define methods
        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<RotationVector>))
        .def("__repr__", &(shiftToString<RotationVector>))

        .def(
            "is_defined",
            &RotationVector::isDefined,
            R"doc(
                Check if the rotation vector is defined.

                Returns:
                    bool: True if the rotation vector is defined, False otherwise.

                Example:
                    >>> rot_vector = RotationVector(axis, angle)
                    >>> rot_vector.is_defined()  # True
            )doc"
        )

        .def(
            "get_axis",
            &RotationVector::getAxis,
            R"doc(
                Get the rotation axis vector.

                Returns:
                    Vector3d: The normalized rotation axis.

                Example:
                    >>> rot_vector = RotationVector(np.array([1.0, 0.0, 0.0]), angle)
                    >>> axis = rot_vector.get_axis()  # [1.0, 0.0, 0.0]
            )doc"
        )
        .def(
            "get_angle",
            &RotationVector::getAngle,
            R"doc(
                Get the rotation angle.

                Returns:
                    Angle: The rotation angle around the axis.

                Example:
                    >>> rot_vector = RotationVector(axis, Angle.degrees(90.0))
                    >>> angle = rot_vector.get_angle()  # 90 degrees
            )doc"
        )
        .def(
            "to_string",
            +[](const RotationVector& aRotationVector) -> String
            {
                return aRotationVector.toString();
            },
            R"doc(
                Convert the rotation vector to string representation.

                Returns:
                    str: String representation of the rotation vector.

                Example:
                    >>> rot_vector = RotationVector.unit()
                    >>> rot_vector.to_string()
            )doc"
        )
        .def(
            "to_string",
            +[](const RotationVector& aRotationVector, const Integer& aPrecision) -> String
            {
                return aRotationVector.toString(aPrecision);
            },
            R"doc(
                Convert the rotation vector to string representation with specified precision.

                Args:
                    precision (int): The precision for floating point numbers.

                Returns:
                    str: String representation of the rotation vector.

                Example:
                    >>> rot_vector = RotationVector.unit()
                    >>> rot_vector.to_string(3)
            )doc",
            arg("precision")
        )

        .def(
            "rectify",
            +[](RotationVector& aRotationVector) -> void
            {
                aRotationVector.rectify();
            },
            R"doc(
                Rectify the rotation vector in-place (ensure angle is in [0, π]).

                Example:
                    >>> rot_vector = RotationVector(axis, Angle.degrees(270.0))
                    >>> rot_vector.rectify()  # Converts to equivalent rotation with angle ≤ π
            )doc"
        )

        // Define static methods
        .def_static(
            "undefined",
            &RotationVector::Undefined,
            R"doc(
                Create an undefined rotation vector.

                Returns:
                    RotationVector: An undefined rotation vector.

                Example:
                    >>> undefined_vector = RotationVector.undefined()
                    >>> undefined_vector.is_defined()  # False
            )doc"
        )
        .def_static(
            "unit",
            &RotationVector::Unit,
            R"doc(
                Create a unit rotation vector (no rotation).

                Returns:
                    RotationVector: A rotation vector representing no rotation.

                Example:
                    >>> unit_vector = RotationVector.unit()
                    >>> angle = unit_vector.get_angle()  # 0 degrees
            )doc"
        )
        .def_static(
            "x",
            &RotationVector::X,
            R"doc(
                Create a rotation vector around the x-axis.

                Args:
                    angle (Angle): The rotation angle around the x-axis.

                Returns:
                    RotationVector: A rotation vector around the x-axis.

                Example:
                    >>> rot_vector = RotationVector.x(Angle.degrees(90.0))
            )doc",
            arg("angle")
        )
        .def_static(
            "y",
            &RotationVector::Y,
            R"doc(
                Create a rotation vector around the y-axis.

                Args:
                    angle (Angle): The rotation angle around the y-axis.

                Returns:
                    RotationVector: A rotation vector around the y-axis.

                Example:
                    >>> rot_vector = RotationVector.y(Angle.degrees(90.0))
            )doc",
            arg("angle")
        )
        .def_static(
            "z",
            &RotationVector::Z,
            R"doc(
                Create a rotation vector around the z-axis.

                Args:
                    angle (Angle): The rotation angle around the z-axis.

                Returns:
                    RotationVector: A rotation vector around the z-axis.

                Example:
                    >>> rot_vector = RotationVector.z(Angle.degrees(90.0))
            )doc",
            arg("angle")
        )
        .def_static(
            "quaternion",
            &RotationVector::Quaternion,
            R"doc(
                Create a rotation vector from a quaternion.

                Args:
                    quaternion (Quaternion): The quaternion to convert.

                Returns:
                    RotationVector: The equivalent rotation vector.

                Example:
                    >>> q = Quaternion.unit()
                    >>> rot_vector = RotationVector.quaternion(q)
            )doc",
            arg("quaternion")
        )
        .def_static(
            "rotation_matrix",
            &RotationVector::RotationMatrix,
            R"doc(
                Create a rotation vector from a rotation matrix.

                Args:
                    rotation_matrix (RotationMatrix): The rotation matrix to convert.

                Returns:
                    RotationVector: The equivalent rotation vector.

                Example:
                    >>> rm = RotationMatrix.identity()
                    >>> rot_vector = RotationVector.rotation_matrix(rm)
            )doc",
            arg("rotation_matrix")
        )
        .def_static(
            "euler_angle",
            &RotationVector::EulerAngle,
            R"doc(
                Create a rotation vector from Euler angles.

                Args:
                    euler_angle (EulerAngle): The Euler angles to convert.

                Returns:
                    RotationVector: The equivalent rotation vector.

                Example:
                    >>> ea = EulerAngle(Angle.degrees(30), Angle.degrees(45), Angle.degrees(60))
                    >>> rot_vector = RotationVector.euler_angle(ea)
            )doc",
            arg("euler_angle")
        )

        ;
}
