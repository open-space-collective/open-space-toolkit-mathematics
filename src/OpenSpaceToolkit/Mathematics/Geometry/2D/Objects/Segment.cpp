// Copyright © Loft Orbital Solutions Inc.

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/LineString.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/PointSet.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Transformation.hpp>

namespace ostk
{
namespace math
{
namespace geom
{
namespace d2
{
namespace objects
{

Segment::Segment(const Point& aFirstPoint, const Point& aSecondPoint)
    : Object(),
      firstPoint_(aFirstPoint),
      secondPoint_(aSecondPoint)
{
}

Segment* Segment::clone() const
{
    return new Segment(*this);
}

bool Segment::operator==(const Segment& aSegment) const
{
    if ((!this->isDefined()) || (!aSegment.isDefined()))
    {
        return false;
    }

    return ((firstPoint_ == aSegment.firstPoint_) && (secondPoint_ == aSegment.secondPoint_)) ||
           ((firstPoint_ == aSegment.secondPoint_) && (secondPoint_ == aSegment.firstPoint_));
}

bool Segment::operator!=(const Segment& aSegment) const
{
    return !((*this) == aSegment);
}

bool Segment::isDefined() const
{
    return firstPoint_.isDefined() && secondPoint_.isDefined();
}

bool Segment::isDegenerate() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Segment");
    }

    return firstPoint_ == secondPoint_;
}

// bool                            Segment::intersects                         (   const   Segment& aSegment ) const
// {

// }

bool Segment::contains(const Point& aPoint) const
{
    using ostk::math::obj::Vector3d;

    if (!aPoint.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Segment");
    }

    if (this->isDegenerate())
    {
        return firstPoint_ == aPoint;
    }

    const Vector2d AB_2d = secondPoint_ - firstPoint_;
    const Vector2d AC_2d = aPoint - firstPoint_;

    const Vector3d AB = {AB_2d.x(), AB_2d.y(), 0.0};
    const Vector3d AC = {AC_2d.x(), AC_2d.y(), 0.0};

    if (AB.cross(AC).squaredNorm() == 0.0)  // Points are aligned
    {
        const Real K_AC = AB.dot(AC);
        const Real K_AB = AB.dot(AB);

        return (0.0 <= K_AC) && (K_AC <= K_AB);  // C between A and B
    }

    return false;
}

bool Segment::contains(const PointSet& aPointSet) const
{
    return (!aPointSet.isEmpty()) && std::all_of(
                                         aPointSet.begin(),
                                         aPointSet.end(),
                                         [this](const Point& aPoint) -> bool
                                         {
                                             return this->contains(aPoint);
                                         }
                                     );
}

Point Segment::getFirstPoint() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Segment");
    }

    return firstPoint_;
}

Point Segment::getSecondPoint() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Segment");
    }

    return secondPoint_;
}

Point Segment::getCenter() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Segment");
    }

    return firstPoint_ + (secondPoint_ - firstPoint_) / 2.0;
}

Vector2d Segment::getDirection() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Segment");
    }

    if (this->isDegenerate())
    {
        throw ostk::core::error::RuntimeError("Segment is degenerate.");
    }

    return (secondPoint_ - firstPoint_).normalized();
}

Real Segment::getLength() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Segment");
    }

    return (secondPoint_ - firstPoint_).norm();
}

Real Segment::distanceTo(const Point& aPoint) const
{
    if (!aPoint.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Segment");
    }

    if (this->isDegenerate())
    {
        return firstPoint_.distanceTo(aPoint);
    }

    // https://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment

    const Point& v = firstPoint_;
    const Point& w = secondPoint_;
    const Point& p = aPoint;

    // |w-v|^2 (avoid sqrt)
    const double l2 = (secondPoint_ - firstPoint_).squaredNorm();

    // Clamp t from [0,1] to handle points outside the segmentw.
    const double t = std::max(0.0, std::min(1.0, (p - v).dot(w - v) / l2));

    // Projection falls on the segment
    const Point projection = v + t * (w - v);

    return projection.distanceTo(aPoint);
}

Real Segment::distanceTo(const PointSet& aPointSet) const
{
    using ostk::core::ctnr::Array;

    if (aPointSet.isEmpty())
    {
        throw ostk::core::error::runtime::Undefined("Point Set");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Segment");
    }

    const Array<Real> distances = Array<Point>(aPointSet.begin(), aPointSet.end())
                                      .map<Real>(
                                          [this](const Point& aPoint) -> Real
                                          {
                                              return this->distanceTo(aPoint);
                                          }
                                      );

    return *std::min_element(distances.begin(), distances.end());
}

Line Segment::toLine() const
{
    return Line::Points(firstPoint_, secondPoint_);
}

String Segment::toString(const Object::Format& aFormat, const Integer& aPrecision) const
{
    using ostk::math::geom::d2::objects::LineString;

    switch (aFormat)
    {
        case Object::Format::Standard:
            return String::Format(
                "[{} -> {}]",
                firstPoint_.toString(Object::Format::Standard, aPrecision),
                secondPoint_.toString(Object::Format::Standard, aPrecision)
            );

        case Object::Format::WKT:
            return LineString::Segment(*this).toString(Object::Format::WKT, aPrecision);

        default:
            throw ostk::core::error::runtime::Wrong("Format");
            break;
    }

    return String::Empty();
}

void Segment::print(std::ostream& anOutputStream, bool displayDecorators) const
{
    displayDecorators ? ostk::core::utils::Print::Header(anOutputStream, "Segment") : void();

    ostk::core::utils::Print::Line(anOutputStream)
        << "First point:" << (firstPoint_.isDefined() ? firstPoint_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Second point:" << (secondPoint_.isDefined() ? secondPoint_.toString() : "Undefined");

    displayDecorators ? ostk::core::utils::Print::Footer(anOutputStream) : void();
}

void Segment::applyTransformation(const Transformation& aTransformation)
{
    if (!aTransformation.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Transformation");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Segment");
    }

    firstPoint_.applyTransformation(aTransformation);
    secondPoint_.applyTransformation(aTransformation);
}

Segment Segment::Undefined()
{
    return {Point::Undefined(), Point::Undefined()};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}  // namespace objects
}  // namespace d2
}  // namespace geom
}  // namespace math
}  // namespace ostk

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
