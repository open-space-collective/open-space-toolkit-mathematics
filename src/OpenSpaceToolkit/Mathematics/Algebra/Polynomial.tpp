////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/Algebra/Polynomial.tpp
/// @author         Remy Derollez <remy@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Algebra/Polynomial.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <cmath>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace math
{
namespace alg
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                template <class T>
                                Polynomial<T>::Polynomial                   (   const   Array<T>&                   aCoefficientsArray                          )
                                :   degree_(static_cast<int>(aCoefficientsArray.getSize()) - 1),
                                    coefficients_(aCoefficientsArray)
{

}

                                template <class T>
bool                            Polynomial<T>::operator ==                  (   const   Polynomial&                 aPolynomial                                 ) const
{
    return (degree_ == aPolynomial.getDegree()) && (coefficients_ == aPolynomial.getCoefficientsArray()) ;
}

                                template <class T>
bool                            Polynomial<T>::operator !=                  (   const   Polynomial&                 aPolynomial                                 ) const
{
    return !((*this) == aPolynomial) ;
}

//                                 template <class T>
// Polynomial                      Polynomial::operator +                      (   const   Polynomial&                 aPolynomial                                 ) const
// {

//     Polynomial polynomial = Polynomial::Zero() ;

//     return composite ;

// }

// Polynomial&                     Polynomial::operator +=                     (   const   Polynomial&                 aPolynomial                                 )
// {

// }

                                template <class U>
std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Polynomial<U>&              aPolynomial                                 )
{

    Array<U> coefficients = aPolynomial.getCoefficientsArray() ;
    Integer degree = aPolynomial.getDegree() ;

    ostk::core::utils::Print::Header(anOutputStream, "Polynomial") ;
    ostk::core::utils::Print::Line(anOutputStream) << coefficients[0] << "1" ;

    for (int index = 1 ; index < degree + 1 ; index ++)
    {
        ostk::core::utils::Print::Line(anOutputStream) << coefficients[index] << "X^" + std::to_string(index) ;
    }

    ostk::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

                                template <class T>
Integer                         Polynomial<T>::getDegree                    ( ) const
{

    return degree_ ;

}

                                template <class T>
Array<T>                        Polynomial<T>::getCoefficientsArray         ( ) const
{

    return coefficients_ ;

}

                                template <class T>
double                          Polynomial<T>::evaluateAt                   (   const   Real&                       aValue                                      )
{

    double result = coefficients_[0] ;

    for (int index = 1 ; index < degree_ + 1 ; index ++)
    {
        result += coefficients_[index] * std::pow((double)aValue, index) ;
    }

    return result ;

}
                                template <class T>
void                            Polynomial<T>::setCoefficientOfDegree       (   const   Integer&                    aDegree,
                                                                                const   T&                          aValue                                      )
{

    if (aDegree <= degree_)
    {
        coefficients_[aDegree] = aValue ;
    }

    else
    {
        throw ostk::core::error::runtime::Undefined("Polynomial") ; // TBI
    }

}

                                template <class T>
Polynomial<T>                   Zero                                        (   const   Integer&                    aDegree                                     )
{
    return Polynomial<T>(aDegree, Array<T>((Size)(aDegree + 1), 0.0)) ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
