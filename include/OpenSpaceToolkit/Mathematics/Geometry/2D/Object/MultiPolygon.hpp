/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon__
#define __OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiPolygon__

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>
#include <OpenSpaceToolkit/Core/Type/Unique.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/LineString.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/PointSet.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Segment.hpp>

namespace ostk
{
namespace mathematics
{
namespace geometry
{
namespace d2
{
namespace object
{

using ostk::core::container::Array;
using ostk::core::container::Index;
using ostk::core::container::Size;
using ostk::core::type::Unique;

using ostk::mathematics::geometry::d2::Object;
using ostk::mathematics::geometry::d2::object::LineString;
using ostk::mathematics::geometry::d2::object::Point;
using ostk::mathematics::geometry::d2::object::Segment;

using Polygon2d = ostk::mathematics::geometry::d2::object::Polygon;

/// @brief                      Multi-polygon

class MultiPolygon : public Object
{
   public:
    typedef Array<Polygon2d>::ConstIterator ConstIterator;

    /// @brief              Constructor
    ///
    /// @param              [in] aPolygonArray An array of polygons

    MultiPolygon(const Array<Polygon2d>& aPolygonArray = Array<Polygon2d>::Empty());

    /// @brief              Copy constructor
    ///
    /// @param              [in] aMultiPolygon A multi-polygon

    MultiPolygon(const MultiPolygon& aMultiPolygon);

    /// @brief              Destructor (virtual)

    virtual ~MultiPolygon() override;

    /// @brief              Copy assignment operator
    ///
    /// @param              [in] aMultiPolygon A multi-polygon
    /// @return             Reference to multi-polygon

    MultiPolygon& operator=(const MultiPolygon& aMultiPolygon);

    /// @brief              Clone multi-polygon
    ///
    /// @return             Pointer to cloned multi-polygon

    virtual MultiPolygon* clone() const override;

    /// @brief              Equal to operator
    ///
    /// @param              [in] aMultiPolygon A multi-polygon
    /// @return             True if multi-polygons are equal

    bool operator==(const MultiPolygon& aMultiPolygon) const;

    /// @brief              Not equal to operator
    ///
    /// @param              [in] aMultiPolygon A multi-polygon
    /// @return             True if multi-polygons are not equal

    bool operator!=(const MultiPolygon& aMultiPolygon) const;

    /// @brief              Check if multi-polygon is defined
    ///
    /// @return             True if multi-polygon is defined

    virtual bool isDefined() const override;

    /// @brief              Check if multi-polygon contains point
    ///
    /// @code
    ///                     MultiPolygon multiPolygon = ... ;
    ///                     Point point = ... ;
    ///                     multiPolygon.contains(point) ;
    /// @endcode
    ///
    /// @param              [in] aPoint A point
    /// @return             True if multi-polygon contains point

    bool contains(const Point& aPoint) const;

    /// @brief              Check if multi-polygon contains point set
    ///
    /// @code
    ///                     MultiPolygon multiPolygon = ... ;
    ///                     PointSet pointSet = ... ;
    ///                     multiPolygon.contains(pointSet) ;
    /// @endcode
    ///
    /// @param              [in] aPointSet A point set
    /// @return             True if multi-polygon contains point set

    bool contains(const PointSet& aPointSet) const;

    /// @brief              Get number of polygons
    ///
    /// @return             Number of polygons

    Size getPolygonCount() const;

    /// @brief              Get polygons
    ///
    /// @return             Array of polygons

    Array<Polygon2d> getPolygons() const;

    /// @brief              Get multi-polygon convex hull
    ///
    ///                     https://en.wikipedia.org/wiki/Convex_hull
    ///
    /// @return             Multi-polygon convex hull

    Polygon2d getConvexHull() const;

    /// @brief              Compute intersection of multi-polygon with multi-polygon
    ///
    /// @param              [in] aMultiPolygon A multi-polygon
    /// @return             A multi-polygon

    MultiPolygon unionWith(const MultiPolygon& aMultiPolygon) const;

    /// @brief              Get string representation
    ///
    /// @param              [in] aFormat A format
    /// @return             String representation

    virtual String toString(
        const Object::Format& aFormat = Object::Format::Standard, const Integer& aPrecision = Integer::Undefined()
    ) const override;

    /// @brief              Print multi-polygon
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] (optional) displayDecorators If true, display decorators

    virtual void print(std::ostream& anOutputStream, bool displayDecorators = true) const override;

    /// @brief              Get begin const iterator over polygons
    ///
    /// @return             Const iterator

    MultiPolygon::ConstIterator begin() const;

    /// @brief              Get end const iterator over polygons
    ///
    /// @return             Const iterator

    MultiPolygon::ConstIterator end() const;

    /// @brief              Apply transformation to multi-polygon
    ///
    /// @param              [in] aTransformation A transformation

    virtual void applyTransformation(const Transformation& aTransformation) override;

    /// @brief              Constructs an undefined multi-polygon
    ///
    /// @code
    ///                     MultiPolygon multiPolygon = MultiPolygon::Undefined() ; // Undefined
    /// @endcode
    ///
    /// @return             Undefined multi-polygon

    static MultiPolygon Undefined();

    /// @brief              Constructs a multi-polygon from a polygon
    ///
    /// @code
    ///                     MultiPolygon multiPolygon = MultiPolygon::Polygon(polygon) ;
    /// @endcode
    ///
    /// @return             Multi-polygon

    static MultiPolygon Polygon(const Polygon2d& aPolygon);

   private:
    class Impl;

    Unique<MultiPolygon::Impl> implUPtr_;
};

}  // namespace object
}  // namespace d2
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
