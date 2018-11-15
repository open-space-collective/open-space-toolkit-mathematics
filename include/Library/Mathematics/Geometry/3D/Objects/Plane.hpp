////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Plane.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Mathematics_Geometry_3D_Objects_Plane__
#define __Library_Mathematics_Geometry_3D_Objects_Plane__

#include <Library/Mathematics/Geometry/3D/Objects/Point.hpp>
#include <Library/Mathematics/Geometry/3D/Object.hpp>
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
namespace objects
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::math::obj::Vector3d ;
using library::math::geom::d3::Object ;
using library::math::geom::d3::objects::Point ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Plane
///
///                             A plane is a flat, two-dimensional surface that extends infinitely far.
///
/// @ref                        https://en.wikipedia.org/wiki/Plane_(geometry)

class Plane : public Object
{

    public:

        /// @brief              Constructor
        ///
        /// @code
        ///                     Plane plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) ;
        /// @endcode
        ///
        /// @param              [in] aPoint A point
        /// @param              [in] aNormalVector A normal vector

                                Plane                                       (   const   Point&                      aPoint,
                                                                                const   Vector3d&                   aNormalVector                               ) ;

        /// @brief              Clone plane
        ///
        /// @return             Pointer to cloned plane

        virtual Plane*          clone                                       ( ) const override ;

        /// @brief              Equal to operator
        ///
        /// @code
        ///                     Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) ; // True
        /// @endcode
        ///
        /// @param              [in] aPlane A plane
        /// @return             True if planes are equal

        bool                    operator ==                                 (   const   Plane&                      aPlane                                      ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Plane({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0 }) ; // True
        /// @endcode
        ///
        /// @param              [in] aPlane A plane
        /// @return             True if planes are not equal

        bool                    operator !=                                 (   const   Plane&                      aPlane                                      ) const ;

        /// @brief              Check if plane is defined
        ///
        /// @code
        ///                     Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).isDefined() ; // True
        /// @endcode
        ///
        /// @return             True if plane is defined

        virtual bool            isDefined                                   ( ) const override ;

        /// @brief              Check if plane contains point
        ///
        /// @code
        ///                     Point plane = ... ;
        ///                     Point point = ... ;
        ///                     plane.contains(point) ;
        /// @endcode
        ///
        /// @param              [in] aPoint A point
        /// @return             True if plane contains point

        bool                    contains                                    (   const   Point&                      aPoint                                      ) const ;

        /// @brief              Get plane point
        ///
        /// @code
        ///                     Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).getPoint() ; // [0.0, 0.0, 0.0]
        /// @endcode
        ///
        /// @return             Plane point

        Point                   getPoint                                    ( ) const ;

        /// @brief              Get plane normal vector
        ///
        /// @code
        ///                     Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).getNormalVector() ; // [0.0, 0.0, 1.0]
        /// @endcode
        ///
        /// @return             Plane normal vector

        Vector3d                getNormalVector                             ( ) const ;

        /// @brief              Print plane
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] (optional) displayDecorators If true, display decorators

        virtual void            print                                       (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           =   true ) const override ;

        /// @brief              Apply transformation to plane
        ///
        /// @param              [in] aTransformation A transformation

        virtual void            applyTransformation                         (   const   Transformation&             aTransformation                             ) override ;

        /// @brief              Constructs an undefined plane
        ///
        /// @code
        ///                     Plane plane = Plane::Undefined() ; // Undefined
        /// @endcode
        ///
        /// @return             Undefined plane

        static Plane            Undefined                                   ( ) ;

    private:

        Point                   point_ ;
        Vector3d                normal_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////