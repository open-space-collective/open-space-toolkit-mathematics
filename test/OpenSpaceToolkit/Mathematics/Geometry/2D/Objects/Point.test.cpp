////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Point.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Point.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Point, Constructor)
{

    using ostk::math::geom::d2::objects::Point ;

    {

        EXPECT_NO_THROW(Point(1.0, 2.0)) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Point, Clone)
{

    using ostk::math::geom::d2::objects::Point ;

    {

        EXPECT_NO_THROW(const Point* pointPtr = Point(1.0, 2.0).clone() ; delete pointPtr ;) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Point, AdditionOperator)
{

    using ostk::math::obj::Vector2d ;
    using ostk::math::geom::d2::objects::Point ;

    {

        EXPECT_EQ(Point(1.0, 2.0), Point(1.0, 2.0) + Vector2d(0.0, 0.0)) ;
        EXPECT_EQ(Point(2.0, 2.0), Point(1.0, 2.0) + Vector2d(1.0, 0.0)) ;

    }

    {

        EXPECT_ANY_THROW(Point::Undefined() + Vector2d(0.0, 0.0)) ;
        EXPECT_ANY_THROW(Point(1.0, 2.0) + Vector2d::Undefined()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Point, SubtractionOperator)
{

    using ostk::math::obj::Vector2d ;
    using ostk::math::geom::d2::objects::Point ;

    {

        EXPECT_EQ(Point(1.0, 2.0), Point(1.0, 2.0) - Vector2d(0.0, 0.0)) ;
        EXPECT_EQ(Point(0.0, 2.0), Point(1.0, 2.0) - Vector2d(1.0, 0.0)) ;

    }

    {

        EXPECT_ANY_THROW(Point::Undefined() - Vector2d(0.0, 0.0)) ;
        EXPECT_ANY_THROW(Point(1.0, 2.0) - Vector2d::Undefined()) ;

    }

    {

        EXPECT_EQ(Vector2d(1.0, 2.0), Point(1.0, 2.0) - Point(0.0, 0.0)) ;
        EXPECT_EQ(Vector2d(0.0, 2.0), Point(1.0, 2.0) - Point(1.0, 0.0)) ;

    }

    {

        EXPECT_ANY_THROW(Point::Undefined() - Point(0.0, 0.0)) ;
        EXPECT_ANY_THROW(Point(1.0, 2.0) - Point::Undefined()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Point, EqualToOperator)
{

    using ostk::math::geom::d2::objects::Point ;

    {

        EXPECT_TRUE(Point(1.0, 2.0) == Point(1.0, 2.0)) ;

    }

    {

        EXPECT_FALSE(Point(1.0, 2.0) == Point(1.0, 3.0)) ;

    }

    {

        EXPECT_FALSE(Point(1.0, 2.0) == Point::Undefined()) ;
        EXPECT_FALSE(Point::Undefined() == Point(1.0, 2.0)) ;
        EXPECT_FALSE(Point::Undefined() == Point::Undefined()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Point, NotEqualToOperator)
{

    using ostk::math::geom::d2::objects::Point ;

    {

        EXPECT_TRUE(Point(1.0, 2.0) != Point(1.0, 3.0)) ;

    }

    {

        EXPECT_FALSE(Point(1.0, 2.0) != Point(1.0, 2.0)) ;

    }

    {

        EXPECT_TRUE(Point(1.0, 2.0) != Point::Undefined()) ;
        EXPECT_TRUE(Point::Undefined() != Point(1.0, 2.0)) ;
        EXPECT_TRUE(Point::Undefined() != Point::Undefined()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Point, StreamOperator)
{

    using ostk::math::geom::d2::objects::Point ;

    {

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << Point(1.0, 2.0) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Point, IsDefined)
{

    using ostk::math::geom::d2::objects::Point ;

    {

        EXPECT_TRUE(Point(0.0, 0.0).isDefined()) ;
        EXPECT_TRUE(Point(1.0, 2.0).isDefined()) ;

    }

    {

        EXPECT_FALSE(Point::Undefined().isDefined()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Point, IsNear)
{

    using ostk::core::types::Real ;

    using ostk::math::geom::d2::objects::Point ;

    {

        EXPECT_TRUE(Point(0.0, 0.0).isNear(Point(0.0, 0.0), 0.0)) ;
        EXPECT_TRUE(Point(0.0, 0.0).isNear(Point(0.0, 1e-15), 1e-15)) ;

        EXPECT_FALSE(Point(0.0, 0.0).isNear(Point(0.0, 1e-14), 1e-15)) ;

    }

    {

        EXPECT_ANY_THROW(Point::Undefined().isNear(Point::Undefined(), Real::Undefined())) ;
        EXPECT_ANY_THROW(Point(0.0, 0.0).isNear(Point::Undefined(), 1e-15)) ;
        EXPECT_ANY_THROW(Point::Undefined().isNear(Point(0.0, 0.0), 1e-15)) ;
        EXPECT_ANY_THROW(Point(0.0, 0.0).isNear(Point(0.0, 0.0), Real::Undefined())) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Point, AsVector)
{

    using ostk::math::obj::Vector2d ;
    using ostk::math::geom::d2::objects::Point ;

    {

        EXPECT_EQ(Vector2d(1.0, 2.0), Point(1.0, 2.0).asVector()) ;

    }

    {

        EXPECT_ANY_THROW(Point::Undefined().asVector()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Point, DistanceTo)
{

    using ostk::core::types::Real ;

    using ostk::math::geom::d2::objects::Point ;

    {

        EXPECT_EQ(0.0, Point(0.0, 0.0).distanceTo(Point(0.0, 0.0))) ;

        EXPECT_EQ(0.0, Point(+1.0, +1.0).distanceTo(Point(+1.0, +1.0))) ;
        EXPECT_EQ(0.0, Point(-1.0, -1.0).distanceTo(Point(-1.0, -1.0))) ;

        EXPECT_EQ(1.0, Point(0.0, 0.0).distanceTo(Point(+1.0, 0.0))) ;
        EXPECT_EQ(1.0, Point(0.0, 0.0).distanceTo(Point(0.0, +1.0))) ;

        EXPECT_EQ(1.0, Point(0.0, 0.0).distanceTo(Point(-1.0, 0.0))) ;
        EXPECT_EQ(1.0, Point(0.0, 0.0).distanceTo(Point(0.0, -1.0))) ;

        EXPECT_EQ(1.0, Point(+1.0, 0.0).distanceTo(Point(0.0, 0.0))) ;
        EXPECT_EQ(1.0, Point(0.0, +1.0).distanceTo(Point(0.0, 0.0))) ;

        EXPECT_EQ(1.0, Point(-1.0, 0.0).distanceTo(Point(0.0, 0.0))) ;
        EXPECT_EQ(1.0, Point(0.0, -1.0).distanceTo(Point(0.0, 0.0))) ;

        EXPECT_EQ(2.0, Point(0.0, 0.0).distanceTo(Point(+2.0, 0.0))) ;
        EXPECT_EQ(2.0, Point(0.0, 0.0).distanceTo(Point(0.0, +2.0))) ;

        EXPECT_EQ(2.0, Point(0.0, 0.0).distanceTo(Point(-2.0, 0.0))) ;
        EXPECT_EQ(2.0, Point(0.0, 0.0).distanceTo(Point(0.0, -2.0))) ;

        EXPECT_EQ(2.0, Point(+2.0, 0.0).distanceTo(Point(0.0, 0.0))) ;
        EXPECT_EQ(2.0, Point(0.0, +2.0).distanceTo(Point(0.0, 0.0))) ;

        EXPECT_EQ(2.0, Point(-2.0, 0.0).distanceTo(Point(0.0, 0.0))) ;
        EXPECT_EQ(2.0, Point(0.0, -2.0).distanceTo(Point(0.0, 0.0))) ;

    }

    {

        EXPECT_ANY_THROW(Point::Undefined().distanceTo(Point::Undefined())) ;
        EXPECT_ANY_THROW(Point(0.0, 0.0).distanceTo(Point::Undefined())) ;
        EXPECT_ANY_THROW(Point::Undefined().distanceTo(Point(0.0, 0.0))) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Point, ToString)
{

    using ostk::math::geom::d2::objects::Point ;

    {

        EXPECT_EQ("[1.0, 2.0]", Point(1.0, 2.0).toString()) ;
        EXPECT_EQ("[1.0, 2.0]", Point(1.0, 2.0).toString(Point::Format::Standard)) ;
        EXPECT_EQ("POINT(1.0 2.0)", Point(1.0, 2.0).toString(Point::Format::WKT)) ;

    }

    {

        EXPECT_EQ("[1.0000000000, 2.0000000000]", Point(1.0, 2.0).toString(Point::Format::Standard, 10)) ;
        EXPECT_EQ("POINT(1.0000000000 2.0000000000)", Point(1.0, 2.0).toString(Point::Format::WKT, 10)) ;

    }

    {

        EXPECT_ANY_THROW(Point::Undefined().toString()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Point, ApplyTransformation)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector2d ;
    using ostk::math::geom::Angle ;
    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::Transformation ;

    // Translation

    {

        Point point = { 1.0, 2.0 } ;

        point.applyTransformation(Transformation::Translation({ 4.0, 5.0 })) ;

        EXPECT_TRUE(point.isNear(Point(5.0, 7.0), Real::Epsilon())) << point ;

    }

    // Rotation

    {

        Point point = { +1.0, +2.0 } ;

        point.applyTransformation(Transformation::Rotation(Angle::Degrees(90.0))) ;

        EXPECT_TRUE(point.isNear(Point(-2.0, +1.0), Real::Epsilon())) << point ;

    }

    // Rotation Around

    {

        Point point = { +1.0, +2.0 } ;

        point.applyTransformation(Transformation::RotationAround(point, Angle::Degrees(90.0))) ;

        EXPECT_TRUE(point.isNear(Point(+1.0, +2.0), Real::Epsilon())) << point ;

    }

    {

        EXPECT_ANY_THROW(Point::Undefined().applyTransformation(Transformation::Undefined())) ;
        EXPECT_ANY_THROW(Point::Undefined().applyTransformation(Transformation::Identity())) ;
        EXPECT_ANY_THROW(Point(0.0, 0.0).applyTransformation(Transformation::Undefined())) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Point, Undefined)
{

    using ostk::math::geom::d2::objects::Point ;

    {

        EXPECT_NO_THROW(Point::Undefined()) ;
        EXPECT_FALSE(Point::Undefined().isDefined()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Point, Origin)
{

    using ostk::math::geom::d2::objects::Point ;

    {

        EXPECT_NO_THROW(Point::Origin()) ;
        EXPECT_EQ(Point(0.0, 0.0), Point::Origin()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_2D_Objects_Point, Vector)
{

    using ostk::math::obj::Vector2d ;
    using ostk::math::geom::d2::objects::Point ;

    {

        EXPECT_NO_THROW(Point::Vector(Vector2d(1.0, 2.0))) ;
        EXPECT_EQ(Point(1.0, 2.0), Point::Vector(Vector2d(1.0, 2.0))) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
