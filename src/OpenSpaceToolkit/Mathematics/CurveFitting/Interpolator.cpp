/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/BarycentricRational.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/CubicSpline.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/Linear.hpp>

namespace ostk
{
namespace mathematics
{
namespace curvefitting
{

using ostk::mathematics::curvefitting::interpolator::BarycentricRational;
using ostk::mathematics::curvefitting::interpolator::CubicSpline;
using ostk::mathematics::curvefitting::interpolator::Linear;

Interpolator::Interpolator(const InterpolationType& anInterpolationType)
    : interpolationType_(anInterpolationType)
{
}

Interpolator::~Interpolator() {}

Interpolator::InterpolationType Interpolator::getInterpolationType() const
{
    return interpolationType_;
}

const Unique<const Interpolator> Interpolator::GenerateInterpolator(
    const InterpolationType& anInterpolationType, const VectorXd& anXVector, const VectorXd& aYVector
)
{
    switch (anInterpolationType)
    {
        case InterpolationType::Linear:
            return std::make_unique<Linear>(anXVector, aYVector);
        case InterpolationType::BarycentricRational:
            return std::make_unique<BarycentricRational>(anXVector, aYVector);
        case InterpolationType::CubicSpline:
            return std::make_unique<CubicSpline>(anXVector, aYVector);
        default:
            throw ostk::core::error::runtime::Wrong("Invalid interpolation type.");
    }
}

}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk
