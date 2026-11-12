/// Apache License 2.0

#include <cmath>
#include <limits>

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

Quaternion::Quaternion(
    double aFirstComponent,
    double aSecondComponent,
    double aThirdComponent,
    double aFourthComponent,
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

Quaternion::Quaternion(const Vector3d& aVectorPart, double aScalarPart)
    : x_(aVectorPart.x()),
      y_(aVectorPart.y()),
      z_(aVectorPart.z()),
      s_(aScalarPart)
{
}

bool Quaternion::operator==(const Quaternion& aQuaternion) const
{
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

Quaternion Quaternion::operator*(double aScalar) const
{
    if (std::isnan(aScalar))
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    return Quaternion(this->getVectorPart() * aScalar, this->getScalarPart() * aScalar);
}

Quaternion operator*(double aScalar, const Quaternion& aQuaternion)
{
    return aQuaternion * aScalar;
}

Quaternion Quaternion::operator/(const Quaternion& aQuaternion) const
{
    if (aQuaternion.norm() < 1e-15)
    {
        throw ostk::core::error::RuntimeError("Cannot divide by quaternion with zero norm.");
    }

    return this->crossMultiply(aQuaternion.toInverse());
}

Quaternion Quaternion::operator^(double aScalar) const
{
    return this->pow(aScalar);
}

Quaternion& Quaternion::operator+=(const Quaternion& aQuaternion)
{
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
    if (aQuaternion.norm() < 1e-15)
    {
        throw ostk::core::error::RuntimeError("Cannot divide by quaternion with zero norm.");
    }

    (*this) = this->crossMultiply(aQuaternion.toInverse());  // [TBI] This is a shortcut... could be optimized

    return *this;
}

std::ostream& operator<<(std::ostream& anOutputStream, const Quaternion& aQuaternion)
{
    ostk::core::utils::Print::Header(anOutputStream, "Quaternion");

    ostk::core::utils::Print::Line(anOutputStream) << "X:" << String::Format("{:15f}", aQuaternion.x_);
    ostk::core::utils::Print::Line(anOutputStream) << "Y:" << String::Format("{:15f}", aQuaternion.y_);
    ostk::core::utils::Print::Line(anOutputStream) << "Z:" << String::Format("{:15f}", aQuaternion.z_);
    ostk::core::utils::Print::Line(anOutputStream) << "S:" << String::Format("{:15f}", aQuaternion.s_);

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool Quaternion::isUnitary(double aNormTolerance) const
{
    if (std::isnan(aNormTolerance) || aNormTolerance <= 0.0)
    {
        throw ostk::core::error::runtime::Undefined("Norm tolerance");
    }

    return std::abs(this->norm() - 1.0) <= aNormTolerance;
}

bool Quaternion::isNear(const Quaternion& aQuaternion, const Angle& anAngularTolerance) const
{
    return this->angularDifferenceWith(aQuaternion).inRadians(0.0, 2.0 * M_PI) <=
           anAngularTolerance.inRadians(0.0, 2.0 * M_PI);
}

double Quaternion::x() const
{
    return x_;
}

double Quaternion::y() const
{
    return y_;
}

double Quaternion::z() const
{
    return z_;
}

double Quaternion::s() const
{
    return s_;
}

Vector3d Quaternion::getVectorPart() const
{
    return {x_, y_, z_};
}

double Quaternion::getScalarPart() const
{
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

Quaternion Quaternion::toRectify() const
{
    return Quaternion(*this).rectify();
}

Quaternion Quaternion::exp() const
{
    // Ref.: http://www.neil.dantam.name/note/dantam-quaternion.pdf, II-F

    const Vector3d v = this->getVectorPart();
    const double v_norm = v.norm();

    if (v_norm <= 1e-15)
    {
        return Quaternion::Unit();
    }

    return std::exp(s_) * Quaternion(v * sin(v_norm) / v_norm, cos(v_norm));
}

Quaternion Quaternion::log() const
{
    // Ref.: http://www.neil.dantam.name/note/dantam-quaternion.pdf, II-G

    const Vector3d v = this->getVectorPart();
    const double v_norm = v.norm();

    if (v_norm <= 1e-15)
    {
        return Quaternion({0.0, 0.0, 0.0}, std::log(this->norm()));
    }

    return Quaternion(std::atan2(v_norm, s_) / v_norm * v, std::log(this->norm()));
}

Quaternion Quaternion::pow(double aValue) const
{
    // Ref.: http://www.neil.dantam.name/note/dantam-quaternion.pdf, II-H

    return ((this->log()) * aValue).exp();
}

double Quaternion::norm() const
{
    return std::sqrt((x_ * x_) + (y_ * y_) + (z_ * z_) + (s_ * s_));
}

Quaternion Quaternion::crossMultiply(const Quaternion& aQuaternion) const
{
    const Vector3d leftVectorPart = this->getVectorPart();
    const double& leftScalarPart = s_;

    const Vector3d rightVectorPart = aQuaternion.getVectorPart();
    const double& rightScalarPart = aQuaternion.s_;

    const Vector3d vectorPart =
        (rightScalarPart * leftVectorPart) + (leftScalarPart * rightVectorPart) - leftVectorPart.cross(rightVectorPart);
    const double scalarPart = (leftScalarPart * rightScalarPart) - leftVectorPart.dot(rightVectorPart);

    return {vectorPart, scalarPart};
}

Quaternion Quaternion::dotMultiply(const Quaternion& aQuaternion) const
{
    const Vector3d leftVectorPart = this->getVectorPart();
    const double& leftScalarPart = s_;

    const Vector3d rightVectorPart = aQuaternion.getVectorPart();
    const double& rightScalarPart = aQuaternion.s_;

    const Vector3d vectorPart =
        (rightScalarPart * leftVectorPart) + (leftScalarPart * rightVectorPart) + leftVectorPart.cross(rightVectorPart);
    const double scalarPart = (leftScalarPart * rightScalarPart) - leftVectorPart.dot(rightVectorPart);

    return {vectorPart, scalarPart};
}

double Quaternion::dotProduct(const Quaternion& aQuaternion) const
{
    return (x_ * aQuaternion.x_) + (y_ * aQuaternion.y_) + (z_ * aQuaternion.z_) + (s_ * aQuaternion.s_);
}

Vector3d Quaternion::rotateVector(const Vector3d& aVector, double aNormTolerance) const
{
    if (!this->isUnitary(aNormTolerance))
    {
        throw ostk::core::error::RuntimeError("Quaternion with norm [{}] is not unitary.", this->norm());
    }

    return this->crossMultiply(Quaternion(aVector, 0.0)).crossMultiply(this->toConjugate()).getVectorPart();
}

Vector4d Quaternion::toVector(const Quaternion::Format& aFormat) const
{
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
}

String Quaternion::toString(const Quaternion::Format& aFormat) const
{
    return this->toVector(aFormat).toString();
}

String Quaternion::toString(int aPrecision, const Quaternion::Format& aFormat) const
{
    return (aPrecision >= 0) ? this->toVector(aFormat).toString(aPrecision) : this->toVector(aFormat).toString();
}

Quaternion& Quaternion::normalize()
{
    const double norm = this->norm();

    if (std::abs(norm) < 1e-15)
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
    x_ = -x_;
    y_ = -y_;
    z_ = -z_;

    return *this;
}

Quaternion& Quaternion::inverse()
{
    const double reducedNorm = (x_ * x_) + (y_ * y_) + (z_ * z_) + (s_ * s_);

    if (std::abs(reducedNorm) < 1e-15)
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

Quaternion Quaternion::Unit()
{
    return {0.0, 0.0, 0.0, 1.0, Quaternion::Format::XYZS};
}

Quaternion Quaternion::XYZS(
    double aFirstComponent, double aSecondComponent, double aThirdComponent, double aFourthComponent
)
{
    return {aFirstComponent, aSecondComponent, aThirdComponent, aFourthComponent, Quaternion::Format::XYZS};
}

Quaternion Quaternion::RotationVector(const rotation::RotationVector& aRotationVector)
{
    /// @ref Markley F. L.: Fundamentals of Spacecraft Attitude Determination and Control, 45

    const double rotationAngle_rad = aRotationVector.getAngle().inRadians();

    const Vector3d vectorPart = std::sin(rotationAngle_rad / 2.0) * aRotationVector.getAxis();
    const double scalarPart = std::cos(rotationAngle_rad / 2.0);

    return Quaternion(vectorPart, scalarPart).normalize();
}

Quaternion Quaternion::RotationMatrix(const rotation::RotationMatrix& aRotationMatrix)
{
    /// @ref Markley F. L.: Fundamentals of Spacecraft Attitude Determination and Control, 48
    /// @note Should we use this method instead?
    /// https://d3cw3dd2w32x2b.cloudfront.net/wp-content/uploads/2015/01/matrix-to-quat.pdf

    const double trace = aRotationMatrix.getMatrix().trace();

    const double rotationMatrix_11 = aRotationMatrix(0, 0);
    const double rotationMatrix_12 = aRotationMatrix(0, 1);
    const double rotationMatrix_13 = aRotationMatrix(0, 2);

    const double rotationMatrix_21 = aRotationMatrix(1, 0);
    const double rotationMatrix_22 = aRotationMatrix(1, 1);
    const double rotationMatrix_23 = aRotationMatrix(1, 2);

    const double rotationMatrix_31 = aRotationMatrix(2, 0);
    const double rotationMatrix_32 = aRotationMatrix(2, 1);
    const double rotationMatrix_33 = aRotationMatrix(2, 2);

    double x = std::numeric_limits<double>::quiet_NaN();
    double y = std::numeric_limits<double>::quiet_NaN();
    double z = std::numeric_limits<double>::quiet_NaN();
    double s = std::numeric_limits<double>::quiet_NaN();

    if ((trace >= rotationMatrix_11) && (trace >= rotationMatrix_22) && (trace >= rotationMatrix_33))
    {
        x = rotationMatrix_23 - rotationMatrix_32;
        y = rotationMatrix_31 - rotationMatrix_13;
        z = rotationMatrix_12 - rotationMatrix_21;
        s = 1.0 + trace;
    }
    else if ((rotationMatrix_11 >= trace) && (rotationMatrix_11 >= rotationMatrix_22) &&
             (rotationMatrix_11 >= rotationMatrix_33))
    {
        x = 1.0 + 2.0 * rotationMatrix_11 - trace;
        y = rotationMatrix_12 + rotationMatrix_21;
        z = rotationMatrix_13 + rotationMatrix_31;
        s = rotationMatrix_23 - rotationMatrix_32;
    }
    else if ((rotationMatrix_22 >= rotationMatrix_11) && (rotationMatrix_22 >= trace) &&
             (rotationMatrix_22 >= rotationMatrix_33))
    {
        x = rotationMatrix_21 + rotationMatrix_12;
        y = 1.0 + 2.0 * rotationMatrix_22 - trace;
        z = rotationMatrix_23 + rotationMatrix_32;
        s = rotationMatrix_31 - rotationMatrix_13;
    }
    else if ((rotationMatrix_33 >= rotationMatrix_11) && (rotationMatrix_33 >= rotationMatrix_22) &&
             (rotationMatrix_33 >= trace))
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

Quaternion Quaternion::EulerAngle(const rotation::EulerAngle& aEulerAngle)
{
    // Fundamentals of Spacecraft Attitude Determination and Control
    // F. Landis Markley and John L. Crassidis, Springer
    // Table B.5, p. 364

    const double phi = aEulerAngle.getPhi().inRadians();
    const double theta = aEulerAngle.getTheta().inRadians();
    const double psi = aEulerAngle.getPsi().inRadians();

    const double c_phi = std::cos(phi / 2.0);
    const double c_theta = std::cos(theta / 2.0);
    const double c_psi = std::cos(psi / 2.0);

    const double s_phi = std::sin(phi / 2.0);
    const double s_theta = std::sin(theta / 2.0);
    const double s_psi = std::sin(psi / 2.0);

    switch (aEulerAngle.getAxisSequence())
    {
        case EulerAngle::AxisSequence::XYZ:  // 1-2-3
        {
            const double x = s_phi * c_theta * c_psi + c_phi * s_theta * s_psi;
            const double y = c_phi * s_theta * c_psi - s_phi * c_theta * s_psi;
            const double z = c_phi * c_theta * s_psi + s_phi * s_theta * c_psi;
            const double s = c_phi * c_theta * c_psi - s_phi * s_theta * s_psi;

            return Quaternion::XYZS(x, y, z, s).toNormalized();
        }

        case EulerAngle::AxisSequence::ZXY:  // 3-1-2
        {
            const double x = c_phi * s_theta * c_psi - s_phi * c_theta * s_psi;
            const double y = c_phi * c_theta * s_psi + s_phi * s_theta * c_psi;
            const double z = c_phi * s_theta * s_psi + s_phi * c_theta * c_psi;
            const double s = c_phi * c_theta * c_psi - s_phi * s_theta * s_psi;

            return Quaternion::XYZS(x, y, z, s).toNormalized();
        }

        case EulerAngle::AxisSequence::ZYX:  // 3-2-1
        {
            const double x = c_phi * c_theta * s_psi - s_phi * s_theta * c_psi;
            const double y = c_phi * s_theta * c_psi + s_phi * c_theta * s_psi;
            const double z = s_phi * c_theta * c_psi - c_phi * s_theta * s_psi;
            const double s = c_phi * c_theta * c_psi + s_phi * s_theta * s_psi;

            return Quaternion::XYZS(x, y, z, s).toNormalized();
        }

        default:
            throw ostk::core::error::runtime::ToBeImplemented("Axis sequence is not supported.");
    }
}

Quaternion Quaternion::Parse(const String& aString, const Quaternion::Format& aFormat)
{
    using ostk::mathematics::object::VectorXd;

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
    if (aFirstVector.squaredNorm() == 0.0)
    {
        throw ostk::core::error::RuntimeError("First vector length is zero.");
    }

    if (aSecondVector.squaredNorm() == 0.0)
    {
        throw ostk::core::error::RuntimeError("Second vector length is zero.");
    }

    const Vector3d firstNormalizedVector = aFirstVector.normalized();
    const Vector3d secondNormalizedVector = aSecondVector.normalized();

    const Vector3d orthogonalVector = secondNormalizedVector.cross(firstNormalizedVector);
    const double dotProduct = firstNormalizedVector.dot(secondNormalizedVector);

    // According to - https://raw.org/math/algebra/quaternion-from-two-vectors/ split into several cases to handle
    // numerical stability issues

    // Rotation angle is less than or equal to 90 deg (parallel vectors are handled here, they simply return the
    // identity quaternion)
    if (dotProduct >= 0.0)
    {
        return Quaternion::XYZS(orthogonalVector.x(), orthogonalVector.y(), orthogonalVector.z(), 1.0 + dotProduct)
            .toNormalized();
    }

    const double orthogonalVectorSquaredNorm = orthogonalVector.squaredNorm();
    const double epsilon = 1e-8;  // Tolerance choice is a tradeoff between numerical stability for fully anti-parallel
                                  // vectors and error tolerance for nearly anti-parallel vectors.

    // Rotation angle is close to 180 deg than the tolerance - compute the shortest rotation as if they were exactly
    // anti-parallel This is done by redefining the orthogonal vector to be the one that is least aligned with the first
    // vector.
    if (orthogonalVectorSquaredNorm <= (epsilon * epsilon))
    {
        const Vector3d absoluteFirstVector = firstNormalizedVector.cwiseAbs();

        Vector3d leastAlignedBasisVector = Vector3d::UnitZ();

        if ((absoluteFirstVector.x() <= absoluteFirstVector.y()) &&
            (absoluteFirstVector.x() <= absoluteFirstVector.z()))
        {
            leastAlignedBasisVector = Vector3d::UnitX();
        }
        else if (absoluteFirstVector.y() <= absoluteFirstVector.z())
        {
            leastAlignedBasisVector = Vector3d::UnitY();
        }

        const Vector3d rotationAxis = firstNormalizedVector.cross(leastAlignedBasisVector).normalized();

        return Quaternion::XYZS(rotationAxis.x(), rotationAxis.y(), rotationAxis.z(), 0.0);
    }

    // Rotation angle between 90 and 180 deg and still not within tolerance of 180: compute the shortest rotation
    // between the two vectors accounting for numerical instability that can still happens above tolerance but close to
    // 180 deg: as d = dotProduct approaches -1, (1 + d) subtracts two nearly equal numbers and suffers from
    // catastrophic cancellation. An equivalent, stable expression is derived from Lagrange's identity, with c =
    // orthogonalVector and unit input vectors u and v:
    //
    //     |c|^2 = |u|^2 |v|^2 - (u . v)^2 = 1 - d^2 = (1 + d) (1 - d)
    //
    // Since d < 0, (1 - d) lies in (1, 2] and can be divided by safely:
    //
    //     1 + d = |c|^2 / (1 - d)
    //
    // Neither |c|^2 nor (1 - d) involves a cancellation, so the scalar part stays accurate near 180 deg.

    return Quaternion::XYZS(
               orthogonalVector.x(),
               orthogonalVector.y(),
               orthogonalVector.z(),
               (orthogonalVectorSquaredNorm / (1.0 - dotProduct))
    )
        .toNormalized();
}

Quaternion Quaternion::LERP(const Quaternion& aFirstQuaternion, const Quaternion& aSecondQuaternion, double aRatio)
{
    if (std::isnan(aRatio))
    {
        throw ostk::core::error::runtime::Undefined("Ratio");
    }

    if ((aRatio < 0.0) || (aRatio > 1.0))
    {
        throw ostk::core::error::RuntimeError("Ratio [{}] not in [0, 1] interval.", aRatio);
    }

    return (aFirstQuaternion * (1.0 - aRatio) + aSecondQuaternion * aRatio);
}

Quaternion Quaternion::NLERP(const Quaternion& aFirstQuaternion, const Quaternion& aSecondQuaternion, double aRatio)
{
    return Quaternion::LERP(aFirstQuaternion, aSecondQuaternion, aRatio).toNormalized();
}

Quaternion Quaternion::SLERP(const Quaternion& aFirstQuaternion, const Quaternion& aSecondQuaternion, double aRatio)
{
    if (std::isnan(aRatio))
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

}  // namespace rotation
}  // namespace transformation
}  // namespace d3
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk
