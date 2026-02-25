/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Geometry_2D_Object_PointSet__
#define __OpenSpaceToolkit_Mathematics_Geometry_2D_Object_PointSet__

#include <unordered_set>

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

/// @brief                      Point set
///
/// @code{.cpp}
///                             PointSet pointSet({ { 0.0, 0.0 }, { 1.0, 0.0 } }) ;
/// @endcode
class PointSet : public Object
{
   public:
    /// @brief              Point hasher
    ///
    /// @code{.cpp}
    ///                     PointSet::Hasher hasher ;
    ///                     std::size_t hash = hasher(Point(0.0, 0.0)) ;
    /// @endcode
    ///
    /// @ref                https://wjngkoh.wordpress.com/2015/03/04/c-hash-function-for-eigen-matrix-and-vector/
    struct Hasher
    {
        std::size_t operator()(const Point& aPoint) const
        {
            size_t seed = 0;

            for (size_t i = 0; i < 2; ++i)
            {
                auto elem = *(aPoint.asVector().data() + i);

                seed ^= std::hash<double>()(elem) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }

            return seed;
        }
    };

    typedef std::unordered_set<Point, PointSet::Hasher> Container;
    typedef PointSet::Container::const_iterator ConstIterator;

    /// @brief              Constructor
    ///
    /// @code
    ///                     PointSet pointSet({ { 0.0, 0.0 }, { 0.0, 1.0 } }) ;
    /// @endcode
    ///
    /// @param              [in] aPointArray A point array
    PointSet(const Array<Point>& aPointArray);

    /// @brief              Clone point set
    ///
    /// @code{.cpp}
    ///                     PointSet* clonePtr = PointSet({ { 0.0, 0.0 }, { 1.0, 0.0 } }).clone() ;
    /// @endcode
    ///
    /// @return             Pointer to cloned point set
    virtual PointSet* clone() const override;

    /// @brief              Equal to operator
    ///
    /// @code{.cpp}
    ///                     PointSet({ { 0.0, 0.0 } }) == PointSet({ { 0.0, 0.0 } }) ; // True
    /// @endcode
    ///
    /// @param              [in] aPointSet A point set
    /// @return             True if point sets are equal
    bool operator==(const PointSet& aPointSet) const;

    /// @brief              Not equal to operator
    ///
    /// @code{.cpp}
    ///                     PointSet({ { 0.0, 0.0 } }) != PointSet({ { 1.0, 0.0 } }) ; // True
    /// @endcode
    ///
    /// @param              [in] aPointSet A point set
    /// @return             True if point sets are not equal
    bool operator!=(const PointSet& aPointSet) const;

    /// @brief              Check if point set is defined
    ///
    /// @code
    ///                     PointSet(0.0, 0.0).isDefined() ; // True
    /// @endcode
    ///
    /// @return             True if point set is defined
    virtual bool isDefined() const override;

    /// @brief              Check if point set is empty
    ///
    /// @code
    ///                     PointSet::Empty().isEmpty() ; // True
    /// @endcode
    ///
    /// @return             True if point set is empty
    bool isEmpty() const;

    /// @brief              Check if point set is near another point set
    ///
    /// @code
    ///                     PointSet({ { 0.0, 0.0 }, { 0.0, 1.0 } }).isNear(PointSet({ { 0.0, 1e-15 }, { 0.0, 1.0 } }),
    ///                     1e-15) ; // True
    /// @endcode
    ///
    /// @param              [in] aPointSet A point set
    /// @param              [in] aTolerance A tolerance
    /// @return             True if point set is near another point set
    bool isNear(const PointSet& aPointSet, const Real& aTolerance) const;

    /// @brief              Get size of point set
    ///
    /// @code{.cpp}
    ///                     Size size = PointSet({ { 0.0, 0.0 }, { 1.0, 0.0 } }).getSize() ; // 2
    /// @endcode
    ///
    /// @return             Size of point set
    Size getSize() const;

    /// @brief              Get distance to point
    ///
    /// @code{.cpp}
    ///                     Real distance = PointSet({ { 0.0, 0.0 }, { 1.0, 0.0 } }).distanceTo(Point(2.0, 0.0)) ;
    /// @endcode
    ///
    /// @param              [in] aPoint A point
    /// @return             Distance to point
    Real distanceTo(const Point& aPoint) const;

    /// @brief              Get point closest to another point
    ///
    /// @code{.cpp}
    ///                     Point closest = PointSet({ { 0.0, 0.0 }, { 1.0, 0.0 } }).getPointClosestTo(Point(0.1, 0.0))
    ///                     ;
    /// @endcode
    ///
    /// @param              [in] aPoint A point
    /// @return             Closest point
    Point getPointClosestTo(const Point& aPoint) const;

    /// @brief              Get string representation
    ///
    /// @code{.cpp}
    ///                     String str = PointSet({ { 0.0, 0.0 }, { 1.0, 0.0 } }).toString() ;
    /// @endcode
    ///
    /// @param              [in] aFormat A format
    /// @return             String representation
    virtual String toString(
        const Object::Format& aFormat = Object::Format::Standard, const Integer& aPrecision = Integer::Undefined()
    ) const override;

    /// @brief              Print point
    ///
    /// @code{.cpp}
    ///                     PointSet({ { 0.0, 0.0 }, { 1.0, 0.0 } }).print(std::cout, true) ;
    /// @endcode
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] (optional) displayDecorators If true, display decorators
    virtual void print(std::ostream& anOutputStream, bool displayDecorators = true) const override;

    /// @brief              Get begin const iterator
    ///
    /// @code{.cpp}
    ///                     PointSet pointSet({ { 0.0, 0.0 }, { 1.0, 0.0 } }) ;
    ///                     auto it = pointSet.begin() ;
    /// @endcode
    ///
    /// @return             Begin const iterator
    PointSet::ConstIterator begin() const;

    /// @brief              Get end const iterator
    ///
    /// @code{.cpp}
    ///                     PointSet pointSet({ { 0.0, 0.0 }, { 1.0, 0.0 } }) ;
    ///                     auto it = pointSet.end() ;
    /// @endcode
    ///
    /// @return             End const iterator
    PointSet::ConstIterator end() const;

    /// @brief              Apply transformation to point set
    ///
    /// @code{.cpp}
    ///                     PointSet pointSet({ { 0.0, 0.0 }, { 1.0, 0.0 } }) ;
    ///                     pointSet.applyTransformation(aTransformation) ;
    /// @endcode
    ///
    /// @param              [in] aTransformation A transformation
    virtual void applyTransformation(const Transformation& aTransformation) override;

    /// @brief              Constructs an empty point set
    ///
    /// @code
    ///                     PointSet pointSet = PointSet::Empty() ;
    /// @endcode
    ///
    /// @return             Empty point set
    static PointSet Empty();

   private:
    PointSet::Container points_;
};

}  // namespace object
}  // namespace d2
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
