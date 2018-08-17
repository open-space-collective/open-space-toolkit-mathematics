////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Mathematics_Geometry_3D_Objects_Ellipsoid__
#define __Library_Mathematics_Geometry_3D_Objects_Ellipsoid__

#include <Library/Mathematics/Geometry/Transformations/Rotations/Quaternion.hpp>
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
using library::math::geom::trf::rot::Quaternion ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Ellipsoid
///
/// @ref                        https://en.wikipedia.org/wiki/Ellipsoid

class Ellipsoid : public Object
{

    public:

        /// @brief              Constructor
        ///
        /// @code
        ///                     Ellipsoid ellipsoid({ 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0) ;
        /// @endcode
        ///
        /// @param              [in] aCenter An ellipsoid center
        /// @param              [in] aFirstPrincipalSemiAxis An ellipsoid first principal semi-axis
        /// @param              [in] aSecondPrincipalSemiAxis An ellipsoid second principal semi-axis
        /// @param              [in] aThirdPrincipalSemiAxis An ellipsoid third principal semi-axis
        /// @param              [in] (optional) anOrientation An ellipsoid orientation

                                Ellipsoid                                   (   const   Point&                      aCenter,
                                                                                const   Real&                       aFirstPrincipalSemiAxis,
                                                                                const   Real&                       aSecondPrincipalSemiAxis,
                                                                                const   Real&                       aThirdPrincipalSemiAxis,
                                                                                const   Quaternion&                 anOrientation                               =   Quaternion::Unit() ) ;

        /// @brief              Clone ellipsoid
        ///
        /// @return             Pointer to cloned ellipsoid

        virtual Ellipsoid*      clone                                       ( ) const override ;

        /// @brief              Equal to operator
        ///
        /// @code
        ///                     Ellipsoid(Point::Origin(), 1.0, 2.0, 3.0) == Ellipsoid(Point::Origin(), 1.0, 2.0, 3.0) ; // True
        /// @endcode
        ///
        /// @param              [in] anEllipsoid An ellipsoid
        /// @return             True if ellipsoids are equal

        bool                    operator ==                                 (   const   Ellipsoid&                  anEllipsoid                                 ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     Ellipsoid(Point::Origin(), 1.0, 2.0, 3.0) != Ellipsoid(2.0, 1.0, 3.0) ; // True
        /// @endcode
        ///
        /// @param              [in] anEllipsoid An ellipsoid
        /// @return             True if ellipsoids not are equal

        bool                    operator !=                                 (   const   Ellipsoid&                  anEllipsoid                                 ) const ;

        /// @brief              Output stream operator
        ///
        /// @code
        ///                     std::cout << Ellipsoid(Point::Origin(), 1.0, 2.0, 3.0) ;
        /// @endcode
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] anEllipsoid An ellipsoid
        /// @return             An output stream

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Ellipsoid&                  anEllipsoid                                 ) ;

        /// @brief              Check if ellipsoid is defined
        ///
        /// @code
        ///                     Ellipsoid(Point::Origin(), 1.0, 2.0, 3.0).isDefined() ; // True
        /// @endcode
        ///
        /// @return             True if ellipsoid is defined

        virtual bool            isDefined                                   ( ) const override ;

        /// @brief              Get ellipsoid center
        ///
        /// @code
        ///                     Ellipsoid(Point::Origin(), 1.0, 2.0, 3.0).getCenter() ; // [0.0, 0.0, 0.0]
        /// @endcode
        ///
        /// @return             Ellipsoid center

        Point                   getCenter                                   ( ) const ;

        /// @brief              Get ellipsoid first principal semi-axis
        ///
        /// @code
        ///                     Ellipsoid(Point::Origin(), 1.0, 2.0, 3.0).getRadius() ; // 1.0
        /// @endcode
        ///
        /// @return             Ellipsoid first principal semi-axis

        Real                    getFirstPrincipalSemiAxis                   ( ) const ;

        /// @brief              Get ellipsoid second principal semi-axis
        ///
        /// @code
        ///                     Ellipsoid(Point::Origin(), 1.0, 2.0, 3.0).getRadius() ; // 2.0
        /// @endcode
        ///
        /// @return             Ellipsoid second principal semi-axis

        Real                    getSecondPrincipalSemiAxis                  ( ) const ;

        /// @brief              Get ellipsoid third principal semi-axis
        ///
        /// @code
        ///                     Ellipsoid(Point::Origin(), 1.0, 2.0, 3.0).getRadius() ; // 3.0
        /// @endcode
        ///
        /// @return             Ellipsoid third principal semi-axis

        Real                    getThirdPrincipalSemiAxis                   ( ) const ;

        /// @brief              Get ellipsoid orientation
        ///
        /// @code
        ///                     Ellipsoid(Point::Origin(), 1.0, 2.0, 3.0, Quaternion::XYZS(0.0, 0.0, 0.0, 1.0)).getRadius() ; // Quaternion::XYZS(0.0, 0.0, 0.0, 1.0)
        /// @endcode
        ///
        /// @return             Ellipsoid orientation

        Quaternion              getOrientation                              ( ) const ;

        /// @brief              Constructs an undefined ellipsoid
        ///
        /// @code
        ///                     Ellipsoid ellipsoid = Ellipsoid::Undefined() ; // Undefined
        /// @endcode
        ///
        /// @return             Undefined ellipsoid

        static Ellipsoid        Undefined                                   ( ) ;

    private:

        Point                   center_ ;

        Real                    a_ ;
        Real                    b_ ;
        Real                    c_ ;

        Quaternion              q_ ;

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