/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>

#include <Global.test.hpp>

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation, Constructor)
// {

//     using ostk::mathematics::geometry::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation, EqualToOperator)
// {

//     using ostk::mathematics::geometry::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation, NotEqualToOperator)
// {

//     using ostk::mathematics::geometry::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation, MultiplicationOperator)
// {

//     using ostk::mathematics::geometry::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation, MultiplicationAssignmentOperator)
// {

//     using ostk::mathematics::geometry::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation, StreamOperator)
// {

//     using ostk::mathematics::geometry::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation, IsDefined)
// {

//     using ostk::mathematics::geometry::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation, IsRigid)
// {

//     using ostk::mathematics::geometry::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation, GetType)
// {

//     using ostk::mathematics::geometry::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation, GetMatrix)
// {

//     using ostk::mathematics::geometry::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation, GetInverse)
// {

//     using ostk::mathematics::geometry::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation, ApplyTo)
// {

//     using ostk::mathematics::geometry::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation, Undefined)
// {

//     using ostk::mathematics::geometry::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation, Identity)
// {

//     using ostk::mathematics::geometry::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation, Translation)
// {

//     using ostk::mathematics::geometry::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation, Rotation)
// {

//     using ostk::mathematics::geometry::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation, RotationAround)
{
    using ostk::core::type::String;

    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::Transformation;
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;

    {
        const Point rotationCenter = {0.0, 0.0, 0.0};
        const Angle rotationAngle = Angle::Degrees(45.0);
        const RotationVector rotationVector = {{0.0, 0.0, 1.0}, rotationAngle};

        const Transformation transformation = Transformation::RotationAround(rotationCenter, rotationVector);

        Point point = {0.0, 0.0, 0.0};

        point.applyTransformation(transformation);

        const Point rotatedPoint_ref = {0.0, 0.0, 0.0};

        EXPECT_TRUE(point.isNear(rotatedPoint_ref, 1e-11))
            << String::Format("{} ~ {}", point.toString(), rotatedPoint_ref.toString());
    }

    {
        const Point rotationCenter = {1.0, 0.0, 0.0};
        const Angle rotationAngle = Angle::Degrees(45.0);
        const RotationVector rotationVector = {{0.0, 0.0, 1.0}, rotationAngle};

        const Transformation transformation = Transformation::RotationAround(rotationCenter, rotationVector);

        Point point = {1.0, 0.0, 0.0};

        point.applyTransformation(transformation);

        const Point rotatedPoint_ref = {1.0, 0.0, 0.0};

        EXPECT_TRUE(point.isNear(rotatedPoint_ref, 1e-11))
            << String::Format("{} ~ {}", point.toString(), rotatedPoint_ref.toString());
    }

    {
        const Point rotationCenter = {0.0, 0.0, 0.0};
        const Angle rotationAngle = Angle::Degrees(45.0);
        const RotationVector rotationVector = {{0.0, 0.0, 1.0}, rotationAngle};

        const Transformation transformation = Transformation::RotationAround(rotationCenter, rotationVector);

        Point point = {1.0, 0.0, 0.0};

        point.applyTransformation(transformation);

        const Point rotatedPoint_ref = {+0.70710678118, +0.70710678118, 0.0};

        EXPECT_TRUE(point.isNear(rotatedPoint_ref, 1e-11))
            << String::Format("{} ~ {}", point.toString(), rotatedPoint_ref.toString());
    }

    {
        const Point rotationCenter = {0.0, 0.0, 0.0};
        const Angle rotationAngle = Angle::Degrees(-45.0);
        const RotationVector rotationVector = {{0.0, 0.0, 1.0}, rotationAngle};

        const Transformation transformation = Transformation::RotationAround(rotationCenter, rotationVector);

        Point point = {1.0, 0.0, 0.0};

        point.applyTransformation(transformation);

        const Point rotatedPoint_ref = {+0.70710678118, -0.70710678118, 0.0};

        EXPECT_TRUE(point.isNear(rotatedPoint_ref, 1e-11))
            << String::Format("{} ~ {}", point.toString(), rotatedPoint_ref.toString());
    }

    {
        const Point rotationCenter = {0.0, 0.0, 0.0};
        const Angle rotationAngle = Angle::Degrees(45.0);
        const RotationVector rotationVector = {{0.0, 0.0, 1.0}, rotationAngle};

        EXPECT_ANY_THROW(Transformation::RotationAround(Point::Undefined(), rotationVector));
        EXPECT_ANY_THROW(Transformation::RotationAround(rotationCenter, RotationVector::Undefined()));
        EXPECT_ANY_THROW(Transformation::RotationAround(Point::Undefined(), RotationVector::Undefined()));
    }
}

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation, StringFromType)
// {

//     using ostk::mathematics::geometry::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation, TypeOfMatrix)
// {

//     using ostk::mathematics::geometry::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }
