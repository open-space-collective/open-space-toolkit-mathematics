////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Sphere.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Mathematics_Geometry_3D_Objects_Sphere__
#define __Library_Mathematics_Geometry_3D_Objects_Sphere__

#include <Library/Mathematics/Geometry/3D/Objects/Point.hpp>
#include <Library/Mathematics/Geometry/3D/Object.hpp>

#include <Library/Core/Types/Real.hpp>

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

using library::core::types::Real ;

using library::math::geom::d3::Object ;
using library::math::geom::d3::objects::Point ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Sphere
///
///                             A sphere is a perfectly round geometrical object in three-dimensional space that is the surface of a completely round ball.
///
/// @ref                        https://en.wikipedia.org/wiki/Sphere

class Sphere : public Object
{

    public:

        /// @brief              Constructor
        ///
        /// @code
        ///                     Sphere sphere({ 0.0, 0.0, 0.0 }, 1.0) ;
        /// @endcode
        ///
        /// @param              [in] aCenter A sphere center
        /// @param              [in] aRadius A sphere radius

                                Sphere                                      (   const   Point&                      aCenter,
                                                                                const   Real&                       aRadius                                     ) ;

        /// @brief              Clone sphere
        ///
        /// @return             Pointer to cloned sphere

        virtual Sphere*         clone                                       ( ) const override ;

        /// @brief              Equal to operator
        ///
        /// @code
        ///                     Sphere(Point::Origin(), 1.0) == Sphere(Point::Origin(), 1.0) ; // True
        /// @endcode
        ///
        /// @param              [in] aSphere A sphere
        /// @return             True if spheres are equal

        bool                    operator ==                                 (   const   Sphere&                     aSphere                                     ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     Sphere(Point::Origin(), 1.0) != Sphere(Point::Origin(), 2.0) ; // True
        /// @endcode
        ///
        /// @param              [in] aSphere A sphere
        /// @return             True if spheres not are equal

        bool                    operator !=                                 (   const   Sphere&                     aSphere                                     ) const ;

        /// @brief              Check if sphere is defined
        ///
        /// @code
        ///                     Sphere(Point::Origin(), 1.0).isDefined() ; // True
        /// @endcode
        ///
        /// @return             True if sphere is defined

        virtual bool            isDefined                                   ( ) const override ;

        /// @brief              Check if sphere is unitary, i.e. its radius is equal to 1.0
        ///
        /// @code
        ///                     Sphere(Point::Origin(), 1.0).isUnitary() ; // True
        /// @endcode
        ///
        /// @return             True if sphere is unitary

        bool                    isUnitary                                   ( ) const ;

        /// @brief              Get sphere center
        ///
        /// @code
        ///                     Sphere(Point::Origin(), 1.0).getCenter() ; // [0.0, 0.0, 0.0]
        /// @endcode
        ///
        /// @return             Sphere center

        Point                   getCenter                                   ( ) const ;

        /// @brief              Get sphere radius
        ///
        /// @code
        ///                     Sphere(Point::Origin(), 1.0).getRadius() ; // 1.0
        /// @endcode
        ///
        /// @return             Sphere radius

        Real                    getRadius                                   ( ) const ;

        /// @brief              Print sphere
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] (optional) displayDecorators If true, display decorators

        virtual void            print                                       (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           =   true ) const override ;

        /// @brief              Apply transformation to sphere
        ///
        /// @param              [in] aTransformation A transformation

        virtual void            applyTransformation                         (   const   Transformation&             aTransformation                             ) override ;

        /// @brief              Constructs an undefined sphere
        ///
        /// @code
        ///                     Sphere sphere = Sphere::Undefined() ; // Undefined
        /// @endcode
        ///
        /// @return             Undefined sphere

        static Sphere           Undefined                                   ( ) ;

        /// @brief              Constructs a unit sphere
        ///
        /// @ref                https://en.wikipedia.org/wiki/Unit_sphere
        ///
        /// @code
        ///                     Sphere sphere = Sphere::Unit({ 0.0, 0.0, 0.0 }) ;
        /// @endcode
        ///
        /// @return             Unit sphere

        static Sphere           Unit                                        (   const   Point&                      aCenter                                     ) ;

    private:

        Point                   center_ ;
        Real                    radius_ ;

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