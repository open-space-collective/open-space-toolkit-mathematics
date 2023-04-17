////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/CurveFitting/Interpolation/CubicSpline.cpp
/// @author         Vishwa Shah <vishwa@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolation/CubicSpline.hpp>

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

                                CubicSpline::CubicSpline                    (   const   VectorXd&                   x,
                                                                                const   VectorXd&                   y                                           )
{

    if (y.size() < 5)
    {
        throw ostk::core::error::runtime::Wrong("y") ;
    }

    if (x.size() != y.size())
    {
        throw ostk::core::error::runtime::Wrong("x and y") ;
    }

    const double h = x(1) - x(0) ;

    interpolator_ = boost::math::interpolators::cardinal_cubic_b_spline<double>(y.begin(), y.end(), x(0), h) ;

}

                                CubicSpline::CubicSpline                    (   const   VectorXd&                   y,
                                                                                const   Real&                       x0,
                                                                                const   Real&                       h                                           )
{

    if (y.size() < 5)
    {
        throw ostk::core::error::runtime::Wrong("y") ;
    }

    interpolator_ = boost::math::interpolators::cardinal_cubic_b_spline<double>(y.begin(), y.end(), x0, h) ;

}

CubicSpline*            CubicSpline::clone                                  ( ) const
{
    return new CubicSpline(*this) ;
}

VectorXd                        CubicSpline::evaluate                       (   const   VectorXd&                   xInput                                  ) const
{

    VectorXd yOutput(xInput.size()) ;

    for (int i = 0; i < xInput.size(); ++i)
    {
        yOutput(i) = evaluate(xInput(i)) ;
    }

    return yOutput ;

}

double                          CubicSpline::evaluate                       (   const   double&                     xInput                                  ) const
{

    return interpolator_(xInput) ;

}
    

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////