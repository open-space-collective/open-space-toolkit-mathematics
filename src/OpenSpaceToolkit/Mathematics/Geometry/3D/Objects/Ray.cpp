/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Plane.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Ray.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Sphere.hpp>
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

Ray::Ray(const Point& anOrigin, const Vector3d& aDirection)
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

Ray* Ray::clone() const
{
    return new Ray(*this);
}

bool Ray::operator==(const Ray& aRay) const
{
    if ((!this->isDefined()) || (!aRay.isDefined()))
    {
        return false;
    }

    return (origin_ == aRay.origin_) && (direction_ == aRay.direction_);
}

bool Ray::operator!=(const Ray& aRay) const
{
    return !((*this) == aRay);
}

bool Ray::isDefined() const
{
    return origin_.isDefined() && direction_.isDefined();
}

bool Ray::intersects(const Point& aPoint) const
{
    return this->contains(aPoint);
}

// bool                            Ray::intersects                          (   const   Ray&                       aRay
// ) const
// {

// }

bool Ray::intersects(const Plane& aPlane) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ray");
    }

    if (!aPlane.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Plane");
    }

    const Vector3d n = aPlane.getNormalVector();
    const Vector3d v = direction_;

    const Vector3d Q_0 = aPlane.getPoint().asVector();
    const Vector3d P_0 = origin_.asVector();

    const double nDotV = n.dot(v);

    if (nDotV == 0.0)  // Ray and plane are parallel
    {
        return n.dot(Q_0 - P_0) == 0.0;  // Ray is in plane
    }

    const double t = n.dot(Q_0 - P_0) / nDotV;

    return t >= 0.0;
}

bool Ray::intersects(const Sphere& aSphere) const
{
    return aSphere.intersects(*this);
}

bool Ray::intersects(const Ellipsoid& anEllipsoid) const
{
    return anEllipsoid.intersects(*this);
}

bool Ray::contains(const Point& aPoint) const
{
    if (!aPoint.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ray");
    }

    const Vector3d AC = aPoint - origin_;

    return (direction_.cross(AC).squaredNorm() == 0.0) && (0.0 <= direction_.dot(AC));
}

bool Ray::contains(const PointSet& aPointSet) const
{
    if (!aPointSet.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point Set");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ray");
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

Point Ray::getOrigin() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ray");
    }

    return origin_;
}

Vector3d Ray::getDirection() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ray");
    }

    return direction_;
}

Real Ray::distanceTo(const Point& aPoint) const
{
    if (!aPoint.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ray");
    }

    if (aPoint == this->origin_)
    {
        return 0.0;
    }

    const Vector3d originToPoint = aPoint - this->origin_;

    if (originToPoint.dot(this->direction_) < 0.0)
    {
        return originToPoint.norm();
    }

    return this->direction_.cross(aPoint - this->origin_).norm();
}

Intersection Ray::intersectionWith(const Plane& aPlane) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ray");
    }

    if (!aPlane.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Plane");
    }

    const Vector3d n = aPlane.getNormalVector();
    const Vector3d v = direction_;

    const Vector3d Q_0 = aPlane.getPoint().asVector();
    const Vector3d P_0 = origin_.asVector();

    const double nDotV = n.dot(v);

    if (nDotV == 0.0)  // Ray and plane are parallel
    {
        if (n.dot(Q_0 - P_0) == 0.0)  // Ray is in plane
        {
            return Intersection::Ray(*this);
        }

        return Intersection::Empty();
    }

    const double t = n.dot(Q_0 - P_0) / nDotV;

    if (t < 0.0)
    {
        return Intersection::Empty();
    }

    return Intersection::Point(Point::Vector(P_0 + t * v));
}

Intersection Ray::intersectionWith(const Sphere& aSphere, const bool onlyInSight) const
{
    return aSphere.intersectionWith(*this, onlyInSight);
}

Intersection Ray::intersectionWith(const Ellipsoid& anEllipsoid, const bool onlyInSight) const
{
    return anEllipsoid.intersectionWith(*this, onlyInSight);
}

void Ray::print(std::ostream& anOutputStream, bool displayDecorators) const
{
    displayDecorators ? ostk::core::utils::Print::Header(anOutputStream, "Ray") : void();

    ostk::core::utils::Print::Line(anOutputStream)
        << "Origin:" << (origin_.isDefined() ? origin_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Direction:" << (direction_.isDefined() ? direction_.toString() : "Undefined");

    displayDecorators ? ostk::core::utils::Print::Footer(anOutputStream) : void();
}

void Ray::applyTransformation(const Transformation& aTransformation)
{
    if (!aTransformation.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Transformation");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ray");
    }

    origin_.applyTransformation(aTransformation);
    direction_ = aTransformation.applyTo(direction_);
}

Ray Ray::Undefined()
{
    return {Point::Undefined(), Vector3d::Undefined()};
}

}  // namespace objects
}  // namespace d3
}  // namespace geometry
}  // namespace math
}  // namespace ostk
