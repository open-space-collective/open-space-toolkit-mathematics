////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>
#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp>
#include <Library/Mathematics/Geometry/Angle.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Mathematics_Geometry_3D_Transformations_Rotations_RotationMatrix, Constructor)
{

    using library::math::geom::Angle ;
    using library::math::geom::d3::trf::rot::RotationMatrix ;

    // {

    //     EXPECT_NO_THROW(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(45.0))) ;

    //     RotationMatrix rotationMatrix = { { 0.0, 0.0, 1.0 }, Angle::Degrees(45.0) } ;

    //     EXPECT_TRUE(rotationMatrix.isDefined()) ;

    // }

    // {



    // }

    // {

    //     EXPECT_ANY_THROW(RotationMatrix({ 0.0, 0.0, 0.9 }, Angle::Degrees(45.0))) ;
    //     EXPECT_ANY_THROW(RotationMatrix({ 0.0, 0.0, 1.1 }, Angle::Degrees(45.0))) ;

    // }

}

// TEST (Library_Mathematics_Geometry_3D_Transformations_Rotations_RotationMatrix, EqualToOperator)
// {

//     using library::math::geom::Angle ;
//     using library::math::geom::d3::trf::rot::RotationMatrix ;

//     {

//         EXPECT_TRUE(RotationMatrix({ 1.0, 0.0, 0.0 }, Angle::Degrees(0.0)) == RotationMatrix({ 1.0, 0.0, 0.0 }, Angle::Degrees(0.0))) ;
//         EXPECT_TRUE(RotationMatrix({ 0.0, 1.0, 0.0 }, Angle::Degrees(10.0)) == RotationMatrix({ 0.0, 1.0, 0.0 }, Angle::Degrees(10.0))) ;
//         EXPECT_TRUE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(20.0)) == RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(20.0))) ;

//         EXPECT_TRUE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(30.0)) == RotationMatrix({ 0.0, 0.0, +1.0 }, Angle::Degrees(+30.0))) ;
//         EXPECT_TRUE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(30.0)) == RotationMatrix({ 0.0, 0.0, -1.0 }, Angle::Degrees(-30.0))) ;

//         EXPECT_TRUE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(0.0)) == RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(+360.0))) ;
//         EXPECT_TRUE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(0.0)) == RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(-360.0))) ;

//         EXPECT_TRUE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(+180.0)) == RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(-180.0))) ;

//     }

//     {

//         EXPECT_FALSE(RotationMatrix({ 1.0, 0.0, 0.0 }, Angle::Degrees(0.0)) == RotationMatrix({ 1.0, 0.0, 0.0 }, Angle::Degrees(1.0))) ;

//     }

//     {

//         EXPECT_FALSE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(0.0)) == RotationMatrix::Undefined()) ;
//         EXPECT_FALSE(RotationMatrix::Undefined() == RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(0.0))) ;
//         EXPECT_FALSE(RotationMatrix::Undefined() == RotationMatrix::Undefined()) ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformations_Rotations_RotationMatrix, NotEqualToOperator)
// {

//     using library::math::geom::Angle ;
//     using library::math::geom::d3::trf::rot::RotationMatrix ;

//     {

//         EXPECT_TRUE(RotationMatrix({ 1.0, 0.0, 0.0 }, Angle::Degrees(0.0)) != RotationMatrix({ 1.0, 0.0, 0.0 }, Angle::Degrees(1.0))) ;

//     }

//     {

//         EXPECT_TRUE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(0.0)) != RotationMatrix::Undefined()) ;
//         EXPECT_TRUE(RotationMatrix::Undefined() != RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(0.0))) ;
//         EXPECT_TRUE(RotationMatrix::Undefined() != RotationMatrix::Undefined()) ;

//     }

//     {

//         EXPECT_FALSE(RotationMatrix({ 1.0, 0.0, 0.0 }, Angle::Degrees(0.0)) != RotationMatrix({ 1.0, 0.0, 0.0 }, Angle::Degrees(0.0))) ;
//         EXPECT_FALSE(RotationMatrix({ 0.0, 1.0, 0.0 }, Angle::Degrees(10.0)) != RotationMatrix({ 0.0, 1.0, 0.0 }, Angle::Degrees(10.0))) ;
//         EXPECT_FALSE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(20.0)) != RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(20.0))) ;

//         EXPECT_FALSE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(30.0)) != RotationMatrix({ 0.0, 0.0, +1.0 }, Angle::Degrees(+30.0))) ;
//         EXPECT_FALSE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(30.0)) != RotationMatrix({ 0.0, 0.0, -1.0 }, Angle::Degrees(-30.0))) ;

//         EXPECT_FALSE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(0.0)) != RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(+360.0))) ;
//         EXPECT_FALSE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(0.0)) != RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(-360.0))) ;

//         EXPECT_FALSE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(+180.0)) != RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(-180.0))) ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformations_Rotations_RotationMatrix, StreamOperator)
// {

//     using library::math::geom::Angle ;
//     using library::math::geom::d3::trf::rot::RotationMatrix ;

//     {

//         testing::internal::CaptureStdout() ;

//         EXPECT_NO_THROW(std::cout << RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(10.0)) << std::endl) ;

//         EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformations_Rotations_RotationMatrix, IsDefined)
// {

//     using library::math::obj::Vector3d ;
//     using library::math::geom::Angle ;
//     using library::math::geom::d3::trf::rot::RotationMatrix ;

//     {

//         EXPECT_TRUE(RotationMatrix({ 1.0, 0.0, 0.0 }, Angle::Degrees(10.0)).isDefined()) ;

//     }

//     {

//         EXPECT_FALSE(RotationMatrix::Undefined().isDefined()) ;
//         EXPECT_FALSE(RotationMatrix(Vector3d::Undefined(), Angle::Degrees(10.0)).isDefined()) ;
//         EXPECT_FALSE(RotationMatrix({ 1.0, 0.0, 0.0 }, Angle::Undefined()).isDefined()) ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformations_Rotations_RotationMatrix, GetAxis)
// {

//     using library::math::obj::Vector3d ;
//     using library::math::geom::Angle ;
//     using library::math::geom::d3::trf::rot::RotationMatrix ;

//     {

//         EXPECT_EQ(Vector3d(1.0, 0.0, 0.0), RotationMatrix({ 1.0, 0.0, 0.0 }, Angle::Degrees(10.0)).getAxis()) ;
//         EXPECT_EQ(Vector3d(0.0, 1.0, 0.0), RotationMatrix({ 0.0, 1.0, 0.0 }, Angle::Degrees(20.0)).getAxis()) ;
//         EXPECT_EQ(Vector3d(0.0, 0.0, 1.0), RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(30.0)).getAxis()) ;

//     }

//     {

//         EXPECT_ANY_THROW(RotationMatrix::Undefined().getAxis()) ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformations_Rotations_RotationMatrix, GetAngle)
// {

//     using library::math::geom::Angle ;
//     using library::math::geom::d3::trf::rot::RotationMatrix ;

//     {

//         EXPECT_EQ(Angle::Degrees(0.0), RotationMatrix({ 1.0, 0.0, 0.0 }, Angle::Degrees(0.0)).getAngle()) ;

//         EXPECT_EQ(Angle::Degrees(-30.0), RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(-30.0)).getAngle()) ;
//         EXPECT_EQ(Angle::Degrees(+30.0), RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(+30.0)).getAngle()) ;

//         EXPECT_EQ(Angle::Degrees(-90.0), RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0)).getAngle()) ;
//         EXPECT_EQ(Angle::Degrees(+90.0), RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(+90.0)).getAngle()) ;

//         EXPECT_EQ(Angle::Degrees(-180.0), RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(-180.0)).getAngle()) ;
//         EXPECT_EQ(Angle::Degrees(+180.0), RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(+180.0)).getAngle()) ;

//     }

//     {

//         EXPECT_ANY_THROW(RotationMatrix::Undefined().getAngle()) ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformations_Rotations_RotationMatrix, Undefined)
// {

//     using library::math::geom::d3::trf::rot::RotationMatrix ;

//     {

//         EXPECT_NO_THROW(RotationMatrix::Undefined()) ;
//         EXPECT_FALSE(RotationMatrix::Undefined().isDefined()) ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformations_Rotations_RotationMatrix, Unit)
// {

//     using library::math::geom::Angle ;
//     using library::math::geom::d3::trf::rot::RotationMatrix ;

//     {

//         EXPECT_NO_THROW(RotationMatrix::Unit()) ;
//         EXPECT_EQ(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Zero()), RotationMatrix::Unit()) ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Transformations_Rotations_RotationMatrix, RX)
// TEST (Library_Mathematics_Geometry_3D_Transformations_Rotations_RotationMatrix, RY)
// TEST (Library_Mathematics_Geometry_3D_Transformations_Rotations_RotationMatrix, RZ)

// TEST (Library_Mathematics_Geometry_3D_Transformations_Rotations_RotationMatrix, Quaternion)
// {

//     using library::core::types::Real ;
//     using library::math::geom::Angle ;
//     using library::math::geom::d3::trf::rot::Quaternion ;
//     using library::math::geom::d3::trf::rot::RotationMatrix ;

//     {

//         EXPECT_EQ(RotationMatrix::Unit(), RotationMatrix::Quaternion(Quaternion::Unit())) ;

//         EXPECT_EQ(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(180.0)), RotationMatrix::Quaternion(Quaternion::XYZS(0.0, 0.0, 1.0, 0.0))) ;

//     }

//     {

//         EXPECT_ANY_THROW(RotationMatrix::Quaternion(Quaternion::Undefined())) ;

//     }

// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
