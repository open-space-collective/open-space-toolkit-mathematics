////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/Transformations/Rotations/RotationVector.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/Transformations/Rotations/Quaternion.hpp>
#include <Library/Mathematics/Geometry/Angle.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Mathematics_Geometry_Transformations_Rotations_RotationVector, Constructor)
{

    using library::math::geom::Angle ;
    using library::math::geom::trf::rot::RotationVector ;

    {

        EXPECT_NO_THROW(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(45.0))) ;

        RotationVector rotationVector = { { 0.0, 0.0, 1.0 }, Angle::Degrees(45.0) } ;

        EXPECT_TRUE(rotationVector.isDefined()) ;

    }

    {

        EXPECT_ANY_THROW(RotationVector({ 0.0, 0.0, 0.9 }, Angle::Degrees(45.0))) ;
        EXPECT_ANY_THROW(RotationVector({ 0.0, 0.0, 1.1 }, Angle::Degrees(45.0))) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_RotationVector, EqualToOperator)
{

    using library::math::geom::Angle ;
    using library::math::geom::trf::rot::RotationVector ;
    
    {

        EXPECT_TRUE(RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(0.0)) == RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(0.0))) ;
        EXPECT_TRUE(RotationVector({ 0.0, 1.0, 0.0 }, Angle::Degrees(10.0)) == RotationVector({ 0.0, 1.0, 0.0 }, Angle::Degrees(10.0))) ;
        EXPECT_TRUE(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(20.0)) == RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(20.0))) ;
        
        EXPECT_TRUE(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(30.0)) == RotationVector({ 0.0, 0.0, +1.0 }, Angle::Degrees(+30.0))) ;
        EXPECT_TRUE(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(30.0)) == RotationVector({ 0.0, 0.0, -1.0 }, Angle::Degrees(-30.0))) ;

        EXPECT_TRUE(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(0.0)) == RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(+360.0))) ;
        EXPECT_TRUE(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(0.0)) == RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-360.0))) ;

        EXPECT_TRUE(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(+180.0)) == RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-180.0))) ;

    }

    {

        EXPECT_FALSE(RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(0.0)) == RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(1.0))) ;

    }

    {

        EXPECT_FALSE(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(0.0)) == RotationVector::Undefined()) ;
        EXPECT_FALSE(RotationVector::Undefined() == RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(0.0))) ;
        EXPECT_FALSE(RotationVector::Undefined() == RotationVector::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_RotationVector, NotEqualToOperator)
{

    using library::math::geom::Angle ;
    using library::math::geom::trf::rot::RotationVector ;

    {

        EXPECT_TRUE(RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(0.0)) != RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(1.0))) ;

    }

    {

        EXPECT_TRUE(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(0.0)) != RotationVector::Undefined()) ;
        EXPECT_TRUE(RotationVector::Undefined() != RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(0.0))) ;
        EXPECT_TRUE(RotationVector::Undefined() != RotationVector::Undefined()) ;

    }
    
    {

        EXPECT_FALSE(RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(0.0)) != RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(0.0))) ;
        EXPECT_FALSE(RotationVector({ 0.0, 1.0, 0.0 }, Angle::Degrees(10.0)) != RotationVector({ 0.0, 1.0, 0.0 }, Angle::Degrees(10.0))) ;
        EXPECT_FALSE(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(20.0)) != RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(20.0))) ;
        
        EXPECT_FALSE(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(30.0)) != RotationVector({ 0.0, 0.0, +1.0 }, Angle::Degrees(+30.0))) ;
        EXPECT_FALSE(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(30.0)) != RotationVector({ 0.0, 0.0, -1.0 }, Angle::Degrees(-30.0))) ;

        EXPECT_FALSE(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(0.0)) != RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(+360.0))) ;
        EXPECT_FALSE(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(0.0)) != RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-360.0))) ;

        EXPECT_FALSE(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(+180.0)) != RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-180.0))) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_RotationVector, StreamOperator)
{

    using library::math::geom::Angle ;
    using library::math::geom::trf::rot::RotationVector ;
    
    {

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(10.0)) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_RotationVector, IsDefined)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::Angle ;
    using library::math::geom::trf::rot::RotationVector ;
    
    {

        EXPECT_TRUE(RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(10.0)).isDefined()) ;

    }

    {

        EXPECT_FALSE(RotationVector::Undefined().isDefined()) ;
        EXPECT_FALSE(RotationVector(Vector3d::Undefined(), Angle::Degrees(10.0)).isDefined()) ;
        EXPECT_FALSE(RotationVector({ 1.0, 0.0, 0.0 }, Angle::Undefined()).isDefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_RotationVector, GetAxis)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::Angle ;
    using library::math::geom::trf::rot::RotationVector ;

    {

        EXPECT_EQ(Vector3d(1.0, 0.0, 0.0), RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(10.0)).getAxis()) ;
        EXPECT_EQ(Vector3d(0.0, 1.0, 0.0), RotationVector({ 0.0, 1.0, 0.0 }, Angle::Degrees(20.0)).getAxis()) ;
        EXPECT_EQ(Vector3d(0.0, 0.0, 1.0), RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(30.0)).getAxis()) ;

    }

    {

        EXPECT_ANY_THROW(RotationVector::Undefined().getAxis()) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_RotationVector, GetAngle)
{

    using library::math::geom::Angle ;
    using library::math::geom::trf::rot::RotationVector ;

    {

        EXPECT_EQ(Angle::Degrees(0.0), RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(0.0)).getAngle()) ;

        EXPECT_EQ(Angle::Degrees(-30.0), RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-30.0)).getAngle()) ;
        EXPECT_EQ(Angle::Degrees(+30.0), RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(+30.0)).getAngle()) ;
        
        EXPECT_EQ(Angle::Degrees(-90.0), RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0)).getAngle()) ;
        EXPECT_EQ(Angle::Degrees(+90.0), RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(+90.0)).getAngle()) ;

        EXPECT_EQ(Angle::Degrees(-180.0), RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-180.0)).getAngle()) ;
        EXPECT_EQ(Angle::Degrees(+180.0), RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(+180.0)).getAngle()) ;

    }

    {

        EXPECT_ANY_THROW(RotationVector::Undefined().getAngle()) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_RotationVector, Undefined)
{

    using library::math::geom::trf::rot::RotationVector ;
    
    {

        EXPECT_NO_THROW(RotationVector::Undefined()) ;
        EXPECT_FALSE(RotationVector::Undefined().isDefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_RotationVector, Unit)
{

    using library::math::geom::Angle ;
    using library::math::geom::trf::rot::RotationVector ;
    
    {

        EXPECT_NO_THROW(RotationVector::Unit()) ;
        EXPECT_EQ(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Zero()), RotationVector::Unit()) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_RotationVector, Quaternion)
{

    using library::core::types::Real ;
    using library::math::geom::Angle ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    
    {

        EXPECT_EQ(RotationVector::Unit(), RotationVector::Quaternion(Quaternion::Unit())) ;

        EXPECT_EQ(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(180.0)), RotationVector::Quaternion(Quaternion::XYZS(0.0, 0.0, 1.0, 0.0))) ;

    }

    {

        EXPECT_ANY_THROW(RotationVector::Quaternion(Quaternion::Undefined())) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////