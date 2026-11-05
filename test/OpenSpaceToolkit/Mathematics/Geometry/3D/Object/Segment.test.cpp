/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Sphere.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Segment, Constructor)
{
    using ostk::mathematics::geometry::d3::object::Segment;

    {
        EXPECT_NO_THROW(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Segment, Clone)
{
    using ostk::mathematics::geometry::d3::object::Segment;

    {
        EXPECT_NO_THROW(const Segment* segmentPtr = Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).clone();
                        delete segmentPtr;);
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Segment, EqualToOperator)
{
    using ostk::mathematics::geometry::d3::object::Segment;

    {
        EXPECT_TRUE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) == Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}));
        EXPECT_TRUE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) == Segment({0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}));
    }

    {
        EXPECT_FALSE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) == Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 2.0}));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Segment, NotEqualToOperator)
{
    using ostk::mathematics::geometry::d3::object::Segment;

    {
        EXPECT_FALSE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) != Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}));
        EXPECT_FALSE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) != Segment({0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}));
    }

    {
        EXPECT_TRUE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) != Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 2.0}));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Segment, StreamOperator)
{
    using ostk::mathematics::geometry::d3::object::Segment;

    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Segment, IsDegenerate)
{
    using ostk::mathematics::geometry::d3::object::Segment;

    {
        EXPECT_TRUE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}).isDegenerate());
        EXPECT_TRUE(Segment({1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}).isDegenerate());
    }

    {
        EXPECT_FALSE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).isDegenerate());
        EXPECT_FALSE(Segment({1.0, 2.0, 3.0}, {0.0, 0.0, 1.0}).isDegenerate());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Segment, Intersects_Plane)
{
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Segment;

    {
        EXPECT_TRUE(Segment({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}).intersects(Plane({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0})));
        EXPECT_TRUE(Segment({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}).intersects(Plane({0.0, 0.0, 0.0}, {0.0, 1.0, 0.0})));
        EXPECT_TRUE(Segment({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}).intersects(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0})));

        EXPECT_TRUE(Segment({1.0, 2.0, 3.0}, {2.0, 2.0, 3.0}).intersects(Plane({1.0, 2.0, 3.0}, {1.0, 0.0, 0.0})));
        EXPECT_TRUE(Segment({1.0, 2.0, 3.0}, {2.0, 2.0, 3.0}).intersects(Plane({1.0, 2.0, 3.0}, {0.0, 1.0, 0.0})));
        EXPECT_TRUE(Segment({1.0, 2.0, 3.0}, {2.0, 2.0, 3.0}).intersects(Plane({1.0, 2.0, 3.0}, {0.0, 0.0, 1.0})));

        EXPECT_TRUE(Segment({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}).intersects(Plane({+1.0, +2.0, +3.0}, {1.0, 0.0, 0.0})));
    }

    {
        EXPECT_FALSE(Segment({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}).intersects(Plane({+1.0, +2.0, +3.0}, {0.0, 1.0, 0.0})));
        EXPECT_FALSE(Segment({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}).intersects(Plane({+1.0, +2.0, +3.0}, {0.0, 0.0, 1.0})));

        EXPECT_FALSE(Segment({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}).intersects(Plane({-1.0, -2.0, -3.0}, {0.0, 1.0, 0.0})));
        EXPECT_FALSE(Segment({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}).intersects(Plane({-1.0, -2.0, -3.0}, {0.0, 0.0, 1.0})));

        EXPECT_FALSE(Segment({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}).intersects(Plane({-1.0, -2.0, -3.0}, {1.0, 0.0, 0.0})));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Segment, Intersects_Sphere)
{
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::geometry::d3::object::Sphere;

    {
        // See: OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Sphere.Intersects

        SUCCEED();
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Segment, Intersects_Ellipsoid)
{
    using ostk::mathematics::geometry::d3::object::Ellipsoid;
    using ostk::mathematics::geometry::d3::object::Segment;

    {
        // See: OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ellipsoid.Intersects

        SUCCEED();
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Segment, Contains_Point)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Segment;

    {
        EXPECT_TRUE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}).contains(Point(0.0, 0.0, 0.0)));
        EXPECT_TRUE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Point(0.0, 0.0, 0.0)));
        EXPECT_TRUE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Point(0.0, 0.0, 1.0)));
        EXPECT_TRUE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Point(0.0, 0.0, 0.5)));
    }

    {
        EXPECT_FALSE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}).contains(Point(0.0, 0.0, 0.1)));
        EXPECT_FALSE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Point(0.0, 0.0, 2.0)));
        EXPECT_FALSE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Point(0.0, 0.0, -1.0)));
        EXPECT_FALSE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Point(1.0, 0.0, 0.0)));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Segment, GetCenter)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Segment;

    {
        EXPECT_EQ(Point(0.0, 0.0, 0.0), Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}).getCenter());
        EXPECT_EQ(Point(0.0, 0.0, 1.0), Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 2.0}).getCenter());

        EXPECT_EQ(Point(0.0, 0.0, 0.0), Segment({0.0, 0.0, -1.0}, {0.0, 0.0, +1.0}).getCenter());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Segment, GetDirection)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::object::Vector3d;

    {
        EXPECT_EQ(Vector3d(0.0, 0.0, +1.0), Segment({0.0, 0.0, 0.0}, {0.0, 0.0, +2.0}).getDirection());
        EXPECT_EQ(Vector3d(0.0, 0.0, -1.0), Segment({0.0, 0.0, 0.0}, {0.0, 0.0, -2.0}).getDirection());
    }

    {
        EXPECT_ANY_THROW(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}).getDirection());
        EXPECT_ANY_THROW(Segment({1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}).getDirection());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Segment, GetLength)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Segment;

    {
        EXPECT_EQ(0.0, Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}).getLength());
        EXPECT_EQ(0.0, Segment({1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}).getLength());

        EXPECT_EQ(1.0, Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).getLength());
        EXPECT_EQ(2.0, Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 2.0}).getLength());

        EXPECT_EQ(4.0, Segment({0.0, 0.0, -2.0}, {0.0, 0.0, +2.0}).getLength());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Segment, DistanceToPoint)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Segment;

    {
        EXPECT_EQ(0.0, Segment({0.0, 0.0, 0.0}, {0.0, +1.0, 0.0}).distanceTo(Point({0.0, 0.0, 0.0})));
        EXPECT_EQ(0.0, Segment({0.0, 0.0, 0.0}, {0.0, +2.0, 0.0}).distanceTo(Point({0.0, 0.0, 0.0})));
        EXPECT_EQ(0.0, Segment({0.0, 0.0, 0.0}, {0.0, -1.0, 0.0}).distanceTo(Point({0.0, 0.0, 0.0})));
        EXPECT_EQ(0.0, Segment({0.0, 0.0, 0.0}, {0.0, -2.0, 0.0}).distanceTo(Point({0.0, 0.0, 0.0})));

        EXPECT_EQ(0.0, Segment({0.0, 0.0, 0.0}, {0.0, +1.0, 0.0}).distanceTo(Point({0.0, 1.0, 0.0})));
        EXPECT_EQ(0.0, Segment({0.0, 0.0, 0.0}, {0.0, +2.0, 0.0}).distanceTo(Point({0.0, 1.0, 0.0})));

        EXPECT_EQ(0.0, Segment({0.0, 0.0, 0.0}, {0.0, +2.0, 0.0}).distanceTo(Point({0.0, 2.0, 0.0})));

        EXPECT_EQ(1.0, Segment({0.0, 0.0, 0.0}, {0.0, +1.0, 0.0}).distanceTo(Point({+0.0, +2.0, 0.0})));
        EXPECT_EQ(1.0, Segment({0.0, 0.0, 0.0}, {0.0, +1.0, 0.0}).distanceTo(Point({+1.0, +1.0, 0.0})));
        EXPECT_EQ(1.0, Segment({0.0, 0.0, 0.0}, {0.0, +1.0, 0.0}).distanceTo(Point({-1.0, +1.0, 0.0})));

        EXPECT_EQ(1.0, Segment({0.0, 0.0, 0.0}, {0.0, +1.0, 0.0}).distanceTo(Point({+0.0, -1.0, 0.0})));
        EXPECT_EQ(1.0, Segment({0.0, 0.0, 0.0}, {0.0, +1.0, 0.0}).distanceTo(Point({+1.0, +0.0, 0.0})));
        EXPECT_EQ(1.0, Segment({0.0, 0.0, 0.0}, {0.0, +1.0, 0.0}).distanceTo(Point({-1.0, +0.0, 0.0})));

        EXPECT_EQ(2.0, Segment({0.0, 0.0, 0.0}, {0.0, +1.0, 0.0}).distanceTo(Point({+0.0, +3.0, 0.0})));
        EXPECT_EQ(2.0, Segment({0.0, 0.0, 0.0}, {0.0, +1.0, 0.0}).distanceTo(Point({+0.0, -2.0, 0.0})));

        EXPECT_NEAR(1.41421, Segment({0.0, 0.0, 0.0}, {0.0, +1.0, 0.0}).distanceTo(Point({+1.0, +2.0, 0.0})), 1e-5);
        EXPECT_NEAR(1.41421, Segment({0.0, 0.0, 0.0}, {0.0, +1.0, 0.0}).distanceTo(Point({-1.0, +2.0, 0.0})), 1e-5);
        EXPECT_NEAR(1.41421, Segment({0.0, 0.0, 0.0}, {0.0, +1.0, 0.0}).distanceTo(Point({+1.0, -1.0, 0.0})), 1e-5);
        EXPECT_NEAR(1.41421, Segment({0.0, 0.0, 0.0}, {0.0, +1.0, 0.0}).distanceTo(Point({-1.0, -1.0, 0.0})), 1e-5);
    }

    {
        EXPECT_EQ(0.0, Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}).distanceTo(Point({0.0, 0.0, 0.0})));

        EXPECT_EQ(0.0, Segment({+1.0, 0.0, 0.0}, {+1.0, 0.0, 0.0}).distanceTo(Point({+1.0, 0.0, 0.0})));
        EXPECT_EQ(0.0, Segment({0.0, +1.0, 0.0}, {0.0, +1.0, 0.0}).distanceTo(Point({0.0, +1.0, 0.0})));

        EXPECT_EQ(0.0, Segment({-1.0, 0.0, 0.0}, {-1.0, 0.0, 0.0}).distanceTo(Point({-1.0, 0.0, 0.0})));
        EXPECT_EQ(0.0, Segment({0.0, -1.0, 0.0}, {0.0, -1.0, 0.0}).distanceTo(Point({0.0, -1.0, 0.0})));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Segment, DistanceToPointSet)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Segment;

    {
        EXPECT_EQ(
            0.0, Segment({0.0, 0.0, 0.0}, {0.0, +1.0, 0.0}).distanceTo(PointSet({{0.0, 0.0, 0.0}, {0.0, 10.0, 0.0}}))
        );
        EXPECT_EQ(
            0.0, Segment({0.0, 0.0, 0.0}, {0.0, +1.0, 0.0}).distanceTo(PointSet({{0.0, 10.0, 0.0}, {0.0, 0.0, 0.0}}))
        );

        EXPECT_EQ(
            1.0,
            Segment({0.0, 0.0, 0.0}, {0.0, +1.0, 0.0})
                .distanceTo(PointSet({{0.0, 3.0, 0.0}, {0.0, 2.0, 0.0}, {10.0, 0.0, 0.0}}))
        );
    }

    {
        EXPECT_ANY_THROW(Segment({0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}).distanceTo(PointSet::Empty()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Segment, IntersectionWith_Plane)
{
    using ostk::mathematics::geometry::d3::Intersection;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Segment;

    const auto expectSegmentIntersection =
        [](const Segment& aSegment, const Plane& aPlane, const Segment& anIntersectionSegment) -> void
    {
        const Intersection intersection = aSegment.intersectionWith(aPlane);

        ASSERT_TRUE(intersection.getComposite().is<Segment>());

        const Segment segment = intersection.getComposite().as<Segment>();

        EXPECT_EQ(anIntersectionSegment, segment);
    };

    const auto expectPointIntersection =
        [](const Segment& aSegment, const Plane& aPlane, const Point& anIntersectionPoint) -> void
    {
        const Intersection intersection = aSegment.intersectionWith(aPlane);

        ASSERT_TRUE(intersection.getComposite().is<Point>());

        const Point point = intersection.getComposite().as<Point>();

        EXPECT_TRUE(point.isNear(anIntersectionPoint, 1e-15));
    };

    const auto expectEmptyIntersection = [](const Segment& aSegment, const Plane& aPlane) -> void
    {
        const Intersection intersection = aSegment.intersectionWith(aPlane);

        EXPECT_TRUE(intersection.isEmpty());
    };

    {
        expectPointIntersection(
            Segment({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}), Plane({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}), Point(0.0, 0.0, 0.0)
        );
        expectPointIntersection(
            Segment({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}), Plane({1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}), Point(1.0, 0.0, 0.0)
        );

        expectSegmentIntersection(
            Segment({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}),
            Plane({0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}),
            Segment({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0})
        );
        expectSegmentIntersection(
            Segment({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}),
            Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}),
            Segment({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0})
        );

        expectPointIntersection(
            Segment({1.0, 2.0, 3.0}, {2.0, 2.0, 3.0}), Plane({1.0, 2.0, 3.0}, {1.0, 0.0, 0.0}), Point(1.0, 2.0, 3.0)
        );
        expectPointIntersection(
            Segment({1.0, 2.0, 3.0}, {2.0, 2.0, 3.0}), Plane({2.0, 2.0, 3.0}, {1.0, 0.0, 0.0}), Point(2.0, 2.0, 3.0)
        );

        expectSegmentIntersection(
            Segment({1.0, 2.0, 3.0}, {2.0, 2.0, 3.0}),
            Plane({1.0, 2.0, 3.0}, {0.0, 1.0, 0.0}),
            Segment({1.0, 2.0, 3.0}, {2.0, 2.0, 3.0})
        );
        expectSegmentIntersection(
            Segment({1.0, 2.0, 3.0}, {2.0, 2.0, 3.0}),
            Plane({1.0, 2.0, 3.0}, {0.0, 0.0, 1.0}),
            Segment({1.0, 2.0, 3.0}, {2.0, 2.0, 3.0})
        );

        expectPointIntersection(
            Segment({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}), Plane({+1.0, +2.0, +3.0}, {1.0, 0.0, 0.0}), Point(+1.0, 0.0, 0.0)
        );
    }

    {
        expectEmptyIntersection(Segment({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}), Plane({+1.0, +2.0, +3.0}, {0.0, 1.0, 0.0}));
        expectEmptyIntersection(Segment({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}), Plane({+1.0, +2.0, +3.0}, {0.0, 0.0, 1.0}));

        expectEmptyIntersection(Segment({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}), Plane({-1.0, -2.0, -3.0}, {0.0, 1.0, 0.0}));
        expectEmptyIntersection(Segment({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}), Plane({-1.0, -2.0, -3.0}, {0.0, 0.0, 1.0}));

        expectEmptyIntersection(Segment({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}), Plane({-1.0, -2.0, -3.0}, {1.0, 0.0, 0.0}));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Segment, ToLine)
{
    using ostk::mathematics::geometry::d3::object::Line;
    using ostk::mathematics::geometry::d3::object::Segment;

    {
        EXPECT_EQ(Line({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}), Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).toLine());
        EXPECT_EQ(Line({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}), Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 2.0}).toLine());
    }

    {
        EXPECT_ANY_THROW(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}).toLine());
        EXPECT_ANY_THROW(Segment({1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}).toLine());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Segment, ApplyTransformation)
{
    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::geometry::d3::Transformation;
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;
    using ostk::mathematics::object::Vector3d;

    // Translation

    {
        Segment segment = {{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}};

        segment.applyTransformation(Transformation::Translation({4.0, 5.0, 6.0}));

        EXPECT_EQ(Segment({4.0, 5.0, 6.0}, {4.0, 5.0, 7.0}), segment);
    }

    // Rotation

    {
        Segment segment = {{0.0, 0.5, 0.0}, {0.0, 1.0, 0.0}};

        segment.applyTransformation(Transformation::Rotation(RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(90.0))));

        const Segment referenceSegment = {{0.0, 0.0, 0.5}, {0.0, 0.0, 1.0}};

        EXPECT_TRUE(segment.getFirstPoint().isNear(referenceSegment.getFirstPoint(), 1e-15));
        EXPECT_TRUE(segment.getSecondPoint().isNear(referenceSegment.getSecondPoint(), 1e-15));
    }
}
