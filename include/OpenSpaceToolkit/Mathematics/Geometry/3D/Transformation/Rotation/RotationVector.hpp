/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationVector__
#define __OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationVector__

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

using ostk::core::type::Real;
using ostk::core::type::String;

using ostk::mathematics::object::Vector3d;
using ostk::mathematics::geometry::Angle;

class Quaternion;
class RotationMatrix;
class EulerAngle;

/// @brief                      Rotation Vector
///
/// @ref                        https://en.wikipedia.org/wiki/Axis–angle_representation#Rotation_vector

class RotationVector
{
   public:
    /// @brief                  Constructor
    ///
    /// @code
    ///                         RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(45.0));
    /// @endcode
    ///
    /// @param                  [in] anAxis A rotation axis
    /// @param                  [in] anAngle A rotation angle

    RotationVector(const Vector3d& anAxis, const Angle& anAngle);

    /// @brief                  Construct Rotation Vector from vector and angle unit
    ///                         The norm of the vector defines the rotation angle.
    ///
    /// @code
    ///                         RotationVector({1.0, 0.0, 0.0}, Angle::Unit::Radian);
    /// @endcode
    ///
    /// @param                  [in] aVector A vector
    /// @param                  [in] anAngleUnit An angle unit

    RotationVector(const Vector3d& anAxis, const Angle::Unit& anAngleUnit);

    /// @brief                  Equal to operator
    ///
    /// @code
    ///                         RotationVector::Unit() == RotationVector::Unit();
    /// @endcode
    ///
    /// @param                  [in] aRotationVector A Rotation Vector
    /// @return                 True if Rotation Vectors are equal

    bool operator==(const RotationVector& aRotationVector) const;

    /// @brief                  Not equal to operator
    ///
    /// @code
    ///                         RotationVector::Unit() != RotationVector::Unit();
    /// @endcode
    ///
    /// @param                  [in] aRotationVector A Rotation Vector
    /// @return                 True if Rotation Vectors are not equal

    bool operator!=(const RotationVector& aRotationVector) const;

    /// @brief                  Output stream operator
    ///
    /// @code
    ///                         std::cout << RotationVector::Unit();
    /// @endcode
    ///
    /// @param                  [in] anOutputStream An output stream
    /// @param                  [in] aRotationVector A Rotation Vector
    /// @return                 Reference to output stream

    friend std::ostream& operator<<(std::ostream& anOutputStream, const RotationVector& aRotationVector);

    /// @brief                  Check if Rotation Vector is defined
    ///
    /// @code
    ///                         RotationVector::Unit().isDefined();
    /// @endcode
    ///
    /// @return                 True if Rotation Vector is defined

    bool isDefined() const;

    /// @brief                  Get rotation axis
    ///
    /// @code
    ///                         RotationVector::Unit().getAxis();
    /// @endcode
    ///
    /// @return                 Rotation axis

    Vector3d getAxis() const;

    /// @brief                  Get rotation angle
    ///
    /// @code
    ///                         RotationVector::Unit().getAngle();
    /// @endcode
    ///
    /// @return                 Rotation angle

    Angle getAngle() const;

    /// @brief                  Convert Rotation Vector to string representation
    ///
    /// @code
    ///                         RotationVector::Unit().toString();
    /// @endcode
    ///
    /// @param                  [in] (optional) aPrecision A precision
    /// @return                 String representation

    String toString(const Integer& aPrecision = Integer::Undefined()) const;

    /// @brief                  Rectify Rotation Vector (enforce positive angle)
    ///
    /// @code
    ///                         RotationVector::Unit().rectify();
    /// @endcode
    ///
    /// @return                 Rotation Vector reference

    RotationVector& rectify();

    /// @brief                  Construct an undefined Rotation Vector
    ///
    /// @code
    ///                         RotationVector::Undefined();
    /// @endcode
    ///
    /// @return                 Undefined Rotation Vector

    static RotationVector Undefined();

    /// @brief                  Construct a unitary Rotation Vector
    ///
    /// @code
    ///                         RotationVector::Unit();
    /// @endcode
    ///
    /// @return                 Unitary Rotation Vector

    static RotationVector Unit();

    /// @brief                  Construct Rotation Vector around X-axis
    ///
    /// @code
    ///                         RotationVector::X(Angle::Degrees(45.0));
    /// @endcode
    ///
    /// @param                  [in] anAngle A rotation angle
    /// @return                 Rotation Vector

    static RotationVector X(const Angle& anAngle);

    /// @brief                  Construct Rotation Vector around Y-axis
    ///
    /// @code
    ///                         RotationVector::X(Angle::Degrees(45.0));
    /// @endcode
    ///
    /// @param                  [in] anAngle A rotation angle
    /// @return                 Rotation Vector

    static RotationVector Y(const Angle& anAngle);

    /// @brief                  Construct Rotation Vector around Z-axis
    ///
    /// @code
    ///                         RotationVector::X(Angle::Degrees(45.0));
    /// @endcode
    ///
    /// @param                  [in] anAngle A rotation angle
    /// @return                 Rotation Vector

    static RotationVector Z(const Angle& anAngle);

    /// @brief                  Construct Rotation Vector from Quaternion
    ///
    /// @code
    ///                         RotationVector::Quaternion(Quaternion::Unit());
    /// @endcode
    ///
    /// @param                  [in] aQuaternion A quaternion
    /// @return                 Rotation Vector

    static RotationVector Quaternion(const rotation::Quaternion& aQuaternion);

    /// @brief                  Construct Rotation Vector from Rotation Matrix
    ///
    /// @code
    ///                         RotationVector::RotationMatrix(RotationMatrix::Unit());
    /// @endcode
    ///
    /// @param                  [in] aRotationMatrix A Rotation Matrix
    /// @return                 Rotation Vector

    static RotationVector RotationMatrix(const rotation::RotationMatrix& aRotationMatrix);

    /// @brief                  Construct Rotation Vector from Euler Angle
    ///
    /// @code
    ///                         RotationVector::EulerAngle(EulerAngle::Unit());
    /// @endcode
    ///
    /// @param                  [in] aEulerAngle A Euler Angle
    /// @return                 Rotation Vector

    static RotationVector EulerAngle(const rotation::EulerAngle& aEulerAngle);

   private:
    Vector3d axis_;
    Angle angle_;

    RotationVector();
};

}  // namespace rotation
}  // namespace transformation
}  // namespace d3
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
