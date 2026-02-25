/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cuboid__
#define __OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Cuboid__

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

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
using ostk::core::type::Real;

using ostk::mathematics::geometry::d3::Intersection;
using ostk::mathematics::geometry::d3::Object;
using ostk::mathematics::geometry::d3::object::Point;
using ostk::mathematics::geometry::d3::object::Segment;
using ostk::mathematics::object::Vector3d;

class PointSet;
class Line;
class Ray;
class Segment;
class Plane;
class Polygon;
class Sphere;
class Pyramid;

/// @brief                      Cuboid
///
/// @code{.cpp}
///                             Cuboid cuboid(Point(0.0, 0.0, 0.0), {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}},
///                             {1.0, 2.0, 3.0});
/// @endcode
///
/// @ref                        https://en.wikipedia.org/wiki/Cuboid
class Cuboid : public Object
{
   public:
    typedef Point Vertex;
    typedef Segment Edge;

    /// @brief              Constructor
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = { { 0.0, 0.0, 0.0 }, { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0
    ///                     } }, { 1.0, 2.0, 3.0 } } ;
    /// @endcode
    ///
    Cuboid(const Point& aCenter, const std::array<Vector3d, 3>& aAxisArray, const std::array<Real, 3>& anExtent);

    /// @brief              Clone cuboid
    ///
    /// @code{.cpp}
    ///                     Cuboid* clonePtr = cuboid.clone() ;
    /// @endcode
    ///
    /// @return             Pointer to cloned cuboid
    virtual Cuboid* clone() const override;

    /// @brief              Equal to operator
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = { { 0.0, 0.0, 0.0 }, { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0
    ///                     } }, { 1.0, 2.0, 3.0 } } ; cuboid == cuboid ; // True
    /// @endcode
    ///
    /// @param              [in] aCuboid An cuboid
    /// @return             True if cuboids are equal
    bool operator==(const Cuboid& aCuboid) const;

    /// @brief              Not equal to operator
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = { { 0.0, 0.0, 0.0 }, { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0
    ///                     } }, { 1.0, 2.0, 3.0 } } ; cuboid != cuboid ; // False
    /// @endcode
    ///
    /// @param              [in] aCuboid An cuboid
    /// @return             True if cuboids are not equal
    bool operator!=(const Cuboid& aCuboid) const;

    /// @brief              Check if cuboid is defined
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = { { 0.0, 0.0, 0.0 }, { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0
    ///                     } }, { 1.0, 2.0, 3.0 } } ; cuboid.isDefined() ; // True
    /// @endcode
    ///
    /// @return             True if cuboid is defined
    virtual bool isDefined() const override;

    /// @brief              Check if cuboid is near another cuboid
    ///
    /// @code{.cpp}
    ///                     Point(0.0, 0.0, 0.0).isNear(Point(0.0, 0.0, 0.0), 1e-15) ; // True
    /// @endcode
    ///
    /// @param              [in] aCuboid A cuboid
    /// @param              [in] aTolerance A tolerance
    /// @return             True if cuboid is near another cuboid
    bool isNear(const Cuboid& aCuboid, const Real& aTolerance) const;

    /// @brief              Check if cuboid intersects point
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = ... ;
    ///                     Point point = ... ;
    ///                     cuboid.intersects(point) ;
    /// @endcode
    ///
    /// @param              [in] aPoint A point
    /// @return             True if cuboid intersects point
    bool intersects(const Point& aPoint) const;

    /// @brief              Check if cuboid intersects point set
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = ... ;
    ///                     PointSet pointSet = ... ;
    ///                     cuboid.intersects(pointSet) ;
    /// @endcode
    ///
    /// @param              [in] aPointSet A point set
    /// @return             True if cuboid intersects point set
    bool intersects(const PointSet& aPointSet) const;

    /// @brief              Check if cuboid intersects line
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = ... ;
    ///                     Line line = ... ;
    ///                     cuboid.intersects(line) ;
    /// @endcode
    ///
    /// @param              [in] aLine A line
    /// @return             True if cuboid intersects line
    bool intersects(const Line& aLine) const;

    /// @brief              Check if cuboid intersects ray
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = ... ;
    ///                     Ray ray = ... ;
    ///                     cuboid.intersects(ray) ;
    /// @endcode
    ///
    /// @param              [in] aRay A ray
    /// @return             True if cuboid intersects ray
    bool intersects(const Ray& aRay) const;

    /// @brief              Check if cuboid intersects segment
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = ... ;
    ///                     Segment segment = ... ;
    ///                     cuboid.intersects(segment) ;
    /// @endcode
    ///
    /// @param              [in] aSegment A segment
    /// @return             True if cuboid intersects segment
    bool intersects(const Segment& aSegment) const;

    /// @brief              Check if cuboid intersects plane
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = ... ;
    ///                     Plane plane = ... ;
    ///                     cuboid.intersects(plane) ;
    /// @endcode
    ///
    /// @param              [in] aPlane A plane
    /// @return             True if cuboid intersects plane
    bool intersects(const Plane& aPlane) const;

    /// @brief              Check if cuboid intersects sphere
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = ... ;
    ///                     Sphere sphere = ... ;
    ///                     cuboid.intersects(sphere) ;
    /// @endcode
    ///
    /// @param              [in] aSphere A sphere
    /// @return             True if cuboid intersects sphere
    bool intersects(const Sphere& aSphere) const;

    /// @brief              Check if cuboid intersects cuboid
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = ... ;
    ///                     Cuboid anotherCuboid = ... ;
    ///                     cuboid.intersects(anotherCuboid) ;
    /// @endcode
    ///
    /// @param              [in] aCuboid An cuboid
    /// @return             True if cuboid intersects cuboid
    bool intersects(const Cuboid& aCuboid) const;

    /// @brief              Check if cuboid intersects pyramid
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = ... ;
    ///                     Pyramid pyramid = ... ;
    ///                     cuboid.intersects(pyramid) ;
    /// @endcode
    ///
    /// @param              [in] aPyramid A pyramid
    /// @return             True if cuboid intersects pyramid
    bool intersects(const Pyramid& aPyramid) const;

    /// @brief              Check if cuboid contains point
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = ... ;
    ///                     Point point = ... ;
    ///                     cuboid.contains(point) ;
    /// @endcode
    ///
    /// @param              [in] aPoint A point
    /// @return             True if cuboid contains point
    bool contains(const Point& aPoint) const;

    /// @brief              Check if cuboid contains point set
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = ... ;
    ///                     PointSet pointSet = ... ;
    ///                     cuboid.contains(pointSet) ;
    /// @endcode
    ///
    /// @param              [in] aPointSet A point set
    /// @return             True if cuboid contains point set
    bool contains(const PointSet& aPointSet) const;

    /// @brief              Check if cuboid contains segment
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = ... ;
    ///                     Segment segment = ... ;
    ///                     cuboid.contains(segment) ;
    /// @endcode
    ///
    /// @param              [in] aSegment A segment
    /// @return             True if cuboid contains segment
    bool contains(const Segment& aSegment) const;

    /// @brief              Get cuboid center
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = { { 0.0, 0.0, 0.0 }, { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0
    ///                     } }, { 1.0, 2.0, 3.0 } } ; cuboid.getCenter() ; // [0.0, 0.0, 0.0]
    /// @endcode
    ///
    /// @return             Cuboid center
    Point getCenter() const;

    /// @brief              Get cuboid first axis
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = Cuboid::Cube({ 0.0, 0.0, 0.0 }, 1.0) ;
    ///                     Vector3d firstAxis = cuboid.getFirstAxis() ;
    /// @endcode
    ///
    /// @return             Cuboid first axis
    Vector3d getFirstAxis() const;

    /// @brief              Get cuboid second axis
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = Cuboid::Cube({ 0.0, 0.0, 0.0 }, 1.0) ;
    ///                     Vector3d secondAxis = cuboid.getSecondAxis() ;
    /// @endcode
    ///
    /// @return             Cuboid second axis
    Vector3d getSecondAxis() const;

    /// @brief              Get cuboid third axis
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = Cuboid::Cube({ 0.0, 0.0, 0.0 }, 1.0) ;
    ///                     Vector3d thirdAxis = cuboid.getThirdAxis() ;
    /// @endcode
    ///
    /// @return             Cuboid third axis
    Vector3d getThirdAxis() const;

    /// @brief              Get cuboid first extent
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = Cuboid::Cube({ 0.0, 0.0, 0.0 }, 1.0) ;
    ///                     Real firstExtent = cuboid.getFirstExtent() ;
    /// @endcode
    ///
    /// @return             Cuboid first extent
    Real getFirstExtent() const;

    /// @brief              Get cuboid second extent
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = Cuboid::Cube({ 0.0, 0.0, 0.0 }, 1.0) ;
    ///                     Real secondExtent = cuboid.getSecondExtent() ;
    /// @endcode
    ///
    /// @return             Cuboid second extent
    Real getSecondExtent() const;

    /// @brief              Get cuboid third extent
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = Cuboid::Cube({ 0.0, 0.0, 0.0 }, 1.0) ;
    ///                     Real thirdExtent = cuboid.getThirdExtent() ;
    /// @endcode
    ///
    /// @return             Cuboid third extent
    Real getThirdExtent() const;

    /// @brief              Get cuboid vertices
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = Cuboid::Cube({ 0.0, 0.0, 0.0 }, 1.0) ;
    ///                     Array<Cuboid::Vertex> vertices = cuboid.getVertices() ;
    /// @endcode
    ///
    /// @return             Cuboid vertices
    Array<Cuboid::Vertex> getVertices() const;

    /// @brief              Compute intersection of cuboid with line
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = Cuboid::Cube({ 0.0, 0.0, 0.0 }, 1.0) ;
    ///                     Line line = Line({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }) ;
    ///                     Intersection intersection = cuboid.intersectionWith(line) ;
    /// @endcode
    ///
    /// @param              [in] aLine A line
    /// @return             Intersection of cuboid with line
    Intersection intersectionWith(const Line& aLine) const;

    /// @brief              Compute intersection of cuboid with ray
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = Cuboid::Cube({ 0.0, 0.0, 0.0 }, 1.0) ;
    ///                     Ray ray = Ray({ -2.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }) ;
    ///                     Intersection intersection = cuboid.intersectionWith(ray) ;
    /// @endcode
    ///
    /// @param              [in] aRay A ray
    /// @param              [in] onlyInSight (optional) If true, only return intersection points that are in sight
    /// @return             Intersection of cuboid with ray
    Intersection intersectionWith(const Ray& aRay, const bool onlyInSight = false) const;

    /// @brief              Compute intersection of cuboid with segment
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = Cuboid::Cube({ 0.0, 0.0, 0.0 }, 1.0) ;
    ///                     Segment segment = Segment({ -2.0, 0.0, 0.0 }, { 2.0, 0.0, 0.0 }) ;
    ///                     Intersection intersection = cuboid.intersectionWith(segment) ;
    /// @endcode
    ///
    /// @param              [in] aSegment A segment
    /// @return             Intersection of cuboid with segment
    Intersection intersectionWith(const Segment& aSegment) const;

    /// @brief              Compute intersection of cuboid with cuboid
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = Cuboid::Cube({ 0.0, 0.0, 0.0 }, 1.0) ;
    ///                     Cuboid anotherCuboid = Cuboid::Cube({ 0.5, 0.0, 0.0 }, 1.0) ;
    ///                     Intersection intersection = cuboid.intersectionWith(anotherCuboid) ;
    /// @endcode
    ///
    /// @param              [in] aSegment A cuboid
    /// @return             Intersection of cuboid with cuboid
    Intersection intersectionWith(const Cuboid& aCuboid) const;

    /// @brief              Compute intersection of cuboid with pyramid
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = Cuboid::Cube({ 0.0, 0.0, 0.0 }, 1.0) ;
    ///                     Pyramid pyramid = ... ;
    ///                     Intersection intersection = cuboid.intersectionWith(pyramid) ;
    /// @endcode
    ///
    /// @param              [in] aPyramid A pyramid
    /// @param              [in] onlyInSight (optional) If true, only return intersection points that are in sight
    /// @return             Intersection of cuboid with pyramid
    Intersection intersectionWith(const Pyramid& aPyramid, const bool onlyInSight = false) const;

    /// @brief              Print cuboid
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = Cuboid::Cube({ 0.0, 0.0, 0.0 }, 1.0) ;
    ///                     cuboid.print(std::cout, true) ;
    /// @endcode
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] (optional) displayDecorators If true, display decorators
    virtual void print(std::ostream& anOutputStream, bool displayDecorators = true) const override;

    /// @brief              Apply transformation to cuboid
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = Cuboid::Cube({ 0.0, 0.0, 0.0 }, 1.0) ;
    ///                     cuboid.applyTransformation(Transformation::Translation({ 1.0, 0.0, 0.0 })) ;
    /// @endcode
    ///
    /// @param              [in] aTransformation A transformation
    virtual void applyTransformation(const Transformation& aTransformation) override;

    /// @brief              Constructs an undefined cuboid
    ///
    /// @code{.cpp}
    ///                     Cuboid cuboid = Cuboid::Undefined() ; // Undefined
    /// @endcode
    ///
    /// @return             Undefined cuboid
    static Cuboid Undefined();

    /// @brief              Constructs a a cube
    ///
    /// @code{.cpp}
    ///                     Cuboid cube = Cuboid::Cube({ 0.0, 0.0, 0.0 }, 1.0) ;
    /// @endcode
    ///
    /// @return             Cube
    static Cuboid Cube(const Point& aCenter, const Real& anExtent);

   private:
    Point center_;
    std::array<Vector3d, 3> axes_;
    std::array<Real, 3> extent_;
};

}  // namespace object
}  // namespace d3
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
