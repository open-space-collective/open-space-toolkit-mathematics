////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/2D/Object.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/2D/Objects/Polygon.hpp>
#include <Library/Mathematics/Geometry/2D/Objects/Point.hpp>
#include <Library/Mathematics/Geometry/2D/Object.hpp>

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Object::~Object                             ( )
{

}

bool                            Object::operator ==                         (   const   Object&                     anObject                                    ) const
{

    using library::math::geom::d2::objects::Point ;
    using library::math::geom::d2::objects::Polygon ;

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

    if (const Polygon* objectPtr = dynamic_cast<const Polygon*>(this))
    {

        if (const Polygon* otherObjectPtr = dynamic_cast<const Polygon*>(&anObject))
        {
            return (*objectPtr) == (*otherObjectPtr) ;
        }

    }

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

    using library::math::geom::d2::objects::Point ;
    using library::math::geom::d2::objects::Polygon ;

    if (!anObject.isDefined())
    {
        throw library::core::error::runtime::Undefined("Object") ;
    }

    throw library::core::error::runtime::ToBeImplemented("Object :: intersects") ;

    return false ;

}

bool                            Object::contains                            (   const   Object&                     anObject                                    ) const
{

    using library::math::geom::d2::objects::Point ;
    using library::math::geom::d2::objects::Polygon ;

    if (!anObject.isDefined())
    {
        throw library::core::error::runtime::Undefined("Object") ;
    }

    throw library::core::error::runtime::ToBeImplemented("Object :: contains") ;

    return false ;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////