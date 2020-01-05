////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Point.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TEST (Library_Mathematics_Geometry_3D_Transformation, Constructor)
// {

//     using ostk::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, EqualToOperator)
// {

//     using ostk::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, NotEqualToOperator)
// {

//     using ostk::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, MultiplicationOperator)
// {

//     using ostk::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, MultiplicationAssignmentOperator)
// {

//     using ostk::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, StreamOperator)
// {

//     using ostk::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, IsDefined)
// {

//     using ostk::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, IsRigid)
// {

//     using ostk::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, GetType)
// {

//     using ostk::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, GetMatrix)
// {

//     using ostk::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, GetInverse)
// {

//     using ostk::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, ApplyTo)
// {

//     using ostk::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, Undefined)
// {

//     using ostk::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, Identity)
// {

//     using ostk::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, Translation)
// {

//     using ostk::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, Rotation)
// {

//     using ostk::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

TEST (Library_Mathematics_Geometry_3D_Transformation, RotationAround)
{

    using ostk::core::types::String ;

    using ostk::math::geom::Angle ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::Transformation ;
    using ostk::math::geom::d3::trf::rot::RotationVector ;

    {

        const Point rotationCenter = { 0.0, 0.0, 0.0 } ;
        const Angle rotationAngle = Angle::Degrees(45.0) ;
        const RotationVector rotationVector = { { 0.0, 0.0, 1.0 }, rotationAngle } ;

        const Transformation transformation = Transformation::RotationAround(rotationCenter, rotationVector) ;

        Point point = { 0.0, 0.0, 0.0 } ;

        point.applyTransformation(transformation) ;

        const Point rotatedPoint_ref = { 0.0, 0.0, 0.0 } ;

        EXPECT_TRUE(point.isNear(rotatedPoint_ref, 1e-11)) << String::Format("{} ~ {}", point.toString(), rotatedPoint_ref.toString()) ;

    }

    {

        const Point rotationCenter = { 1.0, 0.0, 0.0 } ;
        const Angle rotationAngle = Angle::Degrees(45.0) ;
        const RotationVector rotationVector = { { 0.0, 0.0, 1.0 }, rotationAngle } ;

        const Transformation transformation = Transformation::RotationAround(rotationCenter, rotationVector) ;

        Point point = { 1.0, 0.0, 0.0 } ;

        point.applyTransformation(transformation) ;

        const Point rotatedPoint_ref = { 1.0, 0.0, 0.0 } ;

        EXPECT_TRUE(point.isNear(rotatedPoint_ref, 1e-11)) << String::Format("{} ~ {}", point.toString(), rotatedPoint_ref.toString()) ;

    }

    {

        const Point rotationCenter = { 0.0, 0.0, 0.0 } ;
        const Angle rotationAngle = Angle::Degrees(45.0) ;
        const RotationVector rotationVector = { { 0.0, 0.0, 1.0 }, rotationAngle } ;

        const Transformation transformation = Transformation::RotationAround(rotationCenter, rotationVector) ;

        Point point = { 1.0, 0.0, 0.0 } ;

        point.applyTransformation(transformation) ;

        const Point rotatedPoint_ref = { +0.70710678118, +0.70710678118, 0.0 } ;

        EXPECT_TRUE(point.isNear(rotatedPoint_ref, 1e-11)) << String::Format("{} ~ {}", point.toString(), rotatedPoint_ref.toString()) ;

    }

    {

        const Point rotationCenter = { 0.0, 0.0, 0.0 } ;
        const Angle rotationAngle = Angle::Degrees(-45.0) ;
        const RotationVector rotationVector = { { 0.0, 0.0, 1.0 }, rotationAngle } ;

        const Transformation transformation = Transformation::RotationAround(rotationCenter, rotationVector) ;

        Point point = { 1.0, 0.0, 0.0 } ;

        point.applyTransformation(transformation) ;

        const Point rotatedPoint_ref = { +0.70710678118, -0.70710678118, 0.0 } ;

        EXPECT_TRUE(point.isNear(rotatedPoint_ref, 1e-11)) << String::Format("{} ~ {}", point.toString(), rotatedPoint_ref.toString()) ;

    }

    {

        const Point rotationCenter = { 0.0, 0.0, 0.0 } ;
        const Angle rotationAngle = Angle::Degrees(45.0) ;
        const RotationVector rotationVector = { { 0.0, 0.0, 1.0 }, rotationAngle } ;

        EXPECT_ANY_THROW(Transformation::RotationAround(Point::Undefined(), rotationVector)) ;
        EXPECT_ANY_THROW(Transformation::RotationAround(rotationCenter, RotationVector::Undefined())) ;
        EXPECT_ANY_THROW(Transformation::RotationAround(Point::Undefined(), RotationVector::Undefined())) ;

    }

}

// TEST (Library_Mathematics_Geometry_3D_Transformation, StringFromType)
// {

//     using ostk::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, TypeOfMatrix)
// {

//     using ostk::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
