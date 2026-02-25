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
        default:
            throw ostk::core::error::runtime::Wrong("Invalid interpolation type.");
    }
}

}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk
