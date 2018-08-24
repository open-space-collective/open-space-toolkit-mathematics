////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Ellipsoid.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>

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

    using library::math::geom::d3::objects::Ellipsoid ;
    
    {

        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) == Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0)) ;

    }

    {

        EXPECT_FALSE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) == Ellipsoid({ 1.0, 2.0, 4.0 }, 4.0, 5.0, 6.0)) ;
        EXPECT_FALSE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) == Ellipsoid({ 1.0, 2.0, 3.0 }, 3.0, 5.0, 6.0)) ;

    }

    {

        // [TBI] Check invariants after rotation

    }

    {

        EXPECT_FALSE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) == Ellipsoid::Undefined()) ;
        EXPECT_FALSE(Ellipsoid::Undefined() == Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0)) ;
        EXPECT_FALSE(Ellipsoid::Undefined() == Ellipsoid::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, NotEqualToOperator)
{

    using library::math::geom::d3::objects::Ellipsoid ;

    {

        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) != Ellipsoid({ 1.0, 2.0, 4.0 }, 4.0, 5.0, 6.0)) ;
        EXPECT_TRUE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) != Ellipsoid({ 1.0, 2.0, 3.0 }, 3.0, 5.0, 6.0)) ;

    }

    {

        EXPECT_FALSE(Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0) != Ellipsoid({ 1.0, 2.0, 3.0 }, 4.0, 5.0, 6.0)) ;

    }

    {

        // [TBI] Check invariants after rotation

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

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Intersects)
{

    using library::core::types::Real ;

    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Segment ;
    using library::math::geom::d3::objects::Ellipsoid ;

    // Segment

    {

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

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Contains)
{

    using library::math::geom::d3::objects::Ellipsoid ;

    {

        FAIL() ;

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

    using library::math::geom::d3::objects::Ellipsoid ;

    {

        FAIL() ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, GetSecondAxis)
{

    using library::math::geom::d3::objects::Ellipsoid ;

    {

        FAIL() ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, GetThirdAxis)
{

    using library::math::geom::d3::objects::Ellipsoid ;

    {

        FAIL() ;

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

    using library::math::geom::d3::objects::Ellipsoid ;

    {

        FAIL() ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Translate)
{

    using library::math::geom::d3::objects::Ellipsoid ;

    {

        FAIL() ;

    }

}

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Rotate)
{

    using library::math::geom::d3::objects::Ellipsoid ;

    {

        FAIL() ;

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