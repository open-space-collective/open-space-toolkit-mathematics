/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Cone.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cone, Constructor)
{
    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::object::Vector3d;

    {
        const Point apex = {0.0, 0.0, 0.0};
        const Vector3d axis = Vector3d::Z();
        const Angle angle = Angle::Degrees(45.0);

        EXPECT_NO_THROW(Cone(apex, axis, angle));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cone, Clone)
{
    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::object::Vector3d;

    {
        const Point apex = {0.0, 0.0, 0.0};
        const Vector3d axis = Vector3d::Z();
        const Angle angle = Angle::Degrees(45.0);

        EXPECT_NO_THROW(const Cone* conePtr = Cone(apex, axis, angle).clone(); delete conePtr;);
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cone, EqualToOperator)
{
    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::object::Vector3d;

    {
        const Point apex = {0.0, 0.0, 0.0};
        const Vector3d axis = Vector3d::Z();
        const Angle angle = Angle::Degrees(45.0);

        EXPECT_TRUE(Cone(apex, axis, angle) == Cone(apex, axis, angle));
    }

    {
        const Point firstApex = {0.0, 0.0, 0.0};
        const Vector3d firstAxis = {+1.0, 0.0, 0.0};
        const Angle firstAngle = Angle::Degrees(135.0);

        const Cone firstCone = {firstApex, firstAxis, firstAngle};

        const Point secondApex = {0.0, 0.0, 0.0};
        const Vector3d secondXis = {-1.0, 0.0, 0.0};
        const Angle secondAngle = Angle::Degrees(45.0);

        const Cone secondCone = {secondApex, secondXis, secondAngle};

        EXPECT_TRUE(firstCone == secondCone);
    }

    {
        const Point apex = {0.0, 0.0, 0.0};
        const Vector3d axis = Vector3d::Z();
        const Angle angle = Angle::Degrees(45.0);

        EXPECT_FALSE(Cone(apex, axis, angle) == Cone::Undefined());
        EXPECT_FALSE(Cone::Undefined() == Cone(apex, axis, angle));
        EXPECT_FALSE(Cone::Undefined() == Cone::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cone, NotEqualToOperator)
{
    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::object::Vector3d;

    {
        const Point apex = {0.0, 0.0, 0.0};
        const Vector3d axis = Vector3d::Z();
        const Angle angle = Angle::Degrees(45.0);

        EXPECT_FALSE(Cone(apex, axis, angle) != Cone(apex, axis, angle));
    }

    {
        const Point firstApex = {0.0, 0.0, 0.0};
        const Vector3d firstAxis = {+1.0, 0.0, 0.0};
        const Angle firstAngle = Angle::Degrees(135.0);

        const Cone firstCone = {firstApex, firstAxis, firstAngle};

        const Point secondApex = {0.0, 0.0, 0.0};
        const Vector3d secondXis = {-1.0, 0.0, 0.0};
        const Angle secondAngle = Angle::Degrees(45.0);

        const Cone secondCone = {secondApex, secondXis, secondAngle};

        EXPECT_FALSE(firstCone != secondCone);
    }

    {
        const Point apex = {0.0, 0.0, 0.0};
        const Vector3d axis = Vector3d::Z();
        const Angle angle = Angle::Degrees(45.0);

        EXPECT_TRUE(Cone(apex, axis, angle) != Cone::Undefined());
        EXPECT_TRUE(Cone::Undefined() != Cone(apex, axis, angle));
        EXPECT_TRUE(Cone::Undefined() != Cone::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cone, StreamOperator)
{
    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::object::Vector3d;

    {
        testing::internal::CaptureStdout();

        const Point apex = {0.0, 0.0, 0.0};
        const Vector3d axis = Vector3d::Z();
        const Angle angle = Angle::Degrees(45.0);

        EXPECT_NO_THROW(std::cout << Cone(apex, axis, angle) << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cone, IsDefined)
{
    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::object::Vector3d;

    {
        const Point apex = {0.0, 0.0, 0.0};
        const Vector3d axis = Vector3d::Z();
        const Angle angle = Angle::Degrees(45.0);

        EXPECT_TRUE(Cone(apex, axis, angle).isDefined());
    }

    {
        EXPECT_FALSE(Cone::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cone, Intersects_Sphere)
{
    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Sphere;
    using ostk::mathematics::object::Vector3d;

    // Sphere is completely inside the cone
    {
        const Point apex = {0.0, 0.0, 0.0};
        const Vector3d axis = {0.0, 0.0, 1.0};
        const Angle angle = Angle::Degrees(60.0);

        const Cone cone = {apex, axis, angle};

        const Sphere sphere = {{0.0, 0.0, 5.0}, 1.0};

        EXPECT_TRUE(cone.intersects(sphere));
    }

    // Sphere is completely outside the cone (no intersection)
    {
        const Point apex = {0.0, 0.0, 0.0};
        const Vector3d axis = {0.0, 0.0, 1.0};
        const Angle angle = Angle::Degrees(30.0);

        const Cone cone = {apex, axis, angle};

        const Sphere sphere = {{10.0, 10.0, -10.0}, 1.0};

        EXPECT_FALSE(cone.intersects(sphere));
    }

    // Sphere intersects the cone surface
    {
        const Point apex = {0.0, 0.0, 0.0};
        const Vector3d axis = {0.0, 0.0, 1.0};
        const Angle angle = Angle::Degrees(45.0);

        const Cone cone = {apex, axis, angle};

        const Sphere sphere = {{1.0, 1.0, 1.0}, std::sqrt(3.0)};

        EXPECT_TRUE(cone.intersects(sphere));
    }

    // Sphere contains the cone's apex
    {
        const Point apex = {0.0, 0.0, 0.0};
        const Vector3d axis = {1.0, 0.0, 0.0};
        const Angle angle = Angle::Degrees(15.0);

        const Cone cone = {apex, axis, angle};

        const Sphere sphere = {{0.0, 0.0, 0.0}, 5.0};

        EXPECT_TRUE(cone.intersects(sphere));
    }

    // Test case from KOZ example
    {
        const Point apex = {563726.200583682, -5162285.43178382, 4661267.84065634};
        const Vector3d axis = {0.433806095125264, -0.861209591598177, 0.264821281568289};
        const Angle angle = Angle::Degrees(35.27);

        const Cone cone = {apex, axis, angle};

        const Sphere sphere = {{-22602455774.6168, -137633000770.534, 60466979652.754}, 695500000.0};

        EXPECT_TRUE(cone.intersects(sphere));
    }

    {
        const Point apex = {0.0, 0.0, 0.0};
        const Vector3d axis = {1.0, 0.0, 0.0};
        const Angle angle = Angle::Degrees(15.0);

        const Cone cone = {apex, axis, angle};
        EXPECT_ANY_THROW(cone.intersects(Sphere::Undefined()));
    }

    {
        const Sphere sphere = {{0.0, 0.0, 0.0}, 5.0};

        EXPECT_ANY_THROW(Cone::Undefined().intersects(sphere));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cone, Intersects_Ellipsoid)
{
    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Ellipsoid;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::object::Vector3d;

    {
        const Point apex = {-10.0, 0.0, 10.0};
        const Vector3d axis = Vector3d::X();
        const Angle angle = Angle::Degrees(10.0);

        const Cone cone = {apex, axis, angle};

        const Ellipsoid ellipsoid = {{0.0, 0.0, 10.0}, 5.0, 5.0, 5.0};

        EXPECT_TRUE(cone.intersects(ellipsoid));
    }

    {
        EXPECT_ANY_THROW(Cone::Undefined().intersects(Ellipsoid::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cone, Contains_Point)
{
    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::object::Vector3d;

    {
        const Point apex = {-10.0, 0.0, 10.0};
        const Vector3d axis = Vector3d::X();
        const Angle angle = Angle::Degrees(10.0);

        const Cone cone = {apex, axis, angle};

        EXPECT_TRUE(cone.contains(apex));

        EXPECT_TRUE(cone.contains({-5.0, 0.0, 10.0}));
        EXPECT_TRUE(cone.contains({+0.0, 0.0, 10.0}));
        EXPECT_TRUE(cone.contains({+5.0, 0.0, 10.0}));

        EXPECT_TRUE(cone.contains({+10.0, 0.0, 9.0}));
        EXPECT_TRUE(cone.contains({+10.0, 0.0, 11.0}));

        EXPECT_FALSE(cone.contains({-15.0, 0.0, 10.0}));

        EXPECT_FALSE(cone.contains({+10.0, 0.0, 6.0}));
        EXPECT_FALSE(cone.contains({+10.0, 0.0, 14.0}));
    }

    {
        EXPECT_ANY_THROW(Cone::Undefined().contains(Point::Undefined()));
        EXPECT_ANY_THROW(Cone::Undefined().contains({0.0, 0.0, 0.0}));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cone, Contains_PointSet)
{
    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::object::Vector3d;

    {
        const Point apex = {-10.0, 0.0, 10.0};
        const Vector3d axis = Vector3d::X();
        const Angle angle = Angle::Degrees(10.0);

        const Cone cone = {apex, axis, angle};

        EXPECT_TRUE(cone.contains(PointSet({{-5.0, 0.0, 10.0}, {+0.0, 0.0, 10.0}, {+5.0, 0.0, 10.0}})));
        EXPECT_TRUE(cone.contains(PointSet({{+10.0, 0.0, 9.0}, {+10.0, 0.0, 11.0}})));

        EXPECT_FALSE(cone.contains(PointSet({{+10.0, 0.0, 9.0}, {+10.0, 0.0, 11.0}, {-15.0, 0.0, 10.0}})));
    }

    {
        EXPECT_ANY_THROW(Cone::Undefined().contains(PointSet::Empty()));
        EXPECT_ANY_THROW(Cone::Undefined().contains(PointSet({{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}})));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cone, Contains_Segment)
{
    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::object::Vector3d;

    {
        const Point apex = {-10.0, 0.0, 10.0};
        const Vector3d axis = Vector3d::X();
        const Angle angle = Angle::Degrees(10.0);

        const Cone cone = {apex, axis, angle};

        EXPECT_TRUE(cone.contains(Segment {{-5.0, 0.0, 10.0}, {+0.0, 0.0, 10.0}}));
        EXPECT_TRUE(cone.contains(Segment {{+10.0, 0.0, 9.0}, {+10.0, 0.0, 11.0}}));

        EXPECT_FALSE(cone.contains(Segment {{+10.0, 0.0, 9.0}, {-15.0, 0.0, 10.0}}));
    }

    {
        EXPECT_ANY_THROW(Cone::Undefined().contains(Segment::Undefined()));
        EXPECT_ANY_THROW(Cone::Undefined().contains(Segment {{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}}));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cone, Contains_Ray)
{
    // TBI
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cone, Contains_Sphere)
{
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Sphere;
    using ostk::mathematics::object::Vector3d;

    {
        const Point apex = {-10.0, 0.0, 10.0};
        const Vector3d axis = Vector3d::X();
        const Angle angle = Angle::Degrees(45.0);

        const Cone cone = {apex, axis, angle};

        EXPECT_FALSE(cone.contains(Sphere {apex, 1.0}));
        EXPECT_FALSE(cone.contains(Sphere {apex + Vector3d {1.0, 0.0, 0.0}, 1.0}));
        EXPECT_FALSE(cone.contains(Sphere {apex + Vector3d {std::sqrt(2.0) - Real::Epsilon(), 0.0, 0.0}, 1.0}));

        EXPECT_TRUE(cone.contains(Sphere {apex + Vector3d {std::sqrt(2.0) + Real::Epsilon(), 0.0, 0.0}, 1.0}));
        EXPECT_TRUE(cone.contains(Sphere {apex + Vector3d {2.0, 0.0, 0.0}, 1.0}));

        EXPECT_FALSE(cone.contains(Sphere {(apex - Vector3d {0.5, 0.0, 0.0}), 1.0}));
        EXPECT_FALSE(cone.contains(Sphere {(apex - Vector3d {1.0, 0.0, 0.0}), 1.0}));
    }

    {
        EXPECT_ANY_THROW(Cone::Undefined().contains(Sphere::Undefined()));
        EXPECT_ANY_THROW(Cone::Undefined().contains(Sphere::Unit({0.0, 0.0, 0.0})));
    }
}

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cone, Contains_Ellipsoid)

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cone, GetApex)
{
    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::object::Vector3d;

    {
        const Point apex = {0.0, 0.0, 0.0};
        const Vector3d axis = Vector3d::Z();
        const Angle angle = Angle::Degrees(45.0);

        EXPECT_EQ(apex, Cone(apex, axis, angle).getApex());
    }

    {
        EXPECT_ANY_THROW(Cone::Undefined().getApex());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cone, GetAxis)
{
    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::object::Vector3d;

    {
        const Point apex = {0.0, 0.0, 0.0};
        const Vector3d axis = Vector3d::Z();
        const Angle angle = Angle::Degrees(45.0);

        EXPECT_EQ(axis, Cone(apex, axis, angle).getAxis());
    }

    {
        EXPECT_ANY_THROW(Cone::Undefined().getAxis());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cone, GetAngle)
{
    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::object::Vector3d;

    {
        const Point apex = {0.0, 0.0, 0.0};
        const Vector3d axis = Vector3d::Z();
        const Angle angle = Angle::Degrees(45.0);

        EXPECT_EQ(angle, Cone(apex, axis, angle).getAngle());
    }

    {
        EXPECT_ANY_THROW(Cone::Undefined().getAngle());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cone, GetRaysOfLateralSurface)
{
    using ostk::core::container::Array;
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::object::Vector3d;

    {
        const Point apex = {0.0, 0.0, 0.0};
        const Vector3d axis = Vector3d::Z();
        const Angle angle = Angle::Degrees(45.0);

        const Array<Ray> rays = Cone(apex, axis, angle).getRaysOfLateralSurface(4);

        const Array<Ray> referenceRays = {
            {apex, {0.707106781186548, 0.0, 0.707106781186547}},
            {apex, {1.11022302462516e-16, 0.707106781186548, 0.707106781186547}},
            {apex, {-0.707106781186548, 8.65956056235493e-17, 0.707106781186547}},
            {apex, {-1.11022302462516e-16, -0.707106781186548, 0.707106781186547}}
        };

        EXPECT_TRUE(rays.isNear(
            referenceRays,
            [](const Ray& aFirstRay, const Ray& aSecondRay) -> bool
            {
                return aFirstRay.getOrigin().isNear(aSecondRay.getOrigin(), Real::Epsilon()) &&
                       aFirstRay.getDirection().isNear(aSecondRay.getDirection(), Real::Epsilon());
            }
        ));
    }

    {
        EXPECT_ANY_THROW(Cone::Undefined().getRaysOfLateralSurface());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cone, DistanceTo_Point)
{
    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::object::Vector3d;

    {
        const Point apex = {-10.0, 0.0, 10.0};
        const Vector3d axis = Vector3d::X();
        const Angle angle = Angle::Degrees(45.0);

        const Cone cone = {apex, axis, angle};

        EXPECT_EQ(0.0, cone.distanceTo(apex));

        EXPECT_NEAR(0.0, cone.distanceTo(apex + Vector3d {+1.0, 0.0, -1.0}), 1e-15);  // On lateral surface
        EXPECT_NEAR(0.0, cone.distanceTo(apex + Vector3d {+1.0, 0.0, +1.0}), 1e-15);  // On lateral surface
        EXPECT_NEAR(0.0, cone.distanceTo(apex + Vector3d {+1.0, -1.0, 0.0}), 1e-15);  // On lateral surface
        EXPECT_NEAR(0.0, cone.distanceTo(apex + Vector3d {+1.0, +1.0, 0.0}), 1e-15);  // On lateral surface

        EXPECT_NEAR(0.0, cone.distanceTo(apex + Vector3d {+2.0, 0.0, -2.0}), 1e-15);  // On lateral surface
        EXPECT_NEAR(0.0, cone.distanceTo(apex + Vector3d {+2.0, 0.0, +2.0}), 1e-15);  // On lateral surface
        EXPECT_NEAR(0.0, cone.distanceTo(apex + Vector3d {+2.0, -2.0, 0.0}), 1e-15);  // On lateral surface
        EXPECT_NEAR(0.0, cone.distanceTo(apex + Vector3d {+2.0, +2.0, 0.0}), 1e-15);  // On lateral surface

        EXPECT_NEAR(1.0, cone.distanceTo(apex + Vector3d {-1.0, 0.0, 0.0}), 1e-15);
        EXPECT_NEAR(std::sqrt(2.0) / 2.0, cone.distanceTo(apex + Vector3d {+1.0, 0.0, 0.0}), 1e-15);
        EXPECT_NEAR(std::sqrt(2.0) / 2.0, cone.distanceTo(apex + Vector3d {0.0, -1.0, 0.0}), 1e-15);
        EXPECT_NEAR(std::sqrt(2.0) / 2.0, cone.distanceTo(apex + Vector3d {0.0, +1.0, 0.0}), 1e-15);

        EXPECT_NEAR(std::sqrt(2.0), cone.distanceTo(apex + Vector3d {-1.0, -1.0, 0.0}), 1e-15);
        EXPECT_NEAR(std::sqrt(2.0), cone.distanceTo(apex + Vector3d {-1.0, +1.0, 0.0}), 1e-15);
    }

    {
        EXPECT_ANY_THROW(Cone::Undefined().distanceTo(Point::Undefined()));
        EXPECT_ANY_THROW(Cone::Undefined().distanceTo({0.0, 0.0, 0.0}));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cone, IntersectionWith_Ellipsoid)
{
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::Intersection;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Ellipsoid;
    using ostk::mathematics::geometry::d3::object::LineString;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::object::Vector3d;

    {
        const Point apex = {10.0, 0.0, 10.0};
        const Vector3d axis = {-1.0, 0.0, 0.0};
        const Angle angle = Angle::Degrees(10.0);

        const Cone cone = {apex, axis, angle};

        const Ellipsoid ellipsoid = {{0.0, 0.0, 10.0}, 5.0, 5.0, 5.0};

        const Intersection intersection = cone.intersectionWith(ellipsoid, true, 4);

        EXPECT_TRUE(intersection.isDefined());
        EXPECT_FALSE(intersection.isEmpty());
        EXPECT_TRUE(intersection.accessComposite().is<LineString>());

        const LineString intersectionLineString = intersection.accessComposite().as<LineString>();

        EXPECT_EQ(4, intersectionLineString.getPointCount());

        const LineString referenceLineString = {{
            {4.91908097261278, 0.895903111323379, 10.0},
            {4.91908097261278, 0.0, 9.10409688867662},
            {4.91908097261278, -0.895903111323379, 10.0},
            {4.91908097261278, 0.0, 10.8959031113234},
        }};

        EXPECT_TRUE(intersectionLineString.isNear(referenceLineString, 1e-10));
    }

    {
        EXPECT_ANY_THROW(Cone::Undefined().intersectionWith(Ellipsoid::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cone, ApplyTransformation)
{
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::Transformation;
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;
    using ostk::mathematics::object::Vector3d;

    // Translation

    {
        const Point apex = {0.0, 0.0, 0.0};
        const Vector3d axis = Vector3d::Z();
        const Angle angle = Angle::Degrees(45.0);

        Cone cone = {apex, axis, angle};

        cone.applyTransformation(Transformation::Translation({4.0, 5.0, 6.0}));

        EXPECT_EQ(Cone({4.0, 5.0, 6.0}, axis, angle), cone);
    }

    // Rotation

    {
        const Point apex = {0.0, 1.0, 0.0};
        const Vector3d axis = {0.0, 1.0, 0.0};
        const Angle angle = Angle::Degrees(45.0);

        Cone cone = {apex, axis, angle};

        cone.applyTransformation(Transformation::Rotation(RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(90.0))));

        const Point referenceApex = {0.0, 0.0, 1.0};
        const Vector3d referenceAxis = {0.0, 0.0, 1.0};
        const Angle referenceAngle = Angle::Degrees(45.0);

        const Cone referenceCone = {referenceApex, referenceAxis, referenceAngle};

        EXPECT_TRUE(cone.getApex().isNear(referenceCone.getApex(), Real::Epsilon()))
            << referenceCone.getApex().toString() << cone.getApex().toString();
        EXPECT_TRUE(cone.getAxis().isNear(referenceCone.getAxis(), Real::Epsilon()))
            << referenceCone.getAxis().toString() << cone.getAxis().toString();
        EXPECT_TRUE(cone.getAngle().inDegrees().isNear(referenceCone.getAngle().inDegrees(), Real::Epsilon()))
            << referenceCone.getAngle().toString() << cone.getAngle().toString();
    }

    {
        const Point apex = {0.0, 0.0, 0.0};
        const Vector3d axis = Vector3d::Z();
        const Angle angle = Angle::Degrees(45.0);

        EXPECT_ANY_THROW(Cone::Undefined().applyTransformation(Transformation::Undefined()));
        EXPECT_ANY_THROW(Cone::Undefined().applyTransformation(Transformation::Identity()));
        EXPECT_ANY_THROW(Cone(apex, axis, angle).applyTransformation(Transformation::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cone, Undefined)
{
    using ostk::mathematics::geometry::d3::object::Cone;

    {
        EXPECT_NO_THROW(Cone::Undefined());
        EXPECT_FALSE(Cone::Undefined().isDefined());
    }
}
