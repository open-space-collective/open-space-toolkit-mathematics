/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/NonUniformBSpline.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/QuadraticSpline.hpp>

namespace ostk
{
namespace mathematics
{
namespace curvefitting
{
namespace interpolator
{

QuadraticSpline::QuadraticSpline(const VectorXd& anXVector, const VectorXd& aYVector)
    : Interpolator(Interpolator::Type::QuadraticSpline)
{
    if (aYVector.size() < 3)
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

        cardinalInterpolator_.emplace(std::vector<double>(aYVector.begin(), aYVector.end()), anXVector(0), h);
    }
    else
    {
        interpolator_ = std::make_shared<const NonUniformBSpline>(
            NonUniformBSpline::Interpolate(anXVector, aYVector, 2, NonUniformBSpline::DomainBehavior::Throw)
        );
    }
}

QuadraticSpline::QuadraticSpline(const VectorXd& aYVector, const Real& x0, const Real& h)
    : Interpolator(Interpolator::Type::QuadraticSpline)
{
    if (aYVector.size() < 3)
    {
        throw ostk::core::error::runtime::Wrong("y");
    }

    if (h <= 0.0)
    {
        throw ostk::core::error::runtime::Wrong("h");
    }

    cardinalInterpolator_.emplace(std::vector<double>(aYVector.begin(), aYVector.end()), x0, h);
}

QuadraticSpline::~QuadraticSpline() {}

VectorXd QuadraticSpline::evaluate(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = this->evaluate(aQueryVector(i));
    }

    return yOutput;
}

double QuadraticSpline::evaluate(const double& aQueryValue) const
{
    return cardinalInterpolator_.has_value() ? (*cardinalInterpolator_)(aQueryValue)
                                             : interpolator_->evaluate(aQueryValue);
}

double QuadraticSpline::computeDerivative(const double& aQueryValue) const
{
    return cardinalInterpolator_.has_value() ? cardinalInterpolator_->prime(aQueryValue)
                                             : interpolator_->computeDerivative(aQueryValue);
}

VectorXd QuadraticSpline::computeDerivative(const VectorXd& aQueryVector) const
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
