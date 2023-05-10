/// Apache License 2.0 

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_3D_Transformations_Rotations_Quaternion__
#define __OpenSpaceToolkit_Mathematics_Geometry_3D_Transformations_Rotations_Quaternion__

#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/Angle.hpp>
#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>

namespace ostk
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

using ostk::core::types::Integer;
using ostk::core::types::Real;
using ostk::core::types::String;

using ostk::math::obj::Vector3d;
using ostk::math::obj::Vector4d;
using ostk::math::geom::Angle;

class RotationVector;
class RotationMatrix;

/// @brief                      Quaternion
///
///                             Provide a convenient mathematical notation for representing orientations and rotations
///                             of objects in three dimensions. Compared to Euler angles they are simpler to compose and
///                             avoid the problem of gimbal lock. Compared to rotation matrices they are more compact,
///                             more numerically stable, and more efficient.
///
/// @ref                        https://en.wikipedia.org/wiki/Quaternion
/// @ref                        https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation

class Quaternion
{
   public:
    /// @brief              Quaternion format

    enum class Format
    {

        XYZS,  ///< Vector-scalar format
        SXYZ   ///< Scalar-vector format

    };

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

    Quaternion(
        const Real& aFirstComponent,
        const Real& aSecondComponent,
        const Real& aThirdComponent,
        const Real& aFourthComponent,
        const Quaternion::Format& aFormat
    );

    /// @brief              Constructor
    ///
    /// @code
    ///                     Quaternion quaternion = { Vector4d(0.0, 0.0, 0.0, 0.1), Quaternion::Format::XYZS } ;
    /// @endcode
    ///
    /// @param              [in] aVector A 4D vector
    /// @param              [in] aFormat A quaternion format

    Quaternion(const Vector4d& aVector, const Quaternion::Format& aFormat);

    /// @brief              Constructor
    ///
    /// @code
    ///                     Quaternion quaternion = { Vector3d(0.0, 0.0, 0.0), 1.0 } ;
    /// @endcode
    ///
    /// @param              [in] aVectorPart A vector part
    /// @param              [in] aVectorPart A scalar part

    Quaternion(const Vector3d& aVectorPart, const Real& aScalarPart);

    /// @brief              Equal to operator
    ///
    /// @code
    ///                     Quaternion::XYZS(0.0, 0.0, 0.0, 1.0) == Quaternion::XYZS(0.0, 0.0, 0.0, 1.0) ; // True
    /// @endcode
    ///
    /// @param              [in] aQuaternion A quaternion
    /// @return             True if quaternions are equal

    bool operator==(const Quaternion& aQuaternion) const;

    /// @brief              Not equal to operator
    ///
    /// @code
    ///                     Quaternion::XYZS(0.0, 0.0, 0.0, 1.0) != Quaternion::XYZS(1.0, 0.0, 0.0, 0.0) ; // True
    /// @endcode
    ///
    /// @param              [in] aQuaternion A quaternion
    /// @return             True if quaternions are not equal

    bool operator!=(const Quaternion& aQuaternion) const;

    /// @brief              Addition operator (quaternion)
    ///
    /// @code
    ///                     Quaternion q_1 = ... ;
    ///                     Quaternion q_2 = ... ;
    ///                     Quaternion q_3 = q_1 + q_2 ;
    /// @encode
    ///
    /// @param              [in] aQuaternion A quaternion
    /// @return             Quaternion

    Quaternion operator+(const Quaternion& aQuaternion) const;

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
    /// @return             Quaternion

    Quaternion operator*(const Quaternion& aQuaternion) const;

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
    /// @return             Vector

    Vector3d operator*(const Vector3d& aVector) const;

    /// @brief              Multiplication operator (scalar)
    ///
    /// Example:
    /// @code
    ///                     Quaternion q_1 = ... ;
    ///                     Real scalar = ... ;
    ///                     Quaternion q_2 = q_1 * scalar ;
    /// @endcode
    ///
    /// @param              [in] aScalar A scalar
    /// @return             Quaternion

    Quaternion operator*(const Real& aScalar) const;

    /// @brief              Multiplication operator (scalar)
    ///
    /// Example:
    /// @code
    ///                     Real scalar = ... ;
    ///                     Quaternion q_1 = ... ;
    ///                     Quaternion q_2 = scalar * q_1 ;
    /// @endcode
    ///
    /// @param              [in] aScalar A scalar
    /// @param              [in] aQuaternion A quaternion
    /// @return             Quaternion

    friend Quaternion operator*(const Real& aScalar, const Quaternion& aQuaternion);

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
    /// @return             Quaternion

    Quaternion operator/(const Quaternion& aQuaternion) const;

    /// @brief              Power operator (quaternion)
    ///
    /// @code
    ///                     Quaternion q_1 = ... ;
    ///                     Real scalar = ... ;
    ///                     Quaternion q_2 = q_1 ^ scalar ;
    /// @endcode
    ///
    /// @param              [in] aScalar A scalar
    /// @return             Quaternion

    Quaternion operator^(const Real& aScalar) const;

    /// @brief              Addition assignment operator (quaternion)
    ///
    /// @param              [in] aQuaternion A quaternion
    /// @return             Reference to quaternion

    Quaternion& operator+=(const Quaternion& aQuaternion);

    /// @brief              Multiplication assignment operator (quaternion)
    ///
    /// @note               This operator uses cross multiplication
    ///
    /// @param              [in] aQuaternion A quaternion
    /// @return             Reference to quaternion

    Quaternion& operator*=(const Quaternion& aQuaternion);

    /// @brief              Division assignment operator (quaternion)
    ///
    /// @note               This is equivalent to multiplying with the inverse
    ///
    /// @param              [in] aQuaternion A quaternion
    /// @return             Reference to quaternion

    Quaternion& operator/=(const Quaternion& aQuaternion);

    /// @brief              Output stream operator
    ///
    /// @code
    ///                     std::cout << Quaternion::XYZS(0.0, 0.0, 0.0, 1.0) ;
    /// @endcode
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] aQuaternion A quaternion
    /// @return             A reference to output stream

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Quaternion& aQuaternion);

    /// @brief              Check if quaternion is defined
    ///
    /// @code
    ///                     Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).isDefined() ; // True
    /// @endcode
    ///
    /// @return             True if quaternion is defined

    bool isDefined() const;

    /// @brief              Check if quaternion is unitary, i.e. its norm is equal to 1.0
    ///
    /// @code
    ///                     Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).isUnitary() ; // True
    /// @endcode
    ///
    /// @return             True if quaternion is unitary

    bool isUnitary() const;

    /// @brief              Check if quaternion is near a given quaternion
    ///
    /// @code
    ///                     Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).isNear(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0 + 1e-19),
    ///                     Angle::Radians(1e-6)) ; // True
    /// @endcode
    ///
    /// @param              [in] aQuaternion A quaternion
    /// @param              [in] anAngularTolerance An angular tolerance
    /// @return             True if quaternions are near each other

    bool isNear(const Quaternion& aQuaternion, const Angle& anAngularTolerance) const;

    /// @brief              Get first component of vector part
    ///
    /// @code
    ///                     Quaternion::XYSZ(0.0, 0.0, 0.0, 1.0).x() ; // &0.0
    /// @endcode
    ///
    /// @return             First component of vector part

    Real x() const;

    /// @brief              Get second component of vector part
    ///
    /// @code
    ///                     Quaternion::XYSZ(0.0, 0.0, 0.0, 1.0).y() ; // &0.0
    /// @endcode
    ///
    /// @return             Second component of vector part

    Real y() const;

    /// @brief              Get third component of vector part
    ///
    /// @code
    ///                     Quaternion::XYSZ(0.0, 0.0, 0.0, 1.0).z() ; // &0.0
    /// @endcode
    ///
    /// @return             Third component of vector part

    Real z() const;

    /// @bref               Get scalar part
    ///
    /// @code
    ///                     Quaternion::XYSZ(0.0, 0.0, 0.0, 1.0).s() ; // &1.0
    /// @endcode
    ///
    /// @return             Scalar part

    Real s() const;

    /// @brief              Get vector part
    ///
    /// @code
    ///                     Quaternion::XYSZ(0.0, 0.0, 0.0, 1.0).getVectorPart() ; // [0.0, 0.0, 0.0]
    /// @endcode
    ///
    /// @return             Vector part

    Vector3d getVectorPart() const;

    /// @brief              Get scalar part
    ///
    /// @code
    ///                     Quaternion::XYSZ(0.0, 0.0, 0.0, 1.0).getScalarPart() ; // 1.0
    /// @endcode
    ///
    /// @return             Scalar part

    Real getScalarPart() const;

    /// @brief              Get normalized quaternion
    ///
    /// @code
    ///                     Quaternion::XYZS(0.0, 0.0, 0.0, 1.000000000000001).toNormalized() ; // [0.0, 0.0, 0.0, 1.0]
    /// @encode
    ///
    /// @return             Normalized quaternion

    Quaternion toNormalized() const;

    /// @brief              Get conjugate quaternion
    ///
    /// @code
    ///                     Quaternion::XYZS(0.0, 0.0, 0.70710678118, 0.70710678118).toConjugate() ; // [0.0, 0.0,
    ///                     -0.70710678118, 0.70710678118]
    /// @encode
    ///
    /// @return             Conjugate quaternion

    Quaternion toConjugate() const;

    /// @brief              Get inverse quaternion
    ///
    /// @code
    ///                     Quaternion::XYZS(0.0, 0.0, 0.70710678118, 0.70710678118).toInverse() ; // [0.0, 0.0,
    ///                     -0.70710678118, 0.70710678118]
    /// @encode
    ///
    /// @return             Inverse quaternion

    Quaternion toInverse() const;

    /// @brief              Get exponential
    ///
    /// @code
    ///                     Quaternion q_1 = ...
    ///                     Quaternion q_2 = q_1.exp() ;
    /// @endcode
    ///
    /// @return             Exponential

    Quaternion exp() const;

    /// @brief              Get logarithm
    ///
    /// @code
    ///                     Quaternion q_1 = ...
    ///                     Quaternion q_2 = q_1.log() ;
    /// @endcode
    ///
    /// @return             Logarithm

    Quaternion log() const;

    /// @brief              Get power
    ///
    /// @code
    ///                     Quaternion q_1 = ...
    ///                     Real scalar = ...
    ///                     Quaternion q_2 = q_1 ^ scalar ;
    /// @endcode
    ///
    /// @param              [in] aValue A power value
    /// @return             Power

    Quaternion pow(const Real& aValue) const;

    /// @brief              Get quaternion norm
    ///
    /// @code
    ///                     Quaternion::XYZS(0.0, 0.0, -0.70710678118, 0.70710678118).norm() ; // 1.0
    /// @encode
    ///
    /// @return             Quaternion norm

    Real norm() const;

    /// @brief              Multiply quaternion using cross multiplication
    ///
    /// @code
    ///                     Quaternion q_1 = ...
    ///                     Quaternion q_2 = ...
    ///                     Quaternion q_3 = q_1.crossMultiply(q_2)
    /// @endcode
    ///
    /// @param              [in] aQuaternion A quaternion
    /// @return             Quaternion

    Quaternion crossMultiply(const Quaternion& aQuaternion) const;

    /// @brief              Multiply quaternion using dot multiplication
    ///
    /// @code
    ///                     Quaternion q_1 = ...
    ///                     Quaternion q_2 = ...
    ///                     Quaternion q_3 = q_1.dotMultiply(q_2)
    /// @endcode
    ///
    /// @param              [in] aQuaternion A quaternion
    /// @return             Quaternion

    Quaternion dotMultiply(const Quaternion& aQuaternion) const;

    /// @brief              Calculate quaternion dot product
    ///
    /// @code
    ///                     Quaternion q_1 = ...
    ///                     Quaternion q_2 = ...
    ///                     Real q_3 = q_1.dotProduct(q_2)
    /// @endcode
    ///
    /// @param              [in] aQuaternion A quaternion
    /// @return             Quaternion

    Real dotProduct(const Quaternion& aQuaternion) const;

    /// @brief              Rotate vector using quaternion
    ///
    /// @code
    ///                     Quaternion q = ...
    ///                     Vector3d v_1 = ...
    ///                     Vector3d v_2 = q.rotateVector(v_1)
    /// @endcode
    ///
    /// @param              [in] aQuaternion A quaternion
    /// @return             Vector

    Vector3d rotateVector(const Vector3d& aVector) const;

    /// @brief              Convert quaternion to its vector representation
    ///
    /// @code
    ///                     Quaternion::XYSZ(0.0, 0.0, 0.0, 1.0).toVector() ; // [0.0, 0.0, 0.0, 1.0]
    /// @endcode
    ///
    /// @param              [in] (optional) aFormat A quaternion format
    /// @return             Vector representation

    Vector4d toVector(const Quaternion::Format& aFormat = Quaternion::Format::XYZS) const;

    /// @brief              Convert quaternion to its string representation
    ///
    /// @code
    ///                     Quaternion::XYSZ(0.0, 0.0, 0.0, 1.0).toString() ; // "[0.0, 0.0, 0.0, 1.0]"
    /// @endcode
    ///
    /// @param              [in] (optional) aPrecision A quaternion precision
    /// @param              [in] (optional) aFormat A quaternion format
    /// @return             String representation

    String toString(const Quaternion::Format& aFormat) const;

    String toString(
        const Integer& aPrecision = Integer::Undefined(), const Quaternion::Format& aFormat = Quaternion::Format::XYZS
    ) const;

    /// @brief              Normalize quaternion
    ///
    /// @code
    ///                     Quaternion quaternion = Quaternion::XYZS(0.0, 0.0, 0.0, 1.000000000000001) ; // [0.0, 0.0,
    ///                     0.0, 1.000000000000001] quaternion.normalize() ; // [0.0, 0.0, 0.0, 1.0]
    /// @endcode
    ///
    /// @return             Reference to quaternion

    Quaternion& normalize();

    /// @brief              Conjugate quaternion
    ///
    /// @code
    ///                     Quaternion quaternion = Quaternion::XYZS(0.0, 0.0, 0.70710678118, 0.70710678118) ; // [0.0,
    ///                     0.0, 0.70710678118, 0.70710678118] quaternion.conjugate() ; // [0.0, 0.0, -0.70710678118,
    ///                     0.70710678118]
    /// @endcode
    ///
    /// @return             Reference to quaternion

    Quaternion& conjugate();

    /// @brief              Inverse quaternion
    ///
    /// @code
    ///                     Quaternion quaternion = Quaternion::XYZS(0.0, 0.0, 0.70710678118, 0.70710678118) ; // [0.0,
    ///                     0.0, 0.70710678118, 0.70710678118] quaternion.inverse() ; // [0.0, 0.0, -0.70710678118,
    ///                     0.70710678118]
    /// @endcode
    ///
    /// @return             Reference to quaternion

    Quaternion& inverse();

    /// @brief              Rectify quaternion (enforce positive scalar part)
    ///
    /// @code
    ///                     Quaternion quaternion = Quaternion::XYZS(0.0, 0.0, -0.70710678118, -0.70710678118) ; //
    ///                     [0.0, 0.0, -0.70710678118, -0.70710678118] quaternion.rectify() ; // [0.0, 0.0,
    ///                     0.70710678118, 0.70710678118]
    /// @endcode
    ///
    /// @return             Reference to quaternion

    Quaternion& rectify();

    /// @brief              Get angular difference with quaternion
    ///
    /// @code
    ///                     Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).angularDifferenceWith(Quaternion::XYZS(0.0, 0.0,
    ///                     0.0, 1.0)) ; // 0.0 [rad]
    /// @endcode
    ///
    /// @param              [in] aQuaternion A quaternion
    /// @return             Angular difference

    Angle angularDifferenceWith(const Quaternion& aQuaternion) const;

    /// @brief              Constructs an undefined quaternion
    ///
    /// @code
    ///                     Quaternion quaternion = Quaternion::Undefined() ; // Undefined
    /// @endcode
    ///
    /// @return             Undefined quaternion

    static Quaternion Undefined();

    /// @brief              Constructs a unit quaternion
    ///
    /// @code
    ///                     Quaternion quaternion = Quaternion::Unit() ; // [0.0, 0.0, 0.0, 1.0]
    /// @endcode
    ///
    /// @return             Unit quaternion

    static Quaternion Unit();

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

    static Quaternion XYZS(
        const Real& aFirstComponent,
        const Real& aSecondComponent,
        const Real& aThirdComponent,
        const Real& aFourthComponent
    );

    /// @brief              Constructs a quaternion from a rotation vector
    ///
    /// @code
    ///                     Quaternion quaternion = Quaternion::RotationVector(RotationVector(Vector3d(0.0, 0.0, 1.0),
    ///                     Angle::Degrees(0.0))) ; // [0.0, 0.0, 0.0, 1.0]
    /// @endcode
    ///
    /// @param              [in] aRotationVector A rotation vector
    /// @return             Quaternion

    static Quaternion RotationVector(const rot::RotationVector& aRotationVector);

    /// @brief              Constructs a rquaternion from a rotation matrix
    ///
    /// @code
    ///                     Quaternion quaternion = Quaternion::RotationMatrix(RotationMatrix::Unit()) ;
    /// @endcode
    ///
    /// @param              [in] aRotationMatrix A rotation matrix
    /// @return             Quaternion

    static Quaternion RotationMatrix(const rot::RotationMatrix& aRotationMatrix);

    /// @brief              Constructs a quaternion from a string
    ///
    /// @code
    ///                     Quaternion quaternion = Quaternion::Parse("[0.0, 0.0, 0.0, 1.0]") ; // [0.0, 0.0, 0.0, 1.0]
    /// @endcode
    ///
    /// @param              [in] aString A string
    /// @param              [in] (optional) aFormat A quaternion format
    /// @return             Quaternion

    static Quaternion Parse(const String& aString, const Quaternion::Format& aFormat = Quaternion::Format::XYZS);

    /// @brief              Constructs a quaternion describing the shortest rotation between two vectors
    ///
    /// @code
    ///                     Vector3d v_1 = ...
    ///                     Vector3d v_2 = ...
    ///                     Quaternion q = Quaternion.ShortestRotation(v_1, v_2)
    /// @endcode
    ///
    /// @param              [in] aFirstVector A first vector
    /// @param              [in] aSecondVector A second vector
    /// @return             Quaternion

    static Quaternion ShortestRotation(const Vector3d& aFirstVector, const Vector3d& aSecondVector);

    /// @brief              Linear interpolator method
    ///
    /// @code
    ///                     Quaternion q_1 = ...
    ///                     Quaternion q_2 = ...
    ///                     Quaternion q = Quaternion.LERP(q_1, q_2, 0.5)
    /// @endcode
    ///
    /// @param              [in] aFirstQuaternion A first quaternion
    /// @param              [in] aSecondQuaternion A second quaternion
    /// @param              [in] aRatio An interpolator ratio
    /// @return             Quaternion

    static Quaternion LERP(const Quaternion& aFirstQuaternion, const Quaternion& aSecondQuaternion, const Real& aRatio);

    /// @brief              Normalized linear interpolator method
    ///
    /// @code
    ///                     Quaternion q_1 = ...
    ///                     Quaternion q_2 = ...
    ///                     Quaternion q = Quaternion.NLERP(q_1, q_2, 0.5)
    /// @endcode
    ///
    /// @param              [in] aFirstQuaternion A first quaternion
    /// @param              [in] aSecondQuaternion A second quaternion
    /// @param              [in] aRatio An interpolator ratio
    /// @return             Quaternion

    static Quaternion NLERP(
        const Quaternion& aFirstQuaternion, const Quaternion& aSecondQuaternion, const Real& aRatio
    );

    ///                     Spherical linear interpolator method
    ///
    /// @ref                https://en.wikipedia.org/wiki/Slerp
    ///
    /// @code
    ///                     Quaternion q_1 = ...
    ///                     Quaternion q_2 = ...
    ///                     Quaternion q = Quaternion.SLERP(q_1, q_2, 0.5)
    /// @endcode
    ///
    /// @param              [in] aFirstQuaternion A first quaternion
    /// @param              [in] aSecondQuaternion A second quaternion
    /// @param              [in] aRatio An interpolator ratio
    /// @return             Quaternion

    static Quaternion SLERP(
        const Quaternion& aFirstQuaternion, const Quaternion& aSecondQuaternion, const Real& aRatio
    );

   private:
    Real x_;
    Real y_;
    Real z_;
    Real s_;
};

}  // namespace rot
}  // namespace trf
}  // namespace d3
}  // namespace geom
}  // namespace math
}  // namespace ostk

#endif
