////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Point.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Mathematics_Geometry_3D_Objects_Point__
#define __Library_Mathematics_Geometry_3D_Objects_Point__

#include <Library/Mathematics/Geometry/3D/Object.hpp>
#include <Library/Mathematics/Objects/Vector.hpp>
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
using library::math::obj::Vector3d ;
using library::math::geom::d3::Object ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Point
///
/// @ref                        https://en.wikipedia.org/wiki/Point_(geometry)

class Point : public Object, public Vector3d
{

    public:

        /// @brief              Constructor
        ///
        /// @code
        ///                     Point point(0.0, 0.0, 0.0) ;
        /// @endcode
        ///
        /// @param              [in] aFirstCoordinate A first coordinate
        /// @param              [in] aSecondCoordinate A second coordinate
        /// @param              [in] aThirdCoordinate A third coordinate

                                Point                                       (   const   Real&                       aFirstCoordinate,
                                                                                const   Real&                       aSecondCoordinate,
                                                                                const   Real&                       aThirdCoordinate                            ) ;

        /// @brief              Constructor
        ///
        /// @code
        ///                     Point point({ 0.0, 0.0, 0.0 }) ;
        /// @endcode
        ///
        /// @param              [in] aVector A position vector

                                Point                                       (   const   Vector3d&                   aVector                                     ) ;

        /// @brief              Clone point
        ///
        /// @return             Pointer to cloned point

        virtual Point*          clone                                       ( ) const override ;

        /// @brief              Output stream operator
        ///
        /// @code
        ///                     std::cout << Point(0.0, 0.0, 0.0) ;
        /// @endcode
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] aPoint A point
        /// @return             An output stream

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Point&                      aPoint                                      ) ;

        /// @brief              Check if point is defined
        ///
        /// @code
        ///                     Point(Vector3d::Zero(), 1.0).isDefined() ; // True
        /// @endcode
        ///
        /// @return             True if point is defined

        virtual bool            isDefined                                   ( ) const override ;

        /// @brief              Constructs an undefined point
        ///
        /// @code
        ///                     Point point = Point::Undefined() ; // Undefined
        /// @endcode
        ///
        /// @return             Undefined point

        static Point            Undefined                                   ( ) ;

        /// @brief              Constructs a point at origin
        ///
        /// @code
        ///                     Point point = Point::Origin() ; // [0.0, 0.0, 0.0]
        /// @endcode
        ///
        /// @return             Point at origin

        static Point            Origin                                      ( ) ;

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