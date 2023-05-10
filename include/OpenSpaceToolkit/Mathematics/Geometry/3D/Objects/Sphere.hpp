/// Apache License 2.0 

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Sphere__
#define __OpenSpaceToolkit_Mathematics_Geometry_3D_Objects_Sphere__

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

using ostk::math::geom::d3::Object;
using ostk::math::geom::d3::objects::Point;

#define DEFAULT_ONLY_IN_SIGHT false

class PointSet;
class Line;
class Ray;
class Segment;
class Plane;
class Polygon;
class Ellipsoid;
class Pyramid;
class Cone;

/// @brief                      Sphere
///
///                             A sphere is a perfectly round geometrical object in three-dimensional space that is the
///                             surface of a completely round ball.
///
/// @ref                        https://en.wikipedia.org/wiki/Sphere

class Sphere : public Object
{
   public:
    /// @brief              Constructor
    ///
    /// @code
    ///                     Sphere sphere({ 0.0, 0.0, 0.0 }, 1.0) ;
    /// @endcode
    ///
    /// @param              [in] aCenter A sphere center
    /// @param              [in] aRadius A sphere radius

    Sphere(const Point& aCenter, const Real& aRadius);

    /// @brief              Clone sphere
    ///
    /// @return             Pointer to cloned sphere

    virtual Sphere* clone() const override;

    /// @brief              Equal to operator
    ///
    /// @code
    ///                     Sphere(Point::Origin(), 1.0) == Sphere(Point::Origin(), 1.0) ; // True
    /// @endcode
    ///
    /// @param              [in] aSphere A sphere
    /// @return             True if spheres are equal

    bool operator==(const Sphere& aSphere) const;

    /// @brief              Not equal to operator
    ///
    /// @code
    ///                     Sphere(Point::Origin(), 1.0) != Sphere(Point::Origin(), 2.0) ; // True
    /// @endcode
    ///
    /// @param              [in] aSphere A sphere
    /// @return             True if spheres are not equal

    bool operator!=(const Sphere& aSphere) const;

    /// @brief              Check if sphere is defined
    ///
    /// @code
    ///                     Sphere(Point::Origin(), 1.0).isDefined() ; // True
    /// @endcode
    ///
    /// @return             True if sphere is defined

    virtual bool isDefined() const override;

    /// @brief              Check if sphere is unitary, i.e. its radius is equal to 1.0
    ///
    /// @code
    ///                     Sphere(Point::Origin(), 1.0).isUnitary() ; // True
    /// @endcode
    ///
    /// @return             True if sphere is unitary

    bool isUnitary() const;

    /// @brief              Check if sphere intersects point
    ///
    /// @code
    ///                     Sphere sphere = ... ;
    ///                     Point point = ... ;
    ///                     sphere.intersects(point) ;
    /// @endcode
    ///
    /// @param              [in] aPoint A point
    /// @return             True if sphere intersects point

    bool intersects(const Point& aPoint) const;

    /// @brief              Check if sphere intersects point set
    ///
    /// @code
    ///                     Sphere sphere = ... ;
    ///                     PointSet pointSet = ... ;
    ///                     sphere.intersects(pointSet) ;
    /// @endcode
    ///
    /// @param              [in] aPointSet A point set
    /// @return             True if sphere intersects point set

    bool intersects(const PointSet& aPointSet) const;

    /// @brief              Check if sphere intersects line
    ///
    /// @code
    ///                     Sphere sphere = ... ;
    ///                     Line line = ... ;
    ///                     sphere.intersects(line) ;
    /// @endcode
    ///
    /// @param              [in] aLine A line
    /// @return             True if sphere intersects line

    bool intersects(const Line& aLine) const;

    /// @brief              Check if sphere intersects ray
    ///
    /// @code
    ///                     Sphere sphere = ... ;
    ///                     Ray ray = ... ;
    ///                     sphere.intersects(ray) ;
    /// @endcode
    ///
    /// @param              [in] aRay A ray
    /// @return             True if sphere intersects ray

    bool intersects(const Ray& aRay) const;

    /// @brief              Check if sphere intersects segment
    ///
    /// @code
    ///                     Sphere sphere = ... ;
    ///                     Segment segment = ... ;
    ///                     sphere.intersects(segment) ;
    /// @endcode
    ///
    /// @param              [in] aSegment A segment
    /// @return             True if sphere intersects segment

    bool intersects(const Segment& aSegment) const;

    /// @brief              Check if sphere intersects plane
    ///
    /// @code
    ///                     Sphere sphere = ... ;
    ///                     Plane plane = ... ;
    ///                     sphere.intersects(plane) ;
    /// @endcode
    ///
    /// @param              [in] aPlane A plane
    /// @return             True if sphere intersects plane

    bool intersects(const Plane& aPlane) const;

    /// @brief              Check if sphere intersects ellipsoid
    ///
    /// @code
    ///                     Sphere sphere = ... ;
    ///                     Ellipsoid ellipsoid = ... ;
    ///                     sphere.intersects(ellipsoid) ;
    /// @endcode
    ///
    /// @param              [in] anEllipsoid An ellipsoid
    /// @return             True if sphere intersects ellipsoid

    bool intersects(const Ellipsoid& anEllipsoid) const;

    /// @brief              Check if sphere intersects pyramid
    ///
    /// @code
    ///                     Sphere sphere = ... ;
    ///                     Pyramid pyramid = ... ;
    ///                     sphere.intersects(pyramid) ;
    /// @endcode
    ///
    /// @param              [in] aPyramid A pyramid
    /// @return             True if sphere intersects pyramid

    bool intersects(const Pyramid& aPyramid) const;

    /// @brief              Check if sphere intersects cone
    ///
    /// @code
    ///                     Sphere sphere = ... ;
    ///                     Cone cone = ... ;
    ///                     sphere.intersects(cone) ;
    /// @endcode
    ///
    /// @param              [in] aCone A cone
    /// @return             True if sphere intersects cone

    bool intersects(const Cone& aCone) const;

    /// @brief              Check if sphere contains point
    ///
    /// @code
    ///                     Sphere sphere = ... ;
    ///                     Point point = ... ;
    ///                     sphere.contains(point) ;
    /// @endcode
    ///
    /// @param              [in] aPoint A point
    /// @return             True if sphere contains point

    bool contains(const Point& aPoint) const;

    /// @brief              Check if sphere contains point set
    ///
    /// @code
    ///                     Sphere sphere = ... ;
    ///                     PointSet pointSet = ... ;
    ///                     sphere.contains(pointSet) ;
    /// @endcode
    ///
    /// @param              [in] aPointSet A point set
    /// @return             True if sphere contains point set

    bool contains(const PointSet& aPointSet) const;

    /// @brief              Get sphere center
    ///
    /// @code
    ///                     Sphere(Point::Origin(), 1.0).getCenter() ; // [0.0, 0.0, 0.0]
    /// @endcode
    ///
    /// @return             Sphere center

    Point getCenter() const;

    /// @brief              Get sphere radius
    ///
    /// @code
    ///                     Sphere(Point::Origin(), 1.0).getRadius() ; // 1.0
    /// @endcode
    ///
    /// @return             Sphere radius

    Real getRadius() const;

    /// @brief              Compute intersection of sphere with line
    ///
    /// @param              [in] aLine A line
    /// @return             Intersection of sphere with line

    Intersection intersectionWith(const Line& aLine) const;

    /// @brief              Compute intersection of sphere with ray
    ///
    /// @param              [in] aRay A ray
    /// @param              [in] onlyInSight (optional) If true, only return intersection points that are in sight
    /// @return             Intersection of sphere with ray

    Intersection intersectionWith(const Ray& aRay, const bool onlyInSight = DEFAULT_ONLY_IN_SIGHT) const;

    /// @brief              Compute intersection of sphere with segment
    ///
    /// @param              [in] aSegment A segment
    /// @return             Intersection of sphere with segment

    Intersection intersectionWith(const Segment& aSegment) const;

    /// @brief              Compute intersection of sphere with pyramid
    ///
    /// @param              [in] aPyramid A pyramid
    /// @param              [in] onlyInSight (optional) If true, only return intersection points that are in sight
    /// @return             Intersection of sphere with pyramid

    Intersection intersectionWith(const Pyramid& aPyramid, const bool onlyInSight = DEFAULT_ONLY_IN_SIGHT) const;

    /// @brief              Compute intersection of sphere with cone
    ///
    /// @param              [in] aCone A cone
    /// @param              [in] onlyInSight (optional) If true, only return intersection points that are in sight
    /// @return             Intersection of sphere with cone

    Intersection intersectionWith(const Cone& aCone, const bool onlyInSight = DEFAULT_ONLY_IN_SIGHT) const;

    /// @brief              Print sphere
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] (optional) displayDecorators If true, display decorators

    virtual void print(std::ostream& anOutputStream, bool displayDecorators = true) const override;

    /// @brief              Apply transformation to sphere
    ///
    /// @param              [in] aTransformation A transformation

    virtual void applyTransformation(const Transformation& aTransformation) override;

    /// @brief              Constructs an undefined sphere
    ///
    /// @code
    ///                     Sphere sphere = Sphere::Undefined() ; // Undefined
    /// @endcode
    ///
    /// @return             Undefined sphere

    static Sphere Undefined();

    /// @brief              Constructs a unit sphere
    ///
    /// @ref                https://en.wikipedia.org/wiki/Unit_sphere
    ///
    /// @code
    ///                     Sphere sphere = Sphere::Unit({ 0.0, 0.0, 0.0 }) ;
    /// @endcode
    ///
    /// @return             Unit sphere

    static Sphere Unit(const Point& aCenter);

   private:
    Point center_;
    Real radius_;
};

}  // namespace objects
}  // namespace d3
}  // namespace geom
}  // namespace math
}  // namespace ostk

#endif
