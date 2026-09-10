/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Interpolator_NonUniformBSpline__
#define __OpenSpaceToolkit_Mathematics_Interpolator_NonUniformBSpline__

#include <vector>

#include <OpenSpaceToolkit/Core/Type/Size.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

namespace ostk
{
namespace mathematics
{
namespace curvefitting
{
namespace interpolator
{

using ostk::core::type::Size;

using ostk::mathematics::object::VectorXd;

/// @brief NonUniformBSpline (library-private)
///
/// An interpolating B-spline of a given degree over arbitrarily spaced nodes. Boost only
/// supplies B-spline interpolators for uniformly spaced nodes (the cardinal_*_b_spline
/// family), so the spline interpolators fall back to this when their nodes are not uniformly
/// spaced.
///
/// The construction mirrors the cardinal interpolators it stands in for: the spline is the
/// unique one of the given degree that passes through every data point and matches the
/// endpoint derivatives, which are estimated from the data with one-sided finite differences
/// of the same order of accuracy that Boost uses. Both paths therefore describe very nearly
/// the same curve, and which one is taken is not observable beyond rounding.
///
/// This header lives under src/ rather than include/ because it is an implementation detail
/// and is deliberately not installed as part of the public API.
///
/// @ref Piegl and Tiller, The NURBS Book, 2nd edition, chapters 2 and 9.
class NonUniformBSpline
{
   public:
    /// @brief What to do with a query outside of the interpolation domain
    ///
    /// The Boost cardinal B-splines are not consistent about this: the quadratic and quintic
    /// ones reject such a query, while the cubic one extrapolates. Each interpolator picks the
    /// behaviour of the cardinal implementation it shares its name with, so that which of the
    /// two paths is taken stays invisible to the caller.
    enum class DomainBehavior
    {
        Throw,       ///< Throw std::domain_error
        Extrapolate  ///< Extend the polynomial of the nearest end span
    };

    /// @brief Build the interpolating B-spline of the given degree through the given data
    ///
    /// @param anXVector A vector of x values, sorted in strictly ascending order
    /// @param aYVector A vector of y values
    /// @param aDegree The degree of the spline
    /// @param aDomainBehavior What to do with a query outside of the interpolation domain
    /// @return The interpolating B-spline
    static NonUniformBSpline Interpolate(
        const VectorXd& anXVector, const VectorXd& aYVector, const Size& aDegree, const DomainBehavior& aDomainBehavior
    );

    /// @brief Evaluate the spline
    ///
    /// @param aQueryValue An x value, within the interpolation domain
    /// @return The y value
    double evaluate(const double& aQueryValue) const;

    /// @brief Compute the first derivative of the spline
    ///
    /// @param aQueryValue An x value, within the interpolation domain
    /// @return The first derivative at the given x value
    double computeDerivative(const double& aQueryValue) const;

    /// @brief Compute the second derivative of the spline
    ///
    /// @param aQueryValue An x value, within the interpolation domain
    /// @return The second derivative at the given x value
    double computeSecondDerivative(const double& aQueryValue) const;

   private:
    Size degree_;
    std::vector<double> knots_;
    std::vector<double> coefficients_;
    DomainBehavior domainBehavior_;

    NonUniformBSpline(
        const Size& aDegree,
        std::vector<double>&& aKnotArray,
        std::vector<double>&& aCoefficientArray,
        const DomainBehavior& aDomainBehavior
    );

    /// @brief Evaluate the given derivative order of the spline
    double computeValue(const double& aQueryValue, const Size& aDerivativeOrder) const;
};

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk

#endif
