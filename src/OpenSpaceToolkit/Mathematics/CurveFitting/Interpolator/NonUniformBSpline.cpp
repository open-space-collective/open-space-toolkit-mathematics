/// Apache License 2.0

#include <algorithm>
#include <cmath>
#include <limits>
#include <sstream>
#include <stdexcept>

#pragma GCC diagnostic push  // Save diagnostic state

#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <Eigen/SparseLU>

#pragma GCC diagnostic pop  // Turn the warnings back on

#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/NonUniformBSpline.hpp>

namespace ostk
{
namespace mathematics
{
namespace curvefitting
{
namespace interpolator
{

namespace
{

/// @brief Compute the knot vector of the interpolating spline
///
/// Odd degrees place the breakpoints on the data sites; even degrees stagger them onto the
/// midpoints between consecutive sites, which is what makes the interpolation problem well
/// posed. This is the same arrangement as the Boost cardinal B-spline of each degree, whose
/// basis functions are centred on the data sites.
std::vector<double> ComputeKnots(const VectorXd& anXVector, const int aDegree)
{
    const int size = int(anXVector.size());

    std::vector<double> breakpoints;

    if ((aDegree % 2) == 1)
    {
        breakpoints.assign(anXVector.begin(), anXVector.end());
    }
    else
    {
        breakpoints.reserve(size + 1);

        breakpoints.push_back(anXVector(0));

        for (int i = 0; i + 1 < size; ++i)
        {
            breakpoints.push_back(0.5 * (anXVector(i) + anXVector(i + 1)));
        }

        breakpoints.push_back(anXVector(size - 1));
    }

    // Clamp both ends by repeating the outer breakpoints, so that the spline starts at the
    // first data site and ends at the last one

    std::vector<double> knots;
    knots.reserve(breakpoints.size() + 2 * std::size_t(aDegree));

    knots.insert(knots.end(), std::size_t(aDegree), breakpoints.front());
    knots.insert(knots.end(), breakpoints.begin(), breakpoints.end());
    knots.insert(knots.end(), std::size_t(aDegree), breakpoints.back());

    return knots;
}

/// @brief Find the index of the knot span containing the given value
///
/// @ref Piegl and Tiller, The NURBS Book, algorithm A2.1.
int FindSpan(const std::vector<double>& aKnotArray, const int aDegree, const double& aQueryValue)
{
    const int lastBasisFunctionIndex = int(aKnotArray.size()) - aDegree - 2;

    if (aQueryValue >= aKnotArray[lastBasisFunctionIndex + 1])
    {
        return lastBasisFunctionIndex;
    }

    if (aQueryValue <= aKnotArray[aDegree])
    {
        return aDegree;
    }

    int low = aDegree;
    int high = lastBasisFunctionIndex + 1;
    int middle = (low + high) / 2;

    while ((aQueryValue < aKnotArray[middle]) || (aQueryValue >= aKnotArray[middle + 1]))
    {
        if (aQueryValue < aKnotArray[middle])
        {
            high = middle;
        }
        else
        {
            low = middle;
        }

        middle = (low + high) / 2;
    }

    return middle;
}

/// @brief Compute the non-zero basis functions and their derivatives at the given value
///
/// On return, aDerivativeArray[k][j] holds the k-th derivative of the basis function of index
/// (aSpan - aDegree + j), for k up to aDerivativeOrder and j up to aDegree.
///
/// @ref Piegl and Tiller, The NURBS Book, algorithm A2.3.
void ComputeBasisFunctionDerivatives(
    const std::vector<double>& aKnotArray,
    const int aDegree,
    const int aSpan,
    const double& aQueryValue,
    const int aDerivativeOrder,
    std::vector<std::vector<double>>& aDerivativeArray
)
{
    std::vector<std::vector<double>> ndu(aDegree + 1, std::vector<double>(aDegree + 1, 0.0));
    std::vector<double> left(aDegree + 1, 0.0);
    std::vector<double> right(aDegree + 1, 0.0);

    ndu[0][0] = 1.0;

    for (int j = 1; j <= aDegree; ++j)
    {
        left[j] = aQueryValue - aKnotArray[aSpan + 1 - j];
        right[j] = aKnotArray[aSpan + j] - aQueryValue;

        double saved = 0.0;

        for (int r = 0; r < j; ++r)
        {
            // Lower triangle holds the knot differences, upper triangle the basis functions

            ndu[j][r] = right[r + 1] + left[j - r];

            const double temporary = ndu[r][j - 1] / ndu[j][r];

            ndu[r][j] = saved + right[r + 1] * temporary;
            saved = left[j - r] * temporary;
        }

        ndu[j][j] = saved;
    }

    aDerivativeArray.assign(aDerivativeOrder + 1, std::vector<double>(aDegree + 1, 0.0));

    for (int j = 0; j <= aDegree; ++j)
    {
        aDerivativeArray[0][j] = ndu[j][aDegree];
    }

    std::vector<std::vector<double>> a(2, std::vector<double>(aDegree + 1, 0.0));

    for (int r = 0; r <= aDegree; ++r)
    {
        int s1 = 0;
        int s2 = 1;

        a[0][0] = 1.0;

        for (int k = 1; k <= aDerivativeOrder; ++k)
        {
            double d = 0.0;

            const int rk = r - k;
            const int pk = aDegree - k;

            if (r >= k)
            {
                a[s2][0] = a[s1][0] / ndu[pk + 1][rk];
                d = a[s2][0] * ndu[rk][pk];
            }

            const int j1 = (rk >= -1) ? 1 : -rk;
            const int j2 = ((r - 1) <= pk) ? (k - 1) : (aDegree - r);

            for (int j = j1; j <= j2; ++j)
            {
                a[s2][j] = (a[s1][j] - a[s1][j - 1]) / ndu[pk + 1][rk + j];
                d += a[s2][j] * ndu[rk + j][pk];
            }

            if (r <= pk)
            {
                a[s2][k] = -a[s1][k - 1] / ndu[pk + 1][r];
                d += a[s2][k] * ndu[r][pk];
            }

            aDerivativeArray[k][r] = d;

            std::swap(s1, s2);
        }
    }

    // Multiply through by the correct factors, p! / (p - k)!

    int factor = aDegree;

    for (int k = 1; k <= aDerivativeOrder; ++k)
    {
        for (int j = 0; j <= aDegree; ++j)
        {
            aDerivativeArray[k][j] *= double(factor);
        }

        factor *= (aDegree - k);
    }
}

/// @brief Compute finite difference weights for arbitrarily spaced nodes
///
/// On return, aWeightArray[k][i] is the weight of the value at aNodeArray[i] in the k-th
/// derivative estimate at aQueryValue, for k up to aDerivativeOrder.
///
/// @ref Fornberg, Calculation of weights in finite difference formulas, SIAM Review 40 (1998).
void ComputeFiniteDifferenceWeights(
    const double& aQueryValue,
    const std::vector<double>& aNodeArray,
    const int aDerivativeOrder,
    std::vector<std::vector<double>>& aWeightArray
)
{
    const int size = int(aNodeArray.size());

    aWeightArray.assign(aDerivativeOrder + 1, std::vector<double>(size, 0.0));

    double c1 = 1.0;
    double c4 = aNodeArray[0] - aQueryValue;

    aWeightArray[0][0] = 1.0;

    for (int i = 1; i < size; ++i)
    {
        const int maximumOrder = std::min(i, aDerivativeOrder);

        double c2 = 1.0;
        const double c5 = c4;

        c4 = aNodeArray[i] - aQueryValue;

        for (int j = 0; j < i; ++j)
        {
            const double c3 = aNodeArray[i] - aNodeArray[j];

            c2 *= c3;

            if (j == (i - 1))
            {
                for (int k = maximumOrder; k >= 1; --k)
                {
                    aWeightArray[k][i] =
                        c1 * (double(k) * aWeightArray[k - 1][i - 1] - c5 * aWeightArray[k][i - 1]) / c2;
                }

                aWeightArray[0][i] = -c1 * c5 * aWeightArray[0][i - 1] / c2;
            }

            for (int k = maximumOrder; k >= 1; --k)
            {
                aWeightArray[k][j] = (c4 * aWeightArray[k][j] - double(k) * aWeightArray[k - 1][j]) / c3;
            }

            aWeightArray[0][j] = c4 * aWeightArray[0][j] / c3;
        }

        c1 = c2;
    }
}

/// @brief Get the number of nodes to estimate an endpoint derivative from
///
/// The widths are those that make the estimate as accurate as the spline itself, and match
/// the one-sided finite differences that the Boost cardinal B-spline of the same degree uses,
/// so that the uniform and non-uniform paths agree on uniformly spaced data.
int ComputeStencilSize(const int aDegree, const int aDerivativeOrder, const int aDataPointCount)
{
    const int stencilSize = (aDegree == 2) ? 3 : (aDegree + aDerivativeOrder + 1);

    return std::min(stencilSize, aDataPointCount);
}

/// @brief Estimate a derivative of the data at one of its end points
double EstimateEndpointDerivative(
    const VectorXd& anXVector,
    const VectorXd& aYVector,
    const int aDerivativeOrder,
    const int aStencilSize,
    const bool atLeftEnd
)
{
    const int size = int(anXVector.size());

    std::vector<double> nodes(aStencilSize);
    std::vector<double> values(aStencilSize);

    for (int i = 0; i < aStencilSize; ++i)
    {
        const int index = atLeftEnd ? i : (size - 1 - i);

        nodes[i] = anXVector(index);
        values[i] = aYVector(index);
    }

    std::vector<std::vector<double>> weights;

    ComputeFiniteDifferenceWeights(nodes[0], nodes, aDerivativeOrder, weights);

    double derivative = 0.0;

    for (int i = 0; i < aStencilSize; ++i)
    {
        derivative += weights[aDerivativeOrder][i] * values[i];
    }

    return derivative;
}

}  // namespace

NonUniformBSpline::NonUniformBSpline(
    const Size& aDegree,
    std::vector<double>&& aKnotArray,
    std::vector<double>&& aCoefficientArray,
    const DomainBehavior& aDomainBehavior
)
    : degree_(aDegree),
      knots_(std::move(aKnotArray)),
      coefficients_(std::move(aCoefficientArray)),
      domainBehavior_(aDomainBehavior)
{
}

NonUniformBSpline NonUniformBSpline::Interpolate(
    const VectorXd& anXVector, const VectorXd& aYVector, const Size& aDegree, const DomainBehavior& aDomainBehavior
)
{
    const int degree = int(aDegree);
    const int size = int(aYVector.size());

    if (degree < 1)
    {
        throw ostk::core::error::runtime::Wrong("degree");
    }

    if (size < 2)
    {
        throw ostk::core::error::runtime::Wrong("y");
    }

    if (anXVector.size() != aYVector.size())
    {
        throw ostk::core::error::runtime::Wrong("x and y");
    }

    for (int i = 0; i + 1 < size; ++i)
    {
        if (anXVector(i + 1) <= anXVector(i))
        {
            throw ostk::core::error::runtime::Wrong("x must be sorted in strictly ascending order");
        }
    }

    std::vector<double> knots = ComputeKnots(anXVector, degree);

    const int coefficientCount = int(knots.size()) - degree - 1;

    // The spline has more coefficients than there are data points. The difference is taken up
    // by matching the leading derivatives of the data at each of the two end points.

    const int endpointConditionCount = (coefficientCount - size) / 2;

    std::vector<Eigen::Triplet<double>> triplets;
    triplets.reserve(std::size_t(coefficientCount) * std::size_t(degree + 1));

    VectorXd rightHandSide(coefficientCount);

    std::vector<std::vector<double>> derivatives;

    // Each row of the system is one condition on the spline, and each column one coefficient.
    // Only the degree + 1 basis functions that are non-zero at the row's abscissa contribute,
    // so the system is banded.

    int row = 0;

    const auto addEndpointConditions = [&](const bool atLeftEnd)
    {
        const double endpoint = atLeftEnd ? anXVector(0) : anXVector(size - 1);

        const int span = FindSpan(knots, degree, endpoint);

        ComputeBasisFunctionDerivatives(knots, degree, span, endpoint, endpointConditionCount, derivatives);

        for (int order = 1; order <= endpointConditionCount; ++order)
        {
            for (int j = 0; j <= degree; ++j)
            {
                triplets.emplace_back(row, span - degree + j, derivatives[order][j]);
            }

            rightHandSide(row) = EstimateEndpointDerivative(
                anXVector, aYVector, order, ComputeStencilSize(degree, order, size), atLeftEnd
            );

            ++row;
        }
    };

    addEndpointConditions(true);

    for (int i = 0; i < size; ++i)
    {
        const int span = FindSpan(knots, degree, anXVector(i));

        ComputeBasisFunctionDerivatives(knots, degree, span, anXVector(i), 0, derivatives);

        for (int j = 0; j <= degree; ++j)
        {
            triplets.emplace_back(row, span - degree + j, derivatives[0][j]);
        }

        rightHandSide(row) = aYVector(i);

        ++row;
    }

    addEndpointConditions(false);

    Eigen::SparseMatrix<double> matrix(coefficientCount, coefficientCount);

    matrix.setFromTriplets(triplets.begin(), triplets.end());
    matrix.makeCompressed();

    Eigen::SparseLU<Eigen::SparseMatrix<double>> solver;

    solver.compute(matrix);

    if (solver.info() != Eigen::Success)
    {
        throw ostk::core::error::RuntimeError("Cannot factorize the spline interpolation system.");
    }

    const VectorXd coefficients = solver.solve(rightHandSide);

    if (solver.info() != Eigen::Success)
    {
        throw ostk::core::error::RuntimeError("Cannot solve the spline interpolation system.");
    }

    return NonUniformBSpline(
        aDegree, std::move(knots), std::vector<double>(coefficients.begin(), coefficients.end()), aDomainBehavior
    );
}

double NonUniformBSpline::evaluate(const double& aQueryValue) const
{
    return this->computeValue(aQueryValue, 0);
}

double NonUniformBSpline::computeDerivative(const double& aQueryValue) const
{
    return this->computeValue(aQueryValue, 1);
}

double NonUniformBSpline::computeSecondDerivative(const double& aQueryValue) const
{
    return this->computeValue(aQueryValue, 2);
}

double NonUniformBSpline::computeValue(const double& aQueryValue, const Size& aDerivativeOrder) const
{
    const int degree = int(degree_);

    const double xMinimum = knots_[degree_];
    const double xMaximum = knots_[knots_.size() - degree_ - 1];

    if (((aQueryValue < xMinimum) || (aQueryValue > xMaximum)) && (domainBehavior_ == DomainBehavior::Throw))
    {
        std::ostringstream oss;

        oss.precision(std::numeric_limits<double>::digits10 + 3);
        oss << "Requested abscissa x = " << aQueryValue << ", which is outside of allowed range [" << xMinimum << ", "
            << xMaximum << "]";

        throw std::domain_error(oss.str());
    }

    const int derivativeOrder = int(aDerivativeOrder);

    if (derivativeOrder > degree)
    {
        return 0.0;
    }

    const int span = FindSpan(knots_, degree, aQueryValue);

    std::vector<std::vector<double>> basisFunctionDerivatives;

    ComputeBasisFunctionDerivatives(knots_, degree, span, aQueryValue, derivativeOrder, basisFunctionDerivatives);

    double value = 0.0;

    for (int j = 0; j <= degree; ++j)
    {
        value += coefficients_[std::size_t(span - degree + j)] * basisFunctionDerivatives[derivativeOrder][j];
    }

    return value;
}

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk
