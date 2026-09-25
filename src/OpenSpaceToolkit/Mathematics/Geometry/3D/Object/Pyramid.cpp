/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Plane.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Pyramid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ray.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Sphere.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wint-in-bool-context"

#include <Eigen/Cholesky>

#pragma GCC diagnostic pop

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
/// This is the rotation Quaternion::RotationVector(RotationVector(axis, angle)).conjugate() applies to a vector,
/// evaluated directly instead of through two quaternion products.
Vector3d PyramidRotateVector(
    const Vector3d& aVector, const Vector3d& aUnitAxis, const double aCosine, const double aSine
)
{
    return (aCosine * aVector) + (aSine * aUnitAxis.cross(aVector)) +
           (((1.0 - aCosine) * aUnitAxis.dot(aVector)) * aUnitAxis);
}

/// Lateral face filter that keeps every face.
bool PyramidKeepLateralFace(const Vector3d& aFirstRayDirection, const Vector3d& aSecondRayDirection)
{
    (void)aFirstRayDirection;
    (void)aSecondRayDirection;

    return true;
}

/// Whether a ray from an apex, with a direction in the wedge spanned by two directions, can intersect the unit ball
/// centered at the origin.
///
/// The rays of a lateral face all have their directions in the wedge spanned by the face's first and last rays. The
/// face's rays can only intersect the unit ball if the wedge {apex + s * first + t * second, s >= 0, t >= 0} does, that
/// is if the distance from the origin to the wedge is at most one: the distance to the wedge's plane when the origin
/// projects inside the wedge, and to the closer of its two boundary rays otherwise.
///
/// Returns true when in doubt, and for directions less than a microradian apart.
bool PyramidWedgeMayIntersectUnitBall(
    const Vector3d& anApex, const Vector3d& aFirstDirection, const Vector3d& aSecondDirection
)
{
    // Slack for the rounding of the rays and of the ray tests, which grows with the apex distance

    const double margin = 1e-9 + 1e-15 * anApex.squaredNorm();
    const double squaredMaximumDistance = (1.0 + margin) * (1.0 + margin);

    const auto squaredDistanceToRay = [&anApex](const Vector3d& aUnitDirection) -> double
    {
        return (anApex + std::max(0.0, -anApex.dot(aUnitDirection)) * aUnitDirection).squaredNorm();
    };

    const Vector3d firstDirection = aFirstDirection.normalized();
    const Vector3d secondDirection = aSecondDirection.normalized();

    const double squaredDistanceToBoundary =
        std::min(squaredDistanceToRay(firstDirection), squaredDistanceToRay(secondDirection));

    if (!(squaredDistanceToBoundary > squaredMaximumDistance))
    {
        return true;
    }

    const Vector3d normal = firstDirection.cross(secondDirection);

    if (!(normal.norm() > 1e-6))
    {
        return true;
    }

    const Vector3d unitNormal = normal.normalized();

    // Origin projected onto the wedge's plane, relative to the apex, against the two boundary directions

    const Vector3d projection = -anApex + unitNormal.dot(anApex) * unitNormal;

    const bool isInsideWedge = (firstDirection.cross(projection).dot(unitNormal) >= 0.0) &&
                               (projection.cross(secondDirection).dot(unitNormal) >= 0.0);

    if (!isInsideWedge)
    {
        return false;
    }

    const double distanceToPlane = unitNormal.dot(anApex);

    return !((distanceToPlane * distanceToPlane) > squaredMaximumDistance);
}

/// Lateral face filter keeping the faces whose rays can intersect the solid mapped onto the unit ball by
/// x -> aLinearMap * (x - aCenter).
///
/// The map is affine, so it takes rays to rays and a face's wedge to a wedge: a ray intersects the solid if and only if
/// its image intersects the unit ball.
auto PyramidLateralFaceFilter(const Point& anApex, const Matrix3d& aLinearMap, const Vector3d& aCenter)
{
    const Vector3d apex = aLinearMap * (anApex.asVector() - aCenter);

    return [apex, aLinearMap](const Vector3d& aFirstRayDirection, const Vector3d& aSecondRayDirection) -> bool
    {
        return PyramidWedgeMayIntersectUnitBall(
            apex, aLinearMap * aFirstRayDirection, aLinearMap * aSecondRayDirection
        );
    };
}

/// Lateral face filter keeping the faces whose rays can intersect a sphere.
auto PyramidLateralFaceFilter(const Point& anApex, const Sphere& aSphere)
{
    return PyramidLateralFaceFilter(anApex, Matrix3d::Identity() / aSphere.getRadius(), aSphere.getCenter().asVector());
}

/// Lateral face filter keeping the faces whose rays can intersect an ellipsoid.
auto PyramidLateralFaceFilter(const Point& anApex, const Ellipsoid& anEllipsoid)
{
    // The ellipsoid is (x - c)^T * M * (x - c) <= 1, so any L with L^T * L = M, such as the transpose of the Cholesky
    // factor of M, maps it onto the unit ball

    const Matrix3d matrix = anEllipsoid.getMatrix();

    const Eigen::LLT<Matrix3d> cholesky(matrix);

    if (cholesky.info() != Eigen::Success)  // Degenerate ellipsoid: keep every face
    {
        return PyramidLateralFaceFilter(
            anApex, Matrix3d::Constant(std::numeric_limits<double>::quiet_NaN()), Vector3d::Zero()
        );
    }

    return PyramidLateralFaceFilter(
        anApex, Matrix3d(cholesky.matrixL().transpose()), anEllipsoid.getCenter().asVector()
    );
}

/// Visits the rays of a lateral face of a pyramid, in the order Pyramid::getRaysOfLateralFaceAt returns them, until the
/// visitor returns false. The face is skipped when the filter, given the directions of its first and last rays,
/// returns false.
template <typename FaceFilter, typename Visitor>
void PyramidVisitRaysOfLateralFace(
    const Point& anApex, const Segment& aBaseEdge, const Size aRayCount, FaceFilter&& aFaceFilter, Visitor&& aVisitor
)
{
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;

    const Vector3d firstRayDirection = (aBaseEdge.getFirstPoint() - anApex).normalized();
    const Vector3d secondRayDirection = (aBaseEdge.getSecondPoint() - anApex).normalized();

    if (firstRayDirection == secondRayDirection)
    {
        if (aFaceFilter(firstRayDirection, secondRayDirection))
        {
            aVisitor(Ray(anApex, firstRayDirection));
        }

        return;
    }

    // The rotation vector validates and normalizes the rotation axis, and throws for an axis that is not unitary.

    const Vector3d rotationAxis =
        RotationVector(firstRayDirection.cross(secondRayDirection).normalized(), Angle::Zero()).getAxis();

    if (!aFaceFilter(firstRayDirection, secondRayDirection))
    {
        return;
    }

    // Same angles as Interval<Real>::Closed(0.0, angleBetweenRays).generateArrayWithSize(aRayCount)

    const double angleBetweenRays_rad = Angle::Between(firstRayDirection, secondRayDirection).inRadians();

    const Size rayCount = (aRayCount > 1) ? aRayCount : 1;
    const double angleStep_rad = (aRayCount > 1) ? (angleBetweenRays_rad / static_cast<double>(aRayCount - 1)) : 0.0;

    double rayAngle_rad = 0.0;

    for (Size rayIndex = 0; rayIndex < rayCount; ++rayIndex, rayAngle_rad += angleStep_rad)
    {
        const Ray ray = {
            anApex, PyramidRotateVector(firstRayDirection, rotationAxis, std::cos(rayAngle_rad), std::sin(rayAngle_rad))
        };

        if (!aVisitor(ray))
        {
            return;
        }
    }
}

/// Visits the rays of all lateral faces of a pyramid, in the order Pyramid::getRaysOfLateralFaces returns them, until
/// the visitor returns false. The faces for which the filter returns false are skipped.
template <typename FaceFilter, typename Visitor>
void PyramidVisitRaysOfLateralFaces(
    const Point& anApex,
    const Polygon& aBase,
    const Size aLateralFaceCount,
    const Size aRayCount,
    FaceFilter&& aFaceFilter,
    Visitor&& aVisitor
)
{
    if (aRayCount < aLateralFaceCount)
    {
        throw ostk::core::error::RuntimeError(
            "Ray count [{}] lower than lateral face count [{}].", aRayCount, aLateralFaceCount
        );
    }

    const Size lateralRayCount = aRayCount / aLateralFaceCount;

    bool isVisiting = true;

    for (Index lateralFaceIndex = 0; isVisiting && (lateralFaceIndex < aLateralFaceCount); ++lateralFaceIndex)
    {
        PyramidVisitRaysOfLateralFace(
            anApex,
            aBase.getEdgeAt(lateralFaceIndex),
            lateralRayCount,
            aFaceFilter,
            [&aVisitor, &isVisiting](const Ray& aRay) -> bool
            {
                isVisiting = aVisitor(aRay);

                return isVisiting;
            }
        );
    }
}

Pyramid::Pyramid(const Polygon& aBase, const Point& anApex)
    : Object(),
      base_(aBase),
      apex_(anApex)
{
}

Pyramid* Pyramid::clone() const
{
    return new Pyramid(*this);
}

bool Pyramid::operator==(const Pyramid& aPyramid) const
{
    if ((!this->isDefined()) || (!aPyramid.isDefined()))
    {
        return false;
    }

    return (base_ == aPyramid.base_) && (apex_ == aPyramid.apex_);
}

bool Pyramid::operator!=(const Pyramid& aPyramid) const
{
    return !((*this) == aPyramid);
}

bool Pyramid::isDefined() const
{
    return base_.isDefined() && apex_.isDefined();
}

bool Pyramid::intersects(const Sphere& aSphere, const Size aDiscretizationLevel) const
{
    if (!aSphere.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Sphere");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Pyramid");
    }

    bool intersects = false;

    PyramidVisitRaysOfLateralFaces(
        apex_,
        base_,
        this->getLateralFaceCount(),
        aDiscretizationLevel,
        PyramidLateralFaceFilter(apex_, aSphere),
        [&aSphere, &intersects](const Ray& aRay) -> bool
        {
            intersects = aRay.intersects(aSphere);

            return !intersects;
        }
    );

    return intersects;
}

bool Pyramid::intersects(const Ellipsoid& anEllipsoid, const Size aDiscretizationLevel) const
{
    if (!anEllipsoid.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Pyramid");
    }

    bool intersects = false;

    PyramidVisitRaysOfLateralFaces(
        apex_,
        base_,
        this->getLateralFaceCount(),
        aDiscretizationLevel,
        PyramidLateralFaceFilter(apex_, anEllipsoid),
        [&anEllipsoid, &intersects](const Ray& aRay) -> bool
        {
            intersects = aRay.intersects(anEllipsoid);

            return !intersects;
        }
    );

    return intersects;
}

bool Pyramid::contains(const Point& aPoint) const
{
    using Point2d = ostk::mathematics::geometry::d2::object::Point;

    if (!aPoint.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Pyramid");
    }

    if (aPoint == apex_)
    {
        return true;
    }

    // Projection of the point onto the pyramid base plane, along the apex to point ray (as Ray::intersectionWith(Plane)
    // computes it, without building an Intersection)

    const Vector3d baseXAxis = base_.getXAxis();
    const Vector3d baseYAxis = base_.getYAxis();

    const Ray apexToPointRay = {apex_, aPoint - apex_};

    const Plane basePlane = {base_.getOrigin(), baseXAxis.cross(baseYAxis).normalized()};

    const Vector3d rayDirection = apexToPointRay.getDirection();
    const Vector3d baseNormal = basePlane.getNormalVector();
    const Vector3d baseOrigin = basePlane.getPoint().asVector();
    const Vector3d apex = apex_.asVector();

    const double normalDotDirection = baseNormal.dot(rayDirection);

    if (normalDotDirection == 0.0)  // Ray and base plane are parallel
    {
        if (baseNormal.dot(baseOrigin - apex) == 0.0)  // Ray is in the base plane
        {
            throw ostk::core::error::RuntimeError("Pyramid is degenerate.");
        }

        return false;
    }

    const double t = baseNormal.dot(baseOrigin - apex) / normalDotDirection;

    if (t < 0.0)
    {
        return false;
    }

    const Vector3d intersectionPoint = apex + t * rayDirection;

    // Coordinates of the intersection point in the pyramid base frame

    const Vector3d baseOriginToIntersectionPoint = intersectionPoint - baseOrigin;

    const Point2d projectedPoint = {
        baseXAxis.dot(baseOriginToIntersectionPoint), baseYAxis.dot(baseOriginToIntersectionPoint)
    };

    // Query if projected point is within polygonal base

    return base_.getPolygon2d().contains(projectedPoint);
}

bool Pyramid::contains(const PointSet& aPointSet) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Pyramid");
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

bool Pyramid::contains(const Segment& aSegment) const
{
    return this->contains(aSegment.getFirstPoint()) && this->contains(aSegment.getSecondPoint());
}

bool Pyramid::contains(const Ellipsoid& anEllipsoid) const
{
    if (!anEllipsoid.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Pyramid");
    }

    throw ostk::core::error::runtime::ToBeImplemented("Pyramid");

    return false;
}

Polygon Pyramid::getBase() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Pyramid");
    }

    return base_;
}

Point Pyramid::getApex() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Pyramid");
    }

    return apex_;
}

Size Pyramid::getLateralFaceCount() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Pyramid");
    }

    return base_.getEdgeCount();
}

Polygon Pyramid::getLateralFaceAt(const Index aLateralFaceIndex) const
{
    using ostk::mathematics::object::Vector2d;
    using Point2d = ostk::mathematics::geometry::d2::object::Point;

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Pyramid");
    }

    const Segment baseEdge = base_.getEdgeAt(aLateralFaceIndex);

    const Vector3d firstDirection = (baseEdge.getFirstPoint() - apex_).normalized();
    const Vector3d secondDirection = (baseEdge.getSecondPoint() - apex_).normalized();

    const Vector3d firstAxis = firstDirection;
    const Vector3d secondAxis = (firstAxis.cross(secondDirection)).cross(firstAxis).normalized();

    const Vector3d baseEdgeVector = baseEdge.getSecondPoint() - baseEdge.getFirstPoint();

    const Point2d firstPolygonPoint = {0.0, 0.0};
    const Point2d secondPolygonPoint = {(baseEdge.getFirstPoint() - apex_).norm(), 0.0};
    const Point2d thirdPolygonPoint =
        secondPolygonPoint + Vector2d {baseEdgeVector.dot(firstAxis), baseEdgeVector.dot(secondAxis)};

    const Polygon2d polygon = {{firstPolygonPoint, secondPolygonPoint, thirdPolygonPoint}};

    return {polygon, apex_, firstAxis, secondAxis};
}

Array<Ray> Pyramid::getRaysOfLateralFaceAt(const Index aLateralFaceIndex, const Size aRayCount) const
{
    Array<Ray> rays = Array<Ray>::Empty();

    rays.reserve((aRayCount > 1) ? aRayCount : 1);

    PyramidVisitRaysOfLateralFace(
        apex_,
        base_.getEdgeAt(aLateralFaceIndex),
        aRayCount,
        PyramidKeepLateralFace,
        [&rays](const Ray& aRay) -> bool
        {
            rays.add(aRay);

            return true;
        }
    );

    return rays;
}

Array<Ray> Pyramid::getRaysOfLateralFaces(const Size aRayCount) const
{
    const Size lateralFaceCount = this->getLateralFaceCount();

    Array<Ray> rays = Array<Ray>::Empty();

    rays.reserve(aRayCount);

    // [TBM] Double counting rays: adjacent lateral faces both return the ray through their shared base vertex

    PyramidVisitRaysOfLateralFaces(
        apex_,
        base_,
        lateralFaceCount,
        aRayCount,
        PyramidKeepLateralFace,
        [&rays](const Ray& aRay) -> bool
        {
            rays.add(aRay);

            return true;
        }
    );

    return rays;
}

Intersection Pyramid::intersectionWith(const Sphere& aSphere, const bool onlyInSight, const Size aDiscretizationLevel)
    const
{
    if (!aSphere.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Sphere");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Pyramid");
    }

    Array<Point> firstIntersectionPoints = Array<Point>::Empty();
    Array<Point> secondIntersectionPoints = Array<Point>::Empty();

    PyramidVisitRaysOfLateralFaces(
        apex_,
        base_,
        this->getLateralFaceCount(),
        aDiscretizationLevel,
        PyramidLateralFaceFilter(apex_, aSphere),
        [&aSphere, onlyInSight, &firstIntersectionPoints, &secondIntersectionPoints](const Ray& aRay) -> bool
        {
            const Intersection intersection = aRay.intersectionWith(aSphere, onlyInSight);

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

            return true;
        }
    );

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

Intersection Pyramid::intersectionWith(
    const Ellipsoid& anEllipsoid, const bool onlyInSight, const Size aDiscretizationLevel
) const
{
    if (!anEllipsoid.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Pyramid");
    }

    Array<Point> firstIntersectionPoints = Array<Point>::Empty();
    Array<Point> secondIntersectionPoints = Array<Point>::Empty();

    PyramidVisitRaysOfLateralFaces(
        apex_,
        base_,
        this->getLateralFaceCount(),
        aDiscretizationLevel,
        PyramidLateralFaceFilter(apex_, anEllipsoid),
        [this, &anEllipsoid, onlyInSight, &firstIntersectionPoints, &secondIntersectionPoints](const Ray& aRay) -> bool
        {
            const Intersection intersection = aRay.intersectionWith(anEllipsoid, onlyInSight);

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

                    // firstIntersectionPoints.add(pointSet.getPointClosestTo(apex_)) ;

                    // bool secondIntersectionPointAdded = false ;

                    // for (const auto& point : pointSet)
                    // {

                    //     if (!secondIntersectionPointAdded)
                    //     {

                    //         secondIntersectionPoints.add(point) ;

                    //         secondIntersectionPointAdded = true ;

                    //     }
                    //     else
                    //     {
                    //         firstIntersectionPoints.add(point) ;
                    //     }

                    // }
                }
            }

            return true;
        }
    );

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

void Pyramid::print(std::ostream& anOutputStream, bool displayDecorators) const
{
    displayDecorators ? ostk::core::utils::Print::Header(anOutputStream, "Pyramid") : void();

    ostk::core::utils::Print::Line(anOutputStream) << "Apex:" << (apex_.isDefined() ? apex_.toString() : "Undefined");

    ostk::core::utils::Print::Separator(anOutputStream, "Base:");

    base_.print(anOutputStream, false);

    displayDecorators ? ostk::core::utils::Print::Footer(anOutputStream) : void();
}

void Pyramid::applyTransformation(const Transformation& aTransformation)
{
    if (!aTransformation.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Transformation");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Pyramid");
    }

    base_.applyTransformation(aTransformation);
    apex_.applyTransformation(aTransformation);
}

Pyramid Pyramid::Undefined()
{
    return {Polygon::Undefined(), Point::Undefined()};
}

}  // namespace object
}  // namespace d3
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk
