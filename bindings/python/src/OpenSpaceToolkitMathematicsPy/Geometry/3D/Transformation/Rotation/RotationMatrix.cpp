/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationMatrix.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformation_Rotation_RotationMatrix(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;
    using ostk::core::type::String;

    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::object::Matrix3d;
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix;

    class_<RotationMatrix>(aModule, "RotationMatrix")

        // Define constructors
        .def(init<Matrix3d>(), arg("matrix"))

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

        .def("is_defined", &RotationMatrix::isDefined)

        .def("get_row_at", &RotationMatrix::getRowAt, arg("index"))
        .def("get_column_at", &RotationMatrix::getColumnAt, arg("index"))
        .def("to_transposed", &RotationMatrix::toTransposed)
        .def(
            "transpose",
            +[](RotationMatrix& aRotationMatrix) -> void
            {
                aRotationMatrix.transpose();
            }
        )

        // Define static methods
        .def_static("undefined", &RotationMatrix::Undefined)
        .def_static("unit", &RotationMatrix::Unit)
        .def_static("rx", &RotationMatrix::RX, arg("rotation_angle"))
        .def_static("ry", &RotationMatrix::RY, arg("rotation_angle"))
        .def_static("rz", &RotationMatrix::RZ, arg("rotation_angle"))
        .def_static("rows", &RotationMatrix::Rows, arg("first_row"), arg("second_row"), arg("third_row"))
        .def_static("columns", &RotationMatrix::Columns, arg("first_column"), arg("second_column"), arg("third_column"))
        .def_static("quaternion", &RotationMatrix::Quaternion, arg("quaternion"))
        .def_static("rotation_vector", &RotationMatrix::RotationVector, arg("rotation_vector"))

        ;
}
