/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/QuinticHermite.hpp>

namespace ostk
{
namespace mathematics
{
namespace curvefitting
{
namespace interpolator
{

QuinticHermite::QuinticHermite(
    const VectorXd& anXVector, const VectorXd& aYVector, const VectorXd& aDyDxVector, const VectorXd& aD2yDx2Vector
)
    : Interpolator(Interpolator::Type::QuinticHermite),
      interpolator_(QuinticHermite::BuildInterpolator(anXVector, aYVector, aDyDxVector, aD2yDx2Vector))
{
}

QuinticHermite::~QuinticHermite() {}

VectorXd QuinticHermite::evaluate(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = interpolator_(aQueryVector(i));
    }

    return yOutput;
}

double QuinticHermite::evaluate(const double& aQueryValue) const
{
    return interpolator_(aQueryValue);
}

double QuinticHermite::computeDerivative(const double& aQueryValue) const
{
    return interpolator_.prime(aQueryValue);
}

VectorXd QuinticHermite::computeDerivative(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = interpolator_.prime(aQueryVector(i));
    }

    return yOutput;
}

double QuinticHermite::computeSecondDerivative(const double& aQueryValue) const
{
    return interpolator_.double_prime(aQueryValue);
}

VectorXd QuinticHermite::computeSecondDerivative(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = interpolator_.double_prime(aQueryVector(i));
    }

    return yOutput;
}

quintic_hermite<std::vector<double>> QuinticHermite::BuildInterpolator(
    const VectorXd& anXVector, const VectorXd& aYVector, const VectorXd& aDyDxVector, const VectorXd& aD2yDx2Vector
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

    if (aDyDxVector.size() != aYVector.size())
    {
        throw ostk::core::error::runtime::Wrong("y and dydx");
    }

    if (aD2yDx2Vector.size() != aYVector.size())
    {
        throw ostk::core::error::runtime::Wrong("y and d2ydx2");
    }

    return quintic_hermite<std::vector<double>>(
        std::vector<double>(anXVector.begin(), anXVector.end()),
        std::vector<double>(aYVector.begin(), aYVector.end()),
        std::vector<double>(aDyDxVector.begin(), aDyDxVector.end()),
        std::vector<double>(aD2yDx2Vector.begin(), aD2yDx2Vector.end())
    );
}

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk
