////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Ellipsoid.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>

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

                                Ellipsoid::Ellipsoid                        (   const   Point&                      aCenter,
                                                                                const   Real&                       aFirstPrincipalSemiAxis,
                                                                                const   Real&                       aSecondPrincipalSemiAxis,
                                                                                const   Real&                       aThirdPrincipalSemiAxis,
                                                                                const   Quaternion&                 anOrientation                               )
                                :   Object(),
                                    center_(aCenter),
                                    a_(aFirstPrincipalSemiAxis),
                                    b_(aSecondPrincipalSemiAxis),
                                    c_(aThirdPrincipalSemiAxis),
                                    q_(anOrientation)
{
    
    if (a_.isDefined() && (a_ < 0.0))
    {
        throw library::core::error::RuntimeError("First principal semi-axis is negative.") ;
    }

    if (b_.isDefined() && (b_ < 0.0))
    {
        throw library::core::error::RuntimeError("Second principal semi-axis is negative.") ;
    }

    if (c_.isDefined() && (c_ < 0.0))
    {
        throw library::core::error::RuntimeError("Third principal semi-axis is negative.") ;
    }

}

bool                            Ellipsoid::operator ==                      (   const   Ellipsoid&                  anEllipsoid                                 ) const
{

    if ((!this->isDefined()) || (!anEllipsoid.isDefined()))
    {
        return false ;
    }

    // [TBI] Check for invariants after rotation

    return (center_ == anEllipsoid.center_) && (a_ == anEllipsoid.a_) && (b_ == anEllipsoid.b_) && (c_ == anEllipsoid.c_) && (q_ == anEllipsoid.q_) ;

}

bool                            Ellipsoid::operator !=                      (   const   Ellipsoid&                  anEllipsoid                                 ) const
{
    return !((*this) == anEllipsoid) ;
}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Ellipsoid&                  anEllipsoid                                 )
{

    library::core::utils::Print::Header(anOutputStream, "Ellipsoid") ;

    library::core::utils::Print::Line(anOutputStream) << "Center:" << (anEllipsoid.center_.isDefined() ? anEllipsoid.center_.toString() : "Undefined") ;

    library::core::utils::Print::Line(anOutputStream) << "First principal semi-axis:" << (anEllipsoid.a_.isDefined() ? anEllipsoid.a_.toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Second principal semi-axis:" << (anEllipsoid.b_.isDefined() ? anEllipsoid.b_.toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Third principal semi-axis:" << (anEllipsoid.c_.isDefined() ? anEllipsoid.c_.toString() : "Undefined") ;

    library::core::utils::Print::Line(anOutputStream) << "Orientation:" << (anEllipsoid.q_.isDefined() ? anEllipsoid.q_.toString() : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Ellipsoid::isDefined                        ( ) const
{
    return center_.isDefined() && a_.isDefined() && b_.isDefined() && c_.isDefined() && q_.isDefined() ;
}

Point                           Ellipsoid::getCenter                        ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Ellipsoid") ;
    }
    
    return center_ ;

}

Real                            Ellipsoid::getFirstPrincipalSemiAxis        ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Ellipsoid") ;
    }
    
    return a_ ;

}

Real                            Ellipsoid::getSecondPrincipalSemiAxis       ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Ellipsoid") ;
    }
    
    return b_ ;

}

Real                            Ellipsoid::getThirdPrincipalSemiAxis        ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Ellipsoid") ;
    }
    
    return c_ ;

}

Quaternion                      Ellipsoid::getOrientation                   ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Ellipsoid") ;
    }
    
    return q_ ;

}

Ellipsoid                       Ellipsoid::Undefined                        ( )
{
    return Ellipsoid(Point::Undefined(), Real::Undefined(), Real::Undefined(), Real::Undefined(), Quaternion::Undefined()) ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////