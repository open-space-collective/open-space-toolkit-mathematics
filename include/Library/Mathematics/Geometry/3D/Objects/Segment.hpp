////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Segment.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Mathematics_Geometry_3D_Objects_Segment__
#define __Library_Mathematics_Geometry_3D_Objects_Segment__

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

using library::math::geom::d3::Object ;
using library::math::geom::d3::objects::Point ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Ellipsoid ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Segment
///
/// @ref                        

class Segment : public Object
{

    public:

        /// @brief              Constructor
        ///
        /// @code
        ///                     Segment segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) ;
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
        ///                     Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) ; // True
        /// @endcode
        ///
        /// @param              [in] aSegment A segment
        /// @return             True if segments are equal

        bool                    operator ==                                 (   const   Segment&                    aSegment                                    ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0 }) ; // True
        /// @endcode
        ///
        /// @param              [in] aSegment A segment
        /// @return             True if segments not are equal

        bool                    operator !=                                 (   const   Segment&                    aSegment                                    ) const ;

        /// @brief              Output stream operator
        ///
        /// @code
        ///                     std::cout << Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) ;
        /// @endcode
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] aSegment A segment
        /// @return             A reference to output stream

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Segment&                    aSegment                                    ) ;

        /// @brief              Check if segment is defined
        ///
        /// @code
        ///                     Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).isDefined() ; // True
        /// @endcode
        ///
        /// @return             True if segment is defined

        virtual bool            isDefined                                   ( ) const override ;

        /// @brief              Check if segment is degenerate, i.e. its length is zero
        ///
        /// @code
        ///                     Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }).isDegenerate() ; // True
        /// @endcode
        ///
        /// @return             True if segment is degenerate

        bool                    isDegenerate                                ( ) const ;

        /// @brief              Check if segment intersects ellipsoid
        ///
        /// @code
        ///                     Segment segment = ... ;
        ///                     Ellipsoid ellipsoid = ... ;
        ///                     segment.intersects(ellipsoid) ;
        /// @endcode
        ///
        /// @param              [in] anEllipsoid An ellipsoid
        /// @return             True if segment intersects ellipsoid
        
        bool                    intersects                                  (   const   Ellipsoid&                  anEllipsoid                                 ) const ;

        /// @brief              Check if segment contains point
        ///
        /// @code
        ///                     Segment segment = ... ;
        ///                     Ellipsoid ellipsoid = ... ;
        ///                     segment.contains(ellipsoid) ;
        /// @endcode
        ///
        /// @param              [in] anEllipsoid An ellipsoid
        /// @return             True if segment contains point

        bool                    contains                                    (   const   Point&                      aPoint                                      ) const ;

        /// @brief              Get segment first point
        ///
        /// @code
        ///                     Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).getFirstPoint() ; // [0.0, 0.0, 0.0]
        /// @endcode
        ///
        /// @return             Segment first point

        Point                   getFirstPoint                               ( ) const ;

        /// @brief              Get segment second point
        ///
        /// @code
        ///                     Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).getSecondPoint() ; // [0.0, 0.0, 1.0]
        /// @endcode
        ///
        /// @return             Segment second point
        
        Point                   getSecondPoint                              ( ) const ;

        /// @brief              Get segment center
        ///
        /// @code
        ///                     Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0 }).getCenter() ; // [0.0, 0.0, 1.0]
        /// @endcode
        ///
        /// @return             Segment center

        Point                   getCenter                                   ( ) const ;

        /// @brief              Get segment direction
        ///
        /// @code
        ///                     Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0 }).getDirection() ; // [0.0, 0.0, 1.0]
        /// @endcode
        ///
        /// @return             Segment direction

        Vector3d                getDirection                                ( ) const ;

        /// @brief              Get segment length
        ///
        /// @code
        ///                     Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0 }).getLength() ; // 2.0
        /// @endcode
        ///
        /// @return             Segment length

        Real                    getLength                                   ( ) const ;

        /// @brief              Translate segment
        ///
        /// @param              [in] aTranslation A translation vector

        virtual void            translate                                   (   const   Vector3d&                   aTranslation                                ) override ;

        /// @brief              Rotate segment
        ///
        /// @param              [in] aRotation A rotation quaternion
        
        virtual void            rotate                                      (   const   Quaternion&                 aRotation                                   ) override ;

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