////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Segment.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Transformation.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>

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
        throw library::core::error::runtime::Undefined("Segment") ;
    }
    
    return firstPoint_ == secondPoint_ ;

}

// bool                            Segment::intersects                         (   const   Segment&                    aSegment                                    ) const
// {
    
// }

// bool                            Segment::intersects                         (   const   Sphere&                     aSphere                                     ) const
// {
//     return aSphere.intersects(*this) ;
// }

bool                            Segment::intersects                         (   const   Ellipsoid&                  anEllipsoid                                 ) const
{
    return anEllipsoid.intersects(*this) ;
}

bool                            Segment::contains                           (   const   Point&                      aPoint                                      ) const
{

    if (!aPoint.isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Segment") ;
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
        throw library::core::error::runtime::Undefined("Segment") ;
    }

    return firstPoint_ ;

}

Point                           Segment::getSecondPoint                     ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Segment") ;
    }

    return secondPoint_ ;

}

Point                           Segment::getCenter                          ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Segment") ;
    }
    
    return firstPoint_ + (secondPoint_ - firstPoint_) / 2.0 ;

}

Vector3d                        Segment::getDirection                       ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Segment") ;
    }

    if (this->isDegenerate())
    {
        throw library::core::error::RuntimeError("Segment is degenerate.") ;
    }
    
    return (secondPoint_ - firstPoint_).normalized() ;

}

Real                            Segment::getLength                          ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Segment") ;
    }
    
    return (secondPoint_ - firstPoint_).norm() ;

}

void                            Segment::print                              (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           ) const
{

    displayDecorators ? library::core::utils::Print::Header(anOutputStream, "Segment") : void () ;

    library::core::utils::Print::Line(anOutputStream) << "First point:"         << (firstPoint_.isDefined() ? firstPoint_.toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Second point:"        << (secondPoint_.isDefined() ? secondPoint_.toString() : "Undefined") ;

    displayDecorators ? library::core::utils::Print::Footer(anOutputStream) : void () ;

}

void                            Segment::applyTransformation                (   const   Transformation&             aTransformation                             )
{

    if (!aTransformation.isDefined())
    {
        throw library::core::error::runtime::Undefined("Transformation") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Segment") ;
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