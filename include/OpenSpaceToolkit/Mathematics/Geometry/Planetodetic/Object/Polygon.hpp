/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Polygon__
#define __OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Polygon__

#include <memory>

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/Planetodetic/Object.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/Planetodetic/Object/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/Planetodetic/Object/Point.hpp>

namespace ostk
{
namespace mathematics
{
namespace geometry
{
namespace planetodetic
{
namespace object
{

using ostk::core::container::Array;
using ostk::core::type::Integer;
using ostk::core::type::Size;
using ostk::core::type::String;

using ostk::mathematics::geometry::planetodetic::Object;
using ostk::mathematics::geometry::planetodetic::object::Ellipsoid;
using ostk::mathematics::geometry::planetodetic::object::Point;

#define DEFAULT_PRECISION Integer::Undefined()

/// @brief                      Polygon defined on a reference ellipsoid.
///
///                             The segments connecting both outer ring (and inner rings vertices if any)
///                             are geodesics on the reference ellipsoid. The "inside" of the polygon is defined
///                             as the area to the left when traversing the vertices in a counter-clockwise direction.
///
/// @ref                        https://en.wikipedia.org/wiki/Polygon

class Polygon : public Object
{
   public:
    typedef Point Vertex;

    /// @brief              Copy constructor
    ///
    /// @param              [in] aPolygon A polygon

    Polygon(const Polygon& aPolygon);

    /// @brief              Destructor

    ~Polygon();

    /// @brief              Copy assignment operator
    ///
    /// @param              [in] aPolygon A polygon
    /// @return             Reference to polygon

    Polygon& operator=(const Polygon& aPolygon);

    /// @brief              Clone polygon
    ///
    /// @return             Pointer to cloned polygon

    virtual Polygon* clone() const override;

    /// @brief              Equal to operator
    ///
    /// @param              [in] aPolygon A polygon
    /// @return             True if polygons are equal

    bool operator==(const Polygon& aPolygon) const;

    /// @brief              Not equal to operator
    ///
    /// @param              [in] aPolygon A polygon
    /// @return             True if polygons are not equal

    bool operator!=(const Polygon& aPolygon) const;

    /// @brief              Check if polygon is defined
    ///
    /// @code
    ///                     Polygon polygon = ... ;
    ///                     polygon.isDefined() ; // True
    /// @endcode
    ///
    /// @return             True if polygon is defined

    virtual bool isDefined() const override;

    /// @brief              Check if polygon contains point
    ///
    /// @code
    ///                     Polygon polygon = ... ;
    ///                     Point point = ... ;
    ///                     polygon.contains(point) ;
    /// @endcode
    ///
    /// @param              [in] aPoint A point
    /// @return             True if polygon contains point

    bool contains(const Point& aPoint) const;

    /// @brief              Get reference ellipsoid
    ///
    /// @code
    ///                     Polygon polygon = ... ;
    ///                     Ellipsoid ellipsoid = polygon.getEllipsoid() ;
    /// @endcode
    ///
    /// @return             Reference ellipsoid

    Ellipsoid getEllipsoid() const;

    /// @brief              Get number of vertices
    ///
    /// @code
    ///                     Polygon polygon = ... ;
    ///                     Size vertexCount = polygon.getVertexCount() ;
    /// @endcode
    ///
    /// @return             Number of vertices

    Size getVertexCount() const;

    /// @brief              Get array of vertices
    ///
    /// @code
    ///                     Polygon polygon = ... ;
    ///                     Array<Point> vertices = polygon.getVertices() ;
    /// @endcode
    ///
    /// @return             Array of vertices

    Array<Point> getVertices() const;

    /// @brief              Get string representation
    ///
    /// @param              [in] aFormat A format
    /// @param              [in] aPrecision A precision
    /// @return             String representation

    virtual String toString(
        const Object::Format& aFormat = Object::Format::Standard, const Integer& aPrecision = DEFAULT_PRECISION
    ) const override;

    /// @brief              Print polygon
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] (optional) displayDecorators If true, display decorators

    virtual void print(std::ostream& anOutputStream, bool displayDecorators = true) const override;

    /// @brief              Construct a simple polygon from its outer ring vertices
    ///
    /// @ref                https://en.wikipedia.org/wiki/Simple_polygon
    ///
    /// @code
    ///                     Ellipsoid ellipsoid = Ellipsoid::Sphere(6378137.0);
    ///                     Array<Point> outerRing = {
    ///                         Point(Angle::Degrees(-1.0), Angle::Degrees(-1.0)),
    ///                         Point(Angle::Degrees(-1.0), Angle::Degrees(1.0)),
    ///                         Point(Angle::Degrees(1.0), Angle::Degrees(1.0)),
    ///                         Point(Angle::Degrees(1.0), Angle::Degrees(-1.0))
    ///                     };
    ///                     Polygon polygon = Polygon::Simple(ellipsoid, outerRing);
    /// @endcode
    ///
    /// @param              [in] anEllipsoid A reference ellipsoid
    /// @param              [in] anOuterRing An array of vertices (planetodetic points). The "inside" of the polygon is
    ///                     defined as the area to the left when traversing the outer ring vertices in a
    ///                     counter-clockwise direction.
    ///
    /// @return             Polygon

    static Polygon Simple(const Ellipsoid& anEllipsoid, const Array<Point>& anOuterRing);

    /// @brief              Construct an undefined polygon
    ///
    /// @code
    ///                     Polygon polygon = Polygon::Undefined() ; // Undefined
    /// @endcode
    ///
    /// @return             Undefined polygon

    static Polygon Undefined();

   private:
    /// @brief              Constructor
    ///
    /// @param              [in] anEllipsoid A reference ellipsoid
    /// @param              [in] anOuterRing An array of vertices (planetodetic points)

    Polygon(const Ellipsoid& anEllipsoid, const Array<Point>& anOuterRing);

    class Impl;

    Ellipsoid ellipsoid_;
    Array<Point> outerRing_;
    std::unique_ptr<Impl> implUPtr_;

    void initializeBoostGeometry();
};

}  // namespace object
}  // namespace planetodetic
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
