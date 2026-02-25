/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Geometry_Angle__
#define __OpenSpaceToolkit_Mathematics_Geometry_Angle__

#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

namespace ostk
{
namespace mathematics
{
namespace geometry
{

using ostk::core::type::Integer;
using ostk::core::type::Real;
using ostk::core::type::String;

using ostk::mathematics::object::Vector2d;
using ostk::mathematics::object::Vector3d;

/// @brief                      Angle
///
///                             In plane geometry, an angle is the figure formed by two rays, called the sides of the
///                             angle, sharing a common endpoint, called the vertex of the angle.
///
/// @code{.cpp}
///                             Angle angle = Angle::Degrees(90.0);
/// @endcode
///
/// @ref                        https://en.wikipedia.org/wiki/Angle
class Angle
{
   public:
    enum class Unit
    {

        Undefined,  ///< Undefined
        Radian,     ///< Radian
        Degree,     ///< Degree
        Arcminute,  ///< Arcminute
        Arcsecond,  ///< Arcsecond
        Revolution  ///< Revolution

    };

    /// @brief              Constructor
    ///
    /// @code
    ///                     Angle angle(90.0, Angle::Unit::Degree) ;
    /// @endcode
    ///
    /// @param              [in] aValue A value
    /// @param              [in] aUnit An angle unit
    Angle(const Real& aValue, const Angle::Unit& aUnit);

    /// @brief              Check if two angles are equal
    ///
    /// @code{.cpp}
    ///                     Angle::Degrees(90.0) == Angle::Degrees(90.0);
    /// @endcode
    ///
    /// @param              [in] anAngle An angle
    /// @return             True if angles are equal
    bool operator==(const Angle& anAngle) const;

    /// @brief              Check if two angles are not equal
    ///
    /// @code{.cpp}
    ///                     Angle::Degrees(90.0) != Angle::Degrees(45.0);
    /// @endcode
    ///
    /// @param              [in] anAngle An angle
    /// @return             True if angles are not equal
    bool operator!=(const Angle& anAngle) const;

    /// @brief              Addition operator
    ///
    /// @code{.cpp}
    ///                     Angle angle = Angle::Degrees(90.0) + Angle::Degrees(45.0);
    /// @endcode
    ///
    /// @param              [in] anAngle An angle to add
    /// @return             Sum of the two angles
    Angle operator+(const Angle& anAngle) const;

    /// @brief              Subtraction operator
    ///
    /// @code{.cpp}
    ///                     Angle angle = Angle::Degrees(90.0) - Angle::Degrees(45.0);
    /// @endcode
    ///
    /// @param              [in] anAngle An angle to subtract
    /// @return             Difference of the two angles
    Angle operator-(const Angle& anAngle) const;

    /// @brief              Multiplication operator (angle * scalar)
    ///
    /// @code{.cpp}
    ///                     Angle angle = Angle::Degrees(90.0) * 2.0;
    /// @endcode
    ///
    /// @param              [in] aReal A scalar multiplier
    /// @return             Scaled angle
    Angle operator*(const Real& aReal) const;

    /// @brief              Division operator
    ///
    /// @code{.cpp}
    ///                     Angle angle = Angle::Degrees(90.0) / 2.0;
    /// @endcode
    ///
    /// @param              [in] aReal A scalar divisor
    /// @return             Scaled angle
    Angle operator/(const Real& aReal) const;

    /// @brief              Addition assignment operator
    ///
    /// @code{.cpp}
    ///                     Angle angle = Angle::Degrees(90.0);
    ///                     angle += Angle::Degrees(45.0);
    /// @endcode
    ///
    /// @param              [in] anAngle An angle to add
    /// @return             Reference to the modified angle
    Angle& operator+=(const Angle& anAngle);

    /// @brief              Subtraction assignment operator
    ///
    /// @code{.cpp}
    ///                     Angle angle = Angle::Degrees(90.0);
    ///                     angle -= Angle::Degrees(45.0);
    /// @endcode
    ///
    /// @param              [in] anAngle An angle to subtract
    /// @return             Reference to the modified angle
    Angle& operator-=(const Angle& anAngle);

    /// @brief              Multiplication assignment operator
    ///
    /// @code{.cpp}
    ///                     Angle angle = Angle::Degrees(90.0);
    ///                     angle *= 2.0;
    /// @endcode
    ///
    /// @param              [in] aReal A scalar multiplier
    /// @return             Reference to the modified angle
    Angle& operator*=(const Real& aReal);

    /// @brief              Division assignment operator
    ///
    /// @code{.cpp}
    ///                     Angle angle = Angle::Degrees(90.0);
    ///                     angle /= 2.0;
    /// @endcode
    ///
    /// @param              [in] aReal A scalar divisor
    /// @return             Reference to the modified angle
    Angle& operator/=(const Real& aReal);

    /// @brief              Multiplication operator (scalar * angle)
    ///
    /// @code{.cpp}
    ///                     Angle angle = 2.0 * Angle::Degrees(90.0);
    /// @endcode
    ///
    /// @param              [in] aReal A scalar multiplier
    /// @param              [in] anAngle An angle
    /// @return             Scaled angle
    friend Angle operator*(const Real& aReal, const Angle& anAngle);

    /// @brief              Unary positive operator
    ///
    /// @code{.cpp}
    ///                     Angle angle = +Angle::Degrees(90.0);
    /// @endcode
    ///
    /// @return             Copy of the angle
    Angle operator+() const;

    /// @brief              Unary negative operator
    ///
    /// @code{.cpp}
    ///                     Angle angle = -Angle::Degrees(90.0);
    /// @endcode
    ///
    /// @return             Negated angle
    Angle operator-() const;

    /// @brief              Output stream operator
    ///
    /// @code{.cpp}
    ///                     std::cout << Angle::Degrees(90.0);
    /// @endcode
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] anAngle An angle
    /// @return             Reference to the output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Angle& anAngle);

    /// @brief              Check if the angle is defined
    ///
    /// @code{.cpp}
    ///                     Angle::Degrees(90.0).isDefined();  // True
    /// @endcode
    ///
    /// @return             True if the angle is defined
    bool isDefined() const;

    /// @brief              Check if the angle is zero
    ///
    /// @code{.cpp}
    ///                     Angle::Zero().isZero();  // True
    /// @endcode
    ///
    /// @return             True if the angle is zero
    bool isZero() const;

    /// @brief                  Check if angle is negative
    ///
    /// @code
    ///                         Angle::Zero().isNegative();
    /// @endcode
    ///
    /// @return                 True if angle is negative
    bool isNegative() const;

    /// @brief                  Check if angles are near within an angular tolerance
    ///
    /// @code
    ///                         Angle::Zero().isNear(
    ///                             Angle::Degrees(1.0),
    ///                             Angle::Degrees(2.0)
    ///                         );
    /// @endcode
    ///
    /// @param                  [in] anAngle An angle
    /// @param                  [in] aTolerance A tolerance
    /// @return                 True if angles are near
    bool isNear(const Angle& anAngle, const Angle& aTolerance) const;

    /// @brief              Get the unit of the angle
    ///
    /// @code{.cpp}
    ///                     Angle::Unit unit = Angle::Degrees(90.0).getUnit();
    /// @endcode
    ///
    /// @return             The angle unit
    Angle::Unit getUnit() const;

    /// @brief              Get the angle value in the specified unit
    ///
    /// @code{.cpp}
    ///                     Real value = Angle::Degrees(90.0).in(Angle::Unit::Radian);
    /// @endcode
    ///
    /// @param              [in] aUnit An angle unit
    /// @return             The angle value in the specified unit
    Real in(const Angle::Unit& aUnit) const;

    /// @brief              Get the angle value in radians
    ///
    /// @code{.cpp}
    ///                     Angle::Degrees(180.0).inRadians();  // ~3.14159
    /// @endcode
    ///
    /// @return             The angle value in radians
    Real inRadians() const;

    /// @brief              Get the angle value in radians, reduced to a specified range
    ///
    /// @code{.cpp}
    ///                     Angle::Degrees(270.0).inRadians(0.0, Real::TwoPi());
    /// @endcode
    ///
    /// @param              [in] aLowerBound A lower bound of the range (in radians)
    /// @param              [in] anUpperBound An upper bound of the range (in radians)
    /// @return             The angle value in radians within the specified range
    Real inRadians(const Real& aLowerBound, const Real& anUpperBound) const;

    /// @brief              Get the angle value in degrees
    ///
    /// @code{.cpp}
    ///                     Angle::Radians(Real::Pi()).inDegrees();  // 180.0
    /// @endcode
    ///
    /// @return             The angle value in degrees
    Real inDegrees() const;

    /// @brief              Get the angle value in degrees, reduced to a specified range
    ///
    /// @code{.cpp}
    ///                     Angle::Degrees(370.0).inDegrees(0.0, 360.0);
    /// @endcode
    ///
    /// @param              [in] aLowerBound A lower bound of the range (in degrees)
    /// @param              [in] anUpperBound An upper bound of the range (in degrees)
    /// @return             The angle value in degrees within the specified range
    Real inDegrees(const Real& aLowerBound, const Real& anUpperBound) const;

    /// @brief              Get the angle value in arcminutes
    ///
    /// @code{.cpp}
    ///                     Angle::Degrees(1.0).inArcminutes();
    /// @endcode
    ///
    /// @return             The angle value in arcminutes
    Real inArcminutes() const;

    /// @brief              Get the angle value in arcminutes, reduced to a specified range
    ///
    /// @code{.cpp}
    ///                     Angle::Arcminutes(100.0).inArcminutes(0.0, 60.0);
    /// @endcode
    ///
    /// @param              [in] aLowerBound A lower bound of the range (in arcminutes)
    /// @param              [in] anUpperBound An upper bound of the range (in arcminutes)
    /// @return             The angle value in arcminutes within the specified range
    Real inArcminutes(const Real& aLowerBound, const Real& anUpperBound) const;

    /// @brief              Get the angle value in arcseconds
    ///
    /// @code{.cpp}
    ///                     Angle::Degrees(1.0).inArcseconds();
    /// @endcode
    ///
    /// @return             The angle value in arcseconds
    Real inArcseconds() const;

    /// @brief              Get the angle value in arcseconds, reduced to a specified range
    ///
    /// @code{.cpp}
    ///                     Angle::Arcseconds(5000.0).inArcseconds(0.0, 3600.0);
    /// @endcode
    ///
    /// @param              [in] aLowerBound A lower bound of the range (in arcseconds)
    /// @param              [in] anUpperBound An upper bound of the range (in arcseconds)
    /// @return             The angle value in arcseconds within the specified range
    Real inArcseconds(const Real& aLowerBound, const Real& anUpperBound) const;

    /// @brief              Get the angle value in revolutions
    ///
    /// @code{.cpp}
    ///                     Angle::Degrees(360.0).inRevolutions();
    /// @endcode
    ///
    /// @return             The angle value in revolutions
    Real inRevolutions() const;

    /// @brief              Convert the angle to a string representation
    ///
    /// @code{.cpp}
    ///                     Angle::Degrees(90.0).toString();  // "90.0 [deg]"
    /// @endcode
    ///
    /// @param              [in] aPrecision (optional) A precision for the value
    /// @return             String representation of the angle
    String toString(const Integer& aPrecision = Integer::Undefined()) const;

    /// @brief              Construct an undefined angle
    ///
    /// @code{.cpp}
    ///                     Angle angle = Angle::Undefined();
    /// @endcode
    ///
    /// @return             An undefined angle
    static Angle Undefined();

    /// @brief              Construct a zero angle
    ///
    /// @code{.cpp}
    ///                     Angle angle = Angle::Zero();
    /// @endcode
    ///
    /// @return             A zero angle in radians
    static Angle Zero();

    /// @brief              Construct an angle of pi/2 radians (90 degrees)
    ///
    /// @code{.cpp}
    ///                     Angle angle = Angle::HalfPi();
    /// @endcode
    ///
    /// @return             A pi/2 radian angle
    static Angle HalfPi();

    /// @brief              Construct an angle of pi radians (180 degrees)
    ///
    /// @code{.cpp}
    ///                     Angle angle = Angle::Pi();
    /// @endcode
    ///
    /// @return             A pi radian angle
    static Angle Pi();

    /// @brief              Construct an angle of 2*pi radians (360 degrees)
    ///
    /// @code{.cpp}
    ///                     Angle angle = Angle::TwoPi();
    /// @endcode
    ///
    /// @return             A 2*pi radian angle
    static Angle TwoPi();

    /// @brief              Construct an angle from a value in radians
    ///
    /// @code{.cpp}
    ///                     Angle angle = Angle::Radians(3.14159);
    /// @endcode
    ///
    /// @param              [in] aValue A value in radians
    /// @return             An angle
    static Angle Radians(const Real& aValue);

    /// @brief              Construct an angle from a value in degrees
    ///
    /// @code{.cpp}
    ///                     Angle angle = Angle::Degrees(90.0);
    /// @endcode
    ///
    /// @param              [in] aValue A value in degrees
    /// @return             An angle
    static Angle Degrees(const Real& aValue);

    /// @brief              Construct an angle from a value in arcminutes
    ///
    /// @code{.cpp}
    ///                     Angle angle = Angle::Arcminutes(30.0);
    /// @endcode
    ///
    /// @param              [in] aValue A value in arcminutes
    /// @return             An angle
    static Angle Arcminutes(const Real& aValue);

    /// @brief              Construct an angle from a value in arcseconds
    ///
    /// @code{.cpp}
    ///                     Angle angle = Angle::Arcseconds(3600.0);
    /// @endcode
    ///
    /// @param              [in] aValue A value in arcseconds
    /// @return             An angle
    static Angle Arcseconds(const Real& aValue);

    /// @brief              Construct an angle from a value in revolutions
    ///
    /// @code{.cpp}
    ///                     Angle angle = Angle::Revolutions(0.5);
    /// @endcode
    ///
    /// @param              [in] aValue A value in revolutions
    /// @return             An angle
    static Angle Revolutions(const Real& aValue);

    /// @brief              Compute the angle between two 2D vectors
    ///
    /// @code{.cpp}
    ///                     Angle angle = Angle::Between({1.0, 0.0}, {0.0, 1.0});
    /// @endcode
    ///
    /// @param              [in] aFirstVector A first 2D vector
    /// @param              [in] aSecondVector A second 2D vector
    /// @return             The angle between the two vectors
    static Angle Between(const Vector2d& aFirstVector, const Vector2d& aSecondVector);

    /// @brief              Compute the angle between two 3D vectors
    ///
    /// @code{.cpp}
    ///                     Angle angle = Angle::Between({1.0, 0.0, 0.0}, {0.0, 1.0, 0.0});
    /// @endcode
    ///
    /// @param              [in] aFirstVector A first 3D vector
    /// @param              [in] aSecondVector A second 3D vector
    /// @return             The angle between the two vectors
    static Angle Between(const Vector3d& aFirstVector, const Vector3d& aSecondVector);

    /// @brief              Parse an angle from a string representation
    ///
    /// @code{.cpp}
    ///                     Angle angle = Angle::Parse("90.0 [deg]");
    /// @endcode
    ///
    /// @param              [in] aString A string to parse
    /// @return             An angle
    static Angle Parse(const String& aString);

    /// @brief              Get the string name of an angle unit
    ///
    /// @code{.cpp}
    ///                     String name = Angle::StringFromUnit(Angle::Unit::Degree);
    /// @endcode
    ///
    /// @param              [in] aUnit An angle unit
    /// @return             The string name of the unit
    static String StringFromUnit(const Angle::Unit& aUnit);

    /// @brief              Get the symbol of an angle unit
    ///
    /// @code{.cpp}
    ///                     String symbol = Angle::SymbolFromUnit(Angle::Unit::Degree);
    /// @endcode
    ///
    /// @param              [in] aUnit An angle unit
    /// @return             The symbol of the unit (e.g., "deg", "rad")
    static String SymbolFromUnit(const Angle::Unit& aUnit);

   private:
    Real value_;
    Angle::Unit unit_;

    static Real SIRatio(const Angle::Unit& aUnit);

    static Real ReduceRange(const Real& aValue, const Real& aRangeLowerBound, const Real& aRangeUpperBound);
};

}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
