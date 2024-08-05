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
            arg("phi"),
            arg("theta"),
            arg("psi"),
            arg("axis_sequence")
        )
        .def(
            init<const Vector3d&, const Angle::Unit&, const EulerAngle::AxisSequence&>(),
            arg("vector"),
            arg("angle_unit"),
            arg("axis_sequence")
        )

        // Define methods
        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<EulerAngle>))
        .def("__repr__", &(shiftToString<EulerAngle>))

        .def("is_defined", &EulerAngle::isDefined)
        .def("is_unitary", &EulerAngle::isUnitary)
        .def("is_near", &EulerAngle::isNear, arg("euler_angle"), arg("angular_tolerance"))

        .def_property_readonly("phi", &EulerAngle::getPhi)
        .def_property_readonly("theta", &EulerAngle::getTheta)
        .def_property_readonly("psi", &EulerAngle::getPsi)
        .def_property_readonly("axis_sequence", &EulerAngle::getAxisSequence)

        .def("to_vector", &EulerAngle::toVector, arg("angle_unit"))
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
        .def_static("undefined", &EulerAngle::Undefined)
        .def_static("unit", &EulerAngle::Unit)
        .def_static("xyz", &EulerAngle::XYZ, arg("phi"), arg("theta"), arg("psi"))
        .def_static("zxy", &EulerAngle::ZXY, arg("phi"), arg("theta"), arg("psi"))
        .def_static("zyx", &EulerAngle::ZYX, arg("phi"), arg("theta"), arg("psi"))
        .def_static("quaternion", &EulerAngle::Quaternion, arg("quaternion"), arg("axis_sequence"))
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
