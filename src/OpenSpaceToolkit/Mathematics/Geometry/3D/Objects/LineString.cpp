/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/LineString.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>

namespace ostk
{
namespace math
{
namespace geometry
{
namespace d3
{
namespace objects
{

LineString::LineString(const Array<Point>& aPointArray)
    : Object(),
      points_(aPointArray)
{
}

LineString* LineString::clone() const
{
    return new LineString(*this);
}

bool LineString::operator==(const LineString& aLineString) const
{
    return points_ == aLineString.points_;
}

bool LineString::operator!=(const LineString& aLineString) const
{
    return !((*this) == aLineString);
}

bool LineString::isDefined() const
{
    return !points_.isEmpty();
}

bool LineString::isEmpty() const
{
    return points_.isEmpty();
}

bool LineString::isNear(const LineString& aLineString, const Real& aTolerance) const
{
    if ((this->isEmpty()) || (aLineString.isEmpty()))
    {
        return false;
    }

    if (points_.getSize() != aLineString.points_.getSize())
    {
        return false;
    }

    for (const auto pointTuple : ostk::core::ctnr::iterators::Zip(points_, aLineString.points_))
    {
        if (!std::get<0>(pointTuple).isNear(std::get<1>(pointTuple), aTolerance))
        {
            return false;
        }
    }

    return true;
}

const Point& LineString::accessPointAt(const Index& anIndex) const
{
    if (anIndex >= points_.getSize())
    {
        throw ostk::core::error::RuntimeError("Point index [{}] out of bounds [0 - {}].", anIndex, points_.getSize());
    }

    return points_.at(anIndex);
}

Size LineString::getPointCount() const
{
    return points_.getSize();
}

Point LineString::getPointClosestTo(const Point& aPoint) const
{
    if (!aPoint.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    if (this->isEmpty())
    {
        throw ostk::core::error::runtime::Undefined("Line string");
    }

    Point const* pointPtr = nullptr;
    Real minDistance = Real::Undefined();

    for (const auto& point : points_)
    {
        const Real distance = (point - aPoint).squaredNorm();

        if ((!minDistance.isDefined()) || (distance < minDistance))
        {
            pointPtr = &point;

            minDistance = distance;
        }
    }

    return *pointPtr;
}

void LineString::print(std::ostream& anOutputStream, bool displayDecorators) const
{
    displayDecorators ? ostk::core::utils::Print::Header(anOutputStream, "Line String") : void();

    for (const auto& point : points_)
    {
        ostk::core::utils::Print::Line(anOutputStream) << (point.isDefined() ? point.toString() : "Undefined");
    }

    displayDecorators ? ostk::core::utils::Print::Footer(anOutputStream) : void();
}

LineString::ConstIterator LineString::begin() const
{
    return points_.begin();
}

LineString::ConstIterator LineString::end() const
{
    return points_.end();
}

void LineString::applyTransformation(const Transformation& aTransformation)
{
    if (!aTransformation.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Transformation");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Line string");
    }

    for (auto& point : points_)
    {
        point.applyTransformation(aTransformation);
    }
}

LineString LineString::Empty()
{
    return {Array<Point>::Empty()};
}

LineString LineString::Segment(const objects::Segment& aSegment)
{
    if (!aSegment.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Segment");
    }

    return {{aSegment.getFirstPoint(), aSegment.getSecondPoint()}};
}

}  // namespace objects
}  // namespace d3
}  // namespace geometry
}  // namespace math
}  // namespace ostk
