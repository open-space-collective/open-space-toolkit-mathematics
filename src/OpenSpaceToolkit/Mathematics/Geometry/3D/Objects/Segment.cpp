////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Segment.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Sphere.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Plane.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Segment.hpp>

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

                                Segment::Segment                            (   const   Point&                      aFirstPoint,
                                                                                const   Point&                      aSecondPoint                                )
                                :   Object(),
                                    firstPoint_(aFirstPoint),
                                    secondPoint_(aSecondPoint)
{

}

Segment*                        Segment::clone                              ( ) const
{
    return new Segment(*this) ;
}

bool                            Segment::operator ==                        (   const   Segment&                    aSegment                                    ) const
{

    if ((!this->isDefined()) || (!aSegment.isDefined()))
    {
        return false ;
    }

    return ((firstPoint_ == aSegment.firstPoint_) && (secondPoint_ == aSegment.secondPoint_))
        || ((firstPoint_ == aSegment.secondPoint_) && (secondPoint_ == aSegment.firstPoint_)) ;

}

bool                            Segment::operator !=                        (   const   Segment&                    aSegment                                    ) const
{
    return !((*this) == aSegment) ;
}

bool                            Segment::isDefined                          ( ) const
{
    return firstPoint_.isDefined() && secondPoint_.isDefined() ;
}

bool                            Segment::isDegenerate                       ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Segment") ;
    }

    return firstPoint_ == secondPoint_ ;

}

// bool                            Segment::intersects                         (   const   Segment&                    aSegment                                    ) const
// {

// }

bool                            Segment::intersects                         (   const   Plane&                      aPlane                                      ) const
{

    // http://geomalgorithms.com/a05-_intersect-1.html

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Segment") ;
    }

    if (!aPlane.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Plane") ;
    }

    const Vector3d n = aPlane.getNormalVector() ;
    const Vector3d v = secondPoint_ - firstPoint_ ;

    const Vector3d Q_0 = aPlane.getPoint().asVector() ;
    const Vector3d P_0 = firstPoint_.asVector() ;

    const double nDotV = n.dot(v) ;

    if (nDotV == 0.0) // Segment and plane are parallel
    {
        return n.dot(Q_0 - P_0) == 0.0 ; // Segment is in plane
    }

    const double t = n.dot(Q_0 - P_0) / nDotV ;

    return ((t >= 0.0) && (t <= 1.0)) ;

}

bool                            Segment::intersects                         (   const   Sphere&                     aSphere                                     ) const
{
    return aSphere.intersects(*this) ;
}

bool                            Segment::intersects                         (   const   Ellipsoid&                  anEllipsoid                                 ) const
{
    return anEllipsoid.intersects(*this) ;
}

bool                            Segment::contains                           (   const   Point&                      aPoint                                      ) const
{

    if (!aPoint.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point") ;
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Segment") ;
    }

    if (this->isDegenerate())
    {
        return firstPoint_ == aPoint ;
    }

    const Vector3d AB = secondPoint_ - firstPoint_ ;
    const Vector3d AC = aPoint - firstPoint_ ;

    if (AB.cross(AC).squaredNorm() == 0.0) // Points are aligned
    {

        const Real K_AC = AB.dot(AC) ;
        const Real K_AB = AB.dot(AB) ;

        return (0.0 <= K_AC) && (K_AC <= K_AB) ; // C between A and B

    }

    return false ;

}

// bool                            Segment::contains                           (   const   PointSet&                   aPointSet                                   ) const
// {

// }

Point                           Segment::getFirstPoint                      ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Segment") ;
    }

    return firstPoint_ ;

}

Point                           Segment::getSecondPoint                     ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Segment") ;
    }

    return secondPoint_ ;

}

Point                           Segment::getCenter                          ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Segment") ;
    }

    return firstPoint_ + (secondPoint_ - firstPoint_) / 2.0 ;

}

Vector3d                        Segment::getDirection                       ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Segment") ;
    }

    if (this->isDegenerate())
    {
        throw ostk::core::error::RuntimeError("Segment is degenerate.") ;
    }

    return (secondPoint_ - firstPoint_).normalized() ;

}

Real                            Segment::getLength                          ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Segment") ;
    }

    return (secondPoint_ - firstPoint_).norm() ;

}

Intersection                    Segment::intersectionWith                   (   const   Plane&                      aPlane                                      ) const
{

    // http://geomalgorithms.com/a05-_intersect-1.html

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Segment") ;
    }

    if (!aPlane.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Plane") ;
    }

    const Vector3d n = aPlane.getNormalVector() ;
    const Vector3d v = secondPoint_ - firstPoint_ ;

    const Vector3d Q_0 = aPlane.getPoint().asVector() ;
    const Vector3d P_0 = firstPoint_.asVector() ;

    const double nDotV = n.dot(v) ;

    if (nDotV == 0.0) // Segment and plane are parallel
    {

        if (n.dot(Q_0 - P_0) == 0.0) // Segment is in plane
        {
            return Intersection::Segment(*this) ;
        }

        return Intersection::Empty() ;

    }

    const double t = n.dot(Q_0 - P_0) / nDotV ;

    if ((t < 0.0) || (t > 1.0))
    {
        return Intersection::Empty() ;
    }

    return Intersection::Point(Point::Vector(P_0 + t * v)) ;

}

void                            Segment::print                              (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           ) const
{

    displayDecorators ? ostk::core::utils::Print::Header(anOutputStream, "Segment") : void () ;

    ostk::core::utils::Print::Line(anOutputStream) << "First point:"         << (firstPoint_.isDefined() ? firstPoint_.toString() : "Undefined") ;
    ostk::core::utils::Print::Line(anOutputStream) << "Second point:"        << (secondPoint_.isDefined() ? secondPoint_.toString() : "Undefined") ;

    displayDecorators ? ostk::core::utils::Print::Footer(anOutputStream) : void () ;

}

void                            Segment::applyTransformation                (   const   Transformation&             aTransformation                             )
{

    if (!aTransformation.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Transformation") ;
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Segment") ;
    }

    firstPoint_.applyTransformation(aTransformation) ;
    secondPoint_.applyTransformation(aTransformation) ;

}

Segment                         Segment::Undefined                          ( )
{
    return { Point::Undefined(), Point::Undefined() } ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
