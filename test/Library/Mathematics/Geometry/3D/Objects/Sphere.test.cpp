////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Sphere.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Objects/Sphere.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, Constructor)
{

    using library::math::geom::d3::objects::Sphere ;

    {

        EXPECT_NO_THROW(Sphere({ 1.0, 2.0, 3.0 }, 4.0)) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, EqualToOperator)
{

    using library::math::geom::d3::objects::Sphere ;
    
    {

        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 4.0) == Sphere({ 1.0, 2.0, 3.0 }, 4.0)) ;

    }

    {

        EXPECT_FALSE(Sphere({ 1.0, 2.0, 3.0 }, 4.0) == Sphere({ 1.0, 2.0, 4.0 }, 4.0)) ;
        EXPECT_FALSE(Sphere({ 1.0, 2.0, 3.0 }, 4.0) == Sphere({ 1.0, 2.0, 3.0 }, 3.0)) ;

    }

    {

        EXPECT_FALSE(Sphere({ 1.0, 2.0, 3.0 }, 4.0) == Sphere::Undefined()) ;
        EXPECT_FALSE(Sphere::Undefined() == Sphere({ 1.0, 2.0, 3.0 }, 4.0)) ;
        EXPECT_FALSE(Sphere::Undefined() == Sphere::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, NotEqualToOperator)
{

    using library::math::geom::d3::objects::Sphere ;

    {

        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 4.0) != Sphere({ 1.0, 2.0, 4.0 }, 4.0)) ;
        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 4.0) != Sphere({ 1.0, 2.0, 3.0 }, 3.0)) ;

    }

    {

        EXPECT_FALSE(Sphere({ 1.0, 2.0, 3.0 }, 4.0) != Sphere({ 1.0, 2.0, 3.0 }, 4.0)) ;

    }

    {

        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 4.0) != Sphere::Undefined()) ;
        EXPECT_TRUE(Sphere::Undefined() != Sphere({ 1.0, 2.0, 3.0 }, 4.0)) ;
        EXPECT_TRUE(Sphere::Undefined() != Sphere::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, StreamOperator)
{

    using library::math::geom::d3::objects::Sphere ;
    
    {

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << Sphere({ 0.0, 0.0, 0.0 }, 1.0) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, IsDefined)
{

    using library::math::geom::d3::objects::Sphere ;
    
    {

        EXPECT_TRUE(Sphere({ 0.0, 0.0, 0.0 }, 1.0).isDefined()) ;
        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 4.0).isDefined()) ;

    }

    {

        EXPECT_FALSE(Sphere::Undefined().isDefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, IsUnitary)
{

    using library::math::geom::d3::objects::Sphere ;
    
    {

        EXPECT_TRUE(Sphere({ 0.0, 0.0, 0.0 }, 1.0).isUnitary()) ;
        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 1.0).isUnitary()) ;

    }

    {

        EXPECT_FALSE(Sphere({ 0.0, 0.0, 0.0 }, 1.1).isUnitary()) ;
        EXPECT_FALSE(Sphere({ 1.0, 2.0, 3.0 }, 0.9).isUnitary()) ;

    }

    {

        EXPECT_ANY_THROW(Sphere::Undefined().isUnitary()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, GetCenter)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::objects::Sphere ;
    
    {

        EXPECT_EQ(Vector3d(1.0, 2.0, 3.0), Sphere({ 1.0, 2.0, 3.0 }, 4.0).getCenter()) ;

    }

    {

        EXPECT_ANY_THROW(Sphere::Undefined().getCenter()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, GetRadius)
{

    using library::math::geom::d3::objects::Sphere ;
    
    {

        EXPECT_EQ(4.0, Sphere({ 1.0, 2.0, 3.0 }, 4.0).getRadius()) ;

    }

    {

        EXPECT_ANY_THROW(Sphere::Undefined().getRadius()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, Undefined)
{

    using library::math::geom::d3::objects::Sphere ;
    
    {

        EXPECT_NO_THROW(Sphere::Undefined()) ;
        EXPECT_FALSE(Sphere::Undefined().isDefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, Unit)
{

    using library::math::geom::d3::objects::Sphere ;
    
    {

        EXPECT_NO_THROW(Sphere::Unit({ 0.0, 0.0, 0.0 })) ;
        EXPECT_EQ(Sphere({ 0.0, 0.0, 0.0 }, 1.0), Sphere::Unit({ 0.0, 0.0, 0.0 })) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////