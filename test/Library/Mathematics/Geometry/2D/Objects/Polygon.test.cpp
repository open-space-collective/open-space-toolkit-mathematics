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
    
    using library::math::geom::d2::objects::Polygon ;

    {

        const Array<Polygon::Vertex> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        EXPECT_NO_THROW(Polygon polygon(vertices) ;) ;

    }

    {

        const Array<Polygon::Vertex> outerRing =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Array<Array<Polygon::Vertex>> innerRings =
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

        EXPECT_NO_THROW(Polygon({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } })) ;

    }

    {

        const Array<Polygon::Vertex> vertexArray = Array<Polygon::Vertex>::Empty() ;

        EXPECT_NO_THROW(Polygon polygon(vertexArray) ;) ;

    }

    {

        const Array<Polygon::Vertex> vertexArray = { { 0.0, 0.0 } } ;

        EXPECT_ANY_THROW(Polygon polygon(vertexArray) ;) ;

    }

    {

        const Array<Polygon::Vertex> vertexArray = { { 0.0, 0.0 }, { 0.0, 1.0 } } ;

        EXPECT_ANY_THROW(Polygon polygon(vertexArray) ;) ;

    }

    {

        const Array<Polygon::Vertex> outerRing =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Array<Array<Polygon::Vertex>> innerRings =
        {
            {
                { 0.0, 0.0 },
                { 0.0, 0.5 },
                { 0.5, 0.5 },
                { 0.5, 0.0 }
            },
            {
                { 0.0, 0.0 },
                { 0.0, 0.1 }
            }
        } ;

        EXPECT_ANY_THROW(Polygon polygon(outerRing, innerRings) ;) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_Polygon, Clone)
{

    using library::core::ctnr::Array ;
    
    using library::math::geom::d2::objects::Polygon ;

    {

        const Array<Polygon::Vertex> vertices =
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
    
    using library::math::geom::d2::objects::Polygon ;
    
    {

        const Array<Polygon::Vertex> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        EXPECT_TRUE(Polygon(vertices) == Polygon(vertices)) ;

    }

    {

        const Array<Polygon::Vertex> vertices_A =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Array<Polygon::Vertex> vertices_B =
        {
            { 1.0, 0.0 },
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 }
        } ;

        EXPECT_TRUE(Polygon(vertices_A) == Polygon(vertices_B)) ;

    }

    {

        const Array<Polygon::Vertex> vertices_A =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Array<Polygon::Vertex> vertices_B =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 2.0 },
            { 1.0, 0.0 }
        } ;

        EXPECT_FALSE(Polygon(vertices_A) == Polygon(vertices_B)) ;

    }

    {

        const Array<Polygon::Vertex> vertices =
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
    
    using library::math::geom::d2::objects::Polygon ;
    
    {

        const Array<Polygon::Vertex> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        EXPECT_FALSE(Polygon(vertices) != Polygon(vertices)) ;

    }

    {

        const Array<Polygon::Vertex> vertices_A =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Array<Polygon::Vertex> vertices_B =
        {
            { 1.0, 0.0 },
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 }
        } ;

        EXPECT_FALSE(Polygon(vertices_A) != Polygon(vertices_B)) ;

    }

    {

        const Array<Polygon::Vertex> vertices_A =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Array<Polygon::Vertex> vertices_B =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 2.0 },
            { 1.0, 0.0 }
        } ;

        EXPECT_TRUE(Polygon(vertices_A) != Polygon(vertices_B)) ;

    }

    {

        const Array<Polygon::Vertex> vertices =
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
    
    using library::math::geom::d2::objects::Polygon ;
    
    {

        testing::internal::CaptureStdout() ;

        const Array<Polygon::Vertex> vertices =
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
    
    using library::math::geom::d2::objects::Polygon ;
    
    {

        const Array<Polygon::Vertex> vertices =
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

TEST (Library_Mathematics_Geometry_2D_Objects_Polygon, GetInnerRingCount)
{

    using library::core::ctnr::Array ;

    using library::math::geom::d2::objects::Polygon ;

    {

        const Array<Polygon::Vertex> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Polygon polygon = { vertices } ;

        EXPECT_EQ(0, polygon.getInnerRingCount()) ;

    }

    {

        const Array<Polygon::Vertex> outerRing =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Array<Array<Polygon::Vertex>> innerRings =
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

        const Polygon polygon = { outerRing, innerRings } ;

        EXPECT_EQ(2, polygon.getInnerRingCount()) ;

    }

    {

        EXPECT_ANY_THROW(Polygon::Undefined().getInnerRingCount()) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_Polygon, GetEdgeCount)
{

    using library::core::ctnr::Array ;

    using library::math::geom::d2::objects::Polygon ;

    {

        const Array<Polygon::Vertex> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Polygon polygon = { vertices } ;

        EXPECT_EQ(4, polygon.getEdgeCount()) ;

    }

    {

        const Array<Polygon::Vertex> outerRing =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Array<Array<Polygon::Vertex>> innerRings =
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

        const Polygon polygon = { outerRing, innerRings } ;

        EXPECT_EQ(12, polygon.getEdgeCount()) ;

    }

    {

        EXPECT_ANY_THROW(Polygon::Undefined().getEdgeCount()) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_Polygon, GetVertexCount)
{

    using library::core::ctnr::Array ;

    using library::math::geom::d2::objects::Polygon ;

    {

        const Array<Polygon::Vertex> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Polygon polygon = { vertices } ;

        EXPECT_EQ(4, polygon.getVertexCount()) ;

    }

    {

        const Array<Polygon::Vertex> outerRing =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Array<Array<Polygon::Vertex>> innerRings =
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

        const Polygon polygon = { outerRing, innerRings } ;

        EXPECT_EQ(12, polygon.getVertexCount()) ;

    }

    {

        EXPECT_ANY_THROW(Polygon::Undefined().getVertexCount()) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_Polygon, GetOuterRing)
{

    using library::core::ctnr::Array ;

    using library::math::geom::d2::objects::Polygon ;

    {

        const Array<Polygon::Vertex> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Polygon polygon = { vertices } ;

        const Polygon::Ring referenceOuterRing =
        {
            {
                { 0.0, 0.0 },
                { 0.0, 1.0 },
                { 1.0, 1.0 },
                { 1.0, 0.0 },
                { 0.0, 0.0 }
            }
        } ;

        EXPECT_EQ(referenceOuterRing, polygon.getOuterRing()) ;

    }

    {

        const Array<Polygon::Vertex> outerRing =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Array<Array<Polygon::Vertex>> innerRings =
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

        const Polygon polygon = { outerRing, innerRings } ;

        const Polygon::Ring referenceOuterRing =
        {
            {
                { 0.0, 0.0 },
                { 0.0, 1.0 },
                { 1.0, 1.0 },
                { 1.0, 0.0 },
                { 0.0, 0.0 }
            }
        } ;

        EXPECT_EQ(referenceOuterRing, polygon.getOuterRing()) ;

    }

    {

        EXPECT_ANY_THROW(Polygon::Undefined().getOuterRing()) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_Polygon, GetInnerRingAt)
{

    using library::core::ctnr::Array ;

    using library::math::geom::d2::objects::Polygon ;

    {

        const Array<Polygon::Vertex> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Polygon polygon = { vertices } ;

        EXPECT_ANY_THROW(polygon.getInnerRingAt(0)) ;

    }

    {

        const Array<Polygon::Vertex> outerRing =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Array<Array<Polygon::Vertex>> innerRings =
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

        const Polygon polygon = { outerRing, innerRings } ;

        const Polygon::Ring referenceFirstInnerRing =
        {
            {
                { 0.0, 0.0 },
                { 0.0, 0.5 },
                { 0.5, 0.5 },
                { 0.5, 0.0 },
                { 0.0, 0.0 }
            }
        } ;

        EXPECT_EQ(referenceFirstInnerRing, polygon.getInnerRingAt(0)) ;

        const Polygon::Ring referenceSecondInnerRing =
        {
            {
                { 0.0, 0.0 },
                { 0.0, 0.1 },
                { 0.1, 0.1 },
                { 0.1, 0.0 },
                { 0.0, 0.0 }
            }
        } ;

        EXPECT_EQ(referenceSecondInnerRing, polygon.getInnerRingAt(1)) ;
        
        EXPECT_ANY_THROW(polygon.getInnerRingAt(2)) ;

    }

    {

        EXPECT_ANY_THROW(Polygon::Undefined().getInnerRingAt(0)) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_Polygon, GetEdgeAt)
{

    using library::core::ctnr::Array ;

    using library::math::geom::d2::objects::Polygon ;

    {

        const Array<Polygon::Vertex> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Polygon polygon = { vertices } ;

        EXPECT_EQ(Polygon::Edge({ 0.0, 0.0 }, { 0.0, 1.0 }), polygon.getEdgeAt(0)) ;
        EXPECT_EQ(Polygon::Edge({ 0.0, 1.0 }, { 1.0, 1.0 }), polygon.getEdgeAt(1)) ;
        EXPECT_EQ(Polygon::Edge({ 1.0, 1.0 }, { 1.0, 0.0 }), polygon.getEdgeAt(2)) ;
        EXPECT_EQ(Polygon::Edge({ 1.0, 0.0 }, { 0.0, 0.0 }), polygon.getEdgeAt(3)) ;

        EXPECT_ANY_THROW(polygon.getEdgeAt(4)) ;

    }

    {

        // [TBI] Inner ring support

    }

    {

        EXPECT_ANY_THROW(Polygon::Undefined().getEdgeAt(0)) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_Polygon, GetVertexAt)
{

    using library::core::ctnr::Array ;

    using library::math::geom::d2::objects::Polygon ;

    {

        const Array<Polygon::Vertex> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Polygon polygon = { vertices } ;

        EXPECT_EQ(Polygon::Vertex(0.0, 0.0), polygon.getVertexAt(0)) ;
        EXPECT_EQ(Polygon::Vertex(0.0, 1.0), polygon.getVertexAt(1)) ;
        EXPECT_EQ(Polygon::Vertex(1.0, 1.0), polygon.getVertexAt(2)) ;
        EXPECT_EQ(Polygon::Vertex(1.0, 0.0), polygon.getVertexAt(3)) ;

        EXPECT_ANY_THROW(polygon.getVertexAt(4)) ;

    }

    {

        // [TBI] Inner ring support

    }

    {

        EXPECT_ANY_THROW(Polygon::Undefined().getVertexAt(0)) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_Polygon, GetEdges)
{

    using library::core::ctnr::Array ;

    using library::math::geom::d2::objects::Polygon ;

    {

        const Array<Polygon::Vertex> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Polygon polygon = { vertices } ;

        const Array<Polygon::Edge> referencePolygonEdges =
        {
            Polygon::Edge({ 0.0, 0.0 }, { 0.0, 1.0 }),
            Polygon::Edge({ 0.0, 1.0 }, { 1.0, 1.0 }),
            Polygon::Edge({ 1.0, 1.0 }, { 1.0, 0.0 }),
            Polygon::Edge({ 1.0, 0.0 }, { 0.0, 0.0 })
        } ;

        EXPECT_EQ(referencePolygonEdges, polygon.getEdges()) ;

    }

    {

        // [TBI] Inner ring support

    }

    {

        EXPECT_ANY_THROW(Polygon::Undefined().getEdges()) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_Polygon, GetVertices)
{

    using library::core::ctnr::Array ;
    
    using library::math::geom::d2::objects::Polygon ;

    {

        const Array<Polygon::Vertex> vertices =
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

TEST (Library_Mathematics_Geometry_2D_Objects_Polygon, ToString)
{

    using library::core::ctnr::Array ;
    
    using library::math::obj::Vector2d ;
    using library::math::geom::d2::objects::Polygon ;

    {

        const Array<Polygon::Vertex> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        EXPECT_EQ("POLYGON((0 0,0 1,1 1,1 0,0 0))", Polygon(vertices).toString()) ;
        EXPECT_EQ("POLYGON((0 0,0 1,1 1,1 0,0 0))", Polygon(vertices).toString(Polygon::Format::Standard)) ;
        EXPECT_EQ("POLYGON((0 0,0 1,1 1,1 0,0 0))", Polygon(vertices).toString(Polygon::Format::WKT)) ;

    }

    {

        const Array<Polygon::Vertex> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        EXPECT_EQ("POLYGON((0.0000000000 0.0000000000,0.0000000000 1.0000000000,1.0000000000 1.0000000000,1.0000000000 0.0000000000,0.0000000000 0.0000000000))", Polygon(vertices).toString(Polygon::Format::Standard, 10)) ;
        EXPECT_EQ("POLYGON((0.0000000000 0.0000000000,0.0000000000 1.0000000000,1.0000000000 1.0000000000,1.0000000000 0.0000000000,0.0000000000 0.0000000000))", Polygon(vertices).toString(Polygon::Format::WKT, 10)) ;

    }

    {

        const Array<Polygon::Vertex> outerRing =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Array<Array<Polygon::Vertex>> innerRings =
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

        EXPECT_EQ("POLYGON((0 0,0 1,1 1,1 0,0 0),(0 0,0 0.5,0.5 0.5,0.5 0,0 0),(0 0,0 0.1,0.1 0.1,0.1 0,0 0))", Polygon(outerRing, innerRings).toString()) ;
        EXPECT_EQ("POLYGON((0 0,0 1,1 1,1 0,0 0),(0 0,0 0.5,0.5 0.5,0.5 0,0 0),(0 0,0 0.1,0.1 0.1,0.1 0,0 0))", Polygon(outerRing, innerRings).toString(Polygon::Format::Standard)) ;
        EXPECT_EQ("POLYGON((0 0,0 1,1 1,1 0,0 0),(0 0,0 0.5,0.5 0.5,0.5 0,0 0),(0 0,0 0.1,0.1 0.1,0.1 0,0 0))", Polygon(outerRing, innerRings).toString(Polygon::Format::WKT)) ;
        
    }

    {

        EXPECT_ANY_THROW(Polygon::Undefined().toString()) ;

    }

}

TEST (Library_Mathematics_Geometry_2D_Objects_Polygon, Translate)
{

    using library::core::ctnr::Array ;
    
    using library::math::obj::Vector2d ;
    using library::math::geom::d2::objects::Polygon ;

    {

        const Array<Polygon::Vertex> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        Polygon polygon = { vertices } ;

        polygon.translate({ 4.0, 5.0 }) ;

        EXPECT_EQ(Polygon({ { 4.0, 5.0 }, { 4.0, 6.0 }, { 5.0, 6.0 }, { 5.0, 5.0 } }), polygon) ;

    }

    {

        const Array<Polygon::Vertex> vertices =
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