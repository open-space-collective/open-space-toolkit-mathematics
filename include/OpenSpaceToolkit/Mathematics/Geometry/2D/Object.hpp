/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Geometry_2D_Object__
#define __OpenSpaceToolkit_Mathematics_Geometry_2D_Object__

#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

namespace ostk
{
namespace mathematics
{
namespace geometry
{
namespace d2
{

class Transformation;
class Intersection;

using ostk::core::type::Integer;
using ostk::core::type::String;

/// @brief                      2D object
///
/// @code{.cpp}
///                             Point point(0.0, 0.0) ;  // Point is a concrete 2D Object
/// @endcode
class Object
{
   public:
    enum class Format
    {

        Undefined,  ///< Undefined format
        Standard,   ///< Standard format
        WKT         ///< Well-Known Text (WKT) format

    };

    /// @brief              Default constructor
    ///
    /// @code{.cpp}
    ///                     // Object is abstract; derived classes use the default constructor.
    /// @endcode
    Object() = default;

    /// @brief              Destructor (pure virtual)
    ///
    /// @code{.cpp}
    ///                     // Object is abstract; destructor is called via derived class.
    /// @endcode
    virtual ~Object() = 0;

    /// @brief              Clone object (pure virtual)
    ///
    /// @code{.cpp}
    ///                     Object* clonePtr = objectPtr->clone() ;
    /// @endcode
    ///
    /// @return             Pointer to cloned object
    virtual Object* clone() const = 0;

    /// @brief              Equal to operator
    ///
    /// @code{.cpp}
    ///                     Point(0.0, 0.0) == Point(0.0, 0.0) ; // True
    /// @endcode
    ///
    /// @param              [in] anObject An object
    /// @return             True if objects are equal
    bool operator==(const Object& anObject) const;

    /// @brief              Not equal to operator
    ///
    /// @code{.cpp}
    ///                     Point(0.0, 0.0) != Point(1.0, 0.0) ; // True
    /// @endcode
    ///
    /// @param              [in] anObject An object
    /// @return             True if objects are not equal
    bool operator!=(const Object& anObject) const;

    /// @brief              Output stream operator
    ///
    /// @code{.cpp}
    ///                     std::cout << Point(0.0, 0.0) ;
    /// @endcode
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] anObject An object
    /// @return             A reference to output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Object& anObject);

    /// @brief              Check if object is defined
    ///
    /// @code{.cpp}
    ///                     Point(0.0, 0.0).isDefined() ; // True
    /// @endcode
    ///
    /// @return             True if object is defined
    virtual bool isDefined() const = 0;

    /// @brief              Check if object intersects another object
    ///
    /// @code
    ///                     Unique<Object> objectUPtr = ... ;
    ///                     Unique<Object> anotherObjectUPtr = ... ;
    ///                     objectUPtr->intersects(*anotherObjectUPtr) ;
    /// @endcode
    ///
    /// @param              [in] anObject An object
    /// @return             True if object intersects another object
    virtual bool intersects(const Object& anObject) const;

    /// @brief              Check if object contains another object
    ///
    /// @code
    ///                     Unique<Object> objectUPtr = ... ;
    ///                     Unique<Object> anotherObjectUPtr = ... ;
    ///                     objectUPtr->contains(*anotherObjectUPtr) ;
    /// @endcode
    ///
    /// @param              [in] anObject An object
    /// @return             True if object contains another object
    virtual bool contains(const Object& anObject) const;

    /// @brief              Get string representation
    ///
    /// @code{.cpp}
    ///                     Point(0.0, 0.0).toString() ;
    /// @endcode
    ///
    /// @param              [in] aFormat A format
    /// @return             String representation
    virtual String toString(
        const Object::Format& aFormat = Object::Format::Standard, const Integer& aPrecision = Integer::Undefined()
    ) const = 0;

    /// @brief              Print object
    ///
    /// @code{.cpp}
    ///                     Point(0.0, 0.0).print(std::cout, true) ;
    /// @endcode
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] (optional) displayDecorators If true, display decorators
    virtual void print(std::ostream& anOutputStream, bool displayDecorators = true) const = 0;

    /// @brief              Apply transformation to object
    ///
    /// @code{.cpp}
    ///                     Point point(0.0, 0.0) ;
    ///                     point.applyTransformation(aTransformation) ;
    /// @endcode
    ///
    /// @param              [in] aTransformation A transformation
    virtual void applyTransformation(const Transformation& aTransformation) = 0;
};

}  // namespace d2
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
