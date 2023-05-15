/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_Angle__
#define __OpenSpaceToolkit_Mathematics_Geometry_Angle__

#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>

namespace ostk
{
namespace math
{
namespace geom
{

using ostk::core::types::Integer;
using ostk::core::types::Real;
using ostk::core::types::String;

using ostk::math::obj::Vector2d;
using ostk::math::obj::Vector3d;

/// @brief                      Angle
///
///                             In plane geometry, an angle is the figure formed by two rays, called the sides of the
///                             angle, sharing a common endpoint, called the vertex of the angle.
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

    bool operator==(const Angle& anAngle) const;

    bool operator!=(const Angle& anAngle) const;

    Angle operator+(const Angle& anAngle) const;

    Angle operator-(const Angle& anAngle) const;

    Angle operator*(const Real& aReal) const;

    Angle operator/(const Real& aReal) const;

    Angle& operator+=(const Angle& anAngle);

    Angle& operator-=(const Angle& anAngle);

    Angle& operator*=(const Real& aReal);

    Angle& operator/=(const Real& aReal);

    friend Angle operator*(const Real& aReal, const Angle& anAngle);

    Angle operator+() const;

    Angle operator-() const;

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Angle& anAngle);

    bool isDefined() const;

    bool isZero() const;

    Angle::Unit getUnit() const;

    Real in(const Angle::Unit& aUnit) const;

    Real inRadians() const;

    Real inRadians(const Real& aLowerBound, const Real& anUpperBound) const;

    Real inDegrees() const;

    Real inDegrees(const Real& aLowerBound, const Real& anUpperBound) const;

    Real inArcminutes() const;

    Real inArcminutes(const Real& aLowerBound, const Real& anUpperBound) const;

    Real inArcseconds() const;

    Real inArcseconds(const Real& aLowerBound, const Real& anUpperBound) const;

    Real inRevolutions() const;

    String toString(const Integer& aPrecision = Integer::Undefined()) const;

    static Angle Undefined();

    static Angle Zero();

    static Angle HalfPi();

    static Angle Pi();

    static Angle TwoPi();

    static Angle Radians(const Real& aValue);

    static Angle Degrees(const Real& aValue);

    static Angle Arcminutes(const Real& aValue);

    static Angle Arcseconds(const Real& aValue);

    static Angle Revolutions(const Real& aValue);

    static Angle Between(const Vector2d& aFirstVector, const Vector2d& aSecondVector);

    static Angle Between(const Vector3d& aFirstVector, const Vector3d& aSecondVector);

    static Angle Parse(const String& aString);

    static String StringFromUnit(const Angle::Unit& aUnit);

    static String SymbolFromUnit(const Angle::Unit& aUnit);

   private:
    Real value_;
    Angle::Unit unit_;

    static Real SIRatio(const Angle::Unit& aUnit);

    static Real ReduceRange(const Real& aValue, const Real& aRangeLowerBound, const Real& aRangeUpperBound);
};

}  // namespace geom
}  // namespace math
}  // namespace ostk

#endif
