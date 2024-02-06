/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/BarycentricRational.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/CubicSpline.hpp>

namespace ostk
{
namespace mathematics
{
namespace curvefitting
{

Interpolator::Interpolator(const InterpolationType& anInterpolationType)
    : interpolationType_(anInterpolationType)
{
}

Interpolator::~Interpolator() {}

Interpolator::InterpolationType Interpolator::getInterpolationType() const
{
    return interpolationType_;
}

}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk
