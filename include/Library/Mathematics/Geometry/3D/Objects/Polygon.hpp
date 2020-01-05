////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Polygon.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Polygon__
#define __OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Polygon__

#include <Library/Mathematics/Geometry/3D/Objects/Plane.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/LineString.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Point.hpp>
#include <Library/Mathematics/Geometry/3D/Object.hpp>
#include <Library/Mathematics/Geometry/2D/Objects/Polygon.hpp>

#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Types/Size.hpp>
#include <Library/Core/Types/Index.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
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

using ostk::core::ctnr::Index ;
using ostk::core::ctnr::Size ;
using ostk::core::ctnr::Array ;

using Polygon2d = ostk::math::geom::d2::objects::Polygon ;
using ostk::math::geom::d3::Object ;
using ostk::math::geom::d3::objects::Point ;
using ostk::math::geom::d3::objects::Segment ;
using ostk::math::geom::d3::objects::LineString ;
using ostk::math::geom::d3::objects::Plane ;

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

        typedef                 Point                                           Vertex ;
        typedef                 Segment                                         Edge ;
        typedef                 LineString                                      Ring ;

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
        /// @return             True if polygons are not equal

        bool                    operator !=                                 (   const   Polygon&                    aPolygon                                    ) const ;

        /// @brief              Check if polygon is defined
        ///
        /// @return             True if polygon is defined

        virtual bool            isDefined                                   ( ) const override ;

        /// @brief              Check if polygon is near another polygon
        ///
        /// @param              [in] aPolygon A polygon
        /// @param              [in] aTolerance A tolerance
        /// @return             True if polygon is near another polygon

        bool                    isNear                                      (   const   Polygon&                    aPolygon,
                                                                                const   Real&                       aTolerance                                  ) const ;

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

        /// @brief              Get edge count
        ///
        /// @return             Edge count

        Size                    getEdgeCount                                ( ) const ;

        /// @brief              Get vertex count
        ///
        /// @return             Vertex count

        Size                    getVertexCount                              ( ) const ;

        /// @brief              Get edge at index
        ///
        /// @param              [in] anEdgeIndex An edge index
        /// @return             Edge (segment)

        Polygon::Edge           getEdgeAt                                   (   const   Index                       anEdgeIndex                                 ) const ;

        /// @brief              Get vertex at index
        ///
        /// @param              [in] aVertexIndex A vertex index
        /// @return             Vertex

        Polygon::Vertex         getVertexAt                                 (   const   Index                       aVertexIndex                                ) const ;

        /// @brief              Get polygon edges
        ///
        /// @return             Polygon edges

        Array<Polygon::Edge>    getEdges                                    ( ) const ;

        /// @brief              Get polygon vertices
        ///
        /// @return             Polygon vertices

        Array<Polygon::Vertex>  getVertices                                 ( ) const ;

        /// @brief              Print polygon
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] (optional) displayDecorators If true, display decorators

        virtual void            print                                       (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           =   true ) const override ;

        /// @brief              Apply transformation to polygon
        ///
        /// @param              [in] aTransformation A transformation

        virtual void            applyTransformation                         (   const   Transformation&             aTransformation                             ) override ;

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
