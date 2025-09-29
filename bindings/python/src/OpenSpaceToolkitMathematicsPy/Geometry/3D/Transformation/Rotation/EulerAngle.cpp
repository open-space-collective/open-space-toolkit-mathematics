/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/EulerAngle.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationMatrix.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/Angle.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformation_Rotation_EulerAngle(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;
    using ostk::core::type::String;

    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::transformation::rotation::EulerAngle;
    using ostk::mathematics::object::Vector3d;

    class_<EulerAngle> eulerAngle(aModule, "EulerAngle");

    eulerAngle
        // Define constructor
        .def(
            init<const Angle&, const Angle&, const Angle&, const EulerAngle::AxisSequence&>(),
            R"doc(
                Create Euler angles from three angle components and axis sequence.

                Args:
                    phi (Angle): The first rotation angle.
                    theta (Angle): The second rotation angle.
                    psi (Angle): The third rotation angle.
                    axis_sequence (EulerAngle.AxisSequence): The axis sequence (XYZ, ZXY, ZYX).

                Example:
                    >>> phi = Angle.degrees(30.0)
                    >>> theta = Angle.degrees(45.0)
                    >>> psi = Angle.degrees(60.0)
                    >>> euler = EulerAngle(phi, theta, psi, EulerAngle.AxisSequence.XYZ)
            )doc",
            arg("phi"),
            arg("theta"),
            arg("psi"),
            arg("axis_sequence")
        )
        .def(
            init<const Vector3d&, const Angle::Unit&, const EulerAngle::AxisSequence&>(),
            R"doc(
                Create Euler angles from a 3D vector with specified angle unit and axis sequence.

                Args:
                    vector (np.array): Vector containing the three angle values.
                    angle_unit (Angle.Unit): The unit of the angles in the vector.
                    axis_sequence (EulerAngle.AxisSequence): The axis sequence.

                Example:
                    >>> vector = np.array([30.0, 45.0, 60.0])
                    >>> euler = EulerAngle(vector, Angle.Unit.Degree, EulerAngle.AxisSequence.XYZ)
            )doc",
            arg("vector"),
            arg("angle_unit"),
            arg("axis_sequence")
        )

        // Define methods
        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<EulerAngle>))
        .def("__repr__", &(shiftToString<EulerAngle>))

        .def(
            "is_defined",
            &EulerAngle::isDefined,
            R"doc(
                Check if the Euler angle is defined.

                Returns:
                    bool: True if the Euler angle is defined, False otherwise.

                Example:
                    >>> euler = EulerAngle(phi, theta, psi, EulerAngle.AxisSequence.XYZ)
                    >>> euler.is_defined()  # True
            )doc"
        )
        .def(
            "is_unitary",
            &EulerAngle::isUnitary,
            R"doc(
                Check if the Euler angle represents a unit rotation.

                Returns:
                    bool: True if the Euler angle is unitary, False otherwise.

                Example:
                    >>> euler = EulerAngle.unit()
                    >>> euler.is_unitary()  # True
            )doc"
        )
        .def(
            "is_near",
            &EulerAngle::isNear,
            R"doc(
                Check if this Euler angle is near another Euler angle within tolerance.

                Args:
                    euler_angle (EulerAngle): The Euler angle to compare with.
                    angular_tolerance (Angle): The angular tolerance for comparison.

                Returns:
                    bool: True if angles are within tolerance, False otherwise.

                Example:
                    >>> euler1 = EulerAngle(phi1, theta1, psi1, sequence)
                    >>> euler2 = EulerAngle(phi2, theta2, psi2, sequence)
                    >>> euler1.is_near(euler2, Angle.degrees(1.0))
            )doc",
            arg("euler_angle"),
            arg("angular_tolerance")
        )

        .def_property_readonly("phi", &EulerAngle::getPhi)
        .def_property_readonly("theta", &EulerAngle::getTheta)
        .def_property_readonly("psi", &EulerAngle::getPsi)
        .def_property_readonly("axis_sequence", &EulerAngle::getAxisSequence)

        .def(
            "to_vector",
            &EulerAngle::toVector,
            R"doc(
                Convert the Euler angle to a 3D vector with specified unit.

                Args:
                    angle_unit (Angle.Unit): The unit for the output vector angles.

                Returns:
                    Vector3d: A vector containing [phi, theta, psi] in the specified unit.

                Example:
                    >>> euler = EulerAngle(phi, theta, psi, EulerAngle.AxisSequence.XYZ)
                    >>> vector = euler.to_vector(Angle.Unit.Degree)
            )doc",
            arg("angle_unit")
        )
        .def(
            "to_string",
            +[](const EulerAngle& aEulerAngle) -> String
            {
                return aEulerAngle.toString();
            }
        )
        .def(
            "to_string",
            +[](const EulerAngle& aEulerAngle, const Angle::Unit& anAngleUnit) -> String
            {
                return aEulerAngle.toString(anAngleUnit);
            },
            arg("angle_unit")
        )

        // Define static methods
        .def_static(
            "undefined",
            &EulerAngle::Undefined,
            R"doc(
                Create an undefined Euler angle.

                Returns:
                    EulerAngle: An undefined Euler angle object.

                Example:
                    >>> undefined_euler = EulerAngle.undefined()
                    >>> undefined_euler.is_defined()  # False
            )doc"
        )
        .def_static(
            "unit",
            &EulerAngle::Unit,
            R"doc(
                Create a unit Euler angle (no rotation).

                Returns:
                    EulerAngle: A unit Euler angle representing no rotation.

                Example:
                    >>> unit_euler = EulerAngle.unit()
                    >>> unit_euler.is_unitary()  # True
            )doc"
        )
        .def_static(
            "xyz",
            &EulerAngle::XYZ,
            R"doc(
                Create Euler angles with XYZ axis sequence.

                Args:
                    phi (Angle): The first rotation angle around X-axis.
                    theta (Angle): The second rotation angle around Y-axis.
                    psi (Angle): The third rotation angle around Z-axis.

                Returns:
                    EulerAngle: An Euler angle with XYZ sequence.

                Example:
                    >>> euler = EulerAngle.xyz(Angle.degrees(30.0), Angle.degrees(45.0), Angle.degrees(60.0))
            )doc",
            arg("phi"),
            arg("theta"),
            arg("psi")
        )
        .def_static(
            "zxy",
            &EulerAngle::ZXY,
            R"doc(
                Create Euler angles with ZXY axis sequence.

                Args:
                    phi (Angle): The first rotation angle around Z-axis.
                    theta (Angle): The second rotation angle around X-axis.
                    psi (Angle): The third rotation angle around Y-axis.

                Returns:
                    EulerAngle: An Euler angle with ZXY sequence.

                Example:
                    >>> euler = EulerAngle.zxy(Angle.degrees(30.0), Angle.degrees(45.0), Angle.degrees(60.0))
            )doc",
            arg("phi"),
            arg("theta"),
            arg("psi")
        )
        .def_static(
            "zyx",
            &EulerAngle::ZYX,
            R"doc(
                Create Euler angles with ZYX axis sequence.

                Args:
                    phi (Angle): The first rotation angle around Z-axis.
                    theta (Angle): The second rotation angle around Y-axis.
                    psi (Angle): The third rotation angle around X-axis.

                Returns:
                    EulerAngle: An Euler angle with ZYX sequence.

                Example:
                    >>> euler = EulerAngle.zyx(Angle.degrees(30.0), Angle.degrees(45.0), Angle.degrees(60.0))
            )doc",
            arg("phi"),
            arg("theta"),
            arg("psi")
        )
        .def_static(
            "quaternion",
            &EulerAngle::Quaternion,
            R"doc(
                Create Euler angles from a quaternion with specified axis sequence.

                Args:
                    quaternion (Quaternion): The quaternion to convert.
                    axis_sequence (EulerAngle.AxisSequence): The desired axis sequence.

                Returns:
                    EulerAngle: The equivalent Euler angles.

                Example:
                    >>> quat = Quaternion.unit()
                    >>> euler = EulerAngle.quaternion(quat, EulerAngle.AxisSequence.XYZ)
            )doc",
            arg("quaternion"),
            arg("axis_sequence")
        )
        .def_static("rotation_vector", &EulerAngle::RotationVector, arg("rotation_vector"), arg("axis_sequence"))
        .def_static("rotation_matrix", &EulerAngle::RotationMatrix, arg("rotation_matrix"), arg("axis_sequence"))

        ;

    enum_<EulerAngle::AxisSequence>(eulerAngle, "AxisSequence")

        .value("Undefined", EulerAngle::AxisSequence::Undefined)
        .value("XYZ", EulerAngle::AxisSequence::XYZ)
        .value("ZXY", EulerAngle::AxisSequence::ZXY)
        .value("ZYX", EulerAngle::AxisSequence::ZYX)

        ;
}
