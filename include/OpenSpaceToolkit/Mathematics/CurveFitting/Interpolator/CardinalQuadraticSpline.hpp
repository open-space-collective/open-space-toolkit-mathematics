/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Interpolator_CardinalQuadraticSpline__
#define __OpenSpaceToolkit_Mathematics_Interpolator_CardinalQuadraticSpline__

#include <vector>

#include <boost/math/interpolators/cardinal_quadratic_b_spline.hpp>

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

using boost::math::interpolators::cardinal_quadratic_b_spline;

/// @brief CardinalQuadraticSpline
///
/// A cardinal quadratic spline is a quadratic B-spline over uniformly spaced nodes, fitted so
/// that it passes through the given data points. The resulting interpolant is C1 continuous,
/// and reproduces quadratic polynomials exactly. It is cheaper and less oscillatory than a
/// cubic spline, at the cost of a lower order of accuracy.
///
/// The derivatives at the two end points are estimated from the data.
///
/// @code{.cpp}
///     VectorXd x = {{0.0, 1.0, 2.0, 3.0}};
///     VectorXd y = {{2.0, 0.0, 0.0, 2.0}};
///     CardinalQuadraticSpline interpolator(x, y);
///     double value = interpolator.evaluate(1.5);
/// @endcode
///
/// @ref https://www.boost.org/doc/libs/1_87_0/libs/math/doc/html/math_toolkit/cardinal_quadratic_b.html
class CardinalQuadraticSpline : public Interpolator
{
   public:
    /// @brief Constructor
    ///
    /// @code{.cpp}
    ///                     CardinalQuadraticSpline cardinalQuadraticSpline(x, y);
    /// @endcode
    ///
    /// @param anXVector A vector of x values
    /// @param aYVector A vector of y values
    ///
    /// @warning The x values must be sorted in ascending order
    /// @warning The x values must be equally spaced
    /// @warning At least 3 data points are required
    CardinalQuadraticSpline(const VectorXd& anXVector, const VectorXd& aYVector);

    /// @brief Constructor
    ///
    /// @code{.cpp}
    ///                     CardinalQuadraticSpline cardinalQuadraticSpline(y, 0.0, 1.0);
    /// @endcode
    ///
    /// @param aYVector A vector of y values
    /// @param x0 The first x value
    /// @param h The spacing between x values
    ///
    /// @warning The spacing must be strictly positive
    /// @warning At least 3 data points are required
    CardinalQuadraticSpline(const VectorXd& aYVector, const Real& x0, const Real& h);

    /// @brief Destructor
    ///
    /// @code{.cpp}
    ///                     // Called automatically when the CardinalQuadraticSpline goes out of scope
    /// @endcode
    virtual ~CardinalQuadraticSpline() override;

    /// @brief Evaluate the cardinal quadratic spline interpolator
    ///
    /// @code{.cpp}
    ///                     VectorXd values = cardinalQuadraticSpline.evaluate({1.0, 1.5, 2.0}) ;
    /// @endcode
    ///
    /// @param aQueryVector A vector of x values
    /// @return Vector of y values
    ///
    /// @warning The query values must lie within the interpolation domain
    virtual VectorXd evaluate(const VectorXd& aQueryVector) const override;

    /// @brief Evaluate the cardinal quadratic spline interpolator
    ///
    /// @code{.cpp}
    ///                     double value = cardinalQuadraticSpline.evaluate(1.5) ;
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
    ///                     double derivative = cardinalQuadraticSpline.computeDerivative(1.5) ;
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
    ///                     VectorXd derivatives = cardinalQuadraticSpline.computeDerivative({1.0, 1.5, 2.0}) ;
    /// @endcode
    ///
    /// @param aQueryVector A vector of x values
    /// @return A vector of derivatives at the given x values
    ///
    /// @warning The query values must lie within the interpolation domain
    virtual VectorXd computeDerivative(const VectorXd& aQueryVector) const override;

   private:
    cardinal_quadratic_b_spline<double> interpolator_;

    static cardinal_quadratic_b_spline<double> BuildInterpolator(const VectorXd& anXVector, const VectorXd& aYVector);

    static cardinal_quadratic_b_spline<double> BuildInterpolator(
        const VectorXd& aYVector, const Real& x0, const Real& h
    );
};

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk

#endif
