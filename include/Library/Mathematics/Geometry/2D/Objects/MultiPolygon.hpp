////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           Library/Mathematics/Geometry/2D/Objects/MultiPolygon.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_MultiPolygon__
#define __OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_MultiPolygon__

#include <Library/Mathematics/Geometry/2D/Objects/Polygon.hpp>
#include <Library/Mathematics/Geometry/2D/Objects/LineString.hpp>
#include <Library/Mathematics/Geometry/2D/Objects/Segment.hpp>
#include <Library/Mathematics/Geometry/2D/Objects/PointSet.hpp>
#include <Library/Mathematics/Geometry/2D/Objects/Point.hpp>
#include <Library/Mathematics/Geometry/2D/Object.hpp>

#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Types/Size.hpp>
#include <Library/Core/Types/Index.hpp>
#include <Library/Core/Types/Unique.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace math
{
namespace geom
{
namespace d2
{
namespace objects
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::Unique ;
using ostk::core::ctnr::Index ;
using ostk::core::ctnr::Size ;
using ostk::core::ctnr::Array ;

using ostk::math::geom::d2::Object ;
using ostk::math::geom::d2::objects::Point ;
using ostk::math::geom::d2::objects::Segment ;
using ostk::math::geom::d2::objects::LineString ;
using ostk::math::geom::d2::objects::Polygon ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Multi-polygon

class MultiPolygon : public Object
{

    public:

        /// @brief              Constructor
        ///
        /// @param              [in] aPolygonArray An array of polygons

                                MultiPolygon                                (   const   Array<Polygon>&             aPolygonArray                               =   Array<Polygon>::Empty() ) ;

        /// @brief              Copy constructor
        ///
        /// @param              [in] aMultiPolygon A multi-polygon

                                MultiPolygon                                (   const   MultiPolygon&               aMultiPolygon                               ) ;

        /// @brief              Destructor (virtual)

        virtual                 ~MultiPolygon                               ( ) override ;

        /// @brief              Copy assignment operator
        ///
        /// @param              [in] aMultiPolygon A multi-polygon
        /// @return             Reference to multi-polygon

        MultiPolygon&           operator =                                  (   const   MultiPolygon&               aMultiPolygon                               ) ;

        /// @brief              Clone multi-polygon
        ///
        /// @return             Pointer to cloned multi-polygon

        virtual MultiPolygon*   clone                                       ( ) const override ;

        /// @brief              Equal to operator
        ///
        /// @param              [in] aMultiPolygon A multi-polygon
        /// @return             True if multi-polygons are equal

        bool                    operator ==                                 (   const   MultiPolygon&               aMultiPolygon                               ) const ;

        /// @brief              Not equal to operator
        ///
        /// @param              [in] aMultiPolygon A multi-polygon
        /// @return             True if multi-polygons are not equal

        bool                    operator !=                                 (   const   MultiPolygon&               aMultiPolygon                               ) const ;

        /// @brief              Check if multi-polygon is defined
        ///
        /// @return             True if multi-polygon is defined

        virtual bool            isDefined                                   ( ) const override ;

        /// @brief              Check if multi-polygon contains point
        ///
        /// @code
        ///                     MultiPolygon multiPolygon = ... ;
        ///                     Point point = ... ;
        ///                     multiPolygon.contains(point) ;
        /// @endcode
        ///
        /// @param              [in] aPoint A point
        /// @return             True if multi-polygon contains point

        bool                    contains                                    (   const   Point&                      aPoint                                      ) const ;

        /// @brief              Check if multi-polygon contains point set
        ///
        /// @code
        ///                     MultiPolygon multiPolygon = ... ;
        ///                     PointSet pointSet = ... ;
        ///                     multiPolygon.contains(pointSet) ;
        /// @endcode
        ///
        /// @param              [in] aPointSet A point set
        /// @return             True if multi-polygon contains point set

        bool                    contains                                    (   const   PointSet&                   aPointSet                                   ) const ;

        /// @brief              Get number of polygons
        ///
        /// @return             Number of polygons

        Size                    getPolygonCount                             ( ) const ;

        /// @brief              Compute intersection of multi-polygon with multi-polygon
        ///
        /// @param              [in] aMultiPolygon A multi-polygon
        /// @return             A multi-polygon

        MultiPolygon            unionWith                                   (   const   MultiPolygon&               aMultiPolygon                               ) const ;

        /// @brief              Get string representation
        ///
        /// @param              [in] aFormat A format
        /// @return             String representation

        virtual String          toString                                    (   const   Object::Format&             aFormat                                     =   Object::Format::Standard,
                                                                                const   Integer&                    aPrecision                                  =   Integer::Undefined() ) const override ;

        /// @brief              Print multi-polygon
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] (optional) displayDecorators If true, display decorators

        virtual void            print                                       (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           =   true ) const override ;

        /// @brief              Apply transformation to multi-polygon
        ///
        /// @param              [in] aTransformation A transformation

        virtual void            applyTransformation                         (   const   Transformation&             aTransformation                             ) override ;

        /// @brief              Constructs an undefined multi-polygon
        ///
        /// @code
        ///                     MultiPolygon multiPolygon = MultiPolygon::Undefined() ; // Undefined
        /// @endcode
        ///
        /// @return             Undefined multi-polygon

        static MultiPolygon     Undefined                                   ( ) ;

    private:

        class Impl ;

        Unique<MultiPolygon::Impl> implUPtr_ ;

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
