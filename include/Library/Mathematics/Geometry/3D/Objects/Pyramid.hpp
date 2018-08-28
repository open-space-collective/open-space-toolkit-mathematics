////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Pyramid.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Mathematics_Geometry_3D_Objects_Pyramid__
#define __Library_Mathematics_Geometry_3D_Objects_Pyramid__

#include <Library/Mathematics/Geometry/3D/Objects/Polygon.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Point.hpp>
#include <Library/Mathematics/Geometry/3D/Object.hpp>

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

using library::math::geom::d3::Object ;
using library::math::geom::d3::objects::Point ;
using library::math::geom::d3::objects::Polygon ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Pyramid
///
///                             A pyramid is a polyhedron formed by connecting a polygonal base and a point, called the apex.
///                             Each base edge and apex form a triangle, called a lateral face.
///
/// @ref                        https://en.wikipedia.org/wiki/Pyramid_(geometry)

class Pyramid : public Object
{

    public:

        /// @brief              Constructor
        ///
        /// @code
        ///                     Polygon base = ... ;
        ///                     Point apex = { 0.0, 0.0, 1.0 } ;
        ///                     Pyramid pyramid = { base, apex } ;
        /// @endcode
        ///
        /// @param              [in] aBase A pyramid base
        /// @param              [in] anApex A pyramid apex

                                Pyramid                                     (   const   Polygon&                    aBase,
                                                                                const   Point&                      anApex                                      ) ;

        /// @brief              Clone pyramid
        ///
        /// @return             Pointer to cloned pyramid

        virtual Pyramid*        clone                                       ( ) const override ;

        /// @brief              Equal to operator
        ///
        /// @param              [in] aPyramid A pyramid
        /// @return             True if pyramids are equal

        bool                    operator ==                                 (   const   Pyramid&                    aPyramid                                    ) const ;

        /// @brief              Not equal to operator
        ///
        /// @param              [in] aPyramid A pyramid
        /// @return             True if pyramids not are equal

        bool                    operator !=                                 (   const   Pyramid&                    aPyramid                                    ) const ;

        /// @brief              Output stream operator
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] aPyramid A pyramid
        /// @return             A reference to output stream

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Pyramid&                    aPyramid                                    ) ;

        /// @brief              Check if pyramid is defined
        ///
        /// @return             True if pyramid is defined

        virtual bool            isDefined                                   ( ) const override ;

        /// @brief              Get pyramid base
        ///
        /// @return             Pyramid base

        Polygon                 getBase                                     ( ) const ;

        /// @brief              Get pyramid apex
        ///
        /// @return             Pyramid apex

        Point                   getApex                                     ( ) const ;

        /// @brief              Translate pyramid
        ///
        /// @param              [in] aTranslation A translation vector

        virtual void            translate                                   (   const   Vector3d&                   aTranslation                                ) override ;

        /// @brief              Rotate pyramid
        ///
        /// @param              [in] aRotation A rotation quaternion
        
        virtual void            rotate                                      (   const   Quaternion&                 aRotation                                   ) override ;

        /// @brief              Constructs an undefined pyramid
        ///
        /// @return             Undefined pyramid

        static Pyramid          Undefined                                   ( ) ;

    private:

        Polygon                 base_ ;
        Point                   apex_ ;

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