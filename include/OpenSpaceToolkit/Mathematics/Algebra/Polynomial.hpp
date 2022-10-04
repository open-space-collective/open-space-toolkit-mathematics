////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/Algebra/Polynomial.hpp
/// @author         Remy Derollez <remy@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Mathematics_Algebra_Polynomial__
#define __OpenSpaceToolkit_Mathematics_Algebra_Polynomial__

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
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
using ostk::core::types::Integer ;
using ostk::core::types::Real ;
using ostk::core::types::String ;
using ostk::core::types::Size ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TBI: Polynomials with one indeterminate for now

/// @brief                      Expression consisting of inderterminates (belonging to a field of class T) and coefficients
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

        // Polynomial              operator +                                  (   const   Polynomial&                 aPolynomial                                 ) const ;

        /// @brief              Addition assignment operator (Polynomial addition)
        ///
        ///                     Add a polynomial with another polynomial.
        ///
        /// @param              [in] aPolynomial A polynomial
        /// @return             Reference to resulting polynomial

        // Polynomial&             operator +=                                 (   const   Polynomial&                 aPolynomial                                 ) ;

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

        /// @brief              Evaluate polynomial at value
        ///
        /// @code
        ///                     Polynomial<Real> polynomial = Polynomial<Real>({ 0.0, 1.0, 1.0 }) ;
        ///                     polynomial.evaluateAt(2.0) == Real(6.0) ;
        /// @endcode
        ///
        /// @return             Real

        double                  evaluateAt                                  (   const   Real&                       aValue                                      ) ;

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

    private:

        Integer                 degree_ ;
        Array<T>                coefficients_ ;

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
