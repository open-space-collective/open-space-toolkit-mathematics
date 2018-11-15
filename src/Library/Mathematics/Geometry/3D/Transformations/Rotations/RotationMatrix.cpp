////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>
#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

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

                                RotationMatrix::RotationMatrix              (   const   Matrix3d&                   aMatrix                                     )
                                :   matrix_(aMatrix)
{

    if ((matrix_.col(0).norm() - 1.0) > Real::Epsilon())
    {
        throw library::core::error::RuntimeError("First column is not unitary.") ;
    }

    if ((matrix_.col(1).norm() - 1.0) > Real::Epsilon())
    {
        throw library::core::error::RuntimeError("Second column is not unitary.") ;
    }

    if ((matrix_.col(2).norm() - 1.0) > Real::Epsilon())
    {
        throw library::core::error::RuntimeError("Third column is not unitary.") ;
    }

    if (std::abs(matrix_.col(0).dot(matrix_.col(1))) > Real::Epsilon())
    {
        throw library::core::error::RuntimeError("First and second columns are not orthogonal.") ;
    }

    if (std::abs(matrix_.col(1).dot(matrix_.col(2))) > Real::Epsilon())
    {
        throw library::core::error::RuntimeError("Second and third columns are not orthogonal.") ;
    }

    if (std::abs(matrix_.col(2).dot(matrix_.col(0))) > Real::Epsilon())
    {
        throw library::core::error::RuntimeError("First and third columns are not orthogonal.") ;
    }

}

                                RotationMatrix::RotationMatrix              (   const   Real&                       aFirstCoefficient,
                                                                                const   Real&                       aSecondCoefficient,
                                                                                const   Real&                       aThirdCoefficient,
                                                                                const   Real&                       aFourthCoefficient,
                                                                                const   Real&                       aFifthCoefficient,
                                                                                const   Real&                       aSixthCoefficient,
                                                                                const   Real&                       aSeventhCoefficient,
                                                                                const   Real&                       aEighthCoefficient,
                                                                                const   Real&                       aNinthCoefficient                           )
                                :   matrix_((Matrix3d() <<  aFirstCoefficient, aSecondCoefficient, aThirdCoefficient,
                                                            aFourthCoefficient, aFifthCoefficient, aSixthCoefficient,
                                                            aSeventhCoefficient, aEighthCoefficient, aNinthCoefficient).finished())
{

    if ((matrix_.col(0).norm() - 1.0) > Real::Epsilon())
    {
        throw library::core::error::RuntimeError("First column is not unitary.") ;
    }

    if ((matrix_.col(1).norm() - 1.0) > Real::Epsilon())
    {
        throw library::core::error::RuntimeError("Second column is not unitary.") ;
    }

    if ((matrix_.col(2).norm() - 1.0) > Real::Epsilon())
    {
        throw library::core::error::RuntimeError("Third column is not unitary.") ;
    }

    if (std::abs(matrix_.col(0).dot(matrix_.col(1))) > Real::Epsilon())
    {
        throw library::core::error::RuntimeError("First and second columns are not orthogonal.") ;
    }

    if (std::abs(matrix_.col(1).dot(matrix_.col(2))) > Real::Epsilon())
    {
        throw library::core::error::RuntimeError("Second and third columns are not orthogonal.") ;
    }

    if (std::abs(matrix_.col(2).dot(matrix_.col(0))) > Real::Epsilon())
    {
        throw library::core::error::RuntimeError("First and third columns are not orthogonal.") ;
    }

}

bool                            RotationMatrix::operator ==                 (   const   RotationMatrix&             aRotationMatrix                             ) const
{

    if ((!this->isDefined()) || (!aRotationMatrix.isDefined()))
    {
        return false ;
    }
    
    return matrix_ ==  aRotationMatrix.matrix_ ;

}

bool                            RotationMatrix::operator !=                 (   const   RotationMatrix&             aRotationMatrix                             ) const
{
    return !((*this) == aRotationMatrix) ;
}

RotationMatrix                  RotationMatrix::operator *                  (   const   RotationMatrix&             aRotationMatrix                             ) const
{

    if ((!this->isDefined()) || (!aRotationMatrix.isDefined()))
    {
        throw library::core::error::runtime::Undefined("Rotation matrix") ;
    }

    return RotationMatrix(matrix_ * aRotationMatrix.matrix_) ;

}

Vector3d                        RotationMatrix::operator *                  (   const   Vector3d&                   aVector                                     ) const
{

    if (!aVector.isDefined())
    {
        throw library::core::error::runtime::Undefined("Vector") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Rotation matrix") ;
    }

    return matrix_ * aVector ;

}

double                          RotationMatrix::operator ()                 (   const   Index&                      aRowIndex,
                                                                                const   Index&                      aColumnIndex                                ) const
{

    if (aRowIndex > 3)
    {
        throw library::core::error::RuntimeError("Row index out of bounds.") ;
    }

    if (aColumnIndex > 3)
    {
        throw library::core::error::RuntimeError("Column index out of bounds.") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Rotation matrix") ;
    }
    
    return matrix_(aRowIndex, aColumnIndex) ;

}

double&                         RotationMatrix::operator ()                 (   const   Index&                      aRowIndex,
                                                                                const   Index&                      aColumnIndex                                )
{

    if (aRowIndex > 3)
    {
        throw library::core::error::RuntimeError("Row index out of bounds.") ;
    }

    if (aColumnIndex > 3)
    {
        throw library::core::error::RuntimeError("Column index out of bounds.") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Rotation matrix") ;
    }

    return matrix_(aRowIndex, aColumnIndex) ;

}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   RotationMatrix&             aRotationMatrix                             )
{

    library::core::utils::Print::Header(anOutputStream, "Rotation Matrix") ;

    library::core::utils::Print::Line(anOutputStream) << aRotationMatrix.matrix_(0, 0) << aRotationMatrix.matrix_(0, 1) << aRotationMatrix.matrix_(0, 2) ;
    library::core::utils::Print::Line(anOutputStream) << aRotationMatrix.matrix_(1, 0) << aRotationMatrix.matrix_(1, 1) << aRotationMatrix.matrix_(1, 2) ;
    library::core::utils::Print::Line(anOutputStream) << aRotationMatrix.matrix_(2, 0) << aRotationMatrix.matrix_(2, 1) << aRotationMatrix.matrix_(2, 2) ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            RotationMatrix::isDefined                   ( ) const
{
    return matrix_.isDefined() ;
}

const Matrix3d&                 RotationMatrix::accessMatrix                ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Rotation matrix") ;
    }

    return matrix_ ;

}

Vector3d                        RotationMatrix::getRowAt                    (   const   Index&                      aRowIndex                                   ) const
{

    if (aRowIndex > 3)
    {
        throw library::core::error::RuntimeError("Row index out of bounds.") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Rotation matrix") ;
    }

    return matrix_.block<1,3>(aRowIndex, 0) ;

}

Vector3d                        RotationMatrix::getColumnAt                 (   const   Index&                      aColumnIndex                                ) const
{

    if (aColumnIndex > 3)
    {
        throw library::core::error::RuntimeError("Column index out of bounds.") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Rotation matrix") ;
    }

    return matrix_.block<3,1>(0, aColumnIndex) ;

}

Matrix3d                        RotationMatrix::getMatrix                   ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Rotation matrix") ;
    }

    return matrix_ ;

}

RotationMatrix                  RotationMatrix::toTransposed                ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Rotation matrix") ;
    }

    return RotationMatrix(matrix_.transpose()) ;

}

RotationMatrix&                 RotationMatrix::transpose                   ( )
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Rotation matrix") ;
    }

    matrix_ = matrix_.transpose() ;

    return *this ;

}

RotationMatrix                  RotationMatrix::Undefined                   ( )
{
    return RotationMatrix() ;
}

RotationMatrix                  RotationMatrix::Unit                        ( )
{
    return RotationMatrix(Matrix3d::Identity()) ;
}

RotationMatrix                  RotationMatrix::RX                          (   const   Angle&                      aRotationAngle                              )
{

    if (!aRotationAngle.isDefined())
    {
        throw library::core::error::runtime::Undefined("Rotation angle") ;
    }

    const Real rotationAngle_rad = aRotationAngle.inRadians() ;

    Matrix3d matrix ;
    
    matrix << 1.0, 0.0,                             0.0,
              0.0, +std::cos(rotationAngle_rad), +std::sin(rotationAngle_rad),
              0.0, -std::sin(rotationAngle_rad), +std::cos(rotationAngle_rad) ;                                                                            

    return RotationMatrix(matrix) ;

}

RotationMatrix                  RotationMatrix::RY                          (   const   Angle&                      aRotationAngle                              )
{

    if (!aRotationAngle.isDefined())
    {
        throw library::core::error::runtime::Undefined("Rotation angle") ;
    }

    const Real rotationAngle_rad = aRotationAngle.inRadians() ;

    Matrix3d matrix ;
    
    matrix << +std::cos(rotationAngle_rad), 0.0, -std::sin(rotationAngle_rad),
              0.0,                          1.0, 0.0,
              +std::sin(rotationAngle_rad), 0.0, +std::cos(rotationAngle_rad) ;

    return RotationMatrix(matrix) ;

}

RotationMatrix                  RotationMatrix::RZ                          (   const   Angle&                      aRotationAngle                              )
{

    if (!aRotationAngle.isDefined())
    {
        throw library::core::error::runtime::Undefined("Rotation angle") ;
    }

    const Real rotationAngle_rad = aRotationAngle.inRadians() ;

    Matrix3d matrix ;
    
    matrix << +std::cos(rotationAngle_rad), +std::sin(rotationAngle_rad), 0.0,
              -std::sin(rotationAngle_rad), +std::cos(rotationAngle_rad), 0.0,
              0.0,                          0.0,                          1.0 ;

    return RotationMatrix(matrix) ;

}

RotationMatrix                  RotationMatrix::Rows                        (   const   Vector3d&                   aFirstRow,
                                                                                const   Vector3d&                   aSecondRow,
                                                                                const   Vector3d&                   aThirdRow                                   )
{

    if (!aFirstRow.isDefined())
    {
        throw library::core::error::runtime::Undefined("First row") ;
    }

    if (!aSecondRow.isDefined())
    {
        throw library::core::error::runtime::Undefined("Second row") ;
    }

    if (!aThirdRow.isDefined())
    {
        throw library::core::error::runtime::Undefined("Third row") ;
    }

    if ((aFirstRow.norm() - 1.0) > Real::Epsilon())
    {
        throw library::core::error::RuntimeError("First row is not unitary.") ;
    }

    if ((aSecondRow.norm() - 1.0) > Real::Epsilon())
    {
        throw library::core::error::RuntimeError("Second row is not unitary.") ;
    }

    if ((aThirdRow.norm() - 1.0) > Real::Epsilon())
    {
        throw library::core::error::RuntimeError("Third row is not unitary.") ;
    }

    if (std::abs(aFirstRow.dot(aSecondRow)) > Real::Epsilon())
    {
        throw library::core::error::RuntimeError("First and second columns are not orthogonal.") ;
    }

    if (std::abs(aSecondRow.dot(aThirdRow)) > Real::Epsilon())
    {
        throw library::core::error::RuntimeError("Second and third columns are not orthogonal.") ;
    }

    if (std::abs(aThirdRow.dot(aFirstRow)) > Real::Epsilon())
    {
        throw library::core::error::RuntimeError("First and third columns are not orthogonal.") ;
    }

    Matrix3d matrix ;
    
    matrix << aFirstRow(0),  aFirstRow(1),  aFirstRow(2),
              aSecondRow(0), aSecondRow(1), aSecondRow(2),
              aThirdRow(0),  aThirdRow(1),  aThirdRow(2) ;

    return RotationMatrix(matrix) ;

}

RotationMatrix                  RotationMatrix::Columns                     (   const   Vector3d&                   aFirstColumn,
                                                                                const   Vector3d&                   aSecondColumn,
                                                                                const   Vector3d&                   aThirdColumn                                )
{

    if (!aFirstColumn.isDefined())
    {
        throw library::core::error::runtime::Undefined("First column") ;
    }

    if (!aSecondColumn.isDefined())
    {
        throw library::core::error::runtime::Undefined("Second column") ;
    }

    if (!aThirdColumn.isDefined())
    {
        throw library::core::error::runtime::Undefined("Third column") ;
    }

    if ((aFirstColumn.norm() - 1.0) > Real::Epsilon())
    {
        throw library::core::error::RuntimeError("First column is not unitary.") ;
    }

    if ((aSecondColumn.norm() - 1.0) > Real::Epsilon())
    {
        throw library::core::error::RuntimeError("Second column is not unitary.") ;
    }

    if ((aThirdColumn.norm() - 1.0) > Real::Epsilon())
    {
        throw library::core::error::RuntimeError("Third column is not unitary.") ;
    }

    if (std::abs(aFirstColumn.dot(aSecondColumn)) > Real::Epsilon())
    {
        throw library::core::error::RuntimeError("First and second columns are not orthogonal.") ;
    }

    if (std::abs(aSecondColumn.dot(aThirdColumn)) > Real::Epsilon())
    {
        throw library::core::error::RuntimeError("Second and third columns are not orthogonal.") ;
    }

    if (std::abs(aThirdColumn.dot(aFirstColumn)) > Real::Epsilon())
    {
        throw library::core::error::RuntimeError("First and third columns are not orthogonal.") ;
    }

    Matrix3d matrix ;
    
    matrix << aFirstColumn(0), aSecondColumn(0), aThirdColumn(0),
              aFirstColumn(1), aSecondColumn(1), aThirdColumn(1),
              aFirstColumn(2), aSecondColumn(2), aThirdColumn(2) ;

    return RotationMatrix(matrix) ;

}

RotationMatrix                  RotationMatrix::Quaternion                  (   const   rot::Quaternion&            aQuaternion                                 )
{

    if (!aQuaternion.isDefined())
    {
        throw library::core::error::runtime::Undefined("Quaternion") ;
    }

    if (!aQuaternion.isUnitary())
    {
        throw library::core::error::RuntimeError("Quaternion is not unitary.") ;
    }

    if (aQuaternion == rot::Quaternion::Unit())
    {
        return RotationMatrix::Unit() ;
    }

    const double q_x = aQuaternion.x() ;
    const double q_y = aQuaternion.y() ;
    const double q_z = aQuaternion.z() ;
    const double q_s = aQuaternion.s() ;

    const double m_00 = + q_x * q_x - q_y * q_y - q_z * q_z + q_s * q_s ;
    const double m_01 = 2.0 * (q_x * q_y + q_z * q_s) ;
    const double m_02 = 2.0 * (q_x * q_z - q_y * q_s) ;

    const double m_10 = 2.0 * (q_y * q_x - q_z * q_s) ;
    const double m_11 = - q_x * q_x + q_y * q_y - q_z * q_z + q_s * q_s ;
    const double m_12 = 2.0 * (q_y * q_z + q_x * q_s) ;

    const double m_20 = 2.0 * (q_z * q_x + q_y * q_s) ;
    const double m_21 = 2.0 * (q_z * q_y - q_x * q_s) ;
    const double m_22 = - q_x * q_x - q_y * q_y + q_z * q_z + q_s * q_s ;

    Matrix3d matrix ;
    
    matrix << m_00, m_01, m_02,
              m_10, m_11, m_12,
              m_20, m_21, m_22 ;

    return RotationMatrix(matrix) ;

}

RotationMatrix                  RotationMatrix::RotationVector              (   const   rot::RotationVector&        aRotationVector                             )
{

    if (!aRotationVector.isDefined())
    {
        throw library::core::error::runtime::Undefined("Rotation vector") ;
    }

    const Vector3d axis = aRotationVector.getAxis() ;
    const double theta = aRotationVector.getAngle().inRadians() ;

    const double x = axis.x() ;
    const double y = axis.y() ;
    const double z = axis.z() ;

    const double cosAngle = std::cos(theta) ;
    const double sinAngle = std::sin(theta) ;

    Matrix3d matrix ;

    matrix(0, 0) = cosAngle + ((1.0 - cosAngle) * x * x) ;
    matrix(0, 1) = ((1.0 - cosAngle) * x * y) + (sinAngle * z) ;
    matrix(0, 2) = ((1.0 - cosAngle) * x * z) - (sinAngle * y) ;

    matrix(1, 0) = ((1.0 - cosAngle) * y * x) - (sinAngle * z) ;
    matrix(1, 1) = cosAngle + ((1.0 - cosAngle) * y * y) ;
    matrix(1, 2) = ((1.0 - cosAngle) * y * z) + (sinAngle * x) ;

    matrix(2, 0) = ((1.0 - cosAngle) * z * x) + (sinAngle * y) ;
    matrix(2, 1) = ((1.0 - cosAngle) * z * y) - (sinAngle * x) ;
    matrix(2, 2) = cosAngle + ((1.0 - cosAngle) * z * z) ;

    return RotationMatrix(matrix) ;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                RotationMatrix::RotationMatrix              ( )
                                :   matrix_(Matrix3d::Undefined())
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////