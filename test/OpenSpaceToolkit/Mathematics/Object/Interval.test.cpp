/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Tuple.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Interval.hpp>

#include <Global.test.hpp>

using ostk::core::type::Real;
using ostk::mathematics::object::Interval;
namespace ctnr = ostk::core::container;

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, Constructor)
{
    {
        Real lowerBound = 0.0;
        Real upperBound = 1.0;

        EXPECT_NO_THROW(Interval<Real>(lowerBound, upperBound, Interval<Real>::Type::Closed));
        EXPECT_NO_THROW(Interval<Real>(lowerBound, upperBound, Interval<Real>::Type::Open));
        EXPECT_NO_THROW(Interval<Real>(lowerBound, upperBound, Interval<Real>::Type::HalfOpenLeft));
        EXPECT_NO_THROW(Interval<Real>(lowerBound, upperBound, Interval<Real>::Type::HalfOpenRight));
    }

    {
        EXPECT_ANY_THROW(Interval<Real>(1.0, 0.0, Interval<Real>::Type::Closed));
        EXPECT_ANY_THROW(Interval<Real>(1.0, 0.0, Interval<Real>::Type::Open));
        EXPECT_ANY_THROW(Interval<Real>(1.0, 0.0, Interval<Real>::Type::HalfOpenLeft));
        EXPECT_ANY_THROW(Interval<Real>(1.0, 0.0, Interval<Real>::Type::HalfOpenRight));
    }

    {
        EXPECT_NO_THROW(Interval<Real>(0.0, 0.0, Interval<Real>::Type::Closed));
        EXPECT_ANY_THROW(Interval<Real>(0.0, 0.0, Interval<Real>::Type::Open));
        EXPECT_ANY_THROW(Interval<Real>(0.0, 0.0, Interval<Real>::Type::HalfOpenLeft));
        EXPECT_ANY_THROW(Interval<Real>(0.0, 0.0, Interval<Real>::Type::HalfOpenRight));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, EqualToOperator)
{
    {
        EXPECT_TRUE(
            Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed) ==
            Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed)
        );
        EXPECT_TRUE(
            Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open) == Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open)
        );
        EXPECT_TRUE(
            Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft) ==
            Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft)
        );
        EXPECT_TRUE(
            Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight) ==
            Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight)
        );
    }

    {
        EXPECT_FALSE(
            Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed) ==
            Interval<Real>(1.0, 1.0, Interval<Real>::Type::Closed)
        );
        EXPECT_FALSE(
            Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open) == Interval<Real>(0.0, 2.0, Interval<Real>::Type::Open)
        );
        EXPECT_FALSE(
            Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft) ==
            Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed)
        );
        EXPECT_FALSE(Interval<Real>::Undefined() == Interval<Real>::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, NotEqualToOperator)
{
    {
        EXPECT_FALSE(
            Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed) !=
            Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed)
        );
        EXPECT_FALSE(
            Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open) != Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open)
        );
        EXPECT_FALSE(
            Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft) !=
            Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft)
        );
        EXPECT_FALSE(
            Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight) !=
            Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight)
        );
    }

    {
        EXPECT_TRUE(
            Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed) !=
            Interval<Real>(1.0, 1.0, Interval<Real>::Type::Closed)
        );
        EXPECT_TRUE(
            Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open) != Interval<Real>(0.0, 2.0, Interval<Real>::Type::Open)
        );
        EXPECT_TRUE(
            Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft) !=
            Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed)
        );
        EXPECT_TRUE(Interval<Real>::Undefined() != Interval<Real>::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, IsDefined)
{
    {
        EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).isDefined());
        EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).isDefined());
        EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).isDefined());
        EXPECT_TRUE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).isDefined());
    }

    {
        EXPECT_FALSE(Interval<Real>(Real::Undefined(), 1.0, Interval<Real>::Type::Closed).isDefined());
        EXPECT_FALSE(Interval<Real>(0.0, Real::Undefined(), Interval<Real>::Type::Open).isDefined());
        EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Undefined).isDefined());

        EXPECT_FALSE(Interval<Real>::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, IsDegenerate)
{
    {
        EXPECT_TRUE(Interval<Real>(1.0, 1.0, Interval<Real>::Type::Closed).isDegenerate());
    }

    {
        EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).isDegenerate());
        EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).isDegenerate());
        EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).isDegenerate());
        EXPECT_FALSE(Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).isDegenerate());
    }

    {
        EXPECT_ANY_THROW(Interval<Real>::Undefined().isDegenerate());

        EXPECT_ANY_THROW(Interval<Real>(Real::Undefined(), 1.0, Interval<Real>::Type::Closed).isDegenerate());
        EXPECT_ANY_THROW(Interval<Real>(0.0, Real::Undefined(), Interval<Real>::Type::Open).isDegenerate());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, Intersects)
{
    {
        EXPECT_ANY_THROW(Interval<Real>::Undefined().intersects(Interval<Real>::Undefined()));
    }

    {
        const Interval<Real> interval = Interval<Real>::Closed(0.0, 1.0);

        {
            EXPECT_ANY_THROW(interval.intersects(Interval<Real>::Undefined()));
            EXPECT_ANY_THROW(Interval<Real>::Undefined().intersects(interval));
        }

        {
            EXPECT_FALSE(interval.intersects(Interval<Real>::Closed(-2.0, -1.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenLeft(-2.0, -1.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenRight(-2.0, -1.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::Open(-2.0, -1.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<Real>::Closed(-1.0, 0.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenLeft(-1.0, 0.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenRight(-1.0, 0.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::Open(-1.0, 0.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<Real>::Closed(-1.0, 0.5)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenLeft(-1.0, 0.5)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenRight(-1.0, 0.5)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::Open(-1.0, 0.5)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<Real>::Closed(0.25, 0.75)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenLeft(0.25, 0.75)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenRight(0.25, 0.75)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::Open(0.25, 0.75)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<Real>::Closed(0.0, 1.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenLeft(0.0, 1.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenRight(0.0, 1.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::Open(0.0, 1.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<Real>::Closed(-1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenLeft(-1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenRight(-1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::Open(-1.0, 2.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<Real>::Closed(0.5, 1.5)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenLeft(0.5, 1.5)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenRight(0.5, 1.5)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::Open(0.5, 1.5)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<Real>::Closed(1.0, 2.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenLeft(1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenRight(1.0, 2.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::Open(1.0, 2.0)));
        }

        {
            EXPECT_FALSE(interval.intersects(Interval<Real>::Closed(2.0, 3.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenLeft(2.0, 3.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenRight(2.0, 3.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::Open(2.0, 3.0)));
        }
    }

    {
        const Interval<Real> interval = Interval<Real>::HalfOpenLeft(0.0, 1.0);

        {
            EXPECT_ANY_THROW(interval.intersects(Interval<Real>::Undefined()));
            EXPECT_ANY_THROW(Interval<Real>::Undefined().intersects(interval));
        }

        {
            EXPECT_FALSE(interval.intersects(Interval<Real>::Closed(-2.0, -1.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenLeft(-2.0, -1.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenRight(-2.0, -1.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::Open(-2.0, -1.0)));
        }

        {
            EXPECT_FALSE(interval.intersects(Interval<Real>::Closed(-1.0, 0.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenLeft(-1.0, 0.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenRight(-1.0, 0.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::Open(-1.0, 0.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<Real>::Closed(-1.0, 0.5)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenLeft(-1.0, 0.5)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenRight(-1.0, 0.5)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::Open(-1.0, 0.5)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<Real>::Closed(0.25, 0.75)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenLeft(0.25, 0.75)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenRight(0.25, 0.75)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::Open(0.25, 0.75)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<Real>::Closed(0.0, 1.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenLeft(0.0, 1.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenRight(0.0, 1.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::Open(0.0, 1.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<Real>::Closed(-1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenLeft(-1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenRight(-1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::Open(-1.0, 2.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<Real>::Closed(0.5, 1.5)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenLeft(0.5, 1.5)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenRight(0.5, 1.5)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::Open(0.5, 1.5)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<Real>::Closed(1.0, 2.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenLeft(1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenRight(1.0, 2.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::Open(1.0, 2.0)));
        }

        {
            EXPECT_FALSE(interval.intersects(Interval<Real>::Closed(2.0, 3.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenLeft(2.0, 3.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenRight(2.0, 3.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::Open(2.0, 3.0)));
        }
    }

    {
        const Interval<Real> interval = Interval<Real>::HalfOpenRight(0.0, 1.0);

        {
            EXPECT_ANY_THROW(interval.intersects(Interval<Real>::Undefined()));
            EXPECT_ANY_THROW(Interval<Real>::Undefined().intersects(interval));
        }

        {
            EXPECT_FALSE(interval.intersects(Interval<Real>::Closed(-2.0, -1.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenLeft(-2.0, -1.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenRight(-2.0, -1.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::Open(-2.0, -1.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<Real>::Closed(-1.0, 0.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenLeft(-1.0, 0.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenRight(-1.0, 0.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::Open(-1.0, 0.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<Real>::Closed(-1.0, 0.5)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenLeft(-1.0, 0.5)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenRight(-1.0, 0.5)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::Open(-1.0, 0.5)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<Real>::Closed(0.25, 0.75)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenLeft(0.25, 0.75)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenRight(0.25, 0.75)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::Open(0.25, 0.75)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<Real>::Closed(0.0, 1.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenLeft(0.0, 1.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenRight(0.0, 1.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::Open(0.0, 1.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<Real>::Closed(-1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenLeft(-1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenRight(-1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::Open(-1.0, 2.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<Real>::Closed(0.5, 1.5)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenLeft(0.5, 1.5)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenRight(0.5, 1.5)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::Open(0.5, 1.5)));
        }

        {
            EXPECT_FALSE(interval.intersects(Interval<Real>::Closed(1.0, 2.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenLeft(1.0, 2.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenRight(1.0, 2.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::Open(1.0, 2.0)));
        }

        {
            EXPECT_FALSE(interval.intersects(Interval<Real>::Closed(2.0, 3.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenLeft(2.0, 3.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenRight(2.0, 3.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::Open(2.0, 3.0)));
        }
    }

    {
        const Interval<Real> interval = Interval<Real>::Open(0.0, 1.0);

        {
            EXPECT_ANY_THROW(interval.intersects(Interval<Real>::Undefined()));
            EXPECT_ANY_THROW(Interval<Real>::Undefined().intersects(interval));
        }

        {
            EXPECT_FALSE(interval.intersects(Interval<Real>::Closed(-2.0, -1.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenLeft(-2.0, -1.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenRight(-2.0, -1.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::Open(-2.0, -1.0)));
        }

        {
            EXPECT_FALSE(interval.intersects(Interval<Real>::Closed(-1.0, 0.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenLeft(-1.0, 0.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenRight(-1.0, 0.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::Open(-1.0, 0.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<Real>::Closed(-1.0, 0.5)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenLeft(-1.0, 0.5)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenRight(-1.0, 0.5)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::Open(-1.0, 0.5)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<Real>::Closed(0.25, 0.75)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenLeft(0.25, 0.75)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenRight(0.25, 0.75)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::Open(0.25, 0.75)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<Real>::Closed(0.0, 1.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenLeft(0.0, 1.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenRight(0.0, 1.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::Open(0.0, 1.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<Real>::Closed(-1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenLeft(-1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenRight(-1.0, 2.0)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::Open(-1.0, 2.0)));
        }

        {
            EXPECT_TRUE(interval.intersects(Interval<Real>::Closed(0.5, 1.5)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenLeft(0.5, 1.5)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::HalfOpenRight(0.5, 1.5)));
            EXPECT_TRUE(interval.intersects(Interval<Real>::Open(0.5, 1.5)));
        }

        {
            EXPECT_FALSE(interval.intersects(Interval<Real>::Closed(1.0, 2.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenLeft(1.0, 2.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenRight(1.0, 2.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::Open(1.0, 2.0)));
        }

        {
            EXPECT_FALSE(interval.intersects(Interval<Real>::Closed(2.0, 3.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenLeft(2.0, 3.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::HalfOpenRight(2.0, 3.0)));
            EXPECT_FALSE(interval.intersects(Interval<Real>::Open(2.0, 3.0)));
        }
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, ContainsValue)
{
    {
        EXPECT_ANY_THROW(Interval<Real>::Undefined().contains(0.0));
        EXPECT_ANY_THROW(Interval<Real>::Undefined().contains(Real::Undefined()));
    }

    {
        const Interval<Real> interval = Interval<Real>::Closed(0.0, 1.0);

        EXPECT_ANY_THROW(interval.contains(Real::Undefined()));

        EXPECT_FALSE(interval.contains(-1.0));
        EXPECT_TRUE(interval.contains(0.0));
        EXPECT_TRUE(interval.contains(0.5));
        EXPECT_TRUE(interval.contains(1.0));
        EXPECT_FALSE(interval.contains(2.0));
    }

    {
        const Interval<Real> interval = Interval<Real>::HalfOpenLeft(0.0, 1.0);

        EXPECT_ANY_THROW(interval.contains(Real::Undefined()));

        EXPECT_FALSE(interval.contains(-1.0));
        EXPECT_FALSE(interval.contains(0.0));
        EXPECT_TRUE(interval.contains(0.5));
        EXPECT_TRUE(interval.contains(1.0));
        EXPECT_FALSE(interval.contains(2.0));
    }

    {
        const Interval<Real> interval = Interval<Real>::HalfOpenRight(0.0, 1.0);

        EXPECT_ANY_THROW(interval.contains(Real::Undefined()));

        EXPECT_FALSE(interval.contains(-1.0));
        EXPECT_TRUE(interval.contains(0.0));
        EXPECT_TRUE(interval.contains(0.5));
        EXPECT_FALSE(interval.contains(1.0));
        EXPECT_FALSE(interval.contains(2.0));
    }

    {
        const Interval<Real> interval = Interval<Real>::Open(0.0, 1.0);

        EXPECT_ANY_THROW(interval.contains(Real::Undefined()));

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
        EXPECT_ANY_THROW(Interval<Real>::Undefined().contains(Interval<Real>::Undefined()));
    }

    {
        const Interval<Real> interval = Interval<Real>::Closed(0.0, 1.0);

        {
            EXPECT_ANY_THROW(interval.contains(Interval<Real>::Undefined()));
            EXPECT_ANY_THROW(Interval<Real>::Undefined().contains(interval));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(-2.0, -1.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(-2.0, -1.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(-2.0, -1.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(-2.0, -1.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(-1.0, 0.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(-1.0, 0.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(-1.0, 0.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(-1.0, 0.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(-1.0, 0.5)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(-1.0, 0.5)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(-1.0, 0.5)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(-1.0, 0.5)));
        }

        {
            EXPECT_TRUE(interval.contains(Interval<Real>::Closed(0.25, 0.75)));
            EXPECT_TRUE(interval.contains(Interval<Real>::HalfOpenLeft(0.25, 0.75)));
            EXPECT_TRUE(interval.contains(Interval<Real>::HalfOpenRight(0.25, 0.75)));
            EXPECT_TRUE(interval.contains(Interval<Real>::Open(0.25, 0.75)));
        }

        {
            EXPECT_TRUE(interval.contains(Interval<Real>::Closed(0.0, 1.0)));
            EXPECT_TRUE(interval.contains(Interval<Real>::HalfOpenLeft(0.0, 1.0)));
            EXPECT_TRUE(interval.contains(Interval<Real>::HalfOpenRight(0.0, 1.0)));
            EXPECT_TRUE(interval.contains(Interval<Real>::Open(0.0, 1.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(-1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(-1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(-1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(-1.0, 2.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(0.5, 1.5)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(0.5, 1.5)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(0.5, 1.5)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(0.5, 1.5)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(1.0, 2.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(2.0, 3.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(2.0, 3.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(2.0, 3.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(2.0, 3.0)));
        }
    }

    {
        const Interval<Real> interval = Interval<Real>::HalfOpenLeft(0.0, 1.0);

        {
            EXPECT_ANY_THROW(interval.contains(Interval<Real>::Undefined()));
            EXPECT_ANY_THROW(Interval<Real>::Undefined().contains(interval));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(-2.0, -1.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(-2.0, -1.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(-2.0, -1.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(-2.0, -1.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(-1.0, 0.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(-1.0, 0.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(-1.0, 0.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(-1.0, 0.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(-1.0, 0.5)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(-1.0, 0.5)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(-1.0, 0.5)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(-1.0, 0.5)));
        }

        {
            EXPECT_TRUE(interval.contains(Interval<Real>::Closed(0.25, 0.75)));
            EXPECT_TRUE(interval.contains(Interval<Real>::HalfOpenLeft(0.25, 0.75)));
            EXPECT_TRUE(interval.contains(Interval<Real>::HalfOpenRight(0.25, 0.75)));
            EXPECT_TRUE(interval.contains(Interval<Real>::Open(0.25, 0.75)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(0.0, 1.0)));
            EXPECT_TRUE(interval.contains(Interval<Real>::HalfOpenLeft(0.0, 1.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(0.0, 1.0)));
            EXPECT_TRUE(interval.contains(Interval<Real>::Open(0.0, 1.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(-1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(-1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(-1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(-1.0, 2.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(0.5, 1.5)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(0.5, 1.5)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(0.5, 1.5)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(0.5, 1.5)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(1.0, 2.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(2.0, 3.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(2.0, 3.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(2.0, 3.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(2.0, 3.0)));
        }
    }

    {
        const Interval<Real> interval = Interval<Real>::HalfOpenRight(0.0, 1.0);

        {
            EXPECT_ANY_THROW(interval.contains(Interval<Real>::Undefined()));
            EXPECT_ANY_THROW(Interval<Real>::Undefined().contains(interval));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(-2.0, -1.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(-2.0, -1.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(-2.0, -1.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(-2.0, -1.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(-1.0, 0.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(-1.0, 0.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(-1.0, 0.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(-1.0, 0.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(-1.0, 0.5)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(-1.0, 0.5)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(-1.0, 0.5)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(-1.0, 0.5)));
        }

        {
            EXPECT_TRUE(interval.contains(Interval<Real>::Closed(0.25, 0.75)));
            EXPECT_TRUE(interval.contains(Interval<Real>::HalfOpenLeft(0.25, 0.75)));
            EXPECT_TRUE(interval.contains(Interval<Real>::HalfOpenRight(0.25, 0.75)));
            EXPECT_TRUE(interval.contains(Interval<Real>::Open(0.25, 0.75)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(0.0, 1.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(0.0, 1.0)));
            EXPECT_TRUE(interval.contains(Interval<Real>::HalfOpenRight(0.0, 1.0)));
            EXPECT_TRUE(interval.contains(Interval<Real>::Open(0.0, 1.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(-1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(-1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(-1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(-1.0, 2.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(0.5, 1.5)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(0.5, 1.5)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(0.5, 1.5)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(0.5, 1.5)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(1.0, 2.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(2.0, 3.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(2.0, 3.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(2.0, 3.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(2.0, 3.0)));
        }
    }

    {
        const Interval<Real> interval = Interval<Real>::Open(0.0, 1.0);

        {
            EXPECT_ANY_THROW(interval.contains(Interval<Real>::Undefined()));
            EXPECT_ANY_THROW(Interval<Real>::Undefined().contains(interval));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(-2.0, -1.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(-2.0, -1.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(-2.0, -1.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(-2.0, -1.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(-1.0, 0.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(-1.0, 0.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(-1.0, 0.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(-1.0, 0.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(-1.0, 0.5)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(-1.0, 0.5)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(-1.0, 0.5)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(-1.0, 0.5)));
        }

        {
            EXPECT_TRUE(interval.contains(Interval<Real>::Closed(0.25, 0.75)));
            EXPECT_TRUE(interval.contains(Interval<Real>::HalfOpenLeft(0.25, 0.75)));
            EXPECT_TRUE(interval.contains(Interval<Real>::HalfOpenRight(0.25, 0.75)));
            EXPECT_TRUE(interval.contains(Interval<Real>::Open(0.25, 0.75)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(0.0, 1.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(0.0, 1.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(0.0, 1.0)));
            EXPECT_TRUE(interval.contains(Interval<Real>::Open(0.0, 1.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(-1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(-1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(-1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(-1.0, 2.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(0.5, 1.5)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(0.5, 1.5)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(0.5, 1.5)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(0.5, 1.5)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(1.0, 2.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(1.0, 2.0)));
        }

        {
            EXPECT_FALSE(interval.contains(Interval<Real>::Closed(2.0, 3.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenLeft(2.0, 3.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::HalfOpenRight(2.0, 3.0)));
            EXPECT_FALSE(interval.contains(Interval<Real>::Open(2.0, 3.0)));
        }
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, AccessLowerBound)
{
    {
        EXPECT_EQ(0.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).accessLowerBound());
        EXPECT_EQ(0.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).accessLowerBound());
        EXPECT_EQ(0.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).accessLowerBound());
        EXPECT_EQ(0.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).accessLowerBound());
        EXPECT_EQ(1.0, Interval<Real>(1.0, 1.0, Interval<Real>::Type::Closed).accessLowerBound());
    }

    {
        EXPECT_EQ(-1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::Closed).accessLowerBound());
        EXPECT_EQ(-1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::Open).accessLowerBound());
        EXPECT_EQ(-1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::HalfOpenLeft).accessLowerBound());
        EXPECT_EQ(-1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::HalfOpenRight).accessLowerBound());
    }

    {
        Interval<Real> interval(0.0, 1.0, Interval<Real>::Type::Closed);

        EXPECT_EQ(&interval.accessLowerBound(), &interval.accessLowerBound());
    }

    {
        EXPECT_ANY_THROW(Interval<Real>::Undefined().accessLowerBound());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, AccessUpperBound)
{
    {
        EXPECT_EQ(1.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).accessUpperBound());
        EXPECT_EQ(1.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).accessUpperBound());
        EXPECT_EQ(1.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).accessUpperBound());
        EXPECT_EQ(1.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).accessUpperBound());
        EXPECT_EQ(1.0, Interval<Real>(1.0, 1.0, Interval<Real>::Type::Closed).accessUpperBound());
    }

    {
        EXPECT_EQ(+1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::Closed).accessUpperBound());
        EXPECT_EQ(+1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::Open).accessUpperBound());
        EXPECT_EQ(+1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::HalfOpenLeft).accessUpperBound());
        EXPECT_EQ(+1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::HalfOpenRight).accessUpperBound());
    }

    {
        Interval<Real> interval(0.0, 1.0, Interval<Real>::Type::Closed);

        EXPECT_EQ(&interval.accessUpperBound(), &interval.accessUpperBound());
    }

    {
        EXPECT_ANY_THROW(Interval<Real>::Undefined().accessUpperBound());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, GetType)
{
    {
        EXPECT_EQ(Interval<Real>::Type::Closed, Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).getType());
        EXPECT_EQ(Interval<Real>::Type::Open, Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).getType());
        EXPECT_EQ(
            Interval<Real>::Type::HalfOpenLeft, Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).getType()
        );
        EXPECT_EQ(
            Interval<Real>::Type::HalfOpenRight, Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).getType()
        );
    }

    {
        EXPECT_ANY_THROW(Interval<Real>::Undefined().getType());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, GetLowerBound)
{
    {
        EXPECT_EQ(0.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).getLowerBound());
        EXPECT_EQ(0.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).getLowerBound());
        EXPECT_EQ(0.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).getLowerBound());
        EXPECT_EQ(0.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).getLowerBound());
        EXPECT_EQ(1.0, Interval<Real>(1.0, 1.0, Interval<Real>::Type::Closed).getLowerBound());
    }

    {
        EXPECT_EQ(-1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::Closed).getLowerBound());
        EXPECT_EQ(-1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::Open).getLowerBound());
        EXPECT_EQ(-1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::HalfOpenLeft).getLowerBound());
        EXPECT_EQ(-1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::HalfOpenRight).getLowerBound());
    }

    {
        EXPECT_ANY_THROW(Interval<Real>::Undefined().getLowerBound());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, GetUpperBound)
{
    {
        EXPECT_EQ(1.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).getUpperBound());
        EXPECT_EQ(1.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).getUpperBound());
        EXPECT_EQ(1.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).getUpperBound());
        EXPECT_EQ(1.0, Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).getUpperBound());
        EXPECT_EQ(1.0, Interval<Real>(1.0, 1.0, Interval<Real>::Type::Closed).getUpperBound());
    }

    {
        EXPECT_EQ(+1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::Closed).getUpperBound());
        EXPECT_EQ(+1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::Open).getUpperBound());
        EXPECT_EQ(+1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::HalfOpenLeft).getUpperBound());
        EXPECT_EQ(+1.0, Interval<Real>(-1.0, +1.0, Interval<Real>::Type::HalfOpenRight).getUpperBound());
    }

    {
        EXPECT_ANY_THROW(Interval<Real>::Undefined().getUpperBound());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, GetIntersectionWith)
{
    {
        EXPECT_ANY_THROW(Interval<Real>::Undefined().getIntersectionWith(Interval<Real>::Undefined()));
    }

    {
        const Interval<Real> interval = Interval<Real>::Closed(0.0, 1.0);

        {
            EXPECT_ANY_THROW(interval.getIntersectionWith(Interval<Real>::Undefined()));
            EXPECT_ANY_THROW(Interval<Real>::Undefined().getIntersectionWith(interval));
        }

        {
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Closed(-2.0, -1.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(-2.0, -1.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenRight(-2.0, -1.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Open(-2.0, -1.0)).isDefined());
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::Closed(-1.0, 0.0)), Interval<Real>::Closed(0.0, 0.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(-1.0, 0.0)), Interval<Real>::Closed(0.0, 0.0)
            );
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenRight(-1.0, 0.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Open(-1.0, 0.0)).isDefined());
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::Closed(-1.0, 0.5)), Interval<Real>::Closed(0.0, 0.5)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(-1.0, 0.5)), Interval<Real>::Closed(0.0, 0.5)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenRight(-1.0, 0.5)),
                Interval<Real>::HalfOpenRight(0.0, 0.5)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::Open(-1.0, 0.5)), Interval<Real>::HalfOpenRight(0.0, 0.5)
            );
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::Closed(0.25, 0.75)), Interval<Real>::Closed(0.25, 0.75)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(0.25, 0.75)),
                Interval<Real>::HalfOpenLeft(0.25, 0.75)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenRight(0.25, 0.75)),
                Interval<Real>::HalfOpenRight(0.25, 0.75)
            );
            EXPECT_EQ(interval.getIntersectionWith(Interval<Real>::Open(0.25, 0.75)), Interval<Real>::Open(0.25, 0.75));
        }

        {
            EXPECT_EQ(interval.getIntersectionWith(Interval<Real>::Closed(0.0, 1.0)), Interval<Real>::Closed(0.0, 1.0));
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(0.0, 1.0)),
                Interval<Real>::HalfOpenLeft(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenRight(0.0, 1.0)),
                Interval<Real>::HalfOpenRight(0.0, 1.0)
            );
            EXPECT_EQ(interval.getIntersectionWith(Interval<Real>::Open(0.0, 1.0)), Interval<Real>::Open(0.0, 1.0));
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::Closed(-1.0, 2.0)), Interval<Real>::Closed(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(-1.0, 2.0)), Interval<Real>::Closed(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenRight(-1.0, 2.0)), Interval<Real>::Closed(0.0, 1.0)
            );
            EXPECT_EQ(interval.getIntersectionWith(Interval<Real>::Open(-1.0, 2.0)), Interval<Real>::Closed(0.0, 1.0));
        }

        {
            EXPECT_EQ(interval.getIntersectionWith(Interval<Real>::Closed(0.5, 1.5)), Interval<Real>::Closed(0.5, 1.0));
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(0.5, 1.5)),
                Interval<Real>::HalfOpenLeft(0.5, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenRight(0.5, 1.5)), Interval<Real>::Closed(0.5, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::Open(0.5, 1.5)), Interval<Real>::HalfOpenLeft(0.5, 1.0)
            );
        }

        {
            EXPECT_EQ(interval.getIntersectionWith(Interval<Real>::Closed(1.0, 2.0)), Interval<Real>::Closed(1.0, 1.0));
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(1.0, 2.0)).isDefined());
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenRight(1.0, 2.0)), Interval<Real>::Closed(1.0, 1.0)
            );
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Open(1.0, 2.0)).isDefined());
        }

        {
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Closed(2.0, 3.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(2.0, 3.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenRight(2.0, 3.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Open(2.0, 3.0)).isDefined());
        }
    }

    {
        const Interval<Real> interval = Interval<Real>::HalfOpenLeft(0.0, 1.0);

        {
            EXPECT_ANY_THROW(interval.getIntersectionWith(Interval<Real>::Undefined()));
            EXPECT_ANY_THROW(Interval<Real>::Undefined().getIntersectionWith(interval));
        }

        {
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Closed(-2.0, -1.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(-2.0, -1.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenRight(-2.0, -1.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Open(-2.0, -1.0)).isDefined());
        }

        {
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Closed(-1.0, 0.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(-1.0, 0.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenRight(-1.0, 0.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Open(-1.0, 0.0)).isDefined());
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::Closed(-1.0, 0.5)), Interval<Real>::HalfOpenLeft(0.0, 0.5)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(-1.0, 0.5)),
                Interval<Real>::HalfOpenLeft(0.0, 0.5)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenRight(-1.0, 0.5)), Interval<Real>::Open(0.0, 0.5)
            );
            EXPECT_EQ(interval.getIntersectionWith(Interval<Real>::Open(-1.0, 0.5)), Interval<Real>::Open(0.0, 0.5));
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::Closed(0.25, 0.75)), Interval<Real>::Closed(0.25, 0.75)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(0.25, 0.75)),
                Interval<Real>::HalfOpenLeft(0.25, 0.75)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenRight(0.25, 0.75)),
                Interval<Real>::HalfOpenRight(0.25, 0.75)
            );
            EXPECT_EQ(interval.getIntersectionWith(Interval<Real>::Open(0.25, 0.75)), Interval<Real>::Open(0.25, 0.75));
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::Closed(0.0, 1.0)), Interval<Real>::HalfOpenLeft(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(0.0, 1.0)),
                Interval<Real>::HalfOpenLeft(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenRight(0.0, 1.0)), Interval<Real>::Open(0.0, 1.0)
            );
            EXPECT_EQ(interval.getIntersectionWith(Interval<Real>::Open(0.0, 1.0)), Interval<Real>::Open(0.0, 1.0));
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::Closed(-1.0, 2.0)), Interval<Real>::HalfOpenLeft(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(-1.0, 2.0)),
                Interval<Real>::HalfOpenLeft(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenRight(-1.0, 2.0)),
                Interval<Real>::HalfOpenLeft(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::Open(-1.0, 2.0)), Interval<Real>::HalfOpenLeft(0.0, 1.0)
            );
        }

        {
            EXPECT_EQ(interval.getIntersectionWith(Interval<Real>::Closed(0.5, 1.5)), Interval<Real>::Closed(0.5, 1.0));
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(0.5, 1.5)),
                Interval<Real>::HalfOpenLeft(0.5, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenRight(0.5, 1.5)), Interval<Real>::Closed(0.5, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::Open(0.5, 1.5)), Interval<Real>::HalfOpenLeft(0.5, 1.0)
            );
        }

        {
            EXPECT_EQ(interval.getIntersectionWith(Interval<Real>::Closed(1.0, 2.0)), Interval<Real>::Closed(1.0, 1.0));
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(1.0, 2.0)).isDefined());
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenRight(1.0, 2.0)), Interval<Real>::Closed(1.0, 1.0)
            );
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Open(1.0, 2.0)).isDefined());
        }

        {
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Closed(2.0, 3.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(2.0, 3.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenRight(2.0, 3.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Open(2.0, 3.0)).isDefined());
        }
    }

    {
        const Interval<Real> interval = Interval<Real>::HalfOpenRight(0.0, 1.0);

        {
            EXPECT_ANY_THROW(interval.getIntersectionWith(Interval<Real>::Undefined()));
            EXPECT_ANY_THROW(Interval<Real>::Undefined().getIntersectionWith(interval));
        }

        {
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Closed(-2.0, -1.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(-2.0, -1.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenRight(-2.0, -1.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Open(-2.0, -1.0)).isDefined());
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::Closed(-1.0, 0.0)), Interval<Real>::Closed(0.0, 0.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(-1.0, 0.0)), Interval<Real>::Closed(0.0, 0.0)
            );
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenRight(-1.0, 0.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Open(-1.0, 0.0)).isDefined());
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::Closed(-1.0, 0.5)), Interval<Real>::Closed(0.0, 0.5)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(-1.0, 0.5)), Interval<Real>::Closed(0.0, 0.5)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenRight(-1.0, 0.5)),
                Interval<Real>::HalfOpenRight(0.0, 0.5)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::Open(-1.0, 0.5)), Interval<Real>::HalfOpenRight(0.0, 0.5)
            );
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::Closed(0.25, 0.75)), Interval<Real>::Closed(0.25, 0.75)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(0.25, 0.75)),
                Interval<Real>::HalfOpenLeft(0.25, 0.75)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenRight(0.25, 0.75)),
                Interval<Real>::HalfOpenRight(0.25, 0.75)
            );
            EXPECT_EQ(interval.getIntersectionWith(Interval<Real>::Open(0.25, 0.75)), Interval<Real>::Open(0.25, 0.75));
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::Closed(0.0, 1.0)), Interval<Real>::HalfOpenRight(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(0.0, 1.0)), Interval<Real>::Open(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenRight(0.0, 1.0)),
                Interval<Real>::HalfOpenRight(0.0, 1.0)
            );
            EXPECT_EQ(interval.getIntersectionWith(Interval<Real>::Open(0.0, 1.0)), Interval<Real>::Open(0.0, 1.0));
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::Closed(-1.0, 2.0)), Interval<Real>::HalfOpenRight(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(-1.0, 2.0)),
                Interval<Real>::HalfOpenRight(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenRight(-1.0, 2.0)),
                Interval<Real>::HalfOpenRight(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::Open(-1.0, 2.0)), Interval<Real>::HalfOpenRight(0.0, 1.0)
            );
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::Closed(0.5, 1.5)), Interval<Real>::HalfOpenRight(0.5, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(0.5, 1.5)), Interval<Real>::Open(0.5, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenRight(0.5, 1.5)),
                Interval<Real>::HalfOpenRight(0.5, 1.0)
            );
            EXPECT_EQ(interval.getIntersectionWith(Interval<Real>::Open(0.5, 1.5)), Interval<Real>::Open(0.5, 1.0));
        }

        {
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Closed(1.0, 2.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(1.0, 2.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenRight(1.0, 2.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Open(1.0, 2.0)).isDefined());
        }

        {
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Closed(2.0, 3.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(2.0, 3.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenRight(2.0, 3.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Open(2.0, 3.0)).isDefined());
        }
    }

    {
        const Interval<Real> interval = Interval<Real>::Open(0.0, 1.0);

        {
            EXPECT_ANY_THROW(interval.getIntersectionWith(Interval<Real>::Undefined()));
            EXPECT_ANY_THROW(Interval<Real>::Undefined().getIntersectionWith(interval));
        }

        {
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Closed(-2.0, -1.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(-2.0, -1.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenRight(-2.0, -1.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Open(-2.0, -1.0)).isDefined());
        }

        {
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Closed(-1.0, 0.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(-1.0, 0.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenRight(-1.0, 0.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Open(-1.0, 0.0)).isDefined());
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::Closed(-1.0, 0.5)), Interval<Real>::HalfOpenLeft(0.0, 0.5)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(-1.0, 0.5)),
                Interval<Real>::HalfOpenLeft(0.0, 0.5)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenRight(-1.0, 0.5)), Interval<Real>::Open(0.0, 0.5)
            );
            EXPECT_EQ(interval.getIntersectionWith(Interval<Real>::Open(-1.0, 0.5)), Interval<Real>::Open(0.0, 0.5));
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::Closed(0.25, 0.75)), Interval<Real>::Closed(0.25, 0.75)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(0.25, 0.75)),
                Interval<Real>::HalfOpenLeft(0.25, 0.75)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenRight(0.25, 0.75)),
                Interval<Real>::HalfOpenRight(0.25, 0.75)
            );
            EXPECT_EQ(interval.getIntersectionWith(Interval<Real>::Open(0.25, 0.75)), Interval<Real>::Open(0.25, 0.75));
        }

        {
            EXPECT_EQ(interval.getIntersectionWith(Interval<Real>::Closed(0.0, 1.0)), Interval<Real>::Open(0.0, 1.0));
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(0.0, 1.0)), Interval<Real>::Open(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenRight(0.0, 1.0)), Interval<Real>::Open(0.0, 1.0)
            );
            EXPECT_EQ(interval.getIntersectionWith(Interval<Real>::Open(0.0, 1.0)), Interval<Real>::Open(0.0, 1.0));
        }

        {
            EXPECT_EQ(interval.getIntersectionWith(Interval<Real>::Closed(-1.0, 2.0)), Interval<Real>::Open(0.0, 1.0));
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(-1.0, 2.0)), Interval<Real>::Open(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenRight(-1.0, 2.0)), Interval<Real>::Open(0.0, 1.0)
            );
            EXPECT_EQ(interval.getIntersectionWith(Interval<Real>::Open(-1.0, 2.0)), Interval<Real>::Open(0.0, 1.0));
        }

        {
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::Closed(0.5, 1.5)), Interval<Real>::HalfOpenRight(0.5, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(0.5, 1.5)), Interval<Real>::Open(0.5, 1.0)
            );
            EXPECT_EQ(
                interval.getIntersectionWith(Interval<Real>::HalfOpenRight(0.5, 1.5)),
                Interval<Real>::HalfOpenRight(0.5, 1.0)
            );
            EXPECT_EQ(interval.getIntersectionWith(Interval<Real>::Open(0.5, 1.5)), Interval<Real>::Open(0.5, 1.0));
        }

        {
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Closed(1.0, 2.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(1.0, 2.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenRight(1.0, 2.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Open(1.0, 2.0)).isDefined());
        }

        {
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Closed(2.0, 3.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenLeft(2.0, 3.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::HalfOpenRight(2.0, 3.0)).isDefined());
            EXPECT_FALSE(interval.getIntersectionWith(Interval<Real>::Open(2.0, 3.0)).isDefined());
        }
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, GetUnionWith)
{
    {
        EXPECT_ANY_THROW(Interval<Real>::Undefined().getUnionWith(Interval<Real>::Undefined()));
    }

    {
        const Interval<Real> interval = Interval<Real>::Closed(0.0, 1.0);

        {
            EXPECT_ANY_THROW(interval.getUnionWith(Interval<Real>::Undefined()));
            EXPECT_ANY_THROW(Interval<Real>::Undefined().getUnionWith(interval));
        }

        {
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::Closed(-2.0, -1.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::HalfOpenLeft(-2.0, -1.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::HalfOpenRight(-2.0, -1.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::Open(-2.0, -1.0)).isDefined());
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Closed(-1.0, 0.0)), Interval<Real>::Closed(-1.0, 1.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenLeft(-1.0, 0.0)), Interval<Real>::HalfOpenLeft(-1.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenRight(-1.0, 0.0)), Interval<Real>::Closed(-1.0, 1.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Open(-1.0, 0.0)), Interval<Real>::HalfOpenLeft(-1.0, 1.0));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Closed(-1.0, 0.5)), Interval<Real>::Closed(-1.0, 1.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenLeft(-1.0, 0.5)), Interval<Real>::HalfOpenLeft(-1.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenRight(-1.0, 0.5)), Interval<Real>::Closed(-1.0, 1.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Open(-1.0, 0.5)), Interval<Real>::HalfOpenLeft(-1.0, 1.0));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Closed(0.25, 0.75)), Interval<Real>::Closed(0.0, 1.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenLeft(0.25, 0.75)), Interval<Real>::Closed(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenRight(0.25, 0.75)), Interval<Real>::Closed(0.0, 1.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Open(0.25, 0.75)), Interval<Real>::Closed(0.0, 1.0));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Closed(0.0, 1.0)), Interval<Real>::Closed(0.0, 1.0));
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::HalfOpenLeft(0.0, 1.0)), Interval<Real>::Closed(0.0, 1.0));
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::HalfOpenRight(0.0, 1.0)), Interval<Real>::Closed(0.0, 1.0));
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Open(0.0, 1.0)), Interval<Real>::Closed(0.0, 1.0));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Closed(-1.0, 2.0)), Interval<Real>::Closed(-1.0, 2.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenLeft(-1.0, 2.0)), Interval<Real>::HalfOpenLeft(-1.0, 2.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenRight(-1.0, 2.0)),
                Interval<Real>::HalfOpenRight(-1.0, 2.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Open(-1.0, 2.0)), Interval<Real>::Open(-1.0, 2.0));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Closed(0.5, 1.5)), Interval<Real>::Closed(0.0, 1.5));
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::HalfOpenLeft(0.5, 1.5)), Interval<Real>::Closed(0.0, 1.5));
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenRight(0.5, 1.5)), Interval<Real>::HalfOpenRight(0.0, 1.5)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Open(0.5, 1.5)), Interval<Real>::HalfOpenRight(0.0, 1.5));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Closed(1.0, 2.0)), Interval<Real>::Closed(0.0, 2.0));
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::HalfOpenLeft(1.0, 2.0)), Interval<Real>::Closed(0.0, 2.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenRight(1.0, 2.0)), Interval<Real>::HalfOpenRight(0.0, 2.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Open(1.0, 2.0)), Interval<Real>::HalfOpenRight(0.0, 2.0));
        }

        {
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::Closed(2.0, 3.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::HalfOpenLeft(2.0, 3.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::HalfOpenRight(2.0, 3.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::Open(2.0, 3.0)).isDefined());
        }
    }

    {
        const Interval<Real> interval = Interval<Real>::HalfOpenLeft(0.0, 1.0);

        {
            EXPECT_ANY_THROW(interval.getUnionWith(Interval<Real>::Undefined()));
            EXPECT_ANY_THROW(Interval<Real>::Undefined().getUnionWith(interval));
        }

        {
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::Closed(-2.0, -1.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::HalfOpenLeft(-2.0, -1.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::HalfOpenRight(-2.0, -1.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::Open(-2.0, -1.0)).isDefined());
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Closed(-1.0, 0.0)), Interval<Real>::Closed(-1.0, 1.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenLeft(-1.0, 0.0)), Interval<Real>::HalfOpenLeft(-1.0, 1.0)
            );
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::HalfOpenRight(-1.0, 0.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::Open(-1.0, 0.0)).isDefined());
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Closed(-1.0, 0.5)), Interval<Real>::Closed(-1.0, 1.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenLeft(-1.0, 0.5)), Interval<Real>::HalfOpenLeft(-1.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenRight(-1.0, 0.5)), Interval<Real>::Closed(-1.0, 1.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Open(-1.0, 0.5)), Interval<Real>::HalfOpenLeft(-1.0, 1.0));
        }

        {
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::Closed(0.25, 0.75)), Interval<Real>::HalfOpenLeft(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenLeft(0.25, 0.75)), Interval<Real>::HalfOpenLeft(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenRight(0.25, 0.75)), Interval<Real>::HalfOpenLeft(0.0, 1.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Open(0.25, 0.75)), Interval<Real>::HalfOpenLeft(0.0, 1.0));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Closed(0.0, 1.0)), Interval<Real>::Closed(0.0, 1.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenLeft(0.0, 1.0)), Interval<Real>::HalfOpenLeft(0.0, 1.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::HalfOpenRight(0.0, 1.0)), Interval<Real>::Closed(0.0, 1.0));
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Open(0.0, 1.0)), Interval<Real>::HalfOpenLeft(0.0, 1.0));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Closed(-1.0, 2.0)), Interval<Real>::Closed(-1.0, 2.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenLeft(-1.0, 2.0)), Interval<Real>::HalfOpenLeft(-1.0, 2.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenRight(-1.0, 2.0)),
                Interval<Real>::HalfOpenRight(-1.0, 2.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Open(-1.0, 2.0)), Interval<Real>::Open(-1.0, 2.0));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Closed(0.5, 1.5)), Interval<Real>::HalfOpenLeft(0.0, 1.5));
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenLeft(0.5, 1.5)), Interval<Real>::HalfOpenLeft(0.0, 1.5)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::HalfOpenRight(0.5, 1.5)), Interval<Real>::Open(0.0, 1.5));
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Open(0.5, 1.5)), Interval<Real>::Open(0.0, 1.5));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Closed(1.0, 2.0)), Interval<Real>::HalfOpenLeft(0.0, 2.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenLeft(1.0, 2.0)), Interval<Real>::HalfOpenLeft(0.0, 2.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::HalfOpenRight(1.0, 2.0)), Interval<Real>::Open(0.0, 2.0));
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Open(1.0, 2.0)), Interval<Real>::Open(0.0, 2.0));
        }

        {
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::Closed(2.0, 3.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::HalfOpenLeft(2.0, 3.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::HalfOpenRight(2.0, 3.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::Open(2.0, 3.0)).isDefined());
        }
    }

    {
        const Interval<Real> interval = Interval<Real>::HalfOpenRight(0.0, 1.0);

        {
            EXPECT_ANY_THROW(interval.getUnionWith(Interval<Real>::Undefined()));
            EXPECT_ANY_THROW(Interval<Real>::Undefined().getUnionWith(interval));
        }

        {
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::Closed(-2.0, -1.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::HalfOpenLeft(-2.0, -1.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::HalfOpenRight(-2.0, -1.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::Open(-2.0, -1.0)).isDefined());
        }

        {
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::Closed(-1.0, 0.0)), Interval<Real>::HalfOpenRight(-1.0, 1.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::HalfOpenLeft(-1.0, 0.0)), Interval<Real>::Open(-1.0, 1.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenRight(-1.0, 0.0)),
                Interval<Real>::HalfOpenRight(-1.0, 1.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Open(-1.0, 0.0)), Interval<Real>::Open(-1.0, 1.0));
        }

        {
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::Closed(-1.0, 0.5)), Interval<Real>::HalfOpenRight(-1.0, 1.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::HalfOpenLeft(-1.0, 0.5)), Interval<Real>::Open(-1.0, 1.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenRight(-1.0, 0.5)),
                Interval<Real>::HalfOpenRight(-1.0, 1.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Open(-1.0, 0.5)), Interval<Real>::Open(-1.0, 1.0));
        }

        {
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::Closed(0.25, 0.75)), Interval<Real>::HalfOpenRight(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenLeft(0.25, 0.75)), Interval<Real>::HalfOpenRight(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenRight(0.25, 0.75)),
                Interval<Real>::HalfOpenRight(0.0, 1.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Open(0.25, 0.75)), Interval<Real>::HalfOpenRight(0.0, 1.0));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Closed(0.0, 1.0)), Interval<Real>::Closed(0.0, 1.0));
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::HalfOpenLeft(0.0, 1.0)), Interval<Real>::Closed(0.0, 1.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenRight(0.0, 1.0)), Interval<Real>::HalfOpenRight(0.0, 1.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Open(0.0, 1.0)), Interval<Real>::HalfOpenRight(0.0, 1.0));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Closed(-1.0, 2.0)), Interval<Real>::Closed(-1.0, 2.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenLeft(-1.0, 2.0)), Interval<Real>::HalfOpenLeft(-1.0, 2.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenRight(-1.0, 2.0)),
                Interval<Real>::HalfOpenRight(-1.0, 2.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Open(-1.0, 2.0)), Interval<Real>::Open(-1.0, 2.0));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Closed(0.5, 1.5)), Interval<Real>::Closed(0.0, 1.5));
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::HalfOpenLeft(0.5, 1.5)), Interval<Real>::Closed(0.0, 1.5));
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenRight(0.5, 1.5)), Interval<Real>::HalfOpenRight(0.0, 1.5)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Open(0.5, 1.5)), Interval<Real>::HalfOpenRight(0.0, 1.5));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Closed(1.0, 2.0)), Interval<Real>::Closed(0.0, 2.0));
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::HalfOpenLeft(1.0, 2.0)).isDefined());
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenRight(1.0, 2.0)), Interval<Real>::HalfOpenRight(0.0, 2.0)
            );
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::Open(1.0, 2.0)).isDefined());
        }

        {
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::Closed(2.0, 3.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::HalfOpenLeft(2.0, 3.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::HalfOpenRight(2.0, 3.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::Open(2.0, 3.0)).isDefined());
        }
    }

    {
        const Interval<Real> interval = Interval<Real>::Open(0.0, 1.0);

        {
            EXPECT_ANY_THROW(interval.getUnionWith(Interval<Real>::Undefined()));
            EXPECT_ANY_THROW(Interval<Real>::Undefined().getUnionWith(interval));
        }

        {
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::Closed(-2.0, -1.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::HalfOpenLeft(-2.0, -1.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::HalfOpenRight(-2.0, -1.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::Open(-2.0, -1.0)).isDefined());
        }

        {
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::Closed(-1.0, 0.0)), Interval<Real>::HalfOpenRight(-1.0, 1.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::HalfOpenLeft(-1.0, 0.0)), Interval<Real>::Open(-1.0, 1.0));
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::HalfOpenRight(-1.0, 0.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::Open(-1.0, 0.0)).isDefined());
        }

        {
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::Closed(-1.0, 0.5)), Interval<Real>::HalfOpenRight(-1.0, 1.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::HalfOpenLeft(-1.0, 0.5)), Interval<Real>::Open(-1.0, 1.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenRight(-1.0, 0.5)),
                Interval<Real>::HalfOpenRight(-1.0, 1.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Open(-1.0, 0.5)), Interval<Real>::Open(-1.0, 1.0));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Closed(0.25, 0.75)), Interval<Real>::Open(0.0, 1.0));
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::HalfOpenLeft(0.25, 0.75)), Interval<Real>::Open(0.0, 1.0));
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::HalfOpenRight(0.25, 0.75)), Interval<Real>::Open(0.0, 1.0));
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Open(0.25, 0.75)), Interval<Real>::Open(0.0, 1.0));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Closed(0.0, 1.0)), Interval<Real>::Closed(0.0, 1.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenLeft(0.0, 1.0)), Interval<Real>::HalfOpenLeft(0.0, 1.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenRight(0.0, 1.0)), Interval<Real>::HalfOpenRight(0.0, 1.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Open(0.0, 1.0)), Interval<Real>::Open(0.0, 1.0));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Closed(-1.0, 2.0)), Interval<Real>::Closed(-1.0, 2.0));
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenLeft(-1.0, 2.0)), Interval<Real>::HalfOpenLeft(-1.0, 2.0)
            );
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenRight(-1.0, 2.0)),
                Interval<Real>::HalfOpenRight(-1.0, 2.0)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Open(-1.0, 2.0)), Interval<Real>::Open(-1.0, 2.0));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Closed(0.5, 1.5)), Interval<Real>::HalfOpenLeft(0.0, 1.5));
            EXPECT_EQ(
                interval.getUnionWith(Interval<Real>::HalfOpenLeft(0.5, 1.5)), Interval<Real>::HalfOpenLeft(0.0, 1.5)
            );
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::HalfOpenRight(0.5, 1.5)), Interval<Real>::Open(0.0, 1.5));
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Open(0.5, 1.5)), Interval<Real>::Open(0.0, 1.5));
        }

        {
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::Closed(1.0, 2.0)), Interval<Real>::HalfOpenLeft(0.0, 2.0));
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::HalfOpenLeft(1.0, 2.0)).isDefined());
            EXPECT_EQ(interval.getUnionWith(Interval<Real>::HalfOpenRight(1.0, 2.0)), Interval<Real>::Open(0.0, 2.0));
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::Open(1.0, 2.0)).isDefined());
        }

        {
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::Closed(2.0, 3.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::HalfOpenLeft(2.0, 3.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::HalfOpenRight(2.0, 3.0)).isDefined());
            EXPECT_FALSE(interval.getUnionWith(Interval<Real>::Open(2.0, 3.0)).isDefined());
        }
    }
}

// TEST (OpenSpaceToolkit_Mathematics_Object_Interval, GenerateArrayWithStep)
// {

//     using ostk::core::type::Real ;

//     using ostk::mathematics::object::Interval ;

//     {

//         FAIL() ;

//     }

// }

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, GenerateArrayWithSize)
{
    using ostk::core::container::Array;
    using ostk::core::type::Real;
    using ostk::core::type::Size;

    using ostk::mathematics::object::Interval;

    // Closed

    {
        const Interval<Real> interval = {0.0, 1.0, Interval<Real>::Type::Closed};

        const Array<Real> array = interval.generateArrayWithSize(3);

        EXPECT_TRUE(array.isNear(Array<Real>({0.0, 0.5, 1.0}), Real::Epsilon()));
    }

    {
        const Interval<Real> interval = {0.0, 1.0, Interval<Real>::Type::Closed};

        const Array<Real> array = interval.generateArrayWithSize(5);

        EXPECT_TRUE(array.isNear(Array<Real>({0.0, 0.25, 0.5, 0.75, 1.0}), Real::Epsilon()));
    }

    {
        const Interval<Real> interval = {0.0, 1.0, Interval<Real>::Type::Closed};

        const Array<Real> array = interval.generateArrayWithSize(2);

        EXPECT_TRUE(array.isNear(Array<Real>({0.0, 1.0}), Real::Epsilon()));
    }

    // Open

    {
        const Interval<Real> interval = {0.0, 1.0, Interval<Real>::Type::Open};

        const Array<Real> array = interval.generateArrayWithSize(3);

        EXPECT_TRUE(array.isNear(Array<Real>({0.25, 0.5, 0.75}), Real::Epsilon()));
    }

    {
        const Interval<Real> interval = {0.0, 1.0, Interval<Real>::Type::Open};

        const Array<Real> array = interval.generateArrayWithSize(4);

        EXPECT_TRUE(array.isNear(Array<Real>({0.2, 0.4, 0.6, 0.8}), Real::Epsilon()));
    }

    // Half-Open Left

    {
        const Interval<Real> interval = {0.0, 1.0, Interval<Real>::Type::HalfOpenLeft};

        const Array<Real> array = interval.generateArrayWithSize(4);

        EXPECT_TRUE(array.isNear(Array<Real>({0.25, 0.5, 0.75, 1.0}), Real::Epsilon()));
    }

    {
        const Interval<Real> interval = {0.0, 1.0, Interval<Real>::Type::HalfOpenLeft};

        const Array<Real> array = interval.generateArrayWithSize(5);

        EXPECT_TRUE(array.isNear(Array<Real>({0.2, 0.4, 0.6, 0.8, 1.0}), Real::Epsilon()));
    }

    // Half-Open Right

    {
        const Interval<Real> interval = {0.0, 1.0, Interval<Real>::Type::HalfOpenRight};

        const Array<Real> array = interval.generateArrayWithSize(4);

        EXPECT_TRUE(array.isNear(Array<Real>({0.0, 0.25, 0.5, 0.75}), Real::Epsilon()));
    }

    {
        const Interval<Real> interval = {0.0, 1.0, Interval<Real>::Type::HalfOpenRight};

        const Array<Real> array = interval.generateArrayWithSize(5);

        EXPECT_TRUE(array.isNear(Array<Real>({0.0, 0.2, 0.4, 0.6, 0.8}), Real::Epsilon()));
    }

    {
        EXPECT_ANY_THROW(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).generateArrayWithSize(0));
        EXPECT_ANY_THROW(Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).generateArrayWithSize(1));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, ToString)
{
    using ostk::core::type::Real;

    using ostk::mathematics::object::Interval;

    {
        EXPECT_EQ("[0.0, 1.0]", Interval<Real>(0.0, 1.0, Interval<Real>::Type::Closed).toString());
        EXPECT_EQ("]0.0, 1.0[", Interval<Real>(0.0, 1.0, Interval<Real>::Type::Open).toString());
        EXPECT_EQ("]0.0, 1.0]", Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenLeft).toString());
        EXPECT_EQ("[0.0, 1.0[", Interval<Real>(0.0, 1.0, Interval<Real>::Type::HalfOpenRight).toString());
        EXPECT_EQ("[1.0, 1.0]", Interval<Real>(1.0, 1.0, Interval<Real>::Type::Closed).toString());
    }

    {
        EXPECT_ANY_THROW(Interval<Real>::Undefined().toString());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, SetType)
{
    {
        Interval<Real> interval(0.0, 1.0, Interval<Real>::Type::Closed);

        EXPECT_EQ(Interval<Real>::Type::Closed, interval.getType());

        interval.setType(Interval<Real>::Type::Open);

        EXPECT_EQ(Interval<Real>::Type::Open, interval.getType());
    }

    {
        EXPECT_ANY_THROW(Interval<Real>::Undefined().setType(Interval<Real>::Type::Closed));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, SetLowerBound)
{
    {
        Interval<Real> interval(0.0, 1.0, Interval<Real>::Type::Closed);

        EXPECT_EQ(0.0, interval.getLowerBound());

        interval.setLowerBound(1.0);

        EXPECT_EQ(1.0, interval.getLowerBound());
    }

    {
        EXPECT_ANY_THROW(Interval<Real>::Undefined().setLowerBound(1.0));
    }

    {
        Interval<Real> interval(0.0, 1.0, Interval<Real>::Type::Closed);

        EXPECT_EQ(0.0, interval.getLowerBound());

        EXPECT_ANY_THROW(interval.setLowerBound(2.0));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, SetUpperBound)
{
    {
        Interval<Real> interval(0.0, 1.0, Interval<Real>::Type::Closed);

        EXPECT_EQ(1.0, interval.getUpperBound());

        interval.setUpperBound(2.0);

        EXPECT_EQ(2.0, interval.getUpperBound());
    }

    {
        EXPECT_ANY_THROW(Interval<Real>::Undefined().setUpperBound(1.0));
    }

    {
        Interval<Real> interval(1.0, 1.0, Interval<Real>::Type::Closed);

        EXPECT_EQ(1.0, interval.getUpperBound());

        EXPECT_ANY_THROW(interval.setUpperBound(0.0));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, Undefined)
{
    {
        EXPECT_NO_THROW(Interval<Real>::Undefined());

        EXPECT_FALSE(Interval<Real>::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, Closed)
{
    {
        EXPECT_NO_THROW(Interval<Real>::Closed(0.0, 1.0));

        EXPECT_TRUE(Interval<Real>::Closed(0.0, 1.0).isDefined());

        EXPECT_EQ(Interval<Real>::Type::Closed, Interval<Real>::Closed(0.0, 1.0).getType());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, Open)
{
    {
        EXPECT_NO_THROW(Interval<Real>::Open(0.0, 1.0));

        EXPECT_TRUE(Interval<Real>::Open(0.0, 1.0).isDefined());

        EXPECT_EQ(Interval<Real>::Type::Open, Interval<Real>::Open(0.0, 1.0).getType());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, HalfOpenLeft)
{
    {
        EXPECT_NO_THROW(Interval<Real>::HalfOpenLeft(0.0, 1.0));

        EXPECT_TRUE(Interval<Real>::HalfOpenLeft(0.0, 1.0).isDefined());

        EXPECT_EQ(Interval<Real>::Type::HalfOpenLeft, Interval<Real>::HalfOpenLeft(0.0, 1.0).getType());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, HalfOpenRight)
{
    {
        EXPECT_NO_THROW(Interval<Real>::HalfOpenRight(0.0, 1.0));

        EXPECT_TRUE(Interval<Real>::HalfOpenRight(0.0, 1.0).isDefined());

        EXPECT_EQ(Interval<Real>::Type::HalfOpenRight, Interval<Real>::HalfOpenRight(0.0, 1.0).getType());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, Clip)
{
    {
        EXPECT_ANY_THROW(Interval<Real>::Clip({Interval<Real>::Undefined()}, Interval<Real>::Closed(0.0, 1.0)));
        EXPECT_ANY_THROW(Interval<Real>::Clip(
            {Interval<Real>::Closed(0.0, 1.0), Interval<Real>::Closed(0.0, 1.0)}, Interval<Real>::Undefined()
        ));
        EXPECT_ANY_THROW(Interval<Real>::Clip(
            {Interval<Real>::Closed(0.0, 1.0), Interval<Real>::Undefined()}, Interval<Real>::Closed(0.0, 1.0)
        ));

        EXPECT_EQ(ctnr::Array<Interval<Real>>(), Interval<Real>::Clip({}, Interval<Real>::Closed(0.0, 1.0)));
    }

    {
        ctnr::Array<Interval<Real>> intervals = {
            Interval<Real>::Open(1.0, 2.0), Interval<Real>::Closed(1.5, 5.0), Interval<Real>::Closed(3.0, 4.0)
        };
        ctnr::Array<Interval<Real>> clippedArray = {
            Interval<Real>::HalfOpenRight(2, 5.0), Interval<Real>::Closed(3.0, 4.0)
        };

        EXPECT_EQ(clippedArray, Interval<Real>::Clip(intervals, Interval<Real>::HalfOpenRight(2.0, 5.0)));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, Sort)
{
    {
        EXPECT_ANY_THROW(Interval<Real>::Sort({Interval<Real>::Undefined()}));
        EXPECT_ANY_THROW(Interval<Real>::Sort({Interval<Real>::Closed(0.0, 1.0), Interval<Real>::Undefined()}));

        EXPECT_EQ(ctnr::Array<Interval<Real>>(), Interval<Real>::Sort({}));
    }

    // defaults
    {
        ctnr::Array<Interval<Real>> intervals = {Interval<Real>::Closed(0.0, 1.0), Interval<Real>::Closed(2.0, 3.0)};
        ctnr::Array<Interval<Real>> sortedArray = {Interval<Real>::Closed(0.0, 1.0), Interval<Real>::Closed(2.0, 3.0)};

        EXPECT_EQ(sortedArray, Interval<Real>::Sort(intervals));
    }

    {
        ctnr::Array<Interval<Real>> intervals = {Interval<Real>::Closed(2.0, 3.0), Interval<Real>::Open(0.0, 1.0)};
        ctnr::Array<Interval<Real>> sortedArray = {Interval<Real>::Open(0.0, 1.0), Interval<Real>::Closed(2.0, 3.0)};

        EXPECT_EQ(sortedArray, Interval<Real>::Sort(intervals));
    }

    // by upper bound
    {
        ctnr::Array<Interval<Real>> intervals = {Interval<Real>::Closed(0.0, 7.0), Interval<Real>::Open(2.0, 3.0)};
        ctnr::Array<Interval<Real>> sortedArray = {Interval<Real>::Open(2.0, 3.0), Interval<Real>::Closed(0.0, 7.0)};

        EXPECT_EQ(sortedArray, Interval<Real>::Sort(intervals, false));
    }

    // descending
    {
        ctnr::Array<Interval<Real>> intervals = {Interval<Real>::Closed(2.0, 3.0), Interval<Real>::Open(0.0, 1.0)};
        ctnr::Array<Interval<Real>> sortedArray = {Interval<Real>::Closed(2.0, 3.0), Interval<Real>::Open(0.0, 1.0)};

        EXPECT_EQ(sortedArray, Interval<Real>::Sort(intervals, true, false));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, Merge)
{
    {
        EXPECT_ANY_THROW(Interval<Real>::Merge({Interval<Real>::Undefined()}));
        EXPECT_ANY_THROW(Interval<Real>::Merge({Interval<Real>::Closed(0.0, 1.0), Interval<Real>::Undefined()}));

        EXPECT_EQ(ctnr::Array<Interval<Real>>(), Interval<Real>::Merge({}));
    }

    {
        ctnr::Array<Interval<Real>> unmergedArray = {
            Interval<Real>::Closed(0.0, 3.0),
            Interval<Real>::Open(0.0, 2.0),
            Interval<Real>::HalfOpenLeft(4.0, 5.0),
            Interval<Real>::Closed(0.5, 1.0),
            Interval<Real>::HalfOpenRight(3.0, 3.5)
        };
        ctnr::Array<Interval<Real>> mergedArray = {
            Interval<Real>::HalfOpenRight(0.0, 3.5), Interval<Real>::HalfOpenLeft(4.0, 5.0)
        };

        EXPECT_EQ(mergedArray, Interval<Real>::Merge(unmergedArray));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, Gaps)
{
    {
        EXPECT_ANY_THROW(Interval<Real>::GetGaps({Interval<Real>::Undefined()}, Interval<Real>::Closed(0.0, 1.0)));

        EXPECT_EQ(ctnr::Array<Interval<Real>>(), Interval<Real>::GetGaps({}));

        ctnr::Array<Interval<Real>> gapsArray = {Interval<Real>::Closed(0.0, 1.0)};
        EXPECT_EQ(gapsArray, Interval<Real>::GetGaps({}, {Interval<Real>::Closed(0.0, 1.0)}));
    }

    {
        ctnr::Array<Interval<Real>> intervals = {
            Interval<Real>::Closed(2.0, 3.0),
            Interval<Real>::Open(0.0, 1.0),
            Interval<Real>::HalfOpenLeft(6.0, 7.0),
            Interval<Real>::HalfOpenRight(4.0, 5.0),
            Interval<Real>::Open(8.0, 9.0)
        };
        ctnr::Array<Interval<Real>> gapsArray = {
            Interval<Real>::HalfOpenRight(1.0, 2.0),
            Interval<Real>::Open(3.0, 4.0),
            Interval<Real>::Closed(5.0, 6.0),
            Interval<Real>::HalfOpenLeft(7.0, 8.0)
        };

        EXPECT_EQ(gapsArray, Interval<Real>::GetGaps(intervals));
    }

    {
        ctnr::Array<Interval<Real>> intervals = {
            Interval<Real>::Closed(2.0, 3.0),
            Interval<Real>::Open(0.0, 1.0),
            Interval<Real>::HalfOpenLeft(6.0, 7.0),
            Interval<Real>::HalfOpenRight(4.0, 5.0),
            Interval<Real>::Open(8.0, 9.0)
        };
        ctnr::Array<Interval<Real>> gapsArray = {
            Interval<Real>::HalfOpenLeft(-1.0, 0.0),
            Interval<Real>::HalfOpenRight(1.0, 2.0),
            Interval<Real>::Open(3.0, 4.0),
            Interval<Real>::Closed(5.0, 6.0),
            Interval<Real>::HalfOpenLeft(7.0, 8.0),
            Interval<Real>::Closed(9.0, 10.0),
        };

        EXPECT_EQ(gapsArray, Interval<Real>::GetGaps(intervals, Interval<Real>::HalfOpenLeft(-1.0, 10.0)));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, LogicalOr)
{
    {
        EXPECT_ANY_THROW(Interval<Real>::LogicalOr({Interval<Real>::Undefined()}, {}));
        EXPECT_ANY_THROW(Interval<Real>::LogicalOr({}, {Interval<Real>::Undefined()}));

        EXPECT_EQ(ctnr::Array<Interval<Real>>(), Interval<Real>::LogicalOr({}, {}));

        ctnr::Array<Interval<Real>> logicalOrArray = {Interval<Real>::Closed(0.0, 1.0)};
        EXPECT_EQ(logicalOrArray, Interval<Real>::LogicalOr({}, logicalOrArray));
        EXPECT_EQ(logicalOrArray, Interval<Real>::LogicalOr(logicalOrArray, {}));
    }

    {
        ctnr::Array<Interval<Real>> anArray = {
            Interval<Real>::Closed(2.0, 3.0),
            Interval<Real>::Open(0.0, 3.0),
            Interval<Real>::HalfOpenLeft(6.0, 7.0),
            Interval<Real>::Open(8.0, 9.0),
            Interval<Real>::HalfOpenLeft(4.0, 5.0)
        };
        ctnr::Array<Interval<Real>> anotherArray = {
            Interval<Real>::HalfOpenLeft(10.0, 11.0),
            Interval<Real>::HalfOpenRight(-1.0, 2.0),
            Interval<Real>::Open(5.0, 7.5)
        };
        ctnr::Array<Interval<Real>> logicalOrArray = {
            Interval<Real>::Closed(-1.0, 3.0),
            Interval<Real>::Open(4.0, 7.5),
            Interval<Real>::Open(8.0, 9.0),
            Interval<Real>::HalfOpenLeft(10.0, 11.0)
        };

        EXPECT_EQ(logicalOrArray, Interval<Real>::LogicalOr(anArray, anotherArray));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Object_Interval, LogicalAnd)
{
    {
        EXPECT_ANY_THROW(Interval<Real>::LogicalAnd({Interval<Real>::Undefined()}, {}));
        EXPECT_ANY_THROW(Interval<Real>::LogicalAnd({}, {Interval<Real>::Undefined()}));

        EXPECT_EQ(ctnr::Array<Interval<Real>>(), Interval<Real>::LogicalAnd({}, {}));
        EXPECT_EQ(ctnr::Array<Interval<Real>>(), Interval<Real>::LogicalAnd({Interval<Real>::Closed(0.0, 1.0)}, {}));
        EXPECT_EQ(ctnr::Array<Interval<Real>>(), Interval<Real>::LogicalAnd({}, {Interval<Real>::Closed(0.0, 1.0)}));
    }

    {
        ctnr::Array<Interval<Real>> open = {Interval<Real>::Open(0.0, 1.0)};
        ctnr::Array<Interval<Real>> halfOpenLeft = {Interval<Real>::HalfOpenLeft(0.0, 1.0)};
        ctnr::Array<Interval<Real>> halfOpenRight = {Interval<Real>::HalfOpenRight(0.0, 1.0)};
        ctnr::Array<Interval<Real>> closed = {Interval<Real>::Closed(0.0, 1.0)};

        EXPECT_EQ(open, Interval<Real>::LogicalAnd(open, open));
        EXPECT_EQ(open, Interval<Real>::LogicalAnd(open, halfOpenLeft));
        EXPECT_EQ(open, Interval<Real>::LogicalAnd(open, halfOpenRight));
        EXPECT_EQ(open, Interval<Real>::LogicalAnd(open, closed));

        EXPECT_EQ(open, Interval<Real>::LogicalAnd(halfOpenLeft, open));
        EXPECT_EQ(halfOpenLeft, Interval<Real>::LogicalAnd(halfOpenLeft, halfOpenLeft));
        EXPECT_EQ(open, Interval<Real>::LogicalAnd(halfOpenLeft, halfOpenRight));
        EXPECT_EQ(halfOpenLeft, Interval<Real>::LogicalAnd(halfOpenLeft, closed));

        EXPECT_EQ(open, Interval<Real>::LogicalAnd(halfOpenRight, open));
        EXPECT_EQ(open, Interval<Real>::LogicalAnd(halfOpenRight, halfOpenLeft));
        EXPECT_EQ(halfOpenRight, Interval<Real>::LogicalAnd(halfOpenRight, halfOpenRight));
        EXPECT_EQ(halfOpenRight, Interval<Real>::LogicalAnd(halfOpenRight, closed));

        EXPECT_EQ(open, Interval<Real>::LogicalAnd(closed, open));
        EXPECT_EQ(halfOpenLeft, Interval<Real>::LogicalAnd(closed, halfOpenLeft));
        EXPECT_EQ(halfOpenRight, Interval<Real>::LogicalAnd(closed, halfOpenRight));
        EXPECT_EQ(closed, Interval<Real>::LogicalAnd(closed, closed));
    }

    {
        ctnr::Array<Interval<Real>> anArray = {
            Interval<Real>::Closed(2.0, 3.0),
            Interval<Real>::Open(0.0, 3.0),
            Interval<Real>::HalfOpenLeft(6.0, 7.0),
            Interval<Real>::Open(8.0, 9.0),
            Interval<Real>::HalfOpenLeft(4.0, 5.0)
        };
        ctnr::Array<Interval<Real>> anotherArray = {
            Interval<Real>::HalfOpenLeft(10.0, 11.0),
            Interval<Real>::HalfOpenRight(-1.0, 2.0),
            Interval<Real>::Open(5.0, 7.5)
        };
        ctnr::Array<Interval<Real>> logicalAndArray = {
            Interval<Real>::Open(0.0, 2.0), Interval<Real>::HalfOpenLeft(6.0, 7.0)
        };

        EXPECT_EQ(logicalAndArray, Interval<Real>::LogicalAnd(anArray, anotherArray));
    }
}

// TEST (OpenSpaceToolkit_Mathematics_Object_Interval, Parse)
// {

//     using ostk::core::type::Real ;

//     using ostk::mathematics::object::Interval ;

//     {

//         FAIL() ;

//     }

// }
