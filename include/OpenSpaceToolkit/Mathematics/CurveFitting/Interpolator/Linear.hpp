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

using ostk::core::container::Pair;
using ostk::core::type::Index;
using ostk::core::type::Real;
using ostk::core::type::Size;

using ostk::mathematics::curvefitting::Interpolator;
using ostk::mathematics::object::VectorXd;

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
    /// @brief Constructor
    ///
    /// @code{.cpp}
    ///                     Linear linear(x, y);
    /// @endcode
    ///
    /// @param anXVector A vector of x values
    /// @param aYVector A vector of y values
    ///
    /// @warning The x values must be sorted in ascending order
    Linear(const VectorXd& anXVector, const VectorXd& aYVector);

    /// @brief Destructor
    virtual ~Linear() override;

    /// @brief Evaluate the linear interpolator
    ///
    /// @code{.cpp}
    ///                     VectorXd values = linear.evaluate({1.0, 5.0, 6.0}) ;
    /// @endcode
    ///
    /// @param aQueryVector A vector of x values
    /// @return Vector of y values
    virtual VectorXd evaluate(const VectorXd& aQueryVector) const override;

    /// @brief Evaluate the linear interpolator
    ///
    /// @code{.cpp}
    ///                     double values = linear.evaluate(5.0) ;
    /// @endcode
    ///
    /// @param aQueryValue An x value
    /// @return Vector of y values
    virtual double evaluate(const double& aQueryValue) const override;

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
