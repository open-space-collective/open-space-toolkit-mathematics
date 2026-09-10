/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Interpolator_CubicSpline__
#define __OpenSpaceToolkit_Mathematics_Interpolator_CubicSpline__

#include <optional>

#include <boost/math/interpolators/cardinal_cubic_b_spline.hpp>

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

using boost::math::interpolators::cardinal_cubic_b_spline;

class NonUniformBSpline;

/// @brief CubicSpline
///
/// A cubic spline interpolator is a spline where each piece is a third-degree polynomial
/// specified in spline form, that is by its values and first derivatives at the end points
/// of the corresponding domain interval. The resulting interpolant is C2 continuous.
///
/// The derivatives at the two end points are estimated from the data.
///
/// Nodes may be uniformly or arbitrarily spaced. Uniformly spaced nodes are interpolated with
/// a cardinal B-spline, which finds the containing interval in constant time rather than
/// searching for it, and is therefore faster to evaluate. Which of the two is used is decided
/// from the data and is not otherwise observable.
///
/// @code{.cpp}
///     VectorXd x = {{0.0, 1.0, 2.0, 3.0, 4.0}};
///     VectorXd y = {{0.0, 1.0, 4.0, 9.0, 16.0}};
///     CubicSpline interpolator(x, y);
///     double value = interpolator.evaluate(1.5);
/// @endcode
///
/// @ref https://en.wikipedia.org/wiki/Spline_interpolation
class CubicSpline : public Interpolator
{
   public:
    /// @brief Constructor
    ///
    /// @code{.cpp}
    ///                     CubicSpline cubicSpline(x, y);
    /// @endcode
    ///
    /// @param anXVector A vector of x values
    /// @param aYVector A vector of y values
    ///
    /// @warning The x values must be sorted in strictly ascending order
    /// @warning At least 5 data points are required
    CubicSpline(const VectorXd& anXVector, const VectorXd& aYVector);

    /// @brief Constructor
    ///
    /// @code{.cpp}
    ///                     CubicSpline cubicSpline(y, x0, h) ;
    /// @endcode
    ///
    /// @param aYVector A vector of y values
    /// @param x0 The first x value
    /// @param h The spacing between x values
    ///
    /// @warning The spacing must be strictly positive
    /// @warning At least 5 data points are required
    CubicSpline(const VectorXd& aYVector, const Real& x0, const Real& h);

    /// @brief Destructor
    ///
    /// @code{.cpp}
    ///                     // Called automatically when the CubicSpline goes out of scope
    /// @endcode
    virtual ~CubicSpline() override;

    /// @brief Evaluate the cubic spline interpolator
    ///
    /// @code{.cpp}
    ///                     VectorXd values = cubicSpline.evaluate({1.0, 5.0, 6.0}) ;
    /// @endcode
    ///
    /// @param aQueryVector A vector of x values
    /// @return Vector of y values
    virtual VectorXd evaluate(const VectorXd& aQueryVector) const override;

    /// @brief Evaluate the cubic spline interpolator
    ///
    /// @code{.cpp}
    ///                     double values = cubicSpline.evaluate(5.0) ;
    /// @endcode
    ///
    /// @param aQueryValue An x value
    /// @return Vector of y values
    virtual double evaluate(const double& aQueryValue) const override;

    /// @brief Compute the derivative at a specific query value
    /// @param aQueryValue The x value to compute the derivative at
    ///
    /// @code{.cpp}
    ///                     double derivative = cubicSpline.computeDerivative(5.0) ;
    /// @endcode
    ///
    /// @return The derivative at the given x value
    virtual double computeDerivative(const double& aQueryValue) const override;

    /// @brief Compute the derivatives at multiple query values
    /// @param aQueryVector A vector of x values to compute the derivatives at
    ///
    /// @code{.cpp}
    ///                     VectorXd derivatives = cubicSpline.computeDerivative({1.0, 5.0, 6.0}) ;
    /// @endcode
    ///
    /// @return A vector of derivatives at the given x values
    virtual VectorXd computeDerivative(const VectorXd& aQueryVector) const override;

   private:
    // Exactly one of the two is engaged, depending on whether the nodes are uniformly spaced

    std::optional<cardinal_cubic_b_spline<double>> cardinalInterpolator_;
    Shared<const NonUniformBSpline> interpolator_;
};

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk

#endif
