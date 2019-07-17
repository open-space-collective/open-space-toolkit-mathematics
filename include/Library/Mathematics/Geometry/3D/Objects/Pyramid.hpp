////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Pyramid.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Mathematics_Geometry_3D_Objects_Pyramid__
#define __Library_Mathematics_Geometry_3D_Objects_Pyramid__

#include <Library/Mathematics/Geometry/3D/Objects/Polygon.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ray.hpp>
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

using library::core::ctnr::Index ;
using library::core::ctnr::Size ;
using library::core::ctnr::Array ;

using library::math::geom::d3::Object ;
using library::math::geom::d3::objects::Point ;
using library::math::geom::d3::objects::Ray ;
using library::math::geom::d3::objects::Polygon ;
using library::math::geom::d3::Intersection ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Line ;
class Ray ;
class Segment ;
class Plane ;
class Polygon ;
class Sphere ;
class Ellipsoid ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Pyramid
///
///                             A pyramid is a polyhedron formed by connecting a polygonal base and a point, called the apex.
///                             Each base edge and apex form a triangle, called a lateral face.
///
/// @ref                        https://en.wikipedia.org/wiki/Pyramid_(geometry)

class Pyramid : public Object
{

    public:

        /// @brief              Constructor
        ///
        /// @code
        ///                     Polygon base = ... ;
        ///                     Point apex = { 0.0, 0.0, 1.0 } ;
        ///                     Pyramid pyramid = { base, apex } ;
        /// @endcode
        ///
        /// @param              [in] aBase A pyramid base
        /// @param              [in] anApex A pyramid apex

                                Pyramid                                     (   const   Polygon&                    aBase,
                                                                                const   Point&                      anApex                                      ) ;

        /// @brief              Clone pyramid
        ///
        /// @return             Pointer to cloned pyramid

        virtual Pyramid*        clone                                       ( ) const override ;

        /// @brief              Equal to operator
        ///
        /// @param              [in] aPyramid A pyramid
        /// @return             True if pyramids are equal

        bool                    operator ==                                 (   const   Pyramid&                    aPyramid                                    ) const ;

        /// @brief              Not equal to operator
        ///
        /// @param              [in] aPyramid A pyramid
        /// @return             True if pyramids are not equal

        bool                    operator !=                                 (   const   Pyramid&                    aPyramid                                    ) const ;

        /// @brief              Check if pyramid is defined
        ///
        /// @return             True if pyramid is defined

        virtual bool            isDefined                                   ( ) const override ;

        /// @brief              Check if pyramid intersects sphere
        ///
        /// @code
        ///                     Pyramid pyramid = ... ;
        ///                     Sphere sphere = ... ;
        ///                     pyramid.intersects(sphere) ;
        /// @endcode
        ///
        /// @param              [in] aSphere A sphere
        /// @param              [in] aDiscretizationLevel (optional) The polygonal discretization level
        /// @return             True if pyramid intersects sphere
        
        bool                    intersects                                  (   const   Sphere&                     aSphere,
                                                                                const   Size                        aDiscretizationLevel                        =   40 ) const ;

        /// @brief              Check if pyramid intersects ellipsoid
        ///
        /// @code
        ///                     Pyramid pyramid = ... ;
        ///                     Ellipsoid ellipsoid = ... ;
        ///                     pyramid.intersects(ellipsoid) ;
        /// @endcode
        ///
        /// @param              [in] anEllipsoid An ellipsoid
        /// @param              [in] aDiscretizationLevel (optional) The polygonal discretization level
        /// @return             True if pyramid intersects ellipsoid
        
        bool                    intersects                                  (   const   Ellipsoid&                  anEllipsoid,
                                                                                const   Size                        aDiscretizationLevel                        =   40 ) const ;

        /// @brief              Check if pyramid contains point
        ///
        /// @code
        ///                     Pyramid pyramid = ... ;
        ///                     Point point = ... ;
        ///                     pyramid.contains(point) ;
        /// @endcode
        ///
        /// @param              [in] aPoint A point
        /// @return             True if pyramid contains point

        bool                    contains                                    (   const   Point&                      aPoint                                      ) const ;

        /// @brief              Check if pyramid contains ellipsoid
        ///
        /// @code
        ///                     Pyramid pyramid = ... ;
        ///                     Ellipsoid ellipsoid = ... ;
        ///                     pyramid.contains(ellipsoid) ;
        /// @endcode
        ///
        /// @param              [in] anEllipsoid An ellipsoid
        /// @return             True if pyramid contains ellipsoid

        bool                    contains                                    (   const   Ellipsoid&                  anEllipsoid                                 ) const ;

        /// @brief              Get pyramid base
        ///
        /// @return             Pyramid base

        Polygon                 getBase                                     ( ) const ;

        /// @brief              Get pyramid apex
        ///
        /// @return             Pyramid apex

        Point                   getApex                                     ( ) const ;

        /// @brief              Get number of lateral faces
        ///
        /// @return             Number of lateral faces

        Size                    getLateralFaceCount                         ( ) const ;

        /// @brief              Get lateral face at index
        ///
        /// @param              [in] aLateralFaceIndex A lateral face index
        /// @return             Lateral face

        Polygon                 getLateralFaceAt                            (   const   Index                       aLateralFaceIndex                           ) const ;

        /// @brief              Get rays of lateral face at index
        ///
        /// @param              [in] aLateralFaceIndex A lateral face index
        /// @param              [in] aRayCount A number of rays (at least 2)
        /// @return             Array of rays

        Array<Ray>              getRaysOfLateralFaceAt                      (   const   Index                       aLateralFaceIndex,
                                                                                const   Size                        aRayCount                                   =   2 ) const ;

        /// @brief              Get rays of lateral faces
        ///
        /// @param              [in] aRayCount A number of rays (at least face count)
        /// @return             Array of rays

        Array<Ray>              getRaysOfLateralFaces                       (   const   Size                        aRayCount                                   =   0 ) const ;

        /// @brief              Compute intersection of pyramid with sphere
        ///
        /// @param              [in] aSphere A sphere
        /// @param              [in] onlyInSight (optional) If true, only return intersection points that are in sight
        /// @param              [in] aDiscretizationLevel (optional) The polygonal discretization level
        /// @return             Intersection of pyramid with sphere

        Intersection            intersectionWith                            (   const   Sphere&                     aSphere,
                                                                                const   bool                        onlyInSight                                 =   false,
                                                                                const   Size                        aDiscretizationLevel                        =   40 ) const ;

        /// @brief              Compute intersection of pyramid with ellipsoid
        ///
        /// @param              [in] anEllipsoid An ellipsoid
        /// @param              [in] onlyInSight (optional) If true, only return intersection points that are in sight
        /// @param              [in] aDiscretizationLevel (optional) The polygonal discretization level
        /// @return             Intersection of pyramid with ellipsoid

        Intersection            intersectionWith                            (   const   Ellipsoid&                  anEllipsoid,
                                                                                const   bool                        onlyInSight                                 =   false,
                                                                                const   Size                        aDiscretizationLevel                        =   40 ) const ;

        /// @brief              Print pyramid
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] (optional) displayDecorators If true, display decorators

        virtual void            print                                       (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           =   true ) const override ;

        /// @brief              Apply transformation to pyramid
        ///
        /// @param              [in] aTransformation A transformation

        virtual void            applyTransformation                         (   const   Transformation&             aTransformation                             ) override ;

        /// @brief              Constructs an undefined pyramid
        ///
        /// @return             Undefined pyramid

        static Pyramid          Undefined                                   ( ) ;

    private:

        Polygon                 base_ ;
        Point                   apex_ ;

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