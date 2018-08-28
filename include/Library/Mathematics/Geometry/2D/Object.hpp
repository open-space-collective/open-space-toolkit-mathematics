////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/2D/Object.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Mathematics_Geometry_2D_Object__
#define __Library_Mathematics_Geometry_2D_Object__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Objects/Vector.hpp>

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

using library::math::obj::Vector2d ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      2D object

class Object
{

    public:

        /// @brief              Default constructor

                                Object                                      ( ) = default ;

        /// @brief              Destructor (pure virtual)

        virtual                 ~Object                                     ( ) = 0 ;

        /// @brief              Clone object (pure virtual)
        ///
        /// @return             Pointer to cloned object

        virtual Object*         clone                                       ( ) const = 0 ;

        bool                    operator ==                                 (   const   Object&                     anObject                                    ) const ;

        bool                    operator !=                                 (   const   Object&                     anObject                                    ) const ;

        /// @brief              Check if object is defined
        ///
        /// @return             True if object is defined

        virtual bool            isDefined                                   ( ) const = 0 ;

        /// @brief              Check if object intersects another object
        ///
        /// @code
        ///                     Unique<Object> objectUPtr = ... ;
        ///                     Unique<Object> anotherObjectUPtr = ... ;
        ///                     objectUPtr->intersects(*anotherObjectUPtr) ;
        /// @endcode
        ///
        /// @param              [in] anObject An object
        /// @return             True if object intersects another object
        
        virtual bool            intersects                                  (   const   Object&                     anObject                                    ) const ;

        /// @brief              Check if object contains another object
        ///
        /// @code
        ///                     Unique<Object> objectUPtr = ... ;
        ///                     Unique<Object> anotherObjectUPtr = ... ;
        ///                     objectUPtr->contains(*anotherObjectUPtr) ;
        /// @endcode
        ///
        /// @param              [in] anObject An object
        /// @return             True if object contains another object

        virtual bool            contains                                    (   const   Object&                     anObject                                    ) const ;

        virtual void            translate                                   (   const   Vector2d&                   aTranslation                                ) = 0 ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////