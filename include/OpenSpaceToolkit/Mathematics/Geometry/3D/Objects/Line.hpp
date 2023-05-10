/// Apache License 2.0 

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Line__
#define __OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Line__

#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object.hpp>
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

using ostk::math::obj::Vector3d;
using ostk::math::geom::d3::Object;
using ostk::math::geom::d3::objects::Point;

class PointSet;
class Plane;
class Sphere;
class Ellipsoid;

/// @brief                      Line
///
/// @ref                        https://en.wikipedia.org/wiki/Line_(geometry)

class Line : public Object
{
   public:
    /// @brief              Constructor
    ///
    /// @code
    ///                     Line line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) ;
    /// @endcode
    ///
    /// @param              [in] anOrigin A line origin
    /// @param              [in] aDirection A line direction

    Line(const Point& anOrigin, const Vector3d& aDirection);

    /// @brief              Clone line
    ///
    /// @return             Pointer to cloned line

    virtual Line* clone() const override;

    /// @brief              Equal to operator
    ///
    /// @code
    ///                     Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) ;
    ///                     // True
    /// @endcode
    ///
    /// @param              [in] aLine A line
    /// @return             True if lines are equal

    bool operator==(const Line& aLine) const;

    /// @brief              Not equal to operator
    ///
    /// @code
    ///                     Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0 }) ;
    ///                     // True
    /// @endcode
    ///
    /// @param              [in] aLine A line
    /// @return             True if lines are not equal

    bool operator!=(const Line& aLine) const;

    /// @brief              Check if line is defined
    ///
    /// @code
    ///                     Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).isDefined() ; // True
    /// @endcode
    ///
    /// @return             True if line is defined

    virtual bool isDefined() const override;

    /// @brief              Check if line intersects point
    ///
    /// @code
    ///                     Line line = ... ;
    ///                     Point point = ... ;
    ///                     line.intersects(point) ;
    /// @endcode
    ///
    /// @param              [in] anPoint A point
    /// @return             True if line intersects point

    bool intersects(const Point& aPoint) const;

    /// @brief              Check if line intersects plane
    ///
    /// @code
    ///                     Line line = ... ;
    ///                     Plane plane = ... ;
    ///                     line.intersects(plane) ;
    /// @endcode
    ///
    /// @param              [in] aPlane A plane
    /// @return             True if line intersects plane

    bool intersects(const Plane& aPlane) const;

    /// @brief              Check if line intersects sphere
    ///
    /// @code
    ///                     Line line = ... ;
    ///                     Sphere sphere = ... ;
    ///                     line.intersects(sphere) ;
    /// @endcode
    ///
    /// @param              [in] aSphere A sphere
    /// @return             True if line intersects sphere

    bool intersects(const Sphere& aSphere) const;

    /// @brief              Check if line intersects ellipsoid
    ///
    /// @code
    ///                     Line line = ... ;
    ///                     Ellipsoid ellipsoid = ... ;
    ///                     line.intersects(ellipsoid) ;
    /// @endcode
    ///
    /// @param              [in] anEllipsoid An ellipsoid
    /// @return             True if line intersects ellipsoid

    bool intersects(const Ellipsoid& anEllipsoid) const;

    /// @brief              Check if line contains point
    ///
    /// @code
    ///                     Line line = ... ;
    ///                     Point point = ... ;
    ///                     line.contains(point) ;
    /// @endcode
    ///
    /// @param              [in] aPoint A point
    /// @return             True if line contains point

    bool contains(const Point& aPoint) const;

    /// @brief              Check if line contains point set
    ///
    /// @code
    ///                     Line line = ... ;
    ///                     PointSet pointSet = ... ;
    ///                     line.contains(pointSet) ;
    /// @endcode
    ///
    /// @param              [in] aPointSet A point set
    /// @return             True if line contains point set

    bool contains(const PointSet& aPointSet) const;

    /// @brief              Get line origin
    ///
    /// @code
    ///                     Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).getOrigin() ; // [0.0, 0.0, 0.0]
    /// @endcode
    ///
    /// @return             Line origin

    Point getOrigin() const;

    /// @brief              Get line direction
    ///
    /// @code
    ///                     Line({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).getDirection() ; // [0.0, 0.0, 1.0]
    /// @endcode
    ///
    /// @return             Line direction

    Vector3d getDirection() const;

    /// @brief              Get distance to point
    ///
    /// @param              [in] aPoint A point
    /// @return             Distance to point

    Real distanceTo(const Point& aPoint) const;

    /// @brief              Compute intersection of line with plane
    ///
    /// @param              [in] aPlane A plane
    /// @return             Intersection of line with plane

    Intersection intersectionWith(const Plane& aPlane) const;

    /// @brief              Print line
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] (optional) displayDecorators If true, display decorators

    virtual void print(std::ostream& anOutputStream, bool displayDecorators = true) const override;

    /// @brief              Apply transformation to line
    ///
    /// @param              [in] aTransformation A transformation

    virtual void applyTransformation(const Transformation& aTransformation) override;

    /// @brief              Constructs an undefined line
    ///
    /// @code
    ///                     Line line = Line::Undefined() ; // Undefined
    /// @endcode
    ///
    /// @return             Undefined line

    static Line Undefined();

    /// @brief              Constructs a line using two points
    ///
    /// @code
    ///                     Point p_1 = ...
    ///                     Point p_2 = ...
    ///                     Line line = Line::Points(p_1, p_2) ;
    /// @endcode
    ///
    /// @return             Line

    static Line Points(const Point& aFirstPoint, const Point& aSecondPoint);

   private:
    Point origin_;
    Vector3d direction_;
};

}  // namespace objects
}  // namespace d3
}  // namespace geom
}  // namespace math
}  // namespace ostk

#endif
