/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Interpolator_QuadraticSpline__
#define __OpenSpaceToolkit_Mathematics_Interpolator_QuadraticSpline__

#include <optional>
#include <vector>

#include <boost/math/interpolators/cardinal_quadratic_b_spline.hpp>

#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
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

using ostk::core::type::Real;
using ostk::core::type::Shared;
using ostk::core::type::Size;

using ostk::mathematics::curvefitting::Interpolator;
using ostk::mathematics::object::VectorXd;

using boost::math::interpolators::cardinal_quadratic_b_spline;

class NonUniformBSpline;

/// @brief QuadraticSpline
///
/// A quadratic spline is a piecewise second-degree polynomial fitted so that it passes
/// through the given data points. The resulting interpolant is C1 continuous, and reproduces
/// quadratic polynomials exactly. It is cheaper and less oscillatory than a cubic spline, at
/// the cost of a lower order of accuracy.
///
/// The derivatives at the two end points are estimated from the data.
///
/// Nodes may be uniformly or arbitrarily spaced. Uniformly spaced nodes are interpolated with
/// a cardinal B-spline, which finds the containing interval in constant time rather than
/// searching for it, and is therefore faster to evaluate. Which of the two is used is decided
/// from the data and is not otherwise observable.
///
/// @code{.cpp}
///     VectorXd x = {{0.0, 1.0, 2.0, 3.0}};
///     VectorXd y = {{2.0, 0.0, 0.0, 2.0}};
///     QuadraticSpline interpolator(x, y);
///     double value = interpolator.evaluate(1.5);
/// @endcode
///
/// @ref https://www.boost.org/doc/libs/1_87_0/libs/math/doc/html/math_toolkit/cardinal_quadratic_b.html
class QuadraticSpline : public Interpolator
{
   public:
    /// @brief Constructor
    ///
    /// @code{.cpp}
    ///                     QuadraticSpline quadraticSpline(x, y);
    /// @endcode
    ///
    /// @param anXVector A vector of x values
    /// @param aYVector A vector of y values
    ///
    /// @warning The x values must be sorted in strictly ascending order
    /// @warning At least 3 data points are required
    QuadraticSpline(const VectorXd& anXVector, const VectorXd& aYVector);

    /// @brief Constructor
    ///
    /// @code{.cpp}
    ///                     QuadraticSpline quadraticSpline(y, 0.0, 1.0);
    /// @endcode
    ///
    /// @param aYVector A vector of y values
    /// @param x0 The first x value
    /// @param h The spacing between x values
    ///
    /// @warning The spacing must be strictly positive
    /// @warning At least 3 data points are required
    QuadraticSpline(const VectorXd& aYVector, const Real& x0, const Real& h);

    /// @brief Destructor
    ///
    /// @code{.cpp}
    ///                     // Called automatically when the QuadraticSpline goes out of scope
    /// @endcode
    virtual ~QuadraticSpline() override;

    /// @brief Evaluate the quadratic spline interpolator
    ///
    /// @code{.cpp}
    ///                     VectorXd values = quadraticSpline.evaluate({1.0, 1.5, 2.0}) ;
    /// @endcode
    ///
    /// @param aQueryVector A vector of x values
    /// @return Vector of y values
    ///
    /// @warning The query values must lie within the interpolation domain
    virtual VectorXd evaluate(const VectorXd& aQueryVector) const override;

    /// @brief Evaluate the quadratic spline interpolator
    ///
    /// @code{.cpp}
    ///                     double value = quadraticSpline.evaluate(1.5) ;
    /// @endcode
    ///
    /// @param aQueryValue An x value
    /// @return The y value
    ///
    /// @warning The query value must lie within the interpolation domain
    virtual double evaluate(const double& aQueryValue) const override;

    /// @brief Compute the derivative at a specific query value
    ///
    /// @code{.cpp}
    ///                     double derivative = quadraticSpline.computeDerivative(1.5) ;
    /// @endcode
    ///
    /// @param aQueryValue An x value
    /// @return The derivative at the given x value
    ///
    /// @warning The query value must lie within the interpolation domain
    virtual double computeDerivative(const double& aQueryValue) const override;

    /// @brief Compute the derivatives at multiple query values
    ///
    /// @code{.cpp}
    ///                     VectorXd derivatives = quadraticSpline.computeDerivative({1.0, 1.5, 2.0}) ;
    /// @endcode
    ///
    /// @param aQueryVector A vector of x values
    /// @return A vector of derivatives at the given x values
    ///
    /// @warning The query values must lie within the interpolation domain
    virtual VectorXd computeDerivative(const VectorXd& aQueryVector) const override;

   private:
    // Exactly one of the two is engaged, depending on whether the nodes are uniformly spaced

    std::optional<cardinal_quadratic_b_spline<double>> cardinalInterpolator_;
    Shared<const NonUniformBSpline> interpolator_;
};

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk

#endif
