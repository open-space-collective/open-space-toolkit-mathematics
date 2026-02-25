/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Geometry_3D_Object_PointSet__
#define __OpenSpaceToolkit_Mathematics_Geometry_3D_Object_PointSet__

#include <unordered_set>

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Point.hpp>

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
using ostk::core::type::Index;
using ostk::core::type::Size;

using ostk::mathematics::geometry::d3::Object;
using ostk::mathematics::geometry::d3::object::Point;
using ostk::mathematics::object::Vector3d;

/// @brief                      Point set
///
/// @code{.cpp}
///                             PointSet pointSet({ { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 } }) ;
/// @endcode
class PointSet : public Object
{
   public:
    /// @brief              Point hasher
    ///
    /// @code{.cpp}
    ///                     PointSet::Hasher hasher ;
    ///                     std::size_t hash = hasher(Point::Origin()) ;
    /// @endcode
    ///
    /// @ref                https://wjngkoh.wordpress.com/2015/03/04/c-hash-function-for-eigen-matrix-and-vector/
    struct Hasher
    {
        std::size_t operator()(const Point& aPoint) const
        {
            size_t seed = 0;

            for (size_t i = 0; i < 3; ++i)
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
    ///                     PointSet pointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 } }) ;
    /// @endcode
    ///
    /// @param              [in] aPointArray A point array
    PointSet(const Array<Point>& aPointArray);

    /// @brief              Clone point set
    ///
    /// @code{.cpp}
    ///                     PointSet* pointSetPtr = PointSet({ { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 } }).clone() ;
    /// @endcode
    ///
    /// @return             Pointer to cloned point set
    virtual PointSet* clone() const override;

    /// @brief              Equal to operator
    ///
    /// @code{.cpp}
    ///                     PointSet({ { 0.0, 0.0, 0.0 } }) == PointSet({ { 0.0, 0.0, 0.0 } }) ; // True
    /// @endcode
    ///
    /// @param              [in] aPointSet A point set
    /// @return             True if point sets are equal
    bool operator==(const PointSet& aPointSet) const;

    /// @brief              Not equal to operator
    ///
    /// @code{.cpp}
    ///                     PointSet({ { 0.0, 0.0, 0.0 } }) != PointSet({ { 1.0, 0.0, 0.0 } }) ; // True
    /// @endcode
    ///
    /// @param              [in] aPointSet A point set
    /// @return             True if point sets are not equal
    bool operator!=(const PointSet& aPointSet) const;

    /// @brief              Check if point set is defined
    ///
    /// @code
    ///                     PointSet(0.0, 0.0, 0.0).isDefined() ; // True
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
    ///                     PointSet({ { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 } }).isNear(PointSet({ { 0.0, 1e-15, 0.0 }, {
    ///                     0.0, 0.0, 1.0 } }), 1e-15) ; // True
    /// @endcode
    ///
    /// @param              [in] aPointSet A point set
    /// @param              [in] aTolerance A tolerance
    /// @return             True if point set is near another point set
    bool isNear(const PointSet& aPointSet, const Real& aTolerance) const;

    /// @brief              Get size of point set
    ///
    /// @code{.cpp}
    ///                     PointSet({ { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 } }).getSize() ; // 2
    /// @endcode
    ///
    /// @return             Size of point set
    Size getSize() const;

    /// @brief              Get distance to point
    ///
    /// @code{.cpp}
    ///                     PointSet pointSet = PointSet({ { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 } }) ;
    ///                     Real distance = pointSet.distanceTo(Point(2.0, 0.0, 0.0)) ;
    /// @endcode
    ///
    /// @param              [in] aPoint A point
    /// @return             Distance to point
    Real distanceTo(const Point& aPoint) const;

    /// @brief              Get point closest to another point
    ///
    /// @code{.cpp}
    ///                     PointSet pointSet = PointSet({ { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 } }) ;
    ///                     Point closest = pointSet.getPointClosestTo(Point(0.1, 0.0, 0.0)) ;
    /// @endcode
    ///
    /// @param              [in] aPoint A point
    /// @return             Closest point
    Point getPointClosestTo(const Point& aPoint) const;

    /// @brief              Print point
    ///
    /// @code{.cpp}
    ///                     PointSet({ { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 } }).print(std::cout, true) ;
    /// @endcode
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] (optional) displayDecorators If true, display decorators
    virtual void print(std::ostream& anOutputStream, bool displayDecorators = true) const override;

    /// @brief              Get begin const iterator
    ///
    /// @code{.cpp}
    ///                     PointSet pointSet = PointSet({ { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 } }) ;
    ///                     PointSet::ConstIterator it = pointSet.begin() ;
    /// @endcode
    ///
    /// @return             Begin const iterator
    PointSet::ConstIterator begin() const;

    /// @brief              Get end const iterator
    ///
    /// @code{.cpp}
    ///                     PointSet pointSet = PointSet({ { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 } }) ;
    ///                     PointSet::ConstIterator it = pointSet.end() ;
    /// @endcode
    ///
    /// @return             End const iterator
    PointSet::ConstIterator end() const;

    /// @brief              Apply transformation to point set
    ///
    /// @code{.cpp}
    ///                     PointSet pointSet = PointSet({ { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 } }) ;
    ///                     pointSet.applyTransformation(Transformation::Identity()) ;
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
}  // namespace d3
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
