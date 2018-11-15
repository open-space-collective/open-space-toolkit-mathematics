////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Pyramid.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp>
#include <Library/Mathematics/Geometry/3D/Intersection.hpp>
#include <Library/Mathematics/Geometry/3D/Transformation.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Pyramid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Plane.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <Library/Mathematics/Geometry/2D/Objects/Polygon.hpp>
#include <Library/Mathematics/Geometry/2D/Objects/Point.hpp>
#include <Library/Mathematics/Objects/Interval.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
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

                                Pyramid::Pyramid                            (   const   Polygon&                    aBase,
                                                                                const   Point&                      anApex                                      )
                                :   Object(),
                                    base_(aBase),
                                    apex_(anApex)
{

}

Pyramid*                        Pyramid::clone                              ( ) const
{
    return new Pyramid(*this) ;
}

bool                            Pyramid::operator ==                        (   const   Pyramid&                    aPyramid                                    ) const
{

    if ((!this->isDefined()) || (!aPyramid.isDefined()))
    {
        return false ;
    }

    return (base_ == aPyramid.base_) && (apex_ == aPyramid.apex_) ;

}

bool                            Pyramid::operator !=                        (   const   Pyramid&                    aPyramid                                    ) const
{
    return !((*this) == aPyramid) ;
}

bool                            Pyramid::isDefined                          ( ) const
{
    return base_.isDefined() && apex_.isDefined() ;
}

bool                            Pyramid::intersects                         (   const   Sphere&                     aSphere,
                                                                                const   Size                        aDiscretizationLevel                        ) const
{

    if (!aSphere.isDefined())
    {
        throw library::core::error::runtime::Undefined("Sphere") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Pyramid") ;
    }

    for (const auto& ray : this->getRaysOfLateralFaces(aDiscretizationLevel)) // [TBM] Could be improved by calculating rays on the fly
    {

        if (ray.intersects(aSphere))
        {
            return true ;
        }

    }

    return false ;

}

bool                            Pyramid::intersects                         (   const   Ellipsoid&                  anEllipsoid,
                                                                                const   Size                        aDiscretizationLevel                        ) const
{

    if (!anEllipsoid.isDefined())
    {
        throw library::core::error::runtime::Undefined("Ellipsoid") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Pyramid") ;
    }

    for (const auto& ray : this->getRaysOfLateralFaces(aDiscretizationLevel)) // [TBM] Could be improved by calculating rays on the fly
    {

        if (ray.intersects(anEllipsoid))
        {
            return true ;
        }

    }

    return false ;

}

bool                            Pyramid::contains                           (   const   Ellipsoid&                  anEllipsoid                                 ) const
{

    if (!anEllipsoid.isDefined())
    {
        throw library::core::error::runtime::Undefined("Ellipsoid") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Pyramid") ;
    }

    throw library::core::error::runtime::ToBeImplemented("Pyramid") ;

    return false ;

}

Polygon                         Pyramid::getBase                            ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Pyramid") ;
    }

    return base_ ;

}

Point                           Pyramid::getApex                            ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Pyramid") ;
    }

    return apex_ ;

}

Size                            Pyramid::getLateralFaceCount                ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Pyramid") ;
    }

    return base_.getEdgeCount() ;

}

Polygon                         Pyramid::getLateralFaceAt                   (   const   Index                       aLateralFaceIndex                           ) const
{

    using library::math::obj::Vector2d ;
    using Point2d = library::math::geom::d2::objects::Point ;

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Pyramid") ;
    }

    const Segment baseEdge = base_.getEdgeAt(aLateralFaceIndex) ;

    const Vector3d firstDirection = (baseEdge.getFirstPoint() - apex_).normalized() ;
    const Vector3d secondDirection = (baseEdge.getSecondPoint() - apex_).normalized() ;

    const Vector3d firstAxis = firstDirection ;
    const Vector3d secondAxis = (firstAxis.cross(secondDirection)).cross(firstAxis).normalized() ;

    const Vector3d baseEdgeVector = baseEdge.getSecondPoint() - baseEdge.getFirstPoint() ;

    const Point2d firstPolygonPoint = { 0.0, 0.0 } ;
    const Point2d secondPolygonPoint = { (baseEdge.getFirstPoint() - apex_).norm(), 0.0 } ;
    const Point2d thirdPolygonPoint = secondPolygonPoint + Vector2d { baseEdgeVector.dot(firstAxis), baseEdgeVector.dot(secondAxis) } ;

    const Polygon2d polygon = { { firstPolygonPoint, secondPolygonPoint, thirdPolygonPoint } } ;

    return { polygon, apex_, firstAxis, secondAxis } ;

}

Array<Ray>                      Pyramid::getRaysOfLateralFaceAt             (   const   Index                       aLateralFaceIndex,
                                                                                const   Size                        aRayCount                                   ) const
{

    using library::math::obj::Interval ;
    using library::math::geom::d3::trf::rot::Quaternion ;
    using library::math::geom::d3::trf::rot::RotationVector ;

    // if (aRayCount < 2)
    // {
    //     throw library::core::error::RuntimeError("Ray count [{}] lower than 2.", aRayCount) ;
    // }

    const Segment baseEdge = base_.getEdgeAt(aLateralFaceIndex) ;

    const Vector3d firstRayDirection = (baseEdge.getFirstPoint() - apex_).normalized() ;
    const Vector3d secondRayDirection = (baseEdge.getSecondPoint() - apex_).normalized() ;

    if (firstRayDirection == secondRayDirection)
    {
        return { { apex_, firstRayDirection } } ;
    }

    const Vector3d rotationAxis = firstRayDirection.cross(secondRayDirection).normalized() ;

    const Angle angleBetweenRays = Angle::Between(firstRayDirection, secondRayDirection) ;

    const Array<Real> angles_rad = (aRayCount > 1) ? Interval<Real>::Closed(0.0, angleBetweenRays.inRadians()).generateArrayWithSize(aRayCount) : Array<Real> { 0.0 } ;

    Array<Ray> rays = Array<Ray>::Empty() ;

    rays.reserve(angles_rad.getSize()) ;

    for (const auto& angle_rad : angles_rad)
    {

        const Ray ray = { apex_, Quaternion::RotationVector(RotationVector(rotationAxis, Angle::Radians(angle_rad))).conjugate() * firstRayDirection } ;

        rays.emplace_back(ray) ;

    }

    return rays ;

}

Array<Ray>                      Pyramid::getRaysOfLateralFaces              (   const   Size                        aRayCount                                   ) const
{

    if (aRayCount < this->getLateralFaceCount())
    {
        throw library::core::error::RuntimeError("Ray count [{}] lower than lateral face count [{}].", aRayCount, this->getLateralFaceCount()) ;
    }

    Size lateralRayCount = aRayCount / this->getLateralFaceCount() ;

    Array<Ray> rays = Array<Ray>::Empty() ;

    for (Index lateralFaceIndex = 0; lateralFaceIndex < this->getLateralFaceCount(); ++lateralFaceIndex)
    {

        const Array<Ray> lateralFaceRays = this->getRaysOfLateralFaceAt(lateralFaceIndex, lateralRayCount) ;

        // [TBM] Double counting rays
        
        rays.add(lateralFaceRays) ;

    }

    return rays ;

}

Intersection                    Pyramid::intersectionWith                   (   const   Sphere&                     aSphere,
                                                                                const   bool                        onlyInSight,
                                                                                const   Size                        aDiscretizationLevel                        ) const
{

    if (!aSphere.isDefined())
    {
        throw library::core::error::runtime::Undefined("Sphere") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Pyramid") ;
    }

    Array<Point> firstIntersectionPoints = Array<Point>::Empty() ;
    Array<Point> secondIntersectionPoints = Array<Point>::Empty() ;

    for (const auto& ray : this->getRaysOfLateralFaces(aDiscretizationLevel))
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

Intersection                    Pyramid::intersectionWith                   (   const   Ellipsoid&                  anEllipsoid,
                                                                                const   bool                        onlyInSight,
                                                                                const   Size                        aDiscretizationLevel                        ) const
{

    if (!anEllipsoid.isDefined())
    {
        throw library::core::error::runtime::Undefined("Ellipsoid") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Pyramid") ;
    }

    Array<Point> firstIntersectionPoints = Array<Point>::Empty() ;
    Array<Point> secondIntersectionPoints = Array<Point>::Empty() ;

    for (const auto& ray : this->getRaysOfLateralFaces(aDiscretizationLevel))
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

void                            Pyramid::print                              (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           ) const
{

    displayDecorators ? library::core::utils::Print::Header(anOutputStream, "Pyramid") : void () ;

    library::core::utils::Print::Line(anOutputStream) << "Apex:"                << (apex_.isDefined() ? apex_.toString() : "Undefined") ;
    
    library::core::utils::Print::Separator(anOutputStream, "Base:") ;

    base_.print(anOutputStream, false) ;

    displayDecorators ? library::core::utils::Print::Footer(anOutputStream) : void () ;

}
        
void                            Pyramid::applyTransformation                (   const   Transformation&             aTransformation                             )
{

    if (!aTransformation.isDefined())
    {
        throw library::core::error::runtime::Undefined("Transformation") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Pyramid") ;
    }

    base_.applyTransformation(aTransformation) ;
    apex_.applyTransformation(aTransformation) ;

}

Pyramid                         Pyramid::Undefined                          ( )
{
    return { Polygon::Undefined(), Point::Undefined() } ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////