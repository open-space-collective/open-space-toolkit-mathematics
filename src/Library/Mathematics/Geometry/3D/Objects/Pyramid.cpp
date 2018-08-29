////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Pyramid.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Objects/Pyramid.hpp>
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

                                Pyramid::Pyramid                            (   const   Polygon&                    aBase,
                                                                                const   Point&                      anApex                                      )
                                :   Object(),
                                    base_(aBase),
                                    apex_(anApex)
{

}

Pyramid*                        Pyramid::clone                              ( ) const
{
    return new Pyramid(*this) ;
}

bool                            Pyramid::operator ==                        (   const   Pyramid&                    aPyramid                                    ) const
{

    if ((!this->isDefined()) || (!aPyramid.isDefined()))
    {
        return false ;
    }

    return (base_ == aPyramid.base_) && (apex_ == aPyramid.apex_) ;

}

bool                            Pyramid::operator !=                        (   const   Pyramid&                    aPyramid                                    ) const
{
    return !((*this) == aPyramid) ;
}

bool                            Pyramid::isDefined                          ( ) const
{
    return base_.isDefined() && apex_.isDefined() ;
}

bool                            Pyramid::intersects                         (   const   Ellipsoid&                  anEllipsoid                                 ) const
{

    if (!anEllipsoid.isDefined())
    {
        throw library::core::error::runtime::Undefined("Ellipsoid") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Pyramid") ;
    }

    throw library::core::error::runtime::ToBeImplemented("Pyramid") ;

    return false ;

}

bool                            Pyramid::contains                           (   const   Ellipsoid&                  anEllipsoid                                 ) const
{

    if (!anEllipsoid.isDefined())
    {
        throw library::core::error::runtime::Undefined("Ellipsoid") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Pyramid") ;
    }

    throw library::core::error::runtime::ToBeImplemented("Pyramid") ;

    return false ;

}

Polygon                         Pyramid::getBase                            ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Pyramid") ;
    }

    return base_ ;

}

Point                           Pyramid::getApex                            ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Pyramid") ;
    }

    return apex_ ;

}

void                            Pyramid::print                              (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           ) const
{

    displayDecorators ? library::core::utils::Print::Header(anOutputStream, "Pyramid") : void () ;

    library::core::utils::Print::Line(anOutputStream) << "Apex:"                << (apex_.isDefined() ? apex_.toString() : "Undefined") ;
    
    library::core::utils::Print::Separator(anOutputStream, "Base:") ;

    base_.print(anOutputStream, false) ;

    displayDecorators ? library::core::utils::Print::Footer(anOutputStream) : void () ;

}

void                            Pyramid::translate                          (   const   Vector3d&                   aTranslation                                )
{

    if (!aTranslation.isDefined())
    {
        throw library::core::error::runtime::Undefined("Translation") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Pyramid") ;
    }

    base_.translate(aTranslation) ;
    apex_.translate(aTranslation) ;

}
        
void                            Pyramid::rotate                             (   const   Quaternion&                 aRotation                                   )
{

    if (!aRotation.isDefined())
    {
        throw library::core::error::runtime::Undefined("Rotation") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Pyramid") ;
    }

    throw library::core::error::runtime::ToBeImplemented("Pyramid :: rotate") ;

    // xAxis_ = aRotation * xAxis_ ;
    // yAxis_ = aRotation * yAxis_ ;

}

Pyramid                         Pyramid::Undefined                          ( )
{
    return { Polygon::Undefined(), Point::Undefined() } ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////