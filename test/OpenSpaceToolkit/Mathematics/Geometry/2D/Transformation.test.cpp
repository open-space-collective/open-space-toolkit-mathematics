/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/Angle.hpp>

#include <Global.test.hpp>

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Transformation, Constructor)
// {

//     using ostk::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Transformation, EqualToOperator)
// {

//     using ostk::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Transformation, NotEqualToOperator)
// {

//     using ostk::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Transformation, MultiplicationOperator)
// {

//     using ostk::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Transformation, MultiplicationAssignmentOperator)
// {

//     using ostk::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Transformation, StreamOperator)
// {

//     using ostk::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Transformation, IsDefined)
// {

//     using ostk::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Transformation, GetType)
// {

//     using ostk::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Transformation, GetMatrix)
// {

//     using ostk::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Transformation, GetInverse)
// {

//     using ostk::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Transformation, ApplyTo)
// {

//     using ostk::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Transformation, Undefined)
// {

//     using ostk::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Transformation, Identity)
// {

//     using ostk::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Transformation, Translation)
// {

//     using ostk::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Transformation, Rotation)
// {

//     using ostk::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Transformation, RotationAround)
{
    using ostk::core::types::String;

    using ostk::math::geom::Angle;
    using ostk::math::geom::d2::objects::Point;
    using ostk::math::geom::d2::Transformation;

    {
        const Point rotationCenter = {0.0, 0.0};
        const Angle rotationAngle = Angle::Degrees(45.0);

        const Transformation transformation = Transformation::RotationAround(rotationCenter, rotationAngle);

        Point point = {0.0, 0.0};

        point.applyTransformation(transformation);

        const Point rotatedPoint_ref = {0.0, 0.0};

        EXPECT_TRUE(point.isNear(rotatedPoint_ref, 1e-11))
            << String::Format("{} ~ {}", point.toString(), rotatedPoint_ref.toString());
    }

    {
        const Point rotationCenter = {1.0, 0.0};
        const Angle rotationAngle = Angle::Degrees(45.0);

        const Transformation transformation = Transformation::RotationAround(rotationCenter, rotationAngle);

        Point point = {1.0, 0.0};

        point.applyTransformation(transformation);

        const Point rotatedPoint_ref = {1.0, 0.0};

        EXPECT_TRUE(point.isNear(rotatedPoint_ref, 1e-11))
            << String::Format("{} ~ {}", point.toString(), rotatedPoint_ref.toString());
    }

    {
        const Point rotationCenter = {0.0, 0.0};
        const Angle rotationAngle = Angle::Degrees(45.0);

        const Transformation transformation = Transformation::RotationAround(rotationCenter, rotationAngle);

        Point point = {1.0, 0.0};

        point.applyTransformation(transformation);

        const Point rotatedPoint_ref = {+0.70710678118, +0.70710678118};

        EXPECT_TRUE(point.isNear(rotatedPoint_ref, 1e-11))
            << String::Format("{} ~ {}", point.toString(), rotatedPoint_ref.toString());
    }

    {
        const Point rotationCenter = {0.0, 0.0};
        const Angle rotationAngle = Angle::Degrees(-45.0);

        const Transformation transformation = Transformation::RotationAround(rotationCenter, rotationAngle);

        Point point = {1.0, 0.0};

        point.applyTransformation(transformation);

        const Point rotatedPoint_ref = {+0.70710678118, -0.70710678118};

        EXPECT_TRUE(point.isNear(rotatedPoint_ref, 1e-11))
            << String::Format("{} ~ {}", point.toString(), rotatedPoint_ref.toString());
    }

    {
        const Point rotationCenter = {0.0, 0.0};
        const Angle rotationAngle = Angle::Degrees(45.0);

        EXPECT_ANY_THROW(Transformation::RotationAround(Point::Undefined(), rotationAngle));
        EXPECT_ANY_THROW(Transformation::RotationAround(rotationCenter, Angle::Undefined()));
        EXPECT_ANY_THROW(Transformation::RotationAround(Point::Undefined(), Angle::Undefined()));
    }
}

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Transformation, StringFromType)
// {

//     using ostk::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Transformation, TypeOfMatrix)
// {

//     using ostk::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }
