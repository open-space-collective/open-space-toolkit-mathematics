/// Apache License 2.0

#include <cmath>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/Planetodetic/Object/Spheroid.hpp>

namespace ostk
{
namespace mathematics
{
namespace geometry
{
namespace planetodetic
{
namespace object
{

Spheroid::Spheroid(const Real& anEquatorialRadius, const Real& aFlattening)
    : Object(),
      equatorialRadius_(anEquatorialRadius),
      flattening_(aFlattening)
{
    if (anEquatorialRadius.isDefined() && anEquatorialRadius <= 0.0)
    {
        throw ostk::core::error::runtime::Wrong("Equatorial radius", anEquatorialRadius.toString());
    }

    if (aFlattening.isDefined() && aFlattening >= 1.0)
    {
        throw ostk::core::error::runtime::Wrong("Flattening", aFlattening.toString());
    }
}

Spheroid* Spheroid::clone() const
{
    return new Spheroid(*this);
}

bool Spheroid::operator==(const Spheroid& aSpheroid) const
{
    if ((!this->isDefined()) || (!aSpheroid.isDefined()))
    {
        return false;
    }

    return (equatorialRadius_ == aSpheroid.equatorialRadius_) && (flattening_ == aSpheroid.flattening_);
}

bool Spheroid::operator!=(const Spheroid& aSpheroid) const
{
    return !((*this) == aSpheroid);
}

bool Spheroid::isDefined() const
{
    return equatorialRadius_.isDefined() && flattening_.isDefined() && (equatorialRadius_ > 0.0);
}

Real Spheroid::getEquatorialRadius() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Spheroid");
    }

    return equatorialRadius_;
}

Real Spheroid::getPolarRadius() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Spheroid");
    }

    return equatorialRadius_ * (1.0 - flattening_);
}

Real Spheroid::getFlattening() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Spheroid");
    }

    return flattening_;
}

Real Spheroid::getEccentricity() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Spheroid");
    }

    return std::sqrt(2.0 * flattening_ - flattening_ * flattening_);
}

bool Spheroid::isOblate() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Spheroid");
    }

    return flattening_ > 0.0;
}

bool Spheroid::isProlate() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Spheroid");
    }

    return flattening_ < 0.0;
}

bool Spheroid::isSphere() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Spheroid");
    }

    return flattening_ == 0.0;
}

String Spheroid::toString(const Object::Format& aFormat, const Integer& aPrecision) const
{
    using ostk::core::type::String;

    switch (aFormat)
    {
        case Object::Format::Standard:
        {
            if (aPrecision.isDefined())
            {
                return String::Format(
                    "[{}, {}]", equatorialRadius_.toString(aPrecision), flattening_.toString(aPrecision)
                );
            }

            return String::Format("[{}, {}]", equatorialRadius_.toString(), flattening_.toString());
        }

        default:
            throw ostk::core::error::runtime::Wrong("Format");
    }

    return String::Empty();
}

void Spheroid::print(std::ostream& anOutputStream, bool displayDecorators) const
{
    displayDecorators ? ostk::core::utils::Print::Header(anOutputStream, "Spheroid") : void();

    ostk::core::utils::Print::Line(anOutputStream)
        << "Equatorial radius:" << (equatorialRadius_.isDefined() ? equatorialRadius_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Flattening:" << (flattening_.isDefined() ? flattening_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Polar radius:" << (this->isDefined() ? this->getPolarRadius().toString() : "Undefined");

    displayDecorators ? ostk::core::utils::Print::Footer(anOutputStream) : void();
}

Spheroid Spheroid::FromEquatorialRadiusAndFlattening(const Real& anEquatorialRadius, const Real& aFlattening)
{
    return {anEquatorialRadius, aFlattening};
}

Spheroid Spheroid::Undefined()
{
    return {Real::Undefined(), Real::Undefined()};
}

Spheroid Spheroid::Sphere(const Real& aRadius)
{
    return {aRadius, 0.0};
}

}  // namespace object
}  // namespace planetodetic
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk
