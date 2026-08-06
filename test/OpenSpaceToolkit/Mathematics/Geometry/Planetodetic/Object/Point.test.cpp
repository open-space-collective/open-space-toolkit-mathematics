/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/Angle.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/Planetodetic/Object/Point.hpp>

#include <Global.test.hpp>

using ostk::core::type::String;

using ostk::mathematics::geometry::Angle;
using ostk::mathematics::geometry::planetodetic::object::Point;

class OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Point : public ::testing::Test
{
   protected:
    const Point point_ = Point(Angle::Degrees(45.0), Angle::Degrees(-122.0));
    const Point differentPoint_ = Point(Angle::Degrees(30.0), Angle::Degrees(100.0));
};

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Point, Constructor)
{
    {
        EXPECT_NO_THROW(Point point(Angle::Degrees(45.0), Angle::Degrees(-122.0)););
    }

    {
        EXPECT_NO_THROW(Point point(Angle::Degrees(0.0), Angle::Degrees(0.0)););
    }

    {
        EXPECT_NO_THROW(Point point(Angle::Degrees(90.0), Angle::Degrees(180.0)););
    }

    {
        EXPECT_NO_THROW(Point point(Angle::Degrees(-90.0), Angle::Degrees(-180.0)););
    }

    // Test latitude validation - out of range
    {
        EXPECT_THROW(
            try {
                Point point(Angle::Degrees(91.0), Angle::Degrees(0.0));
            } catch (const ostk::core::error::runtime::Wrong& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("Latitude") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Wrong
        );
    }

    {
        EXPECT_THROW(
            try {
                Point point(Angle::Degrees(-91.0), Angle::Degrees(0.0));
            } catch (const ostk::core::error::runtime::Wrong& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("Latitude") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Wrong
        );
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Point, Clone)
{
    {
        EXPECT_NO_THROW(const Point* pointPtr = point_.clone(); delete pointPtr;);
    }

    {
        const Point* pointPtr = point_.clone();

        EXPECT_EQ(*pointPtr, point_);

        delete pointPtr;
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Point, EqualToOperator)
{
    {
        EXPECT_TRUE(point_ == point_);
    }

    {
        EXPECT_TRUE(Point(Angle::Degrees(45.0), Angle::Degrees(-122.0)) == point_);
    }

    {
        EXPECT_FALSE(point_ == differentPoint_);
    }

    {
        EXPECT_FALSE(Point(Angle::Degrees(45.0), Angle::Degrees(0.0)) == point_);
    }

    {
        EXPECT_FALSE(Point(Angle::Degrees(0.0), Angle::Degrees(-122.0)) == point_);
    }

    // Test longitude normalization
    {
        const Point point1(Angle::Degrees(0.0), Angle::Degrees(370.0));
        const Point point2(Angle::Degrees(0.0), Angle::Degrees(10.0));

        EXPECT_TRUE(point1 == point2);
    }

    {
        const Point point1(Angle::Degrees(0.0), Angle::Degrees(-190.0));
        const Point point2(Angle::Degrees(0.0), Angle::Degrees(170.0));

        EXPECT_TRUE(point1 == point2);
    }

    {
        const Point point1(Angle::Degrees(0.0), Angle::Degrees(180.0));
        const Point point2(Angle::Degrees(0.0), Angle::Degrees(-180.0));

        EXPECT_TRUE(point1 == point2);
    }

    // Test poles
    {
        const Point point1(Angle::Degrees(90.0), Angle::Degrees(0.0));
        const Point point2(Angle::Degrees(90.0), Angle::Degrees(180.0));

        EXPECT_TRUE(point1 == point2);
    }

    {
        const Point point1(Angle::Degrees(-90.0), Angle::Degrees(0.0));
        const Point point2(Angle::Degrees(-90.0), Angle::Degrees(180.0));

        EXPECT_TRUE(point1 == point2);
    }

    {
        EXPECT_FALSE(point_ == Point::Undefined());
        EXPECT_FALSE(Point::Undefined() == point_);
        EXPECT_FALSE(Point::Undefined() == Point::Undefined());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Point, NotEqualToOperator)
{
    {
        EXPECT_FALSE(point_ != point_);
    }

    {
        EXPECT_FALSE(Point(Angle::Degrees(45.0), Angle::Degrees(-122.0)) != point_);
    }

    {
        EXPECT_TRUE(point_ != differentPoint_);
    }

    {
        EXPECT_TRUE(Point(Angle::Degrees(45.0), Angle::Degrees(0.0)) != point_);
    }

    {
        EXPECT_TRUE(Point(Angle::Degrees(0.0), Angle::Degrees(-122.0)) != point_);
    }

    // Test poles
    {
        const Point point1(Angle::Degrees(90.0), Angle::Degrees(0.0));
        const Point point2(Angle::Degrees(90.0), Angle::Degrees(180.0));

        EXPECT_FALSE(point1 != point2);
    }

    {
        const Point point1(Angle::Degrees(-90.0), Angle::Degrees(0.0));
        const Point point2(Angle::Degrees(-90.0), Angle::Degrees(180.0));

        EXPECT_FALSE(point1 != point2);
    }

    // Test longitude normalization
    {
        const Point point1(Angle::Degrees(0.0), Angle::Degrees(370.0));
        const Point point2(Angle::Degrees(0.0), Angle::Degrees(10.0));

        EXPECT_FALSE(point1 != point2);
    }

    {
        const Point point1(Angle::Degrees(0.0), Angle::Degrees(-190.0));
        const Point point2(Angle::Degrees(0.0), Angle::Degrees(170.0));

        EXPECT_FALSE(point1 != point2);
    }

    {
        const Point point1(Angle::Degrees(0.0), Angle::Degrees(180.0));
        const Point point2(Angle::Degrees(0.0), Angle::Degrees(-180.0));

        EXPECT_FALSE(point1 != point2);
    }

    {
        EXPECT_TRUE(point_ != Point::Undefined());
        EXPECT_TRUE(Point::Undefined() != point_);
        EXPECT_TRUE(Point::Undefined() != Point::Undefined());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Point, StreamOperator)
{
    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << point_ << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Point, IsDefined)
{
    {
        EXPECT_TRUE(point_.isDefined());
    }

    {
        EXPECT_TRUE(Point(Angle::Degrees(0.0), Angle::Degrees(0.0)).isDefined());
    }

    {
        EXPECT_FALSE(Point::Undefined().isDefined());
    }

    {
        EXPECT_FALSE(Point(Angle::Undefined(), Angle::Degrees(0.0)).isDefined());
    }

    {
        EXPECT_FALSE(Point(Angle::Degrees(0.0), Angle::Undefined()).isDefined());
    }

    {
        EXPECT_FALSE(Point(Angle::Undefined(), Angle::Undefined()).isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Point, GetLatitude)
{
    {
        EXPECT_EQ(Angle::Degrees(45.0), point_.getLatitude());
    }

    {
        EXPECT_EQ(Angle::Degrees(0.0), Point(Angle::Degrees(0.0), Angle::Degrees(0.0)).getLatitude());
    }

    {
        EXPECT_EQ(Angle::Degrees(90.0), Point::NorthPole().getLatitude());
    }

    {
        EXPECT_EQ(Angle::Degrees(-90.0), Point::SouthPole().getLatitude());
    }

    {
        EXPECT_THROW(
            try { Point::Undefined().getLatitude(); } catch (const ostk::core::error::runtime::Undefined& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("Point") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Undefined
        );
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Point, GetLongitude)
{
    {
        EXPECT_EQ(Angle::Degrees(-122.0), point_.getLongitude());
    }

    {
        EXPECT_EQ(Angle::Degrees(0.0), Point(Angle::Degrees(0.0), Angle::Degrees(0.0)).getLongitude());
    }

    {
        EXPECT_EQ(Angle::Degrees(0.0), Point::Origin().getLongitude());
    }

    {
        const Point point(Angle::Degrees(0.0), Angle::Degrees(370.0));
        EXPECT_EQ(Angle::Degrees(10.0), point.getLongitude());
    }

    {
        const Point point(Angle::Degrees(0.0), Angle::Degrees(-190.0));
        EXPECT_EQ(Angle::Degrees(170.0), point.getLongitude());
    }

    {
        EXPECT_THROW(
            try { Point::Undefined().getLongitude(); } catch (const ostk::core::error::runtime::Undefined& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("Point") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Undefined
        );
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Point, IsCollinear)
{
    // Same parallel
    {
        const Point a(Angle::Degrees(0.0), Angle::Degrees(0.0));
        const Point b(Angle::Degrees(0.0), Angle::Degrees(45.0));
        const Point c(Angle::Degrees(0.0), Angle::Degrees(90.0));

        EXPECT_TRUE(a.isCollinear(b, c));
    }

    // Same meridian
    {
        const Point a(Angle::Degrees(-30.0), Angle::Degrees(0.0));
        const Point b(Angle::Degrees(0.0), Angle::Degrees(0.0));
        const Point c(Angle::Degrees(30.0), Angle::Degrees(0.0));

        EXPECT_TRUE(a.isCollinear(b, c));
    }

    // Same point
    {
        const Point a(Angle::Degrees(0.0), Angle::Degrees(0.0));
        const Point b(Angle::Degrees(10.0), Angle::Degrees(10.0));

        EXPECT_TRUE(a.isCollinear(a, b));
        EXPECT_TRUE(a.isCollinear(b, a));
        EXPECT_TRUE(a.isCollinear(b, b));
        EXPECT_TRUE(a.isCollinear(a, a));
    }

    // Non-collinear points
    {
        const Point a(Angle::Degrees(0.0), Angle::Degrees(0.0));
        const Point b(Angle::Degrees(0.0), Angle::Degrees(45.0));
        const Point c(Angle::Degrees(10.0), Angle::Degrees(90.0));

        EXPECT_FALSE(a.isCollinear(b, c));
    }

    // Test with undefined points
    {
        const Point a(Angle::Degrees(0.0), Angle::Degrees(0.0));
        const Point b(Angle::Degrees(0.0), Angle::Degrees(45.0));

        EXPECT_THROW(
            try { a.isCollinear(b, Point::Undefined()); } catch (const ostk::core::error::runtime::Undefined& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("Point") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Undefined
        );

        EXPECT_THROW(
            try { a.isCollinear(Point::Undefined(), b); } catch (const ostk::core::error::runtime::Undefined& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("Point") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Undefined
        );

        EXPECT_THROW(
            try { Point::Undefined().isCollinear(a, b); } catch (const ostk::core::error::runtime::Undefined& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("Point") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Undefined
        );
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Point, ToString)
{
    {
        EXPECT_FALSE(point_.toString().empty());
    }

    {
        EXPECT_FALSE(point_.toString(Point::Format::Standard).empty());
    }

    {
        EXPECT_FALSE(point_.toString(Point::Format::Standard, 10).empty());
    }

    {
        const String str = point_.toString();
        EXPECT_TRUE(str.find("45") != String::npos);
        EXPECT_TRUE(str.find("122") != String::npos);
    }

    {
        EXPECT_THROW(
            try { Point::Undefined().toString(); } catch (const ostk::core::error::runtime::Undefined& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("undefined") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Undefined
        );
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Point, Print)
{
    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(point_.print(std::cout, true));

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }

    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(point_.print(std::cout, false));

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Point, Undefined)
{
    {
        EXPECT_NO_THROW(Point::Undefined());
        EXPECT_FALSE(Point::Undefined().isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Point, Origin)
{
    {
        EXPECT_NO_THROW(Point::Origin());
        EXPECT_TRUE(Point::Origin().isDefined());
    }

    {
        const Point origin = Point::Origin();

        EXPECT_EQ(Angle::Degrees(0.0), origin.getLatitude());
        EXPECT_EQ(Angle::Degrees(0.0), origin.getLongitude());
    }

    {
        EXPECT_EQ(Point(Angle::Degrees(0.0), Angle::Degrees(0.0)), Point::Origin());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Point, NorthPole)
{
    {
        EXPECT_NO_THROW(Point::NorthPole());
        EXPECT_TRUE(Point::NorthPole().isDefined());
    }

    {
        const Point northPole = Point::NorthPole();

        EXPECT_EQ(Angle::Degrees(90.0), northPole.getLatitude());
        EXPECT_EQ(Angle::Degrees(0.0), northPole.getLongitude());
    }

    {
        EXPECT_EQ(Point(Angle::Degrees(90.0), Angle::Degrees(0.0)), Point::NorthPole());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Point, SouthPole)
{
    {
        EXPECT_NO_THROW(Point::SouthPole());
        EXPECT_TRUE(Point::SouthPole().isDefined());
    }

    {
        const Point southPole = Point::SouthPole();

        EXPECT_EQ(Angle::Degrees(-90.0), southPole.getLatitude());
        EXPECT_EQ(Angle::Degrees(0.0), southPole.getLongitude());
    }

    {
        EXPECT_EQ(Point(Angle::Degrees(-90.0), Angle::Degrees(0.0)), Point::SouthPole());
    }
}
