////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/Algebra/Polynomial.hpp
/// @author         Remy Derollez <remy@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Mathematics_Algebra_Polynomial__
#define __OpenSpaceToolkit_Mathematics_Algebra_Polynomial__

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Map.hpp>
#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Types/Size.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace math
{
namespace alg
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace types = ostk::core::types ;
namespace ctnr = ostk::core::ctnr ;

using ostk::core::ctnr::Array ;
using ostk::core::ctnr::Map ;
using ostk::core::types::Integer ;
using ostk::core::types::Real ;
using ostk::core::types::String ;
using ostk::core::types::Size ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TBI: Polynomials with one indeterminate for now

/// @brief                      Expression consisting of inderterminates and coefficients (belonging to a field of class T)
///
/// @ref                        https://en.wikipedia.org/wiki/Polynomial

template <class T>
class Polynomial
{

    public:

        /// @brief              Constructor
        ///
        /// @code
        ///                     Polynomial<Real> polynomial({ 0.0, 1.0, 3.5 }) ;
        /// @endcode
        ///
        /// @param              [in] aCoefficientsArray An array of coefficients

                                Polynomial                                  (   const   Array<T>&                   aCoefficientsArray                          ) ;

        /// @brief              Equal to operator
        ///
        /// @code
        ///                     Polynomial<Real>({ 0.0, 1.0, 1.0 }) == Polynomial<Real>({ 0.0, 1.0, 1.0 }) ; // True
        /// @endcode
        ///
        /// @param              [in] aPolynomial A Polynomial
        /// @return             True if polynomials are equal

        bool                    operator ==                                 (   const   Polynomial&                 aPolynomial                                 ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     Polynomial<Real>({ 0.0, 1.0, 1.0 }) != Polynomial<Real>({ 0.0, 1.0 }); // True
        /// @endcode
        ///
        /// @param              [in] anPolynomial An Polynomial
        /// @return             True if Polynomials are not equal

        bool                    operator !=                                 (   const   Polynomial&                 aPolynomial                                 ) const ;

        /// @brief              Addition operator
        ///
        ///                     Add a polynomial with another polynomial.
        ///
        /// @param              [in] aPolynomial A polynomial
        /// @return             Resulting polynomial

        Polynomial<T>           operator +                                  (   const   Polynomial<T>&              aPolynomial                                 ) const ;

        /// @brief              Addition assignment operator (Polynomial addition)
        ///
        ///                     Add a polynomial with another polynomial.
        ///
        /// @param              [in] aPolynomial A polynomial
        /// @return             Reference to resulting polynomial

        Polynomial<T>&          operator +=                                 (   const   Polynomial<T>&              aPolynomial                                 ) ;

        /// @brief              Substraction operator
        ///
        ///                     Substract another polynomial from a polynomial.
        ///
        /// @param              [in] aPolynomial A polynomial
        /// @return             Resulting polynomial

        Polynomial<T>           operator -                                  (   const   Polynomial<T>&              aPolynomial                                 ) const ;

        /// @brief              Substraction assignment operator (Polynomial substraction)
        ///
        ///                     Substract another polynomial from a polynomial.
        ///
        /// @param              [in] aPolynomial A polynomial
        /// @return             Reference to resulting polynomial

        Polynomial<T>&          operator -=                                 (   const   Polynomial<T>&              aPolynomial                                 ) ;

        /// @brief              Multiplication operator
        ///
        ///                     Multiply a polynomial with another polynomial.
        ///
        /// @param              [in] aPolynomial A polynomial
        /// @return             Resulting polynomial

        Polynomial<T>           operator *                                  (   const   Polynomial<T>&              aPolynomial                                 ) const ;

        /// @brief              Multiplication assigment operator (Polynomial multiplication)
        ///
        ///                     Multiply a polynomial with another polynomial.
        ///
        /// @param              [in] aPolynomial A polynomial
        /// @return             Reference to resulting polynomial

        Polynomial<T>&           operator *=                                (   const   Polynomial<T>&              aPolynomial                                 ) ;

        /// @brief              Power operator
        ///
        ///                     Raise a polynomial to a specified power value
        ///
        /// @param              [in] aValue A value (Integer)
        /// @return             Polynomial

        Polynomial<T>           operator ^                                  (   const   Integer&                    aValue                                      ) const ;

        /// @brief              Get polynomial degree
        ///
        /// @code
        ///                     Polynomial<Real> polynomial = Polynomial<Real>({ 0.0, 1.0, 1.0 }) ;
        ///                     polynomial.getDegree() == 2 ;
        /// @endcode
        ///
        /// @return             Polynomial degree (Integer)

        Integer                 getDegree                                   ( ) const ;

        /// @brief              Get polynomial coefficients
        ///
        /// @code
        ///                     Polynomial<Real> polynomial = Polynomial<Real>({ 0.0, 1.0, 1.0 }) ;
        ///                     polynomial.getCoefficientsArray() == { 0.0, 1.0, 1.0 } ;
        /// @endcode
        ///
        /// @return             Polynomial coefficients array

        Array<T>                getCoefficientsArray                        ( ) const ;

        /// @brief              Access polynomial coefficient at specified degree
        ///
        /// @code
        ///                     Polynomial<Real> polynomial = Polynomial<Real>({ 0.0, 1.0, 1.0 }) ;
        ///                     polynomial.accessCoefficientForDegree(1) == 1.0 ;
        /// @endcode
        ///
        /// @return             Polynomial coefficient

        T                       accessCoefficientOfDegree                   (   const   Integer&                    aDegree                                     ) const ;

        /// @brief              Evaluate polynomial at value
        ///
        /// @code
        ///                     Polynomial<Real> polynomial = Polynomial<Real>({ 0.0, 1.0, 1.0 }) ;
        ///                     polynomial.evaluateAt(2.0) == Real(6.0) ;
        /// @endcode
        ///
        /// @return             Real

        double                  evaluateAt                                  (   const   Real&                       aValue                                      ) ;

        /// @brief              Normalize polynomial
        ///
        /// @code
        ///                     Remove zero coefficients
        ///                     polynomial.normalize() ;
        /// @endcode
        ///
        /// @return             Nothing

        void                    normalize                                   ( )  ;

        /// @brief              Get power
        ///
        /// @code
        ///                     polynomial.pow(2) ;
        /// @endcode
        /// @param              [in] aValue A power value
        /// @return             Power

        Polynomial<T>           pow                                         (   const   Integer&                    aValue                                      ) const ;

        /// @brief              Output stream operator
        ///
        /// @code
        ///                     Polynomial<Real> Polynomial({ 0.0, 1.0, 2.0 }) ;
        ///                     std::cout << Polynomial ;
        /// @endcode
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] aPolynomial A Polynomial
        /// @return             A reference to output stream

                                template <class U>
        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Polynomial<U>&              aPolynomial                                 ) ;

        /// @brief              Polynomial coefficient setter
        ///
        /// @param              [in] aDegree A coefficient degree

        void                    setCoefficientOfDegree                      (   const   Integer&                    aDegree,
                                                                                const   T&                          aValue                                      ) ;

        /// @brief              Constructs Polynomial with zero coefficients up to specified degree
        ///
        /// @code
        ///                     Polynomial<Real> polynomial = Polynomial<Real>::Zero(2) ; // 0 + 0 * X^1 + 0 * X^2
        /// @endcode
        ///
        /// @return             Polynomial with zero coefficients

        static Polynomial<T>    Zero                                        (   const   Integer&                    aDegree                                     ) ;

        /// @brief              Constructs Monomial of specified degree with specified coefficient
        ///
        /// @code
        ///                     Polynomial<Real> polynomial = Polynomial<Real>::Monomial(2, 3.2) ; //  3.2 * X^2
        /// @endcode
        ///
        /// @return             Monomial

        static Polynomial<T>    Monomial                                    (   const   Integer&                    aDegree,
                                                                                const   T&                          aCoefficient                                ) ;

        /// @brief              Constructs Legendre Polynomial of the first kind of specific degree
        ///
        /// @code
        ///                     Polynomial<Real> polynomial = Polynomial<Real>::Legendre(2) ;
        /// @endcode
        ///
        /// @return             Legendre Polynomial

        static Polynomial<T>    Legendre                                    (   const   Integer&                    aDegree                                     ) ;

        /// @brief              Constructs "Probabilistic" Hermite Polynomial of specified degree
        ///
        /// @code
        ///                     Polynomial<Real> polynomial = Polynomial<Real>::Hermite(3) ;
        /// @endcode
        ///
        /// @return             Legendre Polynomial

        static Polynomial<T>    Hermite                                     (   const   Integer&                    aDegree                                     ) ;

        /// @brief              Constructs Laguerre Polynomial of the first kind of specific degree
        ///
        /// @code
        ///                     Polynomial<Real> polynomial = Polynomial<Real>::Laguerre(4) ;
        /// @endcode
        ///
        /// @return             Laguerre Polynomial

        static Polynomial<T>    Laguerre                                    (   const   Integer&                    aDegree                                     ) ;

        /// @brief              Constructs Chebyshev Polynomial of the first kind of specific degree
        ///
        /// @code
        ///                     Polynomial<Real> polynomial = Polynomial<Real>::Chebyshev(1) ;
        /// @endcode
        ///
        /// @return             Chebyshev Polynomial

        static Polynomial<T>    Chebyshev                                   (   const   Integer&                    aDegree                                     ) ;

    private:

        // TBI: Should use a representation that is less inefficient for sparse polynomials
        Array<T>                coefficients_ ; // Sorted in ascending order

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Algebra/Polynomial.tpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
