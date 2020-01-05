////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Plane.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Plane__
#define __OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Plane__

#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ray.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Line.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/PointSet.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Point.hpp>
#include <Library/Mathematics/Geometry/3D/Object.hpp>
#include <Library/Mathematics/Objects/Vector.hpp>

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

using ostk::math::obj::Vector3d ;
using ostk::math::geom::d3::Object ;
using ostk::math::geom::d3::objects::Point ;
using ostk::math::geom::d3::objects::PointSet ;
using ostk::math::geom::d3::objects::Line ;
using ostk::math::geom::d3::objects::Ray ;
using ostk::math::geom::d3::objects::Segment ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Plane
///
///                             A plane is a flat, two-dimensional surface that extends infinitely far.
///
/// @ref                        https://en.wikipedia.org/wiki/Plane_(geometry)

class Plane : public Object
{

    public:

        /// @brief              Constructor
        ///
        /// @code
        ///                     Plane plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) ;
        /// @endcode
        ///
        /// @param              [in] aPoint A point
        /// @param              [in] aNormalVector A normal vector

                                Plane                                       (   const   Point&                      aPoint,
                                                                                const   Vector3d&                   aNormalVector                               ) ;

        /// @brief              Clone plane
        ///
        /// @return             Pointer to cloned plane

        virtual Plane*          clone                                       ( ) const override ;

        /// @brief              Equal to operator
        ///
        /// @code
        ///                     Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) ; // True
        /// @endcode
        ///
        /// @param              [in] aPlane A plane
        /// @return             True if planes are equal

        bool                    operator ==                                 (   const   Plane&                      aPlane                                      ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Plane({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0 }) ; // True
        /// @endcode
        ///
        /// @param              [in] aPlane A plane
        /// @return             True if planes are not equal

        bool                    operator !=                                 (   const   Plane&                      aPlane                                      ) const ;

        /// @brief              Check if plane is defined
        ///
        /// @code
        ///                     Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).isDefined() ; // True
        /// @endcode
        ///
        /// @return             True if plane is defined

        virtual bool            isDefined                                   ( ) const override ;

        /// @brief              Check if plane intersects point
        ///
        /// @code
        ///                     Plane plane = ... ;
        ///                     Point point = ... ;
        ///                     plane.intersects(point) ;
        /// @endcode
        ///
        /// @param              [in] aPoint A point
        /// @return             True if plane intersects point

        bool                    intersects                                  (   const   Point&                      aPoint                                      ) const ;

        /// @brief              Check if plane intersects point set
        ///
        /// @code
        ///                     Plane plane = ... ;
        ///                     PointSet pointSet = ... ;
        ///                     plane.intersects(pointSet) ;
        /// @endcode
        ///
        /// @param              [in] aPointSet A point set
        /// @return             True if plane intersects point set

        bool                    intersects                                  (   const   PointSet&                   aPointSet                                   ) const ;

        /// @brief              Check if plane intersects line
        ///
        /// @code
        ///                     Plane plane = ... ;
        ///                     Line line = ... ;
        ///                     plane.intersects(line) ;
        /// @endcode
        ///
        /// @param              [in] aLine A line
        /// @return             True if plane intersects line

        bool                    intersects                                  (   const   Line&                       aLine                                       ) const ;

        /// @brief              Check if plane intersects ray
        ///
        /// @code
        ///                     Plane plane = ... ;
        ///                     Ray ray = ... ;
        ///                     plane.intersects(ray) ;
        /// @endcode
        ///
        /// @param              [in] aRay A ray
        /// @return             True if plane intersects ray

        bool                    intersects                                  (   const   Ray&                        aRay                                        ) const ;

        /// @brief              Check if plane intersects segment
        ///
        /// @code
        ///                     Plane plane = ... ;
        ///                     Segment segment = ... ;
        ///                     plane.intersects(segment) ;
        /// @endcode
        ///
        /// @param              [in] aSegment A segment
        /// @return             True if plane intersects segment

        bool                    intersects                                  (   const   Segment&                    aSegment                                    ) const ;

        /// @brief              Check if plane contains point
        ///
        /// @code
        ///                     Plane plane = ... ;
        ///                     Point point = ... ;
        ///                     plane.contains(point) ;
        /// @endcode
        ///
        /// @param              [in] aPoint A point
        /// @return             True if plane contains point

        bool                    contains                                    (   const   Point&                      aPoint                                      ) const ;

        /// @brief              Check if plane contains point set
        ///
        /// @code
        ///                     Point plane = ... ;
        ///                     PointSet pointSet = ... ;
        ///                     plane.contains(pointSet) ;
        /// @endcode
        ///
        /// @param              [in] aPointSet A point set
        /// @return             True if plane contains point set

        bool                    contains                                    (   const   PointSet&                   aPointSet                                   ) const ;

        /// @brief              Check if plane contains line
        ///
        /// @code
        ///                     Point plane = ... ;
        ///                     Line line = ... ;
        ///                     plane.contains(line) ;
        /// @endcode
        ///
        /// @param              [in] aLine A line
        /// @return             True if plane contains line

        bool                    contains                                    (   const   Line&                       aLine                                       ) const ;

        /// @brief              Check if plane contains ray
        ///
        /// @code
        ///                     Point plane = ... ;
        ///                     Ray ray = ... ;
        ///                     plane.contains(ray) ;
        /// @endcode
        ///
        /// @param              [in] aRay A ray
        /// @return             True if plane contains ray

        bool                    contains                                    (   const   Ray&                        aRay                                        ) const ;

        /// @brief              Check if plane contains segment
        ///
        /// @code
        ///                     Point plane = ... ;
        ///                     Segment segment = ... ;
        ///                     plane.contains(segment) ;
        /// @endcode
        ///
        /// @param              [in] aSegment A segment
        /// @return             True if plane contains segment

        bool                    contains                                    (   const   Segment&                    aSegment                                    ) const ;

        /// @brief              Get plane point
        ///
        /// @code
        ///                     Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).getPoint() ; // [0.0, 0.0, 0.0]
        /// @endcode
        ///
        /// @return             Plane point

        Point                   getPoint                                    ( ) const ;

        /// @brief              Get plane normal vector
        ///
        /// @code
        ///                     Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).getNormalVector() ; // [0.0, 0.0, 1.0]
        /// @endcode
        ///
        /// @return             Plane normal vector

        Vector3d                getNormalVector                             ( ) const ;

        /// @brief              Compute intersection of plane with point
        ///
        /// @param              [in] aPoint A point
        /// @return             Intersection of plane with point

        Intersection            intersectionWith                            (   const   Point&                      aPoint                                      ) const ;

        /// @brief              Compute intersection of plane with point set
        ///
        /// @param              [in] aPointSet A point set
        /// @return             Intersection of plane with point set

        Intersection            intersectionWith                            (   const   PointSet&                   aPointSet                                   ) const ;

        /// @brief              Compute intersection of plane with line
        ///
        /// @param              [in] aLine A line
        /// @return             Intersection of plane with line

        Intersection            intersectionWith                            (   const   Line&                       aLine                                       ) const ;

        /// @brief              Compute intersection of plane with ray
        ///
        /// @param              [in] aRay A ray
        /// @return             Intersection of plane with ray

        Intersection            intersectionWith                            (   const   Ray&                        aRay                                        ) const ;

        /// @brief              Compute intersection of plane with segment
        ///
        /// @param              [in] aSegment A segment
        /// @return             Intersection of plane with segment

        Intersection            intersectionWith                            (   const   Segment&                    aSegment                                    ) const ;

        /// @brief              Print plane
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] (optional) displayDecorators If true, display decorators

        virtual void            print                                       (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           =   true ) const override ;

        /// @brief              Apply transformation to plane
        ///
        /// @param              [in] aTransformation A transformation

        virtual void            applyTransformation                         (   const   Transformation&             aTransformation                             ) override ;

        /// @brief              Constructs an undefined plane
        ///
        /// @code
        ///                     Plane plane = Plane::Undefined() ; // Undefined
        /// @endcode
        ///
        /// @return             Undefined plane

        static Plane            Undefined                                   ( ) ;

    private:

        Point                   point_ ;
        Vector3d                normal_ ;

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
