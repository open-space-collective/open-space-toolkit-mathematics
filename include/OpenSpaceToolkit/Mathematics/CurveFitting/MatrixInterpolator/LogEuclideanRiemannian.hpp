/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_MatrixInterpolator_LogEuclideanRiemannian__
#define __OpenSpaceToolkit_Mathematics_MatrixInterpolator_LogEuclideanRiemannian__

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
namespace matrixinterpolator
{

using ostk::core::container::Array;
using ostk::core::container::Pair;
using ostk::core::type::Index;
using ostk::core::type::Real;
using ostk::core::type::Size;

using ostk::mathematics::object::MatrixXd;
using ostk::mathematics::object::VectorXd;

/// @brief Log-Euclidean Riemannian interpolator for symmetric positive definite matrices
///
/// Performs interpolation of symmetric positive definite (SPD) matrices using the
/// Log-Euclidean Riemannian metric. This method maps SPD matrices to the tangent space
/// (symmetric matrices) via the matrix logarithm, performs linear interpolation in that
/// space, and maps back via the matrix exponential. This ensures the interpolated result
/// is always symmetric positive definite.
///
/// The input matrices must be symmetric positive definite (SPD). A matrix M is SPD if:
/// - M is symmetric: M = M^T
/// - All eigenvalues of M are strictly positive
///
/// @code{.cpp}
///     VectorXd x(2);
///     x << 0.0, 1.0;
///     Array<MatrixXd> matrices = {P0, P1};  // symmetric positive definite matrices
///     LogEuclideanRiemannian interpolator(x, matrices);
///     MatrixXd result = interpolator.evaluate(0.5);
/// @endcode
///
/// @ref https://inria.hal.science/inria-00070423/document
class LogEuclideanRiemannian
{
   public:
    /// @brief Constructor
    ///
    /// Constructs a Log-Euclidean Riemannian interpolator from x-coordinates and
    /// corresponding symmetric positive definite matrices. The matrix logarithms are
    /// precomputed at construction time for efficient interpolation.
    ///
    /// @code{.cpp}
    ///     LogEuclideanRiemannian interpolator(x, matrices);
    /// @endcode
    ///
    /// @param anXVector A vector of x values (strictly monotonically increasing)
    /// @param aMatrixArray An array of symmetric positive definite matrices (all same dimensions)
    LogEuclideanRiemannian(const VectorXd& anXVector, const Array<MatrixXd>& aMatrixArray);

    /// @brief Destructor
    ~LogEuclideanRiemannian();

    /// @brief Evaluate the interpolator at a single point
    ///
    /// Returns the interpolated symmetric positive definite matrix at the given x value.
    /// Values outside the x range are clamped to the nearest endpoint matrix.
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

    /// @brief Get the symmetric positive definite matrices provided at construction
    ///
    /// @code{.cpp}
    ///     Array<MatrixXd> matrices = interpolator.getMatrices();
    /// @endcode
    ///
    /// @return The array of symmetric positive definite matrices
    Array<MatrixXd> getMatrices() const;

   private:
    VectorXd x_;
    Array<MatrixXd> matrices_;
    Array<MatrixXd> logMatrices_;

    Pair<Index, Index> findIndexRange(const double& aQueryValue) const;

    static MatrixXd MatrixLogSPD(const MatrixXd& aMatrix);
    static MatrixXd MatrixExpSymmetric(const MatrixXd& aMatrix);
};

}  // namespace matrixinterpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk

#endif
