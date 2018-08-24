////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Ellipsoid.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Objects/Ellipsoid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <Library/Mathematics/Objects/Interval.hpp>

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
namespace objects
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Ellipsoid::Ellipsoid                        (   const   Point&                      aCenter,
                                                                                const   Real&                       aFirstPrincipalSemiAxis,
                                                                                const   Real&                       aSecondPrincipalSemiAxis,
                                                                                const   Real&                       aThirdPrincipalSemiAxis,
                                                                                const   Quaternion&                 anOrientation                               )
                                :   Object(),
                                    center_(aCenter),
                                    a_(aFirstPrincipalSemiAxis),
                                    b_(aSecondPrincipalSemiAxis),
                                    c_(aThirdPrincipalSemiAxis),
                                    q_(anOrientation)
{
    
    if (a_.isDefined() && (a_ < 0.0))
    {
        throw library::core::error::RuntimeError("First principal semi-axis is negative.") ;
    }

    if (b_.isDefined() && (b_ < 0.0))
    {
        throw library::core::error::RuntimeError("Second principal semi-axis is negative.") ;
    }

    if (c_.isDefined() && (c_ < 0.0))
    {
        throw library::core::error::RuntimeError("Third principal semi-axis is negative.") ;
    }

}

Ellipsoid*                      Ellipsoid::clone                            ( ) const
{
    return new Ellipsoid(*this) ;
}

bool                            Ellipsoid::operator ==                      (   const   Ellipsoid&                  anEllipsoid                                 ) const
{

    if ((!this->isDefined()) || (!anEllipsoid.isDefined()))
    {
        return false ;
    }

    // [TBI] Check for invariants after rotation

    return (center_ == anEllipsoid.center_) && (a_ == anEllipsoid.a_) && (b_ == anEllipsoid.b_) && (c_ == anEllipsoid.c_) && (q_ == anEllipsoid.q_) ;

}

bool                            Ellipsoid::operator !=                      (   const   Ellipsoid&                  anEllipsoid                                 ) const
{
    return !((*this) == anEllipsoid) ;
}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Ellipsoid&                  anEllipsoid                                 )
{

    library::core::utils::Print::Header(anOutputStream, "Ellipsoid") ;

    library::core::utils::Print::Line(anOutputStream) << "Center:" << (anEllipsoid.center_.isDefined() ? anEllipsoid.center_.toString() : "Undefined") ;

    library::core::utils::Print::Line(anOutputStream) << "First principal semi-axis:" << (anEllipsoid.a_.isDefined() ? anEllipsoid.a_.toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Second principal semi-axis:" << (anEllipsoid.b_.isDefined() ? anEllipsoid.b_.toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Third principal semi-axis:" << (anEllipsoid.c_.isDefined() ? anEllipsoid.c_.toString() : "Undefined") ;

    library::core::utils::Print::Line(anOutputStream) << "Orientation:" << (anEllipsoid.q_.isDefined() ? anEllipsoid.q_.toString() : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Ellipsoid::isDefined                        ( ) const
{
    return center_.isDefined() && a_.isDefined() && b_.isDefined() && c_.isDefined() && q_.isDefined() ;
}

bool                            Ellipsoid::intersects                       (   const   Segment&                    aSegment                                    ) const
{

    using library::math::obj::Interval ;

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Ellipsoid") ;
    }

    if (!aSegment.isDefined())
    {
        throw library::core::error::runtime::Undefined("Segment") ;
    }

    if (aSegment.isDegenerate())
    {
        return this->contains(aSegment.getFirstPoint()) ;
    }

    // https://www.geometrictools.com/GTEngine/Include/Mathematics/GteIntrSegment3Ellipsoid3.h

    const Vector3d segmentDirection = aSegment.getDirection() ;
    const Vector3d segmentCenter = aSegment.getCenter() ;
    const Real segmentHalfLength = aSegment.getLength() / 2.0 ;

    const Matrix3d M = this->getMatrix() ;

    const Vector3d diff = segmentCenter - this->getCenter() ;
    const Vector3d matDir = M * segmentDirection ;
    const Vector3d matDiff = M * diff ;
    
    const Real a2 = segmentDirection.dot(matDir) ;
    const Real a1 = segmentDirection.dot(matDiff) ;
    const Real a0 = diff.dot(matDiff) - 1.0 ;

    const Real discriminant = (a1 * a1) - (a0 * a2) ;
    
    if (discriminant < 0.0) // No intersection
    {
        return false ;
    }
    else if (discriminant > 0.0)
    {
    
        const Real discriminantRoot = std::sqrt(discriminant) ;
        const Real a2_inverse = 1.0 / a2 ;
        
        const Real t0 = (-a1 - discriminantRoot) * a2_inverse ;
        const Real t1 = (-a1 + discriminantRoot) * a2_inverse ;

        const Interval<Real> resultInterval = Interval<Real>::Open(t0, t1) ;
        const Interval<Real> segmentInterval = Interval<Real>::Closed(-segmentHalfLength, +segmentHalfLength) ;

        if (!resultInterval.contains(segmentInterval))
        {
        
            if (resultInterval.intersects(segmentInterval))
            {
                return true ;
            }
            else // No intersection
            {
                return false ;
            }

        }
        else
        {
            return false ;
        }

    }
    else
    {

        const Real t0 = -a1 / a2 ;
        
        if (std::abs(t0) <= segmentHalfLength) // Single intersection
        {
            return true ;
        }
        else // No intersection
        {
            return false ;
        }

    }

    return false ;

}

bool                            Ellipsoid::contains                         (   const   Point&                      aPoint                                      ) const
{

    using library::math::obj::Vector3d ;

    if (!aPoint.isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Ellipsoid") ;
    }

    Matrix3d dcm ;

    dcm.row(0) = q_ * Vector3d::X() ;
    dcm.row(1) = q_ * Vector3d::Y() ;
    dcm.row(2) = q_ * Vector3d::Z() ;
    
    const Vector3d point = dcm * (aPoint - center_) ;
    
    const Real& x = point.x() ;
    const Real& y = point.y() ;
    const Real& z = point.z() ;

    return std::abs((x * x) / (a_ * a_) + (y * y) / (b_ * b_) + (z * z) / (c_ * c_) - 1.0) < Real::Epsilon() ;

}

// bool                            Ellipsoid::contains                         (   const   PointSet&                   aPointSet                                   ) const
// {

// }

bool                            Ellipsoid::contains                         (   const   Segment&                    aSegment                                    ) const
{
    return this->contains(aSegment.getFirstPoint()) && this->contains(aSegment.getSecondPoint()) ;
}

Point                           Ellipsoid::getCenter                        ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Ellipsoid") ;
    }
    
    return center_ ;

}

Real                            Ellipsoid::getFirstPrincipalSemiAxis        ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Ellipsoid") ;
    }
    
    return a_ ;

}

Real                            Ellipsoid::getSecondPrincipalSemiAxis       ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Ellipsoid") ;
    }
    
    return b_ ;

}

Real                            Ellipsoid::getThirdPrincipalSemiAxis        ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Ellipsoid") ;
    }
    
    return c_ ;

}

Vector3d                        Ellipsoid::getFirstAxis                     ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Ellipsoid") ;
    }

    return q_.toConjugate() * Vector3d::X() ;

}

Vector3d                        Ellipsoid::getSecondAxis                    ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Ellipsoid") ;
    }

    return q_.toConjugate() * Vector3d::Y() ;

}

Vector3d                        Ellipsoid::getThirdAxis                     ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Ellipsoid") ;
    }

    return q_.toConjugate() * Vector3d::Z() ;

}

Quaternion                      Ellipsoid::getOrientation                   ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Ellipsoid") ;
    }
    
    return q_ ;

}

Matrix3d                        Ellipsoid::getMatrix                        ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Ellipsoid") ;
    }

    const Vector3d firstRatio = this->getFirstAxis() / a_ ;
	const Vector3d secondRatio = this->getSecondAxis() / b_ ;
	const Vector3d thirdRatio = this->getThirdAxis() / c_ ;

    auto tensorProduct = [] (const Vector3d& aFirstVector, const Vector3d& aSecondVector) -> Matrix3d
    {

        Matrix3d tensorProductMatrix ;

        tensorProductMatrix <<  aFirstVector(0) * aSecondVector(0), aFirstVector(0) * aSecondVector(1), aFirstVector(0) * aSecondVector(2),
                                aFirstVector(1) * aSecondVector(0), aFirstVector(1) * aSecondVector(1), aFirstVector(1) * aSecondVector(2),
                                aFirstVector(2) * aSecondVector(0), aFirstVector(2) * aSecondVector(1), aFirstVector(2) * aSecondVector(2) ;

        return tensorProductMatrix ;
        
    } ;

	return tensorProduct(firstRatio, firstRatio) + tensorProduct(secondRatio, secondRatio) + tensorProduct(thirdRatio, thirdRatio) ;

}

Ellipsoid                       Ellipsoid::Undefined                        ( )
{
    return Ellipsoid(Point::Undefined(), Real::Undefined(), Real::Undefined(), Real::Undefined(), Quaternion::Undefined()) ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////