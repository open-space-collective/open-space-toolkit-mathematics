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
                    axis (Vector3d): The rotation axis (will be normalized).
                    angle (Angle): The rotation angle around the axis.

                Example:
                    >>> axis = Vector3d([0.0, 0.0, 1.0])
                    >>> angle = Angle.degrees(90.0)
                    >>> rot_vector = RotationVector(axis, angle)
            )doc",
            arg("axis"),
            arg("angle")
        )
        .def(init<const Vector3d&, const Angle::Unit&>(), arg("vector"), arg("angle_unit"))

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
                    >>> rot_vector = RotationVector(Vector3d([1.0, 0.0, 0.0]), angle)
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
            }
        )
        .def(
            "to_string",
            +[](const RotationVector& aRotationVector, const Integer& aPrecision) -> String
            {
                return aRotationVector.toString(aPrecision);
            }
        )

        .def(
            "rectify",
            +[](RotationVector& aRotationVector) -> void
            {
                aRotationVector.rectify();
            }
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
        .def_static("x", &RotationVector::X, arg("angle"))
        .def_static("y", &RotationVector::Y, arg("angle"))
        .def_static("z", &RotationVector::Z, arg("angle"))
        .def_static("quaternion", &RotationVector::Quaternion, arg("quaternion"))
        .def_static("rotation_matrix", &RotationVector::RotationMatrix, arg("rotation_matrix"))
        .def_static("euler_angle", &RotationVector::EulerAngle, arg("euler_angle"))

        ;
}
