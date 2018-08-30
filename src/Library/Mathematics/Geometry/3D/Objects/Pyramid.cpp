////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Pyramid.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/Transformations/Rotations/Quaternion.hpp>
#include <Library/Mathematics/Geometry/3D/Intersection.hpp>
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

bool                            Pyramid::intersects                         (   const   Ellipsoid&                  anEllipsoid                                 ) const
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

    using Point2d = library::math::geom::d2::objects::Point ;

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Pyramid") ;
    }

    const Segment baseEdge = base_.getEdgeAt(aLateralFaceIndex) ;
    // std::cout << "baseEdge = " << baseEdge << std::endl ;

    const Vector3d firstDirection = (baseEdge.getFirstPoint() - apex_).normalized() ;
    // std::cout << "firstDirection = " << firstDirection << std::endl ;
    const Vector3d secondDirection = (baseEdge.getSecondPoint() - apex_).normalized() ;
    // std::cout << "secondDirection = " << secondDirection << std::endl ;

    const Vector3d firstAxis = firstDirection ;
    // std::cout << "firstAxis = " << firstAxis << std::endl ;
    const Vector3d secondAxis = (firstAxis.cross(secondDirection)).cross(firstAxis).normalized() ;
    // std::cout << "secondAxis = " << secondAxis << std::endl ;

    const Vector3d baseEdgeVector = baseEdge.getSecondPoint() - baseEdge.getFirstPoint() ;
    // std::cout << "baseEdgeVector = " << baseEdgeVector << std::endl ;

    const Point2d firstPolygonPoint = { 0.0, 0.0 } ;
    // std::cout << "firstPolygonPoint = " << firstPolygonPoint << std::endl ;
    const Point2d secondPolygonPoint = { (baseEdge.getFirstPoint() - apex_).norm(), 0.0 } ;
    // std::cout << "secondPolygonPoint = " << secondPolygonPoint << std::endl ;
    const Point2d thirdPolygonPoint = secondPolygonPoint + Point2d { baseEdgeVector.dot(firstAxis), baseEdgeVector.dot(secondAxis) } ;
    // std::cout << "thirdPolygonPoint = " << thirdPolygonPoint << std::endl ;

    const Polygon2d polygon = { { firstPolygonPoint, secondPolygonPoint, thirdPolygonPoint } } ;
    // std::cout << "polygon = " << polygon << std::endl ;

    return { polygon, apex_, firstAxis, secondAxis } ;

}

Array<Ray>                      Pyramid::getRaysOfLateralFaceAt             (   const   Index                       aLateralFaceIndex,
                                                                                const   Size                        aRayCount                                   ) const
{

    using library::math::obj::Interval ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;

    if (aRayCount < 2)
    {
        throw library::core::error::runtime::Wrong("Ray count") ;
    }

    const Polygon lateralFace = this->getLateralFaceAt(aLateralFaceIndex) ;

    const Ray firstRay = { apex_, (lateralFace.getVertexAt(1) - apex_).normalized() } ;
    const Ray secondRay = { apex_, (lateralFace.getVertexAt(2) - apex_).normalized() } ;

    const Vector3d rotationAxis = firstRay.getDirection().cross(secondRay.getDirection()).normalized() ;

    const Angle angleBetweenRays = Angle::Between(firstRay.getDirection(), secondRay.getDirection()) ;
// std::cout << "angleBetweenRays = " << std::endl << angleBetweenRays << std::endl ;
    Array<Ray> rays = Array<Ray>::Empty() ;

    for (const auto& angle_rad : Interval<Real>::Closed(0.0, angleBetweenRays.inRadians()).generateArrayWithSize(aRayCount))
    {

        const Ray ray = { firstRay.getOrigin(), Quaternion::RotationVector(RotationVector(rotationAxis, Angle::Radians(angle_rad))).conjugate() * firstRay.getDirection() } ;
// std::cout << "ray @ " << aLateralFaceIndex << " / " << Angle::Radians(angle_rad).inDegrees().toString() << " [deg] = " << std::endl << ray << std::endl ;
        rays.emplace_back(ray) ;

    }

    return rays ;

}

Array<Ray>                      Pyramid::getRaysOfLateralFaces              (   const   Size                        aRayCount                                   ) const
{

    if (aRayCount < this->getLateralFaceCount())
    {
        throw library::core::error::runtime::Wrong("Ray count") ;
    }

    Size lateralRayCount = aRayCount / this->getLateralFaceCount() ;

    Array<Ray> rays = Array<Ray>::Empty() ;

    for (Index lateralFaceIndex = 0; lateralFaceIndex < this->getLateralFaceCount(); ++lateralFaceIndex)
    {

        // [TBM] Double counting rays
        
        rays.add(this->getRaysOfLateralFaceAt(lateralFaceIndex, lateralRayCount)) ;

    }

    // std::cout << "Pyramid::getRaysOfLateralFaces :: rays " << std::endl << rays << std::endl ;

    return rays ;

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

    Array<Point> intersectionPoints = Array<Point>::Empty() ;

    for (const auto& ray : this->getRaysOfLateralFaces(aDiscretizationLevel))
    {
// std::cout << "Pyramid::intersectionWith :: ray " << std::endl << ray << std::endl ;
        const Intersection intersection = ray.intersectionWith(anEllipsoid, onlyInSight) ;
// std::cout << "intersection " << std::endl << intersection << std::endl ;
        if (!intersection.isEmpty())
        {

            if (intersection.is<Point>())
            {
                intersectionPoints.add(intersection.as<Point>()) ;
            }
            else if (intersection.is<PointSet>())
            {

                const PointSet& pointSet = intersection.as<PointSet>() ;

                for (const auto& point : pointSet)
                {
                    intersectionPoints.add(point) ;
                }               

            }

        }

    }

    if (!intersectionPoints.isEmpty())
    {
        return Intersection::PointSet(PointSet(intersectionPoints)) ;
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

void                            Pyramid::translate                          (   const   Vector3d&                   aTranslation                                )
{

    if (!aTranslation.isDefined())
    {
        throw library::core::error::runtime::Undefined("Translation") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Pyramid") ;
    }

    base_.translate(aTranslation) ;
    apex_.translate(aTranslation) ;

}
        
void                            Pyramid::rotate                             (   const   Quaternion&                 aRotation                                   )
{

    if (!aRotation.isDefined())
    {
        throw library::core::error::runtime::Undefined("Rotation") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Pyramid") ;
    }

    throw library::core::error::runtime::ToBeImplemented("Pyramid :: rotate") ;

    // xAxis_ = aRotation * xAxis_ ;
    // yAxis_ = aRotation * yAxis_ ;

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