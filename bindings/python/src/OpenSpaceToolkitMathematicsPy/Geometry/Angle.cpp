// Copyright © Loft Orbital Solutions Inc.

#include <OpenSpaceToolkit/Mathematics/Geometry/Angle.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_Angle(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::types::Real;
    using ostk::core::types::String;

    using ostk::math::obj::Vector2d;
    using ostk::math::obj::Vector3d;
    using ostk::math::geom::Angle;

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

        .def("get_unit", &Angle::getUnit)
        .def("in_unit", &Angle::in, arg("unit"))
        .def(
            "in_radians",
            +[](const Angle& anAngle) -> Real
            {
                return anAngle.inRadians();
            }
        )
        .def(
            "in_degrees",
            +[](const Angle& anAngle) -> Real
            {
                return anAngle.inDegrees();
            }
        )
        .def(
            "in_arcminutes",
            +[](const Angle& anAngle) -> Real
            {
                return anAngle.inArcminutes();
            }
        )
        .def(
            "in_arcseconds",
            +[](const Angle& anAngle) -> Real
            {
                return anAngle.inArcseconds();
            }
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
