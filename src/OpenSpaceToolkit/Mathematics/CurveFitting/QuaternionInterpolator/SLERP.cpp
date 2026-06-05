/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/QuaternionInterpolator/SLERP.hpp>

namespace ostk
{
namespace mathematics
{
namespace curvefitting
{
namespace quaternioninterpolator
{

SLERP::SLERP(const VectorXd& anXVector, const Array<Quaternion>& aQuaternionArray)
    : x_(anXVector),
      quaternions_()
{
    if (anXVector.size() < 2)
    {
        throw ostk::core::error::runtime::Wrong("x", "Insufficient data points.");
    }

    if (Size(anXVector.size()) != aQuaternionArray.getSize())
    {
        throw ostk::core::error::runtime::Wrong("x and quaternions", "Sizes are not consistent.");
    }

    // Check x is strictly monotonically increasing
    for (int i = 1; i < anXVector.size(); ++i)
    {
        if (anXVector(i) <= anXVector(i - 1))
        {
            throw ostk::core::error::runtime::Wrong("x", "Must be strictly monotonically increasing.");
        }
    }

    // Normalize quaternions
    quaternions_.reserve(aQuaternionArray.getSize());
    for (Size i = 0; i < aQuaternionArray.getSize(); ++i)
    {
        if (!aQuaternionArray[i].isDefined())
        {
            throw ostk::core::error::runtime::Undefined("Quaternion");
        }

        quaternions_.add(aQuaternionArray[i].toNormalized());
    }
}

SLERP::~SLERP() {}

Quaternion SLERP::evaluate(const double& aQueryValue) const
{
    const auto [previousIndex, nextIndex] = findIndexRange(aQueryValue);

    if (previousIndex == nextIndex)
    {
        return quaternions_[previousIndex];
    }

    const Real ratio = (aQueryValue - x_(previousIndex)) / (x_(nextIndex) - x_(previousIndex));

    return Quaternion::SLERP(quaternions_[previousIndex], quaternions_[nextIndex], ratio);
}

Array<Quaternion> SLERP::evaluate(const VectorXd& aQueryVector) const
{
    Array<Quaternion> results;
    results.reserve(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        results.add(evaluate(aQueryVector(i)));
    }

    return results;
}

Array<Quaternion> SLERP::getQuaternions() const
{
    return quaternions_;
}

Pair<Index, Index> SLERP::findIndexRange(const double& aQueryValue) const
{
    const Index index = std::distance(x_.begin(), std::lower_bound(x_.begin(), x_.end(), aQueryValue));

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

}  // namespace quaternioninterpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk
