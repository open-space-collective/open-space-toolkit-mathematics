////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Object.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Mathematics_Geometry_3D_Object__
#define __Library_Mathematics_Geometry_3D_Object__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/Error.hpp>

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

class Transformation ;
class Intersection ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      3D object

class Object
{

    public:

        /// @brief              Default constructor (default)

                                Object                                      ( ) = default ;

        /// @brief              Destructor (pure virtual)

        virtual                 ~Object                                     ( ) = 0 ;

        /// @brief              Clone object (pure virtual)
        ///
        /// @return             Pointer to cloned object

        virtual Object*         clone                                       ( ) const = 0 ;

        /// @brief              Equal to operator
        ///
        /// @param              [in] anObject An object
        /// @return             True if objects are equal

        bool                    operator ==                                 (   const   Object&                     anObject                                    ) const ;

        /// @brief              Not equal to operator
        ///
        /// @param              [in] anObject An object
        /// @return             True if objects are not equal

        bool                    operator !=                                 (   const   Object&                     anObject                                    ) const ;

        /// @brief              Output stream operator
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] anObject An object
        /// @return             A reference to output stream

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Object&                     anObject                                    ) ;

        /// @brief              Check if object is defined
        ///
        /// @return             True if object is defined

        virtual bool            isDefined                                   ( ) const = 0 ;

        /// @brief              Returns true if object can be converted to type
        ///
        /// @return             True if object can be converted to type

        template <class Type>
        bool                    is                                          ( ) const
        {
            return dynamic_cast<const Type*>(this) != nullptr ;
        }

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

        /// @brief              Access object as its underlying type
        ///
        /// @return             Reference to underlying type

        template <class Type>
        const Type&             as                                          ( ) const
        {

            const Type* objectPtr = dynamic_cast<const Type*>(this) ;

            if (objectPtr == nullptr)
            {
                throw library::core::error::RuntimeError("Cannot convert object to underlying type.") ;
            }

            return *objectPtr ;

        }

        /// @brief              Compute intersection of object with another object
        ///
        /// @code
        ///                     Unique<Object> objectUPtr = ... ;
        ///                     Unique<Object> anotherObjectUPtr = ... ;
        ///                     Intersection intersection = objectUPtr->intersectionWith(*anotherObjectUPtr) ;
        /// @endcode
        ///
        /// @param              [in] anObject An object
        /// @return             Intersection of object with another object

        virtual Intersection    intersectionWith                            (   const   Object&                     anObject                                    ) const ;

        /// @brief              Print object
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] (optional) displayDecorators If true, display decorators

        virtual void            print                                       (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           =   true ) const = 0 ;

        /// @brief              Apply transformation to object
        ///
        /// @param              [in] aTransformation A transformation

        virtual void            applyTransformation                         (   const   Transformation&             aTransformation                             ) = 0 ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////