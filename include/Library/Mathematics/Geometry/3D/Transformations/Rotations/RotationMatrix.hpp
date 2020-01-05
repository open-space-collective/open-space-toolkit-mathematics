////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_3D_Transformations_Rotations_RotationMatrix__
#define __OpenSpaceToolkit_Mathematics_Geometry_3D_Transformations_Rotations_RotationMatrix__

#include <Library/Mathematics/Geometry/Angle.hpp>
#include <Library/Mathematics/Objects/Vector.hpp>
#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Real.hpp>
#include <Library/Core/Types/Integer.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::Index ;
using ostk::core::types::Real ;
using ostk::core::types::String ;
using ostk::math::obj::Matrix3d ;
using ostk::math::geom::Angle ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Quaternion ;
class RotationVector ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Rotation matrix
///
/// @ref                        https://en.wikipedia.org/wiki/Rotation_matrix

class RotationMatrix
{

    public:

        /// @brief              Constructor
        ///
        /// @param              [in] aMatrix A matrix

                                RotationMatrix                              (   const   Matrix3d&                   aMatrix                                     ) ;

        /// @brief              Constructor
        ///
        /// @param              [in] aFirstCoefficient A first coefficient
        /// @param              [in] aSecondCoefficient A second coefficient
        /// @param              [in] aThirdCoefficient A third coefficient
        /// @param              [in] aFourthCoefficient A fourth coefficient
        /// @param              [in] aFifthCoefficient A fifth coefficient
        /// @param              [in] aSixthCoefficient A sixth coefficient
        /// @param              [in] aSeventhCoefficient A seventh coefficient
        /// @param              [in] aEighthCoefficient A eighth coefficient
        /// @param              [in] aNinthCoefficient A ninth coefficient

                                RotationMatrix                              (   const   Real&                       aFirstCoefficient,
                                                                                const   Real&                       aSecondCoefficient,
                                                                                const   Real&                       aThirdCoefficient,
                                                                                const   Real&                       aFourthCoefficient,
                                                                                const   Real&                       aFifthCoefficient,
                                                                                const   Real&                       aSixthCoefficient,
                                                                                const   Real&                       aSeventhCoefficient,
                                                                                const   Real&                       aEighthCoefficient,
                                                                                const   Real&                       aNinthCoefficient                           ) ;

        /// @brief              Equal to operator
        ///
        /// @code
        ///                     RotationMatrix(...) == RotationMatrix(...) ;
        /// @endcode
        ///
        /// @param              [in] aRotationMatrix A rotation matrix
        /// @return             True if rotation matrices are equal

        bool                    operator ==                                 (   const   RotationMatrix&             aRotationMatrix                             ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     RotationMatrix(...) != RotationMatrix(...) ;
        /// @endcode
        ///
        /// @param              [in] aRotationMatrix A rotation matrix
        /// @return             True if rotation matrices are not equal

        bool                    operator !=                                 (   const   RotationMatrix&             aRotationMatrix                             ) const ;

        /// @brief              Matrix multiplication operator
        ///
        /// @code
        ///                     RotationMatrix rotationMatrix_A_B = ... ;
        ///                     RotationMatrix rotationMatrix_B_C = ... ;
        ///                     RotationMatrix rotationMatrix_A_C = rotationMatrix_A_B * rotationMatrix_B_C ;
        /// @endcode
        ///
        /// @param              [in] aRotationMatrix A rotation matrix
        /// @return             Rotation matrix

        RotationMatrix          operator *                                  (   const   RotationMatrix&             aRotationMatrix                             ) const ;

        /// @brief              Vector multiplication operator
        ///
        /// @code
        ///                     RotationMatrix rotationMatrix_B_A = ... ;
        ///                     Vector3d vector_A = ... ;
        ///                     Vector3d vector_B = rotationMatrix_B_A * vector_A ;
        /// @endcode
        ///
        /// @param              [in] aVector A vector
        /// @return             Vector

        Vector3d                operator *                                  (   const   Vector3d&                   aVector                                     ) const ;

        /// @brief              Index function operator
        ///
        /// @code
        ///                     RotationMatrix rotationMatrix = RotationMatrix::Unit() ;
        ///                     double value_00 = rotationMatrix(0, 0) ; // 1.0
        /// @endcode
        ///
        /// @param              [in] aRowIndex A row index
        /// @param              [in] aColumnIndex A column index
        /// @return             Value at index

        double                  operator ()                                 (   const   Index&                      aRowIndex,
                                                                                const   Index&                      aColumnIndex                                ) const ;

        /// @brief              Index function operator
        ///
        /// @code
        ///                     RotationMatrix rotationMatrix = RotationMatrix::Unit() ;
        ///                     rotationMatrix(0, 0) = 0.0 ;
        /// @endcode
        ///
        /// @param              [in] aRowIndex A row index
        /// @param              [in] aColumnIndex A column index
        /// @return             Reference of value at index

        double&                 operator ()                                 (   const   Index&                      aRowIndex,
                                                                                const   Index&                      aColumnIndex                                ) ;

        /// @brief              Output stream operator
        ///
        /// @code
        ///                     std::cout << RotationMatrix(...) ;
        /// @endcode
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] aRotationMatrix A rotation matrix
        /// @return             A reference to output stream

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   RotationMatrix&             aRotationMatrix                             ) ;

        /// @brief              Check if rotation matrix is defined
        ///
        /// @code
        ///                     RotationMatrix(Vector3d(0.0, 0.0, 1.0), Angle::Degrees(90.0)).isDefined() ; // True
        /// @endcode
        ///
        /// @return             True if rotation matrix is defined

        bool                    isDefined                                   ( ) const ;

        /// @brief              Access underlying rotation matrix
        ///
        /// @return             Reference to underlying rotation matrix

        const Matrix3d&         accessMatrix                                ( ) const ;

        /// @brief              Get row at index
        ///
        /// @param              [in] aRowIndex Index of row
        /// @return             Row at index

        Vector3d                getRowAt                                    (   const   Index&                      aRowIndex                                   ) const ;

        /// @brief              Get column at index
        ///
        /// @param              [in] aColumnIndex Index of column
        /// @return             Column at index

        Vector3d                getColumnAt                                 (   const   Index&                      aColumnIndex                                ) const ;

        /// @brief              Get underlying rotation matrix
        ///
        /// @return             Underlying rotation matrix

        Matrix3d                getMatrix                                   ( ) const ;

        /// @brief              Get transposed rotation matrix
        ///
        /// @code
        ///                     RotationMatrix(...).toTransposed() ;
        /// @endcode
        ///
        /// @return             Transposed rotation matrix

        RotationMatrix          toTransposed                                ( ) const ;

        /// @brief              Transpose rotation matrix
        ///
        /// @code
        ///                     RotationMatrix(...).transpose() ;
        /// @endcode

        RotationMatrix&         transpose                                   ( ) ;

        /// @brief              Constructs an undefined rotation matrix
        ///
        /// @code
        ///                     RotationMatrix rotationMatrix = RotationMatrix::Undefined() ; // Undefined
        /// @endcode
        ///
        /// @return             Undefined rotation matrix

        static RotationMatrix   Undefined                                   ( ) ;

        /// @brief              Constructs a unit rotation matrix
        ///
        /// @code
        ///                     RotationMatrix rotationMatrix = RotationMatrix::Unit() ;
        /// @endcode
        ///
        /// @return             Unit rotation matrix

        static RotationMatrix   Unit                                        ( ) ;

        /// @brief              Constructs a rotation matrix representing a rotation around the X-axis
        ///
        /// @code
        ///                     RotationMatrix rotationMatrix = RotationMatrix::RX(Angle::Degrees(30.0)) ;
        /// @endcode
        ///
        /// @param              [in] aRotationAngle A rotation angle
        /// @return             Rotation matrix

        static RotationMatrix   RX                                          (   const   Angle&                      aRotationAngle                              ) ;

        /// @brief              Constructs a rotation matrix representing a rotation around the Y-axis
        ///
        /// @code
        ///                     RotationMatrix rotationMatrix = RotationMatrix::RY(Angle::Degrees(30.0)) ;
        /// @endcode
        ///
        /// @param              [in] aRotationAngle A rotation angle
        /// @return             Rotation matrix

        static RotationMatrix   RY                                          (   const   Angle&                      aRotationAngle                              ) ;

        /// @brief              Constructs a rotation matrix representing a rotation around the Z-axis
        ///
        /// @code
        ///                     RotationMatrix rotationMatrix = RotationMatrix::RZ(Angle::Degrees(30.0)) ;
        /// @endcode
        ///
        /// @param              [in] aRotationAngle A rotation angle
        /// @return             Rotation matrix

        static RotationMatrix   RZ                                          (   const   Angle&                      aRotationAngle                              ) ;

        /// @brief              Constructs a rotation matrix from row vectors
        ///
        /// @code
        ///                     RotationMatrix rotationMatrix = RotationMatrix::Rows(Vector3d(1.0, 0.0, 0.0), Vector3d(1.0, 0.0, 0.0), Vector3d(1.0, 0.0, 0.0)) ;
        /// @endcode
        ///
        /// @param              [in] aFirstRow A first row
        /// @param              [in] aSecondRow A second row
        /// @param              [in] aThirdRow A third row
        /// @return             Rotation matrix

        static RotationMatrix   Rows                                        (   const   Vector3d&                   aFirstRow,
                                                                                const   Vector3d&                   aSecondRow,
                                                                                const   Vector3d&                   aThirdRow                                   ) ;

        /// @brief              Constructs a rotation matrix from column vectors
        ///
        /// @code
        ///                     RotationMatrix rotationMatrix = RotationMatrix::Columns(Vector3d(1.0, 0.0, 0.0), Vector3d(1.0, 0.0, 0.0), Vector3d(1.0, 0.0, 0.0)) ;
        /// @endcode
        ///
        /// @param              [in] aFirstColumn A first column
        /// @param              [in] aSecondColumn A second column
        /// @param              [in] aThirdColumn A third column
        /// @return             Rotation matrix

        static RotationMatrix   Columns                                     (   const   Vector3d&                   aFirstColumn,
                                                                                const   Vector3d&                   aSecondColumn,
                                                                                const   Vector3d&                   aThirdColumn                                ) ;

        /// @brief              Constructs a rotation matrix from a quaternion
        ///
        /// @code
        ///                     RotationMatrix rotationMatrix = RotationMatrix::Quaternion(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0)) ;
        /// @endcode
        ///
        /// @param              [in] aQuaternion A quaternion
        /// @return             Rotation matrix

        static RotationMatrix   Quaternion                                  (   const   rot::Quaternion&            aQuaternion                                 ) ;

        /// @brief              Constructs a rotation matrix from a rotation vector
        ///
        /// @code
        ///                     RotationMatrix rotationMatrix = RotationMatrix::RotationVector(Vector3d(0.0, 0.0, 1.0), Angle::Degrees(90.0)) ;
        /// @endcode
        ///
        /// @param              [in] aRotationVector A rotation vector
        /// @return             Rotation matrix

        static RotationMatrix   RotationVector                              (   const   rot::RotationVector&        aRotationVector                             ) ;

    private:

        Matrix3d                matrix_ ;

                                RotationMatrix                              ( ) ;

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
