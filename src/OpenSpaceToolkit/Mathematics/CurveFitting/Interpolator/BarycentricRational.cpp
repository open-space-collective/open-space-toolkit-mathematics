/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/BarycentricRational.hpp>

namespace ostk
{
namespace mathematics
{
namespace curvefitting
{
namespace interpolator
{

BarycentricRational::BarycentricRational(const VectorXd& anXVector, const VectorXd& aYVector)
    : Interpolator(Interpolator::InterpolationType::BarycentricRational),
      interpolator_(anXVector.begin(), anXVector.end(), aYVector.begin())
{
    if (anXVector.size() != aYVector.size())
    {
        throw ostk::core::error::runtime::Wrong("Vector size", aYVector.size());
    }
}

BarycentricRational::~BarycentricRational() {}

VectorXd BarycentricRational::evaluate(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = interpolator_(aQueryVector(i));
    }

    return yOutput;
}

double BarycentricRational::evaluate(const double& aQueryValue) const
{
    return interpolator_(aQueryValue);
}

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk
