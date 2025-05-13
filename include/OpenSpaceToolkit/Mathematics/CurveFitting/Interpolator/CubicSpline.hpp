/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Interpolator_CubicSpline__
#define __OpenSpaceToolkit_Mathematics_Interpolator_CubicSpline__

#include <boost/math/interpolators/cardinal_cubic_b_spline.hpp>

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

using boost::math::interpolators::cardinal_cubic_b_spline;

/// @brief CubicSpline
///
/// A cubic Spline interpolator is a spline where each piece is a third-degree polynomial
/// specified in Spline form, that is by its values and first derivatives at the end points
/// of the corresponding domain interval.
///
/// @ref
/// https://en.wikipedia.org/wiki/Cubic_Spline_spline#:~:text=In%20numerical%20analysis%2C%20a%20cubic,of%20the%20corresponding%20domain%20interval.

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
    /// @warning The x values must be sorted in ascending order
    /// @warning The x values must be equally spaced
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
    /// @warning The x values must be sorted in ascending order
    /// @warning The x values must be equally spaced
    CubicSpline(const VectorXd& aYVector, const Real& x0, const Real& h);

    /// @brief Destructor
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
    cardinal_cubic_b_spline<double> interpolator_;
};

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk

#endif
