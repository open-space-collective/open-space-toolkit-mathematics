////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Polygon.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/MultiPolygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Polygon.hpp>

#include <OpenSpaceToolkit/Core/Containers/Tuple.hpp>

#include <Global.test.hpp>

#include <iostream>
#include <deque>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

#include <boost/foreach.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, Constructor)
{

    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d2::objects::Polygon ;

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

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, Clone)
{

    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d2::objects::Polygon ;

    {

        const Array<Polygon::Vertex> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        EXPECT_NO_THROW(const Polygon* polygonPtr = Polygon(vertices).clone() ; delete polygonPtr ;) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, EqualToOperator)
{

    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d2::objects::Polygon ;

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

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, NotEqualToOperator)
{

    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d2::objects::Polygon ;

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

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, StreamOperator)
{

    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d2::objects::Polygon ;

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

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, IsDefined)
{

    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d2::objects::Polygon ;

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

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, IsNear)
{

    using ostk::core::types::Real ;

    using ostk::math::geom::d2::objects::Polygon ;

    // Is near ifself

    {

        const Polygon polygon =
        {
            {
                { 0.0, 0.0 },
                { 0.0, 1.0 },
                { 1.0, 1.0 },
                { 1.0, 0.0 }
            }
        } ;

        EXPECT_TRUE(polygon.isNear(polygon, 0.0)) ;

    }

    // Near tolerance (large)

    {

        const Polygon firstPolygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;
        const Polygon secondPolygon = { { { 0.0 + 1.0, 0.0 }, { 1.0 + 1.0, 0.0 }, { 1.0, 1.0 + 1.0 }, { 0.0 + 1.0, 1.0 } } } ;

        EXPECT_FALSE(firstPolygon.isNear(secondPolygon, 0.5)) ;
        EXPECT_TRUE(firstPolygon.isNear(secondPolygon, 1.0)) ;
        EXPECT_TRUE(firstPolygon.isNear(secondPolygon, 2.0)) ;

    }

    // Near tolerance (small)

    {

        const Polygon firstPolygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;
        const Polygon secondPolygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 + 1e-15 }, { 0.0, 1.0 } } } ;

        EXPECT_FALSE(firstPolygon.isNear(secondPolygon, 1e-16)) ;
        // EXPECT_TRUE(firstPolygon.isNear(secondPolygon, 1e-15)) ; -> Not working due to round-off errors
        EXPECT_TRUE(firstPolygon.isNear(secondPolygon, 1e-14)) ;

    }

    // Undefined throws

    {

        const Polygon polygon =
        {
            {
                { 0.0, 0.0 },
                { 0.0, 1.0 },
                { 1.0, 1.0 },
                { 1.0, 0.0 }
            }
        } ;

        EXPECT_ANY_THROW(Polygon::Undefined().isNear(polygon, 0.0)) ;
        EXPECT_ANY_THROW(polygon.isNear(Polygon::Undefined(), 0.0)) ;
        EXPECT_ANY_THROW(polygon.isNear(polygon, Real::Undefined())) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, IntersectsPolygon)
{

    using ostk::core::ctnr::Tuple ;
    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d2::objects::Polygon ;

    {

        const Array<Tuple<Polygon, Polygon, bool>> testCases =
        {
            { Polygon { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } } }, Polygon { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } } }, true },
            { Polygon { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, Polygon { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, true },
            { Polygon { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, Polygon { { { 5.0, 0.0 }, { 5.0, 0.0 }, { 6.0, 6.0 }, { 0.0, 5.0 } } }, false },
            { Polygon { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, Polygon { { { 0.0, 0.0 }, { 0.5, 0.0 }, { 0.5, 0.5 }, { 0.0, 0.5 } } }, true },
            { Polygon { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, Polygon { { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } } }, true },
            { Polygon { { { 5.0, 0.0 }, { 5.0, 0.0 }, { 6.0, 6.0 }, { 0.0, 5.0 } } }, Polygon { { { 5.0, 0.0 }, { 5.0, 0.0 }, { 6.0, 6.0 }, { 0.0, 5.0 } } }, true },
            { Polygon { { { 5.0, 0.0 }, { 5.0, 0.0 }, { 6.0, 6.0 }, { 0.0, 5.0 } } }, Polygon { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, false },
            { Polygon { { { 5.0, 0.0 }, { 5.0, 0.0 }, { 6.0, 6.0 }, { 0.0, 5.0 } } }, Polygon { { { 0.0, 0.0 }, { 0.5, 0.0 }, { 0.5, 0.5 }, { 0.0, 0.5 } } }, false },
            { Polygon { { { 5.0, 0.0 }, { 5.0, 0.0 }, { 6.0, 6.0 }, { 0.0, 5.0 } } }, Polygon { { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } } }, false },
            { Polygon { { { 0.0, 0.0 }, { 0.5, 0.0 }, { 0.5, 0.5 }, { 0.0, 0.5 } } }, Polygon { { { 0.0, 0.0 }, { 0.5, 0.0 }, { 0.5, 0.5 }, { 0.0, 0.5 } } }, true },
            { Polygon { { { 0.0, 0.0 }, { 0.5, 0.0 }, { 0.5, 0.5 }, { 0.0, 0.5 } } }, Polygon { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, true },
            { Polygon { { { 0.0, 0.0 }, { 0.5, 0.0 }, { 0.5, 0.5 }, { 0.0, 0.5 } } }, Polygon { { { 5.0, 0.0 }, { 5.0, 0.0 }, { 6.0, 6.0 }, { 0.0, 5.0 } } }, false },
            { Polygon { { { 0.0, 0.0 }, { 0.5, 0.0 }, { 0.5, 0.5 }, { 0.0, 0.5 } } }, Polygon { { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } } }, true },
            { Polygon { { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } } }, Polygon { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, true },
            { Polygon { { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } } }, Polygon { { { 5.0, 0.0 }, { 5.0, 0.0 }, { 6.0, 6.0 }, { 0.0, 5.0 } } }, false },
            { Polygon { { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } } }, Polygon { { { 0.0, 0.0 }, { 0.5, 0.0 }, { 0.5, 0.5 }, { 0.0, 0.5 } } }, true },
        } ;

        for (const auto& testCase : testCases)
        {

            const Polygon& firstPolygon = std::get<0>(testCase) ;
            const Polygon& secondPolygon = std::get<1>(testCase) ;
            const bool result = std::get<2>(testCase) ;

            EXPECT_EQ(result, firstPolygon.intersects(secondPolygon)) ;

        }

    }

    {

        const Array<Polygon::Vertex> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Polygon polygon = { vertices } ;

        EXPECT_ANY_THROW(Polygon::Undefined().intersects(Polygon::Undefined())) ;
        EXPECT_ANY_THROW(polygon.intersects(Polygon::Undefined())) ;
        EXPECT_ANY_THROW(Polygon::Undefined().intersects(polygon)) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, ContainsPoint)
{

    using ostk::core::ctnr::Tuple ;
    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::Polygon ;

    {

        const Array<Tuple<Polygon, Point, bool>> testCases =
        {
            { Polygon { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } } }, { 0.0, 0.0 }, true },
            { Polygon { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } } }, { 0.0, 1.0 }, true },
            { Polygon { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } } }, { 1.0, 0.0 }, true },
            { Polygon { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } } }, { 1.0, 1.0 }, true },
            { Polygon { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } } }, { 0.5, 0.5 }, true },
            { Polygon { { { 0.0, 0.0 }, { 0.0, 5.0 }, { 5.0, 5.0 }, { 5.0, 0.0 } } }, { 2.5, 2.5 }, true },
            { Polygon { { { 0.0, 0.0 }, { 0.0, 5.0 }, { 5.0, 5.0 }, { 5.0, 0.0 } } }, { 1.0, 4.0 }, true },
            { Polygon { { { 0.0, 0.0 }, { 0.0, 5.0 }, { 5.0, 5.0 }, { 5.0, 0.0 } } }, { 4.0, 1.0 }, true },
            { Polygon { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } } }, { 0.0, 2.0 }, false },
            { Polygon { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } } }, { 2.0, 0.0 }, false },
            { Polygon { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } } }, { 2.0, 2.0 }, false },
            { Polygon { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } } }, { 0.0, 0.9999 }, true },
            { Polygon { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } } }, { 0.9999, 0.0 }, true },
            { Polygon { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } } }, { 0.0, 1.0001 }, false },
            { Polygon { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } } }, { 1.0001, 0.0 }, false },
            { Polygon { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } } }, { 0.9999, 0.9999 }, true },
            { Polygon { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } } }, { 1.0001, 1.0001 }, false },
            { Polygon { { { 1.49999970000006, 4.0 }, { 2.49999970000006, 4.0 }, { 2.49999970000006, 3.0 }, { 1.49999970000006, 3.0 } } }, { 1.49999970000006, 4.0 }, true }
        } ;

        for (const auto& testCase : testCases)
        {

            const Polygon& polygon = std::get<0>(testCase) ;
            const Point& point = std::get<1>(testCase) ;
            const bool result = std::get<2>(testCase) ;

            EXPECT_EQ(result, polygon.contains(point)) ;

        }

    }

    {

        const Array<Polygon::Vertex> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Polygon polygon = { vertices } ;

        EXPECT_ANY_THROW(Polygon::Undefined().contains(Point::Undefined())) ;
        EXPECT_ANY_THROW(polygon.contains(Point::Undefined())) ;
        EXPECT_ANY_THROW(Polygon::Undefined().contains({ 0.0, 0.0 })) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, ContainsPointSet)
{

    using ostk::core::ctnr::Tuple ;
    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d2::objects::PointSet ;
    using ostk::math::geom::d2::objects::Polygon ;

    {

        const Array<Tuple<Polygon, PointSet, bool>> testCases =
        {
            { Polygon { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } } }, PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 } }), true },
            { Polygon { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } } }, PointSet({ { 0.0, 1.0 }, { 1.0, 0.0 } }), true },
            { Polygon { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } } }, PointSet({ { 1.0, 0.0 }, { 1.0, 1.0 } }), true },
            { Polygon { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } } }, PointSet({ { 1.0, 0.0 }, { 2.0, 2.0 } }), false },
            { Polygon { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } } }, PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } }), true },
            { Polygon { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } } }, PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 2.0, 0.0 } }), false },
            { Polygon { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } } }, PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 2.0, 2.0 }, { 2.0, 0.0 } }), false },
        } ;

        for (const auto& testCase : testCases)
        {

            const Polygon& polygon = std::get<0>(testCase) ;
            const PointSet& pointSet = std::get<1>(testCase) ;
            const bool result = std::get<2>(testCase) ;

            EXPECT_EQ(result, polygon.contains(pointSet)) ;

        }

    }

    {

        const Array<Polygon::Vertex> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        const Polygon polygon = { vertices } ;

        EXPECT_ANY_THROW(Polygon::Undefined().contains(PointSet::Empty())) ;
        EXPECT_ANY_THROW(polygon.contains(PointSet::Empty())) ;
        EXPECT_ANY_THROW(Polygon::Undefined().contains(PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 } }))) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, GetInnerRingCount)
{

    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d2::objects::Polygon ;

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

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, GetEdgeCount)
{

    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d2::objects::Polygon ;

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

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, GetVertexCount)
{

    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d2::objects::Polygon ;

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

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, GetOuterRing)
{

    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d2::objects::Polygon ;

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

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, GetInnerRingAt)
{

    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d2::objects::Polygon ;

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
                { 0.5, 0.0 },
                { 0.5, 0.5 },
                { 0.0, 0.5 },
                { 0.0, 0.0 }
            }
        } ;

        EXPECT_EQ(referenceFirstInnerRing, polygon.getInnerRingAt(0)) ;

        const Polygon::Ring referenceSecondInnerRing =
        {
            {
                { 0.0, 0.0 },
                { 0.1, 0.0 },
                { 0.1, 0.1 },
                { 0.0, 0.1 },
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

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, GetEdgeAt)
{

    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d2::objects::Polygon ;

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

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, GetVertexAt)
{

    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d2::objects::Polygon ;

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

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, GetEdges)
{

    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d2::objects::Polygon ;

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

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, GetVertices)
{

    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d2::objects::Polygon ;

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

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, GetConvexHull)
{

    using ostk::math::geom::d2::objects::Polygon ;

    {

        // Convex hull of convex polygon

        {

            const Polygon polygon =
            {
                {
                    { 0.0, 0.0 },
                    { 0.0, 1.0 },
                    { 1.0, 1.0 },
                    { 1.0, 0.0 }
                }
            } ;

            const Polygon convexHull = polygon.getConvexHull() ;

            ASSERT_TRUE(convexHull == polygon) ;

        }

        // Convex hull of concave polygon

        {

            const Polygon polygon =
            {
                {
                    { 0.0, 0.0 },
                    { 0.5, 0.5 },
                    { 0.0, 1.0 },
                    { 1.0, 1.0 },
                    { 1.0, 0.0 }
                }
            } ;

            const Polygon convexHull = polygon.getConvexHull() ;

            const Polygon referencePolygon =
            {
                {
                    { 0.0, 0.0 },
                    { 0.0, 1.0 },
                    { 1.0, 1.0 },
                    { 1.0, 0.0 }
                }
            } ;

            ASSERT_TRUE(convexHull == referencePolygon) ;

        }

    }

    // Undefined throws

    {

        EXPECT_ANY_THROW(Polygon::Undefined().getConvexHull()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, IntersectionWith)
{

    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::LineString ;
    using ostk::math::geom::d2::objects::Polygon ;
    using ostk::math::geom::d2::Intersection ;

    // TBI: Intersection type to be improved

    // Polygon intersection between two intersecting simple convex polygons

    {

        const Polygon polygon_1 =
        {
            {
                { 0.0, 0.0 },
                { 0.0, 1.0 },
                { 1.0, 1.0 },
                { 1.0, 0.0 }
            }
        } ;

        const Polygon polygon_2 =
        {
            {
                { 0.5, 0.0 },
                { 0.5, 1.0 },
                { 1.5, 1.0 },
                { 1.5, 0.0 }
            }
        } ;

        Intersection intersection = polygon_1.intersectionWith(polygon_2) ;

        const Polygon referencePolygon =
        {
            {
                { 0.5, 1.0 },
                { 1.0, 1.0 },
                { 1.0, 0.0 },
                { 0.5, 0.0 }
            }
        } ;

        EXPECT_TRUE(intersection.isDefined()) ;
        EXPECT_FALSE(intersection.isEmpty()) ;
        EXPECT_TRUE(intersection.accessComposite().getObjectCount() == 1) ;
        EXPECT_TRUE(intersection.accessComposite().is<Polygon>()) ;
        EXPECT_TRUE(intersection.accessComposite().as<Polygon>() == referencePolygon) ;

    }

    // Check symmetry of intersection

    {

        const Polygon polygon_1 =
        {
            {
                { 0.0, 0.0 },
                { 0.0, 1.0 },
                { 1.0, 1.0 },
                { 1.0, 0.0 }
            }
        } ;

        const Polygon polygon_2 =
        {
            {
                { 0.5, 0.0 },
                { 0.5, 1.0 },
                { 1.5, 1.0 },
                { 1.5, 0.0 }
            }
        } ;

        Intersection intersection1 = polygon_1.intersectionWith(polygon_2) ;
        Intersection intersection2 = polygon_2.intersectionWith(polygon_1) ;

        EXPECT_TRUE(intersection1 == intersection2) ;

    }

    // Point intersection between two intersecting simple convex polygons

    {

        const Polygon polygon_1 =
        {
            {
                { 0.0, 0.0 },
                { 0.0, 1.0 },
                { 1.0, 1.0 },
                { 1.0, 0.0 }
            }
        } ;

        const Polygon polygon_2 =
        {
            {
                { 1.0, 1.0 },
                { 1.0, 2.0 },
                { 2.0, 2.0 },
                { 2.0, 1.0 }
            }
        } ;

        Intersection intersection = polygon_1.intersectionWith(polygon_2) ;

        EXPECT_TRUE(intersection.isDefined()) ;
        EXPECT_TRUE(intersection.accessComposite().getObjectCount() == 1) ;
        EXPECT_TRUE(intersection.accessComposite().is<Point>()) ;

    }

    // Polygon intersection between 1 simple convex polygon and 1 complex polygon with one hole

    {

        const Polygon polygon_1 =
        {
            {
                { 0.0, 0.0 },
                { 0.0, 4.0 },
                { 4.0, 4.0 },
                { 4.0, 0.0 }
            },
            {
                {
                    { 1.0, 1.0 },
                    { 3.0, 1.0 },
                    { 3.0, 3.0 },
                    { 1.0, 3.0 }
                }
            }
        } ;

        const Polygon polygon_2 =
        {
            {
                { 0.0, -1.0 },
                { 0.0, 5.0 },
                { 2.5, 5.0 },
                { 2.5, -1.0 }
            }
        } ;

        Intersection intersection = polygon_1.intersectionWith(polygon_2) ;

        EXPECT_TRUE(intersection.isDefined()) ;
        EXPECT_FALSE(intersection.isEmpty()) ;
        EXPECT_TRUE(intersection.accessComposite().getObjectCount() == 1) ;
        EXPECT_TRUE(intersection.accessComposite().is<Polygon>()) ;

    }

    // Composite intersection between 1 simple convex polygon and 1 complex polygon with one hole

    {

        const Polygon polygon_1 =
        {
            {
                { 0.0, 0.0 },
                { 0.0, 4.0 },
                { 4.0, 4.0 },
                { 4.0, 0.0 }
            },
            {
                {
                    { 1.0, 1.0 },
                    { 3.0, 1.0 },
                    { 3.0, 3.0 },
                    { 1.0, 3.0 }
                }
            }
        } ;

        const Polygon polygon_2 =
        {
            {
                { 1.5, -1.0 },
                { 1.5, 5.0 },
                { 2.5, 5.0 },
                { 2.5, -1.0 }
            }
        } ;

        Intersection intersection = polygon_1.intersectionWith(polygon_2) ;

        EXPECT_TRUE(intersection.isDefined()) ;
        EXPECT_FALSE(intersection.isEmpty()) ;
        EXPECT_TRUE(intersection.accessComposite().getObjectCount() == 2) ;
        // EXPECT_TRUE(intersection.isComplex()) ;

    }

    // Intersection between two non-intersecting simple convex polygons

    {

        const Polygon polygon_1 =
        {
            {
                { 0.0, 0.0 },
                { 0.0, 1.0 },
                { 1.0, 1.0 },
                { 1.0, 0.0 }
            }
        } ;

        const Polygon polygon_2 =
        {
            {
                { 2.0, 0.0 },
                { 2.0, 1.0 },
                { 3.0, 1.0 },
                { 3.0, 0.0 }
            }
        } ;

        Intersection intersection = polygon_1.intersectionWith(polygon_2) ;

        EXPECT_TRUE(intersection.isDefined()) ;
        EXPECT_TRUE(intersection.isEmpty()) ;
        EXPECT_TRUE(intersection.accessComposite().getObjectCount() == 0) ;

    }

    // Line String intersection between two intersecting convex polygons

    {

        const Polygon polygon_1 =
        {
            {
                { 0.0, 0.0 },
                { 0.0, 1.0 },
                { 1.0, 1.0 },
                { 1.0, 0.0 }
            }
        } ;

        const Polygon polygon_2 =
        {
            {
                { 1.0, 0.0 },
                { 1.0, 1.0 },
                { 2.0, 1.0 },
                { 2.0, 0.0 }
            }
        } ;

        Intersection intersection = polygon_1.intersectionWith(polygon_2) ;

        EXPECT_TRUE(intersection.isDefined()) ;
        EXPECT_TRUE(intersection.accessComposite().getObjectCount() == 1) ;
        // EXPECT_TRUE(intersection.accessComposite().is<LineString>()) ;

    }

    // Polygon intersection between two intersecting non-convex polygons

    {

        const Polygon polygon_1 =
        {
            {
                { 2.0, 1.3 },
                { 2.4, 1.7 },
                { 2.8, 1.8 },
                { 3.4, 1.2 },
                { 3.7, 1.6 },
                { 3.4, 2.0 },
                { 4.1, 3.0 },
                { 5.3, 2.6 },
                { 5.4, 1.2 },
                { 4.9, 0.8 },
                { 2.9, 0.7 },
                { 2.0, 1.3 }
            },
            {
                {
                    { 4.0, 2.0 },
                    { 4.2, 1.4 },
                    { 4.8, 1.9 },
                    { 4.4, 2.2 },
                    { 4.0, 2.0 }
                }
            }
        } ;

        const Polygon polygon_2 =
        {
            {
                { 4.0, -0.5 },
                { 3.5, 1.0 },
                { 2.0, 1.5 },
                { 3.5, 2.0 },
                { 4.0, 3.5 },
                { 4.5, 2.0 },
                { 6.0, 1.5 },
                { 4.5, 1.0 },
                { 4.0, -0.5}
            }
        } ;

        Intersection intersection = polygon_1.intersectionWith(polygon_2) ;

        EXPECT_TRUE(intersection.isDefined()) ;
        EXPECT_FALSE(intersection.isEmpty()) ;
        EXPECT_TRUE(intersection.accessComposite().getObjectCount() == 1) ;
        EXPECT_TRUE(intersection.accessComposite().is<Polygon>()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, DifferenceWith)
{

    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::LineString ;
    using ostk::math::geom::d2::objects::Polygon ;
    using ostk::math::geom::d2::Intersection ;

    // Polygon difference between two intersecting simple convex polygons

    {

        const Polygon polygon_1 =
        {
            {
                { -111.006, 45.042 },
                { -111.116, 41.046 },
                { -109.05, 37.055 },
                { -94.702, 37.09 },
                { -96.46, 45.921 },
                { -111.006, 45.042 }
            }
        } ;

        const Polygon polygon_2 =
        {
            {
                { -104.062, 40.947 },
                { -104.062, 45.461 },
                { -96.46, 45.921 },
                { -95.282, 40.006 },
                { -104.062, 40.947 }
            }
        } ;

        Intersection difference = polygon_1.differenceWith(polygon_2) ;

        EXPECT_TRUE(difference.isDefined()) ;
        EXPECT_FALSE(difference.isEmpty()) ;
        EXPECT_TRUE(difference.accessComposite().getObjectCount() == 1) ;
        EXPECT_TRUE(difference.accessComposite().is<Polygon>()) ;

    }

}


TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, UnionWith)
{

    using ostk::math::geom::d2::objects::Polygon ;

    {

        using ostk::core::ctnr::Array ;

        using ostk::math::geom::d2::objects::MultiPolygon ;

        // Union with itself

        {

            const Array<Polygon::Vertex> vertices =
            {
                { 0.0, 0.0 },
                { 0.0, 1.0 },
                { 1.0, 1.0 },
                { 1.0, 0.0 }
            } ;

            const Polygon polygon = { vertices } ;

            const MultiPolygon unionMultiPolygon = polygon.unionWith(polygon) ;

            ASSERT_EQ(unionMultiPolygon.getPolygonCount(), 1) ;

            const Polygon unionPolygon = unionMultiPolygon.getPolygons().accessFirst() ;

            ASSERT_TRUE(unionPolygon == polygon) ;

        }

        // Union contains

        {

            const Polygon firstPolygon =
            {
                {
                    { 0.0, 0.0 },
                    { 0.0, 1.0 },
                    { 1.0, 1.0 },
                    { 1.0, 0.0 }
                }
            } ;

            const Polygon secondPolygon =
            {
                {
                    { 0.0, 0.0 },
                    { 0.0, 2.0 },
                    { 2.0, 2.0 },
                    { 2.0, 0.0 }
                }
            } ;

            const MultiPolygon unionMultiPolygon = firstPolygon.unionWith(secondPolygon) ;

            ASSERT_EQ(unionMultiPolygon.getPolygonCount(), 1) ;

            const Polygon unionPolygon = unionMultiPolygon.getPolygons().accessFirst() ;

            ASSERT_TRUE(unionPolygon == secondPolygon) ;

        }

        // Union overlap

        {

            const Polygon firstPolygon =
            {
                {
                    { 0.0, 0.0 },
                    { 0.0, 1.0 },
                    { 1.0, 1.0 },
                    { 1.0, 0.0 }
                }
            } ;

            const Polygon secondPolygon =
            {
                {
                    { 0.5, 0.5 },
                    { 0.5, 1.5 },
                    { 1.5, 1.5 },
                    { 1.5, 0.5 }
                }
            } ;

            const MultiPolygon unionMultiPolygon = firstPolygon.unionWith(secondPolygon) ;

            ASSERT_EQ(unionMultiPolygon.getPolygonCount(), 1) ;

            const Polygon unionPolygon = unionMultiPolygon.getPolygons().accessFirst() ;

            const Polygon referencePolygon =
            {
                {
                    { 0.5, 1.0 },
                    { 0.5, 1.5 },
                    { 1.5, 1.5 },
                    { 1.5, 0.5 },
                    { 1.0, 0.5 },
                    { 1.0, 0.0 },
                    { 0.0, 0.0 },
                    { 0.0, 1.0 }
                }
            } ;

            ASSERT_TRUE(unionPolygon.isNear(referencePolygon, 1e-6)) ;

        }

        // Union side-by-side

        {

            const Polygon firstPolygon =
            {
                {
                    { 0.0, 0.0 },
                    { 0.0, 1.0 },
                    { 1.0, 1.0 },
                    { 1.0, 0.0 }
                }
            } ;

            const Polygon secondPolygon =
            {
                {
                    { 1.0, 0.0 },
                    { 1.0, 1.0 },
                    { 2.0, 1.0 },
                    { 2.0, 0.0 }
                }
            } ;

            const MultiPolygon unionMultiPolygon = firstPolygon.unionWith(secondPolygon) ;

            ASSERT_EQ(unionMultiPolygon.getPolygonCount(), 1) ;

            const Polygon unionPolygon = unionMultiPolygon.getPolygons().accessFirst() ;

            const Polygon referencePolygon =
            {
                {
                    { 0.0, 0.0 },
                    { 0.0, 1.0 },
                    { 2.0, 1.0 },
                    { 2.0, 0.0 }
                }
            } ;

            ASSERT_TRUE(unionPolygon == referencePolygon) ;

        }

        // Union disjoint, vertex in common

        {

            const Polygon firstPolygon =
            {
                {
                    { 0.0, 0.0 },
                    { 0.0, 1.0 },
                    { 1.0, 1.0 },
                    { 1.0, 0.0 }
                }
            } ;

            const Polygon secondPolygon =
            {
                {
                    { 1.0, 1.0 },
                    { 1.0, 2.0 },
                    { 2.0, 2.0 },
                    { 2.0, 1.0 }
                }
            } ;

            const MultiPolygon unionMultiPolygon = firstPolygon.unionWith(secondPolygon) ;

            ASSERT_EQ(unionMultiPolygon.getPolygonCount(), 2) ;

            ASSERT_TRUE(unionMultiPolygon.getPolygons().accessFirst() == firstPolygon) ;
            ASSERT_TRUE(unionMultiPolygon.getPolygons().accessLast() == secondPolygon) ;

        }

        // Union disjoint

        {

            const Polygon firstPolygon =
            {
                {
                    { 0.0, 0.0 },
                    { 0.0, 1.0 },
                    { 1.0, 1.0 },
                    { 1.0, 0.0 }
                }
            } ;

            const Polygon secondPolygon =
            {
                {
                    { 2.0, 2.0 },
                    { 2.0, 3.0 },
                    { 3.0, 3.0 },
                    { 3.0, 2.0 }
                }
            } ;

            const MultiPolygon unionMultiPolygon = firstPolygon.unionWith(secondPolygon) ;

            ASSERT_EQ(unionMultiPolygon.getPolygonCount(), 2) ;

            ASSERT_TRUE(unionMultiPolygon.getPolygons().accessFirst() == firstPolygon) ;
            ASSERT_TRUE(unionMultiPolygon.getPolygons().accessLast() == secondPolygon) ;

        }

    }

    // Undefined throws

    {

        const Polygon polygon =
        {
            {
                { 0.0, 0.0 },
                { 0.0, 1.0 },
                { 1.0, 1.0 },
                { 1.0, 0.0 }
            }
        } ;

        EXPECT_ANY_THROW(Polygon::Undefined().unionWith(polygon)) ;
        EXPECT_ANY_THROW(polygon.unionWith(Polygon::Undefined())) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, ToString)
{

    using ostk::core::ctnr::Array ;

    using ostk::math::obj::Vector2d ;
    using ostk::math::geom::d2::objects::Polygon ;

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

        EXPECT_EQ("POLYGON((0 0,0 1,1 1,1 0,0 0),(0 0,0.5 0,0.5 0.5,0 0.5,0 0),(0 0,0.1 0,0.1 0.1,0 0.1,0 0))", Polygon(outerRing, innerRings).toString()) ;
        EXPECT_EQ("POLYGON((0 0,0 1,1 1,1 0,0 0),(0 0,0.5 0,0.5 0.5,0 0.5,0 0),(0 0,0.1 0,0.1 0.1,0 0.1,0 0))", Polygon(outerRing, innerRings).toString(Polygon::Format::Standard)) ;
        EXPECT_EQ("POLYGON((0 0,0 1,1 1,1 0,0 0),(0 0,0.5 0,0.5 0.5,0 0.5,0 0),(0 0,0.1 0,0.1 0.1,0 0.1,0 0))", Polygon(outerRing, innerRings).toString(Polygon::Format::WKT)) ;

    }

    {

        EXPECT_ANY_THROW(Polygon::Undefined().toString()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, ApplyTransformation)
{

    using ostk::core::ctnr::Array ;

    using ostk::math::obj::Vector2d ;
    using ostk::math::geom::d2::objects::Polygon ;
    using ostk::math::geom::d2::Transformation ;

    // Translation

    {

        const Array<Polygon::Vertex> vertices =
        {
            { 0.0, 0.0 },
            { 0.0, 1.0 },
            { 1.0, 1.0 },
            { 1.0, 0.0 }
        } ;

        Polygon polygon = { vertices } ;

        polygon.applyTransformation(Transformation::Translation({ 4.0, 5.0 })) ;

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

        EXPECT_ANY_THROW(Polygon::Undefined().applyTransformation(Transformation::Undefined())) ;
        EXPECT_ANY_THROW(Polygon::Undefined().applyTransformation(Transformation::Identity())) ;
        EXPECT_ANY_THROW(Polygon(vertices).applyTransformation(Transformation::Undefined())) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Polygon, Undefined)
{

    using ostk::math::geom::d2::objects::Polygon ;

    {

        EXPECT_NO_THROW(Polygon::Undefined()) ;
        EXPECT_FALSE(Polygon::Undefined().isDefined()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
