////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Line.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Mathematics_Geometry_3D_Objects_Line__
#define __Library_Mathematics_Geometry_3D_Objects_Line__

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

using library::math::obj::Vector3d ;
using library::math::geom::d3::Object ;
using library::math::geom::d3::objects::Point ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Ellipsoid ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Line
///
/// @ref                        https://en.wikipedia.org/wiki/Line_(geometry)

class Line : public Object
{

    public:

        /// @brief              Constructor
        ///
        /// @code
        ///                     Line line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) ;
        /// @endcode
        ///
        /// @param              [in] anOrigin A line origin
        /// @param              [in] aDirection A line direction

                                Line                                        (   const   Point&                      anOrigin,
                                                                                const   Vector3d&                   aDirection                                  ) ;

        /// @brief              Clone line
        ///
        /// @return             Pointer to cloned line

        virtual Line*           clone                                       ( ) const override ;

        /// @brief              Equal to operator
        ///
        /// @code
        ///                     Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) ; // True
        /// @endcode
        ///
        /// @param              [in] aLine A line
        /// @return             True if lines are equal

        bool                    operator ==                                 (   const   Line&                       aLine                                       ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0 }) ; // True
        /// @endcode
        ///
        /// @param              [in] aLine A line
        /// @return             True if lines not are equal

        bool                    operator !=                                 (   const   Line&                       aLine                                       ) const ;

        /// @brief              Output stream operator
        ///
        /// @code
        ///                     std::cout << Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) ;
        /// @endcode
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] aLine A line
        /// @return             A reference to output stream

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Line&                       aLine                                       ) ;

        /// @brief              Check if line is defined
        ///
        /// @code
        ///                     Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).isDefined() ; // True
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
        /// @param              [in] anPoint An point
        /// @return             True if line intersects point
        
        bool                    intersects                                  (   const   Point&                      aPoint                                      ) const ;

        /// @brief              Check if line intersects ellipsoid
        ///
        /// @code
        ///                     Line line = ... ;
        ///                     Ellipsoid ellipsoid = ... ;
        ///                     line.intersects(ellipsoid) ;
        /// @endcode
        ///
        /// @param              [in] anEllipsoid An ellipsoid
        /// @return             True if line intersects ellipsoid
        
        bool                    intersects                                  (   const   Ellipsoid&                  anEllipsoid                                 ) const ;

        /// @brief              Check if line contains point
        ///
        /// @code
        ///                     Line line = ... ;
        ///                     Ellipsoid ellipsoid = ... ;
        ///                     line.contains(ellipsoid) ;
        /// @endcode
        ///
        /// @param              [in] anEllipsoid An ellipsoid
        /// @return             True if line contains point

        bool                    contains                                    (   const   Point&                      aPoint                                      ) const ;

        /// @brief              Get line origin
        ///
        /// @code
        ///                     Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).getOrigin() ; // [0.0, 0.0, 0.0]
        /// @endcode
        ///
        /// @return             Line origin

        Point                   getOrigin                                   ( ) const ;

        /// @brief              Get line direction
        ///
        /// @code
        ///                     Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).getDirection() ; // [0.0, 0.0, 1.0]
        /// @endcode
        ///
        /// @return             Line direction

        Vector3d                getDirection                                ( ) const ;

        /// @brief              Translate line
        ///
        /// @param              [in] aTranslation A translation vector

        virtual void            translate                                   (   const   Vector3d&                   aTranslation                                ) override ;

        /// @brief              Rotate line
        ///
        /// @param              [in] aRotation A rotation quaternion
        
        virtual void            rotate                                      (   const   Quaternion&                 aRotation                                   ) override ;

        /// @brief              Constructs an undefined line
        ///
        /// @code
        ///                     Line line = Line::Undefined() ; // Undefined
        /// @endcode
        ///
        /// @return             Undefined line

        static Line             Undefined                                   ( ) ;

    private:

        Point                   origin_ ;
        Vector3d                direction_ ;

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