/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Interpolator_ZeroOrder__
#define __OpenSpaceToolkit_Mathematics_Interpolator_ZeroOrder__

#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

namespace ostk
{
namespace mathematics
{
namespace curvefitting
{
namespace interpolator
{

using ostk::core::type::Index;
using ostk::core::type::Real;
using ostk::core::type::Size;

using ostk::mathematics::curvefitting::Interpolator;
using ostk::mathematics::object::VectorXd;

/// @brief                      Zero-Order Hold Interpolator
///
///                             A step interpolator that returns the value of the previous data point.
///                             For any query value x, it returns the y value of the largest data point
///                             x_i where x_i <= x. Also known as "zero-order hold" or "step" interpolation.
///
/// @ref                        https://en.wikipedia.org/wiki/Zero-order_hold

class ZeroOrder : public Interpolator
{
   public:
    /// @brief Constructor
    ///
    /// @code{.cpp}
    ///                     ZeroOrder zeroOrder(x, y);
    /// @endcode
    ///
    /// @param anXVector A vector of x values
    /// @param aYVector A vector of y values
    ///
    /// @warning The x values must be sorted in ascending order
    ZeroOrder(const VectorXd& anXVector, const VectorXd& aYVector);

    /// @brief Destructor
    virtual ~ZeroOrder() override;

    /// @brief Evaluate the zero-order hold interpolator
    ///
    /// @code{.cpp}
    ///                     VectorXd values = zeroOrder.evaluate({1.0, 5.0, 6.0}) ;
    /// @endcode
    ///
    /// @param aQueryVector A vector of x values
    /// @return Vector of y values
    virtual VectorXd evaluate(const VectorXd& aQueryVector) const override;

    /// @brief Evaluate the zero-order hold interpolator
    ///
    /// @code{.cpp}
    ///                     double values = zeroOrder.evaluate(5.0) ;
    /// @endcode
    ///
    /// @param aQueryValue An x value
    /// @return The y value of the previous data point
    virtual double evaluate(const double& aQueryValue) const override;

    /// @brief Get the derivative of the zero-order hold interpolator
    ///
    /// @code{.cpp}
    ///                     double derivative = zeroOrder.computeDerivative(5.0) ;
    /// @endcode
    ///
    /// @param aQueryValue An x value
    /// @return Derivative of the interpolator at the given x value (always 0.0 for step function)
    virtual double computeDerivative(const double& aQueryValue) const override;

    /// @brief Get the derivative of the zero-order hold interpolator
    ///
    /// @code{.cpp}
    ///                     VectorXd derivatives = zeroOrder.computeDerivative({1.0, 5.0, 6.0}) ;
    /// @endcode
    ///
    /// @param aQueryVector A vector of x values
    /// @return Vector of derivatives of the interpolator at the given x values (always 0.0 for step function)
    virtual VectorXd computeDerivative(const VectorXd& aQueryVector) const override;

   private:
    VectorXd x_;
    VectorXd y_;

    Index findPreviousIndex(const double& aQueryValue) const;
};

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk

#endif
