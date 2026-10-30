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
    : Interpolator(Interpolator::Type::CubicHermite)
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

    if (Interpolator::IsUniformlySpaced(anXVector))
    {
        const Size size = anXVector.size();

        const double h = (anXVector(size - 1) - anXVector(0)) / double(size - 1);

        cardinalInterpolator_.emplace(
            std::vector<double>(aYVector.begin(), aYVector.end()),
            std::vector<double>(aDyDxVector.begin(), aDyDxVector.end()),
            anXVector(0),
            h
        );
    }
    else
    {
        interpolator_.emplace(
            std::vector<double>(anXVector.begin(), anXVector.end()),
            std::vector<double>(aYVector.begin(), aYVector.end()),
            std::vector<double>(aDyDxVector.begin(), aDyDxVector.end())
        );
    }
}

CubicHermite::CubicHermite(const VectorXd& aYVector, const VectorXd& aDyDxVector, const Real& x0, const Real& h)
    : Interpolator(Interpolator::Type::CubicHermite)
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

    cardinalInterpolator_.emplace(
        std::vector<double>(aYVector.begin(), aYVector.end()),
        std::vector<double>(aDyDxVector.begin(), aDyDxVector.end()),
        x0,
        h
    );
}

CubicHermite::~CubicHermite() {}

VectorXd CubicHermite::evaluate(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = this->evaluate(aQueryVector(i));
    }

    return yOutput;
}

double CubicHermite::evaluate(const double& aQueryValue) const
{
    return cardinalInterpolator_.has_value() ? (*cardinalInterpolator_)(aQueryValue) : (*interpolator_)(aQueryValue);
}

double CubicHermite::computeDerivative(const double& aQueryValue) const
{
    return cardinalInterpolator_.has_value() ? cardinalInterpolator_->prime(aQueryValue)
                                             : interpolator_->prime(aQueryValue);
}

VectorXd CubicHermite::computeDerivative(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = this->computeDerivative(aQueryVector(i));
    }

    return yOutput;
}

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk
