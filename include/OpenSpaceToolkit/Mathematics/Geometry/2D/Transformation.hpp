/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_2D_Transformation__
#define __OpenSpaceToolkit_Mathematics_Geometry_2D_Transformation__

#include <OpenSpaceToolkit/Core/Type/String.hpp>
#include <OpenSpaceToolkit/Core/Type/Unique.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Point.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/Angle.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

namespace ostk
{
namespace mathematics
{
namespace geometry
{
namespace d2
{

using ostk::core::type::Unique;
using ostk::core::type::String;

using ostk::mathematics::object::Vector2d;
using ostk::mathematics::object::Vector3d;
using ostk::mathematics::object::Matrix3d;
using ostk::mathematics::geometry::Angle;
using ostk::mathematics::geometry::d2::Object;
using ostk::mathematics::geometry::d2::object::Point;

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

    Transformation(const Matrix3d& aMatrix);

    bool operator==(const Transformation& aTransformation) const;

    bool operator!=(const Transformation& aTransformation) const;

    Transformation operator*(const Transformation& aTransformation) const;

    Vector3d operator*(const Vector3d& aVector) const;

    Transformation& operator*=(const Transformation& aTransformation);

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Transformation& aTransformation);

    bool isDefined() const;

    bool isIdentity() const;

    /// @brief              Returns true if transformation is rigid
    ///
    ///                     A rigid transformation preserves distances and angles.
    ///                     It is either a translation, a rotation, or a reflection.
    ///
    /// @ref                https://en.wikipedia.org/wiki/Rigid_transformation
    ///
    /// @return             True if transformation is rigid

    bool isRigid() const;

    Transformation::Type getType() const;

    Matrix3d getMatrix() const;

    Transformation getInverse() const;

    Point applyTo(const Point& aPoint) const;

    Vector2d applyTo(const Vector2d& aVector) const;

    Unique<Object> applyTo(const Unique<Object>& anObject) const;  // [TBI]

    /// @brief              Print transformation
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] (optional) displayDecorators If true, display decorators

    virtual void print(std::ostream& anOutputStream, bool displayDecorators = true) const;

    static Transformation Undefined();

    static Transformation Identity();

    static Transformation Translation(const Vector2d& aTranslationVector);

    static Transformation Rotation(const Angle& aRotationAngle);

    static Transformation RotationAround(const Point& aPoint, const Angle& aRotationAngle);

    static String StringFromType(const Transformation::Type& aType);

    static Transformation::Type TypeOfMatrix(const Matrix3d& aMatrix);

   private:
    Transformation::Type type_;
    Matrix3d matrix_;

    Transformation(const Transformation::Type& aType, const Matrix3d& aMatrix);
};

}  // namespace d2
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
