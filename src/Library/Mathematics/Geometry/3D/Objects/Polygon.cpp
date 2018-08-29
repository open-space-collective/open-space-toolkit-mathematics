////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Polygon.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Objects/Polygon.hpp>

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

                                Polygon::Polygon                            (   const   Polygon2d&                  aPolygon,
                                                                                const   Point&                      anOrigin,
                                                                                const   Vector3d&                   aXAxis,
                                                                                const   Vector3d&                   aYAxis                                      )
                                :   Object(),
                                    polygon_(aPolygon),
                                    origin_(anOrigin),
                                    xAxis_(aXAxis.isDefined() ? aXAxis.normalized() : aXAxis),
                                    yAxis_(aYAxis.isDefined() ? aYAxis.normalized() : aYAxis)
{

    if (xAxis_.isDefined() && yAxis_.isDefined())
    {

        if (xAxis_.squaredNorm() != 1.0)
        {
            throw library::core::error::runtime::Wrong("X axis") ;
        }

        if (yAxis_.squaredNorm() != 1.0)
        {
            throw library::core::error::runtime::Wrong("Y axis") ;
        }

        if (xAxis_.dot(yAxis_) != 0.0)
        {
            throw library::core::error::RuntimeError("X and Y axes are not orthogonal.") ;
        }

    }

}

Polygon*                        Polygon::clone                              ( ) const
{
    return new Polygon(*this) ;
}

bool                            Polygon::operator ==                        (   const   Polygon&                    aPolygon                                    ) const
{

    if ((!this->isDefined()) || (!aPolygon.isDefined()))
    {
        return false ;
    }

    // [TBI] Implement superposition

    return (polygon_ == aPolygon.polygon_) && (origin_ == aPolygon.origin_) && (xAxis_ == aPolygon.xAxis_) && (yAxis_ == aPolygon.yAxis_) ;

}

bool                            Polygon::operator !=                        (   const   Polygon&                    aPolygon                                    ) const
{
    return !((*this) == aPolygon) ;
}

bool                            Polygon::isDefined                          ( ) const
{
    return polygon_.isDefined() && origin_.isDefined() && xAxis_.isDefined() && yAxis_.isDefined() ;
}

Polygon2d                       Polygon::getPolygon2d                       ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Polygon") ;
    }

    return polygon_ ;

}

Point                           Polygon::getOrigin                          ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Polygon") ;
    }

    return origin_ ;

}

Vector3d                        Polygon::getXAxis                           ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Polygon") ;
    }

    return xAxis_ ;

}

Vector3d                        Polygon::getYAxis                           ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Polygon") ;
    }

    return yAxis_ ;

}

Vector3d                        Polygon::getNormalVector                    ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Polygon") ;
    }

    return xAxis_.cross(yAxis_) ;

}

void                            Polygon::print                              (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           ) const
{

    displayDecorators ? library::core::utils::Print::Header(anOutputStream, "Polygon") : void () ;

    library::core::utils::Print::Line(anOutputStream) << "Origin:"              << (origin_.isDefined() ? origin_.toString() : "Undefined") ;

    library::core::utils::Print::Line(anOutputStream) << "X axis:"              << (xAxis_.isDefined() ? xAxis_.toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Y axis:"              << (yAxis_.isDefined() ? yAxis_.toString() : "Undefined") ;

    library::core::utils::Print::Separator(anOutputStream, "Polygon") ;

    polygon_.print(anOutputStream, false) ;

    displayDecorators ? library::core::utils::Print::Footer(anOutputStream) : void () ;

}

void                            Polygon::translate                          (   const   Vector3d&                   aTranslation                                )
{

    if (!aTranslation.isDefined())
    {
        throw library::core::error::runtime::Undefined("Translation") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Polygon") ;
    }

    origin_ += aTranslation ;

}
        
void                            Polygon::rotate                             (   const   Quaternion&                 aRotation                                   )
{

    if (!aRotation.isDefined())
    {
        throw library::core::error::runtime::Undefined("Rotation") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Polygon") ;
    }

    xAxis_ = aRotation * xAxis_ ;
    yAxis_ = aRotation * yAxis_ ;

}

Polygon                         Polygon::Undefined                          ( )
{
    return { Polygon2d::Undefined(), Point::Undefined(), Vector3d::Undefined(), Vector3d::Undefined() } ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////