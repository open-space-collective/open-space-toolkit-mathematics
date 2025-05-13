/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Interpolator_BarycentricRational__
#define __OpenSpaceToolkit_Mathematics_Interpolator_BarycentricRational__

#include <boost/math/interpolators/barycentric_rational.hpp>

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

using boost::math::interpolators::barycentric_rational;

/// @brief BarycentricRational
///
/// Barycentric rational interpolator is a high-accuracy interpolator method for
/// non-uniformly spaced samples. It requires 𝑶(N) time for construction, and 𝑶(N) time for
/// each evaluation.
///
/// @ref https://www.boost.org/doc/libs/1_81_0/libs/math/doc/html/math_toolkit/barycentric.html
class BarycentricRational : public Interpolator
{
   public:
    /// @brief Constructor
    ///
    /// @code{.cpp}
    ///                  BarycentricRational barycentricRational(x, y);
    /// @endcode
    ///
    /// @param anXVector A vector of x values
    /// @param aYVector A vector of y values
    ///
    /// @warning The x values must be sorted in ascending order
    BarycentricRational(const VectorXd& anXVector, const VectorXd& aYVector);

    /// @brief Destructor
    virtual ~BarycentricRational() override;

    /// @brief Evaluate the spline
    ///
    /// @code{.cpp}
    ///                     VectorXd values = barycentricRational.evaluate({1.0, 5.0, 6.0}) ;
    /// @endcode
    ///
    /// @param aQueryVector A vector of x values
    /// @return Vector of y values
    virtual VectorXd evaluate(const VectorXd& aQueryVector) const override;

    /// @brief Evaluate the spline
    ///
    /// @code{.cpp}
    /// double values = barycentricRational.evaluate(5.0) ;
    /// @endcode
    ///
    /// @param aQueryValue An x value
    /// @return Vector of y values
    virtual double evaluate(const double& aQueryValue) const override;

    /// @brief Compute the derivative at a specific query value
    /// @param aQueryValue The x value to compute the derivative at
    ///
    /// @code{.cpp}
    ///                     double derivative = barycentricRational.computeDerivative(5.0) ;
    /// @endcode
    ///
    /// @return The derivative at the given x value
    virtual double computeDerivative(const double& aQueryValue) const override;

    /// @brief Compute the derivatives at multiple query values
    /// @param aQueryVector A vector of x values to compute the derivatives at
    ///
    /// @code{.cpp}
    ///                     VectorXd derivatives = barycentricRational.computeDerivative({1.0, 5.0, 6.0}) ;
    /// @endcode
    ///
    /// @return A vector of derivatives at the given x values
    virtual VectorXd computeDerivative(const VectorXd& aQueryVector) const override;

   private:
    barycentric_rational<double> interpolator_;
};

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk

#endif
