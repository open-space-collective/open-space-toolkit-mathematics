/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/PointSet.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_PointSet, Constructor)
{
    using ostk::math::geom::d3::objects::Point;
    using ostk::math::geom::d3::objects::PointSet;

    {
        EXPECT_NO_THROW(PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}));
    }

    {
        EXPECT_NO_THROW(PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_PointSet, Clone)
{
    using ostk::math::geom::d3::objects::PointSet;

    {
        EXPECT_NO_THROW(const PointSet* pointSetPtr =
                            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}).clone();
                        delete pointSetPtr;);
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_PointSet, EqualToOperator)
{
    using ostk::math::geom::d3::objects::PointSet;

    {
        EXPECT_TRUE(
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}) ==
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}})
        );
        EXPECT_TRUE(
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}) ==
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 2.0}, {0.0, 0.0, 1.0}})
        );
        EXPECT_TRUE(
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}) ==
            PointSet({{0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 2.0}})
        );
        EXPECT_TRUE(
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}) ==
            PointSet({{0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}, {0.0, 0.0, 0.0}})
        );
        EXPECT_TRUE(
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}) ==
            PointSet({{0.0, 0.0, 2.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}})
        );
        EXPECT_TRUE(
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}) ==
            PointSet({{0.0, 0.0, 2.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}})
        );

        EXPECT_TRUE(
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}) ==
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}})
        );

        EXPECT_TRUE(PointSet::Empty() == PointSet::Empty());
    }

    {
        EXPECT_FALSE(
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}) ==
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 3.0}})
        );
    }

    {
        EXPECT_FALSE(PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}) == PointSet::Empty());
        EXPECT_FALSE(PointSet::Empty() == PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_PointSet, NotEqualToOperator)
{
    using ostk::math::geom::d3::objects::PointSet;

    {
        EXPECT_FALSE(
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}) !=
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}})
        );
        EXPECT_FALSE(
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}) !=
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 2.0}, {0.0, 0.0, 1.0}})
        );
        EXPECT_FALSE(
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}) !=
            PointSet({{0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 2.0}})
        );
        EXPECT_FALSE(
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}) !=
            PointSet({{0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}, {0.0, 0.0, 0.0}})
        );
        EXPECT_FALSE(
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}) !=
            PointSet({{0.0, 0.0, 2.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}})
        );
        EXPECT_FALSE(
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}) !=
            PointSet({{0.0, 0.0, 2.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}})
        );

        EXPECT_FALSE(
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}) !=
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}})
        );

        EXPECT_FALSE(PointSet::Empty() != PointSet::Empty());
    }

    {
        EXPECT_TRUE(
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}) !=
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 3.0}})
        );
    }

    {
        EXPECT_TRUE(PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}) != PointSet::Empty());
        EXPECT_TRUE(PointSet::Empty() != PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_PointSet, StreamOperator)
{
    using ostk::math::geom::d3::objects::PointSet;

    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}) << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_PointSet, IsDefined)
{
    using ostk::math::geom::d3::objects::PointSet;

    {
        EXPECT_TRUE(PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}).isDefined());
        EXPECT_TRUE(PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}).isDefined());
    }

    {
        EXPECT_FALSE(PointSet::Empty().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_PointSet, IsEmpty)
{
    using ostk::math::geom::d3::objects::PointSet;

    {
        EXPECT_FALSE(PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}).isEmpty());
        EXPECT_FALSE(PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}).isEmpty());
    }

    {
        EXPECT_TRUE(PointSet::Empty().isEmpty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_PointSet, IsNear)
{
    using ostk::core::types::Real;

    using ostk::math::geom::d3::objects::PointSet;

    {
        EXPECT_TRUE(PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}
        ).isNear(PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}), Real::Epsilon()));
        EXPECT_TRUE(PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}
        ).isNear(PointSet({{0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 2.0}}), Real::Epsilon()));

        EXPECT_TRUE(
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}})
                .isNear(
                    PointSet({{0.0, Real::Epsilon(), 1.0}, {Real::Epsilon(), 0.0, 2.0}, {0.0, 0.0, Real::Epsilon()}}),
                    Real::Epsilon()
                )
        );
    }

    {
        EXPECT_FALSE(
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}})
                .isNear(
                    PointSet(
                        {{0.0, 2.0 * Real::Epsilon(), 1.0}, {Real::Epsilon(), 0.0, 2.0}, {0.0, 0.0, Real::Epsilon()}}
                    ),
                    Real::Epsilon()
                )
        );
    }

    {
        EXPECT_FALSE(PointSet::Empty().isNear(PointSet::Empty(), Real::Epsilon()));
        EXPECT_FALSE(PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}
        ).isNear(PointSet::Empty(), Real::Epsilon()));
        EXPECT_FALSE(
            PointSet::Empty().isNear(PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}), Real::Epsilon())
        );
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_PointSet, GetSize)
{
    using ostk::math::geom::d3::objects::PointSet;

    {
        EXPECT_EQ(3, PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}).getSize());
    }

    {
        EXPECT_EQ(0, PointSet::Empty().getSize());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_PointSet, DistanceToPoint)
{
    using ostk::math::geom::d3::objects::Point;
    using ostk::math::geom::d3::objects::PointSet;

    {
        EXPECT_EQ(
            0.0, PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}).distanceTo(Point({0.0, 0.0, 0.0}))
        );
        EXPECT_EQ(
            0.0, PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}).distanceTo(Point({0.0, 0.0, 1.0}))
        );
        EXPECT_EQ(
            0.0, PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}).distanceTo(Point({0.0, 0.0, 2.0}))
        );

        EXPECT_EQ(
            1.0, PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}).distanceTo(Point({0.0, 0.0, 3.0}))
        );
    }

    {
        EXPECT_ANY_THROW(PointSet::Empty().distanceTo(Point::Undefined()));
        EXPECT_ANY_THROW(PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}).distanceTo(Point::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_PointSet, GetPointClosestTo)
{
    using ostk::math::geom::d3::objects::Point;
    using ostk::math::geom::d3::objects::PointSet;

    {
        EXPECT_EQ(
            Point(0.0, 0.0, 0.0),
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}).getPointClosestTo({0.0, 0.0, 0.0})
        );
        EXPECT_EQ(
            Point(0.0, 0.0, 1.0),
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}).getPointClosestTo({0.0, 0.0, 1.0})
        );
        EXPECT_EQ(
            Point(0.0, 0.0, 2.0),
            PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}).getPointClosestTo({0.0, 0.0, 2.0})
        );
    }

    {
        EXPECT_ANY_THROW(PointSet::Empty().getPointClosestTo(Point::Undefined()));
        EXPECT_ANY_THROW(PointSet::Empty().getPointClosestTo(Point::Origin()));
        EXPECT_ANY_THROW(PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}
        ).getPointClosestTo(Point::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_PointSet, ConstIterator)
{
    using ostk::core::types::Index;

    using ostk::math::geom::d3::objects::PointSet;

    {
        const PointSet pointSet = {{{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}};

        Index count = 0;

        for (const auto& point : pointSet)
        {
            EXPECT_TRUE(point.isDefined());

            count++;
        }

        EXPECT_EQ(3, count);
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_PointSet, ApplyTransformation)
{
    using ostk::core::types::Real;

    using ostk::math::obj::Vector3d;
    using ostk::math::geom::Angle;
    using ostk::math::geom::d3::objects::Point;
    using ostk::math::geom::d3::objects::PointSet;
    using ostk::math::geom::d3::Transformation;
    using ostk::math::geom::d3::trf::rot::RotationVector;

    // Translation

    {
        PointSet pointSet = {{{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}};

        pointSet.applyTransformation(Transformation::Translation({4.0, 5.0, 6.0}));

        EXPECT_EQ(PointSet({{4.0, 5.0, 6.0}, {4.0, 5.0, 7.0}, {4.0, 5.0, 8.0}}), pointSet);
    }

    // Rotation

    {

        // [TBI]

    }

    {
        EXPECT_ANY_THROW(PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, 2.0}}
        ).applyTransformation(Transformation::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_PointSet, Empty)
{
    using ostk::math::geom::d3::objects::PointSet;

    {
        EXPECT_NO_THROW(PointSet::Empty());
        EXPECT_FALSE(PointSet::Empty().isDefined());
    }
}
