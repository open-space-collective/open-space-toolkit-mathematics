/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cone__
#define __OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cone__

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ray.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/Angle.hpp>

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

using ostk::core::container::Array;
using ostk::core::container::Index;
using ostk::core::container::Size;

using ostk::mathematics::geometry::Angle;
using ostk::mathematics::geometry::d3::Intersection;
using ostk::mathematics::geometry::d3::Object;
using ostk::mathematics::geometry::d3::object::Point;
using ostk::mathematics::geometry::d3::object::Ray;
using ostk::mathematics::object::Vector3d;

#define DEFAULT_RAY_COUNT 0
#define DEFAULT_DISCRETIZATION_LEVEL 40

class Line;
class Segment;
class Plane;
class Polygon;
class Sphere;
class Ellipsoid;

/// @brief                      Cone
///
///                             A cone is a three-dimensional geometric shape that tapers smoothly from a flat circular
///                             base to a point called the apex.
///
/// @code{.cpp}
///                             Cone cone(Point(0.0, 0.0, 0.0), {0.0, 0.0, 1.0}, Angle::Degrees(45.0));
/// @endcode
///
/// @ref                        https://en.wikipedia.org/wiki/Cone
class Cone : public Object
{
   public:
    /// @brief              Constructor
    ///
    /// @code{.cpp}
    ///                     Point apex = { 0.0, 0.0, 0.0 } ;
    ///                     Vector3d axis = { 0.0, 0.0, 1.0 } ;
    ///                     Angle angle = Angle::Degrees(15.0) ;
    ///                     Cone cone = { apex, axis, angle } ;
    /// @endcode
    ///
    /// @param              [in] anApex A cone apex
    /// @param              [in] anAxis A cone axis
    /// @param              [in] anAngle A cone angle
    Cone(const Point& anApex, const Vector3d& anAxis, const Angle& anAngle);

    /// @brief              Clone cone
    ///
    /// @code{.cpp}
    ///                     Cone* clonePtr = cone.clone() ;
    /// @endcode
    ///
    /// @return             Pointer to cloned cone
    virtual Cone* clone() const override;

    /// @brief              Equal to operator
    ///
    /// @code{.cpp}
    ///                     Cone cone = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, Angle::Degrees(15.0) } ;
    ///                     cone == cone ; // True
    /// @endcode
    ///
    /// @param              [in] aCone A cone
    /// @return             True if cones are equal
    bool operator==(const Cone& aCone) const;

    /// @brief              Not equal to operator
    ///
    /// @code{.cpp}
    ///                     Cone coneA = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, Angle::Degrees(15.0) } ;
    ///                     Cone coneB = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, Angle::Degrees(30.0) } ;
    ///                     coneA != coneB ; // True
    /// @endcode
    ///
    /// @param              [in] aCone A cone
    /// @return             True if cones are not equal
    bool operator!=(const Cone& aCone) const;

    /// @brief              Check if cone is defined
    ///
    /// @code{.cpp}
    ///                     Cone cone = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, Angle::Degrees(15.0) } ;
    ///                     cone.isDefined() ; // True
    /// @endcode
    ///
    /// @return             True if cone is defined
    virtual bool isDefined() const override;

    /// @brief              Check if cone intersects sphere
    ///
    /// @code{.cpp}
    ///                     Cone cone = ... ;
    ///                     Sphere sphere = ... ;
    ///                     cone.intersects(sphere) ;
    /// @endcode
    ///
    /// @param              [in] aSphere A sphere
    /// @param              [in] aDiscretizationLevel (optional) The polygonal discretization level
    /// @return             True if cone intersects sphere
    bool intersects(const Sphere& aSphere, const Size aDiscretizationLevel = DEFAULT_DISCRETIZATION_LEVEL) const;

    /// @brief              Check if cone intersects ellipsoid
    ///
    /// @code{.cpp}
    ///                     Cone cone = ... ;
    ///                     Ellipsoid ellipsoid = ... ;
    ///                     cone.intersects(ellipsoid) ;
    /// @endcode
    ///
    /// @param              [in] anEllipsoid An ellipsoid
    /// @param              [in] aDiscretizationLevel (optional) The polygonal discretization level
    /// @return             True if cone intersects ellipsoid
    bool intersects(const Ellipsoid& anEllipsoid, const Size aDiscretizationLevel = DEFAULT_DISCRETIZATION_LEVEL) const;

    /// @brief              Check if cone contains point
    ///
    /// @code{.cpp}
    ///                     Cone cone = ... ;
    ///                     Point point = ... ;
    ///                     cone.contains(point) ;
    /// @endcode
    ///
    /// @param              [in] aPoint A point
    /// @return             True if cone contains point
    bool contains(const Point& aPoint) const;

    /// @brief              Check if cone contains point set
    ///
    /// @code{.cpp}
    ///                     Cone cone = ... ;
    ///                     PointSet pointSet = ... ;
    ///                     cone.contains(pointSet) ;
    /// @endcode
    ///
    /// @param              [in] aPointSet A point set
    /// @return             True if cone contains point set
    bool contains(const PointSet& aPointSet) const;

    /// @brief              Check if cone contains segment
    ///
    /// @code{.cpp}
    ///                     Cone cone = ... ;
    ///                     Segment segment = ... ;
    ///                     cone.contains(segment) ;
    /// @endcode
    ///
    /// @param              [in] aSegment A segment
    /// @return             True if cone contains segment
    bool contains(const Segment& aSegment) const;

    /// @brief              Check if cone contains ray
    ///
    /// @code{.cpp}
    ///                     Cone cone = ... ;
    ///                     Ray ray = ... ;
    ///                     cone.contains(ray) ;
    /// @endcode
    ///
    /// @param              [in] aRay A ray
    /// @return             True if cone contains ray
    bool contains(const Ray& aRay) const;

    /// @brief              Check if cone contains sphere
    ///
    /// @code{.cpp}
    ///                     Cone cone = ... ;
    ///                     Sphere sphere = ... ;
    ///                     cone.contains(sphere) ;
    /// @endcode
    ///
    /// @param              [in] aSphere A sphere
    /// @return             True if cone contains sphere
    bool contains(const Sphere& aSphere) const;

    /// @brief              Check if cone contains ellipsoid
    ///
    /// @code{.cpp}
    ///                     Cone cone = ... ;
    ///                     Ellipsoid ellipsoid = ... ;
    ///                     cone.contains(ellipsoid) ;
    /// @endcode
    ///
    /// @param              [in] anEllipsoid An ellipsoid
    /// @return             True if cone contains ellipsoid
    bool contains(const Ellipsoid& anEllipsoid) const;

    /// @brief              Get cone apex
    ///
    /// @code{.cpp}
    ///                     Cone cone = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, Angle::Degrees(15.0) } ;
    ///                     Point apex = cone.getApex() ;
    /// @endcode
    ///
    /// @return             Cone apex
    Point getApex() const;

    /// @brief              Get cone axis
    ///
    /// @code{.cpp}
    ///                     Cone cone = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, Angle::Degrees(15.0) } ;
    ///                     Vector3d axis = cone.getAxis() ;
    /// @endcode
    ///
    /// @return             Cone axis
    Vector3d getAxis() const;

    /// @brief              Get cone angle
    ///
    /// @code{.cpp}
    ///                     Cone cone = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, Angle::Degrees(15.0) } ;
    ///                     Angle angle = cone.getAngle() ;
    /// @endcode
    ///
    /// @return             Cone angle
    Angle getAngle() const;

    /// @brief              Get rays of lateral surface
    ///
    /// @code{.cpp}
    ///                     Cone cone = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, Angle::Degrees(15.0) } ;
    ///                     Array<Ray> rays = cone.getRaysOfLateralSurface(8) ;
    /// @endcode
    ///
    /// @param              [in] aRayCount A number of rays (at least face count)
    /// @return             Array of rays
    Array<Ray> getRaysOfLateralSurface(const Size aRayCount = DEFAULT_RAY_COUNT) const;

    /// @brief              Compute distance of cone to point
    ///
    /// @code{.cpp}
    ///                     Cone cone = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, Angle::Degrees(15.0) } ;
    ///                     Real distance = cone.distanceTo({ 1.0, 0.0, 0.0 }) ;
    /// @endcode
    ///
    /// @param              [in] aPoint A point
    /// @return             Distance of cone to point
    Real distanceTo(const Point& aPoint) const;

    /// @brief              Compute intersection of cone with sphere
    ///
    /// @code{.cpp}
    ///                     Cone cone = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, Angle::Degrees(15.0) } ;
    ///                     Sphere sphere = Sphere({ 0.0, 0.0, 10.0 }, 1.0) ;
    ///                     Intersection intersection = cone.intersectionWith(sphere) ;
    /// @endcode
    ///
    /// @param              [in] aSphere A sphere
    /// @param              [in] onlyInSight (optional) If true, only return intersection points that are in sight
    /// @param              [in] aDiscretizationLevel (optional) The polygonal discretization level
    /// @return             Intersection of cone with sphere
    Intersection intersectionWith(
        const Sphere& aSphere,
        const bool onlyInSight = false,
        const Size aDiscretizationLevel = DEFAULT_DISCRETIZATION_LEVEL
    ) const;

    /// @brief              Compute intersection of cone with ellipsoid
    ///
    /// @code{.cpp}
    ///                     Cone cone = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, Angle::Degrees(15.0) } ;
    ///                     Ellipsoid ellipsoid = Ellipsoid(Point::Origin(), 1.0, 2.0, 3.0) ;
    ///                     Intersection intersection = cone.intersectionWith(ellipsoid) ;
    /// @endcode
    ///
    /// @param              [in] anEllipsoid An ellipsoid
    /// @param              [in] onlyInSight (optional) If true, only return intersection points that are in sight
    /// @param              [in] aDiscretizationLevel (optional) The polygonal discretization level
    /// @return             Intersection of cone with ellipsoid
    Intersection intersectionWith(
        const Ellipsoid& anEllipsoid,
        const bool onlyInSight = false,
        const Size aDiscretizationLevel = DEFAULT_DISCRETIZATION_LEVEL
    ) const;

    /// @brief              Print cone
    ///
    /// @code{.cpp}
    ///                     Cone cone = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, Angle::Degrees(15.0) } ;
    ///                     cone.print(std::cout, true) ;
    /// @endcode
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] (optional) displayDecorators If true, display decorators
    virtual void print(std::ostream& anOutputStream, bool displayDecorators = true) const override;

    /// @brief              Apply transformation to cone
    ///
    /// @code{.cpp}
    ///                     Cone cone = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, Angle::Degrees(15.0) } ;
    ///                     cone.applyTransformation(Transformation::Translation({ 1.0, 0.0, 0.0 })) ;
    /// @endcode
    ///
    /// @param              [in] aTransformation A transformation
    virtual void applyTransformation(const Transformation& aTransformation) override;

    /// @brief              Constructs an undefined cone
    ///
    /// @code{.cpp}
    ///                     Cone cone = Cone::Undefined() ;
    /// @endcode
    ///
    /// @return             Undefined cone
    static Cone Undefined();

   private:
    Point apex_;
    Vector3d axis_;
    Angle angle_;
};

}  // namespace object
}  // namespace d3
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
