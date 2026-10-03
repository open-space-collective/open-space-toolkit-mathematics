/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_QuaternionInterpolator_SLERP__
#define __OpenSpaceToolkit_Mathematics_QuaternionInterpolator_SLERP__

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Pair.hpp>
#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

namespace ostk
{
namespace mathematics
{
namespace curvefitting
{
namespace quaternioninterpolator
{

using ostk::core::container::Array;
using ostk::core::container::Pair;
using ostk::core::type::Index;
using ostk::core::type::Real;
using ostk::core::type::Size;

using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;
using ostk::mathematics::object::VectorXd;

/// @brief Spherical Linear Interpolation (SLERP) interpolator for quaternions
///
/// Performs interpolation of unit quaternions (orientations) using Spherical Linear
/// Interpolation (SLERP). Given a query value, the two bracketing data points are located
/// and the interpolated quaternion is computed along the shortest great-circle arc on the
/// unit hypersphere, ensuring a constant angular velocity between the two orientations.
///
/// The input quaternions are normalized at construction time. Query values outside the
/// x range are clamped to the nearest endpoint quaternion (no extrapolation).
///
/// @code{.cpp}
///     VectorXd x(2);
///     x << 0.0, 1.0;
///     Array<Quaternion> quaternions = {q0, q1};
///     SLERP interpolator(x, quaternions);
///     Quaternion result = interpolator.evaluate(0.5);
/// @endcode
///
/// @ref https://en.wikipedia.org/wiki/Slerp
class SLERP
{
   public:
    /// @brief Constructor
    ///
    /// Constructs a SLERP interpolator from x-coordinates and corresponding quaternions.
    /// The quaternions are normalized at construction time.
    ///
    /// @code{.cpp}
    ///     SLERP interpolator(x, quaternions);
    /// @endcode
    ///
    /// @param anXVector A vector of x values (strictly monotonically increasing)
    /// @param aQuaternionArray An array of (defined) quaternions
    SLERP(const VectorXd& anXVector, const Array<Quaternion>& aQuaternionArray);

    /// @brief Destructor
    ~SLERP();

    /// @brief Evaluate the interpolator at a single point
    ///
    /// Returns the interpolated (normalized) quaternion at the given x value. Values outside
    /// the x range are clamped to the nearest endpoint quaternion.
    ///
    /// @code{.cpp}
    ///     Quaternion result = interpolator.evaluate(0.5);
    /// @endcode
    ///
    /// @param aQueryValue An x value
    /// @return Interpolated quaternion
    Quaternion evaluate(const double& aQueryValue) const;

    /// @brief Evaluate the interpolator at multiple points
    ///
    /// @code{.cpp}
    ///     Array<Quaternion> results = interpolator.evaluate(queryVector);
    /// @endcode
    ///
    /// @param aQueryVector A vector of x values
    /// @return Array of interpolated quaternions
    Array<Quaternion> evaluate(const VectorXd& aQueryVector) const;

    /// @brief Get the (normalized) quaternions used by the interpolator
    ///
    /// @code{.cpp}
    ///     Array<Quaternion> quaternions = interpolator.getQuaternions();
    /// @endcode
    ///
    /// @return The array of quaternions
    Array<Quaternion> getQuaternions() const;

   private:
    VectorXd x_;
    Array<Quaternion> quaternions_;

    Pair<Index, Index> findIndexRange(const double& aQueryValue) const;
};

}  // namespace quaternioninterpolator
}  // namespace curvefitting
}  // namespace mathematics
}  // namespace ostk

#endif
