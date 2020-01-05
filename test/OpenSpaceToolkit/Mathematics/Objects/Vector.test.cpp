////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/Objects/Vector.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Mathematics_Objects_Vector2i, Constructor)
{

    using ostk::math::obj::Vector2i ;

    {

        const Vector2i vector(1, 2) ;

        EXPECT_EQ(1, vector(0)) ;
        EXPECT_EQ(2, vector(1)) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Objects_Vector2i, ToString)
{

    using ostk::math::obj::Vector2i ;

    {

        const Vector2i vector(1, 2) ;

        EXPECT_EQ("[1, 2]", vector.toString()) ;

        EXPECT_EQ("[1, 2]", vector.toString(0)) ;
        EXPECT_EQ("[1, 2]", vector.toString(1)) ;
        EXPECT_EQ("[1, 2]", vector.toString(2)) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Mathematics_Objects_Vector3i, Constructor)
{

    using ostk::math::obj::Vector3i ;

    {

        const Vector3i vector(1, 2, 3) ;

        EXPECT_EQ(1, vector(0)) ;
        EXPECT_EQ(2, vector(1)) ;
        EXPECT_EQ(3, vector(2)) ;

    }

    {

        const Vector3i vector = Vector3i::X() ;

        EXPECT_EQ(1, vector(0)) ;
        EXPECT_EQ(0, vector(1)) ;
        EXPECT_EQ(0, vector(2)) ;

    }

    {

        const Vector3i vector = Vector3i::Y() ;

        EXPECT_EQ(0, vector(0)) ;
        EXPECT_EQ(1, vector(1)) ;
        EXPECT_EQ(0, vector(2)) ;

    }

    {

        const Vector3i vector = Vector3i::Z() ;

        EXPECT_EQ(0, vector(0)) ;
        EXPECT_EQ(0, vector(1)) ;
        EXPECT_EQ(1, vector(2)) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Objects_Vector3i, ToString)
{

    using ostk::math::obj::Vector3i ;

    {

        const Vector3i vector(1, 2, 3) ;

        EXPECT_EQ("[1, 2, 3]", vector.toString()) ;

        EXPECT_EQ("[1, 2, 3]", vector.toString(0)) ;
        EXPECT_EQ("[1, 2, 3]", vector.toString(1)) ;
        EXPECT_EQ("[1, 2, 3]", vector.toString(2)) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Mathematics_Objects_Vector2d, Constructor)
{

    using ostk::math::obj::Vector2d ;

    {

        const Vector2d vector(1.0, 2.0) ;

        EXPECT_EQ(1.0, vector(0)) ;
        EXPECT_EQ(2.0, vector(1)) ;

    }

    {

        const Vector2d vector = Vector2d::Undefined() ;

        EXPECT_FALSE(vector.isDefined()) ;
        EXPECT_TRUE(vector.isNaN()) ;
        EXPECT_FALSE(vector.isInf()) ;

    }

    {

        const Vector2d vector = Vector2d::NaN() ;

        EXPECT_FALSE(vector.isDefined()) ;
        EXPECT_TRUE(vector.isNaN()) ;
        EXPECT_FALSE(vector.isInf()) ;

    }

    {

        const Vector2d vector = Vector2d::Inf() ;

        EXPECT_FALSE(vector.isDefined()) ;
        EXPECT_FALSE(vector.isNaN()) ;
        EXPECT_TRUE(vector.isInf()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Objects_Vector2d, ToString)
{

    using ostk::math::obj::Vector2d ;

    {

        const Vector2d vector(1.0, 2.0) ;

        EXPECT_EQ("[1.0, 2.0]", vector.toString()) ;

        EXPECT_EQ("[1, 2]", vector.toString(0)) ;
        EXPECT_EQ("[1.0, 2.0]", vector.toString(1)) ;
        EXPECT_EQ("[1.00, 2.00]", vector.toString(2)) ;

    }

    {

        const Vector2d vector(1.0, 2.01) ;

        EXPECT_EQ("[1.0, 2.01]", vector.toString()) ;

        EXPECT_EQ("[1, 2]", vector.toString(0)) ;
        EXPECT_EQ("[1.0, 2.0]", vector.toString(1)) ;
        EXPECT_EQ("[1.00, 2.01]", vector.toString(2)) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Mathematics_Objects_Vector3d, Constructor)
{

    using ostk::math::obj::Vector3d ;

    {

        const Vector3d vector(1.0, 2.0, 3.0) ;

        EXPECT_EQ(1.0, vector(0)) ;
        EXPECT_EQ(2.0, vector(1)) ;
        EXPECT_EQ(3.0, vector(2)) ;

    }

    {

        const Vector3d vector = Vector3d::X() ;

        EXPECT_EQ(1.0, vector(0)) ;
        EXPECT_EQ(0.0, vector(1)) ;
        EXPECT_EQ(0.0, vector(2)) ;

    }

    {

        const Vector3d vector = Vector3d::Y() ;

        EXPECT_EQ(0.0, vector(0)) ;
        EXPECT_EQ(1.0, vector(1)) ;
        EXPECT_EQ(0.0, vector(2)) ;

    }

    {

        const Vector3d vector = Vector3d::Z() ;

        EXPECT_EQ(0.0, vector(0)) ;
        EXPECT_EQ(0.0, vector(1)) ;
        EXPECT_EQ(1.0, vector(2)) ;

    }

    {

        const Vector3d vector = Vector3d::Undefined() ;

        EXPECT_FALSE(vector.isDefined()) ;
        EXPECT_TRUE(vector.isNaN()) ;
        EXPECT_FALSE(vector.isInf()) ;

    }

    {

        const Vector3d vector = Vector3d::NaN() ;

        EXPECT_FALSE(vector.isDefined()) ;
        EXPECT_TRUE(vector.isNaN()) ;
        EXPECT_FALSE(vector.isInf()) ;

    }

    {

        const Vector3d vector = Vector3d::Inf() ;

        EXPECT_FALSE(vector.isDefined()) ;
        EXPECT_FALSE(vector.isNaN()) ;
        EXPECT_TRUE(vector.isInf()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Objects_Vector3d, ToString)
{

    using ostk::math::obj::Vector3d ;

    {

        const Vector3d vector(1.0, 2.0, 3.0) ;

        EXPECT_EQ("[1, 2, 3]", vector.toString(0)) ;
        EXPECT_EQ("[1.0, 2.0, 3.0]", vector.toString(1)) ;
        EXPECT_EQ("[1.00, 2.00, 3.00]", vector.toString(2)) ;

        EXPECT_EQ("[1.0, 2.0, 3.0]", vector.toString()) ;

    }

    {

        const Vector3d vector(1.0, 2.01, 3.001) ;

        EXPECT_EQ("[1.0, 2.01, 3.001]", vector.toString()) ;

        EXPECT_EQ("[1, 2, 3]", vector.toString(0)) ;
        EXPECT_EQ("[1.0, 2.0, 3.0]", vector.toString(1)) ;
        EXPECT_EQ("[1.00, 2.01, 3.00]", vector.toString(2)) ;
        EXPECT_EQ("[1.000, 2.010, 3.001]", vector.toString(3)) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Mathematics_Objects_Vector4d, Constructor)
{

    using ostk::math::obj::Vector4d ;

    {

        const Vector4d vector(1.0, 2.0, 3.0, 4.0) ;

        EXPECT_EQ(1.0, vector(0)) ;
        EXPECT_EQ(2.0, vector(1)) ;
        EXPECT_EQ(3.0, vector(2)) ;
        EXPECT_EQ(4.0, vector(3)) ;

    }

    {

        const Vector4d vector = Vector4d::Undefined() ;

        EXPECT_FALSE(vector.isDefined()) ;
        EXPECT_TRUE(vector.isNaN()) ;
        EXPECT_FALSE(vector.isInf()) ;

    }

    {

        const Vector4d vector = Vector4d::NaN() ;

        EXPECT_FALSE(vector.isDefined()) ;
        EXPECT_TRUE(vector.isNaN()) ;
        EXPECT_FALSE(vector.isInf()) ;

    }

    {

        const Vector4d vector = Vector4d::Inf() ;

        EXPECT_FALSE(vector.isDefined()) ;
        EXPECT_FALSE(vector.isNaN()) ;
        EXPECT_TRUE(vector.isInf()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Objects_Vector4d, IsNear)
{

    using ostk::math::obj::Vector4d ;

    {

        const Vector4d vector(1.0, 2.0, 3.0, 4.0) ;

        EXPECT_TRUE(vector.isNear(vector, 0.0)) ;

    }

    {

        const Vector4d firstVector(1.0, 2.0, 3.0, 4.0) ;
        const Vector4d secondVector(2.0, 2.0, 3.0, 4.0) ;

        EXPECT_TRUE(firstVector.isNear(secondVector, 1.0)) ;
        EXPECT_FALSE(firstVector.isNear(secondVector, 0.0)) ;

    }

    {

        EXPECT_ANY_THROW(Vector4d::NaN().isNear(Vector4d::NaN(), 0.0)) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Objects_Vector4d, ToString)
{

    using ostk::math::obj::Vector4d ;

    {

        const Vector4d vector(1.0, 2.0, 3.0, 4.0) ;

        EXPECT_EQ("[1, 2, 3, 4]", vector.toString(0)) ;
        EXPECT_EQ("[1.0, 2.0, 3.0, 4.0]", vector.toString(1)) ;
        EXPECT_EQ("[1.00, 2.00, 3.00, 4.00]", vector.toString(2)) ;

        EXPECT_EQ("[1.0, 2.0, 3.0, 4.0]", vector.toString()) ;

    }

    {

        const Vector4d vector(1.0, 2.01, 3.001, 4.0001) ;

        EXPECT_EQ("[1.0, 2.01, 3.001, 4.0001]", vector.toString()) ;

        EXPECT_EQ("[1, 2, 3, 4]", vector.toString(0)) ;
        EXPECT_EQ("[1.0, 2.0, 3.0, 4.0]", vector.toString(1)) ;
        EXPECT_EQ("[1.00, 2.01, 3.00, 4.00]", vector.toString(2)) ;
        EXPECT_EQ("[1.000, 2.010, 3.001, 4.000]", vector.toString(3)) ;
        EXPECT_EQ("[1.0000, 2.0100, 3.0010, 4.0001]", vector.toString(4)) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Objects_Vector4d, Parse)
{

    using ostk::math::obj::Vector4d ;

    {

        const Vector4d vector = Vector4d::Parse("[1.000000, 2.000000, 3.000000, 4.000000]") ;

        EXPECT_EQ(4, vector.size()) ;

        EXPECT_EQ(1.0, vector(0)) ;
        EXPECT_EQ(2.0, vector(1)) ;
        EXPECT_EQ(3.0, vector(2)) ;
        EXPECT_EQ(4.0, vector(3)) ;

    }

    {

        EXPECT_ANY_THROW(Vector4d::Parse("")) ;
        EXPECT_ANY_THROW(Vector4d::Parse("[]")) ;
        EXPECT_ANY_THROW(Vector4d::Parse("1.000000, 2.000000, 3.000000, 4.000000, 5.000000")) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Mathematics_Objects_VectorXd, Constructor)
{

    using ostk::math::obj::VectorXd ;

    {

        VectorXd vector(5) ;

        vector(0) = 1.0 ;
        vector(1) = 2.0 ;
        vector(2) = 3.0 ;
        vector(3) = 4.0 ;
        vector(4) = 5.0 ;

        EXPECT_EQ(1.0, vector(0)) ;
        EXPECT_EQ(2.0, vector(1)) ;
        EXPECT_EQ(3.0, vector(2)) ;
        EXPECT_EQ(4.0, vector(3)) ;
        EXPECT_EQ(5.0, vector(4)) ;

    }

    {

        const VectorXd vector = VectorXd::Undefined(5) ;

        EXPECT_FALSE(vector.isDefined()) ;
        EXPECT_TRUE(vector.isNaN()) ;
        EXPECT_FALSE(vector.isInf()) ;

    }

    {

        const VectorXd vector = VectorXd::NaN(5) ;

        EXPECT_FALSE(vector.isDefined()) ;
        EXPECT_TRUE(vector.isNaN()) ;
        EXPECT_FALSE(vector.isInf()) ;

    }

    {

        const VectorXd vector = VectorXd::Inf(5) ;

        EXPECT_FALSE(vector.isDefined()) ;
        EXPECT_FALSE(vector.isNaN()) ;
        EXPECT_TRUE(vector.isInf()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Objects_VectorXd, IsNear)
{

    using ostk::math::obj::VectorXd ;

    {

        VectorXd vector(5) ;

        vector(0) = 1.0 ;
        vector(1) = 2.0 ;
        vector(2) = 3.0 ;
        vector(3) = 4.0 ;
        vector(4) = 5.0 ;

        EXPECT_TRUE(vector.isNear(vector, 0.0)) ;

    }

    {

        VectorXd firstVector(2) ;

        firstVector(0) = 1.0 ;
        firstVector(1) = 2.0 ;

        VectorXd secondVector(2) ;

        secondVector(0) = 1.1 ;
        secondVector(1) = 2.0 ;

        EXPECT_TRUE(firstVector.isNear(secondVector, 1.0)) ;
        EXPECT_FALSE(firstVector.isNear(secondVector, 0.0)) ;

    }

    {

        EXPECT_ANY_THROW(VectorXd::NaN(3).isNear(VectorXd::NaN(3), 0.0)) ;

    }

    {

        VectorXd firstVector(2) ;

        firstVector(0) = 1.0 ;
        firstVector(1) = 2.0 ;

        VectorXd secondVector(3) ;

        secondVector(0) = 1.1 ;
        secondVector(1) = 2.0 ;
        secondVector(2) = 3.0 ;

        EXPECT_ANY_THROW(firstVector.isNear(secondVector, 1.0)) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Objects_VectorXd, ToString)
{

    using ostk::math::obj::VectorXd ;

    {

        VectorXd vector(5) ;

        vector(0) = 1.0 ;
        vector(1) = 2.0 ;
        vector(2) = 3.0 ;
        vector(3) = 4.0 ;
        vector(4) = 5.0 ;

        EXPECT_EQ("[1, 2, 3, 4, 5]", vector.toString(0)) ;
        EXPECT_EQ("[1.0, 2.0, 3.0, 4.0, 5.0]", vector.toString(1)) ;
        EXPECT_EQ("[1.00, 2.00, 3.00, 4.00, 5.00]", vector.toString(2)) ;

        EXPECT_EQ("[1.0, 2.0, 3.0, 4.0, 5.0]", vector.toString()) ;

    }

    {

        VectorXd vector(7) ;

        vector(0) = 1.0 ;
        vector(1) = 2.01 ;
        vector(2) = 3.001 ;
        vector(3) = 4.0001 ;
        vector(4) = 5.00001 ;
        vector(5) = -6.000001 ;
        vector(6) = -2.6988e-10 ;

        EXPECT_EQ("[1.0, 2.01, 3.001, 4.0001, 5.00001, -6.000001, -2.6988e-10]", vector.toString()) ;

        EXPECT_EQ("[1, 2, 3, 4, 5, -6, -0]", vector.toString(0)) ;
        EXPECT_EQ("[1.0, 2.0, 3.0, 4.0, 5.0, -6.0, -0.0]", vector.toString(1)) ;
        EXPECT_EQ("[1.00, 2.01, 3.00, 4.00, 5.00, -6.00, -0.00]", vector.toString(2)) ;
        EXPECT_EQ("[1.000, 2.010, 3.001, 4.000, 5.000, -6.000, -0.000]", vector.toString(3)) ;
        EXPECT_EQ("[1.0000, 2.0100, 3.0010, 4.0001, 5.0000, -6.0000, -0.0000]", vector.toString(4)) ;
        EXPECT_EQ("[1.00000, 2.01000, 3.00100, 4.00010, 5.00001, -6.00000, -0.00000]", vector.toString(5)) ;
        EXPECT_EQ("[1.000000, 2.010000, 3.001000, 4.000100, 5.000010, -6.000001, -0.000000]", vector.toString(6)) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Objects_VectorXd, Parse)
{

    using ostk::math::obj::VectorXd ;

    {

        const VectorXd vector = VectorXd::Parse("[1.000000, 2.000000, 3.000000, 4.000000, 5.000000]") ;

        EXPECT_EQ(5, vector.size()) ;

        EXPECT_EQ(1.0, vector(0)) ;
        EXPECT_EQ(2.0, vector(1)) ;
        EXPECT_EQ(3.0, vector(2)) ;
        EXPECT_EQ(4.0, vector(3)) ;
        EXPECT_EQ(5.0, vector(4)) ;

    }

    {

        EXPECT_ANY_THROW(VectorXd::Parse("")) ;
        EXPECT_ANY_THROW(VectorXd::Parse("[]")) ;
        EXPECT_ANY_THROW(VectorXd::Parse("1.000000, 2.000000, 3.000000, 4.000000, 5.000000")) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
