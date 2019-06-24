////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Plane.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Intersection.hpp>
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

bool                            Plane::intersects                           (   const   Point&                      aPoint                                      ) const
{
    return this->contains(aPoint) ;
}

bool                            Plane::intersects                           (   const   PointSet&                   aPointSet                                   ) const
{

    if (!aPointSet.isDefined())
    {
        throw library::core::error::runtime::Undefined("Point Set") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Plane") ;
    }

    return (!aPointSet.isEmpty()) && std::any_of(aPointSet.begin(), aPointSet.end(), [this] (const Point& aPoint) -> bool { return this->contains(aPoint) ; }) ;

}

bool                            Plane::intersects                           (   const   Line&                       aLine                                       ) const
{
    return aLine.intersects(*this) ;
}

bool                            Plane::intersects                           (   const   Ray&                        aRay                                        ) const
{
    return aRay.intersects(*this) ;
}

bool                            Plane::intersects                           (   const   Segment&                    aSegment                                    ) const
{
    return aSegment.intersects(*this) ;
}

bool                            Plane::contains                             (   const   Point&                      aPoint                                      ) const
{

    if (!aPoint.isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Plane") ;
    }

    return (aPoint - point_).dot(normal_) == 0.0 ;

}

bool                            Plane::contains                             (   const   PointSet&                   aPointSet                                   ) const
{

    if (!aPointSet.isDefined())
    {
        throw library::core::error::runtime::Undefined("Point Set") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Plane") ;
    }

    return (!aPointSet.isEmpty()) && std::all_of(aPointSet.begin(), aPointSet.end(), [this] (const Point& aPoint) -> bool { return this->contains(aPoint) ; }) ;

}

bool                            Plane::contains                             (   const   Line&                       aLine                                       ) const
{

    if (!aLine.isDefined())
    {
        throw library::core::error::runtime::Undefined("Line") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Plane") ;
    }

    return this->contains(aLine.getOrigin()) && (normal_.dot(aLine.getDirection()) == 0.0) ;

}

bool                            Plane::contains                             (   const   Ray&                        aRay                                        ) const
{

    if (!aRay.isDefined())
    {
        throw library::core::error::runtime::Undefined("Ray") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Plane") ;
    }

    return this->contains(aRay.getOrigin()) && (normal_.dot(aRay.getDirection()) == 0.0) ;

}

bool                            Plane::contains                             (   const   Segment&                    aSegment                                    ) const
{

    if (!aSegment.isDefined())
    {
        throw library::core::error::runtime::Undefined("Segment") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Plane") ;
    }

    return this->contains(aSegment.getFirstPoint()) && this->contains(aSegment.getSecondPoint()) ;

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

Intersection                    Plane::intersectionWith                     (   const   Point&                      aPoint                                      ) const
{
    return this->contains(aPoint) ? Intersection::Point(aPoint) : Intersection::Empty() ;
}

Intersection                    Plane::intersectionWith                     (   const   PointSet&                   aPointSet                                   ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Plane") ;
    }

    Array<Point> points = Array<Point>::Empty() ;

    for (const auto& point : aPointSet)
    {

        if (this->contains(point))
        {
            points.add(point) ;
        }

    }

    return (!points.isEmpty()) ? ((points.getSize() == 1) ? Intersection::Point(points.accessFirst()) : Intersection::PointSet({ points })) : Intersection::Empty() ;

}

Intersection                    Plane::intersectionWith                     (   const   Line&                       aLine                                       ) const
{
    return aLine.intersectionWith(*this) ;
}

Intersection                    Plane::intersectionWith                     (   const   Ray&                        aRay                                        ) const
{
    return aRay.intersectionWith(*this) ;
}

Intersection                    Plane::intersectionWith                     (   const   Segment&                    aSegment                                    ) const
{
    return aSegment.intersectionWith(*this) ;
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
