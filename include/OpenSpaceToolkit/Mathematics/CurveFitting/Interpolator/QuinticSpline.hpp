/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Interpolator_QuinticSpline__
#define __OpenSpaceToolkit_Mathematics_Interpolator_QuinticSpline__

#include <optional>
#include <vector>

#include <boost/math/interpolators/cardinal_quintic_b_spline.hpp>

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

using boost::math::interpolators::cardinal_quintic_b_spline;

class NonUniformBSpline;

/// @brief QuinticSpline
///
/// A quintic spline is a piecewise fifth-degree polynomial fitted so that it passes through
/// the given data points. The resulting interpolant is C4 continuous, and reproduces quintic
/// polynomials exactly. It is the highest order of the spline interpolators, and is the
/// natural choice when a smooth second derivative is needed.
///
/// The first and second derivatives at the two end points are estimated from the data.
///
/// Nodes may be uniformly or arbitrarily spaced. Uniformly spaced nodes are interpolated with
/// a cardinal B-spline, which finds the containing interval in constant time rather than
/// searching for it, and is therefore faster to evaluate. Which of the two is used is decided
/// from the data and is not otherwise observable.
///
/// @code{.cpp}
///     VectorXd x = {{0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0}};
///     VectorXd y = {{2.0, 0.0, 6.0, 56.0, 210.0, 552.0, 1190.0, 2256.0}};
///     QuinticSpline interpolator(x, y);
///     double value = interpolator.evaluate(1.5);
/// @endcode
///
/// @ref https://www.boost.org/doc/libs/1_87_0/libs/math/doc/html/math_toolkit/cardinal_quintic_b.html
class QuinticSpline : public Interpolator
{
   public:
    /// @brief Constructor
    ///
    /// @code{.cpp}
    ///                     QuinticSpline quinticSpline(x, y);
    /// @endcode
    ///
    /// @param anXVector A vector of x values
    /// @param aYVector A vector of y values
    ///
    /// @warning The x values must be sorted in strictly ascending order
    /// @warning At least 8 data points are required
    QuinticSpline(const VectorXd& anXVector, const VectorXd& aYVector);

    /// @brief Constructor
    ///
    /// @code{.cpp}
    ///                     QuinticSpline quinticSpline(y, 0.0, 1.0);
    /// @endcode
    ///
    /// @param aYVector A vector of y values
    /// @param x0 The first x value
    /// @param h The spacing between x values
    ///
    /// @warning The spacing must be strictly positive
    /// @warning At least 8 data points are required
    QuinticSpline(const VectorXd& aYVector, const Real& x0, const Real& h);

    /// @brief Destructor
    ///
    /// @code{.cpp}
    ///                     // Called automatically when the QuinticSpline goes out of scope
    /// @endcode
    virtual ~QuinticSpline() override;

    /// @brief Evaluate the quintic spline interpolator
    ///
    /// @code{.cpp}
    ///                     VectorXd values = quinticSpline.evaluate({1.0, 1.5, 2.0}) ;
    /// @endcode
    ///
    /// @param aQueryVector A vector of x values
    /// @return Vector of y values
    ///
    /// @warning The query values must lie within the interpolation domain
    virtual VectorXd evaluate(const VectorXd& aQueryVector) const override;

    /// @brief Evaluate the quintic spline interpolator
    ///
    /// @code{.cpp}
    ///                     double value = quinticSpline.evaluate(1.5) ;
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
    ///                     double derivative = quinticSpline.computeDerivative(1.5) ;
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
    ///                     VectorXd derivatives = quinticSpline.computeDerivative({1.0, 1.5, 2.0}) ;
    /// @endcode
    ///
    /// @param aQueryVector A vector of x values
    /// @return A vector of derivatives at the given x values
    ///
    /// @warning The query values must lie within the interpolation domain
    virtual VectorXd computeDerivative(const VectorXd& aQueryVector) const override;

    /// @brief Compute the second derivative at a specific query value
    ///
    /// @code{.cpp}
    ///                     double secondDerivative = quinticSpline.computeSecondDerivative(1.5) ;
    /// @endcode
    ///
    /// @param aQueryValue An x value
    /// @return The second derivative at the given x value
    ///
    /// @warning The query value must lie within the interpolation domain
    double computeSecondDerivative(const double& aQueryValue) const;

    /// @brief Compute the second derivatives at multiple query values
    ///
    /// @code{.cpp}
    ///                     VectorXd secondDerivatives = quinticSpline.computeSecondDerivative({1.0, 2.0}) ;
    /// @endcode
    ///
    /// @param aQueryVector A vector of x values
    /// @return A vector of second derivatives at the given x values
    ///
    /// @warning The query values must lie within the interpolation domain
    VectorXd computeSecondDerivative(const VectorXd& aQueryVector) const;

   private:
    // Exactly one of the two is engaged, depending on whether the nodes are uniformly spaced

    std::optional<cardinal_quintic_b_spline<double>> cardinalInterpolator_;
    Shared<const NonUniformBSpline> interpolator_;
};

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk

#endif
