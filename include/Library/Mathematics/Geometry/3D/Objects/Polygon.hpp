////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Polygon.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Mathematics_Geometry_3D_Objects_Polygon__
#define __Library_Mathematics_Geometry_3D_Objects_Polygon__

#include <Library/Mathematics/Geometry/3D/Objects/Plane.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Point.hpp>
#include <Library/Mathematics/Geometry/3D/Object.hpp>
#include <Library/Mathematics/Geometry/2D/Objects/Polygon.hpp>

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

using Polygon2d = library::math::geom::d2::objects::Polygon ;

using library::math::geom::d3::Object ;
using library::math::geom::d3::objects::Point ;
using library::math::geom::d3::objects::Plane ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Polygon
///
///                             A polygon is a plane figure that is bounded by a finite chain of straight line segments closing in a loop
///                             to form a closed polygonal chain or circuit.
///                             These segments are called its edges, and the points where two edges meet are the polygon's vertices.
///
/// @ref                        https://en.wikipedia.org/wiki/Polygon

class Polygon : public Object
{

    public:

        /// @brief              Constructor
        ///
        /// @code
        ///                     
        /// @endcode
        ///
        /// @param              [in] aBase A polygon base
        /// @param              [in] anApex A polygon apex

                                // Polygon                                     (   const   Polygon2d&                  aPolygon,
                                //                                                 const   Point&                      anApex                                      ) ;

        /// @brief              Clone polygon
        ///
        /// @return             Pointer to cloned polygon

        virtual Polygon*        clone                                       ( ) const override ;

        /// @brief              Equal to operator
        ///
        /// @code
        ///                     
        /// @endcode
        ///
        /// @param              [in] aPolygon A polygon
        /// @return             True if polygons are equal

        bool                    operator ==                                 (   const   Polygon&                    aPolygon                                    ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     
        /// @endcode
        ///
        /// @param              [in] aPolygon A polygon
        /// @return             True if polygons not are equal

        bool                    operator !=                                 (   const   Polygon&                    aPolygon                                    ) const ;

        /// @brief              Output stream operator
        ///
        /// @code
        ///                     std::cout << Polygon(...) ;
        /// @endcode
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] aPolygon A polygon
        /// @return             An output stream

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Polygon&                    aPolygon                                    ) ;

        /// @brief              Check if polygon is defined
        ///
        /// @code
        ///                     
        /// @endcode
        ///
        /// @return             True if polygon is defined

        virtual bool            isDefined                                   ( ) const override ;

        /// @brief              Translate polygon
        ///
        /// @param              [in] aTranslation A translation vector

        virtual void            translate                                   (   const   Vector3d&                   aTranslation                                ) override ;

        /// @brief              Rotate polygon
        ///
        /// @param              [in] aRotation A rotation quaternion
        
        virtual void            rotate                                      (   const   Quaternion&                 aRotation                                   ) override ;

        /// @brief              Constructs an undefined polygon
        ///
        /// @code
        ///                     Polygon polygon = Polygon::Undefined() ; // Undefined
        /// @endcode
        ///
        /// @return             Undefined polygon

        static Polygon          Undefined                                   ( ) ;

    private:

        Polygon2d               polygon_ ;
        // Transformation          transformation_ ;

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