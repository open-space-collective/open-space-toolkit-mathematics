/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Cone.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Plane.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>

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

/// Rotates a vector about a unit axis by the angle of the given cosine and sine (Rodrigues' rotation formula).
///
/// This is the rotation Quaternion::RotationVector(RotationVector(axis, angle)).toConjugate() applies to a vector,
/// evaluated directly instead of through two quaternion products.
Vector3d ConeRotateVector(const Vector3d& aVector, const Vector3d& aUnitAxis, const double aCosine, const double aSine)
{
    return (aCosine * aVector) + (aSine * aUnitAxis.cross(aVector)) +
           (((1.0 - aCosine) * aUnitAxis.dot(aVector)) * aUnitAxis);
}

/// Visits the rays of the lateral surface of a cone, in the order Cone::getRaysOfLateralSurface returns them, until the
/// visitor returns false.
template <typename Visitor>
void ConeVisitRaysOfLateralSurface(
    const Point& anApex, const Vector3d& anAxis, const Angle& anAngle, const Size aRayCount, Visitor&& aVisitor
)
{
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;

    const Vector3d referenceDirection = (std::abs(anAxis.dot(Vector3d::X())) < 0.5)
                                          ? anAxis.cross(Vector3d::X()).normalized()
                                          : anAxis.cross(Vector3d::Y()).normalized();

    // The rotation vectors validate and normalize the rotation axes, and throw for an axis that is not unitary.

    const Vector3d referenceRotationAxis = RotationVector(referenceDirection, anAngle).getAxis();
    const Vector3d lateralRotationAxis = RotationVector(anAxis, anAngle).getAxis();

    const double angle_rad = anAngle.inRadians();

    const Ray referenceRay = {
        anApex, ConeRotateVector(anAxis, referenceRotationAxis, std::cos(angle_rad), std::sin(angle_rad))
    };

    const Vector3d referenceRayDirection = referenceRay.getDirection();

    // Same angles as Interval<Real>::HalfOpenRight(0.0, 360.0).generateArrayWithSize(aRayCount)

    const double angleStep_deg = (aRayCount > 1) ? (360.0 / static_cast<double>(aRayCount)) : 0.0;

    double rayAngle_deg = 0.0;

    for (Size rayIndex = 0; rayIndex < aRayCount; ++rayIndex, rayAngle_deg += angleStep_deg)
    {
        const double rayAngle_rad = rayAngle_deg * (M_PI / 180.0);

        const Ray ray = {
            anApex,
            ConeRotateVector(referenceRayDirection, lateralRotationAxis, std::cos(rayAngle_rad), std::sin(rayAngle_rad))
        };

        if (!aVisitor(ray))
        {
            return;
        }
    }
}

Cone::Cone(const Point& anApex, const Vector3d& anAxis, const Angle& anAngle)
    : Object(),
      apex_(anApex),
      axis_(anAxis),
      angle_(anAngle)
{
}

Cone* Cone::clone() const
{
    return new Cone(*this);
}

bool Cone::operator==(const Cone& aCone) const
{
    if ((!this->isDefined()) || (!aCone.isDefined()))
    {
        return false;
    }

    return (apex_ == aCone.apex_) && (((axis_ == aCone.axis_) && (angle_ == aCone.angle_)) ||
                                      ((axis_ == -aCone.axis_) && (angle_ == Angle::Degrees(180.0) - aCone.angle_)));
}

bool Cone::operator!=(const Cone& aCone) const
{
    return !((*this) == aCone);
}

bool Cone::isDefined() const
{
    return apex_.isDefined() && axis_.isDefined() && angle_.isDefined();
}

bool Cone::intersects(const Sphere& aSphere, [[maybe_unused]] const Size aDiscretizationLevel) const
{
    if (!aSphere.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Sphere");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone");
    }

    const Vector3d apexToCenter = aSphere.getCenter() - apex_;
    const double distance = apexToCenter.norm();

    if (distance <= aSphere.getRadius())
    {
        return true;
    }

    const Vector3d normalizedAxis = axis_.normalized();

    // Angle between cone axis and vector to sphere center
    const double theta = std::acos(normalizedAxis.dot(apexToCenter.normalized()));

    const double alpha = std::asin(aSphere.getRadius() / distance);

    return theta <= angle_.inRadians() + alpha;
}

bool Cone::intersects(const Ellipsoid& anEllipsoid, const Size aDiscretizationLevel) const
{
    if (!anEllipsoid.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone");
    }

    if (aDiscretizationLevel == 0)
    {
        throw ostk::core::error::runtime::Wrong("Ray count");
    }

    bool intersects = false;

    ConeVisitRaysOfLateralSurface(
        apex_,
        axis_,
        angle_,
        aDiscretizationLevel,
        [&anEllipsoid, &intersects](const Ray& aRay) -> bool
        {
            intersects = aRay.intersects(anEllipsoid);

            return !intersects;
        }
    );

    return intersects;
}

bool Cone::contains(const Point& aPoint) const
{
    if (!aPoint.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone");
    }

    if (aPoint == this->apex_)
    {
        return true;
    }

    const Vector3d apexToPoint = aPoint - this->apex_;

    if (apexToPoint.dot(this->axis_) < 0.0)
    {
        return false;
    }

    return Angle::Between(apexToPoint, this->axis_).inDegrees(0.0, 360.0) <= this->angle_.inDegrees(0.0, 360.0);
}

bool Cone::contains(const PointSet& aPointSet) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone");
    }

    return std::all_of(
        std::begin(aPointSet),
        std::end(aPointSet),
        [this](const Point& aPoint) -> bool
        {
            return this->contains(aPoint);
        }
    );
}

bool Cone::contains(const Segment& aSegment) const
{
    return this->contains(aSegment.getFirstPoint()) && this->contains(aSegment.getSecondPoint());
}

bool Cone::contains(const Ray& aRay) const
{
    if (!aRay.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ray");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone");
    }

    if (!this->contains(aRay.getOrigin()))
    {
        return false;
    }

    return Angle::Between(aRay.getDirection(), this->axis_).inDegrees(0.0, 360.0) <= this->angle_.inDegrees(0.0, 360.0);
}

bool Cone::contains(const Sphere& aSphere) const
{
    if (!aSphere.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Sphere");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone");
    }

    return this->contains(aSphere.getCenter()) && (this->distanceTo(aSphere.getCenter()) >= aSphere.getRadius());
}

bool Cone::contains(const Ellipsoid& anEllipsoid) const
{
    if (!anEllipsoid.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone");
    }

    throw ostk::core::error::runtime::ToBeImplemented("Cone::contains(const Ellipsoid&)");

    return false;  // TBI
}

Point Cone::getApex() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone");
    }

    return apex_;
}

Vector3d Cone::getAxis() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone");
    }

    return axis_;
}

Angle Cone::getAngle() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone");
    }

    return angle_;
}

Array<Ray> Cone::getRaysOfLateralSurface(const Size aRayCount) const
{
    if (aRayCount == 0)
    {
        throw ostk::core::error::runtime::Wrong("Ray count");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone");
    }

    Array<Ray> rays = Array<Ray>::Empty();

    rays.reserve(aRayCount);

    ConeVisitRaysOfLateralSurface(
        apex_,
        axis_,
        angle_,
        aRayCount,
        [&rays](const Ray& aRay) -> bool
        {
            rays.add(aRay);

            return true;
        }
    );

    return rays;
}

Real Cone::distanceTo(const Point& aPoint) const
{
    if (!aPoint.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone");
    }

    if (aPoint == this->apex_)
    {
        return 0.0;
    }

    const Vector3d apexToPoint = aPoint - this->apex_;

    if (apexToPoint.dot(this->axis_) < 0.0)
    {
        return apexToPoint.norm();
    }

    // TBO: There's probably a better way to do this that doesn't require the use of so many vector re-normalization.

    Vector3d nAxis;

    if (this->axis_.cross(apexToPoint).norm() > Real::Epsilon())
    {
        nAxis = (this->axis_.cross(apexToPoint)).cross(this->axis_).normalized();
    }
    else
    {
        if (this->axis_.cross(Vector3d {1.0, 0.0, 0.0}).norm() > Real::Epsilon())
        {
            nAxis = (this->axis_.cross(Vector3d {1.0, 0.0, 0.0})).cross(this->axis_).normalized();
        }
        else
        {
            nAxis = (this->axis_.cross(Vector3d {0.0, 1.0, 0.0})).cross(this->axis_).normalized();
        }
    }

    const Vector3d rayDirection = (this->axis_.normalized() + std::tan(this->angle_.inRadians()) * nAxis).normalized();

    return Ray(this->apex_, rayDirection).distanceTo(aPoint);
}

Intersection Cone::intersectionWith(const Sphere& aSphere, const bool onlyInSight, const Size aDiscretizationLevel)
    const
{
    if (!aSphere.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Sphere");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone");
    }

    Array<Point> firstIntersectionPoints = Array<Point>::Empty();
    Array<Point> secondIntersectionPoints = Array<Point>::Empty();

    for (const auto& ray : this->getRaysOfLateralSurface(aDiscretizationLevel))
    {
        const Intersection intersection = ray.intersectionWith(aSphere, onlyInSight);

        if (!intersection.isEmpty())
        {
            if (intersection.accessComposite().is<Point>())
            {
                firstIntersectionPoints.add(intersection.accessComposite().as<Point>());
            }
            else if (intersection.accessComposite().is<PointSet>())
            {
                const PointSet& pointSet = intersection.accessComposite().as<PointSet>();

                bool secondIntersectionPointAdded = false;

                for (const auto& point : pointSet)
                {
                    if (!secondIntersectionPointAdded)
                    {
                        secondIntersectionPoints.add(point);

                        secondIntersectionPointAdded = true;
                    }
                    else
                    {
                        firstIntersectionPoints.add(point);
                    }
                }
            }
        }
    }

    if ((!firstIntersectionPoints.isEmpty()) && (!secondIntersectionPoints.isEmpty()) && (!onlyInSight))
    {
        return Intersection::LineString(LineString(firstIntersectionPoints)) +
               Intersection::LineString(LineString(secondIntersectionPoints));
    }
    else if (!firstIntersectionPoints.isEmpty())
    {
        return Intersection::LineString(LineString(firstIntersectionPoints));
    }
    else if (!secondIntersectionPoints.isEmpty())
    {
        return Intersection::LineString(LineString(secondIntersectionPoints));
    }

    return Intersection::Empty();
}

Intersection Cone::intersectionWith(
    const Ellipsoid& anEllipsoid, const bool onlyInSight, const Size aDiscretizationLevel
) const
{
    if (!anEllipsoid.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone");
    }

    Array<Point> firstIntersectionPoints = Array<Point>::Empty();
    Array<Point> secondIntersectionPoints = Array<Point>::Empty();

    for (const auto& ray : this->getRaysOfLateralSurface(aDiscretizationLevel))
    {
        const Intersection intersection = ray.intersectionWith(anEllipsoid, onlyInSight);

        if (!intersection.isEmpty())
        {
            if (intersection.accessComposite().is<Point>())
            {
                firstIntersectionPoints.add(intersection.accessComposite().as<Point>());
            }
            else if (intersection.accessComposite().is<PointSet>())
            {
                const PointSet& pointSet = intersection.accessComposite().as<PointSet>();

                const Point closestPointToApex = pointSet.getPointClosestTo(apex_);

                firstIntersectionPoints.add(closestPointToApex);

                for (const auto& point : pointSet)
                {
                    if (point != closestPointToApex)
                    {
                        secondIntersectionPoints.add(point);

                        break;
                    }
                }
            }
        }
    }

    if ((!firstIntersectionPoints.isEmpty()) && (!secondIntersectionPoints.isEmpty()) && (!onlyInSight))
    {
        return Intersection::LineString(LineString(firstIntersectionPoints)) +
               Intersection::LineString(LineString(secondIntersectionPoints));
    }
    else if (!firstIntersectionPoints.isEmpty())
    {
        return Intersection::LineString(LineString(firstIntersectionPoints));
    }
    else if (!secondIntersectionPoints.isEmpty())
    {
        return Intersection::LineString(LineString(secondIntersectionPoints));
    }

    return Intersection::Empty();
}

void Cone::print(std::ostream& anOutputStream, bool displayDecorators) const
{
    displayDecorators ? ostk::core::utils::Print::Header(anOutputStream, "Cone") : void();

    ostk::core::utils::Print::Line(anOutputStream) << "Apex:" << (apex_.isDefined() ? apex_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream) << "Axis:" << (axis_.isDefined() ? axis_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Angle:" << (angle_.isDefined() ? angle_.toString() : "Undefined");

    displayDecorators ? ostk::core::utils::Print::Footer(anOutputStream) : void();
}

void Cone::applyTransformation(const Transformation& aTransformation)
{
    if (!aTransformation.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Transformation");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone");
    }

    apex_ = aTransformation.applyTo(apex_);
    axis_ = aTransformation.applyTo(axis_);

    axis_.normalize();
}

Cone Cone::Undefined()
{
    return {Point::Undefined(), Vector3d::Undefined(), Angle::Undefined()};
}

}  // namespace object
}  // namespace d3
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk
