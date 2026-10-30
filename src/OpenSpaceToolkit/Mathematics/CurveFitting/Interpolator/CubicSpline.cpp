/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/CubicSpline.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/NonUniformBasisSpline.hpp>

namespace ostk
{
namespace mathematics
{
namespace curvefitting
{
namespace interpolator
{

CubicSpline::CubicSpline(const VectorXd& anXVector, const VectorXd& aYVector)
    : Interpolator(Interpolator::Type::CubicSpline)
{
    if (aYVector.size() < 5)
    {
        throw ostk::core::error::runtime::Wrong("y");
    }

    if (anXVector.size() != aYVector.size())
    {
        throw ostk::core::error::runtime::Wrong("x and y");
    }

    if (Interpolator::IsUniformlySpaced(anXVector))
    {
        const Size size = anXVector.size();

        const double h = (anXVector(size - 1) - anXVector(0)) / double(size - 1);

        cardinalInterpolator_.emplace(aYVector.begin(), aYVector.end(), anXVector(0), h);
    }
    else
    {
        interpolator_ = std::make_shared<const NonUniformBasisSpline>(
            // Extrapolate outside of the interpolation domain to match the behaviour of Boost's
            // cardinal_cubic_b_spline, which the uniformly spaced path above uses
            NonUniformBasisSpline::GenerateInterpolator(
                anXVector, aYVector, 3, NonUniformBasisSpline::DomainBehavior::Extrapolate
            )
        );
    }
}

CubicSpline::CubicSpline(const VectorXd& aYVector, const Real& x0, const Real& h)
    : Interpolator(Interpolator::Type::CubicSpline)
{
    if (aYVector.size() < 5)
    {
        throw ostk::core::error::runtime::Wrong("y");
    }

    if (h <= 0.0)
    {
        throw ostk::core::error::runtime::Wrong("h");
    }

    cardinalInterpolator_.emplace(aYVector.begin(), aYVector.end(), x0, h);
}

CubicSpline::~CubicSpline() {}

VectorXd CubicSpline::evaluate(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = this->evaluate(aQueryVector(i));
    }

    return yOutput;
}

double CubicSpline::evaluate(const double& aQueryValue) const
{
    return cardinalInterpolator_.has_value() ? (*cardinalInterpolator_)(aQueryValue)
                                             : interpolator_->evaluate(aQueryValue);
}

double CubicSpline::computeDerivative(const double& aQueryValue) const
{
    return cardinalInterpolator_.has_value() ? cardinalInterpolator_->prime(aQueryValue)
                                             : interpolator_->computeDerivative(aQueryValue);
}

VectorXd CubicSpline::computeDerivative(const VectorXd& aQueryVector) const
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
