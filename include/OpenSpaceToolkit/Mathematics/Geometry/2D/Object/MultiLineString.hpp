/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiLineString__
#define __OpenSpaceToolkit_Mathematics_Geometry_2D_Object_MultiLineString__

#include <unordered_set>

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Types/Index.hpp>
#include <OpenSpaceToolkit/Core/Types/Size.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/LineString.hpp>
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

using ostk::core::types::Index;
using ostk::core::types::Size;
using ostk::core::ctnr::Array;

using ostk::mathematics::object::Vector2d;
using ostk::mathematics::geometry::d2::Object;
using ostk::mathematics::geometry::d2::object::Point;
using ostk::mathematics::geometry::d2::object::LineString;

/// @brief                      Multi Line string

class MultiLineString : public Object
{
   public:
    typedef Array<LineString>::ConstIterator ConstIterator;

    /// @brief              Constructor
    ///
    /// @code
    ///                     MultiLineString multiLineString({ { 0.0, 0.0 }, { 0.0, 1.0 }, { 1.0, 0.0 } }) ;
    /// @endcode
    ///
    /// @param              [in] aPointArray A point array

    MultiLineString(const Array<LineString>& aLineStringArray);

    /// @brief              Clone multi line string
    ///
    /// @return             Pointer to cloned multi line string

    virtual MultiLineString* clone() const override;

    /// @brief              Equal to operator
    ///
    /// @param              [in] aMultiLineString A multi multi line string
    /// @return             True if multi multi line strings are equal

    bool operator==(const MultiLineString& aMultiLineString) const;

    /// @brief              Not equal to operator
    ///
    /// @param              [in] aMultiLineString A multi multi line string
    /// @return             True if multi multi line strings are not equal

    bool operator!=(const MultiLineString& aMultiLineString) const;

    /// @brief              Check if multi multi line string is defined
    ///
    /// @code
    ///                     MultiLineString(0.0, 0.0).isDefined() ; // True
    /// @endcode
    ///
    /// @return             True if multi multi line string is defined

    virtual bool isDefined() const override;

    /// @brief              Check if multi multi line string is empty
    ///
    /// @code
    ///                     MultiLineString::Empty().isEmpty() ; // True
    /// @endcode
    ///
    /// @return             True if multi multi line string is empty

    bool isEmpty() const;

    /// @brief              Get multi line string count
    ///
    /// @return             multi Line string count

    Size getLineStringCount() const;

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

    MultiLineString::ConstIterator begin() const;

    /// @brief              Get end const iterator
    ///
    /// @return             End const iterator

    MultiLineString::ConstIterator end() const;

    /// @brief              Apply transformation to multi line string
    ///
    /// @param              [in] aTransformation A transformation

    virtual void applyTransformation(const Transformation& aTransformation) override;

    /// @brief              Constructs an empty multi line string
    ///
    /// @code
    ///                     MultiLineString multiLineString = MultiLineString::Empty() ;
    /// @endcode
    ///
    /// @return             Empty multi line string

    static MultiLineString Empty();

   private:
    Array<LineString> lineStrings_;
};

}  // namespace object
}  // namespace d2
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
