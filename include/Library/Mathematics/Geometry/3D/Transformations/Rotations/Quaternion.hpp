////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           Library/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_3D_Transformations_Rotations_Quaternion__
#define __OpenSpaceToolkit_Mathematics_Geometry_3D_Transformations_Rotations_Quaternion__

#include <Library/Mathematics/Geometry/Angle.hpp>
#include <Library/Mathematics/Objects/Vector.hpp>

#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Real.hpp>
#include <Library/Core/Types/Integer.hpp>

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

using library::core::types::Integer ;
using library::core::types::Real ;
using library::core::types::String ;

using library::math::obj::Vector3d ;
using library::math::obj::Vector4d ;
using library::math::geom::Angle ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RotationVector ;
class RotationMatrix ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Quaternion
///
///                             Provide a convenient mathematical notation for representing orientations and rotations of objects in three dimensions.
///                             Compared to Euler angles they are simpler to compose and avoid the problem of gimbal lock.
///                             Compared to rotation matrices they are more compact, more numerically stable, and more efficient.
///
/// @ref                        https://en.wikipedia.org/wiki/Quaternion
/// @ref                        https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation

class Quaternion
{

    public:

        /// @brief              Quaternion format

        enum class Format
        {

            XYZS,               ///< Vector-scalar format
            SXYZ                ///< Scalar-vector format

        } ;

        /// @brief              Constructor
        ///
        /// @code
        ///                     Quaternion quaternion = { 0.0, 0.0, 0.0, 0.1, Quaternion::Format::XYZS } ;
        /// @endcode
        ///
        /// @param              [in] aFirstComponent A first component
        /// @param              [in] aSecondComponent A second component
        /// @param              [in] aThirdComponent A third component
        /// @param              [in] aFourthComponent A fourth component
        /// @param              [in] aFormat A quaternion format

                                Quaternion                                  (   const   Real&                       aFirstComponent,
                                                                                const   Real&                       aSecondComponent,
                                                                                const   Real&                       aThirdComponent,
                                                                                const   Real&                       aFourthComponent,
                                                                                const   Quaternion::Format&         aFormat                                     ) ;

        /// @brief              Constructor
        ///
        /// @code
        ///                     Quaternion quaternion = { Vector4d(0.0, 0.0, 0.0, 0.1), Quaternion::Format::XYZS } ;
        /// @endcode
        ///
        /// @param              [in] aVector A 4D vector
        /// @param              [in] aFormat A quaternion format

                                Quaternion                                  (   const   Vector4d&                   aVector,
                                                                                const   Quaternion::Format&         aFormat                                     ) ;

        /// @brief              Constructor
        ///
        /// @code
        ///                     Quaternion quaternion = { Vector3d(0.0, 0.0, 0.0), 1.0 } ;
        /// @endcode
        ///
        /// @param              [in] aVectorPart A vector part
        /// @param              [in] aVectorPart A scalar part

                                Quaternion                                  (   const   Vector3d&                   aVectorPart,
                                                                                const   Real&                       aScalarPart                                 ) ;

        /// @brief              Equal to operator
        ///
        /// @code
        ///                     Quaternion::XYZS(0.0, 0.0, 0.0, 1.0) == Quaternion::XYZS(0.0, 0.0, 0.0, 1.0) ; // True
        /// @endcode
        ///
        /// @param              [in] aQuaternion A quaternion
        /// @return             True if quaternions are equal

        bool                    operator ==                                 (   const   Quaternion&                 aQuaternion                                 ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     Quaternion::XYZS(0.0, 0.0, 0.0, 1.0) != Quaternion::XYZS(1.0, 0.0, 0.0, 0.0) ; // True
        /// @endcode
        ///
        /// @param              [in] aQuaternion A quaternion
        /// @return             True if quaternions are not equal

        bool                    operator !=                                 (   const   Quaternion&                 aQuaternion                                 ) const ;

        /// @brief              Multiplication operator (quaternion)
        ///
        /// @code
        ///                     Quaternion q_B_A = ... ;
        ///                     Quaternion q_C_B = ... ;
        ///                     Quaternion q_C_A = q_C_B * q_B_A ;
        /// @encode
        ///
        /// @note               This operator uses cross multiplication
        ///
        /// @param              [in] aQuaternion A quaternion
        /// @return             A quaternion

        Quaternion              operator *                                  (   const   Quaternion&                 aQuaternion                                 ) const ;

        /// @brief              Multiplication operator (vector)
        ///
        /// Example:
        /// @code
        ///                     Quaternion q_B_A = ... ;
        ///                     Vector3d v_A = ... ;
        ///                     Vector3d v_B = q_B_A * v_A ;
        /// @endcode
        ///
        /// @note               This operator uses transformVector
        ///
        /// @param              [in] aVector A vector
        /// @return             A vector

        Vector3d                operator *                                  (   const   Vector3d&                   aVector                                     ) const ;

        /// @brief              Division operator (quaternion)
        ///
        /// @code
        ///                     Quaternion q_A_B = ... ;
        ///                     Quaternion q_C_B = ... ;
        ///                     Quaternion q_C_A = q_C_B / q_A_B ;
        /// @endcode
        ///
        /// @note               This is equivalent to multiplying with the inverse
        ///
        /// @param              [in] aQuaternion A quaternion
        /// @return             A quaternion

        Quaternion              operator /                                  (   const   Quaternion&                 aQuaternion                                 ) const ;

        /// @brief              Multiplication assignment operator (quaternion)
        ///
        /// @note               This operator uses cross multiplication
        ///
        /// @param              [in] aQuaternion A quaternion
        /// @return             A reference to quaternion

        Quaternion&             operator *=                                 (   const   Quaternion&                 aQuaternion                                 ) ;

        /// @brief              Division assignment operator (quaternion)
        ///
        /// @note               This is equivalent to multiplying with the inverse
        ///
        /// @param              [in] aQuaternion A quaternion
        /// @return             A reference to quaternion

        Quaternion&             operator /=                                 (   const   Quaternion&                 aQuaternion                                 ) ;

        /// @brief              Output stream operator
        ///
        /// @code
        ///                     std::cout << Quaternion::XYZS(0.0, 0.0, 0.0, 1.0) ;
        /// @endcode
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] aQuaternion A quaternion
        /// @return             A reference to output stream

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Quaternion&                 aQuaternion                                 ) ;

        /// @brief              Check if quaternion is defined
        ///
        /// @code
        ///                     Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).isDefined() ; // True
        /// @endcode
        ///
        /// @return             True if quaternion is defined

        bool                    isDefined                                   ( ) const ;

        /// @brief              Check if quaternion is unitary, i.e. its norm is equal to 1.0
        ///
        /// @code
        ///                     Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).isUnitary() ; // True
        /// @endcode
        ///
        /// @return             True if quaternion is unitary

        bool                    isUnitary                                   ( ) const ;

        /// @brief              Check if quaternion is near a given quaternion
        ///
        /// @code
        ///                     Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).isNear(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0 + 1e-19), Angle::Radians(1e-6)) ; // True
        /// @endcode
        ///
        /// @param              [in] aQuaternion A quaternion
        /// @param              [in] anAngularTolerance An angular tolerance
        /// @return             True if quaternions are near each other

        bool                    isNear                                      (   const   Quaternion&                 aQuaternion,
                                                                                const   Angle&                      anAngularTolerance                          ) const ;

        /// @brief              Get first component of vector part
        ///
        /// @code
        ///                     Quaternion::XYSZ(0.0, 0.0, 0.0, 1.0).x() ; // &0.0
        /// @endcode
        ///
        /// @return             First component of vector part

        Real                    x                                           ( ) const ;

        /// @brief              Get second component of vector part
        ///
        /// @code
        ///                     Quaternion::XYSZ(0.0, 0.0, 0.0, 1.0).y() ; // &0.0
        /// @endcode
        ///
        /// @return             Second component of vector part

        Real                    y                                           ( ) const ;

        /// @brief              Get third component of vector part
        ///
        /// @code
        ///                     Quaternion::XYSZ(0.0, 0.0, 0.0, 1.0).z() ; // &0.0
        /// @endcode
        ///
        /// @return             Third component of vector part

        Real                    z                                           ( ) const ;

        /// @bref               Get scalar part
        ///
        /// @code
        ///                     Quaternion::XYSZ(0.0, 0.0, 0.0, 1.0).s() ; // &1.0
        /// @endcode
        ///
        /// @return             Scalar part

        Real                    s                                           ( ) const ;

        /// @brief              Get vector part
        ///
        /// @code
        ///                     Quaternion::XYSZ(0.0, 0.0, 0.0, 1.0).getVectorPart() ; // [0.0, 0.0, 0.0]
        /// @endcode
        ///
        /// @return             Vector part

        Vector3d                getVectorPart                               ( ) const ;

        /// @brief              Get scalar part
        ///
        /// @code
        ///                     Quaternion::XYSZ(0.0, 0.0, 0.0, 1.0).getScalarPart() ; // 1.0
        /// @endcode
        ///
        /// @return             Scalar part

        Real                    getScalarPart                               ( ) const ;

        /// @brief              Get normalized quaternion
        ///
        /// @code
        ///                     Quaternion::XYZS(0.0, 0.0, 0.0, 1.000000000000001).toNormalized() ; // [0.0, 0.0, 0.0, 1.0]
        /// @encode
        ///
        /// @return             Normalized quaternion

        Quaternion              toNormalized                                ( ) const ;

        /// @brief              Get conjugate quaternion
        ///
        /// @code
        ///                     Quaternion::XYZS(0.0, 0.0, 0.70710678118, 0.70710678118).toConjugate() ; // [0.0, 0.0, -0.70710678118, 0.70710678118]
        /// @encode
        ///
        /// @return             Conjugate quaternion

        Quaternion              toConjugate                                 ( ) const ;

        /// @brief              Get inverse quaternion
        ///
        /// @code
        ///                     Quaternion::XYZS(0.0, 0.0, 0.70710678118, 0.70710678118).toInverse() ; // [0.0, 0.0, -0.70710678118, 0.70710678118]
        /// @encode
        ///
        /// @return             Inverse quaternion

        Quaternion              toInverse                                   ( ) const ;

        /// @brief              Get power
        ///
        /// @code
        ///                     TBC...
        /// @endcode
        ///
        /// @param              [in] aValue A power value
        /// @return             Power

        Quaternion              pow                                         (   const   Real&                       aValue                                      ) const ;

        /// @brief              Get exponential
        ///
        /// @code
        ///                     TBC...
        /// @endcode
        ///
        /// @return             Exponential

        Quaternion              exp                                         ( ) const ;

        /// @brief              Get logarithm
        ///
        /// @code
        ///                     TBC...
        /// @endcode
        ///
        /// @return             Logarithm

        Quaternion              log                                         ( ) const ;

        /// @brief              Get quaternion norm
        ///
        /// @code
        ///                     Quaternion::XYZS(0.0, 0.0, -0.70710678118, 0.70710678118).norm() ; // 1.0
        /// @encode
        ///
        /// @return             Quaternion norm

        Real                    norm                                        ( ) const ;

        Quaternion              crossMultiply                               (   const   Quaternion&                 aQuaternion                                 ) const ;

        Quaternion              dotMultiply                                 (   const   Quaternion&                 aQuaternion                                 ) const ;

        Vector3d                rotateVector                                (   const   Vector3d&                   aVector                                     ) const ;

        /// @brief              Convert quaternion to its vector representation
        ///
        /// @code
        ///                     Quaternion::XYSZ(0.0, 0.0, 0.0, 1.0).toVector() ; // [0.0, 0.0, 0.0, 1.0]
        /// @endcode
        ///
        /// @param              [in] (optional) aFormat A quaternion format
        /// @return             Vector representation

        Vector4d                toVector                                    (   const   Quaternion::Format&         aFormat                                     =   Quaternion::Format::XYZS ) const ;

        /// @brief              Convert quaternion to its string representation
        ///
        /// @code
        ///                     Quaternion::XYSZ(0.0, 0.0, 0.0, 1.0).toString() ; // "[0.0, 0.0, 0.0, 1.0]"
        /// @endcode
        ///
        /// @param              [in] (optional) aPrecision A quaternion precision
        /// @param              [in] (optional) aFormat A quaternion format
        /// @return             String representation

        String                  toString                                    (   const   Quaternion::Format&         aFormat                                     ) const ;

        String                  toString                                    (   const   Integer&                    aPrecision                                  =   Integer::Undefined(),
                                                                                const   Quaternion::Format&         aFormat                                     =   Quaternion::Format::XYZS ) const ;

        /// @brief              Normalize quaternion
        ///
        /// @code
        ///                     Quaternion quaternion = Quaternion::XYZS(0.0, 0.0, 0.0, 1.000000000000001) ; // [0.0, 0.0, 0.0, 1.000000000000001]
        ///                     quaternion.normalize() ; // [0.0, 0.0, 0.0, 1.0]
        /// @endcode
        ///
        /// @return             Reference to quaternion

        Quaternion&             normalize                                   ( ) ;

        /// @brief              Conjugate quaternion
        ///
        /// @code
        ///                     Quaternion quaternion = Quaternion::XYZS(0.0, 0.0, 0.70710678118, 0.70710678118) ; // [0.0, 0.0, 0.70710678118, 0.70710678118]
        ///                     quaternion.conjugate() ; // [0.0, 0.0, -0.70710678118, 0.70710678118]
        /// @endcode
        ///
        /// @return             Reference to quaternion

        Quaternion&             conjugate                                   ( ) ;

        /// @brief              Inverse quaternion
        ///
        /// @code
        ///                     Quaternion quaternion = Quaternion::XYZS(0.0, 0.0, 0.70710678118, 0.70710678118) ; // [0.0, 0.0, 0.70710678118, 0.70710678118]
        ///                     quaternion.inverse() ; // [0.0, 0.0, -0.70710678118, 0.70710678118]
        /// @endcode
        ///
        /// @return             Reference to quaternion

        Quaternion&             inverse                                    ( ) ;

        /// @brief              Rectify quaternion (enforce positive scalar part)
        ///
        /// @code
        ///                     Quaternion quaternion = Quaternion::XYZS(0.0, 0.0, -0.70710678118, -0.70710678118) ; // [0.0, 0.0, -0.70710678118, -0.70710678118]
        ///                     quaternion.rectify() ; // [0.0, 0.0, 0.70710678118, 0.70710678118]
        /// @endcode
        ///
        /// @return             Reference to quaternion

        Quaternion&             rectify                                     ( ) ;

        /// @brief              Get angular difference with quaternion
        ///
        /// @code
        ///                     Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).angularDifferenceWith(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0)) ; // 0.0 [rad]
        /// @endcode
        ///
        /// @param              [in] aQuaternion A quaternion
        /// @return             Angular difference

        Angle                   angularDifferenceWith                       (   const   Quaternion&                 aQuaternion                                 ) const ;

        /// @brief              Constructs an undefined quaternion
        ///
        /// @code
        ///                     Quaternion quaternion = Quaternion::Undefined() ; // Undefined
        /// @endcode
        ///
        /// @return             Undefined quaternion

        static Quaternion       Undefined                                   ( ) ;

        /// @brief              Constructs a unit quaternion
        ///
        /// @code
        ///                     Quaternion quaternion = Quaternion::Unit() ; // [0.0, 0.0, 0.0, 1.0]
        /// @endcode
        ///
        /// @return             Unit quaternion

        static Quaternion       Unit                                        ( ) ;

        /// @brief              Constructs a quaternion using the vector-scalar format
        ///
        /// @code
        ///                     Quaternion quaternion = Quaternion::XYZS(0.0, 0.0, 0.0, 1.0) ; // [0.0, 0.0, 0.0, 1.0]
        /// @endcode
        ///
        /// @param              [in] aFirstComponent A first component
        /// @param              [in] aSecondComponent A second component
        /// @param              [in] aThirdComponent A third component
        /// @param              [in] aFourthComponent A fourth component
        /// @return             Quaternion

        static Quaternion       XYZS                                        (   const   Real&                       aFirstComponent,
                                                                                const   Real&                       aSecondComponent,
                                                                                const   Real&                       aThirdComponent,
                                                                                const   Real&                       aFourthComponent                            ) ;

        /// @brief              Constructs a quaternion from a rotation vector
        ///
        /// @code
        ///                     Quaternion quaternion = Quaternion::RotationVector(RotationVector(Vector3d(0.0, 0.0, 1.0), Angle::Degrees(0.0))) ; // [0.0, 0.0, 0.0, 1.0]
        /// @endcode
        ///
        /// @param              [in] aRotationVector A rotation vector
        /// @return             Quaternion

        static Quaternion       RotationVector                              (   const   rot::RotationVector&        aRotationVector                             ) ;

        /// @brief              Constructs a rquaternion from a rotation matrix
        ///
        /// @code
        ///                     Quaternion quaternion = Quaternion::RotationMatrix(RotationMatrix::Unit()) ;
        /// @endcode
        ///
        /// @param              [in] aRotationMatrix A rotation matrix
        /// @return             Quaternion

        static Quaternion       RotationMatrix                              (   const   rot::RotationMatrix&        aRotationMatrix                             ) ;

        /// @brief              Constructs a quaternion from a string
        ///
        /// @code
        ///                     Quaternion quaternion = Quaternion::Parse("[0.0, 0.0, 0.0, 1.0]") ; // [0.0, 0.0, 0.0, 1.0]
        /// @endcode
        ///
        /// @param              [in] aString A string
        /// @param              [in] (optional) aFormat A quaternion format
        /// @return             Quaternion

        static Quaternion       Parse                                       (   const   String&                     aString,
                                                                                const   Quaternion::Format&         aFormat                                     =   Quaternion::Format::XYZS ) ;

    private:

        Real                    x_ ;
        Real                    y_ ;
        Real                    z_ ;
        Real                    s_ ;

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
