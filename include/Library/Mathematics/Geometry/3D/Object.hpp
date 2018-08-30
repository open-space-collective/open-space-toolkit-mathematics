////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Object.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Mathematics_Geometry_3D_Object__
#define __Library_Mathematics_Geometry_3D_Object__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/Transformations/Rotations/Quaternion.hpp>
#include <Library/Mathematics/Objects/Vector.hpp>

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

using library::math::obj::Vector3d ;
using library::math::geom::trf::rot::Quaternion ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Intersection ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      3D object

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

        /// @brief              Translate object
        ///
        /// @param              [in] aTranslation Translation vector

        virtual void            translate                                   (   const   Vector3d&                   aTranslation                                ) = 0 ;

        /// @brief              Rotate object around its center, using passive transformation (alias)
        ///
        /// @param              [in] aRotation Rotation quaternion
        
        virtual void            rotate                                      (   const   Quaternion&                 aRotation                                   ) = 0 ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////