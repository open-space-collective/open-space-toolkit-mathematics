/// Apache License 2.0

#include <cmath>

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
    : axis_(anAxis.normalized()),
      angle_(anAngle)
{
    if (std::abs(anAxis.norm() - 1.0) > 1e-15)
    {
        throw ostk::core::error::RuntimeError("Axis with norm [{}] is not unitary.", anAxis.norm());
    }
}

RotationVector::RotationVector(const Vector3d& aVector, const Angle::Unit& anAngleUnit)
    : axis_(aVector.normalized()),
      angle_(Angle(aVector.norm(), anAngleUnit))
{
    if (axis_ == Vector3d::Zero())
    {
        axis_ = Vector3d::Z();
    }
}

bool RotationVector::operator==(const RotationVector& aRotationVector) const
{
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

    ostk::core::utils::Print::Line(anOutputStream) << "Axis:" << aRotationVector.getAxis().toString();
    ostk::core::utils::Print::Line(anOutputStream) << "Angle:" << aRotationVector.getAngle().toString();

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

const Vector3d& RotationVector::getAxis() const
{
    return axis_;
}

const Angle& RotationVector::getAngle() const
{
    return angle_;
}

RotationVector& RotationVector::rectify()
{
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

String RotationVector::toString(int aPrecision) const
{
    return String::Format(
        "{} : {}", ((aPrecision >= 0) ? axis_.toString(aPrecision) : axis_.toString()), angle_.toString(aPrecision)
    );
}

RotationVector RotationVector::Unit()
{
    return {Vector3d::Z(), Angle::Zero()};
}

RotationVector RotationVector::X(const Angle& anAngle)
{
    return {Vector3d::X(), anAngle};
}

RotationVector RotationVector::Y(const Angle& anAngle)
{
    return {Vector3d::Y(), anAngle};
}

RotationVector RotationVector::Z(const Angle& anAngle)
{
    return {Vector3d::Z(), anAngle};
}

RotationVector RotationVector::Quaternion(const rotation::Quaternion& aQuaternion)
{
    return RotationVector::Quaternion(aQuaternion, false);
}

RotationVector RotationVector::Quaternion(const rotation::Quaternion& aQuaternion, const bool& aRectifyFlag)
{
    rotation::Quaternion quaternion = aQuaternion;

    if (aRectifyFlag)
    {
        quaternion.normalize().rectify();
    }
    else if (!quaternion.isUnitary())
    {
        throw ostk::core::error::RuntimeError("Quaternion is not unitary.");
    }

    if ((quaternion == Quaternion::Unit()) || (std::abs(quaternion.s()) == 1.0))
    {
        return RotationVector::Unit();
    }

    const Vector3d axis = (quaternion.getVectorPart() / std::sqrt(1.0 - quaternion.s() * quaternion.s())).normalized();
    const Angle angle = Angle::Radians(2.0 * std::acos(quaternion.s()));

    return RotationVector(axis, angle);
}

RotationVector RotationVector::RotationMatrix(const rotation::RotationMatrix& aRotationMatrix)
{
    const Angle angle = Angle::Radians(std::acos((aRotationMatrix.getMatrix().trace() - 1.0) / 2.0));

    if (std::abs(angle.inRadians()) < 1e-15)
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

}  // namespace rotation
}  // namespace transformation
}  // namespace d3
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk
