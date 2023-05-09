// Copyright © Loft Orbital Solutions Inc.

#ifndef __OpenSpaceToolkit_Mathematics_Interpolator__
#define __OpenSpaceToolkit_Mathematics_Interpolator__

#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>

#include <OpenSpaceToolkit/Core/Types/Real.hpp>


namespace ostk
{
namespace math
{
namespace curvefitting
{
namespace interp
{


using ostk::core::types::Real ;
using ostk::core::types::Size ;

using ostk::math::obj::VectorXd ;


/// @brief                      Interpolator
///
///                             In mathematics, an interpolator is a type of estimator allowing to construct new data points based on a range of a discrete set
///                             of known data points.
///
/// @ref                        https://en.wikipedia.org/wiki/Interpolator.

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


}
}
}
}


#endif

