/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Pyramid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Pyramid, Constructor)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::object::Vector3d;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        EXPECT_NO_THROW(Pyramid(base, apex));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Pyramid, Clone)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::object::Vector3d;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        EXPECT_NO_THROW(const Pyramid* pyramidPtr = Pyramid(base, apex).clone(); delete pyramidPtr;);
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Pyramid, EqualToOperator)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::object::Vector3d;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        EXPECT_TRUE(Pyramid(base, apex) == Pyramid(base, apex));
    }

    {
        // [TBI] Implement similarities
    }

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        EXPECT_FALSE(Pyramid(base, apex) == Pyramid::Undefined());
        EXPECT_FALSE(Pyramid::Undefined() == Pyramid(base, apex));
        EXPECT_FALSE(Pyramid::Undefined() == Pyramid::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Pyramid, NotEqualToOperator)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::object::Vector3d;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        EXPECT_FALSE(Pyramid(base, apex) != Pyramid(base, apex));
    }

    {
        // [TBI] Implement similarities
    }

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        EXPECT_TRUE(Pyramid(base, apex) != Pyramid::Undefined());
        EXPECT_TRUE(Pyramid::Undefined() != Pyramid(base, apex));
        EXPECT_TRUE(Pyramid::Undefined() != Pyramid::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Pyramid, StreamOperator)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::object::Vector3d;

    {
        testing::internal::CaptureStdout();

        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        EXPECT_NO_THROW(std::cout << Pyramid(base, apex) << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Pyramid, IsDefined)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::object::Vector3d;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        EXPECT_TRUE(Pyramid(base, apex).isDefined());
    }

    {
        EXPECT_FALSE(Pyramid::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Pyramid, Intersects_Ellipsoid)
{
    using ostk::mathematics::geometry::d3::object::Ellipsoid;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::object::Vector3d;

    {
        const Polygon base = {
            {{{-0.1, -0.1}, {+0.1, -0.1}, {+0.1, +0.1}, {-0.1, +0.1}}},
            {0.0, 0.0, 1.0},
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 0.0};

        const Pyramid pyramid = {base, apex};

        const Ellipsoid ellipsoid = {{0.0, 0.0, 10.0}, 5.0, 5.0, 5.0};

        EXPECT_TRUE(pyramid.intersects(ellipsoid));

        // Behind the apex, or beside the field of view

        EXPECT_FALSE(pyramid.intersects(Ellipsoid({0.0, 0.0, -10.0}, 5.0, 5.0, 5.0)));
        EXPECT_FALSE(pyramid.intersects(Ellipsoid({10.0, 0.0, 10.0}, 5.0, 5.0, 5.0)));

        // Hit by some of the rays of the last lateral face only, and missed by the rays through the base vertices

        EXPECT_TRUE(pyramid.intersects(Ellipsoid({0.0, -2.0, 10.0}, 1.2, 1.2, 1.2)));

        EXPECT_ANY_THROW(pyramid.intersects(ellipsoid, 3));
    }

    {
        EXPECT_ANY_THROW(Pyramid::Undefined().intersects(Ellipsoid::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Pyramid, Contains_Point)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::object::Vector3d;

    {
        const Polygon base = {
            {{{-0.1, -0.1}, {+0.1, -0.1}, {+0.1, +0.1}, {-0.1, +0.1}}},
            {0.0, 0.0, 1.0},
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 0.0};

        const Pyramid pyramid = {base, apex};

        EXPECT_TRUE(pyramid.contains(Point {0.0, 0.0, 0.0}));
        EXPECT_TRUE(pyramid.contains(Point {0.0, 0.0, 1.0}));
        EXPECT_TRUE(pyramid.contains(Point {0.0, 0.0, 2.0}));
        EXPECT_TRUE(pyramid.contains(Point {0.0, 0.0, 3.0}));

        EXPECT_FALSE(pyramid.contains(Point {0.0, 0.0, -1.0}));
        EXPECT_FALSE(pyramid.contains(Point {0.0, 0.0, -2.0}));
        EXPECT_FALSE(pyramid.contains(Point {0.0, 0.0, -3.0}));

        EXPECT_FALSE(pyramid.contains(Point {+1.0, 0.0, 0.0}));
        EXPECT_FALSE(pyramid.contains(Point {-1.0, 0.0, 0.0}));

        EXPECT_FALSE(pyramid.contains(Point {0.0, +1.0, 0.0}));
        EXPECT_FALSE(pyramid.contains(Point {0.0, -1.0, 0.0}));

        EXPECT_FALSE(pyramid.contains(Point {2.0, 2.0, 1.0}));
    }

    {
        const Polygon base = {
            {{{-0.1, -0.1}, {+0.1, -0.1}, {+0.1, +0.1}, {-0.1, +0.1}}},
            {0.0, 0.0, -1.0},
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 0.0};

        const Pyramid pyramid = {base, apex};

        EXPECT_TRUE(pyramid.contains(Point {0.0, 0.0, 0.0}));
        EXPECT_TRUE(pyramid.contains(Point {0.0, 0.0, -1.0}));
        EXPECT_TRUE(pyramid.contains(Point {0.0, 0.0, -2.0}));
        EXPECT_TRUE(pyramid.contains(Point {0.0, 0.0, -3.0}));

        EXPECT_FALSE(pyramid.contains(Point {0.0, 0.0, 1.0}));
        EXPECT_FALSE(pyramid.contains(Point {0.0, 0.0, 2.0}));
        EXPECT_FALSE(pyramid.contains(Point {0.0, 0.0, 3.0}));

        EXPECT_FALSE(pyramid.contains(Point {+1.0, 0.0, 0.0}));
        EXPECT_FALSE(pyramid.contains(Point {-1.0, 0.0, 0.0}));

        EXPECT_FALSE(pyramid.contains(Point {0.0, +1.0, 0.0}));
        EXPECT_FALSE(pyramid.contains(Point {0.0, -1.0, 0.0}));

        EXPECT_FALSE(pyramid.contains(Point {2.0, 2.0, -1.0}));
    }

    {
        const Polygon base = {
            {{{-0.1, -0.1}, {+0.1, -0.1}, {+0.1, +0.1}, {-0.1, +0.1}}},
            {0.0, 2.0, 0.0},
            {1.0, 0.0, 0.0},
            {0.0, 0.0, -1.0}
        };
        const Point apex = {0.0, 1.0, 0.0};

        const Pyramid pyramid = {base, apex};

        EXPECT_TRUE(pyramid.contains(Point {0.0, 1.0, 0.0}));
        EXPECT_TRUE(pyramid.contains(Point {0.0, 2.0, 0.0}));
        EXPECT_TRUE(pyramid.contains(Point {0.0, 3.0, 0.0}));
        EXPECT_TRUE(pyramid.contains(Point {0.0, 4.0, 0.0}));

        EXPECT_FALSE(pyramid.contains(Point {0.0, 0.0, 0.0}));
        EXPECT_FALSE(pyramid.contains(Point {0.0, -1.0, 0.0}));
        EXPECT_FALSE(pyramid.contains(Point {0.0, -2.0, 0.0}));
        EXPECT_FALSE(pyramid.contains(Point {0.0, -2.0, 0.0}));

        EXPECT_FALSE(pyramid.contains(Point {+1.0, 0.0, 0.0}));
        EXPECT_FALSE(pyramid.contains(Point {-1.0, 0.0, 0.0}));

        EXPECT_FALSE(pyramid.contains(Point {0.0, 0.0, +1.0}));
        EXPECT_FALSE(pyramid.contains(Point {0.0, 0.0, -1.0}));

        EXPECT_FALSE(pyramid.contains(Point {1.0, 1.0, 1.0}));
    }

    {
        const Polygon base = {
            {{{-1.0, -1.0}, {+1.0, -1.0}, {+1.0, +1.0}, {-1.0, +1.0}}},
            {2.0, 2.0, 0.0},
            {0.0, 0.0, -1.0},
            {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 0.0};

        const Pyramid pyramid = {base, apex};

        EXPECT_TRUE(pyramid.contains(Point {0.0, 0.0, 0.0}));
        EXPECT_TRUE(pyramid.contains(Point {2.0, 2.0, 0.0}));
        EXPECT_TRUE(pyramid.contains(Point {2.0, 1.0, 0.0}));
        EXPECT_TRUE(pyramid.contains(Point {2.0, 3.0, 0.0}));

        EXPECT_FALSE(pyramid.contains(Point {2.0, 0.5, 0.0}));
        EXPECT_FALSE(pyramid.contains(Point {1.0, 2.0, 0.0}));
    }

    {
        EXPECT_ANY_THROW(Pyramid::Undefined().contains(Point::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Pyramid, Contains_PointSet)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::object::Vector3d;

    {
        const Polygon base = {
            {{{-0.1, -0.1}, {+0.1, -0.1}, {+0.1, +0.1}, {-0.1, +0.1}}},
            {0.0, 0.0, 1.0},
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 0.0};

        const Pyramid pyramid = {base, apex};

        EXPECT_TRUE(pyramid.contains(PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}})));
        EXPECT_TRUE(pyramid.contains(PointSet({{0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}})));

        EXPECT_FALSE(pyramid.contains(PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, -1.0}})));
        EXPECT_FALSE(pyramid.contains(PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, -2.0}})));
        EXPECT_FALSE(pyramid.contains(PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, -3.0}})));
    }

    {
        EXPECT_ANY_THROW(Pyramid::Undefined().contains(PointSet::Empty()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Pyramid, Contains_Segment)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::object::Vector3d;

    {
        const Polygon base = {
            {{{-0.1, -0.1}, {+0.1, -0.1}, {+0.1, +0.1}, {-0.1, +0.1}}},
            {0.0, 0.0, 1.0},
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 0.0};

        const Pyramid pyramid = {base, apex};

        EXPECT_TRUE(pyramid.contains(Segment {{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}}));
        EXPECT_TRUE(pyramid.contains(Segment {{0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}}));

        EXPECT_FALSE(pyramid.contains(Segment {{0.0, 0.0, 0.0}, {0.0, 0.0, -1.0}}));
        EXPECT_FALSE(pyramid.contains(Segment {{0.0, 0.0, 0.0}, {0.0, 0.0, -2.0}}));
        EXPECT_FALSE(pyramid.contains(Segment {{0.0, 0.0, 0.0}, {0.0, 0.0, -3.0}}));
    }

    {
        EXPECT_ANY_THROW(Pyramid::Undefined().contains(Segment::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Pyramid, GetBase)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::object::Vector3d;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        EXPECT_EQ(base, Pyramid(base, apex).getBase());
    }

    {
        EXPECT_ANY_THROW(Pyramid::Undefined().getBase());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Pyramid, GetApex)
{
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::object::Vector3d;

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        EXPECT_EQ(apex, Pyramid(base, apex).getApex());
    }

    {
        EXPECT_ANY_THROW(Pyramid::Undefined().getApex());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Pyramid, GetRaysOfLateralFaceAt)
{
    using ostk::core::container::Array;
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Ray;

    const auto areNear = [](const Ray& aFirstRay, const Ray& aSecondRay) -> bool
    {
        return aFirstRay.getOrigin().isNear(aSecondRay.getOrigin(), Real::Epsilon()) &&
               aFirstRay.getDirection().isNear(aSecondRay.getDirection(), Real::Epsilon());
    };

    {
        const Polygon base = {
            {{{-0.1, -0.1}, {+0.1, -0.1}, {+0.1, +0.1}, {-0.1, +0.1}}},
            {0.0, 0.0, 1.0},
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 0.0};

        const Pyramid pyramid = {base, apex};

        {
            const Array<Ray> referenceRays = {
                {apex, {-0.099014754297667429, -0.099014754297667429, 0.99014754297667429}},
                {apex, {-0.099503719020998901, 1.1102230246251565e-16, 0.99503719020998915}},
                {apex, {-0.099014754297667429, 0.099014754297667665, 0.99014754297667429}},
            };

            EXPECT_TRUE(pyramid.getRaysOfLateralFaceAt(0, 3).isNear(referenceRays, areNear));
        }

        {
            const Array<Ray> referenceRays = {
                {apex, {0.099014754297667429, 0.099014754297667429, 0.99014754297667429}},
            };

            EXPECT_TRUE(pyramid.getRaysOfLateralFaceAt(2, 1).isNear(referenceRays, areNear));
        }
    }

    {
        const Polygon base = {
            {{{-0.1, -0.1}, {+0.1, -0.1}, {+0.1, +0.1}, {-0.1, +0.1}}},
            {0.0, 2.0, 0.0},
            {1.0, 0.0, 0.0},
            {0.0, 0.0, -1.0}
        };
        const Point apex = {0.0, 1.0, 0.0};

        const Pyramid pyramid = {base, apex};

        const Array<Ray> referenceRays = {
            {apex, {-0.099014754297667443, 0.9901475429766744, -0.099014754297667443}},
            {apex, {-0.033053065624991253, 0.9944935000473486, -0.099449350004734857}},
            {apex, {0.03305306562499033, 0.99449350004734871, -0.099449350004734885}},
            {apex, {0.099014754297666513, 0.9901475429766744, -0.099014754297667443}},
        };

        EXPECT_TRUE(pyramid.getRaysOfLateralFaceAt(1, 4).isNear(referenceRays, areNear));
    }

    {
        EXPECT_ANY_THROW(Pyramid::Undefined().getRaysOfLateralFaceAt(0, 2));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Pyramid, GetRaysOfLateralFaces)
{
    using ostk::core::container::Array;
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Ray;

    {
        const Polygon base = {
            {{{-0.1, -0.1}, {+0.1, -0.1}, {+0.1, +0.1}, {-0.1, +0.1}}},
            {0.0, 0.0, 1.0},
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 0.0};

        const Pyramid pyramid = {base, apex};

        // Two rays per lateral face, each face going from its first to its second base vertex

        const Array<Ray> referenceRays = {
            {apex, {-0.099014754297667429, -0.099014754297667429, 0.99014754297667429}},
            {apex, {-0.099014754297667429, 0.099014754297667665, 0.99014754297667429}},
            {apex, {-0.099014754297667429, 0.099014754297667429, 0.99014754297667429}},
            {apex, {0.099014754297667665, 0.099014754297667429, 0.99014754297667429}},
            {apex, {0.099014754297667429, 0.099014754297667429, 0.99014754297667429}},
            {apex, {0.099014754297667429, -0.099014754297667665, 0.99014754297667429}},
            {apex, {0.099014754297667429, -0.099014754297667429, 0.99014754297667429}},
            {apex, {-0.099014754297667665, -0.099014754297667429, 0.99014754297667429}},
        };

        EXPECT_TRUE(pyramid.getRaysOfLateralFaces(8).isNear(
            referenceRays,
            [](const Ray& aFirstRay, const Ray& aSecondRay) -> bool
            {
                return aFirstRay.getOrigin().isNear(aSecondRay.getOrigin(), Real::Epsilon()) &&
                       aFirstRay.getDirection().isNear(aSecondRay.getDirection(), Real::Epsilon());
            }
        ));

        EXPECT_EQ(40, pyramid.getRaysOfLateralFaces(40).getSize());
        EXPECT_EQ(40, pyramid.getRaysOfLateralFaces(43).getSize());

        EXPECT_ANY_THROW(pyramid.getRaysOfLateralFaces(3));
    }

    {
        EXPECT_ANY_THROW(Pyramid::Undefined().getRaysOfLateralFaces(8));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Pyramid, IntersectionWith_Ellipsoid)
{
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::d3::Intersection;
    using ostk::mathematics::geometry::d3::object::Ellipsoid;
    using ostk::mathematics::geometry::d3::object::LineString;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::object::Vector3d;

    {
        const Polygon base = {
            {{{-0.1, -0.1}, {+0.1, -0.1}, {+0.1, +0.1}, {-0.1, +0.1}}},
            {0.0, 0.0, 1.0},
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 0.0};

        const Pyramid pyramid = {base, apex};

        const Ellipsoid ellipsoid = {{0.0, 0.0, 10.0}, 5.0, 5.0, 5.0};

        const Intersection intersection = pyramid.intersectionWith(ellipsoid, true, 8);

        EXPECT_TRUE(intersection.isDefined());
        EXPECT_FALSE(intersection.isEmpty());
        EXPECT_TRUE(intersection.accessComposite().is<LineString>());

        const LineString intersectionLineString = intersection.accessComposite().as<LineString>();

        EXPECT_EQ(8, intersectionLineString.getPointCount());

        const LineString referenceLineString = {
            {{-0.505129425743498, -0.505129425743498, 5.05129425743498},
             {-0.505129425743498, 0.505129425743499, 5.05129425743498},
             {-0.505129425743498, 0.505129425743498, 5.05129425743498},
             {0.505129425743499, 0.505129425743498, 5.05129425743498},
             {0.505129425743498, 0.505129425743498, 5.05129425743498},
             {0.505129425743498, -0.505129425743499, 5.05129425743498},
             {0.505129425743498, -0.505129425743498, 5.05129425743498},
             {-0.505129425743499, -0.505129425743498, 5.05129425743498}}
        };

        EXPECT_TRUE(intersectionLineString.isNear(referenceLineString, 1e-10));
    }

    {
        EXPECT_ANY_THROW(Pyramid::Undefined().intersectionWith(Ellipsoid::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Pyramid, ApplyTransformation)
{
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::Transformation;
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;
    using ostk::mathematics::object::Vector3d;

    // Translation

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        Pyramid pyramid = {base, apex};

        pyramid.applyTransformation(Transformation::Translation({4.0, 5.0, 6.0}));

        EXPECT_EQ(
            Pyramid(
                {{{{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {4.0, 5.0, 6.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
                 },
                 {4.0, 5.0, 7.0}}
            ),
            pyramid
        );
    }

    // Rotation

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 2.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 0.0}
        };
        const Point apex = {0.0, 1.0, 0.0};

        Pyramid pyramid = {base, apex};

        pyramid.applyTransformation(Transformation::Rotation(RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(90.0))));

        const Polygon referenceBase = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 2.0}, {0.0, -1.0, 0.0}, {1.0, 0.0, 0.0}
        };
        const Point referenceApex = {0.0, 0.0, 1.0};

        const Pyramid referencePyramid = {referenceBase, referenceApex};

        EXPECT_TRUE(pyramid.getBase().isNear(referencePyramid.getBase(), Real::Epsilon()))
            << referencePyramid.getBase() << pyramid.getBase();
        EXPECT_TRUE(pyramid.getApex().isNear(referencePyramid.getApex(), Real::Epsilon()))
            << referencePyramid.getApex().toString() << pyramid.getApex().toString();
    }

    {
        const Polygon base = {
            {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}
        };
        const Point apex = {0.0, 0.0, 1.0};

        EXPECT_ANY_THROW(Pyramid::Undefined().applyTransformation(Transformation::Undefined()));
        EXPECT_ANY_THROW(Pyramid::Undefined().applyTransformation(Transformation::Identity()));
        EXPECT_ANY_THROW(Pyramid(base, apex).applyTransformation(Transformation::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Pyramid, Undefined)
{
    using ostk::mathematics::geometry::d3::object::Pyramid;

    {
        EXPECT_NO_THROW(Pyramid::Undefined());
        EXPECT_FALSE(Pyramid::Undefined().isDefined());
    }
}
