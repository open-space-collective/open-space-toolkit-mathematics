////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           Library/Mathematics/Objects/Interval.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Objects/Interval.hpp>
#include <Library/Core/Types/Real.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Mathematics_Objects_Interval, Constructor)
{

    using ostk::core::types::Real ;
    using ostk::math::obj::Interval ;

    {

        Real lowerBound = 0.0 ;
        Real upperBound = 1.0 ;

        EXPECT_NO_THROW(Interval<Real>(lowerBound, upperBound, Interval<Real>::Type::Closed)) ;
        EXPECT_NO_THROW(Interval<Real>(lowerBound, upperBound, Interval<Real>::Type::Open)) ;
        EXPECT_NO_THROW(Interval<Real>(lowerBound, upperBound, Interval<Real>::Type::HalfOpenLeft)) ;
        EXPECT_NO_THROW(Interval<Real>(lowerBound, upperBound, Interval<Real>::Type::HalfOpenRight)) ;

    }

    {

        EXPECT_ANY_THROW(Interval<Real>(1.0, 0.0, Interval<Real>::Type::Closed)) ;
        EXPECT_ANY_THROW(Interval<Real>(1.0, 0.0, Interval<Real>::Type::Open)) ;
        EXPECT_ANY_THROW(Interval<Real>(1.0, 0.0, Interval<Real>::Type::HalfOpenLeft)) ;
        EXPECT_ANY_THROW(Interval<Real>(1.0, 0.0, Interval<Real>::Type::HalfOpenRight)) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, EqualToOperator)
{

    using ostk::core::types::Real ;
    using ostk::math::obj::Interval ;

    {

        EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed) == Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed)) ;
        EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open) == Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open)) ;
        EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft) == Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft)) ;
        EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight) == Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight)) ;

    }

    {

        EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed) == Interval<Real>(1.0, 1.0, Interval<Real>::Type::Closed)) ;
        EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open) == Interval<Real>(0.0, 0.0, Interval<Real>::Type::Open)) ;
        EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft) == Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed)) ;
        EXPECT_FALSE(Interval<Real>::Undefined() == Interval<Real>::Undefined()) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, NotEqualToOperator)
{

    using ostk::core::types::Real ;
    using ostk::math::obj::Interval ;

    {

        EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed) != Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed)) ;
        EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open) != Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open)) ;
        EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft) != Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft)) ;
        EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight) != Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight)) ;

    }

    {

        EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed) != Interval<Real>(1.0, 1.0, Interval<Real>::Type::Closed)) ;
        EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open) != Interval<Real>(0.0, 0.0, Interval<Real>::Type::Open)) ;
        EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft) != Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed)) ;
        EXPECT_TRUE(Interval<Real>::Undefined() != Interval<Real>::Undefined()) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, IsDefined)
{

    using ostk::core::types::Real ;
    using ostk::math::obj::Interval ;

    {

        EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).isDefined()) ;
        EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).isDefined()) ;
        EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).isDefined()) ;
        EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).isDefined()) ;

    }

    {

        EXPECT_FALSE(Interval<Real>(Real::Undefined(), 1.0, Interval<Real>::Type::Closed).isDefined()) ;
        EXPECT_FALSE(Interval<Real>(0.0, Real::Undefined(), Interval<Real>::Type::Open).isDefined()) ;
        EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Undefined).isDefined()) ;

        EXPECT_FALSE(Interval<Real>::Undefined().isDefined()) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, IsDegenerate)
{

    using ostk::core::types::Real ;
    using ostk::math::obj::Interval ;

    {

        EXPECT_TRUE(Interval<Real>(1.0, 1.0, Interval<Real>::Type::Closed).isDegenerate()) ;
        EXPECT_TRUE(Interval<Real>(1.0, 1.0, Interval<Real>::Type::Open).isDegenerate()) ;
        EXPECT_TRUE(Interval<Real>(1.0, 1.0, Interval<Real>::Type::HalfOpenLeft).isDegenerate()) ;
        EXPECT_TRUE(Interval<Real>(1.0, 1.0, Interval<Real>::Type::HalfOpenRight).isDegenerate()) ;

    }

    {

        EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).isDegenerate()) ;
        EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).isDegenerate()) ;
        EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).isDegenerate()) ;
        EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).isDegenerate()) ;

    }

    {

        EXPECT_ANY_THROW(Interval<Real>::Undefined().isDegenerate()) ;

        EXPECT_ANY_THROW(Interval<Real>(Real::Undefined(), 1.0, Interval<Real>::Type::Closed).isDegenerate()) ;
        EXPECT_ANY_THROW(Interval<Real>(0.0, Real::Undefined(), Interval<Real>::Type::Open).isDegenerate()) ;

    }

}

// TEST (Library_Mathematics_Objects_Interval, Intersects)
// {

//     using ostk::core::types::Real ;

//     using ostk::math::obj::Interval ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Objects_Interval, Contains)
// {

//     using ostk::core::types::Real ;

//     using ostk::math::obj::Interval ;

//     {

//         EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(0.0)) ;
//         EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(0.1)) ;
//         EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(0.5)) ;
//         EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(0.9)) ;
//         EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(1.0)) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(-1.0)) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(-0.1)) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(+1.1)) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(+2.0)) ;

//     }

//     {

//         EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(0.1)) ;
//         EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(0.5)) ;
//         EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(0.9)) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(-1.0)) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(-0.1)) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(0.0)) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(1.0)) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(+1.1)) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(+2.0)) ;

//     }

//     {

//         EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).contains(0.1)) ;
//         EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).contains(0.5)) ;
//         EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).contains(0.9)) ;
//         EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).contains(1.0)) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).contains(-1.0)) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).contains(-0.1)) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).contains(0.0)) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).contains(+1.1)) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).contains(+2.0)) ;

//     }

//     {

//         EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).contains(0.0)) ;
//         EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).contains(0.1)) ;
//         EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).contains(0.5)) ;
//         EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).contains(0.9)) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).contains(-1.0)) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).contains(-0.1)) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).contains(1.0)) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).contains(+1.1)) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).contains(+2.0)) ;

//     }

//     {

//         EXPECT_ANY_THROW(Interval<Real>::Undefined().contains(1.0)) ;
//         EXPECT_ANY_THROW(Interval<Real>::Undefined().contains(Real::Undefined())) ;

//         EXPECT_ANY_THROW(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Real::Undefined())) ;
//         EXPECT_ANY_THROW(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Real::Undefined())) ;
//         EXPECT_ANY_THROW(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).contains(Real::Undefined())) ;
//         EXPECT_ANY_THROW(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).contains(Real::Undefined())) ;

//     }

//     // Interval(Closed)::contains(Interval)

//     {

//         // Closed

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, -1.0, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, -0.5, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, +0.0, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, +0.5, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, +1.0, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, +1.5, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, +2.0, Interval<Real>::Type::Closed))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-0.5, -0.5, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-0.5, +0.0, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-0.5, +0.5, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-0.5, +1.0, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-0.5, +1.5, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-0.5, +2.0, Interval<Real>::Type::Closed))) ;

//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.0, +0.0, Interval<Real>::Type::Closed))) ;
//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.0, +0.5, Interval<Real>::Type::Closed))) ;
//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.0, +1.0, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.0, +1.5, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.0, +2.0, Interval<Real>::Type::Closed))) ;

//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.5, +0.5, Interval<Real>::Type::Closed))) ;
//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.5, +1.0, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.5, +1.5, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.5, +2.0, Interval<Real>::Type::Closed))) ;

//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+1.0, +1.0, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+1.0, +1.5, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+1.0, +2.0, Interval<Real>::Type::Closed))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+1.5, +1.5, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+1.5, +2.0, Interval<Real>::Type::Closed))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+2.0, +2.0, Interval<Real>::Type::Closed))) ;

//         // Open

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, -1.0, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, -0.5, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, +0.0, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, +0.5, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, +1.0, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, +1.5, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, +2.0, Interval<Real>::Type::Open))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-0.5, -0.5, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-0.5, +0.0, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-0.5, +0.5, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-0.5, +1.0, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-0.5, +1.5, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-0.5, +2.0, Interval<Real>::Type::Open))) ;

//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.0, +0.0, Interval<Real>::Type::Open))) ;
//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.0, +0.5, Interval<Real>::Type::Open))) ;
//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.0, +1.0, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.0, +1.5, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.0, +2.0, Interval<Real>::Type::Open))) ;

//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.5, +0.5, Interval<Real>::Type::Open))) ;
//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.5, +1.0, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.5, +1.5, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.5, +2.0, Interval<Real>::Type::Open))) ;

//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+1.0, +1.0, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+1.0, +1.5, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+1.0, +2.0, Interval<Real>::Type::Open))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+1.5, +1.5, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+1.5, +2.0, Interval<Real>::Type::Open))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+2.0, +2.0, Interval<Real>::Type::Open))) ;

//         // HalfOpenLeft

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, -1.0, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, -0.5, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, +0.0, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, +0.5, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, +1.0, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, +1.5, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, +2.0, Interval<Real>::Type::HalfOpenLeft))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-0.5, -0.5, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-0.5, +0.0, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-0.5, +0.5, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-0.5, +1.0, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-0.5, +1.5, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-0.5, +2.0, Interval<Real>::Type::HalfOpenLeft))) ;

//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.0, +0.0, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.0, +0.5, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.0, +1.0, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.0, +1.5, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.0, +2.0, Interval<Real>::Type::HalfOpenLeft))) ;

//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.5, +0.5, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.5, +1.0, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.5, +1.5, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.5, +2.0, Interval<Real>::Type::HalfOpenLeft))) ;

//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+1.0, +1.0, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+1.0, +1.5, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+1.0, +2.0, Interval<Real>::Type::HalfOpenLeft))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+1.5, +1.5, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+1.5, +2.0, Interval<Real>::Type::HalfOpenLeft))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+2.0, +2.0, Interval<Real>::Type::HalfOpenLeft))) ;

//         // HalfOpenRight

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, -1.0, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, -0.5, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, +0.0, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, +0.5, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, +1.0, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, +1.5, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-1.0, +2.0, Interval<Real>::Type::HalfOpenRight))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-0.5, -0.5, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-0.5, +0.0, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-0.5, +0.5, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-0.5, +1.0, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-0.5, +1.5, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(-0.5, +2.0, Interval<Real>::Type::HalfOpenRight))) ;

//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.0, +0.0, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.0, +0.5, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.0, +1.0, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.0, +1.5, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.0, +2.0, Interval<Real>::Type::HalfOpenRight))) ;

//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.5, +0.5, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.5, +1.0, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.5, +1.5, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+0.5, +2.0, Interval<Real>::Type::HalfOpenRight))) ;

//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+1.0, +1.0, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+1.0, +1.5, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+1.0, +2.0, Interval<Real>::Type::HalfOpenRight))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+1.5, +1.5, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+1.5, +2.0, Interval<Real>::Type::HalfOpenRight))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>(+2.0, +2.0, Interval<Real>::Type::HalfOpenRight))) ;

//     }

//     // Interval(Open)::contains(Interval)

//     {

//         // Closed

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, -1.0, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, -0.5, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, +0.0, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, +0.5, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, +1.0, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, +1.5, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, +2.0, Interval<Real>::Type::Closed))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-0.5, -0.5, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-0.5, +0.0, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-0.5, +0.5, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-0.5, +1.0, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-0.5, +1.5, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-0.5, +2.0, Interval<Real>::Type::Closed))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.0, +0.0, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.0, +0.5, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.0, +1.0, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.0, +1.5, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.0, +2.0, Interval<Real>::Type::Closed))) ;

//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.5, +0.5, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.5, +1.0, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.5, +1.5, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.5, +2.0, Interval<Real>::Type::Closed))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+1.0, +1.0, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+1.0, +1.5, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+1.0, +2.0, Interval<Real>::Type::Closed))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+1.5, +1.5, Interval<Real>::Type::Closed))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+1.5, +2.0, Interval<Real>::Type::Closed))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+2.0, +2.0, Interval<Real>::Type::Closed))) ;

//         // Open

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, -1.0, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, -0.5, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, +0.0, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, +0.5, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, +1.0, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, +1.5, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, +2.0, Interval<Real>::Type::Open))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-0.5, -0.5, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-0.5, +0.0, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-0.5, +0.5, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-0.5, +1.0, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-0.5, +1.5, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-0.5, +2.0, Interval<Real>::Type::Open))) ;

//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.0, +0.0, Interval<Real>::Type::Open))) ;
//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.0, +0.5, Interval<Real>::Type::Open))) ;
//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.0, +1.0, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.0, +1.5, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.0, +2.0, Interval<Real>::Type::Open))) ;

//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.5, +0.5, Interval<Real>::Type::Open))) ;
//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.5, +1.0, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.5, +1.5, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.5, +2.0, Interval<Real>::Type::Open))) ;

//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+1.0, +1.0, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+1.0, +1.5, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+1.0, +2.0, Interval<Real>::Type::Open))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+1.5, +1.5, Interval<Real>::Type::Open))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+1.5, +2.0, Interval<Real>::Type::Open))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+2.0, +2.0, Interval<Real>::Type::Open))) ;

//         // HalfOpenLeft

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, -1.0, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, -0.5, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, +0.0, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, +0.5, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, +1.0, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, +1.5, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, +2.0, Interval<Real>::Type::HalfOpenLeft))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-0.5, -0.5, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-0.5, +0.0, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-0.5, +0.5, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-0.5, +1.0, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-0.5, +1.5, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-0.5, +2.0, Interval<Real>::Type::HalfOpenLeft))) ;

//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.0, +0.0, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.0, +0.5, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.0, +1.0, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.0, +1.5, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.0, +2.0, Interval<Real>::Type::HalfOpenLeft))) ;

//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.5, +0.5, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.5, +1.0, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.5, +1.5, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.5, +2.0, Interval<Real>::Type::HalfOpenLeft))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+1.0, +1.0, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+1.0, +1.5, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+1.0, +2.0, Interval<Real>::Type::HalfOpenLeft))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+1.5, +1.5, Interval<Real>::Type::HalfOpenLeft))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+1.5, +2.0, Interval<Real>::Type::HalfOpenLeft))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+2.0, +2.0, Interval<Real>::Type::HalfOpenLeft))) ;

//         // HalfOpenRight

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, -1.0, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, -0.5, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, +0.0, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, +0.5, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, +1.0, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, +1.5, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-1.0, +2.0, Interval<Real>::Type::HalfOpenRight))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-0.5, -0.5, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-0.5, +0.0, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-0.5, +0.5, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-0.5, +1.0, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-0.5, +1.5, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(-0.5, +2.0, Interval<Real>::Type::HalfOpenRight))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.0, +0.0, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.0, +0.5, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.0, +1.0, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.0, +1.5, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.0, +2.0, Interval<Real>::Type::HalfOpenRight))) ;

//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.5, +0.5, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.5, +1.0, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.5, +1.5, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+0.5, +2.0, Interval<Real>::Type::HalfOpenRight))) ;

//         EXPECT_TRUE (Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+1.0, +1.0, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+1.0, +1.5, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+1.0, +2.0, Interval<Real>::Type::HalfOpenRight))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+1.5, +1.5, Interval<Real>::Type::HalfOpenRight))) ;
//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+1.5, +2.0, Interval<Real>::Type::HalfOpenRight))) ;

//         EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>(+2.0, +2.0, Interval<Real>::Type::HalfOpenRight))) ;

//     }

//     // Interval(HalfOpenLeft)::contains(Interval)

//     {

//         FAIL() ;

//     }

//     // Interval(OpHalfOpenRighten)::contains(Interval)

//     {

//         FAIL() ;

//     }

//     {

//         EXPECT_ANY_THROW(Interval<Real>::Undefined().contains(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed))) ;
//         EXPECT_ANY_THROW(Interval<Real>::Undefined().contains(Interval<Real>::Undefined())) ;

//         EXPECT_ANY_THROW(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).contains(Interval<Real>::Undefined())) ;
//         EXPECT_ANY_THROW(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).contains(Interval<Real>::Undefined())) ;
//         EXPECT_ANY_THROW(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).contains(Interval<Real>::Undefined())) ;
//         EXPECT_ANY_THROW(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).contains(Interval<Real>::Undefined())) ;

//     }

// }

TEST (Library_Mathematics_Objects_Interval, AccessLowerBound)
{

    using ostk::core::types::Real ;
    using ostk::math::obj::Interval ;

    {

        EXPECT_EQ(0.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).accessLowerBound()) ;
        EXPECT_EQ(0.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).accessLowerBound()) ;
        EXPECT_EQ(0.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).accessLowerBound()) ;
        EXPECT_EQ(0.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).accessLowerBound()) ;

    }

    {

        EXPECT_EQ(1.0, Interval<Real>(1.0, 1.0, Interval<Real>::Type::Closed).accessLowerBound()) ;
        EXPECT_EQ(1.0, Interval<Real>(1.0, 1.0, Interval<Real>::Type::Open).accessLowerBound()) ;
        EXPECT_EQ(1.0, Interval<Real>(1.0, 1.0, Interval<Real>::Type::HalfOpenLeft).accessLowerBound()) ;
        EXPECT_EQ(1.0, Interval<Real>(1.0, 1.0, Interval<Real>::Type::HalfOpenRight).accessLowerBound()) ;

    }

    {

        EXPECT_EQ(-1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::Closed).accessLowerBound()) ;
        EXPECT_EQ(-1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::Open).accessLowerBound()) ;
        EXPECT_EQ(-1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::HalfOpenLeft).accessLowerBound()) ;
        EXPECT_EQ(-1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::HalfOpenRight).accessLowerBound()) ;

    }

    {

        Interval<Real> interval(0.0, 1.0, Interval<Real>::Type::Closed) ;

        EXPECT_EQ(&interval.accessLowerBound(), &interval.accessLowerBound()) ;

    }

    {

        EXPECT_ANY_THROW(Interval<Real>::Undefined().accessLowerBound()) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, AccessUpperBound)
{

    using ostk::core::types::Real ;
    using ostk::math::obj::Interval ;

    {

        EXPECT_EQ(1.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).accessUpperBound()) ;
        EXPECT_EQ(1.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).accessUpperBound()) ;
        EXPECT_EQ(1.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).accessUpperBound()) ;
        EXPECT_EQ(1.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).accessUpperBound()) ;

    }

    {

        EXPECT_EQ(1.0, Interval<Real>(1.0, 1.0, Interval<Real>::Type::Closed).accessUpperBound()) ;
        EXPECT_EQ(1.0, Interval<Real>(1.0, 1.0, Interval<Real>::Type::Open).accessUpperBound()) ;
        EXPECT_EQ(1.0, Interval<Real>(1.0, 1.0, Interval<Real>::Type::HalfOpenLeft).accessUpperBound()) ;
        EXPECT_EQ(1.0, Interval<Real>(1.0, 1.0, Interval<Real>::Type::HalfOpenRight).accessUpperBound()) ;

    }

    {

        EXPECT_EQ(+1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::Closed).accessUpperBound()) ;
        EXPECT_EQ(+1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::Open).accessUpperBound()) ;
        EXPECT_EQ(+1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::HalfOpenLeft).accessUpperBound()) ;
        EXPECT_EQ(+1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::HalfOpenRight).accessUpperBound()) ;

    }

    {

        Interval<Real> interval(0.0, 1.0, Interval<Real>::Type::Closed) ;

        EXPECT_EQ(&interval.accessUpperBound(), &interval.accessUpperBound()) ;

    }

    {

        EXPECT_ANY_THROW(Interval<Real>::Undefined().accessUpperBound()) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, GetType)
{

    using ostk::core::types::Real ;
    using ostk::math::obj::Interval ;

    {

        EXPECT_EQ(Interval<Real>::Type::Closed, Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).getType()) ;
        EXPECT_EQ(Interval<Real>::Type::Open, Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).getType()) ;
        EXPECT_EQ(Interval<Real>::Type::HalfOpenLeft, Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).getType()) ;
        EXPECT_EQ(Interval<Real>::Type::HalfOpenRight, Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).getType()) ;

    }

    {

        EXPECT_ANY_THROW(Interval<Real>::Undefined().getType()) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, GetLowerBound)
{

    using ostk::core::types::Real ;
    using ostk::math::obj::Interval ;

    {

        EXPECT_EQ(0.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).getLowerBound()) ;
        EXPECT_EQ(0.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).getLowerBound()) ;
        EXPECT_EQ(0.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).getLowerBound()) ;
        EXPECT_EQ(0.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).getLowerBound()) ;

    }

    {

        EXPECT_EQ(1.0, Interval<Real>(1.0, 1.0, Interval<Real>::Type::Closed).getLowerBound()) ;
        EXPECT_EQ(1.0, Interval<Real>(1.0, 1.0, Interval<Real>::Type::Open).getLowerBound()) ;
        EXPECT_EQ(1.0, Interval<Real>(1.0, 1.0, Interval<Real>::Type::HalfOpenLeft).getLowerBound()) ;
        EXPECT_EQ(1.0, Interval<Real>(1.0, 1.0, Interval<Real>::Type::HalfOpenRight).getLowerBound()) ;

    }

    {

        EXPECT_EQ(-1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::Closed).getLowerBound()) ;
        EXPECT_EQ(-1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::Open).getLowerBound()) ;
        EXPECT_EQ(-1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::HalfOpenLeft).getLowerBound()) ;
        EXPECT_EQ(-1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::HalfOpenRight).getLowerBound()) ;

    }

    {

        EXPECT_ANY_THROW(Interval<Real>::Undefined().getLowerBound()) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, GetUpperBound)
{

    using ostk::core::types::Real ;
    using ostk::math::obj::Interval ;

    {

        EXPECT_EQ(1.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).getUpperBound()) ;
        EXPECT_EQ(1.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).getUpperBound()) ;
        EXPECT_EQ(1.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).getUpperBound()) ;
        EXPECT_EQ(1.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).getUpperBound()) ;

    }

    {

        EXPECT_EQ(1.0, Interval<Real>(1.0, 1.0, Interval<Real>::Type::Closed).getUpperBound()) ;
        EXPECT_EQ(1.0, Interval<Real>(1.0, 1.0, Interval<Real>::Type::Open).getUpperBound()) ;
        EXPECT_EQ(1.0, Interval<Real>(1.0, 1.0, Interval<Real>::Type::HalfOpenLeft).getUpperBound()) ;
        EXPECT_EQ(1.0, Interval<Real>(1.0, 1.0, Interval<Real>::Type::HalfOpenRight).getUpperBound()) ;

    }

    {

        EXPECT_EQ(+1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::Closed).getUpperBound()) ;
        EXPECT_EQ(+1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::Open).getUpperBound()) ;
        EXPECT_EQ(+1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::HalfOpenLeft).getUpperBound()) ;
        EXPECT_EQ(+1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::HalfOpenRight).getUpperBound()) ;

    }

    {

        EXPECT_ANY_THROW(Interval<Real>::Undefined().getUpperBound()) ;

    }

}

// TEST (Library_Mathematics_Objects_Interval, GetIntersectionWith)
// {

//     using ostk::core::types::Real ;

//     using ostk::math::obj::Interval ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Objects_Interval, GetUnionWith)
// {

//     using ostk::core::types::Real ;

//     using ostk::math::obj::Interval ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Objects_Interval, GenerateArrayWithStep)
// {

//     using ostk::core::types::Real ;

//     using ostk::math::obj::Interval ;

//     {

//         FAIL() ;

//     }

// }

TEST (Library_Mathematics_Objects_Interval, GenerateArrayWithSize)
{

    using ostk::core::types::Size ;
    using ostk::core::types::Real ;
    using ostk::core::ctnr::Array ;

    using ostk::math::obj::Interval ;

    // Closed

    {

        const Interval<Real> interval = { 0.0, 1.0, Interval<Real>::Type::Closed } ;

        const Array<Real> array = interval.generateArrayWithSize(3) ;

        EXPECT_TRUE(array.isNear(Array<Real>({ 0.0, 0.5, 1.0 }), Real::Epsilon())) ;

    }

    {

        const Interval<Real> interval = { 0.0, 1.0, Interval<Real>::Type::Closed } ;

        const Array<Real> array = interval.generateArrayWithSize(5) ;

        EXPECT_TRUE(array.isNear(Array<Real>({ 0.0, 0.25, 0.5, 0.75, 1.0 }), Real::Epsilon())) ;

    }

    {

        const Interval<Real> interval = { 0.0, 1.0, Interval<Real>::Type::Closed } ;

        const Array<Real> array = interval.generateArrayWithSize(2) ;

        EXPECT_TRUE(array.isNear(Array<Real>({ 0.0, 1.0 }), Real::Epsilon())) ;

    }

    // Open

    {

        const Interval<Real> interval = { 0.0, 1.0, Interval<Real>::Type::Open } ;

        const Array<Real> array = interval.generateArrayWithSize(3) ;

        EXPECT_TRUE(array.isNear(Array<Real>({ 0.25, 0.5, 0.75 }), Real::Epsilon())) ;

    }

    {

        const Interval<Real> interval = { 0.0, 1.0, Interval<Real>::Type::Open } ;

        const Array<Real> array = interval.generateArrayWithSize(4) ;

        EXPECT_TRUE(array.isNear(Array<Real>({ 0.2, 0.4, 0.6, 0.8 }), Real::Epsilon())) ;

    }

    // Half-Open Left

    {

        const Interval<Real> interval = { 0.0, 1.0, Interval<Real>::Type::HalfOpenLeft } ;

        const Array<Real> array = interval.generateArrayWithSize(4) ;

        EXPECT_TRUE(array.isNear(Array<Real>({ 0.25, 0.5, 0.75, 1.0 }), Real::Epsilon())) ;

    }

    {

        const Interval<Real> interval = { 0.0, 1.0, Interval<Real>::Type::HalfOpenLeft } ;

        const Array<Real> array = interval.generateArrayWithSize(5) ;

        EXPECT_TRUE(array.isNear(Array<Real>({ 0.2, 0.4, 0.6, 0.8, 1.0 }), Real::Epsilon())) ;

    }

    // Half-Open Right

    {

        const Interval<Real> interval = { 0.0, 1.0, Interval<Real>::Type::HalfOpenRight } ;

        const Array<Real> array = interval.generateArrayWithSize(4) ;

        EXPECT_TRUE(array.isNear(Array<Real>({ 0.0, 0.25, 0.5, 0.75 }), Real::Epsilon())) ;

    }

    {

        const Interval<Real> interval = { 0.0, 1.0, Interval<Real>::Type::HalfOpenRight } ;

        const Array<Real> array = interval.generateArrayWithSize(5) ;

        EXPECT_TRUE(array.isNear(Array<Real>({ 0.0, 0.2, 0.4, 0.6, 0.8 }), Real::Epsilon())) ;

    }

    {

        EXPECT_ANY_THROW(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).generateArrayWithSize(0)) ;
        EXPECT_ANY_THROW(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).generateArrayWithSize(1)) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, ToString)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Interval ;

    {

        EXPECT_EQ("[0.0, 1.0]", Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).toString()) ;
        EXPECT_EQ("]0.0, 1.0[", Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).toString()) ;
        EXPECT_EQ("]0.0, 1.0]", Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).toString()) ;
        EXPECT_EQ("[0.0, 1.0[", Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).toString()) ;

    }

    {

        EXPECT_EQ("[1.0, 1.0]", Interval<Real>(1.0, 1.0, Interval<Real>::Type::Closed).toString()) ;
        EXPECT_EQ("]1.0, 1.0[", Interval<Real>(1.0, 1.0, Interval<Real>::Type::Open).toString()) ;
        EXPECT_EQ("]1.0, 1.0]", Interval<Real>(1.0, 1.0, Interval<Real>::Type::HalfOpenLeft).toString()) ;
        EXPECT_EQ("[1.0, 1.0[", Interval<Real>(1.0, 1.0, Interval<Real>::Type::HalfOpenRight).toString()) ;

    }

    {

        EXPECT_EQ("[-1.0, 1.0]", Interval<Real>(-1.0, +1.0, Interval<Real>::Type::Closed).toString()) ;
        EXPECT_EQ("]-1.0, 1.0[", Interval<Real>(-1.0, +1.0, Interval<Real>::Type::Open).toString()) ;
        EXPECT_EQ("]-1.0, 1.0]", Interval<Real>(-1.0, +1.0, Interval<Real>::Type::HalfOpenLeft).toString()) ;
        EXPECT_EQ("[-1.0, 1.0[", Interval<Real>(-1.0, +1.0, Interval<Real>::Type::HalfOpenRight).toString()) ;

    }

    {

        EXPECT_ANY_THROW(Interval<Real>::Undefined().toString()) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, SetType)
{

    using ostk::core::types::Real ;
    using ostk::math::obj::Interval ;

    {

        Interval<Real> interval(0.0, 1.0, Interval<Real>::Type::Closed) ;

        EXPECT_EQ(Interval<Real>::Type::Closed, interval.getType()) ;

        interval.setType(Interval<Real>::Type::Open) ;

        EXPECT_EQ(Interval<Real>::Type::Open, interval.getType()) ;

    }

    {

        EXPECT_ANY_THROW(Interval<Real>::Undefined().setType(Interval<Real>::Type::Closed)) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, SetLowerBound)
{

    using ostk::core::types::Real ;
    using ostk::math::obj::Interval ;

    {

        Interval<Real> interval(0.0, 1.0, Interval<Real>::Type::Closed) ;

        EXPECT_EQ(0.0, interval.getLowerBound()) ;

        interval.setLowerBound(1.0) ;

        EXPECT_EQ(1.0, interval.getLowerBound()) ;

    }

    {

        EXPECT_ANY_THROW(Interval<Real>::Undefined().setLowerBound(1.0)) ;

    }

    {

        Interval<Real> interval(0.0, 1.0, Interval<Real>::Type::Closed) ;

        EXPECT_EQ(0.0, interval.getLowerBound()) ;

        EXPECT_ANY_THROW(interval.setLowerBound(2.0)) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, SetUpperBound)
{

    using ostk::core::types::Real ;
    using ostk::math::obj::Interval ;

    {

        Interval<Real> interval(0.0, 1.0, Interval<Real>::Type::Closed) ;

        EXPECT_EQ(1.0, interval.getUpperBound()) ;

        interval.setUpperBound(2.0) ;

        EXPECT_EQ(2.0, interval.getUpperBound()) ;

    }

    {

        EXPECT_ANY_THROW(Interval<Real>::Undefined().setUpperBound(1.0)) ;

    }

    {

        Interval<Real> interval(1.0, 1.0, Interval<Real>::Type::Closed) ;

        EXPECT_EQ(1.0, interval.getUpperBound()) ;

        EXPECT_ANY_THROW(interval.setUpperBound(0.0)) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, Undefined)
{

    using ostk::core::types::Real ;
    using ostk::math::obj::Interval ;

    {

        EXPECT_NO_THROW(Interval<Real>::Undefined()) ;

        EXPECT_FALSE(Interval<Real>::Undefined().isDefined()) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, Closed)
{

    using ostk::core::types::Real ;
    using ostk::math::obj::Interval ;

    {

        EXPECT_NO_THROW(Interval<Real>::Closed(0.0, 1.0)) ;

        EXPECT_TRUE(Interval<Real>::Closed(0.0, 1.0).isDefined()) ;

        EXPECT_EQ(Interval<Real>::Type::Closed, Interval<Real>::Closed(0.0, 1.0).getType()) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, Open)
{

    using ostk::core::types::Real ;
    using ostk::math::obj::Interval ;

    {

        EXPECT_NO_THROW(Interval<Real>::Open(0.0, 1.0)) ;

        EXPECT_TRUE(Interval<Real>::Open(0.0, 1.0).isDefined()) ;

        EXPECT_EQ(Interval<Real>::Type::Open, Interval<Real>::Open(0.0, 1.0).getType()) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, HalfOpenLeft)
{

    using ostk::core::types::Real ;
    using ostk::math::obj::Interval ;

    {

        EXPECT_NO_THROW(Interval<Real>::HalfOpenLeft(0.0, 1.0)) ;

        EXPECT_TRUE(Interval<Real>::HalfOpenLeft(0.0, 1.0).isDefined()) ;

        EXPECT_EQ(Interval<Real>::Type::HalfOpenLeft, Interval<Real>::HalfOpenLeft(0.0, 1.0).getType()) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, HalfOpenRight)
{

    using ostk::core::types::Real ;
    using ostk::math::obj::Interval ;

    {

        EXPECT_NO_THROW(Interval<Real>::HalfOpenRight(0.0, 1.0)) ;

        EXPECT_TRUE(Interval<Real>::HalfOpenRight(0.0, 1.0).isDefined()) ;

        EXPECT_EQ(Interval<Real>::Type::HalfOpenRight, Interval<Real>::HalfOpenRight(0.0, 1.0).getType()) ;

    }

}

// TEST (Library_Mathematics_Objects_Interval, Parse)
// {

//     using ostk::core::types::Real ;

//     using ostk::math::obj::Interval ;

//     {

//         FAIL() ;

//     }

// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
