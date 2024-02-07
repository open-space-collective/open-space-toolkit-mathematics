/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/Linear.hpp>

namespace ostk
{
namespace mathematics
{
namespace curvefitting
{
namespace interpolator
{

Linear::Linear(const VectorXd& anXVector, const VectorXd& aYVector)
    : Interpolator(Interpolator::InterpolationType::Linear),
      x_(anXVector),
      y_(aYVector)
{
    if (aYVector.size() < 2)
    {
        throw ostk::core::error::runtime::Wrong("y");
    }

    if (anXVector.size() != aYVector.size())
    {
        throw ostk::core::error::runtime::Wrong("x and y");
    }
}

Linear::~Linear() {}

VectorXd Linear::evaluate(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = evaluate(aQueryVector(i));
    }

    return yOutput;
}

double Linear::evaluate(const double& aQueryValue) const
{
    using ostk::core::container::Unpack;

    Index previousIndex;
    Index nextIndex;

    Unpack(previousIndex, nextIndex) = findIndexRange(aQueryValue);

    if (previousIndex == nextIndex)
    {
        return y_(previousIndex);
    }

    const double previousY = y_(previousIndex);
    const double nextY = y_(nextIndex);

    const Real Ratio = (aQueryValue - x_(previousIndex)) / (x_(nextIndex) - x_(previousIndex));

    return previousY + Ratio * (nextY - previousY);
}

Pair<Index, Index> Linear::findIndexRange(const double& aQueryValue) const
{
    Index index = std::distance(x_.begin(), std::lower_bound(x_.begin(), x_.end(), aQueryValue));

    if (index == 0)
    {
        return {0, 0};
    }

    if (index == Index(x_.size()))
    {
        return {index - 1, index - 1};
    }

    return {index - 1, index};
}

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk
