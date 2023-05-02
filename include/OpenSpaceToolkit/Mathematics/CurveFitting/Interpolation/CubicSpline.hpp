////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/CurveFitting/Interpolation/CubicSpline.hpp
/// @author         Vishwa Shah <vishwa@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Mathematics_Interpolator_CubicSpline__
#define __OpenSpaceToolkit_Mathematics_Interpolator_CubicSpline__

#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator.hpp>

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
using ostk::math::curvefitting::interp::Interpolator ;

using boost::math::interpolators::cardinal_cubic_b_spline ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      CubicSpline
///
///                             A cubic Spline interpolator is a spline where each piece is a third-degree polynomial specified in Spline form, that is
///                             by its values and first derivatives at the end points of the corresponding domain interval.
///
/// @ref                        https://en.wikipedia.org/wiki/Cubic_Spline_spline#:~:text=In%20numerical%20analysis%2C%20a%20cubic,of%20the%20corresponding%20domain%20interval.

class CubicSpline: public Interpolator
{

    public:

        /// @brief              Constructor
        ///
        /// @code
        ///                     CubicSpline cubicSpline(x, y) ;
        /// @endcode
        ///
        /// @param              [in] anXVector A vector of x values
        /// @param              [in] aYVector A vector of y values
        ///
        /// @warning            The x values must be sorted in ascending order
        /// @warning            The x values must be equally spaced

                                CubicSpline                                 (   const   VectorXd&                   anXVector,
                                                                                const   VectorXd&                   aYVector                                    ) ;

        /// @brief              Constructor
        ///
        /// @code
        ///                     CubicSpline cubicSpline(y, x0, h) ;
        /// @endcode
        ///
        /// @param              [in] aYVector A vector of y values
        /// @param              [in] x0 The first x value
        /// @param              [in] h The spacing between x values
        ///
        /// @warning            The x values must be sorted in ascending order
        /// @warning            The x values must be equally spaced

                                CubicSpline                                 (   const   VectorXd&                   aYVector,
                                                                                const   Real&                       x0,
                                                                                const   Real&                       h                                           ) ;

        /// @brief              Clone cubic spline
        ///
        /// @return             Pointer to cloned cubic spline interpolator

        virtual CubicSpline*    clone                                       ( ) const ;

        /// @brief              Evaluate the cubic spline interpolator
        ///
        /// @code
        ///                     VectorXd values = cubicSpline.evaluate({1.0, 5.0, 6.0}) ;
        /// @endcode
        ///
        /// @param              [in] aQueryVector A vector of x values
        /// @return             Vector of y values

        VectorXd                evaluate                                    (   const   VectorXd&                   aQueryVector                                ) const ;

        /// @brief              Evaluate the cubic spline interpolator
        ///
        /// @code
        ///                     double values = cubicSpline.evaluate(5.0) ;
        /// @endcode
        ///
        /// @param              [in] aQueryValue An x value
        /// @return             Vector of y values

        double                  evaluate                                    (   const   double&                     aQueryValue                                 ) const ;

    private:

        cardinal_cubic_b_spline<double> interpolator_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
