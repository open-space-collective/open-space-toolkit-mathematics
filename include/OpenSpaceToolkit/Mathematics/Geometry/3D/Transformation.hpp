/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation__
#define __OpenSpaceToolkit_Mathematics_Geometry_3D_Transformation__

#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Types/Unique.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformations/Rotations/RotationVector.hpp>
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

class Transformation;

using ostk::core::types::Unique;
using ostk::core::types::String;

using ostk::mathematics::object::Vector3d;
using ostk::mathematics::object::Vector4d;
using ostk::mathematics::object::Matrix4d;
using ostk::mathematics::geometry::Angle;
using ostk::mathematics::geometry::d3::Object;
using ostk::mathematics::geometry::d3::object::Point;
using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;
using ostk::mathematics::geometry::d3::transformation::rotation::RotationMatrix;

class Transformation
{
   public:
    enum class Type
    {

        Undefined,
        Identity,
        Translation,
        Rotation,
        Scaling,
        Reflection,
        Shear,
        Affine

    };

    /// @brief              Constructor
    ///
    /// @param              [in] aMatrix A transformation matrix

    Transformation(const Matrix4d& aMatrix);

    bool operator==(const Transformation& aTransformation) const;

    bool operator!=(const Transformation& aTransformation) const;

    Transformation operator*(const Transformation& aTransformation) const;

    Vector4d operator*(const Vector4d& aVector) const;

    Transformation& operator*=(const Transformation& aTransformation);

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Transformation& aTransformation);

    bool isDefined() const;

    bool isIdentity() const;

    /// @brief              Returns true if transformation is rigid
    ///
    ///                     A rigid transformation preserves the Euclidean distance between every pair of points.
    ///                     The rigid transformation include rotation, translations, reflections, or their
    ///                     combination.
    ///
    /// @ref                https://en.wikipedia.org/wiki/Rigid_transformation
    ///
    /// @return             True if transformation is rigid

    bool isRigid() const;

    Transformation::Type getType() const;

    Matrix4d getMatrix() const;

    Transformation getInverse() const;

    Point applyTo(const Point& aPoint) const;

    Vector3d applyTo(const Vector3d& aVector) const;

    /// @brief              Print transformation
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] (optional) displayDecorators If true, display decorators

    virtual void print(std::ostream& anOutputStream, bool displayDecorators = true) const;

    static Transformation Undefined();

    static Transformation Identity();

    static Transformation Translation(const Vector3d& aTranslationVector);

    static Transformation Rotation(const RotationVector& aRotationVector);

    static Transformation Rotation(const RotationMatrix& aRotationMatrix);

    static Transformation RotationAround(const Point& aPoint, const RotationVector& aRotationVector);

    static String StringFromType(const Transformation::Type& aType);

    static Transformation::Type TypeOfMatrix(const Matrix4d& aMatrix);

    static bool IsRigid(const Matrix4d& aMatrix);

   private:
    Transformation::Type type_;
    Matrix4d matrix_;

    bool isRigid_;

    Transformation(const Transformation::Type& aType, const Matrix4d& aMatrix, const bool isRigid);
};

}  // namespace d3
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
