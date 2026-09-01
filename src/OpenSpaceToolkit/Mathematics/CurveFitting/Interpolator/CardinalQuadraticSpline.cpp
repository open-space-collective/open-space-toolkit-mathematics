/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/CardinalQuadraticSpline.hpp>

namespace ostk
{
namespace mathematics
{
namespace curvefitting
{
namespace interpolator
{

CardinalQuadraticSpline::CardinalQuadraticSpline(const VectorXd& anXVector, const VectorXd& aYVector)
    : Interpolator(Interpolator::Type::CardinalQuadraticSpline),
      interpolator_(CardinalQuadraticSpline::BuildInterpolator(anXVector, aYVector))
{
}

CardinalQuadraticSpline::CardinalQuadraticSpline(const VectorXd& aYVector, const Real& x0, const Real& h)
    : Interpolator(Interpolator::Type::CardinalQuadraticSpline),
      interpolator_(CardinalQuadraticSpline::BuildInterpolator(aYVector, x0, h))
{
}

CardinalQuadraticSpline::~CardinalQuadraticSpline() {}

VectorXd CardinalQuadraticSpline::evaluate(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = interpolator_(aQueryVector(i));
    }

    return yOutput;
}

double CardinalQuadraticSpline::evaluate(const double& aQueryValue) const
{
    return interpolator_(aQueryValue);
}

double CardinalQuadraticSpline::computeDerivative(const double& aQueryValue) const
{
    return interpolator_.prime(aQueryValue);
}

VectorXd CardinalQuadraticSpline::computeDerivative(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = interpolator_.prime(aQueryVector(i));
    }

    return yOutput;
}

cardinal_quadratic_b_spline<double> CardinalQuadraticSpline::BuildInterpolator(
    const VectorXd& anXVector, const VectorXd& aYVector
)
{
    if (aYVector.size() < 3)
    {
        throw ostk::core::error::runtime::Wrong("y");
    }

    if (anXVector.size() != aYVector.size())
    {
        throw ostk::core::error::runtime::Wrong("x and y");
    }

    const double h = anXVector(1) - anXVector(0);

    const VectorXd diff = anXVector.segment(1, anXVector.size() - 1) - anXVector.segment(0, anXVector.size() - 1);

    if (!diff.isConstant(h, 1e-6))
    {
        throw ostk::core::error::runtime::Wrong("x must be uniformly spaced");
    }

    return CardinalQuadraticSpline::BuildInterpolator(aYVector, anXVector(0), h);
}

cardinal_quadratic_b_spline<double> CardinalQuadraticSpline::BuildInterpolator(
    const VectorXd& aYVector, const Real& x0, const Real& h
)
{
    if (aYVector.size() < 3)
    {
        throw ostk::core::error::runtime::Wrong("y");
    }

    if (h <= 0.0)
    {
        throw ostk::core::error::runtime::Wrong("h");
    }

    return cardinal_quadratic_b_spline<double>(std::vector<double>(aYVector.begin(), aYVector.end()), x0, h);
}

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk
