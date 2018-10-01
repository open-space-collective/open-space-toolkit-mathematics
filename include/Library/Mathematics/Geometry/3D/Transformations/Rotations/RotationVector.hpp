////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Mathematics_Geometry_3D_Transformations_Rotations_RotationVector__
#define __Library_Mathematics_Geometry_3D_Transformations_Rotations_RotationVector__

#include <Library/Mathematics/Geometry/Angle.hpp>
#include <Library/Mathematics/Objects/Vector.hpp>

#include <Library/Core/Types/String.hpp>
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
namespace trf
{
namespace rot
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Real ;
using library::core::types::String ;

using library::math::obj::Vector3d ;
using library::math::geom::Angle ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Quaternion ;
class RotationMatrix ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Rotation vector
///
/// @ref                        https://en.wikipedia.org/wiki/Axis–angle_representation#Rotation_vector

class RotationVector
{

    public:

        /// @brief              Constructor
        ///
        /// @param              [in] anAxis A rotation axis
        /// @param              [in] anAngle A rotation angle

                                RotationVector                              (   const   Vector3d&                   anAxis,
                                                                                const   Angle&                      anAngle                                     ) ;

        /// @brief              Equal to operator
        ///
        /// @code
        ///                     RotationVector(Vector3d(0.0, 0.0, 1.0), Angle::Degrees(90.0)) == RotationVector(Vector3d(0.0, 0.0, 1.0), Angle::Degrees(90.0)) ; // True
        /// @endcode
        ///
        /// @param              [in] aRotationVector A rotation vector
        /// @return             True if rotation vectors are equal

        bool                    operator ==                                 (   const   RotationVector&             aRotationVector                             ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     RotationVector(Vector3d(0.0, 0.0, 1.0), Angle::Degrees(90.0)) != RotationVector(Vector3d(1.0, 0.0, 0.0), Angle::Degrees(90.0)) ; // True
        /// @endcode
        ///
        /// @param              [in] aRotationVector A rotation vector
        /// @return             True if rotation vectors are not equal

        bool                    operator !=                                 (   const   RotationVector&             aRotationVector                             ) const ;

        /// @brief              Output stream operator
        ///
        /// @code
        ///                     std::cout << RotationVector(Vector3d(0.0, 0.0, 1.0), Angle::Degrees(90.0)) ;
        /// @endcode
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] aRotationVector A rotation vector
        /// @return             A reference to output stream

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   RotationVector&             aRotationVector                             ) ;

        /// @brief              Check if rotation vector is defined
        ///
        /// @code
        ///                     RotationVector(Vector3d(0.0, 0.0, 1.0), Angle::Degrees(90.0)).isDefined() ; // True
        /// @endcode
        ///
        /// @return             True if rotation vector is defined

        bool                    isDefined                                   ( ) const ;

        /// @brief              Get rotation axis
        ///
        /// @return             Rotation axis

        Vector3d                getAxis                                     ( ) const ;

        /// @brief              Get rotation angle
        ///
        /// @return             Rotation angle
        
        Angle                   getAngle                                    ( ) const ;

        /// @brief              Convert rotation vector to its string representation
        ///
        /// @code
        ///                     RotationVector(Vector3d(0.0, 0.0, 1.0), Angle::Degrees(90.0)).toString() ; // "[0.0, 0.0, 1.0] : 90.0 [deg]"
        /// @endcode
        ///
        /// @param              [in] (optional) aPrecision A precision
        /// @return             String representation

        String                  toString                                    (   const   Integer&                    aPrecision                                  =   Integer::Undefined() ) const ;

        /// @brief              Constructs an undefined rotation vector
        ///
        /// @code
        ///                     RotationVector rotationVector = RotationVector::Undefined() ; // Undefined
        /// @endcode
        ///
        /// @return             Undefined rotation vector

        static RotationVector   Undefined                                   ( ) ;

        /// @brief              Constructs a unit rotation vector
        ///
        /// @code
        ///                     RotationVector rotationVector = RotationVector::Unit() ;
        /// @endcode
        ///
        /// @return             Unit rotation vector

        static RotationVector   Unit                                        ( ) ;

        /// @brief              Constructs a rotation vector around X-axis
        ///
        /// @code
        ///                     RotationVector rotationVector = RotationVector::X(Angle::Degrees(45.0)) ;
        /// @endcode
        ///
        /// @param              [in] anAngle A rotation angle
        /// @return             Rotation vector

        static RotationVector   X                                           (   const   Angle&                      anAngle                                     ) ;

        /// @brief              Constructs a rotation vector around Y-axis
        ///
        /// @code
        ///                     RotationVector rotationVector = RotationVector::X(Angle::Degrees(45.0)) ;
        /// @endcode
        ///
        /// @param              [in] anAngle A rotation angle
        /// @return             Rotation vector

        static RotationVector   Y                                           (   const   Angle&                      anAngle                                     ) ;

        /// @brief              Constructs a rotation vector around Z-axis
        ///
        /// @code
        ///                     RotationVector rotationVector = RotationVector::X(Angle::Degrees(45.0)) ;
        /// @endcode
        ///
        /// @param              [in] anAngle A rotation angle
        /// @return             Rotation vector

        static RotationVector   Z                                           (   const   Angle&                      anAngle                                     ) ;

        /// @brief              Constructs a rotation vector from a quaternion
        ///
        /// @code
        ///                     RotationVector rotationVector = RotationVector::Quaternion(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0)) ;
        /// @endcode
        ///
        /// @param              [in] aQuaternion A quaternion
        /// @return             Rotation vector

        static RotationVector   Quaternion                                  (   const   rot::Quaternion&            aQuaternion                                 ) ;

        /// @brief              Constructs a rotation vector from a rotation matrix
        ///
        /// @code
        ///                     RotationVector rotationVector = RotationVector::RotationMatrix(RotationMatrix::Unit()) ;
        /// @endcode
        ///
        /// @param              [in] aRotationMatrix A rotation matrix
        /// @return             Rotation vector

        static RotationVector   RotationMatrix                              (   const   rot::RotationMatrix&        aRotationMatrix                             ) ;

    private:

        Vector3d                axis_ ;
        Angle                   angle_ ;

                                RotationVector                              ( ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////