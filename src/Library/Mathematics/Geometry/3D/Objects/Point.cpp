////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Point.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Transformation.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Point.hpp>

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

                                Point::Point                                (   const   Real&                       aFirstCoordinate,
                                                                                const   Real&                       aSecondCoordinate,
                                                                                const   Real&                       aThirdCoordinate                            )
                                :   Object(),
                                    x_(aFirstCoordinate),
                                    y_(aSecondCoordinate),
                                    z_(aThirdCoordinate)
{
    
}

Point*                          Point::clone                                ( ) const
{
    return new Point(*this) ;
}

bool                            Point::operator ==                          (   const   Point&                      aPoint                                      ) const
{

    if ((!this->isDefined()) || (!aPoint.isDefined()))
    {
        return false ;
    }

    return (x_ == aPoint.x_) && (y_ == aPoint.y_) && (z_ == aPoint.z_) ;

}

bool                            Point::operator !=                          (   const   Point&                      aPoint                                      ) const
{
    return !((*this) == aPoint) ;
}

Point                           Point::operator +                           (   const   Vector3d&                   aVector                                     ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }

    if (!aVector.isDefined())
    {
        throw library::core::error::runtime::Undefined("Vector") ;
    }
    
    return { x_ + aVector.x(), y_ + aVector.y(), z_ + aVector.z() } ;

}

Point                           Point::operator -                           (   const   Vector3d&                   aVector                                     ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }

    if (!aVector.isDefined())
    {
        throw library::core::error::runtime::Undefined("Vector") ;
    }
    
    return { x_ - aVector.x(), y_ - aVector.y(), z_ - aVector.z() } ;

}
        
Vector3d                        Point::operator -                           (   const   Point&                      aPoint                                      ) const
{

    if (!aPoint.isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }

    return { x_ - aPoint.x(), y_ - aPoint.y(), z_ - aPoint.z() } ;

}

bool                            Point::isDefined                            ( ) const
{
    return x_.isDefined() && y_.isDefined() && z_.isDefined() ;
}

bool                            Point::isNear                               (   const   Point&                      aPoint,
                                                                                const   Real&                       aTolerance                                  ) const
{

    if (!aTolerance.isDefined())
    {
        throw library::core::error::runtime::Undefined("Tolerance") ;
    }

    return this->distanceTo(aPoint) <= aTolerance ;

}

const Real&                     Point::x                                    ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }
    
    return x_ ;

}

const Real&                     Point::y                                    ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }
    
    return y_ ;

}

const Real&                     Point::z                                    ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }
    
    return z_ ;

}

Vector3d                        Point::asVector                             ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }
    
    return { x_, y_, z_ } ;

}

Real                            Point::distanceTo                           (   const   Point&                      aPoint                                      ) const
{

    if (!aPoint.isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }

    return ((*this) - aPoint).norm() ;

}

String                          Point::toString                             (   const   Integer&                    aPrecision                                  ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }

    return aPrecision.isDefined() ? Vector3d(x_, y_, z_).toString(aPrecision) : Vector3d(x_, y_, z_).toString() ;

}

void                            Point::print                                (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           ) const
{

    displayDecorators ? library::core::utils::Print::Header(anOutputStream, "Point") : void () ;

    library::core::utils::Print::Line(anOutputStream) << "X:"                   << (x_.isDefined() ? x_.toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Y:"                   << (y_.isDefined() ? y_.toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Z:"                   << (z_.isDefined() ? z_.toString() : "Undefined") ;

    displayDecorators ? library::core::utils::Print::Footer(anOutputStream) : void () ;

}

void                            Point::applyTransformation                  (   const   Transformation&             aTransformation                             )
{

    if (!aTransformation.isDefined())
    {
        throw library::core::error::runtime::Undefined("Transformation") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }

    (*this) = aTransformation.applyTo(*this) ;

}

Point                           Point::Undefined                            ( )
{
    return { Real::Undefined(), Real::Undefined(), Real::Undefined() } ;
}

Point                           Point::Origin                               ( )
{
    return { 0.0, 0.0, 0.0 } ;
}

Point                           Point::Vector                               (   const   Vector3d&                   aVector                                     )
{
    return { aVector.x(), aVector.y(), aVector.z() } ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////