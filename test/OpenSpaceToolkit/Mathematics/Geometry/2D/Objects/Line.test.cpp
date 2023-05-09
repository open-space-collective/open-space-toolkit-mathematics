// Copyright © Loft Orbital Solutions Inc.

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Line.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/PointSet.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Transformation.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Line, Constructor)
{
    using ostk::math::geom::d2::objects::Line;

    {
        EXPECT_NO_THROW(Line({0.0, 0.0}, {0.0, 1.0}));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Line, Clone)
{
    using ostk::math::geom::d2::objects::Line;

    {
        EXPECT_NO_THROW(const Line* linePtr = Line({0.0, 0.0}, {0.0, 1.0}).clone(); delete linePtr;);
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Line, EqualToOperator)
{
    using ostk::math::geom::d2::objects::Line;

    {
        EXPECT_TRUE(Line({0.0, 0.0}, {0.0, 1.0}) == Line({0.0, 0.0}, {0.0, +1.0}));
        EXPECT_TRUE(Line({0.0, 0.0}, {0.0, 1.0}) == Line({0.0, 0.0}, {0.0, -1.0}));

        EXPECT_TRUE(Line({0.0, 0.0}, {0.0, 1.0}) == Line({0.0, 0.0}, {0.0, +2.0}));
        EXPECT_TRUE(Line({0.0, 0.0}, {0.0, 1.0}) == Line({0.0, 0.0}, {0.0, -2.0}));

        EXPECT_TRUE(Line({0.0, 1.0}, {0.0, 1.0}) == Line({0.0, 1.0}, {0.0, +1.0}));
        EXPECT_TRUE(Line({0.0, 1.0}, {0.0, 1.0}) == Line({0.0, 1.0}, {0.0, -1.0}));
    }

    {
        EXPECT_FALSE(Line({0.0, 0.0}, {0.0, 1.0}) == Line({1.0, 0.0}, {0.0, 1.0}));
    }

    {
        EXPECT_FALSE(Line({0.0, 0.0}, {0.0, 1.0}) == Line::Undefined());
        EXPECT_FALSE(Line::Undefined() == Line({0.0, 0.0}, {0.0, 1.0}));
        EXPECT_FALSE(Line::Undefined() == Line::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Line, NotEqualToOperator)
{
    using ostk::math::geom::d2::objects::Line;

    {
        EXPECT_FALSE(Line({0.0, 0.0}, {0.0, 1.0}) != Line({0.0, 0.0}, {0.0, +1.0}));
        EXPECT_FALSE(Line({0.0, 0.0}, {0.0, 1.0}) != Line({0.0, 0.0}, {0.0, -1.0}));

        EXPECT_FALSE(Line({0.0, 0.0}, {0.0, 1.0}) != Line({0.0, 0.0}, {0.0, +2.0}));
        EXPECT_FALSE(Line({0.0, 0.0}, {0.0, 1.0}) != Line({0.0, 0.0}, {0.0, -2.0}));

        EXPECT_FALSE(Line({0.0, 1.0}, {0.0, 1.0}) != Line({0.0, 1.0}, {0.0, +1.0}));
        EXPECT_FALSE(Line({0.0, 1.0}, {0.0, 1.0}) != Line({0.0, 1.0}, {0.0, -1.0}));
    }

    {
        EXPECT_TRUE(Line({0.0, 0.0}, {0.0, 1.0}) != Line({1.0, 0.0}, {0.0, 1.0}));
    }

    {
        EXPECT_TRUE(Line({0.0, 0.0}, {0.0, 1.0}) != Line::Undefined());
        EXPECT_TRUE(Line::Undefined() != Line({0.0, 0.0}, {0.0, 1.0}));
        EXPECT_TRUE(Line::Undefined() != Line::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Line, StreamOperator)
{
    using ostk::math::geom::d2::objects::Line;

    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << Line({0.0, 0.0}, {0.0, 1.0}) << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Line, IsDefined)
{
    using ostk::math::geom::d2::objects::Line;

    {
        EXPECT_TRUE(Line({0.0, 0.0}, {0.0, 1.0}).isDefined());
    }

    {
        EXPECT_FALSE(Line::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Line, Intersects_Point)
{
    using ostk::math::geom::d2::objects::Point;
    using ostk::math::geom::d2::objects::Line;

    {
        EXPECT_TRUE(Line({0.0, 0.0}, {0.0, 1.0}).intersects(Point(0.0, 0.0)));

        EXPECT_TRUE(Line({0.0, 0.0}, {0.0, 1.0}).intersects(Point(0.0, -1.0)));
        EXPECT_TRUE(Line({0.0, 0.0}, {0.0, 1.0}).intersects(Point(0.0, +1.0)));

        EXPECT_TRUE(Line({1.0, 0.0}, {0.0, 1.0}).intersects(Point(1.0, 0.0)));

        EXPECT_TRUE(Line({1.0, 0.0}, {0.0, 1.0}).intersects(Point(1.0, -1.0)));
        EXPECT_TRUE(Line({1.0, 0.0}, {0.0, 1.0}).intersects(Point(1.0, +1.0)));
    }

    {
        EXPECT_FALSE(Line({0.0, 0.0}, {0.0, 1.0}).intersects(Point(1.0, 0.0)));
        EXPECT_FALSE(Line({0.0, 0.0}, {0.0, 1.0}).intersects(Point(1.0, 0.0)));
    }

    {
        EXPECT_ANY_THROW(Line::Undefined().intersects(Point::Undefined()));
        EXPECT_ANY_THROW(Line({0.0, 0.0}, {0.0, 1.0}).intersects(Point::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Line, Contains_Point)
{
    using ostk::math::geom::d2::objects::Point;
    using ostk::math::geom::d2::objects::Line;

    {
        EXPECT_TRUE(Line({0.0, 0.0}, {0.0, 1.0}).contains(Point(0.0, -2.0)));
        EXPECT_TRUE(Line({0.0, 0.0}, {0.0, 1.0}).contains(Point(0.0, -1.0)));
        EXPECT_TRUE(Line({0.0, 0.0}, {0.0, 1.0}).contains(Point(0.0, -0.5)));
        EXPECT_TRUE(Line({0.0, 0.0}, {0.0, 1.0}).contains(Point(0.0, +0.0)));
        EXPECT_TRUE(Line({0.0, 0.0}, {0.0, 1.0}).contains(Point(0.0, +0.5)));
        EXPECT_TRUE(Line({0.0, 0.0}, {0.0, 1.0}).contains(Point(0.0, +1.0)));
        EXPECT_TRUE(Line({0.0, 0.0}, {0.0, 1.0}).contains(Point(0.0, +2.0)));
    }

    {
        EXPECT_FALSE(Line({0.0, 0.0}, {0.0, 1.0}).contains(Point(1.0, 0.0)));
    }

    {
        EXPECT_ANY_THROW(Line::Undefined().contains(Point::Undefined()));
        EXPECT_ANY_THROW(Line({0.0, 0.0}, {0.0, 1.0}).contains(Point::Undefined()));
        EXPECT_ANY_THROW(Line::Undefined().contains(Point(0.0, 0.0)));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Line, Contains_PointSet)
{
    using ostk::math::geom::d2::objects::Point;
    using ostk::math::geom::d2::objects::PointSet;
    using ostk::math::geom::d2::objects::Line;

    {
        EXPECT_TRUE(Line({0.0, 0.0}, {0.0, 1.0}).contains(PointSet({Point {0.0, -2.0}})));
        EXPECT_TRUE(Line({0.0, 0.0}, {0.0, 1.0}).contains(PointSet({Point {0.0, -1.0}})));
        EXPECT_TRUE(Line({0.0, 0.0}, {0.0, 1.0}).contains(PointSet({Point {0.0, -0.5}})));
        EXPECT_TRUE(Line({0.0, 0.0}, {0.0, 1.0}).contains(PointSet({Point {0.0, +0.0}})));
        EXPECT_TRUE(Line({0.0, 0.0}, {0.0, 1.0}).contains(PointSet({Point {0.0, +0.5}})));
        EXPECT_TRUE(Line({0.0, 0.0}, {0.0, 1.0}).contains(PointSet({Point {0.0, +1.0}})));
        EXPECT_TRUE(Line({0.0, 0.0}, {0.0, 1.0}).contains(PointSet({Point {0.0, +2.0}})));

        EXPECT_TRUE(Line({0.0, 0.0}, {0.0, 1.0}).contains(PointSet({Point {0.0, -2.0}, Point {0.0, -1.0}})));
    }

    {
        EXPECT_FALSE(Line({0.0, 0.0}, {0.0, 1.0}).contains(PointSet({Point {1.0, 0.0}})));
        EXPECT_FALSE(Line({0.0, 0.0}, {0.0, 1.0}).contains(PointSet({Point {0.0, -2.0}, Point {1.0, 0.0}})));
    }

    {
        EXPECT_ANY_THROW(Line({0.0, 0.0}, {0.0, 1.0}).contains(PointSet::Empty()));
        EXPECT_ANY_THROW(Line::Undefined().contains(PointSet({Point {0.0, 0.0}})));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Line, GetOrigin)
{
    using ostk::math::geom::d2::objects::Point;
    using ostk::math::geom::d2::objects::Line;

    {
        EXPECT_EQ(Point(0.0, 0.0), Line({0.0, 0.0}, {0.0, 1.0}).getOrigin());
        EXPECT_EQ(Point(0.0, 1.0), Line({0.0, 1.0}, {0.0, 2.0}).getOrigin());

        EXPECT_EQ(Point(0.0, -1.0), Line({0.0, -1.0}, {0.0, +1.0}).getOrigin());
    }

    {
        EXPECT_ANY_THROW(Line::Undefined().getOrigin());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Line, GetDirection)
{
    using ostk::math::obj::Vector2d;
    using ostk::math::geom::d2::objects::Point;
    using ostk::math::geom::d2::objects::Line;

    {
        EXPECT_EQ(Vector2d(0.0, +1.0), Line({0.0, 0.0}, {0.0, +2.0}).getDirection());
        EXPECT_EQ(Vector2d(0.0, -1.0), Line({0.0, 0.0}, {0.0, -2.0}).getDirection());
    }

    {
        EXPECT_ANY_THROW(Line::Undefined().getDirection());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Line, DistanceTo_Point)
{
    using ostk::core::types::Real;

    using ostk::math::geom::d2::objects::Point;
    using ostk::math::geom::d2::objects::Line;

    {
        EXPECT_EQ(Line({0.0, 0.0}, {0.0, +1.0}).distanceTo({0.0, 0.0}), 0.0);
        EXPECT_EQ(Line({0.0, 0.0}, {0.0, +1.0}).distanceTo({0.0, +1.0}), 0.0);
        EXPECT_EQ(Line({0.0, 0.0}, {0.0, +1.0}).distanceTo({0.0, -1.0}), 0.0);
        EXPECT_EQ(Line({0.0, 0.0}, {0.0, +1.0}).distanceTo({0.0, +2.0}), 0.0);
        EXPECT_EQ(Line({0.0, 0.0}, {0.0, +1.0}).distanceTo({0.0, -2.0}), 0.0);

        EXPECT_EQ(Line({0.0, 0.0}, {0.0, -1.0}).distanceTo({0.0, 0.0}), 0.0);
        EXPECT_EQ(Line({0.0, 0.0}, {0.0, -1.0}).distanceTo({0.0, +1.0}), 0.0);
        EXPECT_EQ(Line({0.0, 0.0}, {0.0, -1.0}).distanceTo({0.0, -1.0}), 0.0);
        EXPECT_EQ(Line({0.0, 0.0}, {0.0, -1.0}).distanceTo({0.0, +2.0}), 0.0);
        EXPECT_EQ(Line({0.0, 0.0}, {0.0, -1.0}).distanceTo({0.0, -2.0}), 0.0);

        EXPECT_EQ(Line({0.0, 1.0}, {0.0, +1.0}).distanceTo({0.0, 0.0}), 0.0);
        EXPECT_EQ(Line({0.0, 1.0}, {0.0, +1.0}).distanceTo({0.0, +1.0}), 0.0);
        EXPECT_EQ(Line({0.0, 1.0}, {0.0, +1.0}).distanceTo({0.0, -1.0}), 0.0);
        EXPECT_EQ(Line({0.0, 1.0}, {0.0, +1.0}).distanceTo({0.0, +2.0}), 0.0);
        EXPECT_EQ(Line({0.0, 1.0}, {0.0, +1.0}).distanceTo({0.0, -2.0}), 0.0);

        EXPECT_EQ(Line({0.0, 0.0}, {0.0, +1.0}).distanceTo({1.0, 0.0}), 1.0);
        EXPECT_EQ(Line({1.0, 0.0}, {0.0, +1.0}).distanceTo({0.0, 0.0}), 1.0);
        EXPECT_EQ(Line({1.0, 0.0}, {0.0, +1.0}).distanceTo({0.0, 0.0}), 1.0);

        EXPECT_EQ(Line({1.0, 0.0}, {0.0, +1.0}).distanceTo({1.0, 2.0}), 0.0);
    }

    {
        EXPECT_NEAR(Line({1.0, 2.0}, {1.0, 1.0}).distanceTo({1.0, 5.0}), 2.12132, 1e-5);
        EXPECT_NEAR(Line({1.0, 2.0}, {1.0, 0.0}).distanceTo({1.0, 5.0}), 3.0, 1e-5);
        EXPECT_NEAR(Line({1.0, 2.0}, {4.0, 5.0}).distanceTo({7.0, 8.0}), 0.93704, 1e-5);
    }

    {
        EXPECT_ANY_THROW(Line::Undefined().distanceTo({0.0, 0.0}));
        EXPECT_ANY_THROW(Line({0.0, 0.0}, {0.0, 1.0}).distanceTo(Point::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Line, ApplyTransformation)
{
    using ostk::core::types::Real;

    using ostk::math::obj::Vector2d;
    using ostk::math::geom::d2::objects::Line;
    using ostk::math::geom::d2::Transformation;

    // Translation

    {
        Line line = {{0.0, 0.0}, {0.0, 1.0}};

        line.applyTransformation(Transformation::Translation({4.0, 5.0}));

        EXPECT_EQ(Line({4.0, 5.0}, {0.0, 1.0}), line);
    }

    {
        EXPECT_ANY_THROW(Line::Undefined().applyTransformation(Transformation::Undefined()));
        EXPECT_ANY_THROW(Line::Undefined().applyTransformation(Transformation::Identity()));
        EXPECT_ANY_THROW(Line({0.0, 0.0}, {0.0, 1.0}).applyTransformation(Transformation::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Line, Undefined)
{
    using ostk::math::geom::d2::objects::Line;

    {
        EXPECT_NO_THROW(Line::Undefined());
        EXPECT_FALSE(Line::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Line, Points)
{
    using ostk::math::obj::Vector2d;
    using ostk::math::geom::d2::objects::Point;
    using ostk::math::geom::d2::objects::Line;

    {
        const Line line = Line::Points(Point(1.0, 2.0), Point(2.0, 3.0));

        EXPECT_EQ(line.getOrigin(), Point(1.0, 2.0));
        EXPECT_NEAR((line.getDirection() - Vector2d(1.0, 1.0).normalized()).norm(), 0.0, 1e-15);
    }

    {
        EXPECT_ANY_THROW(Line::Points(Point(1.0, 2.0), Point(1.0, 2.0)));
    }

    {
        EXPECT_ANY_THROW(Line::Points(Point::Undefined(), Point(2.0, 3.0)));
        EXPECT_ANY_THROW(Line::Points(Point(1.0, 2.0), Point::Undefined()));
    }
}
