/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ray__
#define __OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Ray__

#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Point.hpp>

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

using ostk::core::type::Real;

using ostk::mathematics::geometry::d3::Object;
using ostk::mathematics::geometry::d3::object::Point;
using ostk::mathematics::object::Vector3d;

#define DEFAULT_ONLY_IN_SIGHT false

class PointSet;
class Line;
class Segment;
class Plane;
class Polygon;
class Sphere;
class Ellipsoid;
class Pyramid;

/// @brief                      Ray
///
/// @code{.cpp}
///                             Ray ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) ;
/// @endcode
///
/// @ref                        https://en.wikipedia.org/wiki/Line_(geometry)#Ray
class Ray : public Object
{
   public:
    /// @brief              Constructor
    ///
    /// @code
    ///                     Ray ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) ;
    /// @endcode
    ///
    /// @param              [in] anOrigin A ray origin
    /// @param              [in] aDirection A ray direction
    Ray(const Point& anOrigin, const Vector3d& aDirection);

    /// @brief              Clone ray
    ///
    /// @code{.cpp}
    ///                     Ray* rayPtr = Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).clone() ;
    /// @endcode
    ///
    /// @return             Pointer to cloned ray
    virtual Ray* clone() const override;

    /// @brief              Equal to operator
    ///
    /// @code
    ///                     Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) == Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) ; //
    ///                     True
    /// @endcode
    ///
    /// @param              [in] aRay A ray
    /// @return             True if rays are equal
    bool operator==(const Ray& aRay) const;

    /// @brief              Not equal to operator
    ///
    /// @code
    ///                     Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) != Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 2.0 }) ; //
    ///                     True
    /// @endcode
    ///
    /// @param              [in] aRay A ray
    /// @return             True if rays are not equal
    bool operator!=(const Ray& aRay) const;

    /// @brief              Check if ray is defined
    ///
    /// @code
    ///                     Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).isDefined() ; // True
    /// @endcode
    ///
    /// @return             True if ray is defined
    virtual bool isDefined() const override;

    /// @brief              Check if ray intersects point
    ///
    /// @code
    ///                     Ray ray = ... ;
    ///                     Point point = ... ;
    ///                     ray.intersects(point) ;
    /// @endcode
    ///
    /// @param              [in] anPoint A point
    /// @return             True if ray intersects point
    bool intersects(const Point& aPoint) const;

    /// @brief              Check if ray intersects plane
    ///
    /// @code
    ///                     Ray ray = ... ;
    ///                     Plane plane = ... ;
    ///                     ray.intersects(plane) ;
    /// @endcode
    ///
    /// @param              [in] aPlane A plane
    /// @return             True if ray intersects plane
    bool intersects(const Plane& aPlane) const;

    /// @brief              Check if ray intersects sphere
    ///
    /// @code
    ///                     Ray ray = ... ;
    ///                     Sphere sphere = ... ;
    ///                     ray.intersects(sphere) ;
    /// @endcode
    ///
    /// @param              [in] anSphere A sphere
    /// @return             True if ray intersects sphere
    bool intersects(const Sphere& aSphere) const;

    /// @brief              Check if ray intersects ellipsoid
    ///
    /// @code
    ///                     Ray ray = ... ;
    ///                     Ellipsoid ellipsoid = ... ;
    ///                     ray.intersects(ellipsoid) ;
    /// @endcode
    ///
    /// @param              [in] anEllipsoid An ellipsoid
    /// @return             True if ray intersects ellipsoid
    bool intersects(const Ellipsoid& anEllipsoid) const;

    /// @brief              Check if ray contains point
    ///
    /// @code
    ///                     Ray ray = ... ;
    ///                     Point point = ... ;
    ///                     ray.contains(point) ;
    /// @endcode
    ///
    /// @param              [in] aPoint A point
    /// @return             True if ray contains point
    bool contains(const Point& aPoint) const;

    /// @brief              Check if ray contains point set
    ///
    /// @code
    ///                     Ray ray = ... ;
    ///                     PointSet pointSet = ... ;
    ///                     ray.contains(pointSet) ;
    /// @endcode
    ///
    /// @param              [in] aPointSet A point set
    /// @return             True if ray contains point set
    bool contains(const PointSet& aPointSet) const;

    /// @brief              Get ray origin
    ///
    /// @code
    ///                     Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).getOrigin() ; // [0.0, 0.0, 0.0]
    /// @endcode
    ///
    /// @return             Ray origin
    Point getOrigin() const;

    /// @brief              Get ray direction
    ///
    /// @code
    ///                     Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).getDirection() ; // [0.0, 0.0, 1.0]
    /// @endcode
    ///
    /// @return             Ray direction
    Vector3d getDirection() const;

    /// @brief              Get distance to point
    ///
    /// @code{.cpp}
    ///                     Ray ray = Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) ;
    ///                     Real distance = ray.distanceTo(Point(1.0, 0.0, 0.0)) ;
    /// @endcode
    ///
    /// @param              [in] aPoint A point
    /// @return             Distance to point
    Real distanceTo(const Point& aPoint) const;

    /// @brief              Compute intersection of ray with plane
    ///
    /// @code{.cpp}
    ///                     Ray ray = Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) ;
    ///                     Plane plane = Plane({ 0.0, 0.0, 1.0 }, { 0.0, 0.0, 1.0 }) ;
    ///                     Intersection intersection = ray.intersectionWith(plane) ;
    /// @endcode
    ///
    /// @param              [in] aPlane A plane
    /// @return             Intersection of ray with plane
    Intersection intersectionWith(const Plane& aPlane) const;

    /// @brief              Compute intersection of ray with sphere
    ///
    /// @code{.cpp}
    ///                     Ray ray = Ray({ 0.0, 0.0, -2.0 }, { 0.0, 0.0, 1.0 }) ;
    ///                     Sphere sphere = Sphere(Point::Origin(), 1.0) ;
    ///                     Intersection intersection = ray.intersectionWith(sphere) ;
    /// @endcode
    ///
    /// @param              [in] aSphere A sphere
    /// @param              [in] onlyInSight (optional) If true, only return intersection points that are in sight
    /// @return             Intersection of ray with sphere
    Intersection intersectionWith(const Sphere& aSphere, const bool onlyInSight = DEFAULT_ONLY_IN_SIGHT) const;

    /// @brief              Compute intersection of ray with ellipsoid
    ///
    /// @code{.cpp}
    ///                     Ray ray = Ray({ 0.0, 0.0, -2.0 }, { 0.0, 0.0, 1.0 }) ;
    ///                     Ellipsoid ellipsoid = ... ;
    ///                     Intersection intersection = ray.intersectionWith(ellipsoid) ;
    /// @endcode
    ///
    /// @param              [in] anEllipsoid An ellipsoid
    /// @param              [in] onlyInSight (optional) If true, only return intersection points that are in sight
    /// @return             Intersection of ray with ellipsoid
    Intersection intersectionWith(const Ellipsoid& anEllipsoid, const bool onlyInSight = DEFAULT_ONLY_IN_SIGHT) const;

    /// @brief              Print ray
    ///
    /// @code{.cpp}
    ///                     Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }).print(std::cout, true) ;
    /// @endcode
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] (optional) displayDecorators If true, display decorators
    virtual void print(std::ostream& anOutputStream, bool displayDecorators = true) const override;

    /// @brief              Apply transformation to ray
    ///
    /// @code{.cpp}
    ///                     Ray ray = Ray({ 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }) ;
    ///                     ray.applyTransformation(Transformation::Identity()) ;
    /// @endcode
    ///
    /// @param              [in] aTransformation A transformation
    virtual void applyTransformation(const Transformation& aTransformation) override;

    /// @brief              Constructs an undefined ray
    ///
    /// @code
    ///                     Ray ray = Ray::Undefined() ; // Undefined
    /// @endcode
    ///
    /// @return             Undefined ray
    static Ray Undefined();

   private:
    Point origin_;
    Vector3d direction_;
};

}  // namespace object
}  // namespace d3
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
