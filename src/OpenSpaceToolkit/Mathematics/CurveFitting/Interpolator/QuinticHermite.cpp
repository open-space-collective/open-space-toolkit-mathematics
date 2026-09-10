/// Apache License 2.0

#include <algorithm>
#include <limits>
#include <sstream>
#include <stdexcept>

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
      x0_(0.0),
      h_(0.0),
      size_(aYVector.size())
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

        this->initializeCardinalInterpolator(aYVector, aDyDxVector, aD2yDx2Vector, anXVector(0), h);
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
    : Interpolator(Interpolator::Type::QuinticHermite),
      x0_(0.0),
      h_(0.0),
      size_(aYVector.size())
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

    this->initializeCardinalInterpolator(aYVector, aDyDxVector, aD2yDx2Vector, x0, h);
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
    return cardinalInterpolator_.has_value() ? (*cardinalInterpolator_)(this->normalizeQueryValue(aQueryValue))
                                             : (*interpolator_)(aQueryValue);
}

double QuinticHermite::computeDerivative(const double& aQueryValue) const
{
    return cardinalInterpolator_.has_value() ? cardinalInterpolator_->prime(this->normalizeQueryValue(aQueryValue)) / h_
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
    return cardinalInterpolator_.has_value()
             ? cardinalInterpolator_->double_prime(this->normalizeQueryValue(aQueryValue)) / (h_ * h_)
             : interpolator_->double_prime(aQueryValue);
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

void QuinticHermite::initializeCardinalInterpolator(
    const VectorXd& aYVector, const VectorXd& aDyDxVector, const VectorXd& aD2yDx2Vector, const Real& x0, const Real& h
)
{
    x0_ = x0;
    h_ = h;

    // Scale the derivatives with respect to the normalized abscissa s = (x - x0) / h

    std::vector<double> scaledDyDx(aDyDxVector.size());
    std::vector<double> scaledD2yDx2(aD2yDx2Vector.size());

    for (int i = 0; i < aYVector.size(); ++i)
    {
        scaledDyDx[i] = aDyDxVector(i) * h_;
        scaledD2yDx2[i] = aD2yDx2Vector(i) * h_ * h_;
    }

    cardinalInterpolator_.emplace(
        std::vector<double>(aYVector.begin(), aYVector.end()), std::move(scaledDyDx), std::move(scaledD2yDx2), 0.0, 1.0
    );
}

double QuinticHermite::normalizeQueryValue(const double& aQueryValue) const
{
    const double sf = double(size_) - 1.0;
    const double xf = x0_ + sf * h_;

    if ((aQueryValue < x0_) || (aQueryValue > xf))
    {
        std::ostringstream oss;

        oss.precision(std::numeric_limits<double>::digits10 + 3);
        oss << "Requested abscissa x = " << aQueryValue << ", which is outside of allowed range [" << x0_ << ", " << xf
            << "]";

        throw std::domain_error(oss.str());
    }

    // Guard against the normalized value falling marginally outside of [0, size - 1] due to rounding

    return std::min(std::max((aQueryValue - x0_) / h_, 0.0), sf);
}

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk
