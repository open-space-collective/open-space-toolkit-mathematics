/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_EulerAngle__
#define __OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation_Rotation_EulerAngle__

#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/Angle.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

namespace ostk
{
namespace mathematics
{
namespace geometry
{
namespace d3
{
namespace transformation
{
namespace rotation
{

using ostk::core::type::Integer;
using ostk::core::type::Real;
using ostk::core::type::String;

using ostk::mathematics::geometry::Angle;
using ostk::mathematics::object::Vector3d;
using ostk::mathematics::object::Vector4d;

class RotationMatrix;
class Quaternion;
class RotationVector;

/// @brief                      Euler Angle (intrinsic rotation)
///
///                             Implementation from "Fundamentals of Spacecraft Attitude Determination and Control",
///                             F. Landis Markley and John L. Crassidis, Springer
///
/// @ref                        https://en.wikipedia.org/wiki/Euler_angles
/// @ref                        https://en.wikipedia.org/wiki/Euler_angles#Conventions_by_intrinsic_rotations

class EulerAngle
{
   public:
    enum class AxisSequence
    {

        Undefined,  ///< Undefined sequence
        XYZ,        ///< X -> Y -> Z sequence
        ZXY,        ///< Z -> X -> Y sequence
        ZYX         ///< Z -> Y -> X sequence

    };

    /// @brief                  Construct Euler Angle from angles and axis sequence
    ///
    /// @code
    ///                         EulerAngle(
    ///                             Angle::Degrees(1.0),
    ///                             Angle::Degrees(2.0),
    ///                             Angle::Degrees(3.0),
    ///                             EulerAngle::AxisSequence::ZYX
    ///                         );
    /// @endcode
    ///
    /// @param                  [in] aFirstAngle A first angle (phi)
    /// @param                  [in] aSecondAngle A second angle (theta)
    /// @param                  [in] aThirdAngle A third angle (psi)
    /// @param                  [in] anAxisSequence An axis sequence

    EulerAngle(
        const Angle& aFirstAngle,
        const Angle& aSecondAngle,
        const Angle& aThirdAngle,
        const EulerAngle::AxisSequence& anAxisSequence
    );

    /// @brief                  Construct Euler Angle from vector of angles and axis sequence
    ///
    /// @code
    ///                         EulerAngle(
    ///                             {1.0, 0.0, 0.0},
    ///                             Angle::Unit::Degree,
    ///                             EulerAngle::AxisSequence::ZYX
    ///                         );
    /// @endcode
    ///
    /// @param                  [in] aVector A vector of angles
    /// @param                  [in] anAngleUnit An angle unit
    /// @param                  [in] anAxisSequence An axis sequence

    EulerAngle(const Vector3d& aVector, const Angle::Unit& anAngleUnit, const EulerAngle::AxisSequence& anAxisSequence);

    /// @brief                  Equal to operator
    ///
    /// @code
    ///                         EulerAngle::Unit() == EulerAngle::Unit();
    /// @endcode
    ///
    /// @param                  [in] aEulerAngle A Euler Angle
    /// @return                 True if Euler Angles are equal

    bool operator==(const EulerAngle& aEulerAngle) const;

    /// @brief                  Not equal to operator
    ///
    /// @code
    ///                         EulerAngle::Unit() != EulerAngle::Unit();
    /// @endcode
    ///
    /// @param                  [in] aEulerAngle A Euler Angle
    /// @return                 True if Euler Angles are not equal

    bool operator!=(const EulerAngle& aEulerAngle) const;

    /// @brief                  Output stream operator
    ///
    /// @code
    ///                         std::cout << EulerAngle::Unit();
    /// @endcode
    ///
    /// @param                  [in] anOutputStream An output stream
    /// @param                  [in] aEulerAngle A Euler Angle
    /// @return                 Output stream reference

    friend std::ostream& operator<<(std::ostream& anOutputStream, const EulerAngle& aEulerAngle);

    /// @brief                  Check if Euler Angle is defined
    ///
    /// @code
    ///                         EulerAngle::Unit().isDefined();
    /// @endcode
    ///
    /// @return                 True if Euler Angle is defined

    bool isDefined() const;

    /// @brief                  Check if Euler Angle is unitary
    ///
    /// @code
    ///                         EulerAngle::Unit().isUnitary();
    /// @endcode
    ///
    /// @return                 True if Euler Angle is unitary

    bool isUnitary() const;

    /// @brief                  Check if Euler Angle is equal to another Euler Angle
    ///                         within a given angular tolerance
    ///
    /// @code
    ///                         EulerAngle::Unit().isNear(
    ///                             EulerAngle::Unit(),
    ///                             Angle::Degrees(1e-6)
    ///                         );
    /// @endcode
    ///
    /// @param                  [in] aEulerAngle A Euler Angle
    /// @param                  [in] anAngularTolerance An angular tolerance
    /// @return                 True if equal within given angular tolerance

    bool isNear(const EulerAngle& aEulerAngle, const Angle& anAngularTolerance) const;

    /// @brief                  Get first angle of rotation (phi)
    ///
    /// @code
    ///                         EulerAngle::Unit().getPhi();
    /// @endcode
    ///
    /// @return                 First angle of rotation

    Angle getPhi() const;

    /// @brief                  Get second angle of rotation (theta)
    ///
    /// @code
    ///                         EulerAngle::Unit().getTheta();
    /// @endcode
    ///
    /// @return                 Second angle of rotation

    Angle getTheta() const;

    /// @brief                  Get third angle of rotation (psi)
    ///
    /// @code
    ///                         EulerAngle::Unit().getPsi();
    /// @endcode
    ///
    /// @return                 Third angle of rotation

    Angle getPsi() const;

    /// @brief                  Get axis sequence
    ///
    /// @code
    ///                         EulerAngle::Unit().getAxisSequence();
    /// @endcode
    ///
    /// @return                 Axis sequence (e.g, ZYX)

    AxisSequence getAxisSequence() const;

    /// @brief                  Return vector containing the three angles
    ///
    /// @code
    ///                         EulerAngle::Unit().toVector(Angle::Unit::Degree);
    /// @endcode
    ///
    /// @param                  [in] anAngleUnit An angle unit
    /// @return                 Vector containing the three angles

    Vector3d toVector(const Angle::Unit& anAngleUnit) const;

    /// @brief                  Return string form of Euler Angle [phi; theta; psi]
    ///
    /// @code
    ///                         EulerAngle::Unit().toString(Angle::Unit::Degree);
    /// @endcode
    ///
    /// @param                  [in] (optional) anAngleUnit An angle unit
    /// @return                 String from of Euler Angle

    String toString(const Angle::Unit& anAngleUnit = Angle::Unit::Degree) const;

    /// @brief                  Construct undefined Euler Angle
    ///
    /// @code
    ///                         EulerAngle::Undefined();
    /// @endcode
    ///
    /// @return                 Undefined Euler Angle

    static EulerAngle Undefined();

    /// @brief                  Construct unitary Euler Angle
    ///
    /// @code
    ///                         EulerAngle::Unit();
    /// @endcode
    ///
    /// @return                 Unitary Euler Angle

    static EulerAngle Unit();

    /// @brief                  Construct Euler Angle from angles following XYZ sequence
    ///
    /// @code
    ///                         EulerAngle::XYZ(
    ///                             Angle::Degrees(1.0),
    ///                             Angle::Degrees(2.0),
    ///                             Angle::Degrees(3.0)
    ///                         );
    /// @endcode
    ///
    /// @param                  [in] aFirstAngle A first angle (phi)
    /// @param                  [in] aSecondAngle A second angle (theta)
    /// @param                  [in] aThirdAngle A third angle (psi)
    /// @return                 Euler Angle

    static EulerAngle XYZ(const Angle& aFirstAngle, const Angle& aSecondAngle, const Angle& aThirdAngle);

    /// @brief                  Construct Euler Angle from angles following ZXY sequence
    ///
    /// @code
    ///                         EulerAngle::ZXY(
    ///                             Angle::Degrees(1.0),
    ///                             Angle::Degrees(2.0),
    ///                             Angle::Degrees(3.0)
    ///                         );
    /// @endcode
    ///
    /// @param                  [in] aFirstAngle A first angle (phi)
    /// @param                  [in] aSecondAngle A second angle (theta)
    /// @param                  [in] aThirdAngle A third angle (psi)
    /// @return                 Euler Angle

    static EulerAngle ZXY(const Angle& aFirstAngle, const Angle& aSecondAngle, const Angle& aThirdAngle);

    /// @brief                  Construct Euler Angle from angles following ZYX sequence
    ///
    /// @code
    ///                         EulerAngle::ZYX(
    ///                             Angle::Degrees(1.0),
    ///                             Angle::Degrees(2.0),
    ///                             Angle::Degrees(3.0)
    ///                         );
    /// @endcode
    ///
    /// @param                  [in] aFirstAngle A first angle (phi)
    /// @param                  [in] aSecondAngle A second angle (theta)
    /// @param                  [in] aThirdAngle A third angle (psi)
    /// @return                 Euler Angle

    static EulerAngle ZYX(const Angle& aFirstAngle, const Angle& aSecondAngle, const Angle& aThirdAngle);

    /// @brief                  Construct Euler Angle from Rotation Matrix
    ///
    /// @code
    ///                         EulerAngle::RotationMatrix(
    ///                             RotationMatrix::Unit(),
    ///                             EulerAngle::AxisSequence::ZYX
    ///                         );
    /// @endcode
    ///
    /// @param                  [in] aRotationMatrix A Rotation Matrix
    /// @param                  [in] anAxisSequence An axis sequence
    /// @return                 Euler Angle

    static EulerAngle Quaternion(
        const rotation::Quaternion& aQuaternion, const EulerAngle::AxisSequence& anAxisSequence
    );

    /// @brief                  Construct Euler Angle from Quaternion
    ///
    /// @code
    ///                         EulerAngle::Quaternion(
    ///                             Quaternion::Unit(),
    ///                             EulerAngle::AxisSequence::ZYX
    ///                         );
    /// @endcode
    ///
    /// @param                  [in] aQuaternion A Quaternion
    /// @param                  [in] anAxisSequence An axis sequence
    /// @return                 Euler Angle

    static EulerAngle RotationVector(
        const rotation::RotationVector& aRotationVector, const EulerAngle::AxisSequence& anAxisSequence
    );

    /// @brief                  Construct Euler Angle from Rotation Vector
    ///
    /// @code
    ///                         EulerAngle::RotationVector(
    ///                             RotationVector::Unit(),
    ///                             EulerAngle::AxisSequence::ZYX
    ///                         );
    /// @endcode
    ///
    /// @param                  [in] aRotationVector A Rotation Vector
    /// @param                  [in] anAxisSequence An axis sequence
    /// @return                 Euler Angle

    static EulerAngle RotationMatrix(
        const rotation::RotationMatrix& aRotationMatrix, const EulerAngle::AxisSequence& anAxisSequence
    );

    /// @brief                  Construct a string representation of an axis sequence
    ///
    /// @code
    ///                         EulerAngle::StringFromAxisSequence(EulerAngle::AxisSequence::ZYX);
    /// @endcode
    ///
    /// @param                  [in] anAxisSequence An axis sequence
    /// @return                 String representation of axis sequence

    static String StringFromAxisSequence(const EulerAngle::AxisSequence& anAxisSequence);

   private:
    Angle phi_;
    Angle theta_;
    Angle psi_;

    EulerAngle::AxisSequence axisSequence_;
};
}  // namespace rotation
}  // namespace transformation
}  // namespace d3
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
