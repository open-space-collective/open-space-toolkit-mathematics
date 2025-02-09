/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Table.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/EulerAngle.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/Angle.hpp>

#include <Global.test.hpp>

using ostk::core::container::Table;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;
using ostk::core::type::Real;
using ostk::core::type::String;

using ostk::mathematics::geometry::Angle;
using ostk::mathematics::geometry::d3::transformation::rotation::EulerAngle;
using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;
using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;
using ostk::mathematics::object::Vector3d;

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationVector, Constructor)
{
    {
        RotationVector rotationVector = {{0.0, 0.0, 1.0}, Angle::Degrees(45.0)};

        EXPECT_TRUE(rotationVector.isDefined());
    }

    {
        RotationVector rotationVector = {{0.0, 0.0, 1.0}, Angle::Unit::Degree};

        EXPECT_TRUE(rotationVector.isDefined());
    }

    {
        RotationVector rotationVector = {{0.0, 0.0, 0.0}, Angle::Unit::Degree};

        EXPECT_TRUE(rotationVector.isDefined());
    }

    {
        EXPECT_ANY_THROW(RotationVector({0.0, 0.0, 0.9}, Angle::Degrees(45.0)));
        EXPECT_ANY_THROW(RotationVector({0.0, 0.0, 1.1}, Angle::Degrees(45.0)));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationVector, EqualToOperator)
{
    {
        EXPECT_TRUE(
            RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(0.0)) == RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(0.0))
        );
        EXPECT_TRUE(
            RotationVector({0.0, 1.0, 0.0}, Angle::Degrees(10.0)) ==
            RotationVector({0.0, 1.0, 0.0}, Angle::Degrees(10.0))
        );
        EXPECT_TRUE(
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(20.0)) ==
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(20.0))
        );

        EXPECT_TRUE(
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(30.0)) ==
            RotationVector({0.0, 0.0, +1.0}, Angle::Degrees(+30.0))
        );
        EXPECT_TRUE(
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(30.0)) ==
            RotationVector({0.0, 0.0, -1.0}, Angle::Degrees(-30.0))
        );

        EXPECT_TRUE(
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(0.0)) ==
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(+360.0))
        );
        EXPECT_TRUE(
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(0.0)) ==
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(-360.0))
        );
        EXPECT_TRUE(
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(+180.0)) ==
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(-180.0))
        );

        EXPECT_TRUE(
            RotationVector({0.0, 0.0, 1.0}, Angle::Radians(Real::Pi())) ==
            RotationVector({0.0, 0.0, 1.0}, Angle::Radians(-Real::Pi()))
        );
        EXPECT_TRUE(
            RotationVector({0.0, 0.0, 1.0}, Angle::Radians(0)) ==
            RotationVector({0.0, 0.0, 1.0}, Angle::Radians(Real::TwoPi()))
        );
        EXPECT_TRUE(
            RotationVector({0.0, 0.0, 1.0}, Angle::Radians(Real::Pi())) ==
            RotationVector({0.0, 0.0, 1.0}, Angle::Radians(3.0 * Real::Pi()))
        );
    }

    {
        EXPECT_FALSE(
            RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(0.0)) == RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(1.0))
        );
        EXPECT_FALSE(
            RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(1.0)) ==
            RotationVector({-1.0, 0.0, 0.0}, Angle::Degrees(1.0))
        );
    }

    {
        EXPECT_FALSE(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(0.0)) == RotationVector::Undefined());
        EXPECT_FALSE(RotationVector::Undefined() == RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(0.0)));
        EXPECT_FALSE(RotationVector::Undefined() == RotationVector::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationVector, NotEqualToOperator)
{
    {
        EXPECT_TRUE(
            RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(0.0)) != RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(1.0))
        );
    }

    {
        EXPECT_TRUE(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(0.0)) != RotationVector::Undefined());
        EXPECT_TRUE(RotationVector::Undefined() != RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(0.0)));
        EXPECT_TRUE(RotationVector::Undefined() != RotationVector::Undefined());
    }

    {
        EXPECT_FALSE(
            RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(0.0)) != RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(0.0))
        );
        EXPECT_FALSE(
            RotationVector({0.0, 1.0, 0.0}, Angle::Degrees(10.0)) !=
            RotationVector({0.0, 1.0, 0.0}, Angle::Degrees(10.0))
        );
        EXPECT_FALSE(
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(20.0)) !=
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(20.0))
        );

        EXPECT_FALSE(
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(30.0)) !=
            RotationVector({0.0, 0.0, +1.0}, Angle::Degrees(+30.0))
        );
        EXPECT_FALSE(
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(30.0)) !=
            RotationVector({0.0, 0.0, -1.0}, Angle::Degrees(-30.0))
        );

        EXPECT_FALSE(
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(0.0)) !=
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(+360.0))
        );
        EXPECT_FALSE(
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(0.0)) !=
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(-360.0))
        );
        EXPECT_FALSE(
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(+180.0)) !=
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(-180.0))
        );

        EXPECT_FALSE(
            RotationVector({0.0, 0.0, 1.0}, Angle::Radians(Real::Pi())) !=
            RotationVector({0.0, 0.0, 1.0}, Angle::Radians(-Real::Pi()))
        );
        EXPECT_FALSE(
            RotationVector({0.0, 0.0, 1.0}, Angle::Radians(0)) !=
            RotationVector({0.0, 0.0, 1.0}, Angle::Radians(Real::TwoPi()))
        );
        EXPECT_FALSE(
            RotationVector({0.0, 0.0, 1.0}, Angle::Radians(Real::Pi())) !=
            RotationVector({0.0, 0.0, 1.0}, Angle::Radians(3.0 * Real::Pi()))
        );
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationVector, StreamOperator)
{
    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(10.0)) << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationVector, IsDefined)
{
    {
        EXPECT_TRUE(RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(10.0)).isDefined());
    }

    {
        EXPECT_FALSE(RotationVector::Undefined().isDefined());
        EXPECT_FALSE(RotationVector(Vector3d::Undefined(), Angle::Degrees(10.0)).isDefined());
        EXPECT_FALSE(RotationVector({1.0, 0.0, 0.0}, Angle::Undefined()).isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationVector, GetAxis)
{
    {
        EXPECT_EQ(Vector3d(1.0, 0.0, 0.0), RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(10.0)).getAxis());
        EXPECT_EQ(Vector3d(0.0, 1.0, 0.0), RotationVector({0.0, 1.0, 0.0}, Angle::Degrees(20.0)).getAxis());
        EXPECT_EQ(Vector3d(0.0, 0.0, 1.0), RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(30.0)).getAxis());
    }

    {
        EXPECT_ANY_THROW(RotationVector::Undefined().getAxis());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationVector, GetAngle)
{
    {
        EXPECT_EQ(Angle::Degrees(0.0), RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(0.0)).getAngle());

        EXPECT_EQ(Angle::Degrees(-30.0), RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(-30.0)).getAngle());
        EXPECT_EQ(Angle::Degrees(+30.0), RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(+30.0)).getAngle());

        EXPECT_EQ(Angle::Degrees(-90.0), RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(-90.0)).getAngle());
        EXPECT_EQ(Angle::Degrees(+90.0), RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(+90.0)).getAngle());

        EXPECT_EQ(Angle::Degrees(-180.0), RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(-180.0)).getAngle());
        EXPECT_EQ(Angle::Degrees(+180.0), RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(+180.0)).getAngle());
    }

    {
        EXPECT_ANY_THROW(RotationVector::Undefined().getAngle());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationVector, ToString)
{
    {
        EXPECT_EQ("[1.0, 0.0, 0.0] : 0.0 [deg]", RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(0.0)).toString());

        EXPECT_EQ("[0.0, 0.0, 1.0] : -30.0 [deg]", RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(-30.0)).toString());
        EXPECT_EQ("[0.0, 0.0, 1.0] : 30.0 [deg]", RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(+30.0)).toString());

        EXPECT_EQ("[0.0, 0.0, 1.0] : -90.0 [deg]", RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(-90.0)).toString());
        EXPECT_EQ("[0.0, 0.0, 1.0] : 90.0 [deg]", RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(+90.0)).toString());

        EXPECT_EQ("[0.0, 0.0, 1.0] : -180.0 [deg]", RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(-180.0)).toString());
        EXPECT_EQ("[0.0, 0.0, 1.0] : 180.0 [deg]", RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(+180.0)).toString());
    }

    {
        EXPECT_EQ(
            "[1.000, 0.000, 0.000] : 0.000 [deg]", RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(0.0)).toString(3)
        );

        EXPECT_EQ(
            "[0.000, 0.000, 1.000] : -30.000 [deg]", RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(-30.0)).toString(3)
        );
        EXPECT_EQ(
            "[0.000, 0.000, 1.000] : 30.000 [deg]", RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(+30.0)).toString(3)
        );

        EXPECT_EQ(
            "[0.000, 0.000, 1.000] : -90.000 [deg]", RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(-90.0)).toString(3)
        );
        EXPECT_EQ(
            "[0.000, 0.000, 1.000] : 90.000 [deg]", RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(+90.0)).toString(3)
        );

        EXPECT_EQ(
            "[0.000, 0.000, 1.000] : -180.000 [deg]",
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(-180.0)).toString(3)
        );
        EXPECT_EQ(
            "[0.000, 0.000, 1.000] : 180.000 [deg]", RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(+180.0)).toString(3)
        );
    }

    {
        EXPECT_ANY_THROW(RotationVector::Undefined().toString());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationVector, Rectify)
{
    {
        EXPECT_EQ(
            RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(0.0)),
            RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(0.0)).rectify()
        );

        EXPECT_EQ(
            RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(0.0)),
            RotationVector({-1.0, 0.0, 0.0}, Angle::Degrees(0.0)).rectify()
        );

        EXPECT_EQ(
            RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(45.0)),
            RotationVector({-1.0, 0.0, 0.0}, Angle::Degrees(-45.0)).rectify()
        );

        EXPECT_EQ(
            RotationVector({-1.0, 0.0, 0.0}, Angle::Degrees(180.0 - 45.0)),
            RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(180.0 + 45.0)).rectify()
        );
    }

    {
        EXPECT_ANY_THROW(RotationVector::Undefined().rectify());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationVector, Undefined)
{
    {
        EXPECT_NO_THROW(RotationVector::Undefined());
        EXPECT_FALSE(RotationVector::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationVector, Unit)
{
    {
        EXPECT_NO_THROW(RotationVector::Unit());
        EXPECT_EQ(RotationVector({0.0, 0.0, 1.0}, Angle::Zero()), RotationVector::Unit());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationVector, X)
{
    {
        EXPECT_NO_THROW(RotationVector::X(Angle::Degrees(45.0)));

        const RotationVector rotationVector = RotationVector::X(Angle::Degrees(45.0));

        EXPECT_EQ(Vector3d::X(), rotationVector.getAxis());
        EXPECT_EQ(Angle::Degrees(45.0), rotationVector.getAngle());
    }

    {
        EXPECT_ANY_THROW(RotationVector::X(Angle::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationVector, Y)
{
    {
        EXPECT_NO_THROW(RotationVector::Y(Angle::Degrees(45.0)));

        const RotationVector rotationVector = RotationVector::Y(Angle::Degrees(45.0));

        EXPECT_EQ(Vector3d::Y(), rotationVector.getAxis());
        EXPECT_EQ(Angle::Degrees(45.0), rotationVector.getAngle());
    }

    {
        EXPECT_ANY_THROW(RotationVector::Y(Angle::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationVector, Z)
{
    {
        EXPECT_NO_THROW(RotationVector::Z(Angle::Degrees(45.0)));

        const RotationVector rotationVector = RotationVector::Z(Angle::Degrees(45.0));

        EXPECT_EQ(Vector3d::Z(), rotationVector.getAxis());
        EXPECT_EQ(Angle::Degrees(45.0), rotationVector.getAngle());
    }

    {
        EXPECT_ANY_THROW(RotationVector::Z(Angle::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationVector, Quaternion)
{
    {
        EXPECT_EQ(RotationVector::Unit(), RotationVector::Quaternion(Quaternion::Unit()));
    }

    {
        EXPECT_EQ(
            RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(180.0)),
            RotationVector::Quaternion(Quaternion::XYZS(1.0, 0.0, 0.0, 0.0))
        );
        EXPECT_EQ(
            RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(180.0)),
            RotationVector::Quaternion(Quaternion::XYZS(-1.0, 0.0, 0.0, 0.0))
        );
        EXPECT_EQ(
            RotationVector({-1.0, 0.0, 0.0}, Angle::Degrees(180.0)),
            RotationVector::Quaternion(Quaternion::XYZS(1.0, 0.0, 0.0, 0.0))
        );
        EXPECT_EQ(
            RotationVector({-1.0, 0.0, 0.0}, Angle::Degrees(180.0)),
            RotationVector::Quaternion(Quaternion::XYZS(-1.0, 0.0, 0.0, 0.0))
        );

        EXPECT_EQ(
            RotationVector({0.0, 1.0, 0.0}, Angle::Degrees(180.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.0, 1.0, 0.0, 0.0))
        );
        EXPECT_EQ(
            RotationVector({0.0, 1.0, 0.0}, Angle::Degrees(180.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.0, -1.0, 0.0, 0.0))
        );
        EXPECT_EQ(
            RotationVector({0.0, -1.0, 0.0}, Angle::Degrees(180.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.0, 1.0, 0.0, 0.0))
        );
        EXPECT_EQ(
            RotationVector({0.0, -1.0, 0.0}, Angle::Degrees(180.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.0, -1.0, 0.0, 0.0))
        );

        EXPECT_EQ(
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(180.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.0, 0.0, 1.0, 0.0))
        );
        EXPECT_EQ(
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(180.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.0, 0.0, -1.0, 0.0))
        );
        EXPECT_EQ(
            RotationVector({0.0, 0.0, -1.0}, Angle::Degrees(180.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.0, 0.0, 1.0, 0.0))
        );
        EXPECT_EQ(
            RotationVector({0.0, 0.0, -1.0}, Angle::Degrees(180.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.0, 0.0, -1.0, 0.0))
        );
    }

    {
        EXPECT_EQ(
            RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(179.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.9999619230641713, 0.0, 0.0, 0.008726535498373897))
        );
        EXPECT_EQ(
            RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(181.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.9999619230641713, 0.0, 0.0, -0.008726535498373997))
        );
        EXPECT_EQ(
            RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(-179.0)),
            RotationVector::Quaternion(Quaternion::XYZS(-0.9999619230641713, 0.0, 0.0, 0.008726535498373897))
        );
        EXPECT_EQ(
            RotationVector({1.0, 0.0, 0.0}, Angle::Degrees(-181.0)),
            RotationVector::Quaternion(Quaternion::XYZS(-0.9999619230641713, 0.0, 0.0, -0.008726535498373997))
        );

        EXPECT_EQ(
            RotationVector({0.0, 1.0, 0.0}, Angle::Degrees(179.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.0, 0.9999619230641713, 0.0, 0.008726535498373897))
        );
        EXPECT_EQ(
            RotationVector({0.0, 1.0, 0.0}, Angle::Degrees(181.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.0, 0.9999619230641713, 0.0, -0.008726535498373997))
        );
        EXPECT_EQ(
            RotationVector({0.0, 1.0, 0.0}, Angle::Degrees(-179.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.0, -0.9999619230641713, 0.0, 0.008726535498373897))
        );
        EXPECT_EQ(
            RotationVector({0.0, 1.0, 0.0}, Angle::Degrees(-181.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.0, -0.9999619230641713, 0.0, -0.008726535498373997))
        );

        EXPECT_EQ(
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(179.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.0, 0.0, 0.9999619230641713, 0.008726535498373897))
        );
        EXPECT_EQ(
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(181.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.0, 0.0, 0.9999619230641713, -0.008726535498373997))
        );
        EXPECT_EQ(
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(-179.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.0, 0.0, -0.9999619230641713, 0.008726535498373897))
        );
        EXPECT_EQ(
            RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(-181.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.0, 0.0, -0.9999619230641713, -0.008726535498373997))
        );

        EXPECT_EQ(
            RotationVector({-1.0, 0.0, 0.0}, Angle::Degrees(179.0)),
            RotationVector::Quaternion(Quaternion::XYZS(-0.9999619230641713, 0.0, 0.0, 0.008726535498373897))
        );
        EXPECT_EQ(
            RotationVector({-1.0, 0.0, 0.0}, Angle::Degrees(181.0)),
            RotationVector::Quaternion(Quaternion::XYZS(-0.9999619230641713, 0.0, 0.0, -0.008726535498373997))
        );
        EXPECT_EQ(
            RotationVector({-1.0, 0.0, 0.0}, Angle::Degrees(-179.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.9999619230641713, 0.0, 0.0, 0.008726535498373897))
        );
        EXPECT_EQ(
            RotationVector({-1.0, 0.0, 0.0}, Angle::Degrees(-181.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.9999619230641713, 0.0, 0.0, -0.008726535498373997))
        );

        EXPECT_EQ(
            RotationVector({0.0, -1.0, 0.0}, Angle::Degrees(179.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.0, -0.9999619230641713, 0.0, 0.008726535498373897))
        );
        EXPECT_EQ(
            RotationVector({0.0, -1.0, 0.0}, Angle::Degrees(181.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.0, -0.9999619230641713, 0.0, -0.008726535498373997))
        );
        EXPECT_EQ(
            RotationVector({0.0, -1.0, 0.0}, Angle::Degrees(-179.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.0, 0.9999619230641713, 0.0, 0.008726535498373897))
        );
        EXPECT_EQ(
            RotationVector({0.0, -1.0, 0.0}, Angle::Degrees(-181.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.0, 0.9999619230641713, 0.0, -0.008726535498373997))
        );

        EXPECT_EQ(
            RotationVector({0.0, 0.0, -1.0}, Angle::Degrees(179.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.0, 0.0, -0.9999619230641713, 0.008726535498373897))
        );
        EXPECT_EQ(
            RotationVector({0.0, 0.0, -1.0}, Angle::Degrees(181.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.0, 0.0, -0.9999619230641713, -0.008726535498373997))
        );
        EXPECT_EQ(
            RotationVector({0.0, 0.0, -1.0}, Angle::Degrees(-179.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.0, 0.0, 0.9999619230641713, 0.008726535498373897))
        );
        EXPECT_EQ(
            RotationVector({0.0, 0.0, -1.0}, Angle::Degrees(-181.0)),
            RotationVector::Quaternion(Quaternion::XYZS(0.0, 0.0, 0.9999619230641713, -0.008726535498373997))
        );
    }

    {
        EXPECT_ANY_THROW(RotationVector::Quaternion(Quaternion::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationVector, EulerAngle)
{
    {
        EXPECT_EQ(RotationVector::Unit(), RotationVector::EulerAngle(EulerAngle::Unit()));
    }

    // XYZ

    {
        const Table referenceDataTable = Table::Load(
            File::Path(
                Path::Parse(
                    "/app/test/OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/"
                    "EulerAngle/RotationVector-EulerAngle-XYZ.csv"
                )
            ),
            Table::Format::CSV,
            true
        );

        const Real tolerance = 1e-9;
        const Angle angularTolerance = Angle::Degrees(1e-9);

        for (const auto& referenceDataRow : referenceDataTable)
        {
            const RotationVector referenceRotationVector = RotationVector(
                                                               Vector3d(
                                                                   referenceDataRow[0].accessReal(),
                                                                   referenceDataRow[1].accessReal(),
                                                                   referenceDataRow[2].accessReal()
                                                               ),
                                                               Angle::Unit::Radian
            )
                                                               .rectify();

            const EulerAngle eulerAngle = EulerAngle::XYZ(
                Angle::Radians(referenceDataRow[3].accessReal()),
                Angle::Radians(referenceDataRow[4].accessReal()),
                Angle::Radians(referenceDataRow[5].accessReal())
            );

            const RotationVector rotationVector = RotationVector::EulerAngle(eulerAngle).rectify();

            EXPECT_TRUE(rotationVector.getAxis().isApprox(referenceRotationVector.getAxis(), tolerance))
                << String::Format(
                       "{} / {}", referenceRotationVector.getAxis().toString(), rotationVector.getAxis().toString()
                   );
            EXPECT_TRUE(rotationVector.getAngle().isNear(referenceRotationVector.getAngle(), angularTolerance))
                << String::Format(
                       "{} / {}", referenceRotationVector.getAngle().toString(), rotationVector.getAngle().toString()
                   );
        }
    }

    // ZXY

    {
        const Table referenceDataTable = Table::Load(
            File::Path(
                Path::Parse(
                    "/app/test/OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/"
                    "EulerAngle/RotationVector-EulerAngle-ZXY.csv"
                )
            ),
            Table::Format::CSV,
            true
        );

        const Real tolerance = 1e-9;
        const Angle angularTolerance = Angle::Degrees(1e-9);

        for (const auto& referenceDataRow : referenceDataTable)
        {
            const RotationVector referenceRotationVector = RotationVector(
                                                               Vector3d(
                                                                   referenceDataRow[0].accessReal(),
                                                                   referenceDataRow[1].accessReal(),
                                                                   referenceDataRow[2].accessReal()
                                                               ),
                                                               Angle::Unit::Radian
            )
                                                               .rectify();

            const EulerAngle eulerAngle = EulerAngle::ZXY(
                Angle::Radians(referenceDataRow[3].accessReal()),
                Angle::Radians(referenceDataRow[4].accessReal()),
                Angle::Radians(referenceDataRow[5].accessReal())
            );

            const RotationVector rotationVector = RotationVector::EulerAngle(eulerAngle).rectify();

            EXPECT_TRUE(rotationVector.getAxis().isApprox(referenceRotationVector.getAxis(), tolerance))
                << String::Format(
                       "{} / {}", referenceRotationVector.getAxis().toString(), rotationVector.getAxis().toString()
                   );
            EXPECT_TRUE(rotationVector.getAngle().isNear(referenceRotationVector.getAngle(), angularTolerance))
                << String::Format(
                       "{} / {}", referenceRotationVector.getAngle().toString(), rotationVector.getAngle().toString()
                   );
        }
    }

    // ZYX

    {
        const Table referenceDataTable = Table::Load(
            File::Path(
                Path::Parse(
                    "/app/test/OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/"
                    "EulerAngle/RotationVector-EulerAngle-ZYX.csv"
                )
            ),
            Table::Format::CSV,
            true
        );

        const Real tolerance = 1e-9;
        const Angle angularTolerance = Angle::Degrees(1e-9);

        for (const auto& referenceDataRow : referenceDataTable)
        {
            const RotationVector referenceRotationVector = RotationVector(
                                                               Vector3d(
                                                                   referenceDataRow[0].accessReal(),
                                                                   referenceDataRow[1].accessReal(),
                                                                   referenceDataRow[2].accessReal()
                                                               ),
                                                               Angle::Unit::Radian
            )
                                                               .rectify();

            const EulerAngle eulerAngle = EulerAngle::ZYX(
                Angle::Radians(referenceDataRow[3].accessReal()),
                Angle::Radians(referenceDataRow[4].accessReal()),
                Angle::Radians(referenceDataRow[5].accessReal())
            );

            const RotationVector rotationVector = RotationVector::EulerAngle(eulerAngle).rectify();

            EXPECT_TRUE(rotationVector.getAxis().isApprox(referenceRotationVector.getAxis(), tolerance))
                << String::Format(
                       "{} / {}", referenceRotationVector.getAxis().toString(), rotationVector.getAxis().toString()
                   );
            EXPECT_TRUE(rotationVector.getAngle().isNear(referenceRotationVector.getAngle(), angularTolerance))
                << String::Format(
                       "{} / {}", referenceRotationVector.getAngle().toString(), rotationVector.getAngle().toString()
                   );
        }
    }

    {
        EXPECT_ANY_THROW(RotationVector::EulerAngle(EulerAngle::Undefined()));
    }
}
