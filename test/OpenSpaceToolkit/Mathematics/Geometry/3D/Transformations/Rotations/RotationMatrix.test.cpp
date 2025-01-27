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
using ostk::mathematics::object::Matrix3d;
using ostk::mathematics::object::Vector3d;

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, Constructor)
{
    {
        const RotationMatrix rotationMatrix = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};

        EXPECT_TRUE(rotationMatrix.isDefined());
    }

    {
        const RotationMatrix rotationMatrix = {Matrix3d::Identity()};

        EXPECT_TRUE(rotationMatrix.isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, IsDefined)
{
    EXPECT_TRUE(RotationMatrix::Unit().isDefined());
    EXPECT_FALSE(RotationMatrix::Undefined().isDefined());
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, EqualToOperator)
{
    // TBI
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, NotEqualToOperator)
{
    // TBI
}

TEST(
    OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix,
    MultiplicationOperator_RotationMatrix
)
{
    // TBI
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, MultiplicationOperator_Vector3d)
{
    // TBI
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, IndexFunctionOperator)
{
    // TBI
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, AccessMatrix)
{
    {
        const RotationMatrix rotationMatrix = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, -1.0, 0.0};

        const Matrix3d& matrix = rotationMatrix.accessMatrix();

        EXPECT_EQ(1.0, matrix(0, 0));
        EXPECT_EQ(0.0, matrix(0, 1));
        EXPECT_EQ(0.0, matrix(0, 2));
        EXPECT_EQ(0.0, matrix(1, 0));
        EXPECT_EQ(0.0, matrix(1, 1));
        EXPECT_EQ(1.0, matrix(1, 2));
        EXPECT_EQ(0.0, matrix(2, 0));
        EXPECT_EQ(-1.0, matrix(2, 1));
        EXPECT_EQ(0.0, matrix(2, 2));
    }

    {
        EXPECT_ANY_THROW(RotationMatrix::Undefined().accessMatrix());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, GetRowAt)
{
    {
        EXPECT_EQ(Vector3d(1.0, 0.0, 0.0), RotationMatrix::Unit().getRowAt(0));
        EXPECT_EQ(Vector3d(0.0, 1.0, 0.0), RotationMatrix::Unit().getRowAt(1));
        EXPECT_EQ(Vector3d(0.0, 0.0, 1.0), RotationMatrix::Unit().getRowAt(2));
    }

    {
        EXPECT_ANY_THROW(RotationMatrix::Undefined().getRowAt(0));
        EXPECT_ANY_THROW(RotationMatrix::Undefined().getRowAt(1));
        EXPECT_ANY_THROW(RotationMatrix::Undefined().getRowAt(2));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, GetColumnAt)
{
    {
        EXPECT_EQ(Vector3d(1.0, 0.0, 0.0), RotationMatrix::Unit().getColumnAt(0));
        EXPECT_EQ(Vector3d(0.0, 1.0, 0.0), RotationMatrix::Unit().getColumnAt(1));
        EXPECT_EQ(Vector3d(0.0, 0.0, 1.0), RotationMatrix::Unit().getColumnAt(2));
    }

    {
        EXPECT_ANY_THROW(RotationMatrix::Undefined().getColumnAt(0));
        EXPECT_ANY_THROW(RotationMatrix::Undefined().getColumnAt(1));
        EXPECT_ANY_THROW(RotationMatrix::Undefined().getColumnAt(2));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, GetMatrix)
{
    {
        const RotationMatrix rotationMatrix = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, -1.0, 0.0};

        const Matrix3d matrix = rotationMatrix.getMatrix();

        EXPECT_EQ(1.0, matrix(0, 0));
        EXPECT_EQ(0.0, matrix(0, 1));
        EXPECT_EQ(0.0, matrix(0, 2));
        EXPECT_EQ(0.0, matrix(1, 0));
        EXPECT_EQ(0.0, matrix(1, 1));
        EXPECT_EQ(1.0, matrix(1, 2));
        EXPECT_EQ(0.0, matrix(2, 0));
        EXPECT_EQ(-1.0, matrix(2, 1));
        EXPECT_EQ(0.0, matrix(2, 2));
    }

    {
        EXPECT_ANY_THROW(RotationMatrix::Undefined().getMatrix());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, ToTransposed)
{
    {
        EXPECT_EQ(RotationMatrix::Unit(), RotationMatrix::Unit().toTransposed());
    }

    {
        RotationMatrix rotationMatrix = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, -1.0, 0.0};

        const RotationMatrix transposedRotationMatrix = rotationMatrix.toTransposed();

        const RotationMatrix referenceRotationMatrix = {1.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0};

        EXPECT_EQ(referenceRotationMatrix, transposedRotationMatrix);
    }

    {
        EXPECT_ANY_THROW(RotationMatrix::Undefined().toTransposed());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, Transpose)
{
    {
        EXPECT_EQ(RotationMatrix::Unit(), RotationMatrix::Unit().transpose());
    }

    {
        RotationMatrix rotationMatrix = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, -1.0, 0.0};

        rotationMatrix.transpose();

        const RotationMatrix referenceRotationMatrix = {1.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0};

        EXPECT_EQ(referenceRotationMatrix, rotationMatrix);
    }

    {
        EXPECT_ANY_THROW(RotationMatrix::Undefined().transpose());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, Undefined)
{
    EXPECT_NO_THROW(RotationMatrix::Undefined());
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, Unit)
{
    EXPECT_NO_THROW(RotationMatrix::Unit());
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, RX)
{
    {
        EXPECT_EQ(RotationMatrix::Unit(), RotationMatrix::RX(Angle::Degrees(0.0)));
    }

    {
        const RotationMatrix rotationMatrix = RotationMatrix::RX(Angle::Degrees(90.0));

        EXPECT_TRUE(rotationMatrix.getRowAt(0).isApprox(Vector3d(1.0, 0.0, 0.0), 1e-16));
        EXPECT_TRUE(rotationMatrix.getRowAt(1).isApprox(Vector3d(0.0, 0.0, 1.0), 1e-16));
        EXPECT_TRUE(rotationMatrix.getRowAt(2).isApprox(Vector3d(0.0, -1.0, 0.0), 1e-16));
    }

    {
        EXPECT_ANY_THROW(RotationMatrix::RX(Angle::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, RY)
{
    {
        EXPECT_EQ(RotationMatrix::Unit(), RotationMatrix::RY(Angle::Degrees(0.0)));
    }

    {
        const RotationMatrix rotationMatrix = RotationMatrix::RY(Angle::Degrees(90.0));

        EXPECT_TRUE(rotationMatrix.getRowAt(0).isApprox(Vector3d(0.0, 0.0, -1.0), 1e-16));
        EXPECT_TRUE(rotationMatrix.getRowAt(1).isApprox(Vector3d(0.0, 1.0, 0.0), 1e-16));
        EXPECT_TRUE(rotationMatrix.getRowAt(2).isApprox(Vector3d(1.0, 0.0, 0.0), 1e-16));
    }

    {
        EXPECT_ANY_THROW(RotationMatrix::RY(Angle::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, RZ)
{
    {
        EXPECT_EQ(RotationMatrix::Unit(), RotationMatrix::RZ(Angle::Degrees(0.0)));
    }

    {
        const RotationMatrix rotationMatrix = RotationMatrix::RZ(Angle::Degrees(90.0));

        EXPECT_TRUE(rotationMatrix.getRowAt(0).isApprox(Vector3d(0.0, 1.0, 0.0), 1e-16));
        EXPECT_TRUE(rotationMatrix.getRowAt(1).isApprox(Vector3d(-1.0, 0.0, 0.0), 1e-16));
        EXPECT_TRUE(rotationMatrix.getRowAt(2).isApprox(Vector3d(0.0, 0.0, 1.0), 1e-16));
    }

    {
        EXPECT_ANY_THROW(RotationMatrix::RZ(Angle::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, Rows)
{
    {
        EXPECT_EQ(RotationMatrix::Unit(), RotationMatrix::Rows({1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}));
    }

    {
        const RotationMatrix rotationMatrix = RotationMatrix::Rows({0.0, 1.0, 0.0}, {-1.0, 0.0, 0.0}, {0.0, 0.0, 1.0});

        EXPECT_EQ(Vector3d(0.0, 1.0, 0.0), rotationMatrix.getRowAt(0));
        EXPECT_EQ(Vector3d(-1.0, 0.0, 0.0), rotationMatrix.getRowAt(1));
        EXPECT_EQ(Vector3d(0.0, 0.0, 1.0), rotationMatrix.getRowAt(2));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, Columns)
{
    {
        EXPECT_EQ(RotationMatrix::Unit(), RotationMatrix::Columns({1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}));
    }

    {
        const RotationMatrix rotationMatrix =
            RotationMatrix::Columns({0.0, 1.0, 0.0}, {-1.0, 0.0, 0.0}, {0.0, 0.0, 1.0});

        EXPECT_EQ(Vector3d(0.0, 1.0, 0.0), rotationMatrix.getColumnAt(0));
        EXPECT_EQ(Vector3d(-1.0, 0.0, 0.0), rotationMatrix.getColumnAt(1));
        EXPECT_EQ(Vector3d(0.0, 0.0, 1.0), rotationMatrix.getColumnAt(2));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, Quaternion)
{
    {
        EXPECT_EQ(RotationMatrix::Unit(), RotationMatrix::Quaternion(Quaternion::Unit()));
    }

    {
        // TBI
    }

    {
        EXPECT_ANY_THROW(RotationMatrix::Quaternion(Quaternion::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, RotationVector)
{
    {
        EXPECT_EQ(RotationMatrix::Unit(), RotationMatrix::RotationVector(RotationVector::Unit()));
    }

    {
        // TBI
    }

    {
        EXPECT_ANY_THROW(RotationMatrix::RotationVector(RotationVector::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, EulerAngle)
{
    {
        EXPECT_EQ(RotationMatrix::Unit(), RotationMatrix::EulerAngle(EulerAngle::Unit()));
    }

    // XYZ

    {
        // TBI
    }

    // ZXY

    {
        // TBI
    }

    // ZYX

    {
        const Table referenceDataTable = Table::Load(
            File::Path(
                Path::Parse(
                    "/app/test/OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/"
                    "EulerAngle/RotationMatrix-EulerAngle-ZYX.csv"
                )
            ),
            Table::Format::CSV,
            true
        );

        const Real tolerance = 1e-10;

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

            const RotationMatrix referenceRotationMatrix = RotationMatrix::Rows(x, y, z);

            const EulerAngle eulerAngle = EulerAngle::ZYX(
                Angle::Radians(referenceDataRow[9].accessReal()),
                Angle::Radians(referenceDataRow[10].accessReal()),
                Angle::Radians(referenceDataRow[11].accessReal())
            );

            const RotationMatrix rotationMatrix = RotationMatrix::EulerAngle(eulerAngle);

            EXPECT_TRUE(rotationMatrix.getRowAt(0).isApprox(referenceRotationMatrix.getRowAt(0), tolerance))
                << String::Format(
                       "{} / {}", rotationMatrix.getRowAt(0).toString(), referenceRotationMatrix.getRowAt(0).toString()
                   );
            EXPECT_TRUE(rotationMatrix.getRowAt(1).isApprox(referenceRotationMatrix.getRowAt(1), tolerance))
                << String::Format(
                       "{} / {}", rotationMatrix.getRowAt(1).toString(), referenceRotationMatrix.getRowAt(1).toString()
                   );
            EXPECT_TRUE(rotationMatrix.getRowAt(2).isApprox(referenceRotationMatrix.getRowAt(2), tolerance))
                << String::Format(
                       "{} / {}", rotationMatrix.getRowAt(2).toString(), referenceRotationMatrix.getRowAt(2).toString()
                   );
        }
    }

    {
        EXPECT_ANY_THROW(RotationMatrix::EulerAngle(EulerAngle::Undefined()));
    }
}
