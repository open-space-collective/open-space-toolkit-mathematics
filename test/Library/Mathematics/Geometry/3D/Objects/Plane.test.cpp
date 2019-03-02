////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Plane.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/3D/Transformation.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Plane.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Mathematics_Geometry_3D_Objects_Plane, Constructor)
{

    using library::math::geom::d3::objects::Plane ;

    {

        EXPECT_NO_THROW(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 })) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Plane, Clone)
{

    using library::math::geom::d3::objects::Plane ;

    {

        EXPECT_NO_THROW(const Plane* planePtr = Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).clone() ; delete planePtr ;) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Plane, EqualToOperator)
{

    using library::math::geom::d3::objects::Plane ;
    
    {

        EXPECT_TRUE(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 })) ;
        EXPECT_TRUE(Plane({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0 }) == Plane({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 })) ;

        EXPECT_TRUE(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Plane({ 1.0, 1.0, 0.0 }, { 0.0, 0.0, +1.0 })) ;
        EXPECT_TRUE(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Plane({ 1.0, 1.0, 0.0 }, { 0.0, 0.0, -1.0 })) ;

    }

    {

        EXPECT_FALSE(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Plane({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0 })) ;

    }

    {

        EXPECT_FALSE(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Plane::Undefined()) ;
        EXPECT_FALSE(Plane::Undefined() == Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 })) ;
        EXPECT_FALSE(Plane::Undefined() == Plane::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Plane, NotEqualToOperator)
{

    using library::math::geom::d3::objects::Plane ;

    {

        EXPECT_FALSE(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 })) ;
        EXPECT_FALSE(Plane({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0 }) != Plane({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 })) ;

        EXPECT_FALSE(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Plane({ 1.0, 1.0, 0.0 }, { 0.0, 0.0, +1.0 })) ;
        EXPECT_FALSE(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Plane({ 1.0, 1.0, 0.0 }, { 0.0, 0.0, -1.0 })) ;

    }

    {

        EXPECT_TRUE(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Plane({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0 })) ;

    }

    {

        EXPECT_TRUE(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Plane::Undefined()) ;
        EXPECT_TRUE(Plane::Undefined() != Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 })) ;
        EXPECT_TRUE(Plane::Undefined() != Plane::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Plane, StreamOperator)
{

    using library::math::geom::d3::objects::Plane ;
    
    {

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Plane, IsDefined)
{

    using library::math::geom::d3::objects::Plane ;
    
    {

        EXPECT_TRUE(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).isDefined()) ;
        EXPECT_TRUE(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0 }).isDefined()) ;

    }

    {

        EXPECT_FALSE(Plane::Undefined().isDefined()) ;

    }

}

// TEST (Library_Mathematics_Geometry_3D_Objects_Plane, Intersects)
// {

//     using library::math::geom::d3::objects::Plane ;
//     using library::math::geom::d3::objects::Ellipsoid ;

//     // Point

//     {

//         // [TBI]

//     }

//     // PointSet

//     {

//         // [TBI]

//     }

//     // Plane

//     {

//         // [TBI]

//     }

//     // Sphere

//     {

//         // [TBI]

//     }

//     // Ellipsoid

//     {

//         {

//             // See: Library_Mathematics_Geometry_3D_Objects_Ellipsoid.Intersects

//             SUCCEED() ;

//         }

//         {

//             EXPECT_ANY_THROW(Plane::Undefined().intersects(Ellipsoid::Undefined())) ;
//             EXPECT_ANY_THROW(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }).intersects(Ellipsoid::Undefined())) ;

//         }

//     }

// }

TEST (Library_Mathematics_Geometry_3D_Objects_Plane, Contains)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Plane ;

    // Point

    {

        {

            EXPECT_TRUE(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 0.0, 0.0))) ;
            EXPECT_TRUE(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(1.0, 0.0, 0.0))) ;
            EXPECT_TRUE(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 1.0, 0.0))) ;
            EXPECT_TRUE(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(1.0, 1.0, 0.0))) ;
            EXPECT_TRUE(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0 }).contains(Point(0.0, 0.0, 0.0))) ;
            EXPECT_TRUE(Plane({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 0.0, 1.0))) ;
            EXPECT_TRUE(Plane({ 1.0, 1.0, 1.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 0.0, 1.0))) ;

        }

        {

            EXPECT_FALSE(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 0.0, 0.1))) ;
            EXPECT_FALSE(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 0.0, 1.0))) ;
            EXPECT_FALSE(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point(0.0, 0.0, -1.0))) ;

        }

        {

            EXPECT_ANY_THROW(Plane::Undefined().contains(Point::Undefined())) ;
            EXPECT_ANY_THROW(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).contains(Point::Undefined())) ;
            EXPECT_ANY_THROW(Plane::Undefined().contains(Point(0.0, 0.0, 0.0))) ;

        }

    }

    // PointSet

    {

        // [TBI]
        
    }

    // Plane

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

TEST (Library_Mathematics_Geometry_3D_Objects_Plane, GetPoint)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Plane ;
    
    {

        EXPECT_EQ(Point(0.0, 0.0, 0.0), Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }).getPoint()) ;
        EXPECT_EQ(Point(0.0, 0.0, 1.0), Plane({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 }).getPoint()) ;

    }

    {

        EXPECT_ANY_THROW(Plane::Undefined().getPoint()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Plane, GetNormalVector)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Plane ;
    
    {

        EXPECT_EQ(Vector3d(0.0, 0.0, +1.0), Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, +2.0 }).getNormalVector()) ;
        EXPECT_EQ(Vector3d(0.0, 0.0, -1.0), Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, -2.0 }).getNormalVector()) ;

    }

    {

        EXPECT_ANY_THROW(Plane::Undefined().getNormalVector()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Plane, ApplyTransformation)
{
    
    using library::core::types::Real ;

    using library::math::obj::Vector3d ;
    using library::math::geom::Angle ;
    using library::math::geom::d3::objects::Plane ;
    using library::math::geom::d3::Transformation ;
    using library::math::geom::d3::trf::rot::RotationVector ;

    // Translation

    {

        Plane plane = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 } } ;

        plane.applyTransformation(Transformation::Translation({ 4.0, 5.0, 6.0 })) ;

        EXPECT_EQ(Plane({ 4.0, 5.0, 6.0 }, { 0.0, 0.0, 1.0 }), plane) ;

    }

    // Rotation

    {

        Plane plane = { { 1.0, 3.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;

        plane.applyTransformation(Transformation::Rotation(RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(90.0)))) ;

        const Plane referencePlane = { { 1.0, 0.0, 3.0 }, { 0.0, 0.0, 1.0 } } ;

        EXPECT_TRUE(plane.getPoint().isNear(referencePlane.getPoint(), Real::Epsilon())) ;
        EXPECT_TRUE(plane.getNormalVector().isNear(referencePlane.getNormalVector(), Real::Epsilon())) ;

    }

    {

        EXPECT_ANY_THROW(Plane::Undefined().applyTransformation(Transformation::Undefined())) ;
        EXPECT_ANY_THROW(Plane::Undefined().applyTransformation(Transformation::Identity())) ;
        EXPECT_ANY_THROW(Plane({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).applyTransformation(Transformation::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Plane, Undefined)
{

    using library::math::geom::d3::objects::Plane ;
    
    {

        EXPECT_NO_THROW(Plane::Undefined()) ;
        EXPECT_FALSE(Plane::Undefined().isDefined()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////