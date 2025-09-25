/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationMatrix.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformation_Rotation_RotationMatrix(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;
    using ostk::core::type::String;

    using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix;
    using ostk::mathematics::object::Matrix3d;
    using ostk::mathematics::object::Vector3d;

    class_<RotationMatrix>(aModule, "RotationMatrix")

        // Define constructors
        .def(
            init<Matrix3d>(),
            R"doc(
                Create a rotation matrix from a 3x3 matrix.

                Args:
                    matrix (Matrix3d): A 3x3 matrix representing the rotation.

                Example:
                    >>> matrix = Matrix3d.identity()
                    >>> rotation_matrix = RotationMatrix(matrix)
            )doc",
            arg("matrix")
        )

        .def(
            init<
                const Real&,
                const Real&,
                const Real&,
                const Real&,
                const Real&,
                const Real&,
                const Real&,
                const Real&,
                const Real&>(),
            R"doc(
                Create a rotation matrix from nine coefficients (row-major order).

                Args:
                    first_coefficient (float): Matrix element (0,0).
                    second_coefficient (float): Matrix element (0,1).
                    third_coefficient (float): Matrix element (0,2).
                    fourth_coefficient (float): Matrix element (1,0).
                    fifth_coefficient (float): Matrix element (1,1).
                    sixth_coefficient (float): Matrix element (1,2).
                    seventh_coefficient (float): Matrix element (2,0).
                    eighth_coefficient (float): Matrix element (2,1).
                    ninth_coefficient (float): Matrix element (2,2).

                Example:
                    >>> rot_matrix = RotationMatrix(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0)
            )doc",
            arg("first_coefficient"),
            arg("second_coefficient"),
            arg("third_coefficient"),
            arg("fourth_coefficient"),
            arg("fifth_coefficient"),
            arg("sixth_coefficient"),
            arg("seventh_coefficient"),
            arg("eighth_coefficient"),
            arg("ninth_coefficient")
        )

        // Define methods
        .def(self == self)
        .def(self != self)

        .def(self * self)
        .def(self * Vector3d())

        .def("__str__", &(shiftToString<RotationMatrix>))
        .def("__repr__", &(shiftToString<RotationMatrix>))

        .def(
            "is_defined",
            &RotationMatrix::isDefined,
            R"doc(
                Check if the rotation matrix is defined.

                Returns:
                    bool: True if the rotation matrix is defined, False otherwise.

                Example:
                    >>> rot_matrix = RotationMatrix(Matrix3d.identity())
                    >>> rot_matrix.is_defined()  # True
            )doc"
        )

        .def(
            "get_row_at",
            &RotationMatrix::getRowAt,
            R"doc(
                Get a row of the rotation matrix at specified index.

                Args:
                    index (int): The row index (0, 1, or 2).

                Returns:
                    Vector3d: The row vector at the specified index.

                Example:
                    >>> rot_matrix = RotationMatrix.unit()
                    >>> first_row = rot_matrix.get_row_at(0)  # [1, 0, 0]
            )doc",
            arg("index")
        )
        .def(
            "get_column_at",
            &RotationMatrix::getColumnAt,
            R"doc(
                Get a column of the rotation matrix at specified index.

                Args:
                    index (int): The column index (0, 1, or 2).

                Returns:
                    Vector3d: The column vector at the specified index.

                Example:
                    >>> rot_matrix = RotationMatrix.unit()
                    >>> first_column = rot_matrix.get_column_at(0)  # [1, 0, 0]
            )doc",
            arg("index")
        )
        .def(
            "get_matrix",
            &RotationMatrix::getMatrix,
            R"doc(
                Get the underlying 3x3 matrix.

                Returns:
                    Matrix3d: The 3x3 rotation matrix.

                Example:
                    >>> rot_matrix = RotationMatrix.unit()
                    >>> matrix = rot_matrix.get_matrix()
            )doc"
        )
        .def(
            "to_transposed",
            &RotationMatrix::toTransposed,
            R"doc(
                Get the transpose of this rotation matrix.

                Returns:
                    RotationMatrix: The transposed rotation matrix.

                Example:
                    >>> rot_matrix = RotationMatrix.rx(Angle.degrees(90.0))
                    >>> transposed = rot_matrix.to_transposed()
            )doc"
        )
        .def(
            "transpose",
            +[](RotationMatrix& aRotationMatrix) -> void
            {
                aRotationMatrix.transpose();
            }
        )

        // Define static methods
        .def_static(
            "undefined",
            &RotationMatrix::Undefined,
            R"doc(
                Create an undefined rotation matrix.

                Returns:
                    RotationMatrix: An undefined rotation matrix.

                Example:
                    >>> undefined_matrix = RotationMatrix.undefined()
                    >>> undefined_matrix.is_defined()  # False
            )doc"
        )
        .def_static(
            "unit",
            &RotationMatrix::Unit,
            R"doc(
                Create a unit rotation matrix (identity matrix).

                Returns:
                    RotationMatrix: The 3x3 identity rotation matrix.

                Example:
                    >>> unit_matrix = RotationMatrix.unit()
                    >>> matrix = unit_matrix.get_matrix()  # 3x3 identity matrix
            )doc"
        )
        .def_static(
            "rx",
            &RotationMatrix::RX,
            R"doc(
                Create a rotation matrix for rotation around the X-axis.

                Args:
                    rotation_angle (Angle): The angle of rotation around X-axis.

                Returns:
                    RotationMatrix: A rotation matrix for X-axis rotation.

                Example:
                    >>> rot_x = RotationMatrix.rx(Angle.degrees(90.0))
            )doc",
            arg("rotation_angle")
        )
        .def_static(
            "ry",
            &RotationMatrix::RY,
            R"doc(
                Create a rotation matrix for rotation around the Y-axis.

                Args:
                    rotation_angle (Angle): The angle of rotation around Y-axis.

                Returns:
                    RotationMatrix: A rotation matrix for Y-axis rotation.

                Example:
                    >>> rot_y = RotationMatrix.ry(Angle.degrees(90.0))
            )doc",
            arg("rotation_angle")
        )
        .def_static(
            "rz",
            &RotationMatrix::RZ,
            R"doc(
                Create a rotation matrix for rotation around the Z-axis.

                Args:
                    rotation_angle (Angle): The angle of rotation around Z-axis.

                Returns:
                    RotationMatrix: A rotation matrix for Z-axis rotation.

                Example:
                    >>> rot_z = RotationMatrix.rz(Angle.degrees(90.0))
            )doc",
            arg("rotation_angle")
        )
        .def_static("rows", &RotationMatrix::Rows, arg("first_row"), arg("second_row"), arg("third_row"))
        .def_static("columns", &RotationMatrix::Columns, arg("first_column"), arg("second_column"), arg("third_column"))
        .def_static(
            "quaternion",
            &RotationMatrix::Quaternion,
            R"doc(
                Create a rotation matrix from a quaternion.

                Args:
                    quaternion (Quaternion): The quaternion to convert.

                Returns:
                    RotationMatrix: The equivalent rotation matrix.

                Example:
                    >>> quat = Quaternion.unit()
                    >>> rot_matrix = RotationMatrix.quaternion(quat)
            )doc",
            arg("quaternion")
        )
        .def_static("rotation_vector", &RotationMatrix::RotationVector, arg("rotation_vector"))
        .def_static("euler_angle", &RotationMatrix::EulerAngle, arg("euler_angle"))

        ;
}
