////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Line.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Line.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Mathematics_Geometry_3D_Objects_Line, Constructor)
{

    using library::math::geom::d3::objects::Line ;

    {

        EXPECT_NO_THROW(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 })) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Line, Clone)
{

    using library::math::geom::d3::objects::Line ;

    {

        EXPECT_NO_THROW(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).clone()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Line, EqualToOperator)
{

    using library::math::geom::d3::objects::Line ;
    
    {

        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, +1.0 })) ;
        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, -1.0 })) ;

        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, +2.0 })) ;
        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, -2.0 })) ;

        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Line({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, +1.0 })) ;
        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Line({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, -1.0 })) ;

    }

    {

        EXPECT_FALSE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Line({ 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 })) ;

    }

    {

        EXPECT_FALSE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Line::Undefined()) ;
        EXPECT_FALSE(Line::Undefined() == Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 })) ;
        EXPECT_FALSE(Line::Undefined() == Line::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Line, NotEqualToOperator)
{

    using library::math::geom::d3::objects::Line ;

    {

        EXPECT_FALSE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, +1.0 })) ;
        EXPECT_FALSE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, -1.0 })) ;

        EXPECT_FALSE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, +2.0 })) ;
        EXPECT_FALSE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, -2.0 })) ;

        EXPECT_FALSE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Line({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, +1.0 })) ;
        EXPECT_FALSE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Line({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, -1.0 })) ;

    }

    {

        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Line({ 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 })) ;

    }

    {

        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Line::Undefined()) ;
        EXPECT_TRUE(Line::Undefined() != Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 })) ;
        EXPECT_TRUE(Line::Undefined() != Line::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Line, StreamOperator)
{

    using library::math::geom::d3::objects::Line ;
    
    {

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Line, IsDefined)
{

    using library::math::geom::d3::objects::Line ;
    
    {

        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).isDefined()) ;

    }

    {

        EXPECT_FALSE(Line::Undefined().isDefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Line, Intersects_Point)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Line ;

    {

        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).intersects(Point(0.0, 0.0, 0.0))) ;
        
        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).intersects(Point(0.0, 0.0, -1.0))) ;
        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).intersects(Point(0.0, 0.0, +1.0))) ;

        EXPECT_TRUE(Line({ 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).intersects(Point(1.0, 0.0, 0.0))) ;

        EXPECT_TRUE(Line({ 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).intersects(Point(1.0, 0.0, -1.0))) ;
        EXPECT_TRUE(Line({ 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).intersects(Point(1.0, 0.0, +1.0))) ;

    }

    {

        EXPECT_FALSE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).intersects(Point(1.0, 0.0, 0.0))) ;
        EXPECT_FALSE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).intersects(Point(0.0, 1.0, 0.0))) ;

    }

    {

        EXPECT_ANY_THROW(Line::Undefined().intersects(Point::Undefined())) ;
        EXPECT_ANY_THROW(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).intersects(Point::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Line, Intersects_Ellipsoid)
{

    using library::math::geom::d3::objects::Line ;
    using library::math::geom::d3::objects::Ellipsoid ;

    {

        // See: Library_Mathematics_Geometry_3D_Objects_Ellipsoid.Intersects_Line

        SUCCEED() ;

    }

    {

        EXPECT_ANY_THROW(Line::Undefined().intersects(Ellipsoid::Undefined())) ;
        EXPECT_ANY_THROW(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).intersects(Ellipsoid::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Line, Contains_Point)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Line ;

    {

        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 0.0, -2.0))) ;
        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 0.0, -1.0))) ;
        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 0.0, -0.5))) ;
        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 0.0, +0.0))) ;
        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 0.0, +0.5))) ;
        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 0.0, +1.0))) ;
        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 0.0, +2.0))) ;

    }

    {

        EXPECT_FALSE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(1.0, 0.0, 0.0))) ;

    }

    {

        EXPECT_ANY_THROW(Line::Undefined().contains(Point::Undefined())) ;
        EXPECT_ANY_THROW(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point::Undefined())) ;
        EXPECT_ANY_THROW(Line::Undefined().contains(Point(0.0, 0.0, 0.0))) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Line, GetOrigin)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Line ;
    
    {

        EXPECT_EQ(Point(0.0, 0.0, 0.0), Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).getOrigin()) ;
        EXPECT_EQ(Point(0.0, 0.0, 1.0), Line({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 }).getOrigin()) ;
        
        EXPECT_EQ(Point(0.0, 0.0, -1.0), Line({ 0.0, 0.0, -1.0 }, { 0.0, 0.0, +1.0 }).getOrigin()) ;

    }

    {

        EXPECT_ANY_THROW(Line::Undefined().getOrigin()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Line, GetDirection)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Line ;
    
    {

        EXPECT_EQ(Vector3d(0.0, 0.0, +1.0), Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, +2.0 }).getDirection()) ;
        EXPECT_EQ(Vector3d(0.0, 0.0, -1.0), Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, -2.0 }).getDirection()) ;

    }

    {

        EXPECT_ANY_THROW(Line::Undefined().getDirection()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Line, Translate)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::objects::Line ;

    {

        Line line = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 } } ;

        line.translate({ 4.0, 5.0, 6.0 }) ;

        EXPECT_EQ(Line({ 4.0, 5.0, 6.0 }, { 0.0, 0.0, 1.0 }), line) ;

    }

    {

        EXPECT_ANY_THROW(Line::Undefined().translate(Vector3d::Undefined())) ;
        EXPECT_ANY_THROW(Line::Undefined().translate({ 0.0, 0.0, 0.0 })) ;
        EXPECT_ANY_THROW(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).translate(Vector3d::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Line, Rotate)
{

    using library::core::types::Real ;

    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Line ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;

    {

        Line line = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 } } ;

        line.rotate(Quaternion::RotationVector(RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(90.0)))) ;

        const Line referenceLine = { { 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;

        EXPECT_TRUE(line.getOrigin().isNear(referenceLine.getOrigin(), Real::Epsilon())) ;
        EXPECT_TRUE(line.getDirection().isNear(referenceLine.getDirection(), Real::Epsilon())) ;

    }

    {

        EXPECT_ANY_THROW(Line::Undefined().rotate(Quaternion::Undefined())) ;
        EXPECT_ANY_THROW(Line::Undefined().rotate(Quaternion::Unit())) ;
        EXPECT_ANY_THROW(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).rotate(Quaternion::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Line, Undefined)
{

    using library::math::geom::d3::objects::Line ;
    
    {

        EXPECT_NO_THROW(Line::Undefined()) ;
        EXPECT_FALSE(Line::Undefined().isDefined()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////