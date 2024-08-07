/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/MultiPolygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/PointSet.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Polygon.hpp>

namespace ostk
{
namespace mathematics
{
namespace geometry
{
namespace d2
{

Object::~Object() {}

bool Object::operator==(const Object& anObject) const
{
    using ostk::mathematics::geometry::d2::object::MultiPolygon;
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::Polygon;

    if ((!this->isDefined()) || (!anObject.isDefined()))
    {
        return false;
    }

    if (typeid(*this) != typeid(anObject))
    {
        return false;
    }

    if (const Point* objectPtr = dynamic_cast<const Point*>(this))
    {
        if (const Point* otherObjectPtr = dynamic_cast<const Point*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr);
        }
    }

    if (const Polygon* objectPtr = dynamic_cast<const Polygon*>(this))
    {
        if (const Polygon* otherObjectPtr = dynamic_cast<const Polygon*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr);
        }
    }

    if (const MultiPolygon* objectPtr = dynamic_cast<const MultiPolygon*>(this))
    {
        if (const MultiPolygon* otherObjectPtr = dynamic_cast<const MultiPolygon*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr);
        }
    }

    return false;
}

bool Object::operator!=(const Object& anObject) const
{
    return !((*this) == anObject);
}

std::ostream& operator<<(std::ostream& anOutputStream, const Object& anObject)
{
    anObject.print(anOutputStream, true);

    return anOutputStream;
}

bool Object::intersects(const Object& anObject) const
{
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::Polygon;

    if (!anObject.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Object");
    }

    throw ostk::core::error::runtime::ToBeImplemented("Object :: intersects");

    return false;
}

bool Object::contains(const Object& anObject) const
{
    using ostk::mathematics::geometry::d2::object::LineString;
    using ostk::mathematics::geometry::d2::object::MultiPolygon;
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::PointSet;
    using ostk::mathematics::geometry::d2::object::Polygon;

    if (!anObject.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Object");
    }

    // LineString

    if (const LineString* objectPtr = dynamic_cast<const LineString*>(this))
    {
        // Point

        if (const Point* otherObjectPtr = dynamic_cast<const Point*>(&anObject))
        {
            return objectPtr->contains(*otherObjectPtr);
        }
    }

    // Polygon

    if (const Polygon* objectPtr = dynamic_cast<const Polygon*>(this))
    {
        // Point

        if (const Point* otherObjectPtr = dynamic_cast<const Point*>(&anObject))
        {
            return objectPtr->contains(*otherObjectPtr);
        }

        // PointSet

        if (const PointSet* otherObjectPtr = dynamic_cast<const PointSet*>(&anObject))
        {
            return objectPtr->contains(*otherObjectPtr);
        }

        // LineString

        if (const LineString* otherObjectPtr = dynamic_cast<const LineString*>(&anObject))
        {
            return objectPtr->contains(*otherObjectPtr);
        }
    }

    // MultiPolygon

    if (const MultiPolygon* objectPtr = dynamic_cast<const MultiPolygon*>(this))
    {
        // Point

        if (const Point* otherObjectPtr = dynamic_cast<const Point*>(&anObject))
        {
            return objectPtr->contains(*otherObjectPtr);
        }

        // PointSet

        if (const PointSet* otherObjectPtr = dynamic_cast<const PointSet*>(&anObject))
        {
            return objectPtr->contains(*otherObjectPtr);
        }
    }

    throw ostk::core::error::runtime::ToBeImplemented("Object :: contains");

    return false;
}

}  // namespace d2
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk
