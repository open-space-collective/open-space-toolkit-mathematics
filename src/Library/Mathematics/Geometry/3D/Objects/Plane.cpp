////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Plane.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Transformation.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Plane.hpp>

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

                                Plane::Plane                                (   const   Point&                      aPoint,
                                                                                const   Vector3d&                   aNormalVector                               )
                                :   Object(),
                                    point_(aPoint),
                                    normal_(aNormalVector.normalized())
{

}

Plane*                          Plane::clone                                ( ) const
{
    return new Plane(*this) ;
}

bool                            Plane::operator ==                          (   const   Plane&                      aPlane                                      ) const
{

    if ((!this->isDefined()) || (!aPlane.isDefined()))
    {
        return false ;
    }

    if ((normal_ == aPlane.normal_) || (normal_ == -aPlane.normal_))
    {
        return (point_ == aPlane.point_) || this->contains(aPlane.point_) ;
    }

    return false ;

}

bool                            Plane::operator !=                          (   const   Plane&                      aPlane                                      ) const
{
    return !((*this) == aPlane) ;
}

bool                            Plane::isDefined                            ( ) const
{
    return point_.isDefined() && normal_.isDefined() ;
}

bool                            Plane::contains                             (   const   Point&                      aPoint                                      ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Plane") ;
    }

    return (aPoint - point_).dot(normal_) == 0.0 ;

}

Point                           Plane::getPoint                             ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Plane") ;
    }

    return point_ ;

}

Vector3d                        Plane::getNormalVector                      ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Plane") ;
    }

    return normal_ ;

}

void                            Plane::print                                (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           ) const
{

    displayDecorators ? library::core::utils::Print::Header(anOutputStream, "Plane") : void () ;

    library::core::utils::Print::Line(anOutputStream) << "Point:"               << (point_.isDefined() ? point_.toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Normal vector:"       << (normal_.isDefined() ? normal_.toString() : "Undefined") ;

    displayDecorators ? library::core::utils::Print::Footer(anOutputStream) : void () ;

}

void                            Plane::applyTransformation                  (   const   Transformation&             aTransformation                             )
{

    if (!aTransformation.isDefined())
    {
        throw library::core::error::runtime::Undefined("Transformation") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Plane") ;
    }

    point_.applyTransformation(aTransformation) ;
    normal_ = aTransformation.applyTo(normal_) ;

}

Plane                           Plane::Undefined                            ( )
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