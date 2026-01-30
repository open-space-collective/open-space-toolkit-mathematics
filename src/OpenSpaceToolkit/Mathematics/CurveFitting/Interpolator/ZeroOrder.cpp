/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/ZeroOrder.hpp>

namespace ostk
{
namespace mathematics
{
namespace curvefitting
{
namespace interpolator
{

ZeroOrder::ZeroOrder(const VectorXd& anXVector, const VectorXd& aYVector)
    : Interpolator(Interpolator::Type::ZeroOrder),
      x_(anXVector),
      y_(aYVector)
{
    if (aYVector.size() < 1)
    {
        throw ostk::core::error::runtime::Wrong("y");
    }

    if (anXVector.size() != aYVector.size())
    {
        throw ostk::core::error::runtime::Wrong("x and y");
    }
}

ZeroOrder::~ZeroOrder() {}

VectorXd ZeroOrder::evaluate(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = evaluate(aQueryVector(i));
    }

    return yOutput;
}

double ZeroOrder::evaluate(const double& aQueryValue) const
{
    const Index previousIndex = findPreviousIndex(aQueryValue);
    return y_(previousIndex);
}

double ZeroOrder::computeDerivative(const double& aQueryValue) const
{
    (void)aQueryValue;  // Unused - derivative is always 0 for step function
    return 0.0;
}

VectorXd ZeroOrder::computeDerivative(const VectorXd& aQueryVector) const
{
    return VectorXd::Zero(aQueryVector.size());
}

Index ZeroOrder::findPreviousIndex(const double& aQueryValue) const
{
    // Find first element greater than aQueryValue
    Index index = std::distance(x_.begin(), std::upper_bound(x_.begin(), x_.end(), aQueryValue));

    // If all elements are greater than aQueryValue, return first element
    if (index == 0)
    {
        return 0;
    }

    // Return the index of the element just before the one found
    return index - 1;
}

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk
