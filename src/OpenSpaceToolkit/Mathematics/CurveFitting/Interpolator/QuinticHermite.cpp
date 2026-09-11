/// Apache License 2.0

#include <boost/version.hpp>

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
    : Interpolator(Interpolator::Type::QuinticHermite)
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

    if (Interpolator::IsUniformlySpaced(anXVector))
    {
        const Size size = anXVector.size();

        const double h = (anXVector(size - 1) - anXVector(0)) / double(size - 1);

        cardinalInterpolator_.emplace(
            std::vector<double>(aYVector.begin(), aYVector.end()),
            std::vector<double>(aDyDxVector.begin(), aDyDxVector.end()),
            std::vector<double>(aD2yDx2Vector.begin(), aD2yDx2Vector.end()),
            anXVector(0),
            h
        );
    }
    else
    {
        interpolator_.emplace(
            std::vector<double>(anXVector.begin(), anXVector.end()),
            std::vector<double>(aYVector.begin(), aYVector.end()),
            std::vector<double>(aDyDxVector.begin(), aDyDxVector.end()),
            std::vector<double>(aD2yDx2Vector.begin(), aD2yDx2Vector.end())
        );
    }
}

QuinticHermite::QuinticHermite(
    const VectorXd& aYVector, const VectorXd& aDyDxVector, const VectorXd& aD2yDx2Vector, const Real& x0, const Real& h
)
    : Interpolator(Interpolator::Type::QuinticHermite)
{
    if (aYVector.size() < 2)
    {
        throw ostk::core::error::runtime::Wrong("y");
    }

    if (aDyDxVector.size() != aYVector.size())
    {
        throw ostk::core::error::runtime::Wrong("y and dydx");
    }

    if (aD2yDx2Vector.size() != aYVector.size())
    {
        throw ostk::core::error::runtime::Wrong("y and d2ydx2");
    }

    if (h <= 0.0)
    {
        throw ostk::core::error::runtime::Wrong("h");
    }

    cardinalInterpolator_.emplace(
        std::vector<double>(aYVector.begin(), aYVector.end()),
        std::vector<double>(aDyDxVector.begin(), aDyDxVector.end()),
        std::vector<double>(aD2yDx2Vector.begin(), aD2yDx2Vector.end()),
        x0,
        h
    );
}

QuinticHermite::~QuinticHermite() {}

VectorXd QuinticHermite::evaluate(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = this->evaluate(aQueryVector(i));
    }

    return yOutput;
}

double QuinticHermite::evaluate(const double& aQueryValue) const
{
    return cardinalInterpolator_.has_value() ? (*cardinalInterpolator_)(aQueryValue) : (*interpolator_)(aQueryValue);
}

double QuinticHermite::computeDerivative(const double& aQueryValue) const
{
    return cardinalInterpolator_.has_value() ? cardinalInterpolator_->prime(aQueryValue)
                                             : interpolator_->prime(aQueryValue);
}

VectorXd QuinticHermite::computeDerivative(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = this->computeDerivative(aQueryVector(i));
    }

    return yOutput;
}

double QuinticHermite::computeSecondDerivative(const double& aQueryValue) const
{
    if (cardinalInterpolator_.has_value())
    {
#if BOOST_VERSION < 109300
        throw ostk::core::error::RuntimeError(
            "The second derivative of a quintic Hermite interpolator with uniformly spaced nodes is only available "
            "with Boost 1.93 or later: boost::math::interpolators::cardinal_quintic_hermite::double_prime is wrong "
            "for a spacing other than 1 in earlier versions."
        );
#else
        return cardinalInterpolator_->double_prime(aQueryValue);
#endif
    }

    return interpolator_->double_prime(aQueryValue);
}

VectorXd QuinticHermite::computeSecondDerivative(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = this->computeSecondDerivative(aQueryVector(i));
    }

    return yOutput;
}

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk
