////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/Interpolation/LinearInterpolator.hpp
/// @author         Vishwa Shah <vishwa@loftorbital.com
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Mathematics_Interpolator_LinearInterpolator__
#define __OpenSpaceToolkit_Mathematics_Interpolator_LinearInterpolator__

#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/Size.hpp>
#include <OpenSpaceToolkit/Core/Types/Index.hpp>
#include <OpenSpaceToolkit/Core/Containers/Pair.hpp>

#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator.hpp>

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
using ostk::core::types::Index ;
using ostk::core::ctnr::Pair ;

using ostk::math::obj::VectorXd ;
using ostk::math::curvefitting::interp::Interpolator ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      LinearInterpolator
///
///                             In mathematics, linear interpolation is a method of curve fitting using linear polynomials to construct new data
///                             points within the range of a discrete set of known data points.
///
/// @ref                        https://en.wikipedia.org/wiki/Linear_interpolation#:~:text=In%20mathematics%2C%20linear%20interpolation%20is,set%20of%20known%20data%20points.

class LinearInterpolator: public Interpolator
{

    public:

        /// @brief              Constructor
        ///
        /// @code
        ///                     LinearInterpolator linear(x, y) ;
        /// @endcode
        ///
        /// @param              [in] anXVector A vector of x values
        /// @param              [in] aYVector A vector of y values
        ///
        /// @warning            The x values must be sorted in ascending order
        /// @warning            The x values must be equally spaced

                                LinearInterpolator                          (   const   VectorXd&                   anXVector,
                                                                                const   VectorXd&                   aYVector                                           ) ;

        /// @brief              Clone cubic spline 
        ///
        /// @return             Pointer to cloned cubic spline

        virtual LinearInterpolator*    clone                                ( ) const ;

        /// @brief              Evaluate the spline
        ///
        /// @code
        ///                     VectorXd values = linear.evaluate({1.0, 5.0, 6.0}) ;
        /// @endcode
        ///
        /// @param              [in] aQueryVector A vector of x values
        /// @return             Vector of y values

        VectorXd                evaluate                                    (   const   VectorXd&                   aQueryVector                                ) const ;
    
        /// @brief              Evaluate the spline
        ///
        /// @code
        ///                     double values = linear.evaluate(5.0) ;
        /// @endcode
        ///
        /// @param              [in] aQueryValue An x value
        /// @return             Vector of y values

        double                  evaluate                                    (   const   double&                     aQueryValue                                 ) const ;

    private:
    
        VectorXd                x_ ;
        VectorXd                y_ ;

        Pair<Index, Index>      findIndexRange                              (   const   double&                     aQueryValue                                 ) const ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
