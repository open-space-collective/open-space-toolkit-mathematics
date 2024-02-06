/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Tuple.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/MultiPolygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Transformation.hpp>

#include <Global.test.hpp>

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon, Constructor)
// {

//     using ostk::core::ctnr::Array ;

//     using ostk::mathematics::geometry::d2::object::MultiPolygon ;

//     {

//         const Array<Polygon::Vertex> vertices =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         EXPECT_NO_THROW(Polygon polygon(vertices) ;) ;

//     }

//     {

//         const Array<Polygon::Vertex> outerRing =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         const Array<Array<Polygon::Vertex>> innerRings =
//         {
//             {
//                 { 0.0, 0.0 },
//                 { 0.0, 0.5 },
//                 { 0.5, 0.5 },
//                 { 0.5, 0.0 }
//             },
//             {
//                 { 0.0, 0.0 },
//                 { 0.0, 0.1 },
//                 { 0.1, 0.1 },
//                 { 0.1, 0.0 }
//             }
//         } ;

//         EXPECT_NO_THROW(Polygon polygon(outerRing, innerRings) ;) ;

//     }

//     {

//         EXPECT_NO_THROW(Polygon({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } })) ;

//     }

//     {

//         const Array<Polygon::Vertex> vertexArray = Array<Polygon::Vertex>::Empty() ;

//         EXPECT_NO_THROW(Polygon polygon(vertexArray) ;) ;

//     }

//     {

//         const Array<Polygon::Vertex> vertexArray = { { 0.0, 0.0 } } ;

//         EXPECT_ANY_THROW(Polygon polygon(vertexArray) ;) ;

//     }

//     {

//         const Array<Polygon::Vertex> vertexArray = { { 0.0, 0.0 }, { 0.0, 1.0 } } ;

//         EXPECT_ANY_THROW(Polygon polygon(vertexArray) ;) ;

//     }

//     {

//         const Array<Polygon::Vertex> outerRing =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         const Array<Array<Polygon::Vertex>> innerRings =
//         {
//             {
//                 { 0.0, 0.0 },
//                 { 0.0, 0.5 },
//                 { 0.5, 0.5 },
//                 { 0.5, 0.0 }
//             },
//             {
//                 { 0.0, 0.0 },
//                 { 0.0, 0.1 }
//             }
//         } ;

//         EXPECT_ANY_THROW(Polygon polygon(outerRing, innerRings) ;) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon, Clone)
// {

//     using ostk::core::ctnr::Array ;

//     using ostk::mathematics::geometry::d2::object::MultiPolygon ;

//     {

//         const Array<Polygon::Vertex> vertices =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         EXPECT_NO_THROW(const Polygon* polygonPtr = Polygon(vertices).clone() ; delete polygonPtr ;) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon, EqualToOperator)
// {

//     using ostk::core::ctnr::Array ;

//     using ostk::mathematics::geometry::d2::object::MultiPolygon ;

//     {

//         const Array<Polygon::Vertex> vertices =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         EXPECT_TRUE(Polygon(vertices) == Polygon(vertices)) ;

//     }

//     {

//         const Array<Polygon::Vertex> vertices_A =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         const Array<Polygon::Vertex> vertices_B =
//         {
//             { 1.0, 0.0 },
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 }
//         } ;

//         EXPECT_TRUE(Polygon(vertices_A) == Polygon(vertices_B)) ;

//     }

//     {

//         const Array<Polygon::Vertex> vertices_A =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         const Array<Polygon::Vertex> vertices_B =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 2.0 },
//             { 1.0, 0.0 }
//         } ;

//         EXPECT_FALSE(Polygon(vertices_A) == Polygon(vertices_B)) ;

//     }

//     {

//         const Array<Polygon::Vertex> vertices =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         EXPECT_FALSE(Polygon(vertices) == Polygon::Undefined()) ;
//         EXPECT_FALSE(Polygon::Undefined() == Polygon(vertices)) ;
//         EXPECT_FALSE(Polygon::Undefined() == Polygon::Undefined()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon, NotEqualToOperator)
// {

//     using ostk::core::ctnr::Array ;

//     using ostk::mathematics::geometry::d2::object::MultiPolygon ;

//     {

//         const Array<Polygon::Vertex> vertices =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         EXPECT_FALSE(Polygon(vertices) != Polygon(vertices)) ;

//     }

//     {

//         const Array<Polygon::Vertex> vertices_A =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         const Array<Polygon::Vertex> vertices_B =
//         {
//             { 1.0, 0.0 },
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 }
//         } ;

//         EXPECT_FALSE(Polygon(vertices_A) != Polygon(vertices_B)) ;

//     }

//     {

//         const Array<Polygon::Vertex> vertices_A =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         const Array<Polygon::Vertex> vertices_B =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 2.0 },
//             { 1.0, 0.0 }
//         } ;

//         EXPECT_TRUE(Polygon(vertices_A) != Polygon(vertices_B)) ;

//     }

//     {

//         const Array<Polygon::Vertex> vertices =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         EXPECT_TRUE(Polygon(vertices) != Polygon::Undefined()) ;
//         EXPECT_TRUE(Polygon::Undefined() != Polygon(vertices)) ;
//         EXPECT_TRUE(Polygon::Undefined() != Polygon::Undefined()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon, StreamOperator)
// {

//     using ostk::core::ctnr::Array ;

//     using ostk::mathematics::geometry::d2::object::MultiPolygon ;

//     {

//         testing::internal::CaptureStdout() ;

//         const Array<Polygon::Vertex> vertices =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         EXPECT_NO_THROW(std::cout << Polygon(vertices) << std::endl) ;

//         EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon, IsDefined)
// {

//     using ostk::core::ctnr::Array ;

//     using ostk::mathematics::geometry::d2::object::MultiPolygon ;

//     {

//         const Array<Polygon::Vertex> vertices =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         EXPECT_TRUE(Polygon(vertices).isDefined()) ;

//     }

//     {

//         EXPECT_FALSE(Polygon::Undefined().isDefined()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon, IntersectsPolygon)
// {

//     using ostk::core::ctnr::Tuple ;
//     using ostk::core::ctnr::Array ;

//     using ostk::mathematics::geometry::d2::object::MultiPolygon ;

//     {

//         const Array<Tuple<Polygon, Polygon, bool>> testCases =
//         {
//             { Polygon { { { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } } }, Polygon { { { 0.0, 0.0 }, {
//             0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 } } }, true }, { Polygon { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0
//             }, { 0.0, 1.0 } } }, Polygon { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, true }, {
//             Polygon { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, Polygon { { { 5.0, 0.0 }, { 5.0,
//             0.0 }, { 6.0, 6.0 }, { 0.0, 5.0 } } }, false }, { Polygon { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, {
//             0.0, 1.0 } } }, Polygon { { { 0.0, 0.0 }, { 0.5, 0.0 }, { 0.5, 0.5 }, { 0.0, 0.5 } } }, true }, { Polygon
//             { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, Polygon { { { 0.0, 0.0 }, { 0.0, 0.0 }, {
//             0.0, 0.0 }, { 0.0, 0.0 } } }, true }, { Polygon { { { 5.0, 0.0 }, { 5.0, 0.0 }, { 6.0, 6.0 }, { 0.0, 5.0
//             } } }, Polygon { { { 5.0, 0.0 }, { 5.0, 0.0 }, { 6.0, 6.0 }, { 0.0, 5.0 } } }, true }, { Polygon { {
//             { 5.0, 0.0 }, { 5.0, 0.0 }, { 6.0, 6.0 }, { 0.0, 5.0 } } }, Polygon { { { 0.0, 0.0 }, { 1.0, 0.0 },
//             { 1.0, 1.0 }, { 0.0, 1.0 } } }, false }, { Polygon { { { 5.0, 0.0 }, { 5.0, 0.0 }, { 6.0, 6.0 }, {
//             0.0, 5.0 } } }, Polygon { { { 0.0, 0.0 }, { 0.5, 0.0 }, { 0.5, 0.5 }, { 0.0, 0.5 } } }, false }, {
//             Polygon { { { 5.0, 0.0 }, { 5.0, 0.0 }, { 6.0, 6.0 }, { 0.0, 5.0 } } }, Polygon { { { 0.0, 0.0 }, { 0.0,
//             0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } } }, false }, { Polygon { { { 0.0, 0.0 }, { 0.5, 0.0 }, { 0.5, 0.5 }, {
//             0.0, 0.5 } } }, Polygon { { { 0.0, 0.0 }, { 0.5, 0.0 }, { 0.5, 0.5 }, { 0.0, 0.5 } } }, true }, { Polygon
//             { { { 0.0, 0.0 }, { 0.5, 0.0 }, { 0.5, 0.5 }, { 0.0, 0.5 } } }, Polygon { { { 0.0, 0.0 }, { 1.0, 0.0 },
//             { 1.0, 1.0 }, { 0.0, 1.0 } } }, true }, { Polygon { { { 0.0, 0.0 }, { 0.5, 0.0 }, { 0.5, 0.5 }, { 0.0,
//             0.5 } } }, Polygon { { { 5.0, 0.0 }, { 5.0, 0.0 }, { 6.0, 6.0 }, { 0.0, 5.0 } } }, false }, { Polygon { {
//             { 0.0, 0.0 }, { 0.5, 0.0 }, { 0.5, 0.5 }, { 0.0, 0.5 } } }, Polygon { { { 0.0, 0.0 }, { 0.0, 0.0 }, {
//             0.0, 0.0 }, { 0.0, 0.0 } } }, true }, { Polygon { { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0
//             } } }, Polygon { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, true }, { Polygon { { {
//             0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } } }, Polygon { { { 5.0, 0.0 }, { 5.0, 0.0 },
//             { 6.0, 6.0 }, { 0.0, 5.0 } } }, false }, { Polygon { { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0,
//             0.0 } } }, Polygon { { { 0.0, 0.0 }, { 0.5, 0.0 }, { 0.5, 0.5 }, { 0.0, 0.5 } } }, true },
//         } ;

//         for (const auto& testCase : testCases)
//         {

//             const Polygon& firstPolygon = std::get<0>(testCase) ;
//             const Polygon& secondPolygon = std::get<1>(testCase) ;
//             const bool result = std::get<2>(testCase) ;

//             EXPECT_EQ(result, firstPolygon.intersects(secondPolygon)) ;

//         }

//     }

//     {

//         const Array<Polygon::Vertex> vertices =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         const Polygon polygon = { vertices } ;

//         EXPECT_ANY_THROW(Polygon::Undefined().intersects(Polygon::Undefined())) ;
//         EXPECT_ANY_THROW(polygon.intersects(Polygon::Undefined())) ;
//         EXPECT_ANY_THROW(Polygon::Undefined().intersects(polygon)) ;

//     }

// }

// // TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon, ContainsPoint)
// // {

// //     using ostk::mathematics::geometry::d2::object::MultiPolygon ;

// //     {

// //         FAIL() ;

// //     }

// // }

// // TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon, ContainsPointSet)
// // {

// //     using ostk::mathematics::geometry::d2::object::MultiPolygon ;

// //     {

// //         FAIL() ;

// //     }

// // }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon, GetInnerRingCount)
// {

//     using ostk::core::ctnr::Array ;

//     using ostk::mathematics::geometry::d2::object::MultiPolygon ;

//     {

//         const Array<Polygon::Vertex> vertices =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         const Polygon polygon = { vertices } ;

//         EXPECT_EQ(0, polygon.getInnerRingCount()) ;

//     }

//     {

//         const Array<Polygon::Vertex> outerRing =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         const Array<Array<Polygon::Vertex>> innerRings =
//         {
//             {
//                 { 0.0, 0.0 },
//                 { 0.0, 0.5 },
//                 { 0.5, 0.5 },
//                 { 0.5, 0.0 }
//             },
//             {
//                 { 0.0, 0.0 },
//                 { 0.0, 0.1 },
//                 { 0.1, 0.1 },
//                 { 0.1, 0.0 }
//             }
//         } ;

//         const Polygon polygon = { outerRing, innerRings } ;

//         EXPECT_EQ(2, polygon.getInnerRingCount()) ;

//     }

//     {

//         EXPECT_ANY_THROW(Polygon::Undefined().getInnerRingCount()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon, GetEdgeCount)
// {

//     using ostk::core::ctnr::Array ;

//     using ostk::mathematics::geometry::d2::object::MultiPolygon ;

//     {

//         const Array<Polygon::Vertex> vertices =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         const Polygon polygon = { vertices } ;

//         EXPECT_EQ(4, polygon.getEdgeCount()) ;

//     }

//     {

//         const Array<Polygon::Vertex> outerRing =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         const Array<Array<Polygon::Vertex>> innerRings =
//         {
//             {
//                 { 0.0, 0.0 },
//                 { 0.0, 0.5 },
//                 { 0.5, 0.5 },
//                 { 0.5, 0.0 }
//             },
//             {
//                 { 0.0, 0.0 },
//                 { 0.0, 0.1 },
//                 { 0.1, 0.1 },
//                 { 0.1, 0.0 }
//             }
//         } ;

//         const Polygon polygon = { outerRing, innerRings } ;

//         EXPECT_EQ(12, polygon.getEdgeCount()) ;

//     }

//     {

//         EXPECT_ANY_THROW(Polygon::Undefined().getEdgeCount()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon, GetVertexCount)
// {

//     using ostk::core::ctnr::Array ;

//     using ostk::mathematics::geometry::d2::object::MultiPolygon ;

//     {

//         const Array<Polygon::Vertex> vertices =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         const Polygon polygon = { vertices } ;

//         EXPECT_EQ(4, polygon.getVertexCount()) ;

//     }

//     {

//         const Array<Polygon::Vertex> outerRing =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         const Array<Array<Polygon::Vertex>> innerRings =
//         {
//             {
//                 { 0.0, 0.0 },
//                 { 0.0, 0.5 },
//                 { 0.5, 0.5 },
//                 { 0.5, 0.0 }
//             },
//             {
//                 { 0.0, 0.0 },
//                 { 0.0, 0.1 },
//                 { 0.1, 0.1 },
//                 { 0.1, 0.0 }
//             }
//         } ;

//         const Polygon polygon = { outerRing, innerRings } ;

//         EXPECT_EQ(12, polygon.getVertexCount()) ;

//     }

//     {

//         EXPECT_ANY_THROW(Polygon::Undefined().getVertexCount()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon, GetOuterRing)
// {

//     using ostk::core::ctnr::Array ;

//     using ostk::mathematics::geometry::d2::object::MultiPolygon ;

//     {

//         const Array<Polygon::Vertex> vertices =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         const Polygon polygon = { vertices } ;

//         const Polygon::Ring referenceOuterRing =
//         {
//             {
//                 { 0.0, 0.0 },
//                 { 0.0, 1.0 },
//                 { 1.0, 1.0 },
//                 { 1.0, 0.0 },
//                 { 0.0, 0.0 }
//             }
//         } ;

//         EXPECT_EQ(referenceOuterRing, polygon.getOuterRing()) ;

//     }

//     {

//         const Array<Polygon::Vertex> outerRing =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         const Array<Array<Polygon::Vertex>> innerRings =
//         {
//             {
//                 { 0.0, 0.0 },
//                 { 0.0, 0.5 },
//                 { 0.5, 0.5 },
//                 { 0.5, 0.0 }
//             },
//             {
//                 { 0.0, 0.0 },
//                 { 0.0, 0.1 },
//                 { 0.1, 0.1 },
//                 { 0.1, 0.0 }
//             }
//         } ;

//         const Polygon polygon = { outerRing, innerRings } ;

//         const Polygon::Ring referenceOuterRing =
//         {
//             {
//                 { 0.0, 0.0 },
//                 { 0.0, 1.0 },
//                 { 1.0, 1.0 },
//                 { 1.0, 0.0 },
//                 { 0.0, 0.0 }
//             }
//         } ;

//         EXPECT_EQ(referenceOuterRing, polygon.getOuterRing()) ;

//     }

//     {

//         EXPECT_ANY_THROW(Polygon::Undefined().getOuterRing()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon, GetInnerRingAt)
// {

//     using ostk::core::ctnr::Array ;

//     using ostk::mathematics::geometry::d2::object::MultiPolygon ;

//     {

//         const Array<Polygon::Vertex> vertices =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         const Polygon polygon = { vertices } ;

//         EXPECT_ANY_THROW(polygon.getInnerRingAt(0)) ;

//     }

//     {

//         const Array<Polygon::Vertex> outerRing =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         const Array<Array<Polygon::Vertex>> innerRings =
//         {
//             {
//                 { 0.0, 0.0 },
//                 { 0.0, 0.5 },
//                 { 0.5, 0.5 },
//                 { 0.5, 0.0 }
//             },
//             {
//                 { 0.0, 0.0 },
//                 { 0.0, 0.1 },
//                 { 0.1, 0.1 },
//                 { 0.1, 0.0 }
//             }
//         } ;

//         const Polygon polygon = { outerRing, innerRings } ;

//         const Polygon::Ring referenceFirstInnerRing =
//         {
//             {
//                 { 0.0, 0.0 },
//                 { 0.0, 0.5 },
//                 { 0.5, 0.5 },
//                 { 0.5, 0.0 },
//                 { 0.0, 0.0 }
//             }
//         } ;

//         EXPECT_EQ(referenceFirstInnerRing, polygon.getInnerRingAt(0)) ;

//         const Polygon::Ring referenceSecondInnerRing =
//         {
//             {
//                 { 0.0, 0.0 },
//                 { 0.0, 0.1 },
//                 { 0.1, 0.1 },
//                 { 0.1, 0.0 },
//                 { 0.0, 0.0 }
//             }
//         } ;

//         EXPECT_EQ(referenceSecondInnerRing, polygon.getInnerRingAt(1)) ;

//         EXPECT_ANY_THROW(polygon.getInnerRingAt(2)) ;

//     }

//     {

//         EXPECT_ANY_THROW(Polygon::Undefined().getInnerRingAt(0)) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon, GetEdgeAt)
// {

//     using ostk::core::ctnr::Array ;

//     using ostk::mathematics::geometry::d2::object::MultiPolygon ;

//     {

//         const Array<Polygon::Vertex> vertices =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         const Polygon polygon = { vertices } ;

//         EXPECT_EQ(Polygon::Edge({ 0.0, 0.0 }, { 0.0, 1.0 }), polygon.getEdgeAt(0)) ;
//         EXPECT_EQ(Polygon::Edge({ 0.0, 1.0 }, { 1.0, 1.0 }), polygon.getEdgeAt(1)) ;
//         EXPECT_EQ(Polygon::Edge({ 1.0, 1.0 }, { 1.0, 0.0 }), polygon.getEdgeAt(2)) ;
//         EXPECT_EQ(Polygon::Edge({ 1.0, 0.0 }, { 0.0, 0.0 }), polygon.getEdgeAt(3)) ;

//         EXPECT_ANY_THROW(polygon.getEdgeAt(4)) ;

//     }

//     {

//         // [TBI] Inner ring support

//     }

//     {

//         EXPECT_ANY_THROW(Polygon::Undefined().getEdgeAt(0)) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon, GetVertexAt)
// {

//     using ostk::core::ctnr::Array ;

//     using ostk::mathematics::geometry::d2::object::MultiPolygon ;

//     {

//         const Array<Polygon::Vertex> vertices =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         const Polygon polygon = { vertices } ;

//         EXPECT_EQ(Polygon::Vertex(0.0, 0.0), polygon.getVertexAt(0)) ;
//         EXPECT_EQ(Polygon::Vertex(0.0, 1.0), polygon.getVertexAt(1)) ;
//         EXPECT_EQ(Polygon::Vertex(1.0, 1.0), polygon.getVertexAt(2)) ;
//         EXPECT_EQ(Polygon::Vertex(1.0, 0.0), polygon.getVertexAt(3)) ;

//         EXPECT_ANY_THROW(polygon.getVertexAt(4)) ;

//     }

//     {

//         // [TBI] Inner ring support

//     }

//     {

//         EXPECT_ANY_THROW(Polygon::Undefined().getVertexAt(0)) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon, GetEdges)
// {

//     using ostk::core::ctnr::Array ;

//     using ostk::mathematics::geometry::d2::object::MultiPolygon ;

//     {

//         const Array<Polygon::Vertex> vertices =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         const Polygon polygon = { vertices } ;

//         const Array<Polygon::Edge> referencePolygonEdges =
//         {
//             Polygon::Edge({ 0.0, 0.0 }, { 0.0, 1.0 }),
//             Polygon::Edge({ 0.0, 1.0 }, { 1.0, 1.0 }),
//             Polygon::Edge({ 1.0, 1.0 }, { 1.0, 0.0 }),
//             Polygon::Edge({ 1.0, 0.0 }, { 0.0, 0.0 })
//         } ;

//         EXPECT_EQ(referencePolygonEdges, polygon.getEdges()) ;

//     }

//     {

//         // [TBI] Inner ring support

//     }

//     {

//         EXPECT_ANY_THROW(Polygon::Undefined().getEdges()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon, GetVertices)
// {

//     using ostk::core::ctnr::Array ;

//     using ostk::mathematics::geometry::d2::object::MultiPolygon ;

//     {

//         const Array<Polygon::Vertex> vertices =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         EXPECT_EQ(vertices, Polygon(vertices).getVertices()) ;

//     }

//     {

//         EXPECT_ANY_THROW(Polygon::Undefined().getVertices()) ;

//     }

// }

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon, GetConvexHull)
{
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::MultiPolygon;

    {
        // Convex hull of convex polygon

        {
            const Polygon polygon = {{{0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}, {1.0, 0.0}}};

            const MultiPolygon multiPolygon = {{polygon}};

            const Polygon convexHull = multiPolygon.getConvexHull();

            ASSERT_TRUE(convexHull == polygon);
        }

        // Convex hull of concave polygon

        {
            const Polygon polygon = {{{0.0, 0.0}, {0.5, 0.5}, {0.0, 1.0}, {1.0, 1.0}, {1.0, 0.0}}};

            const MultiPolygon multiPolygon = {{polygon}};

            const Polygon convexHull = multiPolygon.getConvexHull();

            const Polygon referencePolygon = {{{0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}, {1.0, 0.0}}};

            ASSERT_TRUE(convexHull == referencePolygon);
        }

        // Convex hull of convex polygons

        {
            const MultiPolygon multiPolygon = {
                {Polygon {{{0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}, {1.0, 0.0}}},
                 Polygon {{{2.0, 2.0}, {2.0, 3.0}, {3.0, 3.0}, {3.0, 2.0}}}}
            };

            const Polygon convexHull = multiPolygon.getConvexHull();

            const Polygon referencePolygon = {{{0.0, 0.0}, {0.0, 1.0}, {2.0, 3.0}, {3.0, 3.0}, {3.0, 2.0}, {1.0, 0.0}}};

            ASSERT_TRUE(convexHull == referencePolygon);
        }

        // Convex hull of concave polygons

        {
            const MultiPolygon multiPolygon = {
                {Polygon {{{0.0, 0.0}, {0.5, 0.5}, {0.0, 1.0}, {1.0, 1.0}, {1.0, 0.0}}},
                 Polygon {{{2.0, 2.0}, {2.5, 2.5}, {2.0, 3.0}, {3.0, 3.0}, {3.0, 2.0}}}}
            };

            const Polygon convexHull = multiPolygon.getConvexHull();

            const Polygon referencePolygon = {{{0.0, 0.0}, {0.0, 1.0}, {2.0, 3.0}, {3.0, 3.0}, {3.0, 2.0}, {1.0, 0.0}}};

            ASSERT_TRUE(convexHull == referencePolygon);
        }
    }

    // Undefined throws

    {
        EXPECT_ANY_THROW(MultiPolygon::Undefined().getConvexHull());
    }
}

// // TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon, IntersectionWith)
// // {

// //     using ostk::mathematics::geometry::d2::object::MultiPolygon ;

// //     {

// //         FAIL() ;

// //     }

// // }

// // TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon, UnionWith)
// // {

// //     using ostk::mathematics::geometry::d2::object::MultiPolygon ;

// //     {

// //         FAIL() ;

// //     }

// // }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon, ToString)
// {

//     using ostk::core::ctnr::Array ;

//     using ostk::mathematics::object::Vector2d ;
//     using ostk::mathematics::geometry::d2::object::MultiPolygon ;

//     {

//         const Array<Polygon::Vertex> vertices =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         EXPECT_EQ("POLYGON((0 0,0 1,1 1,1 0,0 0))", Polygon(vertices).toString()) ;
//         EXPECT_EQ("POLYGON((0 0,0 1,1 1,1 0,0 0))", Polygon(vertices).toString(Polygon::Format::Standard)) ;
//         EXPECT_EQ("POLYGON((0 0,0 1,1 1,1 0,0 0))", Polygon(vertices).toString(Polygon::Format::WKT)) ;

//     }

//     {

//         const Array<Polygon::Vertex> vertices =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         EXPECT_EQ("POLYGON((0.0000000000
//         0.0000000000,0.0000000000 1.0000000000,1.0000000000 1.0000000000,1.0000000000 0.0000000000,0.0000000000
//         0.0000000000))", Polygon(vertices).toString(Polygon::Format::Standard, 10)) ;
//         EXPECT_EQ("POLYGON((0.0000000000
//         0.0000000000,0.0000000000 1.0000000000,1.0000000000 1.0000000000,1.0000000000 0.0000000000,0.0000000000
//         0.0000000000))", Polygon(vertices).toString(Polygon::Format::WKT, 10)) ;

//     }

//     {

//         const Array<Polygon::Vertex> outerRing =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         const Array<Array<Polygon::Vertex>> innerRings =
//         {
//             {
//                 { 0.0, 0.0 },
//                 { 0.0, 0.5 },
//                 { 0.5, 0.5 },
//                 { 0.5, 0.0 }
//             },
//             {
//                 { 0.0, 0.0 },
//                 { 0.0, 0.1 },
//                 { 0.1, 0.1 },
//                 { 0.1, 0.0 }
//             }
//         } ;

//         EXPECT_EQ("POLYGON((0 0,0 1,1 1,1 0,0 0),(0 0,0 0.5,0.5 0.5,0.5 0,0 0),(0 0,0 0.1,0.1 0.1,0.1 0,0 0))",
//         Polygon(outerRing, innerRings).toString()) ; EXPECT_EQ("POLYGON((0 0,0 1,1 1,1 0,0 0),(0 0,0 0.5,0.5 0.5,0.5
//         0,0 0),(0 0,0 0.1,0.1 0.1,0.1 0,0 0))", Polygon(outerRing, innerRings).toString(Polygon::Format::Standard)) ;
//         EXPECT_EQ("POLYGON((0 0,0 1,1 1,1 0,0 0),(0 0,0 0.5,0.5 0.5,0.5 0,0 0),(0 0,0 0.1,0.1 0.1,0.1 0,0 0))",
//         Polygon(outerRing, innerRings).toString(Polygon::Format::WKT)) ;

//     }

//     {

//         EXPECT_ANY_THROW(Polygon::Undefined().toString()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon, ApplyTransformation)
// {

//     using ostk::core::ctnr::Array ;

//     using ostk::mathematics::object::Vector2d ;
//     using ostk::mathematics::geometry::d2::object::MultiPolygon ;
//     using ostk::mathematics::geometry::d2::Transformation ;

//     // Translation

//     {

//         const Array<Polygon::Vertex> vertices =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         Polygon polygon = { vertices } ;

//         polygon.applyTransformation(Transformation::Translation({ 4.0, 5.0 })) ;

//         EXPECT_EQ(Polygon({ { 4.0, 5.0 }, { 4.0, 6.0 }, { 5.0, 6.0 }, { 5.0, 5.0 } }), polygon) ;

//     }

//     {

//         const Array<Polygon::Vertex> vertices =
//         {
//             { 0.0, 0.0 },
//             { 0.0, 1.0 },
//             { 1.0, 1.0 },
//             { 1.0, 0.0 }
//         } ;

//         EXPECT_ANY_THROW(Polygon::Undefined().applyTransformation(Transformation::Undefined())) ;
//         EXPECT_ANY_THROW(Polygon::Undefined().applyTransformation(Transformation::Identity())) ;
//         EXPECT_ANY_THROW(Polygon(vertices).applyTransformation(Transformation::Undefined())) ;

//     }

// }

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon, Undefined)
{
    using ostk::mathematics::geometry::d2::object::MultiPolygon;

    {
        EXPECT_NO_THROW(MultiPolygon::Undefined());
        EXPECT_FALSE(MultiPolygon::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon, Polygon)
{
    using ostk::core::ctnr::Array;

    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::MultiPolygon;

    {
        const Array<Polygon::Vertex> vertices = {{0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}, {1.0, 0.0}};

        const Polygon polygon = {vertices};

        EXPECT_NO_THROW(MultiPolygon::Polygon(polygon));
    }
}
