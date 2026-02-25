/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Geometry_3D_Intersection__
#define __OpenSpaceToolkit_Mathematics_Geometry_3D_Intersection__

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>
#include <OpenSpaceToolkit/Core/Type/Unique.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Composite.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Cuboid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ellipsoid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Line.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/LineString.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Plane.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/PointSet.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Polygon.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Pyramid.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ray.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Segment.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Sphere.hpp>

namespace ostk
{
namespace mathematics
{
namespace geometry
{
namespace d3
{

using ostk::core::container::Array;
using ostk::core::type::Index;
using ostk::core::type::Size;
using ostk::core::type::Unique;

using ostk::mathematics::geometry::d3::Object;
using ostk::mathematics::geometry::d3::object::Composite;

/// @brief                      3D intersection
///
/// @code{.cpp}
///                             Intersection intersection = Intersection::Point(Point(0.0, 0.0, 0.0));
/// @endcode
class Intersection
{
   public:
    enum class Type
    {

        Undefined,
        Empty,
        Point,
        PointSet,
        Line,
        Ray,
        Segment,
        LineString,
        Polygon,
        Plane,
        Cuboid,
        Sphere,
        Ellipsoid,
        Pyramid,
        Complex

    };

    /// @brief              Constructor
    ///
    /// @code{.cpp}
    ///                     Array<Unique<Object>> objects ;
    ///                     objects.emplace_back(std::make_unique<object::Point>(0.0, 0.0, 0.0)) ;
    ///                     Intersection intersection = Intersection(std::move(objects)) ;
    /// @endcode
    ///
    /// @param              [in] anObjectArray An array of objects
    Intersection(Array<Unique<Object>>&& anObjectArray);

    /// @brief              Copy constructor
    ///
    /// @code{.cpp}
    ///                     Intersection intersection = Intersection::Point(object::Point(0.0, 0.0, 0.0)) ;
    ///                     Intersection copy = Intersection(intersection) ;
    /// @endcode
    ///
    /// @param              [in] anIntersection An intersection
    Intersection(const Intersection& anIntersection);

    /// @brief              Destructor
    ///
    /// @code{.cpp}
    ///                     Intersection* intersectionPtr = new Intersection(Intersection::Empty()) ;
    ///                     delete intersectionPtr ;
    /// @endcode
    ~Intersection();

    /// @brief              Copy assignment operator
    ///
    /// @code{.cpp}
    ///                     Intersection intersectionA = Intersection::Empty() ;
    ///                     Intersection intersectionB = Intersection::Point(object::Point(0.0, 0.0, 0.0)) ;
    ///                     intersectionA = intersectionB ;
    /// @endcode
    ///
    /// @param              [in] anIntersection An intersection
    /// @return             Reference to intersection
    Intersection& operator=(const Intersection& anIntersection);

    /// @brief              Equal to operator
    ///
    /// @code{.cpp}
    ///                     Intersection intersection = Intersection::Empty() ;
    ///                     intersection == intersection ; // True
    /// @endcode
    ///
    /// @param              [in] anIntersection An intersection
    /// @return             True if intersections are equal
    bool operator==(const Intersection& anIntersection) const;

    /// @brief              Not equal to operator
    ///
    /// @code{.cpp}
    ///                     Intersection intersectionA = Intersection::Empty() ;
    ///                     Intersection intersectionB = Intersection::Point(object::Point(0.0, 0.0, 0.0)) ;
    ///                     intersectionA != intersectionB ; // True
    /// @endcode
    ///
    /// @param              [in] anIntersection An intersection
    /// @return             True if intersections are not equal
    bool operator!=(const Intersection& anIntersection) const;

    /// @brief              Addition operator (intersection concatenation)
    ///
    ///                     Concatenate (merge) intersection with another intersection.
    ///
    /// @code{.cpp}
    ///                     Intersection intersectionA = Intersection::Point(object::Point(0.0, 0.0, 0.0)) ;
    ///                     Intersection intersectionB = Intersection::Point(object::Point(1.0, 0.0, 0.0)) ;
    ///                     Intersection merged = intersectionA + intersectionB ;
    /// @endcode
    ///
    /// @param              [in] anIntersection An intersection
    /// @return             Concatenated intersection
    Intersection operator+(const Intersection& anIntersection) const;

    /// @brief              Addition assignment operator (intersection concatenation)
    ///
    ///                     Concatenate (merge) intersection with another intersection.
    ///
    /// @code{.cpp}
    ///                     Intersection intersectionA = Intersection::Point(object::Point(0.0, 0.0, 0.0)) ;
    ///                     Intersection intersectionB = Intersection::Point(object::Point(1.0, 0.0, 0.0)) ;
    ///                     intersectionA += intersectionB ;
    /// @endcode
    ///
    /// @param              [in] anIntersection An intersection
    /// @return             Reference to concatenated intersection
    Intersection& operator+=(const Intersection& anIntersection);

    /// @brief              Output stream operator
    ///
    /// @code{.cpp}
    ///                     std::cout << Intersection(...) ;
    /// @endcode
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] anIntersection An intersection
    /// @return             A reference to output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Intersection& anIntersection);

    /// @brief              Check if intersection is defined
    ///
    /// @code{.cpp}
    ///                     Intersection intersection = Intersection::Empty() ;
    ///                     intersection.isDefined() ; // True
    /// @endcode
    ///
    /// @return             True if intersection is defined
    bool isDefined() const;

    /// @brief              Check if intersection is empty
    ///
    /// @code{.cpp}
    ///                     Intersection intersection = Intersection::Empty() ;
    ///                     intersection.isEmpty() ; // True
    /// @endcode
    ///
    /// @return             True if intersection is empty
    bool isEmpty() const;

    /// @brief              Check if intersection is complex
    ///
    ///                     A complex intersection contains more than one object.
    ///
    /// @code{.cpp}
    ///                     Intersection intersection = Intersection::Point(object::Point(0.0, 0.0, 0.0)) ;
    ///                     intersection.isComplex() ; // False
    /// @endcode
    ///
    /// @return             True if intersection is complex
    bool isComplex() const;

    /// @brief              Returns true if intersection can be converted to underlying object
    ///
    ///                     Only valid if the intersection only contains one object.
    ///
    /// @code{.cpp}
    ///                     Intersection intersection = Intersection::Point(object::Point(0.0, 0.0, 0.0)) ;
    ///                     bool isPoint = intersection.is<object::Point>() ; // True
    /// @endcode
    ///
    /// @return             True if intersection can be converted to underlying object
    template <class Type>
    bool is() const
    {
        if (!this->isDefined())
        {
            throw ostk::core::error::runtime::Undefined("Intersection");
        }

        return composite_.is<Type>();
    }

    /// @brief              Access intersection as its underlying object
    ///
    ///                     Only valid if the intersection only contains one object.
    ///
    /// @code{.cpp}
    ///                     Intersection intersection = Intersection::Point(object::Point(0.0, 0.0, 0.0)) ;
    ///                     const object::Point& point = intersection.as<object::Point>() ;
    /// @endcode
    ///
    /// @return             Reference to underlying object
    template <class Type>
    const Type& as() const
    {
        if (!this->isDefined())
        {
            throw ostk::core::error::runtime::Undefined("Intersection");
        }

        return composite_.as<Type>();
    }

    /// @brief              Access composite object
    ///
    /// @code{.cpp}
    ///                     Intersection intersection = Intersection::Point(object::Point(0.0, 0.0, 0.0)) ;
    ///                     const Composite& composite = intersection.accessComposite() ;
    /// @endcode
    ///
    /// @return             Reference to composite object
    const Composite& accessComposite() const;

    /// @brief              Get intersection type
    ///
    /// @code{.cpp}
    ///                     Intersection intersection = Intersection::Point(object::Point(0.0, 0.0, 0.0)) ;
    ///                     Intersection::Type type = intersection.getType() ; // Intersection::Type::Point
    /// @endcode
    ///
    /// @return             Intersection type
    Intersection::Type getType() const;

    /// @brief              Constructs an undefined intersection
    ///
    /// @code{.cpp}
    ///                     Intersection intersection = Intersection::Undefined() ; // Undefined
    /// @endcode
    ///
    /// @return             Undefined intersection
    static Intersection Undefined();

    /// @brief              Constructs an empty intersection
    ///
    /// @code{.cpp}
    ///                     Intersection intersection = Intersection::Empty() ;
    /// @endcode
    ///
    /// @return             Empty intersection
    static Intersection Empty();

    /// @brief              Constructs a point intersection
    ///
    /// @code{.cpp}
    ///                     Intersection intersection = Intersection::Point(Point(0.0, 0.0, 0.0)) ;
    /// @endcode
    ///
    /// @return             Point intersection
    static Intersection Point(const object::Point& aPoint);

    /// @brief              Constructs a point set intersection
    ///
    /// @code{.cpp}
    ///                     Intersection intersection = Intersection::PointSet({ Point(0.0, 0.0, 0.0), Point(1.0, 0.0,
    ///                     0.0) }) ;
    /// @endcode
    ///
    /// @return             Point set intersection
    static Intersection PointSet(const object::PointSet& aPointSet);

    /// @brief              Constructs a line string intersection
    ///
    /// @code{.cpp}
    ///                     Intersection intersection = Intersection::LineString({ Point(0.0, 0.0, 0.0), Point(1.0, 0.0,
    ///                     0.0), Point(1.0, 0.0, 1.0) }) ;
    /// @endcode
    ///
    /// @return             Line string intersection
    static Intersection LineString(const object::LineString& aLineString);

    /// @brief              Constructs a line intersection
    ///
    /// @code{.cpp}
    ///                     Intersection intersection = Intersection::Line(Line({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 })) ;
    /// @endcode
    ///
    /// @return             Line intersection
    static Intersection Line(const object::Line& aLine);

    /// @brief              Constructs a ray intersection
    ///
    /// @code{.cpp}
    ///                     Intersection intersection = Intersection::Ray(Ray({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 })) ;
    /// @endcode
    ///
    /// @return             Ray intersection
    static Intersection Ray(const object::Ray& aRay);

    /// @brief              Constructs a segment intersection
    ///
    /// @code{.cpp}
    ///                     Intersection intersection = Intersection::Segment(Segment({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0
    ///                     })) ;
    /// @endcode
    ///
    /// @return             Segment intersection
    static Intersection Segment(const object::Segment& aSegment);

    /// @brief              Converts intersection type to string
    ///
    /// @code{.cpp}
    ///                     String str = Intersection::StringFromType(Intersection::Type::Point) ; // "Point"
    /// @endcode
    ///
    /// @return             String
    static String StringFromType(const Intersection::Type& aType);

   private:
    Intersection::Type type_;

    Composite composite_;

    Intersection();

    Intersection(const Intersection::Type& aType, const Array<Unique<Object>>& anObjectArray);

    static Intersection::Type TypeFromObjects(const Array<Unique<Object>>& anObjectArray);

    static Intersection::Type TypeFromObjects(const Unique<Object>& anObjectUPtr);
};

}  // namespace d3
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
