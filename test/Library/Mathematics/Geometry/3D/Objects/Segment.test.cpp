////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Segment.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, Constructor)
{

    using library::math::geom::d3::objects::Segment ;

    {

        EXPECT_NO_THROW(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 })) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, Clone)
{

    using library::math::geom::d3::objects::Segment ;

    {

        EXPECT_NO_THROW(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).clone()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, EqualToOperator)
{

    using library::math::geom::d3::objects::Segment ;
    
    {

        EXPECT_TRUE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 })) ;
        EXPECT_TRUE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Segment({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, 0.0 })) ;

    }

    {

        EXPECT_FALSE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0 })) ;

    }

    {

        EXPECT_FALSE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Segment::Undefined()) ;
        EXPECT_FALSE(Segment::Undefined() == Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 })) ;
        EXPECT_FALSE(Segment::Undefined() == Segment::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, NotEqualToOperator)
{

    using library::math::geom::d3::objects::Segment ;

    {

        EXPECT_FALSE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 })) ;
        EXPECT_FALSE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Segment({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, 0.0 })) ;

    }

    {

        EXPECT_TRUE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0 })) ;

    }

    {

        EXPECT_TRUE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Segment::Undefined()) ;
        EXPECT_TRUE(Segment::Undefined() != Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 })) ;
        EXPECT_TRUE(Segment::Undefined() != Segment::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, StreamOperator)
{

    using library::math::geom::d3::objects::Segment ;
    
    {

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, IsDefined)
{

    using library::math::geom::d3::objects::Segment ;
    
    {

        EXPECT_TRUE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }).isDefined()) ;
        EXPECT_TRUE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).isDefined()) ;

    }

    {

        EXPECT_FALSE(Segment::Undefined().isDefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, IsDegenerate)
{

    using library::math::geom::d3::objects::Segment ;
    
    {

        EXPECT_TRUE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }).isDegenerate()) ;
        EXPECT_TRUE(Segment({ 1.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0 }).isDegenerate()) ;

    }

    {

        EXPECT_FALSE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).isDegenerate()) ;
        EXPECT_FALSE(Segment({ 1.0, 2.0, 3.0 }, { 0.0, 0.0, 1.0 }).isDegenerate()) ;

    }

    {

        EXPECT_ANY_THROW(Segment::Undefined().isDegenerate()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, Intersects)
{

    using library::math::geom::d3::objects::Segment ;

    {

        FAIL() ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, Contains)
{

    using library::math::geom::d3::objects::Segment ;

    {

        FAIL() ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, GetCenter)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Segment ;
    
    {

        EXPECT_EQ(Point(0.0, 0.0, 0.0), Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }).getCenter()) ;
        EXPECT_EQ(Point(0.0, 0.0, 1.0), Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0 }).getCenter()) ;
        
        EXPECT_EQ(Point(0.0, 0.0, 0.0), Segment({ 0.0, 0.0, -1.0 }, { 0.0, 0.0, +1.0 }).getCenter()) ;

    }

    {

        EXPECT_ANY_THROW(Segment::Undefined().getCenter()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, GetDirection)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Segment ;
    
    {

        EXPECT_EQ(Vector3d(0.0, 0.0, +1.0), Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, +2.0 }).getDirection()) ;
        EXPECT_EQ(Vector3d(0.0, 0.0, -1.0), Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, -2.0 }).getDirection()) ;

    }

    {

        EXPECT_ANY_THROW(Segment::Undefined().getDirection()) ;

        EXPECT_ANY_THROW(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }).getDirection()) ;
        EXPECT_ANY_THROW(Segment({ 1.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0 }).getDirection()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, GetLength)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Segment ;
    
    {

        EXPECT_EQ(0.0, Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }).getLength()) ;
        EXPECT_EQ(0.0, Segment({ 1.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0 }).getLength()) ;
        
        EXPECT_EQ(1.0, Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).getLength()) ;
        EXPECT_EQ(2.0, Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0 }).getLength()) ;
        
        EXPECT_EQ(4.0, Segment({ 0.0, 0.0, -2.0 }, { 0.0, 0.0, +2.0 }).getLength()) ;

    }

    {

        EXPECT_ANY_THROW(Segment::Undefined().getLength()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, Undefined)
{

    using library::math::geom::d3::objects::Segment ;
    
    {

        EXPECT_NO_THROW(Segment::Undefined()) ;
        EXPECT_FALSE(Segment::Undefined().isDefined()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////