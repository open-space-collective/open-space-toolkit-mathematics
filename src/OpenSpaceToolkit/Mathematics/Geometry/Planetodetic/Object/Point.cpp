/// Apache License 2.0

#include <cmath>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/Planetodetic/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

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

Point::Point(const Angle& aLatitude, const Angle& aLongitude)
    : Object(),
      latitude_(aLatitude),
      longitude_(aLongitude)
{
    // Validate latitude is within valid range [-90.0, 90.0]
    if (latitude_.isDefined())
    {
        const double latDegrees = latitude_.inDegrees();
        if (latDegrees < -90.0 || latDegrees > 90.0)
        {
            throw ostk::core::error::runtime::Wrong("Latitude", latDegrees);
        }
    }

    // Normalize longitude to [-180.0, 180.0) range
    if (longitude_.isDefined())
    {
        longitude_ = Angle::Degrees(longitude_.inDegrees(-180.0, 180.0));
    }
}

Point* Point::clone() const
{
    return new Point(*this);
}

bool Point::operator==(const Point& aPoint) const
{
    if ((!this->isDefined()) || (!aPoint.isDefined()))
    {
        return false;
    }

    // Deal with singularities at the poles
    if (latitude_.inDegrees() == 90.0 and aPoint.latitude_.inDegrees() == 90.0)
    {
        return true;
    }

    if (latitude_.inDegrees() == -90.0 and aPoint.latitude_.inDegrees() == -90.0)
    {
        return true;
    }

    return (latitude_ == aPoint.latitude_) && (longitude_ == aPoint.longitude_);
}

bool Point::operator!=(const Point& aPoint) const
{
    return !((*this) == aPoint);
}

bool Point::isDefined() const
{
    return latitude_.isDefined() && longitude_.isDefined();
}

Angle Point::getLatitude() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    return latitude_;
}

Angle Point::getLongitude() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    return longitude_;
}

bool Point::isCollinear(const Point& aPoint1, const Point& aPoint2) const
{
    using ostk::mathematics::object::Vector3d;

    if (!this->isDefined() || !aPoint1.isDefined() || !aPoint2.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    const Vector3d a = this->toVector();
    const Vector3d b = aPoint1.toVector();
    const Vector3d c = aPoint2.toVector();

    // Normal of plane through A and B
    const Vector3d n = a.cross(b);

    // Dot product of normal with C
    const double dotNC = n.dot(c);

    return std::abs(dotNC) < 1e-10;
}

String Point::toString(const Object::Format& aFormat, const Integer& aPrecision) const
{
    using ostk::core::type::String;

    switch (aFormat)
    {
        case Object::Format::Standard:
        {
            if (aPrecision.isDefined())
            {
                return String::Format("[{}, {}]", latitude_.toString(aPrecision), longitude_.toString(aPrecision));
            }

            return String::Format("[{}, {}]", latitude_.toString(), longitude_.toString());
        }

        default:
            throw ostk::core::error::runtime::Wrong("Format");
    }

    return String::Empty();
}

void Point::print(std::ostream& anOutputStream, bool displayDecorators) const
{
    displayDecorators ? ostk::core::utils::Print::Header(anOutputStream, "Planetodetic Point") : void();

    ostk::core::utils::Print::Line(anOutputStream)
        << "Latitude:" << (latitude_.isDefined() ? latitude_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Longitude:" << (longitude_.isDefined() ? longitude_.toString() : "Undefined");

    displayDecorators ? ostk::core::utils::Print::Footer(anOutputStream) : void();
}

Point Point::Undefined()
{
    return {Angle::Undefined(), Angle::Undefined()};
}

Point Point::Origin()
{
    return {Angle::Zero(), Angle::Zero()};
}

Point Point::NorthPole()
{
    return {Angle::Degrees(90.0), Angle::Zero()};
}

Point Point::SouthPole()
{
    return {Angle::Degrees(-90.0), Angle::Zero()};
}

ostk::mathematics::object::Vector3d Point::toVector() const
{
    using ostk::mathematics::object::Vector3d;

    const double lat = latitude_.inRadians();
    const double lon = longitude_.inRadians();

    return Vector3d {std::cos(lat) * std::cos(lon), std::cos(lat) * std::sin(lon), std::sin(lat)};
}

}  // namespace object
}  // namespace planetodetic
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk
