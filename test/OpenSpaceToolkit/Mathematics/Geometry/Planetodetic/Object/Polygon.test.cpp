/// Apache License 2.0

#include <tuple>

#include <OpenSpaceToolkit/Mathematics/Geometry/Angle.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/Planetodetic/Object/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/Planetodetic/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/Planetodetic/Object/Polygon.hpp>

#include <Global.test.hpp>

using ostk::core::container::Array;
using ostk::core::type::String;

using ostk::mathematics::geometry::Angle;
using ostk::mathematics::geometry::planetodetic::object::Ellipsoid;
using ostk::mathematics::geometry::planetodetic::object::Point;
using ostk::mathematics::geometry::planetodetic::object::Polygon;

class OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Polygon : public ::testing::Test
{
   protected:
    const Ellipsoid ellipsoid_ = Ellipsoid::Spheroid(1000.0, 0.01);
    const Ellipsoid differentEllipsoid_ = Ellipsoid::Spheroid(2000.0, 0.02);

    const Array<Point> vertices_ = {
        Point(Angle::Degrees(-1.0), Angle::Degrees(-1.0)),
        Point(Angle::Degrees(-1.0), Angle::Degrees(1.0)),
        Point(Angle::Degrees(1.0), Angle::Degrees(1.0)),
        Point(Angle::Degrees(1.0), Angle::Degrees(-1.0))
    };

    const Array<Point> differentVertices_ = {
        Point(Angle::Degrees(10.0), Angle::Degrees(10.0)),
        Point(Angle::Degrees(10.0), Angle::Degrees(20.0)),
        Point(Angle::Degrees(-10.0), Angle::Degrees(20.0)),
        Point(Angle::Degrees(-10.0), Angle::Degrees(10.0))
    };

    const Polygon polygon_ = Polygon::Simple(ellipsoid_, vertices_);
    const Polygon differentPolygon_ = Polygon::Simple(ellipsoid_, differentVertices_);
};

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Polygon, Clone)
{
    {
        EXPECT_NO_THROW(const Polygon* polygonPtr = polygon_.clone(); delete polygonPtr;);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Polygon, EqualToOperator)
{
    {
        EXPECT_TRUE(polygon_ == polygon_);
    }

    {
        EXPECT_FALSE(polygon_ == Polygon::Simple(differentEllipsoid_, vertices_));
    }

    {
        EXPECT_FALSE(polygon_ == differentPolygon_);
    }

    {
        EXPECT_FALSE(polygon_ == Polygon::Undefined());
        EXPECT_FALSE(Polygon::Undefined() == polygon_);
        EXPECT_FALSE(Polygon::Undefined() == Polygon::Undefined());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Polygon, NotEqualToOperator)
{
    {
        EXPECT_FALSE(polygon_ != polygon_);
    }

    {
        EXPECT_TRUE(polygon_ != Polygon::Simple(differentEllipsoid_, vertices_));
    }

    {
        EXPECT_TRUE(polygon_ != differentPolygon_);
    }

    {
        EXPECT_TRUE(polygon_ != Polygon::Undefined());
        EXPECT_TRUE(Polygon::Undefined() != polygon_);
        EXPECT_TRUE(Polygon::Undefined() != Polygon::Undefined());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Polygon, StreamOperator)
{
    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << polygon_ << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Polygon, IsDefined)
{
    {
        EXPECT_TRUE(polygon_.isDefined());
    }

    {
        EXPECT_FALSE(Polygon::Undefined().isDefined());
    }

    {
        EXPECT_FALSE(Polygon::Simple(Ellipsoid::Undefined(), vertices_).isDefined());
    }

    {
        EXPECT_FALSE(Polygon::Simple(ellipsoid_, Array<Point>::Empty()).isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Polygon, ContainsNotSupported)
{
    {
        const Ellipsoid nonAxisymmetricEllipsoid = Ellipsoid(1000.0, 1100.0, 900.0);
        const Polygon polygon = Polygon::Simple(nonAxisymmetricEllipsoid, vertices_);

        EXPECT_THROW(
            try {
                polygon.contains(Point(Angle::Degrees(0.0), Angle::Degrees(0.0)));
            } catch (const ostk::core::error::RuntimeError& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("axisymmetric") != std::string::npos);
                throw;
            },
            ostk::core::error::RuntimeError
        );
    }

    {
        const Ellipsoid prolateSpheroid = Ellipsoid(1000.0, 1000.0, 1100.0);
        const Polygon polygon = Polygon::Simple(prolateSpheroid, vertices_);

        EXPECT_THROW(
            try {
                polygon.contains(Point(Angle::Degrees(0.0), Angle::Degrees(0.0)));
            } catch (const ostk::core::error::RuntimeError& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("prolate") != std::string::npos);
                throw;
            },
            ostk::core::error::RuntimeError
        );
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Polygon, GetEllipsoid)
{
    {
        const Polygon& polygon = polygon_;

        EXPECT_EQ(ellipsoid_, polygon.getEllipsoid());
    }

    {
        EXPECT_THROW(
            try { Polygon::Undefined().getEllipsoid(); } catch (const ostk::core::error::runtime::Undefined& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("undefined") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Undefined
        );
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Polygon, GetVertexCount)
{
    {
        const Polygon& polygon = polygon_;

        EXPECT_EQ(4, polygon.getVertexCount());
    }

    {
        EXPECT_THROW(
            try { Polygon::Undefined().getVertexCount(); } catch (const ostk::core::error::runtime::Undefined& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("undefined") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Undefined
        );
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Polygon, GetVertices)
{
    {
        const Polygon& polygon = polygon_;

        EXPECT_EQ(vertices_, polygon.getVertices());
    }

    {
        EXPECT_THROW(
            try { Polygon::Undefined().getVertices(); } catch (const ostk::core::error::runtime::Undefined& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("undefined") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Undefined
        );
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Polygon, ToString)
{
    {
        const Polygon& polygon = polygon_;

        EXPECT_FALSE(polygon.toString().empty());
        EXPECT_FALSE(polygon.toString(Polygon::Format::Standard).empty());
    }

    {
        const Polygon& polygon = polygon_;

        EXPECT_FALSE(polygon.toString(Polygon::Format::Standard, 10).empty());
    }

    {
        EXPECT_THROW(
            try { Polygon::Undefined().toString(); } catch (const ostk::core::error::runtime::Undefined& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("undefined") != std::string::npos);
                throw;
            },
            ostk::core::error::runtime::Undefined
        );
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Polygon, Undefined)
{
    {
        EXPECT_NO_THROW(Polygon::Undefined());
        EXPECT_FALSE(Polygon::Undefined().isDefined());
    }
}

// Parametrized test structure for Contains method
struct ContainsTestParams
{
    String name;
    Array<std::tuple<double, double>> polygonVertices;   // (latitude, longitude) in degrees
    Array<std::tuple<double, double, bool>> testPoints;  // (latitude, longitude, expected_contains) in degrees
};

class OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Polygon_Contains_Parametrized
    : public ::testing::TestWithParam<ContainsTestParams>
{
   protected:
    const Ellipsoid ellipsoid_ = Ellipsoid::WGS84();
};

INSTANTIATE_TEST_SUITE_P(
    ContainsTests,
    OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Polygon_Contains_Parametrized,
    ::testing::Values(
        ContainsTestParams {
            "around_origin",
            {{-10.0, -10.0}, {-10.0, 10.0}, {10.0, 10.0}, {10.0, -10.0}},
            {// Basic points
             {0.0, 0.0, true},
             {0.0, 180.0, false},
             {90.0, 0.0, false},
             {-90.0, 0.0, false},
             // Edges
             {-10.0, -10.0, true},
             {-10.0, 10.0, true},
             {10.0, 10.0, true},
             {10.0, -10.0, true},
             // Walk around the edges jumping in and out
             {-10.2, -10.2, false},
             {-9.8, -9.8, true},
             {-10.2, 0.0, false},
             {-9.8, 0.0, true},
             {-10.2, 10.2, false},
             {-9.8, 9.8, true},
             {0.0, 10.2, false},
             {0.0, 9.8, true},
             {10.2, 10.2, false},
             {9.8, 9.8, true},
             {10.2, 0.0, false},
             {0.8, 0.0, true},
             {10.2, -10.2, false},
             {9.8, -9.8, true},
             {0.0, -10.2, false},
             {0.0, -9.8, true}
            }
        },
        ContainsTestParams {
            "around_anti_meridian",
            {{-10.0, 170.0}, {-10.0, -170.0}, {10.0, -170.0}, {10.0, 170.0}},
            {
                // Basic points
                {0.0, 0.0, false},
                {0.0, 180.0, true},
                {90.0, 0.0, false},
                {-90.0, 0.0, false},
                // Edges
                {-10.0, 170.0, true},
                {-10.0, -170.0, true},
                {10.0, -170.0, true},
                {10.0, 170.0, true},
                // Walk around the edges jumping in and out
                {-10.2, 169.8, false},
                {-9.8, 170.2, true},
                {-10.2, 180.0, false},
                {-9.8, 180.0, true},
                {-10.2, -169.8, false},
                {-9.8, -170.2, true},
                {0.0, -169.8, false},
                {0.0, -170.2, true},
                {10.2, -169.8, false},
                {9.8, -170.2, true},
                {10.2, 180.0, false},
                {9.8, 180.0, true},
                {10.2, 169.8, false},
                {9.8, 170.2, true},
                {0.0, 169.8, false},
                {0.0, 170.2, true},
            }
        },
        ContainsTestParams {
            "around_north_pole",
            {{80.0, 0.0}, {80.0, 120.0}, {80.0, 240.0}},
            {{0.0, 0.0, false}, {0.0, 180.0, false}, {90.0, 0.0, true}, {-90.0, 0.0, false}}
        },
        ContainsTestParams {
            "around_south_pole",
            {{-80.0, 0.0}, {-80.0, 120.0}, {-80.0, 240.0}},
            {{0.0, 0.0, false}, {0.0, 180.0, false}, {90.0, 0.0, false}, {-90.0, 0.0, true}}
        },
        ContainsTestParams {
            "approximately_northern_hemisphere",
            {{0.01, 0.0}, {0.0, 120.0}, {0.0, 240.0}},
            {// Check poles
             {90.0, 0.0, true},
             {-90.0, 0.0, false},
             // Check a "belt" of points just north and south of the equator
             {1.0, 0.0, true},
             {1.0, 120.0, true},
             {1.0, 240.0, true},
             {-1.0, 0.0, false},
             {-1.0, 120.0, false},
             {-1.0, 240.0, false}
            }
        },
        ContainsTestParams {
            "approximately_southern_hemisphere",
            {{-0.01, 0.0}, {0.0, 240.0}, {0.0, 120.0}},
            {// Check poles
             {90.0, 0.0, false},
             {-90.0, 0.0, true},
             // Check a "belt" of points just north and south of the equator
             {1.0, 0.0, false},
             {1.0, 120.0, false},
             {1.0, 240.0, false},
             {-1.0, 0.0, true},
             {-1.0, 120.0, true},
             {-1.0, 240.0, true}
            }
        },
        ContainsTestParams {
            "pacific_ocean",
            {{54.0, 164.0}, {21.0, 130.0}, {-36.0, -175.0}, {-68.0, 176.0}, {-67.0, -83.0}, {3.0, -90.0}, {55.0, -146.0}
            },
            {// Walk around the pacific ocean, checking points outside of it
             {-6.0, 127.0, false},
             {-77.0, -125.0, false},
             {-46.0, -53.0, false},
             {44.0, -116.0, false},
             {69.0, -176.0, false},
             {-57.0, 157.0, false},
             // Check points inside
             {6.0, 170.0, true},
             {31.0, -157.0, true},
             {-50.0, -125.0, true}
            }
        }
    ),
    [](const ::testing::TestParamInfo<ContainsTestParams>& paramInfo)
    {
        return paramInfo.param.name;
    }
);

TEST_P(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Polygon_Contains_Parametrized, Contains)
{
    const auto& params = GetParam();

    Array<Point> vertices;
    for (const auto& vertex : params.polygonVertices)
    {
        const double latitude = std::get<0>(vertex);
        const double longitude = std::get<1>(vertex);
        vertices.add(Point(Angle::Degrees(latitude), Angle::Degrees(longitude)));
    }

    const Polygon polygon = Polygon::Simple(ellipsoid_, vertices);

    for (const auto& testPoint : params.testPoints)
    {
        const double latitude = std::get<0>(testPoint);
        const double longitude = std::get<1>(testPoint);
        const bool expectedContains = std::get<2>(testPoint);

        const Point point(Angle::Degrees(latitude), Angle::Degrees(longitude));

        EXPECT_EQ(expectedContains, polygon.contains(point))
            << "Failed for point (" << latitude << "°, " << longitude << "°) in test case: " << params.name;
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Polygon, Simple)
{
    {
        EXPECT_NO_THROW(Polygon::Simple(ellipsoid_, vertices_););
    }

    {
        EXPECT_NO_THROW(Polygon::Simple(ellipsoid_, Array<Point>::Empty()););
    }

    {
        {
            const Array<Point> verticesWithUndefined = {
                Point::Undefined(),
                Point(Angle::Degrees(0.0), Angle::Degrees(1.0)),
                Point(Angle::Degrees(1.0), Angle::Degrees(1.0)),
                Point(Angle::Degrees(1.0), Angle::Degrees(0.0))
            };

            EXPECT_THROW(
                try {
                    Polygon::Simple(ellipsoid_, verticesWithUndefined);
                } catch (const ostk::core::error::RuntimeError& e) {
                    EXPECT_TRUE(std::string(e.getMessage()).find("ill-defined") != std::string::npos);
                    throw;
                },
                ostk::core::error::RuntimeError
            );
        }
    }

    {
        const Array<Point> twoVertices = {
            Point(Angle::Degrees(-10.0), Angle::Degrees(-10.0)), Point(Angle::Degrees(-10.0), Angle::Degrees(10.0))
        };

        EXPECT_THROW(
            try { Polygon::Simple(ellipsoid_, twoVertices); } catch (const ostk::core::error::RuntimeError& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("ill-defined") != std::string::npos);
                throw;
            },
            ostk::core::error::RuntimeError
        );
    }

    {
        const Array<Point> collinearVertices = {
            Point(Angle::Degrees(0.0), Angle::Degrees(0.0)),
            Point(Angle::Degrees(0.0), Angle::Degrees(120.0)),
            Point(Angle::Degrees(0.0), Angle::Degrees(240.0))
        };

        EXPECT_THROW(
            try { Polygon::Simple(ellipsoid_, collinearVertices); } catch (const ostk::core::error::RuntimeError& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("ill-defined") != std::string::npos);
                throw;
            },
            ostk::core::error::RuntimeError
        );
    }

    {
        const Array<Point> intersectingVertices = {
            Point(Angle::Degrees(-1.0), Angle::Degrees(-1.0)),
            Point(Angle::Degrees(1.0), Angle::Degrees(1.0)),
            Point(Angle::Degrees(-1.0), Angle::Degrees(1.0)),
            Point(Angle::Degrees(1.0), Angle::Degrees(-1.0))
        };

        EXPECT_THROW(
            try {
                Polygon::Simple(ellipsoid_, intersectingVertices);
            } catch (const ostk::core::error::RuntimeError& e) {
                EXPECT_TRUE(std::string(e.getMessage()).find("ill-defined") != std::string::npos);
                throw;
            },
            ostk::core::error::RuntimeError
        );
    }
}
