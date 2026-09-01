/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/CardinalCubicHermite.hpp>

namespace ostk
{
namespace mathematics
{
namespace curvefitting
{
namespace interpolator
{

CardinalCubicHermite::CardinalCubicHermite(
    const VectorXd& anXVector, const VectorXd& aYVector, const VectorXd& aDyDxVector
)
    : Interpolator(Interpolator::Type::CardinalCubicHermite),
      interpolator_(CardinalCubicHermite::BuildInterpolator(anXVector, aYVector, aDyDxVector))
{
}

CardinalCubicHermite::CardinalCubicHermite(
    const VectorXd& aYVector, const VectorXd& aDyDxVector, const Real& x0, const Real& h
)
    : Interpolator(Interpolator::Type::CardinalCubicHermite),
      interpolator_(CardinalCubicHermite::BuildInterpolator(aYVector, aDyDxVector, x0, h))
{
}

CardinalCubicHermite::~CardinalCubicHermite() {}

VectorXd CardinalCubicHermite::evaluate(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = interpolator_(aQueryVector(i));
    }

    return yOutput;
}

double CardinalCubicHermite::evaluate(const double& aQueryValue) const
{
    return interpolator_(aQueryValue);
}

double CardinalCubicHermite::computeDerivative(const double& aQueryValue) const
{
    return interpolator_.prime(aQueryValue);
}

VectorXd CardinalCubicHermite::computeDerivative(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = interpolator_.prime(aQueryVector(i));
    }

    return yOutput;
}

cardinal_cubic_hermite<std::vector<double>> CardinalCubicHermite::BuildInterpolator(
    const VectorXd& anXVector, const VectorXd& aYVector, const VectorXd& aDyDxVector
)
{
    if (aYVector.size() < 2)
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

    return CardinalCubicHermite::BuildInterpolator(aYVector, aDyDxVector, anXVector(0), h);
}

cardinal_cubic_hermite<std::vector<double>> CardinalCubicHermite::BuildInterpolator(
    const VectorXd& aYVector, const VectorXd& aDyDxVector, const Real& x0, const Real& h
)
{
    if (aYVector.size() < 2)
    {
        throw ostk::core::error::runtime::Wrong("y");
    }

    if (aDyDxVector.size() != aYVector.size())
    {
        throw ostk::core::error::runtime::Wrong("y and dydx");
    }

    if (h <= 0.0)
    {
        throw ostk::core::error::runtime::Wrong("h");
    }

    return cardinal_cubic_hermite<std::vector<double>>(
        std::vector<double>(aYVector.begin(), aYVector.end()),
        std::vector<double>(aDyDxVector.begin(), aDyDxVector.end()),
        x0,
        h
    );
}

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk
