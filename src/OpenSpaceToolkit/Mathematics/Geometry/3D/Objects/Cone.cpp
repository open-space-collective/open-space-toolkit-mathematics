// Copyright © Loft Orbital Solutions Inc.

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Cone.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Plane.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Objects/Interval.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace math
{
namespace geom
{
namespace d3
{
namespace objects
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Cone::Cone                                  (   const   Point&                      anApex,
                                                                                const   Vector3d&                   anAxis,
                                                                                const   Angle&                      anAngle                                     )
                                :   Object(),
                                    apex_(anApex),
                                    axis_(anAxis),
                                    angle_(anAngle)
{

}

Cone*                           Cone::clone                                 ( ) const
{
    return new Cone(*this) ;
}

bool                            Cone::operator ==                           (   const   Cone&                       aCone                                       ) const
{

    if ((!this->isDefined()) || (!aCone.isDefined()))
    {
        return false ;
    }

    return (apex_ == aCone.apex_)
        && (((axis_ == aCone.axis_) && (angle_ == aCone.angle_)) || ((axis_ == -aCone.axis_) && (angle_ == Angle::Degrees(180.0) - aCone.angle_))) ;

}

bool                            Cone::operator !=                           (   const   Cone&                       aCone                                       ) const
{
    return !((*this) == aCone) ;
}

bool                            Cone::isDefined                          ( ) const
{
    return apex_.isDefined() && axis_.isDefined() && angle_.isDefined() ;
}

bool                            Cone::intersects                            (   const   Sphere&                     aSphere,
                                                                                const   Size                        aDiscretizationLevel                        ) const
{

    if (!aSphere.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Sphere") ;
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone") ;
    }

    for (const auto& ray : this->getRaysOfLateralSurface(aDiscretizationLevel)) // [TBM] Could be improved by calculating rays on the fly
    {

        if (ray.intersects(aSphere))
        {
            return true ;
        }

    }

    return false ;

}

bool                            Cone::intersects                            (   const   Ellipsoid&                  anEllipsoid,
                                                                                const   Size                        aDiscretizationLevel                        ) const
{

    if (!anEllipsoid.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid") ;
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone") ;
    }

    for (const auto& ray : this->getRaysOfLateralSurface(aDiscretizationLevel)) // [TBM] Could be improved by calculating rays on the fly
    {

        if (ray.intersects(anEllipsoid))
        {
            return true ;
        }

    }

    return false ;

}

bool                            Cone::contains                              (   const   Point&                      aPoint                                      ) const
{

    if (!aPoint.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point") ;
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone") ;
    }

    if (aPoint == this->apex_)
    {
        return true ;
    }

    const Vector3d apexToPoint = aPoint - this->apex_ ;

    if (apexToPoint.dot(this->axis_) < 0.0)
    {
        return false ;
    }

    return Angle::Between(apexToPoint, this->axis_).inDegrees(0.0, 360.0) <= this->angle_.inDegrees(0.0, 360.0) ;

}

bool                            Cone::contains                              (   const   PointSet&                   aPointSet                                   ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone") ;
    }

    return std::all_of
    (
        std::begin(aPointSet),
        std::end(aPointSet),
        [this] (const Point& aPoint) -> bool
        {
            return this->contains(aPoint) ;
        }
    ) ;

}

bool                            Cone::contains                              (   const   Segment&                    aSegment                                    ) const
{
    return this->contains(aSegment.getFirstPoint()) && this->contains(aSegment.getSecondPoint()) ;
}

bool                            Cone::contains                              (   const   Ray&                        aRay                                        ) const
{

    if (!aRay.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ray") ;
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone") ;
    }

    if (!this->contains(aRay.getOrigin()))
    {
        return false ;
    }

    return Angle::Between(aRay.getDirection(), this->axis_).inDegrees(0.0, 360.0) <= this->angle_.inDegrees(0.0, 360.0) ;

}

bool                            Cone::contains                              (   const   Sphere&                     aSphere                                     ) const
{

    if (!aSphere.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Sphere") ;
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone") ;
    }

    return this->contains(aSphere.getCenter()) && (this->distanceTo(aSphere.getCenter()) >= aSphere.getRadius()) ;

}

bool                            Cone::contains                              (   const   Ellipsoid&                  anEllipsoid                                 ) const
{

    if (!anEllipsoid.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid") ;
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone") ;
    }

    throw ostk::core::error::runtime::ToBeImplemented("Cone::contains(const Ellipsoid&)") ;

    return false ; // TBI

}

Point                           Cone::getApex                               ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone") ;
    }

    return apex_ ;

}

Vector3d                        Cone::getAxis                              ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone") ;
    }

    return axis_ ;

}

Angle                           Cone::getAngle                              ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone") ;
    }

    return angle_ ;

}

Array<Ray>                      Cone::getRaysOfLateralSurface               (   const   Size                        aRayCount                                   ) const
{

    using ostk::math::obj::Interval ;
    using ostk::math::geom::d3::trf::rot::Quaternion ;
    using ostk::math::geom::d3::trf::rot::RotationVector ;

    if (aRayCount == 0)
    {
        throw ostk::core::error::runtime::Wrong("Ray count") ;
    }

    const Vector3d referenceDirection = (std::abs(axis_.dot(Vector3d::X())) < 0.5) ? axis_.cross(Vector3d::X()).normalized() : axis_.cross(Vector3d::Y()).normalized() ;

    const Ray referenceRay = { apex_, Quaternion::RotationVector(RotationVector(referenceDirection, angle_)).toConjugate() * axis_ } ;

    const Array<Real> angles_rad = (aRayCount > 1) ? Interval<Real>::HalfOpenRight(0.0, 360.0).generateArrayWithSize(aRayCount) : Array<Real> { 0.0 } ;

    Array<Ray> rays = Array<Ray>::Empty() ;

    rays.reserve(angles_rad.getSize()) ;

    for (const auto& angle_rad : angles_rad)
    {

        const Angle angle = Angle::Degrees(angle_rad) ;

        const Ray ray = { apex_, Quaternion::RotationVector(RotationVector(axis_, angle)).toConjugate() * referenceRay.getDirection() } ;

        rays.add(ray) ;

    }

    return rays ;

}

Real                            Cone::distanceTo                            (   const   Point&                      aPoint                                      ) const
{

    if (!aPoint.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point") ;
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone") ;
    }

    if (aPoint == this->apex_)
    {
        return 0.0 ;
    }

    const Vector3d apexToPoint = aPoint - this->apex_ ;

    if (apexToPoint.dot(this->axis_) < 0.0)
    {
        return apexToPoint.norm() ;
    }

    // TBO: There's probably a better way to do this that doesn't require the use of so many vector re-normalization.

    Vector3d nAxis ;

    if (this->axis_.cross(apexToPoint).norm() > Real::Epsilon())
    {
        nAxis = (this->axis_.cross(apexToPoint)).cross(this->axis_).normalized() ;
    }
    else
    {

        if (this->axis_.cross(Vector3d { 1.0, 0.0, 0.0 }).norm() > Real::Epsilon())
        {
            nAxis = (this->axis_.cross(Vector3d { 1.0, 0.0, 0.0 })).cross(this->axis_).normalized() ;
        }
        else
        {
            nAxis = (this->axis_.cross(Vector3d { 0.0, 1.0, 0.0 })).cross(this->axis_).normalized() ;
        }

    }

    const Vector3d rayDirection = (this->axis_.normalized() + std::tan(this->angle_.inRadians()) * nAxis).normalized() ;

    return Ray(this->apex_, rayDirection).distanceTo(aPoint) ;

}

Intersection                    Cone::intersectionWith                      (   const   Sphere&                     aSphere,
                                                                                const   bool                        onlyInSight,
                                                                                const   Size                        aDiscretizationLevel                        ) const
{

    if (!aSphere.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Sphere") ;
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone") ;
    }

    Array<Point> firstIntersectionPoints = Array<Point>::Empty() ;
    Array<Point> secondIntersectionPoints = Array<Point>::Empty() ;

    for (const auto& ray : this->getRaysOfLateralSurface(aDiscretizationLevel))
    {

        const Intersection intersection = ray.intersectionWith(aSphere, onlyInSight) ;

        if (!intersection.isEmpty())
        {

            if (intersection.accessComposite().is<Point>())
            {
                firstIntersectionPoints.add(intersection.accessComposite().as<Point>()) ;
            }
            else if (intersection.accessComposite().is<PointSet>())
            {

                const PointSet& pointSet = intersection.accessComposite().as<PointSet>() ;

                bool secondIntersectionPointAdded = false ;

                for (const auto& point : pointSet)
                {

                    if (!secondIntersectionPointAdded)
                    {

                        secondIntersectionPoints.add(point) ;

                        secondIntersectionPointAdded = true ;

                    }
                    else
                    {
                        firstIntersectionPoints.add(point) ;
                    }

                }

            }

        }

    }

    if ((!firstIntersectionPoints.isEmpty()) && (!secondIntersectionPoints.isEmpty()) && (!onlyInSight))
    {
        return Intersection::LineString(LineString(firstIntersectionPoints)) + Intersection::LineString(LineString(secondIntersectionPoints)) ;
    }
    else if (!firstIntersectionPoints.isEmpty())
    {
        return Intersection::LineString(LineString(firstIntersectionPoints)) ;
    }
    else if (!secondIntersectionPoints.isEmpty())
    {
        return Intersection::LineString(LineString(secondIntersectionPoints)) ;
    }

    return Intersection::Empty() ;

}

Intersection                    Cone::intersectionWith                      (   const   Ellipsoid&                  anEllipsoid,
                                                                                const   bool                        onlyInSight,
                                                                                const   Size                        aDiscretizationLevel                        ) const
{

    if (!anEllipsoid.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid") ;
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone") ;
    }

    Array<Point> firstIntersectionPoints = Array<Point>::Empty() ;
    Array<Point> secondIntersectionPoints = Array<Point>::Empty() ;

    for (const auto& ray : this->getRaysOfLateralSurface(aDiscretizationLevel))
    {

        const Intersection intersection = ray.intersectionWith(anEllipsoid, onlyInSight) ;

        if (!intersection.isEmpty())
        {

            if (intersection.accessComposite().is<Point>())
            {
                firstIntersectionPoints.add(intersection.accessComposite().as<Point>()) ;
            }
            else if (intersection.accessComposite().is<PointSet>())
            {

                const PointSet& pointSet = intersection.accessComposite().as<PointSet>() ;

                const Point closestPointToApex = pointSet.getPointClosestTo(apex_) ;

                firstIntersectionPoints.add(closestPointToApex) ;

                for (const auto& point : pointSet)
                {

                    if (point != closestPointToApex)
                    {

                        secondIntersectionPoints.add(point) ;

                        break ;

                    }

                }

            }

        }

    }

    if ((!firstIntersectionPoints.isEmpty()) && (!secondIntersectionPoints.isEmpty()) && (!onlyInSight))
    {
        return Intersection::LineString(LineString(firstIntersectionPoints)) + Intersection::LineString(LineString(secondIntersectionPoints)) ;
    }
    else if (!firstIntersectionPoints.isEmpty())
    {
        return Intersection::LineString(LineString(firstIntersectionPoints)) ;
    }
    else if (!secondIntersectionPoints.isEmpty())
    {
        return Intersection::LineString(LineString(secondIntersectionPoints)) ;
    }

    return Intersection::Empty() ;

}

void                            Cone::print                                 (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           ) const
{

    displayDecorators ? ostk::core::utils::Print::Header(anOutputStream, "Cone") : void () ;

    ostk::core::utils::Print::Line(anOutputStream) << "Apex:"                << (apex_.isDefined() ? apex_.toString() : "Undefined") ;
    ostk::core::utils::Print::Line(anOutputStream) << "Axis:"                << (axis_.isDefined() ? axis_.toString() : "Undefined") ;
    ostk::core::utils::Print::Line(anOutputStream) << "Angle:"               << (angle_.isDefined() ? angle_.toString() : "Undefined") ;

    displayDecorators ? ostk::core::utils::Print::Footer(anOutputStream) : void () ;

}

void                            Cone::applyTransformation                   (   const   Transformation&             aTransformation                             )
{

    if (!aTransformation.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Transformation") ;
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Cone") ;
    }

    apex_ = aTransformation.applyTo(apex_) ;
    axis_ = aTransformation.applyTo(axis_) ;

    axis_.normalize() ;

}

Cone                            Cone::Undefined                             ( )
{
    return { Point::Undefined(), Vector3d::Undefined(), Angle::Undefined() } ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
