/// Apache License 2.0

#include <cmath>
#include <limits>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Utility.hpp>

namespace ostk
{
namespace mathematics
{
namespace geometry
{
namespace d2
{
namespace object
{

using ostk::mathematics::utility::DoubleToString;

Point::Point(double aFirstCoordinate, double aSecondCoordinate)
    : Object(),
      x_(aFirstCoordinate),
      y_(aSecondCoordinate)
{
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

    return (x_ == aPoint.x_) && (y_ == aPoint.y_);
}

bool Point::operator!=(const Point& aPoint) const
{
    return !((*this) == aPoint);
}

Point Point::operator+(const Vector2d& aVector) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    if (!aVector.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Vector");
    }

    return {x_ + aVector.x(), y_ + aVector.y()};
}

Point Point::operator-(const Vector2d& aVector) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    if (!aVector.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Vector");
    }

    return {x_ - aVector.x(), y_ - aVector.y()};
}

Vector2d Point::operator-(const Point& aPoint) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    if (!aPoint.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    return {x_ - aPoint.x_, y_ - aPoint.y_};
}

bool Point::isDefined() const
{
    return !std::isnan(x_) && !std::isnan(y_);
}

bool Point::isNear(const Point& aPoint, double aTolerance) const
{
    if (std::isnan(aTolerance))
    {
        throw ostk::core::error::runtime::Undefined("Tolerance");
    }

    return this->distanceTo(aPoint) <= aTolerance;
}

const double& Point::x() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    return x_;
}

const double& Point::y() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    return y_;
}

Vector2d Point::asVector() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    return {x_, y_};
}

double Point::distanceTo(const Point& aPoint) const
{
    if (!aPoint.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    return ((*this) - aPoint).norm();
}

String Point::toString(const Object::Format& aFormat, int aPrecision) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    switch (aFormat)
    {
        case Object::Format::Standard:
            return String::Format("[{}, {}]", DoubleToString(x_, aPrecision), DoubleToString(y_, aPrecision));

        case Object::Format::WKT:
            return String::Format("POINT({} {})", DoubleToString(x_, aPrecision), DoubleToString(y_, aPrecision));

        default:
            throw ostk::core::error::runtime::Wrong("Format");
            break;
    }

    return String::Empty();
}

void Point::print(std::ostream& anOutputStream, bool displayDecorators) const
{
    displayDecorators ? ostk::core::utils::Print::Header(anOutputStream, "Point") : void();

    ostk::core::utils::Print::Line(anOutputStream) << "X:" << DoubleToString(x_);
    ostk::core::utils::Print::Line(anOutputStream) << "Y:" << DoubleToString(y_);

    displayDecorators ? ostk::core::utils::Print::Footer(anOutputStream) : void();
}

void Point::applyTransformation(const Transformation& aTransformation)
{
    if (!aTransformation.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Transformation");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    (*this) = aTransformation.applyTo(*this);
}

Point Point::Undefined()
{
    return {std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN()};
}

Point Point::Origin()
{
    return {0.0, 0.0};
}

Point Point::Vector(const Vector2d& aVector)
{
    return {aVector.x(), aVector.y()};
}

}  // namespace object
}  // namespace d2
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk
