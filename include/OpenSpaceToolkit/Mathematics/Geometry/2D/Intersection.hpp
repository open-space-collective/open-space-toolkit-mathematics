/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_2D_Intersection__
#define __OpenSpaceToolkit_Mathematics_Geometry_2D_Intersection__

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>
#include <OpenSpaceToolkit/Core/Type/Unique.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Composite.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Line.hpp>
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

using ostk::core::type::Unique;
using ostk::core::type::Index;
using ostk::core::type::Size;
using ostk::core::container::Array;

using ostk::mathematics::geometry::d2::Object;
using ostk::mathematics::geometry::d2::object::Composite;

/// @brief                      2D intersection

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
        Segment,
        LineString,
        Polygon,
        Complex

    };

    /// @brief              Constructor
    ///
    /// @param              [in] anObjectArray An array of objects

    Intersection(Array<Unique<Object>>&& anObjectArray);

    /// @brief              Copy constructor
    ///
    /// @param              [in] anIntersection An intersection

    Intersection(const Intersection& anIntersection);

    /// @brief              Destructor

    ~Intersection();

    /// @brief              Copy assignment operator
    ///
    /// @param              [in] anIntersection An intersection
    /// @return             Reference to intersection

    Intersection& operator=(const Intersection& anIntersection);

    /// @brief              Equal to operator
    ///
    /// @param              [in] anIntersection An intersection
    /// @return             True if intersections are equal

    bool operator==(const Intersection& anIntersection) const;

    /// @brief              Not equal to operator
    ///
    /// @param              [in] anIntersection An intersection
    /// @return             True if intersections are not equal

    bool operator!=(const Intersection& anIntersection) const;

    /// @brief              Addition operator (intersection concatenation)
    ///
    ///                     Concatenate (merge) intersection with another intersection.
    ///
    /// @param              [in] anIntersection An intersection
    /// @return             Concatenated intersection

    Intersection operator+(const Intersection& anIntersection) const;

    /// @brief              Addition assignment operator (intersection concatenation)
    ///
    ///                     Concatenate (merge) intersection with another intersection.
    ///
    /// @param              [in] anIntersection An intersection
    /// @return             Reference to concatenated intersection

    Intersection& operator+=(const Intersection& anIntersection);

    /// @brief              Output stream operator
    ///
    /// @code
    ///                     std::cout << Intersection(...) ;
    /// @endcode
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] anIntersection An intersection
    /// @return             A reference to output stream

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Intersection& anIntersection);

    /// @brief              Check if intersection is defined
    ///
    /// @return             True if intersection is defined

    bool isDefined() const;

    /// @brief              Check if intersection is empty
    ///
    /// @return             True if intersection is empty

    bool isEmpty() const;

    /// @brief              Check if intersection is complex
    ///
    ///                     A complex intersection contains more than one object.
    ///
    /// @return             True if intersection is complex

    bool isComplex() const;

    /// @brief              Returns true if intersection can be converted to underlying object
    ///
    ///                     Only valid if the intersection only contains one object.
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
    /// @return             Reference to composite object

    const Composite& accessComposite() const;

    /// @brief              Get intersection type
    ///
    /// @return             Intersection type

    Intersection::Type getType() const;

    /// @brief              Constructs an undefined intersection
    ///
    /// @code
    ///                     Intersection intersection = Intersection::Undefined() ; // Undefined
    /// @endcode
    ///
    /// @return             Undefined intersection

    static Intersection Undefined();

    /// @brief              Constructs an empty intersection
    ///
    /// @code
    ///                     Intersection intersection = Intersection::Empty() ;
    /// @endcode
    ///
    /// @return             Empty intersection

    static Intersection Empty();

    /// @brief              Constructs a point intersection
    ///
    /// @code
    ///                     Intersection intersection = Intersection::Point(Point(0.0, 0.0)) ;
    /// @endcode
    ///
    /// @return             Point intersection

    static Intersection Point(const object::Point& aPoint);

    /// @brief              Constructs a point set intersection
    ///
    /// @code
    ///                     Intersection intersection = Intersection::PointSet({ Point(0.0, 0.0), Point(1.0, 0.0) }) ;
    /// @endcode
    ///
    /// @return             Point set intersection

    static Intersection PointSet(const object::PointSet& aPointSet);

    /// @brief              Constructs a line string intersection
    ///
    /// @code
    ///                     Intersection intersection = Intersection::LineString({ Point(0.0, 0.0), Point(1.0, 0.0),
    ///                     Point(0.0, 1.0) }) ;
    /// @endcode
    ///
    /// @return             Line string intersection

    static Intersection LineString(const object::LineString& aLineString);

    /// @brief              Constructs a line intersection
    ///
    /// @code
    ///                     Intersection intersection = Intersection::Line(Line({ 0.0, 0.0 }, { 1.0, 0.0 })) ;
    /// @endcode
    ///
    /// @return             Line intersection

    static Intersection Line(const object::Line& aLine);

    /// @brief              Constructs a segment intersection
    ///
    /// @code
    ///                     Intersection intersection = Intersection::Segment(Segment({ 0.0, 0.0 }, { 1.0, 0.0 })) ;
    /// @endcode
    ///
    /// @return             Segment intersection

    static Intersection Segment(const object::Segment& aSegment);

    /// @brief              Constructs a polygon intersection
    ///
    /// @code
    ///                     Intersection intersection = Intersection::Polygon(Polygon({ 0.0, 0.0 }, { 1.0, 0.0 })) ;
    /// @endcode
    ///
    /// @return             Polygon intersection

    static Intersection Polygon(const object::Polygon& aPolygon);

    /// @brief              Converts intersection type to string
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

}  // namespace d2
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
