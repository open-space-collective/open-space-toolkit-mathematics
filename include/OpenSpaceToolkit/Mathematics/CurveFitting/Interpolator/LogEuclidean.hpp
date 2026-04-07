/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Interpolator_LogEuclidean__
#define __OpenSpaceToolkit_Mathematics_Interpolator_LogEuclidean__

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Pair.hpp>
#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

namespace ostk
{
namespace mathematics
{
namespace curvefitting
{
namespace interpolator
{

using ostk::core::container::Array;
using ostk::core::container::Pair;
using ostk::core::type::Index;
using ostk::core::type::Real;
using ostk::core::type::Size;

using ostk::mathematics::object::MatrixXd;
using ostk::mathematics::object::VectorXd;

/// @brief Log-Euclidean interpolator for symmetric positive definite matrices
///
/// Performs interpolation of symmetric positive definite (SPD) matrices using the
/// Log-Euclidean Riemannian metric. This method maps SPD matrices to the tangent space
/// (symmetric matrices) via the matrix logarithm, performs linear interpolation in that
/// space, and maps back via the matrix exponential. This ensures the interpolated result
/// is always symmetric positive definite.
///
/// @code{.cpp}
///     VectorXd x(2);
///     x << 0.0, 1.0;
///     Array<MatrixXd> matrices = {P0, P1};
///     LogEuclidean interpolator(x, matrices);
///     MatrixXd result = interpolator.evaluate(0.5);
/// @endcode
///
/// @ref https://hal.inria.fr/inria-00071250/document
class LogEuclidean
{
   public:
    /// @brief Constructor
    ///
    /// @code{.cpp}
    ///     LogEuclidean interpolator(x, matrices);
    /// @endcode
    ///
    /// @param anXVector A vector of x values (sorted in ascending order)
    /// @param aMatrixArray An array of symmetric positive definite matrices
    LogEuclidean(const VectorXd& anXVector, const Array<MatrixXd>& aMatrixArray);

    /// @brief Destructor
    ~LogEuclidean();

    /// @brief Evaluate the interpolator at a single point
    ///
    /// @code{.cpp}
    ///     MatrixXd result = interpolator.evaluate(0.5);
    /// @endcode
    ///
    /// @param aQueryValue An x value
    /// @return Interpolated symmetric positive definite matrix
    MatrixXd evaluate(const double& aQueryValue) const;

    /// @brief Evaluate the interpolator at multiple points
    ///
    /// @code{.cpp}
    ///     Array<MatrixXd> results = interpolator.evaluate(queryVector);
    /// @endcode
    ///
    /// @param aQueryVector A vector of x values
    /// @return Array of interpolated symmetric positive definite matrices
    Array<MatrixXd> evaluate(const VectorXd& aQueryVector) const;

    /// @brief Compute the matrix logarithm of a symmetric positive definite matrix
    ///
    /// Uses spectral decomposition: log(P) = Q * log(Lambda) * Q^T
    ///
    /// @param aMatrix A symmetric positive definite matrix
    /// @return The matrix logarithm
    /// @throws RuntimeError if the matrix is not positive definite
    static MatrixXd MatrixLogSPD(const MatrixXd& aMatrix);

    /// @brief Compute the matrix exponential of a symmetric matrix
    ///
    /// Uses spectral decomposition: exp(S) = Q * exp(Lambda) * Q^T
    ///
    /// @param aMatrix A symmetric matrix
    /// @return The matrix exponential (guaranteed symmetric positive definite)
    static MatrixXd MatrixExpSymmetric(const MatrixXd& aMatrix);

    /// @brief Interpolate between two SPD matrices using the Log-Euclidean metric
    ///
    /// @param aFirstMatrix First symmetric positive definite matrix
    /// @param aSecondMatrix Second symmetric positive definite matrix
    /// @param aRatio Interpolation ratio in [0, 1] where 0 returns aFirstMatrix and 1 returns aSecondMatrix
    /// @return Interpolated symmetric positive definite matrix
    static MatrixXd Interpolate(const MatrixXd& aFirstMatrix, const MatrixXd& aSecondMatrix, const double& aRatio);

   private:
    VectorXd x_;
    Array<MatrixXd> matrices_;

    Pair<Index, Index> findIndexRange(const double& aQueryValue) const;
};

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk

#endif
