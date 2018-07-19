////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Ellipsoid.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>

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

TEST (Library_Mathematics_Geometry_3D_Objects_Ellipsoid, Undefined)
{

    using library::math::geom::d3::objects::Ellipsoid ;
    
    {

        EXPECT_NO_THROW(Ellipsoid::Undefined()) ;
        EXPECT_FALSE(Ellipsoid::Undefined().isDefined()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////