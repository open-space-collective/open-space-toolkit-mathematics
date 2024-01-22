/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Line.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/PointSet.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Transformation.hpp>

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

Line::Line(const Point& anOrigin, const Vector2d& aDirection)
    : Object(),
      origin_(anOrigin),
      direction_(aDirection)
{
    if (direction_.isDefined() && (direction_.squaredNorm() != 1.0))
    {
        if (direction_.squaredNorm() == 0.0)
        {
            throw ostk::core::error::runtime::Wrong("Direction");
        }

        direction_ = direction_.normalized();
    }
}

Line* Line::clone() const
{
    return new Line(*this);
}

bool Line::operator==(const Line& aLine) const
{
    if ((!this->isDefined()) || (!aLine.isDefined()))
    {
        return false;
    }

    if ((direction_ == aLine.direction_) || (direction_ == -aLine.direction_))
    {
        return this->contains(aLine.origin_);
    }

    return false;
}

bool Line::operator!=(const Line& aLine) const
{
    return !((*this) == aLine);
}

bool Line::isDefined() const
{
    return origin_.isDefined() && direction_.isDefined();
}

bool Line::intersects(const Point& aPoint) const
{
    return this->contains(aPoint);
}

bool Line::contains(const Point& aPoint) const
{
    if (!aPoint.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Line");
    }

    if (aPoint == origin_)
    {
        return true;
    }

    const Point p_1 = origin_;
    const Point p_2 = origin_ + direction_;

    if (p_2.x() == p_1.x())
    {
        return aPoint.x() == p_1.x();
    }

    const Real m = (p_2.y() - p_1.y()) / (p_2.x() - p_1.x());

    return aPoint.y() == m * (aPoint.x() - p_1.x()) + p_1.y();
}

bool Line::contains(const PointSet& aPointSet) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Line");
    }

    if (aPointSet.isEmpty())
    {
        throw ostk::core::error::runtime::Undefined("Point Set");
    }

    for (auto& point : aPointSet)
    {
        if (!this->contains(point))
        {
            return false;
        }
    }

    return true;
}

Point Line::getOrigin() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Line");
    }

    return origin_;
}

Vector2d Line::getDirection() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Line");
    }

    return direction_;
}

Real Line::distanceTo(const Point& aPoint) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Line");
    }

    // https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line#Vector_formulation

    const Point p = aPoint;
    const Point a = origin_;
    const Vector2d n = direction_;

    return ((p - a) - ((p - a).dot(n)) * n).norm();
}

String Line::toString(const Object::Format& aFormat, const Integer& aPrecision) const
{
    switch (aFormat)
    {
        case Object::Format::Standard:
            return String::Format(
                "[{} -> {}]",
                origin_.toString(Object::Format::Standard, aPrecision),
                Point::Vector(direction_).toString(Object::Format::Standard, aPrecision)
            );

        default:
            throw ostk::core::error::runtime::Wrong("Format");
            break;
    }

    return String::Empty();
}

void Line::print(std::ostream& anOutputStream, bool displayDecorators) const
{
    displayDecorators ? ostk::core::utils::Print::Header(anOutputStream, "Line") : void();

    ostk::core::utils::Print::Line(anOutputStream)
        << "Origin:" << (origin_.isDefined() ? origin_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Direction:" << (direction_.isDefined() ? direction_.toString() : "Undefined");

    displayDecorators ? ostk::core::utils::Print::Footer(anOutputStream) : void();
}

void Line::applyTransformation(const Transformation& aTransformation)
{
    if (!aTransformation.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Transformation");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Line");
    }

    origin_.applyTransformation(aTransformation);
    direction_ = aTransformation.applyTo(direction_);
}

Line Line::Undefined()
{
    return {Point::Undefined(), Vector2d::Undefined()};
}

Line Line::Points(const Point& aFirstPoint, const Point& aSecondPoint)
{
    if (!aFirstPoint.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("First point");
    }

    if (!aSecondPoint.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Second point");
    }

    if (aFirstPoint == aSecondPoint)
    {
        throw ostk::core::error::RuntimeError("Points are identical.");
    }

    return {aFirstPoint, (aSecondPoint - aFirstPoint).normalized()};
}

}  // namespace object
}  // namespace d2
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk
