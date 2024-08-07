/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_2D_Object_LineString__
#define __OpenSpaceToolkit_Mathematics_Geometry_2D_Object_LineString__

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Point.hpp>

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
using ostk::core::type::Index;
using ostk::core::type::Size;

using ostk::mathematics::geometry::d2::Object;
using ostk::mathematics::geometry::d2::object::Point;
using ostk::mathematics::object::Vector2d;

class Segment;

/// @brief                      Line string
///
///                             A line string is a connected series of line segments.
///
/// @ref                        https://en.wikipedia.org/wiki/Polygonal_chain

class LineString : public Object
{
   public:
    typedef Array<Point>::ConstIterator ConstIterator;

    /// @brief              Constructor
    ///
    /// @code
    ///                     LineString lineString({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 0.0 } }) ;
    /// @endcode
    ///
    /// @param              [in] aPointArray A point array

    LineString(const Array<Point>& aPointArray);

    /// @brief              Clone line string
    ///
    /// @return             Pointer to cloned line string

    virtual LineString* clone() const override;

    /// @brief              Equal to operator
    ///
    /// @param              [in] aLineString A line string
    /// @return             True if line strings are equal

    bool operator==(const LineString& aLineString) const;

    /// @brief              Not equal to operator
    ///
    /// @param              [in] aLineString A line string
    /// @return             True if line strings are not equal

    bool operator!=(const LineString& aLineString) const;

    /// @brief              Check if line string is defined
    ///
    /// @code
    ///                     LineString(0.0, 0.0).isDefined() ; // True
    /// @endcode
    ///
    /// @return             True if line string is defined

    virtual bool isDefined() const override;

    /// @brief              Check if line string is empty
    ///
    /// @code
    ///                     LineString::Empty().isEmpty() ; // True
    /// @endcode
    ///
    /// @return             True if line string is empty

    bool isEmpty() const;

    /// @brief              Check if line string contains a point
    ///
    /// @code
    ///                     LineString({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 0.0 } }).contains({ 0.0, 0.5 }) ; // True
    /// @endcode
    ///
    /// @return             True if line string contains a point

    bool contains(const Point& aPoint) const;

    /// @brief              Check if line string is near another line string
    ///
    /// @code
    ///                     LineString({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 0.0 } }).isNear(LineString({ { 0.0, 0.0 }, {
    ///                     0.0, 1.0 }, { 1.0, 1e-15 } }), 1e-15) ; // True
    /// @endcode
    ///
    /// @param              [in] aLineString A line string
    /// @param              [in] aTolerance A tolerance
    /// @return             True if line string is near another line string

    bool isNear(const LineString& aLineString, const Real& aTolerance) const;

    /// @brief              Get point array
    ///
    /// @return             Point array

    const Array<Point>& getPointArray() const;

    /// @brief              Access point at index
    ///
    /// @brief              [in] anIndex A point index
    /// @return             Reference to point at index

    const Point& accessPointAt(const Index& anIndex) const;

    /// @brief              Get point count
    ///
    /// @return             Point count

    Size getPointCount() const;

    /// @brief              Get point closest to another point
    ///
    /// @param              [in] aPoint A point
    /// @return             Closest point

    Point getPointClosestTo(const Point& aPoint) const;

    /// @brief              Get string representation
    ///
    /// @param              [in] aFormat A format
    /// @return             String representation

    virtual String toString(
        const Object::Format& aFormat = Object::Format::Standard, const Integer& aPrecision = Integer::Undefined()
    ) const override;

    /// @brief              Print point
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] (optional) displayDecorators If true, display decorators

    virtual void print(std::ostream& anOutputStream, bool displayDecorators = true) const override;

    /// @brief              Get begin const iterator
    ///
    /// @return             Begin const iterator

    LineString::ConstIterator begin() const;

    /// @brief              Get end const iterator
    ///
    /// @return             End const iterator

    LineString::ConstIterator end() const;

    /// @brief              Apply transformation to line string
    ///
    /// @param              [in] aTransformation A transformation

    virtual void applyTransformation(const Transformation& aTransformation) override;

    /// @brief              Constructs an empty line string
    ///
    /// @code
    ///                     LineString lineString = LineString::Empty() ;
    /// @endcode
    ///
    /// @return             Empty line string

    static LineString Empty();

    /// @brief              Constructs a line string from a segment
    ///
    /// @code
    ///                     Segment segment = { { 0.0, 0.0 }, { 0.0, 1.0 } } ;
    ///                     LineString lineString = LineString::Segment(segment) ;
    /// @endcode
    ///
    /// @return             Line string

    static LineString Segment(const object::Segment& aSegment);

   private:
    Array<Point> points_;
};

}  // namespace object
}  // namespace d2
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
