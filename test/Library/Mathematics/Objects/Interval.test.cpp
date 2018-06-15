////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Objects/Interval.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Objects/Interval.hpp>
#include <Library/Core/Types/Real.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Mathematics_Objects_Interval, Constructor)
{

    using library::core::types::Real ;
    using library::math::obj::Interval ;

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

    using library::core::types::Real ;
    using library::math::obj::Interval ;

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

    using library::core::types::Real ;
    using library::math::obj::Interval ;

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

    using library::core::types::Real ;
    using library::math::obj::Interval ;

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

    using library::core::types::Real ;
    using library::math::obj::Interval ;

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

        EXPECT_FALSE(Interval<Real>(Real::Undefined(), 1.0, Interval<Real>::Type::Closed).isDegenerate()) ;
        EXPECT_FALSE(Interval<Real>(0.0, Real::Undefined(), Interval<Real>::Type::Open).isDegenerate()) ;
        EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Undefined).isDegenerate()) ;

        EXPECT_FALSE(Interval<Real>::Undefined().isDegenerate()) ;

    }

}

// TEST (Library_Mathematics_Objects_Interval, IsIntersectingWith)
// {

//     using library::core::types::Real ;
//     using library::math::obj::Interval ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Objects_Interval, Contains)
// {

//     using library::core::types::Real ;
//     using library::math::obj::Interval ;

//     {

//         FAIL() ;

//     }

// }

TEST (Library_Mathematics_Objects_Interval, AccessLowerBound)
{

    using library::core::types::Real ;
    using library::math::obj::Interval ;

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

        EXPECT_FALSE(Interval<Real>::Undefined().accessLowerBound().isDefined()) ;

    }

    {

        Interval<Real> interval(0.0, 1.0, Interval<Real>::Type::Closed) ;

        EXPECT_EQ(&interval.accessLowerBound(), &interval.accessLowerBound()) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, AccessUpperBound)
{

    using library::core::types::Real ;
    using library::math::obj::Interval ;

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

        EXPECT_FALSE(Interval<Real>::Undefined().accessUpperBound().isDefined()) ;

    }

    {

        Interval<Real> interval(0.0, 1.0, Interval<Real>::Type::Closed) ;

        EXPECT_EQ(&interval.accessUpperBound(), &interval.accessUpperBound()) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, GetType)
{

    using library::core::types::Real ;
    using library::math::obj::Interval ;

    {

        EXPECT_EQ(Interval<Real>::Type::Undefined, Interval<Real>(0.0, 1.0, Interval<Real>::Type::Undefined).getType()) ;
        EXPECT_EQ(Interval<Real>::Type::Closed, Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).getType()) ;
        EXPECT_EQ(Interval<Real>::Type::Open, Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).getType()) ;
        EXPECT_EQ(Interval<Real>::Type::HalfOpenLeft, Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).getType()) ;
        EXPECT_EQ(Interval<Real>::Type::HalfOpenRight, Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).getType()) ;

    }

    {

        EXPECT_EQ(Interval<Real>::Type::Undefined, Interval<Real>::Undefined().getType()) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, GetLowerBound)
{

    using library::core::types::Real ;
    using library::math::obj::Interval ;

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

        EXPECT_FALSE(Interval<Real>::Undefined().getLowerBound().isDefined()) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, GetUpperBound)
{

    using library::core::types::Real ;
    using library::math::obj::Interval ;

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

        EXPECT_FALSE(Interval<Real>::Undefined().getUpperBound().isDefined()) ;

    }

}

// TEST (Library_Mathematics_Objects_Interval, GetIntersectionWith)
// {

//     using library::core::types::Real ;
//     using library::math::obj::Interval ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Objects_Interval, GetUnionWith)
// {

//     using library::core::types::Real ;
//     using library::math::obj::Interval ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Objects_Interval, GenerateArrayWithStep)
// {

//     using library::core::types::Real ;
//     using library::math::obj::Interval ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Objects_Interval, GenerateArrayWithSize)
// {

//     using library::core::types::Real ;
//     using library::math::obj::Interval ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Objects_Interval, GetString)
// {

//     using library::core::types::Real ;
//     using library::math::obj::Interval ;

//     {

//         EXPECT_EQ("[0.0, 1.0]", Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).getString()) ;
//         EXPECT_EQ("]0.0, 1.0[", Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).getString()) ;
//         EXPECT_EQ("]0.0, 1.0]", Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).getString()) ;
//         EXPECT_EQ("[0.0, 1.0[", Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).getString()) ;

//     }

//     {

//         EXPECT_EQ("[1.0, 1.0]", Interval<Real>(1.0, 1.0, Interval<Real>::Type::Closed).getString()) ;
//         EXPECT_EQ("]1.0, 1.0[", Interval<Real>(1.0, 1.0, Interval<Real>::Type::Open).getString()) ;
//         EXPECT_EQ("]1.0, 1.0]", Interval<Real>(1.0, 1.0, Interval<Real>::Type::HalfOpenLeft).getString()) ;
//         EXPECT_EQ("[1.0, 1.0[", Interval<Real>(1.0, 1.0, Interval<Real>::Type::HalfOpenRight).getString()) ;

//     }

//     {

//         EXPECT_EQ("[-1.0, 1.0]", Interval<Real>(-1.0, +1.0, Interval<Real>::Type::Closed).getString()) ;
//         EXPECT_EQ("]-1.0, 1.0[", Interval<Real>(-1.0, +1.0, Interval<Real>::Type::Open).getString()) ;
//         EXPECT_EQ("]-1.0, 1.0]", Interval<Real>(-1.0, +1.0, Interval<Real>::Type::HalfOpenLeft).getString()) ;
//         EXPECT_EQ("[-1.0, 1.0[", Interval<Real>(-1.0, +1.0, Interval<Real>::Type::HalfOpenRight).getString()) ;

//     }

//     {

//         EXPECT_ANY_THROW(Interval<Real>::Undefined().getString()) ;

//     }

// }

TEST (Library_Mathematics_Objects_Interval, SetType)
{

    using library::core::types::Real ;
    using library::math::obj::Interval ;

    {

        Interval<Real> interval(0.0, 1.0, Interval<Real>::Type::Closed) ;

        EXPECT_EQ(Interval<Real>::Type::Closed, interval.getType()) ;

        interval.setType(Interval<Real>::Type::Open) ;

        EXPECT_EQ(Interval<Real>::Type::Open, interval.getType()) ;

    }

    {

        EXPECT_NO_THROW(Interval<Real>::Undefined().setType(Interval<Real>::Type::Closed)) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, SetLowerBound)
{

    using library::core::types::Real ;
    using library::math::obj::Interval ;

    {

        Interval<Real> interval(0.0, 1.0, Interval<Real>::Type::Closed) ;

        EXPECT_EQ(0.0, interval.getLowerBound()) ;

        interval.setLowerBound(1.0) ;

        EXPECT_EQ(1.0, interval.getLowerBound()) ;

    }

    {

        Interval<Real> interval(Real::Undefined(), Real::Undefined(), Interval<Real>::Type::Closed) ;

        EXPECT_FALSE(interval.getLowerBound().isDefined()) ;

        interval.setLowerBound(1.0) ;

        EXPECT_EQ(1.0, interval.getLowerBound()) ;

    }

    {

        Interval<Real> interval(0.0, Real::Undefined(), Interval<Real>::Type::Closed) ;

        EXPECT_EQ(0.0, interval.getLowerBound()) ;

        interval.setLowerBound(1.0) ;

        EXPECT_EQ(1.0, interval.getLowerBound()) ;

    }

    {

        EXPECT_NO_THROW(Interval<Real>::Undefined().setLowerBound(1.0)) ;

    }

    {

        Interval<Real> interval(0.0, 1.0, Interval<Real>::Type::Closed) ;

        EXPECT_EQ(0.0, interval.getLowerBound()) ;

        EXPECT_ANY_THROW(interval.setLowerBound(2.0)) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, SetUpperBound)
{

    using library::core::types::Real ;
    using library::math::obj::Interval ;

    {

        Interval<Real> interval(0.0, 1.0, Interval<Real>::Type::Closed) ;

        EXPECT_EQ(1.0, interval.getUpperBound()) ;

        interval.setUpperBound(2.0) ;

        EXPECT_EQ(2.0, interval.getUpperBound()) ;

    }

    {

        Interval<Real> interval(Real::Undefined(), Real::Undefined(), Interval<Real>::Type::Closed) ;

        EXPECT_FALSE(interval.getUpperBound().isDefined()) ;

        interval.setUpperBound(1.0) ;

        EXPECT_EQ(1.0, interval.getUpperBound()) ;

    }

    {

        Interval<Real> interval(Real::Undefined(), 0.0, Interval<Real>::Type::Closed) ;

        EXPECT_EQ(0.0, interval.getUpperBound()) ;

        interval.setUpperBound(1.0) ;

        EXPECT_EQ(1.0, interval.getUpperBound()) ;

    }

    {

        EXPECT_NO_THROW(Interval<Real>::Undefined().setUpperBound(1.0)) ;

    }

    {

        Interval<Real> interval(1.0, 1.0, Interval<Real>::Type::Closed) ;

        EXPECT_EQ(1.0, interval.getUpperBound()) ;

        EXPECT_ANY_THROW(interval.setUpperBound(0.0)) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, Undefined)
{

    using library::core::types::Real ;
    using library::math::obj::Interval ;

    {

        EXPECT_NO_THROW(Interval<Real>::Undefined()) ;

        EXPECT_FALSE(Interval<Real>::Undefined().isDefined()) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, Closed)
{

    using library::core::types::Real ;
    using library::math::obj::Interval ;

    {

        EXPECT_NO_THROW(Interval<Real>::Closed(0.0, 1.0)) ;

        EXPECT_TRUE(Interval<Real>::Closed(0.0, 1.0).isDefined()) ;

        EXPECT_EQ(Interval<Real>::Type::Closed, Interval<Real>::Closed(0.0, 1.0).getType()) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, Open)
{

    using library::core::types::Real ;
    using library::math::obj::Interval ;

    {

        EXPECT_NO_THROW(Interval<Real>::Open(0.0, 1.0)) ;

        EXPECT_TRUE(Interval<Real>::Open(0.0, 1.0).isDefined()) ;

        EXPECT_EQ(Interval<Real>::Type::Open, Interval<Real>::Open(0.0, 1.0).getType()) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, HalfOpenLeft)
{

    using library::core::types::Real ;
    using library::math::obj::Interval ;

    {

        EXPECT_NO_THROW(Interval<Real>::HalfOpenLeft(0.0, 1.0)) ;

        EXPECT_TRUE(Interval<Real>::HalfOpenLeft(0.0, 1.0).isDefined()) ;

        EXPECT_EQ(Interval<Real>::Type::HalfOpenLeft, Interval<Real>::HalfOpenLeft(0.0, 1.0).getType()) ;

    }

}

TEST (Library_Mathematics_Objects_Interval, HalfOpenRight)
{

    using library::core::types::Real ;
    using library::math::obj::Interval ;

    {

        EXPECT_NO_THROW(Interval<Real>::HalfOpenRight(0.0, 1.0)) ;

        EXPECT_TRUE(Interval<Real>::HalfOpenRight(0.0, 1.0).isDefined()) ;

        EXPECT_EQ(Interval<Real>::Type::HalfOpenRight, Interval<Real>::HalfOpenRight(0.0, 1.0).getType()) ;

    }

}

// TEST (Library_Mathematics_Objects_Interval, Parse)
// {

//     using library::core::types::Real ;
//     using library::math::obj::Interval ;

//     {

//         FAIL() ;

//     }

// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////