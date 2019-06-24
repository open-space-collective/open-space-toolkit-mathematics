////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Mathematics
/// @file           Library/Mathematics/Geometry/3D/Transformation.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/3D/Transformation.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Point.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TEST (Library_Mathematics_Geometry_3D_Transformation, Constructor)
// {

//     using library::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, EqualToOperator)
// {

//     using library::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, NotEqualToOperator)
// {

//     using library::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, MultiplicationOperator)
// {

//     using library::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, MultiplicationAssignmentOperator)
// {

//     using library::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, StreamOperator)
// {

//     using library::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, IsDefined)
// {

//     using library::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, IsRigid)
// {

//     using library::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, GetType)
// {

//     using library::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, GetMatrix)
// {

//     using library::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, GetInverse)
// {

//     using library::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, ApplyTo)
// {

//     using library::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, Undefined)
// {

//     using library::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, Identity)
// {

//     using library::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, Translation)
// {

//     using library::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, Rotation)
// {

//     using library::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

TEST (Library_Mathematics_Geometry_3D_Transformation, RotationAround)
{

    using library::core::types::String ;

    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::Transformation ;
    using library::math::geom::d3::trf::rot::RotationVector ;

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

//     using library::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformation, TypeOfMatrix)
// {

//     using library::math::geom::d3::Transformation ;

//     {

//         FAIL() ;

//     }

// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
