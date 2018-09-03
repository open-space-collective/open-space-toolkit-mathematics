////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Object.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Intersection.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Pyramid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Sphere.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Polygon.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Plane.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ray.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Line.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Point.hpp>
#include <Library/Mathematics/Geometry/3D/Object.hpp>

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Object::~Object                             ( )
{

}

bool                            Object::operator ==                         (   const   Object&                     anObject                                    ) const
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Line ;
    using library::math::geom::d3::objects::Ray ;
    using library::math::geom::d3::objects::Segment ;
    using library::math::geom::d3::objects::Plane ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Sphere ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::d3::objects::Pyramid ;

    if ((!this->isDefined()) || (!anObject.isDefined()))
    {
        return false ;
    }

    if (typeid(*this) != typeid(anObject))
    {
        return false ;
    }

    // Point

    if (const Point* objectPtr = dynamic_cast<const Point*>(this))
    {

        if (const Point* otherObjectPtr = dynamic_cast<const Point*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr) ;
        }

    }

    // Line

    if (const Line* objectPtr = dynamic_cast<const Line*>(this))
    {

        if (const Line* otherObjectPtr = dynamic_cast<const Line*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr) ;
        }

    }

    // Ray

    if (const Ray* objectPtr = dynamic_cast<const Ray*>(this))
    {

        if (const Ray* otherObjectPtr = dynamic_cast<const Ray*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr) ;
        }

    }

    // Segment

    if (const Segment* objectPtr = dynamic_cast<const Segment*>(this))
    {

        if (const Segment* otherObjectPtr = dynamic_cast<const Segment*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr) ;
        }

    }

    // Plane

    if (const Plane* objectPtr = dynamic_cast<const Plane*>(this))
    {

        if (const Plane* otherObjectPtr = dynamic_cast<const Plane*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr) ;
        }

    }

    // Polygon

    if (const Polygon* objectPtr = dynamic_cast<const Polygon*>(this))
    {

        if (const Polygon* otherObjectPtr = dynamic_cast<const Polygon*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr) ;
        }

    }

    // Sphere

    if (const Sphere* objectPtr = dynamic_cast<const Sphere*>(this))
    {

        if (const Sphere* otherObjectPtr = dynamic_cast<const Sphere*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr) ;
        }

    }

    // Ellipsoid

    if (const Ellipsoid* objectPtr = dynamic_cast<const Ellipsoid*>(this))
    {

        if (const Ellipsoid* otherObjectPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr) ;
        }

    }

    // Pyramid

    if (const Pyramid* objectPtr = dynamic_cast<const Pyramid*>(this))
    {

        if (const Pyramid* otherObjectPtr = dynamic_cast<const Pyramid*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr) ;
        }

    }

    throw library::core::error::runtime::ToBeImplemented("Object :: operator ==") ;

    return false ;

}

bool                            Object::operator !=                         (   const   Object&                     anObject                                    ) const
{
    return !((*this) == anObject) ;
}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Object&                     anObject                                    )
{

    anObject.print(anOutputStream, true) ;

    return anOutputStream ;

}

bool                            Object::intersects                          (   const   Object&                     anObject                                    ) const
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Line ;
    using library::math::geom::d3::objects::Ray ;
    using library::math::geom::d3::objects::Segment ;
    using library::math::geom::d3::objects::Plane ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Sphere ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::d3::objects::Pyramid ;

    if (!anObject.isDefined())
    {
        throw library::core::error::runtime::Undefined("Object") ;
    }

    // Line

    if (const Line* objectPtr = dynamic_cast<const Line*>(this))
    {

        // if (const Line* otherObjectPtr = dynamic_cast<const Line*>(&anObject))
        // {
        //     return objectPtr->intersects(*otherObjectPtr) ;
        // }

        if (const Ellipsoid* otherObjectPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr) ;
        }

    }

    // Ray

    if (const Ray* objectPtr = dynamic_cast<const Ray*>(this))
    {

        // if (const Ray* otherObjectPtr = dynamic_cast<const Ray*>(&anObject))
        // {
        //     return objectPtr->intersects(*otherObjectPtr) ;
        // }

        if (const Ellipsoid* otherObjectPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr) ;
        }

    }

    // Segment

    if (const Segment* objectPtr = dynamic_cast<const Segment*>(this))
    {

        // if (const Segment* otherObjectPtr = dynamic_cast<const Segment*>(&anObject))
        // {
        //     return objectPtr->intersects(*otherObjectPtr) ;
        // }

        if (const Ellipsoid* otherObjectPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr) ;
        }

    }

    // Ellipsoid

    if (const Ellipsoid* objectPtr = dynamic_cast<const Ellipsoid*>(this))
    {

        // Segment

        if (const Segment* otherObjectPtr = dynamic_cast<const Segment*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr) ;
        }

        // Ellipsoid

        // if (const Ellipsoid* otherObjectPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        // {
        //     return objectPtr->intersects(*otherObjectPtr) ;
        // }

        // Pyramid

        if (const Pyramid* otherObjectPtr = dynamic_cast<const Pyramid*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr) ;
        }

    }

    // Pyramid

    if (const Pyramid* objectPtr = dynamic_cast<const Pyramid*>(this))
    {

        // Ellipsoid

        if (const Ellipsoid* otherObjectPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        {
            return objectPtr->intersects(*otherObjectPtr) ;
        }

    }

    throw library::core::error::runtime::ToBeImplemented("Object :: intersects") ;

    return false ;

}

bool                            Object::contains                            (   const   Object&                     anObject                                    ) const
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Line ;
    using library::math::geom::d3::objects::Ray ;
    using library::math::geom::d3::objects::Segment ;
    using library::math::geom::d3::objects::Plane ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Sphere ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::d3::objects::Pyramid ;

    if (!anObject.isDefined())
    {
        throw library::core::error::runtime::Undefined("Object") ;
    }

    // Segment

    // if (const Segment* objectPtr = dynamic_cast<const Segment*>(this))
    // {

        // Segment

        // if (const Segment* otherObjectPtr = dynamic_cast<const Segment*>(&anObject))
        // {
        //     return objectPtr->contains(*otherObjectPtr) ;
        // }

        // Ellipsoid

        // if (const Ellipsoid* otherObjectPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        // {
        //     return objectPtr->contains(*otherObjectPtr) ;
        // }

    // }

    // Ellipsoid

    if (const Ellipsoid* objectPtr = dynamic_cast<const Ellipsoid*>(this))
    {

        // Segment

        if (const Segment* otherObjectPtr = dynamic_cast<const Segment*>(&anObject))
        {
            return objectPtr->contains(*otherObjectPtr) ;
        }

        // Ellipsoid

        // if (const Ellipsoid* otherObjectPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        // {
        //     return objectPtr->contains(*otherObjectPtr) ;
        // }

    }

    throw library::core::error::runtime::ToBeImplemented("Object :: contains") ;

    return false ;

}
        
Intersection                    Object::intersectionWith                    (   const   Object&                     anObject                                    ) const
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Line ;
    using library::math::geom::d3::objects::Ray ;
    using library::math::geom::d3::objects::Segment ;
    using library::math::geom::d3::objects::Plane ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Sphere ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::d3::objects::Pyramid ;

    if (!anObject.isDefined())
    {
        throw library::core::error::runtime::Undefined("Object") ;
    }

    // Ray

    if (const Ray* objectPtr = dynamic_cast<const Ray*>(this))
    {

        // Ellipsoid

        if (const Ellipsoid* otherObjectPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        {
            return objectPtr->intersectionWith(*otherObjectPtr) ;
        }

    }

    // Ellipsoid

    if (const Ellipsoid* objectPtr = dynamic_cast<const Ellipsoid*>(this))
    {

        // Ray

        if (const Ray* otherObjectPtr = dynamic_cast<const Ray*>(&anObject))
        {
            return objectPtr->intersectionWith(*otherObjectPtr) ;
        }

    }

    // Pyramid

    if (const Pyramid* objectPtr = dynamic_cast<const Pyramid*>(this))
    {

        // Ellipsoid

        if (const Ellipsoid* otherObjectPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        {
            return objectPtr->intersectionWith(*otherObjectPtr) ;
        }

    }

    throw library::core::error::runtime::ToBeImplemented("Object :: intersectionWith") ;

    return Intersection::Undefined() ;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////