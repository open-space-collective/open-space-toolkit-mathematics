/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/Angle.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_Angle(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;
    using ostk::core::type::String;

    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::object::Vector2d;
    using ostk::mathematics::object::Vector3d;

    class_<Angle> angle(aModule, "Angle");

    // Define constructor
    angle
        .def(init<Real, Angle::Unit>(), arg("value"), arg("unit"))

        // Define methods
        .def(self == self)
        .def(self != self)

        .def(self + self)
        .def(self - self)

        .def(+self)
        .def(-self)

        // Real has default constructor deleted
        // https://docs.python.org/3/library/operator.html
        // .def(self * Real())
        // .def(self / Real())
        // .def(self *= Real())
        // .def(self /= Real())
        .def(
            "__mul__",
            [](const Angle& anAngle, Real aReal)
            {
                return anAngle * aReal;
            },
            is_operator()
        )
        .def(
            "__truediv__",
            [](const Angle& anAngle, Real aReal)
            {
                return anAngle / aReal;
            },
            is_operator()
        )
        .def(
            "__imul__",
            [](const Angle& anAngle, Real aReal)
            {
                return anAngle * aReal;
            },
            is_operator()
        )
        .def(
            "__itruediv__",
            [](const Angle& anAngle, Real aReal)
            {
                return anAngle / aReal;
            },
            is_operator()
        )

        .def(self += self)
        .def(self -= self)

        .def("__str__", &(shiftToString<Angle>))
        .def(
            "__repr__",
            +[](const Angle& anAngle) -> std::string
            {
                return anAngle.toString();
            }
        )

        .def("is_defined", &Angle::isDefined)
        .def("is_zero", &Angle::isZero)
        .def("is_negative", &Angle::isNegative)
        .def("is_near", &Angle::isNear, arg("angle"), arg("tolerance"))

        .def("get_unit", &Angle::getUnit)
        .def("in_unit", &Angle::in, arg("unit"))
        .def("in_radians", overload_cast<>(&Angle::inRadians, const_))
        .def(
            "in_radians",
            overload_cast<const Real&, const Real&>(&Angle::inRadians, const_),
            arg("lower_bound"),
            arg("upper_bound")
        )
        .def("in_degrees", overload_cast<>(&Angle::inDegrees, const_))
        .def(
            "in_degrees",
            overload_cast<const Real&, const Real&>(&Angle::inDegrees, const_),
            arg("lower_bound"),
            arg("upper_bound")
        )
        .def("in_arcminutes", overload_cast<>(&Angle::inArcminutes, const_))
        .def(
            "in_arcminutes",
            overload_cast<const Real&, const Real&>(&Angle::inArcminutes, const_),
            arg("lower_bound"),
            arg("upper_bound")
        )
        .def("in_arcseconds", overload_cast<>(&Angle::inArcseconds, const_))
        .def(
            "in_arcseconds",
            overload_cast<const Real&, const Real&>(&Angle::inArcseconds, const_),
            arg("lower_bound"),
            arg("upper_bound")
        )
        .def("in_revolutions", &Angle::inRevolutions)
        .def("to_string", &Angle::toString, arg("do_sanitize") = false)

        // Define static methods
        .def_static("undefined", &Angle::Undefined)
        .def_static("zero", &Angle::Zero)
        .def_static("half_pi", &Angle::HalfPi)
        .def_static("pi", &Angle::Pi)
        .def_static("two_pi", &Angle::TwoPi)
        .def_static("radians", &Angle::Radians, arg("value"))
        .def_static("degrees", &Angle::Degrees, arg("value"))
        .def_static("arcminutes", &Angle::Arcminutes, arg("value"))
        .def_static("arcseconds", &Angle::Arcseconds, arg("value"))
        .def_static("revolutions", &Angle::Revolutions, arg("value"))
        .def_static(
            "between",
            overload_cast<const Vector2d&, const Vector2d&>(&Angle::Between),
            arg("first_vector"),
            arg("second_vector")
        )
        .def_static(
            "between",
            overload_cast<const Vector3d&, const Vector3d&>(&Angle::Between),
            arg("first_vector"),
            arg("second_vector")
        )

        .def_static("string_from_unit", &Angle::StringFromUnit, arg("unit"))
        .def_static("symbol_from_unit", &Angle::SymbolFromUnit, arg("unit"))

        ;

    // Define emuneration unit for "angle"
    enum_<Angle::Unit>(angle, "Unit")
        .value("Undefined", Angle::Unit::Undefined)
        .value("Radian", Angle::Unit::Radian)
        .value("Degree", Angle::Unit::Degree)
        .value("Arcminute", Angle::Unit::Arcminute)
        .value("Arcsecond", Angle::Unit::Arcsecond)
        .value("Revolution", Angle::Unit::Revolution)

        ;
}
