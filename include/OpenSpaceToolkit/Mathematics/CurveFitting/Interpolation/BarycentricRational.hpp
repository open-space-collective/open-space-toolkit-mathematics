////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/CurveFitting/7Interpolation/BarycentricRational.hpp
/// @author         Vishwa Shah <vishwa@loftorbital.com
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Mathematics_Interpolator_BarycentricRational__
#define __OpenSpaceToolkit_Mathematics_Interpolator_BarycentricRational__

#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>

#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <boost/math/interpolators/barycentric_rational.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace math
{
namespace curvefitting
{
namespace interp
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::Real ;
using ostk::core::types::Size ;

using ostk::math::obj::VectorXd ;

using boost::math::interpolators::barycentric_rational ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      BarycentricRational
///
///                             Barycentric rational interpolation is a high-accuracy interpolation method for non-uniformly spaced samples.
///                             It requires 𝑶(N) time for construction, and 𝑶(N) time for each evaluation.
///
/// @ref                        https://www.boost.org/doc/libs/1_81_0/libs/math/doc/html/math_toolkit/barycentric.html

class BarycentricRational
{

    public:

        /// @brief              Constructor
        ///
        /// @code
        ///                     BarycentricRational barycentricRational(x, y) ;
        /// @endcode
        ///
        /// @param              [in] x A vector of x values
        /// @param              [in] y A vector of y values
        ///
        /// @warning            The x values must be sorted in ascending order
        /// @warning            The x values must be equally spaced

                                BarycentricRational                                 (   const   VectorXd&                   x,
                                                                                        const   VectorXd&                   y                                           ) ;

        /// @brief              Clone barycentric rational
        ///
        /// @return             Pointer to cloned barycentric rational

        BarycentricRational*    clone                                       ( ) const ;

        /// @brief              Evaluate the spline
        ///
        /// @code
        ///                     VectorXd values = barycentricRational.evaluate({1.0, 5.0, 6.0}) ;
        /// @endcode
        ///
        /// @param              [in] xInput A vector of x values
        /// @return             Vector of y values

        VectorXd                evaluate                                    (   const   VectorXd&                   xInput                                      ) const ;
    
        /// @brief              Evaluate the spline
        ///
        /// @code
        ///                     double values = barycentricRational.evaluate(5.0) ;
        /// @endcode
        ///
        /// @param              [in] xInput An x value
        /// @return             Vector of y values

        double                  evaluate                                    (   const   double&                     xInput                                      ) const ;

    private:

        barycentric_rational<double> interpolator_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
