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
        ///                     Polygon2d polygon2d = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;
        ///                     Point origin = { 1.0, 2.0, 3.0 } ;
        ///                     Vector3d xAxis = { 1.0, 0.0, 0.0 } ;
        ///                     Vector3d yAxis = { 0.0, 1.0, 0.0 } ;
        ///                     Polygon polygon = { polygon2d, origin, xAxis, yAxis } ;
        /// @endcode
        ///
        /// @param              [in] aPolygon A 2D polygon
        /// @param              [in] anOrigin An origin
        /// @param              [in] aXAxis A X axis
        /// @param              [in] aYAxis A Y axis

                                Polygon                                     (   const   Polygon2d&                  aPolygon,
                                                                                const   Point&                      anOrigin,
                                                                                const   Vector3d&                   aXAxis,
                                                                                const   Vector3d&                   aYAxis                                      ) ;

        /// @brief              Clone polygon
        ///
        /// @return             Pointer to cloned polygon

        virtual Polygon*        clone                                       ( ) const override ;

        /// @brief              Equal to operator
        ///
        /// @param              [in] aPolygon A polygon
        /// @return             True if polygons are equal

        bool                    operator ==                                 (   const   Polygon&                    aPolygon                                    ) const ;

        /// @brief              Not equal to operator
        ///
        /// @param              [in] aPolygon A polygon
        /// @return             True if polygons not are equal

        bool                    operator !=                                 (   const   Polygon&                    aPolygon                                    ) const ;

        /// @brief              Check if polygon is defined
        ///
        /// @return             True if polygon is defined

        virtual bool            isDefined                                   ( ) const override ;

        /// @brief              Get polygon 2D polygon
        ///
        /// @return             Polygon 2D polygon

        Polygon2d               getPolygon2d                                ( ) const ;

        /// @brief              Get polygon origin
        ///
        /// @return             Polygon origin

        Point                   getOrigin                                   ( ) const ;

        /// @brief              Get polygon X axis
        ///
        /// @return             Polygon X axis

        Vector3d                getXAxis                                    ( ) const ;

        /// @brief              Get polygon Y axis
        ///
        /// @return             Polygon Y axis

        Vector3d                getYAxis                                    ( ) const ;

        /// @brief              Get polygon normal vector
        ///
        /// @return             Polygon normal vector

        Vector3d                getNormalVector                             ( ) const ;

        /// @brief              Print polygon
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] (optional) displayDecorators If true, display decorators

        virtual void            print                                       (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           =   true ) const override ;

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
        /// @return             Undefined polygon

        static Polygon          Undefined                                   ( ) ;

    private:

        Polygon2d               polygon_ ;

        Point                   origin_ ;

        Vector3d                xAxis_ ;
        Vector3d                yAxis_ ;

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