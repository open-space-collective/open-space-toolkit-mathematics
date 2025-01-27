/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Table.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/EulerAngle.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationMatrix.hpp>
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
using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix;
using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;
using ostk::mathematics::object::Vector3d;
using ostk::mathematics::object::Vector4d;

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, Constructor)
{
    {
        EXPECT_NO_THROW(Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS));

        Quaternion quaternion = {0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS};

        EXPECT_TRUE(quaternion.isDefined());
    }

    {
        EXPECT_NO_THROW(Quaternion(Vector4d(0.0, 0.0, 0.0, 1.0), Quaternion::Format::XYZS));

        Quaternion quaternion = {Vector4d(0.0, 0.0, 0.0, 1.0), Quaternion::Format::XYZS};

        EXPECT_TRUE(quaternion.isDefined());
    }

    {
        EXPECT_NO_THROW(Quaternion(Vector3d(0.0, 0.0, 0.0), 1.0));

        Quaternion quaternion = {Vector3d(0.0, 0.0, 0.0), 1.0};

        EXPECT_TRUE(quaternion.isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, EqualToOperator)
{
    {
        EXPECT_TRUE(
            Quaternion(1.0, 0.0, 0.0, 0.0, Quaternion::Format::XYZS) ==
            Quaternion(1.0, 0.0, 0.0, 0.0, Quaternion::Format::XYZS)
        );
        EXPECT_TRUE(
            Quaternion(0.0, 1.0, 0.0, 0.0, Quaternion::Format::XYZS) ==
            Quaternion(0.0, 1.0, 0.0, 0.0, Quaternion::Format::XYZS)
        );
        EXPECT_TRUE(
            Quaternion(0.0, 0.0, 1.0, 0.0, Quaternion::Format::XYZS) ==
            Quaternion(0.0, 0.0, 1.0, 0.0, Quaternion::Format::XYZS)
        );
        EXPECT_TRUE(
            Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS) ==
            Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS)
        );

        EXPECT_TRUE(
            Quaternion(1.0, 0.0, 0.0, 0.0, Quaternion::Format::XYZS) ==
            Quaternion(-1.0, -0.0, -0.0, -0.0, Quaternion::Format::XYZS)
        );
        EXPECT_TRUE(
            Quaternion(0.0, 1.0, 0.0, 0.0, Quaternion::Format::XYZS) ==
            Quaternion(-0.0, -1.0, -0.0, -0.0, Quaternion::Format::XYZS)
        );
        EXPECT_TRUE(
            Quaternion(0.0, 0.0, 1.0, 0.0, Quaternion::Format::XYZS) ==
            Quaternion(-0.0, -0.0, -1.0, -0.0, Quaternion::Format::XYZS)
        );
        EXPECT_TRUE(
            Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS) ==
            Quaternion(-0.0, -0.0, -0.0, -1.0, Quaternion::Format::XYZS)
        );

        EXPECT_TRUE(
            Quaternion(-1.0, -0.0, -0.0, -0.0, Quaternion::Format::XYZS) ==
            Quaternion(1.0, 0.0, 0.0, 0.0, Quaternion::Format::XYZS)
        );
        EXPECT_TRUE(
            Quaternion(-0.0, -1.0, -0.0, -0.0, Quaternion::Format::XYZS) ==
            Quaternion(0.0, 1.0, 0.0, 0.0, Quaternion::Format::XYZS)
        );
        EXPECT_TRUE(
            Quaternion(-0.0, -0.0, -1.0, -0.0, Quaternion::Format::XYZS) ==
            Quaternion(0.0, 0.0, 1.0, 0.0, Quaternion::Format::XYZS)
        );
        EXPECT_TRUE(
            Quaternion(-0.0, -0.0, -0.0, -1.0, Quaternion::Format::XYZS) ==
            Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS)
        );
    }

    {
        EXPECT_FALSE(
            Quaternion(1.0, 0.0, 0.0, 0.0, Quaternion::Format::XYZS) ==
            Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS)
        );
        EXPECT_FALSE(
            Quaternion(0.0, 1.0, 0.0, 0.0, Quaternion::Format::XYZS) ==
            Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS)
        );
        EXPECT_FALSE(
            Quaternion(0.0, 0.0, 1.0, 0.0, Quaternion::Format::XYZS) ==
            Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS)
        );
    }

    {
        EXPECT_FALSE(Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS) == Quaternion::Undefined());
        EXPECT_FALSE(Quaternion::Undefined() == Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS));
        EXPECT_FALSE(Quaternion::Undefined() == Quaternion::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, NotEqualToOperator)
{
    {
        EXPECT_TRUE(
            Quaternion(1.0, 0.0, 0.0, 0.0, Quaternion::Format::XYZS) !=
            Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS)
        );
        EXPECT_TRUE(
            Quaternion(0.0, 1.0, 0.0, 0.0, Quaternion::Format::XYZS) !=
            Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS)
        );
        EXPECT_TRUE(
            Quaternion(0.0, 0.0, 1.0, 0.0, Quaternion::Format::XYZS) !=
            Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS)
        );
    }

    {
        EXPECT_TRUE(Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS) != Quaternion::Undefined());
        EXPECT_TRUE(Quaternion::Undefined() != Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS));
        EXPECT_TRUE(Quaternion::Undefined() != Quaternion::Undefined());
    }

    {
        EXPECT_FALSE(
            Quaternion(1.0, 0.0, 0.0, 0.0, Quaternion::Format::XYZS) !=
            Quaternion(1.0, 0.0, 0.0, 0.0, Quaternion::Format::XYZS)
        );
        EXPECT_FALSE(
            Quaternion(0.0, 1.0, 0.0, 0.0, Quaternion::Format::XYZS) !=
            Quaternion(0.0, 1.0, 0.0, 0.0, Quaternion::Format::XYZS)
        );
        EXPECT_FALSE(
            Quaternion(0.0, 0.0, 1.0, 0.0, Quaternion::Format::XYZS) !=
            Quaternion(0.0, 0.0, 1.0, 0.0, Quaternion::Format::XYZS)
        );
        EXPECT_FALSE(
            Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS) !=
            Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS)
        );

        EXPECT_FALSE(
            Quaternion(1.0, 0.0, 0.0, 0.0, Quaternion::Format::XYZS) !=
            Quaternion(-1.0, -0.0, -0.0, -0.0, Quaternion::Format::XYZS)
        );
        EXPECT_FALSE(
            Quaternion(0.0, 1.0, 0.0, 0.0, Quaternion::Format::XYZS) !=
            Quaternion(-0.0, -1.0, -0.0, -0.0, Quaternion::Format::XYZS)
        );
        EXPECT_FALSE(
            Quaternion(0.0, 0.0, 1.0, 0.0, Quaternion::Format::XYZS) !=
            Quaternion(-0.0, -0.0, -1.0, -0.0, Quaternion::Format::XYZS)
        );
        EXPECT_FALSE(
            Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS) !=
            Quaternion(-0.0, -0.0, -0.0, -1.0, Quaternion::Format::XYZS)
        );

        EXPECT_FALSE(
            Quaternion(-1.0, -0.0, -0.0, -0.0, Quaternion::Format::XYZS) !=
            Quaternion(1.0, 0.0, 0.0, 0.0, Quaternion::Format::XYZS)
        );
        EXPECT_FALSE(
            Quaternion(-0.0, -1.0, -0.0, -0.0, Quaternion::Format::XYZS) !=
            Quaternion(0.0, 1.0, 0.0, 0.0, Quaternion::Format::XYZS)
        );
        EXPECT_FALSE(
            Quaternion(-0.0, -0.0, -1.0, -0.0, Quaternion::Format::XYZS) !=
            Quaternion(0.0, 0.0, 1.0, 0.0, Quaternion::Format::XYZS)
        );
        EXPECT_FALSE(
            Quaternion(-0.0, -0.0, -0.0, -1.0, Quaternion::Format::XYZS) !=
            Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS)
        );
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, AdditionOperator)
{
    {
        EXPECT_EQ(
            Quaternion::XYZS(2.0, 4.0, 6.0, 8.0),
            Quaternion::XYZS(1.0, 2.0, 3.0, 4.0) + Quaternion::XYZS(1.0, 2.0, 3.0, 4.0)
        );
    }

    {
        EXPECT_ANY_THROW(Quaternion::Undefined() + Quaternion::Unit());
        EXPECT_ANY_THROW(Quaternion::Unit() + Quaternion::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, MultiplicationOperator_Quaternion)
{
    {
        EXPECT_EQ(Quaternion::Unit(), Quaternion::Unit() * Quaternion::Unit());
    }

    {
        EXPECT_ANY_THROW(Quaternion::Undefined() * Quaternion::Unit());
        EXPECT_ANY_THROW(Quaternion::Unit() * Quaternion::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, MultiplicationOperator_Vector3d)
{
    {
        EXPECT_EQ(Vector3d::X(), Quaternion::Unit() * Vector3d::X());
    }

    {
        EXPECT_ANY_THROW(Quaternion::Undefined() * Vector3d::X());
        EXPECT_ANY_THROW(Quaternion::Unit() * Vector3d::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, MultiplicationOperator_Real)
{
    {
        EXPECT_EQ(Quaternion::Unit(), Quaternion::Unit() * 1.0);
        EXPECT_EQ(Quaternion::Unit(), 1.0 * Quaternion::Unit());
    }

    {
        EXPECT_ANY_THROW(Quaternion::Undefined() * 1.0);
        EXPECT_ANY_THROW(Quaternion::Unit() * Real::Undefined());

        EXPECT_ANY_THROW(1.0 * Quaternion::Undefined());
        EXPECT_ANY_THROW(Real::Undefined() * Quaternion::Unit());
    }
}

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, DivisionOperator)
// {

//     {

//         FAIL() ;

//     }

// }

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, PowerOperator)
{
    {
        EXPECT_EQ(Quaternion::Unit(), Quaternion::Unit() ^ 1.0);
        EXPECT_TRUE((Quaternion::XYZS(1.0, 0.0, 0.0, 0.0) ^ 2.0)
                        .isNear(Quaternion::XYZS(0.0, 0.0, 0.0, -1.0), Angle::Radians(1e-4)));
    }

    {
        EXPECT_ANY_THROW(Quaternion::Undefined() ^ 2.0);
        EXPECT_ANY_THROW(Quaternion::Unit() ^ Real::Undefined());
    }
}

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion,
// MultiplicationAssignmentOperator)
// {

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, DivisionAssignmentOperator)
// {

//     {

//         FAIL() ;

//     }

// }

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, StreamOperator)
{
    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << Quaternion::XYZS(0.0, 0.0, 0.0, 1.0) << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, IsDefined)
{
    {
        EXPECT_TRUE(Quaternion::XYZS(1.0, 0.0, 0.0, 0.0).isDefined());
        EXPECT_TRUE(Quaternion::XYZS(0.0, 1.0, 0.0, 0.0).isDefined());
        EXPECT_TRUE(Quaternion::XYZS(0.0, 0.0, 1.0, 0.0).isDefined());
        EXPECT_TRUE(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).isDefined());
    }

    {
        EXPECT_TRUE(Quaternion::XYZS(1.0, 2.0, 3.0, 4.0).isDefined());
    }

    {
        EXPECT_FALSE(Quaternion::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, IsUnitary)
{
    {
        EXPECT_TRUE(Quaternion::XYZS(1.0, 0.0, 0.0, 0.0).isUnitary());
        EXPECT_TRUE(Quaternion::XYZS(0.0, 1.0, 0.0, 0.0).isUnitary());
        EXPECT_TRUE(Quaternion::XYZS(0.0, 0.0, 1.0, 0.0).isUnitary());
        EXPECT_TRUE(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).isUnitary());
    }

    {
        EXPECT_FALSE(Quaternion::XYZS(1.0, 2.0, 3.0, 4.0).isUnitary());
    }

    {
        EXPECT_FALSE(Quaternion::XYZS(1.0001, 0.0, 0.0, 0.0).isUnitary(Real(0.0001)));
        EXPECT_TRUE(Quaternion::XYZS(1.0001, 0.0, 0.0, 0.0).isUnitary(Real(0.0003)));
    }

    {
        EXPECT_ANY_THROW(Quaternion::Undefined().isUnitary());
        EXPECT_ANY_THROW(Quaternion::Undefined().isUnitary(Real(0.0001)));
        EXPECT_ANY_THROW(Quaternion::XYZS(1.0001, 0.0, 0.0, 0.0).isUnitary(Real(-0.0001)));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, IsNear)
{
    {
        EXPECT_TRUE(Quaternion::XYZS(1.0, 0.0, 0.0, 0.0).isNear(Quaternion::XYZS(1.0, 0.0, 0.0, 0.0), Angle::Zero()));
        EXPECT_TRUE(Quaternion::XYZS(0.0, 1.0, 0.0, 0.0).isNear(Quaternion::XYZS(0.0, 1.0, 0.0, 0.0), Angle::Zero()));
        EXPECT_TRUE(Quaternion::XYZS(0.0, 0.0, 1.0, 0.0).isNear(Quaternion::XYZS(0.0, 0.0, 1.0, 0.0), Angle::Zero()));
        EXPECT_TRUE(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).isNear(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0), Angle::Zero()));

        EXPECT_TRUE(
            Quaternion::XYZS(1.0, 0.0, 0.0, 0.0)
                .isNear(Quaternion::XYZS(1.0 + 1e-6, 0.0, 0.0, 0.0).normalize(), Angle::Radians(1e-6))
        );
        EXPECT_TRUE(
            Quaternion::XYZS(0.0, 1.0, 0.0, 0.0)
                .isNear(Quaternion::XYZS(0.0, 1.0 + 1e-6, 0.0, 0.0).normalize(), Angle::Radians(1e-6))
        );
        EXPECT_TRUE(
            Quaternion::XYZS(0.0, 0.0, 1.0, 0.0)
                .isNear(Quaternion::XYZS(0.0, 0.0, 1.0 + 1e-6, 0.0).normalize(), Angle::Radians(1e-6))
        );
        EXPECT_TRUE(
            Quaternion::XYZS(0.0, 0.0, 0.0, 1.0)
                .isNear(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0 + 1e-6).normalize(), Angle::Radians(1e-6))
        );
    }

    {
        EXPECT_TRUE(
            Quaternion::XYZS(1.0, 0.0, 0.0, 0.0)
                .isNear(Quaternion::XYZS(1.0 + 1e-6, 0.0, 0.0, 0.0).normalize(), Angle::Radians(0.0))
        );
        EXPECT_TRUE(
            Quaternion::XYZS(0.0, 1.0, 0.0, 0.0)
                .isNear(Quaternion::XYZS(0.0, 1.0 + 1e-6, 0.0, 0.0).normalize(), Angle::Radians(0.0))
        );
        EXPECT_TRUE(
            Quaternion::XYZS(0.0, 0.0, 1.0, 0.0)
                .isNear(Quaternion::XYZS(0.0, 0.0, 1.0 + 1e-6, 0.0).normalize(), Angle::Radians(0.0))
        );
        EXPECT_TRUE(
            Quaternion::XYZS(0.0, 0.0, 0.0, 1.0)
                .isNear(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0 + 1e-6).normalize(), Angle::Radians(0.0))
        );
    }

    {
        EXPECT_ANY_THROW(Quaternion::Undefined().isNear(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0), Angle::Degrees(0.0)));
        EXPECT_ANY_THROW(Quaternion::Undefined().isNear(Quaternion::XYZS(0.0, 0.0, 0.0, 1.1), Angle::Degrees(0.0)));

        EXPECT_ANY_THROW(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).isNear(Quaternion::Undefined(), Angle::Degrees(0.0)));
        EXPECT_ANY_THROW(Quaternion::XYZS(0.0, 0.0, 0.0, 1.1).isNear(Quaternion::Undefined(), Angle::Degrees(0.0)));

        EXPECT_ANY_THROW(
            Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).isNear(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0), Angle::Undefined())
        );
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, X)
{
    {
        EXPECT_EQ(1.0, Quaternion::XYZS(1.0, 2.0, 3.0, 4.0).x());
    }

    {
        EXPECT_ANY_THROW(Quaternion::Undefined().x());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, Y)
{
    {
        EXPECT_EQ(2.0, Quaternion::XYZS(1.0, 2.0, 3.0, 4.0).y());
    }

    {
        EXPECT_ANY_THROW(Quaternion::Undefined().y());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, Z)
{
    {
        EXPECT_EQ(3.0, Quaternion::XYZS(1.0, 2.0, 3.0, 4.0).z());
    }

    {
        EXPECT_ANY_THROW(Quaternion::Undefined().z());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, S)
{
    {
        EXPECT_EQ(4.0, Quaternion::XYZS(1.0, 2.0, 3.0, 4.0).s());
    }

    {
        EXPECT_ANY_THROW(Quaternion::Undefined().s());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, GetVectorPart)
{
    {
        EXPECT_EQ(Vector3d(1.0, 2.0, 3.0), Quaternion::XYZS(1.0, 2.0, 3.0, 4.0).getVectorPart());
    }

    {
        EXPECT_ANY_THROW(Quaternion::Undefined().getVectorPart());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, GetScalarPart)
{
    {
        EXPECT_EQ(4.0, Quaternion::XYZS(1.0, 2.0, 3.0, 4.0).getScalarPart());
    }

    {
        EXPECT_ANY_THROW(Quaternion::Undefined().getScalarPart());
    }
}

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, ToNormalized)
// {

//     {

//         FAIL() ;

//     }

// }

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, ToConjugate)
{
    {
        EXPECT_EQ(Quaternion::XYZS(-1.0, -2.0, -3.0, +4.0), Quaternion::XYZS(+1.0, +2.0, +3.0, +4.0).toConjugate());
        EXPECT_EQ(Quaternion::XYZS(+1.0, +2.0, +3.0, +4.0), Quaternion::XYZS(-1.0, -2.0, -3.0, +4.0).toConjugate());

        EXPECT_EQ(Quaternion::XYZS(-1.0, -2.0, -3.0, -4.0), Quaternion::XYZS(+1.0, +2.0, +3.0, -4.0).toConjugate());
        EXPECT_EQ(Quaternion::XYZS(+1.0, +2.0, +3.0, -4.0), Quaternion::XYZS(-1.0, -2.0, -3.0, -4.0).toConjugate());
    }

    {
        EXPECT_ANY_THROW(Quaternion::Undefined().toConjugate());
    }
}

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, ToInverse)
// {

//     {

//         FAIL() ;

//     }

// }

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, Exp)
{
    {
        EXPECT_EQ(Quaternion::Unit(), Quaternion::Unit().exp());
        EXPECT_TRUE(
            Quaternion::XYZS(1.0, 0.0, 0.0, 0.0)
                .exp()
                .toNormalized()
                .isNear(Quaternion::XYZS(0.841471, 0.0, 0.0, 0.540302).toNormalized(), Angle::Radians(1e-4))
        );
    }

    {
        EXPECT_ANY_THROW(Quaternion::Undefined().exp());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, Log)
{
    {
        EXPECT_EQ(Quaternion({0.0, 0.0, 0.0}, 0.0), Quaternion::Unit().log());
        EXPECT_TRUE(
            Quaternion::XYZS(0.841471, 0.0, 0.0, 0.540302)
                .log()
                .toNormalized()
                .isNear(Quaternion::XYZS(1.0, 0.0, 0.0, 0.0), Angle::Radians(1e-4))
        );
    }

    {
        EXPECT_ANY_THROW(Quaternion::Undefined().log());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, Pow)
{
    {
        EXPECT_EQ(Quaternion::Unit(), Quaternion::Unit().pow(1.0));
        EXPECT_TRUE(
            Quaternion::XYZS(1.0, 0.0, 0.0, 0.0)
                .pow(2.0)
                .isNear(Quaternion::XYZS(0.0, 0.0, 0.0, -1.0), Angle::Radians(1e-4))
        );
    }

    {
        EXPECT_ANY_THROW(Quaternion::Undefined().pow(2.0));
        EXPECT_ANY_THROW(Quaternion::Unit().pow(Real::Undefined()));
    }
}

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, Norm)
// {

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, CrossMultiply)
// {

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, DotMultiply)
// {

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, RotateVector)
// {

//     {

//         FAIL() ;

//     }

// }

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, ToVector)
{
    {
        EXPECT_EQ(
            Vector4d(0.0, 0.0, 0.0, 1.0), Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).toVector(Quaternion::Format::XYZS)
        );
        EXPECT_EQ(
            Vector4d(1.0, 0.0, 0.0, 0.0), Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).toVector(Quaternion::Format::SXYZ)
        );
    }

    {
        EXPECT_ANY_THROW(Quaternion::Undefined().toVector());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, ToString)
{
    {
        EXPECT_EQ("[0.0, 0.0, 0.0, 1.0]", Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).toString(Quaternion::Format::XYZS));
        EXPECT_EQ("[1.0, 0.0, 0.0, 0.0]", Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).toString(Quaternion::Format::SXYZ));
    }

    {
        EXPECT_EQ(
            "[0.00000, 0.00000, 0.00000, 1.00000]",
            Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).toString(5, Quaternion::Format::XYZS)
        );
        EXPECT_EQ(
            "[1.00000, 0.00000, 0.00000, 0.00000]",
            Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).toString(5, Quaternion::Format::SXYZ)
        );
    }

    {
        EXPECT_EQ("[0.1, 0.1, 0.1, 0.9]", Quaternion::XYZS(0.1, 0.1, 0.1, 0.9).toString(Quaternion::Format::XYZS));
        EXPECT_EQ("[0.9, 0.1, 0.1, 0.1]", Quaternion::XYZS(0.1, 0.1, 0.1, 0.9).toString(Quaternion::Format::SXYZ));
    }

    {
        EXPECT_ANY_THROW(Quaternion::Undefined().toString());
    }
}

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, Normalize)
// {

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, Conjugate)
// {

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, Inverse)
// {

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, Rectify)
// {

//     {

//         FAIL() ;

//     }

// }

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, AngularDifferenceWith)
{
    {
        EXPECT_EQ(Angle::Zero(), Quaternion::Unit().angularDifferenceWith(Quaternion::Unit()));
        EXPECT_EQ(
            Angle::Pi(),
            Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).angularDifferenceWith(Quaternion::XYZS(0.0, 0.0, 1.0, 0.0))
        );

        EXPECT_EQ(
            Angle::Zero(),
            Quaternion::XYZS(-0.707716822367268, -0.000523120993000198, -0.706495803466267, -0.000552600541000209)
                .angularDifferenceWith(
                    Quaternion::XYZS(0.707716822554873, 0.000523120132547009, 0.706495803279188, 0.000552600268546972)
                )
        );
    }

    {
        EXPECT_ANY_THROW(Quaternion::Undefined().angularDifferenceWith(Quaternion::Undefined()));
        EXPECT_ANY_THROW(Quaternion::Unit().angularDifferenceWith(Quaternion::Undefined()));
        EXPECT_ANY_THROW(Quaternion::Undefined().angularDifferenceWith(Quaternion::Unit()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, Undefined)
{
    {
        EXPECT_NO_THROW(Quaternion::Undefined());
        EXPECT_FALSE(Quaternion::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, Unit)
{
    {
        EXPECT_NO_THROW(Quaternion::Unit());
        EXPECT_EQ(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0), Quaternion::Unit());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, XYZS)
{
    {
        EXPECT_NO_THROW(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0));
        EXPECT_EQ(Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS), Quaternion::XYZS(0.0, 0.0, 0.0, 1.0));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, RotationVector)
{
    {
        EXPECT_TRUE(Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS)
                        .isNear(
                            Quaternion::RotationVector(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(0.0))),
                            Angle::Radians(Real::Epsilon())
                        ));
        EXPECT_TRUE(Quaternion(0.0, 0.0, 1.0, 0.0, Quaternion::Format::XYZS)
                        .isNear(
                            Quaternion::RotationVector(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(180.0))),
                            Angle::Radians(Real::Epsilon())
                        ));
    }

    {
        EXPECT_ANY_THROW(Quaternion::RotationVector(RotationVector::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, RotationMatrix)
{
    {
        EXPECT_TRUE(Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS)
                        .isNear(Quaternion::RotationMatrix(RotationMatrix::Unit()), Angle::Radians(Real::Epsilon())));
    }

    {
        for (auto angleDeg = 0.0; angleDeg <= 720.0; angleDeg += 50.0)
        {
            const Angle angle = Angle::Degrees(angleDeg);

            for (auto axisIdx = 0; axisIdx < 20; ++axisIdx)
            {
                const Vector3d axis =
                    Vector3d(std::cos(axisIdx), std::sin(axisIdx), std::cos(axisIdx) * std::sin(axisIdx)).normalized();

                const RotationVector rotationVector_A_B = RotationVector(axis, angle);

                const RotationMatrix rotationMatrix_A_B = RotationMatrix::RotationVector(rotationVector_A_B);

                const Quaternion quaternion_A_B = Quaternion::RotationMatrix(rotationMatrix_A_B);

                EXPECT_TRUE(rotationMatrix_A_B.accessMatrix().isNear(
                    RotationMatrix::Quaternion(quaternion_A_B).accessMatrix(), 1e-14
                ));

                for (auto vectorIdx = 0; vectorIdx < 100; ++vectorIdx)
                {
                    const Vector3d vector_B =
                        Vector3d(std::cos(axisIdx), std::sin(axisIdx), std::cos(axisIdx) * std::sin(axisIdx))
                            .normalized();

                    EXPECT_TRUE((quaternion_A_B * vector_B).isNear((rotationMatrix_A_B * vector_B), 1e-14));
                }
            }
        }
    }

    {
        EXPECT_ANY_THROW(Quaternion::RotationMatrix(RotationMatrix::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, EulerAngle)
{
    {
        EXPECT_EQ(Quaternion::Unit(), Quaternion::EulerAngle(EulerAngle::Unit()));
    }

    // XYZ

    {
        const Table referenceDataTable = Table::Load(
            File::Path(
                Path::Parse(
                    "/app/test/OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/"
                    "EulerAngle/Quaternion-EulerAngle-XYZ.csv"
                )
            ),
            Table::Format::CSV,
            true
        );

        const Real tolerance = 1e-10;

        for (const auto& referenceDataRow : referenceDataTable)
        {
            const Quaternion referenceQuaternion = Quaternion::XYZS(
                                                       referenceDataRow[0].accessReal(),
                                                       referenceDataRow[1].accessReal(),
                                                       referenceDataRow[2].accessReal(),
                                                       referenceDataRow[3].accessReal()
            )
                                                       .normalize()
                                                       .rectify();

            const EulerAngle referenceEulerAngle = EulerAngle::XYZ(
                Angle::Radians(referenceDataRow[4].accessReal()),
                Angle::Radians(referenceDataRow[5].accessReal()),
                Angle::Radians(referenceDataRow[6].accessReal())
            );

            const Quaternion quaternion = Quaternion::EulerAngle(referenceEulerAngle).rectify();

            EXPECT_NEAR(quaternion.x(), referenceQuaternion.x(), tolerance)
                << String::Format("{} / {}", referenceQuaternion.x().toString(), quaternion.x().toString());
            EXPECT_NEAR(quaternion.y(), referenceQuaternion.y(), tolerance)
                << String::Format("{} / {}", referenceQuaternion.y().toString(), quaternion.y().toString());
            EXPECT_NEAR(quaternion.z(), referenceQuaternion.z(), tolerance)
                << String::Format("{} / {}", referenceQuaternion.z().toString(), quaternion.z().toString());
            EXPECT_NEAR(quaternion.s(), referenceQuaternion.s(), tolerance)
                << String::Format("{} / {}", referenceQuaternion.s().toString(), quaternion.s().toString());
        }
    }

    // ZXY

    {
        const Table referenceDataTable = Table::Load(
            File::Path(
                Path::Parse(
                    "/app/test/OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/"
                    "EulerAngle/Quaternion-EulerAngle-ZXY.csv"
                )
            ),
            Table::Format::CSV,
            true
        );

        const Real tolerance = 1e-10;

        for (const auto& referenceDataRow : referenceDataTable)
        {
            const Quaternion referenceQuaternion = Quaternion::XYZS(
                                                       referenceDataRow[0].accessReal(),
                                                       referenceDataRow[1].accessReal(),
                                                       referenceDataRow[2].accessReal(),
                                                       referenceDataRow[3].accessReal()
            )
                                                       .normalize()
                                                       .rectify();

            const EulerAngle referenceEulerAngle = EulerAngle::ZXY(
                Angle::Radians(referenceDataRow[4].accessReal()),
                Angle::Radians(referenceDataRow[5].accessReal()),
                Angle::Radians(referenceDataRow[6].accessReal())
            );

            const Quaternion quaternion = Quaternion::EulerAngle(referenceEulerAngle).rectify();

            EXPECT_NEAR(quaternion.x(), referenceQuaternion.x(), tolerance)
                << String::Format("{} / {}", referenceQuaternion.x().toString(), quaternion.x().toString());
            EXPECT_NEAR(quaternion.y(), referenceQuaternion.y(), tolerance)
                << String::Format("{} / {}", referenceQuaternion.y().toString(), quaternion.y().toString());
            EXPECT_NEAR(quaternion.z(), referenceQuaternion.z(), tolerance)
                << String::Format("{} / {}", referenceQuaternion.z().toString(), quaternion.z().toString());
            EXPECT_NEAR(quaternion.s(), referenceQuaternion.s(), tolerance)
                << String::Format("{} / {}", referenceQuaternion.s().toString(), quaternion.s().toString());
        }
    }

    // ZYX

    {
        const Table referenceDataTable = Table::Load(
            File::Path(
                Path::Parse(
                    "/app/test/OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/"
                    "EulerAngle/Quaternion-EulerAngle-ZYX.csv"
                )
            ),
            Table::Format::CSV,
            true
        );

        const Real tolerance = 1e-10;

        for (const auto& referenceDataRow : referenceDataTable)
        {
            const Quaternion referenceQuaternion = Quaternion::XYZS(
                                                       referenceDataRow[0].accessReal(),
                                                       referenceDataRow[1].accessReal(),
                                                       referenceDataRow[2].accessReal(),
                                                       referenceDataRow[3].accessReal()
            )
                                                       .normalize()
                                                       .rectify();

            const EulerAngle referenceEulerAngle = EulerAngle::ZYX(
                Angle::Radians(referenceDataRow[4].accessReal()),
                Angle::Radians(referenceDataRow[5].accessReal()),
                Angle::Radians(referenceDataRow[6].accessReal())
            );

            const Quaternion quaternion = Quaternion::EulerAngle(referenceEulerAngle).rectify();

            EXPECT_NEAR(quaternion.x(), referenceQuaternion.x(), tolerance)
                << String::Format("{} / {}", referenceQuaternion.x().toString(), quaternion.x().toString());
            EXPECT_NEAR(quaternion.y(), referenceQuaternion.y(), tolerance)
                << String::Format("{} / {}", referenceQuaternion.y().toString(), quaternion.y().toString());
            EXPECT_NEAR(quaternion.z(), referenceQuaternion.z(), tolerance)
                << String::Format("{} / {}", referenceQuaternion.z().toString(), quaternion.z().toString());
            EXPECT_NEAR(quaternion.s(), referenceQuaternion.s(), tolerance)
                << String::Format("{} / {}", referenceQuaternion.s().toString(), quaternion.s().toString());
        }
    }

    {
        EXPECT_ANY_THROW(Quaternion::EulerAngle(EulerAngle::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, Parse)
{
    {
        EXPECT_NO_THROW(Quaternion::Parse("[0.0, 0.0, 0.0, 1.0]", Quaternion::Format::XYZS));
        EXPECT_EQ(
            Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS),
            Quaternion::Parse("[0.0, 0.0, 0.0, 1.0]", Quaternion::Format::XYZS)
        );
        EXPECT_EQ(
            Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS),
            Quaternion::Parse("[1.0, 0.0, 0.0, 0.0]", Quaternion::Format::SXYZ)
        );
    }

    {
        EXPECT_ANY_THROW(Quaternion::Parse(""));
        EXPECT_ANY_THROW(Quaternion::Parse("[]"));
        EXPECT_ANY_THROW(Quaternion::Parse("[0.0, 0.0, 0.0]"));
        EXPECT_ANY_THROW(Quaternion::Parse("[0.0, 0.0, 0.0, 0.0, 1.0]"));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, ShortestRotation)
{
    {
        EXPECT_TRUE(
            Quaternion::ShortestRotation({1.0, 0.0, 0.0}, {1.0, 0.0, 0.0})
                .isNear(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0), Angle::Radians(1e-9))
        );
        EXPECT_TRUE(
            Quaternion::ShortestRotation({1.0, 0.0, 0.0}, {0.0, 1.0, 0.0})
                .isNear(
                    Quaternion::RotationVector(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(-90.0))),
                    Angle::Radians(1e-9)
                )
        );
    }

    {
        const Vector3d v_A = {1.0, 0.0, 0.0};
        const Vector3d v_B = {0.0, 1.0, 0.0};

        const Quaternion q_B_A = Quaternion::ShortestRotation(v_A, v_B);

        ASSERT_TRUE(v_B.isApprox(q_B_A * v_A, 1.0e-9));
    }

    {
        EXPECT_ANY_THROW(Quaternion::ShortestRotation({1.0, 0.0, 0.0}, Vector3d::Undefined()));
        EXPECT_ANY_THROW(Quaternion::ShortestRotation(Vector3d::Undefined(), {1.0, 0.0, 0.0}));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, LERP)
{
    {
        EXPECT_TRUE(
            Quaternion::LERP(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0), Quaternion::XYZS(0.0, 0.0, 1.0, 0.0), 0.0)
                .isNear(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0), Angle::Radians(1e-9))
        );
        EXPECT_TRUE(
            Quaternion::LERP(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0), Quaternion::XYZS(0.0, 0.0, 1.0, 0.0), 1.0)
                .isNear(Quaternion::XYZS(0.0, 0.0, 1.0, 0.0), Angle::Radians(1e-9))
        );
    }

    {
        EXPECT_ANY_THROW(Quaternion::LERP(Quaternion::Undefined(), Quaternion::Unit(), 0.5));
        EXPECT_ANY_THROW(Quaternion::LERP(Quaternion::Unit(), Quaternion::Undefined(), 0.5));
        EXPECT_ANY_THROW(Quaternion::LERP(Quaternion::Unit(), Quaternion::Unit(), Real::Undefined()));

        EXPECT_ANY_THROW(Quaternion::LERP(Quaternion::Unit(), Quaternion::Unit(), -0.1));
        EXPECT_ANY_THROW(Quaternion::LERP(Quaternion::Unit(), Quaternion::Unit(), +1.1));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, NLERP)
{
    {
        EXPECT_TRUE(
            Quaternion::NLERP(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0), Quaternion::XYZS(0.0, 0.0, 1.0, 0.0), 0.0)
                .isNear(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0), Angle::Radians(1e-9))
        );
        EXPECT_TRUE(
            Quaternion::NLERP(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0), Quaternion::XYZS(0.0, 0.0, 1.0, 0.0), 1.0)
                .isNear(Quaternion::XYZS(0.0, 0.0, 1.0, 0.0), Angle::Radians(1e-9))
        );

        EXPECT_TRUE(
            Quaternion::NLERP(
                Quaternion::RotationVector(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(0.0))),
                Quaternion::RotationVector(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(90.0))),
                0.5
            )
                .isNear(
                    Quaternion::RotationVector(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(45.0))),
                    Angle::Radians(1e-9)
                )
        );
    }

    {
        EXPECT_ANY_THROW(Quaternion::NLERP(Quaternion::Undefined(), Quaternion::Unit(), 0.5));
        EXPECT_ANY_THROW(Quaternion::NLERP(Quaternion::Unit(), Quaternion::Undefined(), 0.5));
        EXPECT_ANY_THROW(Quaternion::NLERP(Quaternion::Unit(), Quaternion::Unit(), Real::Undefined()));

        EXPECT_ANY_THROW(Quaternion::NLERP(Quaternion::Unit(), Quaternion::Unit(), -0.1));
        EXPECT_ANY_THROW(Quaternion::NLERP(Quaternion::Unit(), Quaternion::Unit(), +1.1));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_Quaternion, SLERP)
{
    {
        EXPECT_TRUE(
            Quaternion::SLERP(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0), Quaternion::XYZS(0.0, 0.0, 1.0, 0.0), 0.0)
                .isNear(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0), Angle::Radians(1e-9))
        );
        EXPECT_TRUE(
            Quaternion::SLERP(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0), Quaternion::XYZS(0.0, 0.0, 1.0, 0.0), 1.0)
                .isNear(Quaternion::XYZS(0.0, 0.0, 1.0, 0.0), Angle::Radians(1e-9))
        );

        EXPECT_TRUE(
            Quaternion::SLERP(
                Quaternion::RotationVector(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(0.0))),
                Quaternion::RotationVector(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(90.0))),
                0.5
            )
                .isNear(
                    Quaternion::RotationVector(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(45.0))),
                    Angle::Radians(1e-9)
                )
        );
    }

    {
        const Quaternion q_1 = Quaternion::XYZS(1.0, 0.0, 0.0, 0.0);
        const Quaternion q_2 = Quaternion::XYZS(0.0, 1.0, 0.0, 0.0);

        EXPECT_TRUE(
            Quaternion::SLERP(q_1, q_2, 0.0)
                .isNear(Quaternion::XYZS(1.0, 0.0, 0.0, 0.0).toNormalized(), Angle::Radians(1e-9))
        );
        EXPECT_TRUE(
            Quaternion::SLERP(q_1, q_2, 0.2)
                .isNear(
                    Quaternion::XYZS(0.951056516295154, 0.309016994374947, 0.0, 0.0).toNormalized(),
                    Angle::Radians(1e-9)
                )
        );
        EXPECT_TRUE(
            Quaternion::SLERP(q_1, q_2, 0.4)
                .isNear(
                    Quaternion::XYZS(0.809016994374947, 0.587785252292473, 0.0, 0.0).toNormalized(),
                    Angle::Radians(1e-9)
                )
        );
        EXPECT_TRUE(
            Quaternion::SLERP(q_1, q_2, 0.6)
                .isNear(
                    Quaternion::XYZS(0.587785252292473, 0.809016994374947, 0.0, 0.0).toNormalized(),
                    Angle::Radians(1e-9)
                )
        );
        EXPECT_TRUE(
            Quaternion::SLERP(q_1, q_2, 0.8)
                .isNear(
                    Quaternion::XYZS(0.309016994374947, 0.951056516295154, 0.0, 0.0).toNormalized(),
                    Angle::Radians(1e-9)
                )
        );
        EXPECT_TRUE(
            Quaternion::SLERP(q_1, q_2, 1.0)
                .isNear(Quaternion::XYZS(6.12323399573677e-17, 1.0, 0.0, 0.0).toNormalized(), Angle::Radians(1e-9))
        );
    }

    {
        EXPECT_ANY_THROW(Quaternion::SLERP(Quaternion::Undefined(), Quaternion::Unit(), 0.5));
        EXPECT_ANY_THROW(Quaternion::SLERP(Quaternion::Unit(), Quaternion::Undefined(), 0.5));
        EXPECT_ANY_THROW(Quaternion::SLERP(Quaternion::Unit(), Quaternion::Unit(), Real::Undefined()));

        EXPECT_ANY_THROW(Quaternion::SLERP(Quaternion::Unit(), Quaternion::Unit(), -0.1));
        EXPECT_ANY_THROW(Quaternion::SLERP(Quaternion::Unit(), Quaternion::Unit(), +1.1));
    }
}
