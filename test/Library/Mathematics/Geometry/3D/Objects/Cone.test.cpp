////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Cone.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/3D/Intersection.hpp>
#include <Library/Mathematics/Geometry/3D/Transformation.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Cone.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Mathematics_Geometry_3D_Objects_Cone, Constructor)
{

    // using library::math::obj::Vector3d ;
    // using library::math::geom::d3::objects::Point ;
    // using library::math::geom::d3::objects::Polygon ;
    // using library::math::geom::d3::objects::Cone ;

    // {

    //     const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
    //     const Point apex = { 0.0, 0.0, 1.0 } ;

    //     EXPECT_NO_THROW(Cone(base, apex)) ;

    // }

    FAIL() ;

}

// TEST (Library_Mathematics_Geometry_3D_Objects_Cone, Clone)
// {

//     using library::math::obj::Vector3d ;
//     using library::math::geom::d3::objects::Point ;
//     using library::math::geom::d3::objects::Polygon ;
//     using library::math::geom::d3::objects::Cone ;

//     {

//         const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
//         const Point apex = { 0.0, 0.0, 1.0 } ;

//         EXPECT_NO_THROW(Cone(base, apex).clone()) ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Objects_Cone, EqualToOperator)
// {

//     using library::math::obj::Vector3d ;
//     using library::math::geom::d3::objects::Point ;
//     using library::math::geom::d3::objects::Polygon ;
//     using library::math::geom::d3::objects::Cone ;
    
//     {

//         const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
//         const Point apex = { 0.0, 0.0, 1.0 } ;

//         EXPECT_TRUE(Cone(base, apex) == Cone(base, apex)) ;

//     }

//     {

//         // [TBI] Implement similarities

//     }

//     {

//         const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
//         const Point apex = { 0.0, 0.0, 1.0 } ;

//         EXPECT_FALSE(Cone(base, apex) == Cone::Undefined()) ;
//         EXPECT_FALSE(Cone::Undefined() == Cone(base, apex)) ;
//         EXPECT_FALSE(Cone::Undefined() == Cone::Undefined()) ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Objects_Cone, NotEqualToOperator)
// {

//     using library::math::obj::Vector3d ;
//     using library::math::geom::d3::objects::Point ;
//     using library::math::geom::d3::objects::Polygon ;
//     using library::math::geom::d3::objects::Cone ;
    
//     {

//         const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
//         const Point apex = { 0.0, 0.0, 1.0 } ;

//         EXPECT_FALSE(Cone(base, apex) != Cone(base, apex)) ;

//     }

//     {

//         // [TBI] Implement similarities

//     }

//     {

//         const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
//         const Point apex = { 0.0, 0.0, 1.0 } ;

//         EXPECT_TRUE(Cone(base, apex) != Cone::Undefined()) ;
//         EXPECT_TRUE(Cone::Undefined() != Cone(base, apex)) ;
//         EXPECT_TRUE(Cone::Undefined() != Cone::Undefined()) ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Objects_Cone, StreamOperator)
// {

//     using library::math::obj::Vector3d ;
//     using library::math::geom::d3::objects::Point ;
//     using library::math::geom::d3::objects::Polygon ;
//     using library::math::geom::d3::objects::Cone ;
    
//     {

//         testing::internal::CaptureStdout() ;

//         const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
//         const Point apex = { 0.0, 0.0, 1.0 } ;

//         EXPECT_NO_THROW(std::cout << Cone(base, apex) << std::endl) ;

//         EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Objects_Cone, IsDefined)
// {

//     using library::math::obj::Vector3d ;
//     using library::math::geom::d3::objects::Point ;
//     using library::math::geom::d3::objects::Polygon ;
//     using library::math::geom::d3::objects::Cone ;
    
//     {

//         const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
//         const Point apex = { 0.0, 0.0, 1.0 } ;

//         EXPECT_TRUE(Cone(base, apex).isDefined()) ;

//     }

//     {

//         EXPECT_FALSE(Cone::Undefined().isDefined()) ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Objects_Cone, Intersects_Ellipsoid)
// {

//     using library::math::obj::Vector3d ;
//     using library::math::geom::d3::objects::Point ;
//     using library::math::geom::d3::objects::Polygon ;
//     using library::math::geom::d3::objects::Ellipsoid ;
//     using library::math::geom::d3::objects::Cone ;
    
//     {

//         const Polygon base = { { { { -0.1, -0.1 }, { +0.1, -0.1 }, { +0.1, +0.1 }, { -0.1, +0.1 } } }, { 0.0, 0.0, 1.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
//         const Point apex = { 0.0, 0.0, 0.0 } ;

//         const Cone cone = { base, apex } ;

//         const Ellipsoid ellipsoid = { { 0.0, 0.0, 10.0 }, 5.0, 5.0, 5.0 } ;

//         EXPECT_TRUE(cone.intersects(ellipsoid)) ;

//     }

//     {

//         EXPECT_ANY_THROW(Cone::Undefined().intersects(Ellipsoid::Undefined())) ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Objects_Cone, GetBase)
// {

//     using library::math::obj::Vector3d ;
//     using library::math::geom::d3::objects::Point ;
//     using library::math::geom::d3::objects::Polygon ;
//     using library::math::geom::d3::objects::Cone ;
    
//     {

//         const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
//         const Point apex = { 0.0, 0.0, 1.0 } ;

//         EXPECT_EQ(base, Cone(base, apex).getBase()) ;

//     }

//     {

//         EXPECT_ANY_THROW(Cone::Undefined().getBase()) ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Objects_Cone, GetApex)
// {

//     using library::math::obj::Vector3d ;
//     using library::math::geom::d3::objects::Point ;
//     using library::math::geom::d3::objects::Polygon ;
//     using library::math::geom::d3::objects::Cone ;
    
//     {

//         const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
//         const Point apex = { 0.0, 0.0, 1.0 } ;

//         EXPECT_EQ(apex, Cone(base, apex).getApex()) ;

//     }

//     {

//         EXPECT_ANY_THROW(Cone::Undefined().getApex()) ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Objects_Cone, IntersectionWith_Ellipsoid)
// {

//     using library::core::types::Real ;
    
//     using library::math::obj::Vector3d ;
//     using library::math::geom::d3::objects::Point ;
//     using library::math::geom::d3::objects::LineString ;
//     using library::math::geom::d3::objects::Polygon ;
//     using library::math::geom::d3::objects::Ellipsoid ;
//     using library::math::geom::d3::objects::Cone ;
//     using library::math::geom::d3::Intersection ;
    
//     {

//         const Polygon base = { { { { -0.1, -0.1 }, { +0.1, -0.1 }, { +0.1, +0.1 }, { -0.1, +0.1 } } }, { 0.0, 0.0, 1.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
//         const Point apex = { 0.0, 0.0, 0.0 } ;

//         const Cone cone = { base, apex } ;

//         const Ellipsoid ellipsoid = { { 0.0, 0.0, 10.0 }, 5.0, 5.0, 5.0 } ;

//         const Intersection intersection = cone.intersectionWith(ellipsoid, true, 8) ;

//         EXPECT_TRUE(intersection.isDefined()) ;
//         EXPECT_FALSE(intersection.isEmpty()) ;
//         EXPECT_TRUE(intersection.accessComposite().is<LineString>()) ;

//         const LineString intersectionLineString = intersection.accessComposite().as<LineString>() ;

//         EXPECT_EQ(8, intersectionLineString.getPointCount()) ;

//         const LineString referenceLineString = 
//         {
//             {
//                 { -0.505129425743498, -0.505129425743498, 5.05129425743498 },
//                 { -0.505129425743498,  0.505129425743499, 5.05129425743498 },
//                 { -0.505129425743498,  0.505129425743498, 5.05129425743498 },
//                 {  0.505129425743499,  0.505129425743498, 5.05129425743498 },
//                 {  0.505129425743498,  0.505129425743498, 5.05129425743498 },
//                 {  0.505129425743498, -0.505129425743499, 5.05129425743498 },
//                 {  0.505129425743498, -0.505129425743498, 5.05129425743498 },
//                 { -0.505129425743499, -0.505129425743498, 5.05129425743498 }
//             }
//         } ;

//         EXPECT_TRUE(intersectionLineString.isNear(referenceLineString, 1e-10)) ;

//     }

//     {

//         EXPECT_ANY_THROW(Cone::Undefined().intersectionWith(Ellipsoid::Undefined())) ;

//     }

// }

// TEST (Library_Mathematics_Geometry_3D_Objects_Cone, ApplyTransformation)
// {

//     using library::core::types::Real ;

//     using library::math::obj::Vector3d ;
//     using library::math::geom::Angle ;
//     using library::math::geom::d3::objects::Point ;
//     using library::math::geom::d3::objects::Polygon ;
//     using library::math::geom::d3::objects::Cone ;
//     using library::math::geom::d3::Transformation ;
//     using library::math::geom::d3::trf::rot::RotationVector ;

//     // Translation

//     {

//         const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
//         const Point apex = { 0.0, 0.0, 1.0 } ;

//         Cone cone = { base, apex } ;

//         cone.applyTransformation(Transformation::Translation({ 4.0, 5.0, 6.0 })) ;

//         EXPECT_EQ(Cone({ { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 4.0, 5.0, 6.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } }, { 4.0, 5.0, 7.0 } }), cone) ;

//     }

//     // Rotation

//     {

//         const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 2.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 1.0, 0.0, 0.0 } } ;
//         const Point apex = { 0.0, 1.0, 0.0 } ;

//         Cone cone = { base, apex } ;

//         cone.applyTransformation(Transformation::Rotation(RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(90.0)))) ;

//         const Polygon referenceBase = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 2.0 }, { 0.0, -1.0, 0.0 }, { 1.0, 0.0, 0.0 } } ;
//         const Point referenceApex = { 0.0, 0.0, 1.0 } ;

//         const Cone referenceCone = { referenceBase, referenceApex } ;

//         EXPECT_TRUE(cone.getBase().isNear(referenceCone.getBase(), Real::Epsilon())) << referenceCone.getBase() << cone.getBase() ;
//         EXPECT_TRUE(cone.getApex().isNear(referenceCone.getApex(), Real::Epsilon())) << referenceCone.getApex().toString() << cone.getApex().toString() ;
        
//     }

//     {

//         const Polygon base = { { { { 0.0, 0.0 }, { 1.0, 0.0 }, { 1.0, 1.0 }, { 0.0, 1.0 } } }, { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 } } ;
//         const Point apex = { 0.0, 0.0, 1.0 } ;

//         EXPECT_ANY_THROW(Cone::Undefined().applyTransformation(Transformation::Undefined())) ;
//         EXPECT_ANY_THROW(Cone::Undefined().applyTransformation(Transformation::Identity())) ;
//         EXPECT_ANY_THROW(Cone(base, apex).applyTransformation(Transformation::Undefined())) ;

//     }

// }

TEST (Library_Mathematics_Geometry_3D_Objects_Cone, Undefined)
{

    using library::math::geom::d3::objects::Cone ;
    
    {

        EXPECT_NO_THROW(Cone::Undefined()) ;
        EXPECT_FALSE(Cone::Undefined().isDefined()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////