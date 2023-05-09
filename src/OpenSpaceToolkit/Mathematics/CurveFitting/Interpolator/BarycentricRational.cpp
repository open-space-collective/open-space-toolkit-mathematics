// Copyright © Loft Orbital Solutions Inc.

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/BarycentricRational.hpp>

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

                                BarycentricRational::BarycentricRational    (   const   VectorXd&                   anXVector,
                                                                                const   VectorXd&                   aYVector                                    )
                                :   interpolator_(anXVector.begin(), anXVector.end(), aYVector.begin())
{

    if (anXVector.size() != aYVector.size())
    {
        throw ostk::core::error::runtime::Wrong("Vector size", aYVector.size()) ;
    }

}

BarycentricRational*            BarycentricRational::clone                  ( ) const
{
    return new BarycentricRational(*this) ;
}

VectorXd                        BarycentricRational::evaluate               (   const   VectorXd&                   aQueryVector                                ) const
{

    VectorXd yOutput(aQueryVector.size()) ;

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = interpolator_(aQueryVector(i)) ;
    }

    return yOutput ;

}

double                          BarycentricRational::evaluate               (   const   double&                     aQueryValue                                 ) const
{

    return interpolator_(aQueryValue) ;

}
    

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
