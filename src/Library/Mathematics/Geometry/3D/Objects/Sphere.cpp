////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Sphere.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Objects/Sphere.hpp>

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

                                Sphere::Sphere                              (   const   Vector3d&                   aCenter,
                                                                                const   Real&                       aRadius                                     )
                                :   Object(),
                                    center_(aCenter),
                                    radius_(aRadius)
{

}

bool                            Sphere::operator ==                         (   const   Sphere&                     aSphere                                     ) const
{

    if ((!this->isDefined()) || (!aSphere.isDefined()))
    {
        return false ;
    }

    return (center_ == aSphere.center_) && (radius_ == aSphere.radius_) ;

}

bool                            Sphere::operator !=                         (   const   Sphere&                     aSphere                                     ) const
{

    if ((!this->isDefined()) || (!aSphere.isDefined()))
    {
        return true ;
    }

    return (center_ != aSphere.center_) || (radius_ != aSphere.radius_) ;

}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Sphere&                     aSphere                                     )
{

    library::core::utils::Print::Header(anOutputStream, "Sphere") ;

    library::core::utils::Print::Line(anOutputStream) << "Center:" << (aSphere.isDefined() ? aSphere.center_.toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Radius:" << (aSphere.isDefined() ? aSphere.radius_.toString() : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Sphere::isDefined                           ( ) const
{
    return center_.isDefined() && radius_.isDefined() ;
}

bool                            Sphere::isUnitary                           ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Sphere") ;
    }
    
    return radius_ == 1.0 ;

}

Vector3d                        Sphere::getCenter                           ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Sphere") ;
    }
    
    return center_ ;

}

Real                            Sphere::getRadius                           ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Sphere") ;
    }
    
    return radius_ ;

}

Sphere                          Sphere::Undefined                           ( )
{
    return Sphere(Vector3d::Undefined(), Real::Undefined()) ;
}

Sphere                          Sphere::Unit                                (   const   Vector3d&                   aCenter                                     )
{
    return Sphere(aCenter, 1.0) ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////