////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/Transformations/Rotations/RotationVector.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationVector.hpp>
#include <Library/Mathematics/Geometry/Transformations/Rotations/RotationMatrix.hpp>
#include <Library/Mathematics/Geometry/Transformations/Rotations/Quaternion.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace math
{
namespace geom
{
namespace trf
{
namespace rot
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


                                RotationVector::RotationVector              (   const   Vector3d&                   anAxis,
                                                                                const   Angle&                      anAngle                                     )
                                :   axis_(anAxis.isDefined() ? anAxis.normalized() : Vector3d::Undefined()),
                                    angle_(anAngle)
{

    if (anAxis.isDefined() && (std::abs(anAxis.norm() - 1.0) > Real::Epsilon()))
    {
        throw library::core::error::RuntimeError("Axis with norm [{}] is not unitary.", anAxis.norm()) ;
    }

}

bool                            RotationVector::operator ==                 (   const   RotationVector&             aRotationVector                             ) const
{

    if ((!this->isDefined()) || (!aRotationVector.isDefined()))
    {
        return false ;
    }

    if (angle_.isZero() && aRotationVector.angle_.isZero())
    {
        return true ;
    }
    
    return ((axis_ ==  aRotationVector.axis_) && (angle_ ==  aRotationVector.angle_))
        || ((axis_ == -aRotationVector.axis_) && (angle_ == -aRotationVector.angle_)) ;

}

bool                            RotationVector::operator !=                 (   const   RotationVector&             aRotationVector                             ) const
{
    return !((*this) == aRotationVector) ;
}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   RotationVector&             aRotationVector                             )
{

    library::core::utils::Print::Header(anOutputStream, "Rotation Vector") ;

    library::core::utils::Print::Line(anOutputStream) << "Axis:" << (aRotationVector.isDefined() ? aRotationVector.getAxis().toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Angle:" << (aRotationVector.isDefined() ? aRotationVector.getAngle().toString() : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            RotationVector::isDefined                   ( ) const
{
    return axis_.isDefined() && angle_.isDefined() ;
}

Vector3d                        RotationVector::getAxis                     ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Rotation vector") ;
    }
    
    return axis_ ;

}

Angle                           RotationVector::getAngle                    ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Rotation vector") ;
    }
    
    return angle_ ;

}

RotationVector                  RotationVector::Undefined                   ( )
{
    return RotationVector() ;
}

RotationVector                  RotationVector::Unit                        ( )
{
    return RotationVector({ 0.0, 0.0, 1.0 }, Angle::Zero()) ;
}

RotationVector                  RotationVector::Quaternion                  (   const   rot::Quaternion&            aQuaternion                                 )
{

    if (!aQuaternion.isDefined())
    {
        throw library::core::error::runtime::Undefined("Quaternion") ;
    }

    if (!aQuaternion.isUnitary())
    {
        throw library::core::error::RuntimeError("Quaternion is not unitary.") ;
    }

    // if (aQuaternion.isNear(rot::Quaternion::Unit(), Angle::Radians(Real::Epsilon())))
    // {
    //     return RotationVector::Unit() ;
    // }

    // std::cout << "aQuaternion = " << aQuaternion.toString() << std::endl ;
    // std::cout << "1.0 - aQuaternion.s() * aQuaternion.s() = " << (1.0 - aQuaternion.s() * aQuaternion.s()).toString() << std::endl ;

    if ((1.0 - aQuaternion.s() * aQuaternion.s()).abs() < Real::Epsilon())
    {
        return RotationVector::Unit() ;
    }

    // if (aQuaternion.s() < 0.0)
    // {
    //     return RotationVector::Quaternion(Quaternion(aQuaternion).rectify()) ;
    // }

    const Vector3d axis = (aQuaternion.getVectorPart() / (1.0 - aQuaternion.s() * aQuaternion.s()).sqrt()).normalized() ;
    
    // const Angle angle = Angle::Radians(2.0 * std::acos(aQuaternion.s())) ;
    const Angle angle = Angle::Radians(2.0 * std::atan2(aQuaternion.getVectorPart().norm(), aQuaternion.s())) ;

    return RotationVector(axis, angle) ;

}

RotationVector                  RotationVector::RotationMatrix              (   const   rot::RotationMatrix&        aRotationMatrix                             )
{

    if (!aRotationMatrix.isDefined())
    {
        throw library::core::error::runtime::Undefined("Rotation matrix") ;
    }

    const Angle angle = Angle::Radians(std::acos((aRotationMatrix.accessMatrix().trace() - 1.0) / 2.0)) ;

    if (angle.inRadians().abs() < Real::Epsilon())
    {   
        return RotationVector(Vector3d::X(), angle) ;
    }

    const double x = aRotationMatrix(1, 2) - aRotationMatrix(2, 1) ;
    const double y = aRotationMatrix(2, 0) - aRotationMatrix(0, 2) ;
    const double z = aRotationMatrix(0, 1) - aRotationMatrix(1, 0) ;

    // const Vector3d axis = (1.0 / (2.0 * std::sin(angle.inRadians()))) * Vector3d(x, y, z) ;
    const Vector3d axis = Vector3d(x, y, z).normalized() ;

    return RotationVector(axis, angle) ;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                RotationVector::RotationVector              ( )
                                :   axis_(Vector3d::Undefined()),
                                    angle_(Angle::Undefined())
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////