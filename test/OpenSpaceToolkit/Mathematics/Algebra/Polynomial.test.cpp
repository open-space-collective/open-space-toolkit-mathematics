////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/Algebra/Polynomial.test.cpp
/// @author         Remy Derollez <remy@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Algebra/Polynomial.hpp>
#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Mathematics_Algebra_Polynomial, Constructor)
{

    using ostk::core::types::Integer ;
    using ostk::core::types::Real ;
    using ostk::math::alg::Polynomial ;

    {

        EXPECT_NO_THROW(Polynomial<Real>({ 1.0, 3.0, 4.0, 2.3, 4.956789 })) ;
        EXPECT_NO_THROW(Polynomial<Integer>({ 1, 2, 3, 4, 5, 6, 7 })) ;
        EXPECT_NO_THROW(Polynomial<Integer>({})) ; // TBI

    }

}

TEST (OpenSpaceToolkit_Mathematics_Algebra_Polynomial, EqualToOperator)
{

    using ostk::core::types::Integer ;
    using ostk::core::types::Real ;
    using ostk::math::alg::Polynomial ;

    {

        Polynomial<Real> polynomial = Polynomial<Real>({ 1.0, 3.0, 4.0, 2.3, 4.956789 }) ;

        EXPECT_TRUE(polynomial == polynomial) ;

    }

    {

        Polynomial<Real> polynomial = Polynomial<Real>({ 1.0, 3.0, 4.0, 2.3 }) ;
        Polynomial<Real> anotherPolynomial = Polynomial<Real>({ 1.0, 3.0, 4.0, 2.1 }) ;

        EXPECT_FALSE(polynomial == anotherPolynomial) ;

    }

    {

        Polynomial<Real> polynomial = Polynomial<Real>({ 1.0, 3.0, 4.0 }) ;
        Polynomial<Real> anotherPolynomial = Polynomial<Real>({ 1.0, 4.0, 3.0 }) ;

        EXPECT_FALSE(polynomial == anotherPolynomial) ;

    }

    {

        Polynomial<Real> polynomial = Polynomial<Real>({ 1.0, 3.0, 4.0 }) ;
        Polynomial<Real> anotherPolynomial = Polynomial<Real>({ 1.0, 3.0 }) ;

        EXPECT_FALSE(polynomial == anotherPolynomial) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Algebra_Polynomial, NotEqualToOperator)
{

    using ostk::core::types::Integer ;
    using ostk::core::types::Real ;
    using ostk::math::alg::Polynomial ;

    {

        Polynomial<Real> polynomial = Polynomial<Real>({ 1.0, 3.0, 4.0, 2.3, 4.956789 }) ;

        EXPECT_FALSE(polynomial != polynomial) ;

    }

    {

        Polynomial<Real> polynomial = Polynomial<Real>({ 1.0, 3.0, 4.0, 2.3, 4.956789 }) ;

        EXPECT_FALSE(polynomial != polynomial) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Algebra_Polynomial, AdditionOperator)
{

    using ostk::core::ctnr::Array ;

    using ostk::core::types::Integer ;
    using ostk::core::types::Real ;
    using ostk::math::alg::Polynomial ;

    {

        Array<Real> coefficientsArray = Array<Real>({ 1.0, 3.0, 4.0, 2.3, 4.956789 }) ;

        Polynomial<Real> polynomial = Polynomial<Real>(coefficientsArray) ;

        EXPECT_EQ(Polynomial<Real>(coefficientsArray.map<Real>([] (const Real& aReal) -> Real { return aReal + aReal ; })), polynomial + polynomial) ;

    }

    {

        Polynomial<Real> aPolynomial = Polynomial<Real>({ 1.0, 3.0, 4.0, 2.3, 4.956789 }) ;
        Polynomial<Real> anotherPolynomial = Polynomial<Real>({ -1.0, 3.0, -4.0 }) ;

        Polynomial<Real> resultingPolynomial = aPolynomial + anotherPolynomial ;

        EXPECT_EQ(4, resultingPolynomial.getDegree()) ;
        EXPECT_EQ(0.0, resultingPolynomial.accessCoefficientOfDegree(0)) ;
        EXPECT_EQ(6.0, resultingPolynomial.accessCoefficientOfDegree(1)) ;
        EXPECT_EQ(0.0, resultingPolynomial.accessCoefficientOfDegree(2)) ;
        EXPECT_EQ(2.3, resultingPolynomial.accessCoefficientOfDegree(3)) ;
        EXPECT_EQ(4.956789, resultingPolynomial.accessCoefficientOfDegree(4)) ;

    }

    {

        Polynomial<Real> aPolynomial = Polynomial<Real>({ 1.0, 3.0, 4.0, 2.3, 4.956789 }) ;
        Polynomial<Real> anotherPolynomial = Polynomial<Real>({ -1.0, 3.0, 0.0, 0.0, -4.956789 }) ;

        Polynomial<Real> resultingPolynomial = aPolynomial + anotherPolynomial ;

        EXPECT_EQ(3, resultingPolynomial.getDegree()) ;
        EXPECT_EQ(0.0, resultingPolynomial.accessCoefficientOfDegree(0)) ;
        EXPECT_EQ(6.0, resultingPolynomial.accessCoefficientOfDegree(1)) ;
        EXPECT_EQ(4.0, resultingPolynomial.accessCoefficientOfDegree(2)) ;
        EXPECT_EQ(2.3, resultingPolynomial.accessCoefficientOfDegree(3)) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Algebra_Polynomial, AdditionAssignmentOperator)
{

    using ostk::core::ctnr::Array ;

    using ostk::core::types::Integer ;
    using ostk::core::types::Real ;
    using ostk::math::alg::Polynomial ;

    {

        Array<Real> coefficientsArray = Array<Real>({ 1.0, 3.0, 4.0, 2.3, 4.956789 }) ;

        Polynomial<Real> polynomial = Polynomial<Real>(coefficientsArray) ;

        polynomial += polynomial ;

        EXPECT_EQ(Polynomial<Real>(coefficientsArray.map<Real>([] (const Real& aReal) -> Real { return aReal + aReal ; })), polynomial) ;

    }

    {

        Polynomial<Real> aPolynomial = Polynomial<Real>({ 1.0, 3.0, 4.0, 2.3, 4.956789 }) ;
        Polynomial<Real> anotherPolynomial = Polynomial<Real>({ -1.0, 3.0, -4.0 }) ;

        aPolynomial += anotherPolynomial ;

        EXPECT_EQ(4, aPolynomial.getDegree()) ;
        EXPECT_EQ(0.0, aPolynomial.accessCoefficientOfDegree(0)) ;
        EXPECT_EQ(6.0, aPolynomial.accessCoefficientOfDegree(1)) ;
        EXPECT_EQ(0.0, aPolynomial.accessCoefficientOfDegree(2)) ;
        EXPECT_EQ(2.3, aPolynomial.accessCoefficientOfDegree(3)) ;
        EXPECT_EQ(4.956789, aPolynomial.accessCoefficientOfDegree(4)) ;

    }

    {

        Polynomial<Real> aPolynomial = Polynomial<Real>({ 1.0, 3.0, 4.0, 2.3, 4.956789 }) ;
        Polynomial<Real> anotherPolynomial = Polynomial<Real>({ -1.0, 3.0, 0.0, 0.0, -4.956789 }) ;

        aPolynomial += anotherPolynomial ;

        EXPECT_EQ(3, aPolynomial.getDegree()) ;
        EXPECT_EQ(0.0, aPolynomial.accessCoefficientOfDegree(0)) ;
        EXPECT_EQ(6.0, aPolynomial.accessCoefficientOfDegree(1)) ;
        EXPECT_EQ(4.0, aPolynomial.accessCoefficientOfDegree(2)) ;
        EXPECT_EQ(2.3, aPolynomial.accessCoefficientOfDegree(3)) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Algebra_Polynomial, MultiplicationOperator)
{

    using ostk::core::ctnr::Array ;

    using ostk::core::types::Integer ;
    using ostk::core::types::Real ;
    using ostk::math::alg::Polynomial ;

    {

        Polynomial<Real> polynomial = Polynomial<Real>({ 1.0, 1.0, 1.0, 2.0 }) ;
        Polynomial<Real> anotherPolynomial = Polynomial<Real>({ 0.0, 2.0 }) ;

        Polynomial<Real> resultingPolynomial = polynomial * anotherPolynomial ;

        EXPECT_EQ(polynomial.getDegree() + anotherPolynomial.getDegree(), resultingPolynomial.getDegree()) ;
        EXPECT_EQ(Array<Real>({ 0.0, 2.0, 2.0, 2.0, 4.0 }), resultingPolynomial.getCoefficientsArray()) ;

    }

    {

        Polynomial<Real> polynomial = Polynomial<Real>({ 1.0, 1.0, 1.0, 2.0 }) ;

        Polynomial<Real> resultingPolynomial = polynomial * polynomial ;

        EXPECT_EQ(polynomial.getDegree() * 2, resultingPolynomial.getDegree()) ;
        EXPECT_EQ(Array<Real>({ 1.0, 2.0, 3.0, 6.0, 5.0, 4.0, 4.0 }), resultingPolynomial.getCoefficientsArray()) ;

    }

    {

        Polynomial<Real> aPolynomial = Polynomial<Real>({ 1.0, 3.0, 4.0, 2.3, 4.956789 }) ;
        Polynomial<Real> anotherPolynomial = Polynomial<Real>({ -1.0, 3.0, -4.0 }) ;

        Polynomial<Real> resultingPolynomial = aPolynomial * anotherPolynomial ;

        EXPECT_EQ(6, resultingPolynomial.getDegree()) ;
        // EXPECT_EQ(Array<Real>({ -1.0, 0.0, 1.0, -2.3, -14.0568, 5.67037, -19.8272 }), resultingPolynomial.getCoefficientsArray()) ; // TBI

    }

    {

        Polynomial<Real> aPolynomial = Polynomial<Real>({ 1.0, 3.0, 4.0, 2.3, 4.956789 }) ;

        Polynomial<Real> resultingPolynomial = aPolynomial * Polynomial<Real>::Zero(2) ;

        EXPECT_EQ(0, resultingPolynomial.getDegree()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Algebra_Polynomial, MultiplicationAssignmentOperator)
{

    using ostk::core::ctnr::Array ;

    using ostk::core::types::Integer ;
    using ostk::core::types::Real ;
    using ostk::math::alg::Polynomial ;

    {

        Polynomial<Real> aPolynomial = Polynomial<Real>({ 1.0, 1.0, 1.0, 2.0 }) ;
        Polynomial<Real> anotherPolynomial = Polynomial<Real>({ 0.0, 2.0 }) ;

        aPolynomial *= anotherPolynomial ;

        EXPECT_EQ(4, aPolynomial.getDegree()) ;
        EXPECT_EQ(Array<Real>({ 0.0, 2.0, 2.0, 2.0, 4.0 }), aPolynomial.getCoefficientsArray()) ;

    }

    {

        Polynomial<Real> aPolynomial = Polynomial<Real>({ 1.0, 1.0, 1.0, 2.0 }) ;

        aPolynomial *= aPolynomial ;

        EXPECT_EQ(6, aPolynomial.getDegree()) ;
        EXPECT_EQ(Array<Real>({ 1.0, 2.0, 3.0, 6.0, 5.0, 4.0, 4.0 }), aPolynomial.getCoefficientsArray()) ;

    }

    {

        Polynomial<Real> aPolynomial = Polynomial<Real>({ 1.0, 3.0, 4.0, 2.3, 4.956789 }) ;
        Polynomial<Real> anotherPolynomial = Polynomial<Real>({ -1.0, 3.0, -4.0 }) ;

        aPolynomial *= anotherPolynomial ;

        EXPECT_EQ(6, aPolynomial.getDegree()) ;
        // EXPECT_EQ(Array<Real>({ -1.0, 0.0, 1.0, -2.3, -14.0568, 5.67037, -19.8272 }), resultingPolynomial.getCoefficientsArray()) ; // TBI

    }

    {

        Polynomial<Real> aPolynomial = Polynomial<Real>({ 1.0, 3.0, 4.0, 2.3, 4.956789 }) ;

        aPolynomial *= Polynomial<Real>::Zero(2) ;

        EXPECT_EQ(0, aPolynomial.getDegree()) ;

    }

}

// TEST (OpenSpaceToolkit_Mathematics_Algebra_Polynomial, PowerOperator)
// {

//     using ostk::core::ctnr::Array ;

//     using ostk::core::types::Integer ;
//     using ostk::core::types::Real ;
//     using ostk::math::alg::Polynomial ;

//     {

//         Array<Real> coefficientsArray = Array<Real>({ 0.0, 1.0 });
//         Polynomial<Real> aPolynomial = Polynomial<Real>(coefficientsArray) ;

//         EXPECT_EQ(0, (aPolynomial^0).getDegree()) ;
//         EXPECT_EQ(Array<Real>({ 0.0 }), (aPolynomial^0).getCoefficientsArray()) ;

//     }

//     {

//         Array<Real> coefficientsArray = Array<Real>({ 0.0, 1.0 });
//         Polynomial<Real> aPolynomial = Polynomial<Real>(coefficientsArray) ;

//         for (int exponent = 1; exponent < 10; exponent ++)
//         {

//             EXPECT_EQ(exponent, (aPolynomial^exponent).getDegree()) ;
//             EXPECT_EQ(coefficientsArray.insert(coefficientsArray.begin(), 0.0), (aPolynomial^exponent).getCoefficientsArray()) ;

//         }

//     }

// }

TEST (OpenSpaceToolkit_Mathematics_Algebra_Polynomial, GetDegree)
{

    using ostk::core::types::Integer ;
    using ostk::core::types::Real ;
    using ostk::math::alg::Polynomial ;

    {

        Polynomial<Real> polynomial = Polynomial<Real>({ 1.0, 3.0, 4.0, 2.3, 4.956789 }) ;

        EXPECT_EQ(4, polynomial.getDegree()) ;

    }

    {

        Polynomial<Real> polynomial = Polynomial<Real>({ 1.0 }) ;

        EXPECT_EQ(0, polynomial.getDegree()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Algebra_Polynomial, GetCoefficientsArray)
{

    using ostk::core::types::Integer ;
    using ostk::core::types::Real ;
    using ostk::core::ctnr::Array ;

    using ostk::math::alg::Polynomial ;

    {

        Array<Real> coefficientsArray = { 1.0, 3.0, 4.0, 2.3, 4.956789 } ;

        Polynomial<Real> polynomial = Polynomial<Real>(coefficientsArray) ;

        EXPECT_EQ(coefficientsArray, polynomial.getCoefficientsArray()) ;
        EXPECT_EQ(5, polynomial.getCoefficientsArray().getSize()) ;

    }

    {

        Array<Real> coefficientsArray = Array<Real>::Empty() ;

        Polynomial<Real> polynomial = Polynomial<Real>(coefficientsArray) ;

        EXPECT_EQ(coefficientsArray, polynomial.getCoefficientsArray()) ;
        EXPECT_EQ(0, polynomial.getCoefficientsArray().getSize()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Algebra_Polynomial, AccessCoefficientOfDegree)
{

    using ostk::core::types::Integer ;
    using ostk::core::types::Real ;
    using ostk::core::ctnr::Array ;

    using ostk::math::alg::Polynomial ;

    {

        Array<Real> coefficientsArray = { 1.0, 3.0, 4.0, 2.3, 4.956789 } ;

        Polynomial<Real> polynomial = Polynomial<Real>(coefficientsArray) ;

        for (int degree = 0; degree < polynomial.getDegree(); degree++)
        {
            EXPECT_EQ(coefficientsArray[degree], polynomial.accessCoefficientOfDegree(degree)) ;
        }

        EXPECT_ANY_THROW(polynomial.accessCoefficientOfDegree(polynomial.getDegree() + 1)) ;
        EXPECT_ANY_THROW(polynomial.accessCoefficientOfDegree(polynomial.getDegree() + 2)) ;
        EXPECT_ANY_THROW(polynomial.accessCoefficientOfDegree(polynomial.getDegree() + 3)) ;

    }

    // {

    //     Array<Real> coefficientsArray = Array<Real>::Empty() ;

    //     Polynomial<Real> polynomial = Polynomial<Real>(coefficientsArray) ;

    //     EXPECT_ANY_THROW(polynomial.accessCoefficientOfDegree(polynomial.getDegree())) ;
    //     EXPECT_ANY_THROW(polynomial.accessCoefficientOfDegree(polynomial.getDegree() + 1)) ;

    // }

}

TEST (OpenSpaceToolkit_Mathematics_Algebra_Polynomial, EvaluateAt)
{

    using ostk::core::types::Integer ;
    using ostk::core::types::Real ;
    using ostk::core::ctnr::Array ;

    using ostk::math::alg::Polynomial ;

    {

        Array<Real> coefficientsArray = { 1.0, 3.0, 4.0 } ;

        Polynomial<Real> polynomial = Polynomial<Real>(coefficientsArray) ;

        EXPECT_EQ(1.0, polynomial.evaluateAt(0.0)) ;
        EXPECT_EQ(8.0, polynomial.evaluateAt(1.0)) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Algebra_Polynomial, Zero)
{

    using ostk::core::types::Real ;
    using ostk::core::ctnr::Array ;

    using ostk::math::alg::Polynomial ;

    {

        Polynomial<Real> polynomial = Polynomial<Real>::Zero(5) ;

        EXPECT_EQ(5, polynomial.getDegree()) ;
        EXPECT_EQ(Array<Real>({ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }), polynomial.getCoefficientsArray()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Algebra_Polynomial, Monomial)
{

    using ostk::core::types::Real ;
    using ostk::core::ctnr::Array ;

    using ostk::math::alg::Polynomial ;

    {

        Polynomial<Real> polynomial = Polynomial<Real>::Monomial(0, 0.0) ;

        EXPECT_EQ(0, polynomial.getDegree()) ;
        EXPECT_EQ(Array<Real>({ 0.0 }), polynomial.getCoefficientsArray()) ;

    }

    {

        Polynomial<Real> polynomial = Polynomial<Real>::Monomial(0, 1.2) ;

        EXPECT_EQ(0, polynomial.getDegree()) ;
        EXPECT_EQ(Array<Real>({ 1.2 }), polynomial.getCoefficientsArray()) ;

    }

    {

        Polynomial<Real> polynomial = Polynomial<Real>::Monomial(4, 1.0) ;

        EXPECT_EQ(4, polynomial.getDegree()) ;
        EXPECT_EQ(Array<Real>({ 0.0, 0.0, 0.0, 0.0, 1.0 }), polynomial.getCoefficientsArray()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Algebra_Polynomial, Legendre)
{

    using ostk::core::types::Real ;
    using ostk::core::ctnr::Array ;

    using ostk::math::alg::Polynomial ;

    {

        Polynomial<Real> aPolynomial = Polynomial<Real>::Legendre(3) ;

        EXPECT_EQ(3, aPolynomial.getDegree()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Algebra_Polynomial, Hermite)
{

    using ostk::core::types::Real ;
    using ostk::core::ctnr::Array ;

    using ostk::math::alg::Polynomial ;

    {

        Polynomial<Real> aPolynomial = Polynomial<Real>::Legendre(3) ;

        EXPECT_EQ(3, aPolynomial.getDegree()) ;

    }

}

// TEST (OpenSpaceToolkit_Mathematics_Algebra_Polynomial, Laguerre)
// {

//     using ostk::core::types::Real ;
//     using ostk::core::ctnr::Array ;

//     using ostk::math::alg::Polynomial ;

//     {

//         Polynomial<Real> aPolynomial = Polynomial<Real>::Laguerre(3) ;

//         EXPECT_EQ(3, aPolynomial.getDegree()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Algebra_Polynomial, Chebyshev)
// {

//     using ostk::core::types::Real ;
//     using ostk::core::ctnr::Array ;

//     using ostk::math::alg::Polynomial ;

//     {

//         Polynomial<Real> aPolynomial = Polynomial<Real>::Chebyshev(3) ;

//         EXPECT_EQ(3, aPolynomial.getDegree()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Algebra_Polynomial, SetCoefficientOfDegree)
// {

//     using ostk::core::types::Integer ;
//     using ostk::core::types::Real ;
//     using ostk::core::ctnr::Array ;

//     using ostk::math::alg::Polynomial ;

//     {

//         Array<Real> coefficientsArray = { 1.0, 3.0, 4.0 } ;

//         Polynomial<Real> polynomial = Polynomial<Real>(coefficientsArray) ;

//         polynomial.setCoefficientOfDegree(0, 2.0) ;

//         EXPECT_EQ(2.0, polynomial.evaluateAt(0.0)) ;

//     }

// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
