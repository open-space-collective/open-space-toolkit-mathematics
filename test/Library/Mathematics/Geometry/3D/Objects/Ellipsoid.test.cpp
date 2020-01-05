////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Ellipsoid.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Pyramid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Plane.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Ray.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Line.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/PointSet.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Constructor)
{

    using ostk::math::geom::d3::trf::rot::Quaternion ;
    using ostk::math::geom::d3::objects::Ellipsoid ;

    {

        ASSERT_NO_THROW(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0)) ;

    }

    {

        ASSERT_NO_THROW(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0, Quaternion::XYZS(0.0, 0.0, 0.0, 1.0))) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Clone)
{

    using ostk::math::geom::d3::objects::Ellipsoid ;

    {

        ASSERT_NO_THROW(const Ellipsoid* ellipsoidPtr = Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).clone() ; delete ellipsoidPtr ;) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, EqualToOperator)
{

    using ostk::math::geom::Angle ;
    using ostk::math::geom::d3::objects::Ellipsoid ;
    using ostk::math::geom::d3::trf::rot::Quaternion ;
    using ostk::math::geom::d3::trf::rot::RotationVector ;

    {

        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) == Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0)) ;

    }

    {

        ASSERT_FALSE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) == Ellipsoid({ 1.0, 2.0, 4.0 }, 4.0, 5.0, 6.0)) ;
        ASSERT_FALSE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) == Ellipsoid({ 1.0, 2.0, 3.0 }, 3.0, 5.0, 6.0)) ;

    }

    {

        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) == Ellipsoid({ 1.0, 2.0, 3.0 }, 5.0, 4.0, 6.0, Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(+90.0))))) ;
        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) == Ellipsoid({ 1.0, 2.0, 3.0 }, 5.0, 4.0, 6.0, Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))))) ;

    }

    {

        ASSERT_FALSE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) == Ellipsoid::Undefined()) ;
        ASSERT_FALSE(Ellipsoid::Undefined() == Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0)) ;
        ASSERT_FALSE(Ellipsoid::Undefined() == Ellipsoid::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, NotEqualToOperator)
{

    using ostk::math::geom::Angle ;
    using ostk::math::geom::d3::objects::Ellipsoid ;
    using ostk::math::geom::d3::trf::rot::Quaternion ;
    using ostk::math::geom::d3::trf::rot::RotationVector ;

    {

        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) != Ellipsoid({ 1.0, 2.0, 4.0 }, 4.0, 5.0, 6.0)) ;
        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) != Ellipsoid({ 1.0, 2.0, 3.0 }, 3.0, 5.0, 6.0)) ;

    }

    {

        ASSERT_FALSE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) != Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0)) ;

    }

    {

        ASSERT_FALSE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) != Ellipsoid({ 1.0, 2.0, 3.0 }, 5.0, 4.0, 6.0, Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(+90.0))))) ;
        ASSERT_FALSE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) != Ellipsoid({ 1.0, 2.0, 3.0 }, 5.0, 4.0, 6.0, Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(-90.0))))) ;

    }

    {

        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) != Ellipsoid::Undefined()) ;
        ASSERT_TRUE(Ellipsoid::Undefined() != Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0)) ;
        ASSERT_TRUE(Ellipsoid::Undefined() != Ellipsoid::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, StreamOperator)
{

    using ostk::math::geom::d3::objects::Ellipsoid ;

    {

        testing::internal::CaptureStdout() ;

        ASSERT_NO_THROW(std::cout << Ellipsoid({ 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0) << std::endl) ;

        ASSERT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, IsDefined)
{

    using ostk::math::geom::d3::objects::Ellipsoid ;

    {

        ASSERT_TRUE(Ellipsoid({ 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0).isDefined()) ;
        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).isDefined()) ;

    }

    {

        ASSERT_FALSE(Ellipsoid::Undefined().isDefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Intersects_Point)
{

    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Ellipsoid ;

    {

        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).intersects(Point(+5.0, +2.0, +3.0))) ;
        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).intersects(Point(-3.0, +2.0, +3.0))) ;

        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).intersects(Point(+1.0, +7.0, +3.0))) ;
        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).intersects(Point(+1.0, -3.0, +3.0))) ;

        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).intersects(Point(+1.0, +2.0, +9.0))) ;
        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).intersects(Point(+1.0, +2.0, -3.0))) ;

    }

    {

        ASSERT_FALSE(Ellipsoid(Point::Origin(), 4.0, 5.0, 6.0).intersects(Point::Origin())) ;

    }

    {

        ASSERT_ANY_THROW(Ellipsoid::Undefined().intersects(Point::Undefined())) ;
        ASSERT_ANY_THROW(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).intersects(Point::Undefined())) ;
        ASSERT_ANY_THROW(Ellipsoid::Undefined().intersects(Point(0.0, 0.0, 0.0))) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Intersects_PointSet)
{

    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::PointSet ;
    using ostk::math::geom::d3::objects::Ellipsoid ;

    {

        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).intersects(PointSet({ { +5.0, +2.0, +3.0 }, { -3.0, +2.0, +3.0 }, { +1.0, +7.0, +3.0 }, { +1.0, -3.0, +3.0 }, { +1.0, +2.0, +9.0 }, { +1.0, +2.0, -3.0 } }))) ;
        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).intersects(PointSet({ { 0.0, 0.0, 0.0 }, { +1.0, +2.0, -3.0 } }))) ;

    }

    {

        ASSERT_FALSE(Ellipsoid(Point::Origin(), 4.0, 5.0, 6.0).intersects(PointSet::Empty())) ;

    }

    {

        ASSERT_ANY_THROW(Ellipsoid::Undefined().intersects(PointSet::Empty())) ;
        ASSERT_ANY_THROW(Ellipsoid::Undefined().intersects(PointSet({ { +5.0, +2.0, +3.0 }, { +5.0, +2.0, +3.0 } }))) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Intersects_Line)
{

    using ostk::core::types::Real ;

    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Line ;
    using ostk::math::geom::d3::objects::Ellipsoid ;

    {

        const Ellipsoid ellipsoid = { Point::Origin(), 1.0, 2.0, 3.0 } ;

        ASSERT_FALSE(ellipsoid.intersects(Line({ -10.0, -3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ -10.0, -2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ -10.0, -2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ -10.0, -1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ -10.0, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ -10.0, +1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ -10.0, +2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ -10.0, +2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ -10.0, +3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Line({ +0.0, -3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ +0.0, -2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +0.0, -2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +0.0, -1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +0.0, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +0.0, +1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +0.0, +2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ +0.0, +2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ +0.0, +3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Line({ +10.0, -3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ +10.0, -2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +10.0, -2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +10.0, -1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +10.0, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +10.0, +1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +10.0, +2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ +10.0, +2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ +10.0, +3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Line({ -10.0, -3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ -10.0, -2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ -10.0, -2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ -10.0, -1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ -10.0, +0.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ -10.0, +1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ -10.0, +2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ -10.0, +2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ -10.0, +3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Line({ +0.0, -3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ +0.0, -2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +0.0, -2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +0.0, -1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +0.0, +0.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +0.0, +1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +0.0, +2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ +0.0, +2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ +0.0, +3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Line({ +10.0, -3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ +10.0, -2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +10.0, -2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +10.0, -1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +10.0, +0.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +10.0, +1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +10.0, +2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ +10.0, +2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ +10.0, +3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Line({ -2.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ -1.1, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ -1.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +0.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +1.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ +1.1, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ +2.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Line({ -2.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ -1.1, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ -1.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +0.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +1.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ +1.1, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ +2.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Line({ -2.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ -1.1, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ -1.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +0.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +1.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ +1.1, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ +2.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Line({ -2.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ -1.1, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ -1.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +0.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +1.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ +1.1, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ +2.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Line({ -2.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ -1.1, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ -1.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +0.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +1.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ +1.1, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ +2.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Line({ -2.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ -1.1, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ -1.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +0.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ +1.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ +1.1, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ +2.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;

    }

    {

        const Real equatorialRadius_m = 6378136.3 ;
        const Real polarRadius_m = equatorialRadius_m * (1.0 - 0.003352810664747) ;

        const Ellipsoid ellipsoid = { Point::Origin(), equatorialRadius_m, equatorialRadius_m, polarRadius_m } ;

        ASSERT_FALSE(ellipsoid.intersects(Line({ 0.0, -7000e3, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ 0.0, -equatorialRadius_m - 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        // ASSERT_TRUE(ellipsoid.intersects(Line({ 0.0, -equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ; // [TBI] Fix precision issues
        ASSERT_TRUE(ellipsoid.intersects(Line({ 0.0, -equatorialRadius_m + 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ 0.0, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Line({ 0.0, +equatorialRadius_m - 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        // ASSERT_TRUE(ellipsoid.intersects(Line({ 0.0, +equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ; // [TBI] Fix precision issues
        ASSERT_FALSE(ellipsoid.intersects(Line({ 0.0, +equatorialRadius_m + 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Line({ 0.0, +7000e3, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

    }

    {

        ASSERT_ANY_THROW(Ellipsoid::Undefined().intersects(Line::Undefined())) ;
        ASSERT_ANY_THROW(Ellipsoid(Point::Origin(), 1.0, 1.0, 1.0).intersects(Line::Undefined())) ;
        ASSERT_ANY_THROW(Ellipsoid::Undefined().intersects(Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }))) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Intersects_Ray)
{

    using ostk::core::types::Real ;

    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Ray ;
    using ostk::math::geom::d3::objects::Ellipsoid ;

    {

        const Ellipsoid ellipsoid = { Point::Origin(), 1.0, 2.0, 3.0 } ;

        ASSERT_FALSE(ellipsoid.intersects(Ray({ -10.0, -3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ -10.0, -2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ -10.0, -2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ -10.0, -1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ -10.0, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ -10.0, +1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ -10.0, +2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ -10.0, +2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ -10.0, +3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Ray({ +0.0, -3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +0.0, -2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ +0.0, -2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ +0.0, -1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ +0.0, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ +0.0, +1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ +0.0, +2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +0.0, +2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +0.0, +3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Ray({ +10.0, -3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +10.0, -2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +10.0, -2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +10.0, -1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +10.0, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +10.0, +1.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +10.0, +2.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +10.0, +2.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +10.0, +3.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Ray({ -10.0, -3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ -10.0, -2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ -10.0, -2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ -10.0, -1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ -10.0, +0.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ -10.0, +1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ -10.0, +2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ -10.0, +2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ -10.0, +3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Ray({ +0.0, -3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +0.0, -2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ +0.0, -2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ +0.0, -1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ +0.0, +0.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ +0.0, +1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ +0.0, +2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +0.0, +2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +0.0, +3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Ray({ +10.0, -3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +10.0, -2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ +10.0, -2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ +10.0, -1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ +10.0, +0.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ +10.0, +1.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ +10.0, +2.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +10.0, +2.1, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +10.0, +3.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Ray({ -2.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ -1.1, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ -1.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ +0.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ +1.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +1.1, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +2.0, -10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Ray({ -2.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ -1.1, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ -1.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ +0.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ +1.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +1.1, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +2.0, +0.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Ray({ -2.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ -1.1, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ -1.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +0.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +1.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +1.1, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +2.0, +10.0, 0.0 }, { 0.0, +1.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Ray({ -2.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ -1.1, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ -1.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +0.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +1.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +1.1, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +2.0, -10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Ray({ -2.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ -1.1, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ -1.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ +0.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ +1.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +1.1, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +2.0, +0.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Ray({ -2.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ -1.1, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ -1.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ +0.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ +1.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +1.1, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +2.0, +10.0, 0.0 }, { 0.0, -1.0, 0.0 }))) ;

    }

    {

        const Real equatorialRadius_m = 6378136.3 ;
        const Real polarRadius_m = equatorialRadius_m * (1.0 - 0.003352810664747) ;

        const Ellipsoid ellipsoid = { Point::Origin(), equatorialRadius_m, equatorialRadius_m, polarRadius_m } ;

        ASSERT_FALSE(ellipsoid.intersects(Ray({ -10000e3, -7000e3, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ -10000e3, -equatorialRadius_m - 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        // ASSERT_TRUE(ellipsoid.intersects(Ray({ -10000e3, -equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ; // [TBI] Fix precision issues
        ASSERT_TRUE(ellipsoid.intersects(Ray({ -10000e3, -equatorialRadius_m + 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ -10000e3, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ -10000e3, +equatorialRadius_m - 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        // ASSERT_TRUE(ellipsoid.intersects(Ray({ -10000e3, +equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ; // [TBI] Fix precision issues
        ASSERT_FALSE(ellipsoid.intersects(Ray({ -10000e3, +equatorialRadius_m + 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ -10000e3, +7000e3, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Ray({ 0.0, -7000e3, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ 0.0, -equatorialRadius_m - 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        // ASSERT_TRUE(ellipsoid.intersects(Ray({ 0.0, -equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ; // [TBI] Fix precision issues
        ASSERT_TRUE(ellipsoid.intersects(Ray({ 0.0, -equatorialRadius_m + 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ 0.0, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Ray({ 0.0, +equatorialRadius_m - 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        // ASSERT_TRUE(ellipsoid.intersects(Ray({ 0.0, +equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ; // [TBI] Fix precision issues
        ASSERT_FALSE(ellipsoid.intersects(Ray({ 0.0, +equatorialRadius_m + 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ 0.0, +7000e3, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Ray({ +10000e3, -7000e3, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +10000e3, -equatorialRadius_m - 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +10000e3, -equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +10000e3, -equatorialRadius_m + 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +10000e3, +0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +10000e3, +equatorialRadius_m - 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +10000e3, +equatorialRadius_m, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +10000e3, +equatorialRadius_m + 0.1, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Ray({ +10000e3, +7000e3, 0.0 }, { +1.0, 0.0, 0.0 }))) ;

    }

    {

        ASSERT_ANY_THROW(Ellipsoid::Undefined().intersects(Ray::Undefined())) ;
        ASSERT_ANY_THROW(Ellipsoid(Point::Origin(), 1.0, 1.0, 1.0).intersects(Ray::Undefined())) ;
        ASSERT_ANY_THROW(Ellipsoid::Undefined().intersects(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }))) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Intersects_Segment)
{

    using ostk::core::types::Real ;

    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Segment ;
    using ostk::math::geom::d3::objects::Ellipsoid ;

    {

        const Ellipsoid ellipsoid = { Point::Origin(), 1.0, 2.0, 3.0 } ;

        ASSERT_FALSE(ellipsoid.intersects(Segment({ -10.0, -3.0, 0.0 }, { +10.0, -3.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Segment({ -10.0, -2.1, 0.0 }, { +10.0, -2.1, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -10.0, -2.0, 0.0 }, { +10.0, -2.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -10.0, -1.0, 0.0 }, { +10.0, -1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -10.0, +0.0, 0.0 }, { +10.0, +0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -10.0, +1.0, 0.0 }, { +10.0, +1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -10.0, +2.0, 0.0 }, { +10.0, +2.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Segment({ -10.0, +2.1, 0.0 }, { +10.0, +2.1, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Segment({ -10.0, +3.0, 0.0 }, { +10.0, +3.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Segment({ -2.0, -10.0, 0.0 }, { -2.0, +10.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Segment({ -1.1, -10.0, 0.0 }, { -1.1, +10.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -1.0, -10.0, 0.0 }, { -1.0, +10.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ +0.0, -10.0, 0.0 }, { +0.0, +10.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ +1.0, -10.0, 0.0 }, { +1.0, +10.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Segment({ +1.1, -10.0, 0.0 }, { +1.1, +10.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Segment({ +2.0, -10.0, 0.0 }, { +2.0, +10.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Segment({ -10.0, 0.0, -4.0 }, { +10.0, 0.0, -4.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Segment({ -10.0, 0.0, -3.1 }, { +10.0, 0.0, -3.1 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -10.0, 0.0, -3.0 }, { +10.0, 0.0, -3.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -10.0, 0.0, -2.0 }, { +10.0, 0.0, -2.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -10.0, 0.0, -1.0 }, { +10.0, 0.0, -1.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -10.0, 0.0, +0.0 }, { +10.0, 0.0, +0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -10.0, 0.0, +1.0 }, { +10.0, 0.0, +1.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -10.0, 0.0, +2.0 }, { +10.0, 0.0, +2.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -10.0, 0.0, +3.0 }, { +10.0, 0.0, +3.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Segment({ -10.0, 0.0, +3.1 }, { +10.0, 0.0, +3.1 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Segment({ -10.0, 0.0, +4.0 }, { +10.0, 0.0, +4.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Segment({ -10.0, 0.0, 0.0 }, { -1.1, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -10.0, 0.0, 0.0 }, { -1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -10.0, 0.0, 0.0 }, { -0.9, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ +10.0, 0.0, 0.0 }, { +0.9, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ +10.0, 0.0, 0.0 }, { +1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Segment({ +10.0, 0.0, 0.0 }, { +1.1, 0.0, 0.0 }))) ;

    }

    {

        const Real equatorialRadius_m = 6378136.3 ;
        const Real polarRadius_m = equatorialRadius_m * (1.0 - 0.003352810664747) ;

        const Ellipsoid ellipsoid = { Point::Origin(), equatorialRadius_m, equatorialRadius_m, polarRadius_m } ;

        ASSERT_FALSE(ellipsoid.intersects(Segment({ -10000e3, -7000e3, 0.0 }, { +10000e3, -7000e3, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Segment({ -10000e3, -equatorialRadius_m - 0.1, 0.0 }, { +10000e3, -equatorialRadius_m - 0.1, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -10000e3, -equatorialRadius_m, 0.0 }, { +10000e3, -equatorialRadius_m, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -10000e3, -equatorialRadius_m + 0.1, 0.0 }, { +10000e3, -equatorialRadius_m + 0.1, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -10000e3, +0.0, 0.0 }, { +10000e3, +0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -10000e3, +equatorialRadius_m - 0.1, 0.0 }, { +10000e3, +equatorialRadius_m - 0.1, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -10000e3, +equatorialRadius_m, 0.0 }, { +10000e3, +equatorialRadius_m, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Segment({ -10000e3, +equatorialRadius_m + 0.1, 0.0 }, { +10000e3, +equatorialRadius_m + 0.1, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Segment({ -10000e3, +7000e3, 0.0 }, { +10000e3, +7000e3, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Segment({ -7000e3, -10000e3, 0.0 }, { -7000e3, +10000e3, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Segment({ -equatorialRadius_m - 0.1, -10000e3, 0.0 }, { -equatorialRadius_m - 0.1, +10000e3, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -equatorialRadius_m, -10000e3, 0.0 }, { -equatorialRadius_m, +10000e3, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -equatorialRadius_m + 0.1, -10000e3, 0.0 }, { -equatorialRadius_m + 0.1, +10000e3, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ +0.0, -10000e3, 0.0 }, { +0.0, +10000e3, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ +equatorialRadius_m - 0.1, -10000e3, 0.0 }, { +equatorialRadius_m - 0.1, +10000e3, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ +equatorialRadius_m, -10000e3, 0.0 }, { +equatorialRadius_m, +10000e3, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Segment({ +equatorialRadius_m + 0.1, -10000e3, 0.0 }, { +equatorialRadius_m + 0.1, +10000e3, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Segment({ +7000e3, -10000e3, 0.0 }, { +7000e3, +10000e3, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Segment({ -10000e3, 0.0, -7000e3 }, { +10000e3, 0.0, -7000e3 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Segment({ -10000e3, 0.0, -polarRadius_m - 0.1 }, { +10000e3, 0.0, -polarRadius_m - 0.1 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -10000e3, 0.0, -polarRadius_m }, { +10000e3, 0.0, -polarRadius_m }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -10000e3, 0.0, -polarRadius_m + 0.1 }, { +10000e3, 0.0, -polarRadius_m + 0.1 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -10000e3, 0.0, +0.0 }, { +10000e3, 0.0, +0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -10000e3, 0.0, +polarRadius_m - 0.1 }, { +10000e3, 0.0, +polarRadius_m - 0.1 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Segment({ -10000e3, 0.0, +polarRadius_m }, { +10000e3, 0.0, +polarRadius_m }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Segment({ -10000e3, 0.0, +polarRadius_m + 0.1 }, { +10000e3, 0.0, +polarRadius_m + 0.1 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Segment({ -10000e3, 0.0, +7000e3 }, { +10000e3, 0.0, +7000e3 }))) ;

    }

    {

        ASSERT_ANY_THROW(Ellipsoid(Point::Origin(), 1.0, 1.0, 1.0).intersects(Segment::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Intersects_Plane)
{

    using ostk::core::types::Real ;

    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Plane ;
    using ostk::math::geom::d3::objects::Ellipsoid ;

    {

        const Ellipsoid ellipsoid = { Point::Origin(), 1.0, 2.0, 3.0 } ;

        ASSERT_TRUE(ellipsoid.intersects(Plane({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Plane({ -2.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Plane({ -1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Plane({ +0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Plane({ +1.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Plane({ +2.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Plane({ 0.0, -3.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Plane({ 0.0, -2.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Plane({ 0.0, -1.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Plane({ 0.0, +0.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Plane({ 0.0, +1.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Plane({ 0.0, +2.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Plane({ 0.0, +3.0, 0.0 }, { 0.0, 1.0, 0.0 }))) ;

        ASSERT_FALSE(ellipsoid.intersects(Plane({ 0.0, 0.0, -4.0 }, { 0.0, 0.0, 1.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Plane({ 0.0, 0.0, -3.0 }, { 0.0, 0.0, 1.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Plane({ 0.0, 0.0, -2.0 }, { 0.0, 0.0, 1.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Plane({ 0.0, 0.0, -1.0 }, { 0.0, 0.0, 1.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Plane({ 0.0, 0.0, +0.0 }, { 0.0, 0.0, 1.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Plane({ 0.0, 0.0, +1.0 }, { 0.0, 0.0, 1.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Plane({ 0.0, 0.0, +2.0 }, { 0.0, 0.0, 1.0 }))) ;
        ASSERT_TRUE(ellipsoid.intersects(Plane({ 0.0, 0.0, +3.0 }, { 0.0, 0.0, 1.0 }))) ;
        ASSERT_FALSE(ellipsoid.intersects(Plane({ 0.0, 0.0, +4.0 }, { 0.0, 0.0, 1.0 }))) ;

    }

    {

        ASSERT_ANY_THROW(Ellipsoid::Undefined().intersects(Plane::Undefined())) ;
        ASSERT_ANY_THROW(Ellipsoid(Point::Origin(), 1.0, 1.0, 1.0).intersects(Plane::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Intersects_Pyramid)
{

    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Ellipsoid ;
    using ostk::math::geom::d3::objects::Pyramid ;

    {

        // See: Library_Mathematics_Geometry_3D_Objects_Pyramid.Intersects_Ellipsoid

        SUCCEED() ;

    }

    {

        ASSERT_ANY_THROW(Ellipsoid::Undefined().intersects(Pyramid::Undefined())) ;
        ASSERT_ANY_THROW(Ellipsoid(Point::Origin(), 1.0, 1.0, 1.0).intersects(Pyramid::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Contains_Point)
{

    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Ellipsoid ;

    {

        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).contains(Point(+5.0, +2.0, +3.0))) ;
        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).contains(Point(-3.0, +2.0, +3.0))) ;

        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).contains(Point(+1.0, +7.0, +3.0))) ;
        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).contains(Point(+1.0, -3.0, +3.0))) ;

        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).contains(Point(+1.0, +2.0, +9.0))) ;
        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).contains(Point(+1.0, +2.0, -3.0))) ;

    }

    {

        ASSERT_FALSE(Ellipsoid(Point::Origin(), 4.0, 5.0, 6.0).contains(Point::Origin())) ;

    }

    {

        ASSERT_ANY_THROW(Ellipsoid::Undefined().contains(Point::Undefined())) ;
        ASSERT_ANY_THROW(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).contains(Point::Undefined())) ;
        ASSERT_ANY_THROW(Ellipsoid::Undefined().contains(Point(0.0, 0.0, 0.0))) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Contains_PointSet)
{

    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::PointSet ;
    using ostk::math::geom::d3::objects::Ellipsoid ;

    {

        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).contains(PointSet({ { +5.0, +2.0, +3.0 }, { -3.0, +2.0, +3.0 }, { +1.0, +7.0, +3.0 }, { +1.0, -3.0, +3.0 }, { +1.0, +2.0, +9.0 }, { +1.0, +2.0, -3.0 } }))) ;

    }

    {

        ASSERT_FALSE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).contains(PointSet({ { +5.0, +2.0, +3.0 }, { -3.0, +2.0, +3.0 }, { +1.0, +7.0, +3.0 }, { +1.0, -3.0, +3.0 }, { +1.0, +2.0, +9.0 }, { 0.0, 0.0, 0.0 } }))) ;

    }

    {

        ASSERT_FALSE(Ellipsoid(Point::Origin(), 4.0, 5.0, 6.0).contains(PointSet::Empty())) ;

    }

    {

        ASSERT_ANY_THROW(Ellipsoid::Undefined().contains(PointSet::Empty())) ;
        ASSERT_ANY_THROW(Ellipsoid::Undefined().contains(PointSet({ { +5.0, +2.0, +3.0 }, { +5.0, +2.0, +3.0 } }))) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, GetCenter)
{

    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Ellipsoid ;

    {

        ASSERT_EQ(Point(1.0, 2.0, 3.0), Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).getCenter()) ;

    }

    {

        ASSERT_ANY_THROW(Ellipsoid::Undefined().getCenter()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, GetFirstPrincipalSemiAxis)
{

    using ostk::math::geom::d3::objects::Ellipsoid ;

    {

        ASSERT_EQ(4.0, Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).getFirstPrincipalSemiAxis()) ;

    }

    {

        ASSERT_ANY_THROW(Ellipsoid::Undefined().getFirstPrincipalSemiAxis()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, GetSecondPrincipalSemiAxis)
{

    using ostk::math::geom::d3::objects::Ellipsoid ;

    {

        ASSERT_EQ(5.0, Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).getSecondPrincipalSemiAxis()) ;

    }

    {

        ASSERT_ANY_THROW(Ellipsoid::Undefined().getSecondPrincipalSemiAxis()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, GetThirdPrincipalSemiAxis)
{

    using ostk::math::geom::d3::objects::Ellipsoid ;

    {

        ASSERT_EQ(6.0, Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).getThirdPrincipalSemiAxis()) ;

    }

    {

        ASSERT_ANY_THROW(Ellipsoid::Undefined().getThirdPrincipalSemiAxis()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, GetFirstAxis)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::Angle ;
    using ostk::math::geom::d3::objects::Ellipsoid ;
    using ostk::math::geom::d3::trf::rot::Quaternion ;
    using ostk::math::geom::d3::trf::rot::RotationVector ;

    {

        ASSERT_EQ(Vector3d(1.0, 0.0, 0.0), Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).getFirstAxis()) ;

        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0, Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(45.0)))).getFirstAxis().isNear(Vector3d(1.0, 1.0, 0.0).normalized(), Real::Epsilon())) ;

    }

    {

        ASSERT_ANY_THROW(Ellipsoid::Undefined().getFirstAxis()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, GetSecondAxis)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::Angle ;
    using ostk::math::geom::d3::objects::Ellipsoid ;
    using ostk::math::geom::d3::trf::rot::Quaternion ;
    using ostk::math::geom::d3::trf::rot::RotationVector ;

    {

        ASSERT_EQ(Vector3d(0.0, 1.0, 0.0), Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).getSecondAxis()) ;

        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0, Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(45.0)))).getSecondAxis().isNear(Vector3d(-1.0, 1.0, 0.0).normalized(), Real::Epsilon())) ;

    }

    {

        ASSERT_ANY_THROW(Ellipsoid::Undefined().getSecondAxis()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, GetThirdAxis)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::Angle ;
    using ostk::math::geom::d3::objects::Ellipsoid ;
    using ostk::math::geom::d3::trf::rot::Quaternion ;
    using ostk::math::geom::d3::trf::rot::RotationVector ;

    {

        ASSERT_EQ(Vector3d(0.0, 0.0, 1.0), Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).getThirdAxis()) ;

        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0, Quaternion::RotationVector(RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(45.0)))).getThirdAxis().isNear(Vector3d(0.0, -1.0, 1.0).normalized(), Real::Epsilon())) ;

    }

    {

        ASSERT_ANY_THROW(Ellipsoid::Undefined().getThirdAxis()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, GetOrientation)
{

    using ostk::math::geom::d3::trf::rot::Quaternion ;
    using ostk::math::geom::d3::objects::Ellipsoid ;

    {

        ASSERT_EQ(Quaternion::Unit(), Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).getOrientation()) ;

    }

    {

        ASSERT_EQ(Quaternion::XYZS(1.0, 0.0, 0.0, 0.0), Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0, Quaternion::XYZS(1.0, 0.0, 0.0, 0.0)).getOrientation()) ;

    }

    {

        ASSERT_ANY_THROW(Ellipsoid::Undefined().getOrientation()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, GetMatrix)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Matrix3d ;
    using ostk::math::geom::Angle ;
    using ostk::math::geom::d3::objects::Ellipsoid ;
    using ostk::math::geom::d3::trf::rot::Quaternion ;
    using ostk::math::geom::d3::trf::rot::RotationVector ;
    using ostk::math::geom::d3::trf::rot::RotationMatrix ;

    {

        Matrix3d referenceEllipsoidMatrix ;

        referenceEllipsoidMatrix << 1.0 / (4.0 * 4.0),  0.0,                0.0,
                                    0.0,                1.0 / (5.0 * 5.0),  0.0,
                                    0.0,                0.0,                1.0 / (6.0 * 6.0) ;

        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).getMatrix().isNear(referenceEllipsoidMatrix, Real::Epsilon())) ;

    }

    {

        const Matrix3d referenceRotationMatrix = RotationMatrix::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(45.0))).getMatrix() ;

        Matrix3d referenceEllipsoidMatrix ;

        referenceEllipsoidMatrix << 1.0 / (4.0 * 4.0),  0.0,                0.0,
                                    0.0,                1.0 / (5.0 * 5.0),  0.0,
                                    0.0,                0.0,                1.0 / (6.0 * 6.0) ;

        referenceEllipsoidMatrix = referenceRotationMatrix.transpose() * referenceEllipsoidMatrix * referenceRotationMatrix ;

        ASSERT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0, Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(45.0)))).getMatrix().isNear(referenceEllipsoidMatrix, Real::Epsilon())) ;

    }

    {

        ASSERT_ANY_THROW(Ellipsoid::Undefined().getMatrix()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, IntersectionWith_Line)
{

    using ostk::core::types::Real ;

    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::PointSet ;
    using ostk::math::geom::d3::objects::Line ;
    using ostk::math::geom::d3::objects::Ellipsoid ;
    using ostk::math::geom::d3::Intersection ;

    {

        const Line line = { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(line) ;

        ASSERT_TRUE(intersection.isDefined()) ;
        ASSERT_TRUE(intersection.accessComposite().isDefined()) ;

        ASSERT_TRUE(intersection.accessComposite().is<PointSet>()) ;

        const PointSet pointSet = intersection.accessComposite().as<PointSet>() ;

        ASSERT_EQ(2, pointSet.getSize()) ;

        ASSERT_TRUE(pointSet.isNear(PointSet({ { -1.0, 0.0, 0.0 }, { +1.0, 0.0, 0.0 } }), Real::Epsilon())) ;

    }

    {

        const Line line = { { 0.0, 0.0, -4.0 }, { 0.0, 0.0, 1.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(line) ;

        ASSERT_TRUE(intersection.isDefined()) ;
        ASSERT_TRUE(intersection.accessComposite().isDefined()) ;

        ASSERT_TRUE(intersection.accessComposite().is<PointSet>()) ;

        const PointSet pointSet = intersection.accessComposite().as<PointSet>() ;

        ASSERT_EQ(2, pointSet.getSize()) ;

        ASSERT_TRUE(pointSet.isNear(PointSet({ { 0.0, 0.0, -3.0 }, { 0.0, 0.0, +3.0 } }), Real::Epsilon())) ;

    }

    {

        const Line line = { { 0.0, 0.0, +4.0 }, { 0.0, 0.0, 1.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(line) ;

        ASSERT_TRUE(intersection.isDefined()) ;
        ASSERT_TRUE(intersection.accessComposite().isDefined()) ;

        ASSERT_TRUE(intersection.accessComposite().is<PointSet>()) ;

        const PointSet pointSet = intersection.accessComposite().as<PointSet>() ;

        ASSERT_EQ(2, pointSet.getSize()) ;

        ASSERT_TRUE(pointSet.isNear(PointSet({ { 0.0, 0.0, -3.0 }, { 0.0, 0.0, +3.0 } }), Real::Epsilon())) ;

    }

    {

        const Line line = { { 0.0, 0.0, +3.0 }, { 1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(line) ;

        ASSERT_TRUE(intersection.isDefined()) ;
        ASSERT_TRUE(intersection.accessComposite().isDefined()) ;

        ASSERT_TRUE(intersection.accessComposite().is<Point>()) ;

        const Point point = intersection.accessComposite().as<Point>() ;

        ASSERT_TRUE(point.isNear(Point(0.0, 0.0, +3.0), Real::Epsilon())) ;

    }

    {

        const Line line = { { 0.0, 0.0, -3.0 }, { 1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(line) ;

        ASSERT_TRUE(intersection.isDefined()) ;
        ASSERT_TRUE(intersection.accessComposite().isDefined()) ;

        ASSERT_TRUE(intersection.accessComposite().is<Point>()) ;

        const Point point = intersection.accessComposite().as<Point>() ;

        ASSERT_TRUE(point.isNear(Point(0.0, 0.0, -3.0), Real::Epsilon())) ;

    }

    {

        const Line line = { { 0.0, +3.0, 0.0 }, { 1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(line) ;

        ASSERT_TRUE(intersection.isEmpty()) ;

    }

    {

        ASSERT_ANY_THROW(Ellipsoid::Undefined().intersectionWith(Line::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, IntersectionWith_Ray)
{

    using ostk::core::types::Real ;

    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::PointSet ;
    using ostk::math::geom::d3::objects::Ray ;
    using ostk::math::geom::d3::objects::Ellipsoid ;
    using ostk::math::geom::d3::Intersection ;

    // onlyInSight = false

    {

        const Ray ray = { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray) ;

        ASSERT_TRUE(intersection.isDefined()) ;
        ASSERT_TRUE(intersection.accessComposite().isDefined()) ;

        ASSERT_TRUE(intersection.accessComposite().is<Point>()) ;

        const Point point = intersection.accessComposite().as<Point>() ;

        ASSERT_TRUE(point.isNear(Point(1.0, 0.0, 0.0), Real::Epsilon())) ;

    }

    {

        const Ray ray = { { 0.0, 0.0, -4.0 }, { 0.0, 0.0, 1.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray) ;

        ASSERT_TRUE(intersection.isDefined()) ;
        ASSERT_TRUE(intersection.accessComposite().isDefined()) ;

        ASSERT_TRUE(intersection.accessComposite().is<PointSet>()) ;

        const PointSet pointSet = intersection.accessComposite().as<PointSet>() ;

        ASSERT_EQ(2, pointSet.getSize()) ;

        ASSERT_TRUE(pointSet.isNear(PointSet({ { 0.0, 0.0, -3.0 }, { 0.0, 0.0, +3.0 } }), Real::Epsilon())) ;

    }

    {

        const Ray ray = { { 0.0, 0.0, -10.0 }, { 0.0, 0.0, 1.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray) ;

        ASSERT_TRUE(intersection.isDefined()) ;
        ASSERT_TRUE(intersection.accessComposite().isDefined()) ;

        ASSERT_TRUE(intersection.accessComposite().is<PointSet>()) ;

        const PointSet pointSet = intersection.accessComposite().as<PointSet>() ;

        ASSERT_EQ(2, pointSet.getSize()) ;

        ASSERT_TRUE(pointSet.isNear(PointSet({ { 0.0, 0.0, -3.0 }, { 0.0, 0.0, +3.0 } }), 1e-10)) ;

    }

    {

        const Ray ray = { { 0.0, 0.0, -100.0 }, { 0.0, 0.0, 1.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray) ;

        ASSERT_TRUE(intersection.isDefined()) ;
        ASSERT_TRUE(intersection.accessComposite().isDefined()) ;

        ASSERT_TRUE(intersection.accessComposite().is<PointSet>()) ;

        const PointSet pointSet = intersection.accessComposite().as<PointSet>() ;

        ASSERT_EQ(2, pointSet.getSize()) ;

        ASSERT_TRUE(pointSet.isNear(PointSet({ { 0.0, 0.0, -3.0 }, { 0.0, 0.0, +3.0 } }), 1e-10)) ;

    }

    {

        const Ray ray = { { 0.0, 0.0, -1000.0 }, { 0.0, 0.0, 1.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray) ;

        ASSERT_TRUE(intersection.isDefined()) ;
        ASSERT_TRUE(intersection.accessComposite().isDefined()) ;

        ASSERT_TRUE(intersection.accessComposite().is<PointSet>()) ;

        const PointSet pointSet = intersection.accessComposite().as<PointSet>() ;

        ASSERT_EQ(2, pointSet.getSize()) ;

        ASSERT_TRUE(pointSet.isNear(PointSet({ { 0.0, 0.0, -3.0 }, { 0.0, 0.0, +3.0 } }), 1e-5)) ;

    }

    {

        const Ray ray = { { 0.0, 0.0, +4.0 }, { 0.0, 0.0, 1.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray) ;

        ASSERT_TRUE(intersection.isEmpty()) ;

    }

    // Disabled because this tests fails when coverage is enabled (for some reason...)

    // {

    //     const Ray ray = { { 0.0, 0.0, +3.0 }, { 1.0, 0.0, 0.0 } } ;
    //     const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

    //     const Intersection intersection = ellipsoid.intersectionWith(ray) ;

    //     ASSERT_TRUE(intersection.isDefined()) ;
    //     ASSERT_TRUE(intersection.accessComposite().isDefined()) ;

    //     ASSERT_TRUE(intersection.accessComposite().is<Point>()) ;

    //     const Point point = intersection.accessComposite().as<Point>() ;

    //     ASSERT_TRUE(point.isNear(Point(0.0, 0.0, +3.0), Real::Epsilon())) ;

    // }

    // {

    //     const Ray ray = { { 0.0, 0.0, -3.0 }, { 1.0, 0.0, 0.0 } } ;
    //     const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

    //     const Intersection intersection = ellipsoid.intersectionWith(ray) ;

    //     ASSERT_TRUE(intersection.isDefined()) ;
    //     ASSERT_TRUE(intersection.accessComposite().isDefined()) ;

    //     ASSERT_TRUE(intersection.accessComposite().is<Point>()) ;

    //     const Point point = intersection.accessComposite().as<Point>() ;

    //     ASSERT_TRUE(point.isNear(Point(0.0, 0.0, -3.0), Real::Epsilon())) ;

    // }

    {

        const Ray ray = { { 0.0, +3.0, 0.0 }, { 1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray) ;

        ASSERT_TRUE(intersection.isEmpty()) ;

    }

    // onlyInSight = true

    {

        const Ray ray = { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray, true) ;

        ASSERT_TRUE(intersection.isDefined()) ;
        ASSERT_TRUE(intersection.accessComposite().isDefined()) ;

        ASSERT_TRUE(intersection.accessComposite().is<Point>()) ;

        const Point point = intersection.accessComposite().as<Point>() ;

        ASSERT_TRUE(point.isNear(Point(1.0, 0.0, 0.0), Real::Epsilon())) ;

    }

    {

        const Ray ray = { { 0.0, 0.0, -4.0 }, { 0.0, 0.0, 1.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray, true) ;

        ASSERT_TRUE(intersection.isDefined()) ;
        ASSERT_TRUE(intersection.accessComposite().isDefined()) ;

        ASSERT_TRUE(intersection.accessComposite().is<Point>()) ;

        const Point point = intersection.accessComposite().as<Point>() ;

        ASSERT_TRUE(point.isNear(Point(0.0, 0.0, -3.0), Real::Epsilon())) ;

    }

    {

        const Ray ray = { { 0.0, 0.0, +4.0 }, { 0.0, 0.0, 1.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray, true) ;

        ASSERT_TRUE(intersection.isEmpty()) ;

    }

    // Disabled because this tests fails when coverage is enabled (for some reason...)

    // {

    //     const Ray ray = { { 0.0, 0.0, +3.0 }, { 1.0, 0.0, 0.0 } } ;
    //     const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

    //     const Intersection intersection = ellipsoid.intersectionWith(ray, true) ;

    //     ASSERT_TRUE(intersection.isDefined()) ;
    //     ASSERT_TRUE(intersection.accessComposite().isDefined()) ;

    //     ASSERT_TRUE(intersection.accessComposite().is<Point>()) ;

    //     const Point point = intersection.accessComposite().as<Point>() ;

    //     ASSERT_TRUE(point.isNear(Point(0.0, 0.0, +3.0), Real::Epsilon())) ;

    // }

    // {

    //     const Ray ray = { { 0.0, 0.0, -3.0 }, { 1.0, 0.0, 0.0 } } ;
    //     const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

    //     const Intersection intersection = ellipsoid.intersectionWith(ray, true) ;

    //     ASSERT_TRUE(intersection.isDefined()) ;
    //     ASSERT_TRUE(intersection.accessComposite().isDefined()) ;

    //     ASSERT_TRUE(intersection.accessComposite().is<Point>()) ;

    //     const Point point = intersection.accessComposite().as<Point>() ;

    //     ASSERT_TRUE(point.isNear(Point(0.0, 0.0, -3.0), Real::Epsilon())) ;

    // }

    {

        const Ray ray = { { 0.0, +3.0, 0.0 }, { 1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(ray, true) ;

        ASSERT_TRUE(intersection.isEmpty()) ;

    }

    {

        ASSERT_ANY_THROW(Ellipsoid::Undefined().intersectionWith(Ray::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, IntersectionWith_Segment)
{

    using ostk::core::types::Real ;

    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::PointSet ;
    using ostk::math::geom::d3::objects::Segment ;
    using ostk::math::geom::d3::objects::Ellipsoid ;
    using ostk::math::geom::d3::Intersection ;

    {

        const Segment segment = { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(segment) ;

        ASSERT_TRUE(intersection.isDefined()) ;
        ASSERT_TRUE(intersection.accessComposite().isDefined()) ;

        ASSERT_TRUE(intersection.accessComposite().is<Point>()) ;

        const Point point = intersection.accessComposite().as<Point>() ;

        ASSERT_TRUE(point.isNear(Point(1.0, 0.0, 0.0), Real::Epsilon())) ;

    }

    {

        const Segment segment = { { 0.0, 0.0, 0.0 }, { 2.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(segment) ;

        ASSERT_TRUE(intersection.isDefined()) ;
        ASSERT_TRUE(intersection.accessComposite().isDefined()) ;

        ASSERT_TRUE(intersection.accessComposite().is<Point>()) ;

        const Point point = intersection.accessComposite().as<Point>() ;

        ASSERT_TRUE(point.isNear(Point(1.0, 0.0, 0.0), Real::Epsilon())) ;

    }

    {

        const Segment segment = { { 0.0, 0.0, 0.0 }, { -1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(segment) ;

        ASSERT_TRUE(intersection.isDefined()) ;
        ASSERT_TRUE(intersection.accessComposite().isDefined()) ;

        ASSERT_TRUE(intersection.accessComposite().is<Point>()) ;

        const Point point = intersection.accessComposite().as<Point>() ;

        ASSERT_TRUE(point.isNear(Point(-1.0, 0.0, 0.0), Real::Epsilon())) ;

    }

    {

        const Segment segment = { { 0.0, 0.0, 0.0 }, { -2.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(segment) ;

        ASSERT_TRUE(intersection.isDefined()) ;
        ASSERT_TRUE(intersection.accessComposite().isDefined()) ;

        ASSERT_TRUE(intersection.accessComposite().is<Point>()) ;

        const Point point = intersection.accessComposite().as<Point>() ;

        ASSERT_TRUE(point.isNear(Point(-1.0, 0.0, 0.0), Real::Epsilon())) ;

    }

    {

        const Segment segment = { { -1.0, 0.0, 0.0 }, { +1.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(segment) ;

        ASSERT_TRUE(intersection.isDefined()) ;
        ASSERT_TRUE(intersection.accessComposite().isDefined()) ;

        ASSERT_TRUE(intersection.accessComposite().is<PointSet>()) ;

        const PointSet pointSet = intersection.accessComposite().as<PointSet>() ;

        ASSERT_EQ(2, pointSet.getSize()) ;

        ASSERT_TRUE(pointSet.isNear(PointSet({ { -1.0, 0.0, 0.0 }, { +1.0, 0.0, 0.0 } }), Real::Epsilon())) ;

    }

    {

        const Segment segment = { { -2.0, 0.0, 0.0 }, { +2.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(segment) ;

        ASSERT_TRUE(intersection.isDefined()) ;
        ASSERT_TRUE(intersection.accessComposite().isDefined()) ;

        ASSERT_TRUE(intersection.accessComposite().is<PointSet>()) ;

        const PointSet pointSet = intersection.accessComposite().as<PointSet>() ;

        ASSERT_EQ(2, pointSet.getSize()) ;

        ASSERT_TRUE(pointSet.isNear(PointSet({ { -1.0, 0.0, 0.0 }, { +1.0, 0.0, 0.0 } }), Real::Epsilon())) ;

    }

    {

        const Segment segment = { { -1.0, 0.0, +3.0 }, { +1.0, 0.0, +3.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(segment) ;

        ASSERT_TRUE(intersection.isDefined()) ;
        ASSERT_TRUE(intersection.accessComposite().isDefined()) ;

        ASSERT_TRUE(intersection.accessComposite().is<Point>()) ;

        const Point point = intersection.accessComposite().as<Point>() ;

        ASSERT_TRUE(point.isNear(Point(0.0, 0.0, +3.0), Real::Epsilon())) ;

    }

    {

        const Segment segment = { { 0.0, 0.0, +3.0 }, { 0.0, 0.0, +3.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(segment) ;

        ASSERT_TRUE(intersection.isDefined()) ;
        ASSERT_TRUE(intersection.accessComposite().isDefined()) ;

        ASSERT_TRUE(intersection.accessComposite().is<Point>()) ;

        const Point point = intersection.accessComposite().as<Point>() ;

        ASSERT_TRUE(point.isNear(Point(0.0, 0.0, +3.0), Real::Epsilon())) ;

    }

    {

        const Segment segment = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(segment) ;

        ASSERT_TRUE(intersection.isEmpty()) ;

    }

    {

        const Segment segment = { { 0.0, 0.0, 0.0 }, { 0.5, 0.0, 0.0 } } ;
        const Ellipsoid ellipsoid = { { 0.0, 0.0, 0.0 }, 1.0, 2.0, 3.0 } ;

        const Intersection intersection = ellipsoid.intersectionWith(segment) ;

        ASSERT_TRUE(intersection.isEmpty()) ;

    }

    {

        ASSERT_ANY_THROW(Ellipsoid::Undefined().intersectionWith(Segment::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, IntersectionWith_Pyramid)
{

    using ostk::math::geom::d3::objects::Point ;
    using ostk::math::geom::d3::objects::Ellipsoid ;
    using ostk::math::geom::d3::objects::Pyramid ;

    {

        // See: Library_Mathematics_Geometry_3D_Objects_Pyramid.IntersectionWith_Ellipsoid

        SUCCEED() ;

    }

    {

        ASSERT_ANY_THROW(Ellipsoid::Undefined().intersectionWith(Pyramid::Undefined())) ;
        ASSERT_ANY_THROW(Ellipsoid(Point::Origin(), 1.0, 1.0, 1.0).intersectionWith(Pyramid::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, ApplyTransformation)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::Vector3d ;
    using ostk::math::geom::Angle ;
    using ostk::math::geom::d3::objects::Ellipsoid ;
    using ostk::math::geom::d3::Transformation ;
    using ostk::math::geom::d3::trf::rot::Quaternion ;
    using ostk::math::geom::d3::trf::rot::RotationVector ;

    // Translation

    {

        Ellipsoid ellipsoid = { { 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0 } ;

        ellipsoid.applyTransformation(Transformation::Translation({ 4.0, 5.0, 6.0 })) ;

        ASSERT_EQ(Ellipsoid({ 5.0, 7.0, 9.0 }, 4.0, 5.0, 6.0), ellipsoid) << ellipsoid ;

    }

    // Rotation

    {

        Ellipsoid ellipsoid = { { 1.0, 3.0, 0.0 }, 4.0, 5.0, 6.0 } ;

        ellipsoid.applyTransformation(Transformation::Rotation(RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(90.0)))) ;

        const Ellipsoid referenceEllipsoid = { { 1.0, 0.0, 3.0 }, 4.0, 6.0, 5.0 } ;

        ASSERT_TRUE(ellipsoid.getCenter().isNear(referenceEllipsoid.getCenter(), Real::Epsilon())) << referenceEllipsoid.getCenter().toString() << ellipsoid.getCenter().toString() ;
        ASSERT_TRUE(ellipsoid.getMatrix().isNear(referenceEllipsoid.getMatrix(), Real::Epsilon())) << referenceEllipsoid.getMatrix().toString() << ellipsoid.getMatrix().toString() ;

    }

    {

        ASSERT_ANY_THROW(Ellipsoid::Undefined().applyTransformation(Transformation::Undefined())) ;
        ASSERT_ANY_THROW(Ellipsoid::Undefined().applyTransformation(Transformation::Identity())) ;
        ASSERT_ANY_THROW(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0).applyTransformation(Transformation::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Undefined)
{

    using ostk::math::geom::d3::objects::Ellipsoid ;

    {

        ASSERT_NO_THROW(Ellipsoid::Undefined()) ;
        ASSERT_FALSE(Ellipsoid::Undefined().isDefined()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
