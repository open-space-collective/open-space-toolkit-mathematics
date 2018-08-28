////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/2D/Objects/Point.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/2D/Objects/Point.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace math
{
namespace geom
{
namespace d2
{
namespace objects
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Point::Point                                (   const   Real&                       aFirstCoordinate,
                                                                                const   Real&                       aSecondCoordinate                           )
                                :   Object(),
                                    Vector2d(aFirstCoordinate, aSecondCoordinate)
{
    
}

                                Point::Point                                (   const   Vector2d&                   aVector                                     )
                                :   Object(),
                                    Vector2d(aVector)
{

}

Point*                          Point::clone                                ( ) const
{
    return new Point(*this) ;
}

bool                            Point::operator ==                          (   const   Point&                      aPoint                                      ) const
{

    if ((!this->isDefined()) && (!aPoint.isDefined()))
    {
        return false ;
    }

    return this->Vector2d::operator == (aPoint) ;

}

bool                            Point::operator !=                          (   const   Point&                      aPoint                                      ) const
{
    return !((*this) == aPoint) ;
}

Point                           Point::operator +                           (   const   Vector2d&                   aVector                                     ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }

    if (!aVector.isDefined())
    {
        throw library::core::error::runtime::Undefined("Vector") ;
    }
    
    return Point(this->Vector2d::operator + (aVector)) ;

}

Point                           Point::operator -                           (   const   Vector2d&                   aVector                                     ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }

    if (!aVector.isDefined())
    {
        throw library::core::error::runtime::Undefined("Vector") ;
    }
    
    return Point(this->Vector2d::operator - (aVector)) ;

}
        
Vector2d                        Point::operator -                           (   const   Point&                      aPoint                                      ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }

    if (!aPoint.isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }

    return this->Vector2d::operator - (aPoint) ;

}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Point&                      aPoint                                      )
{

    library::core::utils::Print::Header(anOutputStream, "Point") ;

    library::core::utils::Print::Line(anOutputStream) << "Coordinates:" << (aPoint.isDefined() ? aPoint.toString() : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Point::isDefined                            ( ) const
{
    return Vector2d::isDefined() ;
}

bool                            Point::isNear                               (   const   Point&                      aPoint,
                                                                                const   Real&                       aTolerance                                  ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }

    if (!aPoint.isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }

    if (!aTolerance.isDefined())
    {
        throw library::core::error::runtime::Undefined("Tolerance") ;
    }

    return (this->Vector2d::operator - (aPoint)).norm() <= aTolerance ;

}

void                            Point::translate                            (   const   Vector2d&                   aTranslation                                )
{

    if (!aTranslation.isDefined())
    {
        throw library::core::error::runtime::Undefined("Translation") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }

    (*this) += aTranslation ;

}

Point                           Point::Undefined                            ( )
{
    return Vector2d::Undefined() ;
}

Point                           Point::Origin                               ( )
{
    return { 0.0, 0.0 } ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////