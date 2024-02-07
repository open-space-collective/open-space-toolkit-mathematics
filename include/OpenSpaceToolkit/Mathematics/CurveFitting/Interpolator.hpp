/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Interpolator__
#define __OpenSpaceToolkit_Mathematics_Interpolator__

#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>
#include <OpenSpaceToolkit/Core/Type/Unique.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

namespace ostk
{
namespace mathematics
{
namespace curvefitting
{

using ostk::core::type::Real;
using ostk::core::type::Size;
using ostk::core::type::Unique;

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

    /// @brief Generate an interpolator
    ///
    /// @param anInterpolationType Interpolation type
    /// @param anXVector A vector of x values
    /// @param aYVector A vector of y values
    /// @return Unique pointer to correct Interpolator
    static const Unique<const Interpolator> GenerateInterpolator(
        const InterpolationType& anInterpolationType, const VectorXd& anXVector, const VectorXd& aYVector
    );

   private:
    InterpolationType interpolationType_;
};

}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk

#endif
