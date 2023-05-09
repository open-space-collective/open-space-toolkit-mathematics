// Copyright © Loft Orbital Solutions Inc.

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Line__
#define __OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Line__

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object.hpp>
#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>

#include <OpenSpaceToolkit/Core/Types/Real.hpp>


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


using ostk::core::types::Real ;

using ostk::math::obj::Vector2d ;
using ostk::math::geom::d2::Object ;
using ostk::math::geom::d2::objects::Point ;


class PointSet ;


/// @brief                      Line
///
/// @ref                        https://en.wikipedia.org/wiki/Line_(geometry)

class Line : public Object
{

    public:

        /// @brief              Constructor
        ///
        /// @code
        ///                     Line line({ 0.0, 0.0 }, { 0.0, 1.0 }) ;
        /// @endcode
        ///
        /// @param              [in] anOrigin A line origin
        /// @param              [in] aDirection A line direction

                                Line                                        (   const   Point&                      anOrigin,
                                                                                const   Vector2d&                   aDirection                                  ) ;

        /// @brief              Clone line
        ///
        /// @return             Pointer to cloned line

        virtual Line*           clone                                       ( ) const override ;

        /// @brief              Equal to operator
        ///
        /// @code
        ///                     Line({ 0.0, 0.0 }, { 0.0, 1.0 }) == Line({ 0.0, 0.0 }, { 0.0, 1.0 }) ; // True
        /// @endcode
        ///
        /// @param              [in] aLine A line
        /// @return             True if lines are equal

        bool                    operator ==                                 (   const   Line&                       aLine                                       ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     Line({ 0.0, 0.0 }, { 0.0, 1.0 }) != Line({ 0.0, 0.0 }, { 0.0, 2.0 }) ; // True
        /// @endcode
        ///
        /// @param              [in] aLine A line
        /// @return             True if lines are not equal

        bool                    operator !=                                 (   const   Line&                       aLine                                       ) const ;

        /// @brief              Check if line is defined
        ///
        /// @code
        ///                     Line({ 0.0, 0.0 }, { 0.0, 1.0 }).isDefined() ; // True
        /// @endcode
        ///
        /// @return             True if line is defined

        virtual bool            isDefined                                   ( ) const override ;

        /// @brief              Check if line intersects point
        ///
        /// @code
        ///                     Line line = ... ;
        ///                     Point point = ... ;
        ///                     line.intersects(point) ;
        /// @endcode
        ///
        /// @param              [in] anPoint A point
        /// @return             True if line intersects point

        bool                    intersects                                  (   const   Point&                      aPoint                                      ) const ;

        /// @brief              Check if line intersects line
        ///
        /// @code
        ///                     Line line = ... ;
        ///                     Line otherLine = ... ;
        ///                     line.intersects(otherLine) ;
        /// @endcode
        ///
        /// @param              [in] aLine A line
        /// @return             True if line intersects kine

        bool                    intersects                                  (   const   Line&                       aLine                                       ) const ;

        /// @brief              Check if line contains point
        ///
        /// @code
        ///                     Line line = ... ;
        ///                     Point point = ... ;
        ///                     line.contains(point) ;
        /// @endcode
        ///
        /// @param              [in] aPoint A point
        /// @return             True if line contains point

        bool                    contains                                    (   const   Point&                      aPoint                                      ) const ;

        /// @brief              Check if line contains point set
        ///
        /// @code
        ///                     Line line = ... ;
        ///                     PointSet pointSet = ... ;
        ///                     line.contains(pointSet) ;
        /// @endcode
        ///
        /// @param              [in] aPointSet A point set
        /// @return             True if line contains point set

        bool                    contains                                    (   const   PointSet&                   aPointSet                                   ) const ;

        /// @brief              Get line origin
        ///
        /// @code
        ///                     Line({ 0.0, 0.0 }, { 0.0, 1.0 }).getOrigin() ; // [0.0, 0.0]
        /// @endcode
        ///
        /// @return             Line origin

        Point                   getOrigin                                   ( ) const ;

        /// @brief              Get line direction
        ///
        /// @code
        ///                     Line({ 0.0, 0.0 }, { 0.0, 1.0 }).getDirection() ; // [0.0, 1.0]
        /// @endcode
        ///
        /// @return             Line direction

        Vector2d                getDirection                                ( ) const ;

        /// @brief              Get distance to point
        ///
        /// @param              [in] aPoint A point
        /// @return             Distance to point

        Real                    distanceTo                                  (   const   Point&                      aPoint                                      ) const ;

        /// @brief              Get string representation
        ///
        /// @param              [in] aFormat A format
        /// @return             String representation

        virtual String          toString                                    (   const   Object::Format&             aFormat                                     =   Object::Format::Standard,
                                                                                const   Integer&                    aPrecision                                  =   Integer::Undefined() ) const override ;

        /// @brief              Print line
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] (optional) displayDecorators If true, display decorators

        virtual void            print                                       (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           =   true ) const override ;



        /// @brief              Apply transformation to line
        ///
        /// @param              [in] aTransformation A transformation

        virtual void            applyTransformation                         (   const   Transformation&             aTransformation                             ) override ;

        /// @brief              Constructs an undefined line
        ///
        /// @code
        ///                     Line line = Line::Undefined() ; // Undefined
        /// @endcode
        ///
        /// @return             Undefined line

        static Line             Undefined                                   ( ) ;

        /// @brief              Constructs a line using two points
        ///
        /// @code
        ///                     Point p_1 = ...
        ///                     Point p_2 = ...
        ///                     Line line = Line::Points(p_1, p_2) ;
        /// @endcode
        ///
        /// @return             Line

        static Line             Points                                      (   const   Point&                      aFirstPoint,
                                                                                const   Point&                      aSecondPoint                                ) ;

    private:

        Point                   origin_ ;
        Vector2d                direction_ ;

} ;


}
}
}
}
}


#endif

