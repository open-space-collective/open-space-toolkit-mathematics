/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/LogEuclidean.hpp>

#include <Eigen/Eigenvalues>

namespace ostk
{
namespace mathematics
{
namespace curvefitting
{
namespace interpolator
{

LogEuclidean::LogEuclidean(const VectorXd& anXVector, const Array<MatrixXd>& aMatrixArray)
    : x_(anXVector),
      matrices_(aMatrixArray)
{
    if (anXVector.size() < 2)
    {
        throw ostk::core::error::runtime::Wrong("x");
    }

    if (Size(anXVector.size()) != aMatrixArray.getSize())
    {
        throw ostk::core::error::runtime::Wrong("x and matrices");
    }

    const Size rows = static_cast<Size>(aMatrixArray[0].rows());
    const Size cols = static_cast<Size>(aMatrixArray[0].cols());

    if (rows != cols)
    {
        throw ostk::core::error::runtime::Wrong("Matrix must be square");
    }

    for (Size i = 1; i < aMatrixArray.getSize(); ++i)
    {
        if (static_cast<Size>(aMatrixArray[i].rows()) != rows || static_cast<Size>(aMatrixArray[i].cols()) != cols)
        {
            throw ostk::core::error::runtime::Wrong("All matrices must have the same dimensions");
        }
    }

    // Check x is strictly monotonically increasing
    for (int i = 1; i < anXVector.size(); ++i)
    {
        if (anXVector(i) <= anXVector(i - 1))
        {
            throw ostk::core::error::runtime::Wrong("x must be strictly monotonically increasing");
        }
    }
}

LogEuclidean::~LogEuclidean() {}

MatrixXd LogEuclidean::evaluate(const double& aQueryValue) const
{
    const auto [previousIndex, nextIndex] = findIndexRange(aQueryValue);

    if (previousIndex == nextIndex)
    {
        return matrices_[previousIndex];
    }

    const double ratio = (aQueryValue - x_(previousIndex)) / (x_(nextIndex) - x_(previousIndex));

    return Interpolate(matrices_[previousIndex], matrices_[nextIndex], ratio);
}

Array<MatrixXd> LogEuclidean::evaluate(const VectorXd& aQueryVector) const
{
    Array<MatrixXd> results;
    results.reserve(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        results.add(evaluate(aQueryVector(i)));
    }

    return results;
}

MatrixXd LogEuclidean::MatrixLogSPD(const MatrixXd& aMatrix)
{
    const Eigen::SelfAdjointEigenSolver<MatrixXd> solver(aMatrix);

    if (solver.info() != Eigen::Success)
    {
        throw ostk::core::error::RuntimeError("Eigendecomposition failed.");
    }

    const VectorXd& eigenvalues = solver.eigenvalues();

    for (int i = 0; i < eigenvalues.size(); ++i)
    {
        if (eigenvalues(i) <= 0.0)
        {
            throw ostk::core::error::RuntimeError("Matrix is not positive definite.");
        }
    }

    const VectorXd logEigenvalues = eigenvalues.array().log().matrix();
    const MatrixXd& eigenvectors = solver.eigenvectors();

    return eigenvectors * logEigenvalues.asDiagonal() * eigenvectors.transpose();
}

MatrixXd LogEuclidean::MatrixExpSymmetric(const MatrixXd& aMatrix)
{
    const Eigen::SelfAdjointEigenSolver<MatrixXd> solver(aMatrix);

    if (solver.info() != Eigen::Success)
    {
        throw ostk::core::error::RuntimeError("Eigendecomposition failed.");
    }

    const VectorXd expEigenvalues = solver.eigenvalues().array().exp().matrix();
    const MatrixXd& eigenvectors = solver.eigenvectors();

    return eigenvectors * expEigenvalues.asDiagonal() * eigenvectors.transpose();
}

MatrixXd LogEuclidean::Interpolate(const MatrixXd& aFirstMatrix, const MatrixXd& aSecondMatrix, const double& aRatio)
{
    const MatrixXd logFirst = MatrixLogSPD(aFirstMatrix);
    const MatrixXd logSecond = MatrixLogSPD(aSecondMatrix);

    const MatrixXd logInterpolated = logFirst * (1.0 - aRatio) + logSecond * aRatio;

    return MatrixExpSymmetric(logInterpolated);
}

Pair<Index, Index> LogEuclidean::findIndexRange(const double& aQueryValue) const
{
    const Index index = std::distance(x_.begin(), std::lower_bound(x_.begin(), x_.end(), aQueryValue));

    if (index == 0)
    {
        return {0, 0};
    }

    if (index == Index(x_.size()))
    {
        return {index - 1, index - 1};
    }

    return {index - 1, index};
}

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk
