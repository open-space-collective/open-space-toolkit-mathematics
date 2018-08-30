////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Ray.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/3D/Intersection.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ray.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Mathematics_Geometry_3D_Objects_Ray, Constructor)
{

    using library::math::geom::d3::objects::Ray ;

    {

        EXPECT_NO_THROW(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 })) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ray, Clone)
{

    using library::math::geom::d3::objects::Ray ;

    {

        EXPECT_NO_THROW(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).clone()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ray, EqualToOperator)
{

    using library::math::geom::d3::objects::Ray ;
    
    {

        EXPECT_TRUE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Ray({ 0.0, 0.0, +0.0 }, { 0.0, 0.0, +1.0 })) ;
        EXPECT_TRUE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Ray({ 0.0, 0.0, +0.0 }, { 0.0, 0.0, +2.0 })) ;

    }

    {

        EXPECT_FALSE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Ray({ 0.0, 0.0, +1.0 }, { 0.0, 0.0, +1.0 })) ;
        EXPECT_FALSE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Ray({ 0.0, 0.0, +1.0 }, { 0.0, 0.0, +2.0 })) ;

        EXPECT_FALSE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Ray({ 0.0, 0.0, -1.0 }, { 0.0, 0.0, +1.0 })) ;
        EXPECT_FALSE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, -1.0 })) ;

    }

    {

        EXPECT_FALSE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Ray::Undefined()) ;
        EXPECT_FALSE(Ray::Undefined() == Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 })) ;
        EXPECT_FALSE(Ray::Undefined() == Ray::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ray, NotEqualToOperator)
{

    using library::math::geom::d3::objects::Ray ;

    {

        EXPECT_FALSE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Ray({ 0.0, 0.0, +0.0 }, { 0.0, 0.0, +1.0 })) ;
        EXPECT_FALSE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Ray({ 0.0, 0.0, +0.0 }, { 0.0, 0.0, +2.0 })) ;

    }

    {

        EXPECT_TRUE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Ray({ 0.0, 0.0, +1.0 }, { 0.0, 0.0, +1.0 })) ;
        EXPECT_TRUE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Ray({ 0.0, 0.0, +1.0 }, { 0.0, 0.0, +2.0 })) ;

        EXPECT_TRUE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Ray({ 0.0, 0.0, -1.0 }, { 0.0, 0.0, +1.0 })) ;
        EXPECT_TRUE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, -1.0 })) ;

    }

    {

        EXPECT_TRUE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Ray({ 0.0, 0.0, -1.0 }, { 0.0, 0.0, +1.0 })) ;
        EXPECT_TRUE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, -1.0 })) ;

    }

    {

        EXPECT_TRUE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Ray::Undefined()) ;
        EXPECT_TRUE(Ray::Undefined() != Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 })) ;
        EXPECT_TRUE(Ray::Undefined() != Ray::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ray, StreamOperator)
{

    using library::math::geom::d3::objects::Ray ;
    
    {

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ray, IsDefined)
{

    using library::math::geom::d3::objects::Ray ;
    
    {

        EXPECT_TRUE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).isDefined()) ;

    }

    {

        EXPECT_FALSE(Ray::Undefined().isDefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ray, Intersects_Point)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Ray ;

    {

        EXPECT_TRUE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).intersects(Point(0.0, 0.0, 0.0))) ;
        EXPECT_TRUE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).intersects(Point(0.0, 0.0, +1.0))) ;
        EXPECT_TRUE(Ray({ 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).intersects(Point(1.0, 0.0, 0.0))) ;
        EXPECT_TRUE(Ray({ 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).intersects(Point(1.0, 0.0, +1.0))) ;

    }

    {

        EXPECT_FALSE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).intersects(Point(0.0, 0.0, -1.0))) ;
        EXPECT_FALSE(Ray({ 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).intersects(Point(1.0, 0.0, -1.0))) ;
        EXPECT_FALSE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).intersects(Point(1.0, 0.0, 0.0))) ;
        EXPECT_FALSE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).intersects(Point(0.0, 1.0, 0.0))) ;

    }

    {

        EXPECT_ANY_THROW(Ray::Undefined().intersects(Point::Undefined())) ;
        EXPECT_ANY_THROW(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).intersects(Point::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ray, Intersects_Ellipsoid)
{

    using library::math::geom::d3::objects::Ray ;
    using library::math::geom::d3::objects::Ellipsoid ;

    {

        // See: Library_Mathematics_Geometry_3D_Objects_Ellipsoid.Intersects_Ray

        SUCCEED() ;

    }

    {

        EXPECT_ANY_THROW(Ray::Undefined().intersects(Ellipsoid::Undefined())) ;
        EXPECT_ANY_THROW(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).intersects(Ellipsoid::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ray, Contains_Point)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Ray ;

    {

        EXPECT_TRUE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 0.0, +0.0))) ;
        EXPECT_TRUE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 0.0, +0.5))) ;
        EXPECT_TRUE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 0.0, +1.0))) ;
        EXPECT_TRUE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 0.0, +2.0))) ;

    }

    {

        EXPECT_FALSE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 0.0, -2.0))) ;
        EXPECT_FALSE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 0.0, -1.0))) ;
        EXPECT_FALSE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 0.0, -0.5))) ;
        EXPECT_FALSE(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(1.0, 0.0, 0.0))) ;

    }

    {

        EXPECT_ANY_THROW(Ray::Undefined().contains(Point::Undefined())) ;
        EXPECT_ANY_THROW(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point::Undefined())) ;
        EXPECT_ANY_THROW(Ray::Undefined().contains(Point(0.0, 0.0, 0.0))) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ray, GetOrigin)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Ray ;
    
    {

        EXPECT_EQ(Point(0.0, 0.0, 0.0), Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).getOrigin()) ;
        EXPECT_EQ(Point(0.0, 0.0, 1.0), Ray({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 }).getOrigin()) ;
        
        EXPECT_EQ(Point(0.0, 0.0, -1.0), Ray({ 0.0, 0.0, -1.0 }, { 0.0, 0.0, +1.0 }).getOrigin()) ;

    }

    {

        EXPECT_ANY_THROW(Ray::Undefined().getOrigin()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ray, GetDirection)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Ray ;
    
    {

        EXPECT_EQ(Vector3d(0.0, 0.0, +1.0), Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, +2.0 }).getDirection()) ;
        EXPECT_EQ(Vector3d(0.0, 0.0, -1.0), Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, -2.0 }).getDirection()) ;

    }

    {

        EXPECT_ANY_THROW(Ray::Undefined().getDirection()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ray, IntersectionWith_Ellipsoid)
{

    using library::math::geom::d3::objects::Ray ;
    using library::math::geom::d3::objects::Ellipsoid ;
    
    {

        // See: Library_Mathematics_Geometry_3D_Objects_Ellipsoid.IntersectionWith_Ray

        SUCCEED() ;

    }

    {

        EXPECT_ANY_THROW(Ray::Undefined().intersectionWith(Ellipsoid::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ray, Translate)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::objects::Ray ;

    {

        Ray ray = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 } } ;

        ray.translate({ 4.0, 5.0, 6.0 }) ;

        EXPECT_EQ(Ray({ 4.0, 5.0, 6.0 }, { 0.0, 0.0, 1.0 }), ray) ;

    }

    {

        EXPECT_ANY_THROW(Ray::Undefined().translate(Vector3d::Undefined())) ;
        EXPECT_ANY_THROW(Ray::Undefined().translate({ 0.0, 0.0, 0.0 })) ;
        EXPECT_ANY_THROW(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).translate(Vector3d::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ray, Rotate)
{

    using library::core::types::Real ;

    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Ray ;
    using library::math::geom::trf::rot::Quaternion ;
    using library::math::geom::trf::rot::RotationVector ;

    {

        Ray ray = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 } } ;

        ray.rotate(Quaternion::RotationVector(RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(90.0)))) ;

        const Ray referenceRay = { { 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;

        EXPECT_TRUE(ray.getOrigin().isNear(referenceRay.getOrigin(), Real::Epsilon())) ;
        EXPECT_TRUE(ray.getDirection().isApprox(referenceRay.getDirection(), Real::Epsilon())) ;

    }

    {

        EXPECT_ANY_THROW(Ray::Undefined().rotate(Quaternion::Undefined())) ;
        EXPECT_ANY_THROW(Ray::Undefined().rotate(Quaternion::Unit())) ;
        EXPECT_ANY_THROW(Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).rotate(Quaternion::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ray, Undefined)
{

    using library::math::geom::d3::objects::Ray ;
    
    {

        EXPECT_NO_THROW(Ray::Undefined()) ;
        EXPECT_FALSE(Ray::Undefined().isDefined()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////