/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Geometry_3D_Object__
#define __OpenSpaceToolkit_Mathematics_Geometry_3D_Object__

#include <OpenSpaceToolkit/Core/Error.hpp>

namespace ostk
{
namespace mathematics
{
namespace geometry
{
namespace d3
{

class Transformation;
class Intersection;

/// @brief                      3D object
///
/// @code{.cpp}
///                             // Object is abstract; use derived types such as Point, Line, Sphere, etc.
///                             Point point = Point::Origin() ;
/// @endcode
class Object
{
   public:
    /// @brief              Default constructor (default)
    ///
    /// @code{.cpp}
    ///                     // Object is abstract, construct via a derived type
    /// @endcode
    Object() = default;

    /// @brief              Destructor (pure virtual)
    ///
    /// @code{.cpp}
    ///                     // Destructor is called automatically when a derived object goes out of scope
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
    ///                     Point point = Point::Origin() ;
    ///                     point == point ; // True
    /// @endcode
    ///
    /// @param              [in] anObject An object
    /// @return             True if objects are equal
    bool operator==(const Object& anObject) const;

    /// @brief              Not equal to operator
    ///
    /// @code{.cpp}
    ///                     Point::Origin() != Point(1.0, 0.0, 0.0) ; // True
    /// @endcode
    ///
    /// @param              [in] anObject An object
    /// @return             True if objects are not equal
    bool operator!=(const Object& anObject) const;

    /// @brief              Output stream operator
    ///
    /// @code{.cpp}
    ///                     Point point = Point::Origin() ;
    ///                     std::cout << point ;
    /// @endcode
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] anObject An object
    /// @return             A reference to output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Object& anObject);

    /// @brief              Check if object is defined
    ///
    /// @code{.cpp}
    ///                     Point::Origin().isDefined() ; // True
    /// @endcode
    ///
    /// @return             True if object is defined
    virtual bool isDefined() const = 0;

    /// @brief              Returns true if object can be converted to type
    ///
    /// @code{.cpp}
    ///                     Unique<Object> objectUPtr = std::make_unique<Point>(Point::Origin()) ;
    ///                     objectUPtr->is<Point>() ; // True
    /// @endcode
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
    /// @code{.cpp}
    ///                     Unique<Object> objectUPtr = std::make_unique<Point>(Point::Origin()) ;
    ///                     const Point& point = objectUPtr->as<Point>() ;
    /// @endcode
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

    /// @brief              Compute intersection of object with another object
    ///
    /// @code
    ///                     Unique<Object> objectUPtr = ... ;
    ///                     Unique<Object> anotherObjectUPtr = ... ;
    ///                     Intersection intersection = objectUPtr->intersectionWith(*anotherObjectUPtr) ;
    /// @endcode
    ///
    /// @param              [in] anObject An object
    /// @return             Intersection of object with another object
    virtual Intersection intersectionWith(const Object& anObject) const;

    /// @brief              Print object
    ///
    /// @code{.cpp}
    ///                     Point::Origin().print(std::cout, true) ;
    /// @endcode
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] (optional) displayDecorators If true, display decorators
    virtual void print(std::ostream& anOutputStream, bool displayDecorators = true) const = 0;

    /// @brief              Apply transformation to object
    ///
    /// @code{.cpp}
    ///                     Point point = Point::Origin() ;
    ///                     point.applyTransformation(Transformation::Identity()) ;
    /// @endcode
    ///
    /// @param              [in] aTransformation A transformation
    virtual void applyTransformation(const Transformation& aTransformation) = 0;
};

}  // namespace d3
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
