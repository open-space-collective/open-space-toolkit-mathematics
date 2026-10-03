/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Ellipsoid__
#define __OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Ellipsoid__

#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/Planetodetic/Object.hpp>

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
using ostk::core::type::Real;
using ostk::core::type::String;

using ostk::mathematics::geometry::planetodetic::Object;

#define DEFAULT_PRECISION Integer::Undefined()

/// @brief                      A reference ellipsoid used in planetodetic coordinate systems. Defined by its equatorial
/// (a, b) and polar (c) radii.
///
/// @note                       As opposed to the 3D ellipsoid, this one does not require an origin nor an orientation,
/// since it itself constitutes a reference frame in the planetodetic coordinate system.
///
/// @ref                        https://en.wikipedia.org/wiki/Ellipsoid

class Ellipsoid : public Object
{
   public:
    /// @brief              Constructor
    ///
    /// @param              [in] anEquatorialRadiusA First equatorial radius (a); distance from the center to the prime
    /// meridian along the equator (0°, 0°)
    /// @param              [in] anEquatorialRadiusB Second equatorial radius (b); distance from the center to the 90°
    /// meridian along the equator (0°, 90°)
    /// @param              [in] aPolarRadius Polar radius (c); distance from the center to the poles

    Ellipsoid(const Real& anEquatorialRadiusA, const Real& anEquatorialRadiusB, const Real& aPolarRadius);

    /// @brief              Clone ellipsoid
    ///
    /// @return             Pointer to cloned ellipsoid

    virtual Ellipsoid* clone() const override;

    /// @brief              Equal to operator
    ///
    /// @code
    ///                     Ellipsoid(6378137.0, 6378137.0, 6356752.3142) == Ellipsoid(6378137.0, 6378137.0,
    ///                     6356752.3142) ;
    ///                     // True
    /// @endcode
    ///
    /// @param              [in] anEllipsoid An ellipsoid
    /// @return             True if ellipsoids are equal

    bool operator==(const Ellipsoid& anEllipsoid) const;

    /// @brief              Not equal to operator
    ///
    /// @code
    ///                     Ellipsoid(6378137.0, 6378137.0, 6356752.3142) != Ellipsoid(6378137.0, 6378137.0, 6378137.0)
    ///                     ; // True
    /// @endcode
    ///
    /// @param              [in] anEllipsoid An ellipsoid
    /// @return             True if ellipsoids are not equal

    bool operator!=(const Ellipsoid& anEllipsoid) const;

    /// @brief              Check if ellipsoid is defined
    ///
    /// @code
    ///                     Ellipsoid(6378137.0, 6378137.0, 6356752.3142).isDefined() ; // True
    /// @endcode
    ///
    /// @return             True if ellipsoid is defined

    virtual bool isDefined() const override;

    /// @brief              Get first equatorial radius (a)
    ///
    /// @code
    ///                     Ellipsoid(6378137.0, 6378137.0, 6356752.3142).getEquatorialRadiusA() ; // 6378137.0
    /// @endcode
    ///
    /// @return             First equatorial radius

    Real getEquatorialRadiusA() const;

    /// @brief              Get second equatorial radius (b)
    ///
    /// @code
    ///                     Ellipsoid(6378137.0, 6378137.0, 6356752.3142).getEquatorialRadiusB() ; // 6378137.0
    /// @endcode
    ///
    /// @return             Second equatorial radius

    Real getEquatorialRadiusB() const;

    /// @brief              Get polar radius (c)
    ///
    /// @code
    ///                     Ellipsoid(6378137.0, 6378137.0, 6356752.3142).getPolarRadius() ; // 6356752.3142
    /// @endcode
    ///
    /// @return             Polar radius

    Real getPolarRadius() const;

    /// @brief              Get string representation
    ///
    /// @param              [in] aFormat A format
    /// @param              [in] aPrecision A precision
    /// @return             String representation

    virtual String toString(
        const Object::Format& aFormat = Object::Format::Standard, const Integer& aPrecision = DEFAULT_PRECISION
    ) const override;

    /// @brief              Print ellipsoid
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] (optional) displayDecorators If true, display decorators

    virtual void print(std::ostream& anOutputStream, bool displayDecorators = true) const override;

    /// @brief              Construct an undefined ellipsoid
    ///
    /// @code
    ///                     Ellipsoid ellipsoid = Ellipsoid::Undefined() ; // Undefined
    /// @endcode
    ///
    /// @return             Undefined ellipsoid

    static Ellipsoid Undefined();

    /// @brief              Construct a spherical ellipsoid (a = b = c)
    ///
    /// @code
    ///                     Ellipsoid ellipsoid = Ellipsoid::Sphere(6378137.0) ; // Sphere
    /// @endcode
    ///
    /// @ref                https://en.wikipedia.org/wiki/Sphere
    ///
    /// @param              [in] aRadius A radius
    /// @return             Sphere

    static Ellipsoid Sphere(const Real& aRadius);

    /// @brief              Construct an ellipsoid of revolution (spheroid) around the polar axis.
    ///
    /// @note               Only 2 arguments are allowed.
    ///
    /// @code
    ///                     // Using equatorial radius and flattening
    ///                     Ellipsoid ellipsoid = Ellipsoid::Spheroid(6378137.0, 1.0 / 298.257223563) ;
    ///
    ///                     // Using equatorial radius and polar radius
    ///                     Ellipsoid ellipsoid = Ellipsoid::Spheroid(6378137.0, Real::Undefined(), 6356752.3142) ;
    ///
    ///                     // Using polar radius and flattening
    ///                     Ellipsoid ellipsoid = Ellipsoid::Spheroid(Real::Undefined(), 1.0 / 298.257223563,
    ///                     6356752.3142) ;
    /// @endcode
    /// @ref                https://en.wikipedia.org/wiki/Spheroid
    ///
    /// @param              [in] anEquatorialRadius An equatorial radius (a)
    /// @param              [in] aFlattening A flattening (f = (a - c) / a)
    /// @param              [in] aPolarRadius A polar radius (c)
    /// @return             Spheroid

    static Ellipsoid Spheroid(
        const Real& anEquatorialRadius = Real::Undefined(),
        const Real& aFlattening = Real::Undefined(),
        const Real& aPolarRadius = Real::Undefined()
    );

    /// @brief              Construct a WGS84 spheroid (in meters)
    ///
    /// @code
    ///                     Ellipsoid ellipsoid = Ellipsoid::WGS84() ;
    /// @endcode
    ///
    /// @return             WGS84 spheroid

    static Ellipsoid WGS84();

   private:
    Real equatorialRadiusA_;  // a
    Real equatorialRadiusB_;  // b
    Real polarRadius_;        // c
};

}  // namespace object
}  // namespace planetodetic
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
