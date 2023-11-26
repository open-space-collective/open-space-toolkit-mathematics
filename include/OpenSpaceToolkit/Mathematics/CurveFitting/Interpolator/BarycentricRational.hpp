/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Interpolator_BarycentricRational__
#define __OpenSpaceToolkit_Mathematics_Interpolator_BarycentricRational__

#include <boost/math/interpolators/barycentric_rational.hpp>

#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator.hpp>
#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>

namespace ostk
{
namespace math
{
namespace curvefitting
{
namespace interpolator
{

using ostk::core::types::Real;
using ostk::core::types::Size;

using ostk::math::object::VectorXd;
using ostk::math::curvefitting::Interpolator;

using boost::math::interpolators::barycentric_rational;

/// @brief                      BarycentricRational
///
///                             Barycentric rational interpolator is a high-accuracy interpolator method for
///                             non-uniformly spaced samples. It requires 𝑶(N) time for construction, and 𝑶(N) time for
///                             each evaluation.
///
/// @ref                        https://www.boost.org/doc/libs/1_81_0/libs/math/doc/html/math_toolkit/barycentric.html

class BarycentricRational : public Interpolator
{
   public:
    /// @brief              Constructor
    ///
    /// @code
    ///                     BarycentricRational barycentricRational(x, y) ;
    /// @endcode
    ///
    /// @param              [in] anXVector A vector of x values
    /// @param              [in] aYVector A vector of y values
    ///
    /// @warning            The x values must be sorted in ascending order
    /// @warning            The x values must be equally spaced

    BarycentricRational(const VectorXd& anXVector, const VectorXd& aYVector);

    /// @brief              Clone barycentric rational
    ///
    /// @return             Pointer to cloned barycentric rational

    BarycentricRational* clone() const;

    /// @brief              Evaluate the spline
    ///
    /// @code
    ///                     VectorXd values = barycentricRational.evaluate({1.0, 5.0, 6.0}) ;
    /// @endcode
    ///
    /// @param              [in] aQueryVector A vector of x values
    /// @return             Vector of y values

    VectorXd evaluate(const VectorXd& aQueryVector) const;

    /// @brief              Evaluate the spline
    ///
    /// @code
    ///                     double values = barycentricRational.evaluate(5.0) ;
    /// @endcode
    ///
    /// @param              [in] aQueryValue An x value
    /// @return             Vector of y values

    double evaluate(const double& aQueryValue) const;

   private:
    barycentric_rational<double> interpolator_;
};

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace math
}  // namespace ostk

#endif