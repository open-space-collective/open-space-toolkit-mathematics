////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Point.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
                                    Vector3d(aFirstCoordinate, aSecondCoordinate, aThirdCoordinate)
{
    
}

                                Point::Point                                (   const   Vector3d&                   aVector                                     )
                                :   Object(),
                                    Vector3d(aVector)
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

    return this->Vector3d::operator == (aPoint) ;

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
    
    return Point(this->Vector3d::operator + (aVector)) ;

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
    
    return Point(this->Vector3d::operator - (aVector)) ;

}
        
Vector3d                        Point::operator -                           (   const   Point&                      aPoint                                      ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }

    if (!aPoint.isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }

    return this->Vector3d::operator - (aPoint) ;

}

bool                            Point::isDefined                            ( ) const
{
    return Vector3d::isDefined() ;
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

    return (this->Vector3d::operator - (aPoint)).norm() <= aTolerance ;

}

void                            Point::print                                (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           ) const
{

    displayDecorators ? library::core::utils::Print::Header(anOutputStream, "Point") : void () ;

    library::core::utils::Print::Line(anOutputStream) << "Coordinates:"         << (this->isDefined() ? this->toString() : "Undefined") ;

    displayDecorators ? library::core::utils::Print::Footer(anOutputStream) : void () ;

}

void                            Point::translate                            (   const   Vector3d&                   aTranslation                                )
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
        
void                            Point::rotate                               (   const   Quaternion&                 aRotation                                   )
{

    if (!aRotation.isDefined())
    {
        throw library::core::error::runtime::Undefined("Rotation") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }

    // Do nothing

}

Point                           Point::Undefined                            ( )
{
    return Vector3d::Undefined() ;
}

Point                           Point::Origin                               ( )
{
    return { 0.0, 0.0, 0.0 } ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////