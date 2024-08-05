/// Apache License 2.0

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

    {
        EXPECT_FALSE(Point(1.0, 2.0, 3.0) == Point::Undefined());
        EXPECT_FALSE(Point::Undefined() == Point(1.0, 2.0, 3.0));
        EXPECT_FALSE(Point::Undefined() == Point::Undefined());
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

    {
        EXPECT_TRUE(Point(1.0, 2.0, 3.0) != Point::Undefined());
        EXPECT_TRUE(Point::Undefined() != Point(1.0, 2.0, 3.0));
        EXPECT_TRUE(Point::Undefined() != Point::Undefined());
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

    {
        EXPECT_ANY_THROW(Point::Undefined() + Vector3d(0.0, 0.0, 0.0));
        EXPECT_ANY_THROW(Point(1.0, 2.0, 3.0) + Vector3d::Undefined());
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
        EXPECT_ANY_THROW(Point::Undefined() - Vector3d(0.0, 0.0, 0.0));
        EXPECT_ANY_THROW(Point(1.0, 2.0, 3.0) - Vector3d::Undefined());
    }

    {
        EXPECT_EQ(Vector3d(1.0, 2.0, 3.0), Point(1.0, 2.0, 3.0) - Point(0.0, 0.0, 0.0));
        EXPECT_EQ(Vector3d(0.0, 2.0, 3.0), Point(1.0, 2.0, 3.0) - Point(1.0, 0.0, 0.0));
    }

    {
        EXPECT_ANY_THROW(Point::Undefined() - Point(0.0, 0.0, 0.0));
        EXPECT_ANY_THROW(Point(1.0, 2.0, 3.0) - Point::Undefined());
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

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Point, IsDefined)
{
    using ostk::mathematics::geometry::d3::object::Point;

    {
        EXPECT_TRUE(Point(0.0, 0.0, 0.0).isDefined());
        EXPECT_TRUE(Point(1.0, 2.0, 3.0).isDefined());
    }

    {
        EXPECT_FALSE(Point::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Point, IsNear)
{
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::d3::object::Point;

    {
        EXPECT_TRUE(Point(0.0, 0.0, 0.0).isNear(Point(0.0, 0.0, 0.0), 0.0));
        EXPECT_TRUE(Point(0.0, 0.0, 0.0).isNear(Point(0.0, 0.0, 1e-15), 1e-15));

        EXPECT_FALSE(Point(0.0, 0.0, 0.0).isNear(Point(0.0, 0.0, 1e-14), 1e-15));
    }

    {
        EXPECT_ANY_THROW(Point::Undefined().isNear(Point::Undefined(), Real::Undefined()));
        EXPECT_ANY_THROW(Point(0.0, 0.0, 0.0).isNear(Point::Undefined(), 1e-15));
        EXPECT_ANY_THROW(Point::Undefined().isNear(Point(0.0, 0.0, 0.0), 1e-15));
        EXPECT_ANY_THROW(Point(0.0, 0.0, 0.0).isNear(Point(0.0, 0.0, 0.0), Real::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Point, AsVector)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::object::Vector3d;

    {
        EXPECT_EQ(Vector3d(1.0, 2.0, 3.0), Point(1.0, 2.0, 3.0).asVector());
    }

    {
        EXPECT_ANY_THROW(Point::Undefined().asVector());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Point, DistanceTo)
{
    using ostk::core::type::Real;

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

    {
        EXPECT_ANY_THROW(Point::Undefined().distanceTo(Point::Undefined()));
        EXPECT_ANY_THROW(Point(0.0, 0.0, 0.0).distanceTo(Point::Undefined()));
        EXPECT_ANY_THROW(Point::Undefined().distanceTo(Point(0.0, 0.0, 0.0)));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Point, ApplyTransformation)
{
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::Transformation;
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;
    using ostk::mathematics::object::Vector3d;

    // Translation

    {
        Point point = {1.0, 2.0, 3.0};

        point.applyTransformation(Transformation::Translation({4.0, 5.0, 6.0}));

        EXPECT_TRUE(point.isNear(Point(5.0, 7.0, 9.0), Real::Epsilon()));
    }

    // Rotation

    {
        Point point = {1.0, 2.0, 0.0};

        point.applyTransformation(Transformation::Rotation(RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(90.0))));

        EXPECT_TRUE(point.isNear(Point(1.0, 0.0, 2.0), Real::Epsilon()));
    }

    {
        EXPECT_ANY_THROW(Point::Undefined().applyTransformation(Transformation::Undefined()));
        EXPECT_ANY_THROW(Point::Undefined().applyTransformation(Transformation::Identity()));
        EXPECT_ANY_THROW(Point(0.0, 0.0, 0.0).applyTransformation(Transformation::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Point, Undefined)
{
    using ostk::mathematics::geometry::d3::object::Point;

    {
        EXPECT_NO_THROW(Point::Undefined());
        EXPECT_FALSE(Point::Undefined().isDefined());
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
