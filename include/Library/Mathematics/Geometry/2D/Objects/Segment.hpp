////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/2D/Objects/Segment.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Mathematics_Geometry_2D_Objects_Segment__
#define __Library_Mathematics_Geometry_2D_Objects_Segment__

#include <Library/Mathematics/Geometry/2D/Objects/Point.hpp>
#include <Library/Mathematics/Geometry/2D/Object.hpp>

#include <Library/Core/Types/Real.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
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

using library::core::types::Real ;

using library::math::geom::d2::Object ;
using library::math::geom::d2::objects::Point ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PointSet ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Segment
///
///                             A segment is a part of a line that is bounded by two distinct end points,
///                             and contains every point on the line between its endpoints.
///
/// @ref                        https://en.wikipedia.org/wiki/Line_segment

class Segment : public Object
{

    public:

        /// @brief              Constructor
        ///
        /// @code
        ///                     Segment segment({ 0.0, 0.0 }, { 0.0, 1.0 }) ;
        /// @endcode
        ///
        /// @param              [in] aFirstPoint A first point
        /// @param              [in] aSecondPoint A second point

                                Segment                                     (   const   Point&                      aFirstPoint,
                                                                                const   Point&                      aSecondPoint                                ) ;

        /// @brief              Clone segment
        ///
        /// @return             Pointer to cloned segment

        virtual Segment*        clone                                       ( ) const override ;

        /// @brief              Equal to operator
        ///
        /// @code
        ///                     Segment({ 0.0, 0.0 }, { 0.0, 1.0 }) == Segment({ 0.0, 0.0 }, { 0.0, 1.0 }) ; // True
        /// @endcode
        ///
        /// @param              [in] aSegment A segment
        /// @return             True if segments are equal

        bool                    operator ==                                 (   const   Segment&                    aSegment                                    ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     Segment({ 0.0, 0.0 }, { 0.0, 1.0 }) != Segment({ 0.0, 0.0 }, { 0.0, 2.0 }) ; // True
        /// @endcode
        ///
        /// @param              [in] aSegment A segment
        /// @return             True if segments not are equal

        bool                    operator !=                                 (   const   Segment&                    aSegment                                    ) const ;

        /// @brief              Check if segment is defined
        ///
        /// @code
        ///                     Segment({ 0.0, 0.0 }, { 0.0, 1.0 }).isDefined() ; // True
        /// @endcode
        ///
        /// @return             True if segment is defined

        virtual bool            isDefined                                   ( ) const override ;

        /// @brief              Check if segment is degenerate, i.e. its length is zero
        ///
        /// @code
        ///                     Segment({ 0.0, 0.0 }, { 0.0, 0.0 }).isDegenerate() ; // True
        /// @endcode
        ///
        /// @return             True if segment is degenerate

        bool                    isDegenerate                                ( ) const ;

        /// @brief              Check if segment contains point
        ///
        /// @code
        ///                     Segment segment = ... ;
        ///                     Point point = ... ;
        ///                     segment.contains(point) ;
        /// @endcode
        ///
        /// @param              [in] aPoint A point
        /// @return             True if segment contains point

        bool                    contains                                    (   const   Point&                      aPoint                                      ) const ;

        /// @brief              Check if segment contains point set
        ///
        /// @code
        ///                     Segment segment = ... ;
        ///                     PointSet pointSet = ... ;
        ///                     segment.contains(pointSet) ;
        /// @endcode
        ///
        /// @param              [in] aPointSet A point set
        /// @return             True if segment contains point set

        bool                    contains                                    (   const   PointSet&                   aPointSet                                   ) const ;

        /// @brief              Get segment first point
        ///
        /// @code
        ///                     Segment({ 0.0, 0.0 }, { 0.0, 1.0 }).getFirstPoint() ; // [0.0, 0.0]
        /// @endcode
        ///
        /// @return             Segment first point

        Point                   getFirstPoint                               ( ) const ;

        /// @brief              Get segment second point
        ///
        /// @code
        ///                     Segment({ 0.0, 0.0 }, { 0.0, 1.0 }).getSecondPoint() ; // [0.0, 1.0]
        /// @endcode
        ///
        /// @return             Segment second point
        
        Point                   getSecondPoint                              ( ) const ;

        /// @brief              Get segment center
        ///
        /// @code
        ///                     Segment({ 0.0, 0.0 }, { 0.0, 2.0 }).getCenter() ; // [0.0, 1.0]
        /// @endcode
        ///
        /// @return             Segment center

        Point                   getCenter                                   ( ) const ;

        /// @brief              Get segment direction
        ///
        /// @code
        ///                     Segment({ 0.0, 0.0 }, { 0.0, 2.0 }).getDirection() ; // [0.0, 1.0]
        /// @endcode
        ///
        /// @return             Segment direction

        Vector2d                getDirection                                ( ) const ;

        /// @brief              Get segment length
        ///
        /// @code
        ///                     Segment({ 0.0, 0.0 }, { 0.0, 2.0 }).getLength() ; // 2.0
        /// @endcode
        ///
        /// @return             Segment length

        Real                    getLength                                   ( ) const ;

        /// @brief              Get string representation
        ///
        /// @param              [in] aFormat A format
        /// @return             String representation

        virtual String          toString                                    (   const   Object::Format&             aFormat                                     =   Object::Format::Standard,
                                                                                const   Integer&                    aPrecision                                  =   Integer::Undefined() ) const override ;

        /// @brief              Print segment
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] (optional) displayDecorators If true, display decorators

        virtual void            print                                       (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           =   true ) const override ;

        /// @brief              Apply transformation to segment
        ///
        /// @param              [in] aTransformation A transformation

        virtual void            applyTransformation                         (   const   Transformation&             aTransformation                             ) override ;

        /// @brief              Constructs an undefined segment
        ///
        /// @code
        ///                     Segment segment = Segment::Undefined() ; // Undefined
        /// @endcode
        ///
        /// @return             Undefined segment

        static Segment          Undefined                                   ( ) ;

    private:

        Point                   firstPoint_ ;
        Point                   secondPoint_ ;

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