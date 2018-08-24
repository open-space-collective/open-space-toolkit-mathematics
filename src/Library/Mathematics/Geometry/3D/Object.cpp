////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Object.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Sphere.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Point.hpp>
#include <Library/Mathematics/Geometry/3D/Intersection.hpp>
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
    using library::math::geom::d3::objects::Segment ;
    using library::math::geom::d3::objects::Sphere ;
    using library::math::geom::d3::objects::Ellipsoid ;

    if ((!this->isDefined()) && (!anObject.isDefined()))
    {
        return false ;
    }

    if (typeid(*this) != typeid(anObject))
    {
        return false ;
    }

    if (const Point* objectPtr = dynamic_cast<const Point*>(this))
    {

        if (const Point* otherObjectPtr = dynamic_cast<const Point*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr) ;
        }

    }

    if (const Segment* objectPtr = dynamic_cast<const Segment*>(this))
    {

        if (const Segment* otherObjectPtr = dynamic_cast<const Segment*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr) ;
        }

    }

    if (const Sphere* objectPtr = dynamic_cast<const Sphere*>(this))
    {

        if (const Sphere* otherObjectPtr = dynamic_cast<const Sphere*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr) ;
        }

    }

    if (const Ellipsoid* objectPtr = dynamic_cast<const Ellipsoid*>(this))
    {

        if (const Ellipsoid* otherObjectPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr) ;
        }

    }

    return false ;

}

bool                            Object::intersects                          (   const   Object&                     anObject                                    ) const
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Segment ;
    using library::math::geom::d3::objects::Sphere ;
    using library::math::geom::d3::objects::Ellipsoid ;

    if (!anObject.isDefined())
    {
        throw library::core::error::runtime::Undefined("Object") ;
    }

    // Segment

    if (const Segment* segmentPtr = dynamic_cast<const Segment*>(this))
    {

        // if (const Segment* otherSegmentPtr = dynamic_cast<const Segment*>(&anObject))
        // {
        //     return segmentPtr->intersects(*otherSegmentPtr) ;
        // }

        if (const Ellipsoid* otherEllipsoidPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        {
            return segmentPtr->intersects(*otherEllipsoidPtr) ;
        }

    }

    // Ellipsoid

    if (const Ellipsoid* ellipsoidPtr = dynamic_cast<const Ellipsoid*>(this))
    {

        if (const Segment* otherSegmentPtr = dynamic_cast<const Segment*>(&anObject))
        {
            return ellipsoidPtr->intersects(*otherSegmentPtr) ;
        }

        // if (const Ellipsoid* otherEllipsoidPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        // {
        //     return ellipsoidPtr->intersects(*otherEllipsoidPtr) ;
        // }

    }

    throw library::core::error::runtime::ToBeImplemented("Object :: intersects") ;

    return false ;

}

bool                            Object::contains                            (   const   Object&                     anObject                                    ) const
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Segment ;
    using library::math::geom::d3::objects::Sphere ;
    using library::math::geom::d3::objects::Ellipsoid ;

    if (!anObject.isDefined())
    {
        throw library::core::error::runtime::Undefined("Object") ;
    }

    // Segment

    if (const Segment* segmentPtr = dynamic_cast<const Segment*>(this))
    {

        // if (const Segment* otherSegmentPtr = dynamic_cast<const Segment*>(&anObject))
        // {
        //     return segmentPtr->contains(*otherSegmentPtr) ;
        // }

        // if (const Ellipsoid* otherEllipsoidPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        // {
        //     return segmentPtr->contains(*otherEllipsoidPtr) ;
        // }

    }

    // Ellipsoid

    if (const Ellipsoid* ellipsoidPtr = dynamic_cast<const Ellipsoid*>(this))
    {

        if (const Segment* otherSegmentPtr = dynamic_cast<const Segment*>(&anObject))
        {
            return ellipsoidPtr->contains(*otherSegmentPtr) ;
        }

        // if (const Ellipsoid* otherEllipsoidPtr = dynamic_cast<const Ellipsoid*>(&anObject))
        // {
        //     return ellipsoidPtr->contains(*otherEllipsoidPtr) ;
        // }

    }

    throw library::core::error::runtime::ToBeImplemented("Object :: contains") ;

    return false ;

}
        
Intersection                    Object::computeIntersectionWith             (   const   Object&                     anObject                                    ) const
{

    if (!anObject.isDefined())
    {
        throw library::core::error::runtime::Undefined("Object") ;
    }

    throw library::core::error::runtime::ToBeImplemented("Object :: computeIntersectionWith") ;

    return Intersection::Undefined() ;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////