////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Segment.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/3D/Transformation.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Sphere.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, Constructor)
{

    using library::math::geom::d3::objects::Segment ;

    {

        EXPECT_NO_THROW(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 })) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, Clone)
{

    using library::math::geom::d3::objects::Segment ;

    {

        EXPECT_NO_THROW(const Segment* segmentPtr = Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).clone() ; delete segmentPtr ;) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, EqualToOperator)
{

    using library::math::geom::d3::objects::Segment ;

    {

        EXPECT_TRUE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 })) ;
        EXPECT_TRUE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Segment({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, 0.0 })) ;

    }

    {

        EXPECT_FALSE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0 })) ;

    }

    {

        EXPECT_FALSE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Segment::Undefined()) ;
        EXPECT_FALSE(Segment::Undefined() == Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 })) ;
        EXPECT_FALSE(Segment::Undefined() == Segment::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, NotEqualToOperator)
{

    using library::math::geom::d3::objects::Segment ;

    {

        EXPECT_FALSE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 })) ;
        EXPECT_FALSE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Segment({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, 0.0 })) ;

    }

    {

        EXPECT_TRUE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0 })) ;

    }

    {

        EXPECT_TRUE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Segment::Undefined()) ;
        EXPECT_TRUE(Segment::Undefined() != Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 })) ;
        EXPECT_TRUE(Segment::Undefined() != Segment::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, StreamOperator)
{

    using library::math::geom::d3::objects::Segment ;

    {

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, IsDefined)
{

    using library::math::geom::d3::objects::Segment ;

    {

        EXPECT_TRUE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }).isDefined()) ;
        EXPECT_TRUE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).isDefined()) ;

    }

    {

        EXPECT_FALSE(Segment::Undefined().isDefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, IsDegenerate)
{

    using library::math::geom::d3::objects::Segment ;

    {

        EXPECT_TRUE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }).isDegenerate()) ;
        EXPECT_TRUE(Segment({ 1.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0 }).isDegenerate()) ;

    }

    {

        EXPECT_FALSE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).isDegenerate()) ;
        EXPECT_FALSE(Segment({ 1.0, 2.0, 3.0 }, { 0.0, 0.0, 1.0 }).isDegenerate()) ;

    }

    {

        EXPECT_ANY_THROW(Segment::Undefined().isDegenerate()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, Intersects_Sphere)
{

    using library::math::geom::d3::objects::Segment ;
    using library::math::geom::d3::objects::Sphere ;

    {

        // See: Library_Mathematics_Geometry_3D_Objects_Sphere.Intersects

        SUCCEED() ;

    }

    {

        EXPECT_ANY_THROW(Segment::Undefined().intersects(Sphere::Undefined())) ;
        EXPECT_ANY_THROW(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }).intersects(Sphere::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, Intersects_Ellipsoid)
{

    using library::math::geom::d3::objects::Segment ;
    using library::math::geom::d3::objects::Ellipsoid ;

    {

        // See: Library_Mathematics_Geometry_3D_Objects_Ellipsoid.Intersects

        SUCCEED() ;

    }

    {

        EXPECT_ANY_THROW(Segment::Undefined().intersects(Ellipsoid::Undefined())) ;
        EXPECT_ANY_THROW(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }).intersects(Ellipsoid::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, Contains)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Segment ;

    // Point

    {

        {

            EXPECT_TRUE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }).contains(Point(0.0, 0.0, 0.0))) ;
            EXPECT_TRUE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 0.0, 0.0))) ;
            EXPECT_TRUE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 0.0, 1.0))) ;
            EXPECT_TRUE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 0.0, 0.5))) ;

        }

        {

            EXPECT_FALSE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }).contains(Point(0.0, 0.0, 0.1))) ;
            EXPECT_FALSE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 0.0, 2.0))) ;
            EXPECT_FALSE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 0.0, -1.0))) ;
            EXPECT_FALSE(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(1.0, 0.0, 0.0))) ;

        }

        {

            EXPECT_ANY_THROW(Segment::Undefined().contains(Point::Undefined())) ;
            EXPECT_ANY_THROW(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }).contains(Point::Undefined())) ;
            EXPECT_ANY_THROW(Segment::Undefined().contains(Point(0.0, 0.0, 0.0))) ;

        }

    }

    // PointSet

    {

        // [TBI]

    }

    // Segment

    {

        // [TBI]

    }

    // Sphere

    {

        // [TBI]

    }

    // Ellipsoid

    {

        // [TBI]

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, GetCenter)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Segment ;

    {

        EXPECT_EQ(Point(0.0, 0.0, 0.0), Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }).getCenter()) ;
        EXPECT_EQ(Point(0.0, 0.0, 1.0), Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0 }).getCenter()) ;

        EXPECT_EQ(Point(0.0, 0.0, 0.0), Segment({ 0.0, 0.0, -1.0 }, { 0.0, 0.0, +1.0 }).getCenter()) ;

    }

    {

        EXPECT_ANY_THROW(Segment::Undefined().getCenter()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, GetDirection)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Segment ;

    {

        EXPECT_EQ(Vector3d(0.0, 0.0, +1.0), Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, +2.0 }).getDirection()) ;
        EXPECT_EQ(Vector3d(0.0, 0.0, -1.0), Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, -2.0 }).getDirection()) ;

    }

    {

        EXPECT_ANY_THROW(Segment::Undefined().getDirection()) ;

        EXPECT_ANY_THROW(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }).getDirection()) ;
        EXPECT_ANY_THROW(Segment({ 1.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0 }).getDirection()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, GetLength)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Segment ;

    {

        EXPECT_EQ(0.0, Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }).getLength()) ;
        EXPECT_EQ(0.0, Segment({ 1.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0 }).getLength()) ;

        EXPECT_EQ(1.0, Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).getLength()) ;
        EXPECT_EQ(2.0, Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0 }).getLength()) ;

        EXPECT_EQ(4.0, Segment({ 0.0, 0.0, -2.0 }, { 0.0, 0.0, +2.0 }).getLength()) ;

    }

    {

        EXPECT_ANY_THROW(Segment::Undefined().getLength()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, ApplyTransformation)
{

    using library::core::types::Real ;

    using library::math::obj::Vector3d ;
    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Segment ;
    using library::math::geom::d3::Transformation ;
    using library::math::geom::d3::trf::rot::RotationVector ;

    // Translation

    {

        Segment segment = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 } } ;

        segment.applyTransformation(Transformation::Translation({ 4.0, 5.0, 6.0 })) ;

        EXPECT_EQ(Segment({ 4.0, 5.0, 6.0 }, { 4.0, 5.0, 7.0 }), segment) ;

    }

    // Rotation

    {

        Segment segment = { { 0.0, 0.5, 0.0 }, { 0.0, 1.0, 0.0 } } ;

        segment.applyTransformation(Transformation::Rotation(RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(90.0)))) ;

        const Segment referenceSegment = { { 0.0, 0.0, 0.5 }, { 0.0, 0.0, 1.0 } } ;

        EXPECT_TRUE(segment.getFirstPoint().isNear(referenceSegment.getFirstPoint(), Real::Epsilon())) ;
        EXPECT_TRUE(segment.getSecondPoint().isNear(referenceSegment.getSecondPoint(), Real::Epsilon())) ;

    }

    {

        EXPECT_ANY_THROW(Segment::Undefined().applyTransformation(Transformation::Undefined())) ;
        EXPECT_ANY_THROW(Segment::Undefined().applyTransformation(Transformation::Identity())) ;
        EXPECT_ANY_THROW(Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).applyTransformation(Transformation::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Segment, Undefined)
{

    using library::math::geom::d3::objects::Segment ;

    {

        EXPECT_NO_THROW(Segment::Undefined()) ;
        EXPECT_FALSE(Segment::Undefined().isDefined()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
