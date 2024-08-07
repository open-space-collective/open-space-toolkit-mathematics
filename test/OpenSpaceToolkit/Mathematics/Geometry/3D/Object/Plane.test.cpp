/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Plane.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Plane, Constructor)
{
    using ostk::mathematics::geometry::d3::object::Plane;

    {
        EXPECT_NO_THROW(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Plane, Clone)
{
    using ostk::mathematics::geometry::d3::object::Plane;

    {
        EXPECT_NO_THROW(const Plane* planePtr = Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).clone(); delete planePtr;);
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Plane, EqualToOperator)
{
    using ostk::mathematics::geometry::d3::object::Plane;

    {
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) == Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}));
        EXPECT_TRUE(Plane({0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}) == Plane({0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}));

        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) == Plane({1.0, 1.0, 0.0}, {0.0, 0.0, +1.0}));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) == Plane({1.0, 1.0, 0.0}, {0.0, 0.0, -1.0}));
    }

    {
        EXPECT_FALSE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) == Plane({0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}));
    }

    {
        EXPECT_FALSE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) == Plane::Undefined());
        EXPECT_FALSE(Plane::Undefined() == Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}));
        EXPECT_FALSE(Plane::Undefined() == Plane::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Plane, NotEqualToOperator)
{
    using ostk::mathematics::geometry::d3::object::Plane;

    {
        EXPECT_FALSE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) != Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}));
        EXPECT_FALSE(Plane({0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}) != Plane({0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}));

        EXPECT_FALSE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) != Plane({1.0, 1.0, 0.0}, {0.0, 0.0, +1.0}));
        EXPECT_FALSE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) != Plane({1.0, 1.0, 0.0}, {0.0, 0.0, -1.0}));
    }

    {
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) != Plane({0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}));
    }

    {
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) != Plane::Undefined());
        EXPECT_TRUE(Plane::Undefined() != Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}));
        EXPECT_TRUE(Plane::Undefined() != Plane::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Plane, StreamOperator)
{
    using ostk::mathematics::geometry::d3::object::Plane;

    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Plane, IsDefined)
{
    using ostk::mathematics::geometry::d3::object::Plane;

    {
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).isDefined());
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 2.0}).isDefined());
    }

    {
        EXPECT_FALSE(Plane::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Plane, Intersects_Point)
{
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;

    {
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersects(Point(0.0, 0.0, 0.0)));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersects(Point(1.0, 0.0, 0.0)));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersects(Point(0.0, 1.0, 0.0)));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersects(Point(1.0, 1.0, 0.0)));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 2.0}).intersects(Point(0.0, 0.0, 0.0)));
        EXPECT_TRUE(Plane({0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}).intersects(Point(0.0, 0.0, 1.0)));
        EXPECT_TRUE(Plane({1.0, 1.0, 1.0}, {0.0, 0.0, 1.0}).intersects(Point(0.0, 0.0, 1.0)));
    }

    {
        EXPECT_FALSE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersects(Point(0.0, 0.0, 0.1)));
        EXPECT_FALSE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersects(Point(0.0, 0.0, 1.0)));
        EXPECT_FALSE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersects(Point(0.0, 0.0, -1.0)));
    }

    {
        EXPECT_ANY_THROW(Plane::Undefined().intersects(Point::Undefined()));
        EXPECT_ANY_THROW(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersects(Point::Undefined()));
        EXPECT_ANY_THROW(Plane::Undefined().intersects(Point(0.0, 0.0, 0.0)));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Plane, Intersects_PointSet)
{
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::PointSet;

    {
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0})
                        .intersects(PointSet({{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}})));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersects(PointSet({{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}})));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersects(PointSet({{0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}})));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersects(PointSet({{1.0, 1.0, 0.0}, {0.0, 0.0, 0.0}})));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 2.0})
                        .intersects(PointSet({{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}})));
        EXPECT_TRUE(Plane({0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}).intersects(PointSet({{0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}})));
        EXPECT_TRUE(Plane({1.0, 1.0, 1.0}, {0.0, 0.0, 1.0}).intersects(PointSet({{0.0, 0.0, 1.0}, {0.0, 1.0, 1.0}})));

        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersects(PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.1}})));
    }

    {
        EXPECT_FALSE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0})
                         .intersects(PointSet({{0.0, 0.0, 0.1}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0}})));
    }

    {
        EXPECT_ANY_THROW(Plane::Undefined().intersects(PointSet::Empty()));
        EXPECT_ANY_THROW(Plane::Undefined().intersects(PointSet({{0.0, 0.0, 0.0}})));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Plane, Intersects_Line)
{
    using ostk::mathematics::geometry::d3::object::Line;
    using ostk::mathematics::geometry::d3::object::Plane;

    {
        // See: OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Line.Intersects_Plane

        SUCCEED();
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Plane, Intersects_Ray)
{
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Ray;

    {
        // See: OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ray.Intersects_Plane

        SUCCEED();
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Plane, Intersects_Segment)
{
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Segment;

    {
        // See: OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Segment.Intersects_Plane

        SUCCEED();
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Plane, Contains_Point)
{
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;

    {
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Point(0.0, 0.0, 0.0)));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Point(1.0, 0.0, 0.0)));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Point(0.0, 1.0, 0.0)));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Point(1.0, 1.0, 0.0)));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 2.0}).contains(Point(0.0, 0.0, 0.0)));
        EXPECT_TRUE(Plane({0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}).contains(Point(0.0, 0.0, 1.0)));
        EXPECT_TRUE(Plane({1.0, 1.0, 1.0}, {0.0, 0.0, 1.0}).contains(Point(0.0, 0.0, 1.0)));
    }

    {
        EXPECT_FALSE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Point(0.0, 0.0, 0.1)));
        EXPECT_FALSE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Point(0.0, 0.0, 1.0)));
        EXPECT_FALSE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Point(0.0, 0.0, -1.0)));
    }

    {
        EXPECT_ANY_THROW(Plane::Undefined().contains(Point::Undefined()));
        EXPECT_ANY_THROW(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Point::Undefined()));
        EXPECT_ANY_THROW(Plane::Undefined().contains(Point(0.0, 0.0, 0.0)));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Plane, Contains_PointSet)
{
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::PointSet;

    {
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0})
                        .contains(PointSet({{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}})));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(PointSet({{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}})));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(PointSet({{0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}})));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(PointSet({{1.0, 1.0, 0.0}, {0.0, 0.0, 0.0}})));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 2.0})
                        .contains(PointSet({{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}})));
        EXPECT_TRUE(Plane({0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}).contains(PointSet({{0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}})));
        EXPECT_TRUE(Plane({1.0, 1.0, 1.0}, {0.0, 0.0, 1.0}).contains(PointSet({{0.0, 0.0, 1.0}, {0.0, 1.0, 1.0}})));
    }

    {
        EXPECT_FALSE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0})
                         .contains(PointSet({{0.0, 0.0, 0.1}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0}})));
        EXPECT_FALSE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.1}})));
    }

    {
        EXPECT_ANY_THROW(Plane::Undefined().contains(PointSet::Empty()));
        EXPECT_ANY_THROW(Plane::Undefined().contains(PointSet({{0.0, 0.0, 0.0}})));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Plane, Contains_Line)
{
    using ostk::mathematics::geometry::d3::object::Line;
    using ostk::mathematics::geometry::d3::object::Plane;

    {
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Line({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0})));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Line({0.0, 0.0, 0.0}, {0.0, 1.0, 0.0})));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Line({0.0, 0.0, 0.0}, {1.0, 1.0, 0.0})));

        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Line({1.0, 0.0, 0.0}, {1.0, 0.0, 0.0})));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Line({0.0, 1.0, 0.0}, {0.0, 1.0, 0.0})));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Line({1.0, 1.0, 0.0}, {1.0, 1.0, 0.0})));
    }

    {
        EXPECT_FALSE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Line({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0})));

        EXPECT_FALSE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Line({0.0, 0.0, +1.0}, {1.0, 0.0, 0.0})));
        EXPECT_FALSE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Line({0.0, 0.0, -1.0}, {0.0, 1.0, 0.0})));
    }

    {
        EXPECT_ANY_THROW(Plane::Undefined().contains(Line::Undefined()));
        EXPECT_ANY_THROW(Plane::Undefined().contains(Line({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0})));
        EXPECT_ANY_THROW(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Line::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Plane, Contains_Ray)
{
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Ray;

    {
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Ray({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0})));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Ray({0.0, 0.0, 0.0}, {0.0, 1.0, 0.0})));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Ray({0.0, 0.0, 0.0}, {1.0, 1.0, 0.0})));

        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Ray({1.0, 0.0, 0.0}, {1.0, 0.0, 0.0})));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Ray({0.0, 1.0, 0.0}, {0.0, 1.0, 0.0})));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Ray({1.0, 1.0, 0.0}, {1.0, 1.0, 0.0})));
    }

    {
        EXPECT_FALSE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0})));

        EXPECT_FALSE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Ray({0.0, 0.0, +1.0}, {1.0, 0.0, 0.0})));
        EXPECT_FALSE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Ray({0.0, 0.0, -1.0}, {0.0, 1.0, 0.0})));
    }

    {
        EXPECT_ANY_THROW(Plane::Undefined().contains(Ray::Undefined()));
        EXPECT_ANY_THROW(Plane::Undefined().contains(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0})));
        EXPECT_ANY_THROW(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Ray::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Plane, Contains_Segment)
{
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Segment;

    {
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0})));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Segment({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0})));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Segment({0.0, 0.0, 0.0}, {0.0, 1.0, 0.0})));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Segment({0.0, 0.0, 0.0}, {1.0, 1.0, 0.0})));

        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Segment({1.0, 0.0, 0.0}, {1.0, 0.0, 0.0})));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Segment({0.0, 1.0, 0.0}, {0.0, 1.0, 0.0})));
        EXPECT_TRUE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Segment({1.0, 1.0, 0.0}, {1.0, 1.0, 0.0})));
    }

    {
        EXPECT_FALSE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0})));

        EXPECT_FALSE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Segment({0.0, 0.0, +1.0}, {1.0, 0.0, +1.0})));
        EXPECT_FALSE(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Segment({0.0, 0.0, -1.0}, {0.0, 1.0, -1.0})));
    }

    {
        EXPECT_ANY_THROW(Plane::Undefined().contains(Segment::Undefined()));
        EXPECT_ANY_THROW(Plane::Undefined().contains(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0})));
        EXPECT_ANY_THROW(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Segment::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Plane, GetPoint)
{
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;

    {
        EXPECT_EQ(Point(0.0, 0.0, 0.0), Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}).getPoint());
        EXPECT_EQ(Point(0.0, 0.0, 1.0), Plane({0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}).getPoint());
    }

    {
        EXPECT_ANY_THROW(Plane::Undefined().getPoint());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Plane, GetNormalVector)
{
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::object::Vector3d;

    {
        EXPECT_EQ(Vector3d(0.0, 0.0, +1.0), Plane({0.0, 0.0, 0.0}, {0.0, 0.0, +2.0}).getNormalVector());
        EXPECT_EQ(Vector3d(0.0, 0.0, -1.0), Plane({0.0, 0.0, 0.0}, {0.0, 0.0, -2.0}).getNormalVector());
    }

    {
        EXPECT_ANY_THROW(Plane::Undefined().getNormalVector());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Plane, IntersectionWith_Point)
{
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::d3::Intersection;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;

    const auto expectPointIntersection = [](const Plane& aPlane, const Point& aPoint, const Point& anIntersectionPoint
                                         ) -> void
    {
        const Intersection intersection = aPlane.intersectionWith(aPoint);

        EXPECT_TRUE(intersection.isDefined());

        ASSERT_TRUE(intersection.accessComposite().is<Point>());

        const Point point = intersection.accessComposite().as<Point>();

        EXPECT_TRUE(point.isNear(anIntersectionPoint, Real::Epsilon()));
    };

    const auto expectEmptyIntersection = [](const Plane& aPlane, const Point& aPoint) -> void
    {
        const Intersection intersection = aPlane.intersectionWith(aPoint);

        EXPECT_TRUE(intersection.isDefined());
        EXPECT_TRUE(intersection.isEmpty());
    };

    {
        expectPointIntersection(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}), Point(0.0, 0.0, 0.0), Point(0.0, 0.0, 0.0));
        expectPointIntersection(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}), Point(1.0, 0.0, 0.0), Point(1.0, 0.0, 0.0));
        expectPointIntersection(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}), Point(0.0, 1.0, 0.0), Point(0.0, 1.0, 0.0));
        expectPointIntersection(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}), Point(1.0, 1.0, 0.0), Point(1.0, 1.0, 0.0));
        expectPointIntersection(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 2.0}), Point(0.0, 0.0, 0.0), Point(0.0, 0.0, 0.0));
        expectPointIntersection(Plane({0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}), Point(0.0, 0.0, 1.0), Point(0.0, 0.0, 1.0));
        expectPointIntersection(Plane({1.0, 1.0, 1.0}, {0.0, 0.0, 1.0}), Point(0.0, 0.0, 1.0), Point(0.0, 0.0, 1.0));
    }

    {
        expectEmptyIntersection(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}), Point(0.0, 0.0, 0.1));
        expectEmptyIntersection(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}), Point(0.0, 0.0, 1.0));
        expectEmptyIntersection(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}), Point(0.0, 0.0, -1.0));
    }

    {
        EXPECT_ANY_THROW(Plane::Undefined().intersectionWith(Point::Undefined()));
        EXPECT_ANY_THROW(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersectionWith(Point::Undefined()));
        EXPECT_ANY_THROW(Plane::Undefined().intersectionWith(Point(0.0, 0.0, 0.0)));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Plane, IntersectionWith_PointSet)
{
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::d3::Intersection;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;

    const auto expectPointIntersection =
        [](const Plane& aPlane, const PointSet& aPointSet, const Point& anIntersectionPoint) -> void
    {
        const Intersection intersection = aPlane.intersectionWith(aPointSet);

        EXPECT_TRUE(intersection.isDefined());

        ASSERT_TRUE(intersection.accessComposite().is<Point>());

        const Point point = intersection.accessComposite().as<Point>();

        EXPECT_TRUE(point.isNear(anIntersectionPoint, Real::Epsilon()));
    };

    const auto expectPointSetIntersection =
        [](const Plane& aPlane, const PointSet& aPointSet, const PointSet& anIntersectionPointSet) -> void
    {
        const Intersection intersection = aPlane.intersectionWith(aPointSet);

        EXPECT_TRUE(intersection.isDefined());

        ASSERT_TRUE(intersection.accessComposite().is<PointSet>());

        const PointSet pointSet = intersection.accessComposite().as<PointSet>();

        EXPECT_TRUE(pointSet.isNear(anIntersectionPointSet, Real::Epsilon()));
    };

    const auto expectEmptyIntersection = [](const Plane& aPlane, const PointSet& aPointSet) -> void
    {
        const Intersection intersection = aPlane.intersectionWith(aPointSet);

        EXPECT_TRUE(intersection.isDefined());
        EXPECT_TRUE(intersection.isEmpty());
    };

    {
        expectPointSetIntersection(
            Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}),
            PointSet({{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}}),
            PointSet({{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}})
        );
        expectPointSetIntersection(
            Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}),
            PointSet({{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}),
            PointSet({{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}})
        );
        expectPointSetIntersection(
            Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}),
            PointSet({{0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}}),
            PointSet({{0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}})
        );
        expectPointSetIntersection(
            Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}),
            PointSet({{1.0, 1.0, 0.0}, {0.0, 0.0, 0.0}}),
            PointSet({{1.0, 1.0, 0.0}, {0.0, 0.0, 0.0}})
        );

        expectPointSetIntersection(
            Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 2.0}),
            PointSet({{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}}),
            PointSet({{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}})
        );
        expectPointSetIntersection(
            Plane({0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}),
            PointSet({{0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}}),
            PointSet({{0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}})
        );
        expectPointSetIntersection(
            Plane({1.0, 1.0, 1.0}, {0.0, 0.0, 1.0}),
            PointSet({{0.0, 0.0, 1.0}, {0.0, 1.0, 1.0}}),
            PointSet({{0.0, 0.0, 1.0}, {0.0, 1.0, 1.0}})
        );
    }

    {
        expectPointIntersection(
            Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}),
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.1}}),
            Point({0.0, 0.0, 0.0})
        );
    }

    {
        expectEmptyIntersection(
            Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}), PointSet({{0.0, 0.0, 0.1}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0}})
        );
    }

    {
        EXPECT_ANY_THROW(Plane::Undefined().intersectionWith(PointSet::Empty()));
        EXPECT_ANY_THROW(Plane::Undefined().intersectionWith(PointSet({{0.0, 0.0, 0.0}})));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Plane, IntersectionWith_Line)
{
    using ostk::mathematics::geometry::d3::object::Line;
    using ostk::mathematics::geometry::d3::object::Plane;

    {
        // See: OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Line.IntersectionWith_Plane

        SUCCEED();
    }

    {
        EXPECT_ANY_THROW(Plane::Undefined().intersectionWith(Line::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Plane, IntersectionWith_Ray)
{
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Ray;

    {
        // See: OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ray.IntersectionWith_Plane

        SUCCEED();
    }

    {
        EXPECT_ANY_THROW(Plane::Undefined().intersectionWith(Ray::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Plane, IntersectionWith_Segment)
{
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Segment;

    {
        // See: OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Segment.IntersectionWith_Plane

        SUCCEED();
    }

    {
        EXPECT_ANY_THROW(Plane::Undefined().intersectionWith(Segment::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Plane, ApplyTransformation)
{
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::Transformation;
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;
    using ostk::mathematics::object::Vector3d;

    // Translation

    {
        Plane plane = {{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}};

        plane.applyTransformation(Transformation::Translation({4.0, 5.0, 6.0}));

        EXPECT_EQ(Plane({4.0, 5.0, 6.0}, {0.0, 0.0, 1.0}), plane);
    }

    // Rotation

    {
        Plane plane = {{1.0, 3.0, 0.0}, {0.0, 1.0, 0.0}};

        plane.applyTransformation(Transformation::Rotation(RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(90.0))));

        const Plane referencePlane = {{1.0, 0.0, 3.0}, {0.0, 0.0, 1.0}};

        EXPECT_TRUE(plane.getPoint().isNear(referencePlane.getPoint(), Real::Epsilon()));
        EXPECT_TRUE(plane.getNormalVector().isNear(referencePlane.getNormalVector(), Real::Epsilon()));
    }

    {
        EXPECT_ANY_THROW(Plane::Undefined().applyTransformation(Transformation::Undefined()));
        EXPECT_ANY_THROW(Plane::Undefined().applyTransformation(Transformation::Identity()));
        EXPECT_ANY_THROW(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).applyTransformation(Transformation::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Plane, Undefined)
{
    using ostk::mathematics::geometry::d3::object::Plane;

    {
        EXPECT_NO_THROW(Plane::Undefined());
        EXPECT_FALSE(Plane::Undefined().isDefined());
    }
}
