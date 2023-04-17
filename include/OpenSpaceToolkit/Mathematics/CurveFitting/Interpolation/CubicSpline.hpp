////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/Interpolation/CubicSpline.hpp
/// @author         Vishwa Shah <vishwa@loftorbital.com
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Mathematics_Interpolator_CubicSpline__
#define __OpenSpaceToolkit_Mathematics_Interpolator_CubicSpline__

#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>

#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <boost/math/interpolators/cardinal_cubic_b_spline.hpp>

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

using boost::math::interpolators::cardinal_cubic_b_spline ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      CubicSpline
///
///                             A cubic Spline interpolator is a spline where each piece is a third-degree polynomial specified in Spline form, that is
///                             by its values and first derivatives at the end points of the corresponding domain interval.
///
/// @ref                        https://en.wikipedia.org/wiki/Cubic_Spline_spline#:~:text=In%20numerical%20analysis%2C%20a%20cubic,of%20the%20corresponding%20domain%20interval.

class CubicSpline
{

    public:

        /// @brief              Constructor
        ///
        /// @code
        ///                     CubicSpline cubicSpline(x, y) ;
        /// @endcode
        ///
        /// @param              [in] x A vector of x values
        /// @param              [in] y A vector of y values
        ///
        /// @warning            The x values must be sorted in ascending order
        /// @warning            The x values must be equally spaced

                                CubicSpline                                 (   const   VectorXd&                   x,
                                                                                const   VectorXd&                   y                                           ) ;

        /// @brief              Constructor
        ///
        /// @code
        ///                     CubicSpline cubicSpline(y, x0, h) ;
        /// @endcode
        ///
        /// @param              [in] y A vector of y values
        /// @param              [in] x0 The first x value
        /// @param              [in] h The spacing between x values
        ///
        /// @warning            The x values must be sorted in ascending order
        /// @warning            The x values must be equally spaced

                                CubicSpline                                 (   const   VectorXd&                   y,
                                                                                const   Real&                       x0,
                                                                                const   Real&                       h                                           ) ;

        /// @brief              Clone barycentric rational
        ///
        /// @return             Pointer to cloned barycentric rational

        CubicSpline*    clone                                              ( ) const ;

        /// @brief              Evaluate the spline
        ///
        /// @code
        ///                     VectorXd values = cubicSpline.evaluate({1.0, 5.0, 6.0}) ;
        /// @endcode
        ///
        /// @param              [in] xInput A vector of x values
        /// @return             Vector of y values

        VectorXd                evaluate                                    (   const   VectorXd&                   xInput                                      ) const ;
    
        /// @brief              Evaluate the spline
        ///
        /// @code
        ///                     double values = cubicSpline.evaluate(5.0) ;
        /// @endcode
        ///
        /// @param              [in] xInput An x value
        /// @return             Vector of y values

        double                  evaluate                                    (   const   double&                     xInput                                      ) const ;

    private:

        boost::math::interpolators::cardinal_cubic_b_spline<double> interpolator_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
