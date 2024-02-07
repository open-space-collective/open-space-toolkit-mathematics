/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Interpolator_Linear__
#define __OpenSpaceToolkit_Mathematics_Interpolator_Linear__

#include <OpenSpaceToolkit/Core/Container/Pair.hpp>
#include <OpenSpaceToolkit/Core/Type/Index.hpp>
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
using ostk::core::type::Index;
using ostk::core::container::Pair;

using ostk::mathematics::object::VectorXd;
using ostk::mathematics::curvefitting::Interpolator;

/// @brief                      Linear
///
///                             In mathematics, linear interpolator is a method of curve fitting using linear
///                             polynomials to construct new data points within the range of a discrete set of known
///                             data points.
///
/// @ref
/// https://en.wikipedia.org/wiki/Linear_interpolator#:~:text=In%20mathematics%2C%20linear%20interpolator%20is,set%20of%20known%20data%20points.

class Linear : public Interpolator
{
   public:
    /// @brief              Constructor
    ///
    /// @code
    ///                     Linear linear(x, y) ;
    /// @endcode
    ///
    /// @param              [in] anXVector A vector of x values
    /// @param              [in] aYVector A vector of y values
    ///
    /// @warning            The x values must be sorted in ascending order
    /// @warning            The x values must be equally spaced

    Linear(const VectorXd& anXVector, const VectorXd& aYVector);

    /// @brief              Clone linear
    ///
    /// @return             Pointer to cloned linear interpolator

    virtual Linear* clone() const;

    /// @brief              Evaluate the linear interpolator
    ///
    /// @code
    ///                     VectorXd values = linear.evaluate({1.0, 5.0, 6.0}) ;
    /// @endcode
    ///
    /// @param              [in] aQueryVector A vector of x values
    /// @return             Vector of y values

    VectorXd evaluate(const VectorXd& aQueryVector) const;

    /// @brief              Evaluate the linear interpolator
    ///
    /// @code
    ///                     double values = linear.evaluate(5.0) ;
    /// @endcode
    ///
    /// @param              [in] aQueryValue An x value
    /// @return             Vector of y values

    double evaluate(const double& aQueryValue) const;

   private:
    VectorXd x_;
    VectorXd y_;

    Pair<Index, Index> findIndexRange(const double& aQueryValue) const;
};

}  // namespace interpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk

#endif
