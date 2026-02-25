/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Pyramid__
#define __OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Pyramid__

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ray.hpp>

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

using ostk::mathematics::geometry::d3::Intersection;
using ostk::mathematics::geometry::d3::Object;
using ostk::mathematics::geometry::d3::object::Point;
using ostk::mathematics::geometry::d3::object::Polygon;
using ostk::mathematics::geometry::d3::object::Ray;

#define DEFAULT_ONLY_IN_SIGHT false
#define DEFAULT_DISCRETIZATION_LEVEL 40

class Line;
class Ray;
class Segment;
class Plane;
class Polygon;
class Sphere;
class Ellipsoid;

/// @brief                      Pyramid
///
///                             A pyramid is a polyhedron formed by connecting a polygonal base and a point, called the
///                             apex. Each base edge and apex form a triangle, called a lateral face.
///
/// @code{.cpp}
///                             Pyramid pyramid(polygon, Point(0.0, 0.0, 1.0));
/// @endcode
///
/// @ref                        https://en.wikipedia.org/wiki/Pyramid_(geometry)
class Pyramid : public Object
{
   public:
    /// @brief              Constructor
    ///
    /// @code{.cpp}
    ///                     Polygon base = ... ;
    ///                     Point apex = { 0.0, 0.0, 1.0 } ;
    ///                     Pyramid pyramid = { base, apex } ;
    /// @endcode
    ///
    /// @param              [in] aBase A pyramid base
    /// @param              [in] anApex A pyramid apex
    Pyramid(const Polygon& aBase, const Point& anApex);

    /// @brief              Clone pyramid
    ///
    /// @code{.cpp}
    ///                     Pyramid* clonePtr = pyramid.clone() ;
    /// @endcode
    ///
    /// @return             Pointer to cloned pyramid
    virtual Pyramid* clone() const override;

    /// @brief              Equal to operator
    ///
    /// @code{.cpp}
    ///                     Pyramid pyramid = ... ;
    ///                     pyramid == pyramid ; // True
    /// @endcode
    ///
    /// @param              [in] aPyramid A pyramid
    /// @return             True if pyramids are equal
    bool operator==(const Pyramid& aPyramid) const;

    /// @brief              Not equal to operator
    ///
    /// @code{.cpp}
    ///                     Pyramid pyramidA = ... ;
    ///                     Pyramid pyramidB = ... ;
    ///                     pyramidA != pyramidB ; // True
    /// @endcode
    ///
    /// @param              [in] aPyramid A pyramid
    /// @return             True if pyramids are not equal
    bool operator!=(const Pyramid& aPyramid) const;

    /// @brief              Check if pyramid is defined
    ///
    /// @code{.cpp}
    ///                     Pyramid pyramid = ... ;
    ///                     pyramid.isDefined() ; // True
    /// @endcode
    ///
    /// @return             True if pyramid is defined
    virtual bool isDefined() const override;

    /// @brief              Check if pyramid intersects sphere
    ///
    /// @code{.cpp}
    ///                     Pyramid pyramid = ... ;
    ///                     Sphere sphere = ... ;
    ///                     pyramid.intersects(sphere) ;
    /// @endcode
    ///
    /// @param              [in] aSphere A sphere
    /// @param              [in] aDiscretizationLevel (optional) The polygonal discretization level
    /// @return             True if pyramid intersects sphere
    bool intersects(const Sphere& aSphere, const Size aDiscretizationLevel = DEFAULT_DISCRETIZATION_LEVEL) const;

    /// @brief              Check if pyramid intersects ellipsoid
    ///
    /// @code{.cpp}
    ///                     Pyramid pyramid = ... ;
    ///                     Ellipsoid ellipsoid = ... ;
    ///                     pyramid.intersects(ellipsoid) ;
    /// @endcode
    ///
    /// @param              [in] anEllipsoid An ellipsoid
    /// @param              [in] aDiscretizationLevel (optional) The polygonal discretization level
    /// @return             True if pyramid intersects ellipsoid
    bool intersects(const Ellipsoid& anEllipsoid, const Size aDiscretizationLevel = DEFAULT_DISCRETIZATION_LEVEL) const;

    /// @brief              Check if pyramid contains point
    ///
    /// @code{.cpp}
    ///                     Pyramid pyramid = ... ;
    ///                     Point point = ... ;
    ///                     pyramid.contains(point) ;
    /// @endcode
    ///
    /// @param              [in] aPoint A point
    /// @return             True if pyramid contains point
    bool contains(const Point& aPoint) const;

    /// @brief              Check if pyramid contains point set
    ///
    /// @code{.cpp}
    ///                     Pyramid pyramid = ... ;
    ///                     PointSet pointSet = ... ;
    ///                     pyramid.contains(pointSet) ;
    /// @endcode
    ///
    /// @param              [in] aPointSet A point set
    /// @return             True if pyramid contains point set
    bool contains(const PointSet& aPointSet) const;

    /// @brief              Check if pyramid contains segment
    ///
    /// @code{.cpp}
    ///                     Pyramid pyramid = ... ;
    ///                     Segment segment = ... ;
    ///                     pyramid.contains(segment) ;
    /// @endcode
    ///
    /// @param              [in] aSegment A segment
    /// @return             True if pyramid contains segment
    bool contains(const Segment& aSegment) const;

    /// @brief              Check if pyramid contains ellipsoid
    ///
    /// @code{.cpp}
    ///                     Pyramid pyramid = ... ;
    ///                     Ellipsoid ellipsoid = ... ;
    ///                     pyramid.contains(ellipsoid) ;
    /// @endcode
    ///
    /// @param              [in] anEllipsoid An ellipsoid
    /// @return             True if pyramid contains ellipsoid
    bool contains(const Ellipsoid& anEllipsoid) const;

    /// @brief              Get pyramid base
    ///
    /// @code{.cpp}
    ///                     Pyramid pyramid = ... ;
    ///                     Polygon base = pyramid.getBase() ;
    /// @endcode
    ///
    /// @return             Pyramid base
    Polygon getBase() const;

    /// @brief              Get pyramid apex
    ///
    /// @code{.cpp}
    ///                     Pyramid pyramid = ... ;
    ///                     Point apex = pyramid.getApex() ;
    /// @endcode
    ///
    /// @return             Pyramid apex
    Point getApex() const;

    /// @brief              Get number of lateral faces
    ///
    /// @code{.cpp}
    ///                     Pyramid pyramid = ... ;
    ///                     Size count = pyramid.getLateralFaceCount() ;
    /// @endcode
    ///
    /// @return             Number of lateral faces
    Size getLateralFaceCount() const;

    /// @brief              Get lateral face at index
    ///
    /// @code{.cpp}
    ///                     Pyramid pyramid = ... ;
    ///                     Polygon lateralFace = pyramid.getLateralFaceAt(0) ;
    /// @endcode
    ///
    /// @param              [in] aLateralFaceIndex A lateral face index
    /// @return             Lateral face
    Polygon getLateralFaceAt(const Index aLateralFaceIndex) const;

    /// @brief              Get rays of lateral face at index
    ///
    /// @code{.cpp}
    ///                     Pyramid pyramid = ... ;
    ///                     Array<Ray> rays = pyramid.getRaysOfLateralFaceAt(0, 2) ;
    /// @endcode
    ///
    /// @param              [in] aLateralFaceIndex A lateral face index
    /// @param              [in] aRayCount A number of rays (at least 2)
    /// @return             Array of rays
    Array<Ray> getRaysOfLateralFaceAt(const Index aLateralFaceIndex, const Size aRayCount = 2) const;

    /// @brief              Get rays of lateral faces
    ///
    /// @code{.cpp}
    ///                     Pyramid pyramid = ... ;
    ///                     Array<Ray> rays = pyramid.getRaysOfLateralFaces() ;
    /// @endcode
    ///
    /// @param              [in] aRayCount A number of rays (at least face count)
    /// @return             Array of rays
    Array<Ray> getRaysOfLateralFaces(const Size aRayCount = 0) const;

    /// @brief              Compute intersection of pyramid with sphere
    ///
    /// @code{.cpp}
    ///                     Pyramid pyramid = ... ;
    ///                     Sphere sphere = Sphere({ 0.0, 0.0, 0.0 }, 1.0) ;
    ///                     Intersection intersection = pyramid.intersectionWith(sphere) ;
    /// @endcode
    ///
    /// @param              [in] aSphere A sphere
    /// @param              [in] onlyInSight (optional) If true, only return intersection points that are in sight
    /// @param              [in] aDiscretizationLevel (optional) The polygonal discretization level
    /// @return             Intersection of pyramid with sphere
    Intersection intersectionWith(
        const Sphere& aSphere,
        const bool onlyInSight = DEFAULT_ONLY_IN_SIGHT,
        const Size aDiscretizationLevel = DEFAULT_DISCRETIZATION_LEVEL
    ) const;

    /// @brief              Compute intersection of pyramid with ellipsoid
    ///
    /// @code{.cpp}
    ///                     Pyramid pyramid = ... ;
    ///                     Ellipsoid ellipsoid = Ellipsoid(Point::Origin(), 1.0, 2.0, 3.0) ;
    ///                     Intersection intersection = pyramid.intersectionWith(ellipsoid) ;
    /// @endcode
    ///
    /// @param              [in] anEllipsoid An ellipsoid
    /// @param              [in] onlyInSight (optional) If true, only return intersection points that are in sight
    /// @param              [in] aDiscretizationLevel (optional) The polygonal discretization level
    /// @return             Intersection of pyramid with ellipsoid
    Intersection intersectionWith(
        const Ellipsoid& anEllipsoid,
        const bool onlyInSight = DEFAULT_ONLY_IN_SIGHT,
        const Size aDiscretizationLevel = DEFAULT_DISCRETIZATION_LEVEL
    ) const;

    /// @brief              Print pyramid
    ///
    /// @code{.cpp}
    ///                     Pyramid pyramid = ... ;
    ///                     pyramid.print(std::cout, true) ;
    /// @endcode
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] (optional) displayDecorators If true, display decorators
    virtual void print(std::ostream& anOutputStream, bool displayDecorators = true) const override;

    /// @brief              Apply transformation to pyramid
    ///
    /// @code{.cpp}
    ///                     Pyramid pyramid = ... ;
    ///                     pyramid.applyTransformation(Transformation::Translation({ 1.0, 0.0, 0.0 })) ;
    /// @endcode
    ///
    /// @param              [in] aTransformation A transformation
    virtual void applyTransformation(const Transformation& aTransformation) override;

    /// @brief              Constructs an undefined pyramid
    ///
    /// @code{.cpp}
    ///                     Pyramid pyramid = Pyramid::Undefined() ;
    /// @endcode
    ///
    /// @return             Undefined pyramid
    static Pyramid Undefined();

   private:
    Polygon base_;
    Point apex_;
};

}  // namespace object
}  // namespace d3
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
