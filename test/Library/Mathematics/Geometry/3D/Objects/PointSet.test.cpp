////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/PointSet.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/PointSet.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Mathematics_Geometry_3D_Objects_PointSet, Constructor)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::PointSet ;

    {

        EXPECT_NO_THROW(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } })) ;

    }

    {

        EXPECT_NO_THROW(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 } })) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_PointSet, Clone)
{

    using library::math::geom::d3::objects::PointSet ;

    {

        EXPECT_NO_THROW(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }).clone()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_PointSet, EqualToOperator)
{

    using library::math::geom::d3::objects::PointSet ;
    
    {

        EXPECT_TRUE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }) == PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } })) ;
        EXPECT_TRUE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }) == PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0 }, { 0.0, 0.0, 1.0 } })) ;
        EXPECT_TRUE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }) == PointSet({ { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0 } })) ;
        EXPECT_TRUE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }) == PointSet({ { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 }, { 0.0, 0.0, 0.0 } })) ;
        EXPECT_TRUE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }) == PointSet({ { 0.0, 0.0, 2.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 } })) ;
        EXPECT_TRUE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }) == PointSet({ { 0.0, 0.0, 2.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 0.0 } })) ;
        
        EXPECT_TRUE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }) == PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } })) ;

        EXPECT_TRUE(PointSet::Empty() == PointSet::Empty()) ;

    }

    {

        EXPECT_FALSE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }) == PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 3.0 } })) ;

    }

    {

        EXPECT_FALSE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }) == PointSet::Empty()) ;
        EXPECT_FALSE(PointSet::Empty() == PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } })) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_PointSet, NotEqualToOperator)
{

    using library::math::geom::d3::objects::PointSet ;

    {

        EXPECT_FALSE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }) != PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } })) ;
        EXPECT_FALSE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }) != PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0 }, { 0.0, 0.0, 1.0 } })) ;
        EXPECT_FALSE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }) != PointSet({ { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0 } })) ;
        EXPECT_FALSE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }) != PointSet({ { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 }, { 0.0, 0.0, 0.0 } })) ;
        EXPECT_FALSE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }) != PointSet({ { 0.0, 0.0, 2.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 } })) ;
        EXPECT_FALSE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }) != PointSet({ { 0.0, 0.0, 2.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 0.0 } })) ;
        
        EXPECT_FALSE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }) != PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } })) ;

        EXPECT_FALSE(PointSet::Empty() != PointSet::Empty()) ;

    }

    {

        EXPECT_TRUE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }) != PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 3.0 } })) ;

    }

    {

        EXPECT_TRUE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }) != PointSet::Empty()) ;
        EXPECT_TRUE(PointSet::Empty() != PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } })) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_PointSet, StreamOperator)
{

    using library::math::geom::d3::objects::PointSet ;
    
    {

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_PointSet, IsDefined)
{

    using library::math::geom::d3::objects::PointSet ;
    
    {

        EXPECT_TRUE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }).isDefined()) ;
        EXPECT_TRUE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 } }).isDefined()) ;

    }

    {

        EXPECT_FALSE(PointSet::Empty().isDefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_PointSet, IsEmpty)
{

    using library::math::geom::d3::objects::PointSet ;
    
    {

        EXPECT_FALSE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }).isEmpty()) ;
        EXPECT_FALSE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 } }).isEmpty()) ;

    }

    {

        EXPECT_TRUE(PointSet::Empty().isEmpty()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_PointSet, IsNear)
{

    using library::core::types::Real ;
    
    using library::math::geom::d3::objects::PointSet ;
    
    {

        EXPECT_TRUE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }).isNear(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }), Real::Epsilon())) ;
        EXPECT_TRUE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }).isNear(PointSet({ { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0 } }), Real::Epsilon())) ;
        
        EXPECT_TRUE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }).isNear(PointSet({ { 0.0, Real::Epsilon(), 1.0 }, { Real::Epsilon(), 0.0, 2.0 }, { 0.0, 0.0, Real::Epsilon() } }), Real::Epsilon())) ;

    }

    {

        EXPECT_FALSE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }).isNear(PointSet({ { 0.0, 2.0 * Real::Epsilon(), 1.0 }, { Real::Epsilon(), 0.0, 2.0 }, { 0.0, 0.0, Real::Epsilon() } }), Real::Epsilon())) ;

    }

    {

        EXPECT_FALSE(PointSet::Empty().isNear(PointSet::Empty(), Real::Epsilon())) ;
        EXPECT_FALSE(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }).isNear(PointSet::Empty(), Real::Epsilon())) ;
        EXPECT_FALSE(PointSet::Empty().isNear(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }), Real::Epsilon())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_PointSet, GetSize)
{

    using library::math::geom::d3::objects::PointSet ;

    {

        EXPECT_EQ(3, PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }).getSize()) ;

    }

    {

        EXPECT_EQ(0, PointSet::Empty().getSize()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_PointSet, GetPointClosestTo)
{

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::PointSet ;

    {

        EXPECT_EQ(Point(0.0, 0.0, 0.0), PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }).getPointClosestTo({ 0.0, 0.0, 0.0 })) ;
        EXPECT_EQ(Point(0.0, 0.0, 1.0), PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }).getPointClosestTo({ 0.0, 0.0, 1.0 })) ;
        EXPECT_EQ(Point(0.0, 0.0, 2.0), PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }).getPointClosestTo({ 0.0, 0.0, 2.0 })) ;

    }

    {

        EXPECT_ANY_THROW(PointSet::Empty().getPointClosestTo(Point::Undefined())) ;
        EXPECT_ANY_THROW(PointSet::Empty().getPointClosestTo(Point::Origin())) ;
        EXPECT_ANY_THROW(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }).getPointClosestTo(Point::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_PointSet, ConstIterator)
{

    using library::core::types::Index ;

    using library::math::geom::d3::objects::PointSet ;

    {

        const PointSet pointSet = { { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } } } ;

        Index count = 0 ;

        for (const auto& point : pointSet)
        {

            EXPECT_TRUE(point.isDefined()) ;

            count++ ;

        }

        EXPECT_EQ(3, count) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_PointSet, Translate)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::PointSet ;

    {

        PointSet pointSet = { { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } } } ;

        pointSet.translate({ 4.0, 5.0, 6.0 }) ;

        EXPECT_EQ(PointSet({ { 4.0, 5.0, 6.0 }, { 4.0, 5.0, 7.0 }, { 4.0, 5.0, 8.0 } }), pointSet) ;

    }

    {

        EXPECT_ANY_THROW(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }).translate(Vector3d::Undefined())) ;

    }

}

// TEST (Library_Mathematics_Geometry_3D_Objects_PointSet, Rotate)
// {

//     using library::core::types::Real ;

//     using library::math::obj::Vector3d ;
//     using library::math::geom::Angle ;
//     using library::math::geom::d3::objects::PointSet ;
//     using library::math::geom::trf::rot::Quaternion ;
//     using library::math::geom::trf::rot::RotationVector ;

//     {

//         // PointSet pointSet = { { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } } } ;

//         // pointSet.rotate(Quaternion::RotationVector(RotationVector({ 1.0, 0.0, 0.0 }, Angle::Degrees(90.0)))) ;

//         // EXPECT_EQ(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }), pointSet) ;

//         FAIL() ;

//     }

//     {

//         EXPECT_ANY_THROW(PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, 2.0 } }).rotate(Quaternion::Undefined())) ;

//     }

// }

TEST (Library_Mathematics_Geometry_3D_Objects_PointSet, Empty)
{

    using library::math::geom::d3::objects::PointSet ;
    
    {

        EXPECT_NO_THROW(PointSet::Empty()) ;
        EXPECT_FALSE(PointSet::Empty().isDefined()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////