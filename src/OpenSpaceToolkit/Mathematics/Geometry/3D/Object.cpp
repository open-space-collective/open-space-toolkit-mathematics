/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Composite.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Cone.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Cuboid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Line.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/LineString.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Plane.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/PointSet.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Pyramid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ray.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Sphere.hpp>

namespace ostk
{
namespace mathematics
{
namespace geometry
{
namespace d3
{

Object::~Object() {}

bool Object::operator==(const Object& anObject) const
{
    using ostk::mathematics::geometry::d3::object::Composite;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Cuboid;
    using ostk::mathematics::geometry::d3::object::Ellipsoid;
    using ostk::mathematics::geometry::d3::object::Line;
    using ostk::mathematics::geometry::d3::object::LineString;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::geometry::d3::object::Sphere;

    if ((!this->isDefined()) || (!anObject.isDefined()))
    {
        return false;
    }

    if (typeid(*this) != typeid(anObject))
    {
        return false;
    }

    // Point

    if (const Point* objectPtr = dynamic_cast<const Point*>(this))
    {
        if (const Point* otherObjectPtr = dynamic_cast<const Point*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr);
        }
    }

    // PointSet

    if (const PointSet* objectPtr = dynamic_cast<const PointSet*>(this))
    {
        if (const PointSet* otherObjectPtr = dynamic_cast<const PointSet*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr);
        }
    }

    // Line

    if (const Line* objectPtr = dynamic_cast<const Line*>(this))
    {
        if (const Line* otherObjectPtr = dynamic_cast<const Line*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr);
        }
    }

    // Ray

    if (const Ray* objectPtr = dynamic_cast<const Ray*>(this))
    {
        if (const Ray* otherObjectPtr = dynamic_cast<const Ray*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr);
        }
    }

    // Segment

    if (const Segment* objectPtr = dynamic_cast<const Segment*>(this))
    {
        if (const Segment* otherObjectPtr = dynamic_cast<const Segment*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr);
        }
    }

    // LineString

    if (const LineString* objectPtr = dynamic_cast<const LineString*>(this))
    {
        if (const LineString* otherObjectPtr = dynamic_cast<const LineString*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr);
        }
    }

    // Polygon

    if (const Polygon* objectPtr = dynamic_cast<const Polygon*>(this))
    {
        if (const Polygon* otherObjectPtr = dynamic_cast<const Polygon*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr);
        }
    }

    // Plane

    if (const Plane* objectPtr = dynamic_cast<const Plane*>(this))
    {
        if (const Plane* otherObjectPtr = dynamic_cast<const Plane*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr);
        }
    }

    // Cuboid

    if (const Cuboid* objectPtr = dynamic_cast<const Cuboid*>(this))
    {
        if (const Cuboid* otherObjectPtr = dynamic_cast<const Cuboid*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr);
        }
    }

    // Sphere

    if (const Sphere* objectPtr = dynamic_cast<const Sphere*>(this))
    {
        if (const Sphere* otherObjectPtr = dynamic_cast<const Sphere*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr);
        }
    }

    // Ellipsoid

    if (const Ellipsoid* objectPtr = dynamic_cast<const Ellipsoid*>(this))
    {
        if (const Ellipsoid* otherObjectPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr);
        }
    }

    // Pyramid

    if (const Pyramid* objectPtr = dynamic_cast<const Pyramid*>(this))
    {
        if (const Pyramid* otherObjectPtr = dynamic_cast<const Pyramid*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr);
        }
    }

    // Cone

    if (const Cone* objectPtr = dynamic_cast<const Cone*>(this))
    {
        if (const Cone* otherObjectPtr = dynamic_cast<const Cone*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr);
        }
    }

    // Composite

    if (const Composite* objectPtr = dynamic_cast<const Composite*>(this))
    {
        if (const Composite* otherObjectPtr = dynamic_cast<const Composite*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr);
        }
    }

    std::cout << (*this) << std::endl;
    std::cout << anObject << std::endl;

    throw ostk::core::error::runtime::ToBeImplemented("Object :: operator ==");

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
    using ostk::mathematics::geometry::d3::object::Composite;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Cuboid;
    using ostk::mathematics::geometry::d3::object::Ellipsoid;
    using ostk::mathematics::geometry::d3::object::Line;
    using ostk::mathematics::geometry::d3::object::LineString;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::geometry::d3::object::Sphere;

    if (!anObject.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Object");
    }

    // Line

    if (const Line* objectPtr = dynamic_cast<const Line*>(this))
    {
        // Plane

        if (const Plane* otherObjectPtr = dynamic_cast<const Plane*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }

        // Sphere

        if (const Sphere* otherObjectPtr = dynamic_cast<const Sphere*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }

        // Ellipsoid

        if (const Ellipsoid* otherObjectPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }
    }

    // Ray

    if (const Ray* objectPtr = dynamic_cast<const Ray*>(this))
    {
        // Plane

        if (const Plane* otherObjectPtr = dynamic_cast<const Plane*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }

        // Sphere

        if (const Sphere* otherObjectPtr = dynamic_cast<const Sphere*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }

        // Ellipsoid

        if (const Ellipsoid* otherObjectPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }
    }

    // Segment

    if (const Segment* objectPtr = dynamic_cast<const Segment*>(this))
    {
        // Plane

        if (const Plane* otherObjectPtr = dynamic_cast<const Plane*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }

        // Sphere

        if (const Sphere* otherObjectPtr = dynamic_cast<const Sphere*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }

        // Ellipsoid

        if (const Ellipsoid* otherObjectPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }
    }

    // Plane

    if (const Plane* objectPtr = dynamic_cast<const Plane*>(this))
    {
        // Point

        if (const Point* otherObjectPtr = dynamic_cast<const Point*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }

        // PointSet

        if (const PointSet* otherObjectPtr = dynamic_cast<const PointSet*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }

        // Line

        if (const Line* otherObjectPtr = dynamic_cast<const Line*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }

        // Ray

        if (const Ray* otherObjectPtr = dynamic_cast<const Ray*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }

        // Segment

        if (const Segment* otherObjectPtr = dynamic_cast<const Segment*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }
    }

    // Sphere

    if (const Sphere* objectPtr = dynamic_cast<const Sphere*>(this))
    {
        // Line

        if (const Line* otherObjectPtr = dynamic_cast<const Line*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }

        // Segment

        if (const Segment* otherObjectPtr = dynamic_cast<const Segment*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }

        // Ray

        if (const Ray* otherObjectPtr = dynamic_cast<const Ray*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }

        // Pyramid

        if (const Pyramid* otherObjectPtr = dynamic_cast<const Pyramid*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }

        // Cone

        if (const Cone* otherObjectPtr = dynamic_cast<const Cone*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }
    }

    // Ellipsoid

    if (const Ellipsoid* objectPtr = dynamic_cast<const Ellipsoid*>(this))
    {
        // Line

        if (const Line* otherObjectPtr = dynamic_cast<const Line*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }

        // Segment

        if (const Segment* otherObjectPtr = dynamic_cast<const Segment*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }

        // Ray

        if (const Ray* otherObjectPtr = dynamic_cast<const Ray*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }

        // Ellipsoid

        // if (const Ellipsoid* otherObjectPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        // {
        //     return objectPtr->intersects(*otherObjectPtr) ;
        // }

        // Pyramid

        if (const Pyramid* otherObjectPtr = dynamic_cast<const Pyramid*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }

        // Cone

        if (const Cone* otherObjectPtr = dynamic_cast<const Cone*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }
    }

    // Pyramid

    if (const Pyramid* objectPtr = dynamic_cast<const Pyramid*>(this))
    {
        // Sphere

        if (const Sphere* otherObjectPtr = dynamic_cast<const Sphere*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }

        // Ellipsoid

        if (const Ellipsoid* otherObjectPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }
    }

    // Cone

    if (const Cone* objectPtr = dynamic_cast<const Cone*>(this))
    {
        // Sphere

        if (const Sphere* otherObjectPtr = dynamic_cast<const Sphere*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }

        // Ellipsoid

        if (const Ellipsoid* otherObjectPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr);
        }
    }

    std::cout << (*this) << std::endl;
    std::cout << anObject << std::endl;

    throw ostk::core::error::runtime::ToBeImplemented("Object :: intersects");

    return false;
}

bool Object::contains(const Object& anObject) const
{
    using ostk::mathematics::geometry::d3::object::Composite;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Cuboid;
    using ostk::mathematics::geometry::d3::object::Ellipsoid;
    using ostk::mathematics::geometry::d3::object::Line;
    using ostk::mathematics::geometry::d3::object::LineString;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::geometry::d3::object::Sphere;

    if (!anObject.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Object");
    }

    // Segment

    // if (const Segment* objectPtr = dynamic_cast<const Segment*>(this))
    // {

    // Segment

    // if (const Segment* otherObjectPtr = dynamic_cast<const Segment*>(&anObject))
    // {
    //     return objectPtr->contains(*otherObjectPtr) ;
    // }

    // Ellipsoid

    // if (const Ellipsoid* otherObjectPtr = dynamic_cast<const Ellipsoid*>(&anObject))
    // {
    //     return objectPtr->contains(*otherObjectPtr) ;
    // }

    // }

    // Plane

    if (const Plane* objectPtr = dynamic_cast<const Plane*>(this))
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

        // Line

        if (const Line* otherObjectPtr = dynamic_cast<const Line*>(&anObject))
        {
            return objectPtr->contains(*otherObjectPtr);
        }

        // Ray

        if (const Ray* otherObjectPtr = dynamic_cast<const Ray*>(&anObject))
        {
            return objectPtr->contains(*otherObjectPtr);
        }

        // Segment

        if (const Segment* otherObjectPtr = dynamic_cast<const Segment*>(&anObject))
        {
            return objectPtr->contains(*otherObjectPtr);
        }
    }

    // Ellipsoid

    if (const Ellipsoid* objectPtr = dynamic_cast<const Ellipsoid*>(this))
    {
        // Segment

        if (const Segment* otherObjectPtr = dynamic_cast<const Segment*>(&anObject))
        {
            return objectPtr->contains(*otherObjectPtr);
        }

        // Ellipsoid

        // if (const Ellipsoid* otherObjectPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        // {
        //     return objectPtr->contains(*otherObjectPtr) ;
        // }
    }

    // Pyramid

    if (const Pyramid* objectPtr = dynamic_cast<const Pyramid*>(this))
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

        // Segment

        if (const Segment* otherObjectPtr = dynamic_cast<const Segment*>(&anObject))
        {
            return objectPtr->contains(*otherObjectPtr);
        }

        // Ellipsoid

        if (const Ellipsoid* otherObjectPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        {
            return objectPtr->contains(*otherObjectPtr);
        }
    }

    // Cone

    if (const Cone* objectPtr = dynamic_cast<const Cone*>(this))
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

        // Segment

        if (const Segment* otherObjectPtr = dynamic_cast<const Segment*>(&anObject))
        {
            return objectPtr->contains(*otherObjectPtr);
        }

        // Ray

        if (const Ray* otherObjectPtr = dynamic_cast<const Ray*>(&anObject))
        {
            return objectPtr->contains(*otherObjectPtr);
        }

        // Sphere

        if (const Sphere* otherObjectPtr = dynamic_cast<const Sphere*>(&anObject))
        {
            return objectPtr->contains(*otherObjectPtr);
        }

        // Ellipsoid

        if (const Ellipsoid* otherObjectPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        {
            return objectPtr->contains(*otherObjectPtr);
        }
    }

    throw ostk::core::error::runtime::ToBeImplemented("Object :: contains");

    return false;
}

Intersection Object::intersectionWith(const Object& anObject) const
{
    using ostk::mathematics::geometry::d3::object::Composite;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Cuboid;
    using ostk::mathematics::geometry::d3::object::Ellipsoid;
    using ostk::mathematics::geometry::d3::object::Line;
    using ostk::mathematics::geometry::d3::object::LineString;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::geometry::d3::object::Sphere;

    if (!anObject.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Object");
    }

    // Line

    if (const Line* objectPtr = dynamic_cast<const Line*>(this))
    {
        // Plane

        if (const Plane* otherObjectPtr = dynamic_cast<const Plane*>(&anObject))
        {
            return objectPtr->intersectionWith(*otherObjectPtr);
        }
    }

    // Ray

    if (const Ray* objectPtr = dynamic_cast<const Ray*>(this))
    {
        // Plane

        if (const Plane* otherObjectPtr = dynamic_cast<const Plane*>(&anObject))
        {
            return objectPtr->intersectionWith(*otherObjectPtr);
        }

        // Ellipsoid

        if (const Ellipsoid* otherObjectPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        {
            return objectPtr->intersectionWith(*otherObjectPtr);
        }
    }

    // Segment

    if (const Segment* objectPtr = dynamic_cast<const Segment*>(this))
    {
        // Plane

        if (const Plane* otherObjectPtr = dynamic_cast<const Plane*>(&anObject))
        {
            return objectPtr->intersectionWith(*otherObjectPtr);
        }
    }

    // Sphere

    if (const Sphere* objectPtr = dynamic_cast<const Sphere*>(this))
    {
        // Ray

        if (const Ray* otherObjectPtr = dynamic_cast<const Ray*>(&anObject))
        {
            return objectPtr->intersectionWith(*otherObjectPtr);
        }

        // Pyramid

        if (const Pyramid* otherObjectPtr = dynamic_cast<const Pyramid*>(&anObject))
        {
            return objectPtr->intersectionWith(*otherObjectPtr);
        }

        // Cone

        if (const Cone* otherObjectPtr = dynamic_cast<const Cone*>(&anObject))
        {
            return objectPtr->intersectionWith(*otherObjectPtr);
        }
    }

    // Ellipsoid

    if (const Ellipsoid* objectPtr = dynamic_cast<const Ellipsoid*>(this))
    {
        // Ray

        if (const Ray* otherObjectPtr = dynamic_cast<const Ray*>(&anObject))
        {
            return objectPtr->intersectionWith(*otherObjectPtr);
        }

        // Pyramid

        if (const Pyramid* otherObjectPtr = dynamic_cast<const Pyramid*>(&anObject))
        {
            return objectPtr->intersectionWith(*otherObjectPtr);
        }

        // Cone

        if (const Cone* otherObjectPtr = dynamic_cast<const Cone*>(&anObject))
        {
            return objectPtr->intersectionWith(*otherObjectPtr);
        }
    }

    // Pyramid

    if (const Pyramid* objectPtr = dynamic_cast<const Pyramid*>(this))
    {
        // Sphere

        if (const Sphere* otherObjectPtr = dynamic_cast<const Sphere*>(&anObject))
        {
            return objectPtr->intersectionWith(*otherObjectPtr);
        }

        // Ellipsoid

        if (const Ellipsoid* otherObjectPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        {
            return objectPtr->intersectionWith(*otherObjectPtr);
        }
    }

    // Cone

    if (const Cone* objectPtr = dynamic_cast<const Cone*>(this))
    {
        // Sphere

        if (const Sphere* otherObjectPtr = dynamic_cast<const Sphere*>(&anObject))
        {
            return objectPtr->intersectionWith(*otherObjectPtr);
        }

        // Ellipsoid

        if (const Ellipsoid* otherObjectPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        {
            return objectPtr->intersectionWith(*otherObjectPtr);
        }
    }

    // Polygon

    if (const Polygon* objectPtr = dynamic_cast<const Polygon*>(this))
    {
        // Polygon

        if (const Polygon* otherObjectPtr = dynamic_cast<const Polygon*>(&anObject))
        {
            return objectPtr->intersectionWith(*otherObjectPtr);
        }
    }

    std::cout << (*this) << std::endl;
    std::cout << anObject << std::endl;

    throw ostk::core::error::runtime::ToBeImplemented("Object :: intersectionWith");

    return Intersection::Undefined();
}

}  // namespace d3
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk
