// Copyright © Loft Orbital Solutions Inc.

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationMatrix.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>

namespace ostk
{
namespace math
{
namespace geom
{
namespace d3
{
namespace trf
{
namespace rot
{

Quaternion::Quaternion(
    const Real& aFirstComponent,
    const Real& aSecondComponent,
    const Real& aThirdComponent,
    const Real& aFourthComponent,
    const Quaternion::Format& aFormat
)
    : x_((aFormat == Quaternion::Format::XYZS) ? aFirstComponent : aSecondComponent),
      y_((aFormat == Quaternion::Format::XYZS) ? aSecondComponent : aThirdComponent),
      z_((aFormat == Quaternion::Format::XYZS) ? aThirdComponent : aFourthComponent),
      s_((aFormat == Quaternion::Format::XYZS) ? aFourthComponent : aFirstComponent)
{
}

Quaternion::Quaternion(const Vector4d& aVector, const Quaternion::Format& aFormat)
    : x_((aFormat == Quaternion::Format::XYZS) ? aVector(0) : aVector(1)),
      y_((aFormat == Quaternion::Format::XYZS) ? aVector(1) : aVector(2)),
      z_((aFormat == Quaternion::Format::XYZS) ? aVector(2) : aVector(3)),
      s_((aFormat == Quaternion::Format::XYZS) ? aVector(3) : aVector(0))
{
}

Quaternion::Quaternion(const Vector3d& aVectorPart, const Real& aScalarPart)
    : x_(aVectorPart.x()),
      y_(aVectorPart.y()),
      z_(aVectorPart.z()),
      s_(aScalarPart)
{
}

bool Quaternion::operator==(const Quaternion& aQuaternion) const
{
    if ((!this->isDefined()) || (!aQuaternion.isDefined()))
    {
        return false;
    }

    return ((x_ == +aQuaternion.x_) && (y_ == +aQuaternion.y_) && (z_ == +aQuaternion.z_) && (s_ == +aQuaternion.s_)) ||
           ((x_ == -aQuaternion.x_) && (y_ == -aQuaternion.y_) && (z_ == -aQuaternion.z_) && (s_ == -aQuaternion.s_));
}

bool Quaternion::operator!=(const Quaternion& aQuaternion) const
{
    return !((*this) == aQuaternion);
}

Quaternion Quaternion::operator+(const Quaternion& aQuaternion) const
{
    return Quaternion(
        this->getVectorPart() + aQuaternion.getVectorPart(), this->getScalarPart() + aQuaternion.getScalarPart()
    );
}

Quaternion Quaternion::operator*(const Quaternion& aQuaternion) const
{
    return this->crossMultiply(aQuaternion);
}

Vector3d Quaternion::operator*(const Vector3d& aVector) const
{
    return this->rotateVector(aVector);
}

Quaternion Quaternion::operator*(const Real& aScalar) const
{
    return Quaternion(this->getVectorPart() * aScalar, this->getScalarPart() * aScalar);
}

Quaternion operator*(const Real& aScalar, const Quaternion& aQuaternion)
{
    return aQuaternion * aScalar;
}

Quaternion Quaternion::operator/(const Quaternion& aQuaternion) const
{
    if (aQuaternion.norm() < Real::Epsilon())
    {
        throw ostk::core::error::RuntimeError("Cannot divide by quaternion with zero norm.");
    }

    return this->crossMultiply(aQuaternion.toInverse());
}

Quaternion Quaternion::operator^(const Real& aScalar) const
{
    return this->pow(aScalar);
}

Quaternion& Quaternion::operator+=(const Quaternion& aQuaternion)
{
    if ((!this->isDefined()) || (!aQuaternion.isDefined()))
    {
        throw ostk::core::error::runtime::Undefined("Quaternion");
    }

    x_ += aQuaternion.x_;
    y_ += aQuaternion.y_;
    z_ += aQuaternion.z_;
    s_ += aQuaternion.s_;

    return *this;
}

Quaternion& Quaternion::operator*=(const Quaternion& aQuaternion)
{
    (*this) = this->crossMultiply(aQuaternion);  // [TBI] This is a shortcut... could be optimized

    return *this;
}

Quaternion& Quaternion::operator/=(const Quaternion& aQuaternion)
{
    if (aQuaternion.norm() < Real::Epsilon())
    {
        throw ostk::core::error::RuntimeError("Cannot divide by quaternion with zero norm.");
    }

    (*this) = this->crossMultiply(aQuaternion.toInverse());  // [TBI] This is a shortcut... could be optimized

    return *this;
}

std::ostream& operator<<(std::ostream& anOutputStream, const Quaternion& aQuaternion)
{
    ostk::core::utils::Print::Header(anOutputStream, "Quaternion");

    ostk::core::utils::Print::Line(anOutputStream)
        << "X:" << (aQuaternion.isDefined() ? String::Format("{:15f}", aQuaternion.x_) : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Y:" << (aQuaternion.isDefined() ? String::Format("{:15f}", aQuaternion.y_) : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Z:" << (aQuaternion.isDefined() ? String::Format("{:15f}", aQuaternion.z_) : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "S:" << (aQuaternion.isDefined() ? String::Format("{:15f}", aQuaternion.s_) : "Undefined");

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool Quaternion::isDefined() const
{
    return x_.isDefined() && y_.isDefined() && z_.isDefined() && s_.isDefined();
}

bool Quaternion::isUnitary() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Quaternion");
    }

    return std::abs(((x_ * x_) + (y_ * y_) + (z_ * z_) + (s_ * s_)) - 1.0) <= Real::Epsilon();
}

bool Quaternion::isNear(const Quaternion& aQuaternion, const Angle& anAngularTolerance) const
{
    if (!anAngularTolerance.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Angular tolerance");
    }

    return this->angularDifferenceWith(aQuaternion).inRadians(0.0, Real::TwoPi()) <=
           anAngularTolerance.inRadians(0.0, Real::TwoPi());
}

Real Quaternion::x() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Quaternion");
    }

    return x_;
}

Real Quaternion::y() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Quaternion");
    }

    return y_;
}

Real Quaternion::z() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Quaternion");
    }

    return z_;
}

Real Quaternion::s() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Quaternion");
    }

    return s_;
}

Vector3d Quaternion::getVectorPart() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Quaternion");
    }

    return {x_, y_, z_};
}

Real Quaternion::getScalarPart() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Quaternion");
    }

    return s_;
}

Quaternion Quaternion::toNormalized() const
{
    return Quaternion(*this).normalize();
}

Quaternion Quaternion::toConjugate() const
{
    return Quaternion(*this).conjugate();
}

Quaternion Quaternion::toInverse() const
{
    return Quaternion(*this).inverse();
}

Quaternion Quaternion::exp() const
{
    // Ref.: http://www.neil.dantam.name/note/dantam-quaternion.pdf, II-F

    const Vector3d v = this->getVectorPart();
    const Real v_norm = v.norm();

    if (v_norm <= Real::Epsilon())
    {
        return Quaternion::Unit();
    }

    return std::exp(s_) * Quaternion(v * sin(v_norm) / v_norm, cos(v_norm));
}

Quaternion Quaternion::log() const
{
    // Ref.: http://www.neil.dantam.name/note/dantam-quaternion.pdf, II-G

    const Vector3d v = this->getVectorPart();
    const Real v_norm = v.norm();

    if (v_norm <= Real::Epsilon())
    {
        return Quaternion({0.0, 0.0, 0.0}, std::log(this->norm()));
    }

    return Quaternion(std::atan2(v_norm, s_) / v_norm * v, std::log(this->norm()));
}

Quaternion Quaternion::pow(const Real& aValue) const
{
    // Ref.: http://www.neil.dantam.name/note/dantam-quaternion.pdf, II-H

    return ((this->log()) * aValue).exp();
}

Real Quaternion::norm() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Quaternion");
    }

    return ((x_ * x_) + (y_ * y_) + (z_ * z_) + (s_ * s_)).sqrt();
}

Quaternion Quaternion::crossMultiply(const Quaternion& aQuaternion) const
{
    const Vector3d leftVectorPart = this->getVectorPart();
    const Real& leftScalarPart = s_;

    const Vector3d rightVectorPart = aQuaternion.getVectorPart();
    const Real& rightScalarPart = aQuaternion.s_;

    const Vector3d vectorPart =
        (rightScalarPart * leftVectorPart) + (leftScalarPart * rightVectorPart) - leftVectorPart.cross(rightVectorPart);
    const Real scalarPart = (leftScalarPart * rightScalarPart) - leftVectorPart.dot(rightVectorPart);

    return {vectorPart, scalarPart};
}

Quaternion Quaternion::dotMultiply(const Quaternion& aQuaternion) const
{
    const Vector3d leftVectorPart = this->getVectorPart();
    const Real& leftScalarPart = s_;

    const Vector3d rightVectorPart = aQuaternion.getVectorPart();
    const Real& rightScalarPart = aQuaternion.s_;

    const Vector3d vectorPart =
        (rightScalarPart * leftVectorPart) + (leftScalarPart * rightVectorPart) + leftVectorPart.cross(rightVectorPart);
    const Real scalarPart = (leftScalarPart * rightScalarPart) - leftVectorPart.dot(rightVectorPart);

    return {vectorPart, scalarPart};
}

Real Quaternion::dotProduct(const Quaternion& aQuaternion) const
{
    if ((!this->isDefined()) || (!aQuaternion.isDefined()))
    {
        throw ostk::core::error::runtime::Undefined("Quaternion");
    }

    return (x_ * aQuaternion.x_) + (y_ * aQuaternion.y_) + (z_ * aQuaternion.z_) + (s_ * aQuaternion.s_);
}

Vector3d Quaternion::rotateVector(const Vector3d& aVector) const
{
    if (!aVector.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Vector");
    }

    if (!this->isUnitary())
    {
        throw ostk::core::error::RuntimeError("Quaternion with norm [{}] is not unitary.", this->norm());
    }

    return this->crossMultiply(Quaternion(aVector, 0.0)).crossMultiply(this->toConjugate()).getVectorPart();
}

Vector4d Quaternion::toVector(const Quaternion::Format& aFormat) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Quaternion");
    }

    switch (aFormat)
    {
        case Quaternion::Format::XYZS:
            return Vector4d(x_, y_, z_, s_);

        case Quaternion::Format::SXYZ:
            return Vector4d(s_, x_, y_, z_);

        default:
            throw ostk::core::error::runtime::Wrong("Format");
            break;
    }

    return Vector4d::Undefined();
}

String Quaternion::toString(const Quaternion::Format& aFormat) const
{
    return this->toVector(aFormat).toString();
}

String Quaternion::toString(const Integer& aPrecision, const Quaternion::Format& aFormat) const
{
    return aPrecision.isDefined() ? this->toVector(aFormat).toString(aPrecision) : this->toVector(aFormat).toString();
}

Quaternion& Quaternion::normalize()
{
    const Real norm = this->norm();

    if (norm.abs() < Real::Epsilon())
    {
        throw ostk::core::error::RuntimeError("Quaternion norm is zero.");
    }

    x_ /= norm;
    y_ /= norm;
    z_ /= norm;
    s_ /= norm;

    return *this;
}

Quaternion& Quaternion::conjugate()
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Quaternion");
    }

    x_ = -x_;
    y_ = -y_;
    z_ = -z_;

    return *this;
}

Quaternion& Quaternion::inverse()
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Quaternion");
    }

    const Real reducedNorm = (x_ * x_) + (y_ * y_) + (z_ * z_) + (s_ * s_);

    if (reducedNorm.abs() < Real::Epsilon())
    {
        throw ostk::core::error::RuntimeError("Quaternion norm is zero.");
    }

    x_ = -x_ / reducedNorm;
    y_ = -y_ / reducedNorm;
    z_ = -z_ / reducedNorm;
    s_ = +s_ / reducedNorm;

    return *this;
}

Quaternion& Quaternion::rectify()
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Quaternion");
    }

    if (s_ < 0.0)
    {
        x_ = -x_;
        y_ = -y_;
        z_ = -z_;
        s_ = -s_;
    }

    return *this;
}

Angle Quaternion::angularDifferenceWith(const Quaternion& aQuaternion) const
{
    if ((!this->isUnitary()) || (!aQuaternion.isUnitary()))
    {
        throw ostk::core::error::RuntimeError("Quaternion is not unitary.");
    }

    const Quaternion deltaQuaternion = ((*this) / aQuaternion).normalize();

    return Angle::Radians(2.0 * std::acos(std::abs(deltaQuaternion.s_)));
}

Quaternion Quaternion::Undefined()
{
    return {Real::Undefined(), Real::Undefined(), Real::Undefined(), Real::Undefined(), Quaternion::Format::XYZS};
}

Quaternion Quaternion::Unit()
{
    return {0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS};
}

Quaternion Quaternion::XYZS(
    const Real& aFirstComponent, const Real& aSecondComponent, const Real& aThirdComponent, const Real& aFourthComponent
)
{
    return {aFirstComponent, aSecondComponent, aThirdComponent, aFourthComponent, Quaternion::Format::XYZS};
}

Quaternion Quaternion::RotationVector(const rot::RotationVector& aRotationVector)
{
    /// @ref Markley F. L.: Fundamentals of Spacecraft Attitude Determination and Control, 45

    const Real rotationAngle_rad = aRotationVector.getAngle().inRadians();

    const Vector3d vectorPart = std::sin(rotationAngle_rad / 2.0) * aRotationVector.getAxis();
    const Real scalarPart = std::cos(rotationAngle_rad / 2.0);

    return Quaternion(vectorPart, scalarPart).normalize();
}

Quaternion Quaternion::RotationMatrix(const rot::RotationMatrix& aRotationMatrix)
{
    /// @ref Markley F. L.: Fundamentals of Spacecraft Attitude Determination and Control, 48
    /// @note Should we use this method instead?
    /// https://d3cw3dd2w32x2b.cloudfront.net/wp-content/uploads/2015/01/matrix-to-quat.pdf

    const Real trace = aRotationMatrix.accessMatrix().trace();

    const Real rotationMatrix_11 = aRotationMatrix(0, 0);
    const Real rotationMatrix_12 = aRotationMatrix(0, 1);
    const Real rotationMatrix_13 = aRotationMatrix(0, 2);

    const Real rotationMatrix_21 = aRotationMatrix(1, 0);
    const Real rotationMatrix_22 = aRotationMatrix(1, 1);
    const Real rotationMatrix_23 = aRotationMatrix(1, 2);

    const Real rotationMatrix_31 = aRotationMatrix(2, 0);
    const Real rotationMatrix_32 = aRotationMatrix(2, 1);
    const Real rotationMatrix_33 = aRotationMatrix(2, 2);

    Real x = Real::Undefined();
    Real y = Real::Undefined();
    Real z = Real::Undefined();
    Real s = Real::Undefined();

    if ((trace >= rotationMatrix_11) && (trace >= rotationMatrix_22) && (trace >= rotationMatrix_33))
    {
        x = rotationMatrix_23 - rotationMatrix_32;
        y = rotationMatrix_31 - rotationMatrix_13;
        z = rotationMatrix_12 - rotationMatrix_21;
        s = 1.0 + trace;
    }
    else if ((rotationMatrix_11 >= trace) && (rotationMatrix_11 >= rotationMatrix_22) && (rotationMatrix_11 >= rotationMatrix_33))
    {
        x = 1.0 + 2.0 * rotationMatrix_11 - trace;
        y = rotationMatrix_12 + rotationMatrix_21;
        z = rotationMatrix_13 + rotationMatrix_31;
        s = rotationMatrix_23 - rotationMatrix_32;
    }
    else if ((rotationMatrix_22 >= rotationMatrix_11) && (rotationMatrix_22 >= trace) && (rotationMatrix_22 >= rotationMatrix_33))
    {
        x = rotationMatrix_21 + rotationMatrix_12;
        y = 1.0 + 2.0 * rotationMatrix_22 - trace;
        z = rotationMatrix_23 + rotationMatrix_32;
        s = rotationMatrix_31 - rotationMatrix_13;
    }
    else if ((rotationMatrix_33 >= rotationMatrix_11) && (rotationMatrix_33 >= rotationMatrix_22) && (rotationMatrix_33 >= trace))
    {
        x = rotationMatrix_31 + rotationMatrix_13;
        y = rotationMatrix_32 + rotationMatrix_23;
        z = 1.0 + 2.0 * rotationMatrix_33 - trace;
        s = rotationMatrix_12 - rotationMatrix_21;
    }
    else
    {
        throw ostk::core::error::RuntimeError("Rotation matrix cannot be converted into quaternion.");
    }

    return Quaternion::XYZS(x, y, z, s).normalize();
}

Quaternion Quaternion::Parse(const String& aString, const Quaternion::Format& aFormat)
{
    using ostk::math::obj::VectorXd;

    if (aString.isEmpty())
    {
        throw ostk::core::error::runtime::Undefined("String");
    }

    const VectorXd vector = VectorXd::Parse(aString);

    if (vector.size() != 4)
    {
        throw ostk::core::error::RuntimeError("Vector size is not 4.");
    }

    return {vector, aFormat};
}

Quaternion Quaternion::ShortestRotation(const Vector3d& aFirstVector, const Vector3d& aSecondVector)
{
    if (!aFirstVector.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("First vector");
    }

    if (!aSecondVector.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Second vector");
    }

    const Vector3d firstNormalizedVector = aFirstVector.normalized();
    const Vector3d secondNormalizedVector = aSecondVector.normalized();

    const Vector3d orthogonalVector = secondNormalizedVector.cross(firstNormalizedVector);
    const Real dotProduct = firstNormalizedVector.dot(secondNormalizedVector);

    return Quaternion::XYZS(orthogonalVector.x(), orthogonalVector.y(), orthogonalVector.z(), 1.0 + dotProduct)
        .toNormalized();
}

Quaternion Quaternion::LERP(const Quaternion& aFirstQuaternion, const Quaternion& aSecondQuaternion, const Real& aRatio)
{
    if (!aRatio.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ratio");
    }

    if ((aRatio < 0.0) || (aRatio > 1.0))
    {
        throw ostk::core::error::RuntimeError("Ratio [{}] not in [0, 1] interval.", aRatio);
    }

    return (aFirstQuaternion * (1.0 - aRatio) + aSecondQuaternion * aRatio);
}

Quaternion Quaternion::NLERP(
    const Quaternion& aFirstQuaternion, const Quaternion& aSecondQuaternion, const Real& aRatio
)
{
    return Quaternion::LERP(aFirstQuaternion, aSecondQuaternion, aRatio).toNormalized();
}

Quaternion Quaternion::SLERP(
    const Quaternion& aFirstQuaternion, const Quaternion& aSecondQuaternion, const Real& aRatio
)
{
    if (!aRatio.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Ratio");
    }

    if ((aRatio < 0.0) || (aRatio > 1.0))
    {
        throw ostk::core::error::RuntimeError("Ratio [{}] not in [0, 1] interval.", aRatio);
    }

    if (aFirstQuaternion.dotProduct(aSecondQuaternion) >= 0.0)
    {
        return (aFirstQuaternion * ((aFirstQuaternion.toInverse() * aSecondQuaternion) ^ aRatio)).toNormalized();
    }

    return (aFirstQuaternion * ((aFirstQuaternion.toInverse() * (-1.0) * aSecondQuaternion) ^ aRatio)).toNormalized();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}  // namespace rot
}  // namespace trf
}  // namespace d3
}  // namespace geom
}  // namespace math
}  // namespace ostk

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
