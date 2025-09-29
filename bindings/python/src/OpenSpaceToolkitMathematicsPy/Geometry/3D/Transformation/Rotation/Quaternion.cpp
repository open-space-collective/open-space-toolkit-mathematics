/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationMatrix.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>

using ostk::core::container::Array;
using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;

void set_quaternion_array(const Array<Quaternion>& anArray)
{
    (void)anArray;
}

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformation_Rotation_Quaternion(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;
    using ostk::core::type::String;

    using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;
    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::object::Vector4d;

    class_<Quaternion> quaternion(aModule, "Quaternion");

    quaternion
        .def(
            init<const Real&, const Real&, const Real&, const Real&, const Quaternion::Format&>(),
            R"doc(
                Create a quaternion from four components and format.

                Args:
                    first_component (float): First component (x or w depending on format).
                    second_component (float): Second component (y or x depending on format).
                    third_component (float): Third component (z or y depending on format).
                    fourth_component (float): Fourth component (w or z depending on format).
                    format (Quaternion.Format): The quaternion format (XYZS or SXYZ).

                Example:
                    >>> q = Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion.Format.XYZS)
                    >>> q = Quaternion(1.0, 0.0, 0.0, 0.0, Quaternion.Format.SXYZ)
            )doc",
            arg("first_component"),
            arg("second_component"),
            arg("third_component"),
            arg("fourth_component"),
            arg("format")
        )

        .def(
            init<const Vector4d&, const Quaternion::Format&>(),
            R"doc(
                Create a quaternion from a 4D vector and format.

                Args:
                    vector (np.array): The 4D vector containing quaternion components.
                    format (Quaternion.Format): The quaternion format.

                Example:
                    >>> vector = np.array([0.0, 0.0, 0.0, 1.0])
                    >>> q = Quaternion(vector, Quaternion.Format.XYZS)
            )doc",
            arg("vector"),
            arg("format")
        )
        .def(
            init<const Vector3d&, const Real&>(),
            R"doc(
                Create a quaternion from vector and scalar parts.

                Args:
                    vector_part (np.array): The vector part (x, y, z components).
                    scalar_part (float): The scalar part (s component).

                Example:
                    >>> vector_part = np.array([0.0, 0.0, 0.0])
                    >>> scalar_part = 1.0
                    >>> q = Quaternion(vector_part, scalar_part)
            )doc",
            arg("vector_part"),
            arg("scalar_part")
        )
        .def(
            init<const Quaternion&>(),
            R"doc(
                Create a quaternion by copying another quaternion.

                Args:
                    quaternion (Quaternion): The quaternion to copy.

                Example:
                    >>> original = Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion.Format.XYZS)
                    >>> copy = Quaternion(original)
            )doc",
            arg("quaternion")
        )

        .def(self == self)
        .def(self != self)

        .def(self + self)
        .def(self += self)
        .def(self * self)
        .def(self * Vector3d())
        .def(self * double())
        .def(double() * self)

        .def(self / self)

        .def(
            "__pow__",
            +[](const Quaternion& aQuaternion, double aScalar) -> Quaternion
            {
                return aQuaternion ^ aScalar;
            },
            is_operator()
        )

        .def("__str__", &(shiftToString<Quaternion>))
        .def(
            "__repr__",
            +[](const Quaternion& aQuaternion) -> std::string
            {
                return aQuaternion.toString();
            }
        )

        .def(
            "is_defined",
            &Quaternion::isDefined,
            R"doc(
                Check if the quaternion is defined.

                Returns:
                    bool: True if the quaternion is defined, False otherwise.
            )doc"
        )
        .def(
            "is_unitary",
            &Quaternion::isUnitary,
            arg_v("norm_tolerance", Real::Epsilon(), "Real.epsilon()"),
            R"doc(
                Check if the quaternion is unitary.

                Returns:
                    bool: True if the quaternion is unitary, False otherwise.
            )doc"
        )
        .def(
            "is_near",
            &Quaternion::isNear,
            arg("quaternion"),
            arg("angular_tolerance"),
            R"doc(
                Check if the quaternion is near another quaternion.

                Returns:
                    bool: True if the quaternion is near another quaternion, False otherwise.
            )doc"
        )

        .def(
            "x",
            &Quaternion::x,
            R"doc(
                Get the x-coordinate of the quaternion.

                Returns:
                    float: The x-coordinate.
            )doc"
        )
        .def(
            "y",
            &Quaternion::y,
            R"doc(
                Get the y-coordinate of the quaternion.

                Returns:
                    float: The y-coordinate.
            )doc"
        )
        .def(
            "z",
            &Quaternion::z,
            R"doc(
                Get the z-coordinate of the quaternion.

                Returns:
                    float: The z-coordinate.
            )doc"
        )
        .def(
            "s",
            &Quaternion::s,
            R"doc(
                Get the s-coordinate of the quaternion.

                Returns:
                    float: The s-coordinate.
            )doc"
        )
        .def(
            "get_vector_part",
            &Quaternion::getVectorPart,
            R"doc(
                Get the vector part of the quaternion.

                Returns:
                    Vector3d: The vector part.
            )doc"
        )
        .def(
            "get_scalar_part",
            &Quaternion::getScalarPart,
            R"doc(
                Get the scalar part of the quaternion.

                Returns:
                    float: The scalar part.

                Example:
                    >>> q = Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion.Format.XYZS)
                    >>> q.get_scalar_part()  # 1.0
            )doc"
        )
        .def(
            "to_normalized",
            &Quaternion::toNormalized,
            R"doc(
                Get a normalized copy of the quaternion.

                Returns:
                    Quaternion: The normalized quaternion.

                Example:
                    >>> q = Quaternion(1.0, 1.0, 1.0, 1.0, Quaternion.Format.XYZS)
                    >>> normalized = q.to_normalized()
            )doc"
        )
        .def(
            "to_conjugate",
            &Quaternion::toConjugate,
            R"doc(
                Get the conjugate of the quaternion.

                Returns:
                    Quaternion: The conjugate quaternion.

                Example:
                    >>> q = Quaternion(1.0, 2.0, 3.0, 4.0, Quaternion.Format.XYZS)
                    >>> conjugate = q.to_conjugate()
            )doc"
        )
        .def(
            "to_inverse",
            &Quaternion::toInverse,
            R"doc(
                Get the inverse of the quaternion.

                Returns:
                    Quaternion: The inverse quaternion.

                Example:
                    >>> q = Quaternion.unit()
                    >>> inverse = q.to_inverse()
            )doc"
        )
        .def(
            "exp",
            &Quaternion::exp,
            R"doc(
                Compute the exponential of the quaternion.

                Returns:
                    Quaternion: The exponential of the quaternion.

                Example:
                    >>> q = Quaternion(0.1, 0.2, 0.3, 0.0, Quaternion.Format.XYZS)
                    >>> exp_q = q.exp()
            )doc"
        )
        .def(
            "log",
            &Quaternion::log,
            R"doc(
                Compute the natural logarithm of the quaternion.

                Returns:
                    Quaternion: The natural logarithm of the quaternion.

                Example:
                    >>> q = Quaternion.unit()
                    >>> log_q = q.log()
            )doc"
        )
        .def(
            "pow",
            &Quaternion::pow,
            R"doc(
                Raise the quaternion to a power.

                Args:
                    value (float): The exponent.

                Returns:
                    Quaternion: The quaternion raised to the power.

                Example:
                    >>> q = Quaternion.unit()
                    >>> powered = q.pow(2.0)
            )doc",
            arg("value")
        )
        .def(
            "norm",
            &Quaternion::norm,
            R"doc(
                Compute the norm (magnitude) of the quaternion.

                Returns:
                    float: The norm of the quaternion.

                Example:
                    >>> q = Quaternion(1.0, 2.0, 3.0, 4.0, Quaternion.Format.XYZS)
                    >>> magnitude = q.norm()
            )doc"
        )
        .def(
            "cross_multiply",
            &Quaternion::crossMultiply,
            R"doc(
                Perform cross multiplication with another quaternion.

                Args:
                    quaternion (Quaternion): The quaternion to multiply with.

                Returns:
                    Quaternion: The result of cross multiplication.

                Example:
                    >>> q1 = Quaternion.unit()
                    >>> q2 = Quaternion(0.1, 0.2, 0.3, 0.9, Quaternion.Format.XYZS)
                    >>> result = q1.cross_multiply(q2)
            )doc",
            arg("quaternion")
        )
        .def(
            "dot_multiply",
            &Quaternion::dotMultiply,
            R"doc(
                Perform dot multiplication with another quaternion.

                Args:
                    quaternion (Quaternion): The quaternion to multiply with.

                Returns:
                    Quaternion: The result of dot multiplication.

                Example:
                    >>> q1 = Quaternion.unit()
                    >>> q2 = Quaternion(0.1, 0.2, 0.3, 0.9, Quaternion.Format.XYZS)
                    >>> result = q1.dot_multiply(q2)
            )doc",
            arg("quaternion")
        )
        .def(
            "dot_product",
            &Quaternion::dotProduct,
            R"doc(
                Compute the dot product with another quaternion.

                Args:
                    quaternion (Quaternion): The quaternion to compute dot product with.

                Returns:
                    float: The dot product result.

                Example:
                    >>> q1 = Quaternion.unit()
                    >>> q2 = Quaternion(0.1, 0.2, 0.3, 0.9, Quaternion.Format.XYZS)
                    >>> dot = q1.dot_product(q2)
            )doc",
            arg("quaternion")
        )
        .def(
            "rotate_vector",
            &Quaternion::rotateVector,
            R"doc(
                Rotate a vector using this quaternion.

                Args:
                    vector (np.array): The 3D vector to rotate.
                    norm_tolerance (float, optional): Tolerance for normalization check.

                Returns:
                    Vector3d: The rotated vector.

                Example:
                    >>> q = Quaternion.unit()
                    >>> vector = np.array([1.0, 0.0, 0.0])
                    >>> rotated = q.rotate_vector(vector)
            )doc",
            arg("vector"),
            arg_v("norm_tolerance", Real::Epsilon(), "Real.epsilon()")
        )
        .def(
            "to_vector",
            &Quaternion::toVector,
            R"doc(
                Convert the quaternion to a 4D vector.

                Args:
                    format (Quaternion.Format): The format for the vector components.

                Returns:
                    Vector4d: The quaternion as a 4D vector.

                Example:
                    >>> q = Quaternion.unit()
                    >>> vector = q.to_vector(Quaternion.Format.XYZS)
            )doc",
            arg("format")
        )
        .def(
            "to_string",
            +[](const Quaternion& aQuaternion) -> String
            {
                return aQuaternion.toString();
            },
            R"doc(
                Convert the quaternion to string representation.

                Returns:
                    str: String representation of the quaternion.

                Example:
                    >>> q = Quaternion.unit()
                    >>> q.to_string()
            )doc"
        )
        .def(
            "to_string",
            +[](const Quaternion& aQuaternion, const Quaternion::Format aFormat) -> String
            {
                return aQuaternion.toString(aFormat);
            },
            R"doc(
                Convert the quaternion to string representation with specified format.

                Args:
                    format (Quaternion.Format): The format for string representation.

                Returns:
                    str: String representation of the quaternion.

                Example:
                    >>> q = Quaternion.unit()
                    >>> q.to_string(Quaternion.Format.SXYZ)
            )doc",
            arg("format")
        )
        .def(
            "normalize",
            +[](Quaternion& aQuaternion) -> void
            {
                aQuaternion.normalize();
            },
            R"doc(
                Normalize the quaternion in-place.

                Example:
                    >>> q = Quaternion(1.0, 1.0, 1.0, 1.0, Quaternion.Format.XYZS)
                    >>> q.normalize()
            )doc"
        )
        .def(
            "conjugate",
            +[](Quaternion& aQuaternion) -> void
            {
                aQuaternion.conjugate();
            },
            R"doc(
                Conjugate the quaternion in-place.

                Example:
                    >>> q = Quaternion(1.0, 2.0, 3.0, 4.0, Quaternion.Format.XYZS)
                    >>> q.conjugate()
            )doc"
        )
        .def(
            "inverse",
            +[](Quaternion& aQuaternion) -> void
            {
                aQuaternion.inverse();
            },
            R"doc(
                Invert the quaternion in-place.

                Example:
                    >>> q = Quaternion.unit()
                    >>> q.inverse()
            )doc"
        )
        .def(
            "rectify",
            +[](Quaternion& aQuaternion) -> void
            {
                aQuaternion.rectify();
            },
            R"doc(
                Rectify the quaternion in-place (ensure positive scalar part).

                Example:
                    >>> q = Quaternion(0.0, 0.0, 0.0, -1.0, Quaternion.Format.XYZS)
                    >>> q.rectify()
            )doc"
        )
        .def(
            "angular_difference_with",
            &Quaternion::angularDifferenceWith,
            R"doc(
                Compute the angular difference with another quaternion.

                Args:
                    quaternion (Quaternion): The quaternion to compare with.

                Returns:
                    Angle: The angular difference.

                Example:
                    >>> q1 = Quaternion.unit()
                    >>> q2 = Quaternion(0.1, 0.2, 0.3, 0.9, Quaternion.Format.XYZS)
                    >>> angle = q1.angular_difference_with(q2)
            )doc",
            arg("quaternion")
        )

        .def_static(
            "undefined",
            &Quaternion::Undefined,
            R"doc(
                Create an undefined quaternion.

                Returns:
                    Quaternion: An undefined quaternion.

                Example:
                    >>> q = Quaternion.undefined()
                    >>> q.is_defined()  # False
            )doc"
        )
        .def_static(
            "unit",
            &Quaternion::Unit,
            R"doc(
                Create a unit quaternion (identity rotation).

                Returns:
                    Quaternion: A unit quaternion.

                Example:
                    >>> q = Quaternion.unit()
                    >>> q.is_unitary()  # True
            )doc"
        )
        .def_static(
            "xyzs",
            &Quaternion::XYZS,
            R"doc(
                Create a quaternion in XYZS format.

                Args:
                    first_component (float): The x component.
                    second_component (float): The y component.
                    third_component (float): The z component.
                    fourth_component (float): The s component.

                Returns:
                    Quaternion: The quaternion in XYZS format.

                Example:
                    >>> q = Quaternion.xyzs(0.0, 0.0, 0.0, 1.0)
            )doc",
            arg("first_component"),
            arg("second_component"),
            arg("third_component"),
            arg("fourth_component")
        )
        .def_static(
            "rotation_vector",
            &Quaternion::RotationVector,
            R"doc(
                Create a quaternion from a rotation vector.

                Args:
                    rotation_vector (RotationVector): The rotation vector.

                Returns:
                    Quaternion: The quaternion representing the rotation.

                Example:
                    >>> rv = RotationVector([0.1, 0.2, 0.3], Angle.radians(1.0))
                    >>> q = Quaternion.rotation_vector(rv)
            )doc",
            arg("rotation_vector")
        )
        .def_static(
            "rotation_matrix",
            &Quaternion::RotationMatrix,
            R"doc(
                Create a quaternion from a rotation matrix.

                Args:
                    rotation_matrix (RotationMatrix): The rotation matrix.

                Returns:
                    Quaternion: The quaternion representing the rotation.

                Example:
                    >>> rm = RotationMatrix.identity()
                    >>> q = Quaternion.rotation_matrix(rm)
            )doc",
            arg("rotation_matrix")
        )
        .def_static(
            "euler_angle",
            &Quaternion::EulerAngle,
            R"doc(
                Create a quaternion from Euler angles.

                Args:
                    euler_angle (EulerAngle): The Euler angles.

                Returns:
                    Quaternion: The quaternion representing the rotation.

                Example:
                    >>> ea = EulerAngle(Angle.radians(0.1), Angle.radians(0.2), Angle.radians(0.3))
                    >>> q = Quaternion.euler_angle(ea)
            )doc",
            arg("euler_angle")
        )
        .def_static(
            "parse",
            &Quaternion::Parse,
            R"doc(
                Parse a quaternion from a string.

                Args:
                    string (str): The string representation of the quaternion.
                    format (Quaternion.Format): The format of the quaternion.

                Returns:
                    Quaternion: The parsed quaternion.

                Example:
                    >>> q = Quaternion.parse("[0.0, 0.0, 0.0, 1.0]", Quaternion.Format.XYZS)
            )doc",
            arg("string"),
            arg("format")
        )
        .def_static(
            "shortest_rotation",
            &Quaternion::ShortestRotation,
            R"doc(
                Create a quaternion representing the shortest rotation between two vectors.

                Args:
                    first_vector (np.array): The first vector.
                    second_vector (np.array): The second vector.

                Returns:
                    Quaternion: The quaternion representing the shortest rotation.

                Example:
                    >>> v1 = np.array([1.0, 0.0, 0.0])
                    >>> v2 = np.array([0.0, 1.0, 0.0])
                    >>> q = Quaternion.shortest_rotation(v1, v2)
            )doc",
            arg("first_vector"),
            arg("second_vector")
        )
        .def_static(
            "lerp",
            &Quaternion::LERP,
            R"doc(
                Linear interpolation between two quaternions.

                Args:
                    first_quaternion (Quaternion): The first quaternion.
                    second_quaternion (Quaternion): The second quaternion.
                    ratio (float): The interpolation ratio (0.0 to 1.0).

                Returns:
                    Quaternion: The interpolated quaternion.

                Example:
                    >>> q1 = Quaternion.unit()
                    >>> q2 = Quaternion(0.1, 0.2, 0.3, 0.9, Quaternion.Format.XYZS)
                    >>> q_interp = Quaternion.lerp(q1, q2, 0.5)
            )doc",
            arg("first_quaternion"),
            arg("second_quaternion"),
            arg("ratio")
        )
        .def_static(
            "nlerp",
            &Quaternion::NLERP,
            R"doc(
                Normalized linear interpolation between two quaternions.

                Args:
                    first_quaternion (Quaternion): The first quaternion.
                    second_quaternion (Quaternion): The second quaternion.
                    ratio (float): The interpolation ratio (0.0 to 1.0).

                Returns:
                    Quaternion: The normalized interpolated quaternion.

                Example:
                    >>> q1 = Quaternion.unit()
                    >>> q2 = Quaternion(0.1, 0.2, 0.3, 0.9, Quaternion.Format.XYZS)
                    >>> q_interp = Quaternion.nlerp(q1, q2, 0.5)
            )doc",
            arg("first_quaternion"),
            arg("second_quaternion"),
            arg("ratio")
        )
        .def_static(
            "slerp",
            &Quaternion::SLERP,
            R"doc(
                Spherical linear interpolation between two quaternions.

                Args:
                    first_quaternion (Quaternion): The first quaternion.
                    second_quaternion (Quaternion): The second quaternion.
                    ratio (float): The interpolation ratio (0.0 to 1.0).

                Returns:
                    Quaternion: The spherically interpolated quaternion.

                Example:
                    >>> q1 = Quaternion.unit()
                    >>> q2 = Quaternion(0.1, 0.2, 0.3, 0.9, Quaternion.Format.XYZS)
                    >>> q_interp = Quaternion.slerp(q1, q2, 0.5)
            )doc",
            arg("first_quaternion"),
            arg("second_quaternion"),
            arg("ratio")
        )

        ;

    enum_<Quaternion::Format>(quaternion, "Format")

        .value("XYZS", Quaternion::Format::XYZS)
        .value("SXYZ", Quaternion::Format::SXYZ)

        ;

    aModule.def("set_quaternion_array", overload_cast<const Array<Quaternion>&>(&set_quaternion_array));
}
