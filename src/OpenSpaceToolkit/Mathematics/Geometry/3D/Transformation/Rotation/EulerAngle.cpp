/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/EulerAngle.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationMatrix.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>

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

EulerAngle::EulerAngle(
    const Angle& aFirstAngle,
    const Angle& aSecondAngle,
    const Angle& aThirdAngle,
    const EulerAngle::AxisSequence& anAxisSequence
)
    : phi_(aFirstAngle),
      theta_(aSecondAngle),
      psi_(aThirdAngle),
      axisSequence_(anAxisSequence)
{
}

EulerAngle::EulerAngle(
    const Vector3d& aVector, const Angle::Unit& anAngleUnit, const EulerAngle::AxisSequence& anAxisSequence
)
    : phi_(Angle(aVector(0), anAngleUnit)),
      theta_(Angle(aVector(1), anAngleUnit)),
      psi_(Angle(aVector(2), anAngleUnit)),
      axisSequence_(anAxisSequence)
{
}

bool EulerAngle::operator==(const EulerAngle& aEulerAngle) const
{
    if ((!this->isDefined()) || (!aEulerAngle.isDefined()))
    {
        return false;
    }

    if (axisSequence_ != aEulerAngle.axisSequence_)
    {
        return false;
    }

    if ((phi_ == aEulerAngle.phi_) && (theta_ == aEulerAngle.theta_) && (psi_ == aEulerAngle.psi_))
    {
        return true;
    }

    // https://math.stackexchange.com/a/55552
    if ((phi_ + Angle::Pi() == aEulerAngle.phi_) && (Angle::Pi() - theta_ == aEulerAngle.theta_) &&
        (psi_ + Angle::Pi() == aEulerAngle.psi_))
    {
        return true;
    }

    return false;
}

bool EulerAngle::operator!=(const EulerAngle& aEulerAngle) const
{
    return !((*this) == aEulerAngle);
}

std::ostream& operator<<(std::ostream& anOutputStream, const EulerAngle& aEulerAngle)
{
    ostk::core::utils::Print::Header(anOutputStream, "Euler Angle");

    ostk::core::utils::Print::Line(anOutputStream)
        << "Phi:" << (aEulerAngle.isDefined() ? String::Format("{}", aEulerAngle.phi_.toString()) : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Theta:" << (aEulerAngle.isDefined() ? String::Format("{}", aEulerAngle.theta_.toString()) : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Psi:" << (aEulerAngle.isDefined() ? String::Format("{}", aEulerAngle.psi_.toString()) : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream
    ) << "Axis sequence:"
      << (aEulerAngle.isDefined() ? String::Format("{}", EulerAngle::StringFromAxisSequence(aEulerAngle.axisSequence_))
                                  : "Undefined");

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool EulerAngle::isDefined() const
{
    return phi_.isDefined() && theta_.isDefined() && psi_.isDefined() &&
           axisSequence_ != EulerAngle::AxisSequence::Undefined;
}

bool EulerAngle::isUnitary() const
{
    return phi_.isZero() && theta_.isZero() && psi_.isZero();
}

bool EulerAngle::isNear(const EulerAngle& aEulerAngle, const Angle& anAngularTolerance) const
{
    return Quaternion::EulerAngle(*this).isNear(Quaternion::EulerAngle(aEulerAngle), anAngularTolerance);
}

Angle EulerAngle::getPhi() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Euler Angle");
    }

    return phi_;
}

Angle EulerAngle::getTheta() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Euler Angle");
    }

    return theta_;
}

Angle EulerAngle::getPsi() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Euler Angle");
    }

    return psi_;
}

EulerAngle::AxisSequence EulerAngle::getAxisSequence() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Euler Angle");
    }

    return axisSequence_;
}

Vector3d EulerAngle::toVector(const Angle::Unit& anAngleUnit) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Euler Angle");
    }

    return {phi_.in(anAngleUnit), theta_.in(anAngleUnit), psi_.in(anAngleUnit)};
}

String EulerAngle::toString(const Angle::Unit& anAngleUnit) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Euler Angle");
    }

    return String::Format(
        "[{}, {}, {}] ({})",
        phi_.in(anAngleUnit),
        theta_.in(anAngleUnit),
        psi_.in(anAngleUnit),
        EulerAngle::StringFromAxisSequence(axisSequence_)
    );
}

EulerAngle EulerAngle::Undefined()
{
    return {Angle::Undefined(), Angle::Undefined(), Angle::Undefined(), EulerAngle::AxisSequence::Undefined};
}

EulerAngle EulerAngle::Unit()
{
    return {Angle::Zero(), Angle::Zero(), Angle::Zero(), EulerAngle::AxisSequence::ZYX};
}

EulerAngle EulerAngle::XYZ(const Angle& aFirstAngle, const Angle& aSecondAngle, const Angle& aThirdAngle)
{
    return {aFirstAngle, aSecondAngle, aThirdAngle, EulerAngle::AxisSequence::XYZ};
}

EulerAngle EulerAngle::ZXY(const Angle& aFirstAngle, const Angle& aSecondAngle, const Angle& aThirdAngle)
{
    return {aFirstAngle, aSecondAngle, aThirdAngle, EulerAngle::AxisSequence::ZXY};
}

EulerAngle EulerAngle::ZYX(const Angle& aFirstAngle, const Angle& aSecondAngle, const Angle& aThirdAngle)
{
    return {aFirstAngle, aSecondAngle, aThirdAngle, EulerAngle::AxisSequence::ZYX};
}

EulerAngle EulerAngle::Quaternion(
    const rotation::Quaternion& aQuaternion, const EulerAngle::AxisSequence& anAxisSequence
)
{
    if (!aQuaternion.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Quaternion");
    }

    if (!aQuaternion.isUnitary())
    {
        throw ostk::core::error::RuntimeError("Quaternion is not unitary.");
    }

    const Real q_x = aQuaternion.x();
    const Real q_y = aQuaternion.y();
    const Real q_z = aQuaternion.z();
    const Real q_s = aQuaternion.s();

    Real phi = Real::Undefined();
    Real theta = Real::Undefined();
    Real psi = Real::Undefined();

    switch (anAxisSequence)
    {
        case EulerAngle::AxisSequence::ZYX:  // 3-2-1
        {
            phi = std::atan2(2.0 * (q_x * q_y + q_s * q_z), q_s * q_s - q_z * q_z - q_y * q_y + q_x * q_x);
            theta = std::asin(-2.0 * (q_x * q_z - q_y * q_s));
            psi = std::atan2(2.0 * (q_y * q_z + q_x * q_s), q_s * q_s + q_z * q_z - q_y * q_y - q_x * q_x);
            break;
        }

        default:
            // TBI: This is an inefficient fallback.
            return EulerAngle::RotationMatrix(RotationMatrix::Quaternion(aQuaternion), anAxisSequence);
    }

    // https://math.stackexchange.com/a/55552
    if (phi < 0.0)
    {
        phi = phi + M_PI;
        theta = M_PI - theta;
        psi = psi + M_PI;
    }

    return EulerAngle::ZYX(Angle::Radians(phi), Angle::Radians(theta), Angle::Radians(psi));
}

EulerAngle EulerAngle::RotationVector(
    const rotation::RotationVector& aRotationVector, const EulerAngle::AxisSequence& anAxisSequence
)
{
    return EulerAngle::Quaternion(Quaternion::RotationVector(aRotationVector), anAxisSequence);
}

EulerAngle EulerAngle::RotationMatrix(
    const rotation::RotationMatrix& aRotationMatrix, const EulerAngle::AxisSequence& anAxisSequence
)
{
    if (!aRotationMatrix.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Rotation Matrix");
    }

    Real phi = Real::Undefined();
    Real theta = Real::Undefined();
    Real psi = Real::Undefined();

    switch (anAxisSequence)
    {
        case EulerAngle::AxisSequence::XYZ:  // 1-2-3
        {
            phi = std::atan2(-aRotationMatrix(2, 1), aRotationMatrix(2, 2));
            theta = std::asin(aRotationMatrix(2, 0));
            psi = std::atan2(-aRotationMatrix(1, 0), aRotationMatrix(0, 0));
            break;
        }

        case EulerAngle::AxisSequence::ZXY:  // 3-1-2
        {
            phi = std::atan2(-aRotationMatrix(1, 0), aRotationMatrix(1, 1));
            theta = std::asin(aRotationMatrix(1, 2));
            psi = std::atan2(-aRotationMatrix(0, 2), aRotationMatrix(2, 2));
            break;
        }

        case EulerAngle::AxisSequence::ZYX:  // 3-2-1
        {
            phi = std::atan2(aRotationMatrix(0, 1), aRotationMatrix(0, 0));
            theta = std::asin(-aRotationMatrix(0, 2));
            psi = std::atan2(aRotationMatrix(1, 2), aRotationMatrix(2, 2));
            break;
        }

        default:
            throw ostk::core::error::runtime::ToBeImplemented("Axis sequence is not supported.");
    }

    // https://math.stackexchange.com/a/55552
    if (phi < 0.0)
    {
        phi = phi + M_PI;
        theta = M_PI - theta;
        psi = psi + M_PI;
    }

    return EulerAngle::ZYX(Angle::Radians(phi), Angle::Radians(theta), Angle::Radians(psi));
}

String EulerAngle::StringFromAxisSequence(const EulerAngle::AxisSequence& anAxisSequence)
{
    switch (anAxisSequence)
    {
        case EulerAngle::AxisSequence::XYZ:
            return "XYZ";

        case EulerAngle::AxisSequence::ZXY:
            return "ZXY";

        case EulerAngle::AxisSequence::ZYX:
            return "ZYX";

        default:
            throw ostk::core::error::runtime::Wrong("Axis sequence");
    }
}

}  // namespace rotation
}  // namespace transformation
}  // namespace d3
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk
