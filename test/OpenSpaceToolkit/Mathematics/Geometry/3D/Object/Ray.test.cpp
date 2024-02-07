/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ray.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Sphere.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ray, Constructor)
{
    using ostk::mathematics::geometry::d3::object::Ray;

    {
        EXPECT_NO_THROW(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ray, Clone)
{
    using ostk::mathematics::geometry::d3::object::Ray;

    {
        EXPECT_NO_THROW(const Ray* rayPtr = Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).clone(); delete rayPtr;);
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ray, EqualToOperator)
{
    using ostk::mathematics::geometry::d3::object::Ray;

    {
        EXPECT_TRUE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) == Ray({0.0, 0.0, +0.0}, {0.0, 0.0, +1.0}));
        EXPECT_TRUE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) == Ray({0.0, 0.0, +0.0}, {0.0, 0.0, +2.0}));
    }

    {
        EXPECT_FALSE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) == Ray({0.0, 0.0, +1.0}, {0.0, 0.0, +1.0}));
        EXPECT_FALSE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) == Ray({0.0, 0.0, +1.0}, {0.0, 0.0, +2.0}));

        EXPECT_FALSE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) == Ray({0.0, 0.0, -1.0}, {0.0, 0.0, +1.0}));
        EXPECT_FALSE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) == Ray({0.0, 0.0, 0.0}, {0.0, 0.0, -1.0}));
    }

    {
        EXPECT_FALSE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) == Ray::Undefined());
        EXPECT_FALSE(Ray::Undefined() == Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}));
        EXPECT_FALSE(Ray::Undefined() == Ray::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ray, NotEqualToOperator)
{
    using ostk::mathematics::geometry::d3::object::Ray;

    {
        EXPECT_FALSE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) != Ray({0.0, 0.0, +0.0}, {0.0, 0.0, +1.0}));
        EXPECT_FALSE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) != Ray({0.0, 0.0, +0.0}, {0.0, 0.0, +2.0}));
    }

    {
        EXPECT_TRUE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) != Ray({0.0, 0.0, +1.0}, {0.0, 0.0, +1.0}));
        EXPECT_TRUE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) != Ray({0.0, 0.0, +1.0}, {0.0, 0.0, +2.0}));

        EXPECT_TRUE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) != Ray({0.0, 0.0, -1.0}, {0.0, 0.0, +1.0}));
        EXPECT_TRUE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) != Ray({0.0, 0.0, 0.0}, {0.0, 0.0, -1.0}));
    }

    {
        EXPECT_TRUE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) != Ray({0.0, 0.0, -1.0}, {0.0, 0.0, +1.0}));
        EXPECT_TRUE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) != Ray({0.0, 0.0, 0.0}, {0.0, 0.0, -1.0}));
    }

    {
        EXPECT_TRUE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) != Ray::Undefined());
        EXPECT_TRUE(Ray::Undefined() != Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}));
        EXPECT_TRUE(Ray::Undefined() != Ray::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ray, StreamOperator)
{
    using ostk::mathematics::geometry::d3::object::Ray;

    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}) << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ray, IsDefined)
{
    using ostk::mathematics::geometry::d3::object::Ray;

    {
        EXPECT_TRUE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).isDefined());
    }

    {
        EXPECT_FALSE(Ray::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ray, Intersects_Point)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Ray;

    {
        EXPECT_TRUE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersects(Point(0.0, 0.0, 0.0)));
        EXPECT_TRUE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersects(Point(0.0, 0.0, +1.0)));
        EXPECT_TRUE(Ray({1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersects(Point(1.0, 0.0, 0.0)));
        EXPECT_TRUE(Ray({1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersects(Point(1.0, 0.0, +1.0)));
    }

    {
        EXPECT_FALSE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersects(Point(0.0, 0.0, -1.0)));
        EXPECT_FALSE(Ray({1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersects(Point(1.0, 0.0, -1.0)));
        EXPECT_FALSE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersects(Point(1.0, 0.0, 0.0)));
        EXPECT_FALSE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersects(Point(0.0, 1.0, 0.0)));
    }

    {
        EXPECT_ANY_THROW(Ray::Undefined().intersects(Point::Undefined()));
        EXPECT_ANY_THROW(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersects(Point::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ray, Intersects_Plane)
{
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Plane;

    {
        EXPECT_TRUE(Ray({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}).intersects(Plane({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0})));
        EXPECT_TRUE(Ray({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}).intersects(Plane({0.0, 0.0, 0.0}, {0.0, 1.0, 0.0})));
        EXPECT_TRUE(Ray({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}).intersects(Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0})));

        EXPECT_TRUE(Ray({1.0, 2.0, 3.0}, {1.0, 0.0, 0.0}).intersects(Plane({1.0, 2.0, 3.0}, {1.0, 0.0, 0.0})));
        EXPECT_TRUE(Ray({1.0, 2.0, 3.0}, {1.0, 0.0, 0.0}).intersects(Plane({1.0, 2.0, 3.0}, {0.0, 1.0, 0.0})));
        EXPECT_TRUE(Ray({1.0, 2.0, 3.0}, {1.0, 0.0, 0.0}).intersects(Plane({1.0, 2.0, 3.0}, {0.0, 0.0, 1.0})));

        EXPECT_TRUE(Ray({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}).intersects(Plane({+1.0, +2.0, +3.0}, {1.0, 0.0, 0.0})));
    }

    {
        EXPECT_FALSE(Ray({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}).intersects(Plane({+1.0, +2.0, +3.0}, {0.0, 1.0, 0.0})));
        EXPECT_FALSE(Ray({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}).intersects(Plane({+1.0, +2.0, +3.0}, {0.0, 0.0, 1.0})));

        EXPECT_FALSE(Ray({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}).intersects(Plane({-1.0, -2.0, -3.0}, {0.0, 1.0, 0.0})));
        EXPECT_FALSE(Ray({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}).intersects(Plane({-1.0, -2.0, -3.0}, {0.0, 0.0, 1.0})));

        EXPECT_FALSE(Ray({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}).intersects(Plane({-1.0, -2.0, -3.0}, {1.0, 0.0, 0.0})));
    }

    {
        EXPECT_ANY_THROW(Ray::Undefined().intersects(Plane::Undefined()));
        EXPECT_ANY_THROW(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersects(Plane::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ray, Intersects_Sphere)
{
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Sphere;

    {
        // See: OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Sphere.Intersects_Ray

        SUCCEED();
    }

    {
        EXPECT_ANY_THROW(Ray::Undefined().intersects(Sphere::Undefined()));
        EXPECT_ANY_THROW(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersects(Sphere::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ray, Intersects_Ellipsoid)
{
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Ellipsoid;

    {
        // See: OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ellipsoid.Intersects_Ray

        SUCCEED();
    }

    {
        EXPECT_ANY_THROW(Ray::Undefined().intersects(Ellipsoid::Undefined()));
        EXPECT_ANY_THROW(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersects(Ellipsoid::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ray, Contains_Point)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Ray;

    {
        EXPECT_TRUE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Point(0.0, 0.0, +0.0)));
        EXPECT_TRUE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Point(0.0, 0.0, +0.5)));
        EXPECT_TRUE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Point(0.0, 0.0, +1.0)));
        EXPECT_TRUE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Point(0.0, 0.0, +2.0)));
    }

    {
        EXPECT_FALSE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Point(0.0, 0.0, -2.0)));
        EXPECT_FALSE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Point(0.0, 0.0, -1.0)));
        EXPECT_FALSE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Point(0.0, 0.0, -0.5)));
        EXPECT_FALSE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Point(1.0, 0.0, 0.0)));
    }

    {
        EXPECT_ANY_THROW(Ray::Undefined().contains(Point::Undefined()));
        EXPECT_ANY_THROW(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(Point::Undefined()));
        EXPECT_ANY_THROW(Ray::Undefined().contains(Point(0.0, 0.0, 0.0)));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ray, Contains_PointSet)
{
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Ray;

    {
        EXPECT_TRUE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(PointSet({{0.0, 0.0, 0.0}})));
        EXPECT_TRUE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).contains(PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}})));
        EXPECT_TRUE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0})
                        .contains(PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.5}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}})));
    }

    {
        EXPECT_FALSE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0})
                         .contains(PointSet({{0.0, 0.0, -1.0}, {0.0, 0.0, 0.5}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}})));
        EXPECT_FALSE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0})
                         .contains(PointSet({{0.0, 0.0, -2.0}, {0.0, 0.0, 0.5}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}})));
        EXPECT_FALSE(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0})
                         .contains(PointSet({{-1.0, 0.0, 0.0}, {0.0, 0.0, 0.5}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}})));
    }

    {
        EXPECT_ANY_THROW(Ray::Undefined().contains(PointSet::Empty()));
        EXPECT_ANY_THROW(Ray::Undefined().contains(PointSet({{0.0, 0.0, 0.0}})));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ray, GetOrigin)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Ray;

    {
        EXPECT_EQ(Point(0.0, 0.0, 0.0), Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).getOrigin());
        EXPECT_EQ(Point(0.0, 0.0, 1.0), Ray({0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}).getOrigin());

        EXPECT_EQ(Point(0.0, 0.0, -1.0), Ray({0.0, 0.0, -1.0}, {0.0, 0.0, +1.0}).getOrigin());
    }

    {
        EXPECT_ANY_THROW(Ray::Undefined().getOrigin());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ray, GetDirection)
{
    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Ray;

    {
        EXPECT_EQ(Vector3d(0.0, 0.0, +1.0), Ray({0.0, 0.0, 0.0}, {0.0, 0.0, +2.0}).getDirection());
        EXPECT_EQ(Vector3d(0.0, 0.0, -1.0), Ray({0.0, 0.0, 0.0}, {0.0, 0.0, -2.0}).getDirection());
    }

    {
        EXPECT_ANY_THROW(Ray::Undefined().getDirection());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ray, DistanceTo_Point)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Ray;

    {
        EXPECT_EQ(0.0, Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).distanceTo(Point(0.0, 0.0, 0.0)));

        EXPECT_EQ(0.0, Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).distanceTo(Point(0.0, 0.0, +1.0)));
        EXPECT_EQ(0.0, Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).distanceTo(Point(0.0, 0.0, +2.0)));

        EXPECT_EQ(1.0, Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).distanceTo(Point(+1.0, 0.0, 0.0)));
        EXPECT_EQ(1.0, Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).distanceTo(Point(-1.0, 0.0, 0.0)));
        EXPECT_EQ(1.0, Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).distanceTo(Point(0.0, +1.0, 0.0)));
        EXPECT_EQ(1.0, Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).distanceTo(Point(0.0, -1.0, 0.0)));

        EXPECT_EQ(1.0, Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).distanceTo(Point(0.0, 0.0, -1.0)));
        EXPECT_EQ(2.0, Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).distanceTo(Point(0.0, 0.0, -2.0)));
    }

    {
        EXPECT_ANY_THROW(Ray::Undefined().distanceTo(Point::Undefined()));
        EXPECT_ANY_THROW(Ray::Undefined().distanceTo({0.0, 0.0, 0.0}));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ray, IntersectionWith_Plane)
{
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::Intersection;

    const auto expectRayIntersection = [](const Ray& aRay, const Plane& aPlane, const Ray& anIntersectionRay) -> void
    {
        const Intersection intersection = aRay.intersectionWith(aPlane);

        EXPECT_TRUE(intersection.isDefined());

        ASSERT_TRUE(intersection.accessComposite().is<Ray>());

        const Ray ray = intersection.accessComposite().as<Ray>();

        EXPECT_EQ(anIntersectionRay, ray);
    };

    const auto expectPointIntersection = [](const Ray& aRay, const Plane& aPlane, const Point& anIntersectionPoint
                                         ) -> void
    {
        const Intersection intersection = aRay.intersectionWith(aPlane);

        EXPECT_TRUE(intersection.isDefined());

        ASSERT_TRUE(intersection.accessComposite().is<Point>());

        const Point point = intersection.accessComposite().as<Point>();

        EXPECT_TRUE(point.isNear(anIntersectionPoint, Real::Epsilon()));
    };

    const auto expectEmptyIntersection = [](const Ray& aRay, const Plane& aPlane) -> void
    {
        const Intersection intersection = aRay.intersectionWith(aPlane);

        EXPECT_TRUE(intersection.isDefined());
        EXPECT_TRUE(intersection.isEmpty());
    };

    {
        expectPointIntersection(
            Ray({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}), Plane({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}), Point(0.0, 0.0, 0.0)
        );
        expectRayIntersection(
            Ray({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}),
            Plane({0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}),
            Ray({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0})
        );
        expectRayIntersection(
            Ray({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}),
            Plane({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}),
            Ray({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0})
        );

        expectPointIntersection(
            Ray({1.0, 2.0, 3.0}, {1.0, 0.0, 0.0}), Plane({1.0, 2.0, 3.0}, {1.0, 0.0, 0.0}), Point(1.0, 2.0, 3.0)
        );
        expectRayIntersection(
            Ray({1.0, 2.0, 3.0}, {1.0, 0.0, 0.0}),
            Plane({1.0, 2.0, 3.0}, {0.0, 1.0, 0.0}),
            Ray({1.0, 2.0, 3.0}, {1.0, 0.0, 0.0})
        );
        expectRayIntersection(
            Ray({1.0, 2.0, 3.0}, {1.0, 0.0, 0.0}),
            Plane({1.0, 2.0, 3.0}, {0.0, 0.0, 1.0}),
            Ray({1.0, 2.0, 3.0}, {1.0, 0.0, 0.0})
        );

        expectPointIntersection(
            Ray({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}), Plane({+1.0, +2.0, +3.0}, {1.0, 0.0, 0.0}), Point(+1.0, 0.0, 0.0)
        );
    }

    {
        expectEmptyIntersection(Ray({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}), Plane({+1.0, +2.0, +3.0}, {0.0, 1.0, 0.0}));
        expectEmptyIntersection(Ray({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}), Plane({+1.0, +2.0, +3.0}, {0.0, 0.0, 1.0}));

        expectEmptyIntersection(Ray({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}), Plane({-1.0, -2.0, -3.0}, {0.0, 1.0, 0.0}));
        expectEmptyIntersection(Ray({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}), Plane({-1.0, -2.0, -3.0}, {0.0, 0.0, 1.0}));

        expectEmptyIntersection(Ray({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}), Plane({-1.0, -2.0, -3.0}, {1.0, 0.0, 0.0}));
    }

    {
        EXPECT_ANY_THROW(Ray::Undefined().intersectionWith(Plane::Undefined()));
        EXPECT_ANY_THROW(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).intersectionWith(Plane::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ray, IntersectionWith_Ellipsoid)
{
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Ellipsoid;

    {
        // See: OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ellipsoid.IntersectionWith_Ray

        SUCCEED();
    }

    {
        EXPECT_ANY_THROW(Ray::Undefined().intersectionWith(Ellipsoid::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ray, ApplyTransformation)
{
    using ostk::core::type::Real;

    using ostk::mathematics::object::Vector3d;
    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::Transformation;
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;

    // Translation

    {
        Ray ray = {{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}};

        ray.applyTransformation(Transformation::Translation({4.0, 5.0, 6.0}));

        EXPECT_EQ(Ray({4.0, 5.0, 6.0}, {0.0, 0.0, 1.0}), ray);
    }

    // Rotation

    {
        Ray ray = {{0.0, 0.5, 0.0}, {0.0, 0.0, +1.0}};

        ray.applyTransformation(Transformation::Rotation(RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(90.0))));

        const Ray referenceRay = {{0.0, 0.0, 0.5}, {0.0, -1.0, 0.0}};

        EXPECT_TRUE(ray.getOrigin().isNear(referenceRay.getOrigin(), Real::Epsilon()));
        EXPECT_TRUE(ray.getDirection().isNear(referenceRay.getDirection(), Real::Epsilon()));
    }

    {
        EXPECT_ANY_THROW(Ray::Undefined().applyTransformation(Transformation::Undefined()));
        EXPECT_ANY_THROW(Ray::Undefined().applyTransformation(Transformation::Identity()));
        EXPECT_ANY_THROW(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}).applyTransformation(Transformation::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ray, Undefined)
{
    using ostk::mathematics::geometry::d3::object::Ray;

    {
        EXPECT_NO_THROW(Ray::Undefined());
        EXPECT_FALSE(Ray::Undefined().isDefined());
    }
}
