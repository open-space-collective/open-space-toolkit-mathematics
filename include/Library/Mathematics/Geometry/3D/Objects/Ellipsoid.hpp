////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Mathematics_Geometry_3D_Objects_Ellipsoid__
#define __Library_Mathematics_Geometry_3D_Objects_Ellipsoid__

#include <Library/Mathematics/Geometry/Transformations/Rotations/Quaternion.hpp>
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
using library::math::geom::trf::rot::Quaternion ;

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
        ///                     Ellipsoid ellipsoid({ 0.0, 0.0, 0.0 }, 1.0) ;
        /// @endcode
        ///
        /// @param              [in] aCenter An ellipsoid center
        /// @param              [in] aRadius An ellipsoid radius

                                Ellipsoid                                   (   const   Vector3d&                   aCenter,
                                                                                const   Real&                       aRadius                                     ) ;

        /// @brief              Equal to operator
        ///
        /// @code
        ///                     Ellipsoid(Vector3d::Zero(), 1.0) == Ellipsoid(Vector3d::Zero(), 1.0) ; // True
        /// @endcode
        ///
        /// @param              [in] anEllipsoid An ellipsoid
        /// @return             True if ellipsoids are equal

        bool                    operator ==                                 (   const   Ellipsoid&                  anEllipsoid                                 ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     Ellipsoid(Vector3d::Zero(), 1.0) != Ellipsoid(2.0) ; // True
        /// @endcode
        ///
        /// @param              [in] anEllipsoid An ellipsoid
        /// @return             True if ellipsoids not are equal

        bool                    operator !=                                 (   const   Ellipsoid&                  anEllipsoid                                 ) const ;

        /// @brief              Output stream operator
        ///
        /// @code
        ///                     std::cout << Ellipsoid(Vector3d::Zero(), 1.0) ;
        /// @endcode
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] anEllipsoid An ellipsoid
        /// @return             An output stream

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Ellipsoid&                  anEllipsoid                                 ) ;

        /// @brief              Check if ellipsoid is defined
        ///
        /// @code
        ///                     Ellipsoid(Vector3d::Zero(), 1.0).isDefined() ; // True
        /// @endcode
        ///
        /// @return             True if ellipsoid is defined

        virtual bool            isDefined                                   ( ) const override ;

        /// @brief              Check if ellipsoid is unitary, i.e. its radius is equal to 1.0
        ///
        /// @code
        ///                     Ellipsoid(Vector3d::Zero(), 1.0).isUnitary() ; // True
        /// @endcode
        ///
        /// @return             True if ellipsoid is unitary

        bool                    isUnitary                                   ( ) const ;

        /// @brief              Get ellipsoid center
        ///
        /// @code
        ///                     Ellipsoid(Vector3d::Zero(), 1.0).getCenter() ; // [0.0, 0.0, 0.0]
        /// @endcode
        ///
        /// @return             Ellipsoid center

        Vector3d                getCenter                                   ( ) const ;

        /// @brief              Get ellipsoid radius
        ///
        /// @code
        ///                     Ellipsoid(Vector3d::Zero(), 1.0).getRadius() ; // 1.0
        /// @endcode
        ///
        /// @return             Ellipsoid radius

        Real                    getRadius                                   ( ) const ;

        /// @brief              Constructs an undefined ellipsoid
        ///
        /// @code
        ///                     Ellipsoid ellipsoid = Ellipsoid::Undefined() ; // Undefined
        /// @endcode
        ///
        /// @return             Undefined ellipsoid

        static Ellipsoid        Undefined                                   ( ) ;

    private:

        Vector3d                center_ ;

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