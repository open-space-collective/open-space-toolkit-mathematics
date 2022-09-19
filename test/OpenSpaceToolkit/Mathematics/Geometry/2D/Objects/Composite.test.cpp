////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Composite.test.cpp
/// @author         Remy Derollez <remy@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// #include <OpenSpaceToolkit/Mathematics/Geometry/2D/Intersection.hpp>
// #include <OpenSpaceToolkit/Mathematics/Geometry/2D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Composite.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Line.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/PointSet.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Point.hpp>

#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Composite, Constructor)
{

    using ostk::core::types::Unique ;
    using ostk::core::types::Real ;
    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d2::Object ;
    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::Polygon ;
    using ostk::math::geom::d2::objects::Composite ;

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;

        EXPECT_NO_THROW(Composite composite(polygon) ;) ;

    }

    {

        const Array<Point> outerRing = { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } ;
        const Array<Array<Point>> innerRings = Array<Array<Point>>::Empty() ;

        const Unique<Object> polygonUPtr = std::make_unique<Polygon>(outerRing, innerRings) ;

        EXPECT_NO_THROW(Composite composite(polygonUPtr) ;) ;

    }

    // {

    //     const Array<Point> outerRing = { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } ;
    //     const Array<Array<Point>> innerRings = Array<Array<Point>>::Empty() ;

    //     const Unique<Object> polygonUPtr = std::make_unique<Polygon>(outerRing, innerRings) ;

    //     const Real pointX = 0.0 ;
    //     const Real pointY = 0.0 ;

    //     Unique<Object> PointUPtr = std::make_unique<Point>(pointX, pointY) ;

    //     Array<Unique<Object>> objects = Array<Unique<Object>>::Empty() ;

    //     objects.emplace_back(std::move(polygonUPtr)) ;
    //     objects.emplace_back(std::move(PointUPtr)) ;

    //     EXPECT_NO_THROW(Composite composite(std::move(objects)) ;) ;

    // }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Composite, Clone)
{

    using ostk::math::geom::d2::Object ;
    using ostk::math::geom::d2::objects::Polygon ;
    using ostk::math::geom::d2::objects::Composite ;

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;

        EXPECT_NO_THROW(const Composite* compositePtr = Composite(polygon).clone() ; delete compositePtr ;) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Composite, CopyConstructor)
{

    using ostk::math::geom::d2::Object ;
    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::Polygon ;
    using ostk::math::geom::d2::objects::Composite ;

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;

        const Composite composite = Composite { polygon } ;

        EXPECT_NO_THROW(Composite otherComposite(composite) ;) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Composite, EqualToOperator)
{

    using ostk::core::types::Unique ;
    using ostk::core::types::Real ;
    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d2::Object ;
    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::Polygon ;
    using ostk::math::geom::d2::objects::Composite ;

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;

        const Composite composite = Composite { polygon } ;

        EXPECT_TRUE(composite == composite) ;

    }

    {

        // const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        // const Point apex = { 0.0, 0.0, 1.0 } ;

        // Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex) ;

        // const Point center = { 0.0, 0.0, 0.0 } ;
        // const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        // const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        // Unique<Object> cuboidUPtr = std::make_unique<Cuboid>(center, axes, extent) ;

        // Array<Unique<Object>> objects = Array<Unique<Object>>::Empty() ;

        // objects.emplace_back(std::move(pyramidUPtr)) ;
        // objects.emplace_back(std::move(cuboidUPtr)) ;

        // const Composite composite = Composite { std::move(objects) } ;

        // EXPECT_TRUE(composite == composite) ;

    }

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;

        const Composite composite = Composite { polygon } ;

        EXPECT_FALSE(Composite::Undefined() == Composite::Undefined()) ;
        EXPECT_FALSE(Composite::Undefined() == composite) ;
        EXPECT_FALSE(composite == Composite::Undefined()) ;

    }

}

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Composite, NotEqualToOperator)
// {

//     using ostk::core::types::Unique ;
//     using ostk::core::types::Real ;
//     using ostk::core::ctnr::Array ;

//     using ostk::math::obj::Vector3d ;
//     using ostk::math::geom::d2::Object ;
//     using ostk::math::geom::d2::objects::Point ;
//     using ostk::math::geom::d2::objects::Polygon ;
//     using ostk::math::geom::d2::objects::Cuboid ;
//     using ostk::math::geom::d2::objects::Pyramid ;
//     using ostk::math::geom::d2::objects::Composite ;

//     {

//         const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
//         const Point apex = { 0.0, 0.0, 1.0 } ;

//         const Pyramid pyramid = { base, apex } ;

//         const Composite composite = Composite { pyramid } ;

//         EXPECT_FALSE(composite != composite) ;

//     }

//     {

//         const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
//         const Point apex = { 0.0, 0.0, 1.0 } ;

//         Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex) ;

//         const Point center = { 0.0, 0.0, 0.0 } ;
//         const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
//         const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

//         Unique<Object> cuboidUPtr = std::make_unique<Cuboid>(center, axes, extent) ;

//         Array<Unique<Object>> objects = Array<Unique<Object>>::Empty() ;

//         objects.emplace_back(std::move(pyramidUPtr)) ;
//         objects.emplace_back(std::move(cuboidUPtr)) ;

//         const Composite composite = Composite { std::move(objects) } ;

//         EXPECT_FALSE(composite != composite) ;

//     }

//     {

//         const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
//         const Point apex = { 0.0, 0.0, 1.0 } ;

//         const Pyramid pyramid = { base, apex } ;

//         const Composite firstComposite = Composite { pyramid } ;

//         const Point center = { 0.0, 0.0, 0.0 } ;
//         const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
//         const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

//         const Cuboid cuboid = { center, axes, extent } ;

//         const Composite secondComposite = Composite { cuboid } ;

//         EXPECT_TRUE(firstComposite != secondComposite) ;

//     }

//     {

//         const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
//         const Point apex = { 0.0, 0.0, 1.0 } ;

//         const Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex) ;

//         const Point center = { 0.0, 0.0, 0.0 } ;
//         const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
//         const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

//         const Unique<Object> cuboidUPtr = std::make_unique<Cuboid>(center, axes, extent) ;

//         Array<Unique<Object>> firstObjects = Array<Unique<Object>>::Empty() ;

//         firstObjects.emplace_back(std::move(pyramidUPtr->clone())) ;
//         firstObjects.emplace_back(std::move(cuboidUPtr->clone())) ;

//         const Composite firstComposite = Composite { std::move(firstObjects) } ;

//         Array<Unique<Object>> secondObjects = Array<Unique<Object>>::Empty() ;

//         secondObjects.emplace_back(std::move(cuboidUPtr->clone())) ;
//         secondObjects.emplace_back(std::move(pyramidUPtr->clone())) ;

//         const Composite secondComposite = Composite { std::move(secondObjects) } ;

//         EXPECT_TRUE(firstComposite != secondComposite) ;

//     }

//     {

//         const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
//         const Point apex = { 0.0, 0.0, 1.0 } ;

//         const Pyramid pyramid = { base, apex } ;

//         const Composite composite = Composite { pyramid } ;

//         EXPECT_TRUE(Composite::Undefined() != Composite::Undefined()) ;
//         EXPECT_TRUE(Composite::Undefined() != composite) ;
//         EXPECT_TRUE(composite != Composite::Undefined()) ;

//     }

// }

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Composite, AdditionOperator)
{

    using ostk::core::types::Unique ;
    using ostk::core::types::Real ;
    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d2::Object ;
    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::Polygon ;
    using ostk::math::geom::d2::objects::Composite ;

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;

        const Composite composite = Composite { polygon } ;

        EXPECT_NO_THROW(composite + composite) ;

    }

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;

        const Composite composite = Composite { polygon } ;

        EXPECT_ANY_THROW(Composite::Undefined() + composite) ;
        EXPECT_ANY_THROW(composite + Composite::Undefined()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Composite, AdditionAssignmentOperator)
{

    using ostk::math::geom::d2::Object ;
    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::Polygon ;
    using ostk::math::geom::d2::objects::Composite ;

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;

        Composite composite = Composite { polygon } ;

        EXPECT_NO_THROW(composite += composite) ;

    }

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;

        Composite composite = Composite { polygon } ;

        EXPECT_ANY_THROW(Composite::Undefined() += composite) ;
        EXPECT_ANY_THROW(composite += Composite::Undefined()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Composite, StreamOperator)
{

    using ostk::math::geom::d2::Object ;
    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::Polygon ;
    using ostk::math::geom::d2::objects::Composite ;

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;

        const Composite composite = Composite { polygon } ;

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << composite << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Composite, IsDefined)
{

    using ostk::core::types::Real ;
    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d2::Object ;
    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::Polygon ;
    using ostk::math::geom::d2::objects::Composite ;

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;

        const Composite composite = Composite { polygon } ;

        EXPECT_TRUE(composite.isDefined()) ;

    }

    {

        EXPECT_FALSE(Composite::Undefined().isDefined()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Composite, IsEmpty)
{

    using ostk::core::types::Unique ;
    using ostk::core::types::Real ;
    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d2::Object ;
    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::Polygon ;
    using ostk::math::geom::d2::objects::Composite ;

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;

        const Composite composite = Composite { polygon } ;

        EXPECT_FALSE(composite.isEmpty()) ;

    }

    {

        EXPECT_TRUE(Composite::Empty().isEmpty()) ;

    }

    {

        EXPECT_ANY_THROW(Composite::Undefined().isEmpty()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Composite, Intersects)
{

    using ostk::math::geom::d2::objects::Polygon ;
    using ostk::math::geom::d2::objects::Composite ;

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;

        const Composite composite = Composite { polygon } ;

        EXPECT_ANY_THROW(Composite::Undefined().intersects(Composite::Undefined())) ;
        EXPECT_ANY_THROW(Composite::Undefined().intersects(composite)) ;
        EXPECT_ANY_THROW(composite.intersects(Composite::Undefined())) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Composite, Contains)
{

    using ostk::math::geom::d2::Object ;
    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::LineString ;
    using ostk::math::geom::d2::objects::Polygon ;
    using ostk::math::geom::d2::objects::Composite ;

    {

        const Point point = { 1.0, 0.0 } ;

        EXPECT_FALSE(Composite::Empty().contains(point)) ;

    }

    // Point contained in border of the Polygon as part of the Polygon definition

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;

        const Composite composite = Composite { polygon } ;

        const Point point = { 1.0, 0.0 } ;

        EXPECT_ANY_THROW(Composite::Undefined().contains(Composite::Undefined())) ;
        EXPECT_ANY_THROW(Composite::Undefined().contains(composite)) ;
        EXPECT_ANY_THROW(composite.contains(Composite::Undefined())) ;
        EXPECT_TRUE(composite.contains(point)) ;

    }

    // Point contained in border of the Polygon, not part of the Polygon definition

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;

        const Composite composite = Composite { polygon } ;

        const Point point = { 0.5, 0.0 } ;

        EXPECT_TRUE(composite.contains(point)) ;

    }

    // Point contained in the interior of the Polygon, not part of the Polygon definition

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;

        const Composite composite = Composite { polygon } ;

        const Point point = { 0.5, 0.5 } ;

        EXPECT_TRUE(composite.contains(point)) ;

    }

    // Point contained in the border of the Polygon, but not in the LineString

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;
        const LineString lineString = LineString({ { 2.0, 2.0 }, { 2.0, 3.0 } }) ;

        Composite composite = Composite { polygon } ;

        composite += Composite { lineString }  ;

        const Point point = { 1.0, 0.0 } ;

        EXPECT_FALSE(composite.contains(point)) ;

    }

    // Point contained in the border of the Polygon, but not in the LineString

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;
        const LineString lineString = LineString({ { 2.0, 2.0 }, { 2.0, 3.0 } }) ;

        Composite composite = Composite { polygon } ;

        composite += Composite { lineString }  ;

        const Point point = { 0.5, 0.0 } ;

        EXPECT_FALSE(composite.contains(point)) ;

    }

    // Point contained in the border of the Polygon, and in the LineString

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;
        const LineString lineString = LineString({ { 0.5, -1.0 }, { 0.5, 3.0 } }) ;

        Composite composite = Composite { polygon } ;

        composite += Composite { lineString }  ;

        const Point point = { 0.5, 0.0 } ;

        EXPECT_TRUE(composite.contains(point)) ;

    }

    // Point contained in the interior of the Polygon, and in the LineString

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;
        const LineString lineString = LineString({ { 0.5, -1.0 }, { 0.5, 3.0 } }) ;

        Composite composite = Composite { polygon } ;

        composite += Composite { lineString }  ;

        const Point point = { 0.5, 0.5 } ;

        EXPECT_TRUE(composite.contains(point)) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Composite, AnyContains)
{

    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::LineString ;
    using ostk::math::geom::d2::objects::Polygon ;
    using ostk::math::geom::d2::objects::Composite ;

    {

        const Point point = { 1.0, 0.0 } ;

        EXPECT_FALSE(Composite::Empty().anyContains(point)) ;

    }

    // Point contained in border of the Polygon as part of the Polygon definition

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;

        const Composite composite = Composite { polygon } ;

        const Point point = { 1.0, 0.0 } ;

        EXPECT_ANY_THROW(Composite::Undefined().contains(Composite::Undefined())) ;
        EXPECT_ANY_THROW(Composite::Undefined().contains(composite)) ;
        EXPECT_ANY_THROW(composite.contains(Composite::Undefined())) ;
        EXPECT_TRUE(composite.anyContains(point)) ;

    }

    // Point contained in border of the Polygon, not part of the Polygon definition

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;

        const Composite composite = Composite { polygon } ;

        const Point point = { 0.5, 0.0 } ;

        EXPECT_TRUE(composite.anyContains(point)) ;

    }

    // Point contained in the interior of the Polygon, not part of the Polygon definition

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;

        const Composite composite = Composite { polygon } ;

        const Point point = { 0.5, 0.5 } ;

        EXPECT_TRUE(composite.anyContains(point)) ;

    }

    // Point contained in the border of the Polygon, but not in the LineString

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;
        const LineString lineString = LineString({ { 2.0, 2.0 }, { 2.0, 3.0 } }) ;

        Composite composite = Composite { polygon } ;

        composite += Composite { lineString }  ;

        const Point point = { 1.0, 0.0 } ;

        EXPECT_TRUE(composite.anyContains(point)) ;

    }

    // Point contained in the border of the Polygon, but not in the LineString

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;
        const LineString lineString = LineString({ { 2.0, 2.0 }, { 2.0, 3.0 } }) ;

        Composite composite = Composite { polygon } ;

        composite += Composite { lineString }  ;

        const Point point = { 0.5, 0.0 } ;

        EXPECT_TRUE(composite.anyContains(point)) ;

    }

    // Point contained in the border of the Polygon, and in the LineString

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;
        const LineString lineString = LineString({ { 0.5, -1.0 }, { 0.5, 3.0 } }) ;

        Composite composite = Composite { polygon } ;

        composite += Composite { lineString }  ;

        const Point point = { 0.5, 0.0 } ;

        EXPECT_TRUE(composite.anyContains(point)) ;

    }

    // Point contained in the interior of the Polygon, and in the LineString

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;
        const LineString lineString = LineString({ { 0.5, -1.0 }, { 0.5, 3.0 } }) ;

        Composite composite = Composite { polygon } ;

        composite += Composite { lineString }  ;

        const Point point = { 0.5, 0.5 } ;

        EXPECT_TRUE(composite.anyContains(point)) ;

    }

    // Point not contained in the Polygon nor in the LineString

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;
        const LineString lineString = LineString({ { 0.5, -1.0 }, { 0.5, 3.0 } }) ;

        Composite composite = Composite { polygon } ;

        composite += Composite { lineString }  ;

        const Point point = { 5.0, 5.0 } ;

        EXPECT_FALSE(composite.anyContains(point)) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Composite, Is)
{

    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::Polygon ;
    using ostk::math::geom::d2::objects::Composite ;

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;

        const Composite composite = Composite { polygon } ;

        EXPECT_TRUE(composite.is<Polygon>()) ;

        EXPECT_FALSE(composite.is<Point>()) ;

    }

    {

        EXPECT_ANY_THROW(Composite::Undefined().is<Polygon>()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Composite, As)
{

    using ostk::math::geom::d2::Object ;
    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::Polygon ;
    using ostk::math::geom::d2::objects::Composite ;

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;

        const Composite composite = Composite { polygon } ;

        EXPECT_EQ(polygon, composite.as<Polygon>()) ;

        EXPECT_ANY_THROW(composite.as<Point>()) ;

    }

    {

        EXPECT_ANY_THROW(Composite::Undefined().as<Point>()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Composite, AccessObjectAt)
{

    using ostk::core::types::Unique ;
    using ostk::core::types::Real ;
    using ostk::core::ctnr::Array ;

    using ostk::math::geom::d2::Object ;
    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::Polygon ;
    using ostk::math::geom::d2::objects::Composite ;

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;

        const Composite composite = Composite { polygon } ;

        EXPECT_EQ(composite.accessObjectAt(0), polygon) ;
        EXPECT_ANY_THROW(composite.accessObjectAt(1)) ;

    }

    // {

    //     const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
    //     const Point apex = { 0.0, 0.0, 1.0 } ;

    //     Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex) ;

    //     const Point center = { 0.0, 0.0, 0.0 } ;
    //     const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
    //     const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

    //     Unique<Object> cuboidUPtr = std::make_unique<Cuboid>(center, axes, extent) ;

    //     Array<Unique<Object>> objects = Array<Unique<Object>>::Empty() ;

    //     objects.emplace_back(std::move(pyramidUPtr)) ;
    //     objects.emplace_back(std::move(cuboidUPtr)) ;

    //     const Composite composite = Composite { std::move(objects) } ;

    //     EXPECT_TRUE(composite.accessObjectAt(0).is<Pyramid>()) ;
    //     EXPECT_TRUE(composite.accessObjectAt(1).is<Cuboid>()) ;

    //     EXPECT_ANY_THROW(composite.accessObjectAt(2)) ;

    // }

    {

        EXPECT_ANY_THROW(Composite::Undefined().accessObjectAt(0)) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Composite, AccessObjects)
{

    using ostk::math::geom::d2::objects::Polygon ;
    using ostk::math::geom::d2::objects::Composite ;

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;

        const Composite composite = Composite { polygon } ;

        EXPECT_EQ(1, composite.accessObjects().getSize()) ;

    }

    // {

    //     const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
    //     const Point apex = { 0.0, 0.0, 1.0 } ;

    //     Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex) ;

    //     const Point center = { 0.0, 0.0, 0.0 } ;
    //     const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
    //     const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

    //     Unique<Object> cuboidUPtr = std::make_unique<Cuboid>(center, axes, extent) ;

    //     Array<Unique<Object>> objects = Array<Unique<Object>>::Empty() ;

    //     objects.emplace_back(std::move(pyramidUPtr)) ;
    //     objects.emplace_back(std::move(cuboidUPtr)) ;

    //     const Composite composite = Composite { std::move(objects) } ;

    //     EXPECT_EQ(2, composite.accessObjects().getSize()) ;

    // }

    {

        EXPECT_ANY_THROW(Composite::Undefined().accessObjects()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Composite, GetObjectCount)
{

    using ostk::math::geom::d2::objects::Polygon ;
    using ostk::math::geom::d2::objects::Composite ;

    {

        const Polygon polygon = { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } } ;

        const Composite composite = Composite { polygon } ;

        EXPECT_EQ(1, composite.getObjectCount()) ;

    }

    // {

    //     const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
    //     const Point apex = { 0.0, 0.0, 1.0 } ;

    //     Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex) ;

    //     const Point center = { 0.0, 0.0, 0.0 } ;
    //     const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
    //     const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

    //     Unique<Object> cuboidUPtr = std::make_unique<Cuboid>(center, axes, extent) ;

    //     Array<Unique<Object>> objects = Array<Unique<Object>>::Empty() ;

    //     objects.emplace_back(std::move(pyramidUPtr)) ;
    //     objects.emplace_back(std::move(cuboidUPtr)) ;

    //     const Composite composite = Composite { std::move(objects) } ;

    //     EXPECT_EQ(2, composite.getObjectCount()) ;

    // }

    {

        EXPECT_ANY_THROW(Composite::Undefined().getObjectCount()) ;

    }

}

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Composite, ConstIterator)
// {

//     using ostk::core::types::Unique ;
//     using ostk::core::types::Real ;
//     using ostk::core::ctnr::Array ;

//     using ostk::math::obj::Vector3d ;
//     using ostk::math::geom::d2::Object ;
//     using ostk::math::geom::d2::objects::Point ;
//     using ostk::math::geom::d2::objects::Polygon ;
//     using ostk::math::geom::d2::objects::Cuboid ;
//     using ostk::math::geom::d2::objects::Pyramid ;
//     using ostk::math::geom::d2::objects::Composite ;

//     {

//         const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
//         const Point apex = { 0.0, 0.0, 1.0 } ;

//         const Pyramid pyramid = { base, apex } ;

//         const Composite composite = Composite { pyramid } ;

//         EXPECT_NO_THROW
//         (

//             for (const auto& objectUPtr : composite)
//             {
//                 EXPECT_TRUE(objectUPtr->isDefined()) ;
//             }

//         ) ;

//     }

//     {

//         const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
//         const Point apex = { 0.0, 0.0, 1.0 } ;

//         Unique<Object> pyramidUPtr = std::make_unique<Pyramid>(base, apex) ;

//         const Point center = { 0.0, 0.0, 0.0 } ;
//         const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
//         const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

//         Unique<Object> cuboidUPtr = std::make_unique<Cuboid>(center, axes, extent) ;

//         Array<Unique<Object>> objects = Array<Unique<Object>>::Empty() ;

//         objects.emplace_back(std::move(pyramidUPtr)) ;
//         objects.emplace_back(std::move(cuboidUPtr)) ;

//         const Composite composite = Composite { std::move(objects) } ;

//         EXPECT_NO_THROW
//         (

//             for (const auto& objectUPtr : composite)
//             {
//                 EXPECT_TRUE(objectUPtr->isDefined()) ;
//             }

//         ) ;

//     }

//     {

//         EXPECT_ANY_THROW
//         (

//             for (const auto& objectUPtr : Composite::Undefined())
//             {
//                 (void) objectUPtr ;
//             }

//         ) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Composite, ApplyTransformation)
// {

//     using ostk::core::types::Unique ;
//     using ostk::core::types::Real ;
//     using ostk::core::ctnr::Array ;

//     using ostk::math::obj::Vector3d ;
//     using ostk::math::geom::d2::Object ;
//     using ostk::math::geom::d2::objects::Point ;
//     using ostk::math::geom::d2::objects::Polygon ;
//     using ostk::math::geom::d2::objects::Cuboid ;
//     using ostk::math::geom::d2::objects::Pyramid ;
//     using ostk::math::geom::d2::objects::Composite ;
//     using ostk::math::geom::d2::Transformation ;

//     {

//         const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
//         const Point apex = { 0.0, 0.0, 1.0 } ;

//         const Pyramid pyramid = { base, apex } ;

//         Composite composite = Composite { pyramid } ;

//         EXPECT_NO_THROW(composite.applyTransformation(Transformation::Identity())) ;

//     }

//     {

//         const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
//         const Point apex = { 0.0, 0.0, 1.0 } ;

//         const Pyramid pyramid = { base, apex } ;

//         Composite composite = Composite { pyramid } ;

//         EXPECT_ANY_THROW(composite.applyTransformation(Transformation::Undefined())) ;
//         EXPECT_ANY_THROW(Composite::Undefined().applyTransformation(Transformation::Undefined())) ;
//         EXPECT_ANY_THROW(Composite::Undefined().applyTransformation(Transformation::Identity())) ;


//     }

// }

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Composite, Undefined)
{

    using ostk::math::geom::d2::objects::Composite ;

    {

        EXPECT_NO_THROW(Composite::Undefined()) ;
        EXPECT_FALSE(Composite::Undefined().isDefined()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Composite, Empty)
{

    using ostk::math::geom::d2::objects::Composite ;

    {

        EXPECT_NO_THROW(Composite::Empty()) ;
        EXPECT_TRUE(Composite::Empty().isDefined()) ;
        EXPECT_TRUE(Composite::Empty().isEmpty()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
