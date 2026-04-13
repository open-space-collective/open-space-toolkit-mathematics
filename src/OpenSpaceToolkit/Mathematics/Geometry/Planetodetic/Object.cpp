/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/Planetodetic/Object.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/Planetodetic/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/Planetodetic/Object/Polygon.hpp>

namespace ostk
{
namespace mathematics
{
namespace geometry
{
namespace planetodetic
{

Object::~Object() {}

bool Object::operator==(const Object& anObject) const
{
    return this->isDefined() && anObject.isDefined() && (this == &anObject);
}

bool Object::operator!=(const Object& anObject) const
{
    return !((*this) == anObject);
}

std::ostream& operator<<(std::ostream& anOutputStream, const Object& anObject)
{
    anObject.print(anOutputStream, false);

    return anOutputStream;
}

bool Object::intersects(const Object&) const
{
    throw ostk::core::error::runtime::ToBeImplemented("Object :: intersects");

    return false;
}

bool Object::contains(const Object& anObject) const
{
    using ostk::mathematics::geometry::planetodetic::object::Point;
    using ostk::mathematics::geometry::planetodetic::object::Polygon;

    if (!anObject.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Object");
    }

    // Polygon

    if (const Polygon* objectPtr = dynamic_cast<const Polygon*>(this))
    {
        // Point

        if (const Point* otherObjectPtr = dynamic_cast<const Point*>(&anObject))
        {
            return objectPtr->contains(*otherObjectPtr);
        }
    }

    throw ostk::core::error::runtime::ToBeImplemented("Object :: contains");

    return false;
}

}  // namespace planetodetic
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk
