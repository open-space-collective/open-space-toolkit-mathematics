/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/LineString.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Transformation.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_LineString, Constructor)
{
    using ostk::mathematics::geometry::d2::object::LineString;
    using ostk::mathematics::geometry::d2::object::Point;

    {
        EXPECT_NO_THROW(LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}));
    }

    {
        EXPECT_NO_THROW(LineString({{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}}));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_LineString, Clone)
{
    using ostk::mathematics::geometry::d2::object::LineString;

    {
        EXPECT_NO_THROW(const LineString* lineStringPtr = LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}).clone();
                        delete lineStringPtr;);
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_LineString, EqualToOperator)
{
    using ostk::mathematics::geometry::d2::object::LineString;

    {
        EXPECT_TRUE(
            LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}) == LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}})
        );

        EXPECT_TRUE(LineString::Empty() == LineString::Empty());
    }

    {
        EXPECT_FALSE(
            LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}) == LineString({{0.0, 0.0}, {0.0, 2.0}, {0.0, 1.0}})
        );
        EXPECT_FALSE(
            LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}) == LineString({{0.0, 1.0}, {0.0, 0.0}, {0.0, 2.0}})
        );
        EXPECT_FALSE(
            LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}) == LineString({{0.0, 1.0}, {0.0, 2.0}, {0.0, 0.0}})
        );
        EXPECT_FALSE(
            LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}) == LineString({{0.0, 2.0}, {0.0, 0.0}, {0.0, 1.0}})
        );
        EXPECT_FALSE(
            LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}) == LineString({{0.0, 2.0}, {0.0, 1.0}, {0.0, 0.0}})
        );

        EXPECT_FALSE(
            LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}) ==
            LineString({{0.0, 0.0}, {0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}})
        );

        EXPECT_FALSE(
            LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}) == LineString({{0.0, 0.0}, {0.0, 1.0}, {0.0, 3.0}})
        );
    }

    {
        EXPECT_FALSE(LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}) == LineString::Empty());
        EXPECT_FALSE(LineString::Empty() == LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_LineString, NotEqualToOperator)
{
    using ostk::mathematics::geometry::d2::object::LineString;

    {
        EXPECT_FALSE(
            LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}) != LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}})
        );

        EXPECT_FALSE(LineString::Empty() != LineString::Empty());
    }

    {
        EXPECT_TRUE(
            LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}) != LineString({{0.0, 0.0}, {0.0, 2.0}, {0.0, 1.0}})
        );
        EXPECT_TRUE(
            LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}) != LineString({{0.0, 1.0}, {0.0, 0.0}, {0.0, 2.0}})
        );
        EXPECT_TRUE(
            LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}) != LineString({{0.0, 1.0}, {0.0, 2.0}, {0.0, 0.0}})
        );
        EXPECT_TRUE(
            LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}) != LineString({{0.0, 2.0}, {0.0, 0.0}, {0.0, 1.0}})
        );
        EXPECT_TRUE(
            LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}) != LineString({{0.0, 2.0}, {0.0, 1.0}, {0.0, 0.0}})
        );

        EXPECT_TRUE(
            LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}) !=
            LineString({{0.0, 0.0}, {0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}})
        );

        EXPECT_TRUE(
            LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}) != LineString({{0.0, 0.0}, {0.0, 1.0}, {0.0, 3.0}})
        );
    }

    {
        EXPECT_TRUE(LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}) != LineString::Empty());
        EXPECT_TRUE(LineString::Empty() != LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_LineString, StreamOperator)
{
    using ostk::mathematics::geometry::d2::object::LineString;

    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}) << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_LineString, IsDefined)
{
    using ostk::mathematics::geometry::d2::object::LineString;

    {
        EXPECT_TRUE(LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}).isDefined());
        EXPECT_TRUE(LineString({{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}}).isDefined());
    }

    {
        EXPECT_FALSE(LineString::Empty().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_LineString, IsEmpty)
{
    using ostk::mathematics::geometry::d2::object::LineString;

    {
        EXPECT_FALSE(LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}).isEmpty());
        EXPECT_FALSE(LineString({{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}}).isEmpty());
    }

    {
        EXPECT_TRUE(LineString::Empty().isEmpty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_LineString, Contains)
{
    using ostk::core::container::Array;

    using ostk::mathematics::geometry::d2::object::LineString;
    using ostk::mathematics::geometry::d2::object::Point;

    {
        const Point point = {1.0, 0.0};

        EXPECT_ANY_THROW(LineString::Empty().contains(point));
    }

    {
        const LineString lineString = LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}});

        EXPECT_ANY_THROW(lineString.contains(Point::Undefined()));
    }

    {
        const Point point = {1.0, 0.0};

        const Array<Point> pointArray = {point};

        const LineString lineString = LineString(pointArray);

        EXPECT_TRUE(lineString.contains(point));
    }

    {
        const LineString lineString = LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}});

        const Point point = {1.0, 0.0};

        EXPECT_TRUE(lineString.contains(point));
    }

    {
        const LineString lineString = LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}});

        const Point point = {0.0, 0.5};

        EXPECT_TRUE(lineString.contains(point));
    }

    {
        const LineString lineString = LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}});

        const Point point = {3.0, 3.0};

        EXPECT_FALSE(lineString.contains(point));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_LineString, IsNear)
{
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::d2::object::LineString;

    {
        EXPECT_TRUE(LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}
        ).isNear(LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}), Real::Epsilon()));

        EXPECT_TRUE(LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}
        ).isNear(LineString({{0.0, Real::Epsilon()}, {Real::Epsilon(), 1.0}, {1.0, 0.0}}), Real::Epsilon()));
    }

    {
        EXPECT_FALSE(LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}
        ).isNear(LineString({{0.0, 2.0 * Real::Epsilon()}, {Real::Epsilon(), 1.0}, {1.0, 0.0}}), Real::Epsilon()));
    }

    {
        EXPECT_FALSE(LineString::Empty().isNear(LineString::Empty(), Real::Epsilon()));
        EXPECT_FALSE(LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}).isNear(LineString::Empty(), Real::Epsilon()));
        EXPECT_FALSE(LineString::Empty().isNear(LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}), Real::Epsilon()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_LineString, GetPointArray)
{
    using ostk::core::container::Array;

    using ostk::mathematics::geometry::d2::object::LineString;
    using ostk::mathematics::geometry::d2::object::Point;

    {
        Array<Point> pointArray = {{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}, {0.0, 0.0}};

        EXPECT_EQ(pointArray, LineString(pointArray).getPointArray());
    }

    {
        EXPECT_EQ(Array<Point>::Empty(), LineString::Empty().getPointArray());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_LineString, AccessPointAt)
{
    using ostk::mathematics::geometry::d2::object::LineString;
    using ostk::mathematics::geometry::d2::object::Point;

    {
        EXPECT_EQ(Point(0.0, 0.0), LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}, {0.0, 0.0}}).accessPointAt(0));
        EXPECT_EQ(Point(0.0, 1.0), LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}, {0.0, 0.0}}).accessPointAt(1));
        EXPECT_EQ(Point(1.0, 0.0), LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}, {0.0, 0.0}}).accessPointAt(2));
        EXPECT_EQ(Point(0.0, 0.0), LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}, {0.0, 0.0}}).accessPointAt(3));

        EXPECT_ANY_THROW(LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}, {0.0, 0.0}}).accessPointAt(5));
    }

    {
        EXPECT_ANY_THROW(LineString::Empty().accessPointAt(0));
        EXPECT_ANY_THROW(LineString::Empty().accessPointAt(1));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_LineString, GetPointCount)
{
    using ostk::mathematics::geometry::d2::object::LineString;

    {
        EXPECT_EQ(4, LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}, {0.0, 0.0}}).getPointCount());
    }

    {
        EXPECT_EQ(0, LineString::Empty().getPointCount());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_LineString, ToString)
{
    using ostk::mathematics::geometry::d2::object::LineString;
    using ostk::mathematics::geometry::d2::object::Point;

    {
        EXPECT_EQ(
            "[[0.0, 0.0] -> [0.0, 1.0] -> [1.0, 0.0]]", LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}).toString()
        );
        EXPECT_EQ(
            "[[0.0, 0.0] -> [0.0, 1.0] -> [1.0, 0.0]]",
            LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}).toString(Point::Format::Standard)
        );
        EXPECT_EQ(
            "LINESTRING(0.0 0.0, 0.0 1.0, 1.0 0.0)",
            LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}).toString(Point::Format::WKT)
        );
    }

    {
        EXPECT_EQ(
            "[[0.0000000000, 0.0000000000] -> [0.0000000000, 1.0000000000] -> [1.0000000000, 0.0000000000]]",
            LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}).toString(Point::Format::Standard, 10)
        );
        EXPECT_EQ(
            "LINESTRING(0.0000000000 0.0000000000, 0.0000000000 1.0000000000, 1.0000000000 0.0000000000)",
            LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}).toString(Point::Format::WKT, 10)
        );
    }

    {
        EXPECT_EQ("[]", LineString::Empty().toString());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_LineString, ConstIterator)
{
    using ostk::core::type::Index;

    using ostk::mathematics::geometry::d2::object::LineString;

    {
        const LineString lineString = {{{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}};

        Index count = 0;

        for (const auto& point : lineString)
        {
            EXPECT_TRUE(point.isDefined());

            count++;
        }

        EXPECT_EQ(3, count);
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_LineString, ApplyTransformation)
{
    using ostk::mathematics::geometry::d2::object::LineString;
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::Transformation;
    using ostk::mathematics::object::Vector2d;

    // Translation

    {
        LineString lineString = {{{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}};

        lineString.applyTransformation(Transformation::Translation({4.0, 5.0}));

        EXPECT_EQ(LineString({{4.0, 5.0}, {4.0, 6.0}, {5.0, 5.0}}), lineString) << lineString;
    }

    {
        EXPECT_ANY_THROW(LineString({{0.0, 0.0}, {0.0, 1.0}, {1.0, 0.0}}
        ).applyTransformation(Transformation::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_LineString, Empty)
{
    using ostk::mathematics::geometry::d2::object::LineString;

    {
        EXPECT_NO_THROW(LineString::Empty());
        EXPECT_FALSE(LineString::Empty().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_LineString, Segment)
{
    using ostk::mathematics::geometry::d2::object::LineString;
    using ostk::mathematics::geometry::d2::object::Segment;

    {
        EXPECT_EQ(LineString({{0.0, 0.0}, {0.0, 1.0}}), LineString::Segment(Segment({0.0, 0.0}, {0.0, 1.0})));
    }
}
