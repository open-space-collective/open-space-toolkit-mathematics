////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Cone.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cone__
#define __OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cone__

#include <Library/Mathematics/Geometry/3D/Objects/Ray.hpp>
#include <Library/Mathematics/Geometry/3D/Object.hpp>
#include <Library/Mathematics/Geometry/Angle.hpp>

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

using library::math::obj::Vector3d ;
using library::math::geom::Angle ;
using library::math::geom::d3::Object ;
using library::math::geom::d3::objects::Point ;
using library::math::geom::d3::objects::Ray ;
using library::math::geom::d3::Intersection ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Line ;
class Segment ;
class Plane ;
class Polygon ;
class Sphere ;
class Ellipsoid ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Cone
///
///                             A cone is a three-dimensional geometric shape that tapers smoothly from a flat circular base to a point called the apex.
///
/// @ref                        https://en.wikipedia.org/wiki/Cone

class Cone : public Object
{

    public:

        /// @brief              Constructor
        ///
        /// @code
        ///                     Point apex = { 0.0, 0.0, 0.0 } ;
        ///                     Vector3d axis = { 0.0, 0.0, 1.0 } ;
        ///                     Angle angle = Angle::Degrees(15.0) ;
        ///                     Cone cone = { apex, axis, angle } ;
        /// @endcode
        ///
        /// @param              [in] anApex A cone apex
        /// @param              [in] anAxis A cone axis
        /// @param              [in] anAngle A cone angle

                                Cone                                        (   const   Point&                      anApex,
                                                                                const   Vector3d&                   anAxis,
                                                                                const   Angle&                      anAngle                                     ) ;

        /// @brief              Clone cone
        ///
        /// @return             Pointer to cloned cone

        virtual Cone*           clone                                       ( ) const override ;

        /// @brief              Equal to operator
        ///
        /// @param              [in] aCone A cone
        /// @return             True if cones are equal

        bool                    operator ==                                 (   const   Cone&                       aCone                                       ) const ;

        /// @brief              Not equal to operator
        ///
        /// @param              [in] aCone A cone
        /// @return             True if cones are not equal

        bool                    operator !=                                 (   const   Cone&                       aCone                                       ) const ;

        /// @brief              Check if cone is defined
        ///
        /// @return             True if cone is defined

        virtual bool            isDefined                                   ( ) const override ;

        /// @brief              Check if cone intersects sphere
        ///
        /// @code
        ///                     Cone cone = ... ;
        ///                     Sphere sphere = ... ;
        ///                     cone.intersects(sphere) ;
        /// @endcode
        ///
        /// @param              [in] aSphere A sphere
        /// @param              [in] aDiscretizationLevel (optional) The polygonal discretization level
        /// @return             True if cone intersects sphere

        bool                    intersects                                  (   const   Sphere&                     aSphere,
                                                                                const   Size                        aDiscretizationLevel                        =   40 ) const ;

        /// @brief              Check if cone intersects ellipsoid
        ///
        /// @code
        ///                     Cone cone = ... ;
        ///                     Ellipsoid ellipsoid = ... ;
        ///                     cone.intersects(ellipsoid) ;
        /// @endcode
        ///
        /// @param              [in] anEllipsoid An ellipsoid
        /// @param              [in] aDiscretizationLevel (optional) The polygonal discretization level
        /// @return             True if cone intersects ellipsoid

        bool                    intersects                                  (   const   Ellipsoid&                  anEllipsoid,
                                                                                const   Size                        aDiscretizationLevel                        =   40 ) const ;

        /// @brief              Get cone apex
        ///
        /// @return             Cone apex

        Point                   getApex                                     ( ) const ;

        /// @brief              Get cone axis
        ///
        /// @return             Cone axis

        Vector3d                getAxis                                     ( ) const ;

        /// @brief              Get cone angle
        ///
        /// @return             Cone angle

        Angle                   getAngle                                    ( ) const ;

        /// @brief              Get rays of lateral surface
        ///
        /// @param              [in] aRayCount A number of rays (at least face count)
        /// @return             Array of rays

        Array<Ray>              getRaysOfLateralSurface                     (   const   Size                        aRayCount                                   =   0 ) const ;

        /// @brief              Compute intersection of cone with sphere
        ///
        /// @param              [in] aSphere A sphere
        /// @param              [in] onlyInSight (optional) If true, only return intersection points that are in sight
        /// @param              [in] aDiscretizationLevel (optional) The polygonal discretization level
        /// @return             Intersection of cone with sphere

        Intersection            intersectionWith                            (   const   Sphere&                     aSphere,
                                                                                const   bool                        onlyInSight                                 =   false,
                                                                                const   Size                        aDiscretizationLevel                        =   40 ) const ;

        /// @brief              Compute intersection of cone with ellipsoid
        ///
        /// @param              [in] anEllipsoid An ellipsoid
        /// @param              [in] onlyInSight (optional) If true, only return intersection points that are in sight
        /// @param              [in] aDiscretizationLevel (optional) The polygonal discretization level
        /// @return             Intersection of cone with ellipsoid

        Intersection            intersectionWith                            (   const   Ellipsoid&                  anEllipsoid,
                                                                                const   bool                        onlyInSight                                 =   false,
                                                                                const   Size                        aDiscretizationLevel                        =   40 ) const ;

        /// @brief              Print cone
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] (optional) displayDecorators If true, display decorators

        virtual void            print                                       (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           =   true ) const override ;

        /// @brief              Apply transformation to cone
        ///
        /// @param              [in] aTransformation A transformation

        virtual void            applyTransformation                         (   const   Transformation&             aTransformation                             ) override ;

        /// @brief              Constructs an undefined cone
        ///
        /// @return             Undefined cone

        static Cone             Undefined                                   ( ) ;

    private:

        Point                   apex_ ;
        Vector3d                axis_ ;
        Angle                   angle_ ;

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
