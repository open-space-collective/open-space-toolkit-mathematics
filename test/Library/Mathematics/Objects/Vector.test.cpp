////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Objects/Vector.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Objects/Vector.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Mathematics_Objects_Vector2i, Constructor)
{

    using library::math::obj::Vector2i ;

    {

        const Vector2i vector(1, 2) ;

        EXPECT_EQ(1, vector(0)) ;
        EXPECT_EQ(2, vector(1)) ;

    }

}

TEST (Library_Mathematics_Objects_Vector2i, ToString)
{

    using library::math::obj::Vector2i ;

    {

        const Vector2i vector(1, 2) ;

        EXPECT_EQ("[1, 2]", vector.toString()) ;

        EXPECT_EQ("[1, 2]", vector.toString(0)) ;
        EXPECT_EQ("[1, 2]", vector.toString(1)) ;
        EXPECT_EQ("[1, 2]", vector.toString(2)) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Mathematics_Objects_Vector3i, Constructor)
{

    using library::math::obj::Vector3i ;

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

TEST (Library_Mathematics_Objects_Vector3i, ToString)
{

    using library::math::obj::Vector3i ;

    {

        const Vector3i vector(1, 2, 3) ;

        EXPECT_EQ("[1, 2, 3]", vector.toString()) ;

        EXPECT_EQ("[1, 2, 3]", vector.toString(0)) ;
        EXPECT_EQ("[1, 2, 3]", vector.toString(1)) ;
        EXPECT_EQ("[1, 2, 3]", vector.toString(2)) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Mathematics_Objects_Vector2d, Constructor)
{

    using library::math::obj::Vector2d ;

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

TEST (Library_Mathematics_Objects_Vector2d, ToString)
{

    using library::math::obj::Vector2d ;

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

TEST (Library_Mathematics_Objects_Vector3d, Constructor)
{

    using library::math::obj::Vector3d ;

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

TEST (Library_Mathematics_Objects_Vector3d, ToString)
{

    using library::math::obj::Vector3d ;

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

TEST (Library_Mathematics_Objects_Vector4d, Constructor)
{

    using library::math::obj::Vector4d ;

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

TEST (Library_Mathematics_Objects_Vector4d, ToString)
{

    using library::math::obj::Vector4d ;

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

TEST (Library_Mathematics_Objects_Vector4d, Parse)
{

    using library::math::obj::Vector4d ;

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

TEST (Library_Mathematics_Objects_VectorXd, Constructor)
{

    using library::math::obj::VectorXd ;

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

TEST (Library_Mathematics_Objects_VectorXd, ToString)
{

    using library::math::obj::VectorXd ;

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

        VectorXd vector(5) ;

        vector(0) = 1.0 ;
        vector(1) = 2.01 ;
        vector(2) = 3.001 ;
        vector(3) = 4.0001 ;
        vector(4) = 5.00001 ;

        EXPECT_EQ("[1.0, 2.01, 3.001, 4.0001, 5.00001]", vector.toString()) ;

        EXPECT_EQ("[1, 2, 3, 4, 5]", vector.toString(0)) ;
        EXPECT_EQ("[1.0, 2.0, 3.0, 4.0, 5.0]", vector.toString(1)) ;
        EXPECT_EQ("[1.00, 2.01, 3.00, 4.00, 5.00]", vector.toString(2)) ;
        EXPECT_EQ("[1.000, 2.010, 3.001, 4.000, 5.000]", vector.toString(3)) ;
        EXPECT_EQ("[1.0000, 2.0100, 3.0010, 4.0001, 5.0000]", vector.toString(4)) ;
        EXPECT_EQ("[1.00000, 2.01000, 3.00100, 4.00010, 5.00001]", vector.toString(5)) ;
        
    }

}

TEST (Library_Mathematics_Objects_VectorXd, Parse)
{

    using library::math::obj::VectorXd ;

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