////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Sphere.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/3D/Transformation.hpp>
#include <Library/Mathematics/Geometry/3D/Intersection.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Pyramid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Sphere.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Plane.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ray.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Line.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/PointSet.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Point.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, Constructor)
{

    using library::math::geom::d3::objects::Sphere ;

    {

        EXPECT_NO_THROW(Sphere({ 1.0, 2.0, 3.0 }, 4.0)) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, Clone)
{

    using library::math::geom::d3::objects::Sphere ;

    {

        EXPECT_NO_THROW(const Sphere* spherePtr = Sphere({ 1.0, 2.0, 3.0 }, 4.0).clone() ; delete spherePtr ;) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, EqualToOperator)
{

    using library::math::geom::d3::objects::Sphere ;

    {

        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 4.0) == Sphere({ 1.0, 2.0, 3.0 }, 4.0)) ;

    }

    {

        EXPECT_FALSE(Sphere({ 1.0, 2.0, 3.0 }, 4.0) == Sphere({ 1.0, 2.0, 4.0 }, 4.0)) ;
        EXPECT_FALSE(Sphere({ 1.0, 2.0, 3.0 }, 4.0) == Sphere({ 1.0, 2.0, 3.0 }, 3.0)) ;

    }

    {

        EXPECT_FALSE(Sphere({ 1.0, 2.0, 3.0 }, 4.0) == Sphere::Undefined()) ;
        EXPECT_FALSE(Sphere::Undefined() == Sphere({ 1.0, 2.0, 3.0 }, 4.0)) ;
        EXPECT_FALSE(Sphere::Undefined() == Sphere::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, NotEqualToOperator)
{

    using library::math::geom::d3::objects::Sphere ;

    {

        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 4.0) != Sphere({ 1.0, 2.0, 4.0 }, 4.0)) ;
        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 4.0) != Sphere({ 1.0, 2.0, 3.0 }, 3.0)) ;

    }

    {

        EXPECT_FALSE(Sphere({ 1.0, 2.0, 3.0 }, 4.0) != Sphere({ 1.0, 2.0, 3.0 }, 4.0)) ;

    }

    {

        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 4.0) != Sphere::Undefined()) ;
        EXPECT_TRUE(Sphere::Undefined() != Sphere({ 1.0, 2.0, 3.0 }, 4.0)) ;
        EXPECT_TRUE(Sphere::Undefined() != Sphere::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, StreamOperator)
{

    using library::math::geom::d3::objects::Sphere ;

    {

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << Sphere({ 0.0, 0.0, 0.0 }, 1.0) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, IsDefined)
{

    using library::math::geom::d3::objects::Sphere ;

    {

        EXPECT_TRUE(Sphere({ 0.0, 0.0, 0.0 }, 1.0).isDefined()) ;
        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 4.0).isDefined()) ;

    }

    {

        EXPECT_FALSE(Sphere::Undefined().isDefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, IsUnitary)
{

    using library::math::geom::d3::objects::Sphere ;

    {

        EXPECT_TRUE(Sphere({ 0.0, 0.0, 0.0 }, 1.0).isUnitary()) ;
        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 1.0).isUnitary()) ;

    }

    {

        EXPECT_FALSE(Sphere({ 0.0, 0.0, 0.0 }, 1.1).isUnitary()) ;
        EXPECT_FALSE(Sphere({ 1.0, 2.0, 3.0 }, 0.9).isUnitary()) ;

    }

    {

        EXPECT_ANY_THROW(Sphere::Undefined().isUnitary()) ;

    }

}

















TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, Intersects_Point)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Sphere ;

    {

        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 4.0).intersects(Point(+5.0, +2.0, +3.0))) ;
        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 4.0).intersects(Point(-3.0, +2.0, +3.0))) ;

        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 4.0).intersects(Point(+1.0, +6.0, +3.0))) ;
        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 4.0).intersects(Point(+1.0, -2.0, +3.0))) ;

        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 4.0).intersects(Point(+1.0, +2.0, +7.0))) ;
        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 4.0).intersects(Point(+1.0, +2.0, -1.0))) ;

    }

    {

        EXPECT_FALSE(Sphere(Point::Origin(), 4.0).intersects(Point::Origin())) ;

    }

    {

        EXPECT_ANY_THROW(Sphere::Undefined().intersects(Point::Undefined())) ;
        EXPECT_ANY_THROW(Sphere({ 1.0, 2.0, 3.0 }, 4.0).intersects(Point::Undefined())) ;
        EXPECT_ANY_THROW(Sphere::Undefined().intersects(Point(0.0, 0.0, 0.0))) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, Intersects_PointSet)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::PointSet ;
    using library::math::geom::d3::objects::Sphere ;

    {

        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 4.0).intersects(PointSet({ { +5.0, +2.0, +3.0 }, { -3.0, +2.0, +3.0 }, { +1.0, +6.0, +3.0 }, { +1.0, -2.0, +3.0 }, { +1.0, +2.0, +7.0 }, { +1.0, +2.0, -1.0 } }))) ;
        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 4.0).intersects(PointSet({ { 0.0, 0.0, 0.0 }, { +5.0, +2.0, +3.0 } }))) ;

    }

    {

        EXPECT_FALSE(Sphere(Point::Origin(), 4.0).intersects(PointSet::Empty())) ;

    }

    {

        EXPECT_ANY_THROW(Sphere::Undefined().intersects(PointSet::Empty())) ;
        EXPECT_ANY_THROW(Sphere::Undefined().intersects(PointSet({ { +5.0, +2.0, +3.0 }, { +5.0, +2.0, +3.0 } }))) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, Intersects_Line)
{

    using library::core::types::Real ;

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Line ;
    using library::math::geom::d3::objects::Sphere ;

    {

        const Sphere sphere = { Point::Origin(), 2.0 } ;

        EXPECT_FALSE(sphere.intersects(Line({ -10.0, -3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ -10.0, -2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ -10.0, -2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ -10.0, -1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ -10.0, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ -10.0, +1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ -10.0, +2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ -10.0, +2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ -10.0, +3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Line({ +0.0, -3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ +0.0, -2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +0.0, -2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +0.0, -1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +0.0, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +0.0, +1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +0.0, +2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ +0.0, +2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ +0.0, +3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Line({ +10.0, -3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ +10.0, -2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +10.0, -2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +10.0, -1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +10.0, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +10.0, +1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +10.0, +2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ +10.0, +2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ +10.0, +3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Line({ -10.0, -3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ -10.0, -2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ -10.0, -2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ -10.0, -1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ -10.0, +0.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ -10.0, +1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ -10.0, +2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ -10.0, +2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ -10.0, +3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Line({ +0.0, -3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ +0.0, -2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +0.0, -2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +0.0, -1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +0.0, +0.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +0.0, +1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +0.0, +2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ +0.0, +2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ +0.0, +3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Line({ +10.0, -3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ +10.0, -2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +10.0, -2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +10.0, -1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +10.0, +0.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +10.0, +1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +10.0, +2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ +10.0, +2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ +10.0, +3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Line({ -3.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ -2.1, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ -2.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ -1.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +0.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +1.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +2.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ +2.1, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ +3.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Line({ -3.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ -2.1, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ -2.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ -1.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +0.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +1.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +2.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ +2.1, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ +3.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Line({ -3.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ -2.1, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ -2.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ -1.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +0.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +1.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +2.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ +2.1, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ +3.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Line({ -3.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ -2.1, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ -2.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ -1.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +0.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +1.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +2.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ +2.1, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ +3.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Line({ -3.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ -2.1, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ -2.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ -1.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +0.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +1.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +2.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ +2.1, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ +3.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Line({ -3.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ -2.1, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ -2.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ -1.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +0.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +1.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ +2.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ +2.1, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ +3.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;

    }

    {

        const Real equatorialRadius_m = 6378136.3 ;

        const Sphere sphere = { Point::Origin(), equatorialRadius_m } ;

        EXPECT_FALSE(sphere.intersects(Line({ 0.0, -7000e3, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ 0.0, -equatorialRadius_m - 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        // EXPECT_TRUE(sphere.intersects(Line({ 0.0, -equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ; // [TBI] Fix precision issues
        EXPECT_TRUE(sphere.intersects(Line({ 0.0, -equatorialRadius_m + 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ 0.0, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Line({ 0.0, +equatorialRadius_m - 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        // EXPECT_TRUE(sphere.intersects(Line({ 0.0, +equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ; // [TBI] Fix precision issues
        EXPECT_FALSE(sphere.intersects(Line({ 0.0, +equatorialRadius_m + 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Line({ 0.0, +7000e3, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

    }

    {

        EXPECT_ANY_THROW(Sphere::Undefined().intersects(Line::Undefined())) ;
        EXPECT_ANY_THROW(Sphere(Point::Origin(), 1.0).intersects(Line::Undefined())) ;
        EXPECT_ANY_THROW(Sphere::Undefined().intersects(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }))) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, Intersects_Ray)
{

    using library::core::types::Real ;

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Ray ;
    using library::math::geom::d3::objects::Sphere ;

    {

        const Sphere sphere = { Point::Origin(), 2.0 } ;

        EXPECT_FALSE(sphere.intersects(Ray({ -10.0, -3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ -10.0, -2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ -10.0, -2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ -10.0, -1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ -10.0, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ -10.0, +1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ -10.0, +2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ -10.0, +2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ -10.0, +3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Ray({ +0.0, -3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +0.0, -2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +0.0, -2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +0.0, -1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +0.0, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +0.0, +1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +0.0, +2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +0.0, +2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +0.0, +3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Ray({ +10.0, -3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +10.0, -2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +10.0, -2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +10.0, -1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +10.0, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +10.0, +1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +10.0, +2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +10.0, +2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +10.0, +3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Ray({ -10.0, -3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ -10.0, -2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ -10.0, -2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ -10.0, -1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ -10.0, +0.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ -10.0, +1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ -10.0, +2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ -10.0, +2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ -10.0, +3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Ray({ +0.0, -3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +0.0, -2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +0.0, -2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +0.0, -1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +0.0, +0.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +0.0, +1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +0.0, +2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +0.0, +2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +0.0, +3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Ray({ +10.0, -3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +10.0, -2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +10.0, -2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +10.0, -1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +10.0, +0.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +10.0, +1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +10.0, +2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +10.0, +2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +10.0, +3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Ray({ -3.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ -2.1, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ -2.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ -1.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +0.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +1.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +2.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +2.1, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +3.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Ray({ -3.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ -2.1, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ -2.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ -1.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +0.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +1.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +2.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +2.1, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +3.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Ray({ -3.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ -2.1, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ -2.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ -1.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +0.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +1.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +2.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +2.1, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +3.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Ray({ -3.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ -2.1, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ -2.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ -1.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +0.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +1.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +2.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +2.1, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +3.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Ray({ -3.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ -2.1, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ -2.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ -1.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +0.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +1.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +2.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +2.1, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +3.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Ray({ -3.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ -2.1, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ -2.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ -1.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +0.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +1.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ +2.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +2.1, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +3.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;

    }

    {

        const Real equatorialRadius_m = 6378136.3 ;

        const Sphere sphere = { Point::Origin(), equatorialRadius_m } ;

        EXPECT_FALSE(sphere.intersects(Ray({ -10000e3, -7000e3, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ -10000e3, -equatorialRadius_m - 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        // EXPECT_TRUE(sphere.intersects(Ray({ -10000e3, -equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ; // [TBI] Fix precision issues
        EXPECT_TRUE(sphere.intersects(Ray({ -10000e3, -equatorialRadius_m + 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ -10000e3, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ -10000e3, +equatorialRadius_m - 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        // EXPECT_TRUE(sphere.intersects(Ray({ -10000e3, +equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ; // [TBI] Fix precision issues
        EXPECT_FALSE(sphere.intersects(Ray({ -10000e3, +equatorialRadius_m + 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ -10000e3, +7000e3, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Ray({ 0.0, -7000e3, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ 0.0, -equatorialRadius_m - 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        // EXPECT_TRUE(sphere.intersects(Ray({ 0.0, -equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ; // [TBI] Fix precision issues
        EXPECT_TRUE(sphere.intersects(Ray({ 0.0, -equatorialRadius_m + 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ 0.0, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Ray({ 0.0, +equatorialRadius_m - 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        // EXPECT_TRUE(sphere.intersects(Ray({ 0.0, +equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ; // [TBI] Fix precision issues
        EXPECT_FALSE(sphere.intersects(Ray({ 0.0, +equatorialRadius_m + 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ 0.0, +7000e3, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Ray({ +10000e3, -7000e3, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +10000e3, -equatorialRadius_m - 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +10000e3, -equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +10000e3, -equatorialRadius_m + 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +10000e3, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +10000e3, +equatorialRadius_m - 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +10000e3, +equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +10000e3, +equatorialRadius_m + 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Ray({ +10000e3, +7000e3, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

    }

    {

        EXPECT_ANY_THROW(Sphere::Undefined().intersects(Ray::Undefined())) ;
        EXPECT_ANY_THROW(Sphere(Point::Origin(), 1.0).intersects(Ray::Undefined())) ;
        EXPECT_ANY_THROW(Sphere::Undefined().intersects(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }))) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, Intersects_Segment)
{

    using library::core::types::Real ;

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Segment ;
    using library::math::geom::d3::objects::Sphere ;

    {

        const Sphere sphere = { Point::Origin(), 2.0 } ;

        EXPECT_FALSE(sphere.intersects(Segment({ -10.0, -3.0, 0.0 }, { +10.0, -3.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Segment({ -10.0, -2.1, 0.0 }, { +10.0, -2.1, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -10.0, -2.0, 0.0 }, { +10.0, -2.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -10.0, -1.0, 0.0 }, { +10.0, -1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -10.0, +0.0, 0.0 }, { +10.0, +0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -10.0, +1.0, 0.0 }, { +10.0, +1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -10.0, +2.0, 0.0 }, { +10.0, +2.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Segment({ -10.0, +2.1, 0.0 }, { +10.0, +2.1, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Segment({ -10.0, +3.0, 0.0 }, { +10.0, +3.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Segment({ -3.0, -10.0, 0.0 }, { -3.0, +10.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Segment({ -2.1, -10.0, 0.0 }, { -2.1, +10.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -2.0, -10.0, 0.0 }, { -2.0, +10.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -1.0, -10.0, 0.0 }, { -1.0, +10.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ +0.0, -10.0, 0.0 }, { +0.0, +10.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ +1.0, -10.0, 0.0 }, { +1.0, +10.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ +2.0, -10.0, 0.0 }, { +2.0, +10.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Segment({ +2.1, -10.0, 0.0 }, { +2.1, +10.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Segment({ +3.0, -10.0, 0.0 }, { +3.0, +10.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Segment({ -10.0, 0.0, -3.0 }, { +10.0, 0.0, -3.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Segment({ -10.0, 0.0, -2.1 }, { +10.0, 0.0, -2.1 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -10.0, 0.0, -2.0 }, { +10.0, 0.0, -2.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -10.0, 0.0, -1.0 }, { +10.0, 0.0, -1.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -10.0, 0.0, +0.0 }, { +10.0, 0.0, +0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -10.0, 0.0, +1.0 }, { +10.0, 0.0, +1.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -10.0, 0.0, +2.0 }, { +10.0, 0.0, +2.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Segment({ -10.0, 0.0, +2.1 }, { +10.0, 0.0, +2.1 }))) ;
        EXPECT_FALSE(sphere.intersects(Segment({ -10.0, 0.0, +3.0 }, { +10.0, 0.0, +3.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Segment({ -10.0, 0.0, 0.0 }, { -2.1, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -10.0, 0.0, 0.0 }, { -2.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -10.0, 0.0, 0.0 }, { -1.9, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ +10.0, 0.0, 0.0 }, { +1.9, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ +10.0, 0.0, 0.0 }, { +2.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Segment({ +10.0, 0.0, 0.0 }, { +2.1, 0.0, 0.0 }))) ;

    }

    {

        const Real equatorialRadius_m = 6378136.3 ;

        const Sphere sphere = { Point::Origin(), equatorialRadius_m } ;

        EXPECT_FALSE(sphere.intersects(Segment({ -10000e3, -7000e3, 0.0 }, { +10000e3, -7000e3, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Segment({ -10000e3, -equatorialRadius_m - 0.1, 0.0 }, { +10000e3, -equatorialRadius_m - 0.1, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -10000e3, -equatorialRadius_m, 0.0 }, { +10000e3, -equatorialRadius_m, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -10000e3, -equatorialRadius_m + 0.1, 0.0 }, { +10000e3, -equatorialRadius_m + 0.1, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -10000e3, +0.0, 0.0 }, { +10000e3, +0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -10000e3, +equatorialRadius_m - 0.1, 0.0 }, { +10000e3, +equatorialRadius_m - 0.1, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -10000e3, +equatorialRadius_m, 0.0 }, { +10000e3, +equatorialRadius_m, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Segment({ -10000e3, +equatorialRadius_m + 0.1, 0.0 }, { +10000e3, +equatorialRadius_m + 0.1, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Segment({ -10000e3, +7000e3, 0.0 }, { +10000e3, +7000e3, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Segment({ -7000e3, -10000e3, 0.0 }, { -7000e3, +10000e3, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Segment({ -equatorialRadius_m - 0.1, -10000e3, 0.0 }, { -equatorialRadius_m - 0.1, +10000e3, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -equatorialRadius_m, -10000e3, 0.0 }, { -equatorialRadius_m, +10000e3, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -equatorialRadius_m + 0.1, -10000e3, 0.0 }, { -equatorialRadius_m + 0.1, +10000e3, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ +0.0, -10000e3, 0.0 }, { +0.0, +10000e3, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ +equatorialRadius_m - 0.1, -10000e3, 0.0 }, { +equatorialRadius_m - 0.1, +10000e3, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ +equatorialRadius_m, -10000e3, 0.0 }, { +equatorialRadius_m, +10000e3, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Segment({ +equatorialRadius_m + 0.1, -10000e3, 0.0 }, { +equatorialRadius_m + 0.1, +10000e3, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Segment({ +7000e3, -10000e3, 0.0 }, { +7000e3, +10000e3, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Segment({ -10000e3, 0.0, -7000e3 }, { +10000e3, 0.0, -7000e3 }))) ;
        EXPECT_FALSE(sphere.intersects(Segment({ -10000e3, 0.0, -equatorialRadius_m - 0.1 }, { +10000e3, 0.0, -equatorialRadius_m - 0.1 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -10000e3, 0.0, -equatorialRadius_m }, { +10000e3, 0.0, -equatorialRadius_m }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -10000e3, 0.0, -equatorialRadius_m + 0.1 }, { +10000e3, 0.0, -equatorialRadius_m + 0.1 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -10000e3, 0.0, +0.0 }, { +10000e3, 0.0, +0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -10000e3, 0.0, +equatorialRadius_m - 0.1 }, { +10000e3, 0.0, +equatorialRadius_m - 0.1 }))) ;
        EXPECT_TRUE(sphere.intersects(Segment({ -10000e3, 0.0, +equatorialRadius_m }, { +10000e3, 0.0, +equatorialRadius_m }))) ;
        EXPECT_FALSE(sphere.intersects(Segment({ -10000e3, 0.0, +equatorialRadius_m + 0.1 }, { +10000e3, 0.0, +equatorialRadius_m + 0.1 }))) ;
        EXPECT_FALSE(sphere.intersects(Segment({ -10000e3, 0.0, +7000e3 }, { +10000e3, 0.0, +7000e3 }))) ;

    }

    {

        EXPECT_ANY_THROW(Sphere(Point::Origin(), 1.0).intersects(Segment::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, Intersects_Plane)
{

    using library::core::types::Real ;

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Plane ;
    using library::math::geom::d3::objects::Sphere ;

    {

        const Sphere sphere = { Point::Origin(), 2.0 } ;

        EXPECT_TRUE(sphere.intersects(Plane({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Plane({ -3.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Plane({ -2.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Plane({ -1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Plane({ +0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Plane({ +1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Plane({ +2.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Plane({ +3.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Plane({ 0.0, -3.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Plane({ 0.0, -2.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Plane({ 0.0, -1.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Plane({ 0.0, +0.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Plane({ 0.0, +1.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Plane({ 0.0, +2.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Plane({ 0.0, +3.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;

        EXPECT_FALSE(sphere.intersects(Plane({ 0.0, 0.0, -3.0 }, { 0.0, 0.0, 1.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Plane({ 0.0, 0.0, -2.0 }, { 0.0, 0.0, 1.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Plane({ 0.0, 0.0, -1.0 }, { 0.0, 0.0, 1.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Plane({ 0.0, 0.0, +0.0 }, { 0.0, 0.0, 1.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Plane({ 0.0, 0.0, +1.0 }, { 0.0, 0.0, 1.0 }))) ;
        EXPECT_TRUE(sphere.intersects(Plane({ 0.0, 0.0, +2.0 }, { 0.0, 0.0, 1.0 }))) ;
        EXPECT_FALSE(sphere.intersects(Plane({ 0.0, 0.0, +3.0 }, { 0.0, 0.0, 1.0 }))) ;

    }

    {

        EXPECT_ANY_THROW(Sphere::Undefined().intersects(Plane::Undefined())) ;
        EXPECT_ANY_THROW(Sphere(Point::Origin(), 1.0).intersects(Plane::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, Intersects_Pyramid)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Sphere ;
    using library::math::geom::d3::objects::Pyramid ;

    {

        // See: Library_Mathematics_Geometry_3D_Objects_Pyramid.Intersects_Sphere

        SUCCEED() ;

    }

    {

        EXPECT_ANY_THROW(Sphere::Undefined().intersects(Pyramid::Undefined())) ;
        EXPECT_ANY_THROW(Sphere(Point::Origin(), 1.0).intersects(Pyramid::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, Contains_Point)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Sphere ;

    {

        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 4.0).contains(Point(+5.0, +2.0, +3.0))) ;
        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 4.0).contains(Point(-3.0, +2.0, +3.0))) ;

        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 4.0).contains(Point(+1.0, +6.0, +3.0))) ;
        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 4.0).contains(Point(+1.0, -2.0, +3.0))) ;

        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 4.0).contains(Point(+1.0, +2.0, +7.0))) ;
        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 4.0).contains(Point(+1.0, +2.0, -1.0))) ;

    }

    {

        EXPECT_FALSE(Sphere(Point::Origin(), 4.0).contains(Point::Origin())) ;

    }

    {

        EXPECT_ANY_THROW(Sphere::Undefined().contains(Point::Undefined())) ;
        EXPECT_ANY_THROW(Sphere({ 1.0, 2.0, 3.0 }, 4.0).contains(Point::Undefined())) ;
        EXPECT_ANY_THROW(Sphere::Undefined().contains(Point(0.0, 0.0, 0.0))) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, Contains_PointSet)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::PointSet ;
    using library::math::geom::d3::objects::Sphere ;

    {

        EXPECT_TRUE(Sphere({ 1.0, 2.0, 3.0 }, 4.0).contains(PointSet({ { +5.0, +2.0, +3.0 }, { -3.0, +2.0, +3.0 }, { +1.0, +6.0, +3.0 }, { +1.0, -2.0, +3.0 }, { +1.0, +2.0, +7.0 }, { +1.0, +2.0, -1.0 } }))) ;

    }

    {

        EXPECT_FALSE(Sphere({ 1.0, 2.0, 3.0 }, 4.0).contains(PointSet({ { +5.0, +2.0, +3.0 }, { -3.0, +2.0, +3.0 }, { +1.0, +6.0, +3.0 }, { +1.0, -2.0, +3.0 }, { +1.0, +2.0, +7.0 }, { 0.0, 0.0, 0.0 } }))) ;

    }

    {

        EXPECT_FALSE(Sphere(Point::Origin(), 4.0).contains(PointSet::Empty())) ;

    }

    {

        EXPECT_ANY_THROW(Sphere::Undefined().contains(PointSet::Empty())) ;
        EXPECT_ANY_THROW(Sphere::Undefined().contains(PointSet({ { +5.0, +2.0, +3.0 }, { +5.0, +2.0, +3.0 } }))) ;

    }

}



































TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, GetCenter)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Sphere ;

    {

        EXPECT_EQ(Point(1.0, 2.0, 3.0), Sphere({ 1.0, 2.0, 3.0 }, 4.0).getCenter()) ;

    }

    {

        EXPECT_ANY_THROW(Sphere::Undefined().getCenter()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, GetRadius)
{

    using library::math::geom::d3::objects::Sphere ;

    {

        EXPECT_EQ(4.0, Sphere({ 1.0, 2.0, 3.0 }, 4.0).getRadius()) ;

    }

    {

        EXPECT_ANY_THROW(Sphere::Undefined().getRadius()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, ApplyTransformation)
{

    using library::core::types::Real ;

    using library::math::obj::Vector3d ;
    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Sphere ;
    using library::math::geom::d3::Transformation ;
    using library::math::geom::d3::trf::rot::RotationVector ;

    // Translation

    {

        Sphere sphere = { { 1.0, 2.0, 3.0 }, 4.0 } ;

        sphere.applyTransformation(Transformation::Translation({ 4.0, 5.0, 6.0 })) ;

        EXPECT_EQ(Sphere({ 5.0, 7.0, 9.0 }, 4.0), sphere) ;

    }

    // Rotation

    {

        Sphere sphere = { { 1.0, 2.0, 0.0 }, 4.0 } ;

        sphere.applyTransformation(Transformation::Rotation(RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(90.0)))) ;

        const Sphere referenceSphere = { { 1.0, 0.0, 2.0 }, 4.0 } ;

        EXPECT_TRUE(sphere.getCenter().isNear(referenceSphere.getCenter(), Real::Epsilon())) ;
        EXPECT_EQ(referenceSphere.getRadius(), sphere.getRadius()) ;

    }

    {

        EXPECT_ANY_THROW(Sphere::Undefined().applyTransformation(Transformation::Undefined())) ;
        EXPECT_ANY_THROW(Sphere::Undefined().applyTransformation(Transformation::Identity())) ;
        EXPECT_ANY_THROW(Sphere({ 1.0, 2.0, 3.0 }, 4.0).applyTransformation(Transformation::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, Undefined)
{

    using library::math::geom::d3::objects::Sphere ;

    {

        EXPECT_NO_THROW(Sphere::Undefined()) ;
        EXPECT_FALSE(Sphere::Undefined().isDefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Sphere, Unit)
{

    using library::math::geom::d3::objects::Sphere ;

    {

        EXPECT_NO_THROW(Sphere::Unit({ 0.0, 0.0, 0.0 })) ;
        EXPECT_EQ(Sphere({ 0.0, 0.0, 0.0 }, 1.0), Sphere::Unit({ 0.0, 0.0, 0.0 })) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
