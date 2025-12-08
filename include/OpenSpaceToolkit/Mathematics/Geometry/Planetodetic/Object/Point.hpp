/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Point__
#define __OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Point__

#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/Angle.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/Planetodetic/Object.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

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

using ostk::core::type::Integer;
using ostk::core::type::String;

using ostk::mathematics::geometry::Angle;
using ostk::mathematics::geometry::planetodetic::Object;
using ostk::mathematics::object::Vector3d;

#define DEFAULT_PRECISION Integer::Undefined()

/// @brief                      Planetodetic Point
///
///                             A point on a reference spheroid defined by geodetic coordinates
///                             (latitude and longitude)
///
/// @ref                        https://en.wikipedia.org/wiki/Geodetic_coordinates

class Point : public Object
{
   public:
    /// @brief              Constructor
    ///
    /// @code
    ///                     Point point(Angle::Degrees(45.0), Angle::Degrees(-122.0)) ;
    /// @endcode
    ///
    /// @param              [in] aLatitude A latitude
    /// @param              [in] aLongitude A longitude

    Point(const Angle& aLatitude, const Angle& aLongitude);

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

    /// @brief              Check if point is defined
    ///
    /// @code
    ///                     Point(Angle::Degrees(45.0), Angle::Degrees(-122.0)).isDefined() ; // True
    /// @endcode
    ///
    /// @return             True if point is defined

    virtual bool isDefined() const override;

    /// @brief              Get latitude
    ///
    /// @code
    ///                     Point(Angle::Degrees(45.0), Angle::Degrees(-122.0)).getLatitude() ; // 45.0 deg
    /// @endcode
    ///
    /// @return             Latitude

    Angle getLatitude() const;

    /// @brief              Get longitude
    ///
    /// @code
    ///                     Point(Angle::Degrees(45.0), Angle::Degrees(-122.0)).getLongitude() ; // -122.0 deg
    /// @endcode
    ///
    /// @return             Longitude

    Angle getLongitude() const;

    /// @brief              Check if three points are collinear
    ///
    /// @code
    ///                     Point a(Angle::Degrees(0.0), Angle::Degrees(0.0)) ;
    ///                     Point b(Angle::Degrees(0.0), Angle::Degrees(45.0)) ;
    ///                     Point c(Angle::Degrees(0.0), Angle::Degrees(90.0)) ;
    ///                     a.isCollinear(b, c) ; // True (all on equator)
    /// @endcode
    ///
    /// @param              [in] aPoint1 First point
    /// @param              [in] aPoint2 Second point
    /// @return             True if the three points (this, aPoint1, aPoint2) are collinear

    bool isCollinear(const Point& aPoint1, const Point& aPoint2) const;

    /// @brief              Get string representation
    ///
    /// @param              [in] aFormat A format
    /// @param              [in] aPrecision A precision
    /// @return             String representation

    virtual String toString(
        const Object::Format& aFormat = Object::Format::Standard, const Integer& aPrecision = DEFAULT_PRECISION
    ) const override;

    /// @brief              Print point
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] (optional) displayDecorators If true, display decorators

    virtual void print(std::ostream& anOutputStream, bool displayDecorators = true) const override;

    /// @brief              Constructs an undefined point
    ///
    /// @code
    ///                     Point point = Point::Undefined() ; // Undefined
    /// @endcode
    ///
    /// @return             Undefined point

    static Point Undefined();

    /// @brief              Constructs a point at origin (0°, 0°)
    ///
    /// @code
    ///                     Point point = Point::Origin() ; // (0°, 0°)
    /// @endcode
    ///
    /// @return             Point at origin

    static Point Origin();

    /// @brief              Constructs the North Pole (90°N, 0°)
    ///
    /// @code
    ///                     Point point = Point::NorthPole() ; // (90°N, 0°)
    /// @endcode
    ///
    /// @return             North Pole point

    static Point NorthPole();

    /// @brief              Constructs the South Pole (90°S, 0°)
    ///
    /// @code
    ///                     Point point = Point::SouthPole() ; // (90°S, 0°)
    /// @endcode
    ///
    /// @return             South Pole point

    static Point SouthPole();

   private:
    Angle latitude_;
    Angle longitude_;

    /// @brief              Transform point to a 3-dimensional Cartesian unitary vector
    ///
    /// @return             3D unit vector representation of the point

    ostk::mathematics::object::Vector3d toVector() const;
};

}  // namespace object
}  // namespace planetodetic
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
