/// Apache License 2.0

#include <cmath>
#include <limits>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/Angle.hpp>
#include <OpenSpaceToolkit/Mathematics/Utility.hpp>

namespace ostk
{
namespace mathematics
{
namespace geometry
{

using ostk::mathematics::utility::DoubleToString;

Angle::Angle(double aValue, const Angle::Unit& aUnit)
    : value_(aValue),
      unit_(aUnit)
{
}

bool Angle::operator==(const Angle& anAngle) const
{
    if ((unit_ == Angle::Unit::Undefined) || (anAngle.unit_ == Angle::Unit::Undefined))
    {
        return false;
    }

    switch (unit_)
    {
        case Angle::Unit::Radian:
            return value_ ==
                   Angle::ReduceRange(
                       ((anAngle.unit_ == Angle::Unit::Radian) ? anAngle.value_ : anAngle.in(Angle::Unit::Radian)),
                       value_,
                       value_ + 2.0 * M_PI
                   );

        case Angle::Unit::Degree:
            return value_ ==
                   Angle::ReduceRange(
                       ((anAngle.unit_ == Angle::Unit::Degree) ? anAngle.value_ : anAngle.in(Angle::Unit::Degree)),
                       value_,
                       value_ + 360.0
                   );

        case Angle::Unit::Arcminute:
            return value_ == Angle::ReduceRange(
                                 ((anAngle.unit_ == Angle::Unit::Arcminute) ? anAngle.value_
                                                                            : anAngle.in(Angle::Unit::Arcminute)),
                                 value_,
                                 value_ + 21600.0
                             );

        case Angle::Unit::Arcsecond:
            return value_ == Angle::ReduceRange(
                                 ((anAngle.unit_ == Angle::Unit::Arcsecond) ? anAngle.value_
                                                                            : anAngle.in(Angle::Unit::Arcsecond)),
                                 value_,
                                 value_ + 1296000.0
                             );

        case Angle::Unit::Revolution:
            return value_ == Angle::ReduceRange(
                                 ((anAngle.unit_ == Angle::Unit::Revolution) ? anAngle.value_
                                                                             : anAngle.in(Angle::Unit::Revolution)),
                                 value_,
                                 value_ + 1.0
                             );

        default:
            throw ostk::core::error::runtime::Wrong("Unit");
            break;
    }

    return false;
}

bool Angle::operator!=(const Angle& anAngle) const
{
    return !((*this) == anAngle);
}

Angle Angle::operator+(const Angle& anAngle) const
{
    if ((unit_ == Angle::Unit::Undefined) || (anAngle.unit_ == Angle::Unit::Undefined))
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    return Angle((value_ + ((unit_ == anAngle.unit_) ? anAngle.value_ : anAngle.in(unit_))), unit_);
}

Angle Angle::operator-(const Angle& anAngle) const
{
    if ((unit_ == Angle::Unit::Undefined) || (anAngle.unit_ == Angle::Unit::Undefined))
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    return Angle((value_ - ((unit_ == anAngle.unit_) ? anAngle.value_ : anAngle.in(unit_))), unit_);
}

Angle Angle::operator*(double aReal) const
{
    if (unit_ == Angle::Unit::Undefined)
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    if (std::isnan(aReal))
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    return Angle((value_ * aReal), unit_);
}

Angle Angle::operator/(double aReal) const
{
    if (unit_ == Angle::Unit::Undefined)
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    if (std::isnan(aReal))
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    if (aReal == 0.0)
    {
        throw ostk::core::error::RuntimeError("Cannot divide by zero.");
    }

    return Angle((value_ / aReal), unit_);
}

Angle& Angle::operator+=(const Angle& anAngle)
{
    if ((unit_ == Angle::Unit::Undefined) || (anAngle.unit_ == Angle::Unit::Undefined))
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    value_ += ((unit_ == anAngle.unit_) ? anAngle.value_ : anAngle.in(unit_));

    return *this;
}

Angle& Angle::operator-=(const Angle& anAngle)
{
    if ((unit_ == Angle::Unit::Undefined) || (anAngle.unit_ == Angle::Unit::Undefined))
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    value_ -= ((unit_ == anAngle.unit_) ? anAngle.value_ : anAngle.in(unit_));

    return *this;
}

Angle& Angle::operator*=(double aReal)
{
    if (unit_ == Angle::Unit::Undefined)
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    if (std::isnan(aReal))
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    value_ *= aReal;

    return *this;
}

Angle& Angle::operator/=(double aReal)
{
    if (unit_ == Angle::Unit::Undefined)
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    if (std::isnan(aReal))
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    if (aReal == 0.0)
    {
        throw ostk::core::error::RuntimeError("Cannot divide by zero.");
    }

    value_ /= aReal;

    return *this;
}

Angle operator*(double aReal, const Angle& anAngle)
{
    if (std::isnan(aReal))
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    if (anAngle.unit_ == Angle::Unit::Undefined)
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    return Angle((anAngle.value_ * aReal), anAngle.unit_);
}

Angle Angle::operator+() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    return Angle(value_, unit_);
}

Angle Angle::operator-() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    return Angle(-value_, unit_);
}

std::ostream& operator<<(std::ostream& anOutputStream, const Angle& anAngle)
{
    ostk::core::utils::Print::Header(anOutputStream, "Angle");

    ostk::core::utils::Print::Line(anOutputStream) << "Value:" << anAngle.value_;
    ostk::core::utils::Print::Line(anOutputStream) << "Unit:" << Angle::StringFromUnit(anAngle.unit_);

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool Angle::isDefined() const
{
    return !std::isnan(value_) && (unit_ != Angle::Unit::Undefined);
}

bool Angle::isZero() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    return value_ == 0.0;
}

bool Angle::isNegative() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    return value_ < 0.0;
}

bool Angle::isNear(const Angle& anAngle, const Angle& aTolerance) const
{
    if ((!this->isDefined()) || (!anAngle.isDefined()))
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    if (!aTolerance.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Tolerance");
    }

    const double normalizedAngle_1 = Angle::ReduceRange(this->inDegrees(), 0.0, 360.0);
    const double normalizedAngle_2 = Angle::ReduceRange(anAngle.inDegrees(), 0.0, 360.0);

    const double diff = std::abs(normalizedAngle_2 - normalizedAngle_1);
    const double tolerance = std::abs(aTolerance.inDegrees());

    return (diff <= tolerance) || (360.0 - diff <= tolerance);
}

Angle::Unit Angle::getUnit() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    return unit_;
}

double Angle::in(const Angle::Unit& aUnit) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    if (unit_ == aUnit)
    {
        return value_;
    }

    return value_ * Angle::SIRatio(unit_) / Angle::SIRatio(aUnit);
}

double Angle::inRadians() const
{
    return this->in(Angle::Unit::Radian);
}

double Angle::inRadians(double aLowerBound, double anUpperBound) const
{
    if (std::isnan(aLowerBound))
    {
        throw ostk::core::error::runtime::Undefined("Lower bound");
    }

    if (std::isnan(anUpperBound))
    {
        throw ostk::core::error::runtime::Undefined("Upper bound");
    }

    if ((anUpperBound - aLowerBound) != 2.0 * M_PI)
    {
        throw ostk::core::error::runtime::Undefined("Range span is not [2π].");
    }

    return Angle::ReduceRange(this->in(Angle::Unit::Radian), aLowerBound, anUpperBound);
}

double Angle::inDegrees() const
{
    return this->in(Angle::Unit::Degree);
}

double Angle::inDegrees(double aLowerBound, double anUpperBound) const
{
    if (std::isnan(aLowerBound))
    {
        throw ostk::core::error::runtime::Undefined("Lower bound");
    }

    if (std::isnan(anUpperBound))
    {
        throw ostk::core::error::runtime::Undefined("Upper bound");
    }

    if ((anUpperBound - aLowerBound) != 360.0)
    {
        throw ostk::core::error::runtime::Undefined("Range span is not [360].");
    }

    return Angle::ReduceRange(this->in(Angle::Unit::Degree), aLowerBound, anUpperBound);
}

double Angle::inArcminutes() const
{
    return this->in(Angle::Unit::Arcminute);
}

double Angle::inArcminutes(double aLowerBound, double anUpperBound) const
{
    if (std::isnan(aLowerBound))
    {
        throw ostk::core::error::runtime::Undefined("Lower bound");
    }

    if (std::isnan(anUpperBound))
    {
        throw ostk::core::error::runtime::Undefined("Upper bound");
    }

    if ((anUpperBound - aLowerBound) != 21600.0)
    {
        throw ostk::core::error::runtime::Undefined("Range span is not [21600].");
    }

    return Angle::ReduceRange(this->in(Angle::Unit::Arcminute), aLowerBound, anUpperBound);
}

double Angle::inArcseconds() const
{
    return this->in(Angle::Unit::Arcsecond);
}

double Angle::inArcseconds(double aLowerBound, double anUpperBound) const
{
    if (std::isnan(aLowerBound))
    {
        throw ostk::core::error::runtime::Undefined("Lower bound");
    }

    if (std::isnan(anUpperBound))
    {
        throw ostk::core::error::runtime::Undefined("Upper bound");
    }

    if ((anUpperBound - aLowerBound) != 1296000.0)
    {
        throw ostk::core::error::runtime::Undefined("Range span is not [1296000].");
    }

    return Angle::ReduceRange(this->in(Angle::Unit::Arcsecond), aLowerBound, anUpperBound);
}

double Angle::inRevolutions() const
{
    return this->in(Angle::Unit::Revolution);
}

String Angle::toString(int aPrecision) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    return DoubleToString(value_, aPrecision) + " [" + Angle::SymbolFromUnit(unit_) + "]";
}

Angle Angle::Undefined()
{
    return {std::numeric_limits<double>::quiet_NaN(), Angle::Unit::Undefined};
}

Angle Angle::Zero()
{
    return {0.0, Angle::Unit::Radian};
}

Angle Angle::HalfPi()
{
    return {M_PI / 2.0, Angle::Unit::Radian};
}

Angle Angle::Pi()
{
    return {M_PI, Angle::Unit::Radian};
}

Angle Angle::TwoPi()
{
    return {M_PI * 2.0, Angle::Unit::Radian};
}

Angle Angle::Radians(double aValue)
{
    return {aValue, Angle::Unit::Radian};
}

Angle Angle::Degrees(double aValue)
{
    return {aValue, Angle::Unit::Degree};
}

Angle Angle::Arcminutes(double aValue)
{
    return {aValue, Angle::Unit::Arcminute};
}

Angle Angle::Arcseconds(double aValue)
{
    return {aValue, Angle::Unit::Arcsecond};
}

Angle Angle::Revolutions(double aValue)
{
    return {aValue, Angle::Unit::Revolution};
}

// Angle                            Angle::Parse                               (   const   String& aString )
// {

// }

Angle Angle::Between(const Vector2d& aFirstVector, const Vector2d& aSecondVector)
{
    if ((!aFirstVector.isDefined()) || (!aSecondVector.isDefined()))
    {
        throw ostk::core::error::runtime::Undefined("Vector");
    }

    if ((aFirstVector.squaredNorm() < 1e-15) || (aSecondVector.squaredNorm() < 1e-15))
    {
        throw ostk::core::error::RuntimeError("Vector norm is too small.");
    }

    if (aFirstVector == aSecondVector)
    {
        return Angle::Zero();
    }

    if (aFirstVector == -aSecondVector)
    {
        return Angle::Pi();
    }

    const double dotProduct = aFirstVector.normalized().dot(aSecondVector.normalized());

    if (dotProduct >= 1.0)
    {
        return Angle::Zero();
    }

    if (dotProduct <= -1.0)
    {
        return Angle::Pi();
    }

    return Angle::Radians(std::acos(dotProduct));
}

Angle Angle::Between(const Vector3d& aFirstVector, const Vector3d& aSecondVector)
{
    if ((!aFirstVector.isDefined()) || (!aSecondVector.isDefined()))
    {
        throw ostk::core::error::runtime::Undefined("Vector");
    }

    if ((aFirstVector.squaredNorm() < 1e-15) || (aSecondVector.squaredNorm() < 1e-15))
    {
        throw ostk::core::error::RuntimeError("Vector norm is too small.");
    }

    if (aFirstVector == aSecondVector)
    {
        return Angle::Zero();
    }

    if (aFirstVector == -aSecondVector)
    {
        return Angle::Pi();
    }

    const double dotProduct = aFirstVector.normalized().dot(aSecondVector.normalized());

    if (dotProduct >= 1.0)
    {
        return Angle::Zero();
    }

    if (dotProduct <= -1.0)
    {
        return Angle::Pi();
    }

    return Angle::Radians(std::acos(dotProduct));
}

String Angle::StringFromUnit(const Angle::Unit& aUnit)
{
    switch (aUnit)
    {
        case Angle::Unit::Undefined:
            return "Undefined";

        case Angle::Unit::Radian:
            return "Radian";

        case Angle::Unit::Degree:
            return "Degree";

        case Angle::Unit::Arcminute:
            return "Arcminute";

        case Angle::Unit::Arcsecond:
            return "Arcsecond";

        case Angle::Unit::Revolution:
            return "Revolution";

        default:
            throw ostk::core::error::runtime::Wrong("Unit");
            break;
    }

    return String::Empty();
}

String Angle::SymbolFromUnit(const Angle::Unit& aUnit)
{
    switch (aUnit)
    {
        case Angle::Unit::Radian:
            return "rad";

        case Angle::Unit::Degree:
            return "deg";

        case Angle::Unit::Arcminute:
            return "amin";

        case Angle::Unit::Arcsecond:
            return "asec";

        case Angle::Unit::Revolution:
            return "rev";

        default:
            throw ostk::core::error::runtime::Wrong("Unit");
            break;
    }

    return String::Empty();
}

double Angle::SIRatio(const Angle::Unit& aUnit)
{
    switch (aUnit)
    {
        case Angle::Unit::Radian:
            return 1.0;

        case Angle::Unit::Degree:
            return M_PI / 180.0;

        case Angle::Unit::Arcminute:
            return M_PI / 10800.0;

        case Angle::Unit::Arcsecond:
            return M_PI / 648000.0;

        case Angle::Unit::Revolution:
            return 2.0 * M_PI;

        default:
            throw ostk::core::error::runtime::Wrong("Unit");
            break;
    }

    return std::numeric_limits<double>::quiet_NaN();
}

double Angle::ReduceRange(double aValue, double aRangeLowerBound, double aRangeUpperBound)
{
    if ((aValue >= aRangeLowerBound) && (aValue < aRangeUpperBound))  // Value already in range
    {
        return aValue;
    }

    double value = aValue;

    const double range = aRangeUpperBound - aRangeLowerBound;

    while (value < aRangeLowerBound
    )  // [TBM] This is a STUPID implementation: just used as a logic placeholder... should be improved ASAP
    {
        value += range;
    }

    while (value >= aRangeUpperBound
    )  // [TBM] This is a STUPID implementation: just used as a logic placeholder... should be improved ASAP
    {
        value -= range;
    }

    return value;
}

}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk
