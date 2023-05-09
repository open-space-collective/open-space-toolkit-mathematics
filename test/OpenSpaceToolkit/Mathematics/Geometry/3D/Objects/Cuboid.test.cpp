// Copyright © Loft Orbital Solutions Inc.

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Pyramid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Cuboid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Plane.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Ray.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Line.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/PointSet.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, Constructor)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Cuboid ;

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        EXPECT_NO_THROW(Cuboid(center, axes, extent)) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, Clone)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Cuboid ;

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        EXPECT_NO_THROW(const Cuboid* cuboidPtr = Cuboid(center, axes, extent).clone() ; delete cuboidPtr ;) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, EqualToOperator)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Cuboid ;

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        EXPECT_TRUE(Cuboid(center, axes, extent) == Cuboid(center, axes, extent)) ;

    }

    {

        const Point center = { 0.0, 0.0, 0.0 } ;

        const Cuboid firstCuboid = { center, { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } }, { 1.0, 2.0, 3.0 } } ;
        const Cuboid secondCuboid = { center, { Vector3d { 0.0, 1.0, 0.0 }, Vector3d { -1.0, 0.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } }, { 2.0, 1.0, 3.0 } } ;

        EXPECT_TRUE(firstCuboid == secondCuboid) ;

    }

    {

        const Point center = { 1.0, 2.0, 3.0 } ;

        const Cuboid firstCuboid = { center, { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } }, { 1.0, 2.0, 3.0 } } ;
        const Cuboid secondCuboid = { center, { Vector3d { 0.0, 0.0, -1.0 }, Vector3d { 0.0, -1.0, 0.0 }, Vector3d { -1.0, 0.0, 0.0 } }, { 3.0, 2.0, 1.0 } } ;

        EXPECT_TRUE(firstCuboid == secondCuboid) ;

    }

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        EXPECT_FALSE(Cuboid(center, axes, extent) == Cuboid::Undefined()) ;
        EXPECT_FALSE(Cuboid::Undefined() == Cuboid(center, axes, extent)) ;
        EXPECT_FALSE(Cuboid::Undefined() == Cuboid::Undefined()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, NotEqualToOperator)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Cuboid ;

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        EXPECT_FALSE(Cuboid(center, axes, extent) != Cuboid(center, axes, extent)) ;

    }

    {

        const Point center = { 0.0, 0.0, 0.0 } ;

        const Cuboid firstCuboid = { center, { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } }, { 1.0, 2.0, 3.0 } } ;
        const Cuboid secondCuboid = { center, { Vector3d { 0.0, 1.0, 0.0 }, Vector3d { -1.0, 0.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } }, { 2.0, 1.0, 3.0 } } ;

        EXPECT_FALSE(firstCuboid != secondCuboid) ;

    }

    {

        const Point center = { 1.0, 2.0, 3.0 } ;

        const Cuboid firstCuboid = { center, { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } }, { 1.0, 2.0, 3.0 } } ;
        const Cuboid secondCuboid = { center, { Vector3d { 0.0, 0.0, -1.0 }, Vector3d { 0.0, -1.0, 0.0 }, Vector3d { -1.0, 0.0, 0.0 } }, { 3.0, 2.0, 1.0 } } ;

        EXPECT_FALSE(firstCuboid != secondCuboid) ;

    }

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        EXPECT_TRUE(Cuboid(center, axes, extent) != Cuboid::Undefined()) ;
        EXPECT_TRUE(Cuboid::Undefined() != Cuboid(center, axes, extent)) ;
        EXPECT_TRUE(Cuboid::Undefined() != Cuboid::Undefined()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, StreamOperator)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Cuboid ;

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << Cuboid(center, axes, extent) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, IsDefined)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Cuboid ;

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        EXPECT_TRUE(Cuboid(center, axes, extent).isDefined()) ;

    }

    {

        EXPECT_FALSE(Cuboid::Undefined().isDefined()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, IsNear)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Cuboid ;

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        const Cuboid cuboid = { center, axes, extent } ;

        EXPECT_TRUE(cuboid.isNear(cuboid, 0.0)) ;

    }

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        const Cuboid firstCuboid = { center, axes, extent } ;
        const Cuboid secondCuboid = { { 0.0, 0.0, 1e-6 }, axes, extent } ;

        EXPECT_TRUE(firstCuboid.isNear(secondCuboid, 1e-5)) ;

    }

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        const Cuboid firstCuboid = { center, axes, extent } ;
        const Cuboid secondCuboid = { center, axes, { 1.0 + 1e-6, 2.0, 3.0 } } ;

        EXPECT_TRUE(firstCuboid.isNear(secondCuboid, 1e-5)) ;

    }

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        const Cuboid firstCuboid = { center, axes, extent } ;
        const Cuboid secondCuboid = { center, axes, { 1.0 + 1e-4, 2.0, 3.0 } } ;

        EXPECT_FALSE(firstCuboid.isNear(secondCuboid, 1e-5)) ;

    }

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        const Cuboid cuboid = { center, axes, extent } ;

        EXPECT_ANY_THROW(Cuboid::Undefined().isNear(Cuboid::Undefined(), Real::Undefined())) ;
        EXPECT_ANY_THROW(cuboid.isNear(Cuboid::Undefined(), Real::Undefined())) ;
        EXPECT_ANY_THROW(Cuboid::Undefined().isNear(cuboid, Real::Undefined())) ;
        EXPECT_ANY_THROW(cuboid.isNear(cuboid, Real::Undefined())) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, Intersects_Point)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Cuboid ;

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        const Cuboid cuboid = { center, axes, extent } ;

        EXPECT_TRUE(cuboid.intersects(Point(+1.0, 0.0, 0.0))) ;
        EXPECT_TRUE(cuboid.intersects(Point(-1.0, 0.0, 0.0))) ;

        EXPECT_TRUE(cuboid.intersects(Point(0.0, +2.0, 0.0))) ;
        EXPECT_TRUE(cuboid.intersects(Point(0.0, -2.0, 0.0))) ;

        EXPECT_TRUE(cuboid.intersects(Point(0.0, 0.0, +3.0))) ;
        EXPECT_TRUE(cuboid.intersects(Point(0.0, 0.0, -3.0))) ;

        EXPECT_TRUE(cuboid.intersects(Point(+1.0, +2.0, +3.0))) ;
        EXPECT_TRUE(cuboid.intersects(Point(-1.0, -2.0, -3.0))) ;

        EXPECT_TRUE(cuboid.intersects(Point(+1.0, +0.5, 0.0))) ;
        EXPECT_TRUE(cuboid.intersects(Point(+1.0, -0.5, 0.0))) ;

        EXPECT_TRUE(cuboid.intersects(Point(+1.0, +0.5, +1.0))) ;
        EXPECT_TRUE(cuboid.intersects(Point(+1.0, -0.5, +1.0))) ;

        EXPECT_TRUE(cuboid.intersects(Point(+1.0, +0.5, -1.0))) ;
        EXPECT_TRUE(cuboid.intersects(Point(+1.0, -0.5, -1.0))) ;

        EXPECT_TRUE(cuboid.intersects(Point(+0.5, +2.0, -1.0))) ;
        EXPECT_TRUE(cuboid.intersects(Point(+0.5, -2.0, -1.0))) ;

        EXPECT_FALSE(cuboid.intersects(Point(+0.5, +2.0, +3.1))) ;
        EXPECT_FALSE(cuboid.intersects(Point(+0.5, -2.0, -3.1))) ;

    }

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        EXPECT_ANY_THROW(Cuboid(center, axes, extent).intersects(Point::Undefined())) ;
        EXPECT_ANY_THROW(Cuboid::Undefined().intersects(Point(0.0, 0.0, 0.0))) ;
        EXPECT_ANY_THROW(Cuboid::Undefined().intersects(Point::Undefined())) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, Intersects_PointSet)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::PointSet ;
    using ostk::math::geom::d3::objects::Cuboid ;

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        const Cuboid cuboid = { center, axes, extent } ;

        const PointSet pointSet =
        {
            {
                { +1.0, 0.0, 0.0 },
                { -1.0, 0.0, 0.0 },
                { 0.0, +2.0, 0.0 },
                { 0.0, -2.0, 0.0 },
                { 0.0, 0.0, +3.0 },
                { 0.0, 0.0, -3.0 },
                { +1.0, +2.0, +3.0 },
                { -1.0, -2.0, -3.0 },
                { +1.0, +0.5, 0.0 },
                { +1.0, -0.5, 0.0 },
                { +1.0, +0.5, +1.0 },
                { +1.0, -0.5, +1.0 },
                { +1.0, +0.5, -1.0 },
                { +1.0, -0.5, -1.0 },
                { +0.5, +2.0, -1.0 },
                { +0.5, -2.0, -1.0 }
            }
        } ;

        EXPECT_TRUE(cuboid.intersects(pointSet)) ;

    }

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        const Cuboid cuboid = { center, axes, extent } ;

        const PointSet pointSet =
        {
            {
                { +1.0, 0.0, 0.0 },
                { -1.0, 0.0, 0.0 },
                { 0.0, +2.0, 0.0 },
                { 0.0, -2.0, 0.0 },
                { 0.0, 0.0, +3.0 },
                { 0.0, 0.0, -3.0 },
                { +1.0, +2.0, +3.0 },
                { -1.0, -2.0, -3.0 },
                { +1.0, +0.5, 0.0 },
                { +1.0, -0.5, 0.0 },
                { +1.0, +0.5, +1.0 },
                { +1.0, -0.5, +1.0 },
                { +1.0, +0.5, -1.0 },
                { +1.0, -0.5, -1.0 },
                { +0.5, +2.0, -1.0 },
                { +0.5, -2.0, -1.0 },
                { +0.5, -2.0, -3.1 }
            }
        } ;

        EXPECT_TRUE(cuboid.intersects(pointSet)) ;

    }

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        const Cuboid cuboid = { center, axes, extent } ;

        const PointSet pointSet =
        {
            {
                { +0.5, +2.0, +3.1 },
                { +0.5, -2.0, -3.1 }
            }
        } ;

        EXPECT_FALSE(cuboid.intersects(pointSet)) ;

    }

    {

        EXPECT_ANY_THROW(Cuboid::Undefined().intersects(PointSet::Empty())) ;
        EXPECT_ANY_THROW(Cuboid::Undefined().intersects(PointSet({ { +5.0, +2.0, +3.0 }, { +5.0, +2.0, +3.0 } }))) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, Intersects_Line)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::PointSet ;
    using ostk::math::geom::d3::objects::Line ;
    using ostk::math::geom::d3::objects::Cuboid ;

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        const Cuboid cuboid = { center, axes, extent } ;

        EXPECT_TRUE(cuboid.intersects(Line({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(cuboid.intersects(Line({ 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_TRUE(cuboid.intersects(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }))) ;

        EXPECT_TRUE(cuboid.intersects(Line({ +1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(cuboid.intersects(Line({ +1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_TRUE(cuboid.intersects(Line({ +1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }))) ;

        EXPECT_TRUE(cuboid.intersects(Line({ -1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(cuboid.intersects(Line({ -1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_TRUE(cuboid.intersects(Line({ -1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }))) ;

        EXPECT_TRUE(cuboid.intersects(Line({ 0.0, +2.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(cuboid.intersects(Line({ 0.0, +2.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_TRUE(cuboid.intersects(Line({ 0.0, +2.0, 0.0 }, { 0.0, 0.0, 1.0 }))) ;

        EXPECT_TRUE(cuboid.intersects(Line({ 0.0, -2.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(cuboid.intersects(Line({ 0.0, -2.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_TRUE(cuboid.intersects(Line({ 0.0, -2.0, 0.0 }, { 0.0, 0.0, 1.0 }))) ;

        EXPECT_TRUE(cuboid.intersects(Line({ 0.0, 0.0, +3.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(cuboid.intersects(Line({ 0.0, 0.0, +3.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_TRUE(cuboid.intersects(Line({ 0.0, 0.0, +3.0 }, { 0.0, 0.0, 1.0 }))) ;

        EXPECT_TRUE(cuboid.intersects(Line({ 0.0, 0.0, -3.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(cuboid.intersects(Line({ 0.0, 0.0, -3.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_TRUE(cuboid.intersects(Line({ 0.0, 0.0, -3.0 }, { 0.0, 0.0, 1.0 }))) ;

        EXPECT_TRUE(cuboid.intersects(Line({ +1.1, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(cuboid.intersects(Line({ +1.1, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_FALSE(cuboid.intersects(Line({ +1.1, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }))) ;

        EXPECT_TRUE(cuboid.intersects(Line({ -1.1, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(cuboid.intersects(Line({ -1.1, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_FALSE(cuboid.intersects(Line({ -1.1, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }))) ;

        EXPECT_FALSE(cuboid.intersects(Line({ 0.0, +2.1, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(cuboid.intersects(Line({ 0.0, +2.1, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_FALSE(cuboid.intersects(Line({ 0.0, +2.1, 0.0 }, { 0.0, 0.0, 1.0 }))) ;

        EXPECT_FALSE(cuboid.intersects(Line({ 0.0, -2.1, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_TRUE(cuboid.intersects(Line({ 0.0, -2.1, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_FALSE(cuboid.intersects(Line({ 0.0, -2.1, 0.0 }, { 0.0, 0.0, 1.0 }))) ;

        EXPECT_FALSE(cuboid.intersects(Line({ 0.0, 0.0, +3.1 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(cuboid.intersects(Line({ 0.0, 0.0, +3.1 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_TRUE(cuboid.intersects(Line({ 0.0, 0.0, +3.1 }, { 0.0, 0.0, 1.0 }))) ;

        EXPECT_FALSE(cuboid.intersects(Line({ 0.0, 0.0, -3.1 }, { 1.0, 0.0, 0.0 }))) ;
        EXPECT_FALSE(cuboid.intersects(Line({ 0.0, 0.0, -3.1 }, { 0.0, 1.0, 0.0 }))) ;
        EXPECT_TRUE(cuboid.intersects(Line({ 0.0, 0.0, -3.1 }, { 0.0, 0.0, 1.0 }))) ;

    }

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        const Cuboid cuboid = { center, axes, extent } ;

        EXPECT_ANY_THROW(Cuboid::Undefined().intersects(Line::Undefined())) ;
        EXPECT_ANY_THROW(cuboid.intersects(Line::Undefined())) ;
        EXPECT_ANY_THROW(Cuboid::Undefined().intersects(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }))) ;

    }

}

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, Intersects_Ray)
// {

//     using ostk::core::types::Real ;

//     using ostk::math::geom::d3::objects::Point ;
//     using ostk::math::geom::d3::objects::Ray ;
//     using ostk::math::geom::d3::objects::Cuboid ;

//     {

//         EXPECT_ANY_THROW(Cuboid::Undefined().intersects(Ray::Undefined())) ;
//         EXPECT_ANY_THROW(Cuboid(Point::Origin(), 1.0, 1.0, 1.0).intersects(Ray::Undefined())) ;
//         EXPECT_ANY_THROW(Cuboid::Undefined().intersects(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }))) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, Intersects_Segment)
// {

//     using ostk::core::types::Real ;

//     using ostk::math::geom::d3::objects::Point ;
//     using ostk::math::geom::d3::objects::Segment ;
//     using ostk::math::geom::d3::objects::Cuboid ;

//     {

//         EXPECT_ANY_THROW(Cuboid(Point::Origin(), 1.0, 1.0, 1.0).intersects(Segment::Undefined())) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, Intersects_Plane)
// {

//     using ostk::core::types::Real ;

//     using ostk::math::geom::d3::objects::Point ;
//     using ostk::math::geom::d3::objects::Plane ;
//     using ostk::math::geom::d3::objects::Cuboid ;

//     {

//         EXPECT_ANY_THROW(Cuboid::Undefined().intersects(Plane::Undefined())) ;
//         EXPECT_ANY_THROW(Cuboid(Point::Origin(), 1.0, 1.0, 1.0).intersects(Plane::Undefined())) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, Intersects_Pyramid)
// {

//     using ostk::math::geom::d3::objects::Point ;
//     using ostk::math::geom::d3::objects::Cuboid ;
//     using ostk::math::geom::d3::objects::Pyramid ;

//     {

//         EXPECT_ANY_THROW(Cuboid::Undefined().intersects(Pyramid::Undefined())) ;
//         EXPECT_ANY_THROW(Cuboid(Point::Origin(), 1.0, 1.0, 1.0).intersects(Pyramid::Undefined())) ;

//     }

// }

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, Contains_Point)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Cuboid ;

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        const Cuboid cuboid = { center, axes, extent } ;

        EXPECT_TRUE(cuboid.contains(Point(+1.0, 0.0, 0.0))) ;
        EXPECT_TRUE(cuboid.contains(Point(-1.0, 0.0, 0.0))) ;

        EXPECT_TRUE(cuboid.contains(Point(0.0, +2.0, 0.0))) ;
        EXPECT_TRUE(cuboid.contains(Point(0.0, -2.0, 0.0))) ;

        EXPECT_TRUE(cuboid.contains(Point(0.0, 0.0, +3.0))) ;
        EXPECT_TRUE(cuboid.contains(Point(0.0, 0.0, -3.0))) ;

        EXPECT_TRUE(cuboid.contains(Point(+1.0, +2.0, +3.0))) ;
        EXPECT_TRUE(cuboid.contains(Point(-1.0, -2.0, -3.0))) ;

        EXPECT_TRUE(cuboid.contains(Point(+1.0, +0.5, 0.0))) ;
        EXPECT_TRUE(cuboid.contains(Point(+1.0, -0.5, 0.0))) ;

        EXPECT_TRUE(cuboid.contains(Point(+1.0, +0.5, +1.0))) ;
        EXPECT_TRUE(cuboid.contains(Point(+1.0, -0.5, +1.0))) ;

        EXPECT_TRUE(cuboid.contains(Point(+1.0, +0.5, -1.0))) ;
        EXPECT_TRUE(cuboid.contains(Point(+1.0, -0.5, -1.0))) ;

        EXPECT_TRUE(cuboid.contains(Point(+0.5, +2.0, -1.0))) ;
        EXPECT_TRUE(cuboid.contains(Point(+0.5, -2.0, -1.0))) ;

        EXPECT_FALSE(cuboid.contains(Point(+0.5, +2.0, +3.1))) ;
        EXPECT_FALSE(cuboid.contains(Point(+0.5, -2.0, -3.1))) ;

    }

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        EXPECT_ANY_THROW(Cuboid(center, axes, extent).contains(Point::Undefined())) ;
        EXPECT_ANY_THROW(Cuboid::Undefined().contains(Point(0.0, 0.0, 0.0))) ;
        EXPECT_ANY_THROW(Cuboid::Undefined().contains(Point::Undefined())) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, Contains_PointSet)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::PointSet ;
    using ostk::math::geom::d3::objects::Cuboid ;

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        const Cuboid cuboid = { center, axes, extent } ;

        const PointSet pointSet =
        {
            {
                { +1.0, 0.0, 0.0 },
                { -1.0, 0.0, 0.0 },
                { 0.0, +2.0, 0.0 },
                { 0.0, -2.0, 0.0 },
                { 0.0, 0.0, +3.0 },
                { 0.0, 0.0, -3.0 },
                { +1.0, +2.0, +3.0 },
                { -1.0, -2.0, -3.0 },
                { +1.0, +0.5, 0.0 },
                { +1.0, -0.5, 0.0 },
                { +1.0, +0.5, +1.0 },
                { +1.0, -0.5, +1.0 },
                { +1.0, +0.5, -1.0 },
                { +1.0, -0.5, -1.0 },
                { +0.5, +2.0, -1.0 },
                { +0.5, -2.0, -1.0 }
            }
        } ;

        EXPECT_TRUE(cuboid.contains(pointSet)) ;

    }

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        const Cuboid cuboid = { center, axes, extent } ;

        const PointSet pointSet =
        {
            {
                { +1.0, 0.0, 0.0 },
                { -1.0, 0.0, 0.0 },
                { 0.0, +2.0, 0.0 },
                { 0.0, -2.0, 0.0 },
                { 0.0, 0.0, +3.0 },
                { 0.0, 0.0, -3.0 },
                { +1.0, +2.0, +3.0 },
                { -1.0, -2.0, -3.0 },
                { +1.0, +0.5, 0.0 },
                { +1.0, -0.5, 0.0 },
                { +1.0, +0.5, +1.0 },
                { +1.0, -0.5, +1.0 },
                { +1.0, +0.5, -1.0 },
                { +1.0, -0.5, -1.0 },
                { +0.5, +2.0, -1.0 },
                { +0.5, -2.0, -1.0 },
                { +0.5, -2.0, -3.1 }
            }
        } ;

        EXPECT_FALSE(cuboid.contains(pointSet)) ;

    }

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        const Cuboid cuboid = { center, axes, extent } ;

        const PointSet pointSet =
        {
            {
                { +0.5, +2.0, +3.1 },
                { +0.5, -2.0, -3.1 }
            }
        } ;

        EXPECT_FALSE(cuboid.contains(pointSet)) ;

    }

    {

        EXPECT_ANY_THROW(Cuboid::Undefined().contains(PointSet::Empty())) ;
        EXPECT_ANY_THROW(Cuboid::Undefined().contains(PointSet({ { +5.0, +2.0, +3.0 }, { +5.0, +2.0, +3.0 } }))) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, GetCenter)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Cuboid ;

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        EXPECT_EQ(center, Cuboid(center, axes, extent).getCenter()) ;

    }

    {

        EXPECT_ANY_THROW(Cuboid::Undefined().getCenter()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, GetFirstAxis)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Cuboid ;

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        EXPECT_EQ(axes[0], Cuboid(center, axes, extent).getFirstAxis()) ;

    }

    {

        EXPECT_ANY_THROW(Cuboid::Undefined().getFirstAxis()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, GetSecondAxis)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Cuboid ;

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        EXPECT_EQ(axes[1], Cuboid(center, axes, extent).getSecondAxis()) ;

    }

    {

        EXPECT_ANY_THROW(Cuboid::Undefined().getSecondAxis()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, GetThirdAxis)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Cuboid ;

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        EXPECT_EQ(axes[2], Cuboid(center, axes, extent).getThirdAxis()) ;

    }

    {

        EXPECT_ANY_THROW(Cuboid::Undefined().getThirdAxis()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, GetFirstExtent)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Cuboid ;

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        EXPECT_EQ(extent[0], Cuboid(center, axes, extent).getFirstExtent()) ;

    }

    {

        EXPECT_ANY_THROW(Cuboid::Undefined().getFirstExtent()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, GetSecondExtent)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Cuboid ;

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        EXPECT_EQ(extent[1], Cuboid(center, axes, extent).getSecondExtent()) ;

    }

    {

        EXPECT_ANY_THROW(Cuboid::Undefined().getSecondExtent()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, GetThirdExtent)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Cuboid ;

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        EXPECT_EQ(extent[2], Cuboid(center, axes, extent).getThirdExtent()) ;

    }

    {

        EXPECT_ANY_THROW(Cuboid::Undefined().getThirdExtent()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, GetVertices)
{

    using ostk::core::types::Real ;
    using ostk::core::ctnr::Array ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Cuboid ;

    {

        const Point center = { 0.0, 0.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        const Cuboid cuboid = { center, axes, extent } ;

        const Array<Cuboid::Vertex> referenceVertices =
        {
            {
                { +0.5, +1.0, +1.5 },
                { +0.5, +1.0, -1.5 },
                { +0.5, -1.0, -1.5 },
                { +0.5, -1.0, +1.5 },
                { -0.5, +1.0, +1.5 },
                { -0.5, +1.0, -1.5 },
                { -0.5, -1.0, -1.5 },
                { -0.5, -1.0, +1.5 }
            }
        } ;

        EXPECT_EQ(referenceVertices, cuboid.getVertices()) << referenceVertices << cuboid.getVertices() ;

    }

    {

        EXPECT_ANY_THROW(Cuboid::Undefined().getVertices()) ;

    }

}

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, IntersectionWith_Line)
// {

//     using ostk::core::types::Real ;

//     using ostk::math::geom::d3::objects::Point ;
//     using ostk::math::geom::d3::objects::PointSet ;
//     using ostk::math::geom::d3::objects::Line ;
//     using ostk::math::geom::d3::objects::Cuboid ;
//     using ostk::math::geom::d3::Intersection ;

//     {

//         FAIL() ;

//     }

//     {

//         EXPECT_ANY_THROW(Cuboid::Undefined().intersectionWith(Line::Undefined())) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, IntersectionWith_Ray)
// {

//     using ostk::core::types::Real ;

//     using ostk::math::geom::d3::objects::Point ;
//     using ostk::math::geom::d3::objects::PointSet ;
//     using ostk::math::geom::d3::objects::Ray ;
//     using ostk::math::geom::d3::objects::Cuboid ;
//     using ostk::math::geom::d3::Intersection ;

//     {

//         FAIL() ;

//     }

//     {

//         EXPECT_ANY_THROW(Cuboid::Undefined().intersectionWith(Ray::Undefined())) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, IntersectionWith_Segment)
// {

//     using ostk::core::types::Real ;

//     using ostk::math::geom::d3::objects::Point ;
//     using ostk::math::geom::d3::objects::PointSet ;
//     using ostk::math::geom::d3::objects::Segment ;
//     using ostk::math::geom::d3::objects::Cuboid ;
//     using ostk::math::geom::d3::Intersection ;

//     {

//         FAIL() ;

//     }

//     {

//         EXPECT_ANY_THROW(Cuboid::Undefined().intersectionWith(Segment::Undefined())) ;

//     }

// }

// TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, IntersectionWith_Pyramid)
// {

//     using ostk::math::geom::d3::objects::Point ;
//     using ostk::math::geom::d3::objects::Cuboid ;
//     using ostk::math::geom::d3::objects::Pyramid ;

//     {

//         FAIL() ;

//     }

//     {

//         EXPECT_ANY_THROW(Cuboid::Undefined().intersectionWith(Pyramid::Undefined())) ;

//     }

// }

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, ApplyTransformation)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::Angle ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Cuboid ;
    using ostk::math::geom::d3::Transformation ;
    using ostk::math::geom::d3::trf::rot::Quaternion ;
    using ostk::math::geom::d3::trf::rot::RotationVector ;

    // Translation

    {

        const Point center = { 1.0, 2.0, 3.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        Cuboid cuboid = { center, axes, extent } ;

        cuboid.applyTransformation(Transformation::Translation({ 4.0, 5.0, 6.0 })) ;

        const Cuboid referenceCuboid = { { 5.0, 7.0, 9.0 }, axes, extent } ;

        EXPECT_EQ(referenceCuboid, cuboid) << cuboid ;

    }

    // Rotation

    {

        const Point center = { 1.0, 2.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        Cuboid cuboid = { center, axes, extent } ;

        cuboid.applyTransformation(Transformation::Rotation(RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(90.0)))) ;

        const Cuboid referenceCuboid = { { 1.0, 0.0, 2.0 }, axes, { 1.0, 3.0, 2.0 } } ;

        EXPECT_TRUE(cuboid.isNear(referenceCuboid, Real::Epsilon())) << referenceCuboid << cuboid ;

    }

    {

        const Point center = { 1.0, 2.0, 0.0 } ;
        const std::array<Vector3d, 3> axes = { Vector3d { 1.0, 0.0, 0.0 }, Vector3d { 0.0, 1.0, 0.0 }, Vector3d { 0.0, 0.0, 1.0 } } ;
        const std::array<Real, 3> extent = { 1.0, 2.0, 3.0 } ;

        Cuboid cuboid = { center, axes, extent } ;

        EXPECT_ANY_THROW(cuboid.applyTransformation(Transformation::Undefined())) ;
        EXPECT_ANY_THROW(Cuboid::Undefined().applyTransformation(Transformation::Undefined())) ;
        EXPECT_ANY_THROW(Cuboid::Undefined().applyTransformation(Transformation::Identity())) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, Undefined)
{

    using ostk::math::geom::d3::objects::Cuboid ;

    {

        EXPECT_NO_THROW(Cuboid::Undefined()) ;
        EXPECT_FALSE(Cuboid::Undefined().isDefined()) ;

    }

}

TEST (OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Cuboid, Cube)
{

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Cuboid ;

    {

        const Cuboid cube = Cuboid::Cube({ 0.0, 0.0, 0.0 }, 1.0) ;

        EXPECT_TRUE(cube.isDefined()) ;

        EXPECT_EQ(Point(0.0, 0.0, 0.0), cube.getCenter()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
