////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Objects/Cuboid.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>
#include <Library/Mathematics/Geometry/3D/Transformation.hpp>
#include <Library/Mathematics/Geometry/3D/Intersection.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Pyramid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Cuboid.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Sphere.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Ray.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/Line.hpp>
#include <Library/Mathematics/Geometry/3D/Objects/PointSet.hpp>
#include <Library/Mathematics/Objects/Interval.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <Gte/Mathematics/GteIntrOrientedBox3Cone3.h>
#include <Gte/Mathematics/GteIntrOrientedBox3Frustum3.h>
// #include <Gte/Mathematics/GteIntrOrientedBox3Cylinder3.h>
#include <Gte/Mathematics/GteIntrOrientedBox3Sphere3.h>
#include <Gte/Mathematics/GteIntrOrientedBox3OrientedBox3.h>
#include <Gte/Mathematics/GteIntrPlane3OrientedBox3.h>
#include <Gte/Mathematics/GteIntrRay3OrientedBox3.h>
#include <Gte/Mathematics/GteIntrSegment3OrientedBox3.h>
#include <Gte/Mathematics/GteIntrLine3OrientedBox3.h>

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

gte::Vector3<double>            CuboidGteVectorFromPoint                    (   const   Point&                      aPoint                                      )
{
    return { aPoint.x(), aPoint.y(), aPoint.z() } ;
}

gte::Vector3<double>            CuboidGteVectorFromVector3d                 (   const   Vector3d&                   aVector                                     )
{
    return { aVector.x(), aVector.y(), aVector.z() } ;
}

Point                           CuboidPointFromGteVector                    (   const   gte::Vector3<double>&       aVector                                     )
{
    return { aVector[0], aVector[1], aVector[2] } ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Cuboid::Cuboid                              (   const   Point&                      aCenter,
                                                                                const   std::array<Vector3d, 3>&    aAxisArray,
                                                                                const   std::array<Real, 3>&        anExtent                                    )
                                :   Object(),
                                    center_(aCenter),
                                    axes_(aAxisArray),
                                    extent_(anExtent)
{

}

Cuboid*                         Cuboid::clone                               ( ) const
{
    return new Cuboid(*this) ;
}

bool                            Cuboid::operator ==                         (   const   Cuboid&                     aCuboid                                     ) const
{

    if ((!this->isDefined()) || (!aCuboid.isDefined()))
    {
        return false ;
    }

    if (center_ == aCuboid.center_)
    {

        if (((axes_[0] == aCuboid.axes_[0]) || (axes_[0] == -aCuboid.axes_[0])) && (extent_[0] == aCuboid.extent_[0]))
        {

            if (((axes_[1] == aCuboid.axes_[1]) || (axes_[1] == -aCuboid.axes_[1])) && (extent_[1] == aCuboid.extent_[1]))
            {

                if (((axes_[2] == aCuboid.axes_[2]) || (axes_[2] == -aCuboid.axes_[2])) && (extent_[2] == aCuboid.extent_[2]))
                {
                    return true ; // (0 == 0) && (1 == 1) && (2 == 2)
                }

            }
            else if (((axes_[1] == aCuboid.axes_[2]) || (axes_[1] == -aCuboid.axes_[2])) && (extent_[1] == aCuboid.extent_[2]))
            {

                if (((axes_[2] == aCuboid.axes_[1]) || (axes_[2] == -aCuboid.axes_[1])) && (extent_[2] == aCuboid.extent_[1]))
                {
                    return true ; // (0 == 0) && (1 == 2) && (2 == 1)
                }

            }
            
        }
        else if (((axes_[0] == aCuboid.axes_[1]) || (axes_[0] == -aCuboid.axes_[1])) && (extent_[0] == aCuboid.extent_[1]))
        {

            if (((axes_[1] == aCuboid.axes_[0]) || (axes_[1] == -aCuboid.axes_[0])) && (extent_[1] == aCuboid.extent_[0]))
            {

                if (((axes_[2] == aCuboid.axes_[2]) || (axes_[2] == -aCuboid.axes_[2])) && (extent_[2] == aCuboid.extent_[2]))
                {
                    return true ; // (0 == 1) && (1 == 0) && (2 == 2)
                }

            }
            else if (((axes_[1] == aCuboid.axes_[2]) || (axes_[1] == -aCuboid.axes_[2])) && (extent_[1] == aCuboid.extent_[2]))
            {

                if (((axes_[2] == aCuboid.axes_[0]) || (axes_[2] == -aCuboid.axes_[0])) && (extent_[2] == aCuboid.extent_[0]))
                {
                    return true ; // (0 == 1) && (1 == 2) && (2 == 0)
                }

            }
            
        }
        else if (((axes_[0] == aCuboid.axes_[2]) || (axes_[0] == -aCuboid.axes_[2])) && (extent_[0] == aCuboid.extent_[2]))
        {

            if (((axes_[1] == aCuboid.axes_[0]) || (axes_[1] == -aCuboid.axes_[0])) && (extent_[1] == aCuboid.extent_[0]))
            {

                if (((axes_[2] == aCuboid.axes_[1]) || (axes_[2] == -aCuboid.axes_[1])) && (extent_[2] == aCuboid.extent_[1]))
                {
                    return true ; // (0 == 2) && (1 == 0) && (2 == 1)
                }

            }
            else if (((axes_[1] == aCuboid.axes_[1]) || (axes_[1] == -aCuboid.axes_[1])) && (extent_[1] == aCuboid.extent_[1]))
            {

                if (((axes_[2] == aCuboid.axes_[0]) || (axes_[2] == -aCuboid.axes_[0])) && (extent_[2] == aCuboid.extent_[0]))
                {
                    return true ; // (0 == 2) && (1 == 1) && (2 == 0)
                }

            }
            
        }

    }

    return false ;

}

bool                            Cuboid::operator !=                         (   const   Cuboid&                     aCuboid                                     ) const
{
    return !((*this) == aCuboid) ;
}

bool                            Cuboid::isDefined                           ( ) const
{

    return center_.isDefined()
        && axes_[0].isDefined() && axes_[1].isDefined() && axes_[2].isDefined()
        && extent_[0].isDefined() && extent_[1].isDefined() && extent_[2].isDefined() ;

}

bool                            Cuboid::isNear                              (   const   Cuboid&                     aCuboid,
                                                                                const   Real&                       aTolerance                                  ) const
{

    if (!aCuboid.isDefined())
    {
        throw library::core::error::runtime::Undefined("Cuboid") ;
    }

    if (!aTolerance.isDefined())
    {
        throw library::core::error::runtime::Undefined("Tolerance") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Cuboid") ;
    }

    return PointSet(this->getVertices()).isNear(PointSet(aCuboid.getVertices()), aTolerance) ;

}

bool                            Cuboid::intersects                          (   const   Point&                      aPoint                                      ) const
{
    return this->contains(aPoint) ;
}

bool                            Cuboid::intersects                          (   const   PointSet&                   aPointSet                                   ) const
{
    
    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Cuboid") ;
    }
    
    return (!aPointSet.isEmpty()) && std::any_of(aPointSet.begin(), aPointSet.end(), [this] (const Point& aPoint) -> bool { return this->contains(aPoint) ; }) ;

}

bool                            Cuboid::intersects                          (   const   Line&                       aLine                                       ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Cuboid") ;
    }

    if (!aLine.isDefined())
    {
        throw library::core::error::runtime::Undefined("Line") ;
    }

    // Line

    const gte::Line3<double> line = { CuboidGteVectorFromPoint(aLine.getOrigin()), CuboidGteVectorFromVector3d(aLine.getDirection()) } ;

    // Cuboid

    const gte::Vector3<double> center = CuboidGteVectorFromPoint(center_) ;
    const std::array<gte::Vector3<double>, 3> axis = { CuboidGteVectorFromVector3d(axes_[0]), CuboidGteVectorFromVector3d(axes_[1]), CuboidGteVectorFromVector3d(axes_[2]) } ;
    const gte::Vector3<double> extent = { extent_[0], extent_[1], extent_[2] } ;

    const gte::OrientedBox3<double> cuboid = { center, axis, extent } ;

    // Intersection

    gte::TIQuery<double, gte::Line3<double>, gte::OrientedBox3<double>> intersectionQuery ;

    auto intersectionResult = intersectionQuery(line, cuboid) ;

    return intersectionResult.intersect ;

}

bool                            Cuboid::intersects                          (   const   Cuboid&                     aCuboid                                     ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Cuboid") ;
    }

    if (!aCuboid.isDefined())
    {
        throw library::core::error::runtime::Undefined("Cuboid") ;
    }

    // First cuboid

    const gte::Vector3<double> firstCenter = CuboidGteVectorFromPoint(center_) ;
    const std::array<gte::Vector3<double>, 3> firstAxis = { CuboidGteVectorFromVector3d(axes_[0]), CuboidGteVectorFromVector3d(axes_[1]), CuboidGteVectorFromVector3d(axes_[2]) } ;
    const gte::Vector3<double> firstExtent = { extent_[0], extent_[1], extent_[2] } ;

    const gte::OrientedBox3<double> firstCuboid = { firstCenter, firstAxis, firstExtent } ;

    // Second cuboid

    const gte::Vector3<double> secondCenter = CuboidGteVectorFromPoint(aCuboid.center_) ;
    const std::array<gte::Vector3<double>, 3> secondAxis = { CuboidGteVectorFromVector3d(aCuboid.axes_[0]), CuboidGteVectorFromVector3d(aCuboid.axes_[1]), CuboidGteVectorFromVector3d(aCuboid.axes_[2]) } ;
    const gte::Vector3<double> secondExtent = { aCuboid.extent_[0], aCuboid.extent_[1], aCuboid.extent_[2] } ;

    const gte::OrientedBox3<double> secondCuboid = { secondCenter, secondAxis, secondExtent } ;

    // Intersection

    gte::TIQuery<double, gte::OrientedBox3<double>, gte::OrientedBox3<double>> intersectionQuery ;

    auto intersectionResult = intersectionQuery(firstCuboid, secondCuboid) ;

    return intersectionResult.intersect ;

}

bool                            Cuboid::contains                            (   const   Point&                      aPoint                                      ) const
{

    if (!aPoint.isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Cuboid") ;
    }

    const Vector3d dx = aPoint - center_ ;

    const Real a = std::abs(dx.dot(axes_[0])) ;
    const Real b = std::abs(dx.dot(axes_[1])) ;
    const Real c = std::abs(dx.dot(axes_[2])) ;

    if (std::abs(a - extent_[0]) < Real::Epsilon())
    {
        return (b <= extent_[1]) && (c <= extent_[2]) ;
    }

    if (std::abs(b - extent_[1]) < Real::Epsilon())
    {
        return (a <= extent_[0]) && (c <= extent_[2]) ;
    }

    if (std::abs(c - extent_[2]) < Real::Epsilon())
    {
        return (a <= extent_[0]) && (b <= extent_[1]) ;
    }

    return false ;

}

bool                            Cuboid::contains                            (   const   PointSet&                   aPointSet                                   ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Cuboid") ;
    }
    
    return (!aPointSet.isEmpty()) && std::all_of(aPointSet.begin(), aPointSet.end(), [this] (const Point& aPoint) -> bool { return this->contains(aPoint) ; }) ;

}

bool                            Cuboid::contains                            (   const   Segment&                    aSegment                                    ) const
{
    return this->contains(aSegment.getFirstPoint()) && this->contains(aSegment.getSecondPoint()) ;
}

Point                           Cuboid::getCenter                           ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Cuboid") ;
    }
    
    return center_ ;

}

Vector3d                        Cuboid::getFirstAxis                        ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Cuboid") ;
    }

    return axes_[0] ;

}

Vector3d                        Cuboid::getSecondAxis                       ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Cuboid") ;
    }

    return axes_[1] ;

}

Vector3d                        Cuboid::getThirdAxis                        ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Cuboid") ;
    }

    return axes_[2] ;

}

Real                            Cuboid::getFirstExtent                      ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Cuboid") ;
    }

    return extent_[0] ;

}

Real                            Cuboid::getSecondExtent                     ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Cuboid") ;
    }

    return extent_[1] ;

}

Real                            Cuboid::getThirdExtent                      ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Cuboid") ;
    }

    return extent_[2] ;

}

Array<Cuboid::Vertex>           Cuboid::getVertices                         ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Cuboid") ;
    }

    Array<Cuboid::Vertex> vertices = Array<Cuboid::Vertex>::Empty() ;

    vertices.reserve(8) ;

    const Real halfFirstExtent = extent_[0] / 2.0 ;
    const Real halfSecondExtent = extent_[1] / 2.0 ;
    const Real halfThirdExtent = extent_[2] / 2.0 ;

    vertices.add(center_ + (halfFirstExtent * axes_[0]) + (halfSecondExtent * axes_[1]) + (halfThirdExtent * axes_[2])) ;
    vertices.add(center_ + (halfFirstExtent * axes_[0]) + (halfSecondExtent * axes_[1]) - (halfThirdExtent * axes_[2])) ;
    vertices.add(center_ + (halfFirstExtent * axes_[0]) - (halfSecondExtent * axes_[1]) - (halfThirdExtent * axes_[2])) ;
    vertices.add(center_ + (halfFirstExtent * axes_[0]) - (halfSecondExtent * axes_[1]) + (halfThirdExtent * axes_[2])) ;
    vertices.add(center_ - (halfFirstExtent * axes_[0]) + (halfSecondExtent * axes_[1]) + (halfThirdExtent * axes_[2])) ;
    vertices.add(center_ - (halfFirstExtent * axes_[0]) + (halfSecondExtent * axes_[1]) - (halfThirdExtent * axes_[2])) ;
    vertices.add(center_ - (halfFirstExtent * axes_[0]) - (halfSecondExtent * axes_[1]) - (halfThirdExtent * axes_[2])) ;
    vertices.add(center_ - (halfFirstExtent * axes_[0]) - (halfSecondExtent * axes_[1]) + (halfThirdExtent * axes_[2])) ;

    return vertices ;

}

void                            Cuboid::print                               (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           ) const
{

    displayDecorators ? library::core::utils::Print::Header(anOutputStream, "Cuboid") : void () ;

    library::core::utils::Print::Line(anOutputStream) << "Center:"              << (center_.isDefined() ? center_.toString() : "Undefined") ;

    library::core::utils::Print::Line(anOutputStream) << "First axis:"          << (axes_[0].isDefined() ? axes_[0].toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Second axis:"         << (axes_[1].isDefined() ? axes_[1].toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Third axis:"          << (axes_[2].isDefined() ? axes_[2].toString() : "Undefined") ;

    library::core::utils::Print::Line(anOutputStream) << "First extent:"        << (extent_[0].isDefined() ? extent_[0].toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Second extent:"       << (extent_[1].isDefined() ? extent_[1].toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Third extent:"        << (extent_[2].isDefined() ? extent_[2].toString() : "Undefined") ;

    displayDecorators ? library::core::utils::Print::Footer(anOutputStream) : void () ;

}

void                            Cuboid::applyTransformation                 (   const   Transformation&             aTransformation                             )
{

    using library::math::geom::d3::trf::rot::RotationMatrix ;

    if (!aTransformation.isDefined())
    {
        throw library::core::error::runtime::Undefined("Transformation") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Cuboid") ;
    }

    if (aTransformation.isIdentity())
    {
        return ;
    }

    center_.applyTransformation(aTransformation) ;

    axes_[0] = aTransformation.applyTo(axes_[0]) ;
    axes_[1] = aTransformation.applyTo(axes_[1]) ;
    axes_[2] = aTransformation.applyTo(axes_[2]) ;

    extent_[0] *= axes_[0].norm() ;
    extent_[1] *= axes_[1].norm() ;
    extent_[2] *= axes_[2].norm() ;

    axes_[0].normalize() ;
    axes_[1].normalize() ;
    axes_[2].normalize() ;

}

Cuboid                          Cuboid::Undefined                           ( )
{
    return { Point::Undefined(), { Vector3d::Undefined(), Vector3d::Undefined(), Vector3d::Undefined() }, { Real::Undefined(), Real::Undefined(), Real::Undefined() } } ;
}

Cuboid                          Cuboid::Cube                                (   const   Point&                      aCenter,
                                                                                const   Real&                       anExtent                                    )
{

    if (!aCenter.isDefined())
    {
        throw library::core::error::runtime::Undefined("Center") ;
    }

    if (!anExtent.isDefined())
    {
        throw library::core::error::runtime::Undefined("Extent") ;
    }

    return { aCenter, { Vector3d::X(), Vector3d::Y(), Vector3d::Z() }, { anExtent, anExtent, anExtent } } ;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////