/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Spheroid__
#define __OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object_Spheroid__

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

/// @brief                      Spheroid (ellipsoid of revolution)
///
///                             A spheroid is a surface formed by rotating an ellipse about one of its
///                             principal axes. It is defined by its equatorial radius and flattening.
///
/// @ref                        https://en.wikipedia.org/wiki/Spheroid

class Spheroid : public Object
{
   public:
    /// @brief              Clone spheroid
    ///
    /// @return             Pointer to cloned spheroid

    virtual Spheroid* clone() const override;

    /// @brief              Equal to operator
    ///
    /// @code
    ///                     Spheroid(6378137.0, 1.0 / 298.257223563) == Spheroid(6378137.0, 1.0 / 298.257223563) ;
    ///                     // True
    /// @endcode
    ///
    /// @param              [in] aSpheroid A spheroid
    /// @return             True if spheroids are equal

    bool operator==(const Spheroid& aSpheroid) const;

    /// @brief              Not equal to operator
    ///
    /// @code
    ///                     Spheroid(6378137.0, 1.0 / 298.257223563) != Spheroid(6378137.0, 0.0) ; // True
    /// @endcode
    ///
    /// @param              [in] aSpheroid A spheroid
    /// @return             True if spheroids are not equal

    bool operator!=(const Spheroid& aSpheroid) const;

    /// @brief              Check if spheroid is defined
    ///
    /// @code
    ///                     Spheroid(6378137.0, 1.0 / 298.257223563).isDefined() ; // True
    /// @endcode
    ///
    /// @return             True if spheroid is defined

    virtual bool isDefined() const override;

    /// @brief              Get equatorial radius (a)
    ///
    /// @code
    ///                     Spheroid(6378137.0, 1.0 / 298.257223563).getEquatorialRadius() ; // 6378137.0
    /// @endcode
    ///
    /// @return             Equatorial radius

    Real getEquatorialRadius() const;

    /// @brief              Get polar radius (c)
    ///
    ///                     The polar radius is computed from the equatorial radius and flattening:
    ///                     c = a * (1 - f)
    ///
    /// @code
    ///                     Spheroid(6378137.0, 1.0 / 298.257223563).getPolarRadius() ; // ~6356752.3142
    /// @endcode
    ///
    /// @return             Polar radius

    Real getPolarRadius() const;

    /// @brief              Get flattening (f)
    ///
    /// @code
    ///                     Spheroid(6378137.0, 1.0 / 298.257223563).getFlattening() ; // ~0.00335281
    /// @endcode
    ///
    /// @return             Flattening

    Real getFlattening() const;

    /// @brief              Get eccentricity (e)
    ///
    ///                     The eccentricity is computed from the flattening:
    ///                     e = sqrt(2*f - f^2)
    ///
    /// @code
    ///                     Spheroid(6378137.0, 1.0 / 298.257223563).getEccentricity() ; // ~0.0818191908
    /// @endcode
    ///
    /// @return             Eccentricity

    Real getEccentricity() const;

    /// @brief              Check if spheroid is oblate
    ///
    ///                     An oblate spheroid has f > 0 (equatorial radius > polar radius)
    ///
    /// @code
    ///                     Spheroid(6378137.0, 1.0 / 298.257223563).isOblate() ; // True
    /// @endcode
    ///
    /// @return             True if spheroid is oblate

    bool isOblate() const;

    /// @brief              Check if spheroid is prolate
    ///
    ///                     A prolate spheroid has f < 0 (equatorial radius < polar radius)
    ///
    /// @code
    ///                     Spheroid(6378137.0, -0.1).isProlate() ; // True
    /// @endcode
    ///
    /// @return             True if spheroid is prolate

    bool isProlate() const;

    /// @brief              Check if spheroid is a sphere
    ///
    ///                     A sphere has f = 0 (equatorial radius = polar radius)
    ///
    /// @code
    ///                     Spheroid(6378137.0, 0.0).isSphere() ; // True
    /// @endcode
    ///
    /// @return             True if spheroid is a sphere

    bool isSphere() const;

    /// @brief              Get string representation
    ///
    /// @param              [in] aFormat A format
    /// @param              [in] aPrecision A precision
    /// @return             String representation

    virtual String toString(
        const Object::Format& aFormat = Object::Format::Standard, const Integer& aPrecision = DEFAULT_PRECISION
    ) const override;

    /// @brief              Print spheroid
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] (optional) displayDecorators If true, display decorators

    virtual void print(std::ostream& anOutputStream, bool displayDecorators = true) const override;

    /// @brief              Constructs an undefined spheroid
    ///
    /// @code
    ///                     Spheroid spheroid = Spheroid::Undefined() ; // Undefined
    /// @endcode
    ///
    /// @return             Undefined spheroid

    static Spheroid Undefined();

    /// @brief              Constructs a spherical spheroid (f = 0)
    ///
    /// @code
    ///                     Spheroid spheroid = Spheroid::Sphere(6378137.0) ; // Sphere
    /// @endcode
    ///
    /// @param              [in] aRadius A radius
    /// @return             Spherical spheroid

    static Spheroid Sphere(const Real& aRadius);

    /// @brief              Constructs a spheroid from equatorial radius and flattening
    ///
    /// @code
    ///                     Spheroid spheroid = Spheroid::FromEquatorialRadiusAndFlattening(6378137.0, 1.0 /
    ///                     298.257223563) ; // WGS84
    /// @endcode
    ///
    /// @param              [in] anEquatorialRadius An equatorial radius (a)
    /// @param              [in] aFlattening A flattening (f = (a - c) / a)
    /// @return             Spheroid

    static Spheroid FromEquatorialRadiusAndFlattening(const Real& anEquatorialRadius, const Real& aFlattening);

   private:
    /// @brief              Constructor
    ///
    /// @param              [in] anEquatorialRadius An equatorial radius (a)
    /// @param              [in] aFlattening A flattening (f = (a - c) / a)

    Spheroid(const Real& anEquatorialRadius, const Real& aFlattening);

    Real equatorialRadius_;  // a
    Real flattening_;        // f = (a - c) / a
};

}  // namespace object
}  // namespace planetodetic
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
