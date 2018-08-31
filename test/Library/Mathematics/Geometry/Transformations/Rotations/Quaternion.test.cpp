////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/Transformations/Rotations/Quaternion.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationMatrix.hpp>
#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/Transformations/Rotations/Quaternion.hpp>
#include <Library/Mathematics/Geometry/Angle.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, Constructor)
{

    using library::math::obj::Vector3d ;
    using library::math::obj::Vector4d ;
    using library::math::geom::trf::rot::Quaternion ;

    {

        EXPECT_NO_THROW(Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS)) ;

        Quaternion quaternion = { 0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS } ;

        EXPECT_TRUE(quaternion.isDefined()) ;

    }

    {

        EXPECT_NO_THROW(Quaternion(Vector4d(0.0, 0.0, 0.0, 1.0), Quaternion::Format::XYZS)) ;

        Quaternion quaternion = { Vector4d(0.0, 0.0, 0.0, 1.0), Quaternion::Format::XYZS } ;

        EXPECT_TRUE(quaternion.isDefined()) ;

    }

    {

        EXPECT_NO_THROW(Quaternion(Vector3d(0.0, 0.0, 0.0), 1.0)) ;

        Quaternion quaternion = { Vector3d(0.0, 0.0, 0.0), 1.0 } ;

        EXPECT_TRUE(quaternion.isDefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, EqualToOperator)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        EXPECT_TRUE(Quaternion(1.0, 0.0, 0.0, 0.0, Quaternion::Format::XYZS) == Quaternion(1.0, 0.0, 0.0, 0.0, Quaternion::Format::XYZS)) ;
        EXPECT_TRUE(Quaternion(0.0, 1.0, 0.0, 0.0, Quaternion::Format::XYZS) == Quaternion(0.0, 1.0, 0.0, 0.0, Quaternion::Format::XYZS)) ;
        EXPECT_TRUE(Quaternion(0.0, 0.0, 1.0, 0.0, Quaternion::Format::XYZS) == Quaternion(0.0, 0.0, 1.0, 0.0, Quaternion::Format::XYZS)) ;
        EXPECT_TRUE(Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS) == Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS)) ;

        EXPECT_TRUE(Quaternion(1.0, 0.0, 0.0, 0.0, Quaternion::Format::XYZS) == Quaternion(-1.0, -0.0, -0.0, -0.0, Quaternion::Format::XYZS)) ;
        EXPECT_TRUE(Quaternion(0.0, 1.0, 0.0, 0.0, Quaternion::Format::XYZS) == Quaternion(-0.0, -1.0, -0.0, -0.0, Quaternion::Format::XYZS)) ;
        EXPECT_TRUE(Quaternion(0.0, 0.0, 1.0, 0.0, Quaternion::Format::XYZS) == Quaternion(-0.0, -0.0, -1.0, -0.0, Quaternion::Format::XYZS)) ;
        EXPECT_TRUE(Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS) == Quaternion(-0.0, -0.0, -0.0, -1.0, Quaternion::Format::XYZS)) ;

        EXPECT_TRUE(Quaternion(-1.0, -0.0, -0.0, -0.0, Quaternion::Format::XYZS) == Quaternion(1.0, 0.0, 0.0, 0.0, Quaternion::Format::XYZS)) ;
        EXPECT_TRUE(Quaternion(-0.0, -1.0, -0.0, -0.0, Quaternion::Format::XYZS) == Quaternion(0.0, 1.0, 0.0, 0.0, Quaternion::Format::XYZS)) ;
        EXPECT_TRUE(Quaternion(-0.0, -0.0, -1.0, -0.0, Quaternion::Format::XYZS) == Quaternion(0.0, 0.0, 1.0, 0.0, Quaternion::Format::XYZS)) ;
        EXPECT_TRUE(Quaternion(-0.0, -0.0, -0.0, -1.0, Quaternion::Format::XYZS) == Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS)) ;

    }

    {

        EXPECT_FALSE(Quaternion(1.0, 0.0, 0.0, 0.0, Quaternion::Format::XYZS) == Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS)) ;
        EXPECT_FALSE(Quaternion(0.0, 1.0, 0.0, 0.0, Quaternion::Format::XYZS) == Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS)) ;
        EXPECT_FALSE(Quaternion(0.0, 0.0, 1.0, 0.0, Quaternion::Format::XYZS) == Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS)) ;

    }

    {

        EXPECT_FALSE(Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS) == Quaternion::Undefined()) ;
        EXPECT_FALSE(Quaternion::Undefined() == Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS)) ;
        EXPECT_FALSE(Quaternion::Undefined() == Quaternion::Undefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, NotEqualToOperator)
{

    using library::math::geom::trf::rot::Quaternion ;

    {

        EXPECT_TRUE(Quaternion(1.0, 0.0, 0.0, 0.0, Quaternion::Format::XYZS) != Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS)) ;
        EXPECT_TRUE(Quaternion(0.0, 1.0, 0.0, 0.0, Quaternion::Format::XYZS) != Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS)) ;
        EXPECT_TRUE(Quaternion(0.0, 0.0, 1.0, 0.0, Quaternion::Format::XYZS) != Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS)) ;

    }

    {

        EXPECT_TRUE(Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS) != Quaternion::Undefined()) ;
        EXPECT_TRUE(Quaternion::Undefined() != Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS)) ;
        EXPECT_TRUE(Quaternion::Undefined() != Quaternion::Undefined()) ;

    }
    
    {

        EXPECT_FALSE(Quaternion(1.0, 0.0, 0.0, 0.0, Quaternion::Format::XYZS) != Quaternion(1.0, 0.0, 0.0, 0.0, Quaternion::Format::XYZS)) ;
        EXPECT_FALSE(Quaternion(0.0, 1.0, 0.0, 0.0, Quaternion::Format::XYZS) != Quaternion(0.0, 1.0, 0.0, 0.0, Quaternion::Format::XYZS)) ;
        EXPECT_FALSE(Quaternion(0.0, 0.0, 1.0, 0.0, Quaternion::Format::XYZS) != Quaternion(0.0, 0.0, 1.0, 0.0, Quaternion::Format::XYZS)) ;
        EXPECT_FALSE(Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS) != Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS)) ;

        EXPECT_FALSE(Quaternion(1.0, 0.0, 0.0, 0.0, Quaternion::Format::XYZS) != Quaternion(-1.0, -0.0, -0.0, -0.0, Quaternion::Format::XYZS)) ;
        EXPECT_FALSE(Quaternion(0.0, 1.0, 0.0, 0.0, Quaternion::Format::XYZS) != Quaternion(-0.0, -1.0, -0.0, -0.0, Quaternion::Format::XYZS)) ;
        EXPECT_FALSE(Quaternion(0.0, 0.0, 1.0, 0.0, Quaternion::Format::XYZS) != Quaternion(-0.0, -0.0, -1.0, -0.0, Quaternion::Format::XYZS)) ;
        EXPECT_FALSE(Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS) != Quaternion(-0.0, -0.0, -0.0, -1.0, Quaternion::Format::XYZS)) ;

        EXPECT_FALSE(Quaternion(-1.0, -0.0, -0.0, -0.0, Quaternion::Format::XYZS) != Quaternion(1.0, 0.0, 0.0, 0.0, Quaternion::Format::XYZS)) ;
        EXPECT_FALSE(Quaternion(-0.0, -1.0, -0.0, -0.0, Quaternion::Format::XYZS) != Quaternion(0.0, 1.0, 0.0, 0.0, Quaternion::Format::XYZS)) ;
        EXPECT_FALSE(Quaternion(-0.0, -0.0, -1.0, -0.0, Quaternion::Format::XYZS) != Quaternion(0.0, 0.0, 1.0, 0.0, Quaternion::Format::XYZS)) ;
        EXPECT_FALSE(Quaternion(-0.0, -0.0, -0.0, -1.0, Quaternion::Format::XYZS) != Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS)) ;

    }

}

// TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, MultiplicationOperator)
// {

//     using library::math::geom::trf::rot::Quaternion ;
    
//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, DivisionOperator)
// {

//     using library::math::geom::trf::rot::Quaternion ;
    
//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, MultiplicationAssignmentOperator)
// {

//     using library::math::geom::trf::rot::Quaternion ;
    
//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, DivisionAssignmentOperator)
// {

//     using library::math::geom::trf::rot::Quaternion ;
    
//     {

//         FAIL() ;

//     }

// }

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, StreamOperator)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << Quaternion::XYZS(0.0, 0.0, 0.0, 1.0) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, IsDefined)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        EXPECT_TRUE(Quaternion::XYZS(1.0, 0.0, 0.0, 0.0).isDefined()) ;
        EXPECT_TRUE(Quaternion::XYZS(0.0, 1.0, 0.0, 0.0).isDefined()) ;
        EXPECT_TRUE(Quaternion::XYZS(0.0, 0.0, 1.0, 0.0).isDefined()) ;
        EXPECT_TRUE(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).isDefined()) ;

    }

    {

        EXPECT_TRUE(Quaternion::XYZS(1.0, 2.0, 3.0, 4.0).isDefined()) ;

    }

    {

        EXPECT_FALSE(Quaternion::Undefined().isDefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, IsUnitary)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        EXPECT_TRUE(Quaternion::XYZS(1.0, 0.0, 0.0, 0.0).isUnitary()) ;
        EXPECT_TRUE(Quaternion::XYZS(0.0, 1.0, 0.0, 0.0).isUnitary()) ;
        EXPECT_TRUE(Quaternion::XYZS(0.0, 0.0, 1.0, 0.0).isUnitary()) ;
        EXPECT_TRUE(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).isUnitary()) ;

    }

    {

        EXPECT_FALSE(Quaternion::XYZS(1.0, 2.0, 3.0, 4.0).isUnitary()) ;

    }

    {

        EXPECT_ANY_THROW(Quaternion::Undefined().isUnitary()) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, IsNear)
{

    using library::math::geom::Angle ;
    using library::math::geom::trf::rot::Quaternion ;
    
    {

        EXPECT_TRUE(Quaternion::XYZS(1.0, 0.0, 0.0, 0.0).isNear(Quaternion::XYZS(1.0, 0.0, 0.0, 0.0), Angle::Zero())) ;
        EXPECT_TRUE(Quaternion::XYZS(0.0, 1.0, 0.0, 0.0).isNear(Quaternion::XYZS(0.0, 1.0, 0.0, 0.0), Angle::Zero())) ;
        EXPECT_TRUE(Quaternion::XYZS(0.0, 0.0, 1.0, 0.0).isNear(Quaternion::XYZS(0.0, 0.0, 1.0, 0.0), Angle::Zero())) ;
        EXPECT_TRUE(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).isNear(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0), Angle::Zero())) ;

        EXPECT_TRUE(Quaternion::XYZS(1.0, 0.0, 0.0, 0.0).isNear(Quaternion::XYZS(1.0 + 1e-6, 0.0, 0.0, 0.0).normalize(), Angle::Radians(1e-6))) ;
        EXPECT_TRUE(Quaternion::XYZS(0.0, 1.0, 0.0, 0.0).isNear(Quaternion::XYZS(0.0, 1.0 + 1e-6, 0.0, 0.0).normalize(), Angle::Radians(1e-6))) ;
        EXPECT_TRUE(Quaternion::XYZS(0.0, 0.0, 1.0, 0.0).isNear(Quaternion::XYZS(0.0, 0.0, 1.0 + 1e-6, 0.0).normalize(), Angle::Radians(1e-6))) ;
        EXPECT_TRUE(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).isNear(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0 + 1e-6).normalize(), Angle::Radians(1e-6))) ;

    }

    {

        EXPECT_TRUE(Quaternion::XYZS(1.0, 0.0, 0.0, 0.0).isNear(Quaternion::XYZS(1.0 + 1e-6, 0.0, 0.0, 0.0).normalize(), Angle::Radians(0.0))) ;
        EXPECT_TRUE(Quaternion::XYZS(0.0, 1.0, 0.0, 0.0).isNear(Quaternion::XYZS(0.0, 1.0 + 1e-6, 0.0, 0.0).normalize(), Angle::Radians(0.0))) ;
        EXPECT_TRUE(Quaternion::XYZS(0.0, 0.0, 1.0, 0.0).isNear(Quaternion::XYZS(0.0, 0.0, 1.0 + 1e-6, 0.0).normalize(), Angle::Radians(0.0))) ;
        EXPECT_TRUE(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).isNear(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0 + 1e-6).normalize(), Angle::Radians(0.0))) ;

    }

    {

        EXPECT_ANY_THROW(Quaternion::Undefined().isNear(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0), Angle::Degrees(0.0))) ;
        EXPECT_ANY_THROW(Quaternion::Undefined().isNear(Quaternion::XYZS(0.0, 0.0, 0.0, 1.1), Angle::Degrees(0.0))) ;

        EXPECT_ANY_THROW(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).isNear(Quaternion::Undefined(), Angle::Degrees(0.0))) ;
        EXPECT_ANY_THROW(Quaternion::XYZS(0.0, 0.0, 0.0, 1.1).isNear(Quaternion::Undefined(), Angle::Degrees(0.0))) ;

        EXPECT_ANY_THROW(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).isNear(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0), Angle::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, X)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        EXPECT_EQ(1.0, Quaternion::XYZS(1.0, 2.0, 3.0, 4.0).x()) ;

    }

    {

        EXPECT_ANY_THROW(Quaternion::Undefined().x()) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, Y)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        EXPECT_EQ(2.0, Quaternion::XYZS(1.0, 2.0, 3.0, 4.0).y()) ;

    }

    {

        EXPECT_ANY_THROW(Quaternion::Undefined().y()) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, Z)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        EXPECT_EQ(3.0, Quaternion::XYZS(1.0, 2.0, 3.0, 4.0).z()) ;

    }

    {

        EXPECT_ANY_THROW(Quaternion::Undefined().z()) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, S)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        EXPECT_EQ(4.0, Quaternion::XYZS(1.0, 2.0, 3.0, 4.0).s()) ;

    }

    {

        EXPECT_ANY_THROW(Quaternion::Undefined().s()) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, GetVectorPart)
{

    using library::math::obj::Vector3d ;
    using library::math::geom::trf::rot::Quaternion ;
    
    {

        EXPECT_EQ(Vector3d(1.0, 2.0, 3.0), Quaternion::XYZS(1.0, 2.0, 3.0, 4.0).getVectorPart()) ;

    }

    {

        EXPECT_ANY_THROW(Quaternion::Undefined().getVectorPart()) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, GetScalarPart)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        EXPECT_EQ(4.0, Quaternion::XYZS(1.0, 2.0, 3.0, 4.0).getScalarPart()) ;

    }

    {

        EXPECT_ANY_THROW(Quaternion::Undefined().getScalarPart()) ;

    }

}

// TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, ToNormalized)
// {

//     using library::math::geom::trf::rot::Quaternion ;
    
//     {

//         FAIL() ;

//     }

// }

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, ToConjugate)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        EXPECT_EQ(Quaternion::XYZS(-1.0, -2.0, -3.0, +4.0), Quaternion::XYZS(+1.0, +2.0, +3.0, +4.0).toConjugate()) ;
        EXPECT_EQ(Quaternion::XYZS(+1.0, +2.0, +3.0, +4.0), Quaternion::XYZS(-1.0, -2.0, -3.0, +4.0).toConjugate()) ;

        EXPECT_EQ(Quaternion::XYZS(-1.0, -2.0, -3.0, -4.0), Quaternion::XYZS(+1.0, +2.0, +3.0, -4.0).toConjugate()) ;
        EXPECT_EQ(Quaternion::XYZS(+1.0, +2.0, +3.0, -4.0), Quaternion::XYZS(-1.0, -2.0, -3.0, -4.0).toConjugate()) ;

    }

    {

        EXPECT_ANY_THROW(Quaternion::Undefined().toConjugate()) ;

    }

}

// TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, ToInverse)
// {

//     using library::math::geom::trf::rot::Quaternion ;
    
//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, Pow)
// {

//     using library::math::geom::trf::rot::Quaternion ;
    
//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, Exp)
// {

//     using library::math::geom::trf::rot::Quaternion ;
    
//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, Log)
// {

//     using library::math::geom::trf::rot::Quaternion ;
    
//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, Norm)
// {

//     using library::math::geom::trf::rot::Quaternion ;
    
//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, CrossMultiply)
// {

//     using library::math::geom::trf::rot::Quaternion ;
    
//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, DotMultiply)
// {

//     using library::math::geom::trf::rot::Quaternion ;
    
//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, RotateVector)
// {

//     using library::math::geom::trf::rot::Quaternion ;
    
//     {

//         FAIL() ;

//     }

// }

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, ToVector)
{

    using library::math::obj::Vector4d ;
    using library::math::geom::trf::rot::Quaternion ;
    
    {

        EXPECT_EQ(Vector4d(0.0, 0.0, 0.0, 1.0), Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).toVector(Quaternion::Format::XYZS)) ;
        EXPECT_EQ(Vector4d(1.0, 0.0, 0.0, 0.0), Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).toVector(Quaternion::Format::SXYZ)) ;

    }

    {

        EXPECT_ANY_THROW(Quaternion::Undefined().toVector()) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, ToString)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        EXPECT_EQ("[0.0, 0.0, 0.0, 1.0]", Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).toString(Quaternion::Format::XYZS)) ;
        EXPECT_EQ("[1.0, 0.0, 0.0, 0.0]", Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).toString(Quaternion::Format::SXYZ)) ;

    }

    {

        EXPECT_EQ("[0.00000, 0.00000, 0.00000, 1.00000]", Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).toString(5, Quaternion::Format::XYZS)) ;
        EXPECT_EQ("[1.00000, 0.00000, 0.00000, 0.00000]", Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).toString(5, Quaternion::Format::SXYZ)) ;

    }

    {

        EXPECT_EQ("[0.1, 0.1, 0.1, 0.9]", Quaternion::XYZS(0.1, 0.1, 0.1, 0.9).toString(Quaternion::Format::XYZS)) ;
        EXPECT_EQ("[0.9, 0.1, 0.1, 0.1]", Quaternion::XYZS(0.1, 0.1, 0.1, 0.9).toString(Quaternion::Format::SXYZ)) ;

    }

    {

        EXPECT_ANY_THROW(Quaternion::Undefined().toString()) ;

    }

}

// TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, Normalize)
// {

//     using library::math::geom::trf::rot::Quaternion ;
    
//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, Conjugate)
// {

//     using library::math::geom::trf::rot::Quaternion ;
    
//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, Inverse)
// {

//     using library::math::geom::trf::rot::Quaternion ;
    
//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, Rectify)
// {

//     using library::math::geom::trf::rot::Quaternion ;
    
//     {

//         FAIL() ;

//     }

// }

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, AngularDifferenceWith)
{

    using library::math::geom::Angle ;
    using library::math::geom::trf::rot::Quaternion ;
    
    {

        EXPECT_EQ(Angle::Zero(), Quaternion::Unit().angularDifferenceWith(Quaternion::Unit())) ;
        EXPECT_EQ(Angle::Pi(), Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).angularDifferenceWith(Quaternion::XYZS(0.0, 0.0, 1.0, 0.0))) ;

    }

    {

        EXPECT_ANY_THROW(Quaternion::Undefined().angularDifferenceWith(Quaternion::Undefined())) ;
        EXPECT_ANY_THROW(Quaternion::Unit().angularDifferenceWith(Quaternion::Undefined())) ;
        EXPECT_ANY_THROW(Quaternion::Undefined().angularDifferenceWith(Quaternion::Unit())) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, Undefined)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        EXPECT_NO_THROW(Quaternion::Undefined()) ;
        EXPECT_FALSE(Quaternion::Undefined().isDefined()) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, Unit)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        EXPECT_NO_THROW(Quaternion::Unit()) ;
        EXPECT_EQ(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0), Quaternion::Unit()) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, XYZS)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        EXPECT_NO_THROW(Quaternion::XYZS(0.0, 0.0, 0.0, 1.0)) ;
        EXPECT_EQ(Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS), Quaternion::XYZS(0.0, 0.0, 0.0, 1.0)) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, RotationVector)
{

    using library::core::types::Real ;
    using library::math::geom::Angle ;
    using library::math::geom::trf::rot::RotationVector ;
    using library::math::geom::trf::rot::Quaternion ;
    
    {

        EXPECT_TRUE(Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS).isNear(Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(0.0))), Angle::Radians(Real::Epsilon()))) ;
        EXPECT_TRUE(Quaternion(0.0, 0.0, 1.0, 0.0, Quaternion::Format::XYZS).isNear(Quaternion::RotationVector(RotationVector({ 0.0, 0.0, 1.0 }, Angle::Degrees(180.0))), Angle::Radians(Real::Epsilon()))) ;

    }

    {

        EXPECT_ANY_THROW(Quaternion::RotationVector(RotationVector::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, RotationMatrix)
{

    using library::core::types::Real ;
    using library::math::obj::Vector3d ;
    using library::math::geom::Angle ;
    using library::math::geom::trf::rot::RotationVector ;
    using library::math::geom::trf::rot::RotationMatrix ;
    using library::math::geom::trf::rot::Quaternion ;
    
    {

        EXPECT_TRUE(Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS).isNear(Quaternion::RotationMatrix(RotationMatrix::Unit()), Angle::Radians(Real::Epsilon()))) ;

    }

    {

        for (auto angleDeg = 0.0; angleDeg <= 720.0; angleDeg += 5.0)
        {

            const Angle angle = Angle::Degrees(angleDeg) ;

            for (auto axisIdx = 0; axisIdx < 100; ++axisIdx)
            {

                const Vector3d axis = Vector3d(std::cos(axisIdx), std::sin(axisIdx), std::cos(axisIdx) * std::sin(axisIdx)).normalized() ;

                const RotationVector rotationVector_A_B = RotationVector(axis, angle) ;

                const RotationMatrix rotationMatrix_A_B = RotationMatrix::RotationVector(rotationVector_A_B) ;

                const Quaternion quaternion_A_B = Quaternion::RotationMatrix(rotationMatrix_A_B) ;

                EXPECT_TRUE(rotationMatrix_A_B.accessMatrix().isApprox(RotationMatrix::Quaternion(quaternion_A_B).accessMatrix(), 1e-14)) ;

                for (auto vectorIdx = 0; vectorIdx < 100; ++vectorIdx)
                {

                    const Vector3d vector_B = Vector3d(std::cos(axisIdx), std::sin(axisIdx), std::cos(axisIdx) * std::sin(axisIdx)).normalized() ;

                    EXPECT_TRUE((quaternion_A_B * vector_B).isApprox((rotationMatrix_A_B * vector_B), 1e-14)) ;

                }

            }

        }

    }

    {

        EXPECT_ANY_THROW(Quaternion::RotationMatrix(RotationMatrix::Undefined())) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, Parse)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        EXPECT_NO_THROW(Quaternion::Parse("[0.0, 0.0, 0.0, 1.0]", Quaternion::Format::XYZS)) ;
        EXPECT_EQ(Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS), Quaternion::Parse("[0.0, 0.0, 0.0, 1.0]", Quaternion::Format::XYZS)) ;
        EXPECT_EQ(Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS), Quaternion::Parse("[1.0, 0.0, 0.0, 0.0]", Quaternion::Format::SXYZ)) ;

    }

    {

        EXPECT_ANY_THROW(Quaternion::Parse("")) ;
        EXPECT_ANY_THROW(Quaternion::Parse("[]")) ;
        EXPECT_ANY_THROW(Quaternion::Parse("[0.0, 0.0, 0.0]")) ;
        EXPECT_ANY_THROW(Quaternion::Parse("[0.0, 0.0, 0.0, 0.0, 1.0]")) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////