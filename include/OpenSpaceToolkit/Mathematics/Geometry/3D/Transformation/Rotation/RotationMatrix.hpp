/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix__
#define __OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix__

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

using ostk::core::type::Index;
using ostk::core::type::Real;
using ostk::core::type::String;
using ostk::mathematics::geometry::Angle;
using ostk::mathematics::object::Matrix3d;

class Quaternion;
class RotationVector;
class EulerAngle;

/// @brief                      Rotation matrix
///
/// @ref                        https://en.wikipedia.org/wiki/Rotation_matrix

class RotationMatrix
{
   public:
    /// @brief                  Constructor
    ///
    /// @param                  [in] aMatrix A matrix

    RotationMatrix(const Matrix3d& aMatrix);

    /// @brief                  Constructor
    ///
    /// @param                  [in] aFirstCoefficient A first coefficient
    /// @param                  [in] aSecondCoefficient A second coefficient
    /// @param                  [in] aThirdCoefficient A third coefficient
    /// @param                  [in] aFourthCoefficient A fourth coefficient
    /// @param                  [in] aFifthCoefficient A fifth coefficient
    /// @param                  [in] aSixthCoefficient A sixth coefficient
    /// @param                  [in] aSeventhCoefficient A seventh coefficient
    /// @param                  [in] aEighthCoefficient A eighth coefficient
    /// @param                  [in] aNinthCoefficient A ninth coefficient

    RotationMatrix(
        const Real& aFirstCoefficient,
        const Real& aSecondCoefficient,
        const Real& aThirdCoefficient,
        const Real& aFourthCoefficient,
        const Real& aFifthCoefficient,
        const Real& aSixthCoefficient,
        const Real& aSeventhCoefficient,
        const Real& aEighthCoefficient,
        const Real& aNinthCoefficient
    );

    /// @brief                  Equal to operator
    ///
    /// @code
    ///                         RotationMatrix(...) == RotationMatrix(...);
    /// @endcode
    ///
    /// @param                  [in] aRotationMatrix A Rotation Matrix
    /// @return                 True if rotation matrices are equal

    bool operator==(const RotationMatrix& aRotationMatrix) const;

    /// @brief                  Not equal to operator
    ///
    /// @code
    ///                         RotationMatrix(...) != RotationMatrix(...);
    /// @endcode
    ///
    /// @param                  [in] aRotationMatrix A Rotation Matrix
    /// @return                 True if rotation matrices are not equal

    bool operator!=(const RotationMatrix& aRotationMatrix) const;

    /// @brief                  Matrix multiplication operator
    ///
    /// @code
    ///                         RotationMatrix rotationMatrix_A_B = ... ;
    ///                         RotationMatrix rotationMatrix_B_C = ... ;
    ///                         RotationMatrix rotationMatrix_A_C = rotationMatrix_A_B * rotationMatrix_B_C ;
    /// @endcode
    ///
    /// @param                  [in] aRotationMatrix A Rotation Matrix
    /// @return                 Rotation matrix

    RotationMatrix operator*(const RotationMatrix& aRotationMatrix) const;

    /// @brief                  Vector multiplication operator
    ///
    /// @code
    ///                         RotationMatrix rotationMatrix_B_A = ... ;
    ///                         Vector3d vector_A = ... ;
    ///                         Vector3d vector_B = rotationMatrix_B_A * vector_A ;
    /// @endcode
    ///
    /// @param                  [in] aVector A vector
    /// @return                 Vector

    Vector3d operator*(const Vector3d& aVector) const;

    /// @brief                  Index function operator
    ///
    /// @code
    ///                         RotationMatrix::Unit();
    ///                         double value_00 = rotationMatrix(0, 0); // 1.0
    /// @endcode
    ///
    /// @param                  [in] aRowIndex A row index
    /// @param                  [in] aColumnIndex A column index
    /// @return                 Value at index

    double operator()(const Index& aRowIndex, const Index& aColumnIndex) const;

    /// @brief                  Index function operator
    ///
    /// @code
    ///                         RotationMatrix::Unit();
    ///                         rotationMatrix(0, 0) = 0.0 ;
    /// @endcode
    ///
    /// @param                  [in] aRowIndex A row index
    /// @param                  [in] aColumnIndex A column index
    /// @return                 Reference of value at index

    double& operator()(const Index& aRowIndex, const Index& aColumnIndex);

    /// @brief                  Output stream operator
    ///
    /// @code
    ///                         std::cout << RotationMatrix(...);
    /// @endcode
    ///
    /// @param                  [in] anOutputStream An output stream
    /// @param                  [in] aRotationMatrix A Rotation Matrix
    /// @return                 Output stream reference

    friend std::ostream& operator<<(std::ostream& anOutputStream, const RotationMatrix& aRotationMatrix);

    /// @brief                  Check if Rotation Matrix is defined
    ///
    /// @code
    ///                         RotationMatrix(Vector3d(0.0, 0.0, 1.0), Angle::Degrees(90.0)).isDefined();
    /// @endcode
    ///
    /// @return                 True if Rotation Matrix is defined

    bool isDefined() const;

    /// @brief                  Access underlying 3D Matrix
    ///
    /// @return                 Matrix reference

    const Matrix3d& accessMatrix() const;

    /// @brief                  Get row at index
    ///
    /// @param                  [in] aRowIndex Index of row
    /// @return                 Vector

    Vector3d getRowAt(const Index& aRowIndex) const;

    /// @brief                  Get column at index
    ///
    /// @param                  [in] aColumnIndex Index of column
    /// @return                 Vector

    Vector3d getColumnAt(const Index& aColumnIndex) const;

    /// @brief                  Get underlying 3D Matrix
    ///
    /// @return                 Matrix

    Matrix3d getMatrix() const;

    /// @brief                  Calculate transposed Rotation Matrix
    ///
    /// @code
    ///                         RotationMatrix(...).toTransposed();
    /// @endcode
    ///
    /// @return                 Rotation Matrix

    RotationMatrix toTransposed() const;

    /// @brief                  Transpose Rotation Matrix
    ///
    /// @code
    ///                         RotationMatrix(...).transpose();
    /// @endcode
    ///
    /// @return                 Rotation Matrix reference

    RotationMatrix& transpose();

    /// @brief                  Construct an undefined Rotation Matrix
    ///
    /// @code
    ///                         RotationMatrix::Undefined();
    /// @endcode
    ///
    /// @return                 Rotation Matrix

    static RotationMatrix Undefined();

    /// @brief                  Construct unitary Rotation Matrix
    ///
    /// @code
    ///                         RotationMatrix::Unit();
    /// @endcode
    ///
    /// @return                 Rotation Matrix

    static RotationMatrix Unit();

    /// @brief                  Construct Rotation Matrix representing a rotation around the X-axis
    ///
    /// @code
    ///                         RotationMatrix::RX(Angle::Degrees(30.0));
    /// @endcode
    ///
    /// @param                  [in] aRotationAngle A rotation angle
    /// @return                 Rotation matrix

    static RotationMatrix RX(const Angle& aRotationAngle);

    /// @brief                  Construct Rotation Matrix representing a rotation around the Y-axis
    ///
    /// @code
    ///                         RotationMatrix::RY(Angle::Degrees(30.0));
    /// @endcode
    ///
    /// @param                  [in] aRotationAngle A rotation angle
    /// @return                 Rotation matrix

    static RotationMatrix RY(const Angle& aRotationAngle);

    /// @brief                  Construct Rotation Matrix representing a rotation around the Z-axis
    ///
    /// @code
    ///                         RotationMatrix::RZ(Angle::Degrees(30.0));
    /// @endcode
    ///
    /// @param                  [in] aRotationAngle A rotation angle
    /// @return                 Rotation matrix

    static RotationMatrix RZ(const Angle& aRotationAngle);

    /// @brief                  Construct Rotation Matrix from row vectors
    ///
    /// @code
    ///                         RotationMatrix::Rows({1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0});
    /// @endcode
    ///
    /// @param                  [in] aFirstRow A first row
    /// @param                  [in] aSecondRow A second row
    /// @param                  [in] aThirdRow A third row
    /// @return                 Rotation matrix

    static RotationMatrix Rows(const Vector3d& aFirstRow, const Vector3d& aSecondRow, const Vector3d& aThirdRow);

    /// @brief                  Construct Rotation Matrix from column vectors
    ///
    /// @code
    ///                         RotationMatrix::Columns({1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0});
    /// @endcode
    ///
    /// @param                  [in] aFirstColumn A first column
    /// @param                  [in] aSecondColumn A second column
    /// @param                  [in] aThirdColumn A third column
    /// @return                 Rotation matrix

    static RotationMatrix Columns(
        const Vector3d& aFirstColumn, const Vector3d& aSecondColumn, const Vector3d& aThirdColumn
    );

    /// @brief                  Construct Rotation Matrix from Quaternion
    ///
    /// @code
    ///                         RotationMatrix::Quaternion(Quaternion::Unit());
    /// @endcode
    ///
    /// @param                  [in] aQuaternion A Quaternion
    /// @return                 Rotation matrix

    static RotationMatrix Quaternion(const rotation::Quaternion& aQuaternion);

    /// @brief                  Construct Rotation Matrix from Rotation Vector
    ///
    /// @code
    ///                         RotationMatrix::RotationVector(RotationVector::Unit());
    /// @endcode
    ///
    /// @param                  [in] aRotationVector A Rotation Vector
    /// @return                 Rotation matrix

    static RotationMatrix RotationVector(const rotation::RotationVector& aRotationVector);

    /// @brief                  Construct Rotation Matrix from Euler Angle
    ///
    /// @code
    ///                         RotationMatrix::EulerAngle(EulerAngle::Unit());
    /// @endcode
    ///
    /// @param                  [in] aEulerAngle A Euler Angle
    /// @return                 Rotation matrix

    static RotationMatrix EulerAngle(const rotation::EulerAngle& aEulerAngle);

    /// @brief                  Construct Rotation Matrix from two pairs of vectors. The first pair is the source
    /// vectors, the second pair is the destination vectors. Basis vectors are constructed from the source vectors by
    /// taking the cross product of the first and second vectors and normalizing the result.
    ///
    /// @code
    ///                         RotationMatrix::VectorBasis({1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
    ///                         {0.0, 1.0, 0.0});
    /// @endcode
    ///
    /// @param                  [in] aFirstSourceVector A first source vector
    /// @param                  [in] aSecondSourceVector A second source vector
    /// @param                  [in] aFirstDestinationVector A first destination vector
    /// @param                  [in] aSecondDestinationVector A second destination vector

    static RotationMatrix VectorBasis(
        const Vector3d& aFirstSourceVector,
        const Vector3d& aSecondSourceVector,
        const Vector3d& aFirstDestinationVector,
        const Vector3d& aSecondDestinationVector
    );

   private:
    Matrix3d matrix_;

    RotationMatrix();
};

}  // namespace rotation
}  // namespace transformation
}  // namespace d3
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
