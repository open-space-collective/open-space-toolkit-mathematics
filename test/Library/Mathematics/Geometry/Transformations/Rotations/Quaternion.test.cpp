////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/Transformations/Rotations/Quaternion.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/Transformations/Rotations/Quaternion.hpp>

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

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, MultiplicationOperator)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        FAIL() ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, DivisionOperator)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        FAIL() ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, StreamOperator)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        FAIL() ;

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

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, ToNormalized)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        FAIL() ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, ToConjugate)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        EXPECT_EQ(Quaternion::XYZS(-1.0, -2.0, -3.0, +4.0).toConjugate(), Quaternion::XYZS(+1.0, +2.0, +3.0, +4.0).toConjugate()) ;
        EXPECT_EQ(Quaternion::XYZS(+1.0, +2.0, +3.0, +4.0).toConjugate(), Quaternion::XYZS(-1.0, -2.0, -3.0, +4.0).toConjugate()) ;

        EXPECT_EQ(Quaternion::XYZS(-1.0, -2.0, -3.0, -4.0).toConjugate(), Quaternion::XYZS(+1.0, +2.0, +3.0, -4.0).toConjugate()) ;
        EXPECT_EQ(Quaternion::XYZS(+1.0, +2.0, +3.0, -4.0).toConjugate(), Quaternion::XYZS(-1.0, -2.0, -3.0, -4.0).toConjugate()) ;

    }

    {

        EXPECT_ANY_THROW(Quaternion::Undefined().toConjugate()) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, ToInverse)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        FAIL() ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, Pow)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        FAIL() ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, Exp)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        FAIL() ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, Log)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        FAIL() ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, Norm)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        FAIL() ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, CrossMultiply)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        FAIL() ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, DotMultiply)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        FAIL() ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, RotateVector)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        FAIL() ;

    }

}

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

        EXPECT_EQ("[0.000000, 0.000000, 0.000000, 1.000000]", Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).toString(Quaternion::Format::XYZS)) ;
        EXPECT_EQ("[1.000000, 0.000000, 0.000000, 0.000000]", Quaternion::XYZS(0.0, 0.0, 0.0, 1.0).toString(Quaternion::Format::SXYZ)) ;

    }

    {

        EXPECT_ANY_THROW(Quaternion::Undefined().toString()) ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, Normalize)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        FAIL() ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, Conjugate)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        FAIL() ;

    }

}

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, Inverse)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        FAIL() ;

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

TEST (Library_Mathematics_Geometry_Transformations_Rotations_Quaternion, Parse)
{

    using library::math::geom::trf::rot::Quaternion ;
    
    {

        EXPECT_NO_THROW(Quaternion::Parse("[0.0, 0.0, 0.0, 1.0]", Quaternion::Format::XYZS)) ;
        EXPECT_EQ(Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS), Quaternion::Parse("[0.0, 0.0, 0.0, 1.0]", Quaternion::Format::XYZS)) ;
        EXPECT_EQ(Quaternion(0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS), Quaternion::Parse("[1.0, 0.0, 0.0, 0.0]", Quaternion::Format::SXYZ)) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////