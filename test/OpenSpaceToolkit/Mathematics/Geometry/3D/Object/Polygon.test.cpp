/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Polygon, Constructor)
{
    using ostk::mathematics::object::Vector3d;
    using Polygon2d = ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;

    {
        const Polygon2d polygon2d = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point origin = {1.0, 2.0, 3.0};
        const Vector3d xAxis = {1.0, 0.0, 0.0};
        const Vector3d yAxis = {0.0, 1.0, 0.0};

        EXPECT_NO_THROW(Polygon(polygon2d, origin, xAxis, yAxis));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Polygon, Clone)
{
    using ostk::mathematics::object::Vector3d;
    using Polygon2d = ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;

    {
        const Polygon2d polygon2d = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point origin = {1.0, 2.0, 3.0};
        const Vector3d xAxis = {1.0, 0.0, 0.0};
        const Vector3d yAxis = {0.0, 1.0, 0.0};

        EXPECT_NO_THROW(
            const Polygon* polygonPtr = Polygon(polygon2d, origin, xAxis, yAxis).clone(); delete polygonPtr;
        );
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Polygon, EqualToOperator)
{
    using ostk::mathematics::object::Vector3d;
    using Polygon2d = ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;

    {
        const Polygon2d polygon2d = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point origin = {1.0, 2.0, 3.0};
        const Vector3d xAxis = {1.0, 0.0, 0.0};
        const Vector3d yAxis = {0.0, 1.0, 0.0};

        EXPECT_TRUE(Polygon(polygon2d, origin, xAxis, yAxis) == Polygon(polygon2d, origin, xAxis, yAxis));
    }

    {
        // [TBI] Implement similarities
    }

    {
        const Polygon2d polygon2d = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point origin = {1.0, 2.0, 3.0};
        const Vector3d xAxis = {1.0, 0.0, 0.0};
        const Vector3d yAxis = {0.0, 1.0, 0.0};

        EXPECT_FALSE(Polygon(polygon2d, origin, xAxis, yAxis) == Polygon::Undefined());
        EXPECT_FALSE(Polygon::Undefined() == Polygon(polygon2d, origin, xAxis, yAxis));
        EXPECT_FALSE(Polygon::Undefined() == Polygon::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Polygon, NotEqualToOperator)
{
    using ostk::mathematics::object::Vector3d;
    using Polygon2d = ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;

    {
        const Polygon2d polygon2d = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point origin = {1.0, 2.0, 3.0};
        const Vector3d xAxis = {1.0, 0.0, 0.0};
        const Vector3d yAxis = {0.0, 1.0, 0.0};

        EXPECT_FALSE(Polygon(polygon2d, origin, xAxis, yAxis) != Polygon(polygon2d, origin, xAxis, yAxis));
    }

    {
        // [TBI] Implement similarities
    }

    {
        const Polygon2d polygon2d = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point origin = {1.0, 2.0, 3.0};
        const Vector3d xAxis = {1.0, 0.0, 0.0};
        const Vector3d yAxis = {0.0, 1.0, 0.0};

        EXPECT_TRUE(Polygon(polygon2d, origin, xAxis, yAxis) != Polygon::Undefined());
        EXPECT_TRUE(Polygon::Undefined() != Polygon(polygon2d, origin, xAxis, yAxis));
        EXPECT_TRUE(Polygon::Undefined() != Polygon::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Polygon, StreamOperator)
{
    using ostk::mathematics::object::Vector3d;
    using Polygon2d = ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;

    {
        testing::internal::CaptureStdout();

        const Polygon2d polygon2d = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point origin = {1.0, 2.0, 3.0};
        const Vector3d xAxis = {1.0, 0.0, 0.0};
        const Vector3d yAxis = {0.0, 1.0, 0.0};

        EXPECT_NO_THROW(std::cout << Polygon(polygon2d, origin, xAxis, yAxis) << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Polygon, IsDefined)
{
    using ostk::mathematics::object::Vector3d;
    using Polygon2d = ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;

    {
        const Polygon2d polygon2d = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point origin = {1.0, 2.0, 3.0};
        const Vector3d xAxis = {1.0, 0.0, 0.0};
        const Vector3d yAxis = {0.0, 1.0, 0.0};

        EXPECT_TRUE(Polygon(polygon2d, origin, xAxis, yAxis).isDefined());
    }

    {
        EXPECT_FALSE(Polygon::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Polygon, IsNear)
{
    using ostk::core::type::Real;

    using ostk::mathematics::object::Vector3d;
    using Polygon2d = ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;

    {
        const Polygon2d polygon2d = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point origin = {1.0, 2.0, 3.0};
        const Vector3d xAxis = {1.0, 0.0, 0.0};
        const Vector3d yAxis = {0.0, 1.0, 0.0};

        EXPECT_TRUE(Polygon(polygon2d, origin, xAxis, yAxis).isNear(Polygon(polygon2d, origin, xAxis, yAxis), 0.0));
    }

    {
        const Polygon2d polygon2d = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point origin = {1.0, 2.0, 3.0};
        const Vector3d xAxis = {1.0, 0.0, 0.0};
        const Vector3d yAxis = {0.0, 1.0, 0.0};

        EXPECT_TRUE(Polygon(polygon2d, origin, xAxis, yAxis)
                        .isNear(Polygon(polygon2d, {1.0, 2.0, 3.0 + 1e-15}, xAxis, yAxis), 1e-15));
    }

    {
        const Polygon2d polygon2d = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point origin = {1.0, 2.0, 3.0};
        const Vector3d xAxis = {1.0, 0.0, 0.0};
        const Vector3d yAxis = {0.0, 1.0, 0.0};

        EXPECT_TRUE(
            Polygon(polygon2d, origin, xAxis, yAxis)
                .isNear(Polygon({{{0.0, 0.0}, {1.0, 1e-15}, {1.0, 1.0}, {0.0, 1.0}}}, origin, xAxis, yAxis), 1e-15)
        );
    }

    {
        const Polygon2d polygon2d = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point origin = {1.0, 2.0, 3.0};
        const Vector3d xAxis = {1.0, 0.0, 0.0};
        const Vector3d yAxis = {0.0, 1.0, 0.0};

        EXPECT_FALSE(Polygon(polygon2d, origin, xAxis, yAxis)
                         .isNear(
                             Polygon({{{0.0, 0.0}, {1.0, 2.0 * 1e-15}, {1.0, 1.0}, {0.0, 1.0}}}, origin, xAxis, yAxis),
                             1e-15
                         ));
    }

    {
        const Polygon2d polygon2d = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point origin = {1.0, 2.0, 3.0};
        const Vector3d xAxis = {1.0, 0.0, 0.0};
        const Vector3d yAxis = {0.0, 1.0, 0.0};

        EXPECT_ANY_THROW(Polygon::Undefined().isNear(Polygon::Undefined(), Real::Undefined()));
        EXPECT_ANY_THROW(Polygon(polygon2d, origin, xAxis, yAxis).isNear(Polygon::Undefined(), 1.0));
        EXPECT_ANY_THROW(Polygon::Undefined().isNear(Polygon(polygon2d, origin, xAxis, yAxis), 1.0));
        EXPECT_ANY_THROW(
            Polygon(polygon2d, origin, xAxis, yAxis).isNear(Polygon(polygon2d, origin, xAxis, yAxis), Real::Undefined())
        );
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Polygon, GetPolygon2d)
{
    using ostk::mathematics::object::Vector3d;
    using Polygon2d = ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;

    {
        const Polygon2d polygon2d = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point origin = {1.0, 2.0, 3.0};
        const Vector3d xAxis = {1.0, 0.0, 0.0};
        const Vector3d yAxis = {0.0, 1.0, 0.0};

        EXPECT_EQ(polygon2d, Polygon(polygon2d, origin, xAxis, yAxis).getPolygon2d());
    }

    {
        EXPECT_ANY_THROW(Polygon::Undefined().getOrigin());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Polygon, GetOrigin)
{
    using ostk::mathematics::object::Vector3d;
    using Polygon2d = ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;

    {
        const Polygon2d polygon2d = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point origin = {1.0, 2.0, 3.0};
        const Vector3d xAxis = {1.0, 0.0, 0.0};
        const Vector3d yAxis = {0.0, 1.0, 0.0};

        EXPECT_EQ(origin, Polygon(polygon2d, origin, xAxis, yAxis).getOrigin());
    }

    {
        EXPECT_ANY_THROW(Polygon::Undefined().getOrigin());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Polygon, GetXAxis)
{
    using ostk::mathematics::object::Vector3d;
    using Polygon2d = ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;

    {
        const Polygon2d polygon2d = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point origin = {1.0, 2.0, 3.0};
        const Vector3d xAxis = {1.0, 0.0, 0.0};
        const Vector3d yAxis = {0.0, 1.0, 0.0};

        EXPECT_EQ(xAxis, Polygon(polygon2d, origin, xAxis, yAxis).getXAxis());
    }

    {
        EXPECT_ANY_THROW(Polygon::Undefined().getXAxis());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Polygon, GetYAxis)
{
    using ostk::mathematics::object::Vector3d;
    using Polygon2d = ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;

    {
        const Polygon2d polygon2d = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point origin = {1.0, 2.0, 3.0};
        const Vector3d xAxis = {1.0, 0.0, 0.0};
        const Vector3d yAxis = {0.0, 1.0, 0.0};

        EXPECT_EQ(yAxis, Polygon(polygon2d, origin, xAxis, yAxis).getYAxis());
    }

    {
        EXPECT_ANY_THROW(Polygon::Undefined().getYAxis());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Polygon, GetNormalVector)
{
    using ostk::core::type::Real;

    using ostk::mathematics::object::Vector3d;
    using Polygon2d = ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;

    {
        const Polygon2d polygon2d = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point origin = {1.0, 2.0, 3.0};
        const Vector3d xAxis = {1.0, 0.0, 0.0};
        const Vector3d yAxis = {0.0, 1.0, 0.0};

        EXPECT_EQ(Vector3d(0.0, 0.0, +1.0), Polygon(polygon2d, origin, xAxis, yAxis).getNormalVector());
    }

    {
        const Polygon2d polygon2d = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point origin = {1.0, 2.0, 3.0};
        const Vector3d xAxis = {1.0000000000000006, 0.0, 0.0};

        const Vector3d yAxis = {0.0, 1.0000000000000006, 0.0};

        // X and Y axes can be considered unitary while their cross product is not
        EXPECT_TRUE(
            (xAxis.norm() - 1.0) < Real::Epsilon() && (yAxis.norm() - 1.0) < Real::Epsilon() &&
            (xAxis.cross(yAxis).norm() - 1.0) > Real::Epsilon()
        );

        // The `getNormalVector` function normalizes the output
        EXPECT_TRUE((Polygon(polygon2d, origin, xAxis, yAxis).getNormalVector().norm() - 1.0) < Real::Epsilon());
    }

    {
        EXPECT_ANY_THROW(Polygon::Undefined().getNormalVector());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Polygon, ApplyTransformation)
{
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::object::Vector3d;
    using Polygon2d = ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::Transformation;
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;

    // Translation

    {
        const Polygon2d polygon2d = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point origin = {1.0, 2.0, 3.0};
        const Vector3d xAxis = {1.0, 0.0, 0.0};
        const Vector3d yAxis = {0.0, 1.0, 0.0};

        Polygon polygon = {polygon2d, origin, xAxis, yAxis};

        polygon.applyTransformation(Transformation::Translation({4.0, 5.0, 6.0}));

        EXPECT_EQ(Polygon({polygon2d, {5.0, 7.0, 9.0}, xAxis, yAxis}), polygon);
    }

    // Rotation

    {
        const Polygon2d polygon2d = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point origin = {1.0, 2.0, 0.0};
        const Vector3d xAxis = {1.0, 0.0, 0.0};
        const Vector3d yAxis = {0.0, 1.0, 0.0};

        Polygon polygon = {polygon2d, origin, xAxis, yAxis};

        polygon.applyTransformation(Transformation::Rotation(RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(90.0))));

        const Polygon2d referencePolygon2d = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point referenceOrigin = {1.0, 0.0, 2.0};
        const Vector3d referenceXAxis = {1.0, 0.0, 0.0};
        const Vector3d referenceYAxis = {0.0, 0.0, 1.0};

        const Polygon referencePolygon = {referencePolygon2d, referenceOrigin, referenceXAxis, referenceYAxis};

        EXPECT_TRUE(polygon.getOrigin().isNear(referencePolygon.getOrigin(), Real::Epsilon()));
        EXPECT_TRUE(polygon.getXAxis().isNear(referencePolygon.getXAxis(), Real::Epsilon()));
        EXPECT_TRUE(polygon.getYAxis().isNear(referencePolygon.getYAxis(), Real::Epsilon()));
        EXPECT_TRUE(polygon.getNormalVector().isNear(referencePolygon.getNormalVector(), Real::Epsilon()));
    }

    {
        const Polygon2d polygon2d = {{{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}}};
        const Point origin = {1.0, 2.0, 3.0};
        const Vector3d xAxis = {1.0, 0.0, 0.0};
        const Vector3d yAxis = {0.0, 1.0, 0.0};

        EXPECT_ANY_THROW(Polygon::Undefined().applyTransformation(Transformation::Undefined()));
        EXPECT_ANY_THROW(Polygon::Undefined().applyTransformation(Transformation::Identity()));
        EXPECT_ANY_THROW(Polygon(polygon2d, origin, xAxis, yAxis).applyTransformation(Transformation::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Polygon, Undefined)
{
    using ostk::mathematics::geometry::d3::object::Polygon;

    {
        EXPECT_NO_THROW(Polygon::Undefined());
        EXPECT_FALSE(Polygon::Undefined().isDefined());
    }
}
