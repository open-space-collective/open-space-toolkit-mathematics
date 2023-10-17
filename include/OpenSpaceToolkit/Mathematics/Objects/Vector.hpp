/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Objects_Vector__
#define __OpenSpaceToolkit_Mathematics_Objects_Vector__

#include <OpenSpaceToolkit/Core/Types/String.hpp>

#define EIGEN_MATRIXBASE_PLUGIN "OpenSpaceToolkit/Mathematics/Objects/Eigen.hpp"

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
namespace math
{
namespace obj
{

using Vector2i = Eigen::Vector2i;
using Vector3i = Eigen::Vector3i;
using Vector4i = Eigen::Vector4i;

using VectorXi = Eigen::VectorXi;

using Vector2d = Eigen::Vector2d;
using Vector3d = Eigen::Vector3d;
using Vector4d = Eigen::Vector4d;
using Vector6d = Eigen::Matrix<double, 6, 1>;

using VectorXd = Eigen::VectorXd;

using RowVectorXd = Eigen::RowVectorXd;

using Matrix2i = Eigen::Matrix2i;
using Matrix3i = Eigen::Matrix3i;
using Matrix4i = Eigen::Matrix4i;

using MatrixXi = Eigen::MatrixXi;

using Matrix2d = Eigen::Matrix2d;
using Matrix3d = Eigen::Matrix3d;
using Matrix4d = Eigen::Matrix4d;

using MatrixXd = Eigen::MatrixXd;

}  // namespace obj
}  // namespace math
}  // namespace ostk

#endif
