////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/2D/Transformation.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/2D/Transformation.hpp>
#include <Library/Mathematics/Geometry/2D/Objects/Segment.hpp>
#include <Library/Mathematics/Geometry/2D/Objects/Point.hpp>
#include <Library/Mathematics/Geometry/Angle.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TEST (Library_Mathematics_Geometry_2D_Transformation, Constructor)
// {

//     using library::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_2D_Transformation, EqualToOperator)
// {

//     using library::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_2D_Transformation, NotEqualToOperator)
// {

//     using library::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_2D_Transformation, MultiplicationOperator)
// {

//     using library::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_2D_Transformation, MultiplicationAssignmentOperator)
// {

//     using library::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_2D_Transformation, StreamOperator)
// {

//     using library::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_2D_Transformation, IsDefined)
// {
    
//     using library::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_2D_Transformation, GetType)
// {
    
//     using library::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_2D_Transformation, GetMatrix)
// {
    
//     using library::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_2D_Transformation, GetInverse)
// {
    
//     using library::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_2D_Transformation, ApplyTo)
// {
    
//     using library::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_2D_Transformation, Undefined)
// {
    
//     using library::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_2D_Transformation, Identity)
// {
    
//     using library::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_2D_Transformation, Translation)
// {
    
//     using library::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_2D_Transformation, Rotation)
// {
    
//     using library::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

TEST (Library_Mathematics_Geometry_2D_Transformation, RotationAround)
{

    using library::core::types::String ;
    
    using library::math::geom::Angle ;
    using library::math::geom::d2::objects::Point ;
    using library::math::geom::d2::Transformation ;

    {

        const Point rotationCenter = { 0.0, 0.0 } ;
        const Angle rotationAngle = Angle::Degrees(45.0) ;

        const Transformation transformation = Transformation::RotationAround(rotationCenter, rotationAngle) ;

        Point point = { 0.0, 0.0 } ;

        point.applyTransformation(transformation) ;
        
        const Point rotatedPoint_ref = { 0.0, 0.0 } ;

        EXPECT_TRUE(point.isNear(rotatedPoint_ref, 1e-11)) << String::Format("{} ~ {}", point.toString(), rotatedPoint_ref.toString()) ;

    }

    {

        const Point rotationCenter = { 1.0, 0.0 } ;
        const Angle rotationAngle = Angle::Degrees(45.0) ;

        const Transformation transformation = Transformation::RotationAround(rotationCenter, rotationAngle) ;

        Point point = { 1.0, 0.0 } ;

        point.applyTransformation(transformation) ;
        
        const Point rotatedPoint_ref = { 1.0, 0.0 } ;

        EXPECT_TRUE(point.isNear(rotatedPoint_ref, 1e-11)) << String::Format("{} ~ {}", point.toString(), rotatedPoint_ref.toString()) ;

    }

    {

        const Point rotationCenter = { 0.0, 0.0 } ;
        const Angle rotationAngle = Angle::Degrees(45.0) ;

        const Transformation transformation = Transformation::RotationAround(rotationCenter, rotationAngle) ;

        Point point = { 1.0, 0.0 } ;

        point.applyTransformation(transformation) ;
        
        const Point rotatedPoint_ref = { +0.70710678118, +0.70710678118 } ;

        EXPECT_TRUE(point.isNear(rotatedPoint_ref, 1e-11)) << String::Format("{} ~ {}", point.toString(), rotatedPoint_ref.toString()) ;

    }

    {

        const Point rotationCenter = { 0.0, 0.0 } ;
        const Angle rotationAngle = Angle::Degrees(-45.0) ;

        const Transformation transformation = Transformation::RotationAround(rotationCenter, rotationAngle) ;

        Point point = { 1.0, 0.0 } ;

        point.applyTransformation(transformation) ;
        
        const Point rotatedPoint_ref = { +0.70710678118, -0.70710678118 } ;

        EXPECT_TRUE(point.isNear(rotatedPoint_ref, 1e-11)) << String::Format("{} ~ {}", point.toString(), rotatedPoint_ref.toString()) ;

    }

    {

        const Point rotationCenter = { 0.0, 0.0 } ;
        const Angle rotationAngle = Angle::Degrees(45.0) ;

        EXPECT_ANY_THROW(Transformation::RotationAround(Point::Undefined(), rotationAngle)) ;
        EXPECT_ANY_THROW(Transformation::RotationAround(rotationCenter, Angle::Undefined())) ;
        EXPECT_ANY_THROW(Transformation::RotationAround(Point::Undefined(), Angle::Undefined())) ;

    }

}

// TEST (Library_Mathematics_Geometry_2D_Transformation, StringFromType)
// {
    
//     using library::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_2D_Transformation, TypeOfMatrix)
// {
    
//     using library::math::geom::d2::Transformation ;

//     {

//         FAIL() ;

//     }

// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////