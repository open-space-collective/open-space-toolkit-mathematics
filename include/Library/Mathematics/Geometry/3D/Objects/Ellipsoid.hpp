////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Ellipsoid__
#define __OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Ellipsoid__

#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Point.hpp>
#include <Library/Mathematics/Geometry/3D/Object.hpp>

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

using library::math::obj::Matrix3d ;
using library::math::geom::d3::Object ;
using library::math::geom::d3::objects::Point ;
using library::math::geom::d3::Intersection ;
using library::math::geom::d3::trf::rot::Quaternion ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PointSet ;
class Line ;
class Ray ;
class Segment ;
class Plane ;
class Polygon ;
class Sphere ;
class Pyramid ;
class Cone ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Ellipsoid
///
/// @ref                        https://en.wikipedia.org/wiki/Ellipsoid

class Ellipsoid : public Object
{

    public:

        /// @brief              Constructor
        ///
        /// @code
        ///                     Ellipsoid ellipsoid({ 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0) ;
        /// @endcode
        ///
        /// @param              [in] aCenter An ellipsoid center
        /// @param              [in] aFirstPrincipalSemiAxis An ellipsoid first principal semi-axis
        /// @param              [in] aSecondPrincipalSemiAxis An ellipsoid second principal semi-axis
        /// @param              [in] aThirdPrincipalSemiAxis An ellipsoid third principal semi-axis
        /// @param              [in] (optional) anOrientation An ellipsoid orientation

                                Ellipsoid                                   (   const   Point&                      aCenter,
                                                                                const   Real&                       aFirstPrincipalSemiAxis,
                                                                                const   Real&                       aSecondPrincipalSemiAxis,
                                                                                const   Real&                       aThirdPrincipalSemiAxis,
                                                                                const   Quaternion&                 anOrientation                               =   Quaternion::Unit() ) ;

        /// @brief              Clone ellipsoid
        ///
        /// @return             Pointer to cloned ellipsoid

        virtual Ellipsoid*      clone                                       ( ) const override ;

        /// @brief              Equal to operator
        ///
        /// @code
        ///                     Ellipsoid(Point::Origin(), 1.0, 2.0, 3.0) == Ellipsoid(Point::Origin(), 1.0, 2.0, 3.0) ; // True
        /// @endcode
        ///
        /// @param              [in] anEllipsoid An ellipsoid
        /// @return             True if ellipsoids are equal

        bool                    operator ==                                 (   const   Ellipsoid&                  anEllipsoid                                 ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     Ellipsoid(Point::Origin(), 1.0, 2.0, 3.0) != Ellipsoid(2.0, 1.0, 3.0) ; // True
        /// @endcode
        ///
        /// @param              [in] anEllipsoid An ellipsoid
        /// @return             True if ellipsoids are not equal

        bool                    operator !=                                 (   const   Ellipsoid&                  anEllipsoid                                 ) const ;

        /// @brief              Check if ellipsoid is defined
        ///
        /// @code
        ///                     Ellipsoid(Point::Origin(), 1.0, 2.0, 3.0).isDefined() ; // True
        /// @endcode
        ///
        /// @return             True if ellipsoid is defined

        virtual bool            isDefined                                   ( ) const override ;

        /// @brief              Check if ellipsoid intersects point
        ///
        /// @code
        ///                     Ellipsoid ellipsoid = ... ;
        ///                     Point point = ... ;
        ///                     ellipsoid.intersects(point) ;
        /// @endcode
        ///
        /// @param              [in] aPoint A point
        /// @return             True if ellipsoid intersects point

        bool                    intersects                                  (   const   Point&                      aPoint                                      ) const ;

        /// @brief              Check if ellipsoid intersects point set
        ///
        /// @code
        ///                     Ellipsoid ellipsoid = ... ;
        ///                     PointSet pointSet = ... ;
        ///                     ellipsoid.intersects(pointSet) ;
        /// @endcode
        ///
        /// @param              [in] aPointSet A point set
        /// @return             True if ellipsoid intersects point set

        bool                    intersects                                  (   const   PointSet&                   aPointSet                                   ) const ;

        /// @brief              Check if ellipsoid intersects line
        ///
        /// @code
        ///                     Ellipsoid ellipsoid = ... ;
        ///                     Line line = ... ;
        ///                     ellipsoid.intersects(line) ;
        /// @endcode
        ///
        /// @param              [in] aLine A line
        /// @return             True if ellipsoid intersects line

        bool                    intersects                                  (   const   Line&                       aLine                                       ) const ;

        /// @brief              Check if ellipsoid intersects ray
        ///
        /// @code
        ///                     Ellipsoid ellipsoid = ... ;
        ///                     Ray ray = ... ;
        ///                     ellipsoid.intersects(ray) ;
        /// @endcode
        ///
        /// @param              [in] aRay A ray
        /// @return             True if ellipsoid intersects ray

        bool                    intersects                                  (   const   Ray&                        aRay                                        ) const ;

        /// @brief              Check if ellipsoid intersects segment
        ///
        /// @code
        ///                     Ellipsoid ellipsoid = ... ;
        ///                     Segment segment = ... ;
        ///                     ellipsoid.intersects(segment) ;
        /// @endcode
        ///
        /// @param              [in] aSegment A segment
        /// @return             True if ellipsoid intersects segment

        bool                    intersects                                  (   const   Segment&                    aSegment                                    ) const ;

        /// @brief              Check if ellipsoid intersects plane
        ///
        /// @code
        ///                     Ellipsoid ellipsoid = ... ;
        ///                     Plane plane = ... ;
        ///                     ellipsoid.intersects(plane) ;
        /// @endcode
        ///
        /// @param              [in] aPlane A plane
        /// @return             True if ellipsoid intersects plane

        bool                    intersects                                  (   const   Plane&                      aPlane                                      ) const ;

        /// @brief              Check if ellipsoid intersects sphere
        ///
        /// @code
        ///                     Ellipsoid ellipsoid = ... ;
        ///                     Sphere sphere = ... ;
        ///                     ellipsoid.intersects(sphere) ;
        /// @endcode
        ///
        /// @param              [in] aSphere A sphere
        /// @return             True if ellipsoid intersects sphere

        bool                    intersects                                  (   const   Sphere&                     aSphere                                     ) const ;

        /// @brief              Check if ellipsoid intersects ellipsoid
        ///
        /// @code
        ///                     Ellipsoid ellipsoid = ... ;
        ///                     Ellipsoid anotherEllipsoid = ... ;
        ///                     ellipsoid.intersects(anotherEllipsoid) ;
        /// @endcode
        ///
        /// @param              [in] anEllipsoid An ellipsoid
        /// @return             True if ellipsoid intersects ellipsoid

        bool                    intersects                                  (   const   Ellipsoid&                  anEllipsoid                                 ) const ;

        /// @brief              Check if ellipsoid intersects pyramid
        ///
        /// @code
        ///                     Ellipsoid ellipsoid = ... ;
        ///                     Pyramid pyramid = ... ;
        ///                     ellipsoid.intersects(pyramid) ;
        /// @endcode
        ///
        /// @param              [in] aPyramid A pyramid
        /// @return             True if ellipsoid intersects pyramid

        bool                    intersects                                  (   const   Pyramid&                    aPyramid                                    ) const ;

        /// @brief              Check if ellipsoid intersects cone
        ///
        /// @code
        ///                     Ellipsoid ellipsoid = ... ;
        ///                     Cone cone = ... ;
        ///                     ellipsoid.intersects(cone) ;
        /// @endcode
        ///
        /// @param              [in] aCone A cone
        /// @return             True if ellipsoid intersects cone

        bool                    intersects                                  (   const   Cone&                       aCone                                       ) const ;

        /// @brief              Check if ellipsoid contains point
        ///
        /// @code
        ///                     Ellipsoid ellipsoid = ... ;
        ///                     Point point = ... ;
        ///                     ellipsoid.contains(point) ;
        /// @endcode
        ///
        /// @param              [in] aPoint A point
        /// @return             True if ellipsoid contains point

        bool                    contains                                    (   const   Point&                      aPoint                                      ) const ;

        /// @brief              Check if ellipsoid contains point set
        ///
        /// @code
        ///                     Ellipsoid ellipsoid = ... ;
        ///                     PointSet pointSet = ... ;
        ///                     ellipsoid.contains(pointSet) ;
        /// @endcode
        ///
        /// @param              [in] aPointSet A point set
        /// @return             True if ellipsoid contains point set

        bool                    contains                                    (   const   PointSet&                   aPointSet                                   ) const ;

        /// @brief              Check if ellipsoid contains segment
        ///
        /// @code
        ///                     Ellipsoid ellipsoid = ... ;
        ///                     Segment segment = ... ;
        ///                     ellipsoid.contains(segment) ;
        /// @endcode
        ///
        /// @param              [in] aSegment A segment
        /// @return             True if ellipsoid contains segment

        bool                    contains                                    (   const   Segment&                    aSegment                                    ) const ;

        /// @brief              Get ellipsoid center
        ///
        /// @code
        ///                     Ellipsoid(Point::Origin(), 1.0, 2.0, 3.0).getCenter() ; // [0.0, 0.0, 0.0]
        /// @endcode
        ///
        /// @return             Ellipsoid center

        Point                   getCenter                                   ( ) const ;

        /// @brief              Get ellipsoid first principal semi-axis
        ///
        /// @code
        ///                     Ellipsoid(Point::Origin(), 1.0, 2.0, 3.0).getFirstPrincipalSemiAxis() ; // 1.0
        /// @endcode
        ///
        /// @return             Ellipsoid first principal semi-axis

        Real                    getFirstPrincipalSemiAxis                   ( ) const ;

        /// @brief              Get ellipsoid second principal semi-axis
        ///
        /// @code
        ///                     Ellipsoid(Point::Origin(), 1.0, 2.0, 3.0).getSecondPrincipalSemiAxis() ; // 2.0
        /// @endcode
        ///
        /// @return             Ellipsoid second principal semi-axis

        Real                    getSecondPrincipalSemiAxis                  ( ) const ;

        /// @brief              Get ellipsoid third principal semi-axis
        ///
        /// @code
        ///                     Ellipsoid(Point::Origin(), 1.0, 2.0, 3.0).getThirdPrincipalSemiAxis() ; // 3.0
        /// @endcode
        ///
        /// @return             Ellipsoid third principal semi-axis

        Real                    getThirdPrincipalSemiAxis                   ( ) const ;

        /// @brief              Get ellipsoid first axis
        ///
        /// @return             Ellipsoid first axis

        Vector3d                getFirstAxis                                ( ) const ;

        /// @brief              Get ellipsoid second axis
        ///
        /// @return             Ellipsoid second axis

        Vector3d                getSecondAxis                               ( ) const ;

        /// @brief              Get ellipsoid third axis
        ///
        /// @return             Ellipsoid third axis

        Vector3d                getThirdAxis                                ( ) const ;

        /// @brief              Get ellipsoid orientation
        ///
        /// @code
        ///                     Ellipsoid(Point::Origin(), 1.0, 2.0, 3.0, Quaternion::XYZS(0.0, 0.0, 0.0, 1.0)).getOrientation() ; // Quaternion::XYZS(0.0, 0.0, 0.0, 1.0)
        /// @endcode
        ///
        /// @return             Ellipsoid orientation

        Quaternion              getOrientation                              ( ) const ;

        /// @brief              Get ellipsoid matrix
        ///
        /// @code
        ///                     Ellipsoid(Point::Origin(), 1.0, 2.0, 3.0, Quaternion::XYZS(0.0, 0.0, 0.0, 1.0)).getMatrix() ;
        /// @endcode
        ///
        /// @return             Ellipsoid matrix

        Matrix3d                getMatrix                                   ( ) const ;

        /// @brief              Compute intersection of ellipsoid with line
        ///
        /// @param              [in] aLine A line
        /// @return             Intersection of ellipsoid with line

        Intersection            intersectionWith                            (   const   Line&                       aLine                                       ) const ;

        /// @brief              Compute intersection of ellipsoid with ray
        ///
        /// @param              [in] aRay A ray
        /// @param              [in] onlyInSight (optional) If true, only return intersection points that are in sight
        /// @return             Intersection of ellipsoid with ray

        Intersection            intersectionWith                            (   const   Ray&                        aRay,
                                                                                const   bool                        onlyInSight                                 =   false ) const ;

        /// @brief              Compute intersection of ellipsoid with segment
        ///
        /// @param              [in] aSegment A segment
        /// @return             Intersection of ellipsoid with segment

        Intersection            intersectionWith                            (   const   Segment&                    aSegment                                    ) const ;

        /// @brief              Compute intersection of ellipsoid with pyramid
        ///
        /// @param              [in] aPyramid A pyramid
        /// @param              [in] onlyInSight (optional) If true, only return intersection points that are in sight
        /// @return             Intersection of ellipsoid with pyramid

        Intersection            intersectionWith                            (   const   Pyramid&                    aPyramid,
                                                                                const   bool                        onlyInSight                                 =   false ) const ;

        /// @brief              Compute intersection of ellipsoid with cone
        ///
        /// @param              [in] aCone A cone
        /// @param              [in] onlyInSight (optional) If true, only return intersection points that are in sight
        /// @return             Intersection of ellipsoid with cone

        Intersection            intersectionWith                            (   const   Cone&                       aCone,
                                                                                const   bool                        onlyInSight                                 =   false ) const ;

        /// @brief              Print ellipsoid
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] (optional) displayDecorators If true, display decorators

        virtual void            print                                       (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           =   true ) const override ;

        /// @brief              Apply transformation to ellipsoid
        ///
        /// @param              [in] aTransformation A transformation

        virtual void            applyTransformation                         (   const   Transformation&             aTransformation                             ) override ;

        /// @brief              Constructs an undefined ellipsoid
        ///
        /// @code
        ///                     Ellipsoid ellipsoid = Ellipsoid::Undefined() ; // Undefined
        /// @endcode
        ///
        /// @return             Undefined ellipsoid

        static Ellipsoid        Undefined                                   ( ) ;

    private:

        Point                   center_ ;

        Real                    a_ ;
        Real                    b_ ;
        Real                    c_ ;

        Quaternion              q_ ;

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
