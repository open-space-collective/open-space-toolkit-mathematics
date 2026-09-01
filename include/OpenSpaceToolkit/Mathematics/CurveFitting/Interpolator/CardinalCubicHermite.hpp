/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Interpolator_CardinalCubicHermite__
#define __OpenSpaceToolkit_Mathematics_Interpolator_CardinalCubicHermite__

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

using boost::math::interpolators::cardinal_cubic_hermite;

/// @brief CardinalCubicHermite
///
/// A cardinal cubic Hermite spline is a cubic Hermite spline whose nodes are uniformly
/// spaced. Since the containing interval can be computed in constant time rather than
/// searched for, evaluation is faster than for the non-uniform CubicHermite variant.
///
/// @code{.cpp}
///     VectorXd y = {{0.0, 1.0, 4.0, 9.0}};
///     VectorXd dydx = {{0.0, 2.0, 4.0, 6.0}};
///     CardinalCubicHermite interpolator(y, dydx, 0.0, 1.0);
///     double value = interpolator.evaluate(1.5);
/// @endcode
///
/// @ref https://www.boost.org/doc/libs/1_87_0/libs/math/doc/html/math_toolkit/cardinal_cubic_hermite.html
class CardinalCubicHermite : public Interpolator
{
   public:
    /// @brief Constructor
    ///
    /// @code{.cpp}
    ///                     CardinalCubicHermite cardinalCubicHermite(x, y, dydx);
    /// @endcode
    ///
    /// @param anXVector A vector of x values
    /// @param aYVector A vector of y values
    /// @param aDyDxVector A vector of first derivative values
    ///
    /// @warning The x values must be sorted in ascending order
    /// @warning The x values must be equally spaced
    CardinalCubicHermite(const VectorXd& anXVector, const VectorXd& aYVector, const VectorXd& aDyDxVector);

    /// @brief Constructor
    ///
    /// @code{.cpp}
    ///                     CardinalCubicHermite cardinalCubicHermite(y, dydx, 0.0, 1.0);
    /// @endcode
    ///
    /// @param aYVector A vector of y values
    /// @param aDyDxVector A vector of first derivative values
    /// @param x0 The first x value
    /// @param h The spacing between x values
    ///
    /// @warning The spacing must be strictly positive
    CardinalCubicHermite(const VectorXd& aYVector, const VectorXd& aDyDxVector, const Real& x0, const Real& h);

    /// @brief Destructor
    ///
    /// @code{.cpp}
    ///                     // Called automatically when the CardinalCubicHermite goes out of scope
    /// @endcode
    virtual ~CardinalCubicHermite() override;

    /// @brief Evaluate the cardinal cubic Hermite interpolator
    ///
    /// @code{.cpp}
    ///                     VectorXd values = cardinalCubicHermite.evaluate({1.0, 1.5, 2.0}) ;
    /// @endcode
    ///
    /// @param aQueryVector A vector of x values
    /// @return Vector of y values
    ///
    /// @warning The query values must lie within the interpolation domain
    virtual VectorXd evaluate(const VectorXd& aQueryVector) const override;

    /// @brief Evaluate the cardinal cubic Hermite interpolator
    ///
    /// @code{.cpp}
    ///                     double value = cardinalCubicHermite.evaluate(1.5) ;
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
    ///                     double derivative = cardinalCubicHermite.computeDerivative(1.5) ;
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
    ///                     VectorXd derivatives = cardinalCubicHermite.computeDerivative({1.0, 1.5, 2.0}) ;
    /// @endcode
    ///
    /// @param aQueryVector A vector of x values
    /// @return A vector of derivatives at the given x values
    ///
    /// @warning The query values must lie within the interpolation domain
    virtual VectorXd computeDerivative(const VectorXd& aQueryVector) const override;

   private:
    cardinal_cubic_hermite<std::vector<double>> interpolator_;

    static cardinal_cubic_hermite<std::vector<double>> BuildInterpolator(
        const VectorXd& anXVector, const VectorXd& aYVector, const VectorXd& aDyDxVector
    );

    static cardinal_cubic_hermite<std::vector<double>> BuildInterpolator(
        const VectorXd& aYVector, const VectorXd& aDyDxVector, const Real& x0, const Real& h
    );
};

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk

#endif
