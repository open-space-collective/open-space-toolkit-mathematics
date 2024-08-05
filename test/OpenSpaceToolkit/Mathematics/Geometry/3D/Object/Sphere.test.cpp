/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Line.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Plane.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/PointSet.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Pyramid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ray.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Sphere.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Sphere, Constructor)
{
    using ostk::mathematics::geometry::d3::object::Sphere;

    {
        EXPECT_NO_THROW(Sphere({1.0, 2.0, 3.0}, 4.0));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Sphere, Clone)
{
    using ostk::mathematics::geometry::d3::object::Sphere;

    {
        EXPECT_NO_THROW(const Sphere* spherePtr = Sphere({1.0, 2.0, 3.0}, 4.0).clone(); delete spherePtr;);
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Sphere, EqualToOperator)
{
    using ostk::mathematics::geometry::d3::object::Sphere;

    {
        EXPECT_TRUE(Sphere({1.0, 2.0, 3.0}, 4.0) == Sphere({1.0, 2.0, 3.0}, 4.0));
    }

    {
        EXPECT_FALSE(Sphere({1.0, 2.0, 3.0}, 4.0) == Sphere({1.0, 2.0, 4.0}, 4.0));
        EXPECT_FALSE(Sphere({1.0, 2.0, 3.0}, 4.0) == Sphere({1.0, 2.0, 3.0}, 3.0));
    }

    {
        EXPECT_FALSE(Sphere({1.0, 2.0, 3.0}, 4.0) == Sphere::Undefined());
        EXPECT_FALSE(Sphere::Undefined() == Sphere({1.0, 2.0, 3.0}, 4.0));
        EXPECT_FALSE(Sphere::Undefined() == Sphere::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Sphere, NotEqualToOperator)
{
    using ostk::mathematics::geometry::d3::object::Sphere;

    {
        EXPECT_TRUE(Sphere({1.0, 2.0, 3.0}, 4.0) != Sphere({1.0, 2.0, 4.0}, 4.0));
        EXPECT_TRUE(Sphere({1.0, 2.0, 3.0}, 4.0) != Sphere({1.0, 2.0, 3.0}, 3.0));
    }

    {
        EXPECT_FALSE(Sphere({1.0, 2.0, 3.0}, 4.0) != Sphere({1.0, 2.0, 3.0}, 4.0));
    }

    {
        EXPECT_TRUE(Sphere({1.0, 2.0, 3.0}, 4.0) != Sphere::Undefined());
        EXPECT_TRUE(Sphere::Undefined() != Sphere({1.0, 2.0, 3.0}, 4.0));
        EXPECT_TRUE(Sphere::Undefined() != Sphere::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Sphere, StreamOperator)
{
    using ostk::mathematics::geometry::d3::object::Sphere;

    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << Sphere({0.0, 0.0, 0.0}, 1.0) << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Sphere, IsDefined)
{
    using ostk::mathematics::geometry::d3::object::Sphere;

    {
        EXPECT_TRUE(Sphere({0.0, 0.0, 0.0}, 1.0).isDefined());
        EXPECT_TRUE(Sphere({1.0, 2.0, 3.0}, 4.0).isDefined());
    }

    {
        EXPECT_FALSE(Sphere::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Sphere, IsUnitary)
{
    using ostk::mathematics::geometry::d3::object::Sphere;

    {
        EXPECT_TRUE(Sphere({0.0, 0.0, 0.0}, 1.0).isUnitary());
        EXPECT_TRUE(Sphere({1.0, 2.0, 3.0}, 1.0).isUnitary());
    }

    {
        EXPECT_FALSE(Sphere({0.0, 0.0, 0.0}, 1.1).isUnitary());
        EXPECT_FALSE(Sphere({1.0, 2.0, 3.0}, 0.9).isUnitary());
    }

    {
        EXPECT_ANY_THROW(Sphere::Undefined().isUnitary());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Sphere, Intersects_Point)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Sphere;

    {
        EXPECT_TRUE(Sphere({1.0, 2.0, 3.0}, 4.0).intersects(Point(+5.0, +2.0, +3.0)));
        EXPECT_TRUE(Sphere({1.0, 2.0, 3.0}, 4.0).intersects(Point(-3.0, +2.0, +3.0)));

        EXPECT_TRUE(Sphere({1.0, 2.0, 3.0}, 4.0).intersects(Point(+1.0, +6.0, +3.0)));
        EXPECT_TRUE(Sphere({1.0, 2.0, 3.0}, 4.0).intersects(Point(+1.0, -2.0, +3.0)));

        EXPECT_TRUE(Sphere({1.0, 2.0, 3.0}, 4.0).intersects(Point(+1.0, +2.0, +7.0)));
        EXPECT_TRUE(Sphere({1.0, 2.0, 3.0}, 4.0).intersects(Point(+1.0, +2.0, -1.0)));
    }

    {
        EXPECT_FALSE(Sphere(Point::Origin(), 4.0).intersects(Point::Origin()));
    }

    {
        EXPECT_ANY_THROW(Sphere::Undefined().intersects(Point::Undefined()));
        EXPECT_ANY_THROW(Sphere({1.0, 2.0, 3.0}, 4.0).intersects(Point::Undefined()));
        EXPECT_ANY_THROW(Sphere::Undefined().intersects(Point(0.0, 0.0, 0.0)));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Sphere, Intersects_PointSet)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Sphere;

    {
        EXPECT_TRUE(Sphere({1.0, 2.0, 3.0}, 4.0)
                        .intersects(PointSet(
                            {{+5.0, +2.0, +3.0},
                             {-3.0, +2.0, +3.0},
                             {+1.0, +6.0, +3.0},
                             {+1.0, -2.0, +3.0},
                             {+1.0, +2.0, +7.0},
                             {+1.0, +2.0, -1.0}}
                        )));
        EXPECT_TRUE(Sphere({1.0, 2.0, 3.0}, 4.0).intersects(PointSet({{0.0, 0.0, 0.0}, {+5.0, +2.0, +3.0}})));
    }

    {
        EXPECT_FALSE(Sphere(Point::Origin(), 4.0).intersects(PointSet::Empty()));
    }

    {
        EXPECT_ANY_THROW(Sphere::Undefined().intersects(PointSet::Empty()));
        EXPECT_ANY_THROW(Sphere::Undefined().intersects(PointSet({{+5.0, +2.0, +3.0}, {+5.0, +2.0, +3.0}})));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Sphere, Intersects_Line)
{
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::d3::object::Line;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Sphere;

    {
        const Sphere sphere = {Point::Origin(), 2.0};

        EXPECT_FALSE(sphere.intersects(Line({-10.0, -3.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({-10.0, -2.1, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({-10.0, -2.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({-10.0, -1.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({-10.0, +0.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({-10.0, +1.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({-10.0, +2.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({-10.0, +2.1, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({-10.0, +3.0, 0.0}, {+1.0, 0.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Line({+0.0, -3.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({+0.0, -2.1, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+0.0, -2.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+0.0, -1.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+0.0, +0.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+0.0, +1.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+0.0, +2.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({+0.0, +2.1, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({+0.0, +3.0, 0.0}, {+1.0, 0.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Line({+10.0, -3.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({+10.0, -2.1, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+10.0, -2.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+10.0, -1.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+10.0, +0.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+10.0, +1.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+10.0, +2.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({+10.0, +2.1, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({+10.0, +3.0, 0.0}, {+1.0, 0.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Line({-10.0, -3.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({-10.0, -2.1, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({-10.0, -2.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({-10.0, -1.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({-10.0, +0.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({-10.0, +1.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({-10.0, +2.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({-10.0, +2.1, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({-10.0, +3.0, 0.0}, {-1.0, 0.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Line({+0.0, -3.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({+0.0, -2.1, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+0.0, -2.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+0.0, -1.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+0.0, +0.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+0.0, +1.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+0.0, +2.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({+0.0, +2.1, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({+0.0, +3.0, 0.0}, {-1.0, 0.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Line({+10.0, -3.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({+10.0, -2.1, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+10.0, -2.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+10.0, -1.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+10.0, +0.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+10.0, +1.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+10.0, +2.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({+10.0, +2.1, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({+10.0, +3.0, 0.0}, {-1.0, 0.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Line({-3.0, -10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({-2.1, -10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({-2.0, -10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({-1.0, -10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+0.0, -10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+1.0, -10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+2.0, -10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({+2.1, -10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({+3.0, -10.0, 0.0}, {0.0, +1.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Line({-3.0, +0.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({-2.1, +0.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({-2.0, +0.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({-1.0, +0.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+0.0, +0.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+1.0, +0.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+2.0, +0.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({+2.1, +0.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({+3.0, +0.0, 0.0}, {0.0, +1.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Line({-3.0, +10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({-2.1, +10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({-2.0, +10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({-1.0, +10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+0.0, +10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+1.0, +10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+2.0, +10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({+2.1, +10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({+3.0, +10.0, 0.0}, {0.0, +1.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Line({-3.0, -10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({-2.1, -10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({-2.0, -10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({-1.0, -10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+0.0, -10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+1.0, -10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+2.0, -10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({+2.1, -10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({+3.0, -10.0, 0.0}, {0.0, -1.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Line({-3.0, +0.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({-2.1, +0.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({-2.0, +0.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({-1.0, +0.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+0.0, +0.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+1.0, +0.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+2.0, +0.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({+2.1, +0.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({+3.0, +0.0, 0.0}, {0.0, -1.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Line({-3.0, +10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({-2.1, +10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({-2.0, +10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({-1.0, +10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+0.0, +10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+1.0, +10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({+2.0, +10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({+2.1, +10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({+3.0, +10.0, 0.0}, {0.0, -1.0, 0.0})));
    }

    {
        const Real equatorialRadius_m = 6378136.3;

        const Sphere sphere = {Point::Origin(), equatorialRadius_m};

        EXPECT_FALSE(sphere.intersects(Line({0.0, -7000e3, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({0.0, -equatorialRadius_m - 0.1, 0.0}, {+1.0, 0.0, 0.0})));
        // EXPECT_TRUE(sphere.intersects(Line({ 0.0, -equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ; // [TBI] Fix
        // precision issues
        EXPECT_TRUE(sphere.intersects(Line({0.0, -equatorialRadius_m + 0.1, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({0.0, +0.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Line({0.0, +equatorialRadius_m - 0.1, 0.0}, {+1.0, 0.0, 0.0})));
        // EXPECT_TRUE(sphere.intersects(Line({ 0.0, +equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ; // [TBI] Fix
        // precision issues
        EXPECT_FALSE(sphere.intersects(Line({0.0, +equatorialRadius_m + 0.1, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Line({0.0, +7000e3, 0.0}, {+1.0, 0.0, 0.0})));
    }

    {
        EXPECT_ANY_THROW(Sphere::Undefined().intersects(Line::Undefined()));
        EXPECT_ANY_THROW(Sphere(Point::Origin(), 1.0).intersects(Line::Undefined()));
        EXPECT_ANY_THROW(Sphere::Undefined().intersects(Line({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0})));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Sphere, Intersects_Ray)
{
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Sphere;

    {
        const Sphere sphere = {Point::Origin(), 2.0};

        EXPECT_FALSE(sphere.intersects(Ray({-10.0, -3.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({-10.0, -2.1, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({-10.0, -2.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({-10.0, -1.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({-10.0, +0.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({-10.0, +1.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({-10.0, +2.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({-10.0, +2.1, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({-10.0, +3.0, 0.0}, {+1.0, 0.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Ray({+0.0, -3.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+0.0, -2.1, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+0.0, -2.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+0.0, -1.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+0.0, +0.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+0.0, +1.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+0.0, +2.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+0.0, +2.1, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+0.0, +3.0, 0.0}, {+1.0, 0.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Ray({+10.0, -3.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+10.0, -2.1, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+10.0, -2.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+10.0, -1.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+10.0, +0.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+10.0, +1.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+10.0, +2.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+10.0, +2.1, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+10.0, +3.0, 0.0}, {+1.0, 0.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Ray({-10.0, -3.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({-10.0, -2.1, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({-10.0, -2.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({-10.0, -1.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({-10.0, +0.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({-10.0, +1.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({-10.0, +2.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({-10.0, +2.1, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({-10.0, +3.0, 0.0}, {-1.0, 0.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Ray({+0.0, -3.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+0.0, -2.1, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+0.0, -2.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+0.0, -1.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+0.0, +0.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+0.0, +1.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+0.0, +2.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+0.0, +2.1, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+0.0, +3.0, 0.0}, {-1.0, 0.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Ray({+10.0, -3.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+10.0, -2.1, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+10.0, -2.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+10.0, -1.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+10.0, +0.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+10.0, +1.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+10.0, +2.0, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+10.0, +2.1, 0.0}, {-1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+10.0, +3.0, 0.0}, {-1.0, 0.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Ray({-3.0, -10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({-2.1, -10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({-2.0, -10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({-1.0, -10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+0.0, -10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+1.0, -10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+2.0, -10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+2.1, -10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+3.0, -10.0, 0.0}, {0.0, +1.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Ray({-3.0, +0.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({-2.1, +0.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({-2.0, +0.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({-1.0, +0.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+0.0, +0.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+1.0, +0.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+2.0, +0.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+2.1, +0.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+3.0, +0.0, 0.0}, {0.0, +1.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Ray({-3.0, +10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({-2.1, +10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({-2.0, +10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({-1.0, +10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+0.0, +10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+1.0, +10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+2.0, +10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+2.1, +10.0, 0.0}, {0.0, +1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+3.0, +10.0, 0.0}, {0.0, +1.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Ray({-3.0, -10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({-2.1, -10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({-2.0, -10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({-1.0, -10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+0.0, -10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+1.0, -10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+2.0, -10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+2.1, -10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+3.0, -10.0, 0.0}, {0.0, -1.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Ray({-3.0, +0.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({-2.1, +0.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({-2.0, +0.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({-1.0, +0.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+0.0, +0.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+1.0, +0.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+2.0, +0.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+2.1, +0.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+3.0, +0.0, 0.0}, {0.0, -1.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Ray({-3.0, +10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({-2.1, +10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({-2.0, +10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({-1.0, +10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+0.0, +10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+1.0, +10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({+2.0, +10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+2.1, +10.0, 0.0}, {0.0, -1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+3.0, +10.0, 0.0}, {0.0, -1.0, 0.0})));
    }

    {
        const Real equatorialRadius_m = 6378136.3;

        const Sphere sphere = {Point::Origin(), equatorialRadius_m};

        EXPECT_FALSE(sphere.intersects(Ray({-10000e3, -7000e3, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({-10000e3, -equatorialRadius_m - 0.1, 0.0}, {+1.0, 0.0, 0.0})));
        // EXPECT_TRUE(sphere.intersects(Ray({ -10000e3, -equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ; // [TBI]
        // Fix precision issues
        EXPECT_TRUE(sphere.intersects(Ray({-10000e3, -equatorialRadius_m + 0.1, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({-10000e3, +0.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({-10000e3, +equatorialRadius_m - 0.1, 0.0}, {+1.0, 0.0, 0.0})));
        // EXPECT_TRUE(sphere.intersects(Ray({ -10000e3, +equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ; // [TBI]
        // Fix precision issues
        EXPECT_FALSE(sphere.intersects(Ray({-10000e3, +equatorialRadius_m + 0.1, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({-10000e3, +7000e3, 0.0}, {+1.0, 0.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Ray({0.0, -7000e3, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({0.0, -equatorialRadius_m - 0.1, 0.0}, {+1.0, 0.0, 0.0})));
        // EXPECT_TRUE(sphere.intersects(Ray({ 0.0, -equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ; // [TBI] Fix
        // precision issues
        EXPECT_TRUE(sphere.intersects(Ray({0.0, -equatorialRadius_m + 0.1, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({0.0, +0.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Ray({0.0, +equatorialRadius_m - 0.1, 0.0}, {+1.0, 0.0, 0.0})));
        // EXPECT_TRUE(sphere.intersects(Ray({ 0.0, +equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ; // [TBI] Fix
        // precision issues
        EXPECT_FALSE(sphere.intersects(Ray({0.0, +equatorialRadius_m + 0.1, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({0.0, +7000e3, 0.0}, {+1.0, 0.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Ray({+10000e3, -7000e3, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+10000e3, -equatorialRadius_m - 0.1, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+10000e3, -equatorialRadius_m, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+10000e3, -equatorialRadius_m + 0.1, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+10000e3, +0.0, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+10000e3, +equatorialRadius_m - 0.1, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+10000e3, +equatorialRadius_m, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+10000e3, +equatorialRadius_m + 0.1, 0.0}, {+1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Ray({+10000e3, +7000e3, 0.0}, {+1.0, 0.0, 0.0})));
    }

    {
        EXPECT_ANY_THROW(Sphere::Undefined().intersects(Ray::Undefined()));
        EXPECT_ANY_THROW(Sphere(Point::Origin(), 1.0).intersects(Ray::Undefined()));
        EXPECT_ANY_THROW(Sphere::Undefined().intersects(Ray({0.0, 0.0, 0.0}, {0.0, 0.0, 1.0})));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Sphere, Intersects_Segment)
{
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::geometry::d3::object::Sphere;

    {
        const Sphere sphere = {Point::Origin(), 2.0};

        EXPECT_FALSE(sphere.intersects(Segment({-10.0, -3.0, 0.0}, {+10.0, -3.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Segment({-10.0, -2.1, 0.0}, {+10.0, -2.1, 0.0})));
        EXPECT_TRUE(sphere.intersects(Segment({-10.0, -2.0, 0.0}, {+10.0, -2.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Segment({-10.0, -1.0, 0.0}, {+10.0, -1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Segment({-10.0, +0.0, 0.0}, {+10.0, +0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Segment({-10.0, +1.0, 0.0}, {+10.0, +1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Segment({-10.0, +2.0, 0.0}, {+10.0, +2.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Segment({-10.0, +2.1, 0.0}, {+10.0, +2.1, 0.0})));
        EXPECT_FALSE(sphere.intersects(Segment({-10.0, +3.0, 0.0}, {+10.0, +3.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Segment({-3.0, -10.0, 0.0}, {-3.0, +10.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Segment({-2.1, -10.0, 0.0}, {-2.1, +10.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Segment({-2.0, -10.0, 0.0}, {-2.0, +10.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Segment({-1.0, -10.0, 0.0}, {-1.0, +10.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Segment({+0.0, -10.0, 0.0}, {+0.0, +10.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Segment({+1.0, -10.0, 0.0}, {+1.0, +10.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Segment({+2.0, -10.0, 0.0}, {+2.0, +10.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Segment({+2.1, -10.0, 0.0}, {+2.1, +10.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Segment({+3.0, -10.0, 0.0}, {+3.0, +10.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Segment({-10.0, 0.0, -3.0}, {+10.0, 0.0, -3.0})));
        EXPECT_FALSE(sphere.intersects(Segment({-10.0, 0.0, -2.1}, {+10.0, 0.0, -2.1})));
        EXPECT_TRUE(sphere.intersects(Segment({-10.0, 0.0, -2.0}, {+10.0, 0.0, -2.0})));
        EXPECT_TRUE(sphere.intersects(Segment({-10.0, 0.0, -1.0}, {+10.0, 0.0, -1.0})));
        EXPECT_TRUE(sphere.intersects(Segment({-10.0, 0.0, +0.0}, {+10.0, 0.0, +0.0})));
        EXPECT_TRUE(sphere.intersects(Segment({-10.0, 0.0, +1.0}, {+10.0, 0.0, +1.0})));
        EXPECT_TRUE(sphere.intersects(Segment({-10.0, 0.0, +2.0}, {+10.0, 0.0, +2.0})));
        EXPECT_FALSE(sphere.intersects(Segment({-10.0, 0.0, +2.1}, {+10.0, 0.0, +2.1})));
        EXPECT_FALSE(sphere.intersects(Segment({-10.0, 0.0, +3.0}, {+10.0, 0.0, +3.0})));

        EXPECT_FALSE(sphere.intersects(Segment({-10.0, 0.0, 0.0}, {-2.1, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Segment({-10.0, 0.0, 0.0}, {-2.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Segment({-10.0, 0.0, 0.0}, {-1.9, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Segment({+10.0, 0.0, 0.0}, {+1.9, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Segment({+10.0, 0.0, 0.0}, {+2.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Segment({+10.0, 0.0, 0.0}, {+2.1, 0.0, 0.0})));
    }

    {
        const Real equatorialRadius_m = 6378136.3;

        const Sphere sphere = {Point::Origin(), equatorialRadius_m};

        EXPECT_FALSE(sphere.intersects(Segment({-10000e3, -7000e3, 0.0}, {+10000e3, -7000e3, 0.0})));
        EXPECT_FALSE(sphere.intersects(
            Segment({-10000e3, -equatorialRadius_m - 0.1, 0.0}, {+10000e3, -equatorialRadius_m - 0.1, 0.0})
        ));
        EXPECT_TRUE(
            sphere.intersects(Segment({-10000e3, -equatorialRadius_m, 0.0}, {+10000e3, -equatorialRadius_m, 0.0}))
        );
        EXPECT_TRUE(sphere.intersects(
            Segment({-10000e3, -equatorialRadius_m + 0.1, 0.0}, {+10000e3, -equatorialRadius_m + 0.1, 0.0})
        ));
        EXPECT_TRUE(sphere.intersects(Segment({-10000e3, +0.0, 0.0}, {+10000e3, +0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(
            Segment({-10000e3, +equatorialRadius_m - 0.1, 0.0}, {+10000e3, +equatorialRadius_m - 0.1, 0.0})
        ));
        EXPECT_TRUE(
            sphere.intersects(Segment({-10000e3, +equatorialRadius_m, 0.0}, {+10000e3, +equatorialRadius_m, 0.0}))
        );
        EXPECT_FALSE(sphere.intersects(
            Segment({-10000e3, +equatorialRadius_m + 0.1, 0.0}, {+10000e3, +equatorialRadius_m + 0.1, 0.0})
        ));
        EXPECT_FALSE(sphere.intersects(Segment({-10000e3, +7000e3, 0.0}, {+10000e3, +7000e3, 0.0})));

        EXPECT_FALSE(sphere.intersects(Segment({-7000e3, -10000e3, 0.0}, {-7000e3, +10000e3, 0.0})));
        EXPECT_FALSE(sphere.intersects(
            Segment({-equatorialRadius_m - 0.1, -10000e3, 0.0}, {-equatorialRadius_m - 0.1, +10000e3, 0.0})
        ));
        EXPECT_TRUE(
            sphere.intersects(Segment({-equatorialRadius_m, -10000e3, 0.0}, {-equatorialRadius_m, +10000e3, 0.0}))
        );
        EXPECT_TRUE(sphere.intersects(
            Segment({-equatorialRadius_m + 0.1, -10000e3, 0.0}, {-equatorialRadius_m + 0.1, +10000e3, 0.0})
        ));
        EXPECT_TRUE(sphere.intersects(Segment({+0.0, -10000e3, 0.0}, {+0.0, +10000e3, 0.0})));
        EXPECT_TRUE(sphere.intersects(
            Segment({+equatorialRadius_m - 0.1, -10000e3, 0.0}, {+equatorialRadius_m - 0.1, +10000e3, 0.0})
        ));
        EXPECT_TRUE(
            sphere.intersects(Segment({+equatorialRadius_m, -10000e3, 0.0}, {+equatorialRadius_m, +10000e3, 0.0}))
        );
        EXPECT_FALSE(sphere.intersects(
            Segment({+equatorialRadius_m + 0.1, -10000e3, 0.0}, {+equatorialRadius_m + 0.1, +10000e3, 0.0})
        ));
        EXPECT_FALSE(sphere.intersects(Segment({+7000e3, -10000e3, 0.0}, {+7000e3, +10000e3, 0.0})));

        EXPECT_FALSE(sphere.intersects(Segment({-10000e3, 0.0, -7000e3}, {+10000e3, 0.0, -7000e3})));
        EXPECT_FALSE(sphere.intersects(
            Segment({-10000e3, 0.0, -equatorialRadius_m - 0.1}, {+10000e3, 0.0, -equatorialRadius_m - 0.1})
        ));
        EXPECT_TRUE(
            sphere.intersects(Segment({-10000e3, 0.0, -equatorialRadius_m}, {+10000e3, 0.0, -equatorialRadius_m}))
        );
        EXPECT_TRUE(sphere.intersects(
            Segment({-10000e3, 0.0, -equatorialRadius_m + 0.1}, {+10000e3, 0.0, -equatorialRadius_m + 0.1})
        ));
        EXPECT_TRUE(sphere.intersects(Segment({-10000e3, 0.0, +0.0}, {+10000e3, 0.0, +0.0})));
        EXPECT_TRUE(sphere.intersects(
            Segment({-10000e3, 0.0, +equatorialRadius_m - 0.1}, {+10000e3, 0.0, +equatorialRadius_m - 0.1})
        ));
        EXPECT_TRUE(
            sphere.intersects(Segment({-10000e3, 0.0, +equatorialRadius_m}, {+10000e3, 0.0, +equatorialRadius_m}))
        );
        EXPECT_FALSE(sphere.intersects(
            Segment({-10000e3, 0.0, +equatorialRadius_m + 0.1}, {+10000e3, 0.0, +equatorialRadius_m + 0.1})
        ));
        EXPECT_FALSE(sphere.intersects(Segment({-10000e3, 0.0, +7000e3}, {+10000e3, 0.0, +7000e3})));
    }

    {
        EXPECT_ANY_THROW(Sphere(Point::Origin(), 1.0).intersects(Segment::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Sphere, Intersects_Plane)
{
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Sphere;

    {
        const Sphere sphere = {Point::Origin(), 2.0};

        EXPECT_TRUE(sphere.intersects(Plane({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Plane({0.0, 0.0, 0.0}, {0.0, 1.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Plane({-3.0, 0.0, 0.0}, {1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Plane({-2.0, 0.0, 0.0}, {1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Plane({-1.0, 0.0, 0.0}, {1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Plane({+0.0, 0.0, 0.0}, {1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Plane({+1.0, 0.0, 0.0}, {1.0, 0.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Plane({+2.0, 0.0, 0.0}, {1.0, 0.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Plane({+3.0, 0.0, 0.0}, {1.0, 0.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Plane({0.0, -3.0, 0.0}, {0.0, 1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Plane({0.0, -2.0, 0.0}, {0.0, 1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Plane({0.0, -1.0, 0.0}, {0.0, 1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Plane({0.0, +0.0, 0.0}, {0.0, 1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Plane({0.0, +1.0, 0.0}, {0.0, 1.0, 0.0})));
        EXPECT_TRUE(sphere.intersects(Plane({0.0, +2.0, 0.0}, {0.0, 1.0, 0.0})));
        EXPECT_FALSE(sphere.intersects(Plane({0.0, +3.0, 0.0}, {0.0, 1.0, 0.0})));

        EXPECT_FALSE(sphere.intersects(Plane({0.0, 0.0, -3.0}, {0.0, 0.0, 1.0})));
        EXPECT_TRUE(sphere.intersects(Plane({0.0, 0.0, -2.0}, {0.0, 0.0, 1.0})));
        EXPECT_TRUE(sphere.intersects(Plane({0.0, 0.0, -1.0}, {0.0, 0.0, 1.0})));
        EXPECT_TRUE(sphere.intersects(Plane({0.0, 0.0, +0.0}, {0.0, 0.0, 1.0})));
        EXPECT_TRUE(sphere.intersects(Plane({0.0, 0.0, +1.0}, {0.0, 0.0, 1.0})));
        EXPECT_TRUE(sphere.intersects(Plane({0.0, 0.0, +2.0}, {0.0, 0.0, 1.0})));
        EXPECT_FALSE(sphere.intersects(Plane({0.0, 0.0, +3.0}, {0.0, 0.0, 1.0})));
    }

    {
        EXPECT_ANY_THROW(Sphere::Undefined().intersects(Plane::Undefined()));
        EXPECT_ANY_THROW(Sphere(Point::Origin(), 1.0).intersects(Plane::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Sphere, Intersects_Pyramid)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Sphere;

    {
        // See: OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Pyramid.Intersects_Sphere

        SUCCEED();
    }

    {
        EXPECT_ANY_THROW(Sphere::Undefined().intersects(Pyramid::Undefined()));
        EXPECT_ANY_THROW(Sphere(Point::Origin(), 1.0).intersects(Pyramid::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Sphere, Contains_Point)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Sphere;

    {
        EXPECT_TRUE(Sphere({1.0, 2.0, 3.0}, 4.0).contains(Point(+5.0, +2.0, +3.0)));
        EXPECT_TRUE(Sphere({1.0, 2.0, 3.0}, 4.0).contains(Point(-3.0, +2.0, +3.0)));

        EXPECT_TRUE(Sphere({1.0, 2.0, 3.0}, 4.0).contains(Point(+1.0, +6.0, +3.0)));
        EXPECT_TRUE(Sphere({1.0, 2.0, 3.0}, 4.0).contains(Point(+1.0, -2.0, +3.0)));

        EXPECT_TRUE(Sphere({1.0, 2.0, 3.0}, 4.0).contains(Point(+1.0, +2.0, +7.0)));
        EXPECT_TRUE(Sphere({1.0, 2.0, 3.0}, 4.0).contains(Point(+1.0, +2.0, -1.0)));
    }

    {
        EXPECT_FALSE(Sphere(Point::Origin(), 4.0).contains(Point::Origin()));
    }

    {
        EXPECT_ANY_THROW(Sphere::Undefined().contains(Point::Undefined()));
        EXPECT_ANY_THROW(Sphere({1.0, 2.0, 3.0}, 4.0).contains(Point::Undefined()));
        EXPECT_ANY_THROW(Sphere::Undefined().contains(Point(0.0, 0.0, 0.0)));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Sphere, Contains_PointSet)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Sphere;

    {
        EXPECT_TRUE(Sphere({1.0, 2.0, 3.0}, 4.0)
                        .contains(PointSet(
                            {{+5.0, +2.0, +3.0},
                             {-3.0, +2.0, +3.0},
                             {+1.0, +6.0, +3.0},
                             {+1.0, -2.0, +3.0},
                             {+1.0, +2.0, +7.0},
                             {+1.0, +2.0, -1.0}}
                        )));
    }

    {
        EXPECT_FALSE(Sphere({1.0, 2.0, 3.0}, 4.0)
                         .contains(PointSet(
                             {{+5.0, +2.0, +3.0},
                              {-3.0, +2.0, +3.0},
                              {+1.0, +6.0, +3.0},
                              {+1.0, -2.0, +3.0},
                              {+1.0, +2.0, +7.0},
                              {0.0, 0.0, 0.0}}
                         )));
    }

    {
        EXPECT_FALSE(Sphere(Point::Origin(), 4.0).contains(PointSet::Empty()));
    }

    {
        EXPECT_ANY_THROW(Sphere::Undefined().contains(PointSet::Empty()));
        EXPECT_ANY_THROW(Sphere::Undefined().contains(PointSet({{+5.0, +2.0, +3.0}, {+5.0, +2.0, +3.0}})));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Sphere, GetCenter)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Sphere;

    {
        EXPECT_EQ(Point(1.0, 2.0, 3.0), Sphere({1.0, 2.0, 3.0}, 4.0).getCenter());
    }

    {
        EXPECT_ANY_THROW(Sphere::Undefined().getCenter());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Sphere, GetRadius)
{
    using ostk::mathematics::geometry::d3::object::Sphere;

    {
        EXPECT_EQ(4.0, Sphere({1.0, 2.0, 3.0}, 4.0).getRadius());
    }

    {
        EXPECT_ANY_THROW(Sphere::Undefined().getRadius());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Sphere, ApplyTransformation)
{
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Sphere;
    using ostk::mathematics::geometry::d3::Transformation;
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;
    using ostk::mathematics::object::Vector3d;

    // Translation

    {
        Sphere sphere = {{1.0, 2.0, 3.0}, 4.0};

        sphere.applyTransformation(Transformation::Translation({4.0, 5.0, 6.0}));

        EXPECT_EQ(Sphere({5.0, 7.0, 9.0}, 4.0), sphere);
    }

    // Rotation

    {
        Sphere sphere = {{1.0, 2.0, 0.0}, 4.0};

        sphere.applyTransformation(Transformation::Rotation(RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(90.0))));

        const Sphere referenceSphere = {{1.0, 0.0, 2.0}, 4.0};

        EXPECT_TRUE(sphere.getCenter().isNear(referenceSphere.getCenter(), Real::Epsilon()));
        EXPECT_EQ(referenceSphere.getRadius(), sphere.getRadius());
    }

    {
        EXPECT_ANY_THROW(Sphere::Undefined().applyTransformation(Transformation::Undefined()));
        EXPECT_ANY_THROW(Sphere::Undefined().applyTransformation(Transformation::Identity()));
        EXPECT_ANY_THROW(Sphere({1.0, 2.0, 3.0}, 4.0).applyTransformation(Transformation::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Sphere, Undefined)
{
    using ostk::mathematics::geometry::d3::object::Sphere;

    {
        EXPECT_NO_THROW(Sphere::Undefined());
        EXPECT_FALSE(Sphere::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Sphere, Unit)
{
    using ostk::mathematics::geometry::d3::object::Sphere;

    {
        EXPECT_NO_THROW(Sphere::Unit({0.0, 0.0, 0.0}));
        EXPECT_EQ(Sphere({0.0, 0.0, 0.0}, 1.0), Sphere::Unit({0.0, 0.0, 0.0}));
    }
}
