/// Apache License 2.0

#include <limits>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Transformation.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Point, Constructor)
{
    using ostk::mathematics::geometry::d2::object::Point;

    {
        EXPECT_NO_THROW(Point(1.0, 2.0));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Point, Clone)
{
    using ostk::mathematics::geometry::d2::object::Point;

    {
        EXPECT_NO_THROW(const Point* pointPtr = Point(1.0, 2.0).clone(); delete pointPtr;);
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Point, AdditionOperator)
{
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::object::Vector2d;

    {
        EXPECT_EQ(Point(1.0, 2.0), Point(1.0, 2.0) + Vector2d(0.0, 0.0));
        EXPECT_EQ(Point(2.0, 2.0), Point(1.0, 2.0) + Vector2d(1.0, 0.0));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Point, SubtractionOperator)
{
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::object::Vector2d;

    {
        EXPECT_EQ(Point(1.0, 2.0), Point(1.0, 2.0) - Vector2d(0.0, 0.0));
        EXPECT_EQ(Point(0.0, 2.0), Point(1.0, 2.0) - Vector2d(1.0, 0.0));
    }

    {
        EXPECT_EQ(Vector2d(1.0, 2.0), Point(1.0, 2.0) - Point(0.0, 0.0));
        EXPECT_EQ(Vector2d(0.0, 2.0), Point(1.0, 2.0) - Point(1.0, 0.0));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Point, EqualToOperator)
{
    using ostk::mathematics::geometry::d2::object::Point;

    {
        EXPECT_TRUE(Point(1.0, 2.0) == Point(1.0, 2.0));
    }

    {
        EXPECT_FALSE(Point(1.0, 2.0) == Point(1.0, 3.0));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Point, NotEqualToOperator)
{
    using ostk::mathematics::geometry::d2::object::Point;

    {
        EXPECT_TRUE(Point(1.0, 2.0) != Point(1.0, 3.0));
    }

    {
        EXPECT_FALSE(Point(1.0, 2.0) != Point(1.0, 2.0));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Point, StreamOperator)
{
    using ostk::mathematics::geometry::d2::object::Point;

    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << Point(1.0, 2.0) << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Point, IsNear)
{
    using ostk::mathematics::geometry::d2::object::Point;

    {
        EXPECT_TRUE(Point(0.0, 0.0).isNear(Point(0.0, 0.0), 0.0));
        EXPECT_TRUE(Point(0.0, 0.0).isNear(Point(0.0, 1e-15), 1e-15));

        EXPECT_FALSE(Point(0.0, 0.0).isNear(Point(0.0, 1e-14), 1e-15));
    }

    {
        EXPECT_ANY_THROW(Point(0.0, 0.0).isNear(Point(0.0, 0.0), std::numeric_limits<double>::quiet_NaN()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Point, AsVector)
{
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::object::Vector2d;

    {
        EXPECT_EQ(Vector2d(1.0, 2.0), Point(1.0, 2.0).asVector());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Point, DistanceTo)
{
    using ostk::mathematics::geometry::d2::object::Point;

    {
        EXPECT_EQ(0.0, Point(0.0, 0.0).distanceTo(Point(0.0, 0.0)));

        EXPECT_EQ(0.0, Point(+1.0, +1.0).distanceTo(Point(+1.0, +1.0)));
        EXPECT_EQ(0.0, Point(-1.0, -1.0).distanceTo(Point(-1.0, -1.0)));

        EXPECT_EQ(1.0, Point(0.0, 0.0).distanceTo(Point(+1.0, 0.0)));
        EXPECT_EQ(1.0, Point(0.0, 0.0).distanceTo(Point(0.0, +1.0)));

        EXPECT_EQ(1.0, Point(0.0, 0.0).distanceTo(Point(-1.0, 0.0)));
        EXPECT_EQ(1.0, Point(0.0, 0.0).distanceTo(Point(0.0, -1.0)));

        EXPECT_EQ(1.0, Point(+1.0, 0.0).distanceTo(Point(0.0, 0.0)));
        EXPECT_EQ(1.0, Point(0.0, +1.0).distanceTo(Point(0.0, 0.0)));

        EXPECT_EQ(1.0, Point(-1.0, 0.0).distanceTo(Point(0.0, 0.0)));
        EXPECT_EQ(1.0, Point(0.0, -1.0).distanceTo(Point(0.0, 0.0)));

        EXPECT_EQ(2.0, Point(0.0, 0.0).distanceTo(Point(+2.0, 0.0)));
        EXPECT_EQ(2.0, Point(0.0, 0.0).distanceTo(Point(0.0, +2.0)));

        EXPECT_EQ(2.0, Point(0.0, 0.0).distanceTo(Point(-2.0, 0.0)));
        EXPECT_EQ(2.0, Point(0.0, 0.0).distanceTo(Point(0.0, -2.0)));

        EXPECT_EQ(2.0, Point(+2.0, 0.0).distanceTo(Point(0.0, 0.0)));
        EXPECT_EQ(2.0, Point(0.0, +2.0).distanceTo(Point(0.0, 0.0)));

        EXPECT_EQ(2.0, Point(-2.0, 0.0).distanceTo(Point(0.0, 0.0)));
        EXPECT_EQ(2.0, Point(0.0, -2.0).distanceTo(Point(0.0, 0.0)));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Point, ToString)
{
    using ostk::mathematics::geometry::d2::object::Point;

    {
        EXPECT_EQ("[1.0, 2.0]", Point(1.0, 2.0).toString());
        EXPECT_EQ("[1.0, 2.0]", Point(1.0, 2.0).toString(Point::Format::Standard));
        EXPECT_EQ("POINT(1.0 2.0)", Point(1.0, 2.0).toString(Point::Format::WKT));
    }

    {
        EXPECT_EQ("[1.0000000000, 2.0000000000]", Point(1.0, 2.0).toString(Point::Format::Standard, 10));
        EXPECT_EQ("POINT(1.0000000000 2.0000000000)", Point(1.0, 2.0).toString(Point::Format::WKT, 10));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Point, ApplyTransformation)
{
    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::Transformation;
    using ostk::mathematics::object::Vector2d;

    // Translation

    {
        Point point = {1.0, 2.0};

        point.applyTransformation(Transformation::Translation({4.0, 5.0}));

        EXPECT_TRUE(point.isNear(Point(5.0, 7.0), 1e-15)) << point;
    }

    // Rotation

    {
        Point point = {+1.0, +2.0};

        point.applyTransformation(Transformation::Rotation(Angle::Degrees(90.0)));

        EXPECT_TRUE(point.isNear(Point(-2.0, +1.0), 1e-15)) << point;
    }

    // Rotation Around

    {
        Point point = {+1.0, +2.0};

        point.applyTransformation(Transformation::RotationAround(point, Angle::Degrees(90.0)));

        EXPECT_TRUE(point.isNear(Point(+1.0, +2.0), 1e-15)) << point;
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Point, Origin)
{
    using ostk::mathematics::geometry::d2::object::Point;

    {
        EXPECT_NO_THROW(Point::Origin());
        EXPECT_EQ(Point(0.0, 0.0), Point::Origin());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Point, Vector)
{
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::object::Vector2d;

    {
        EXPECT_NO_THROW(Point::Vector(Vector2d(1.0, 2.0)));
        EXPECT_EQ(Point(1.0, 2.0), Point::Vector(Vector2d(1.0, 2.0)));
    }
}
