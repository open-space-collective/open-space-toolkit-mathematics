/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Point__
#define __OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Point__

#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

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

using ostk::core::type::Real;

using ostk::mathematics::object::Vector2d;
using ostk::mathematics::geometry::d2::Object;

/// @brief                      Point
///
/// @ref                        https://en.wikipedia.org/wiki/Point_(geometry)

class Point : public Object
{
   public:
    /// @brief              Constructor
    ///
    /// @code
    ///                     Point point = { 0.0, 0.0 } ;
    /// @endcode
    ///
    /// @param              [in] aFirstCoordinate A first coordinate
    /// @param              [in] aSecondCoordinate A second coordinate

    Point(const Real& aFirstCoordinate, const Real& aSecondCoordinate);

    /// @brief              Clone point
    ///
    /// @return             Pointer to cloned point

    virtual Point* clone() const override;

    /// @brief              Equal to operator
    ///
    /// @param              [in] aPoint A point
    /// @return             True if points are equal

    bool operator==(const Point& aPoint) const;

    /// @brief              Not equal to operator
    ///
    /// @param              [in] aPoint A point
    /// @return             True if points are not equal

    bool operator!=(const Point& aPoint) const;

    /// @brief              Addition operator: translate point along vector
    ///
    /// @code
    ///                     Point(0.0, 0.0) + Vector2d(0.0, 1.0) ; // [0.0, 1.0]
    /// @encode
    ///
    /// @param              [in] aVector A translation vector
    /// @return             A point

    Point operator+(const Vector2d& aVector) const;

    /// @brief              Subtraction operator: translate point along opposite vector
    ///
    /// @code
    ///                     Point(0.0, 1.0) - Vector2d(0.0, 1.0) ; // [0.0, 0.0]
    /// @encode
    ///
    /// @param              [in] aVector A translation vector
    /// @return             A point

    Point operator-(const Vector2d& aVector) const;

    /// @brief              Subtraction operator: get translation vector between two points
    ///
    /// @code
    ///                     Point(0.0, 1.0) - Point(0.0, 0.0)  ; // [0.0, 1.0]
    /// @encode
    ///
    /// @param              [in] aPoint A point
    /// @return             A translation vector

    Vector2d operator-(const Point& aPoint) const;

    /// @brief              Check if point is defined
    ///
    /// @code
    ///                     Point(0.0, 0.0).isDefined() ; // True
    /// @endcode
    ///
    /// @return             True if point is defined

    virtual bool isDefined() const override;

    /// @brief              Check if point is near another point
    ///
    /// @code
    ///                     Point(0.0, 0.0).isNear(Point(0.0, 0.0), 1e-15) ; // True
    /// @endcode
    ///
    /// @param              [in] aPoint A point
    /// @param              [in] aTolerance A tolerance
    /// @return             True if point is near another point

    bool isNear(const Point& aPoint, const Real& aTolerance) const;

    /// @brief              Get reference to first coordinate
    ///
    /// @code
    ///                     Point(1.0, 2.0).x() ; // &1.0
    /// @endcode
    ///
    /// @return             Reference to first coordinate

    const Real& x() const;

    /// @brief              Get reference to second coordinate
    ///
    /// @code
    ///                     Point(1.0, 2.0).y() ; // &2.0
    /// @endcode
    ///
    /// @return             Reference to second coordinate

    const Real& y() const;

    /// @brief              Get vector representation of point
    ///
    /// @return             Vector representation of point

    Vector2d asVector() const;

    /// @brief              Get distance to another point
    ///
    /// @param              [in] aPoint A point
    /// @return             Distance to point

    Real distanceTo(const Point& aPoint) const;

    /// @brief              Get string representation
    ///
    /// @param              [in] aFormat A format
    /// @param              [in] (optional) aPrecision A precision
    /// @return             String representation

    virtual String toString(
        const Object::Format& aFormat = Object::Format::Standard, const Integer& aPrecision = Integer::Undefined()
    ) const override;

    /// @brief              Print point
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] (optional) displayDecorators If true, display decorators

    virtual void print(std::ostream& anOutputStream, bool displayDecorators = true) const override;

    /// @brief              Apply transformation to point
    ///
    /// @param              [in] aTransformation A transformation

    virtual void applyTransformation(const Transformation& aTransformation) override;

    /// @brief              Constructs an undefined point
    ///
    /// @code
    ///                     Point point = Point::Undefined() ; // Undefined
    /// @endcode
    ///
    /// @return             Undefined point

    static Point Undefined();

    /// @brief              Constructs a point at origin
    ///
    /// @code
    ///                     Point point = Point::Origin() ; // [0.0, 0.0]
    /// @endcode
    ///
    /// @return             Point at origin

    static Point Origin();

    /// @brief              Constructs a point from a vector
    ///
    /// @code
    ///                     Point point = Point::Vector({ 0.0, 0.0 }) ; // [0.0, 0.0]
    /// @endcode
    ///
    /// @return             Point

    static Point Vector(const Vector2d& aVector);

   private:
    Real x_;
    Real y_;
};

}  // namespace object
}  // namespace d2
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
