////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Mathematics
/// @file           Library/Mathematics/Geometry/3D/Transformation.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>
#include <Library/Mathematics/Geometry/3D/Transformation.hpp>

#include <Library/Core/Containers/Map.hpp>
#include <Library/Core/Containers/Pair.hpp>
#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace math
{
namespace geom
{
namespace d3
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Transformation::Transformation              (   const   Matrix4d&                   aMatrix                                     )
                                :   type_(Transformation::TypeOfMatrix(aMatrix)),
                                    matrix_(aMatrix),
                                    isRigid_(Transformation::IsRigid(aMatrix))
{

}

bool                            Transformation::operator ==                 (   const   Transformation&             aTransformation                             ) const
{

    if ((!this->isDefined()) || (!aTransformation.isDefined()))
    {
        return false ;
    }

    return matrix_ == aTransformation.matrix_ ;

}

bool                            Transformation::operator !=                 (   const   Transformation&             aTransformation                             ) const
{
    return !((*this) == aTransformation) ;
}

Transformation                  Transformation::operator *                  (   const   Transformation&             aTransformation                             ) const
{

    Transformation transformation = { *this } ;

    transformation *= aTransformation ;

    return transformation ;

}

Vector4d                        Transformation::operator *                  (   const   Vector4d&                   aVector                                     ) const
{

    if (!aVector.isDefined())
    {
        throw library::core::error::runtime::Undefined("Vector") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Transformation") ;
    }

    return matrix_ * aVector ;

}

Transformation&                 Transformation::operator *=                 (   const   Transformation&             aTransformation                             )
{

    using library::core::ctnr::Pair ;
    using library::core::ctnr::Map ;

    if (!aTransformation.isDefined())
    {
        throw library::core::error::runtime::Undefined("Transformation") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Transformation") ;
    }

    static const Map<Pair<Transformation::Type, Transformation::Type>, Transformation::Type> TypeCompositionMap =
    {

        { { Transformation::Type::Undefined,        Transformation::Type::Undefined },      Transformation::Type::Undefined },
        { { Transformation::Type::Undefined,        Transformation::Type::Identity },       Transformation::Type::Undefined },
        { { Transformation::Type::Undefined,        Transformation::Type::Translation },    Transformation::Type::Undefined },
        { { Transformation::Type::Undefined,        Transformation::Type::Rotation },       Transformation::Type::Undefined },
        { { Transformation::Type::Undefined,        Transformation::Type::Scaling },        Transformation::Type::Undefined },
        { { Transformation::Type::Undefined,        Transformation::Type::Reflection },     Transformation::Type::Undefined },
        { { Transformation::Type::Undefined,        Transformation::Type::Shear },          Transformation::Type::Undefined },
        { { Transformation::Type::Undefined,        Transformation::Type::Affine },         Transformation::Type::Undefined },

        { { Transformation::Type::Identity,         Transformation::Type::Undefined },      Transformation::Type::Undefined },
        { { Transformation::Type::Identity,         Transformation::Type::Identity },       Transformation::Type::Identity },
        { { Transformation::Type::Identity,         Transformation::Type::Translation },    Transformation::Type::Translation },
        { { Transformation::Type::Identity,         Transformation::Type::Rotation },       Transformation::Type::Rotation },
        { { Transformation::Type::Identity,         Transformation::Type::Scaling },        Transformation::Type::Scaling },
        { { Transformation::Type::Identity,         Transformation::Type::Reflection },     Transformation::Type::Reflection },
        { { Transformation::Type::Identity,         Transformation::Type::Shear },          Transformation::Type::Shear },
        { { Transformation::Type::Identity,         Transformation::Type::Affine },         Transformation::Type::Affine },

        { { Transformation::Type::Translation,      Transformation::Type::Undefined },      Transformation::Type::Undefined },
        { { Transformation::Type::Translation,      Transformation::Type::Identity },       Transformation::Type::Translation },
        { { Transformation::Type::Translation,      Transformation::Type::Translation },    Transformation::Type::Translation },
        { { Transformation::Type::Translation,      Transformation::Type::Rotation },       Transformation::Type::Affine },
        { { Transformation::Type::Translation,      Transformation::Type::Scaling },        Transformation::Type::Affine },
        { { Transformation::Type::Translation,      Transformation::Type::Reflection },     Transformation::Type::Affine },
        { { Transformation::Type::Translation,      Transformation::Type::Shear },          Transformation::Type::Affine },
        { { Transformation::Type::Translation,      Transformation::Type::Affine },         Transformation::Type::Affine },

        { { Transformation::Type::Rotation,         Transformation::Type::Undefined },      Transformation::Type::Undefined },
        { { Transformation::Type::Rotation,         Transformation::Type::Identity },       Transformation::Type::Rotation },
        { { Transformation::Type::Rotation,         Transformation::Type::Translation },    Transformation::Type::Affine },
        { { Transformation::Type::Rotation,         Transformation::Type::Rotation },       Transformation::Type::Rotation },
        { { Transformation::Type::Rotation,         Transformation::Type::Scaling },        Transformation::Type::Affine },
        { { Transformation::Type::Rotation,         Transformation::Type::Reflection },     Transformation::Type::Affine },
        { { Transformation::Type::Rotation,         Transformation::Type::Shear },          Transformation::Type::Affine },
        { { Transformation::Type::Rotation,         Transformation::Type::Affine },         Transformation::Type::Affine },

        { { Transformation::Type::Reflection,       Transformation::Type::Undefined },      Transformation::Type::Undefined },
        { { Transformation::Type::Reflection,       Transformation::Type::Identity },       Transformation::Type::Reflection },
        { { Transformation::Type::Reflection,       Transformation::Type::Translation },    Transformation::Type::Affine },
        { { Transformation::Type::Reflection,       Transformation::Type::Rotation },       Transformation::Type::Affine },
        { { Transformation::Type::Reflection,       Transformation::Type::Scaling },        Transformation::Type::Affine },
        { { Transformation::Type::Reflection,       Transformation::Type::Reflection },     Transformation::Type::Affine },
        { { Transformation::Type::Reflection,       Transformation::Type::Shear },          Transformation::Type::Affine },
        { { Transformation::Type::Reflection,       Transformation::Type::Affine },         Transformation::Type::Affine },

        { { Transformation::Type::Scaling,          Transformation::Type::Undefined },      Transformation::Type::Undefined },
        { { Transformation::Type::Scaling,          Transformation::Type::Identity },       Transformation::Type::Scaling },
        { { Transformation::Type::Scaling,          Transformation::Type::Translation },    Transformation::Type::Affine },
        { { Transformation::Type::Scaling,          Transformation::Type::Rotation },       Transformation::Type::Affine },
        { { Transformation::Type::Scaling,          Transformation::Type::Scaling },        Transformation::Type::Scaling },
        { { Transformation::Type::Scaling,          Transformation::Type::Reflection },     Transformation::Type::Affine },
        { { Transformation::Type::Scaling,          Transformation::Type::Shear },          Transformation::Type::Affine },
        { { Transformation::Type::Scaling,          Transformation::Type::Affine },         Transformation::Type::Affine },

        { { Transformation::Type::Shear,            Transformation::Type::Undefined },      Transformation::Type::Undefined },
        { { Transformation::Type::Shear,            Transformation::Type::Identity },       Transformation::Type::Shear },
        { { Transformation::Type::Shear,            Transformation::Type::Translation },    Transformation::Type::Affine },
        { { Transformation::Type::Shear,            Transformation::Type::Rotation },       Transformation::Type::Affine },
        { { Transformation::Type::Shear,            Transformation::Type::Scaling },        Transformation::Type::Affine },
        { { Transformation::Type::Shear,            Transformation::Type::Reflection },     Transformation::Type::Affine },
        { { Transformation::Type::Shear,            Transformation::Type::Shear },          Transformation::Type::Affine },
        { { Transformation::Type::Shear,            Transformation::Type::Affine },         Transformation::Type::Affine },

        { { Transformation::Type::Affine,           Transformation::Type::Undefined },      Transformation::Type::Undefined },
        { { Transformation::Type::Affine,           Transformation::Type::Identity },       Transformation::Type::Affine },
        { { Transformation::Type::Affine,           Transformation::Type::Translation },    Transformation::Type::Affine },
        { { Transformation::Type::Affine,           Transformation::Type::Rotation },       Transformation::Type::Affine },
        { { Transformation::Type::Affine,           Transformation::Type::Scaling },        Transformation::Type::Affine },
        { { Transformation::Type::Affine,           Transformation::Type::Reflection },     Transformation::Type::Affine },
        { { Transformation::Type::Affine,           Transformation::Type::Shear },          Transformation::Type::Affine },
        { { Transformation::Type::Affine,           Transformation::Type::Affine },         Transformation::Type::Affine }

    } ;

    type_ = TypeCompositionMap.at({ type_, aTransformation.type_ }) ;
    matrix_ *= aTransformation.matrix_ ;
    isRigid_ = isRigid_ && aTransformation.isRigid_ ;

    return *this ;

}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Transformation&             aTransformation                             )
{

    aTransformation.print(anOutputStream, true) ;

    return anOutputStream ;

}

bool                            Transformation::isDefined                   ( ) const
{
    return type_ != Transformation::Type::Undefined ;
}

bool                            Transformation::isIdentity                  ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Transformation") ;
    }

    return type_ == Transformation::Type::Identity ;

}

bool                            Transformation::isRigid                     ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Transformation") ;
    }

    return isRigid_ ;

}

Transformation::Type            Transformation::getType                     ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Transformation") ;
    }

    return type_ ;

}

Matrix4d                        Transformation::getMatrix                   ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Transformation") ;
    }

    return matrix_ ;

}

Transformation                  Transformation::getInverse                  ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Transformation") ;
    }

    return { type_, matrix_.inverse(), isRigid_ } ;

}

Point                           Transformation::applyTo                     (   const   Point&                      aPoint                                      ) const
{
    return Point::Vector((matrix_ * Vector4d(aPoint.x(), aPoint.y(), aPoint.z(), 1.0)).head<3>()) ;
}

Vector3d                        Transformation::applyTo                     (   const   Vector3d&                   aVector                                     ) const
{
    return Vector3d { (matrix_ * Vector4d(aVector.x(), aVector.y(), aVector.z(), 0.0)).head<3>() } ;
}

void                            Transformation::print                       (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           ) const
{

    displayDecorators ? library::core::utils::Print::Header(anOutputStream, "3D :: Transformation") : void () ;

    library::core::utils::Print::Line(anOutputStream) << "Type:"                << Transformation::StringFromType(type_) ;

    library::core::utils::Print::Line(anOutputStream) << "Matrix:" ;

    anOutputStream << matrix_ << std::endl ;

    displayDecorators ? library::core::utils::Print::Footer(anOutputStream) : void () ;

}

Transformation                  Transformation::Undefined                   ( )
{
    return { Transformation::Type::Undefined, Matrix4d::Undefined(), false } ;
}

Transformation                  Transformation::Identity                    ( )
{
    return { Transformation::Type::Identity, Matrix4d::Identity(), true } ;
}

Transformation                  Transformation::Translation                 (   const   Vector3d&                   aTranslationVector                          )
{

    if (!aTranslationVector.isDefined())
    {
        throw library::core::error::runtime::Undefined("Translation vector") ;
    }

    Matrix4d transformationMatrix ;

    transformationMatrix << 1.0, 0.0, 0.0, aTranslationVector.x(),
                            0.0, 1.0, 0.0, aTranslationVector.y(),
                            0.0, 0.0, 1.0, aTranslationVector.z(),
                            0.0, 0.0, 0.0, 1.0 ;

    return { Transformation::Type::Translation, transformationMatrix, true } ;

}

Transformation                  Transformation::Rotation                    (   const   RotationVector&             aRotationVector                             )
{

    if (!aRotationVector.isDefined())
    {
        throw library::core::error::runtime::Undefined("Rotation vector") ;
    }

    Matrix4d transformationMatrix = Matrix4d::Identity() ;

    transformationMatrix.block<3, 3>(0, 0) = RotationMatrix::RotationVector(aRotationVector).getMatrix().transpose() ;

    return { Transformation::Type::Rotation, transformationMatrix, true } ;

}

Transformation                  Transformation::Rotation                    (   const   RotationMatrix&             aRotationMatrix                             )
{

    if (!aRotationMatrix.isDefined())
    {
        throw library::core::error::runtime::Undefined("Rotation matrix") ;
    }

    Matrix4d transformationMatrix = Matrix4d::Identity() ;

    transformationMatrix.block<3, 3>(0, 0) = aRotationMatrix.getMatrix().transpose() ;

    return { Transformation::Type::Rotation, transformationMatrix, true } ;

}

Transformation                  Transformation::RotationAround              (   const   Point&                      aPoint,
                                                                                const   RotationVector&             aRotationVector                             )
{
    return Transformation::Translation(aPoint.asVector()) * Transformation::Rotation(aRotationVector) * Transformation::Translation(-aPoint.asVector()) ;
}

String                          Transformation::StringFromType              (   const   Transformation::Type&       aType                                       )
{

    switch (aType)
    {

        case Transformation::Type::Undefined:
            return "Undefined" ;

        case Transformation::Type::Identity:
            return "Identity" ;

        case Transformation::Type::Translation:
            return "Translation" ;

        case Transformation::Type::Rotation:
            return "Rotation" ;

        case Transformation::Type::Scaling:
            return "Scaling" ;

        case Transformation::Type::Reflection:
            return "Reflection" ;

        case Transformation::Type::Shear:
            return "Shear" ;

        case Transformation::Type::Affine:
            return "Affine" ;

        default:
            throw library::core::error::runtime::Wrong("Type") ;
            break ;

    }

    return String::Empty() ;

}

Transformation::Type            Transformation::TypeOfMatrix                (   const   Matrix4d&                   aMatrix                                     )
{

    if (!aMatrix.isDefined())
    {
        return Transformation::Type::Undefined ;
    }

    if (aMatrix.isIdentity())
    {
        return Transformation::Type::Identity ;
    }

    // [TBI] ...

    throw library::core::error::RuntimeError("Cannot identify transformation type.") ;

    return Transformation::Type::Undefined ;

}

bool                            Transformation::IsRigid                     (   const   Matrix4d&                   aMatrix                                     )
{

    using library::math::obj::Matrix3d ;

    if (!aMatrix.isDefined())
    {
        return false ;
    }

    if ((aMatrix(3, 0) != 0.0) || (aMatrix(3, 1) != 0.0) || (aMatrix(3, 2) != 0.0) || (aMatrix(3, 3) != 1.0))
    {
        return false ;
    }

    const Matrix3d topLeftMatrix = aMatrix.topLeftCorner<3, 3>() ;

    return (topLeftMatrix.transpose() * topLeftMatrix).isIdentity() ;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Transformation::Transformation              (   const   Transformation::Type&       aType,
                                                                                const   Matrix4d&                   aMatrix,
                                                                                const   bool                        isRigid                                     )
                                :   type_(aType),
                                    matrix_(aMatrix),
                                    isRigid_(isRigid)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
