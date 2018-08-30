////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Intersection.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Mathematics_Geometry_3D_Intersection__
#define __Library_Mathematics_Geometry_3D_Intersection__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Sphere.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Plane.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ray.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/LineString.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Line.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/PointSet.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Point.hpp>
#include <Library/Mathematics/Geometry/3D/Object.hpp>

#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Types/Unique.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace math
{
namespace geom
{
namespace d3
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Unique ;
using library::core::ctnr::Array ;

using library::math::geom::d3::Object ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      3D intersection

class Intersection
{

    public:

        enum class Type
        {

            Undefined,
            Empty,
            Point,
            PointSet,
            Line,
            LineString,
            Ray,
            Segment,
            Plane,
            Sphere,
            Ellipsoid,
            Complex

        } ;

        /// @brief              Constructor
        ///
        /// @param              [in] anObjectArray An array of objects

                                Intersection                                (   const   Array<Unique<Object>>&      anObjectArray                               ) ;

        /// @brief              Copy constructor
        ///
        /// @param              [in] anIntersection An intersection

                                Intersection                                (   const   Intersection&               anIntersection                              ) ;

        /// @brief              Destructor

                                ~Intersection                               ( ) ;

        /// @brief              Copy assignment operator
        ///
        /// @param              [in] anIntersection An intersection
        /// @return             Reference to intersection

        Intersection&           operator =                                  (   const   Intersection&               anIntersection                              ) ;

        /// @brief              Equal to operator
        ///
        /// @param              [in] anIntersection An intersection
        /// @return             True if intersections are equal

        bool                    operator ==                                 (   const   Intersection&               anIntersection                              ) const ;

        /// @brief              Not equal to operator
        ///
        /// @param              [in] anIntersection An intersection
        /// @return             True if intersections not are equal

        bool                    operator !=                                 (   const   Intersection&               anIntersection                              ) const ;

        /// @brief              Output stream operator
        ///
        /// @code
        ///                     std::cout << Intersection(...) ;
        /// @endcode
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] anIntersection An intersection
        /// @return             A reference to output stream

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Intersection&               anIntersection                              ) ;

        /// @brief              Check if intersection is defined
        ///
        /// @return             True if intersection is defined

        bool                    isDefined                                   ( ) const ;

        /// @brief              Check if intersection is empty
        ///
        /// @return             True if intersection is empty

        bool                    isEmpty                                     ( ) const ;

        /// @brief              Returns true if intersection can be converted to underlying object
        ///
        /// @return             True if intersection can be converted to underlying object

        template <class Type>
        bool                    is                                          ( ) const
        {
            return (!objects_.isEmpty()) && (dynamic_cast<const Type*>(objects_.accessFirst().get()) != nullptr) ;
        }

        /// @brief              Get intersection type
        ///
        /// @return             Intersection type

        Intersection::Type      getType                                     ( ) const ;

        /// @brief              Access intersection as its underlying object
        ///
        /// @return             Reference to underlying object

        template <class Type>
        const Type&             as                                          ( ) const
        {

            if (objects_.isEmpty())
            {
                throw library::core::error::RuntimeError("Cannot convert intersection: it is empty.") ;
            }

            const Type* objectPtr = dynamic_cast<const Type*>(objects_.accessFirst().get()) ;

            if (objectPtr == nullptr)
            {
                throw library::core::error::RuntimeError("Cannot convert intersection: wrong type.") ;
            }

            return *objectPtr ;

        }

        /// @brief              Constructs an undefined intersection
        ///
        /// @code
        ///                     Intersection intersection = Intersection::Undefined() ; // Undefined
        /// @endcode
        ///
        /// @return             Undefined intersection

        static Intersection     Undefined                                   ( ) ;

        /// @brief              Constructs an empty intersection
        ///
        /// @code
        ///                     Intersection intersection = Intersection::Empty() ;
        /// @endcode
        ///
        /// @return             Empty intersection

        static Intersection     Empty                                       ( ) ;

        /// @brief              Constructs a point intersection
        ///
        /// @code
        ///                     Intersection intersection = Intersection::Point(Point(0.0, 0.0, 0.0)) ;
        /// @endcode
        ///
        /// @return             Point intersection

        static Intersection     Point                                       (   const   objects::Point&             aPoint                                      ) ;

        /// @brief              Constructs a point set intersection
        ///
        /// @code
        ///                     Intersection intersection = Intersection::PointSet({ Point(0.0, 0.0, 0.0), Point(1.0, 0.0, 0.0) }) ;
        /// @endcode
        ///
        /// @return             Point set intersection

        static Intersection     PointSet                                    (   const   objects::PointSet&          aPointSet                                   ) ;

        /// @brief              Constructs a line string intersection
        ///
        /// @code
        ///                     Intersection intersection = Intersection::LineString({ Point(0.0, 0.0, 0.0), Point(1.0, 0.0, 0.0), Point(1.0, 0.0, 1.0) }) ;
        /// @endcode
        ///
        /// @return             Line string intersection

        static Intersection     LineString                                  (   const   objects::LineString&        aLineString                                 ) ;

        /// @brief              Converts intersection type to string
        ///
        /// @return             String

        static String           StringFromType                              (   const   Intersection::Type&         aType                                       ) ;

    private:

        Intersection::Type      type_ ;

        Array<Unique<Object>>   objects_ ;

                                Intersection                                ( ) ;

                                Intersection                                (   const   Intersection::Type&         aType,
                                                                                const   Array<Unique<Object>>&      anObjectArray                               ) ;

        static Intersection::Type TypeFromObjects                           (   const   Array<Unique<Object>>&      anObjectArray                               ) ;

        static Intersection::Type TypeFromObject                            (   const   Unique<Object>&             anObjectUPtr                                ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////