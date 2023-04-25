////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/Interpolation/CubicSpline.hpp
/// @author         Vishwa Shah <vishwa@loftorbital.com
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Mathematics_Interpolator__
#define __OpenSpaceToolkit_Mathematics_Interpolator__

#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>

#include <OpenSpaceToolkit/Core/Types/Real.hpp>

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Interpolator
///
///                             A cubic Spline interpolator is a spline where each piece is a third-degree polynomial specified in Spline form, that is
///                             by its values and first derivatives at the end points of the corresponding domain interval.
///
/// @ref                        https://en.wikipedia.org/wiki/Cubic_Spline_spline#:~:text=In%20numerical%20analysis%2C%20a%20cubic,of%20the%20corresponding%20domain%20interval.

class Interpolator
{

    public:

        /// @brief              Default constructor
        ///
                                Interpolator                                ( ) = default ;

        /// @brief              Destructor (pure virtual)

        virtual                 ~Interpolator                               ( ) = 0 ;

        /// @brief              Clone interpolator
        ///
        /// @return             Pointer to cloned interpolator

        virtual Interpolator*   clone                                       ( ) const = 0 ;

        /// @brief              Evaluate the interpolator
        ///
        /// @param              [in] aQueryVector A vector of x values
        /// @return             Vector of y values

        virtual VectorXd        evaluate                                    (   const   VectorXd&                   aQueryVector                                ) const ;
    
        /// @brief              Evaluate the interpolator
        ///
        /// @param              [in] aQueryValue An x value
        /// @return             Vector of y values

        virtual double          evaluate                                    (   const   double&                     aQueryValue                                 ) const ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
