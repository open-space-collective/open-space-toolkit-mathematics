/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Interpolator_QuinticHermite__
#define __OpenSpaceToolkit_Mathematics_Interpolator_QuinticHermite__

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

using boost::math::interpolators::quintic_hermite;

/// @brief QuinticHermite
///
/// A quintic Hermite spline is a piecewise fifth-degree polynomial which matches the value,
/// the first derivative and the second derivative of the underlying function at every node.
/// The resulting interpolant is C2 continuous. Nodes may be arbitrarily (non-uniformly)
/// spaced.
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
    double computeSecondDerivative(const double& aQueryValue) const;

    /// @brief Compute the second derivatives at multiple query values
    ///
    /// @code{.cpp}
    ///                     VectorXd secondDerivatives = quinticHermite.computeSecondDerivative({1.0, 1.5, 2.0}) ;
    /// @endcode
    ///
    /// @param aQueryVector A vector of x values
    /// @return A vector of second derivatives at the given x values
    ///
    /// @warning The query values must lie within the interpolation domain
    VectorXd computeSecondDerivative(const VectorXd& aQueryVector) const;

   private:
    quintic_hermite<std::vector<double>> interpolator_;

    static quintic_hermite<std::vector<double>> BuildInterpolator(
        const VectorXd& anXVector, const VectorXd& aYVector, const VectorXd& aDyDxVector, const VectorXd& aD2yDx2Vector
    );
};

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk

#endif
