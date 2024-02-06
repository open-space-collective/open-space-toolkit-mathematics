/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/PointSet.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Transformation.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_PointSet, Constructor)
{
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::PointSet;

    {
        EXPECT_NO_THROW(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}));
    }

    {
        EXPECT_NO_THROW(PointSet({{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}}));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_PointSet, Clone)
{
    using ostk::mathematics::geometry::d2::object::PointSet;

    {
        EXPECT_NO_THROW(const PointSet* pointSetPtr = PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}).clone();
                        delete pointSetPtr;);
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_PointSet, EqualToOperator)
{
    using ostk::mathematics::geometry::d2::object::PointSet;

    {
        EXPECT_TRUE(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}) == PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}));
        EXPECT_TRUE(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}) == PointSet({{0.0, 0.0}, {0.0, 2.0}, {0.0, 1.0}}));
        EXPECT_TRUE(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}) == PointSet({{0.0, 1.0}, {0.0, 0.0}, {0.0, 2.0}}));
        EXPECT_TRUE(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}) == PointSet({{0.0, 1.0}, {0.0, 2.0}, {0.0, 0.0}}));
        EXPECT_TRUE(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}) == PointSet({{0.0, 2.0}, {0.0, 0.0}, {0.0, 1.0}}));
        EXPECT_TRUE(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}) == PointSet({{0.0, 2.0}, {0.0, 1.0}, {0.0, 0.0}}));

        EXPECT_TRUE(
            PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}) == PointSet({{0.0, 0.0}, {0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}})
        );

        EXPECT_TRUE(PointSet::Empty() == PointSet::Empty());
    }

    {
        EXPECT_FALSE(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}) == PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 3.0}}));
    }

    {
        EXPECT_FALSE(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}) == PointSet::Empty());
        EXPECT_FALSE(PointSet::Empty() == PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_PointSet, NotEqualToOperator)
{
    using ostk::mathematics::geometry::d2::object::PointSet;

    {
        EXPECT_FALSE(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}) != PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}));
        EXPECT_FALSE(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}) != PointSet({{0.0, 0.0}, {0.0, 2.0}, {0.0, 1.0}}));
        EXPECT_FALSE(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}) != PointSet({{0.0, 1.0}, {0.0, 0.0}, {0.0, 2.0}}));
        EXPECT_FALSE(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}) != PointSet({{0.0, 1.0}, {0.0, 2.0}, {0.0, 0.0}}));
        EXPECT_FALSE(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}) != PointSet({{0.0, 2.0}, {0.0, 0.0}, {0.0, 1.0}}));
        EXPECT_FALSE(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}) != PointSet({{0.0, 2.0}, {0.0, 1.0}, {0.0, 0.0}}));

        EXPECT_FALSE(
            PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}) != PointSet({{0.0, 0.0}, {0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}})
        );

        EXPECT_FALSE(PointSet::Empty() != PointSet::Empty());
    }

    {
        EXPECT_TRUE(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}) != PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 3.0}}));
    }

    {
        EXPECT_TRUE(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}) != PointSet::Empty());
        EXPECT_TRUE(PointSet::Empty() != PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_PointSet, StreamOperator)
{
    using ostk::mathematics::geometry::d2::object::PointSet;

    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}) << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_PointSet, IsDefined)
{
    using ostk::mathematics::geometry::d2::object::PointSet;

    {
        EXPECT_TRUE(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}).isDefined());
        EXPECT_TRUE(PointSet({{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}}).isDefined());
    }

    {
        EXPECT_FALSE(PointSet::Empty().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_PointSet, IsEmpty)
{
    using ostk::mathematics::geometry::d2::object::PointSet;

    {
        EXPECT_FALSE(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}).isEmpty());
        EXPECT_FALSE(PointSet({{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}}).isEmpty());
    }

    {
        EXPECT_TRUE(PointSet::Empty().isEmpty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_PointSet, IsNear)
{
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::d2::object::PointSet;

    {
        EXPECT_TRUE(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}
        ).isNear(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}), Real::Epsilon()));
        EXPECT_TRUE(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}
        ).isNear(PointSet({{0.0, 1.0}, {0.0, 0.0}, {0.0, 2.0}}), Real::Epsilon()));

        EXPECT_TRUE(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}
        ).isNear(PointSet({{0.0, Real::Epsilon()}, {Real::Epsilon(), 1.0}, {0.0, 2.0}}), Real::Epsilon()));
    }

    {
        EXPECT_FALSE(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}
        ).isNear(PointSet({{0.0, 2.0 * Real::Epsilon()}, {Real::Epsilon(), 1.0}, {0.0, 2.0}}), Real::Epsilon()));
    }

    {
        EXPECT_FALSE(PointSet::Empty().isNear(PointSet::Empty(), Real::Epsilon()));
        EXPECT_FALSE(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}).isNear(PointSet::Empty(), Real::Epsilon()));
        EXPECT_FALSE(PointSet::Empty().isNear(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}), Real::Epsilon()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_PointSet, GetSize)
{
    using ostk::mathematics::geometry::d2::object::PointSet;

    {
        EXPECT_EQ(3, PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}).getSize());
    }

    {
        EXPECT_EQ(0, PointSet::Empty().getSize());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_PointSet, DistanceToPoint)
{
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::PointSet;

    {
        EXPECT_EQ(0.0, PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}).distanceTo(Point({0.0, 0.0})));
        EXPECT_EQ(0.0, PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}).distanceTo(Point({0.0, 1.0})));
        EXPECT_EQ(0.0, PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}).distanceTo(Point({0.0, 2.0})));

        EXPECT_EQ(1.0, PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}).distanceTo(Point({0.0, 3.0})));
    }

    {
        EXPECT_ANY_THROW(PointSet::Empty().distanceTo(Point::Undefined()));
        EXPECT_ANY_THROW(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}).distanceTo(Point::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_PointSet, GetPointClosestTo)
{
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::PointSet;

    {
        EXPECT_EQ(Point(0.0, 0.0), PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}).getPointClosestTo({0.0, 0.0}));
        EXPECT_EQ(Point(0.0, 1.0), PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}).getPointClosestTo({0.0, 1.0}));
        EXPECT_EQ(Point(0.0, 2.0), PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}).getPointClosestTo({0.0, 2.0}));
    }

    {
        EXPECT_ANY_THROW(PointSet::Empty().getPointClosestTo(Point::Undefined()));
        EXPECT_ANY_THROW(PointSet::Empty().getPointClosestTo(Point::Origin()));
        EXPECT_ANY_THROW(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}).getPointClosestTo(Point::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_PointSet, ToString)
{
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::PointSet;

    {
        EXPECT_EQ("[[0.0, 2.0], [0.0, 1.0], [0.0, 0.0]]", PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}).toString());
        EXPECT_EQ(
            "[[0.0, 2.0], [0.0, 1.0], [0.0, 0.0]]",
            PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}).toString(Point::Format::Standard)
        );
    }

    {
        EXPECT_EQ(
            "[[0.0000000000, 2.0000000000], [0.0000000000, 1.0000000000], [0.0000000000, 0.0000000000]]",
            PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}).toString(Point::Format::Standard, 10)
        );
    }

    {
        EXPECT_EQ("[]", PointSet::Empty().toString());
    }

    {
        EXPECT_ANY_THROW(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}).toString(Point::Format::WKT));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_PointSet, ConstIterator)
{
    using ostk::core::type::Index;

    using ostk::mathematics::geometry::d2::object::PointSet;

    {
        const PointSet pointSet = {{{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}};

        Index count = 0;

        for (const auto& point : pointSet)
        {
            EXPECT_TRUE(point.isDefined());

            count++;
        }

        EXPECT_EQ(3, count);
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_PointSet, ApplyTransformation)
{
    using ostk::mathematics::object::Vector2d;
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::PointSet;
    using ostk::mathematics::geometry::d2::Transformation;

    // Translation

    {
        PointSet pointSet = {{{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}};

        pointSet.applyTransformation(Transformation::Translation({4.0, 5.0}));

        EXPECT_EQ(PointSet({{4.0, 5.0}, {4.0, 6.0}, {4.0, 7.0}}), pointSet);
    }

    {
        EXPECT_ANY_THROW(PointSet({{0.0, 0.0}, {0.0, 1.0}, {0.0, 2.0}}).applyTransformation(Transformation::Undefined())
        );
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_PointSet, Empty)
{
    using ostk::mathematics::geometry::d2::object::PointSet;

    {
        EXPECT_NO_THROW(PointSet::Empty());
        EXPECT_FALSE(PointSet::Empty().isDefined());
    }
}
