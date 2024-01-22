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

Interpolator::~Interpolator() {}

double Interpolator::evaluate(const double& aQueryValue) const
{
    using ostk::mathematics::curvefitting::interpolator::CubicSpline;
    using ostk::mathematics::curvefitting::interpolator::BarycentricRational;

    if (const CubicSpline* interpolatorPtr = dynamic_cast<const CubicSpline*>(this))
    {
        return interpolatorPtr->evaluate(aQueryValue);
    }

    if (const BarycentricRational* interpolatorPtr = dynamic_cast<const BarycentricRational*>(this))
    {
        return interpolatorPtr->evaluate(aQueryValue);
    }

    throw ostk::core::error::runtime::ToBeImplemented("Interpolator :: evaluate");

    return 0.0;
}

VectorXd Interpolator::evaluate(const VectorXd& aQueryVector) const
{
    using ostk::mathematics::curvefitting::interpolator::CubicSpline;
    using ostk::mathematics::curvefitting::interpolator::BarycentricRational;

    if (const CubicSpline* interpolatorPtr = dynamic_cast<const CubicSpline*>(this))
    {
        return interpolatorPtr->evaluate(aQueryVector);
    }

    if (const BarycentricRational* interpolatorPtr = dynamic_cast<const BarycentricRational*>(this))
    {
        return interpolatorPtr->evaluate(aQueryVector);
    }

    throw ostk::core::error::runtime::ToBeImplemented("Interpolator :: evaluate");

    return VectorXd::Zero(aQueryVector.size());
}

}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk
