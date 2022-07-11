////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Line.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Sphere.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Plane.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Line.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
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

                                Line::Line                                  (   const   Point&                      anOrigin,
                                                                                const   Vector3d&                   aDirection                                  )
                                :   Object(),
                                    origin_(anOrigin),
                                    direction_(aDirection)
{

    if (direction_.isDefined() && (direction_.squaredNorm() != 1.0))
    {

        if (direction_.squaredNorm() == 0.0)
        {
            throw ostk::core::error::runtime::Wrong("Direction") ;
        }

        direction_ = direction_.normalized() ;

    }

}

Line*                           Line::clone                                 ( ) const
{
    return new Line(*this) ;
}

bool                            Line::operator ==                           (   const   Line&                       aLine                                       ) const
{

    if ((!this->isDefined()) || (!aLine.isDefined()))
    {
        return false ;
    }

    if ((direction_ == aLine.direction_) || (direction_ == -aLine.direction_))
    {
        return this->contains(aLine.origin_) ;
    }

    return false ;

}

bool                            Line::operator !=                           (   const   Line&                       aLine                                       ) const
{
    return !((*this) == aLine) ;
}

bool                            Line::isDefined                             ( ) const
{
    return origin_.isDefined() && direction_.isDefined() ;
}

bool                            Line::intersects                            (   const   Point&                      aPoint                                      ) const
{
    return this->contains(aPoint) ;
}

// bool                            Line::intersects                            (   const   Line&                       aLine                                       ) const
// {

// }

bool                            Line::intersects                            (   const   Plane&                      aPlane                                      ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Line") ;
    }

    if (!aPlane.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Plane") ;
    }

    const Vector3d n = aPlane.getNormalVector() ;
    const Vector3d v = direction_ ;

    const Vector3d Q_0 = aPlane.getPoint().asVector() ;
    const Vector3d P_0 = origin_.asVector() ;

    const double nDotV = n.dot(v) ;

    if (nDotV == 0.0) // Line and plane are parallel
    {
        return n.dot(Q_0 - P_0) == 0.0 ; // Line is in plane
    }

    return true ;

}

bool                            Line::intersects                            (   const   Sphere&                     aSphere                                     ) const
{
    return aSphere.intersects(*this) ;
}

bool                            Line::intersects                            (   const   Ellipsoid&                  anEllipsoid                                 ) const
{
    return anEllipsoid.intersects(*this) ;
}

bool                            Line::contains                              (   const   Point&                      aPoint                                      ) const
{

    if (!aPoint.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point") ;
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Line") ;
    }

    return direction_.cross(aPoint - origin_).squaredNorm() == 0.0 ;

}

bool                            Line::contains                              (   const   PointSet&                   aPointSet                                   ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Line") ;
    }

    if (aPointSet.isEmpty())
    {
        throw ostk::core::error::runtime::Undefined("Point Set") ;
    }

    for (auto& point : aPointSet)
    {
        if (!this->contains(point))
        {
            return false;
        }
    }

    return true ;

}

Point                           Line::getOrigin                             ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Line") ;
    }

    return origin_ ;

}

Vector3d                        Line::getDirection                          ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Line") ;
    }

    return direction_ ;

}

Real                            Line::distanceTo                            (   const   Point&                      aPoint                                      ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Line") ;
    }

    return this->getDirection().cross(aPoint - origin_).norm() ;

}

Intersection                    Line::intersectionWith                      (   const   Plane&                      aPlane                                      ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Line") ;
    }

    if (!aPlane.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Plane") ;
    }

    const Vector3d n = aPlane.getNormalVector() ;
    const Vector3d v = direction_ ;

    const Vector3d Q_0 = aPlane.getPoint().asVector() ;
    const Vector3d P_0 = origin_.asVector() ;

    const double nDotV = n.dot(v) ;

    if (nDotV == 0.0) // Line and plane are parallel
    {

        if (n.dot(Q_0 - P_0) == 0.0) // Line is in plane
        {
            return Intersection::Line(*this) ;
        }

        return Intersection::Empty() ;

    }

    const double t = n.dot(Q_0 - P_0) / nDotV ;

    return Intersection::Point(Point::Vector(P_0 + t * v)) ;

}

void                            Line::print                                 (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           ) const
{

    displayDecorators ? ostk::core::utils::Print::Header(anOutputStream, "Line") : void () ;

    ostk::core::utils::Print::Line(anOutputStream) << "Origin:"              << (origin_.isDefined() ? origin_.toString() : "Undefined") ;
    ostk::core::utils::Print::Line(anOutputStream) << "Direction:"           << (direction_.isDefined() ? direction_.toString() : "Undefined") ;

    displayDecorators ? ostk::core::utils::Print::Footer(anOutputStream) : void () ;

}

void                            Line::applyTransformation                   (   const   Transformation&             aTransformation                             )
{

    if (!aTransformation.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Transformation") ;
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Line") ;
    }

    origin_.applyTransformation(aTransformation) ;
    direction_ = aTransformation.applyTo(direction_) ;

}

Line                            Line::Undefined                             ( )
{
    return { Point::Undefined(), Vector3d::Undefined() } ;
}

Line                            Line::Points                                (   const   Point&                      aFirstPoint,
                                                                                const   Point&                      aSecondPoint                                )
{

    if (!aFirstPoint.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("First point") ;
    }

    if (!aSecondPoint.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Second point") ;
    }

    if (aFirstPoint == aSecondPoint)
    {
        throw ostk::core::error::RuntimeError("Points are identical.") ;
    }

    return { aFirstPoint, (aSecondPoint - aFirstPoint).normalized() } ;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
