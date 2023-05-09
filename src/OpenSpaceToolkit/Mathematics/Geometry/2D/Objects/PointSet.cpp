// Copyright © Loft Orbital Solutions Inc.

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/PointSet.hpp>
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

PointSet::PointSet(const Array<Point>& aPointArray)
    : Object(),
      points_(aPointArray.begin(), aPointArray.end())
{
}

PointSet* PointSet::clone() const
{
    return new PointSet(*this);
}

bool PointSet::operator==(const PointSet& aPointSet) const
{
    return points_ == aPointSet.points_;
}

bool PointSet::operator!=(const PointSet& aPointSet) const
{
    return !((*this) == aPointSet);
}

bool PointSet::isDefined() const
{
    return !points_.empty();
}

bool PointSet::isEmpty() const
{
    return points_.empty();
}

bool PointSet::isNear(const PointSet& aPointSet, const Real& aTolerance) const
{
    if ((this->isEmpty()) || (aPointSet.isEmpty()))
    {
        return false;
    }

    if (this->getSize() != aPointSet.getSize())
    {
        return false;
    }

    PointSet::Container firstPointSetBuffer = points_;
    PointSet::Container secondPointSetBuffer = aPointSet.points_;

    while (!firstPointSetBuffer.empty())
    {
        const Point& firstPoint = *(firstPointSetBuffer.begin());

        bool foundClosestPoint = false;

        for (auto secondPointSetBufferIt = secondPointSetBuffer.begin();
             secondPointSetBufferIt != secondPointSetBuffer.end();
             ++secondPointSetBufferIt)
        {
            const Point& secondPoint = *secondPointSetBufferIt;

            if (firstPoint.isNear(secondPoint, aTolerance))
            {
                foundClosestPoint = true;

                secondPointSetBuffer.erase(secondPointSetBufferIt);

                break;
            }
        }

        if (foundClosestPoint)
        {
            firstPointSetBuffer.erase(firstPointSetBuffer.begin());
        }
        else
        {
            return false;
        }
    }

    return true;
}

Size PointSet::getSize() const
{
    return points_.size();
}

Real PointSet::distanceTo(const Point& aPoint) const
{
    using ostk::core::ctnr::Array;

    if (!aPoint.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    if (this->isEmpty())
    {
        throw ostk::core::error::runtime::Undefined("Point Set");
    }

    const Array<Real> distances = Array<Point>(this->begin(), this->end())
                                      .map<Real>(
                                          [&aPoint](const Point& anOtherPoint) -> Real
                                          {
                                              return aPoint.distanceTo(anOtherPoint);
                                          }
                                      );

    return *std::min_element(distances.begin(), distances.end());
}

Point PointSet::getPointClosestTo(const Point& aPoint) const
{
    if (!aPoint.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    if (this->isEmpty())
    {
        throw ostk::core::error::runtime::Undefined("Point set");
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

String PointSet::toString(const Object::Format& aFormat, const Integer& aPrecision) const
{
    switch (aFormat)
    {
        case Object::Format::Standard:
        {
            String pointSetString = "[";

            Index pointIndex = 0;
            const Size pointCount = this->getSize();

            for (const auto& point : points_)
            {
                pointSetString += point.toString(Object::Format::Standard, aPrecision);

                if ((pointIndex + 1) < pointCount)
                {
                    pointSetString += ", ";
                }

                pointIndex++;
            }

            pointSetString += "]";

            return pointSetString;
        }

        case Object::Format::WKT:
            throw ostk::core::error::RuntimeError("LineString is not supported by WKT format.");

        default:
            throw ostk::core::error::runtime::Wrong("Format");
            break;
    }

    return String::Empty();
}

void PointSet::print(std::ostream& anOutputStream, bool displayDecorators) const
{
    displayDecorators ? ostk::core::utils::Print::Header(anOutputStream, "Point Set") : void();

    for (const auto& point : points_)
    {
        ostk::core::utils::Print::Line(anOutputStream) << (point.isDefined() ? point.toString() : "Undefined");
    }

    displayDecorators ? ostk::core::utils::Print::Footer(anOutputStream) : void();
}

PointSet::ConstIterator PointSet::begin() const
{
    return points_.begin();
}

PointSet::ConstIterator PointSet::end() const
{
    return points_.end();
}

void PointSet::applyTransformation(const Transformation& aTransformation)
{
    if (!aTransformation.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Transformation");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point set");
    }

    PointSet::Container points;

    for (auto& point : points_)
    {
        points.insert(aTransformation.applyTo(point));
    }

    points_ = points;
}

PointSet PointSet::Empty()
{
    return {Array<Point>::Empty()};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}  // namespace objects
}  // namespace d2
}  // namespace geom
}  // namespace math
}  // namespace ostk

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
