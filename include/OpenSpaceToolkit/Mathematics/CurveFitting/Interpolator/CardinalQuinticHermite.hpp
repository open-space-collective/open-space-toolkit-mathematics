/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Interpolator_CardinalQuinticHermite__
#define __OpenSpaceToolkit_Mathematics_Interpolator_CardinalQuinticHermite__

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

/// @brief CardinalQuinticHermite
///
/// A cardinal quintic Hermite spline is a quintic Hermite spline whose nodes are uniformly
/// spaced. Since the containing interval can be computed in constant time rather than
/// searched for, evaluation is faster than for the non-uniform QuinticHermite variant.
///
/// @code{.cpp}
///     VectorXd y = {{0.0, 1.0, 4.0, 9.0}};
///     VectorXd dydx = {{0.0, 2.0, 4.0, 6.0}};
///     VectorXd d2ydx2 = {{2.0, 2.0, 2.0, 2.0}};
///     CardinalQuinticHermite interpolator(y, dydx, d2ydx2, 0.0, 1.0);
///     double value = interpolator.evaluate(1.5);
/// @endcode
///
/// @ref https://www.boost.org/doc/libs/1_87_0/libs/math/doc/html/math_toolkit/cardinal_quintic_hermite.html
class CardinalQuinticHermite : public Interpolator
{
   public:
    /// @brief Constructor
    ///
    /// @code{.cpp}
    ///                     CardinalQuinticHermite cardinalQuinticHermite(x, y, dydx, d2ydx2);
    /// @endcode
    ///
    /// @param anXVector A vector of x values
    /// @param aYVector A vector of y values
    /// @param aDyDxVector A vector of first derivative values
    /// @param aD2yDx2Vector A vector of second derivative values
    ///
    /// @warning The x values must be sorted in ascending order
    /// @warning The x values must be equally spaced
    CardinalQuinticHermite(
        const VectorXd& anXVector, const VectorXd& aYVector, const VectorXd& aDyDxVector, const VectorXd& aD2yDx2Vector
    );

    /// @brief Constructor
    ///
    /// @code{.cpp}
    ///                     CardinalQuinticHermite cardinalQuinticHermite(y, dydx, d2ydx2, 0.0, 1.0);
    /// @endcode
    ///
    /// @param aYVector A vector of y values
    /// @param aDyDxVector A vector of first derivative values
    /// @param aD2yDx2Vector A vector of second derivative values
    /// @param x0 The first x value
    /// @param h The spacing between x values
    ///
    /// @warning The spacing must be strictly positive
    CardinalQuinticHermite(
        const VectorXd& aYVector,
        const VectorXd& aDyDxVector,
        const VectorXd& aD2yDx2Vector,
        const Real& x0,
        const Real& h
    );

    /// @brief Destructor
    ///
    /// @code{.cpp}
    ///                     // Called automatically when the CardinalQuinticHermite goes out of scope
    /// @endcode
    virtual ~CardinalQuinticHermite() override;

    /// @brief Evaluate the cardinal quintic Hermite interpolator
    ///
    /// @code{.cpp}
    ///                     VectorXd values = cardinalQuinticHermite.evaluate({1.0, 1.5, 2.0}) ;
    /// @endcode
    ///
    /// @param aQueryVector A vector of x values
    /// @return Vector of y values
    ///
    /// @warning The query values must lie within the interpolation domain
    virtual VectorXd evaluate(const VectorXd& aQueryVector) const override;

    /// @brief Evaluate the cardinal quintic Hermite interpolator
    ///
    /// @code{.cpp}
    ///                     double value = cardinalQuinticHermite.evaluate(1.5) ;
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
    ///                     double derivative = cardinalQuinticHermite.computeDerivative(1.5) ;
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
    ///                     VectorXd derivatives = cardinalQuinticHermite.computeDerivative({1.0, 1.5, 2.0}) ;
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
    ///                     double secondDerivative = cardinalQuinticHermite.computeSecondDerivative(1.5) ;
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
    ///                     VectorXd secondDerivatives = cardinalQuinticHermite.computeSecondDerivative({1.0, 2.0}) ;
    /// @endcode
    ///
    /// @param aQueryVector A vector of x values
    /// @return A vector of second derivatives at the given x values
    ///
    /// @warning The query values must lie within the interpolation domain
    VectorXd computeSecondDerivative(const VectorXd& aQueryVector) const;

   private:
    // The underlying interpolant is built over the normalized abscissa s = (x - x0) / h, i.e. over the unit grid
    // s = 0, 1, ..., n - 1, with the derivatives scaled accordingly, and the results scaled back on the way out.
    // This is needed because boost::math::interpolators::cardinal_quintic_hermite::double_prime omits the 1 / h^2
    // factor on its first derivative terms, and is therefore only correct for a unit spacing. Still unfixed as of
    // Boost 1.92 (verified on the develop branch too), so this cannot simply be dropped on a Boost upgrade.

    cardinal_quintic_hermite<std::vector<double>> interpolator_;
    double x0_;
    double h_;
    Size size_;

    double normalizeQueryValue(const double& aQueryValue) const;

    static cardinal_quintic_hermite<std::vector<double>> BuildInterpolator(
        const VectorXd& anXVector, const VectorXd& aYVector, const VectorXd& aDyDxVector, const VectorXd& aD2yDx2Vector
    );

    static cardinal_quintic_hermite<std::vector<double>> BuildInterpolator(
        const VectorXd& aYVector, const VectorXd& aDyDxVector, const VectorXd& aD2yDx2Vector, const Real& h
    );
};

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk

#endif
