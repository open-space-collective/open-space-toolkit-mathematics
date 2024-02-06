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
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationMatrix.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Interval.hpp>

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

    for (const auto& ray :
         this->getRaysOfLateralFaces(aDiscretizationLevel))  // [TBM] Could be improved by calculating rays on the fly
    {
        if (ray.intersects(aSphere))
        {
            return true;
        }
    }

    return false;
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

    for (const auto& ray :
         this->getRaysOfLateralFaces(aDiscretizationLevel))  // [TBM] Could be improved by calculating rays on the fly
    {
        if (ray.intersects(anEllipsoid))
        {
            return true;
        }
    }

    return false;
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

    // Projection of the point onto the pyramid base plane, along the apex to point ray

    const Ray apexToPointRay = {apex_, aPoint - apex_};

    const Plane basePlane = {base_.getOrigin(), base_.getNormalVector()};

    const Intersection rayPlaneIntersection = apexToPointRay.intersectionWith(basePlane);

    if (rayPlaneIntersection.isEmpty())
    {
        return false;
    }

    if (!rayPlaneIntersection.is<Point>())
    {
        throw ostk::core::error::RuntimeError("Pyramid is degenerate.");
    }

    const Point intersectionPoint = rayPlaneIntersection.as<Point>();

    // Convert intersection point into pyramid base frame

    const Transformation translation = Transformation::Translation(-base_.getOrigin().asVector());

    const Vector3d baseXAxis = base_.getXAxis();
    const Vector3d baseYAxis = base_.getYAxis();
    const Vector3d baseZAxis = base_.getNormalVector();

    const RotationMatrix rotationMatrix = RotationMatrix::Columns(baseXAxis, baseYAxis, baseZAxis);

    const Transformation rotation = Transformation::Rotation(rotationMatrix);

    const Transformation combinedTransformation = rotation * translation;

    const Point transformedPoint = combinedTransformation.applyTo(intersectionPoint);

    const Point2d projectedPoint = {transformedPoint.x(), transformedPoint.y()};

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
    using ostk::mathematics::object::Interval;
    using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;

    // if (aRayCount < 2)
    // {
    //     throw ostk::core::error::RuntimeError("Ray count [{}] lower than 2.", aRayCount) ;
    // }

    const Segment baseEdge = base_.getEdgeAt(aLateralFaceIndex);

    const Vector3d firstRayDirection = (baseEdge.getFirstPoint() - apex_).normalized();
    const Vector3d secondRayDirection = (baseEdge.getSecondPoint() - apex_).normalized();

    if (firstRayDirection == secondRayDirection)
    {
        return {{apex_, firstRayDirection}};
    }

    const Vector3d rotationAxis = firstRayDirection.cross(secondRayDirection).normalized();

    const Angle angleBetweenRays = Angle::Between(firstRayDirection, secondRayDirection);

    const Array<Real> angles_rad =
        (aRayCount > 1) ? Interval<Real>::Closed(0.0, angleBetweenRays.inRadians()).generateArrayWithSize(aRayCount)
                        : Array<Real> {0.0};

    Array<Ray> rays = Array<Ray>::Empty();

    rays.reserve(angles_rad.getSize());

    for (const auto& angle_rad : angles_rad)
    {
        const Ray ray = {
            apex_,
            Quaternion::RotationVector(RotationVector(rotationAxis, Angle::Radians(angle_rad))).conjugate() *
                firstRayDirection
        };

        rays.emplace_back(ray);
    }

    return rays;
}

Array<Ray> Pyramid::getRaysOfLateralFaces(const Size aRayCount) const
{
    if (aRayCount < this->getLateralFaceCount())
    {
        throw ostk::core::error::RuntimeError(
            "Ray count [{}] lower than lateral face count [{}].", aRayCount, this->getLateralFaceCount()
        );
    }

    Size lateralRayCount = aRayCount / this->getLateralFaceCount();

    Array<Ray> rays = Array<Ray>::Empty();

    for (Index lateralFaceIndex = 0; lateralFaceIndex < this->getLateralFaceCount(); ++lateralFaceIndex)
    {
        const Array<Ray> lateralFaceRays = this->getRaysOfLateralFaceAt(lateralFaceIndex, lateralRayCount);

        // [TBM] Double counting rays

        rays.add(lateralFaceRays);
    }

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

    for (const auto& ray : this->getRaysOfLateralFaces(aDiscretizationLevel))
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

    for (const auto& ray : this->getRaysOfLateralFaces(aDiscretizationLevel))
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
