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
            arg("first_component"),
            arg("second_component"),
            arg("third_component"),
            arg("fourth_component"),
            arg("format")
        )

        .def(init<const Vector4d&, const Quaternion::Format&>(), arg("vector"), arg("format"))
        .def(init<const Vector3d&, const Real&>(), arg("vector_part"), arg("scalar_part"))
        .def(init<const Quaternion&>(), arg("quaternion"))

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

        .def("is_defined", &Quaternion::isDefined)
        .def("is_unitary", &Quaternion::isUnitary, arg_v("norm_tolerance", Real::Epsilon(), "Real.Epislon()"))
        .def("is_near", &Quaternion::isNear, arg("quaternion"), arg("angular_tolerance"))

        .def("x", &Quaternion::x)
        .def("y", &Quaternion::y)
        .def("z", &Quaternion::z)
        .def("s", &Quaternion::s)
        .def("get_vector_part", &Quaternion::getVectorPart)
        .def("get_scalar_part", &Quaternion::getScalarPart)
        .def("to_normalized", &Quaternion::toNormalized)
        .def("to_conjugate", &Quaternion::toConjugate)
        .def("to_inverse", &Quaternion::toInverse)
        .def("exp", &Quaternion::exp)
        .def("log", &Quaternion::log)
        .def("pow", &Quaternion::pow, arg("value"))
        .def("norm", &Quaternion::norm)
        .def("cross_multiply", &Quaternion::crossMultiply, arg("quaternion"))
        .def("dot_multiply", &Quaternion::dotMultiply, arg("quaternion"))
        .def("dot_product", &Quaternion::dotProduct, arg("quaternion"))
        .def(
            "rotate_vector",
            &Quaternion::rotateVector,
            arg("vector"),
            arg_v("norm_tolerance", Real::Epsilon(), "Real.Epsilon()")
        )
        .def("to_vector", &Quaternion::toVector, arg("format"))
        .def(
            "to_string",
            +[](const Quaternion& aQuaternion) -> String
            {
                return aQuaternion.toString();
            }
        )
        .def(
            "to_string",
            +[](const Quaternion& aQuaternion, const Quaternion::Format aFormat) -> String
            {
                return aQuaternion.toString(aFormat);
            }
        )
        .def(
            "normalize",
            +[](Quaternion& aQuaternion) -> void
            {
                aQuaternion.normalize();
            }
        )
        .def(
            "conjugate",
            +[](Quaternion& aQuaternion) -> void
            {
                aQuaternion.conjugate();
            }
        )
        .def(
            "inverse",
            +[](Quaternion& aQuaternion) -> void
            {
                aQuaternion.inverse();
            }
        )
        .def(
            "rectify",
            +[](Quaternion& aQuaternion) -> void
            {
                aQuaternion.rectify();
            }
        )
        .def("angular_difference_with", &Quaternion::angularDifferenceWith, arg("quaternion"))

        .def_static("undefined", &Quaternion::Undefined)
        .def_static("unit", &Quaternion::Unit)
        .def_static(
            "xyzs",
            &Quaternion::XYZS,
            arg("first_component"),
            arg("second_component"),
            arg("third_component"),
            arg("fourth_component")
        )
        .def_static("rotation_vector", &Quaternion::RotationVector, arg("rotation_vector"))
        .def_static("rotation_matrix", &Quaternion::RotationMatrix, arg("rotation_matrix"))
        .def_static("euler_angle", &Quaternion::EulerAngle, arg("euler_angle"))
        .def_static("parse", &Quaternion::Parse, arg("string"), arg("format"))
        .def_static("shortest_rotation", &Quaternion::ShortestRotation, arg("first_vector"), arg("second_vector"))
        .def_static("lerp", &Quaternion::LERP, arg("first_quaternion"), arg("second_quaternion"), arg("ratio"))
        .def_static("nlerp", &Quaternion::NLERP, arg("first_quaternion"), arg("second_quaternion"), arg("ratio"))
        .def_static("slerp", &Quaternion::SLERP, arg("first_quaternion"), arg("second_quaternion"), arg("ratio"))

        ;

    enum_<Quaternion::Format>(quaternion, "Format")

        .value("XYZS", Quaternion::Format::XYZS)
        .value("SXYZ", Quaternion::Format::SXYZ)

        ;

    aModule.def("set_quaternion_array", overload_cast<const Array<Quaternion>&>(&set_quaternion_array));
}
