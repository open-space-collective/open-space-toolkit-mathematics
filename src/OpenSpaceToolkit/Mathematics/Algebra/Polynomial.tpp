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
                                :  coefficients_(aCoefficientsArray)
{
    // this->normalize() ;
}

                                template <class T>
bool                            Polynomial<T>::operator ==                  (   const   Polynomial&                 aPolynomial                                 ) const
{
    return (coefficients_ == aPolynomial.getCoefficientsArray()) ;
}

                                template <class T>
bool                            Polynomial<T>::operator !=                  (   const   Polynomial&                 aPolynomial                                 ) const
{
    return !((*this) == aPolynomial) ;
}

                                template <class T>
Polynomial<T>                   Polynomial<T>::operator +                   (   const   Polynomial<T>&              aPolynomial                                 ) const
{

    // TBI: Figure out casting to be able to perform Polynomial<T> + Polynomial<U> when desirable
    // TBI: Generalize to Polynomial of Matrices and other types T

    Integer maximumDegree = std::max(this->getDegree(), aPolynomial.getDegree()) ;

    Polynomial<T> resultPolynomial = Polynomial<T>::Zero(maximumDegree) ;

    for (int degree = 0; degree < maximumDegree + 1; degree++)
    {

        T firstCoefficient = (degree <= this->getDegree()) ? this->accessCoefficientOfDegree(degree) : T(0.0) ;
        T secondCoefficient = (degree <= aPolynomial.getDegree()) ? aPolynomial.accessCoefficientOfDegree(degree) : T(0.0) ;

        resultPolynomial.setCoefficientOfDegree(degree, firstCoefficient + secondCoefficient) ;  // TBI: Should use atrribute directly

    }

    resultPolynomial.normalize() ;

    return resultPolynomial ;

}

                                template <class T>
Polynomial<T>&                  Polynomial<T>::operator +=                  (   const   Polynomial<T>&              aPolynomial                                 )
{

    Integer maximumDegree = std::max(this->getDegree(), aPolynomial.getDegree()) ;

    coefficients_.reserve(maximumDegree) ;

    for (int degree = 0; degree < maximumDegree + 1; degree++)
    {

        T firstCoefficient = (degree <= this->getDegree()) ? this->accessCoefficientOfDegree(degree) : T(0.0) ; // TBI: Should be output automatically by accessCoefficientOfDegree here tbh
        T secondCoefficient = (degree <= aPolynomial.getDegree()) ? aPolynomial.accessCoefficientOfDegree(degree) : T(0.0) ;

        coefficients_[degree] = firstCoefficient + secondCoefficient ;

    }

    this->normalize() ;

    return *this ;

}

                                template <class T>
Polynomial<T>                   Polynomial<T>::operator -                   (   const   Polynomial<T>&              aPolynomial                                 ) const
{

    // TBI: Figure out casting to be able to perform Polynomial<T> + Polynomial<U> when desirable
    // TBI: Generalize to Polynomial of Matrices and other types T

    Polynomial<T> oppositeSignCoefficientsPolynomial = Polynomial<T>(aPolynomial.getCoefficientsArray().map([] (const T& aCoefficient) -> T { return - aCoefficient ; })) ;

    Polynomial<T> resultPolynomial = this + oppositeSignCoefficientsPolynomial ;

    return resultPolynomial ;

}

                                template <class T>
Polynomial<T>&                  Polynomial<T>::operator -=                  (   const   Polynomial<T>&              aPolynomial                                 )
{

    Polynomial<T> oppositeSignCoefficientsPolynomial = Polynomial<T>(aPolynomial.getCoefficientsArray().map([] (const T& aCoefficient) -> T { return - aCoefficient ; })) ;

    this += oppositeSignCoefficientsPolynomial ;

    return *this ;

}

                                template <class T>
Polynomial<T>                   Polynomial<T>::operator *                   (   const   Polynomial<T>&              aPolynomial                                 ) const
{

    // TBI: Figure out casting to be able to perform Polynomial<T> * Polynomial<U> when desirable
    // TBI: Generalize to Polynomial of Matrices and other types T

    Integer newMaximumDegree = this->getDegree() + aPolynomial.getDegree() ;

    Polynomial<T> resultPolynomial = Polynomial<T>::Zero(newMaximumDegree) ;

    for (int degree = this->getDegree(); degree >= 0 ; degree--)
    {

        for (int anotherDegree = aPolynomial.getDegree(); anotherDegree >= 0; anotherDegree--)
        {

            Integer assignmentDegree = degree + anotherDegree ;

            T firstCoefficient = (degree <= this->getDegree()) ? this->accessCoefficientOfDegree(degree) : T(0.0) ;
            T secondCoefficient = (anotherDegree <= aPolynomial.getDegree()) ? aPolynomial.accessCoefficientOfDegree(anotherDegree) : T(0.0) ;

            resultPolynomial += Polynomial<T>::Monomial(assignmentDegree, firstCoefficient * secondCoefficient) ;

        }

    }

    resultPolynomial.normalize() ;

    return resultPolynomial ;

}

                                template <class T>
Polynomial<T>&                  Polynomial<T>::operator *=                  (   const   Polynomial<T>&              aPolynomial                                 )
{

    Polynomial<T> resultingPolynomial = (*this) * aPolynomial ;

    (*this) = resultingPolynomial ;  // TBI

    return *this ;

}

                                template <class T>
Polynomial<T>                   Polynomial<T>::operator ^                   (   const   Integer&                    aValue                                      ) const
{
    return this->pow(aValue) ;
}

                                template <class U>
std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Polynomial<U>&              aPolynomial                                 )
{

    Array<U> coefficients = aPolynomial.getCoefficientsArray() ;
    Integer degree = aPolynomial.getDegree() ;

    if (coefficients.isEmpty())
    {

        ostk::core::utils::Print::Header(anOutputStream, "Polynomial") ;
        ostk::core::utils::Print::Line(anOutputStream) << 0.0 << "1" ;

    }

    else
    {

        ostk::core::utils::Print::Header(anOutputStream, "Polynomial") ;
        ostk::core::utils::Print::Line(anOutputStream) << coefficients[0] << "1" ;

        if (degree > 0)
        {

            for (int index = 1 ; index < degree + 1 ; index ++)
            {
                ostk::core::utils::Print::Line(anOutputStream) << coefficients[index] << "X^" + std::to_string(index) ;
            }

        }

    }

    ostk::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

                                template <class T>
void                            Polynomial<T>::normalize                    ( )
{
    coefficients_.erase(std::find_if(coefficients_.rbegin(), coefficients_.rend(), [](const T& x)->bool { return x != T(0); }).base(), coefficients_.end());
}

                                template <class T>
Polynomial<T>                   Polynomial<T>::pow                          (   const   Integer&                    aValue                                      ) const
{

    if (aValue < 0)
    {
        throw ostk::core::error::RuntimeError("Negative exponent are not supported.") ;
    }

    else if (aValue == 0)
    {
        return Polynomial<T>::Zero(0) ;
    }

    else
    {

        Polynomial<T> resultingPolynomial = (*this) ;

        for (int i = 0; i < aValue; i++)
        {
            resultingPolynomial *= (*this) ;
        }

        return resultingPolynomial ;

    }

}

                                template <class T>
Integer                         Polynomial<T>::getDegree                    ( ) const
{

    if (coefficients_.isEmpty())
    {
        return 0 ;
    }

    return static_cast<int>(coefficients_.getSize()) - 1 ;

}

                                template <class T>
Array<T>                        Polynomial<T>::getCoefficientsArray         ( ) const
{

    return coefficients_ ;

}

                                template <class T>
T                               Polynomial<T>::accessCoefficientOfDegree    (   const   Integer&                    aDegree                                     ) const
{

    Integer degree = this->getDegree() ;

    if (aDegree > degree)
    {
        throw ostk::core::error::RuntimeError("Specified degree is larger than Polynomial maximum degree") ; // TBD
    }

    return coefficients_[aDegree] ;

}

                                template <class T>
double                          Polynomial<T>::evaluateAt                   (   const   Real&                       aValue                                      )
{

    double result = coefficients_[0] ;

    Integer degree = this->getDegree() ;

    for (int index = 1 ; index < degree + 1 ; index ++)
    {
        result += coefficients_[index] * std::pow((double)aValue, index) ;
    }

    return result ;

}
                                template <class T>
void                            Polynomial<T>::setCoefficientOfDegree       (   const   Integer&                    aDegree,
                                                                                const   T&                          aValue                                      )
{

    Integer degree = this->getDegree() ;

    if (aDegree <= degree)
    {
        coefficients_[aDegree] = aValue ;
    }

    else
    {
        throw ostk::core::error::runtime::Undefined("Coefficient of the Polynomial for specified degree") ; // TBI
    }

}

                                template <class T>
Polynomial<T>                   Polynomial<T>::Zero                         (   const   Integer&                    aDegree                                     )
{
    return Polynomial<T>(Array<T>((Size)(aDegree + 1), 0.0)) ;
}

                                template <class T>
Polynomial<T>                   Polynomial<T>::Monomial                     (   const   Integer&                    aDegree,
                                                                                const   T&                          aCoefficient                                )
{

    // TBI: Good display of inefficient storage with this constructor. Leverage list of (degree, coefficient) to deal better with sparse or dispersed polynomials
    // TBI: Could also leverage algebra on monomials and linear vector operations between monomial basis and coefficients, TBD

    Polynomial<T> monomial = Polynomial<T>::Zero(aDegree) ;
    monomial.setCoefficientOfDegree(aDegree, aCoefficient) ;

    return monomial ;

}

// TBI: Following static function should not depend on T
                                template <class T>
Polynomial<T>                   Polynomial<T>::Legendre                     (   const   Integer&                    aDegree                                     )
{

    // TBI: Temporary
    // TBI: Harcoding the lower degrees polynomials while figuring out the best way to fetch or compute the coefficients (boost, std, recurring suite)
    Map<Integer, Array<T>> legendrePolynomialsCoefficients =
    {
        { 1,  Array<T>({ 0.0, 1.0 }) },
        { 2,  Array<T>({ -1.0, 0.0, 3.0/2.0 }) },
        { 3,  Array<T>({ 0.0, -3.0, 0.0, 5.0/2.0 }) },
        { 4,  Array<T>({ 3.0/8.0, 0.0, -30.0/8.0, 0.0, 35.0/8.0 }) },
        { 5,  Array<T>({ 0.0, 15.0/8.0, 0.0, -70.0/8.0, 0.0, 63.0/8.0 }) },
        { 6,  Array<T>({ -5.0/16.0, 0.0, 105.0/16.0, 0.0, -315.0/16.0, 0.0, 231.0/16.0 }) },
        { 7,  Array<T>({ 0.0, -35.0/16.0, 0.0, 315.0/16.0, 0.0, -693.0/16.0, 0.0, 429.0/16.0 }) },
        { 8,  Array<T>({ 35.0/128.0, 0.0, -1260.0/128.0, 0.0, 6930.0/128.0, 0.0, -12012.0/128.0, 0.0, 6435.0/128.0 }) },
        { 9,  Array<T>({ 0.0, 315.0/128.0, 0.0, -4620.0/128.0, 0.0, 18018.0/128.0, 0.0, -25740.0/128.0, 0.0, 12155.0/128.0 }) },
        { 10, Array<T>({ -63.0/256.0, 0.0, 3465.0/256.0, 0.0, -30030.0/256.0, 0.0, 90090.0/256.0, 0.0, -109395.0/256.0, 0.0, 46189.0/256.0 }) },
    } ;

    if (aDegree < 0)
    {
        return Polynomial<T>::Zero(1) ;
    }

    else if (aDegree > 0 && aDegree < 11)
    {
        return Polynomial<T>(legendrePolynomialsCoefficients[aDegree]) ;
    }

    else
    {
        throw ostk::core::error::runtime::ToBeImplemented("Higer degree Legendre Polynommial.") ;
    }

}

                                template <class T>
Polynomial<T>                   Polynomial<T>::Hermite                      (   const   Integer&                    aDegree                                     )
{

    // TBI: Temporary
    // TBI: Harcoding the lower degrees polynomials while figuring out the best way to fetch or compute the coefficients (boost, std, recurring suite)
    Map<Integer, Array<T>> hermitePolynomialsCoefficients =
    {
        { 1,  Array<T>({ 0.0, 1.0 }) },
        { 2,  Array<T>({ -1.0, 0.0, 1.0 }) },
        { 3,  Array<T>({ 0.0, -3.0, 0.0, 1.0 }) },
        { 4,  Array<T>({ 3.0, 0.0, -6.0, 0.0, 1.0 }) },
        { 5,  Array<T>({ 0.0, 15.0, 0.0, -10.0, 0.0, 1.0 }) },
        { 6,  Array<T>({ -15.0, 0.0, 45.0, 0.0, -15.0, 0.0, 1.0 }) },
        { 7,  Array<T>({ 0.0, -105.0, 0.0, 105.0, 0.0, -21.0, 0.0, 1.0 }) },
        { 8,  Array<T>({ 105.0, 0.0, -420.0, 0.0, 210.0, 0.0, -28.0, 0.0, 1.0 }) },
        { 9,  Array<T>({ 0.0, 945.0, 0.0, -1260.0, 0.0, 378.0, 0.0, -36.0, 0.0, 1.0 }) },
        { 10, Array<T>({ -945.0, 0.0, 4725.0, 0.0, -3150.0, 0.0, 630.0, 0.0, -45.0, 0.0, 1.0 }) },
    } ;

    if (aDegree < 0)
    {
        return Polynomial<T>::Zero(1) ;
    }

    else if (aDegree > 0 && aDegree < 11)
    {
        return Polynomial<T>(hermitePolynomialsCoefficients[aDegree]) ;
    }

    else
    {
        throw ostk::core::error::runtime::ToBeImplemented("Higer degree Legendre Polynommial.") ;
    }

}

// Leverage Ref.: https://www.boost.org/doc/libs/1_69_0/boost/math/tools/polynomial.hpp for Chebyshev

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
