/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Sphere.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Segment, Constructor)
{
    using ostk::math::geometry::d3::objects::Segment;

    {
        EXPECT_NO_THROW(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Segment, Clone)
{
    using ostk::math::geometry::d3::objects::Segment;

    {
        EXPECT_NO_THROW(const Segment* segmentPtr = Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).clone();
                        delete segmentPtr;);
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Segment, EqualToOperator)
{
    using ostk::math::geometry::d3::objects::Segment;

    {
        EXPECT_TRUE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) == Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}));
        EXPECT_TRUE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) == Segment({0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}));
    }

    {
        EXPECT_FALSE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) == Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 2.0}));
    }

    {
        EXPECT_FALSE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) == Segment::Undefined());
        EXPECT_FALSE(Segment::Undefined() == Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}));
        EXPECT_FALSE(Segment::Undefined() == Segment::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Segment, NotEqualToOperator)
{
    using ostk::math::geometry::d3::objects::Segment;

    {
        EXPECT_FALSE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) != Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}));
        EXPECT_FALSE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) != Segment({0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}));
    }

    {
        EXPECT_TRUE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) != Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 2.0}));
    }

    {
        EXPECT_TRUE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) != Segment::Undefined());
        EXPECT_TRUE(Segment::Undefined() != Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}));
        EXPECT_TRUE(Segment::Undefined() != Segment::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Segment, StreamOperator)
{
    using ostk::math::geometry::d3::objects::Segment;

    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Segment, IsDefined)
{
    using ostk::math::geometry::d3::objects::Segment;

    {
        EXPECT_TRUE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}).isDefined());
        EXPECT_TRUE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).isDefined());
    }

    {
        EXPECT_FALSE(Segment::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Segment, IsDegenerate)
{
    using ostk::math::geometry::d3::objects::Segment;

    {
        EXPECT_TRUE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}).isDegenerate());
        EXPECT_TRUE(Segment({1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}).isDegenerate());
    }

    {
        EXPECT_FALSE(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).isDegenerate());
        EXPECT_FALSE(Segment({1.0, 2.0, 3.0}, {0.0, 0.0, 1.0}).isDegenerate());
    }

    {
        EXPECT_ANY_THROW(Segment::Undefined().isDegenerate());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Segment, Intersects_Plane)
{
    using ostk::math::geometry::d3::objects::Segment;
    using ostk::math::geometry::d3::objects::Plane;

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

    {
        EXPECT_ANY_THROW(Segment::Undefined().intersects(Plane::Undefined()));
        EXPECT_ANY_THROW(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersects(Plane::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Segment, Intersects_Sphere)
{
    using ostk::math::geometry::d3::objects::Segment;
    using ostk::math::geometry::d3::objects::Sphere;

    {
        // See: OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Sphere.Intersects

        SUCCEED();
    }

    {
        EXPECT_ANY_THROW(Segment::Undefined().intersects(Sphere::Undefined()));
        EXPECT_ANY_THROW(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}).intersects(Sphere::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Segment, Intersects_Ellipsoid)
{
    using ostk::math::geometry::d3::objects::Segment;
    using ostk::math::geometry::d3::objects::Ellipsoid;

    {
        // See: OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Ellipsoid.Intersects

        SUCCEED();
    }

    {
        EXPECT_ANY_THROW(Segment::Undefined().intersects(Ellipsoid::Undefined()));
        EXPECT_ANY_THROW(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}).intersects(Ellipsoid::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Segment, Contains_Point)
{
    using ostk::math::geometry::d3::objects::Point;
    using ostk::math::geometry::d3::objects::Segment;

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

    {
        EXPECT_ANY_THROW(Segment::Undefined().contains(Point::Undefined()));
        EXPECT_ANY_THROW(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}).contains(Point::Undefined()));
        EXPECT_ANY_THROW(Segment::Undefined().contains(Point(0.0, 0.0, 0.0)));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Segment, GetCenter)
{
    using ostk::math::geometry::d3::objects::Point;
    using ostk::math::geometry::d3::objects::Segment;

    {
        EXPECT_EQ(Point(0.0, 0.0, 0.0), Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}).getCenter());
        EXPECT_EQ(Point(0.0, 0.0, 1.0), Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 2.0}).getCenter());

        EXPECT_EQ(Point(0.0, 0.0, 0.0), Segment({0.0, 0.0, -1.0}, {0.0, 0.0, +1.0}).getCenter());
    }

    {
        EXPECT_ANY_THROW(Segment::Undefined().getCenter());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Segment, GetDirection)
{
    using ostk::math::object::Vector3d;
    using ostk::math::geometry::d3::objects::Point;
    using ostk::math::geometry::d3::objects::Segment;

    {
        EXPECT_EQ(Vector3d(0.0, 0.0, +1.0), Segment({0.0, 0.0, 0.0}, {0.0, 0.0, +2.0}).getDirection());
        EXPECT_EQ(Vector3d(0.0, 0.0, -1.0), Segment({0.0, 0.0, 0.0}, {0.0, 0.0, -2.0}).getDirection());
    }

    {
        EXPECT_ANY_THROW(Segment::Undefined().getDirection());

        EXPECT_ANY_THROW(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}).getDirection());
        EXPECT_ANY_THROW(Segment({1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}).getDirection());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Segment, GetLength)
{
    using ostk::math::geometry::d3::objects::Point;
    using ostk::math::geometry::d3::objects::Segment;

    {
        EXPECT_EQ(0.0, Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}).getLength());
        EXPECT_EQ(0.0, Segment({1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}).getLength());

        EXPECT_EQ(1.0, Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).getLength());
        EXPECT_EQ(2.0, Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 2.0}).getLength());

        EXPECT_EQ(4.0, Segment({0.0, 0.0, -2.0}, {0.0, 0.0, +2.0}).getLength());
    }

    {
        EXPECT_ANY_THROW(Segment::Undefined().getLength());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Segment, DistanceToPoint)
{
    using ostk::math::geometry::d3::objects::Point;
    using ostk::math::geometry::d3::objects::Segment;

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

    {
        EXPECT_ANY_THROW(Segment::Undefined().distanceTo(Point({0.0, 0.0, 0.0})));
        EXPECT_ANY_THROW(Segment({0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}).distanceTo(Point::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Segment, DistanceToPointSet)
{
    using ostk::math::geometry::d3::objects::Point;
    using ostk::math::geometry::d3::objects::PointSet;
    using ostk::math::geometry::d3::objects::Segment;

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
        EXPECT_ANY_THROW(Segment::Undefined().distanceTo(PointSet({{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}})));
        EXPECT_ANY_THROW(Segment({0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}).distanceTo(PointSet::Empty()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Segment, IntersectionWith_Plane)
{
    using ostk::core::type::Real;

    using ostk::math::geometry::d3::objects::Point;
    using ostk::math::geometry::d3::objects::Segment;
    using ostk::math::geometry::d3::objects::Plane;
    using ostk::math::geometry::d3::Intersection;

    const auto expectSegmentIntersection =
        [](const Segment& aSegment, const Plane& aPlane, const Segment& anIntersectionSegment) -> void
    {
        const Intersection intersection = aSegment.intersectionWith(aPlane);

        EXPECT_TRUE(intersection.isDefined());

        ASSERT_TRUE(intersection.accessComposite().is<Segment>());

        const Segment segment = intersection.accessComposite().as<Segment>();

        EXPECT_EQ(anIntersectionSegment, segment);
    };

    const auto expectPointIntersection =
        [](const Segment& aSegment, const Plane& aPlane, const Point& anIntersectionPoint) -> void
    {
        const Intersection intersection = aSegment.intersectionWith(aPlane);

        EXPECT_TRUE(intersection.isDefined());

        ASSERT_TRUE(intersection.accessComposite().is<Point>());

        const Point point = intersection.accessComposite().as<Point>();

        EXPECT_TRUE(point.isNear(anIntersectionPoint, Real::Epsilon()));
    };

    const auto expectEmptyIntersection = [](const Segment& aSegment, const Plane& aPlane) -> void
    {
        const Intersection intersection = aSegment.intersectionWith(aPlane);

        EXPECT_TRUE(intersection.isDefined());
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

    {
        EXPECT_ANY_THROW(Segment::Undefined().intersectionWith(Plane::Undefined()));
        EXPECT_ANY_THROW(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersectionWith(Plane::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Segment, ToLine)
{
    using ostk::math::geometry::d3::objects::Line;
    using ostk::math::geometry::d3::objects::Segment;

    {
        EXPECT_EQ(Line({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}), Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).toLine());
        EXPECT_EQ(Line({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}), Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 2.0}).toLine());
    }

    {
        EXPECT_ANY_THROW(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}).toLine());
        EXPECT_ANY_THROW(Segment({1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}).toLine());
    }

    {
        EXPECT_ANY_THROW(Segment::Undefined().toLine());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Segment, ApplyTransformation)
{
    using ostk::core::type::Real;

    using ostk::math::object::Vector3d;
    using ostk::math::geometry::Angle;
    using ostk::math::geometry::d3::objects::Segment;
    using ostk::math::geometry::d3::Transformation;
    using ostk::math::geometry::d3::transformation::rotation::RotationVector;

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

        EXPECT_TRUE(segment.getFirstPoint().isNear(referenceSegment.getFirstPoint(), Real::Epsilon()));
        EXPECT_TRUE(segment.getSecondPoint().isNear(referenceSegment.getSecondPoint(), Real::Epsilon()));
    }

    {
        EXPECT_ANY_THROW(Segment::Undefined().applyTransformation(Transformation::Undefined()));
        EXPECT_ANY_THROW(Segment::Undefined().applyTransformation(Transformation::Identity()));
        EXPECT_ANY_THROW(Segment({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).applyTransformation(Transformation::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Segment, Undefined)
{
    using ostk::math::geometry::d3::objects::Segment;

    {
        EXPECT_NO_THROW(Segment::Undefined());
        EXPECT_FALSE(Segment::Undefined().isDefined());
    }
}
