/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/PointSet.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Transformation.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Segment, Constructor)
{
    using ostk::math::geometry::d2::objects::Segment;

    {
        EXPECT_NO_THROW(Segment({0.0, 0.0}, {0.0, 1.0}));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Segment, Clone)
{
    using ostk::math::geometry::d2::objects::Segment;

    {
        EXPECT_NO_THROW(const Segment* segmentPtr = Segment({0.0, 0.0}, {0.0, 1.0}).clone(); delete segmentPtr;);
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Segment, EqualToOperator)
{
    using ostk::math::geometry::d2::objects::Segment;

    {
        EXPECT_TRUE(Segment({0.0, 0.0}, {0.0, 1.0}) == Segment({0.0, 0.0}, {0.0, 1.0}));
        EXPECT_TRUE(Segment({0.0, 0.0}, {0.0, 1.0}) == Segment({0.0, 1.0}, {0.0, 0.0}));
    }

    {
        EXPECT_FALSE(Segment({0.0, 0.0}, {0.0, 1.0}) == Segment({0.0, 0.0}, {0.0, 2.0}));
    }

    {
        EXPECT_FALSE(Segment({0.0, 0.0}, {0.0, 1.0}) == Segment::Undefined());
        EXPECT_FALSE(Segment::Undefined() == Segment({0.0, 0.0}, {0.0, 1.0}));
        EXPECT_FALSE(Segment::Undefined() == Segment::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Segment, NotEqualToOperator)
{
    using ostk::math::geometry::d2::objects::Segment;

    {
        EXPECT_FALSE(Segment({0.0, 0.0}, {0.0, 1.0}) != Segment({0.0, 0.0}, {0.0, 1.0}));
        EXPECT_FALSE(Segment({0.0, 0.0}, {0.0, 1.0}) != Segment({0.0, 1.0}, {0.0, 0.0}));
    }

    {
        EXPECT_TRUE(Segment({0.0, 0.0}, {0.0, 1.0}) != Segment({0.0, 0.0}, {0.0, 2.0}));
    }

    {
        EXPECT_TRUE(Segment({0.0, 0.0}, {0.0, 1.0}) != Segment::Undefined());
        EXPECT_TRUE(Segment::Undefined() != Segment({0.0, 0.0}, {0.0, 1.0}));
        EXPECT_TRUE(Segment::Undefined() != Segment::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Segment, StreamOperator)
{
    using ostk::math::geometry::d2::objects::Segment;

    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << Segment({0.0, 0.0}, {0.0, 1.0}) << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Segment, IsDefined)
{
    using ostk::math::geometry::d2::objects::Segment;

    {
        EXPECT_TRUE(Segment({0.0, 0.0}, {0.0, 0.0}).isDefined());
        EXPECT_TRUE(Segment({0.0, 0.0}, {0.0, 1.0}).isDefined());
    }

    {
        EXPECT_FALSE(Segment::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Segment, IsDegenerate)
{
    using ostk::math::geometry::d2::objects::Segment;

    {
        EXPECT_TRUE(Segment({0.0, 0.0}, {0.0, 0.0}).isDegenerate());
        EXPECT_TRUE(Segment({1.0, 1.0}, {1.0, 1.0}).isDegenerate());
    }

    {
        EXPECT_FALSE(Segment({0.0, 0.0}, {0.0, 1.0}).isDegenerate());
        EXPECT_FALSE(Segment({1.0, 2.0}, {0.0, 1.0}).isDegenerate());
    }

    {
        EXPECT_ANY_THROW(Segment::Undefined().isDegenerate());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Segment, Contains_Point)
{
    using ostk::math::geometry::d2::objects::Point;
    using ostk::math::geometry::d2::objects::Segment;

    {
        EXPECT_TRUE(Segment({0.0, 0.0}, {0.0, 0.0}).contains(Point(0.0, 0.0)));
        EXPECT_TRUE(Segment({0.0, 0.0}, {0.0, 1.0}).contains(Point(0.0, 0.0)));
        EXPECT_TRUE(Segment({0.0, 0.0}, {0.0, 1.0}).contains(Point(0.0, 1.0)));
        EXPECT_TRUE(Segment({0.0, 0.0}, {0.0, 1.0}).contains(Point(0.0, 0.5)));
    }

    {
        EXPECT_FALSE(Segment({0.0, 0.0}, {0.0, 0.0}).contains(Point(0.0, 0.1)));
        EXPECT_FALSE(Segment({0.0, 0.0}, {0.0, 1.0}).contains(Point(0.0, 2.0)));
        EXPECT_FALSE(Segment({0.0, 0.0}, {0.0, 1.0}).contains(Point(0.0, -1.0)));
        EXPECT_FALSE(Segment({0.0, 0.0}, {0.0, 1.0}).contains(Point(1.0, 0.0)));
    }

    {
        EXPECT_ANY_THROW(Segment::Undefined().contains(Point::Undefined()));
        EXPECT_ANY_THROW(Segment({0.0, 0.0}, {0.0, 0.0}).contains(Point::Undefined()));
        EXPECT_ANY_THROW(Segment::Undefined().contains(Point(0.0, 0.0)));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Segment, GetCenter)
{
    using ostk::math::geometry::d2::objects::Point;
    using ostk::math::geometry::d2::objects::Segment;

    {
        EXPECT_EQ(Point(0.0, 0.0), Segment({0.0, 0.0}, {0.0, 0.0}).getCenter());
        EXPECT_EQ(Point(0.0, 1.0), Segment({0.0, 0.0}, {0.0, 2.0}).getCenter());

        EXPECT_EQ(Point(0.0, 0.0), Segment({0.0, -1.0}, {0.0, +1.0}).getCenter());
    }

    {
        EXPECT_ANY_THROW(Segment::Undefined().getCenter());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Segment, GetDirection)
{
    using ostk::math::object::Vector2d;
    using ostk::math::geometry::d2::objects::Point;
    using ostk::math::geometry::d2::objects::Segment;

    {
        EXPECT_EQ(Vector2d(0.0, +1.0), Segment({0.0, 0.0}, {0.0, +2.0}).getDirection());
        EXPECT_EQ(Vector2d(0.0, -1.0), Segment({0.0, 0.0}, {0.0, -2.0}).getDirection());
    }

    {
        EXPECT_ANY_THROW(Segment::Undefined().getDirection());

        EXPECT_ANY_THROW(Segment({0.0, 0.0}, {0.0, 0.0}).getDirection());
        EXPECT_ANY_THROW(Segment({1.0, 1.0}, {1.0, 1.0}).getDirection());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Segment, GetLength)
{
    using ostk::math::geometry::d2::objects::Point;
    using ostk::math::geometry::d2::objects::Segment;

    {
        EXPECT_EQ(0.0, Segment({0.0, 0.0}, {0.0, 0.0}).getLength());
        EXPECT_EQ(0.0, Segment({1.0, 1.0}, {1.0, 1.0}).getLength());

        EXPECT_EQ(1.0, Segment({0.0, 0.0}, {0.0, 1.0}).getLength());
        EXPECT_EQ(2.0, Segment({0.0, 0.0}, {0.0, 2.0}).getLength());

        EXPECT_EQ(4.0, Segment({0.0, -2.0}, {0.0, +2.0}).getLength());
    }

    {
        EXPECT_ANY_THROW(Segment::Undefined().getLength());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Segment, DistanceToPoint)
{
    using ostk::math::geometry::d2::objects::Point;
    using ostk::math::geometry::d2::objects::Segment;

    {
        EXPECT_EQ(0.0, Segment({0.0, 0.0}, {0.0, +1.0}).distanceTo(Point({0.0, 0.0})));
        EXPECT_EQ(0.0, Segment({0.0, 0.0}, {0.0, +2.0}).distanceTo(Point({0.0, 0.0})));
        EXPECT_EQ(0.0, Segment({0.0, 0.0}, {0.0, -1.0}).distanceTo(Point({0.0, 0.0})));
        EXPECT_EQ(0.0, Segment({0.0, 0.0}, {0.0, -2.0}).distanceTo(Point({0.0, 0.0})));

        EXPECT_EQ(0.0, Segment({0.0, 0.0}, {0.0, +1.0}).distanceTo(Point({0.0, 1.0})));
        EXPECT_EQ(0.0, Segment({0.0, 0.0}, {0.0, +2.0}).distanceTo(Point({0.0, 1.0})));

        EXPECT_EQ(0.0, Segment({0.0, 0.0}, {0.0, +2.0}).distanceTo(Point({0.0, 2.0})));

        EXPECT_EQ(1.0, Segment({0.0, 0.0}, {0.0, +1.0}).distanceTo(Point({+0.0, +2.0})));
        EXPECT_EQ(1.0, Segment({0.0, 0.0}, {0.0, +1.0}).distanceTo(Point({+1.0, +1.0})));
        EXPECT_EQ(1.0, Segment({0.0, 0.0}, {0.0, +1.0}).distanceTo(Point({-1.0, +1.0})));

        EXPECT_EQ(1.0, Segment({0.0, 0.0}, {0.0, +1.0}).distanceTo(Point({+0.0, -1.0})));
        EXPECT_EQ(1.0, Segment({0.0, 0.0}, {0.0, +1.0}).distanceTo(Point({+1.0, +0.0})));
        EXPECT_EQ(1.0, Segment({0.0, 0.0}, {0.0, +1.0}).distanceTo(Point({-1.0, +0.0})));

        EXPECT_EQ(2.0, Segment({0.0, 0.0}, {0.0, +1.0}).distanceTo(Point({+0.0, +3.0})));
        EXPECT_EQ(2.0, Segment({0.0, 0.0}, {0.0, +1.0}).distanceTo(Point({+0.0, -2.0})));

        EXPECT_NEAR(1.41421, Segment({0.0, 0.0}, {0.0, +1.0}).distanceTo(Point({+1.0, +2.0})), 1e-5);
        EXPECT_NEAR(1.41421, Segment({0.0, 0.0}, {0.0, +1.0}).distanceTo(Point({-1.0, +2.0})), 1e-5);
        EXPECT_NEAR(1.41421, Segment({0.0, 0.0}, {0.0, +1.0}).distanceTo(Point({+1.0, -1.0})), 1e-5);
        EXPECT_NEAR(1.41421, Segment({0.0, 0.0}, {0.0, +1.0}).distanceTo(Point({-1.0, -1.0})), 1e-5);
    }

    {
        EXPECT_EQ(0.0, Segment({0.0, 0.0}, {0.0, 0.0}).distanceTo(Point({0.0, 0.0})));

        EXPECT_EQ(0.0, Segment({+1.0, 0.0}, {+1.0, 0.0}).distanceTo(Point({+1.0, 0.0})));
        EXPECT_EQ(0.0, Segment({0.0, +1.0}, {0.0, +1.0}).distanceTo(Point({0.0, +1.0})));

        EXPECT_EQ(0.0, Segment({-1.0, 0.0}, {-1.0, 0.0}).distanceTo(Point({-1.0, 0.0})));
        EXPECT_EQ(0.0, Segment({0.0, -1.0}, {0.0, -1.0}).distanceTo(Point({0.0, -1.0})));
    }

    {
        EXPECT_ANY_THROW(Segment::Undefined().distanceTo(Point({0.0, 0.0})));
        EXPECT_ANY_THROW(Segment({0.0, 0.0}, {0.0, 1.0}).distanceTo(Point::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Segment, DistanceToPointSet)
{
    using ostk::math::geometry::d2::objects::Point;
    using ostk::math::geometry::d2::objects::PointSet;
    using ostk::math::geometry::d2::objects::Segment;

    {
        EXPECT_EQ(0.0, Segment({0.0, 0.0}, {0.0, +1.0}).distanceTo(PointSet({{0.0, 0.0}, {0.0, 10.0}})));
        EXPECT_EQ(0.0, Segment({0.0, 0.0}, {0.0, +1.0}).distanceTo(PointSet({{0.0, 10.0}, {0.0, 0.0}})));

        EXPECT_EQ(1.0, Segment({0.0, 0.0}, {0.0, +1.0}).distanceTo(PointSet({{0.0, 3.0}, {0.0, 2.0}, {10.0, 0.0}})));
    }

    {
        EXPECT_ANY_THROW(Segment::Undefined().distanceTo(PointSet({{0.0, 0.0}, {1.0, 0.0}})));
        EXPECT_ANY_THROW(Segment({0.0, 0.0}, {0.0, 1.0}).distanceTo(PointSet::Empty()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Segment, ToLine)
{
    using ostk::math::geometry::d2::objects::Line;
    using ostk::math::geometry::d2::objects::Segment;

    {
        EXPECT_EQ(Line({0.0, 0.0}, {0.0, 1.0}), Segment({0.0, 0.0}, {0.0, 1.0}).toLine());
        EXPECT_EQ(Line({0.0, 0.0}, {0.0, 1.0}), Segment({0.0, 0.0}, {0.0, 2.0}).toLine());
    }

    {
        EXPECT_ANY_THROW(Segment({0.0, 0.0}, {0.0, 0.0}).toLine());
        EXPECT_ANY_THROW(Segment({1.0, 1.0}, {1.0, 1.0}).toLine());
    }

    {
        EXPECT_ANY_THROW(Segment::Undefined().toLine());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Segment, ApplyTransformation)
{
    using ostk::core::type::Real;

    using ostk::math::object::Vector2d;
    using ostk::math::geometry::d2::objects::Segment;
    using ostk::math::geometry::d2::Transformation;

    // Translation

    {
        Segment segment = {{0.0, 0.0}, {0.0, 1.0}};

        segment.applyTransformation(Transformation::Translation({4.0, 5.0}));

        EXPECT_EQ(Segment({4.0, 5.0}, {4.0, 6.0}), segment);
    }

    {
        EXPECT_ANY_THROW(Segment::Undefined().applyTransformation(Transformation::Undefined()));
        EXPECT_ANY_THROW(Segment::Undefined().applyTransformation(Transformation::Identity()));
        EXPECT_ANY_THROW(Segment({0.0, 0.0}, {0.0, 1.0}).applyTransformation(Transformation::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Segment, Undefined)
{
    using ostk::math::geometry::d2::objects::Segment;

    {
        EXPECT_NO_THROW(Segment::Undefined());
        EXPECT_FALSE(Segment::Undefined().isDefined());
    }
}
