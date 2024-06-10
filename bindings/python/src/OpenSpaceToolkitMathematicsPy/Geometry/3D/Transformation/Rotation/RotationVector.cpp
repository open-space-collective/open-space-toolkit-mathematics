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

    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;

    class_<RotationVector>(aModule, "RotationVector")

        // Define constructor
        .def(init<const Vector3d&, const Angle&>(), arg("axis"), arg("angle"))
        .def(init<const Vector3d&, const Angle::Unit&>(), arg("vector"), arg("angle_unit"))

        // Define methods
        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<RotationVector>))
        .def("__repr__", &(shiftToString<RotationVector>))

        .def("is_defined", &RotationVector::isDefined)

        .def("get_axis", &RotationVector::getAxis)
        .def("get_angle", &RotationVector::getAngle)
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
        .def_static("undefined", &RotationVector::Undefined)
        .def_static("unit", &RotationVector::Unit)
        .def_static("x", &RotationVector::X, arg("angle"))
        .def_static("y", &RotationVector::Y, arg("angle"))
        .def_static("z", &RotationVector::Z, arg("angle"))
        .def_static("quaternion", &RotationVector::Quaternion, arg("quaternion"))
        .def_static("rotation_matrix", &RotationVector::RotationMatrix, arg("rotation_matrix"))
        .def_static("euler_angle", &RotationVector::EulerAngle, arg("euler_angle"))

        ;
}
