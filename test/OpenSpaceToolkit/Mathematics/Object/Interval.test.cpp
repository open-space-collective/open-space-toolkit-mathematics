/// Apache License 2.0

#include <cmath>
#include <limits>

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Tuple.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Interval.hpp>

#include <Global.test.hpp>

using ostk::mathematics::object::Interval;
namespace ctnr = ostk::core::container;

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, Constructor)
{
    {
        double lowerBound = 0.0;
        double upperBound = 1.0;

        EXPECT_NO_THROW(Interval<double>(lowerBound, upperBound, Interval<double>::Type::Closed));
        EXPECT_NO_THROW(Interval<double>(lowerBound, upperBound, Interval<double>::Type::Open));
        EXPECT_NO_THROW(Interval<double>(lowerBound, upperBound, Interval<double>::Type::HalfOpenLeft));
        EXPECT_NO_THROW(Interval<double>(lowerBound, upperBound, Interval<double>::Type::HalfOpenRight));
    }

    {
        EXPECT_ANY_THROW(Interval<double>(1.0, 0.0, Interval<double>::Type::Closed));
        EXPECT_ANY_THROW(Interval<double>(1.0, 0.0, Interval<double>::Type::Open));
        EXPECT_ANY_THROW(Interval<double>(1.0, 0.0, Interval<double>::Type::HalfOpenLeft));
        EXPECT_ANY_THROW(Interval<double>(1.0, 0.0, Interval<double>::Type::HalfOpenRight));
    }

    {
        EXPECT_NO_THROW(Interval<double>(0.0, 0.0, Interval<double>::Type::Closed));
        EXPECT_ANY_THROW(Interval<double>(0.0, 0.0, Interval<double>::Type::Open));
        EXPECT_ANY_THROW(Interval<double>(0.0, 0.0, Interval<double>::Type::HalfOpenLeft));
        EXPECT_ANY_THROW(Interval<double>(0.0, 0.0, Interval<double>::Type::HalfOpenRight));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, EqualToOperator)
{
    {
        EXPECT_TRUE(
            Interval<double>(0.0, 1.0, Interval<double>::Type::Closed) ==
            Interval<double>(0.0, 1.0, Interval<double>::Type::Closed)
        );
        EXPECT_TRUE(
            Interval<double>(0.0, 1.0, Interval<double>::Type::Open) ==
            Interval<double>(0.0, 1.0, Interval<double>::Type::Open)
        );
        EXPECT_TRUE(
            Interval<double>(0.0, 1.0, Interval<double>::Type::HalfOpenLeft) ==
            Interval<double>(0.0, 1.0, Interval<double>::Type::HalfOpenLeft)
        );
        EXPECT_TRUE(
            Interval<double>(0.0, 1.0, Interval<double>::Type::HalfOpenRight) ==
            Interval<double>(0.0, 1.0, Interval<double>::Type::HalfOpenRight)
        );
    }

    {
        EXPECT_FALSE(
            Interval<double>(0.0, 1.0, Interval<double>::Type::Closed) ==
            Interval<double>(1.0, 1.0, Interval<double>::Type::Closed)
        );
        EXPECT_FALSE(
            Interval<double>(0.0, 1.0, Interval<double>::Type::Open) ==
            Interval<double>(0.0, 2.0, Interval<double>::Type::Open)
        );
        EXPECT_FALSE(
            Interval<double>(0.0, 1.0, Interval<double>::Type::HalfOpenLeft) ==
            Interval<double>(0.0, 1.0, Interval<double>::Type::Closed)
        );
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, NotEqualToOperator)
{
    {
        EXPECT_FALSE(
            Interval<double>(0.0, 1.0, Interval<double>::Type::Closed) !=
            Interval<double>(0.0, 1.0, Interval<double>::Type::Closed)
        );
        EXPECT_FALSE(
            Interval<double>(0.0, 1.0, Interval<double>::Type::Open) !=
            Interval<double>(0.0, 1.0, Interval<double>::Type::Open)
        );
        EXPECT_FALSE(
            Interval<double>(0.0, 1.0, Interval<double>::Type::HalfOpenLeft) !=
            Interval<double>(0.0, 1.0, Interval<double>::Type::HalfOpenLeft)
        );
        EXPECT_FALSE(
            Interval<double>(0.0, 1.0, Interval<double>::Type::HalfOpenRight) !=
            Interval<double>(0.0, 1.0, Interval<double>::Type::HalfOpenRight)
        );
    }

    {
        EXPECT_TRUE(
            Interval<double>(0.0, 1.0, Interval<double>::Type::Closed) !=
            Interval<double>(1.0, 1.0, Interval<double>::Type::Closed)
        );
        EXPECT_TRUE(
            Interval<double>(0.0, 1.0, Interval<double>::Type::Open) !=
            Interval<double>(0.0, 2.0, Interval<double>::Type::Open)
        );
        EXPECT_TRUE(
            Interval<double>(0.0, 1.0, Interval<double>::Type::HalfOpenLeft) !=
            Interval<double>(0.0, 1.0, Interval<double>::Type::Closed)
        );
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, IsDegenerate)
{
    {
        EXPECT_TRUE(Interval<double>(1.0, 1.0, Interval<double>::Type::Closed).isDegenerate());
    }

    {
        EXPECT_FALSE(Interval<double>(0.0, 1.0, Interval<double>::Type::Closed).isDegenerate());
        EXPECT_FALSE(Interval<double>(0.0, 1.0, Interval<double>::Type::Open).isDegenerate());
        EXPECT_FALSE(Interval<double>(0.0, 1.0, Interval<double>::Type::HalfOpenLeft).isDegenerate());
        EXPECT_FALSE(Interval<double>(0.0, 1.0, Interval<double>::Type::HalfOpenRight).isDegenerate());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, Intersects)
{
    {
        const Interval<double> interval = Interval<double>::Closed(0.0, 1.0);

        {
        }

        {
            EXPECT_FALSE(interval.intersects(Interval<double>::Closed(-2.0, -1.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenLeft(-2.0, -1.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenRight(-2.0, -1.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::Open(-2.0, -1.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<double>::Closed(-1.0, 0.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenLeft(-1.0, 0.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenRight(-1.0, 0.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::Open(-1.0, 0.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<double>::Closed(-1.0, 0.5)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenLeft(-1.0, 0.5)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenRight(-1.0, 0.5)));
            EXPECT_TRUE(interval.intersects(Interval<double>::Open(-1.0, 0.5)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<double>::Closed(0.25, 0.75)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenLeft(0.25, 0.75)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenRight(0.25, 0.75)));
            EXPECT_TRUE(interval.intersects(Interval<double>::Open(0.25, 0.75)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<double>::Closed(0.0, 1.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenLeft(0.0, 1.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenRight(0.0, 1.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::Open(0.0, 1.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<double>::Closed(-1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenLeft(-1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenRight(-1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::Open(-1.0, 2.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<double>::Closed(0.5, 1.5)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenLeft(0.5, 1.5)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenRight(0.5, 1.5)));
            EXPECT_TRUE(interval.intersects(Interval<double>::Open(0.5, 1.5)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<double>::Closed(1.0, 2.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenLeft(1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenRight(1.0, 2.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::Open(1.0, 2.0)));
        }

        {
            EXPECT_FALSE(interval.intersects(Interval<double>::Closed(2.0, 3.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenLeft(2.0, 3.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenRight(2.0, 3.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::Open(2.0, 3.0)));
        }
    }

    {
        const Interval<double> interval = Interval<double>::HalfOpenLeft(0.0, 1.0);

        {
        }

        {
            EXPECT_FALSE(interval.intersects(Interval<double>::Closed(-2.0, -1.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenLeft(-2.0, -1.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenRight(-2.0, -1.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::Open(-2.0, -1.0)));
        }

        {
            EXPECT_FALSE(interval.intersects(Interval<double>::Closed(-1.0, 0.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenLeft(-1.0, 0.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenRight(-1.0, 0.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::Open(-1.0, 0.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<double>::Closed(-1.0, 0.5)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenLeft(-1.0, 0.5)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenRight(-1.0, 0.5)));
            EXPECT_TRUE(interval.intersects(Interval<double>::Open(-1.0, 0.5)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<double>::Closed(0.25, 0.75)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenLeft(0.25, 0.75)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenRight(0.25, 0.75)));
            EXPECT_TRUE(interval.intersects(Interval<double>::Open(0.25, 0.75)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<double>::Closed(0.0, 1.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenLeft(0.0, 1.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenRight(0.0, 1.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::Open(0.0, 1.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<double>::Closed(-1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenLeft(-1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenRight(-1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::Open(-1.0, 2.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<double>::Closed(0.5, 1.5)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenLeft(0.5, 1.5)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenRight(0.5, 1.5)));
            EXPECT_TRUE(interval.intersects(Interval<double>::Open(0.5, 1.5)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<double>::Closed(1.0, 2.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenLeft(1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenRight(1.0, 2.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::Open(1.0, 2.0)));
        }

        {
            EXPECT_FALSE(interval.intersects(Interval<double>::Closed(2.0, 3.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenLeft(2.0, 3.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenRight(2.0, 3.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::Open(2.0, 3.0)));
        }
    }

    {
        const Interval<double> interval = Interval<double>::HalfOpenRight(0.0, 1.0);

        {
        }

        {
            EXPECT_FALSE(interval.intersects(Interval<double>::Closed(-2.0, -1.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenLeft(-2.0, -1.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenRight(-2.0, -1.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::Open(-2.0, -1.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<double>::Closed(-1.0, 0.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenLeft(-1.0, 0.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenRight(-1.0, 0.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::Open(-1.0, 0.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<double>::Closed(-1.0, 0.5)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenLeft(-1.0, 0.5)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenRight(-1.0, 0.5)));
            EXPECT_TRUE(interval.intersects(Interval<double>::Open(-1.0, 0.5)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<double>::Closed(0.25, 0.75)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenLeft(0.25, 0.75)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenRight(0.25, 0.75)));
            EXPECT_TRUE(interval.intersects(Interval<double>::Open(0.25, 0.75)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<double>::Closed(0.0, 1.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenLeft(0.0, 1.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenRight(0.0, 1.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::Open(0.0, 1.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<double>::Closed(-1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenLeft(-1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenRight(-1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::Open(-1.0, 2.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<double>::Closed(0.5, 1.5)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenLeft(0.5, 1.5)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenRight(0.5, 1.5)));
            EXPECT_TRUE(interval.intersects(Interval<double>::Open(0.5, 1.5)));
        }

        {
            EXPECT_FALSE(interval.intersects(Interval<double>::Closed(1.0, 2.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenLeft(1.0, 2.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenRight(1.0, 2.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::Open(1.0, 2.0)));
        }

        {
            EXPECT_FALSE(interval.intersects(Interval<double>::Closed(2.0, 3.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenLeft(2.0, 3.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenRight(2.0, 3.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::Open(2.0, 3.0)));
        }
    }

    {
        const Interval<double> interval = Interval<double>::Open(0.0, 1.0);

        {
        }

        {
            EXPECT_FALSE(interval.intersects(Interval<double>::Closed(-2.0, -1.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenLeft(-2.0, -1.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenRight(-2.0, -1.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::Open(-2.0, -1.0)));
        }

        {
            EXPECT_FALSE(interval.intersects(Interval<double>::Closed(-1.0, 0.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenLeft(-1.0, 0.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenRight(-1.0, 0.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::Open(-1.0, 0.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<double>::Closed(-1.0, 0.5)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenLeft(-1.0, 0.5)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenRight(-1.0, 0.5)));
            EXPECT_TRUE(interval.intersects(Interval<double>::Open(-1.0, 0.5)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<double>::Closed(0.25, 0.75)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenLeft(0.25, 0.75)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenRight(0.25, 0.75)));
            EXPECT_TRUE(interval.intersects(Interval<double>::Open(0.25, 0.75)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<double>::Closed(0.0, 1.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenLeft(0.0, 1.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenRight(0.0, 1.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::Open(0.0, 1.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<double>::Closed(-1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenLeft(-1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenRight(-1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<double>::Open(-1.0, 2.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<double>::Closed(0.5, 1.5)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenLeft(0.5, 1.5)));
            EXPECT_TRUE(interval.intersects(Interval<double>::HalfOpenRight(0.5, 1.5)));
            EXPECT_TRUE(interval.intersects(Interval<double>::Open(0.5, 1.5)));
        }

        {
            EXPECT_FALSE(interval.intersects(Interval<double>::Closed(1.0, 2.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenLeft(1.0, 2.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenRight(1.0, 2.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::Open(1.0, 2.0)));
        }

        {
            EXPECT_FALSE(interval.intersects(Interval<double>::Closed(2.0, 3.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenLeft(2.0, 3.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::HalfOpenRight(2.0, 3.0)));
            EXPECT_FALSE(interval.intersects(Interval<double>::Open(2.0, 3.0)));
        }
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, ContainsValue)
{
    {
        const Interval<double> interval = Interval<double>::Closed(0.0, 1.0);

        EXPECT_FALSE(interval.contains(-1.0));
        EXPECT_TRUE(interval.contains(0.0));
        EXPECT_TRUE(interval.contains(0.5));
        EXPECT_TRUE(interval.contains(1.0));
        EXPECT_FALSE(interval.contains(2.0));
    }

    {
        const Interval<double> interval = Interval<double>::HalfOpenLeft(0.0, 1.0);

        EXPECT_FALSE(interval.contains(-1.0));
        EXPECT_FALSE(interval.contains(0.0));
        EXPECT_TRUE(interval.contains(0.5));
        EXPECT_TRUE(interval.contains(1.0));
        EXPECT_FALSE(interval.contains(2.0));
    }

    {
        const Interval<double> interval = Interval<double>::HalfOpenRight(0.0, 1.0);

        EXPECT_FALSE(interval.contains(-1.0));
        EXPECT_TRUE(interval.contains(0.0));
        EXPECT_TRUE(interval.contains(0.5));
        EXPECT_FALSE(interval.contains(1.0));
        EXPECT_FALSE(interval.contains(2.0));
    }

    {
        const Interval<double> interval = Interval<double>::Open(0.0, 1.0);

        EXPECT_FALSE(interval.contains(-1.0));
        EXPECT_FALSE(interval.contains(0.0));
        EXPECT_TRUE(interval.contains(0.5));
        EXPECT_FALSE(interval.contains(1.0));
        EXPECT_FALSE(interval.contains(2.0));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, ContainsInterval)
{
    {
        const Interval<double> interval = Interval<double>::Closed(0.0, 1.0);

        {
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(-2.0, -1.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(-2.0, -1.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(-2.0, -1.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(-2.0, -1.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(-1.0, 0.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(-1.0, 0.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(-1.0, 0.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(-1.0, 0.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(-1.0, 0.5)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(-1.0, 0.5)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(-1.0, 0.5)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(-1.0, 0.5)));
        }

        {
            EXPECT_TRUE(interval.contains(Interval<double>::Closed(0.25, 0.75)));
            EXPECT_TRUE(interval.contains(Interval<double>::HalfOpenLeft(0.25, 0.75)));
            EXPECT_TRUE(interval.contains(Interval<double>::HalfOpenRight(0.25, 0.75)));
            EXPECT_TRUE(interval.contains(Interval<double>::Open(0.25, 0.75)));
        }

        {
            EXPECT_TRUE(interval.contains(Interval<double>::Closed(0.0, 1.0)));
            EXPECT_TRUE(interval.contains(Interval<double>::HalfOpenLeft(0.0, 1.0)));
            EXPECT_TRUE(interval.contains(Interval<double>::HalfOpenRight(0.0, 1.0)));
            EXPECT_TRUE(interval.contains(Interval<double>::Open(0.0, 1.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(-1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(-1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(-1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(-1.0, 2.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(0.5, 1.5)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(0.5, 1.5)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(0.5, 1.5)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(0.5, 1.5)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(1.0, 2.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(2.0, 3.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(2.0, 3.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(2.0, 3.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(2.0, 3.0)));
        }
    }

    {
        const Interval<double> interval = Interval<double>::HalfOpenLeft(0.0, 1.0);

        {
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(-2.0, -1.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(-2.0, -1.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(-2.0, -1.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(-2.0, -1.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(-1.0, 0.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(-1.0, 0.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(-1.0, 0.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(-1.0, 0.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(-1.0, 0.5)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(-1.0, 0.5)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(-1.0, 0.5)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(-1.0, 0.5)));
        }

        {
            EXPECT_TRUE(interval.contains(Interval<double>::Closed(0.25, 0.75)));
            EXPECT_TRUE(interval.contains(Interval<double>::HalfOpenLeft(0.25, 0.75)));
            EXPECT_TRUE(interval.contains(Interval<double>::HalfOpenRight(0.25, 0.75)));
            EXPECT_TRUE(interval.contains(Interval<double>::Open(0.25, 0.75)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(0.0, 1.0)));
            EXPECT_TRUE(interval.contains(Interval<double>::HalfOpenLeft(0.0, 1.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(0.0, 1.0)));
            EXPECT_TRUE(interval.contains(Interval<double>::Open(0.0, 1.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(-1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(-1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(-1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(-1.0, 2.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(0.5, 1.5)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(0.5, 1.5)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(0.5, 1.5)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(0.5, 1.5)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(1.0, 2.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(2.0, 3.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(2.0, 3.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(2.0, 3.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(2.0, 3.0)));
        }
    }

    {
        const Interval<double> interval = Interval<double>::HalfOpenRight(0.0, 1.0);

        {
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(-2.0, -1.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(-2.0, -1.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(-2.0, -1.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(-2.0, -1.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(-1.0, 0.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(-1.0, 0.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(-1.0, 0.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(-1.0, 0.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(-1.0, 0.5)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(-1.0, 0.5)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(-1.0, 0.5)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(-1.0, 0.5)));
        }

        {
            EXPECT_TRUE(interval.contains(Interval<double>::Closed(0.25, 0.75)));
            EXPECT_TRUE(interval.contains(Interval<double>::HalfOpenLeft(0.25, 0.75)));
            EXPECT_TRUE(interval.contains(Interval<double>::HalfOpenRight(0.25, 0.75)));
            EXPECT_TRUE(interval.contains(Interval<double>::Open(0.25, 0.75)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(0.0, 1.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(0.0, 1.0)));
            EXPECT_TRUE(interval.contains(Interval<double>::HalfOpenRight(0.0, 1.0)));
            EXPECT_TRUE(interval.contains(Interval<double>::Open(0.0, 1.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(-1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(-1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(-1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(-1.0, 2.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(0.5, 1.5)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(0.5, 1.5)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(0.5, 1.5)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(0.5, 1.5)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(1.0, 2.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(2.0, 3.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(2.0, 3.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(2.0, 3.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(2.0, 3.0)));
        }
    }

    {
        const Interval<double> interval = Interval<double>::Open(0.0, 1.0);

        {
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(-2.0, -1.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(-2.0, -1.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(-2.0, -1.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(-2.0, -1.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(-1.0, 0.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(-1.0, 0.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(-1.0, 0.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(-1.0, 0.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(-1.0, 0.5)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(-1.0, 0.5)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(-1.0, 0.5)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(-1.0, 0.5)));
        }

        {
            EXPECT_TRUE(interval.contains(Interval<double>::Closed(0.25, 0.75)));
            EXPECT_TRUE(interval.contains(Interval<double>::HalfOpenLeft(0.25, 0.75)));
            EXPECT_TRUE(interval.contains(Interval<double>::HalfOpenRight(0.25, 0.75)));
            EXPECT_TRUE(interval.contains(Interval<double>::Open(0.25, 0.75)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(0.0, 1.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(0.0, 1.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(0.0, 1.0)));
            EXPECT_TRUE(interval.contains(Interval<double>::Open(0.0, 1.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(-1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(-1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(-1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(-1.0, 2.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(0.5, 1.5)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(0.5, 1.5)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(0.5, 1.5)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(0.5, 1.5)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(1.0, 2.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<double>::Closed(2.0, 3.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenLeft(2.0, 3.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::HalfOpenRight(2.0, 3.0)));
            EXPECT_FALSE(interval.contains(Interval<double>::Open(2.0, 3.0)));
        }
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, GetType)
{
    {
        EXPECT_EQ(Interval<double>::Type::Closed, Interval<double>(0.0, 1.0, Interval<double>::Type::Closed).getType());
        EXPECT_EQ(Interval<double>::Type::Open, Interval<double>(0.0, 1.0, Interval<double>::Type::Open).getType());
        EXPECT_EQ(
            Interval<double>::Type::HalfOpenLeft,
            Interval<double>(0.0, 1.0, Interval<double>::Type::HalfOpenLeft).getType()
        );
        EXPECT_EQ(
            Interval<double>::Type::HalfOpenRight,
            Interval<double>(0.0, 1.0, Interval<double>::Type::HalfOpenRight).getType()
        );
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, GetLowerBound)
{
    {
        EXPECT_EQ(0.0, Interval<double>(0.0, 1.0, Interval<double>::Type::Closed).getLowerBound());
        EXPECT_EQ(0.0, Interval<double>(0.0, 1.0, Interval<double>::Type::Open).getLowerBound());
        EXPECT_EQ(0.0, Interval<double>(0.0, 1.0, Interval<double>::Type::HalfOpenLeft).getLowerBound());
        EXPECT_EQ(0.0, Interval<double>(0.0, 1.0, Interval<double>::Type::HalfOpenRight).getLowerBound());
        EXPECT_EQ(1.0, Interval<double>(1.0, 1.0, Interval<double>::Type::Closed).getLowerBound());
    }

    {
        EXPECT_EQ(-1.0, Interval<double>(-1.0, +1.0, Interval<double>::Type::Closed).getLowerBound());
        EXPECT_EQ(-1.0, Interval<double>(-1.0, +1.0, Interval<double>::Type::Open).getLowerBound());
        EXPECT_EQ(-1.0, Interval<double>(-1.0, +1.0, Interval<double>::Type::HalfOpenLeft).getLowerBound());
        EXPECT_EQ(-1.0, Interval<double>(-1.0, +1.0, Interval<double>::Type::HalfOpenRight).getLowerBound());
    }

    {
        Interval<double> interval(0.0, 1.0, Interval<double>::Type::Closed);

        EXPECT_EQ(&interval.getLowerBound(), &interval.getLowerBound());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, GetUpperBound)
{
    {
        EXPECT_EQ(1.0, Interval<double>(0.0, 1.0, Interval<double>::Type::Closed).getUpperBound());
        EXPECT_EQ(1.0, Interval<double>(0.0, 1.0, Interval<double>::Type::Open).getUpperBound());
        EXPECT_EQ(1.0, Interval<double>(0.0, 1.0, Interval<double>::Type::HalfOpenLeft).getUpperBound());
        EXPECT_EQ(1.0, Interval<double>(0.0, 1.0, Interval<double>::Type::HalfOpenRight).getUpperBound());
        EXPECT_EQ(1.0, Interval<double>(1.0, 1.0, Interval<double>::Type::Closed).getUpperBound());
    }

    {
        EXPECT_EQ(+1.0, Interval<double>(-1.0, +1.0, Interval<double>::Type::Closed).getUpperBound());
        EXPECT_EQ(+1.0, Interval<double>(-1.0, +1.0, Interval<double>::Type::Open).getUpperBound());
        EXPECT_EQ(+1.0, Interval<double>(-1.0, +1.0, Interval<double>::Type::HalfOpenLeft).getUpperBound());
        EXPECT_EQ(+1.0, Interval<double>(-1.0, +1.0, Interval<double>::Type::HalfOpenRight).getUpperBound());
    }

    {
        Interval<double> interval(0.0, 1.0, Interval<double>::Type::Closed);

        EXPECT_EQ(&interval.getUpperBound(), &interval.getUpperBound());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, GetIntersectionWith)
{
    {
        const Interval<double> interval = Interval<double>::Closed(0.0, 1.0);

        {
        }

        {
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Closed(-2.0, -1.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenLeft(-2.0, -1.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenRight(-2.0, -1.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Open(-2.0, -1.0)).has_value());
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Closed(-1.0, 0.0)), Interval<double>::Closed(0.0, 0.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenLeft(-1.0, 0.0)),
                Interval<double>::Closed(0.0, 0.0)
            );
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenRight(-1.0, 0.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Open(-1.0, 0.0)).has_value());
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Closed(-1.0, 0.5)), Interval<double>::Closed(0.0, 0.5)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenLeft(-1.0, 0.5)),
                Interval<double>::Closed(0.0, 0.5)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenRight(-1.0, 0.5)),
                Interval<double>::HalfOpenRight(0.0, 0.5)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Open(-1.0, 0.5)),
                Interval<double>::HalfOpenRight(0.0, 0.5)
            );
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Closed(0.25, 0.75)), Interval<double>::Closed(0.25, 0.75)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenLeft(0.25, 0.75)),
                Interval<double>::HalfOpenLeft(0.25, 0.75)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenRight(0.25, 0.75)),
                Interval<double>::HalfOpenRight(0.25, 0.75)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Open(0.25, 0.75)), Interval<double>::Open(0.25, 0.75)
            );
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Closed(0.0, 1.0)), Interval<double>::Closed(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenLeft(0.0, 1.0)),
                Interval<double>::HalfOpenLeft(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenRight(0.0, 1.0)),
                Interval<double>::HalfOpenRight(0.0, 1.0)
            );
            EXPECT_EQ(interval.getIntersectionWith(Interval<double>::Open(0.0, 1.0)), Interval<double>::Open(0.0, 1.0));
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Closed(-1.0, 2.0)), Interval<double>::Closed(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenLeft(-1.0, 2.0)),
                Interval<double>::Closed(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenRight(-1.0, 2.0)),
                Interval<double>::Closed(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Open(-1.0, 2.0)), Interval<double>::Closed(0.0, 1.0)
            );
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Closed(0.5, 1.5)), Interval<double>::Closed(0.5, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenLeft(0.5, 1.5)),
                Interval<double>::HalfOpenLeft(0.5, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenRight(0.5, 1.5)),
                Interval<double>::Closed(0.5, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Open(0.5, 1.5)), Interval<double>::HalfOpenLeft(0.5, 1.0)
            );
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Closed(1.0, 2.0)), Interval<double>::Closed(1.0, 1.0)
            );
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenLeft(1.0, 2.0)).has_value());
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenRight(1.0, 2.0)),
                Interval<double>::Closed(1.0, 1.0)
            );
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Open(1.0, 2.0)).has_value());
        }

        {
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Closed(2.0, 3.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenLeft(2.0, 3.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenRight(2.0, 3.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Open(2.0, 3.0)).has_value());
        }
    }

    {
        const Interval<double> interval = Interval<double>::HalfOpenLeft(0.0, 1.0);

        {
        }

        {
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Closed(-2.0, -1.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenLeft(-2.0, -1.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenRight(-2.0, -1.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Open(-2.0, -1.0)).has_value());
        }

        {
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Closed(-1.0, 0.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenLeft(-1.0, 0.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenRight(-1.0, 0.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Open(-1.0, 0.0)).has_value());
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Closed(-1.0, 0.5)),
                Interval<double>::HalfOpenLeft(0.0, 0.5)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenLeft(-1.0, 0.5)),
                Interval<double>::HalfOpenLeft(0.0, 0.5)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenRight(-1.0, 0.5)),
                Interval<double>::Open(0.0, 0.5)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Open(-1.0, 0.5)), Interval<double>::Open(0.0, 0.5)
            );
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Closed(0.25, 0.75)), Interval<double>::Closed(0.25, 0.75)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenLeft(0.25, 0.75)),
                Interval<double>::HalfOpenLeft(0.25, 0.75)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenRight(0.25, 0.75)),
                Interval<double>::HalfOpenRight(0.25, 0.75)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Open(0.25, 0.75)), Interval<double>::Open(0.25, 0.75)
            );
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Closed(0.0, 1.0)),
                Interval<double>::HalfOpenLeft(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenLeft(0.0, 1.0)),
                Interval<double>::HalfOpenLeft(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenRight(0.0, 1.0)),
                Interval<double>::Open(0.0, 1.0)
            );
            EXPECT_EQ(interval.getIntersectionWith(Interval<double>::Open(0.0, 1.0)), Interval<double>::Open(0.0, 1.0));
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Closed(-1.0, 2.0)),
                Interval<double>::HalfOpenLeft(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenLeft(-1.0, 2.0)),
                Interval<double>::HalfOpenLeft(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenRight(-1.0, 2.0)),
                Interval<double>::HalfOpenLeft(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Open(-1.0, 2.0)),
                Interval<double>::HalfOpenLeft(0.0, 1.0)
            );
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Closed(0.5, 1.5)), Interval<double>::Closed(0.5, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenLeft(0.5, 1.5)),
                Interval<double>::HalfOpenLeft(0.5, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenRight(0.5, 1.5)),
                Interval<double>::Closed(0.5, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Open(0.5, 1.5)), Interval<double>::HalfOpenLeft(0.5, 1.0)
            );
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Closed(1.0, 2.0)), Interval<double>::Closed(1.0, 1.0)
            );
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenLeft(1.0, 2.0)).has_value());
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenRight(1.0, 2.0)),
                Interval<double>::Closed(1.0, 1.0)
            );
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Open(1.0, 2.0)).has_value());
        }

        {
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Closed(2.0, 3.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenLeft(2.0, 3.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenRight(2.0, 3.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Open(2.0, 3.0)).has_value());
        }
    }

    {
        const Interval<double> interval = Interval<double>::HalfOpenRight(0.0, 1.0);

        {
        }

        {
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Closed(-2.0, -1.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenLeft(-2.0, -1.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenRight(-2.0, -1.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Open(-2.0, -1.0)).has_value());
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Closed(-1.0, 0.0)), Interval<double>::Closed(0.0, 0.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenLeft(-1.0, 0.0)),
                Interval<double>::Closed(0.0, 0.0)
            );
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenRight(-1.0, 0.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Open(-1.0, 0.0)).has_value());
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Closed(-1.0, 0.5)), Interval<double>::Closed(0.0, 0.5)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenLeft(-1.0, 0.5)),
                Interval<double>::Closed(0.0, 0.5)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenRight(-1.0, 0.5)),
                Interval<double>::HalfOpenRight(0.0, 0.5)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Open(-1.0, 0.5)),
                Interval<double>::HalfOpenRight(0.0, 0.5)
            );
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Closed(0.25, 0.75)), Interval<double>::Closed(0.25, 0.75)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenLeft(0.25, 0.75)),
                Interval<double>::HalfOpenLeft(0.25, 0.75)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenRight(0.25, 0.75)),
                Interval<double>::HalfOpenRight(0.25, 0.75)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Open(0.25, 0.75)), Interval<double>::Open(0.25, 0.75)
            );
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Closed(0.0, 1.0)),
                Interval<double>::HalfOpenRight(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenLeft(0.0, 1.0)), Interval<double>::Open(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenRight(0.0, 1.0)),
                Interval<double>::HalfOpenRight(0.0, 1.0)
            );
            EXPECT_EQ(interval.getIntersectionWith(Interval<double>::Open(0.0, 1.0)), Interval<double>::Open(0.0, 1.0));
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Closed(-1.0, 2.0)),
                Interval<double>::HalfOpenRight(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenLeft(-1.0, 2.0)),
                Interval<double>::HalfOpenRight(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenRight(-1.0, 2.0)),
                Interval<double>::HalfOpenRight(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Open(-1.0, 2.0)),
                Interval<double>::HalfOpenRight(0.0, 1.0)
            );
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Closed(0.5, 1.5)),
                Interval<double>::HalfOpenRight(0.5, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenLeft(0.5, 1.5)), Interval<double>::Open(0.5, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenRight(0.5, 1.5)),
                Interval<double>::HalfOpenRight(0.5, 1.0)
            );
            EXPECT_EQ(interval.getIntersectionWith(Interval<double>::Open(0.5, 1.5)), Interval<double>::Open(0.5, 1.0));
        }

        {
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Closed(1.0, 2.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenLeft(1.0, 2.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenRight(1.0, 2.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Open(1.0, 2.0)).has_value());
        }

        {
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Closed(2.0, 3.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenLeft(2.0, 3.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenRight(2.0, 3.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Open(2.0, 3.0)).has_value());
        }
    }

    {
        const Interval<double> interval = Interval<double>::Open(0.0, 1.0);

        {
        }

        {
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Closed(-2.0, -1.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenLeft(-2.0, -1.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenRight(-2.0, -1.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Open(-2.0, -1.0)).has_value());
        }

        {
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Closed(-1.0, 0.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenLeft(-1.0, 0.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenRight(-1.0, 0.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Open(-1.0, 0.0)).has_value());
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Closed(-1.0, 0.5)),
                Interval<double>::HalfOpenLeft(0.0, 0.5)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenLeft(-1.0, 0.5)),
                Interval<double>::HalfOpenLeft(0.0, 0.5)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenRight(-1.0, 0.5)),
                Interval<double>::Open(0.0, 0.5)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Open(-1.0, 0.5)), Interval<double>::Open(0.0, 0.5)
            );
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Closed(0.25, 0.75)), Interval<double>::Closed(0.25, 0.75)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenLeft(0.25, 0.75)),
                Interval<double>::HalfOpenLeft(0.25, 0.75)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenRight(0.25, 0.75)),
                Interval<double>::HalfOpenRight(0.25, 0.75)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Open(0.25, 0.75)), Interval<double>::Open(0.25, 0.75)
            );
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Closed(0.0, 1.0)), Interval<double>::Open(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenLeft(0.0, 1.0)), Interval<double>::Open(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenRight(0.0, 1.0)),
                Interval<double>::Open(0.0, 1.0)
            );
            EXPECT_EQ(interval.getIntersectionWith(Interval<double>::Open(0.0, 1.0)), Interval<double>::Open(0.0, 1.0));
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Closed(-1.0, 2.0)), Interval<double>::Open(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenLeft(-1.0, 2.0)),
                Interval<double>::Open(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenRight(-1.0, 2.0)),
                Interval<double>::Open(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Open(-1.0, 2.0)), Interval<double>::Open(0.0, 1.0)
            );
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::Closed(0.5, 1.5)),
                Interval<double>::HalfOpenRight(0.5, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenLeft(0.5, 1.5)), Interval<double>::Open(0.5, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<double>::HalfOpenRight(0.5, 1.5)),
                Interval<double>::HalfOpenRight(0.5, 1.0)
            );
            EXPECT_EQ(interval.getIntersectionWith(Interval<double>::Open(0.5, 1.5)), Interval<double>::Open(0.5, 1.0));
        }

        {
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Closed(1.0, 2.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenLeft(1.0, 2.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenRight(1.0, 2.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Open(1.0, 2.0)).has_value());
        }

        {
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Closed(2.0, 3.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenLeft(2.0, 3.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::HalfOpenRight(2.0, 3.0)).has_value());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<double>::Open(2.0, 3.0)).has_value());
        }
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, GetUnionWith)
{
    {
        const Interval<double> interval = Interval<double>::Closed(0.0, 1.0);

        {
        }

        {
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::Closed(-2.0, -1.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::HalfOpenLeft(-2.0, -1.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::HalfOpenRight(-2.0, -1.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::Open(-2.0, -1.0)).has_value());
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Closed(-1.0, 0.0)), Interval<double>::Closed(-1.0, 1.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(-1.0, 0.0)),
                Interval<double>::HalfOpenLeft(-1.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(-1.0, 0.0)), Interval<double>::Closed(-1.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::Open(-1.0, 0.0)), Interval<double>::HalfOpenLeft(-1.0, 1.0)
            );
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Closed(-1.0, 0.5)), Interval<double>::Closed(-1.0, 1.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(-1.0, 0.5)),
                Interval<double>::HalfOpenLeft(-1.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(-1.0, 0.5)), Interval<double>::Closed(-1.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::Open(-1.0, 0.5)), Interval<double>::HalfOpenLeft(-1.0, 1.0)
            );
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Closed(0.25, 0.75)), Interval<double>::Closed(0.0, 1.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(0.25, 0.75)), Interval<double>::Closed(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(0.25, 0.75)), Interval<double>::Closed(0.0, 1.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Open(0.25, 0.75)), Interval<double>::Closed(0.0, 1.0));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Closed(0.0, 1.0)), Interval<double>::Closed(0.0, 1.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(0.0, 1.0)), Interval<double>::Closed(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(0.0, 1.0)), Interval<double>::Closed(0.0, 1.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Open(0.0, 1.0)), Interval<double>::Closed(0.0, 1.0));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Closed(-1.0, 2.0)), Interval<double>::Closed(-1.0, 2.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(-1.0, 2.0)),
                Interval<double>::HalfOpenLeft(-1.0, 2.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(-1.0, 2.0)),
                Interval<double>::HalfOpenRight(-1.0, 2.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Open(-1.0, 2.0)), Interval<double>::Open(-1.0, 2.0));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Closed(0.5, 1.5)), Interval<double>::Closed(0.0, 1.5));
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(0.5, 1.5)), Interval<double>::Closed(0.0, 1.5)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(0.5, 1.5)),
                Interval<double>::HalfOpenRight(0.0, 1.5)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::Open(0.5, 1.5)), Interval<double>::HalfOpenRight(0.0, 1.5)
            );
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Closed(1.0, 2.0)), Interval<double>::Closed(0.0, 2.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(1.0, 2.0)), Interval<double>::Closed(0.0, 2.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(1.0, 2.0)),
                Interval<double>::HalfOpenRight(0.0, 2.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::Open(1.0, 2.0)), Interval<double>::HalfOpenRight(0.0, 2.0)
            );
        }

        {
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::Closed(2.0, 3.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::HalfOpenLeft(2.0, 3.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::HalfOpenRight(2.0, 3.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::Open(2.0, 3.0)).has_value());
        }
    }

    {
        const Interval<double> interval = Interval<double>::HalfOpenLeft(0.0, 1.0);

        {
        }

        {
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::Closed(-2.0, -1.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::HalfOpenLeft(-2.0, -1.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::HalfOpenRight(-2.0, -1.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::Open(-2.0, -1.0)).has_value());
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Closed(-1.0, 0.0)), Interval<double>::Closed(-1.0, 1.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(-1.0, 0.0)),
                Interval<double>::HalfOpenLeft(-1.0, 1.0)
            );
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::HalfOpenRight(-1.0, 0.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::Open(-1.0, 0.0)).has_value());
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Closed(-1.0, 0.5)), Interval<double>::Closed(-1.0, 1.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(-1.0, 0.5)),
                Interval<double>::HalfOpenLeft(-1.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(-1.0, 0.5)), Interval<double>::Closed(-1.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::Open(-1.0, 0.5)), Interval<double>::HalfOpenLeft(-1.0, 1.0)
            );
        }

        {
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::Closed(0.25, 0.75)), Interval<double>::HalfOpenLeft(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(0.25, 0.75)),
                Interval<double>::HalfOpenLeft(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(0.25, 0.75)),
                Interval<double>::HalfOpenLeft(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::Open(0.25, 0.75)), Interval<double>::HalfOpenLeft(0.0, 1.0)
            );
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Closed(0.0, 1.0)), Interval<double>::Closed(0.0, 1.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(0.0, 1.0)),
                Interval<double>::HalfOpenLeft(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(0.0, 1.0)), Interval<double>::Closed(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::Open(0.0, 1.0)), Interval<double>::HalfOpenLeft(0.0, 1.0)
            );
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Closed(-1.0, 2.0)), Interval<double>::Closed(-1.0, 2.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(-1.0, 2.0)),
                Interval<double>::HalfOpenLeft(-1.0, 2.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(-1.0, 2.0)),
                Interval<double>::HalfOpenRight(-1.0, 2.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Open(-1.0, 2.0)), Interval<double>::Open(-1.0, 2.0));
        }

        {
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::Closed(0.5, 1.5)), Interval<double>::HalfOpenLeft(0.0, 1.5)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(0.5, 1.5)),
                Interval<double>::HalfOpenLeft(0.0, 1.5)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(0.5, 1.5)), Interval<double>::Open(0.0, 1.5)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Open(0.5, 1.5)), Interval<double>::Open(0.0, 1.5));
        }

        {
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::Closed(1.0, 2.0)), Interval<double>::HalfOpenLeft(0.0, 2.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(1.0, 2.0)),
                Interval<double>::HalfOpenLeft(0.0, 2.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(1.0, 2.0)), Interval<double>::Open(0.0, 2.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Open(1.0, 2.0)), Interval<double>::Open(0.0, 2.0));
        }

        {
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::Closed(2.0, 3.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::HalfOpenLeft(2.0, 3.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::HalfOpenRight(2.0, 3.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::Open(2.0, 3.0)).has_value());
        }
    }

    {
        const Interval<double> interval = Interval<double>::HalfOpenRight(0.0, 1.0);

        {
        }

        {
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::Closed(-2.0, -1.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::HalfOpenLeft(-2.0, -1.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::HalfOpenRight(-2.0, -1.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::Open(-2.0, -1.0)).has_value());
        }

        {
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::Closed(-1.0, 0.0)), Interval<double>::HalfOpenRight(-1.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(-1.0, 0.0)), Interval<double>::Open(-1.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(-1.0, 0.0)),
                Interval<double>::HalfOpenRight(-1.0, 1.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Open(-1.0, 0.0)), Interval<double>::Open(-1.0, 1.0));
        }

        {
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::Closed(-1.0, 0.5)), Interval<double>::HalfOpenRight(-1.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(-1.0, 0.5)), Interval<double>::Open(-1.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(-1.0, 0.5)),
                Interval<double>::HalfOpenRight(-1.0, 1.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Open(-1.0, 0.5)), Interval<double>::Open(-1.0, 1.0));
        }

        {
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::Closed(0.25, 0.75)), Interval<double>::HalfOpenRight(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(0.25, 0.75)),
                Interval<double>::HalfOpenRight(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(0.25, 0.75)),
                Interval<double>::HalfOpenRight(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::Open(0.25, 0.75)), Interval<double>::HalfOpenRight(0.0, 1.0)
            );
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Closed(0.0, 1.0)), Interval<double>::Closed(0.0, 1.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(0.0, 1.0)), Interval<double>::Closed(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(0.0, 1.0)),
                Interval<double>::HalfOpenRight(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::Open(0.0, 1.0)), Interval<double>::HalfOpenRight(0.0, 1.0)
            );
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Closed(-1.0, 2.0)), Interval<double>::Closed(-1.0, 2.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(-1.0, 2.0)),
                Interval<double>::HalfOpenLeft(-1.0, 2.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(-1.0, 2.0)),
                Interval<double>::HalfOpenRight(-1.0, 2.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Open(-1.0, 2.0)), Interval<double>::Open(-1.0, 2.0));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Closed(0.5, 1.5)), Interval<double>::Closed(0.0, 1.5));
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(0.5, 1.5)), Interval<double>::Closed(0.0, 1.5)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(0.5, 1.5)),
                Interval<double>::HalfOpenRight(0.0, 1.5)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::Open(0.5, 1.5)), Interval<double>::HalfOpenRight(0.0, 1.5)
            );
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Closed(1.0, 2.0)), Interval<double>::Closed(0.0, 2.0));
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::HalfOpenLeft(1.0, 2.0)).has_value());
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(1.0, 2.0)),
                Interval<double>::HalfOpenRight(0.0, 2.0)
            );
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::Open(1.0, 2.0)).has_value());
        }

        {
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::Closed(2.0, 3.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::HalfOpenLeft(2.0, 3.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::HalfOpenRight(2.0, 3.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::Open(2.0, 3.0)).has_value());
        }
    }

    {
        const Interval<double> interval = Interval<double>::Open(0.0, 1.0);

        {
        }

        {
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::Closed(-2.0, -1.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::HalfOpenLeft(-2.0, -1.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::HalfOpenRight(-2.0, -1.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::Open(-2.0, -1.0)).has_value());
        }

        {
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::Closed(-1.0, 0.0)), Interval<double>::HalfOpenRight(-1.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(-1.0, 0.0)), Interval<double>::Open(-1.0, 1.0)
            );
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::HalfOpenRight(-1.0, 0.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::Open(-1.0, 0.0)).has_value());
        }

        {
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::Closed(-1.0, 0.5)), Interval<double>::HalfOpenRight(-1.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(-1.0, 0.5)), Interval<double>::Open(-1.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(-1.0, 0.5)),
                Interval<double>::HalfOpenRight(-1.0, 1.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Open(-1.0, 0.5)), Interval<double>::Open(-1.0, 1.0));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Closed(0.25, 0.75)), Interval<double>::Open(0.0, 1.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(0.25, 0.75)), Interval<double>::Open(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(0.25, 0.75)), Interval<double>::Open(0.0, 1.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Open(0.25, 0.75)), Interval<double>::Open(0.0, 1.0));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Closed(0.0, 1.0)), Interval<double>::Closed(0.0, 1.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(0.0, 1.0)),
                Interval<double>::HalfOpenLeft(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(0.0, 1.0)),
                Interval<double>::HalfOpenRight(0.0, 1.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Open(0.0, 1.0)), Interval<double>::Open(0.0, 1.0));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Closed(-1.0, 2.0)), Interval<double>::Closed(-1.0, 2.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(-1.0, 2.0)),
                Interval<double>::HalfOpenLeft(-1.0, 2.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(-1.0, 2.0)),
                Interval<double>::HalfOpenRight(-1.0, 2.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Open(-1.0, 2.0)), Interval<double>::Open(-1.0, 2.0));
        }

        {
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::Closed(0.5, 1.5)), Interval<double>::HalfOpenLeft(0.0, 1.5)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenLeft(0.5, 1.5)),
                Interval<double>::HalfOpenLeft(0.0, 1.5)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(0.5, 1.5)), Interval<double>::Open(0.0, 1.5)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<double>::Open(0.5, 1.5)), Interval<double>::Open(0.0, 1.5));
        }

        {
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::Closed(1.0, 2.0)), Interval<double>::HalfOpenLeft(0.0, 2.0)
            );
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::HalfOpenLeft(1.0, 2.0)).has_value());
            EXPECT_EQ(
                interval.getUnionWith(Interval<double>::HalfOpenRight(1.0, 2.0)), Interval<double>::Open(0.0, 2.0)
            );
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::Open(1.0, 2.0)).has_value());
        }

        {
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::Closed(2.0, 3.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::HalfOpenLeft(2.0, 3.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::HalfOpenRight(2.0, 3.0)).has_value());
            EXPECT_FALSE(interval.getUnionWith(Interval<double>::Open(2.0, 3.0)).has_value());
        }
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, GenerateArrayWithStep)
{
    using ostk::core::container::Array;
    using ostk::mathematics::object::Interval;

    // Closed

    {
        const Interval<double> interval = {0.0, 1.0, Interval<double>::Type::Closed};

        const Array<double> array = interval.generateArrayWithStep(0.5);

        EXPECT_TRUE(array.isNear(Array<double>({0.0, 0.5, 1.0}), 1e-15));
    }

    {
        const Interval<double> interval = {0.0, 1.0, Interval<double>::Type::Closed};

        const Array<double> array = interval.generateArrayWithStep(-0.5);

        EXPECT_TRUE(array.isNear(Array<double>({1.0, 0.5, 0.0}), 1e-15));
    }

    {
        const Interval<double> interval = {0.0, 1.0, Interval<double>::Type::Closed};

        const Array<double> array = interval.generateArrayWithStep(2.0);

        EXPECT_TRUE(array.isNear(Array<double>({0.0, 1.0}), 1e-15));
    }

    {
        const Interval<double> interval = {0.0, 1.0, Interval<double>::Type::Closed};

        const Array<double> array = interval.generateArrayWithStep(-2.0);

        EXPECT_TRUE(array.isNear(Array<double>({1.0, 0.0}), 1e-15));
    }

    // Open

    {
        const Interval<double> interval = {0.0, 1.0, Interval<double>::Type::Open};

        const Array<double> array = interval.generateArrayWithStep(0.5);

        EXPECT_TRUE(array.isNear(Array<double>({0.5}), 1e-15));
    }

    {
        const Interval<double> interval = {0.0, 1.0, Interval<double>::Type::Open};

        const Array<double> array = interval.generateArrayWithStep(-0.5);

        EXPECT_TRUE(array.isNear(Array<double>({0.5}), 1e-15));
    }

    {
        const Interval<double> interval = {0.0, 1.0, Interval<double>::Type::Open};

        const Array<double> array = interval.generateArrayWithStep(2.0);

        EXPECT_TRUE(array.isEmpty());
    }

    {
        const Interval<double> interval = {0.0, 1.0, Interval<double>::Type::Open};

        const Array<double> array = interval.generateArrayWithStep(-2.0);

        EXPECT_TRUE(array.isEmpty());
    }

    // Half-Open Left

    {
        const Interval<double> interval = {0.0, 1.0, Interval<double>::Type::HalfOpenLeft};

        const Array<double> array = interval.generateArrayWithStep(0.5);

        EXPECT_TRUE(array.isNear(Array<double>({0.5, 1.0}), 1e-15));
    }

    {
        const Interval<double> interval = {0.0, 1.0, Interval<double>::Type::HalfOpenLeft};

        const Array<double> array = interval.generateArrayWithStep(-0.5);

        EXPECT_TRUE(array.isNear(Array<double>({1.0, 0.5}), 1e-15));
    }

    {
        const Interval<double> interval = {0.0, 1.0, Interval<double>::Type::HalfOpenLeft};

        const Array<double> array = interval.generateArrayWithStep(2.0);

        EXPECT_TRUE(array.isNear(Array<double>({1.0}), 1e-15));
    }

    {
        const Interval<double> interval = {0.0, 1.0, Interval<double>::Type::HalfOpenLeft};

        const Array<double> array = interval.generateArrayWithStep(-2.0);

        EXPECT_TRUE(array.isNear(Array<double>({1.0}), 1e-15));
    }

    // Half-Open Right

    {
        const Interval<double> interval = {0.0, 1.0, Interval<double>::Type::HalfOpenRight};

        const Array<double> array = interval.generateArrayWithStep(0.5);

        EXPECT_TRUE(array.isNear(Array<double>({0.0, 0.5}), 1e-15));
    }

    {
        const Interval<double> interval = {0.0, 1.0, Interval<double>::Type::HalfOpenRight};

        const Array<double> array = interval.generateArrayWithStep(-0.5);

        EXPECT_TRUE(array.isNear(Array<double>({0.5, 0.0}), 1e-15));
    }

    {
        const Interval<double> interval = {0.0, 1.0, Interval<double>::Type::HalfOpenRight};

        const Array<double> array = interval.generateArrayWithStep(2.0);

        EXPECT_TRUE(array.isNear(Array<double>({0.0}), 1e-15));
    }

    {
        const Interval<double> interval = {0.0, 1.0, Interval<double>::Type::HalfOpenRight};

        const Array<double> array = interval.generateArrayWithStep(-2.0);

        EXPECT_TRUE(array.isNear(Array<double>({0.0}), 1e-15));
    }

    {
        EXPECT_ANY_THROW(Interval<double>(0.0, 1.0, Interval<double>::Type::Closed).generateArrayWithStep(0.0));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, GenerateArrayWithSize)
{
    using ostk::core::container::Array;
    using ostk::core::type::Size;

    using ostk::mathematics::object::Interval;

    // Closed

    {
        const Interval<double> interval = {0.0, 1.0, Interval<double>::Type::Closed};

        const Array<double> array = interval.generateArrayWithSize(3);

        EXPECT_TRUE(array.isNear(Array<double>({0.0, 0.5, 1.0}), 1e-15));
    }

    {
        const Interval<double> interval = {0.0, 1.0, Interval<double>::Type::Closed};

        const Array<double> array = interval.generateArrayWithSize(5);

        EXPECT_TRUE(array.isNear(Array<double>({0.0, 0.25, 0.5, 0.75, 1.0}), 1e-15));
    }

    {
        const Interval<double> interval = {0.0, 1.0, Interval<double>::Type::Closed};

        const Array<double> array = interval.generateArrayWithSize(2);

        EXPECT_TRUE(array.isNear(Array<double>({0.0, 1.0}), 1e-15));
    }

    // Open

    {
        const Interval<double> interval = {0.0, 1.0, Interval<double>::Type::Open};

        const Array<double> array = interval.generateArrayWithSize(3);

        EXPECT_TRUE(array.isNear(Array<double>({0.25, 0.5, 0.75}), 1e-15));
    }

    {
        const Interval<double> interval = {0.0, 1.0, Interval<double>::Type::Open};

        const Array<double> array = interval.generateArrayWithSize(4);

        EXPECT_TRUE(array.isNear(Array<double>({0.2, 0.4, 0.6, 0.8}), 1e-15));
    }

    // Half-Open Left

    {
        const Interval<double> interval = {0.0, 1.0, Interval<double>::Type::HalfOpenLeft};

        const Array<double> array = interval.generateArrayWithSize(4);

        EXPECT_TRUE(array.isNear(Array<double>({0.25, 0.5, 0.75, 1.0}), 1e-15));
    }

    {
        const Interval<double> interval = {0.0, 1.0, Interval<double>::Type::HalfOpenLeft};

        const Array<double> array = interval.generateArrayWithSize(5);

        EXPECT_TRUE(array.isNear(Array<double>({0.2, 0.4, 0.6, 0.8, 1.0}), 1e-15));
    }

    // Half-Open Right

    {
        const Interval<double> interval = {0.0, 1.0, Interval<double>::Type::HalfOpenRight};

        const Array<double> array = interval.generateArrayWithSize(4);

        EXPECT_TRUE(array.isNear(Array<double>({0.0, 0.25, 0.5, 0.75}), 1e-15));
    }

    {
        const Interval<double> interval = {0.0, 1.0, Interval<double>::Type::HalfOpenRight};

        const Array<double> array = interval.generateArrayWithSize(5);

        EXPECT_TRUE(array.isNear(Array<double>({0.0, 0.2, 0.4, 0.6, 0.8}), 1e-15));
    }

    {
        EXPECT_ANY_THROW(Interval<double>(0.0, 1.0, Interval<double>::Type::Closed).generateArrayWithSize(0));
        EXPECT_ANY_THROW(Interval<double>(0.0, 1.0, Interval<double>::Type::Closed).generateArrayWithSize(1));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, ToString)
{
    using ostk::mathematics::object::Interval;

    {
        EXPECT_EQ("[0.0, 1.0]", Interval<double>(0.0, 1.0, Interval<double>::Type::Closed).toString());
        EXPECT_EQ("]0.0, 1.0[", Interval<double>(0.0, 1.0, Interval<double>::Type::Open).toString());
        EXPECT_EQ("]0.0, 1.0]", Interval<double>(0.0, 1.0, Interval<double>::Type::HalfOpenLeft).toString());
        EXPECT_EQ("[0.0, 1.0[", Interval<double>(0.0, 1.0, Interval<double>::Type::HalfOpenRight).toString());
        EXPECT_EQ("[1.0, 1.0]", Interval<double>(1.0, 1.0, Interval<double>::Type::Closed).toString());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, SetType)
{
    {
        Interval<double> interval(0.0, 1.0, Interval<double>::Type::Closed);

        EXPECT_EQ(Interval<double>::Type::Closed, interval.getType());

        interval.setType(Interval<double>::Type::Open);

        EXPECT_EQ(Interval<double>::Type::Open, interval.getType());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, SetLowerBound)
{
    {
        Interval<double> interval(0.0, 1.0, Interval<double>::Type::Closed);

        EXPECT_EQ(0.0, interval.getLowerBound());

        interval.setLowerBound(1.0);

        EXPECT_EQ(1.0, interval.getLowerBound());
    }

    {
        Interval<double> interval(0.0, 1.0, Interval<double>::Type::Closed);

        EXPECT_EQ(0.0, interval.getLowerBound());

        EXPECT_ANY_THROW(interval.setLowerBound(2.0));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, SetUpperBound)
{
    {
        Interval<double> interval(0.0, 1.0, Interval<double>::Type::Closed);

        EXPECT_EQ(1.0, interval.getUpperBound());

        interval.setUpperBound(2.0);

        EXPECT_EQ(2.0, interval.getUpperBound());
    }

    {
        Interval<double> interval(1.0, 1.0, Interval<double>::Type::Closed);

        EXPECT_EQ(1.0, interval.getUpperBound());

        EXPECT_ANY_THROW(interval.setUpperBound(0.0));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, Closed)
{
    {
        EXPECT_NO_THROW(Interval<double>::Closed(0.0, 1.0));

        EXPECT_EQ(Interval<double>::Type::Closed, Interval<double>::Closed(0.0, 1.0).getType());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, Open)
{
    {
        EXPECT_NO_THROW(Interval<double>::Open(0.0, 1.0));

        EXPECT_EQ(Interval<double>::Type::Open, Interval<double>::Open(0.0, 1.0).getType());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, HalfOpenLeft)
{
    {
        EXPECT_NO_THROW(Interval<double>::HalfOpenLeft(0.0, 1.0));

        EXPECT_EQ(Interval<double>::Type::HalfOpenLeft, Interval<double>::HalfOpenLeft(0.0, 1.0).getType());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, HalfOpenRight)
{
    {
        EXPECT_NO_THROW(Interval<double>::HalfOpenRight(0.0, 1.0));

        EXPECT_EQ(Interval<double>::Type::HalfOpenRight, Interval<double>::HalfOpenRight(0.0, 1.0).getType());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, Clip)
{
    {
        EXPECT_EQ(ctnr::Array<Interval<double>>(), Interval<double>::Clip({}, Interval<double>::Closed(0.0, 1.0)));
    }

    {
        ctnr::Array<Interval<double>> intervals = {
            Interval<double>::Open(1.0, 2.0), Interval<double>::Closed(1.5, 5.0), Interval<double>::Closed(3.0, 4.0)
        };
        ctnr::Array<Interval<double>> clippedArray = {
            Interval<double>::HalfOpenRight(2, 5.0), Interval<double>::Closed(3.0, 4.0)
        };

        EXPECT_EQ(clippedArray, Interval<double>::Clip(intervals, Interval<double>::HalfOpenRight(2.0, 5.0)));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, Sort)
{
    {
        EXPECT_EQ(ctnr::Array<Interval<double>>(), Interval<double>::Sort({}));
    }

    // defaults
    {
        ctnr::Array<Interval<double>> intervals = {
            Interval<double>::Closed(0.0, 1.0), Interval<double>::Closed(2.0, 3.0)
        };
        ctnr::Array<Interval<double>> sortedArray = {
            Interval<double>::Closed(0.0, 1.0), Interval<double>::Closed(2.0, 3.0)
        };

        EXPECT_EQ(sortedArray, Interval<double>::Sort(intervals));
    }

    {
        ctnr::Array<Interval<double>> intervals = {
            Interval<double>::Closed(2.0, 3.0), Interval<double>::Open(0.0, 1.0)
        };
        ctnr::Array<Interval<double>> sortedArray = {
            Interval<double>::Open(0.0, 1.0), Interval<double>::Closed(2.0, 3.0)
        };

        EXPECT_EQ(sortedArray, Interval<double>::Sort(intervals));
    }

    // by upper bound
    {
        ctnr::Array<Interval<double>> intervals = {
            Interval<double>::Closed(0.0, 7.0), Interval<double>::Open(2.0, 3.0)
        };
        ctnr::Array<Interval<double>> sortedArray = {
            Interval<double>::Open(2.0, 3.0), Interval<double>::Closed(0.0, 7.0)
        };

        EXPECT_EQ(sortedArray, Interval<double>::Sort(intervals, false));
    }

    // descending
    {
        ctnr::Array<Interval<double>> intervals = {
            Interval<double>::Closed(2.0, 3.0), Interval<double>::Open(0.0, 1.0)
        };
        ctnr::Array<Interval<double>> sortedArray = {
            Interval<double>::Closed(2.0, 3.0), Interval<double>::Open(0.0, 1.0)
        };

        EXPECT_EQ(sortedArray, Interval<double>::Sort(intervals, true, false));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, Merge)
{
    {
        EXPECT_EQ(ctnr::Array<Interval<double>>(), Interval<double>::Merge({}));
    }

    {
        ctnr::Array<Interval<double>> unmergedArray = {
            Interval<double>::Closed(0.0, 3.0),
            Interval<double>::Open(0.0, 2.0),
            Interval<double>::HalfOpenLeft(4.0, 5.0),
            Interval<double>::Closed(0.5, 1.0),
            Interval<double>::HalfOpenRight(3.0, 3.5)
        };
        ctnr::Array<Interval<double>> mergedArray = {
            Interval<double>::HalfOpenRight(0.0, 3.5), Interval<double>::HalfOpenLeft(4.0, 5.0)
        };

        EXPECT_EQ(mergedArray, Interval<double>::Merge(unmergedArray));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, Gaps)
{
    {
        EXPECT_EQ(ctnr::Array<Interval<double>>(), Interval<double>::GetGaps({}));

        ctnr::Array<Interval<double>> gapsArray = {Interval<double>::Closed(0.0, 1.0)};
        EXPECT_EQ(gapsArray, Interval<double>::GetGaps({}, {Interval<double>::Closed(0.0, 1.0)}));
    }

    {
        ctnr::Array<Interval<double>> intervals = {
            Interval<double>::Closed(2.0, 3.0),
            Interval<double>::Open(0.0, 1.0),
            Interval<double>::HalfOpenLeft(6.0, 7.0),
            Interval<double>::HalfOpenRight(4.0, 5.0),
            Interval<double>::Open(8.0, 9.0)
        };
        ctnr::Array<Interval<double>> gapsArray = {
            Interval<double>::HalfOpenRight(1.0, 2.0),
            Interval<double>::Open(3.0, 4.0),
            Interval<double>::Closed(5.0, 6.0),
            Interval<double>::HalfOpenLeft(7.0, 8.0)
        };

        EXPECT_EQ(gapsArray, Interval<double>::GetGaps(intervals));
    }

    {
        ctnr::Array<Interval<double>> intervals = {
            Interval<double>::Closed(2.0, 3.0),
            Interval<double>::Open(0.0, 1.0),
            Interval<double>::HalfOpenLeft(6.0, 7.0),
            Interval<double>::HalfOpenRight(4.0, 5.0),
            Interval<double>::Open(8.0, 9.0)
        };
        ctnr::Array<Interval<double>> gapsArray = {
            Interval<double>::HalfOpenLeft(-1.0, 0.0),
            Interval<double>::HalfOpenRight(1.0, 2.0),
            Interval<double>::Open(3.0, 4.0),
            Interval<double>::Closed(5.0, 6.0),
            Interval<double>::HalfOpenLeft(7.0, 8.0),
            Interval<double>::Closed(9.0, 10.0),
        };

        EXPECT_EQ(gapsArray, Interval<double>::GetGaps(intervals, Interval<double>::HalfOpenLeft(-1.0, 10.0)));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, LogicalOr)
{
    {
        EXPECT_EQ(ctnr::Array<Interval<double>>(), Interval<double>::LogicalOr({}, {}));

        ctnr::Array<Interval<double>> logicalOrArray = {Interval<double>::Closed(0.0, 1.0)};
        EXPECT_EQ(logicalOrArray, Interval<double>::LogicalOr({}, logicalOrArray));
        EXPECT_EQ(logicalOrArray, Interval<double>::LogicalOr(logicalOrArray, {}));
    }

    {
        ctnr::Array<Interval<double>> anArray = {
            Interval<double>::Closed(2.0, 3.0),
            Interval<double>::Open(0.0, 3.0),
            Interval<double>::HalfOpenLeft(6.0, 7.0),
            Interval<double>::Open(8.0, 9.0),
            Interval<double>::HalfOpenLeft(4.0, 5.0)
        };
        ctnr::Array<Interval<double>> anotherArray = {
            Interval<double>::HalfOpenLeft(10.0, 11.0),
            Interval<double>::HalfOpenRight(-1.0, 2.0),
            Interval<double>::Open(5.0, 7.5)
        };
        ctnr::Array<Interval<double>> logicalOrArray = {
            Interval<double>::Closed(-1.0, 3.0),
            Interval<double>::Open(4.0, 7.5),
            Interval<double>::Open(8.0, 9.0),
            Interval<double>::HalfOpenLeft(10.0, 11.0)
        };

        EXPECT_EQ(logicalOrArray, Interval<double>::LogicalOr(anArray, anotherArray));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, LogicalAnd)
{
    {
        EXPECT_EQ(ctnr::Array<Interval<double>>(), Interval<double>::LogicalAnd({}, {}));
        EXPECT_EQ(
            ctnr::Array<Interval<double>>(), Interval<double>::LogicalAnd({Interval<double>::Closed(0.0, 1.0)}, {})
        );
        EXPECT_EQ(
            ctnr::Array<Interval<double>>(), Interval<double>::LogicalAnd({}, {Interval<double>::Closed(0.0, 1.0)})
        );
    }

    {
        ctnr::Array<Interval<double>> open = {Interval<double>::Open(0.0, 1.0)};
        ctnr::Array<Interval<double>> halfOpenLeft = {Interval<double>::HalfOpenLeft(0.0, 1.0)};
        ctnr::Array<Interval<double>> halfOpenRight = {Interval<double>::HalfOpenRight(0.0, 1.0)};
        ctnr::Array<Interval<double>> closed = {Interval<double>::Closed(0.0, 1.0)};

        EXPECT_EQ(open, Interval<double>::LogicalAnd(open, open));
        EXPECT_EQ(open, Interval<double>::LogicalAnd(open, halfOpenLeft));
        EXPECT_EQ(open, Interval<double>::LogicalAnd(open, halfOpenRight));
        EXPECT_EQ(open, Interval<double>::LogicalAnd(open, closed));

        EXPECT_EQ(open, Interval<double>::LogicalAnd(halfOpenLeft, open));
        EXPECT_EQ(halfOpenLeft, Interval<double>::LogicalAnd(halfOpenLeft, halfOpenLeft));
        EXPECT_EQ(open, Interval<double>::LogicalAnd(halfOpenLeft, halfOpenRight));
        EXPECT_EQ(halfOpenLeft, Interval<double>::LogicalAnd(halfOpenLeft, closed));

        EXPECT_EQ(open, Interval<double>::LogicalAnd(halfOpenRight, open));
        EXPECT_EQ(open, Interval<double>::LogicalAnd(halfOpenRight, halfOpenLeft));
        EXPECT_EQ(halfOpenRight, Interval<double>::LogicalAnd(halfOpenRight, halfOpenRight));
        EXPECT_EQ(halfOpenRight, Interval<double>::LogicalAnd(halfOpenRight, closed));

        EXPECT_EQ(open, Interval<double>::LogicalAnd(closed, open));
        EXPECT_EQ(halfOpenLeft, Interval<double>::LogicalAnd(closed, halfOpenLeft));
        EXPECT_EQ(halfOpenRight, Interval<double>::LogicalAnd(closed, halfOpenRight));
        EXPECT_EQ(closed, Interval<double>::LogicalAnd(closed, closed));
    }

    {
        ctnr::Array<Interval<double>> anArray = {
            Interval<double>::Closed(2.0, 3.0),
            Interval<double>::Open(0.0, 3.0),
            Interval<double>::HalfOpenLeft(6.0, 7.0),
            Interval<double>::Open(8.0, 9.0),
            Interval<double>::HalfOpenLeft(4.0, 5.0)
        };
        ctnr::Array<Interval<double>> anotherArray = {
            Interval<double>::HalfOpenLeft(10.0, 11.0),
            Interval<double>::HalfOpenRight(-1.0, 2.0),
            Interval<double>::Open(5.0, 7.5)
        };
        ctnr::Array<Interval<double>> logicalAndArray = {
            Interval<double>::Open(0.0, 2.0), Interval<double>::HalfOpenLeft(6.0, 7.0)
        };

        EXPECT_EQ(logicalAndArray, Interval<double>::LogicalAnd(anArray, anotherArray));
    }
}

// TEST (OpenSpaceToolkit_Mathematics_Object_Interval, Parse)
// {

//     using ostk::mathematics::object::Interval ;

//     {

//         FAIL() ;

//     }

// }
