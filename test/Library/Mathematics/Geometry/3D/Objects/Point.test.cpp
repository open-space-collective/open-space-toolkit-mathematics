////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Point.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Objects/Point.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Mathematics_Geometry_3D_Objects_Point, Constructor)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::objects::Point ;

    {

        EXPECT_NO_THROW(Point(1.0, 2.0, 3.0)) ;

    }

    {

        EXPECT_NO_THROW(Point(Vector3d({ 1.0, 2.0, 3.0 }))) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Point, Clone)
{

    using library::math::geom::d3::objects::Point ;

    {

        EXPECT_NO_THROW(Point(1.0, 2.0, 3.0).clone()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Point, AdditionOperator)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::objects::Point ;

    {

        EXPECT_EQ(Point(1.0, 2.0, 3.0), Point(1.0, 2.0, 3.0) + Vector3d(0.0, 0.0, 0.0)) ;
        EXPECT_EQ(Point(2.0, 2.0, 3.0), Point(1.0, 2.0, 3.0) + Vector3d(1.0, 0.0, 0.0)) ;

    }

    {

        EXPECT_ANY_THROW(Point::Undefined() + Vector3d(0.0, 0.0, 0.0)) ;
        EXPECT_ANY_THROW(Point(1.0, 2.0, 3.0) + Vector3d::Undefined()) ;
        
    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Point, SubtractionOperator)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::objects::Point ;

    {

        EXPECT_EQ(Point(1.0, 2.0, 3.0), Point(1.0, 2.0, 3.0) - Vector3d(0.0, 0.0, 0.0)) ;
        EXPECT_EQ(Point(0.0, 2.0, 3.0), Point(1.0, 2.0, 3.0) - Vector3d(1.0, 0.0, 0.0)) ;

    }

    {

        EXPECT_ANY_THROW(Point::Undefined() - Vector3d(0.0, 0.0, 0.0)) ;
        EXPECT_ANY_THROW(Point(1.0, 2.0, 3.0) - Vector3d::Undefined()) ;
        
    }
    
}

TEST (Library_Mathematics_Geometry_3D_Objects_Point, EqualToOperator)
{

    using library::math::geom::d3::objects::Point ;
    
    {

        EXPECT_TRUE(Point(1.0, 2.0, 3.0) == Point(1.0, 2.0, 3.0)) ;

    }

    {

        EXPECT_FALSE(Point(1.0, 2.0, 3.0) == Point(1.0, 2.0, 4.0)) ;

    }

    {

        EXPECT_FALSE(Point(1.0, 2.0, 3.0) == Point::Undefined()) ;
        EXPECT_FALSE(Point::Undefined() == Point(1.0, 2.0, 3.0)) ;
        EXPECT_FALSE(Point::Undefined() == Point::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Point, NotEqualToOperator)
{

    using library::math::geom::d3::objects::Point ;

    {

        EXPECT_TRUE(Point(1.0, 2.0, 3.0) != Point(1.0, 2.0, 4.0)) ;

    }

    {

        EXPECT_FALSE(Point(1.0, 2.0, 3.0) != Point(1.0, 2.0, 3.0)) ;

    }

    {

        EXPECT_TRUE(Point(1.0, 2.0, 3.0) != Point::Undefined()) ;
        EXPECT_TRUE(Point::Undefined() != Point(1.0, 2.0, 3.0)) ;
        EXPECT_TRUE(Point::Undefined() != Point::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Point, StreamOperator)
{

    using library::math::geom::d3::objects::Point ;
    
    {

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << Point(1.0, 2.0, 3.0) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Point, IsDefined)
{

    using library::math::geom::d3::objects::Point ;
    
    {

        EXPECT_TRUE(Point(0.0, 0.0, 0.0).isDefined()) ;
        EXPECT_TRUE(Point(1.0, 2.0, 3.0).isDefined()) ;

    }

    {

        EXPECT_FALSE(Point::Undefined().isDefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Point, Undefined)
{

    using library::math::geom::d3::objects::Point ;
    
    {

        EXPECT_NO_THROW(Point::Undefined()) ;
        EXPECT_FALSE(Point::Undefined().isDefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Point, Origin)
{

    using library::math::geom::d3::objects::Point ;
    
    {

        EXPECT_NO_THROW(Point::Origin()) ;
        EXPECT_EQ(Point(0.0, 0.0, 0.0), Point::Origin()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////