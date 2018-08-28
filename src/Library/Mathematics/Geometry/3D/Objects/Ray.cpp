////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Ray.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ray.hpp>

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

                                Ray::Ray                                    (   const   Point&                      anOrigin,
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

Ray*                            Ray::clone                                  ( ) const
{
    return new Ray(*this) ;
}

bool                            Ray::operator ==                            (   const   Ray&                        aRay                                        ) const
{

    if ((!this->isDefined()) || (!aRay.isDefined()))
    {
        return false ;
    }

    return (origin_ == aRay.origin_) && (direction_ == aRay.direction_) ;

}

bool                            Ray::operator !=                            (   const   Ray&                        aRay                                        ) const
{
    return !((*this) == aRay) ;
}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Ray&                        aRay                                        )
{

    library::core::utils::Print::Header(anOutputStream, "Ray") ;

    library::core::utils::Print::Line(anOutputStream) << "Origin:"              << (aRay.origin_.isDefined() ? aRay.origin_.toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Direction:"           << (aRay.direction_.isDefined() ? aRay.direction_.toString() : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Ray::isDefined                              ( ) const
{
    return origin_.isDefined() && direction_.isDefined() ;
}

bool                            Ray::intersects                             (   const   Point&                      aPoint                                      ) const
{
    return this->contains(aPoint) ;
}

// bool                            Ray::intersects                          (   const   Ray&                       aRay                                       ) const
// {
    
// }

// bool                            Ray::intersects                          (   const   Sphere&                     aSphere                                     ) const
// {
//     return aSphere.intersects(*this) ;
// }

bool                            Ray::intersects                             (   const   Ellipsoid&                  anEllipsoid                                 ) const
{
    return anEllipsoid.intersects(*this) ;
}

bool                            Ray::contains                               (   const   Point&                      aPoint                                      ) const
{

    if (!aPoint.isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Ray") ;
    }

    const Vector3d AC = aPoint - origin_ ;

    return (direction_.cross(AC).squaredNorm() == 0.0) && (0.0 <= direction_.dot(AC)) ;

}

// bool                            Ray::contains                              (   const   PointSet&                   aPointSet                                   ) const
// {

// }

Point                           Ray::getOrigin                              ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Ray") ;
    }
    
    return origin_ ;

}

Vector3d                        Ray::getDirection                           ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Ray") ;
    }
    
    return direction_ ;

}

void                            Ray::translate                              (   const   Vector3d&                   aTranslation                                )
{

    if (!aTranslation.isDefined())
    {
        throw library::core::error::runtime::Undefined("Translation") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Ray") ;
    }

    origin_ += aTranslation ;

}
        
void                            Ray::rotate                                 (   const   Quaternion&                 aRotation                                   )
{

    if (!aRotation.isDefined())
    {
        throw library::core::error::runtime::Undefined("Rotation") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Ray") ;
    }

    direction_ = aRotation * direction_ ;

}

Ray                             Ray::Undefined                              ( )
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