/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/CubicHermite.hpp>

namespace ostk
{
namespace mathematics
{
namespace curvefitting
{
namespace interpolator
{

CubicHermite::CubicHermite(const VectorXd& anXVector, const VectorXd& aYVector, const VectorXd& aDyDxVector)
    : Interpolator(Interpolator::Type::CubicHermite),
      interpolator_(CubicHermite::BuildInterpolator(anXVector, aYVector, aDyDxVector))
{
}

CubicHermite::~CubicHermite() {}

VectorXd CubicHermite::evaluate(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = interpolator_(aQueryVector(i));
    }

    return yOutput;
}

double CubicHermite::evaluate(const double& aQueryValue) const
{
    return interpolator_(aQueryValue);
}

double CubicHermite::computeDerivative(const double& aQueryValue) const
{
    return interpolator_.prime(aQueryValue);
}

VectorXd CubicHermite::computeDerivative(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = interpolator_.prime(aQueryVector(i));
    }

    return yOutput;
}

cubic_hermite<std::vector<double>> CubicHermite::BuildInterpolator(
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

    if (aDyDxVector.size() != aYVector.size())
    {
        throw ostk::core::error::runtime::Wrong("y and dydx");
    }

    return cubic_hermite<std::vector<double>>(
        std::vector<double>(anXVector.begin(), anXVector.end()),
        std::vector<double>(aYVector.begin(), aYVector.end()),
        std::vector<double>(aDyDxVector.begin(), aDyDxVector.end())
    );
}

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk
