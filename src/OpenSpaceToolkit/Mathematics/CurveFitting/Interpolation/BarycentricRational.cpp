////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/CurveFitting/Interpolation/BarycentricRational.cpp
/// @author         Vishwa Shah <vishwa@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolation/BarycentricRational.hpp>

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

                                BarycentricRational::BarycentricRational    (   const   VectorXd&                   x,
                                                                                const   VectorXd&                   y                                           )
                                :   interpolator_(x.begin(), x.end(), y.begin())
{

    if (x.size() != y.size())
    {
        throw ostk::core::error::runtime::Wrong("xVector.size()", "y.size()") ;
    }

}

BarycentricRational*            BarycentricRational::clone                  ( ) const
{
    return new BarycentricRational(*this) ;
}

VectorXd                        BarycentricRational::evaluate                (   const   VectorXd&                   xInput                                     ) const
{

    VectorXd yOutput(xInput.size()) ;

    for (int i = 0; i < xInput.size(); ++i)
    {
        yOutput(i) = evaluate(xInput(i)) ;
    }

    return yOutput ;

}

double                          BarycentricRational::evaluate                (   const   double&                     xInput                                     ) const
{

    return interpolator_(xInput) ;

}
    

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////