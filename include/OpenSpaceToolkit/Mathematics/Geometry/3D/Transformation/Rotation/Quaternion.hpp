/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion__
#define __OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion__

#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/Angle.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

namespace ostk
{
namespace mathematics
{
namespace geometry
{
namespace d3
{
namespace transformation
{
namespace rotation
{

using ostk::core::type::Integer;
using ostk::core::type::Real;
using ostk::core::type::String;

using ostk::mathematics::geometry::Angle;
using ostk::mathematics::object::Vector3d;
using ostk::mathematics::object::Vector4d;

class RotationVector;
class RotationMatrix;
class EulerAngle;

/// @brief                      Quaternion
///
///                             Provide a convenient mathematical notation for representing orientations and rotation
///                             of object in three dimensions. Compared to Euler angles they are simpler to compose and
///                             avoid the problem of gimbal lock. Compared to rotation matrices they are more compact,
///                             more numerically stable, and more efficient.
///
/// @ref                        https://en.wikipedia.org/wiki/Quaternion
/// @ref                        https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation

class Quaternion
{
   public:
    /// @brief                  Quaternion format

    enum class Format
    {

        XYZS,  ///< Vector-scalar format
        SXYZ   ///< Scalar-vector format

    };

    /// @brief                  Constructor
    ///
    /// @code
    ///                         Quaternion(0.0, 0.0, 0.0, 0.1, Quaternion::Format::XYZS) ;
    /// @endcode
    ///
    /// @param                  [in] aFirstComponent A first component
    /// @param                  [in] aSecondComponent A second component
    /// @param                  [in] aThirdComponent A third component
    /// @param                  [in] aFourthComponent A fourth component
    /// @param                  [in] aFormat A Quaternion format

    Quaternion(
        const Real& aFirstComponent,
        const Real& aSecondComponent,
        const Real& aThirdComponent,
        const Real& aFourthComponent,
        const Quaternion::Format& aFormat
    );

    /// @brief                  Constructor
    ///
    /// @code
    ///                         Quaternion({0.0, 0.0, 0.0, 0.1}, Quaternion::Format::XYZS) ;
    /// @endcode
    ///
    /// @param                  [in] aVector A 4D vector
    /// @param                  [in] aFormat A Quaternion format

    Quaternion(const Vector4d& aVector, const Quaternion::Format& aFormat);

    /// @brief                  Constructor
    ///
    /// @code
    ///                         Quaternion({0.0, 0.0, 0.0}, 1.0);
    /// @endcode
    ///
    /// @param                  [in] aVectorPart A vector part
    /// @param                  [in] aVectorPart A scalar part

    Quaternion(const Vector3d& aVectorPart, const Real& aScalarPart);

    /// @brief                  Equal to operator
    ///
    /// @code
    ///                         Quaternion::Unit() == Quaternion::Unit()
    /// @endcode
    ///
    /// @param                  [in] aQuaternion A Quaternion
    /// @return                 True if Quaternions are equal

    bool operator==(const Quaternion& aQuaternion) const;

    /// @brief                  Not equal to operator
    ///
    /// @code
    ///                         Quaternion::Unit() != Quaternion::Unit();
    /// @endcode
    ///
    /// @param                  [in] aQuaternion A Quaternion
    /// @return                 True if Quaternions are not equal

    bool operator!=(const Quaternion& aQuaternion) const;

    /// @brief                  Addition operator
    ///
    /// @code
    ///                         Quaternion q_1 = ... ;
    ///                         Quaternion q_2 = ... ;
    ///                         Quaternion q_3 = q_1 + q_2 ;
    /// @endcode
    ///
    /// @param                  [in] aQuaternion A Quaternion
    /// @return                 Quaternion

    Quaternion operator+(const Quaternion& aQuaternion) const;

    /// @brief                  Multiplication operator (Quaternion)
    ///
    /// @code
    ///                         Quaternion q_B_A = ... ;
    ///                         Quaternion q_C_B = ... ;
    ///                         Quaternion q_C_A = q_C_B * q_B_A ;
    /// @endcode
    ///
    /// @note                   This operator uses cross multiplication
    ///
    /// @param                  [in] aQuaternion A Quaternion
    /// @return                 Quaternion

    Quaternion operator*(const Quaternion& aQuaternion) const;

    /// @brief                  Multiplication operator (vector)
    ///
    /// @code
    ///                         Quaternion q_B_A = ... ;
    ///                         Vector3d v_A = ... ;
    ///                         Vector3d v_B = q_B_A * v_A ;
    /// @endcode
    ///
    /// @note                   This operator uses transformVector
    ///
    /// @param                  [in] aVector A vector
    /// @return                 Vector

    Vector3d operator*(const Vector3d& aVector) const;

    /// @brief                  Multiplication operator (scalar)
    ///
    /// @code
    ///                         Quaternion q_1 = ... ;
    ///                         Real scalar = ... ;
    ///                         Quaternion q_2 = q_1 * scalar ;
    /// @endcode
    ///
    /// @param                  [in] aScalar A scalar
    /// @return                 Quaternion

    Quaternion operator*(const Real& aScalar) const;

    /// @brief                  Multiplication operator (scalar)
    ///
    /// @code
    ///                         Real scalar = ... ;
    ///                         Quaternion q_1 = ... ;
    ///                         Quaternion q_2 = scalar * q_1 ;
    /// @endcode
    ///
    /// @param                  [in] aScalar A scalar
    /// @param                  [in] aQuaternion A Quaternion
    /// @return                 Quaternion

    friend Quaternion operator*(const Real& aScalar, const Quaternion& aQuaternion);

    /// @brief                  Division operator (Quaternion)
    ///
    /// @code
    ///                         Quaternion q_A_B = ... ;
    ///                         Quaternion q_C_B = ... ;
    ///                         Quaternion q_C_A = q_C_B / q_A_B ;
    /// @endcode
    ///
    /// @note                   This is equivalent to multiplying with the inverse
    ///
    /// @param                  [in] aQuaternion A Quaternion
    /// @return                 Quaternion

    Quaternion operator/(const Quaternion& aQuaternion) const;

    /// @brief                  Power operator (Quaternion)
    ///
    /// @code
    ///                         Quaternion q_1 = ... ;
    ///                         Real scalar = ... ;
    ///                         Quaternion q_2 = q_1 ^ scalar ;
    /// @endcode
    ///
    /// @param                  [in] aScalar A scalar
    /// @return                 Quaternion

    Quaternion operator^(const Real& aScalar) const;

    /// @brief                  Addition assignment operator (Quaternion)
    ///
    /// @param                  [in] aQuaternion A Quaternion
    /// @return                 Quaternion reference

    Quaternion& operator+=(const Quaternion& aQuaternion);

    /// @brief                  Multiplication assignment operator (Quaternion)
    ///
    /// @note                   This operator uses cross multiplication
    ///
    /// @param                  [in] aQuaternion A Quaternion
    /// @return                 Quaternion reference

    Quaternion& operator*=(const Quaternion& aQuaternion);

    /// @brief                  Division assignment operator (Quaternion)
    ///
    /// @note                   This is equivalent to multiplying with the inverse
    ///
    /// @param                  [in] aQuaternion A Quaternion
    /// @return                 Quaternion reference

    Quaternion& operator/=(const Quaternion& aQuaternion);

    /// @brief                  Output stream operator
    ///
    /// @code
    ///                         std::cout << Quaternion::XYZS(0.0, 0.0, 0.0, 1.0);
    /// @endcode
    ///
    /// @param                  [in] anOutputStream An output stream
    /// @param                  [in] aQuaternion A Quaternion
    /// @return                 Output stream reference

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Quaternion& aQuaternion);

    /// @brief                  Check if Quaternion is defined
    ///
    /// @code
    ///                         Quaternion::Unit().isDefined();
    /// @endcode
    ///
    /// @return                 True if Quaternion is defined

    bool isDefined() const;

    /// @brief                  Check if Quaternion is unitary (i.e., its norm is equal to 1.0)
    ///
    /// @code
    ///                         Quaternion::Unit().isUnitary();
    /// @endcode
    ///
    /// @return                 True if Quaternion is unitary

    bool isUnitary(const Real& aNormTolerance = Real::Epsilon()) const;

    /// @brief                  Check if Quaternion is near another Quaternion
    ///
    /// @code
    ///                         Quaternion::Unit().isNear(
    ///                             Quaternion::XYZS(0.0, 0.0, 0.0, 1.0 + 1e-19),
    ///                             Angle::Radians(1e-6)
    ///                         );
    /// @endcode
    ///
    /// @param                  [in] aQuaternion A Quaternion
    /// @param                  [in] anAngularTolerance An angular tolerance
    /// @return                 True if Quaternions are near each other

    bool isNear(const Quaternion& aQuaternion, const Angle& anAngularTolerance) const;

    /// @brief                  Get first component of vector part
    ///
    /// @code
    ///                         Quaternion::Unit().x();
    /// @endcode
    ///
    /// @return                 Real

    Real x() const;

    /// @brief                  Get second component of vector part
    ///
    /// @code
    ///                         Quaternion::Unit().y();
    /// @endcode
    ///
    /// @return                 Real

    Real y() const;

    /// @brief                  Get third component of vector part
    ///
    /// @code
    ///                         Quaternion::Unit().z();
    /// @endcode
    ///
    /// @return                 Real

    Real z() const;

    /// @bref                   Get scalar part
    ///
    /// @code
    ///                         Quaternion::XYSZ(0.0, 0.0, 0.0, 1.0).s();
    /// @endcode
    ///
    /// @return                 Real

    Real s() const;

    /// @brief                  Get vector part
    ///
    /// @code
    ///                         Quaternion::Unit().getVectorPart();
    /// @endcode
    ///
    /// @return                 Vector

    Vector3d getVectorPart() const;

    /// @brief                  Get scalar part
    ///
    /// @code
    ///                         Quaternion::Unit().getScalarPart();
    /// @endcode
    ///
    /// @return                 Real

    Real getScalarPart() const;

    /// @brief                  Calculate normalized Quaternion
    ///
    /// @code
    ///                         Quaternion::XYZS(0.0, 0.0, 0.0, 1.000000000000001).toNormalized();
    /// @endcode
    ///
    /// @return                 Quaternion

    Quaternion toNormalized() const;

    /// @brief                  Calculate conjugate of Quaternion
    ///
    /// @code
    ///                         Quaternion::XYZS(0.0, 0.0, 0.70710678118, 0.70710678118).toConjugate();
    /// @endcode
    ///
    /// @return                 Quaternion

    Quaternion toConjugate() const;

    /// @brief                  Calculate inverse of Quaternion
    ///
    /// @code
    ///                         Quaternion::XYZS(0.0, 0.0, 0.70710678118, 0.70710678118).toInverse();
    /// @endcode
    ///
    /// @return                 Quaternion

    Quaternion toInverse() const;

    /// @brief                  Calculate rectified Quaternion (with positive scalar part)
    ///
    /// @code
    ///                         Quaternion::XYZS(0.0, 0.0, -0.70710678118, -0.70710678118).toRectify();
    /// @endcode
    ///
    /// @return                 Quaternion

    Quaternion toRectify() const;

    /// @brief                  Calculate exponential of Quaternion
    ///
    /// @code
    ///                         Quaternion q_1 = ...
    ///                         Quaternion q_2 = q_1.exp();
    /// @endcode
    ///
    /// @return                 Quaternion

    Quaternion exp() const;

    /// @brief                  Calculate logarithm of Quaternion
    ///
    /// @code
    ///                         Quaternion q_1 = ...
    ///                         Quaternion q_2 = q_1.log();
    /// @endcode
    ///
    /// @return                 Quaternion

    Quaternion log() const;

    /// @brief                  Calculate power of Quaternion
    ///
    /// @code
    ///                         Quaternion q_1 = ...
    ///                         Real scalar = ...
    ///                         Quaternion q_2 = q_1 ^ scalar ;
    /// @endcode
    ///
    /// @param                  [in] aValue A power value
    /// @return                 Quaternion

    Quaternion pow(const Real& aValue) const;

    /// @brief                  Calculate norm of Quaternion
    ///
    /// @code
    ///                         Quaternion::XYZS(0.0, 0.0, -0.70710678118, 0.70710678118).norm();
    /// @endcode
    ///
    /// @return                 Quaternion norm

    Real norm() const;

    /// @brief                  Multiply Quaternion using cross multiplication
    ///
    /// @details                Multiply quaternions using the Shuster/JPL convention, such that
    ///                         q_1.crossMultiply(q_2) == q_2.dotMultiply(q_1)
    ///
    /// @ref                    https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation#Alternative_conventions
    /// @ref                    Markley F. L. — Fundamentals of Spacecraft Attitude Determination and Control, p.37
    ///
    /// @code
    ///                         Quaternion q_1 = ...
    ///                         Quaternion q_2 = ...
    ///                         Quaternion q_3 = q_1.crossMultiply(q_2)
    /// @endcode
    ///
    /// @param                  [in] aQuaternion A Quaternion
    /// @return                 Quaternion

    Quaternion crossMultiply(const Quaternion& aQuaternion) const;

    /// @brief                  Multiply Quaternion using dot multiplication
    ///
    /// @details                Multiply quaternions using the Hamiltonian convention
    ///
    /// @ref                    https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation
    /// @ref                    Markley F. L. — Fundamentals of Spacecraft Attitude Determination and Control, p.37
    ///
    /// @code
    ///                         Quaternion q_1 = ...
    ///                         Quaternion q_2 = ...
    ///                         Quaternion q_3 = q_1.dotMultiply(q_2)
    /// @endcode
    ///
    /// @param                  [in] aQuaternion A Quaternion
    /// @return                 Quaternion

    Quaternion dotMultiply(const Quaternion& aQuaternion) const;

    /// @brief                  Calculate Quaternion dot product
    ///
    /// @code
    ///                         Quaternion q_1 = ...
    ///                         Quaternion q_2 = ...
    ///                         Real q_3 = q_1.dotProduct(q_2)
    /// @endcode
    ///
    /// @param                  [in] aQuaternion A Quaternion
    /// @return                 Quaternion

    Real dotProduct(const Quaternion& aQuaternion) const;

    /// @brief                  Rotate vector using Quaternion
    ///
    /// @code
    ///                         Vector3d v_1 = ...
    ///                         Vector3d v_2 = q.rotateVector(v_1);
    /// @endcode
    ///
    /// @param                  [in] aQuaternion A Quaternion
    /// @return                 Vector

    Vector3d rotateVector(const Vector3d& aVector, const Real& aNormTolerance = Real::Epsilon()) const;

    /// @brief                  Convert Quaternion to its vector representation
    ///
    /// @code
    ///                         Quaternion::XYSZ(0.0, 0.0, 0.0, 1.0).toVector();
    /// @endcode
    ///
    /// @param                  [in] (optional) aFormat A Quaternion format
    /// @return                 Vector representation

    Vector4d toVector(const Quaternion::Format& aFormat = Quaternion::Format::XYZS) const;

    /// @brief                  Convert Quaternion to its string representation
    ///
    /// @code
    ///                         Quaternion::XYSZ(0.0, 0.0, 0.0, 1.0).toString();
    /// @endcode
    ///
    /// @param                  [in] (optional) aPrecision A Quaternion precision
    /// @param                  [in] (optional) aFormat A Quaternion format
    /// @return                 String representation

    String toString(const Quaternion::Format& aFormat) const;

    String toString(
        const Integer& aPrecision = Integer::Undefined(), const Quaternion::Format& aFormat = Quaternion::Format::XYZS
    ) const;

    /// @brief                  Normalize Quaternion
    ///
    /// @code
    ///                         Quaternion::XYZS(0.0, 0.0, 0.0, 1.000000000000001).normalize();
    /// @endcode
    ///
    /// @return                 Quaternion reference

    Quaternion& normalize();

    /// @brief                  Conjugate Quaternion
    ///
    /// @code
    ///                         Quaternion::XYZS(0.0, 0.0, 0.70710678118, 0.70710678118).conjugate();
    /// @endcode
    ///
    /// @return                 Quaternion reference

    Quaternion& conjugate();

    /// @brief                  Inverse Quaternion
    ///
    /// @code
    ///                         Quaternion::XYZS(0.0, 0.0, 0.70710678118, 0.70710678118).inverse();
    /// @endcode
    ///
    /// @return                 Quaternion reference

    Quaternion& inverse();

    /// @brief                  Rectify Quaternion (enforce positive scalar part)
    ///
    /// @code
    ///                         Quaternion::XYZS(0.0, 0.0, -0.70710678118, -0.70710678118).rectify();
    /// @endcode
    ///
    /// @return                 Quaternion reference

    Quaternion& rectify();

    /// @brief                  Compute angular difference with Quaternion
    ///
    /// @code
    ///                         Quaternion::Unit().angularDifferenceWith(Quaternion::Unit());
    /// @endcode
    ///
    /// @param                  [in] aQuaternion A Quaternion
    /// @return                 Angular difference

    Angle angularDifferenceWith(const Quaternion& aQuaternion) const;

    /// @brief                  Construct undefined Quaternion
    ///
    /// @code
    ///                         Quaternion::Undefined();
    /// @endcode
    ///
    /// @return                 Quaternion

    static Quaternion Undefined();

    /// @brief                  Construct unitary Quaternion
    ///
    /// @code
    ///                         Quaternion::Unit();
    /// @endcode
    ///
    /// @return                 Quaternion

    static Quaternion Unit();

    /// @brief                  Construct Quaternion using the vector-scalar format
    ///
    /// @code
    ///                         Quaternion::XYZS(0.0, 0.0, 0.0, 1.0);
    /// @endcode
    ///
    /// @param                  [in] aFirstComponent A first component
    /// @param                  [in] aSecondComponent A second component
    /// @param                  [in] aThirdComponent A third component
    /// @param                  [in] aFourthComponent A fourth component
    /// @return                 Quaternion

    static Quaternion XYZS(
        const Real& aFirstComponent,
        const Real& aSecondComponent,
        const Real& aThirdComponent,
        const Real& aFourthComponent
    );

    /// @brief                  Construct Quaternion from rotation vector
    ///
    /// @code
    ///                         Quaternion::RotationVector(RotationVector::Unit());
    /// @endcode
    ///
    /// @param                  [in] aRotationVector A Rotation Vector
    /// @return                 Quaternion

    static Quaternion RotationVector(const rotation::RotationVector& aRotationVector);

    /// @brief                  Construct Quaternion from Rotation Matrix
    ///
    /// @code
    ///                         Quaternion::RotationMatrix(RotationMatrix::Unit());
    /// @endcode
    ///
    /// @param                  [in] aRotationMatrix A Rotation Matrix
    /// @return                 Quaternion

    static Quaternion RotationMatrix(const rotation::RotationMatrix& aRotationMatrix);

    /// @brief                  Construct Quaternion from Euler Angle
    ///
    /// @code
    ///                         Quaternion::EulerAngle(EulerAngle::Unit());
    /// @endcode
    ///
    /// @param                  [in] EulerAngle A Euler Angle
    /// @return                 Quaternion

    static Quaternion EulerAngle(const rotation::EulerAngle& aEulerAngle);

    /// @brief                  Construct Quaternion from string
    ///
    /// @code
    ///                         Quaternion::Parse("[0.0, 0.0, 0.0, 1.0]");
    /// @endcode
    ///
    /// @param                  [in] aString A string
    /// @param                  [in] (optional) aFormat A Quaternion format
    /// @return                 Quaternion

    static Quaternion Parse(const String& aString, const Quaternion::Format& aFormat = Quaternion::Format::XYZS);

    /// @brief                  Construct Quaternion describing the shortest rotation between two vectors
    ///
    /// @code
    ///                         Quaternion::ShortestRotation({1.0, 0.0, 0.0}, {0.0, 1.0, 0.0});
    /// @endcode
    ///
    /// @param                  [in] aFirstVector A first vector
    /// @param                  [in] aSecondVector A second vector
    /// @return                 Quaternion

    static Quaternion ShortestRotation(const Vector3d& aFirstVector, const Vector3d& aSecondVector);

    /// @brief                  Linear interpolator method
    ///
    /// @code
    ///                         Quaternion q_1 = ...
    ///                         Quaternion q_2 = ...
    ///                         Quaternion::LERP(q_1, q_2, 0.5);
    /// @endcode
    ///
    /// @param                  [in] aFirstQuaternion A first Quaternion
    /// @param                  [in] aSecondQuaternion A second Quaternion
    /// @param                  [in] aRatio An interpolator ratio
    /// @return                 Quaternion

    static Quaternion LERP(const Quaternion& aFirstQuaternion, const Quaternion& aSecondQuaternion, const Real& aRatio);

    /// @brief                  Normalized linear interpolator method
    ///
    /// @code
    ///                         Quaternion q_1 = ...
    ///                         Quaternion q_2 = ...
    ///                         Quaternion::NLERP(q_1, q_2, 0.5);
    /// @endcode
    ///
    /// @param                  [in] aFirstQuaternion A first Quaternion
    /// @param                  [in] aSecondQuaternion A second Quaternion
    /// @param                  [in] aRatio An interpolator ratio
    /// @return                 Quaternion

    static Quaternion NLERP(
        const Quaternion& aFirstQuaternion, const Quaternion& aSecondQuaternion, const Real& aRatio
    );

    ///                         Spherical linear interpolator method
    ///
    /// @ref                    https://en.wikipedia.org/wiki/Slerp
    ///
    /// @code
    ///                         Quaternion q_1 = ...
    ///                         Quaternion q_2 = ...
    ///                         Quaternion::SLERP(q_1, q_2, 0.5);
    /// @endcode
    ///
    /// @param                  [in] aFirstQuaternion A first Quaternion
    /// @param                  [in] aSecondQuaternion A second Quaternion
    /// @param                  [in] aRatio An interpolator ratio
    /// @return                 Quaternion

    static Quaternion SLERP(
        const Quaternion& aFirstQuaternion, const Quaternion& aSecondQuaternion, const Real& aRatio
    );

   private:
    Real x_;
    Real y_;
    Real z_;
    Real s_;
};

}  // namespace rotation
}  // namespace transformation
}  // namespace d3
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
