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

RotationVector::RotationVector(const Vector3d& anAxis, const Angle& anAngle)
    : axis_(anAxis.isDefined() ? anAxis.normalized() : Vector3d::Undefined()),
      angle_(anAngle)
{
    if (anAxis.isDefined() && (std::abs(anAxis.norm() - 1.0) > Real::Epsilon()))
    {
        throw ostk::core::error::RuntimeError("Axis with norm [{}] is not unitary.", anAxis.norm());
    }
}

RotationVector::RotationVector(const Vector3d& aVector, const Angle::Unit& anAngleUnit)
    : axis_(aVector.isDefined() ? aVector.normalized() : Vector3d::Undefined()),
      angle_(Angle(aVector.norm(), anAngleUnit))
{
    if (axis_ == Vector3d::Zero())
    {
        axis_ = Vector3d::Z();
    }
}

bool RotationVector::operator==(const RotationVector& aRotationVector) const
{
    if ((!this->isDefined()) || (!aRotationVector.isDefined()))
    {
        return false;
    }

    if (angle_.isZero() && aRotationVector.angle_.isZero())
    {
        return true;
    }

    return ((axis_ == aRotationVector.axis_) && (angle_ == aRotationVector.angle_)) ||
           ((axis_ == -aRotationVector.axis_) && (angle_ == -aRotationVector.angle_));
}

bool RotationVector::operator!=(const RotationVector& aRotationVector) const
{
    return !((*this) == aRotationVector);
}

std::ostream& operator<<(std::ostream& anOutputStream, const RotationVector& aRotationVector)
{
    ostk::core::utils::Print::Header(anOutputStream, "Rotation Vector");

    ostk::core::utils::Print::Line(anOutputStream)
        << "Axis:" << (aRotationVector.isDefined() ? aRotationVector.getAxis().toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Angle:" << (aRotationVector.isDefined() ? aRotationVector.getAngle().toString() : "Undefined");

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool RotationVector::isDefined() const
{
    return axis_.isDefined() && angle_.isDefined();
}

Vector3d RotationVector::getAxis() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Rotation vector");
    }

    return axis_;
}

Angle RotationVector::getAngle() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Rotation vector");
    }

    return angle_;
}

RotationVector& RotationVector::rectify()
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Rotation vector");
    }

    if (angle_.isNegative())
    {
        axis_ = -axis_;
        angle_ = -angle_;
    }

    if (angle_.inRadians() > Angle::Pi().inRadians())
    {
        axis_ = -axis_;
        angle_ = Angle::TwoPi() - angle_;
    }

    return *this;
}

String RotationVector::toString(const Integer& aPrecision) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Rotation vector");
    }

    return String::Format(
        "{} : {}", (aPrecision.isDefined() ? axis_.toString(aPrecision) : axis_.toString()), angle_.toString(aPrecision)
    );
}

RotationVector RotationVector::Undefined()
{
    return {};
}

RotationVector RotationVector::Unit()
{
    return {Vector3d::Z(), Angle::Zero()};
}

RotationVector RotationVector::X(const Angle& anAngle)
{
    if (!anAngle.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    return {Vector3d::X(), anAngle};
}

RotationVector RotationVector::Y(const Angle& anAngle)
{
    if (!anAngle.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    return {Vector3d::Y(), anAngle};
}

RotationVector RotationVector::Z(const Angle& anAngle)
{
    if (!anAngle.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Angle");
    }

    return {Vector3d::Z(), anAngle};
}

RotationVector RotationVector::Quaternion(const rotation::Quaternion& aQuaternion)
{
    if (!aQuaternion.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Quaternion");
    }

    if (!aQuaternion.isUnitary())
    {
        throw ostk::core::error::RuntimeError("Quaternion is not unitary.");
    }

    if ((aQuaternion == Quaternion::Unit()) || (aQuaternion.s().abs() == 1.0))
    {
        return RotationVector::Unit();
    }

    const Vector3d axis = (aQuaternion.getVectorPart() / (1.0 - aQuaternion.s() * aQuaternion.s()).sqrt()).normalized();
    const Angle angle = Angle::Radians(2.0 * std::acos(aQuaternion.s()));

    return RotationVector(axis, angle);
}

RotationVector RotationVector::RotationMatrix(const rotation::RotationMatrix& aRotationMatrix)
{
    if (!aRotationMatrix.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Rotation matrix");
    }

    const Angle angle = Angle::Radians(std::acos((aRotationMatrix.accessMatrix().trace() - 1.0) / 2.0));

    if (angle.inRadians().abs() < Real::Epsilon())
    {
        return RotationVector(Vector3d::X(), angle);
    }

    const double x = aRotationMatrix(1, 2) - aRotationMatrix(2, 1);
    const double y = aRotationMatrix(2, 0) - aRotationMatrix(0, 2);
    const double z = aRotationMatrix(0, 1) - aRotationMatrix(1, 0);

    // const Vector3d axis = (1.0 / (2.0 * std::sin(angle.inRadians()))) * Vector3d(x, y, z) ;
    const Vector3d axis = Vector3d(x, y, z).normalized();

    return RotationVector(axis, angle);
}

RotationVector RotationVector::EulerAngle(const rotation::EulerAngle& aEulerAngle)
{
    return RotationVector::Quaternion(Quaternion::EulerAngle(aEulerAngle));
}

RotationVector::RotationVector()
    : axis_(Vector3d::Undefined()),
      angle_(Angle::Undefined())
{
}

}  // namespace rotation
}  // namespace transformation
}  // namespace d3
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk
