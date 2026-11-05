/// Apache License 2.0

#include <limits>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Point, Constructor)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::object::Vector3d;

    {
        EXPECT_NO_THROW(Point(1.0, 2.0, 3.0));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Point, Clone)
{
    using ostk::mathematics::geometry::d3::object::Point;

    {
        EXPECT_NO_THROW(const Point* pointPtr = Point(1.0, 2.0, 3.0).clone(); delete pointPtr;);
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Point, EqualToOperator)
{
    using ostk::mathematics::geometry::d3::object::Point;

    {
        EXPECT_TRUE(Point(1.0, 2.0, 3.0) == Point(1.0, 2.0, 3.0));
    }

    {
        EXPECT_FALSE(Point(1.0, 2.0, 3.0) == Point(1.0, 2.0, 4.0));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Point, NotEqualToOperator)
{
    using ostk::mathematics::geometry::d3::object::Point;

    {
        EXPECT_TRUE(Point(1.0, 2.0, 3.0) != Point(1.0, 2.0, 4.0));
    }

    {
        EXPECT_FALSE(Point(1.0, 2.0, 3.0) != Point(1.0, 2.0, 3.0));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Point, AdditionOperator)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::object::Vector3d;

    {
        EXPECT_EQ(Point(1.0, 2.0, 3.0), Point(1.0, 2.0, 3.0) + Vector3d(0.0, 0.0, 0.0));
        EXPECT_EQ(Point(2.0, 2.0, 3.0), Point(1.0, 2.0, 3.0) + Vector3d(1.0, 0.0, 0.0));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Point, SubtractionOperator)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::object::Vector3d;

    {
        EXPECT_EQ(Point(1.0, 2.0, 3.0), Point(1.0, 2.0, 3.0) - Vector3d(0.0, 0.0, 0.0));
        EXPECT_EQ(Point(0.0, 2.0, 3.0), Point(1.0, 2.0, 3.0) - Vector3d(1.0, 0.0, 0.0));
    }

    {
        EXPECT_EQ(Vector3d(1.0, 2.0, 3.0), Point(1.0, 2.0, 3.0) - Point(0.0, 0.0, 0.0));
        EXPECT_EQ(Vector3d(0.0, 2.0, 3.0), Point(1.0, 2.0, 3.0) - Point(1.0, 0.0, 0.0));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Point, StreamOperator)
{
    using ostk::mathematics::geometry::d3::object::Point;

    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << Point(1.0, 2.0, 3.0) << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Point, IsNear)
{
    using ostk::mathematics::geometry::d3::object::Point;

    {
        EXPECT_TRUE(Point(0.0, 0.0, 0.0).isNear(Point(0.0, 0.0, 0.0), 0.0));
        EXPECT_TRUE(Point(0.0, 0.0, 0.0).isNear(Point(0.0, 0.0, 1e-15), 1e-15));

        EXPECT_FALSE(Point(0.0, 0.0, 0.0).isNear(Point(0.0, 0.0, 1e-14), 1e-15));
    }

    {
        EXPECT_ANY_THROW(Point(0.0, 0.0, 0.0).isNear(Point(0.0, 0.0, 0.0), std::numeric_limits<double>::quiet_NaN()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Point, AsVector)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::object::Vector3d;

    {
        EXPECT_EQ(Vector3d(1.0, 2.0, 3.0), Point(1.0, 2.0, 3.0).asVector());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Point, DistanceTo)
{
    using ostk::mathematics::geometry::d3::object::Point;

    {
        EXPECT_EQ(0.0, Point(0.0, 0.0, 0.0).distanceTo(Point(0.0, 0.0, 0.0)));

        EXPECT_EQ(0.0, Point(+1.0, +1.0, +1.0).distanceTo(Point(+1.0, +1.0, +1.0)));
        EXPECT_EQ(0.0, Point(-1.0, -1.0, -1.0).distanceTo(Point(-1.0, -1.0, -1.0)));

        EXPECT_EQ(1.0, Point(0.0, 0.0, 0.0).distanceTo(Point(+1.0, 0.0, 0.0)));
        EXPECT_EQ(1.0, Point(0.0, 0.0, 0.0).distanceTo(Point(0.0, +1.0, 0.0)));
        EXPECT_EQ(1.0, Point(0.0, 0.0, 0.0).distanceTo(Point(0.0, 0.0, +1.0)));

        EXPECT_EQ(1.0, Point(0.0, 0.0, 0.0).distanceTo(Point(-1.0, 0.0, 0.0)));
        EXPECT_EQ(1.0, Point(0.0, 0.0, 0.0).distanceTo(Point(0.0, -1.0, 0.0)));
        EXPECT_EQ(1.0, Point(0.0, 0.0, 0.0).distanceTo(Point(0.0, 0.0, -1.0)));

        EXPECT_EQ(1.0, Point(+1.0, 0.0, 0.0).distanceTo(Point(0.0, 0.0, 0.0)));
        EXPECT_EQ(1.0, Point(0.0, +1.0, 0.0).distanceTo(Point(0.0, 0.0, 0.0)));
        EXPECT_EQ(1.0, Point(0.0, 0.0, +1.0).distanceTo(Point(0.0, 0.0, 0.0)));

        EXPECT_EQ(1.0, Point(-1.0, 0.0, 0.0).distanceTo(Point(0.0, 0.0, 0.0)));
        EXPECT_EQ(1.0, Point(0.0, -1.0, 0.0).distanceTo(Point(0.0, 0.0, 0.0)));
        EXPECT_EQ(1.0, Point(0.0, 0.0, -1.0).distanceTo(Point(0.0, 0.0, 0.0)));

        EXPECT_EQ(2.0, Point(0.0, 0.0, 0.0).distanceTo(Point(+2.0, 0.0, 0.0)));
        EXPECT_EQ(2.0, Point(0.0, 0.0, 0.0).distanceTo(Point(0.0, +2.0, 0.0)));
        EXPECT_EQ(2.0, Point(0.0, 0.0, 0.0).distanceTo(Point(0.0, 0.0, +2.0)));

        EXPECT_EQ(2.0, Point(0.0, 0.0, 0.0).distanceTo(Point(-2.0, 0.0, 0.0)));
        EXPECT_EQ(2.0, Point(0.0, 0.0, 0.0).distanceTo(Point(0.0, -2.0, 0.0)));
        EXPECT_EQ(2.0, Point(0.0, 0.0, 0.0).distanceTo(Point(0.0, 0.0, -2.0)));

        EXPECT_EQ(2.0, Point(+2.0, 0.0, 0.0).distanceTo(Point(0.0, 0.0, 0.0)));
        EXPECT_EQ(2.0, Point(0.0, +2.0, 0.0).distanceTo(Point(0.0, 0.0, 0.0)));
        EXPECT_EQ(2.0, Point(0.0, 0.0, +2.0).distanceTo(Point(0.0, 0.0, 0.0)));

        EXPECT_EQ(2.0, Point(-2.0, 0.0, 0.0).distanceTo(Point(0.0, 0.0, 0.0)));
        EXPECT_EQ(2.0, Point(0.0, -2.0, 0.0).distanceTo(Point(0.0, 0.0, 0.0)));
        EXPECT_EQ(2.0, Point(0.0, 0.0, -2.0).distanceTo(Point(0.0, 0.0, 0.0)));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Point, ApplyTransformation)
{
    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::Transformation;
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;
    using ostk::mathematics::object::Vector3d;

    // Translation

    {
        Point point = {1.0, 2.0, 3.0};

        point.applyTransformation(Transformation::Translation({4.0, 5.0, 6.0}));

        EXPECT_TRUE(point.isNear(Point(5.0, 7.0, 9.0), 1e-15));
    }

    // Rotation

    {
        Point point = {1.0, 2.0, 0.0};

        point.applyTransformation(Transformation::Rotation(RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(90.0))));

        EXPECT_TRUE(point.isNear(Point(1.0, 0.0, 2.0), 1e-15));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Point, Origin)
{
    using ostk::mathematics::geometry::d3::object::Point;

    {
        EXPECT_NO_THROW(Point::Origin());
        EXPECT_EQ(Point(0.0, 0.0, 0.0), Point::Origin());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Point, Vector)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::object::Vector3d;

    {
        EXPECT_NO_THROW(Point::Vector(Vector3d(1.0, 2.0, 3.0)));
        EXPECT_EQ(Point(1.0, 2.0, 3.0), Point::Vector(Vector3d(1.0, 2.0, 3.0)));
    }
}
