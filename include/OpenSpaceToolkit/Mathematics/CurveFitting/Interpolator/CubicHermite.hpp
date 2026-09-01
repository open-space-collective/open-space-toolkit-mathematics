/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Interpolator_CubicHermite__
#define __OpenSpaceToolkit_Mathematics_Interpolator_CubicHermite__

#include <vector>

#include <boost/math/interpolators/cubic_hermite.hpp>

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

using boost::math::interpolators::cubic_hermite;

/// @brief CubicHermite
///
/// A cubic Hermite spline is a piecewise third-degree polynomial which matches both the
/// value and the first derivative of the underlying function at every node. The resulting
/// interpolant is C1 continuous. Nodes may be arbitrarily (non-uniformly) spaced.
///
/// @code{.cpp}
///     VectorXd x = {{0.0, 1.0, 2.0, 3.0}};
///     VectorXd y = {{0.0, 1.0, 4.0, 9.0}};
///     VectorXd dydx = {{0.0, 2.0, 4.0, 6.0}};
///     CubicHermite interpolator(x, y, dydx);
///     double value = interpolator.evaluate(1.5);
/// @endcode
///
/// @ref https://www.boost.org/doc/libs/1_87_0/libs/math/doc/html/math_toolkit/cubic_hermite.html
class CubicHermite : public Interpolator
{
   public:
    /// @brief Constructor
    ///
    /// @code{.cpp}
    ///                     CubicHermite cubicHermite(x, y, dydx);
    /// @endcode
    ///
    /// @param anXVector A vector of x values
    /// @param aYVector A vector of y values
    /// @param aDyDxVector A vector of first derivative values
    ///
    /// @warning The x values must be sorted in strictly ascending order
    CubicHermite(const VectorXd& anXVector, const VectorXd& aYVector, const VectorXd& aDyDxVector);

    /// @brief Destructor
    ///
    /// @code{.cpp}
    ///                     // Called automatically when the CubicHermite goes out of scope
    /// @endcode
    virtual ~CubicHermite() override;

    /// @brief Evaluate the cubic Hermite interpolator
    ///
    /// @code{.cpp}
    ///                     VectorXd values = cubicHermite.evaluate({1.0, 1.5, 2.0}) ;
    /// @endcode
    ///
    /// @param aQueryVector A vector of x values
    /// @return Vector of y values
    ///
    /// @warning The query values must lie within the interpolation domain
    virtual VectorXd evaluate(const VectorXd& aQueryVector) const override;

    /// @brief Evaluate the cubic Hermite interpolator
    ///
    /// @code{.cpp}
    ///                     double value = cubicHermite.evaluate(1.5) ;
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
    ///                     double derivative = cubicHermite.computeDerivative(1.5) ;
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
    ///                     VectorXd derivatives = cubicHermite.computeDerivative({1.0, 1.5, 2.0}) ;
    /// @endcode
    ///
    /// @param aQueryVector A vector of x values
    /// @return A vector of derivatives at the given x values
    ///
    /// @warning The query values must lie within the interpolation domain
    virtual VectorXd computeDerivative(const VectorXd& aQueryVector) const override;

   private:
    cubic_hermite<std::vector<double>> interpolator_;

    static cubic_hermite<std::vector<double>> BuildInterpolator(
        const VectorXd& anXVector, const VectorXd& aYVector, const VectorXd& aDyDxVector
    );
};

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk

#endif
