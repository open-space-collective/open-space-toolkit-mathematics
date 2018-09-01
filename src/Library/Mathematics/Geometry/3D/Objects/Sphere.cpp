////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Sphere.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Transformation.hpp>
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

                                Sphere::Sphere                              (   const   Point&                      aCenter,
                                                                                const   Real&                       aRadius                                     )
                                :   Object(),
                                    center_(aCenter),
                                    radius_(aRadius)
{

}

Sphere*                         Sphere::clone                               ( ) const
{
    return new Sphere(*this) ;
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

Point                           Sphere::getCenter                           ( ) const
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

void                            Sphere::print                               (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           ) const
{

    displayDecorators ? library::core::utils::Print::Header(anOutputStream, "Sphere") : void () ;

    library::core::utils::Print::Line(anOutputStream) << "Center:"              << (center_.isDefined() ? center_.toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Radius:"              << (radius_.isDefined() ? radius_.toString() : "Undefined") ;

    displayDecorators ? library::core::utils::Print::Footer(anOutputStream) : void () ;

}

void                            Sphere::applyTransformation                 (   const   Transformation&             aTransformation                             )
{

    if (!aTransformation.isDefined())
    {
        throw library::core::error::runtime::Undefined("Transformation") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Sphere") ;
    }

    if (!aTransformation.isRigid())
    {
        throw library::core::error::RuntimeError("Only rigid transformation is supported.") ;
    }

    center_.applyTransformation(aTransformation) ;

}

Sphere                          Sphere::Undefined                           ( )
{
    return { Point::Undefined(), Real::Undefined() } ;
}

Sphere                          Sphere::Unit                                (   const   Point&                      aCenter                                     )
{
    return { aCenter, 1.0 } ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////