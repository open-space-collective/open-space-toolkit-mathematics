// Copyright © Loft Orbital Solutions Inc.

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Segment__
#define __OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Segment__

#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Line.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Objects/Point.hpp>

namespace ostk
{
namespace math
{
namespace geom
{
namespace d3
{
namespace objects
{

using ostk::core::types::Real;

using ostk::math::geom::d3::Object;
using ostk::math::geom::d3::objects::Point;
using ostk::math::geom::d3::objects::PointSet;
using ostk::math::geom::d3::objects::Line;

class PointSet;
class Plane;
class Sphere;
class Ellipsoid;

/// @brief                      Segment
///
///                             A segment is a part of a line that is bounded by two distinct end points,
///                             and contains every point on the line between its endpoints.
///
/// @ref                        https://en.wikipedia.org/wiki/Line_segment

class Segment : public Object
{
   public:
    /// @brief              Constructor
    ///
    /// @code
    ///                     Segment segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) ;
    /// @endcode
    ///
    /// @param              [in] aFirstPoint A first point
    /// @param              [in] aSecondPoint A second point

    Segment(const Point& aFirstPoint, const Point& aSecondPoint);

    /// @brief              Clone segment
    ///
    /// @return             Pointer to cloned segment

    virtual Segment* clone() const override;

    /// @brief              Equal to operator
    ///
    /// @code
    ///                     Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0
    ///                     }) ; // True
    /// @endcode
    ///
    /// @param              [in] aSegment A segment
    /// @return             True if segments are equal

    bool operator==(const Segment& aSegment) const;

    /// @brief              Not equal to operator
    ///
    /// @code
    ///                     Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0
    ///                     }) ; // True
    /// @endcode
    ///
    /// @param              [in] aSegment A segment
    /// @return             True if segments are not equal

    bool operator!=(const Segment& aSegment) const;

    /// @brief              Check if segment is defined
    ///
    /// @code
    ///                     Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).isDefined() ; // True
    /// @endcode
    ///
    /// @return             True if segment is defined

    virtual bool isDefined() const override;

    /// @brief              Check if segment is degenerate, i.e. its length is zero
    ///
    /// @code
    ///                     Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }).isDegenerate() ; // True
    /// @endcode
    ///
    /// @return             True if segment is degenerate

    bool isDegenerate() const;

    /// @brief              Check if segment intersects plane
    ///
    /// @code
    ///                     Segment segment = ... ;
    ///                     Plane plane = ... ;
    ///                     segment.intersects(plane) ;
    /// @endcode
    ///
    /// @param              [in] aPlane A plane
    /// @return             True if segment intersects plane

    bool intersects(const Plane& aPlane) const;

    /// @brief              Check if segment intersects sphere
    ///
    /// @code
    ///                     Segment segment = ... ;
    ///                     Sphere sphere = ... ;
    ///                     segment.intersects(sphere) ;
    /// @endcode
    ///
    /// @param              [in] aSphere A sphere
    /// @return             True if segment intersects sphere

    bool intersects(const Sphere& aSphere) const;

    /// @brief              Check if segment intersects ellipsoid
    ///
    /// @code
    ///                     Segment segment = ... ;
    ///                     Ellipsoid ellipsoid = ... ;
    ///                     segment.intersects(ellipsoid) ;
    /// @endcode
    ///
    /// @param              [in] anEllipsoid An ellipsoid
    /// @return             True if segment intersects ellipsoid

    bool intersects(const Ellipsoid& anEllipsoid) const;

    /// @brief              Check if segment contains point
    ///
    /// @code
    ///                     Segment segment = ... ;
    ///                     Point point = ... ;
    ///                     segment.contains(point) ;
    /// @endcode
    ///
    /// @param              [in] aPoint A point
    /// @return             True if segment contains point

    bool contains(const Point& aPoint) const;

    /// @brief              Get segment first point
    ///
    /// @code
    ///                     Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).getFirstPoint() ; // [0.0, 0.0, 0.0]
    /// @endcode
    ///
    /// @return             Segment first point

    Point getFirstPoint() const;

    /// @brief              Get segment second point
    ///
    /// @code
    ///                     Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).getSecondPoint() ; // [0.0, 0.0, 1.0]
    /// @endcode
    ///
    /// @return             Segment second point

    Point getSecondPoint() const;

    /// @brief              Get segment center
    ///
    /// @code
    ///                     Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0 }).getCenter() ; // [0.0, 0.0, 1.0]
    /// @endcode
    ///
    /// @return             Segment center

    Point getCenter() const;

    /// @brief              Get segment direction
    ///
    /// @code
    ///                     Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0 }).getDirection() ; // [0.0, 0.0, 1.0]
    /// @endcode
    ///
    /// @return             Segment direction

    Vector3d getDirection() const;

    /// @brief              Get segment length
    ///
    /// @code
    ///                     Segment({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0 }).getLength() ; // 2.0
    /// @endcode
    ///
    /// @return             Segment length

    Real getLength() const;

    /// @brief              Get distance to point
    ///
    /// @param              [in] aPoint A point
    /// @return             Distance to point

    Real distanceTo(const Point& aPoint) const;

    /// @brief              Get distance to point set
    ///
    /// @param              [in] aPointSet A point set
    /// @return             Distance to point set

    Real distanceTo(const PointSet& aPointSet) const;

    /// @brief              Compute intersection of segment with plane
    ///
    /// @param              [in] aPlane A plane
    /// @return             Intersection of segment with plane

    Intersection intersectionWith(const Plane& aPlane) const;

    /// @brief              Get line from segment
    ///
    /// @return             Line

    Line toLine() const;

    /// @brief              Print segment
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] (optional) displayDecorators If true, display decorators

    virtual void print(std::ostream& anOutputStream, bool displayDecorators = true) const override;

    /// @brief              Apply transformation to segment
    ///
    /// @param              [in] aTransformation A transformation

    virtual void applyTransformation(const Transformation& aTransformation) override;

    /// @brief              Constructs an undefined segment
    ///
    /// @code
    ///                     Segment segment = Segment::Undefined() ; // Undefined
    /// @endcode
    ///
    /// @return             Undefined segment

    static Segment Undefined();

   private:
    Point firstPoint_;
    Point secondPoint_;
};

}  // namespace objects
}  // namespace d3
}  // namespace geom
}  // namespace math
}  // namespace ostk

#endif
