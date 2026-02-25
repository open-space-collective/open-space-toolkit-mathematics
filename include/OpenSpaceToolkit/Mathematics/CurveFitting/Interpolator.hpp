/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Interpolator__
#define __OpenSpaceToolkit_Mathematics_Interpolator__

#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

namespace ostk
{
namespace mathematics
{
namespace curvefitting
{

using ostk::core::type::Real;
using ostk::core::type::Shared;
using ostk::core::type::Size;

using ostk::mathematics::object::VectorXd;

/// @brief Interpolator (abstract class)
///
/// In mathematics, an interpolator is a type of estimator allowing to construct new data
/// points based on a range of a discrete set of known data points.
///
/// @code{.cpp}
///     auto interpolator = Interpolator::GenerateInterpolator(Interpolator::Type::Linear, x, y);
///     double value = interpolator->evaluate(1.5);
/// @endcode
///
/// @ref https://en.wikipedia.org/wiki/Interpolator.
class Interpolator
{
   public:
    enum class Type
    {
        BarycentricRational,
        CubicSpline,
        Linear,
        ZeroOrder
    };

    /// @brief Constructor (can only be called by derived classes since it is pure virtual)
    ///
    /// @code{.cpp}
    ///                     Interpolator interpolator(Interpolator::Type::Linear);
    /// @endcode
    ///
    /// @param aType Interpolation type
    Interpolator(const Type& aType);

    /// @brief Destructor (pure virtual)
    ///
    /// @code{.cpp}
    ///                     // Called automatically when the interpolator goes out of scope
    /// @endcode
    virtual ~Interpolator() = 0;

    /// @brief Get the interpolation type
    ///
    /// @code{.cpp}
    ///                     Interpolator::Type type = interpolator.getInterpolationType();
    /// @endcode
    ///
    /// @return Interpolation type
    Type getInterpolationType() const;

    /// @brief Evaluate the interpolator
    ///
    /// @code{.cpp}
    ///                     VectorXd values = interpolator.evaluate(queryVector);
    /// @endcode
    ///
    /// @param aQueryVector A vector of x values
    /// @return Vector of y values
    virtual VectorXd evaluate(const VectorXd& aQueryVector) const = 0;

    /// @brief Evaluate the interpolator
    ///
    /// @code{.cpp}
    ///                     double value = interpolator.evaluate(5.0);
    /// @endcode
    ///
    /// @param aQueryValue An x value
    /// @return Vector of y values
    virtual double evaluate(const double& aQueryValue) const = 0;

    /// @brief Get the derivative of the interpolator
    ///
    /// @code{.cpp}
    ///                     double derivative = interpolator.computeDerivative(5.0);
    /// @endcode
    ///
    /// @param aQueryValue An x value
    /// @return Derivative of the interpolator at the given x value
    virtual double computeDerivative(const double& aQueryValue) const = 0;

    /// @brief Get the derivative of the interpolator
    ///
    /// @code{.cpp}
    ///                     VectorXd derivatives = interpolator.computeDerivative(queryVector);
    /// @endcode
    ///
    /// @param aQueryVector A vector of x values
    /// @return Vector of derivatives of the interpolator at the given x values
    virtual VectorXd computeDerivative(const VectorXd& aQueryVector) const = 0;

    /// @brief Generate an interpolator
    ///
    /// @code{.cpp}
    ///                     auto interpolator = Interpolator::GenerateInterpolator(Interpolator::Type::Linear, x, y);
    /// @endcode
    ///
    /// @param aType Interpolation type
    /// @param anXVector A vector of x values
    /// @param aYVector A vector of y values
    /// @return Shared pointer to correct Interpolator
    static const Shared<const Interpolator> GenerateInterpolator(
        const Type& aType, const VectorXd& anXVector, const VectorXd& aYVector
    );

   private:
    const Type type_;
};

}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk

#endif
