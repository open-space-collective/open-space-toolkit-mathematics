////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Pyramid.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/3D/Intersection.hpp>
#include <Library/Mathematics/Geometry/3D/Transformation.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Pyramid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Mathematics_Geometry_3D_Objects_Pyramid, Constructor)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Pyramid ;

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        EXPECT_NO_THROW(Pyramid(base, apex)) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Pyramid, Clone)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Pyramid ;

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        EXPECT_NO_THROW(Pyramid(base, apex).clone()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Pyramid, EqualToOperator)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Pyramid ;
    
    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        EXPECT_TRUE(Pyramid(base, apex) == Pyramid(base, apex)) ;

    }

    {

        // [TBI] Implement similarities

    }

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        EXPECT_FALSE(Pyramid(base, apex) == Pyramid::Undefined()) ;
        EXPECT_FALSE(Pyramid::Undefined() == Pyramid(base, apex)) ;
        EXPECT_FALSE(Pyramid::Undefined() == Pyramid::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Pyramid, NotEqualToOperator)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Pyramid ;
    
    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        EXPECT_FALSE(Pyramid(base, apex) != Pyramid(base, apex)) ;

    }

    {

        // [TBI] Implement similarities

    }

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        EXPECT_TRUE(Pyramid(base, apex) != Pyramid::Undefined()) ;
        EXPECT_TRUE(Pyramid::Undefined() != Pyramid(base, apex)) ;
        EXPECT_TRUE(Pyramid::Undefined() != Pyramid::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Pyramid, StreamOperator)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Pyramid ;
    
    {

        testing::internal::CaptureStdout() ;

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        EXPECT_NO_THROW(std::cout << Pyramid(base, apex) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Pyramid, IsDefined)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Pyramid ;
    
    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        EXPECT_TRUE(Pyramid(base, apex).isDefined()) ;

    }

    {

        EXPECT_FALSE(Pyramid::Undefined().isDefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Pyramid, Intersects_Ellipsoid)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::d3::objects::Pyramid ;
    
    {

        const Polygon base = { { { { -0.1, -0.1 }, { +0.1, -0.1 }, { +0.1, +0.1 }, { -0.1, +0.1 } } }, { 0.0, 0.0, 1.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 0.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Ellipsoid ellipsoid = { { 0.0, 0.0, 10.0 }, 5.0, 5.0, 5.0 } ;

        EXPECT_TRUE(pyramid.intersects(ellipsoid)) ;

    }

    {

        EXPECT_ANY_THROW(Pyramid::Undefined().intersects(Ellipsoid::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Pyramid, GetBase)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Pyramid ;
    
    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        EXPECT_EQ(base, Pyramid(base, apex).getBase()) ;

    }

    {

        EXPECT_ANY_THROW(Pyramid::Undefined().getBase()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Pyramid, GetApex)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Pyramid ;
    
    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        EXPECT_EQ(apex, Pyramid(base, apex).getApex()) ;

    }

    {

        EXPECT_ANY_THROW(Pyramid::Undefined().getApex()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Pyramid, IntersectionWith_Ellipsoid)
{

    using library::core::types::Real ;
    
    using library::math::obj::Vector3d ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::LineString ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Ellipsoid ;
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::Intersection ;
    
    {

        const Polygon base = { { { { -0.1, -0.1 }, { +0.1, -0.1 }, { +0.1, +0.1 }, { -0.1, +0.1 } } }, { 0.0, 0.0, 1.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 0.0 } ;

        const Pyramid pyramid = { base, apex } ;

        const Ellipsoid ellipsoid = { { 0.0, 0.0, 10.0 }, 5.0, 5.0, 5.0 } ;

        const Intersection intersection = pyramid.intersectionWith(ellipsoid, true, 8) ;

        EXPECT_TRUE(intersection.isDefined()) ;
        EXPECT_FALSE(intersection.isEmpty()) ;
        EXPECT_TRUE(intersection.is<LineString>()) ;

        const LineString intersectionLineString = intersection.as<LineString>() ;

        EXPECT_EQ(8, intersectionLineString.getPointCount()) ;

        const LineString referenceLineString = 
        {
            {
                { -0.505129425743498, -0.505129425743498, 5.05129425743498 },
                { -0.505129425743498,  0.505129425743499, 5.05129425743498 },
                { -0.505129425743498,  0.505129425743498, 5.05129425743498 },
                {  0.505129425743499,  0.505129425743498, 5.05129425743498 },
                {  0.505129425743498,  0.505129425743498, 5.05129425743498 },
                {  0.505129425743498, -0.505129425743499, 5.05129425743498 },
                {  0.505129425743498, -0.505129425743498, 5.05129425743498 },
                { -0.505129425743499, -0.505129425743498, 5.05129425743498 }
            }
        } ;

        EXPECT_TRUE(intersectionLineString.isNear(referenceLineString, 1e-10)) ;

    }

    {

        EXPECT_ANY_THROW(Pyramid::Undefined().intersectionWith(Ellipsoid::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Pyramid, ApplyTransformation)
{

    using library::core::types::Real ;

    using library::math::obj::Vector3d ;
    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Polygon ;
    using library::math::geom::d3::objects::Pyramid ;
    using library::math::geom::d3::Transformation ;
    using library::math::geom::d3::trf::rot::RotationVector ;

    // Translation

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        Pyramid pyramid = { base, apex } ;

        pyramid.applyTransformation(Transformation::Translation({ 4.0, 5.0, 6.0 })) ;

        EXPECT_EQ(Pyramid({ { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 4.0, 5.0, 6.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } }, { 4.0, 5.0, 7.0 } }), pyramid) ;

    }

    // Rotation

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 2.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 1.0, 0.0, 0.0 } } ;
        const Point apex = { 0.0, 1.0, 0.0 } ;

        Pyramid pyramid = { base, apex } ;

        pyramid.applyTransformation(Transformation::Rotation(RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(90.0)))) ;

        const Polygon referenceBase = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 2.0 }, { 0.0, -1.0, 0.0 }, { 1.0, 0.0, 0.0 } } ;
        const Point referenceApex = { 0.0, 0.0, 1.0 } ;

        const Pyramid referencePyramid = { referenceBase, referenceApex } ;

        EXPECT_TRUE(pyramid.getBase().isNear(referencePyramid.getBase(), Real::Epsilon())) << referencePyramid.getBase() << pyramid.getBase() ;
        EXPECT_TRUE(pyramid.getApex().isNear(referencePyramid.getApex(), Real::Epsilon())) << referencePyramid.getApex().toString() << pyramid.getApex().toString() ;
        
    }

    {

        const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
        const Point apex = { 0.0, 0.0, 1.0 } ;

        EXPECT_ANY_THROW(Pyramid::Undefined().applyTransformation(Transformation::Undefined())) ;
        EXPECT_ANY_THROW(Pyramid::Undefined().applyTransformation(Transformation::Identity())) ;
        EXPECT_ANY_THROW(Pyramid(base, apex).applyTransformation(Transformation::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Pyramid, Undefined)
{

    using library::math::geom::d3::objects::Pyramid ;
    
    {

        EXPECT_NO_THROW(Pyramid::Undefined()) ;
        EXPECT_FALSE(Pyramid::Undefined().isDefined()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////