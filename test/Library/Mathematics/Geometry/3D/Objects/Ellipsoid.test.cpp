////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Ellipsoid.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationMatrix.hpp>
#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/3D/Intersection.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Pyramid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Plane.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ray.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Line.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/PointSet.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Constructor)
{

    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::d3::objects::Ellipsoid ;

    {

        EXPECT_NO_THROW(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0)) ;

    }

    {

        EXPECT_NO_THROW(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0, Quaternion::XYZS(0.0, 0.0, 0.0, 1.0))) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Clone)
{

    using library::math::geom::d3::objects::Ellipsoid ;

    {

        EXPECT_NO_THROW(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).clone()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, EqualToOperator)
{

    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    
    {

        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) == Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0)) ;

    }

    {

        EXPECT_FALSE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) == Ellipsoid({ 1.0, 2.0, 4.0 }, 4.0, 5.0, 6.0)) ;
        EXPECT_FALSE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) == Ellipsoid({ 1.0, 2.0, 3.0 }, 3.0, 5.0, 6.0)) ;

    }

    {

        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) == Ellipsoid({ 1.0, 2.0, 3.0 }, 5.0, 4.0, 6.0, Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(+90.0))))) ;
        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) == Ellipsoid({ 1.0, 2.0, 3.0 }, 5.0, 4.0, 6.0, Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))))) ;

    }

    {

        EXPECT_FALSE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) == Ellipsoid::Undefined()) ;
        EXPECT_FALSE(Ellipsoid::Undefined() == Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0)) ;
        EXPECT_FALSE(Ellipsoid::Undefined() == Ellipsoid::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, NotEqualToOperator)
{

    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;

    {

        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) != Ellipsoid({ 1.0, 2.0, 4.0 }, 4.0, 5.0, 6.0)) ;
        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) != Ellipsoid({ 1.0, 2.0, 3.0 }, 3.0, 5.0, 6.0)) ;

    }

    {

        EXPECT_FALSE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) != Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0)) ;

    }

    {

        EXPECT_FALSE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) != Ellipsoid({ 1.0, 2.0, 3.0 }, 5.0, 4.0, 6.0, Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(+90.0))))) ;
        EXPECT_FALSE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) != Ellipsoid({ 1.0, 2.0, 3.0 }, 5.0, 4.0, 6.0, Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))))) ;

    }

    {

        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) != Ellipsoid::Undefined()) ;
        EXPECT_TRUE(Ellipsoid::Undefined() != Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0)) ;
        EXPECT_TRUE(Ellipsoid::Undefined() != Ellipsoid::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, StreamOperator)
{

    using library::math::geom::d3::objects::Ellipsoid ;
    
    {

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << Ellipsoid({ 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, IsDefined)
{

    using library::math::geom::d3::objects::Ellipsoid ;
    
    {

        EXPECT_TRUE(Ellipsoid({ 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0).isDefined()) ;
        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).isDefined()) ;

    }

    {

        EXPECT_FALSE(Ellipsoid::Undefined().isDefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Intersects_Point)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Ellipsoid ;

    {

        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).intersects(Point(+5.0, +2.0, +3.0))) ;
        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).intersects(Point(-3.0, +2.0, +3.0))) ;

        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).intersects(Point(+1.0, +7.0, +3.0))) ;
        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).intersects(Point(+1.0, -3.0, +3.0))) ;

        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).intersects(Point(+1.0, +2.0, +9.0))) ;
        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).intersects(Point(+1.0, +2.0, -3.0))) ;

    }

    {

        EXPECT_FALSE(Ellipsoid(Point::Origin(), 4.0, 5.0, 6.0).intersects(Point::Origin())) ;
        
    }

    {

        EXPECT_ANY_THROW(Ellipsoid::Undefined().intersects(Point::Undefined())) ;
        EXPECT_ANY_THROW(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).intersects(Point::Undefined())) ;
        EXPECT_ANY_THROW(Ellipsoid::Undefined().intersects(Point(0.0, 0.0, 0.0))) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Intersects_PointSet)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::PointSet ;
    using library::math::geom::d3::objects::Ellipsoid ;

    {

        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).intersects(PointSet({ { +5.0, +2.0, +3.0 }, { -3.0, +2.0, +3.0 }, { +1.0, +7.0, +3.0 }, { +1.0, -3.0, +3.0 }, { +1.0, +2.0, +9.0 }, { +1.0, +2.0, -3.0 } }))) ;
        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).intersects(PointSet({ { 0.0, 0.0, 0.0 }, { +1.0, +2.0, -3.0 } }))) ;

    }

    {

        EXPECT_FALSE(Ellipsoid(Point::Origin(), 4.0, 5.0, 6.0).intersects(PointSet::Empty())) ;
        
    }

    {

        EXPECT_ANY_THROW(Ellipsoid::Undefined().intersects(PointSet::Empty())) ;
        EXPECT_ANY_THROW(Ellipsoid::Undefined().intersects(PointSet({ { +5.0, +2.0, +3.0 }, { +5.0, +2.0, +3.0 } }))) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Intersects_Line)
{

    using library::core::types::Real ;

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Line ;
    using library::math::geom::d3::objects::Ellipsoid ;

    {

        const Ellipsoid ellipsoid = { Point::Origin(), 1.0, 2.0, 3.0 } ;

        EXPECT_FALSE(ellipsoid.intersects(Line({ -10.0, -3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ -10.0, -2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ -10.0, -2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ -10.0, -1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ -10.0, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ -10.0, +1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ -10.0, +2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ -10.0, +2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ -10.0, +3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Line({ +0.0, -3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ +0.0, -2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +0.0, -2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +0.0, -1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +0.0, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +0.0, +1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +0.0, +2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ +0.0, +2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ +0.0, +3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Line({ +10.0, -3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ +10.0, -2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +10.0, -2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +10.0, -1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +10.0, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +10.0, +1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +10.0, +2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ +10.0, +2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ +10.0, +3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Line({ -10.0, -3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ -10.0, -2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ -10.0, -2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ -10.0, -1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ -10.0, +0.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ -10.0, +1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ -10.0, +2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ -10.0, +2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ -10.0, +3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Line({ +0.0, -3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ +0.0, -2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +0.0, -2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +0.0, -1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +0.0, +0.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +0.0, +1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +0.0, +2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ +0.0, +2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ +0.0, +3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Line({ +10.0, -3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ +10.0, -2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +10.0, -2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +10.0, -1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +10.0, +0.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +10.0, +1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +10.0, +2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ +10.0, +2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ +10.0, +3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Line({ -2.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ -1.1, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ -1.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +0.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +1.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ +1.1, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ +2.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Line({ -2.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ -1.1, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ -1.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +0.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +1.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ +1.1, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ +2.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Line({ -2.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ -1.1, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ -1.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +0.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +1.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ +1.1, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ +2.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Line({ -2.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ -1.1, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ -1.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +0.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +1.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ +1.1, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ +2.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Line({ -2.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ -1.1, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ -1.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +0.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +1.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ +1.1, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ +2.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Line({ -2.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ -1.1, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ -1.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +0.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ +1.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ +1.1, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ +2.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;

    }

    {

        const Real equatorialRadius_m = 6378136.3 ;
        const Real polarRadius_m = equatorialRadius_m * (1.0 - 0.003352810664747) ;

        const Ellipsoid ellipsoid = { Point::Origin(), equatorialRadius_m, equatorialRadius_m, polarRadius_m } ;

        EXPECT_FALSE(ellipsoid.intersects(Line({ 0.0, -7000e3, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ 0.0, -equatorialRadius_m - 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        // EXPECT_TRUE(ellipsoid.intersects(Line({ 0.0, -equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ; // [TBI] Fix precision issues
        EXPECT_TRUE(ellipsoid.intersects(Line({ 0.0, -equatorialRadius_m + 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ 0.0, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Line({ 0.0, +equatorialRadius_m - 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        // EXPECT_TRUE(ellipsoid.intersects(Line({ 0.0, +equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ; // [TBI] Fix precision issues
        EXPECT_FALSE(ellipsoid.intersects(Line({ 0.0, +equatorialRadius_m + 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Line({ 0.0, +7000e3, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

    }

    {
        
        EXPECT_ANY_THROW(Ellipsoid::Undefined().intersects(Line::Undefined())) ;
        EXPECT_ANY_THROW(Ellipsoid(Point::Origin(), 1.0, 1.0, 1.0).intersects(Line::Undefined())) ;
        EXPECT_ANY_THROW(Ellipsoid::Undefined().intersects(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }))) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Intersects_Ray)
{

    using library::core::types::Real ;

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Ray ;
    using library::math::geom::d3::objects::Ellipsoid ;

    {

        const Ellipsoid ellipsoid = { Point::Origin(), 1.0, 2.0, 3.0 } ;

        EXPECT_FALSE(ellipsoid.intersects(Ray({ -10.0, -3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ -10.0, -2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ -10.0, -2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ -10.0, -1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ -10.0, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ -10.0, +1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ -10.0, +2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ -10.0, +2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ -10.0, +3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Ray({ +0.0, -3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +0.0, -2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ +0.0, -2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ +0.0, -1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ +0.0, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ +0.0, +1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ +0.0, +2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +0.0, +2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +0.0, +3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Ray({ +10.0, -3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +10.0, -2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +10.0, -2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +10.0, -1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +10.0, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +10.0, +1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +10.0, +2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +10.0, +2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +10.0, +3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Ray({ -10.0, -3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ -10.0, -2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ -10.0, -2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ -10.0, -1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ -10.0, +0.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ -10.0, +1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ -10.0, +2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ -10.0, +2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ -10.0, +3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Ray({ +0.0, -3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +0.0, -2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ +0.0, -2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ +0.0, -1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ +0.0, +0.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ +0.0, +1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ +0.0, +2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +0.0, +2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +0.0, +3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Ray({ +10.0, -3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +10.0, -2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ +10.0, -2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ +10.0, -1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ +10.0, +0.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ +10.0, +1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ +10.0, +2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +10.0, +2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +10.0, +3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Ray({ -2.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ -1.1, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ -1.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ +0.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ +1.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +1.1, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +2.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Ray({ -2.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ -1.1, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ -1.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ +0.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ +1.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +1.1, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +2.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Ray({ -2.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ -1.1, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ -1.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +0.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +1.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +1.1, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +2.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Ray({ -2.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ -1.1, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ -1.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +0.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +1.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +1.1, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +2.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Ray({ -2.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ -1.1, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ -1.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ +0.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ +1.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +1.1, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +2.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Ray({ -2.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ -1.1, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ -1.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ +0.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ +1.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +1.1, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +2.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;

    }

    {

        const Real equatorialRadius_m = 6378136.3 ;
        const Real polarRadius_m = equatorialRadius_m * (1.0 - 0.003352810664747) ;

        const Ellipsoid ellipsoid = { Point::Origin(), equatorialRadius_m, equatorialRadius_m, polarRadius_m } ;

        EXPECT_FALSE(ellipsoid.intersects(Ray({ -10000e3, -7000e3, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ -10000e3, -equatorialRadius_m - 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        // EXPECT_TRUE(ellipsoid.intersects(Ray({ -10000e3, -equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ; // [TBI] Fix precision issues
        EXPECT_TRUE(ellipsoid.intersects(Ray({ -10000e3, -equatorialRadius_m + 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ -10000e3, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ -10000e3, +equatorialRadius_m - 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        // EXPECT_TRUE(ellipsoid.intersects(Ray({ -10000e3, +equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ; // [TBI] Fix precision issues
        EXPECT_FALSE(ellipsoid.intersects(Ray({ -10000e3, +equatorialRadius_m + 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ -10000e3, +7000e3, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Ray({ 0.0, -7000e3, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ 0.0, -equatorialRadius_m - 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        // EXPECT_TRUE(ellipsoid.intersects(Ray({ 0.0, -equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ; // [TBI] Fix precision issues
        EXPECT_TRUE(ellipsoid.intersects(Ray({ 0.0, -equatorialRadius_m + 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ 0.0, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Ray({ 0.0, +equatorialRadius_m - 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        // EXPECT_TRUE(ellipsoid.intersects(Ray({ 0.0, +equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ; // [TBI] Fix precision issues
        EXPECT_FALSE(ellipsoid.intersects(Ray({ 0.0, +equatorialRadius_m + 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ 0.0, +7000e3, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Ray({ +10000e3, -7000e3, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +10000e3, -equatorialRadius_m - 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +10000e3, -equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +10000e3, -equatorialRadius_m + 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +10000e3, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +10000e3, +equatorialRadius_m - 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +10000e3, +equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +10000e3, +equatorialRadius_m + 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Ray({ +10000e3, +7000e3, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

    }

    {
        
        EXPECT_ANY_THROW(Ellipsoid::Undefined().intersects(Ray::Undefined())) ;
        EXPECT_ANY_THROW(Ellipsoid(Point::Origin(), 1.0, 1.0, 1.0).intersects(Ray::Undefined())) ;
        EXPECT_ANY_THROW(Ellipsoid::Undefined().intersects(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }))) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Intersects_Segment)
{

    using library::core::types::Real ;

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Segment ;
    using library::math::geom::d3::objects::Ellipsoid ;

    {

        const Ellipsoid ellipsoid = { Point::Origin(), 1.0, 2.0, 3.0 } ;

        EXPECT_FALSE(ellipsoid.intersects(Segment({ -10.0, -3.0, 0.0 }, { +10.0, -3.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Segment({ -10.0, -2.1, 0.0 }, { +10.0, -2.1, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -10.0, -2.0, 0.0 }, { +10.0, -2.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -10.0, -1.0, 0.0 }, { +10.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -10.0, +0.0, 0.0 }, { +10.0, +0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -10.0, +1.0, 0.0 }, { +10.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -10.0, +2.0, 0.0 }, { +10.0, +2.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Segment({ -10.0, +2.1, 0.0 }, { +10.0, +2.1, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Segment({ -10.0, +3.0, 0.0 }, { +10.0, +3.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Segment({ -2.0, -10.0, 0.0 }, { -2.0, +10.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Segment({ -1.1, -10.0, 0.0 }, { -1.1, +10.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -1.0, -10.0, 0.0 }, { -1.0, +10.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ +0.0, -10.0, 0.0 }, { +0.0, +10.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ +1.0, -10.0, 0.0 }, { +1.0, +10.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Segment({ +1.1, -10.0, 0.0 }, { +1.1, +10.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Segment({ +2.0, -10.0, 0.0 }, { +2.0, +10.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Segment({ -10.0, 0.0, -4.0 }, { +10.0, 0.0, -4.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Segment({ -10.0, 0.0, -3.1 }, { +10.0, 0.0, -3.1 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -10.0, 0.0, -3.0 }, { +10.0, 0.0, -3.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -10.0, 0.0, -2.0 }, { +10.0, 0.0, -2.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -10.0, 0.0, -1.0 }, { +10.0, 0.0, -1.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -10.0, 0.0, +0.0 }, { +10.0, 0.0, +0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -10.0, 0.0, +1.0 }, { +10.0, 0.0, +1.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -10.0, 0.0, +2.0 }, { +10.0, 0.0, +2.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -10.0, 0.0, +3.0 }, { +10.0, 0.0, +3.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Segment({ -10.0, 0.0, +3.1 }, { +10.0, 0.0, +3.1 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Segment({ -10.0, 0.0, +4.0 }, { +10.0, 0.0, +4.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Segment({ -10.0, 0.0, 0.0 }, { -1.1, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -10.0, 0.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -10.0, 0.0, 0.0 }, { -0.9, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ +10.0, 0.0, 0.0 }, { +0.9, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ +10.0, 0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Segment({ +10.0, 0.0, 0.0 }, { +1.1, 0.0, 0.0 }))) ;

    }

    {

        const Real equatorialRadius_m = 6378136.3 ;
        const Real polarRadius_m = equatorialRadius_m * (1.0 - 0.003352810664747) ;

        const Ellipsoid ellipsoid = { Point::Origin(), equatorialRadius_m, equatorialRadius_m, polarRadius_m } ;

        EXPECT_FALSE(ellipsoid.intersects(Segment({ -10000e3, -7000e3, 0.0 }, { +10000e3, -7000e3, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Segment({ -10000e3, -equatorialRadius_m - 0.1, 0.0 }, { +10000e3, -equatorialRadius_m - 0.1, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -10000e3, -equatorialRadius_m, 0.0 }, { +10000e3, -equatorialRadius_m, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -10000e3, -equatorialRadius_m + 0.1, 0.0 }, { +10000e3, -equatorialRadius_m + 0.1, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -10000e3, +0.0, 0.0 }, { +10000e3, +0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -10000e3, +equatorialRadius_m - 0.1, 0.0 }, { +10000e3, +equatorialRadius_m - 0.1, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -10000e3, +equatorialRadius_m, 0.0 }, { +10000e3, +equatorialRadius_m, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Segment({ -10000e3, +equatorialRadius_m + 0.1, 0.0 }, { +10000e3, +equatorialRadius_m + 0.1, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Segment({ -10000e3, +7000e3, 0.0 }, { +10000e3, +7000e3, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Segment({ -7000e3, -10000e3, 0.0 }, { -7000e3, +10000e3, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Segment({ -equatorialRadius_m - 0.1, -10000e3, 0.0 }, { -equatorialRadius_m - 0.1, +10000e3, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -equatorialRadius_m, -10000e3, 0.0 }, { -equatorialRadius_m, +10000e3, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -equatorialRadius_m + 0.1, -10000e3, 0.0 }, { -equatorialRadius_m + 0.1, +10000e3, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ +0.0, -10000e3, 0.0 }, { +0.0, +10000e3, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ +equatorialRadius_m - 0.1, -10000e3, 0.0 }, { +equatorialRadius_m - 0.1, +10000e3, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ +equatorialRadius_m, -10000e3, 0.0 }, { +equatorialRadius_m, +10000e3, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Segment({ +equatorialRadius_m + 0.1, -10000e3, 0.0 }, { +equatorialRadius_m + 0.1, +10000e3, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Segment({ +7000e3, -10000e3, 0.0 }, { +7000e3, +10000e3, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Segment({ -10000e3, 0.0, -7000e3 }, { +10000e3, 0.0, -7000e3 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Segment({ -10000e3, 0.0, -polarRadius_m - 0.1 }, { +10000e3, 0.0, -polarRadius_m - 0.1 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -10000e3, 0.0, -polarRadius_m }, { +10000e3, 0.0, -polarRadius_m }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -10000e3, 0.0, -polarRadius_m + 0.1 }, { +10000e3, 0.0, -polarRadius_m + 0.1 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -10000e3, 0.0, +0.0 }, { +10000e3, 0.0, +0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -10000e3, 0.0, +polarRadius_m - 0.1 }, { +10000e3, 0.0, +polarRadius_m - 0.1 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Segment({ -10000e3, 0.0, +polarRadius_m }, { +10000e3, 0.0, +polarRadius_m }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Segment({ -10000e3, 0.0, +polarRadius_m + 0.1 }, { +10000e3, 0.0, +polarRadius_m + 0.1 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Segment({ -10000e3, 0.0, +7000e3 }, { +10000e3, 0.0, +7000e3 }))) ;

    }

    {
        
        EXPECT_ANY_THROW(Ellipsoid(Point::Origin(), 1.0, 1.0, 1.0).intersects(Segment::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Intersects_Plane)
{

    using library::core::types::Real ;

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Plane ;
    using library::math::geom::d3::objects::Ellipsoid ;

    {

        const Ellipsoid ellipsoid = { Point::Origin(), 1.0, 2.0, 3.0 } ;

        EXPECT_TRUE(ellipsoid.intersects(Plane({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Plane({ -2.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Plane({ -1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Plane({ +0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Plane({ +1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Plane({ +2.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Plane({ 0.0, -3.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Plane({ 0.0, -2.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Plane({ 0.0, -1.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Plane({ 0.0, +0.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Plane({ 0.0, +1.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Plane({ 0.0, +2.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Plane({ 0.0, +3.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;

        EXPECT_FALSE(ellipsoid.intersects(Plane({ 0.0, 0.0, -4.0 }, { 0.0, 0.0, 1.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Plane({ 0.0, 0.0, -3.0 }, { 0.0, 0.0, 1.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Plane({ 0.0, 0.0, -2.0 }, { 0.0, 0.0, 1.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Plane({ 0.0, 0.0, -1.0 }, { 0.0, 0.0, 1.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Plane({ 0.0, 0.0, +0.0 }, { 0.0, 0.0, 1.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Plane({ 0.0, 0.0, +1.0 }, { 0.0, 0.0, 1.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Plane({ 0.0, 0.0, +2.0 }, { 0.0, 0.0, 1.0 }))) ;
        EXPECT_TRUE(ellipsoid.intersects(Plane({ 0.0, 0.0, +3.0 }, { 0.0, 0.0, 1.0 }))) ;
        EXPECT_FALSE(ellipsoid.intersects(Plane({ 0.0, 0.0, +4.0 }, { 0.0, 0.0, 1.0 }))) ;

    }

    {
        
        EXPECT_ANY_THROW(Ellipsoid::Undefined().intersects(Plane::Undefined())) ;
        EXPECT_ANY_THROW(Ellipsoid(Point::Origin(), 1.0, 1.0, 1.0).intersects(Plane::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Intersects_Pyramid)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::d3::objects::Pyramid ;

    {

        // See: Library_Mathematics_Geometry_3D_Objects_Pyramid.Intersects_Ellipsoid

        SUCCEED() ;

    }

    {

        EXPECT_ANY_THROW(Ellipsoid::Undefined().intersects(Pyramid::Undefined())) ;
        EXPECT_ANY_THROW(Ellipsoid(Point::Origin(), 1.0, 1.0, 1.0).intersects(Pyramid::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Contains_Point)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Ellipsoid ;

    {

        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).contains(Point(+5.0, +2.0, +3.0))) ;
        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).contains(Point(-3.0, +2.0, +3.0))) ;

        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).contains(Point(+1.0, +7.0, +3.0))) ;
        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).contains(Point(+1.0, -3.0, +3.0))) ;

        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).contains(Point(+1.0, +2.0, +9.0))) ;
        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).contains(Point(+1.0, +2.0, -3.0))) ;

    }

    {

        EXPECT_FALSE(Ellipsoid(Point::Origin(), 4.0, 5.0, 6.0).contains(Point::Origin())) ;
        
    }

    {

        EXPECT_ANY_THROW(Ellipsoid::Undefined().contains(Point::Undefined())) ;
        EXPECT_ANY_THROW(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).contains(Point::Undefined())) ;
        EXPECT_ANY_THROW(Ellipsoid::Undefined().contains(Point(0.0, 0.0, 0.0))) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Contains_PointSet)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::PointSet ;
    using library::math::geom::d3::objects::Ellipsoid ;

    {

        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).contains(PointSet({ { +5.0, +2.0, +3.0 }, { -3.0, +2.0, +3.0 }, { +1.0, +7.0, +3.0 }, { +1.0, -3.0, +3.0 }, { +1.0, +2.0, +9.0 }, { +1.0, +2.0, -3.0 } }))) ;

    }

    {

        EXPECT_FALSE(Ellipsoid(Point::Origin(), 4.0, 5.0, 6.0).contains(PointSet::Empty())) ;
        
    }

    {

        EXPECT_ANY_THROW(Ellipsoid::Undefined().contains(PointSet::Empty())) ;
        EXPECT_ANY_THROW(Ellipsoid::Undefined().contains(PointSet({ { +5.0, +2.0, +3.0 }, { +5.0, +2.0, +3.0 } }))) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, GetCenter)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Ellipsoid ;
    
    {

        EXPECT_EQ(Point(1.0, 2.0, 3.0), Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).getCenter()) ;

    }

    {

        EXPECT_ANY_THROW(Ellipsoid::Undefined().getCenter()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, GetFirstPrincipalSemiAxis)
{

    using library::math::geom::d3::objects::Ellipsoid ;
    
    {

        EXPECT_EQ(4.0, Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).getFirstPrincipalSemiAxis()) ;

    }

    {

        EXPECT_ANY_THROW(Ellipsoid::Undefined().getFirstPrincipalSemiAxis()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, GetSecondPrincipalSemiAxis)
{

    using library::math::geom::d3::objects::Ellipsoid ;
    
    {

        EXPECT_EQ(5.0, Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).getSecondPrincipalSemiAxis()) ;

    }

    {

        EXPECT_ANY_THROW(Ellipsoid::Undefined().getSecondPrincipalSemiAxis()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, GetThirdPrincipalSemiAxis)
{

    using library::math::geom::d3::objects::Ellipsoid ;
    
    {

        EXPECT_EQ(6.0, Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).getThirdPrincipalSemiAxis()) ;

    }

    {

        EXPECT_ANY_THROW(Ellipsoid::Undefined().getThirdPrincipalSemiAxis()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, GetFirstAxis)
{

    using library::core::types::Real ;
    
    using library::math::obj::Vector3d ;
    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;

    {

        EXPECT_EQ(Vector3d(1.0, 0.0, 0.0), Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).getFirstAxis()) ;

        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0, Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(45.0)))).getFirstAxis().isApprox(Vector3d(1.0, 1.0, 0.0).normalized(), Real::Epsilon())) ;

    }

    {

        EXPECT_ANY_THROW(Ellipsoid::Undefined().getFirstAxis()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, GetSecondAxis)
{

    using library::core::types::Real ;
    
    using library::math::obj::Vector3d ;
    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;

    {

        EXPECT_EQ(Vector3d(0.0, 1.0, 0.0), Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).getSecondAxis()) ;

        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0, Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(45.0)))).getSecondAxis().isApprox(Vector3d(-1.0, 1.0, 0.0).normalized(), Real::Epsilon())) ;

    }

    {

        EXPECT_ANY_THROW(Ellipsoid::Undefined().getSecondAxis()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, GetThirdAxis)
{

    using library::core::types::Real ;
    
    using library::math::obj::Vector3d ;
    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;

    {

        EXPECT_EQ(Vector3d(0.0, 0.0, 1.0), Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).getThirdAxis()) ;

        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0, Quaternion::RotationVector(RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(45.0)))).getThirdAxis().isApprox(Vector3d(0.0, -1.0, 1.0).normalized(), Real::Epsilon())) ;

    }

    {

        EXPECT_ANY_THROW(Ellipsoid::Undefined().getThirdAxis()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, GetOrientation)
{

    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::d3::objects::Ellipsoid ;
    
    {

        EXPECT_EQ(Quaternion::Unit(), Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).getOrientation()) ;

    }

    {

        EXPECT_EQ(Quaternion::XYZS(1.0, 0.0, 0.0, 0.0), Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0, Quaternion::XYZS(1.0, 0.0, 0.0, 0.0)).getOrientation()) ;

    }

    {

        EXPECT_ANY_THROW(Ellipsoid::Undefined().getOrientation()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, GetMatrix)
{

    using library::core::types::Real ;

    using library::math::obj::Matrix3d ;
    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;
    using library::math::geom::trf::rot::RotationMatrix ;

    {

        Matrix3d referenceEllipsoidMatrix ;

        referenceEllipsoidMatrix << 1.0 / (4.0 * 4.0),  0.0,                0.0,
                                    0.0,                1.0 / (5.0 * 5.0),  0.0,
                                    0.0,                0.0,                1.0 / (6.0 * 6.0) ;

        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).getMatrix().isApprox(referenceEllipsoidMatrix, Real::Epsilon())) ;

    }

    {

        const Matrix3d referenceRotationMatrix = RotationMatrix::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(45.0))).getMatrix() ;

        Matrix3d referenceEllipsoidMatrix ;

        referenceEllipsoidMatrix << 1.0 / (4.0 * 4.0),  0.0,                0.0,
                                    0.0,                1.0 / (5.0 * 5.0),  0.0,
                                    0.0,                0.0,                1.0 / (6.0 * 6.0) ;

        referenceEllipsoidMatrix = referenceRotationMatrix.transpose() * referenceEllipsoidMatrix * referenceRotationMatrix ;

        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0, Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(45.0)))).getMatrix().isApprox(referenceEllipsoidMatrix, Real::Epsilon())) ;

    }

    {

        EXPECT_ANY_THROW(Ellipsoid::Undefined().getMatrix()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, IntersectionWith_Line)
{

    using library::core::types::Real ;

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::PointSet ;
    using library::math::geom::d3::objects::Line ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::d3::Intersection ;

    {

        const Line line = { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(line) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.is<PointSet>()) ;

        const PointSet pointSet = intersection.as<PointSet>() ;

        EXPECT_EQ(2, pointSet.getSize()) ;

        EXPECT_TRUE(pointSet.isNear(PointSet({ { -1.0, 0.0, 0.0 }, { +1.0, 0.0, 0.0 } }), Real::Epsilon())) ;

    }

    {

        const Line line = { { 0.0, 0.0, -4.0 }, { 0.0, 0.0, 1.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(line) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.is<PointSet>()) ;

        const PointSet pointSet = intersection.as<PointSet>() ;

        EXPECT_EQ(2, pointSet.getSize()) ;

        EXPECT_TRUE(pointSet.isNear(PointSet({ { 0.0, 0.0, -3.0 }, { 0.0, 0.0, +3.0 } }), Real::Epsilon())) ;

    }

    {

        const Line line = { { 0.0, 0.0, +4.0 }, { 0.0, 0.0, 1.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(line) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.is<PointSet>()) ;

        const PointSet pointSet = intersection.as<PointSet>() ;

        EXPECT_EQ(2, pointSet.getSize()) ;

        EXPECT_TRUE(pointSet.isNear(PointSet({ { 0.0, 0.0, -3.0 }, { 0.0, 0.0, +3.0 } }), Real::Epsilon())) ;

    }

    {

        const Line line = { { 0.0, 0.0, +3.0 }, { 1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(line) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.is<Point>()) ;

        const Point point = intersection.as<Point>() ;

        EXPECT_TRUE(point.isNear(Point(0.0, 0.0, +3.0), Real::Epsilon())) ;

    }

    {

        const Line line = { { 0.0, 0.0, -3.0 }, { 1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(line) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.is<Point>()) ;

        const Point point = intersection.as<Point>() ;

        EXPECT_TRUE(point.isNear(Point(0.0, 0.0, -3.0), Real::Epsilon())) ;

    }

    {

        const Line line = { { 0.0, +3.0, 0.0 }, { 1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(line) ;

        EXPECT_TRUE(intersection.isEmpty()) ;

    }

    {

        EXPECT_ANY_THROW(Ellipsoid::Undefined().intersectionWith(Line::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, IntersectionWith_Ray)
{

    using library::core::types::Real ;

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::PointSet ;
    using library::math::geom::d3::objects::Ray ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::d3::Intersection ;

    // onlyInSight = false

    {

        const Ray ray = { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.is<Point>()) ;

        const Point point = intersection.as<Point>() ;

        EXPECT_TRUE(point.isNear(Point(1.0, 0.0, 0.0), Real::Epsilon())) ;

    }

    {

        const Ray ray = { { 0.0, 0.0, -4.0 }, { 0.0, 0.0, 1.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.is<PointSet>()) ;

        const PointSet pointSet = intersection.as<PointSet>() ;

        EXPECT_EQ(2, pointSet.getSize()) ;

        EXPECT_TRUE(pointSet.isNear(PointSet({ { 0.0, 0.0, -3.0 }, { 0.0, 0.0, +3.0 } }), Real::Epsilon())) ;

    }

    {

        const Ray ray = { { 0.0, 0.0, -10.0 }, { 0.0, 0.0, 1.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.is<PointSet>()) ;

        const PointSet pointSet = intersection.as<PointSet>() ;

        EXPECT_EQ(2, pointSet.getSize()) ;

        EXPECT_TRUE(pointSet.isNear(PointSet({ { 0.0, 0.0, -3.0 }, { 0.0, 0.0, +3.0 } }), 1e-10)) ;

    }

    {

        const Ray ray = { { 0.0, 0.0, -100.0 }, { 0.0, 0.0, 1.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.is<PointSet>()) ;

        const PointSet pointSet = intersection.as<PointSet>() ;

        EXPECT_EQ(2, pointSet.getSize()) ;

        EXPECT_TRUE(pointSet.isNear(PointSet({ { 0.0, 0.0, -3.0 }, { 0.0, 0.0, +3.0 } }), 1e-10)) ;

    }

    {

        const Ray ray = { { 0.0, 0.0, -1000.0 }, { 0.0, 0.0, 1.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.is<PointSet>()) ;

        const PointSet pointSet = intersection.as<PointSet>() ;

        EXPECT_EQ(2, pointSet.getSize()) ;

        EXPECT_TRUE(pointSet.isNear(PointSet({ { 0.0, 0.0, -3.0 }, { 0.0, 0.0, +3.0 } }), 1e-5)) ;

    }

    {

        const Ray ray = { { 0.0, 0.0, +4.0 }, { 0.0, 0.0, 1.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray) ;

        EXPECT_TRUE(intersection.isEmpty()) ;

    }

    {

        const Ray ray = { { 0.0, 0.0, +3.0 }, { 1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.is<Point>()) ;

        const Point point = intersection.as<Point>() ;

        EXPECT_TRUE(point.isNear(Point(0.0, 0.0, +3.0), Real::Epsilon())) ;

    }

    {

        const Ray ray = { { 0.0, 0.0, -3.0 }, { 1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.is<Point>()) ;

        const Point point = intersection.as<Point>() ;

        EXPECT_TRUE(point.isNear(Point(0.0, 0.0, -3.0), Real::Epsilon())) ;

    }

    {

        const Ray ray = { { 0.0, +3.0, 0.0 }, { 1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray) ;

        EXPECT_TRUE(intersection.isEmpty()) ;

    }

    // onlyInSight = true

    {

        const Ray ray = { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray, true) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.is<Point>()) ;

        const Point point = intersection.as<Point>() ;

        EXPECT_TRUE(point.isNear(Point(1.0, 0.0, 0.0), Real::Epsilon())) ;

    }

    {

        const Ray ray = { { 0.0, 0.0, -4.0 }, { 0.0, 0.0, 1.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray, true) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.is<Point>()) ;

        const Point point = intersection.as<Point>() ;

        EXPECT_TRUE(point.isNear(Point(0.0, 0.0, -3.0), Real::Epsilon())) ;

    }

    {

        const Ray ray = { { 0.0, 0.0, +4.0 }, { 0.0, 0.0, 1.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray, true) ;

        EXPECT_TRUE(intersection.isEmpty()) ;

    }

    {

        const Ray ray = { { 0.0, 0.0, +3.0 }, { 1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray, true) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.is<Point>()) ;

        const Point point = intersection.as<Point>() ;

        EXPECT_TRUE(point.isNear(Point(0.0, 0.0, +3.0), Real::Epsilon())) ;

    }

    {

        const Ray ray = { { 0.0, 0.0, -3.0 }, { 1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray, true) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.is<Point>()) ;

        const Point point = intersection.as<Point>() ;

        EXPECT_TRUE(point.isNear(Point(0.0, 0.0, -3.0), Real::Epsilon())) ;

    }

    {

        const Ray ray = { { 0.0, +3.0, 0.0 }, { 1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray, true) ;

        EXPECT_TRUE(intersection.isEmpty()) ;

    }

    {

        EXPECT_ANY_THROW(Ellipsoid::Undefined().intersectionWith(Ray::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, IntersectionWith_Segment)
{

    using library::core::types::Real ;

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::PointSet ;
    using library::math::geom::d3::objects::Segment ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::d3::Intersection ;

    {

        const Segment segment = { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(segment) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.is<Point>()) ;

        const Point point = intersection.as<Point>() ;

        EXPECT_TRUE(point.isNear(Point(1.0, 0.0, 0.0), Real::Epsilon())) ;

    }

    {

        const Segment segment = { { 0.0, 0.0, 0.0 }, { 2.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(segment) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.is<Point>()) ;

        const Point point = intersection.as<Point>() ;

        EXPECT_TRUE(point.isNear(Point(1.0, 0.0, 0.0), Real::Epsilon())) ;

    }

    {

        const Segment segment = { { 0.0, 0.0, 0.0 }, { -1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(segment) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.is<Point>()) ;

        const Point point = intersection.as<Point>() ;

        EXPECT_TRUE(point.isNear(Point(-1.0, 0.0, 0.0), Real::Epsilon())) ;

    }

    {

        const Segment segment = { { 0.0, 0.0, 0.0 }, { -2.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(segment) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.is<Point>()) ;

        const Point point = intersection.as<Point>() ;

        EXPECT_TRUE(point.isNear(Point(-1.0, 0.0, 0.0), Real::Epsilon())) ;

    }

    {

        const Segment segment = { { -1.0, 0.0, 0.0 }, { +1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(segment) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.is<PointSet>()) ;

        const PointSet pointSet = intersection.as<PointSet>() ;

        EXPECT_EQ(2, pointSet.getSize()) ;

        EXPECT_TRUE(pointSet.isNear(PointSet({ { -1.0, 0.0, 0.0 }, { +1.0, 0.0, 0.0 } }), Real::Epsilon())) ;

    }

    {

        const Segment segment = { { -2.0, 0.0, 0.0 }, { +2.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(segment) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.is<PointSet>()) ;

        const PointSet pointSet = intersection.as<PointSet>() ;

        EXPECT_EQ(2, pointSet.getSize()) ;

        EXPECT_TRUE(pointSet.isNear(PointSet({ { -1.0, 0.0, 0.0 }, { +1.0, 0.0, 0.0 } }), Real::Epsilon())) ;

    }

    {

        const Segment segment = { { -1.0, 0.0, +3.0 }, { +1.0, 0.0, +3.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(segment) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.is<Point>()) ;

        const Point point = intersection.as<Point>() ;

        EXPECT_TRUE(point.isNear(Point(0.0, 0.0, +3.0), Real::Epsilon())) ;

    }

    {

        const Segment segment = { { 0.0, 0.0, +3.0 }, { 0.0, 0.0, +3.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(segment) ;

        EXPECT_TRUE(intersection.isDefined()) ;

        ASSERT_TRUE(intersection.is<Point>()) ;

        const Point point = intersection.as<Point>() ;

        EXPECT_TRUE(point.isNear(Point(0.0, 0.0, +3.0), Real::Epsilon())) ;

    }

    {

        const Segment segment = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(segment) ;

        EXPECT_TRUE(intersection.isEmpty()) ;

    }

    {

        const Segment segment = { { 0.0, 0.0, 0.0 }, { 0.5, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(segment) ;

        EXPECT_TRUE(intersection.isEmpty()) ;

    }

    {

        EXPECT_ANY_THROW(Ellipsoid::Undefined().intersectionWith(Segment::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, IntersectionWith_Pyramid)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::d3::objects::Pyramid ;

    {

        // See: Library_Mathematics_Geometry_3D_Objects_Pyramid.IntersectionWith_Ellipsoid

        SUCCEED() ;

    }

    {

        EXPECT_ANY_THROW(Ellipsoid::Undefined().intersectionWith(Pyramid::Undefined())) ;
        EXPECT_ANY_THROW(Ellipsoid(Point::Origin(), 1.0, 1.0, 1.0).intersectionWith(Pyramid::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Translate)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::objects::Ellipsoid ;

    {

        Ellipsoid ellipsoid = { { 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0 } ;

        ellipsoid.translate({ 4.0, 5.0, 6.0 }) ;

        EXPECT_EQ(Ellipsoid({ 5.0, 7.0, 9.0 }, 4.0, 5.0, 6.0), ellipsoid) ;

    }

    {

        EXPECT_ANY_THROW(Ellipsoid::Undefined().translate(Vector3d::Undefined())) ;
        EXPECT_ANY_THROW(Ellipsoid::Undefined().translate({ 0.0, 0.0, 0.0 })) ;
        EXPECT_ANY_THROW(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).translate(Vector3d::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Rotate)
{

    using library::core::types::Real ;

    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;

    {

        Ellipsoid ellipsoid = { { 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0 } ;

        ellipsoid.rotate(Quaternion::RotationVector(RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(90.0)))) ;

        EXPECT_EQ(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 6.0, 5.0), ellipsoid) ;

    }

    {

        EXPECT_ANY_THROW(Ellipsoid::Undefined().rotate(Quaternion::Undefined())) ;
        EXPECT_ANY_THROW(Ellipsoid::Undefined().rotate(Quaternion::Unit())) ;
        EXPECT_ANY_THROW(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).rotate(Quaternion::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Undefined)
{

    using library::math::geom::d3::objects::Ellipsoid ;
    
    {

        EXPECT_NO_THROW(Ellipsoid::Undefined()) ;
        EXPECT_FALSE(Ellipsoid::Undefined().isDefined()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////