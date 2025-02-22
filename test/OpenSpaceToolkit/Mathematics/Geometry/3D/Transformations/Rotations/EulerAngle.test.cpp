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
using ostk::core::type::String;

using ostk::mathematics::geometry::Angle;
using ostk::mathematics::geometry::d3::transformation::rotation::EulerAngle;
using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;
using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix;
using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;
using ostk::mathematics::object::Vector3d;

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_EulerAngle, Constructor)
{
    {
        EulerAngle eulerAngle = {
            Angle::Degrees(0.0), Angle::Degrees(0.0), Angle::Degrees(0.0), EulerAngle::AxisSequence::ZYX
        };

        EXPECT_TRUE(eulerAngle.isDefined());
    }

    {
        EulerAngle eulerAngle = {
            Angle::Degrees(0.0), Angle::Undefined(), Angle::Degrees(0.0), EulerAngle::AxisSequence::ZYX
        };

        EXPECT_FALSE(eulerAngle.isDefined());
    }

    {
        EulerAngle eulerAngle = {
            Angle::Degrees(0.0), Angle::Degrees(0.0), Angle::Degrees(0.0), EulerAngle::AxisSequence::Undefined
        };

        EXPECT_FALSE(eulerAngle.isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_EulerAngle, EqualToOperator)
{
    {
        EXPECT_TRUE(
            EulerAngle(Angle::Degrees(0.0), Angle::Degrees(0.0), Angle::Degrees(0.0), EulerAngle::AxisSequence::ZYX) ==
            EulerAngle(Angle::Degrees(0.0), Angle::Degrees(0.0), Angle::Degrees(0.0), EulerAngle::AxisSequence::ZYX)
        );

        EXPECT_TRUE(
            EulerAngle(Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0), EulerAngle::AxisSequence::ZYX) ==
            EulerAngle(Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0), EulerAngle::AxisSequence::ZYX)
        );
    }

    {
        EXPECT_FALSE(
            EulerAngle(Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0), EulerAngle::AxisSequence::ZYX) ==
            EulerAngle(Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0), EulerAngle::AxisSequence::XYZ)
        );

        EXPECT_FALSE(
            EulerAngle(Angle::Degrees(0.0), Angle::Degrees(0.0), Angle::Degrees(0.0), EulerAngle::AxisSequence::ZYX) ==
            EulerAngle::Undefined()
        );

        EXPECT_FALSE(
            EulerAngle::Undefined() ==
            EulerAngle(Angle::Degrees(0.0), Angle::Degrees(0.0), Angle::Degrees(0.0), EulerAngle::AxisSequence::ZYX)
        );

        EXPECT_FALSE(EulerAngle::Undefined() == EulerAngle::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_EulerAngle, NotEqualToOperator)
{
    {
        EXPECT_TRUE(
            EulerAngle(Angle::Degrees(0.0), Angle::Degrees(0.0), Angle::Degrees(0.0), EulerAngle::AxisSequence::ZYX) !=
            EulerAngle(Angle::Degrees(0.0), Angle::Degrees(0.0), Angle::Degrees(1.0), EulerAngle::AxisSequence::ZYX)
        );

        EXPECT_TRUE(
            EulerAngle(Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0), EulerAngle::AxisSequence::ZYX) !=
            EulerAngle(Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0), EulerAngle::AxisSequence::XYZ)
        );
    }

    {
        EXPECT_FALSE(
            EulerAngle(Angle::Degrees(0.0), Angle::Degrees(0.0), Angle::Degrees(0.0), EulerAngle::AxisSequence::ZYX) !=
            EulerAngle(Angle::Degrees(0.0), Angle::Degrees(0.0), Angle::Degrees(0.0), EulerAngle::AxisSequence::ZYX)
        );

        EXPECT_FALSE(
            EulerAngle(Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0), EulerAngle::AxisSequence::ZYX) !=
            EulerAngle(Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0), EulerAngle::AxisSequence::ZYX)
        );
    }

    {
        EXPECT_TRUE(
            EulerAngle(Angle::Degrees(0.0), Angle::Degrees(0.0), Angle::Degrees(0.0), EulerAngle::AxisSequence::ZYX) !=
            EulerAngle::Undefined()
        );

        EXPECT_TRUE(
            EulerAngle::Undefined() !=
            EulerAngle(Angle::Degrees(0.0), Angle::Degrees(0.0), Angle::Degrees(0.0), EulerAngle::AxisSequence::ZYX)
        );

        EXPECT_TRUE(EulerAngle::Undefined() != EulerAngle::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_EulerAngle, IsDefined)
{
    {
        EXPECT_TRUE(
            EulerAngle(Angle::Degrees(0.0), Angle::Degrees(0.0), Angle::Degrees(0.0), EulerAngle::AxisSequence::ZYX)
                .isDefined()
        );

        EXPECT_TRUE(
            EulerAngle(Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0), EulerAngle::AxisSequence::ZYX)
                .isDefined()
        );
    }

    {
        EXPECT_FALSE(
            EulerAngle(Angle::Degrees(1.0), Angle::Undefined(), Angle::Degrees(3.0), EulerAngle::AxisSequence::ZYX)
                .isDefined()
        );
    }

    {
        EXPECT_FALSE(EulerAngle::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_EulerAngle, IsUnitary)
{
    {
        EXPECT_TRUE(
            EulerAngle(Angle::Degrees(0.0), Angle::Degrees(0.0), Angle::Degrees(0.0), EulerAngle::AxisSequence::ZYX)
                .isUnitary()
        );

        EXPECT_TRUE(EulerAngle::Unit().isUnitary());
    }

    {
        EXPECT_FALSE(
            EulerAngle(Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0), EulerAngle::AxisSequence::ZYX)
                .isUnitary()
        );
    }

    {
        EXPECT_ANY_THROW(EulerAngle::Undefined().isUnitary());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_EulerAngle, IsNear)
{
    {
        EXPECT_TRUE(
            EulerAngle(Angle::Degrees(0.0), Angle::Degrees(0.0), Angle::Degrees(0.0), EulerAngle::AxisSequence::ZYX)
                .isNear(
                    EulerAngle(
                        Angle::Degrees(0.0), Angle::Degrees(0.0), Angle::Degrees(0.0), EulerAngle::AxisSequence::ZYX
                    ),
                    Angle::Degrees(0.0)
                )
        );

        EXPECT_TRUE(
            EulerAngle(Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0), EulerAngle::AxisSequence::ZYX)
                .isNear(
                    EulerAngle(
                        Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0), EulerAngle::AxisSequence::ZYX
                    ),
                    Angle::Degrees(0.0)
                )
        );

        EXPECT_TRUE(
            EulerAngle(Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0), EulerAngle::AxisSequence::ZYX)
                .isNear(
                    EulerAngle(
                        Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0), EulerAngle::AxisSequence::ZYX
                    ),
                    Angle::Degrees(1.0)
                )
        );

        EXPECT_TRUE(
            EulerAngle(Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(4.0), EulerAngle::AxisSequence::ZYX)
                .isNear(
                    EulerAngle(
                        Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0), EulerAngle::AxisSequence::ZYX
                    ),
                    Angle::Degrees(1.0)
                )
        );
    }

    {
        EXPECT_FALSE(
            EulerAngle(Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.1), EulerAngle::AxisSequence::ZYX)
                .isNear(
                    EulerAngle(
                        Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0), EulerAngle::AxisSequence::ZYX
                    ),
                    Angle::Degrees(0.0)
                )
        );
    }

    {
        EXPECT_ANY_THROW(EulerAngle::Unit().isNear(EulerAngle::Undefined(), Angle::Undefined()));
        EXPECT_ANY_THROW(EulerAngle::Undefined().isNear(EulerAngle::Unit(), Angle::Undefined()));
        EXPECT_ANY_THROW(EulerAngle::Unit().isNear(EulerAngle::Unit(), Angle::Undefined()));
        EXPECT_ANY_THROW(EulerAngle::Undefined().isNear(EulerAngle::Undefined(), Angle::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_EulerAngle, GetPhi)
{
    {
        EXPECT_EQ(
            Angle::Degrees(1.0),
            EulerAngle(Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0), EulerAngle::AxisSequence::ZYX)
                .getPhi()
        );
    }

    {
        EXPECT_ANY_THROW(EulerAngle::Undefined().getPhi());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_EulerAngle, GetTheta)
{
    {
        EXPECT_EQ(
            Angle::Degrees(2.0),
            EulerAngle(Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0), EulerAngle::AxisSequence::ZYX)
                .getTheta()
        );
    }

    {
        EXPECT_ANY_THROW(EulerAngle::Undefined().getTheta());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_EulerAngle, GetPsi)
{
    {
        EXPECT_EQ(
            Angle::Degrees(3.0),
            EulerAngle(Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0), EulerAngle::AxisSequence::ZYX)
                .getPsi()
        );
    }

    {
        EXPECT_ANY_THROW(EulerAngle::Undefined().getPsi());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_EulerAngle, GetAxisSequence)
{
    {
        EXPECT_EQ(
            EulerAngle::AxisSequence::ZYX,
            EulerAngle(Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0), EulerAngle::AxisSequence::ZYX)
                .getAxisSequence()
        );
    }

    {
        EXPECT_ANY_THROW(EulerAngle::Undefined().getAxisSequence());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_EulerAngle, ToVector)
{
    {
        EXPECT_EQ(
            Vector3d(1.0, 2.0, 3.0),
            EulerAngle(Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0), EulerAngle::AxisSequence::ZYX)
                .toVector(Angle::Unit::Degree)
        );
    }

    {
        EXPECT_ANY_THROW(EulerAngle::Undefined().toVector(Angle::Unit::Degree));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_EulerAngle, ToString)
{
    {
        EXPECT_EQ(
            "[1.1, 2.2, 3.3] (ZYX)",
            EulerAngle(Angle::Degrees(1.1), Angle::Degrees(2.2), Angle::Degrees(3.3), EulerAngle::AxisSequence::ZYX)
                .toString(Angle::Unit::Degree)
        );
    }

    {
        EXPECT_ANY_THROW(EulerAngle::Undefined().toString(Angle::Unit::Degree));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_EulerAngle, Undefined)
{
    {
        EXPECT_NO_THROW(EulerAngle::Undefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_EulerAngle, Unit)
{
    {
        EXPECT_NO_THROW(EulerAngle::Unit());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_EulerAngle, XYZ)
{
    {
        EXPECT_EQ(
            EulerAngle(Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0), EulerAngle::AxisSequence::XYZ),
            EulerAngle::XYZ(Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0))
        );
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_EulerAngle, ZXY)
{
    {
        EXPECT_EQ(
            EulerAngle(Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0), EulerAngle::AxisSequence::ZXY),
            EulerAngle::ZXY(Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0))
        );
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_EulerAngle, ZYX)
{
    {
        EXPECT_EQ(
            EulerAngle(Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0), EulerAngle::AxisSequence::ZYX),
            EulerAngle::ZYX(Angle::Degrees(1.0), Angle::Degrees(2.0), Angle::Degrees(3.0))
        );
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_EulerAngle, Quaternion)
{
    {
        EXPECT_EQ(EulerAngle::Unit(), EulerAngle::Quaternion(Quaternion::Unit(), EulerAngle::AxisSequence::ZYX));
    }

    // XYZ

    {
        const Table referenceDataTable = Table::Load(
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/"
                                   "EulerAngle/Quaternion-EulerAngle-XYZ.csv")),
            Table::Format::CSV,
            true
        );

        const Angle angularTolerance = Angle::Degrees(1e-8);

        for (const auto& referenceDataRow : referenceDataTable)
        {
            const Quaternion quaternion = Quaternion::XYZS(
                                              referenceDataRow[0].accessReal(),
                                              referenceDataRow[1].accessReal(),
                                              referenceDataRow[2].accessReal(),
                                              referenceDataRow[3].accessReal()
            )
                                              .normalize();

            const EulerAngle referenceEulerAngle = EulerAngle::ZYX(
                Angle::Radians(referenceDataRow[4].accessReal()),
                Angle::Radians(referenceDataRow[5].accessReal()),
                Angle::Radians(referenceDataRow[6].accessReal())
            );

            const EulerAngle eulerAngle = EulerAngle::Quaternion(quaternion, EulerAngle::AxisSequence::XYZ);

            EXPECT_TRUE(eulerAngle.getPhi().isNear(referenceEulerAngle.getPhi(), angularTolerance))
                << String::Format("{} / {}", referenceEulerAngle.getPhi().toString(), eulerAngle.getPhi().toString());
            EXPECT_TRUE(eulerAngle.getTheta().isNear(referenceEulerAngle.getTheta(), angularTolerance)
            ) << String::Format("{} / {}", referenceEulerAngle.getTheta().toString(), eulerAngle.getTheta().toString());
            EXPECT_TRUE(eulerAngle.getPsi().isNear(referenceEulerAngle.getPsi(), angularTolerance))
                << String::Format("{} / {}", referenceEulerAngle.getPsi().toString(), eulerAngle.getPsi().toString());
        }
    }

    // ZXY

    {
        const Table referenceDataTable = Table::Load(
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/"
                                   "EulerAngle/Quaternion-EulerAngle-ZXY.csv")),
            Table::Format::CSV,
            true
        );

        const Angle angularTolerance = Angle::Degrees(1e-8);

        for (const auto& referenceDataRow : referenceDataTable)
        {
            const Quaternion quaternion = Quaternion::XYZS(
                                              referenceDataRow[0].accessReal(),
                                              referenceDataRow[1].accessReal(),
                                              referenceDataRow[2].accessReal(),
                                              referenceDataRow[3].accessReal()
            )
                                              .normalize();

            const EulerAngle referenceEulerAngle = EulerAngle::ZXY(
                Angle::Radians(referenceDataRow[4].accessReal()),
                Angle::Radians(referenceDataRow[5].accessReal()),
                Angle::Radians(referenceDataRow[6].accessReal())
            );

            const EulerAngle eulerAngle = EulerAngle::Quaternion(quaternion, EulerAngle::AxisSequence::ZXY);

            EXPECT_TRUE(eulerAngle.getPhi().isNear(referenceEulerAngle.getPhi(), angularTolerance))
                << String::Format("{} / {}", referenceEulerAngle.getPhi().toString(), eulerAngle.getPhi().toString());
            EXPECT_TRUE(eulerAngle.getTheta().isNear(referenceEulerAngle.getTheta(), angularTolerance)
            ) << String::Format("{} / {}", referenceEulerAngle.getTheta().toString(), eulerAngle.getTheta().toString());
            EXPECT_TRUE(eulerAngle.getPsi().isNear(referenceEulerAngle.getPsi(), angularTolerance))
                << String::Format("{} / {}", referenceEulerAngle.getPsi().toString(), eulerAngle.getPsi().toString());
        }
    }

    // ZYX

    {
        const Table referenceDataTable = Table::Load(
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/"
                                   "EulerAngle/Quaternion-EulerAngle-ZYX.csv")),
            Table::Format::CSV,
            true
        );

        const Angle angularTolerance = Angle::Degrees(1e-8);

        for (const auto& referenceDataRow : referenceDataTable)
        {
            const Quaternion quaternion = Quaternion::XYZS(
                                              referenceDataRow[0].accessReal(),
                                              referenceDataRow[1].accessReal(),
                                              referenceDataRow[2].accessReal(),
                                              referenceDataRow[3].accessReal()
            )
                                              .normalize();

            const EulerAngle referenceEulerAngle = EulerAngle::ZYX(
                Angle::Radians(referenceDataRow[4].accessReal()),
                Angle::Radians(referenceDataRow[5].accessReal()),
                Angle::Radians(referenceDataRow[6].accessReal())
            );

            const EulerAngle eulerAngle = EulerAngle::Quaternion(quaternion, EulerAngle::AxisSequence::ZYX);

            EXPECT_TRUE(eulerAngle.getPhi().isNear(referenceEulerAngle.getPhi(), angularTolerance))
                << String::Format("{} / {}", referenceEulerAngle.getPhi().toString(), eulerAngle.getPhi().toString());
            EXPECT_TRUE(eulerAngle.getTheta().isNear(referenceEulerAngle.getTheta(), angularTolerance)
            ) << String::Format("{} / {}", referenceEulerAngle.getTheta().toString(), eulerAngle.getTheta().toString());
            EXPECT_TRUE(eulerAngle.getPsi().isNear(referenceEulerAngle.getPsi(), angularTolerance))
                << String::Format("{} / {}", referenceEulerAngle.getPsi().toString(), eulerAngle.getPsi().toString());
        }
    }

    {
        EXPECT_ANY_THROW(EulerAngle::Quaternion(Quaternion::Unit(), EulerAngle::AxisSequence::Undefined));
        EXPECT_ANY_THROW(EulerAngle::Quaternion(Quaternion::Undefined(), EulerAngle::AxisSequence::ZYX));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_EulerAngle, RotationVector)
{
    {
        EXPECT_EQ(
            EulerAngle::Unit(), EulerAngle::RotationVector(RotationVector::Unit(), EulerAngle::AxisSequence::ZYX)
        );
    }

    // XYZ

    {
        const Table referenceDataTable = Table::Load(
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/"
                                   "EulerAngle/RotationVector-EulerAngle-XYZ.csv")),
            Table::Format::CSV,
            true
        );

        const Angle angularTolerance = Angle::Degrees(1e-6);

        for (const auto& referenceDataRow : referenceDataTable)
        {
            const RotationVector rotationVector = RotationVector(
                Vector3d(
                    referenceDataRow[0].accessReal(), referenceDataRow[1].accessReal(), referenceDataRow[2].accessReal()
                ),
                Angle::Unit::Radian
            );

            const EulerAngle referenceEulerAngle = EulerAngle::XYZ(
                Angle::Radians(referenceDataRow[3].accessReal()),
                Angle::Radians(referenceDataRow[4].accessReal()),
                Angle::Radians(referenceDataRow[5].accessReal())
            );

            const EulerAngle eulerAngle = EulerAngle::RotationVector(rotationVector, EulerAngle::AxisSequence::XYZ);

            EXPECT_TRUE(eulerAngle.getPhi().isNear(referenceEulerAngle.getPhi(), angularTolerance))
                << String::Format("{} / {}", referenceEulerAngle.getPhi().toString(), eulerAngle.getPhi().toString());
            EXPECT_TRUE(eulerAngle.getTheta().isNear(referenceEulerAngle.getTheta(), angularTolerance)
            ) << String::Format("{} / {}", referenceEulerAngle.getTheta().toString(), eulerAngle.getTheta().toString());
            EXPECT_TRUE(eulerAngle.getPsi().isNear(referenceEulerAngle.getPsi(), angularTolerance))
                << String::Format("{} / {}", referenceEulerAngle.getPsi().toString(), eulerAngle.getPsi().toString());
        }
    }

    // ZXY

    {
        const Table referenceDataTable = Table::Load(
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/"
                                   "EulerAngle/RotationVector-EulerAngle-ZXY.csv")),
            Table::Format::CSV,
            true
        );

        const Angle angularTolerance = Angle::Degrees(1e-6);

        for (const auto& referenceDataRow : referenceDataTable)
        {
            const RotationVector rotationVector = RotationVector(
                Vector3d(
                    referenceDataRow[0].accessReal(), referenceDataRow[1].accessReal(), referenceDataRow[2].accessReal()
                ),
                Angle::Unit::Radian
            );

            const EulerAngle referenceEulerAngle = EulerAngle::ZXY(
                Angle::Radians(referenceDataRow[3].accessReal()),
                Angle::Radians(referenceDataRow[4].accessReal()),
                Angle::Radians(referenceDataRow[5].accessReal())
            );

            const EulerAngle eulerAngle = EulerAngle::RotationVector(rotationVector, EulerAngle::AxisSequence::ZXY);

            EXPECT_TRUE(eulerAngle.getPhi().isNear(referenceEulerAngle.getPhi(), angularTolerance))
                << String::Format("{} / {}", referenceEulerAngle.getPhi().toString(), eulerAngle.getPhi().toString());
            EXPECT_TRUE(eulerAngle.getTheta().isNear(referenceEulerAngle.getTheta(), angularTolerance)
            ) << String::Format("{} / {}", referenceEulerAngle.getTheta().toString(), eulerAngle.getTheta().toString());
            EXPECT_TRUE(eulerAngle.getPsi().isNear(referenceEulerAngle.getPsi(), angularTolerance))
                << String::Format("{} / {}", referenceEulerAngle.getPsi().toString(), eulerAngle.getPsi().toString());
        }
    }

    // ZYX

    {
        const Table referenceDataTable = Table::Load(
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/"
                                   "EulerAngle/RotationVector-EulerAngle-ZYX.csv")),
            Table::Format::CSV,
            true
        );

        const Angle angularTolerance = Angle::Degrees(1e-6);

        for (const auto& referenceDataRow : referenceDataTable)
        {
            const RotationVector rotationVector = RotationVector(
                Vector3d(
                    referenceDataRow[0].accessReal(), referenceDataRow[1].accessReal(), referenceDataRow[2].accessReal()
                ),
                Angle::Unit::Radian
            );

            const EulerAngle referenceEulerAngle = EulerAngle::ZYX(
                Angle::Radians(referenceDataRow[3].accessReal()),
                Angle::Radians(referenceDataRow[4].accessReal()),
                Angle::Radians(referenceDataRow[5].accessReal())
            );

            const EulerAngle eulerAngle = EulerAngle::RotationVector(rotationVector, EulerAngle::AxisSequence::ZYX);

            EXPECT_TRUE(eulerAngle.getPhi().isNear(referenceEulerAngle.getPhi(), angularTolerance))
                << String::Format("{} / {}", referenceEulerAngle.getPhi().toString(), eulerAngle.getPhi().toString());
            EXPECT_TRUE(eulerAngle.getTheta().isNear(referenceEulerAngle.getTheta(), angularTolerance)
            ) << String::Format("{} / {}", referenceEulerAngle.getTheta().toString(), eulerAngle.getTheta().toString());
            EXPECT_TRUE(eulerAngle.getPsi().isNear(referenceEulerAngle.getPsi(), angularTolerance))
                << String::Format("{} / {}", referenceEulerAngle.getPsi().toString(), eulerAngle.getPsi().toString());
        }
    }

    {
        EXPECT_ANY_THROW(EulerAngle::RotationVector(RotationVector::Unit(), EulerAngle::AxisSequence::Undefined));
        EXPECT_ANY_THROW(EulerAngle::RotationVector(RotationVector::Undefined(), EulerAngle::AxisSequence::ZYX));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_EulerAngle, RotationMatrix)
{
    {
        EXPECT_EQ(
            EulerAngle::Unit(), EulerAngle::RotationMatrix(RotationMatrix::Unit(), EulerAngle::AxisSequence::ZYX)
        );
    }

    // XYZ

    {
        const Table referenceDataTable = Table::Load(
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/"
                                   "EulerAngle/RotationMatrix-EulerAngle-XYZ.csv")),
            Table::Format::CSV,
            true
        );

        const Angle angularTolerance = Angle::Degrees(1e-8);

        for (const auto& referenceDataRow : referenceDataTable)
        {
            const Vector3d x =
                Vector3d(
                    referenceDataRow[0].accessReal(), referenceDataRow[1].accessReal(), referenceDataRow[2].accessReal()
                )
                    .normalized();

            Vector3d y =
                Vector3d(
                    referenceDataRow[3].accessReal(), referenceDataRow[4].accessReal(), referenceDataRow[5].accessReal()
                )
                    .normalized();

            const Vector3d z = x.cross(y);

            // Ensure that the y-axis is orthogonal to the x-axis
            y = z.cross(x);

            const RotationMatrix rotationMatrix = RotationMatrix::Rows(x, y, z);

            const EulerAngle referenceEulerAngle = EulerAngle::XYZ(
                Angle::Radians(referenceDataRow[9].accessReal()),
                Angle::Radians(referenceDataRow[10].accessReal()),
                Angle::Radians(referenceDataRow[11].accessReal())
            );

            const EulerAngle eulerAngle = EulerAngle::RotationMatrix(rotationMatrix, EulerAngle::AxisSequence::XYZ);

            EXPECT_TRUE(eulerAngle.getPhi().isNear(referenceEulerAngle.getPhi(), angularTolerance))
                << String::Format("{} / {}", referenceEulerAngle.getPhi().toString(), eulerAngle.getPhi().toString());
            EXPECT_TRUE(eulerAngle.getTheta().isNear(referenceEulerAngle.getTheta(), angularTolerance)
            ) << String::Format("{} / {}", referenceEulerAngle.getTheta().toString(), eulerAngle.getTheta().toString());
            EXPECT_TRUE(eulerAngle.getPsi().isNear(referenceEulerAngle.getPsi(), angularTolerance))
                << String::Format("{} / {}", referenceEulerAngle.getPsi().toString(), eulerAngle.getPsi().toString());
        }
    }

    // ZXY

    {
        const Table referenceDataTable = Table::Load(
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/"
                                   "EulerAngle/RotationMatrix-EulerAngle-ZXY.csv")),
            Table::Format::CSV,
            true
        );

        const Angle angularTolerance = Angle::Degrees(1e-8);

        for (const auto& referenceDataRow : referenceDataTable)
        {
            const Vector3d x =
                Vector3d(
                    referenceDataRow[0].accessReal(), referenceDataRow[1].accessReal(), referenceDataRow[2].accessReal()
                )
                    .normalized();

            Vector3d y =
                Vector3d(
                    referenceDataRow[3].accessReal(), referenceDataRow[4].accessReal(), referenceDataRow[5].accessReal()
                )
                    .normalized();

            const Vector3d z = x.cross(y);

            // Ensure that the y-axis is orthogonal to the x-axis
            y = z.cross(x);

            const RotationMatrix rotationMatrix = RotationMatrix::Rows(x, y, z);

            const EulerAngle referenceEulerAngle = EulerAngle::ZXY(
                Angle::Radians(referenceDataRow[9].accessReal()),
                Angle::Radians(referenceDataRow[10].accessReal()),
                Angle::Radians(referenceDataRow[11].accessReal())
            );

            const EulerAngle eulerAngle = EulerAngle::RotationMatrix(rotationMatrix, EulerAngle::AxisSequence::ZXY);

            EXPECT_TRUE(eulerAngle.getPhi().isNear(referenceEulerAngle.getPhi(), angularTolerance))
                << String::Format("{} / {}", referenceEulerAngle.getPhi().toString(), eulerAngle.getPhi().toString());
            EXPECT_TRUE(eulerAngle.getTheta().isNear(referenceEulerAngle.getTheta(), angularTolerance)
            ) << String::Format("{} / {}", referenceEulerAngle.getTheta().toString(), eulerAngle.getTheta().toString());
            EXPECT_TRUE(eulerAngle.getPsi().isNear(referenceEulerAngle.getPsi(), angularTolerance))
                << String::Format("{} / {}", referenceEulerAngle.getPsi().toString(), eulerAngle.getPsi().toString());
        }
    }

    // ZYX

    {
        const Table referenceDataTable = Table::Load(
            File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/"
                                   "EulerAngle/RotationMatrix-EulerAngle-ZYX.csv")),
            Table::Format::CSV,
            true
        );

        const Angle angularTolerance = Angle::Degrees(1e-8);

        for (const auto& referenceDataRow : referenceDataTable)
        {
            const Vector3d x =
                Vector3d(
                    referenceDataRow[0].accessReal(), referenceDataRow[1].accessReal(), referenceDataRow[2].accessReal()
                )
                    .normalized();

            Vector3d y =
                Vector3d(
                    referenceDataRow[3].accessReal(), referenceDataRow[4].accessReal(), referenceDataRow[5].accessReal()
                )
                    .normalized();

            const Vector3d z = x.cross(y);

            // Ensure that the y-axis is orthogonal to the x-axis
            y = z.cross(x);

            const RotationMatrix rotationMatrix = RotationMatrix::Rows(x, y, z);

            const EulerAngle referenceEulerAngle = EulerAngle::ZYX(
                Angle::Radians(referenceDataRow[9].accessReal()),
                Angle::Radians(referenceDataRow[10].accessReal()),
                Angle::Radians(referenceDataRow[11].accessReal())
            );

            const EulerAngle eulerAngle = EulerAngle::RotationMatrix(rotationMatrix, EulerAngle::AxisSequence::ZYX);

            EXPECT_TRUE(eulerAngle.getPhi().isNear(referenceEulerAngle.getPhi(), angularTolerance))
                << String::Format("{} / {}", referenceEulerAngle.getPhi().toString(), eulerAngle.getPhi().toString());
            EXPECT_TRUE(eulerAngle.getTheta().isNear(referenceEulerAngle.getTheta(), angularTolerance)
            ) << String::Format("{} / {}", referenceEulerAngle.getTheta().toString(), eulerAngle.getTheta().toString());
            EXPECT_TRUE(eulerAngle.getPsi().isNear(referenceEulerAngle.getPsi(), angularTolerance))
                << String::Format("{} / {}", referenceEulerAngle.getPsi().toString(), eulerAngle.getPsi().toString());
        }
    }

    {
        EXPECT_ANY_THROW(EulerAngle::RotationMatrix(RotationMatrix::Unit(), EulerAngle::AxisSequence::Undefined));
        EXPECT_ANY_THROW(EulerAngle::RotationMatrix(RotationMatrix::Undefined(), EulerAngle::AxisSequence::ZYX));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_EulerAngle, StringFromAxisSequence)
{
    {
        EXPECT_EQ("XYZ", EulerAngle::StringFromAxisSequence(EulerAngle::AxisSequence::XYZ));
        EXPECT_EQ("ZXY", EulerAngle::StringFromAxisSequence(EulerAngle::AxisSequence::ZXY));
        EXPECT_EQ("XYZ", EulerAngle::StringFromAxisSequence(EulerAngle::AxisSequence::XYZ));
    }

    {
        EXPECT_ANY_THROW(EulerAngle::StringFromAxisSequence(EulerAngle::AxisSequence::Undefined));
    }
}
