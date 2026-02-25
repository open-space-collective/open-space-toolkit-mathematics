/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Object_Vector__
#define __OpenSpaceToolkit_Mathematics_Object_Vector__

#include <OpenSpaceToolkit/Core/Type/String.hpp>

#define EIGEN_MATRIXBASE_PLUGIN "OpenSpaceToolkit/Mathematics/Object/Eigen.hpp"

// Disable Eigen warnings

#pragma GCC diagnostic push  // Save diagnostic state

#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wint-in-bool-context"
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"

#include <Eigen/Core>
#include <Eigen/Geometry>

#pragma GCC diagnostic pop  // Turn the warnings back on

namespace ostk
{
namespace mathematics
{
namespace object
{

/// @brief 2D integer vector type alias for Eigen::Vector2i
using Vector2i = Eigen::Vector2i;
/// @brief 3D integer vector type alias for Eigen::Vector3i
using Vector3i = Eigen::Vector3i;
/// @brief 4D integer vector type alias for Eigen::Vector4i
using Vector4i = Eigen::Vector4i;

/// @brief Dynamic-size integer vector type alias for Eigen::VectorXi
using VectorXi = Eigen::VectorXi;

/// @brief 2D double vector type alias for Eigen::Vector2d
using Vector2d = Eigen::Vector2d;
/// @brief 3D double vector type alias for Eigen::Vector3d
using Vector3d = Eigen::Vector3d;
/// @brief 4D double vector type alias for Eigen::Vector4d
using Vector4d = Eigen::Vector4d;
/// @brief 6D double vector type alias
using Vector6d = Eigen::Matrix<double, 6, 1>;

/// @brief Dynamic-size double vector type alias for Eigen::VectorXd
using VectorXd = Eigen::VectorXd;

/// @brief Dynamic-size double row vector type alias for Eigen::RowVectorXd
using RowVectorXd = Eigen::RowVectorXd;

/// @brief 2x2 integer matrix type alias for Eigen::Matrix2i
using Matrix2i = Eigen::Matrix2i;
/// @brief 3x3 integer matrix type alias for Eigen::Matrix3i
using Matrix3i = Eigen::Matrix3i;
/// @brief 4x4 integer matrix type alias for Eigen::Matrix4i
using Matrix4i = Eigen::Matrix4i;

/// @brief Dynamic-size integer matrix type alias for Eigen::MatrixXi
using MatrixXi = Eigen::MatrixXi;

/// @brief 2x2 double matrix type alias for Eigen::Matrix2d
using Matrix2d = Eigen::Matrix2d;
/// @brief 3x3 double matrix type alias for Eigen::Matrix3d
using Matrix3d = Eigen::Matrix3d;
/// @brief 4x4 double matrix type alias for Eigen::Matrix4d
using Matrix4d = Eigen::Matrix4d;

/// @brief Dynamic-size double matrix type alias for Eigen::MatrixXd
using MatrixXd = Eigen::MatrixXd;

}  // namespace object
}  // namespace mathematics
}  // namespace ostk

#endif
