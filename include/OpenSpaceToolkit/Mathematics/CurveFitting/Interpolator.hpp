/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Interpolator__
#define __OpenSpaceToolkit_Mathematics_Interpolator__

#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

namespace ostk
{
namespace mathematics
{
namespace curvefitting
{

using ostk::core::type::Real;
using ostk::core::type::Size;

using ostk::mathematics::object::VectorXd;

/// @brief Interpolator (abstract class)
///
/// In mathematics, an interpolator is a type of estimator allowing to construct new data
/// points based on a range of a discrete set of known data points.
///
/// @ref https://en.wikipedia.org/wiki/Interpolator.
class Interpolator
{
   public:
    enum class InterpolationType
    {
        Linear,
        BarycentricRational,
        CubicSpline
    };

    /// @brief Constructor
    Interpolator(const InterpolationType& anInterpolationType);

    /// @brief Destructor (pure virtual)
    virtual ~Interpolator() = 0;

    /// @brief Get the interpolation type
    /// @return Interpolation type
    InterpolationType getInterpolationType() const;

    /// @brief Evaluate the interpolator
    ///
    /// @param aQueryVector A vector of x values
    /// @return Vector of y values
    virtual VectorXd evaluate(const VectorXd& aQueryVector) const = 0;

    /// @brief Evaluate the interpolator
    ///
    /// @param aQueryValue An x value
    /// @return Vector of y values
    virtual double evaluate(const double& aQueryValue) const = 0;

   private:
    InterpolationType interpolationType_;
};

}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk

#endif
