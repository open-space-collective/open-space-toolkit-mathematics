/// Apache License 2.0

#include <Gte/Mathematics/GteIntrSphere3Sphere3.h>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Cone.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Line.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Plane.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/PointSet.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Pyramid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ray.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Sphere.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>
// #include <Gte/Mathematics/GteIntrHalfspace3Sphere3.h>
#include <Gte/Mathematics/GteIntrLine3Sphere3.h>
#include <Gte/Mathematics/GteIntrPlane3Sphere3.h>
#include <Gte/Mathematics/GteIntrRay3Sphere3.h>
#include <Gte/Mathematics/GteIntrSegment3Sphere3.h>

namespace ostk
{
namespace mathematics
{
namespace geometry
{
namespace d3
{
namespace object
{

gte::Vector3<double> SphereGteVectorFromPoint(const Point& aPoint)
{
    return {aPoint.x(), aPoint.y(), aPoint.z()};
}

gte::Vector3<double> SphereGteVectorFromVector3d(const Vector3d& aVector)
{
    return {aVector.x(), aVector.y(), aVector.z()};
}

Point SpherePointFromGteVector(const gte::Vector3<double>& aVector)
{
    return {aVector[0], aVector[1], aVector[2]};
}

Sphere::Sphere(const Point& aCenter, const Real& aRadius)
    : Object(),
      center_(aCenter),
      radius_(aRadius)
{
}

Sphere* Sphere::clone() const
{
    return new Sphere(*this);
}

bool Sphere::operator==(const Sphere& aSphere) const
{
    if ((!this->isDefined()) || (!aSphere.isDefined()))
    {
        return false;
    }

    return (center_ == aSphere.center_) && (radius_ == aSphere.radius_);
}

bool Sphere::operator!=(const Sphere& aSphere) const
{
    if ((!this->isDefined()) || (!aSphere.isDefined()))
    {
        return true;
    }

    return (center_ != aSphere.center_) || (radius_ != aSphere.radius_);
}

bool Sphere::isDefined() const
{
    return center_.isDefined() && radius_.isDefined();
}

bool Sphere::isUnitary() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Sphere");
    }

    return radius_ == 1.0;
}

bool Sphere::intersects(const Point& aPoint) const
{
    return this->contains(aPoint);
}

bool Sphere::intersects(const PointSet& aPointSet) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Sphere");
    }

    return (!aPointSet.isEmpty()) && std::any_of(
                                         aPointSet.begin(),
                                         aPointSet.end(),
                                         [this](const Point& aPoint) -> bool
                                         {
                                             return this->contains(aPoint);
                                         }
                                     );
}

bool Sphere::intersects(const Line& aLine) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Sphere");
    }

    if (!aLine.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Line");
    }

    // Line

    const gte::Line3<double> line = {
        SphereGteVectorFromPoint(aLine.getOrigin()), SphereGteVectorFromVector3d(aLine.getDirection())
    };

    // Sphere

    const gte::Vector3<double> center = SphereGteVectorFromPoint(center_);

    const gte::Sphere3<double> sphere = {center, radius_};

    // Intersection

    gte::TIQuery<double, gte::Line3<double>, gte::Sphere3<double>> intersectionQuery;

    auto intersectionResult = intersectionQuery(line, sphere);

    return intersectionResult.intersect;
}

bool Sphere::intersects(const Ray& aRay) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Sphere");
    }

    if (!aRay.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ray");
    }

    // Ray

    const gte::Ray3<double> ray = {
        SphereGteVectorFromPoint(aRay.getOrigin()), SphereGteVectorFromVector3d(aRay.getDirection())
    };

    // Sphere

    const gte::Vector3<double> center = SphereGteVectorFromPoint(center_);

    const gte::Sphere3<double> sphere = {center, radius_};

    // Intersection

    gte::TIQuery<double, gte::Ray3<double>, gte::Sphere3<double>> intersectionQuery;

    auto intersectionResult = intersectionQuery(ray, sphere);

    return intersectionResult.intersect;
}

bool Sphere::intersects(const Segment& aSegment) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Sphere");
    }

    if (!aSegment.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Segment");
    }

    // Segment

    const gte::Segment3<double> segment = {
        SphereGteVectorFromPoint(aSegment.getFirstPoint()), SphereGteVectorFromPoint(aSegment.getSecondPoint())
    };

    // Sphere

    const gte::Vector3<double> center = SphereGteVectorFromPoint(center_);

    const gte::Sphere3<double> sphere = {center, radius_};

    // Intersection

    gte::TIQuery<double, gte::Segment3<double>, gte::Sphere3<double>> intersectionQuery;

    auto intersectionResult = intersectionQuery(segment, sphere);

    return intersectionResult.intersect;
}

bool Sphere::intersects(const Plane& aPlane) const
{
    if (!aPlane.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Plane");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Sphere");
    }

    // Plane

    const gte::Vector3<double> normal = SphereGteVectorFromVector3d(aPlane.getNormalVector());
    const gte::Vector3<double> point = SphereGteVectorFromPoint(aPlane.getPoint());

    const gte::Plane3<double> plane = {normal, point};

    // Sphere

    const gte::Vector3<double> center = SphereGteVectorFromPoint(center_);

    const gte::Sphere3<double> sphere = {center, radius_};

    // Intersection

    gte::TIQuery<double, gte::Plane3<double>, gte::Sphere3<double>> intersectionQuery;

    auto intersectionResult = intersectionQuery(plane, sphere);

    return intersectionResult.intersect;
}

bool Sphere::intersects(const Pyramid& aPyramid) const
{
    return aPyramid.intersects(*this);
}

bool Sphere::intersects(const Cone& aCone) const
{
    return aCone.intersects(*this);
}

bool Sphere::contains(const Point& aPoint) const
{
    using ostk::mathematics::object::Vector3d;

    if (!aPoint.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Sphere");
    }

    return std::abs((aPoint - center_).squaredNorm() - (radius_ * radius_)) < Real::Epsilon();
}

bool Sphere::contains(const PointSet& aPointSet) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Sphere");
    }

    return (!aPointSet.isEmpty()) && std::all_of(
                                         aPointSet.begin(),
                                         aPointSet.end(),
                                         [this](const Point& aPoint) -> bool
                                         {
                                             return this->contains(aPoint);
                                         }
                                     );
}

Point Sphere::getCenter() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Sphere");
    }

    return center_;
}

Real Sphere::getRadius() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Sphere");
    }

    return radius_;
}

Intersection Sphere::intersectionWith(const Line& aLine) const
{
    using ostk::mathematics::geometry::d3::object::PointSet;

    if (!aLine.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Line");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Sphere");
    }

    // Line

    const gte::Line3<double> segment = {
        SphereGteVectorFromPoint(aLine.getOrigin()), SphereGteVectorFromVector3d(aLine.getDirection())
    };

    // Sphere

    const gte::Vector3<double> center = SphereGteVectorFromPoint(center_);

    const gte::Sphere3<double> sphere = {center, radius_};

    // Intersection

    gte::FIQuery<double, gte::Line3<double>, gte::Sphere3<double>> intersectionQuery;

    auto intersectionResult = intersectionQuery(segment, sphere);

    if (intersectionResult.intersect)
    {
        if (intersectionResult.numIntersections == 1)
        {
            return Intersection::Point(SpherePointFromGteVector(intersectionResult.point[0]));
        }
        else if (intersectionResult.numIntersections == 2)
        {
            return Intersection::PointSet(PointSet(
                {Point(SpherePointFromGteVector(intersectionResult.point[0])),
                 Point(SpherePointFromGteVector(intersectionResult.point[1]))}
            ));
        }
        else
        {
            throw ostk::core::error::RuntimeError("Intersection algorithm has failed.");
        }
    }

    return Intersection::Empty();
}

Intersection Sphere::intersectionWith(const Ray& aRay, const bool onlyInSight) const
{
    using ostk::mathematics::geometry::d3::object::PointSet;

    if (!aRay.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ray");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Sphere");
    }

    // Ray

    const gte::Ray3<double> segment = {
        SphereGteVectorFromPoint(aRay.getOrigin()), SphereGteVectorFromVector3d(aRay.getDirection())
    };

    // Sphere

    const gte::Vector3<double> center = SphereGteVectorFromPoint(center_);

    const gte::Sphere3<double> sphere = {center, radius_};

    // Intersection

    gte::FIQuery<double, gte::Ray3<double>, gte::Sphere3<double>> intersectionQuery;

    auto intersectionResult = intersectionQuery(segment, sphere);

    if (intersectionResult.intersect)
    {
        if (intersectionResult.numIntersections == 1)
        {
            const Point point = SpherePointFromGteVector(intersectionResult.point[0]);

            if ((point == aRay.getOrigin()) && (!this->contains(point)))  // Discard ray origin, if returned by Gte
            {
                return Intersection::Empty();
            }

            return Intersection::Point(point);
        }
        else if (intersectionResult.numIntersections == 2)
        {
            const Point firstPoint = SpherePointFromGteVector(intersectionResult.point[0]);
            const Point secondPoint = SpherePointFromGteVector(intersectionResult.point[1]);

            const PointSet pointSet = {{firstPoint, secondPoint}};

            if ((firstPoint == aRay.getOrigin()) || (secondPoint == aRay.getOrigin()))
            {
                if ((firstPoint == aRay.getOrigin()) &&
                    (!this->contains(firstPoint)))  // Discard ray origin, if returned by Gte
                {
                    return Intersection::Point(secondPoint);
                }

                if ((secondPoint == aRay.getOrigin()) &&
                    (!this->contains(secondPoint)))  // Discard ray origin, if returned by Gte
                {
                    return Intersection::Point(firstPoint);
                }
            }

            return onlyInSight ? Intersection::Point(pointSet.getPointClosestTo(aRay.getOrigin()))
                               : Intersection::PointSet(pointSet);
        }
        else
        {
            throw ostk::core::error::RuntimeError("Intersection algorithm has failed.");
        }
    }

    return Intersection::Empty();
}

Intersection Sphere::intersectionWith(const Segment& aSegment) const
{
    using ostk::mathematics::geometry::d3::object::PointSet;

    if (!aSegment.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Segment");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Sphere");
    }

    // Segment

    const gte::Segment3<double> segment = {
        SphereGteVectorFromPoint(aSegment.getFirstPoint()), SphereGteVectorFromPoint(aSegment.getSecondPoint())
    };
    ;

    // Sphere

    const gte::Vector3<double> center = SphereGteVectorFromPoint(center_);

    const gte::Sphere3<double> sphere = {center, radius_};

    // Intersection

    gte::FIQuery<double, gte::Segment3<double>, gte::Sphere3<double>> intersectionQuery;

    auto intersectionResult = intersectionQuery(segment, sphere);

    if (intersectionResult.intersect)
    {
        if (intersectionResult.numIntersections == 1)
        {
            const Point point = SpherePointFromGteVector(intersectionResult.point[0]);

            if ((point == aSegment.getFirstPoint() || (point == aSegment.getSecondPoint())) &&
                (!this->contains(point)))  // Discard segment points, if returned by Gte
            {
                return Intersection::Empty();
            }

            return Intersection::Point(point);
        }
        else if (intersectionResult.numIntersections == 2)
        {
            const Point firstPoint = SpherePointFromGteVector(intersectionResult.point[0]);
            const Point secondPoint = SpherePointFromGteVector(intersectionResult.point[1]);

            if ((firstPoint == aSegment.getFirstPoint()) || (secondPoint == aSegment.getFirstPoint()) ||
                (firstPoint == aSegment.getSecondPoint()) ||
                (secondPoint == aSegment.getSecondPoint()))  // Discard segment points, if returned by Gte
            {
                if ((firstPoint == aSegment.getFirstPoint()) && (!this->contains(firstPoint)))
                {
                    if ((secondPoint == aSegment.getSecondPoint()) && (!this->contains(secondPoint)))
                    {
                        return Intersection::Empty();
                    }

                    return Intersection::Point(secondPoint);
                }

                if ((firstPoint == aSegment.getSecondPoint()) && (!this->contains(firstPoint)))
                {
                    if ((secondPoint == aSegment.getFirstPoint()) && (!this->contains(secondPoint)))
                    {
                        return Intersection::Empty();
                    }

                    return Intersection::Point(secondPoint);
                }

                if ((secondPoint == aSegment.getFirstPoint()) && (!this->contains(secondPoint)))
                {
                    if ((firstPoint == aSegment.getSecondPoint()) && (!this->contains(firstPoint)))
                    {
                        return Intersection::Empty();
                    }

                    return Intersection::Point(firstPoint);
                }

                if ((secondPoint == aSegment.getSecondPoint()) && (!this->contains(secondPoint)))
                {
                    if ((firstPoint == aSegment.getFirstPoint()) && (!this->contains(firstPoint)))
                    {
                        return Intersection::Empty();
                    }

                    return Intersection::Point(firstPoint);
                }
            }

            return Intersection::PointSet(PointSet({firstPoint, secondPoint}));
        }
        else
        {
            throw ostk::core::error::RuntimeError("Intersection algorithm has failed.");
        }
    }

    return Intersection::Empty();
}

Intersection Sphere::intersectionWith(const Pyramid& aPyramid, const bool onlyInSight) const
{
    return aPyramid.intersectionWith(*this, onlyInSight);
}

Intersection Sphere::intersectionWith(const Cone& aCone, const bool onlyInSight) const
{
    return aCone.intersectionWith(*this, onlyInSight);
}

void Sphere::print(std::ostream& anOutputStream, bool displayDecorators) const
{
    displayDecorators ? ostk::core::utils::Print::Header(anOutputStream, "Sphere") : void();

    ostk::core::utils::Print::Line(anOutputStream)
        << "Center:" << (center_.isDefined() ? center_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Radius:" << (radius_.isDefined() ? radius_.toString() : "Undefined");

    displayDecorators ? ostk::core::utils::Print::Footer(anOutputStream) : void();
}

void Sphere::applyTransformation(const Transformation& aTransformation)
{
    if (!aTransformation.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Transformation");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Sphere");
    }

    if (!aTransformation.isRigid())
    {
        throw ostk::core::error::RuntimeError("Only rigid transformation is supported.");
    }

    center_.applyTransformation(aTransformation);
}

Sphere Sphere::Undefined()
{
    return {Point::Undefined(), Real::Undefined()};
}

Sphere Sphere::Unit(const Point& aCenter)
{
    return {aCenter, 1.0};
}

}  // namespace object
}  // namespace d3
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk
