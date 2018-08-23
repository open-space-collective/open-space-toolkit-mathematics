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
    return Vector3d::isDefined() ;
}

Point                           Point::Undefined                            ( )
{
    return Vector3d::Undefined() ;
}

Point                           Point::Origin                               ( )
{
    return Point(0.0, 0.0, 0.0) ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////