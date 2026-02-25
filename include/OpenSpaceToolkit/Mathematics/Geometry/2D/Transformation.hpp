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

using ostk::core::type::String;
using ostk::core::type::Unique;

using ostk::mathematics::geometry::Angle;
using ostk::mathematics::geometry::d2::Object;
using ostk::mathematics::geometry::d2::object::Point;
using ostk::mathematics::object::Matrix3d;
using ostk::mathematics::object::Vector2d;
using ostk::mathematics::object::Vector3d;

/// @brief                      2D geometric transformation
///
/// @details                    Represents a 2D affine transformation using a 3x3 homogeneous matrix.
///                             Supports translation, rotation, scaling, reflection, shear, and their compositions.
///
/// @code{.cpp}
///                             Transformation t = Transformation::Identity();
///                             Transformation rotation = Transformation::Rotation(Angle::Degrees(45.0));
///                             Point p = rotation.applyTo(Point(1.0, 0.0));
/// @endcode
class Transformation
{
   public:
    enum class Type
    {

        Undefined,   ///< Undefined transformation
        Identity,    ///< Identity transformation
        Translation, ///< Translation transformation
        Rotation,    ///< Rotation transformation
        Scaling,     ///< Scaling transformation
        Reflection,  ///< Reflection transformation
        Shear,       ///< Shear transformation
        Affine       ///< General affine transformation

    };

    /// @brief              Constructor
    ///
    /// @code{.cpp}
    ///                     Transformation t(Matrix3d::Identity());
    /// @endcode
    ///
    /// @param              [in] aMatrix A transformation matrix
    Transformation(const Matrix3d& aMatrix);

    /// @brief              Equality operator
    ///
    /// @code{.cpp}
    ///                     Transformation::Identity() == Transformation::Identity();
    /// @endcode
    ///
    /// @param              [in] aTransformation A transformation
    /// @return             True if transformations are equal
    bool operator==(const Transformation& aTransformation) const;

    /// @brief              Inequality operator
    ///
    /// @code{.cpp}
    ///                     Transformation::Identity() != Transformation::Translation({1.0, 2.0});
    /// @endcode
    ///
    /// @param              [in] aTransformation A transformation
    /// @return             True if transformations are not equal
    bool operator!=(const Transformation& aTransformation) const;

    /// @brief              Composition operator (multiply two transformations)
    ///
    /// @code{.cpp}
    ///                     Transformation t = Transformation::Translation({1.0, 0.0}) * Transformation::Identity();
    /// @endcode
    ///
    /// @param              [in] aTransformation A transformation to compose with
    /// @return             The composed transformation
    Transformation operator*(const Transformation& aTransformation) const;

    /// @brief              Apply transformation to a vector
    ///
    /// @code{.cpp}
    ///                     Vector3d v = Transformation::Identity() * Vector3d(1.0, 2.0, 1.0);
    /// @endcode
    ///
    /// @param              [in] aVector A 3D homogeneous vector
    /// @return             The transformed vector
    Vector3d operator*(const Vector3d& aVector) const;

    /// @brief              Composition assignment operator
    ///
    /// @code{.cpp}
    ///                     Transformation t = Transformation::Identity();
    ///                     t *= Transformation::Translation({1.0, 2.0});
    /// @endcode
    ///
    /// @param              [in] aTransformation A transformation to compose with
    /// @return             Reference to the modified transformation
    Transformation& operator*=(const Transformation& aTransformation);

    /// @brief              Output stream operator
    ///
    /// @code{.cpp}
    ///                     std::cout << Transformation::Identity();
    /// @endcode
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] aTransformation A transformation
    /// @return             Reference to the output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Transformation& aTransformation);

    /// @brief              Check if the transformation is defined
    ///
    /// @code{.cpp}
    ///                     Transformation::Identity().isDefined();
    /// @endcode
    ///
    /// @return             True if the transformation is defined
    bool isDefined() const;

    /// @brief              Check if the transformation is the identity
    ///
    /// @code{.cpp}
    ///                     Transformation::Identity().isIdentity();
    /// @endcode
    ///
    /// @return             True if the transformation is the identity
    bool isIdentity() const;

    /// @brief              Returns true if transformation is rigid
    ///
    /// @code{.cpp}
    ///                     Transformation::Identity().isRigid();
    /// @endcode
    ///
    ///                     A rigid transformation preserves distances and angles.
    ///                     It is either a translation, a rotation, or a reflection.
    ///
    /// @ref                https://en.wikipedia.org/wiki/Rigid_transformation
    ///
    /// @return             True if transformation is rigid
    bool isRigid() const;

    /// @brief              Get the type of the transformation
    ///
    /// @code{.cpp}
    ///                     Transformation::Type type = Transformation::Identity().getType();
    /// @endcode
    ///
    /// @return             The transformation type
    Transformation::Type getType() const;

    /// @brief              Get the transformation matrix
    ///
    /// @code{.cpp}
    ///                     Matrix3d matrix = Transformation::Identity().getMatrix();
    /// @endcode
    ///
    /// @return             The 3x3 homogeneous transformation matrix
    Matrix3d getMatrix() const;

    /// @brief              Get the inverse transformation
    ///
    /// @code{.cpp}
    ///                     Transformation inv = Transformation::Translation({1.0, 2.0}).getInverse();
    /// @endcode
    ///
    /// @return             The inverse transformation
    Transformation getInverse() const;

    /// @brief              Apply the transformation to a point
    ///
    /// @code{.cpp}
    ///                     Transformation t = Transformation::Translation({1.0, 2.0});
    ///                     Point p = t.applyTo(Point(0.0, 0.0));  // (1.0, 2.0)
    /// @endcode
    ///
    /// @param              [in] aPoint A point
    /// @return             The transformed point
    Point applyTo(const Point& aPoint) const;

    /// @brief              Apply the transformation to a 2D vector
    ///
    /// @code{.cpp}
    ///                     Vector2d v = Transformation::Identity().applyTo(Vector2d(1.0, 2.0));
    /// @endcode
    ///
    /// @param              [in] aVector A 2D vector
    /// @return             The transformed vector
    Vector2d applyTo(const Vector2d& aVector) const;

    /// @brief              Apply the transformation to a 2D object
    ///
    /// @code{.cpp}
    ///                     Unique<Object> transformed = Transformation::Identity().applyTo(anObject);
    /// @endcode
    ///
    /// @param              [in] anObject A unique pointer to a 2D object
    /// @return             The transformed object
    Unique<Object> applyTo(const Unique<Object>& anObject) const;  // [TBI]

    /// @brief              Print transformation
    ///
    /// @code{.cpp}
    ///                     Transformation::Identity().print(std::cout);
    /// @endcode
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] (optional) displayDecorators If true, display decorators
    virtual void print(std::ostream& anOutputStream, bool displayDecorators = true) const;

    /// @brief              Construct an undefined transformation
    ///
    /// @code{.cpp}
    ///                     Transformation t = Transformation::Undefined();
    /// @endcode
    ///
    /// @return             An undefined transformation
    static Transformation Undefined();

    /// @brief              Construct an identity transformation
    ///
    /// @code{.cpp}
    ///                     Transformation t = Transformation::Identity();
    /// @endcode
    ///
    /// @return             An identity transformation
    static Transformation Identity();

    /// @brief              Construct a translation transformation
    ///
    /// @code{.cpp}
    ///                     Transformation t = Transformation::Translation({1.0, 2.0});
    /// @endcode
    ///
    /// @param              [in] aTranslationVector A 2D translation vector
    /// @return             A translation transformation
    static Transformation Translation(const Vector2d& aTranslationVector);

    /// @brief              Construct a rotation transformation
    ///
    /// @code{.cpp}
    ///                     Transformation t = Transformation::Rotation(Angle::Degrees(45.0));
    /// @endcode
    ///
    /// @param              [in] aRotationAngle A rotation angle
    /// @return             A rotation transformation
    static Transformation Rotation(const Angle& aRotationAngle);

    /// @brief              Construct a rotation transformation around a given point
    ///
    /// @code{.cpp}
    ///                     Transformation t = Transformation::RotationAround(Point(1.0, 0.0), Angle::Degrees(90.0));
    /// @endcode
    ///
    /// @param              [in] aPoint A center point of rotation
    /// @param              [in] aRotationAngle A rotation angle
    /// @return             A rotation transformation around the given point
    static Transformation RotationAround(const Point& aPoint, const Angle& aRotationAngle);

    /// @brief              Get a string from a transformation type
    ///
    /// @code{.cpp}
    ///                     String str = Transformation::StringFromType(Transformation::Type::Identity);
    /// @endcode
    ///
    /// @param              [in] aType A transformation type
    /// @return             The string name of the type
    static String StringFromType(const Transformation::Type& aType);

    /// @brief              Determine the transformation type from a matrix
    ///
    /// @code{.cpp}
    ///                     Transformation::Type type = Transformation::TypeOfMatrix(Matrix3d::Identity());
    /// @endcode
    ///
    /// @param              [in] aMatrix A 3x3 transformation matrix
    /// @return             The transformation type
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
