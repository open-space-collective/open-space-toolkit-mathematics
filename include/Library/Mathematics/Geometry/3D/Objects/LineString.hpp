////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/LineString.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Mathematics_Geometry_3D_Objects_LineString__
#define __Library_Mathematics_Geometry_3D_Objects_LineString__

#include <Library/Mathematics/Geometry/3D/Objects/Point.hpp>
#include <Library/Mathematics/Geometry/3D/Object.hpp>

#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Types/Size.hpp>
#include <Library/Core/Types/Index.hpp>

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

using library::core::types::Index ;
using library::core::types::Size ;
using library::core::ctnr::Array ;

using library::math::obj::Vector3d ;
using library::math::geom::d3::Object ;
using library::math::geom::d3::objects::Point ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Segment ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Line string

class LineString : public Object
{

    public:

        typedef                 Array<Point>::ConstIterator                     ConstIterator ;

        /// @brief              Constructor
        ///
        /// @code
        ///                     LineString lineString({ { 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 1.0, 0.0, 1.0 } }) ;
        /// @endcode
        ///
        /// @param              [in] aPointArray A point array

                                LineString                                  (   const   Array<Point>&               aPointArray                                 ) ;

        /// @brief              Clone line string
        ///
        /// @return             Pointer to cloned line string

        virtual LineString*     clone                                       ( ) const override ;

        /// @brief              Equal to operator
        ///
        /// @param              [in] aLineString A line string
        /// @return             True if line strings are equal

        bool                    operator ==                                 (   const   LineString&                 aLineString                                 ) const ;

        /// @brief              Not equal to operator
        ///
        /// @param              [in] aLineString A line string
        /// @return             True if line strings not are equal

        bool                    operator !=                                 (   const   LineString&                 aLineString                                 ) const ;

        /// @brief              Check if line string is defined
        ///
        /// @code
        ///                     LineString(0.0, 0.0).isDefined() ; // True
        /// @endcode
        ///
        /// @return             True if line string is defined

        virtual bool            isDefined                                   ( ) const override ;

        /// @brief              Check if line string is empty
        ///
        /// @code
        ///                     LineString::Empty().isEmpty() ; // True
        /// @endcode
        ///
        /// @return             True if line string is empty

        bool                    isEmpty                                     ( ) const ;

        /// @brief              Check if line string is near another line string
        ///
        /// @code
        ///                     LineString({ { 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 1.0, 0.0, 1.0 } }).isNear(LineString({ { 0.0, 0.0, 0.0 }, { 0.0, 1.0, 1e-15 }, { 1.0, 0.0, 1.0 } }), 1e-15) ; // True
        /// @endcode
        ///
        /// @param              [in] aLineString A line string
        /// @param              [in] aTolerance A tolerance
        /// @return             True if line string is near another line string

        bool                    isNear                                      (   const   LineString&                 aLineString,
                                                                                const   Real&                       aTolerance                                  ) const ;

        /// @brief              Get point count
        ///
        /// @return             Point count

        Size                    getPointCount                               ( ) const ;

        /// @brief              Get point closest to another point
        ///
        /// @param              [in] aPoint A point
        /// @return             Closest point

        Point                   getPointClosestTo                           (   const   Point&                      aPoint                                      ) const ;

        /// @brief              Print point
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] (optional) displayDecorators If true, display decorators

        virtual void            print                                       (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           =   true ) const override ;

        /// @brief              Get begin const iterator
        ///
        /// @return             Begin const iterator

        LineString::ConstIterator begin                                     ( ) const ;

        /// @brief              Get end const iterator
        ///
        /// @return             End const iterator

        LineString::ConstIterator end                                       ( ) const ;

        /// @brief              Apply transformation to line string
        ///
        /// @param              [in] aTransformation A transformation

        virtual void            applyTransformation                         (   const   Transformation&             aTransformation                             ) override ;

        /// @brief              Constructs an empty line string
        ///
        /// @code
        ///                     LineString lineString = LineString::Empty() ;
        /// @endcode
        ///
        /// @return             Empty line string

        static LineString       Empty                                       ( ) ;

        /// @brief              Constructs a line string from a segment
        ///
        /// @code
        ///                     Segment segment = { { 0.0, 0.0, 0.0 }, { 0.0, 1.0, 2.0 } } ;
        ///                     LineString lineString = LineString::Segment(segment) ;
        /// @endcode
        ///
        /// @return             Line string

        static LineString       Segment                                     (   const   objects::Segment&           aSegment                                    ) ;

    private:

        Array<Point>            points_ ;

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