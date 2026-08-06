/// Apache License 2.0

#include <cmath>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/Planetodetic/Object/Ellipsoid.hpp>

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

Ellipsoid::Ellipsoid(const Real& anEquatorialRadiusA, const Real& anEquatorialRadiusB, const Real& aPolarRadius)
    : Object(),
      equatorialRadiusA_(anEquatorialRadiusA),
      equatorialRadiusB_(anEquatorialRadiusB),
      polarRadius_(aPolarRadius)
{
    if (anEquatorialRadiusA.isDefined() && anEquatorialRadiusA <= 0.0)
    {
        throw ostk::core::error::runtime::Wrong("Equatorial radius A", anEquatorialRadiusA.toString());
    }

    if (anEquatorialRadiusB.isDefined() && anEquatorialRadiusB <= 0.0)
    {
        throw ostk::core::error::runtime::Wrong("Equatorial radius B", anEquatorialRadiusB.toString());
    }

    if (aPolarRadius.isDefined() && aPolarRadius <= 0.0)
    {
        throw ostk::core::error::runtime::Wrong("Polar radius", aPolarRadius.toString());
    }
}

Ellipsoid* Ellipsoid::clone() const
{
    return new Ellipsoid(*this);
}

bool Ellipsoid::operator==(const Ellipsoid& anEllipsoid) const
{
    if ((!this->isDefined()) || (!anEllipsoid.isDefined()))
    {
        return false;
    }

    return (equatorialRadiusA_ == anEllipsoid.equatorialRadiusA_) &&
           (equatorialRadiusB_ == anEllipsoid.equatorialRadiusB_) && (polarRadius_ == anEllipsoid.polarRadius_);
}

bool Ellipsoid::operator!=(const Ellipsoid& anEllipsoid) const
{
    return !((*this) == anEllipsoid);
}

bool Ellipsoid::isDefined() const
{
    return equatorialRadiusA_.isDefined() && equatorialRadiusB_.isDefined() && polarRadius_.isDefined();
}

Real Ellipsoid::getEquatorialRadiusA() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    return equatorialRadiusA_;
}

Real Ellipsoid::getEquatorialRadiusB() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    return equatorialRadiusB_;
}

Real Ellipsoid::getPolarRadius() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    return polarRadius_;
}

String Ellipsoid::toString(const Object::Format& aFormat, const Integer& aPrecision) const
{
    switch (aFormat)
    {
        case Object::Format::Standard:
        {
            if (aPrecision.isDefined())
            {
                return String::Format(
                    "[{}, {}, {}]",
                    equatorialRadiusA_.toString(aPrecision),
                    equatorialRadiusB_.toString(aPrecision),
                    polarRadius_.toString(aPrecision)
                );
            }

            return String::Format(
                "[{}, {}, {}]", equatorialRadiusA_.toString(), equatorialRadiusB_.toString(), polarRadius_.toString()
            );
        }

        default:
            throw ostk::core::error::runtime::Wrong("Format");
    }
}

void Ellipsoid::print(std::ostream& anOutputStream, bool displayDecorators) const
{
    displayDecorators ? ostk::core::utils::Print::Header(anOutputStream, "Ellipsoid") : void();

    ostk::core::utils::Print::Line(anOutputStream)
        << "Equatorial radius A:" << (equatorialRadiusA_.isDefined() ? equatorialRadiusA_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Equatorial radius B:" << (equatorialRadiusB_.isDefined() ? equatorialRadiusB_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Polar radius:" << (polarRadius_.isDefined() ? polarRadius_.toString() : "Undefined");

    displayDecorators ? ostk::core::utils::Print::Footer(anOutputStream) : void();
}

Ellipsoid Ellipsoid::Undefined()
{
    return {Real::Undefined(), Real::Undefined(), Real::Undefined()};
}

Ellipsoid Ellipsoid::Sphere(const Real& aRadius)
{
    return {aRadius, aRadius, aRadius};
}

Ellipsoid Ellipsoid::Spheroid(const Real& anEquatorialRadius, const Real& aFlattening, const Real& aPolarRadius)
{
    if (anEquatorialRadius.isDefined() && aFlattening.isDefined() && aPolarRadius.isDefined())
    {
        throw ostk::core::error::RuntimeError("Only 2 arguments are allowed.");
    }

    if (aFlattening.isDefined() && aFlattening >= 1.0)
    {
        throw ostk::core::error::runtime::Wrong("Flattening", aFlattening.toString());
    }

    if (anEquatorialRadius.isDefined() && aFlattening.isDefined())
    {
        return {anEquatorialRadius, anEquatorialRadius, anEquatorialRadius * (1.0 - aFlattening)};
    }

    if (anEquatorialRadius.isDefined() && aPolarRadius.isDefined())
    {
        return {anEquatorialRadius, anEquatorialRadius, aPolarRadius};
    }

    if (aPolarRadius.isDefined() && aFlattening.isDefined())
    {
        const Real equatorialRadius = aPolarRadius / (1.0 - aFlattening);
        return {equatorialRadius, equatorialRadius, aPolarRadius};
    }

    throw ostk::core::error::RuntimeError("Insufficient arguments provided.");
}

Ellipsoid Ellipsoid::WGS84()
{
    return Ellipsoid::Spheroid(6378137.0, 1.0 / 298.257223563, Real::Undefined());
}

}  // namespace object
}  // namespace planetodetic
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk
