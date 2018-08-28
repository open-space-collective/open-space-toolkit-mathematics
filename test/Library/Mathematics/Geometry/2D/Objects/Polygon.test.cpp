////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/2D/Objects/Polygon.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/2D/Objects/Polygon.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Mathematics_Geometry_2D_Objects_Polygon, Constructor)
{

    using library::core::ctnr::Array ;
    
    using library::math::geom::d2::objects::Point ;
    using library::math::geom::d2::objects::Polygon ;

    {

        const Array<Point> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        EXPECT_NO_THROW(Polygon polygon(vertices) ;) ;

    }

    {

        const Array<Point> outerRing =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Array<Array<Point>> innerRings =
        {
            {
                { 0.0, 0.0 },
                { 0.0, 0.5 },
                { 0.5, 0.5 },
                { 0.5, 0.0 }
            },
            {
                { 0.0, 0.0 },
                { 0.0, 0.1 },
                { 0.1, 0.1 },
                { 0.1, 0.0 }
            }
        } ;

        EXPECT_NO_THROW(Polygon polygon(outerRing, innerRings) ;) ;

    }

    {

        EXPECT_NO_THROW(Polygon({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 }})) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_Polygon, Clone)
{

    using library::core::ctnr::Array ;
    
    using library::math::geom::d2::objects::Point ;
    using library::math::geom::d2::objects::Polygon ;

    {

        const Array<Point> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        EXPECT_NO_THROW(Polygon(vertices).clone()) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_Polygon, EqualToOperator)
{

    using library::core::ctnr::Array ;
    
    using library::math::geom::d2::objects::Point ;
    using library::math::geom::d2::objects::Polygon ;
    
    {

        const Array<Point> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        EXPECT_TRUE(Polygon(vertices) == Polygon(vertices)) ;

    }

    {

        const Array<Point> vertices_A =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Array<Point> vertices_B =
        {
            { 1.0, 0.0 },
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 }
        } ;

        EXPECT_TRUE(Polygon(vertices_A) == Polygon(vertices_B)) ;

    }

    {

        const Array<Point> vertices_A =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Array<Point> vertices_B =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 2.0 },
            { 1.0, 0.0 }
        } ;

        EXPECT_FALSE(Polygon(vertices_A) == Polygon(vertices_B)) ;

    }

    {

        const Array<Point> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        EXPECT_FALSE(Polygon(vertices) == Polygon::Undefined()) ;
        EXPECT_FALSE(Polygon::Undefined() == Polygon(vertices)) ;
        EXPECT_FALSE(Polygon::Undefined() == Polygon::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_Polygon, NotEqualToOperator)
{

    using library::core::ctnr::Array ;
    
    using library::math::geom::d2::objects::Point ;
    using library::math::geom::d2::objects::Polygon ;
    
    {

        const Array<Point> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        EXPECT_FALSE(Polygon(vertices) != Polygon(vertices)) ;

    }

    {

        const Array<Point> vertices_A =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Array<Point> vertices_B =
        {
            { 1.0, 0.0 },
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 }
        } ;

        EXPECT_FALSE(Polygon(vertices_A) != Polygon(vertices_B)) ;

    }

    {

        const Array<Point> vertices_A =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Array<Point> vertices_B =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 2.0 },
            { 1.0, 0.0 }
        } ;

        EXPECT_TRUE(Polygon(vertices_A) != Polygon(vertices_B)) ;

    }

    {

        const Array<Point> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        EXPECT_TRUE(Polygon(vertices) != Polygon::Undefined()) ;
        EXPECT_TRUE(Polygon::Undefined() != Polygon(vertices)) ;
        EXPECT_TRUE(Polygon::Undefined() != Polygon::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_Polygon, StreamOperator)
{

    using library::core::ctnr::Array ;
    
    using library::math::geom::d2::objects::Point ;
    using library::math::geom::d2::objects::Polygon ;
    
    {

        testing::internal::CaptureStdout() ;

        const Array<Point> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        EXPECT_NO_THROW(std::cout << Polygon(vertices) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_Polygon, IsDefined)
{

    using library::core::ctnr::Array ;
    
    using library::math::geom::d2::objects::Point ;
    using library::math::geom::d2::objects::Polygon ;
    
    {

        const Array<Point> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        EXPECT_TRUE(Polygon(vertices).isDefined()) ;

    }

    {

        EXPECT_FALSE(Polygon::Undefined().isDefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_Polygon, GetVertices)
{

    using library::core::ctnr::Array ;
    
    using library::math::geom::d2::objects::Point ;
    using library::math::geom::d2::objects::Polygon ;

    {

        const Array<Point> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        EXPECT_EQ(vertices, Polygon(vertices).getVertices()) ;

    }

    {

        EXPECT_ANY_THROW(Polygon::Undefined().getVertices()) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_Polygon, Translate)
{

    using library::core::ctnr::Array ;
    
    using library::math::obj::Vector2d ;
    using library::math::geom::d2::objects::Point ;
    using library::math::geom::d2::objects::Polygon ;

    {

        const Array<Point> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        Polygon polygon = { vertices } ;

        polygon.translate({ 4.0, 5.0 }) ;

        EXPECT_EQ(Polygon({ { 4.0, 5.0 }, { 4.0, 6.0 }, { 5.0, 6.0 }, { 5.0, 5.0 }}), polygon) ;

    }

    {

        const Array<Point> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        EXPECT_ANY_THROW(Polygon::Undefined().translate(Vector2d::Undefined())) ;
        EXPECT_ANY_THROW(Polygon::Undefined().translate({ 0.0, 0.0 })) ;
        EXPECT_ANY_THROW(Polygon(vertices).translate(Vector2d::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_Polygon, Undefined)
{

    using library::math::geom::d2::objects::Polygon ;
    
    {

        EXPECT_NO_THROW(Polygon::Undefined()) ;
        EXPECT_FALSE(Polygon::Undefined().isDefined()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////