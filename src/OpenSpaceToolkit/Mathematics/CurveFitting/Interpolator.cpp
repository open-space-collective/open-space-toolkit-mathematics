////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/CubicSpline.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/BarycentricRational.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>

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

                                Interpolator::~Interpolator                 ( )
{

}

double                          Interpolator::evaluate                      (   const   double&                     aQueryValue                                 ) const
{

    using ostk::math::curvefitting::interp::CubicSpline ;
    using ostk::math::curvefitting::interp::BarycentricRational ;

    if (const CubicSpline* interpolatorPtr = dynamic_cast<const CubicSpline*>(this))
    {
        return interpolatorPtr->evaluate(aQueryValue) ;
    }

    if (const BarycentricRational* interpolatorPtr = dynamic_cast<const BarycentricRational*>(this))
    {
        return interpolatorPtr->evaluate(aQueryValue) ;
    }

    throw ostk::core::error::runtime::ToBeImplemented("Interpolator :: evaluate") ;

    return 0.0 ;

}

VectorXd                        Interpolator::evaluate                      (   const   VectorXd&                   aQueryVector                                ) const
{

    using ostk::math::curvefitting::interp::CubicSpline ;
    using ostk::math::curvefitting::interp::BarycentricRational ;

    if (const CubicSpline* interpolatorPtr = dynamic_cast<const CubicSpline*>(this))
    {
        return interpolatorPtr->evaluate(aQueryVector) ;
    }

    if (const BarycentricRational* interpolatorPtr = dynamic_cast<const BarycentricRational*>(this))
    {
        return interpolatorPtr->evaluate(aQueryVector) ;
    }

    throw ostk::core::error::runtime::ToBeImplemented("Interpolator :: evaluate") ;

    return VectorXd::Zero(aQueryVector.size()) ;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
