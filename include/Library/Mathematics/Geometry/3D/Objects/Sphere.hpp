////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Sphere.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Mathematics_Geometry_3D_Objects_Sphere__
#define __Library_Mathematics_Geometry_3D_Objects_Sphere__

#include <Library/Mathematics/Geometry/3D/Object.hpp>
#include <Library/Mathematics/Objects/Vector.hpp>
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Sphere
///
/// @ref                        https://en.wikipedia.org/wiki/Sphere

class Sphere : public Object
{

    public:

        /// @brief              Constructor
        ///
        /// @code
        ///                     Sphere sphere({ 0.0, 0.0, 0.0 }, 1.0) ;
        /// @endcode
        ///
        /// @param              [in] aCenter A sphere center
        /// @param              [in] aRadius A sphere radius

                                Sphere                                      (   const   Vector3d&                   aCenter,
                                                                                const   Real&                       aRadius                                     ) ;

        /// @brief              Equal to operator
        ///
        /// @code
        ///                     Sphere(Vector3d::Zero(), 1.0) == Sphere(Vector3d::Zero(), 1.0) ; // True
        /// @endcode
        ///
        /// @param              [in] aSphere A sphere
        /// @return             True if spheres are equal

        bool                    operator ==                                 (   const   Sphere&                     aSphere                                     ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     Sphere(Vector3d::Zero(), 1.0) != Sphere(2.0) ; // True
        /// @endcode
        ///
        /// @param              [in] aSphere A sphere
        /// @return             True if spheres not are equal

        bool                    operator !=                                 (   const   Sphere&                     aSphere                                     ) const ;

        /// @brief              Output stream operator
        ///
        /// @code
        ///                     std::cout << Sphere(Vector3d::Zero(), 1.0) ;
        /// @endcode
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] aSphere A sphere
        /// @return             An output stream

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Sphere&                     aSphere                                     ) ;

        /// @brief              Check if sphere is defined
        ///
        /// @code
        ///                     Sphere(Vector3d::Zero(), 1.0).isDefined() ; // True
        /// @endcode
        ///
        /// @return             True if sphere is defined

        virtual bool            isDefined                                   ( ) const override ;

        /// @brief              Check if sphere is unitary, i.e. its radius is equal to 1.0
        ///
        /// @code
        ///                     Sphere(Vector3d::Zero(), 1.0).isUnitary() ; // True
        /// @endcode
        ///
        /// @return             True if sphere is unitary

        bool                    isUnitary                                   ( ) const ;

        /// @brief              Get sphere center
        ///
        /// @code
        ///                     Sphere(Vector3d::Zero(), 1.0).getCenter() ; // [0.0, 0.0, 0.0]
        /// @endcode
        ///
        /// @return             Sphere center

        Vector3d                getCenter                                   ( ) const ;

        /// @brief              Get sphere radius
        ///
        /// @code
        ///                     Sphere(Vector3d::Zero(), 1.0).getRadius() ; // 1.0
        /// @endcode
        ///
        /// @return             Sphere radius

        Real                    getRadius                                   ( ) const ;

        /// @brief              Constructs an undefined sphere
        ///
        /// @code
        ///                     Sphere sphere = Sphere::Undefined() ; // Undefined
        /// @endcode
        ///
        /// @return             Undefined sphere

        static Sphere           Undefined                                   ( ) ;

        /// @brief              Constructs a unit sphere
        ///
        /// @ref                https://en.wikipedia.org/wiki/Unit_sphere
        ///
        /// @code
        ///                     Sphere sphere = Sphere::Unit({ 0.0, 0.0, 0.0 }) ;
        /// @endcode
        ///
        /// @return             Unit sphere

        static Sphere           Unit                                        (   const   Vector3d&                   aCenter                                     ) ;

    private:

        Vector3d                center_ ;
        Real                    radius_ ;

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