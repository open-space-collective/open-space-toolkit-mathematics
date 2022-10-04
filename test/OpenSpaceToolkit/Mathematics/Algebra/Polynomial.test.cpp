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

    }

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

TEST (OpenSpaceToolkit_Mathematics_Algebra_Polynomial, SetCoefficientOfDegree)
{

    using ostk::core::types::Integer ;
    using ostk::core::types::Real ;
    using ostk::core::ctnr::Array ;

    using ostk::math::alg::Polynomial ;

    {

        Array<Real> coefficientsArray = { 1.0, 3.0, 4.0 } ;

        Polynomial<Real> polynomial = Polynomial<Real>(coefficientsArray) ;

        polynomial.setCoefficientOfDegree(0, 2.0) ;

        EXPECT_EQ(2.0, polynomial.evaluateAt(0.0)) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
