/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/CardinalQuinticSpline.hpp>

namespace ostk
{
namespace mathematics
{
namespace curvefitting
{
namespace interpolator
{

CardinalQuinticSpline::CardinalQuinticSpline(const VectorXd& anXVector, const VectorXd& aYVector)
    : Interpolator(Interpolator::Type::CardinalQuinticSpline),
      interpolator_(CardinalQuinticSpline::BuildInterpolator(anXVector, aYVector))
{
}

CardinalQuinticSpline::CardinalQuinticSpline(const VectorXd& aYVector, const Real& x0, const Real& h)
    : Interpolator(Interpolator::Type::CardinalQuinticSpline),
      interpolator_(CardinalQuinticSpline::BuildInterpolator(aYVector, x0, h))
{
}

CardinalQuinticSpline::~CardinalQuinticSpline() {}

VectorXd CardinalQuinticSpline::evaluate(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = interpolator_(aQueryVector(i));
    }

    return yOutput;
}

double CardinalQuinticSpline::evaluate(const double& aQueryValue) const
{
    return interpolator_(aQueryValue);
}

double CardinalQuinticSpline::computeDerivative(const double& aQueryValue) const
{
    return interpolator_.prime(aQueryValue);
}

VectorXd CardinalQuinticSpline::computeDerivative(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = interpolator_.prime(aQueryVector(i));
    }

    return yOutput;
}

double CardinalQuinticSpline::computeSecondDerivative(const double& aQueryValue) const
{
    return interpolator_.double_prime(aQueryValue);
}

VectorXd CardinalQuinticSpline::computeSecondDerivative(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = interpolator_.double_prime(aQueryVector(i));
    }

    return yOutput;
}

cardinal_quintic_b_spline<double> CardinalQuinticSpline::BuildInterpolator(
    const VectorXd& anXVector, const VectorXd& aYVector
)
{
    if (aYVector.size() < 8)
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

    return CardinalQuinticSpline::BuildInterpolator(aYVector, anXVector(0), h);
}

cardinal_quintic_b_spline<double> CardinalQuinticSpline::BuildInterpolator(
    const VectorXd& aYVector, const Real& x0, const Real& h
)
{
    if (aYVector.size() < 8)
    {
        throw ostk::core::error::runtime::Wrong("y");
    }

    if (h <= 0.0)
    {
        throw ostk::core::error::runtime::Wrong("h");
    }

    return cardinal_quintic_b_spline<double>(std::vector<double>(aYVector.begin(), aYVector.end()), x0, h);
}

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk
