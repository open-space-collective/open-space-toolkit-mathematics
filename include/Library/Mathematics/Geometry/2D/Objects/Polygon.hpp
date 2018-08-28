////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/2D/Objects/Polygon.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Mathematics_Geometry_2D_Objects_Polygon__
#define __Library_Mathematics_Geometry_2D_Objects_Polygon__

#include <Library/Mathematics/Geometry/2D/Objects/Point.hpp>
#include <Library/Mathematics/Geometry/2D/Object.hpp>

#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Types/Unique.hpp>

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

using library::core::types::Unique ;
using library::core::ctnr::Array ;

using library::math::geom::d2::Object ;
using library::math::geom::d2::objects::Point ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Polygon
///
///                             A polygon is a plane figure that is bounded by a finite chain of straight line segments closing in a loop
///                             to form a closed polygonal chain or circuit.
///                             These segments are called its edges, and the points where two edges meet are the polygon's vertices.
///
/// @ref                        https://en.wikipedia.org/wiki/Polygon

class Polygon : public Object
{

    public:

        /// @brief              Constructor
        ///
        /// @code
        ///                     
        /// @endcode
        ///
        /// @param              [in] anOuterRing An outer ring
        /// @param              [in] anInnerRingArray An array of inner rings

                                Polygon                                     (   const   Array<Point>&               anOuterRing,
                                                                                const   Array<Array<Point>>&        anInnerRingArray                            =   Array<Array<Point>>::Empty() ) ;

        /// @brief              Copy constructor
        ///
        /// @param              [in] aPolygon A polygon

                                Polygon                                     (   const   Polygon&                    aPolygon                                    ) ;

        /// @brief              Destructor (virtual)

        virtual                 ~Polygon                                    ( ) override ;

        /// @brief              Copy assignment operator
        ///
        /// @param              [in] aPolygon A polygon
        /// @return             Reference to polygon

        Polygon&                operator =                                  (   const   Polygon&                    aPolygon                                    ) ;

        /// @brief              Clone polygon
        ///
        /// @return             Pointer to cloned polygon

        virtual Polygon*        clone                                       ( ) const override ;

        /// @brief              Equal to operator
        ///
        /// @code
        ///                     
        /// @endcode
        ///
        /// @param              [in] aPolygon A polygon
        /// @return             True if polygons are equal

        bool                    operator ==                                 (   const   Polygon&                    aPolygon                                    ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     
        /// @endcode
        ///
        /// @param              [in] aPolygon A polygon
        /// @return             True if polygons not are equal

        bool                    operator !=                                 (   const   Polygon&                    aPolygon                                    ) const ;

        /// @brief              Output stream operator
        ///
        /// @code
        ///                     std::cout << Polygon(...) ;
        /// @endcode
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] aPolygon A polygon
        /// @return             An output stream

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Polygon&                    aPolygon                                    ) ;

        /// @brief              Check if polygon is defined
        ///
        /// @code
        ///                     
        /// @endcode
        ///
        /// @return             True if polygon is defined

        virtual bool            isDefined                                   ( ) const override ;

        /// @brief              Get polygon vertices
        ///
        /// @code
        ///                     
        /// @endcode
        ///
        /// @return             Polygon vertices

        Array<Point>            getVertices                                 ( ) const ;

        /// @brief              Translate polygon
        ///
        /// @param              [in] aTranslation A translation vector

        virtual void            translate                                   (   const   Vector2d&                   aTranslation                                ) override ;

        /// @brief              Constructs an undefined polygon
        ///
        /// @code
        ///                     Polygon polygon = Polygon::Undefined() ; // Undefined
        /// @endcode
        ///
        /// @return             Undefined polygon

        static Polygon          Undefined                                   ( ) ;

    private:

        class Impl ;

        Unique<Polygon::Impl>   implUPtr_ ;

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