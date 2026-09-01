/// Apache License 2.0

#include <algorithm>
#include <limits>
#include <sstream>
#include <stdexcept>

#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/CardinalQuinticHermite.hpp>

namespace ostk
{
namespace mathematics
{
namespace curvefitting
{
namespace interpolator
{

CardinalQuinticHermite::CardinalQuinticHermite(
    const VectorXd& anXVector, const VectorXd& aYVector, const VectorXd& aDyDxVector, const VectorXd& aD2yDx2Vector
)
    : Interpolator(Interpolator::Type::CardinalQuinticHermite),
      interpolator_(CardinalQuinticHermite::BuildInterpolator(anXVector, aYVector, aDyDxVector, aD2yDx2Vector)),
      x0_(anXVector(0)),
      h_(anXVector(1) - anXVector(0)),
      size_(aYVector.size())
{
}

CardinalQuinticHermite::CardinalQuinticHermite(
    const VectorXd& aYVector, const VectorXd& aDyDxVector, const VectorXd& aD2yDx2Vector, const Real& x0, const Real& h
)
    : Interpolator(Interpolator::Type::CardinalQuinticHermite),
      interpolator_(CardinalQuinticHermite::BuildInterpolator(aYVector, aDyDxVector, aD2yDx2Vector, h)),
      x0_(x0),
      h_(h),
      size_(aYVector.size())
{
}

CardinalQuinticHermite::~CardinalQuinticHermite() {}

VectorXd CardinalQuinticHermite::evaluate(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = evaluate(aQueryVector(i));
    }

    return yOutput;
}

double CardinalQuinticHermite::evaluate(const double& aQueryValue) const
{
    return interpolator_(normalizeQueryValue(aQueryValue));
}

double CardinalQuinticHermite::computeDerivative(const double& aQueryValue) const
{
    return interpolator_.prime(normalizeQueryValue(aQueryValue)) / h_;
}

VectorXd CardinalQuinticHermite::computeDerivative(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = computeDerivative(aQueryVector(i));
    }

    return yOutput;
}

double CardinalQuinticHermite::computeSecondDerivative(const double& aQueryValue) const
{
    return interpolator_.double_prime(normalizeQueryValue(aQueryValue)) / (h_ * h_);
}

VectorXd CardinalQuinticHermite::computeSecondDerivative(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = computeSecondDerivative(aQueryVector(i));
    }

    return yOutput;
}

double CardinalQuinticHermite::normalizeQueryValue(const double& aQueryValue) const
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

cardinal_quintic_hermite<std::vector<double>> CardinalQuinticHermite::BuildInterpolator(
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

    const double h = anXVector(1) - anXVector(0);

    const VectorXd diff = anXVector.segment(1, anXVector.size() - 1) - anXVector.segment(0, anXVector.size() - 1);

    if (!diff.isConstant(h, 1e-6))
    {
        throw ostk::core::error::runtime::Wrong("x must be uniformly spaced");
    }

    return CardinalQuinticHermite::BuildInterpolator(aYVector, aDyDxVector, aD2yDx2Vector, h);
}

cardinal_quintic_hermite<std::vector<double>> CardinalQuinticHermite::BuildInterpolator(
    const VectorXd& aYVector, const VectorXd& aDyDxVector, const VectorXd& aD2yDx2Vector, const Real& h
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

    if (aD2yDx2Vector.size() != aYVector.size())
    {
        throw ostk::core::error::runtime::Wrong("y and d2ydx2");
    }

    if (h <= 0.0)
    {
        throw ostk::core::error::runtime::Wrong("h");
    }

    // Scale the derivatives with respect to the normalized abscissa s = (x - x0) / h

    const double hValue = h;

    std::vector<double> scaledDyDx(aDyDxVector.size());
    std::vector<double> scaledD2yDx2(aD2yDx2Vector.size());

    for (int i = 0; i < aYVector.size(); ++i)
    {
        scaledDyDx[i] = aDyDxVector(i) * hValue;
        scaledD2yDx2[i] = aD2yDx2Vector(i) * hValue * hValue;
    }

    return cardinal_quintic_hermite<std::vector<double>>(
        std::vector<double>(aYVector.begin(), aYVector.end()), std::move(scaledDyDx), std::move(scaledD2yDx2), 0.0, 1.0
    );
}

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk
