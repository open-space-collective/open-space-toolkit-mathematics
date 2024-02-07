/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationMatrix.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/Angle.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, Constructor)
{
    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix;

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

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, EqualToOperator)
// {

//     using ostk::mathematics::geometry::Angle ;
//     using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix ;

//     {

//         EXPECT_TRUE(RotationMatrix({ 1.0, 0.0, 0.0 }, Angle::Degrees(0.0)) == RotationMatrix({ 1.0, 0.0, 0.0 },
//         Angle::Degrees(0.0))) ; EXPECT_TRUE(RotationMatrix({ 0.0, 1.0, 0.0 }, Angle::Degrees(10.0)) ==
//         RotationMatrix({ 0.0, 1.0, 0.0 }, Angle::Degrees(10.0))) ; EXPECT_TRUE(RotationMatrix({ 0.0, 0.0, 1.0 },
//         Angle::Degrees(20.0)) == RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(20.0))) ;

//         EXPECT_TRUE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(30.0)) == RotationMatrix({ 0.0, 0.0, +1.0 },
//         Angle::Degrees(+30.0))) ; EXPECT_TRUE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(30.0)) ==
//         RotationMatrix({ 0.0, 0.0, -1.0 }, Angle::Degrees(-30.0))) ;

//         EXPECT_TRUE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(0.0)) == RotationMatrix({ 0.0, 0.0, 1.0 },
//         Angle::Degrees(+360.0))) ; EXPECT_TRUE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(0.0)) ==
//         RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(-360.0))) ;

//         EXPECT_TRUE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(+180.0)) == RotationMatrix({ 0.0, 0.0, 1.0 },
//         Angle::Degrees(-180.0))) ;

//     }

//     {

//         EXPECT_FALSE(RotationMatrix({ 1.0, 0.0, 0.0 }, Angle::Degrees(0.0)) == RotationMatrix({ 1.0, 0.0, 0.0 },
//         Angle::Degrees(1.0))) ;

//     }

//     {

//         EXPECT_FALSE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(0.0)) == RotationMatrix::Undefined()) ;
//         EXPECT_FALSE(RotationMatrix::Undefined() == RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(0.0))) ;
//         EXPECT_FALSE(RotationMatrix::Undefined() == RotationMatrix::Undefined()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, NotEqualToOperator)
// {

//     using ostk::mathematics::geometry::Angle ;
//     using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix ;

//     {

//         EXPECT_TRUE(RotationMatrix({ 1.0, 0.0, 0.0 }, Angle::Degrees(0.0)) != RotationMatrix({ 1.0, 0.0, 0.0 },
//         Angle::Degrees(1.0))) ;

//     }

//     {

//         EXPECT_TRUE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(0.0)) != RotationMatrix::Undefined()) ;
//         EXPECT_TRUE(RotationMatrix::Undefined() != RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(0.0))) ;
//         EXPECT_TRUE(RotationMatrix::Undefined() != RotationMatrix::Undefined()) ;

//     }

//     {

//         EXPECT_FALSE(RotationMatrix({ 1.0, 0.0, 0.0 }, Angle::Degrees(0.0)) != RotationMatrix({ 1.0, 0.0, 0.0 },
//         Angle::Degrees(0.0))) ; EXPECT_FALSE(RotationMatrix({ 0.0, 1.0, 0.0 }, Angle::Degrees(10.0)) !=
//         RotationMatrix({ 0.0, 1.0, 0.0 }, Angle::Degrees(10.0))) ; EXPECT_FALSE(RotationMatrix({ 0.0, 0.0, 1.0 },
//         Angle::Degrees(20.0)) != RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(20.0))) ;

//         EXPECT_FALSE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(30.0)) != RotationMatrix({ 0.0, 0.0, +1.0 },
//         Angle::Degrees(+30.0))) ; EXPECT_FALSE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(30.0)) !=
//         RotationMatrix({ 0.0, 0.0, -1.0 }, Angle::Degrees(-30.0))) ;

//         EXPECT_FALSE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(0.0)) != RotationMatrix({ 0.0, 0.0, 1.0 },
//         Angle::Degrees(+360.0))) ; EXPECT_FALSE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(0.0)) !=
//         RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(-360.0))) ;

//         EXPECT_FALSE(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(+180.0)) != RotationMatrix({ 0.0, 0.0, 1.0 },
//         Angle::Degrees(-180.0))) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, StreamOperator)
// {

//     using ostk::mathematics::geometry::Angle ;
//     using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix ;

//     {

//         testing::internal::CaptureStdout() ;

//         EXPECT_NO_THROW(std::cout << RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(10.0)) << std::endl) ;

//         EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, IsDefined)
// {

//     using ostk::mathematics::object::Vector3d ;
//     using ostk::mathematics::geometry::Angle ;
//     using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix ;

//     {

//         EXPECT_TRUE(RotationMatrix({ 1.0, 0.0, 0.0 }, Angle::Degrees(10.0)).isDefined()) ;

//     }

//     {

//         EXPECT_FALSE(RotationMatrix::Undefined().isDefined()) ;
//         EXPECT_FALSE(RotationMatrix(Vector3d::Undefined(), Angle::Degrees(10.0)).isDefined()) ;
//         EXPECT_FALSE(RotationMatrix({ 1.0, 0.0, 0.0 }, Angle::Undefined()).isDefined()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, GetAxis)
// {

//     using ostk::mathematics::object::Vector3d ;
//     using ostk::mathematics::geometry::Angle ;
//     using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix ;

//     {

//         EXPECT_EQ(Vector3d(1.0, 0.0, 0.0), RotationMatrix({ 1.0, 0.0, 0.0 }, Angle::Degrees(10.0)).getAxis()) ;
//         EXPECT_EQ(Vector3d(0.0, 1.0, 0.0), RotationMatrix({ 0.0, 1.0, 0.0 }, Angle::Degrees(20.0)).getAxis()) ;
//         EXPECT_EQ(Vector3d(0.0, 0.0, 1.0), RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(30.0)).getAxis()) ;

//     }

//     {

//         EXPECT_ANY_THROW(RotationMatrix::Undefined().getAxis()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, GetAngle)
// {

//     using ostk::mathematics::geometry::Angle ;
//     using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix ;

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

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, Undefined)
// {

//     using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix ;

//     {

//         EXPECT_NO_THROW(RotationMatrix::Undefined()) ;
//         EXPECT_FALSE(RotationMatrix::Undefined().isDefined()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, Unit)
// {

//     using ostk::mathematics::geometry::Angle ;
//     using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix ;

//     {

//         EXPECT_NO_THROW(RotationMatrix::Unit()) ;
//         EXPECT_EQ(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Zero()), RotationMatrix::Unit()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, RX)
// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, RY)
// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, RZ)

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_RotationMatrix, Quaternion)
// {

//     using ostk::core::type::Real ;
//     using ostk::mathematics::geometry::Angle ;
//     using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion ;
//     using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix ;

//     {

//         EXPECT_EQ(RotationMatrix::Unit(), RotationMatrix::Quaternion(Quaternion::Unit())) ;

//         EXPECT_EQ(RotationMatrix({ 0.0, 0.0, 1.0 }, Angle::Degrees(180.0)),
//         RotationMatrix::Quaternion(Quaternion::XYZS(0.0, 0.0, 1.0, 0.0))) ;

//     }

//     {

//         EXPECT_ANY_THROW(RotationMatrix::Quaternion(Quaternion::Undefined())) ;

//     }

// }
