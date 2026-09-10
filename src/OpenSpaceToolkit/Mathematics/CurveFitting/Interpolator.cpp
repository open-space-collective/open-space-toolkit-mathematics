/// Apache License 2.0

#include <algorithm>
#include <cmath>
#include <limits>

#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/BarycentricRational.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/CubicSpline.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/Linear.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/QuadraticSpline.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/QuinticSpline.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/ZeroOrder.hpp>

namespace ostk
{
namespace mathematics
{
namespace curvefitting
{

using ostk::mathematics::curvefitting::interpolator::BarycentricRational;
using ostk::mathematics::curvefitting::interpolator::CubicSpline;
using ostk::mathematics::curvefitting::interpolator::Linear;
using ostk::mathematics::curvefitting::interpolator::QuadraticSpline;
using ostk::mathematics::curvefitting::interpolator::QuinticSpline;
using ostk::mathematics::curvefitting::interpolator::ZeroOrder;

Interpolator::Interpolator(const Type& aType)
    : type_(aType)
{
}

Interpolator::~Interpolator() {}

Interpolator::Type Interpolator::getInterpolationType() const
{
    return type_;
}

const Shared<const Interpolator> Interpolator::GenerateInterpolator(
    const Type& aType, const VectorXd& anXVector, const VectorXd& aYVector
)
{
    switch (aType)
    {
        case Type::BarycentricRational:
            return std::make_shared<BarycentricRational>(anXVector, aYVector);
        case Type::CubicSpline:
            return std::make_shared<CubicSpline>(anXVector, aYVector);
        case Type::Linear:
            return std::make_shared<Linear>(anXVector, aYVector);
        case Type::ZeroOrder:
            return std::make_shared<ZeroOrder>(anXVector, aYVector);
        case Type::QuadraticSpline:
            return std::make_shared<QuadraticSpline>(anXVector, aYVector);
        case Type::QuinticSpline:
            return std::make_shared<QuinticSpline>(anXVector, aYVector);
        case Type::CubicHermite:
        case Type::QuinticHermite:
            throw ostk::core::error::RuntimeError(
                "Hermite interpolators require derivative data, and cannot be generated from x and y only."
            );
        default:
            throw ostk::core::error::runtime::Wrong("Invalid interpolation type.");
    }
}

bool Interpolator::IsUniformlySpaced(const VectorXd& anXVector)
{
    const Size size = anXVector.size();

    if (size < 3)
    {
        return true;
    }

    const double x0 = anXVector(0);
    const double span = anXVector(size - 1) - x0;

    if (span <= 0.0)
    {
        return false;
    }

    const double h = span / double(size - 1);

    // The x values are only known to within their own representation error, which for large
    // magnitudes can be coarser than any fixed fraction of the spacing, so allow for both.

    const double maximumMagnitude = std::max(std::abs(x0), std::abs(anXVector(size - 1)));

    const double tolerance = 1e-10 * span + 8.0 * std::numeric_limits<double>::epsilon() * maximumMagnitude;

    for (Size i = 1; i < size - 1; ++i)
    {
        if (std::abs(anXVector(i) - (x0 + double(i) * h)) > tolerance)
        {
            return false;
        }
    }

    return true;
}

}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk
