////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Cuboid.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Mathematics_Geometry_3D_Objects_Cuboid__
#define __Library_Mathematics_Geometry_3D_Objects_Cuboid__

#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Point.hpp>
#include <Library/Mathematics/Objects/Vector.hpp>

#include <Library/Core/Containers/Array.hpp>
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
using library::core::ctnr::Array ;

using library::math::obj::Vector3d ;
using library::math::geom::d3::Object ;
using library::math::geom::d3::objects::Point ;
using library::math::geom::d3::objects::Segment ;
using library::math::geom::d3::Intersection ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PointSet ;
class Line ;
class Ray ;
class Segment ;
class Plane ;
class Polygon ;
class Sphere ;
class Pyramid ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Cuboid
///
/// @ref                        https://en.wikipedia.org/wiki/Cuboid

class Cuboid : public Object
{

    public:

        typedef                 Point                                           Vertex ;
        typedef                 Segment                                         Edge ;

        /// @brief              Constructor
        ///
        /// @code
        ///                     Cuboid cuboid = { { 0.0, 0.0, 0.0 }, { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } }, { 1.0, 2.0, 3.0 } } ;
        /// @endcode
        ///

                                Cuboid                                      (   const   Point&                      aCenter,
                                                                                const   std::array<Vector3d, 3>&    aAxisArray,
                                                                                const   std::array<Real, 3>&        anExtent                                    ) ;

        /// @brief              Clone cuboid
        ///
        /// @return             Pointer to cloned cuboid

        virtual Cuboid*         clone                                       ( ) const override ;

        /// @brief              Equal to operator
        ///
        /// @code
        ///                     Cuboid cuboid = { { 0.0, 0.0, 0.0 }, { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } }, { 1.0, 2.0, 3.0 } } ;
        ///                     cuboid == cuboid ; // True
        /// @endcode
        ///
        /// @param              [in] aCuboid An cuboid
        /// @return             True if cuboids are equal

        bool                    operator ==                                 (   const   Cuboid&                     aCuboid                                     ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     Cuboid cuboid = { { 0.0, 0.0, 0.0 }, { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } }, { 1.0, 2.0, 3.0 } } ;
        ///                     cuboid != cuboid ; // False
        /// @endcode
        ///
        /// @param              [in] aCuboid An cuboid
        /// @return             True if cuboids are not equal

        bool                    operator !=                                 (   const   Cuboid&                     aCuboid                                     ) const ;

        /// @brief              Check if cuboid is defined
        ///
        /// @code
        ///                     Cuboid cuboid = { { 0.0, 0.0, 0.0 }, { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } }, { 1.0, 2.0, 3.0 } } ;
        ///                     cuboid.isDefined() ; // True
        /// @endcode
        ///
        /// @return             True if cuboid is defined

        virtual bool            isDefined                                   ( ) const override ;

        /// @brief              Check if cuboid is near another cuboid
        ///
        /// @code
        ///                     Point(0.0, 0.0, 0.0).isNear(Point(0.0, 0.0, 0.0), 1e-15) ; // True
        /// @endcode
        ///
        /// @param              [in] aCuboid A cuboid
        /// @param              [in] aTolerance A tolerance
        /// @return             True if cuboid is near another cuboid

        bool                    isNear                                      (   const   Cuboid&                     aCuboid,
                                                                                const   Real&                       aTolerance                                  ) const ;

        /// @brief              Check if cuboid intersects point
        ///
        /// @code
        ///                     Cuboid cuboid = ... ;
        ///                     Point point = ... ;
        ///                     cuboid.intersects(point) ;
        /// @endcode
        ///
        /// @param              [in] aPoint A point
        /// @return             True if cuboid intersects point

        bool                    intersects                                  (   const   Point&                      aPoint                                      ) const ;

        /// @brief              Check if cuboid intersects point set
        ///
        /// @code
        ///                     Cuboid cuboid = ... ;
        ///                     PointSet pointSet = ... ;
        ///                     cuboid.intersects(pointSet) ;
        /// @endcode
        ///
        /// @param              [in] aPointSet A point set
        /// @return             True if cuboid intersects point set

        bool                    intersects                                  (   const   PointSet&                   aPointSet                                   ) const ;

        /// @brief              Check if cuboid intersects line
        ///
        /// @code
        ///                     Cuboid cuboid = ... ;
        ///                     Line line = ... ;
        ///                     cuboid.intersects(line) ;
        /// @endcode
        ///
        /// @param              [in] aLine A line
        /// @return             True if cuboid intersects line

        bool                    intersects                                  (   const   Line&                       aLine                                       ) const ;

        /// @brief              Check if cuboid intersects ray
        ///
        /// @code
        ///                     Cuboid cuboid = ... ;
        ///                     Ray ray = ... ;
        ///                     cuboid.intersects(ray) ;
        /// @endcode
        ///
        /// @param              [in] aRay A ray
        /// @return             True if cuboid intersects ray

        bool                    intersects                                  (   const   Ray&                        aRay                                        ) const ;

        /// @brief              Check if cuboid intersects segment
        ///
        /// @code
        ///                     Cuboid cuboid = ... ;
        ///                     Segment segment = ... ;
        ///                     cuboid.intersects(segment) ;
        /// @endcode
        ///
        /// @param              [in] aSegment A segment
        /// @return             True if cuboid intersects segment

        bool                    intersects                                  (   const   Segment&                    aSegment                                    ) const ;

        /// @brief              Check if cuboid intersects plane
        ///
        /// @code
        ///                     Cuboid cuboid = ... ;
        ///                     Plane plane = ... ;
        ///                     cuboid.intersects(plane) ;
        /// @endcode
        ///
        /// @param              [in] aPlane A plane
        /// @return             True if cuboid intersects plane

        bool                    intersects                                  (   const   Plane&                      aPlane                                      ) const ;

        /// @brief              Check if cuboid intersects sphere
        ///
        /// @code
        ///                     Cuboid cuboid = ... ;
        ///                     Sphere sphere = ... ;
        ///                     cuboid.intersects(sphere) ;
        /// @endcode
        ///
        /// @param              [in] aSphere A sphere
        /// @return             True if cuboid intersects sphere

        bool                    intersects                                  (   const   Sphere&                     aSphere                                     ) const ;

        /// @brief              Check if cuboid intersects cuboid
        ///
        /// @code
        ///                     Cuboid cuboid = ... ;
        ///                     Cuboid anotherCuboid = ... ;
        ///                     cuboid.intersects(anotherCuboid) ;
        /// @endcode
        ///
        /// @param              [in] aCuboid An cuboid
        /// @return             True if cuboid intersects cuboid

        bool                    intersects                                  (   const   Cuboid&                     aCuboid                                     ) const ;

        /// @brief              Check if cuboid intersects pyramid
        ///
        /// @code
        ///                     Cuboid cuboid = ... ;
        ///                     Pyramid pyramid = ... ;
        ///                     cuboid.intersects(pyramid) ;
        /// @endcode
        ///
        /// @param              [in] aPyramid A pyramid
        /// @return             True if cuboid intersects pyramid

        bool                    intersects                                  (   const   Pyramid&                    aPyramid                                    ) const ;

        /// @brief              Check if cuboid contains point
        ///
        /// @code
        ///                     Cuboid cuboid = ... ;
        ///                     Point point = ... ;
        ///                     cuboid.contains(point) ;
        /// @endcode
        ///
        /// @param              [in] aPoint A point
        /// @return             True if cuboid contains point

        bool                    contains                                    (   const   Point&                      aPoint                                      ) const ;

        /// @brief              Check if cuboid contains point set
        ///
        /// @code
        ///                     Cuboid cuboid = ... ;
        ///                     PointSet pointSet = ... ;
        ///                     cuboid.contains(pointSet) ;
        /// @endcode
        ///
        /// @param              [in] aPointSet A point set
        /// @return             True if cuboid contains point set

        bool                    contains                                    (   const   PointSet&                   aPointSet                                   ) const ;

        /// @brief              Check if cuboid contains segment
        ///
        /// @code
        ///                     Cuboid cuboid = ... ;
        ///                     Segment segment = ... ;
        ///                     cuboid.contains(segment) ;
        /// @endcode
        ///
        /// @param              [in] aSegment A segment
        /// @return             True if cuboid contains segment

        bool                    contains                                    (   const   Segment&                    aSegment                                    ) const ;

        /// @brief              Get cuboid center
        ///
        /// @code
        ///                     Cuboid cuboid = { { 0.0, 0.0, 0.0 }, { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } }, { 1.0, 2.0, 3.0 } } ;
        ///                     cuboid.getCenter() ; // [0.0, 0.0, 0.0]
        /// @endcode
        ///
        /// @return             Cuboid center

        Point                   getCenter                                   ( ) const ;

        /// @brief              Get cuboid first axis
        ///
        /// @return             Cuboid first axis

        Vector3d                getFirstAxis                                ( ) const ;

        /// @brief              Get cuboid second axis
        ///
        /// @return             Cuboid second axis

        Vector3d                getSecondAxis                               ( ) const ;

        /// @brief              Get cuboid third axis
        ///
        /// @return             Cuboid third axis

        Vector3d                getThirdAxis                                ( ) const ;

        /// @brief              Get cuboid first extent
        ///
        /// @return             Cuboid first extent

        Real                    getFirstExtent                              ( ) const ;

        /// @brief              Get cuboid second extent
        ///
        /// @return             Cuboid second extent

        Real                    getSecondExtent                             ( ) const ;

        /// @brief              Get cuboid third extent
        ///
        /// @return             Cuboid third extent

        Real                    getThirdExtent                              ( ) const ;

        /// @brief              Get cuboid vertices
        ///
        /// @return             Cuboid vertices

        Array<Cuboid::Vertex>   getVertices                                 ( ) const ;

        /// @brief              Compute intersection of cuboid with line
        ///
        /// @param              [in] aLine A line
        /// @return             Intersection of cuboid with line

        Intersection            intersectionWith                            (   const   Line&                       aLine                                       ) const ;

        /// @brief              Compute intersection of cuboid with ray
        ///
        /// @param              [in] aRay A ray
        /// @param              [in] onlyInSight (optional) If true, only return intersection points that are in sight
        /// @return             Intersection of cuboid with ray

        Intersection            intersectionWith                            (   const   Ray&                        aRay,
                                                                                const   bool                        onlyInSight                                 =   false ) const ;

        /// @brief              Compute intersection of cuboid with segment
        ///
        /// @param              [in] aSegment A segment
        /// @return             Intersection of cuboid with segment

        Intersection            intersectionWith                            (   const   Segment&                    aSegment                                    ) const ;

        /// @brief              Compute intersection of cuboid with cuboid
        ///
        /// @param              [in] aSegment A cuboid
        /// @return             Intersection of cuboid with cuboid

        Intersection            intersectionWith                            (   const   Cuboid&                     aCuboid                                     ) const ;

        /// @brief              Compute intersection of cuboid with pyramid
        ///
        /// @param              [in] aPyramid A pyramid
        /// @param              [in] onlyInSight (optional) If true, only return intersection points that are in sight
        /// @return             Intersection of cuboid with pyramid

        Intersection            intersectionWith                            (   const   Pyramid&                    aPyramid,
                                                                                const   bool                        onlyInSight                                 =   false ) const ;

        /// @brief              Print cuboid
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] (optional) displayDecorators If true, display decorators

        virtual void            print                                       (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           =   true ) const override ;

        /// @brief              Apply transformation to cuboid
        ///
        /// @param              [in] aTransformation A transformation

        virtual void            applyTransformation                         (   const   Transformation&             aTransformation                             ) override ;

        /// @brief              Constructs an undefined cuboid
        ///
        /// @code
        ///                     Cuboid cuboid = Cuboid::Undefined() ; // Undefined
        /// @endcode
        ///
        /// @return             Undefined cuboid

        static Cuboid           Undefined                                   ( ) ;

        /// @brief              Constructs a a cube
        ///
        /// @code
        ///                     Cuboid cube = Cuboid::Cube({ 0.0, 0.0, 0.0 }, 1.0) ;
        /// @endcode
        ///
        /// @return             Cube

        static Cuboid           Cube                                        (   const   Point&                      aCenter,
                                                                                const   Real&                       anExtent                                    ) ;

    private:

        Point                   center_ ;
        std::array<Vector3d, 3> axes_ ;
        std::array<Real, 3>     extent_ ;

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
