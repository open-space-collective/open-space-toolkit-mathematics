/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object__
#define __OpenSpaceToolkit_Mathematics_Geometry_Planetodetic_Object__

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

namespace ostk
{
namespace mathematics
{
namespace geometry
{
namespace planetodetic
{

using ostk::core::type::Integer;
using ostk::core::type::String;

/// @brief                      Planetodetic object
///
///                             Base class for objects in planetodetic coordinate systems.
///
/// @ref                        https://en.wikipedia.org/wiki/Planetary_coordinate_system

class Object
{
   public:
    enum class Format
    {

        Undefined,  ///< Undefined format
        Standard    ///< Standard format

    };

    /// @brief              Default constructor (default)

    Object() = default;

    /// @brief              Destructor (pure virtual)

    virtual ~Object() = 0;

    /// @brief              Clone object (pure virtual)
    ///
    /// @return             Pointer to cloned object

    virtual Object* clone() const = 0;

    /// @brief              Equal to operator
    ///
    /// @param              [in] anObject An object
    /// @return             True if objects are equal

    bool operator==(const Object& anObject) const;

    /// @brief              Not equal to operator
    ///
    /// @param              [in] anObject An object
    /// @return             True if objects are not equal

    bool operator!=(const Object& anObject) const;

    /// @brief              Output stream operator
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] anObject An object
    /// @return             A reference to output stream

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Object& anObject);

    /// @brief              Check if object is defined
    ///
    /// @return             True if object is defined

    virtual bool isDefined() const = 0;

    /// @brief              Returns true if object can be converted to type
    ///
    /// @return             True if object can be converted to type

    template <class Type>
    bool is() const
    {
        return dynamic_cast<const Type*>(this) != nullptr;
    }

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

    /// @brief              Access object as its underlying type
    ///
    /// @return             Reference to underlying type

    template <class Type>
    const Type& as() const
    {
        const Type* objectPtr = dynamic_cast<const Type*>(this);

        if (objectPtr == nullptr)
        {
            throw ostk::core::error::RuntimeError("Cannot convert object to underlying type.");
        }

        return *objectPtr;
    }

    /// @brief              Get string representation
    ///
    /// @param              [in] aFormat A format
    /// @param              [in] aPrecision A precision
    /// @return             String representation

    virtual String toString(
        const Object::Format& aFormat = Object::Format::Standard, const Integer& aPrecision = Integer::Undefined()
    ) const = 0;

    /// @brief              Print object
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] (optional) displayDecorators If true, display decorators

    virtual void print(std::ostream& anOutputStream, bool displayDecorators = true) const = 0;
};

}  // namespace planetodetic
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
