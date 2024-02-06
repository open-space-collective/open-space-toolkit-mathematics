/// Apache License 2.0

#include <Gte/Mathematics/GteIntrEllipsoid3Ellipsoid3.h>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Cone.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Line.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/PointSet.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Pyramid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ray.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Sphere.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationMatrix.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Interval.hpp>
// #include <Gte/Mathematics/GteIntrHalfspace3Ellipsoid3.h>
#include <Gte/Mathematics/GteIntrLine3Ellipsoid3.h>
#include <Gte/Mathematics/GteIntrPlane3Ellipsoid3.h>
#include <Gte/Mathematics/GteIntrRay3Ellipsoid3.h>
#include <Gte/Mathematics/GteIntrSegment3Ellipsoid3.h>

// Disable Eigen warnings

#pragma GCC diagnostic push  // Save diagnostic state

#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wint-in-bool-context"

#include <Eigen/Eigenvalues>

#pragma GCC diagnostic pop  // Turn the warnings back on

#include <math.h>

namespace ostk
{
namespace mathematics
{
namespace geometry
{
namespace d3
{
namespace object
{

gte::Vector3<double> EllipsoidGteVectorFromPoint(const Point& aPoint)
{
    return {aPoint.x(), aPoint.y(), aPoint.z()};
}

gte::Vector3<double> EllipsoidGteVectorFromVector3d(const Vector3d& aVector)
{
    return {aVector.x(), aVector.y(), aVector.z()};
}

Point EllipsoidPointFromGteVector(const gte::Vector3<double>& aVector)
{
    return {aVector[0], aVector[1], aVector[2]};
}

Ellipsoid::Ellipsoid(
    const Point& aCenter,
    const Real& aFirstPrincipalSemiAxis,
    const Real& aSecondPrincipalSemiAxis,
    const Real& aThirdPrincipalSemiAxis,
    const Quaternion& anOrientation
)
    : Object(),
      center_(aCenter),
      a_(aFirstPrincipalSemiAxis),
      b_(aSecondPrincipalSemiAxis),
      c_(aThirdPrincipalSemiAxis),
      q_(anOrientation)
{
    if (a_.isDefined() && (a_ < 0.0))
    {
        throw ostk::core::error::RuntimeError("First principal semi-axis is negative.");
    }

    if (b_.isDefined() && (b_ < 0.0))
    {
        throw ostk::core::error::RuntimeError("Second principal semi-axis is negative.");
    }

    if (c_.isDefined() && (c_ < 0.0))
    {
        throw ostk::core::error::RuntimeError("Third principal semi-axis is negative.");
    }
}

Ellipsoid* Ellipsoid::clone() const
{
    return new Ellipsoid(*this);
}

bool Ellipsoid::operator==(const Ellipsoid& anEllipsoid) const
{
    if ((!this->isDefined()) || (!anEllipsoid.isDefined()))
    {
        return false;
    }

    if (center_ == anEllipsoid.center_)
    {
        if ((a_ == anEllipsoid.a_) && (b_ == anEllipsoid.b_) && (c_ == anEllipsoid.c_) && (q_ == anEllipsoid.q_))
        {
            return true;
        }

        return this->getMatrix().isNear(anEllipsoid.getMatrix(), Real::Epsilon());
    }

    return false;
}

bool Ellipsoid::operator!=(const Ellipsoid& anEllipsoid) const
{
    return !((*this) == anEllipsoid);
}

bool Ellipsoid::isDefined() const
{
    return center_.isDefined() && a_.isDefined() && b_.isDefined() && c_.isDefined() && q_.isDefined();
}

bool Ellipsoid::intersects(const Point& aPoint) const
{
    return this->contains(aPoint);
}

bool Ellipsoid::intersects(const PointSet& aPointSet) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    return (!aPointSet.isEmpty()) && std::any_of(
                                         aPointSet.begin(),
                                         aPointSet.end(),
                                         [this](const Point& aPoint) -> bool
                                         {
                                             return this->contains(aPoint);
                                         }
                                     );
}

bool Ellipsoid::intersects(const Line& aLine) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    if (!aLine.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Line");
    }

    // Line

    const gte::Line3<double> line = {
        EllipsoidGteVectorFromPoint(aLine.getOrigin()), EllipsoidGteVectorFromVector3d(aLine.getDirection())
    };

    // Ellipsoid

    const gte::Vector3<double> center = EllipsoidGteVectorFromPoint(center_);
    const std::array<gte::Vector3<double>, 3> axes = {
        EllipsoidGteVectorFromVector3d(this->getFirstAxis()),
        EllipsoidGteVectorFromVector3d(this->getSecondAxis()),
        EllipsoidGteVectorFromVector3d(this->getThirdAxis())
    };
    const gte::Vector3<double> extent = {a_, b_, c_};

    const gte::Ellipsoid3<double> ellipsoid = {center, axes, extent};

    // Intersection

    gte::TIQuery<double, gte::Line3<double>, gte::Ellipsoid3<double>> intersectionQuery;

    auto intersectionResult = intersectionQuery(line, ellipsoid);

    return intersectionResult.intersect;
}

bool Ellipsoid::intersects(const Ray& aRay) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    if (!aRay.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ray");
    }

    // Ray

    const gte::Ray3<double> ray = {
        EllipsoidGteVectorFromPoint(aRay.getOrigin()), EllipsoidGteVectorFromVector3d(aRay.getDirection())
    };

    // Ellipsoid

    const gte::Vector3<double> center = EllipsoidGteVectorFromPoint(center_);
    const std::array<gte::Vector3<double>, 3> axes = {
        EllipsoidGteVectorFromVector3d(this->getFirstAxis()),
        EllipsoidGteVectorFromVector3d(this->getSecondAxis()),
        EllipsoidGteVectorFromVector3d(this->getThirdAxis())
    };
    const gte::Vector3<double> extent = {a_, b_, c_};

    const gte::Ellipsoid3<double> ellipsoid = {center, axes, extent};

    // Intersection

    gte::TIQuery<double, gte::Ray3<double>, gte::Ellipsoid3<double>> intersectionQuery;

    auto intersectionResult = intersectionQuery(ray, ellipsoid);

    return intersectionResult.intersect;
}

bool Ellipsoid::intersects(const Segment& aSegment) const
{
    using ostk::mathematics::object::Interval;

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    if (!aSegment.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Segment");
    }

    // // Does not work for some reason... most likely a bug w/ gte::TIQuery<double, gte::Segment3<double>,
    // gte::Ellipsoid3<double>>

    // // Segment

    // const gte::Segment3<double> segment = { EllipsoidGteVectorFromVector3d(aSegment.getFirstPoint()),
    // EllipsoidGteVectorFromVector3d(aSegment.getSecondPoint()) } ;

    // // Ellipsoid

    // const gte::Vector3<double> center = EllipsoidGteVectorFromVector3d(center_) ;
    // const std::array<gte::Vector3<double>, 3> axes = { EllipsoidGteVectorFromVector3d(this->getFirstAxis()),
    // EllipsoidGteVectorFromVector3d(this->getSecondAxis()), EllipsoidGteVectorFromVector3d(this->getThirdAxis()) } ;
    // const gte::Vector3<double> extent = { a_, b_, c_ } ;

    // const gte::Ellipsoid3<double> ellipsoid = { center, axes, extent } ;

    // // Intersection

    // gte::TIQuery<double, gte::Segment3<double>, gte::Ellipsoid3<double>> intersectionQuery ;

    // auto intersectionResult = intersectionQuery(segment, ellipsoid) ;

    // return intersectionResult.intersect ;

    if (aSegment.isDegenerate())
    {
        return this->contains(aSegment.getFirstPoint());
    }

    // https://www.geometrictools.com/GTEngine/Include/Mathematics/GteIntrSegment3Ellipsoid3.h

    const Vector3d segmentDirection = aSegment.getDirection();
    const Vector3d segmentCenter = aSegment.getCenter().asVector();
    const Real segmentHalfLength = aSegment.getLength() / 2.0;

    const Matrix3d M = this->getMatrix();

    const Vector3d diff = segmentCenter - center_.asVector();
    const Vector3d matDir = M * segmentDirection;
    const Vector3d matDiff = M * diff;

    const Real a2 = segmentDirection.dot(matDir);
    const Real a1 = segmentDirection.dot(matDiff);
    const Real a0 = diff.dot(matDiff) - 1.0;

    const Real discriminant = (a1 * a1) - (a0 * a2);

    static const Real tolerance = 1e-25;  // [TBM] Tolerance parameter should be dynamic

    if (discriminant < -tolerance)  // No real roots
    {
        return false;
    }
    else if (discriminant > tolerance)  // Two real roots
    {
        const Real discriminantRoot = std::sqrt(discriminant);
        const Real a2_inverse = 1.0 / a2;

        const Real t0 = (-a1 - discriminantRoot) * a2_inverse;
        const Real t1 = (-a1 + discriminantRoot) * a2_inverse;

        const Interval<Real> resultInterval = Interval<Real>::Open(t0, t1);
        const Interval<Real> segmentInterval = Interval<Real>::Closed(-segmentHalfLength, +segmentHalfLength);

        if (!resultInterval.contains(segmentInterval))
        {
            if (resultInterval.intersects(segmentInterval))
            {
                return true;
            }
            else  // No intersection
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else  // One real root
    {
        const Real t0 = -a1 / a2;

        if (std::abs(t0) <= segmentHalfLength)  // Single intersection
        {
            return true;
        }
        else  // No intersection
        {
            return false;
        }
    }

    return false;
}

bool Ellipsoid::intersects(const Plane& aPlane) const
{
    // https://file.scirp.org/pdf/AM20121100009_89014420.pdf
    // https://www.researchgate.net/publication/312384498_Intersection_of_an_Ellipsoid_and_a_Plane

    if (!aPlane.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Plane");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    // Plane

    const gte::Vector3<double> normal = EllipsoidGteVectorFromVector3d(aPlane.getNormalVector());
    const gte::Vector3<double> point = EllipsoidGteVectorFromPoint(aPlane.getPoint());

    const gte::Plane3<double> plane = {normal, point};

    // Ellipsoid

    const gte::Vector3<double> center = EllipsoidGteVectorFromPoint(center_);
    const std::array<gte::Vector3<double>, 3> axes = {
        EllipsoidGteVectorFromVector3d(this->getFirstAxis()),
        EllipsoidGteVectorFromVector3d(this->getSecondAxis()),
        EllipsoidGteVectorFromVector3d(this->getThirdAxis())
    };
    const gte::Vector3<double> extent = {a_, b_, c_};

    const gte::Ellipsoid3<double> ellipsoid = {center, axes, extent};

    // Intersection

    gte::TIQuery<double, gte::Plane3<double>, gte::Ellipsoid3<double>> intersectionQuery;

    auto intersectionResult = intersectionQuery(plane, ellipsoid);

    return intersectionResult.intersect;
}

// bool                            Ellipsoid::intersects                       (   const   Sphere& aSphere ) const
// {

//     if (!aSphere.isDefined())
//     {
//         throw ostk::core::error::runtime::Undefined("Sphere") ;
//     }

//     if (!this->isDefined())
//     {
//         throw ostk::core::error::runtime::Undefined("Ellipsoid") ;
//     }

//     return this->intersects(Ellipsoid(aSphere.getCenter(), aSphere.getRadius(), aSphere.getRadius(),
//     aSphere.getRadius())) ;

// }

// bool                            Ellipsoid::intersects                       (   const   Ellipsoid& anEllipsoid )
// const
// {

//     if (!anEllipsoid.isDefined())
//     {
//         throw ostk::core::error::runtime::Undefined("Ellipsoid") ;
//     }

//     if (!this->isDefined())
//     {
//         throw ostk::core::error::runtime::Undefined("Ellipsoid") ;
//     }

//     // Ellipsoid

//     const gte::Vector3<double> center = EllipsoidGteVectorFromPoint(center_) ;
//     const std::array<gte::Vector3<double>, 3> axes = { EllipsoidGteVectorFromVector3d(this->getFirstAxis()),
//     EllipsoidGteVectorFromVector3d(this->getSecondAxis()), EllipsoidGteVectorFromVector3d(this->getThirdAxis()) } ;
//     const gte::Vector3<double> extent = { a_, b_, c_ } ;

//     const gte::Ellipsoid3<double> ellipsoid = { center, axes, extent } ;

//     // Another ellipsoid

//     const gte::Vector3<double> anotherCenter = EllipsoidGteVectorFromPoint(anEllipsoid.center_) ;
//     const std::array<gte::Vector3<double>, 3> anotherAxes = {
//     EllipsoidGteVectorFromVector3d(anEllipsoid.getFirstAxis()),
//     EllipsoidGteVectorFromVector3d(anEllipsoid.getSecondAxis()),
//     EllipsoidGteVectorFromVector3d(anEllipsoid.getThirdAxis()) } ; const gte::Vector3<double> anotherExtent = {
//     anEllipsoid.a_, anEllipsoid.b_, anEllipsoid.c_ } ;

//     const gte::Ellipsoid3<double> anotherEllipsoid = { anotherCenter, anotherAxes, anotherExtent } ;

//     // Intersection

//     gte::TIQuery<double, gte::Ellipsoid3<double>, gte::Ellipsoid3<double>> intersectionQuery ;

//     auto intersectionResult = intersectionQuery(ellipsoid, anotherEllipsoid) ;

//     return intersectionResult.intersect ;

// }

bool Ellipsoid::intersects(const Pyramid& aPyramid) const
{
    return aPyramid.intersects(*this);
}

bool Ellipsoid::intersects(const Cone& aCone) const
{
    return aCone.intersects(*this);
}

bool Ellipsoid::contains(const Point& aPoint) const
{
    using ostk::mathematics::object::Vector3d;

    if (!aPoint.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Point");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    Matrix3d dcm;

    dcm.row(0) = q_ * Vector3d::X();
    dcm.row(1) = q_ * Vector3d::Y();
    dcm.row(2) = q_ * Vector3d::Z();

    const Vector3d point = dcm * (aPoint - center_);

    const Real& x = point.x();
    const Real& y = point.y();
    const Real& z = point.z();

    return std::abs((x * x) / (a_ * a_) + (y * y) / (b_ * b_) + (z * z) / (c_ * c_) - 1.0) < Real::Epsilon();
}

bool Ellipsoid::contains(const PointSet& aPointSet) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    return (!aPointSet.isEmpty()) && std::all_of(
                                         aPointSet.begin(),
                                         aPointSet.end(),
                                         [this](const Point& aPoint) -> bool
                                         {
                                             return this->contains(aPoint);
                                         }
                                     );
}

bool Ellipsoid::contains(const Segment& aSegment) const
{
    return this->contains(aSegment.getFirstPoint()) && this->contains(aSegment.getSecondPoint());
}

Point Ellipsoid::getCenter() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    return center_;
}

Real Ellipsoid::getFirstPrincipalSemiAxis() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    return a_;
}

Real Ellipsoid::getSecondPrincipalSemiAxis() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    return b_;
}

Real Ellipsoid::getThirdPrincipalSemiAxis() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    return c_;
}

Vector3d Ellipsoid::getFirstAxis() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    return q_.toConjugate() * Vector3d::X();
}

Vector3d Ellipsoid::getSecondAxis() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    return q_.toConjugate() * Vector3d::Y();
}

Vector3d Ellipsoid::getThirdAxis() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    return q_.toConjugate() * Vector3d::Z();
}

Quaternion Ellipsoid::getOrientation() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    return q_;
}

Matrix3d Ellipsoid::getMatrix() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    const Vector3d firstRatio = this->getFirstAxis() / a_;
    const Vector3d secondRatio = this->getSecondAxis() / b_;
    const Vector3d thirdRatio = this->getThirdAxis() / c_;

    auto tensorProduct = [](const Vector3d& aFirstVector, const Vector3d& aSecondVector) -> Matrix3d
    {
        Matrix3d tensorProductMatrix;

        tensorProductMatrix << aFirstVector(0) * aSecondVector(0), aFirstVector(0) * aSecondVector(1),
            aFirstVector(0) * aSecondVector(2), aFirstVector(1) * aSecondVector(0), aFirstVector(1) * aSecondVector(1),
            aFirstVector(1) * aSecondVector(2), aFirstVector(2) * aSecondVector(0), aFirstVector(2) * aSecondVector(1),
            aFirstVector(2) * aSecondVector(2);

        return tensorProductMatrix;
    };

    return tensorProduct(firstRatio, firstRatio) + tensorProduct(secondRatio, secondRatio) +
           tensorProduct(thirdRatio, thirdRatio);
}

Intersection Ellipsoid::intersectionWith(const Line& aLine) const
{
    using ostk::mathematics::geometry::d3::object::PointSet;

    if (!aLine.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Line");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    // Line

    const gte::Line3<double> segment = {
        EllipsoidGteVectorFromPoint(aLine.getOrigin()), EllipsoidGteVectorFromVector3d(aLine.getDirection())
    };

    // Ellipsoid

    const gte::Vector3<double> center = EllipsoidGteVectorFromPoint(center_);
    const std::array<gte::Vector3<double>, 3> axes = {
        EllipsoidGteVectorFromVector3d(this->getFirstAxis()),
        EllipsoidGteVectorFromVector3d(this->getSecondAxis()),
        EllipsoidGteVectorFromVector3d(this->getThirdAxis())
    };
    const gte::Vector3<double> extent = {a_, b_, c_};

    const gte::Ellipsoid3<double> ellipsoid = {center, axes, extent};

    // Intersection

    gte::FIQuery<double, gte::Line3<double>, gte::Ellipsoid3<double>> intersectionQuery;

    auto intersectionResult = intersectionQuery(segment, ellipsoid);

    if (intersectionResult.intersect)
    {
        if (intersectionResult.numIntersections == 1)
        {
            return Intersection::Point(EllipsoidPointFromGteVector(intersectionResult.point[0]));
        }
        else if (intersectionResult.numIntersections == 2)
        {
            return Intersection::PointSet(PointSet(
                {Point(EllipsoidPointFromGteVector(intersectionResult.point[0])),
                 Point(EllipsoidPointFromGteVector(intersectionResult.point[1]))}
            ));
        }
        else
        {
            throw ostk::core::error::RuntimeError("Intersection algorithm has failed.");
        }
    }

    return Intersection::Empty();
}

Intersection Ellipsoid::intersectionWith(const Ray& aRay, const bool onlyInSight) const
{
    using ostk::mathematics::geometry::d3::object::PointSet;

    if (!aRay.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ray");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    // Ray

    const gte::Ray3<double> ray = {
        EllipsoidGteVectorFromPoint(aRay.getOrigin()), EllipsoidGteVectorFromVector3d(aRay.getDirection())
    };

    // Ellipsoid

    const gte::Vector3<double> center = EllipsoidGteVectorFromPoint(center_);
    const std::array<gte::Vector3<double>, 3> axes = {
        EllipsoidGteVectorFromVector3d(this->getFirstAxis()),
        EllipsoidGteVectorFromVector3d(this->getSecondAxis()),
        EllipsoidGteVectorFromVector3d(this->getThirdAxis())
    };
    const gte::Vector3<double> extent = {a_, b_, c_};

    const gte::Ellipsoid3<double> ellipsoid = {center, axes, extent};

    // Intersection

    gte::FIQuery<double, gte::Ray3<double>, gte::Ellipsoid3<double>> intersectionQuery;

    auto intersectionResult = intersectionQuery(ray, ellipsoid);

    if (intersectionResult.intersect)
    {
        if (intersectionResult.numIntersections == 1)
        {
            const Point point = EllipsoidPointFromGteVector(intersectionResult.point[0]);

            if ((point == aRay.getOrigin()) && (!this->contains(point)))  // Discard ray origin, if returned by Gte
            {
                return Intersection::Empty();
            }

            return Intersection::Point(point);
        }
        else if (intersectionResult.numIntersections == 2)
        {
            const Point firstPoint = EllipsoidPointFromGteVector(intersectionResult.point[0]);
            const Point secondPoint = EllipsoidPointFromGteVector(intersectionResult.point[1]);

            if ((firstPoint == aRay.getOrigin()) || (secondPoint == aRay.getOrigin()))
            {
                if ((firstPoint == aRay.getOrigin()) &&
                    (!this->contains(firstPoint)))  // Discard ray origin, if returned by Gte
                {
                    return Intersection::Point(secondPoint);
                }

                if ((secondPoint == aRay.getOrigin()) &&
                    (!this->contains(secondPoint)))  // Discard ray origin, if returned by Gte
                {
                    return Intersection::Point(firstPoint);
                }
            }

            if ((firstPoint - secondPoint).norm() < Real::Epsilon())
            {
                return Intersection::Point(firstPoint);
            }

            const PointSet pointSet = {{firstPoint, secondPoint}};

            return onlyInSight ? Intersection::Point(pointSet.getPointClosestTo(aRay.getOrigin()))
                               : Intersection::PointSet(pointSet);
        }
        else
        {
            throw ostk::core::error::RuntimeError("Intersection algorithm has failed.");
        }
    }

    return Intersection::Empty();
}

Intersection Ellipsoid::intersectionWith(const Segment& aSegment) const
{
    using ostk::mathematics::geometry::d3::object::PointSet;

    if (!aSegment.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Segment");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    if (aSegment.isDegenerate() && this->contains(aSegment.getFirstPoint()))
    {
        return Intersection::Point(aSegment.getFirstPoint());
    }

    // Segment

    const gte::Segment3<double> segment = {
        EllipsoidGteVectorFromPoint(aSegment.getFirstPoint()), EllipsoidGteVectorFromPoint(aSegment.getSecondPoint())
    };
    ;

    // Ellipsoid

    const gte::Vector3<double> center = EllipsoidGteVectorFromPoint(center_);
    const std::array<gte::Vector3<double>, 3> axes = {
        EllipsoidGteVectorFromVector3d(this->getFirstAxis()),
        EllipsoidGteVectorFromVector3d(this->getSecondAxis()),
        EllipsoidGteVectorFromVector3d(this->getThirdAxis())
    };
    const gte::Vector3<double> extent = {a_, b_, c_};

    const gte::Ellipsoid3<double> ellipsoid = {center, axes, extent};

    // Intersection

    gte::FIQuery<double, gte::Segment3<double>, gte::Ellipsoid3<double>> intersectionQuery;

    auto intersectionResult = intersectionQuery(segment, ellipsoid);

    if (intersectionResult.intersect)
    {
        if (intersectionResult.numIntersections == 1)
        {
            const Point point = EllipsoidPointFromGteVector(intersectionResult.point[0]);

            if (isnan(point.x()) || isnan(point.y()) || isnan(point.z()))
            {
                return Intersection::Empty();
            }

            if ((!point.isDefined()) || ((point == aSegment.getFirstPoint() || (point == aSegment.getSecondPoint())) &&
                                         (!this->contains(point))))  // Discard segment points, if returned by Gte
            {
                return Intersection::Empty();
            }

            return Intersection::Point(point);
        }
        else if (intersectionResult.numIntersections == 2)
        {
            const Point firstPoint = EllipsoidPointFromGteVector(intersectionResult.point[0]);
            const Point secondPoint = EllipsoidPointFromGteVector(intersectionResult.point[1]);

            if ((firstPoint == aSegment.getFirstPoint()) || (secondPoint == aSegment.getFirstPoint()) ||
                (firstPoint == aSegment.getSecondPoint()) ||
                (secondPoint == aSegment.getSecondPoint()))  // Discard segment points, if returned by Gte
            {
                if ((firstPoint == aSegment.getFirstPoint()) && (!this->contains(firstPoint)))
                {
                    if ((secondPoint == aSegment.getSecondPoint()) && (!this->contains(secondPoint)))
                    {
                        return Intersection::Empty();
                    }

                    return Intersection::Point(secondPoint);
                }

                if ((firstPoint == aSegment.getSecondPoint()) && (!this->contains(firstPoint)))
                {
                    if ((secondPoint == aSegment.getFirstPoint()) && (!this->contains(secondPoint)))
                    {
                        return Intersection::Empty();
                    }

                    return Intersection::Point(secondPoint);
                }

                if ((secondPoint == aSegment.getFirstPoint()) && (!this->contains(secondPoint)))
                {
                    if ((firstPoint == aSegment.getSecondPoint()) && (!this->contains(firstPoint)))
                    {
                        return Intersection::Empty();
                    }

                    return Intersection::Point(firstPoint);
                }

                if ((secondPoint == aSegment.getSecondPoint()) && (!this->contains(secondPoint)))
                {
                    if ((firstPoint == aSegment.getFirstPoint()) && (!this->contains(firstPoint)))
                    {
                        return Intersection::Empty();
                    }

                    return Intersection::Point(firstPoint);
                }
            }

            return Intersection::PointSet(PointSet({firstPoint, secondPoint}));
        }
        else
        {
            throw ostk::core::error::RuntimeError("Intersection algorithm has failed.");
        }
    }

    return Intersection::Empty();
}

Intersection Ellipsoid::intersectionWith(const Pyramid& aPyramid, const bool onlyInSight) const
{
    return aPyramid.intersectionWith(*this, onlyInSight);
}

Intersection Ellipsoid::intersectionWith(const Cone& aCone, const bool onlyInSight) const
{
    return aCone.intersectionWith(*this, onlyInSight);
}

void Ellipsoid::print(std::ostream& anOutputStream, bool displayDecorators) const
{
    displayDecorators ? ostk::core::utils::Print::Header(anOutputStream, "Ellipsoid") : void();

    ostk::core::utils::Print::Line(anOutputStream)
        << "Center:" << (center_.isDefined() ? center_.toString() : "Undefined");

    ostk::core::utils::Print::Line(anOutputStream)
        << "First principal semi-axis:" << (a_.isDefined() ? a_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Second principal semi-axis:" << (b_.isDefined() ? b_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Third principal semi-axis:" << (c_.isDefined() ? c_.toString() : "Undefined");

    ostk::core::utils::Print::Line(anOutputStream)
        << "First axis:" << (q_.isDefined() ? this->getFirstAxis().toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Second axis:" << (q_.isDefined() ? this->getSecondAxis().toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Third axis:" << (q_.isDefined() ? this->getThirdAxis().toString() : "Undefined");

    ostk::core::utils::Print::Line(anOutputStream) << "Orientation:" << (q_.isDefined() ? q_.toString() : "Undefined");

    displayDecorators ? ostk::core::utils::Print::Footer(anOutputStream) : void();
}

void Ellipsoid::applyTransformation(const Transformation& aTransformation)
{
    using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix;

    if (!aTransformation.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Transformation");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ellipsoid");
    }

    if (aTransformation.isIdentity())
    {
        return;
    }

    center_.applyTransformation(aTransformation);

    const Matrix3d rotationMatrix = aTransformation.getMatrix().block<3, 3>(0, 0).inverse();
    const Matrix3d transformedMatrix = rotationMatrix.transpose() * this->getMatrix() * rotationMatrix;

    Eigen::SelfAdjointEigenSolver<Matrix3d> eigenSolver(transformedMatrix);

    if (eigenSolver.info() != Eigen::Success)
    {
        throw ostk::core::error::RuntimeError("Eigen vector calculation has failed.");
    }

    a_ = std::sqrt(1.0 / eigenSolver.eigenvalues()(0));
    b_ = std::sqrt(1.0 / eigenSolver.eigenvalues()(1));
    c_ = std::sqrt(1.0 / eigenSolver.eigenvalues()(2));

    const Vector3d firstAxis = eigenSolver.eigenvectors().col(0);
    const Vector3d secondAxis = eigenSolver.eigenvectors().col(1);
    const Vector3d thirdAxis = firstAxis.cross(secondAxis);

    q_ = Quaternion::RotationMatrix(RotationMatrix::Columns(firstAxis, secondAxis, thirdAxis)).conjugate();
}

Ellipsoid Ellipsoid::Undefined()
{
    return {Point::Undefined(), Real::Undefined(), Real::Undefined(), Real::Undefined(), Quaternion::Undefined()};
}

}  // namespace object
}  // namespace d3
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk
