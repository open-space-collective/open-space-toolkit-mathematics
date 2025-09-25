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
        .def(
            init<Real, Angle::Unit>(),
            R"doc(
                Create an angle with specified value and unit.

                Args:
                    value (float): The numerical value of the angle.
                    unit (Angle.Unit): The unit of the angle (Radian, Degree, etc.).

                Example:
                    >>> angle = Angle(3.14159, Angle.Unit.Radian)
                    >>> angle = Angle(180.0, Angle.Unit.Degree)
            )doc",
            arg("value"),
            arg("unit")
        )

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

        .def(
            "is_defined",
            &Angle::isDefined,
            R"doc(
                Check if the angle is defined.

                Returns:
                    bool: True if the angle is defined, False otherwise.

                Example:
                    >>> angle = Angle.radians(1.0)
                    >>> angle.is_defined()  # True
            )doc"
        )
        .def(
            "is_zero",
            &Angle::isZero,
            R"doc(
                Check if the angle is zero.

                Returns:
                    bool: True if the angle is zero, False otherwise.

                Example:
                    >>> angle = Angle.zero()
                    >>> angle.is_zero()  # True
            )doc"
        )
        .def(
            "is_negative",
            &Angle::isNegative,
            R"doc(
                Check if the angle is negative.

                Returns:
                    bool: True if the angle is negative, False otherwise.

                Example:
                    >>> angle = Angle.degrees(-30.0)
                    >>> angle.is_negative()  # True
            )doc"
        )
        .def(
            "is_near",
            &Angle::isNear,
            R"doc(
                Check if this angle is near another angle within a tolerance.

                Args:
                    angle (Angle): The angle to compare with.
                    tolerance (Angle): The tolerance for comparison.

                Returns:
                    bool: True if angles are within tolerance, False otherwise.

                Example:
                    >>> angle1 = Angle.degrees(30.0)
                    >>> angle2 = Angle.degrees(30.1)
                    >>> tolerance = Angle.degrees(0.2)
                    >>> angle1.is_near(angle2, tolerance)  # True
            )doc",
            arg("angle"),
            arg("tolerance")
        )

        .def(
            "get_unit",
            &Angle::getUnit,
            R"doc(
                Get the unit of the angle.

                Returns:
                    Angle.Unit: The unit of the angle.

                Example:
                    >>> angle = Angle.degrees(90.0)
                    >>> angle.get_unit()  # Angle.Unit.Degree
            )doc"
        )
        .def(
            "in_unit",
            &Angle::in,
            R"doc(
                Get the angle value in a specific unit.

                Args:
                    unit (Angle.Unit): The unit to convert to.

                Returns:
                    float: The angle value in the specified unit.

                Example:
                    >>> angle = Angle.degrees(180.0)
                    >>> angle.in_unit(Angle.Unit.Radian)  # ~3.14159
            )doc",
            arg("unit")
        )
        .def(
            "in_radians",
            overload_cast<>(&Angle::inRadians, const_),
            R"doc(
                Get the angle value in radians.

                Returns:
                    float: The angle value in radians.

                Example:
                    >>> angle = Angle.degrees(180.0)
                    >>> angle.in_radians()  # ~3.14159
            )doc"
        )
        .def(
            "in_radians",
            overload_cast<const Real&, const Real&>(&Angle::inRadians, const_),
            R"doc(
                Get the angle value in radians within specified bounds.

                Args:
                    lower_bound (float): The lower bound in radians.
                    upper_bound (float): The upper bound in radians.

                Returns:
                    float: The angle value in radians, wrapped within bounds.

                Example:
                    >>> angle = Angle.radians(7.0)
                    >>> angle.in_radians(-3.14159, 3.14159)  # Wrapped to [-π, π]
            )doc",
            arg("lower_bound"),
            arg("upper_bound")
        )
        .def(
            "in_degrees",
            overload_cast<>(&Angle::inDegrees, const_),
            R"doc(
                Get the angle value in degrees.

                Returns:
                    float: The angle value in degrees.

                Example:
                    >>> angle = Angle.radians(3.14159)
                    >>> angle.in_degrees()  # ~180.0
            )doc"
        )
        .def(
            "in_degrees",
            overload_cast<const Real&, const Real&>(&Angle::inDegrees, const_),
            R"doc(
                Get the angle value in degrees within specified bounds.

                Args:
                    lower_bound (float): The lower bound in degrees.
                    upper_bound (float): The upper bound in degrees.

                Returns:
                    float: The angle value in degrees, wrapped within bounds.

                Example:
                    >>> angle = Angle.degrees(450.0)
                    >>> angle.in_degrees(-180.0, 180.0)  # 90.0
            )doc",
            arg("lower_bound"),
            arg("upper_bound")
        )
        .def(
            "in_arcminutes",
            overload_cast<>(&Angle::inArcminutes, const_),
            R"doc(
                Get the angle value in arcminutes.

                Returns:
                    float: The angle value in arcminutes.

                Example:
                    >>> angle = Angle.degrees(1.0)
                    >>> angle.in_arcminutes()  # 60.0
            )doc"
        )
        .def(
            "in_arcminutes",
            overload_cast<const Real&, const Real&>(&Angle::inArcminutes, const_),
            R"doc(
                Get the angle value in arcminutes within specified bounds.

                Args:
                    lower_bound (float): The lower bound in arcminutes.
                    upper_bound (float): The upper bound in arcminutes.

                Returns:
                    float: The angle value in arcminutes, wrapped within bounds.
            )doc",
            arg("lower_bound"),
            arg("upper_bound")
        )
        .def(
            "in_arcseconds",
            overload_cast<>(&Angle::inArcseconds, const_),
            R"doc(
                Get the angle value in arcseconds.

                Returns:
                    float: The angle value in arcseconds.

                Example:
                    >>> angle = Angle.degrees(1.0)
                    >>> angle.in_arcseconds()  # 3600.0
            )doc"
        )
        .def(
            "in_arcseconds",
            overload_cast<const Real&, const Real&>(&Angle::inArcseconds, const_),
            R"doc(
                Get the angle value in arcseconds within specified bounds.

                Args:
                    lower_bound (float): The lower bound in arcseconds.
                    upper_bound (float): The upper bound in arcseconds.

                Returns:
                    float: The angle value in arcseconds, wrapped within bounds.
            )doc",
            arg("lower_bound"),
            arg("upper_bound")
        )
        .def(
            "in_revolutions",
            &Angle::inRevolutions,
            R"doc(
                Get the angle value in revolutions.

                Returns:
                    float: The angle value in revolutions.

                Example:
                    >>> angle = Angle.degrees(360.0)
                    >>> angle.in_revolutions()  # 1.0
            )doc"
        )
        .def(
            "to_string",
            &Angle::toString,
            R"doc(
                Convert the angle to a string representation.

                Args:
                    do_sanitize (bool, optional): Whether to sanitize the output. Defaults to False.

                Returns:
                    str: String representation of the angle.

                Example:
                    >>> angle = Angle.degrees(90.0)
                    >>> angle.to_string()  # "90.0 [deg]"
            )doc",
            arg("do_sanitize") = false
        )

        // Define static methods
        .def_static(
            "undefined",
            &Angle::Undefined,
            R"doc(
                Create an undefined angle.

                Returns:
                    Angle: An undefined angle.

                Example:
                    >>> undefined_angle = Angle.undefined()
                    >>> undefined_angle.is_defined()  # False
            )doc"
        )
        .def_static(
            "zero",
            &Angle::Zero,
            R"doc(
                Create a zero angle.

                Returns:
                    Angle: A zero angle (0 radians).

                Example:
                    >>> zero_angle = Angle.zero()
                    >>> zero_angle.is_zero()  # True
            )doc"
        )
        .def_static(
            "half_pi",
            &Angle::HalfPi,
            R"doc(
                Create an angle of π/2 radians (90 degrees).

                Returns:
                    Angle: An angle of π/2 radians.

                Example:
                    >>> half_pi = Angle.half_pi()
                    >>> half_pi.in_degrees()  # 90.0
            )doc"
        )
        .def_static(
            "pi",
            &Angle::Pi,
            R"doc(
                Create an angle of π radians (180 degrees).

                Returns:
                    Angle: An angle of π radians.

                Example:
                    >>> pi = Angle.pi()
                    >>> pi.in_degrees()  # 180.0
            )doc"
        )
        .def_static(
            "two_pi",
            &Angle::TwoPi,
            R"doc(
                Create an angle of 2π radians (360 degrees).

                Returns:
                    Angle: An angle of 2π radians.

                Example:
                    >>> two_pi = Angle.two_pi()
                    >>> two_pi.in_degrees()  # 360.0
            )doc"
        )
        .def_static(
            "radians",
            &Angle::Radians,
            R"doc(
                Create an angle from a value in radians.

                Args:
                    value (float): The angle value in radians.

                Returns:
                    Angle: An angle with the specified value in radians.

                Example:
                    >>> angle = Angle.radians(3.14159)
                    >>> angle.in_degrees()  # ~180.0
            )doc",
            arg("value")
        )
        .def_static(
            "degrees",
            &Angle::Degrees,
            R"doc(
                Create an angle from a value in degrees.

                Args:
                    value (float): The angle value in degrees.

                Returns:
                    Angle: An angle with the specified value in degrees.

                Example:
                    >>> angle = Angle.degrees(180.0)
                    >>> angle.in_radians()  # ~3.14159
            )doc",
            arg("value")
        )
        .def_static(
            "arcminutes",
            &Angle::Arcminutes,
            R"doc(
                Create an angle from a value in arcminutes.

                Args:
                    value (float): The angle value in arcminutes.

                Returns:
                    Angle: An angle with the specified value in arcminutes.

                Example:
                    >>> angle = Angle.arcminutes(60.0)
                    >>> angle.in_degrees()  # 1.0
            )doc",
            arg("value")
        )
        .def_static(
            "arcseconds",
            &Angle::Arcseconds,
            R"doc(
                Create an angle from a value in arcseconds.

                Args:
                    value (float): The angle value in arcseconds.

                Returns:
                    Angle: An angle with the specified value in arcseconds.

                Example:
                    >>> angle = Angle.arcseconds(3600.0)
                    >>> angle.in_degrees()  # 1.0
            )doc",
            arg("value")
        )
        .def_static(
            "revolutions",
            &Angle::Revolutions,
            R"doc(
                Create an angle from a value in revolutions.

                Args:
                    value (float): The angle value in revolutions.

                Returns:
                    Angle: An angle with the specified value in revolutions.

                Example:
                    >>> angle = Angle.revolutions(1.0)
                    >>> angle.in_degrees()  # 360.0
            )doc",
            arg("value")
        )
        .def_static(
            "between",
            overload_cast<const Vector2d&, const Vector2d&>(&Angle::Between),
            R"doc(
                Calculate the angle between two 2D vectors.

                Args:
                    first_vector (Vector2d): The first vector.
                    second_vector (Vector2d): The second vector.

                Returns:
                    Angle: The angle between the vectors.

                Example:
                    >>> v1 = Vector2d([1.0, 0.0])
                    >>> v2 = Vector2d([0.0, 1.0])
                    >>> angle = Angle.between(v1, v2)
                    >>> angle.in_degrees()  # 90.0
            )doc",
            arg("first_vector"),
            arg("second_vector")
        )
        .def_static(
            "between",
            overload_cast<const Vector3d&, const Vector3d&>(&Angle::Between),
            R"doc(
                Calculate the angle between two 3D vectors.

                Args:
                    first_vector (Vector3d): The first vector.
                    second_vector (Vector3d): The second vector.

                Returns:
                    Angle: The angle between the vectors.

                Example:
                    >>> v1 = Vector3d([1.0, 0.0, 0.0])
                    >>> v2 = Vector3d([0.0, 1.0, 0.0])
                    >>> angle = Angle.between(v1, v2)
                    >>> angle.in_degrees()  # 90.0
            )doc",
            arg("first_vector"),
            arg("second_vector")
        )

        .def_static(
            "string_from_unit",
            &Angle::StringFromUnit,
            R"doc(
                Get the string representation of an angle unit.

                Args:
                    unit (Angle.Unit): The angle unit.

                Returns:
                    str: String representation of the unit.

                Example:
                    >>> Angle.string_from_unit(Angle.Unit.Degree)  # "Degree"
            )doc",
            arg("unit")
        )
        .def_static(
            "symbol_from_unit",
            &Angle::SymbolFromUnit,
            R"doc(
                Get the symbol representation of an angle unit.

                Args:
                    unit (Angle.Unit): The angle unit.

                Returns:
                    str: Symbol representation of the unit.

                Example:
                    >>> Angle.symbol_from_unit(Angle.Unit.Degree)  # "deg"
                    >>> Angle.symbol_from_unit(Angle.Unit.Radian)  # "rad"
            )doc",
            arg("unit")
        )

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
