////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Line.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Sphere.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Line.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Line, Constructor)
{

    using ostk::math::geom::d3::objects::Line ;

    {

        EXPECT_NO_THROW(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 })) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Line, Clone)
{

    using ostk::math::geom::d3::objects::Line ;

    {

        EXPECT_NO_THROW(const Line* linePtr = Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).clone() ; delete linePtr ;) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Line, EqualToOperator)
{

    using ostk::math::geom::d3::objects::Line ;

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

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Line, NotEqualToOperator)
{

    using ostk::math::geom::d3::objects::Line ;

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

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Line, StreamOperator)
{

    using ostk::math::geom::d3::objects::Line ;

    {

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Line, IsDefined)
{

    using ostk::math::geom::d3::objects::Line ;

    {

        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).isDefined()) ;

    }

    {

        EXPECT_FALSE(Line::Undefined().isDefined()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Line, Intersects_Point)
{

    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Line ;

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

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Line, Intersects_Plane)
{

    using ostk::math::geom::d3::objects::Line ;
    using ostk::math::geom::d3::objects::Plane ;

    {

        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }).intersects(Plane({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }).intersects(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }).intersects(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }))) ;

        EXPECT_TRUE(Line({ 1.0, 2.0, 3.0 }, { 1.0, 0.0, 0.0 }).intersects(Plane({ 1.0, 2.0, 3.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(Line({ 1.0, 2.0, 3.0 }, { 1.0, 0.0, 0.0 }).intersects(Plane({ 1.0, 2.0, 3.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_TRUE(Line({ 1.0, 2.0, 3.0 }, { 1.0, 0.0, 0.0 }).intersects(Plane({ 1.0, 2.0, 3.0 }, { 0.0, 0.0, 1.0 }))) ;

        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }).intersects(Plane({ +1.0, +2.0, +3.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }).intersects(Plane({ -1.0, -2.0, -3.0 }, { 1.0, 0.0, 0.0 }))) ;

    }

    {

        EXPECT_FALSE(Line({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }).intersects(Plane({ +1.0, +2.0, +3.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_FALSE(Line({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }).intersects(Plane({ +1.0, +2.0, +3.0 }, { 0.0, 0.0, 1.0 }))) ;

        EXPECT_FALSE(Line({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }).intersects(Plane({ -1.0, -2.0, -3.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_FALSE(Line({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }).intersects(Plane({ -1.0, -2.0, -3.0 }, { 0.0, 0.0, 1.0 }))) ;

    }

    {

        EXPECT_ANY_THROW(Line::Undefined().intersects(Plane::Undefined())) ;
        EXPECT_ANY_THROW(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).intersects(Plane::Undefined())) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Line, Intersects_Sphere)
{

    using ostk::math::geom::d3::objects::Line ;
    using ostk::math::geom::d3::objects::Sphere ;

    {

        // See: OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Sphere.Intersects_Line

        SUCCEED() ;

    }

    {

        EXPECT_ANY_THROW(Line::Undefined().intersects(Sphere::Undefined())) ;
        EXPECT_ANY_THROW(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).intersects(Sphere::Undefined())) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Line, Intersects_Ellipsoid)
{

    using ostk::math::geom::d3::objects::Line ;
    using ostk::math::geom::d3::objects::Ellipsoid ;

    {

        // See: OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Ellipsoid.Intersects_Line

        SUCCEED() ;

    }

    {

        EXPECT_ANY_THROW(Line::Undefined().intersects(Ellipsoid::Undefined())) ;
        EXPECT_ANY_THROW(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).intersects(Ellipsoid::Undefined())) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Line, Contains_Point)
{

    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Line ;

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

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Line, Contains_PointSet)
{

    using ostk::math::geom::d3::objects::PointSet ;
    using ostk::math::geom::d3::objects::Line ;

    {

        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(PointSet({ { 0.0, 0.0, -2.0 } }))) ;
        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(PointSet({ { 0.0, 0.0, -1.0 } }))) ;
        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(PointSet({ { 0.0, 0.0, -0.5 } }))) ;
        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(PointSet({ { 0.0, 0.0, +0.0 } }))) ;
        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(PointSet({ { 0.0, 0.0, +0.5 } }))) ;
        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(PointSet({ { 0.0, 0.0, +1.0 } }))) ;
        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(PointSet({ { 0.0, 0.0, +2.0 } }))) ;

        EXPECT_TRUE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(PointSet({ { 0.0, 0.0, -2.0 }, { 0.0, 0.0, -1.0 } }))) ;

    }

    {

        EXPECT_FALSE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(PointSet({ { 1.0, 0.0, 0.0 }}))) ;
        EXPECT_FALSE(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(PointSet({ { 0.0, 0.0, -2.0 }, { 1.0, 0.0, 0.0 }}))) ;

    }

    {

        EXPECT_ANY_THROW(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(PointSet::Empty())) ;
        EXPECT_ANY_THROW(Line::Undefined().contains(PointSet({ { 0.0, 0.0, 0.0 } }))) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Line, GetOrigin)
{

    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Line ;

    {

        EXPECT_EQ(Point(0.0, 0.0, 0.0), Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).getOrigin()) ;
        EXPECT_EQ(Point(0.0, 0.0, 1.0), Line({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 }).getOrigin()) ;

        EXPECT_EQ(Point(0.0, 0.0, -1.0), Line({ 0.0, 0.0, -1.0 }, { 0.0, 0.0, +1.0 }).getOrigin()) ;

    }

    {

        EXPECT_ANY_THROW(Line::Undefined().getOrigin()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Line, GetDirection)
{

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Line ;

    {

        EXPECT_EQ(Vector3d(0.0, 0.0, +1.0), Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, +2.0 }).getDirection()) ;
        EXPECT_EQ(Vector3d(0.0, 0.0, -1.0), Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, -2.0 }).getDirection()) ;

    }

    {

        EXPECT_ANY_THROW(Line::Undefined().getDirection()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Line, DistanceTo_Point)
{

    using ostk::core::types::Real ;

    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Line ;

    {

        EXPECT_EQ(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, +1.0 }).distanceTo({ 0.0, 0.0, 0.0 }), 0.0) ;
        EXPECT_EQ(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, +1.0 }).distanceTo({ 0.0, 0.0, +1.0 }), 0.0) ;
        EXPECT_EQ(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, +1.0 }).distanceTo({ 0.0, 0.0, -1.0 }), 0.0) ;
        EXPECT_EQ(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, +1.0 }).distanceTo({ 0.0, 0.0, +2.0 }), 0.0) ;
        EXPECT_EQ(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, +1.0 }).distanceTo({ 0.0, 0.0, -2.0 }), 0.0) ;

        EXPECT_EQ(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, -1.0 }).distanceTo({ 0.0, 0.0, 0.0 }), 0.0) ;
        EXPECT_EQ(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, -1.0 }).distanceTo({ 0.0, 0.0, +1.0 }), 0.0) ;
        EXPECT_EQ(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, -1.0 }).distanceTo({ 0.0, 0.0, -1.0 }), 0.0) ;
        EXPECT_EQ(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, -1.0 }).distanceTo({ 0.0, 0.0, +2.0 }), 0.0) ;
        EXPECT_EQ(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, -1.0 }).distanceTo({ 0.0, 0.0, -2.0 }), 0.0) ;

        EXPECT_EQ(Line({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, +1.0 }).distanceTo({ 0.0, 0.0, 0.0 }), 0.0) ;
        EXPECT_EQ(Line({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, +1.0 }).distanceTo({ 0.0, 0.0, +1.0 }), 0.0) ;
        EXPECT_EQ(Line({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, +1.0 }).distanceTo({ 0.0, 0.0, -1.0 }), 0.0) ;
        EXPECT_EQ(Line({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, +1.0 }).distanceTo({ 0.0, 0.0, +2.0 }), 0.0) ;
        EXPECT_EQ(Line({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, +1.0 }).distanceTo({ 0.0, 0.0, -2.0 }), 0.0) ;

        EXPECT_EQ(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, +1.0 }).distanceTo({ 1.0, 0.0, 0.0 }), 1.0) ;
        EXPECT_EQ(Line({ 1.0, 0.0, 0.0 }, { 0.0, 0.0, +1.0 }).distanceTo({ 0.0, 0.0, 0.0 }), 1.0) ;
        EXPECT_EQ(Line({ 0.0, 1.0, 0.0 }, { 0.0, 0.0, +1.0 }).distanceTo({ 0.0, 0.0, 0.0 }), 1.0) ;

        EXPECT_EQ(Line({ 1.0, 0.0, 0.0 }, { 0.0, 0.0, +1.0 }).distanceTo({ 1.0, 0.0, 2.0 }), 0.0) ;

    }

    {

        EXPECT_NEAR(Line({ 1.0, 2.0, 3.0 }, { 4.0, 5.0, 6.0 }).distanceTo({ 7.0, 8.0, 9.0 }), 1.67487, 1e-5) ;

    }

    {

        EXPECT_ANY_THROW(Line::Undefined().distanceTo({ 0.0, 0.0, 0.0 })) ;
        EXPECT_ANY_THROW(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).distanceTo(Point::Undefined())) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Line, IntersectionWith_Plane)
{

    using ostk::core::types::Real ;

    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Line ;
    using ostk::math::geom::d3::objects::Plane ;
    using ostk::math::geom::d3::Intersection ;

    const auto expectLineIntersection =
    [] (const Line& aLine, const Plane& aPlane, const Line& anIntersectionLine) -> void
    {

        const Intersection intersection = aLine.intersectionWith(aPlane) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.accessComposite().is<Line>()) ;

        const Line line = intersection.accessComposite().as<Line>() ;

        EXPECT_EQ(anIntersectionLine, line) ;

    } ;

    const auto expectPointIntersection =
    [] (const Line& aLine, const Plane& aPlane, const Point& anIntersectionPoint) -> void
    {

        const Intersection intersection = aLine.intersectionWith(aPlane) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.accessComposite().is<Point>()) ;

        const Point point = intersection.accessComposite().as<Point>() ;

        EXPECT_TRUE(point.isNear(anIntersectionPoint, Real::Epsilon())) ;

    } ;

    const auto expectEmptyIntersection =
    [] (const Line& aLine, const Plane& aPlane) -> void
    {

        const Intersection intersection = aLine.intersectionWith(aPlane) ;

        EXPECT_TRUE(intersection.isDefined()) ;
        EXPECT_TRUE(intersection.isEmpty()) ;

    } ;

    {

        expectPointIntersection(Line({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }), Plane({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }), Point(0.0, 0.0, 0.0)) ;
        expectLineIntersection(Line({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }), Plane({ 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }), Line({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 })) ;
        expectLineIntersection(Line({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }), Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }), Line({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 })) ;

        expectPointIntersection(Line({ 1.0, 2.0, 3.0 }, { 1.0, 0.0, 0.0 }), Plane({ 1.0, 2.0, 3.0 }, { 1.0, 0.0, 0.0 }), Point(1.0, 2.0, 3.0)) ;
        expectLineIntersection(Line({ 1.0, 2.0, 3.0 }, { 1.0, 0.0, 0.0 }), Plane({ 1.0, 2.0, 3.0 }, { 0.0, 1.0, 0.0 }), Line({ 1.0, 2.0, 3.0 }, { 1.0, 0.0, 0.0 })) ;
        expectLineIntersection(Line({ 1.0, 2.0, 3.0 }, { 1.0, 0.0, 0.0 }), Plane({ 1.0, 2.0, 3.0 }, { 0.0, 0.0, 1.0 }), Line({ 1.0, 2.0, 3.0 }, { 1.0, 0.0, 0.0 })) ;

        expectPointIntersection(Line({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }), Plane({ +1.0, +2.0, +3.0 }, { 1.0, 0.0, 0.0 }), Point(+1.0, 0.0, 0.0)) ;
        expectPointIntersection(Line({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }), Plane({ -1.0, -2.0, -3.0 }, { 1.0, 0.0, 0.0 }), Point(-1.0, 0.0, 0.0)) ;

    }

    {

        expectEmptyIntersection(Line({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }), Plane({ +1.0, +2.0, +3.0 }, { 0.0, 1.0, 0.0 })) ;
        expectEmptyIntersection(Line({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }), Plane({ +1.0, +2.0, +3.0 }, { 0.0, 0.0, 1.0 })) ;

        expectEmptyIntersection(Line({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }), Plane({ -1.0, -2.0, -3.0 }, { 0.0, 1.0, 0.0 })) ;
        expectEmptyIntersection(Line({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }), Plane({ -1.0, -2.0, -3.0 }, { 0.0, 0.0, 1.0 })) ;

    }

    {

        EXPECT_ANY_THROW(Line::Undefined().intersectionWith(Plane::Undefined())) ;
        EXPECT_ANY_THROW(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).intersectionWith(Plane::Undefined())) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Line, ApplyTransformation)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::Angle ;
    using ostk::math::geom::d3::objects::Line ;
    using ostk::math::geom::d3::Transformation ;
    using ostk::math::geom::d3::trf::rot::RotationVector ;

    // Translation

    {

        Line line = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 } } ;

        line.applyTransformation(Transformation::Translation({ 4.0, 5.0, 6.0 })) ;

        EXPECT_EQ(Line({ 4.0, 5.0, 6.0 }, { 0.0, 0.0, 1.0 }), line) ;

    }

    // Rotation

    {

        Line line = { { 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;

        line.applyTransformation(Transformation::Rotation(RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(90.0)))) ;

        const Line referenceLine = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 } } ;

        EXPECT_TRUE(line.getOrigin().isNear(referenceLine.getOrigin(), Real::Epsilon())) ;
        EXPECT_TRUE(line.getDirection().isNear(referenceLine.getDirection(), Real::Epsilon())) ;

    }

    {

        EXPECT_ANY_THROW(Line::Undefined().applyTransformation(Transformation::Undefined())) ;
        EXPECT_ANY_THROW(Line::Undefined().applyTransformation(Transformation::Identity())) ;
        EXPECT_ANY_THROW(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).applyTransformation(Transformation::Undefined())) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Line, Undefined)
{

    using ostk::math::geom::d3::objects::Line ;

    {

        EXPECT_NO_THROW(Line::Undefined()) ;
        EXPECT_FALSE(Line::Undefined().isDefined()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Line, Points)
{

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Line ;

    {

        const Line line = Line::Points(Point(1.0, 2.0, 3.0), Point(2.0, 3.0, 4.0)) ;

        EXPECT_EQ(line.getOrigin(), Point(1.0, 2.0, 3.0)) ;
        EXPECT_NEAR((line.getDirection() - Vector3d(1.0, 1.0, 1.0).normalized()).norm(), 0.0, 1e-15) ;

    }

    {

        EXPECT_ANY_THROW(Line::Points(Point(1.0, 2.0, 3.0), Point(1.0, 2.0, 3.0))) ;

    }

    {

        EXPECT_ANY_THROW(Line::Points(Point::Undefined(), Point(2.0, 3.0, 4.0))) ;
        EXPECT_ANY_THROW(Line::Points(Point(1.0, 2.0, 3.0), Point::Undefined())) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
