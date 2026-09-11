/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Interpolator_QuinticHermite__
#define __OpenSpaceToolkit_Mathematics_Interpolator_QuinticHermite__

#include <optional>
#include <vector>

#include <boost/math/interpolators/quintic_hermite.hpp>

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

using ostk::core::type::Real;
using ostk::core::type::Size;

using ostk::mathematics::curvefitting::Interpolator;
using ostk::mathematics::object::VectorXd;

using boost::math::interpolators::cardinal_quintic_hermite;
using boost::math::interpolators::quintic_hermite;

/// @brief QuinticHermite
///
/// A quintic Hermite spline is a piecewise fifth-degree polynomial which matches the value,
/// the first derivative and the second derivative of the underlying function at every node.
/// The resulting interpolant is C2 continuous.
///
/// Nodes may be uniformly or arbitrarily spaced. Uniformly spaced nodes are interpolated with
/// a cardinal Hermite spline, which finds the containing interval in constant time rather
/// than searching for it, and is therefore faster to evaluate. Which of the two is used is
/// decided from the data and is not otherwise observable, with one exception: the second
/// derivative of the cardinal Hermite spline is only available with Boost 1.93 or later
/// (see computeSecondDerivative).
///
/// @code{.cpp}
///     VectorXd x = {{0.0, 1.0, 2.0, 3.0}};
///     VectorXd y = {{0.0, 1.0, 4.0, 9.0}};
///     VectorXd dydx = {{0.0, 2.0, 4.0, 6.0}};
///     VectorXd d2ydx2 = {{2.0, 2.0, 2.0, 2.0}};
///     QuinticHermite interpolator(x, y, dydx, d2ydx2);
///     double value = interpolator.evaluate(1.5);
/// @endcode
///
/// @ref https://www.boost.org/doc/libs/1_87_0/libs/math/doc/html/math_toolkit/quintic_hermite.html
class QuinticHermite : public Interpolator
{
   public:
    /// @brief Constructor
    ///
    /// @code{.cpp}
    ///                     QuinticHermite quinticHermite(x, y, dydx, d2ydx2);
    /// @endcode
    ///
    /// @param anXVector A vector of x values
    /// @param aYVector A vector of y values
    /// @param aDyDxVector A vector of first derivative values
    /// @param aD2yDx2Vector A vector of second derivative values
    ///
    /// @warning The x values must be sorted in strictly ascending order
    QuinticHermite(
        const VectorXd& anXVector, const VectorXd& aYVector, const VectorXd& aDyDxVector, const VectorXd& aD2yDx2Vector
    );

    /// @brief Constructor
    ///
    /// @code{.cpp}
    ///                     QuinticHermite quinticHermite(y, dydx, d2ydx2, 0.0, 1.0);
    /// @endcode
    ///
    /// @param aYVector A vector of y values
    /// @param aDyDxVector A vector of first derivative values
    /// @param aD2yDx2Vector A vector of second derivative values
    /// @param x0 The first x value
    /// @param h The spacing between x values
    ///
    /// @warning The spacing must be strictly positive
    QuinticHermite(
        const VectorXd& aYVector,
        const VectorXd& aDyDxVector,
        const VectorXd& aD2yDx2Vector,
        const Real& x0,
        const Real& h
    );

    /// @brief Destructor
    ///
    /// @code{.cpp}
    ///                     // Called automatically when the QuinticHermite goes out of scope
    /// @endcode
    virtual ~QuinticHermite() override;

    /// @brief Evaluate the quintic Hermite interpolator
    ///
    /// @code{.cpp}
    ///                     VectorXd values = quinticHermite.evaluate({1.0, 1.5, 2.0}) ;
    /// @endcode
    ///
    /// @param aQueryVector A vector of x values
    /// @return Vector of y values
    ///
    /// @warning The query values must lie within the interpolation domain
    virtual VectorXd evaluate(const VectorXd& aQueryVector) const override;

    /// @brief Evaluate the quintic Hermite interpolator
    ///
    /// @code{.cpp}
    ///                     double value = quinticHermite.evaluate(1.5) ;
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
    ///                     double derivative = quinticHermite.computeDerivative(1.5) ;
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
    ///                     VectorXd derivatives = quinticHermite.computeDerivative({1.0, 1.5, 2.0}) ;
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
    ///                     double secondDerivative = quinticHermite.computeSecondDerivative(1.5) ;
    /// @endcode
    ///
    /// @param aQueryValue An x value
    /// @return The second derivative at the given x value
    ///
    /// @warning The query value must lie within the interpolation domain
    /// @warning Throws for uniformly spaced nodes when built against Boost older than 1.93, whose
    ///          cardinal quintic Hermite spline computes a wrong second derivative for a spacing other than 1
    double computeSecondDerivative(const double& aQueryValue) const;

    /// @brief Compute the second derivatives at multiple query values
    ///
    /// @code{.cpp}
    ///                     VectorXd secondDerivatives = quinticHermite.computeSecondDerivative({1.0, 2.0}) ;
    /// @endcode
    ///
    /// @param aQueryVector A vector of x values
    /// @return A vector of second derivatives at the given x values
    ///
    /// @warning The query values must lie within the interpolation domain
    /// @warning Throws for uniformly spaced nodes when built against Boost older than 1.93, whose
    ///          cardinal quintic Hermite spline computes a wrong second derivative for a spacing other than 1
    VectorXd computeSecondDerivative(const VectorXd& aQueryVector) const;

   private:
    // Exactly one of the two is engaged, depending on whether the nodes are uniformly spaced.
    //
    // boost::math::interpolators::cardinal_quintic_hermite::double_prime omits the 1 / h^2 factor on its first
    // derivative terms up to and including Boost 1.92, and is therefore only correct for a unit spacing. The fix
    // (boostorg/math#1101) is on the Boost develop branch and ships with Boost 1.93, so the second derivative of
    // the cardinal interpolant is withheld when built against an older Boost.

    std::optional<cardinal_quintic_hermite<std::vector<double>>> cardinalInterpolator_;
    std::optional<quintic_hermite<std::vector<double>>> interpolator_;
};

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk

#endif
