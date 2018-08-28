////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Line.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Line.hpp>

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

                                Line::Line                                  (   const   Point&                      anOrigin,
                                                                                const   Vector3d&                   aDirection                                  )
                                :   Object(),
                                    origin_(anOrigin),
                                    direction_(aDirection)
{

    if (direction_.isDefined() && (direction_.squaredNorm() != 1.0))
    {

        if (direction_.squaredNorm() == 0.0)
        {
            throw library::core::error::runtime::Wrong("Direction") ;
        }
        
        direction_ = direction_.normalized() ;

    }

}

Line*                           Line::clone                                 ( ) const
{
    return new Line(*this) ;
}

bool                            Line::operator ==                           (   const   Line&                       aLine                                       ) const
{

    if ((!this->isDefined()) || (!aLine.isDefined()))
    {
        return false ;
    }

    if ((direction_ == aLine.direction_) || (direction_ == -aLine.direction_))
    {
        return this->contains(aLine.origin_) ;
    }

    return false ;

}

bool                            Line::operator !=                           (   const   Line&                       aLine                                       ) const
{
    return !((*this) == aLine) ;
}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Line&                       aLine                                       )
{

    library::core::utils::Print::Header(anOutputStream, "Line") ;

    library::core::utils::Print::Line(anOutputStream) << "Origin:"              << (aLine.origin_.isDefined() ? aLine.origin_.toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Direction:"           << (aLine.direction_.isDefined() ? aLine.direction_.toString() : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Line::isDefined                             ( ) const
{
    return origin_.isDefined() && direction_.isDefined() ;
}

bool                            Line::intersects                            (   const   Point&                      aPoint                                      ) const
{
    return this->contains(aPoint) ;
}

// bool                            Line::intersects                            (   const   Line&                       aLine                                       ) const
// {
    
// }

// bool                            Line::intersects                            (   const   Sphere&                     aSphere                                     ) const
// {
//     return aSphere.intersects(*this) ;
// }

bool                            Line::intersects                            (   const   Ellipsoid&                  anEllipsoid                                 ) const
{
    return anEllipsoid.intersects(*this) ;
}

bool                            Line::contains                              (   const   Point&                      aPoint                                      ) const
{

    if (!aPoint.isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Line") ;
    }

    return direction_.cross(aPoint - origin_).squaredNorm() == 0.0 ;

}

// bool                            Line::contains                              (   const   PointSet&                   aPointSet                                   ) const
// {

// }

Point                           Line::getOrigin                             ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Line") ;
    }
    
    return origin_ ;

}

Vector3d                        Line::getDirection                       ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Line") ;
    }
    
    return direction_ ;

}

void                            Line::translate                             (   const   Vector3d&                   aTranslation                                )
{

    if (!aTranslation.isDefined())
    {
        throw library::core::error::runtime::Undefined("Translation") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Line") ;
    }

    origin_ += aTranslation ;

}
        
void                            Line::rotate                                (   const   Quaternion&                 aRotation                                   )
{

    if (!aRotation.isDefined())
    {
        throw library::core::error::runtime::Undefined("Rotation") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Line") ;
    }

    direction_ = aRotation * direction_ ;

}

Line                            Line::Undefined                             ( )
{
    return { Point::Undefined(), Vector3d::Undefined() } ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////