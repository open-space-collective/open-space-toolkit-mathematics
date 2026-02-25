/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Composite__
#define __OpenSpaceToolkit_Mathematics_Geometry_2D_Object_Composite__

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>
#include <OpenSpaceToolkit/Core/Type/Unique.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object.hpp>

namespace ostk
{
namespace mathematics
{
namespace geometry
{
namespace d2
{
namespace object
{

using ostk::core::container::Array;
using ostk::core::type::Index;
using ostk::core::type::Size;
using ostk::core::type::Unique;

using ostk::mathematics::geometry::d2::Object;

/// @brief                      Composite object
///
/// @code{.cpp}
///                             Composite composite(Point(0.0, 0.0)) ;
/// @endcode
class Composite : public Object
{
   public:
    typedef Array<Unique<Object>>::ConstIterator ConstIterator;

    /// @brief              Constructor
    ///
    /// @code{.cpp}
    ///                     Composite composite(Point(0.0, 0.0)) ;
    /// @endcode
    ///
    /// @param              [in] anObject An object
    explicit Composite(const Object& anObject);

    /// @brief              Constructor
    ///
    /// @code{.cpp}
    ///                     Unique<Object> objectUPtr = std::make_unique<Point>(0.0, 0.0) ;
    ///                     Composite composite(objectUPtr) ;
    /// @endcode
    ///
    /// @param              [in] anObjectUPtr A unique pointer to object
    explicit Composite(const Unique<Object>& anObjectUPtr);

    /// @brief              Constructor
    ///
    /// @code{.cpp}
    ///                     Array<Unique<Object>> objects ;
    ///                     objects.add(std::make_unique<Point>(0.0, 0.0)) ;
    ///                     Composite composite(std::move(objects)) ;
    /// @endcode
    ///
    /// @param              [in] anObjectArray An array of unique pointers to object
    explicit Composite(Array<Unique<Object>>&& anObjectArray);

    /// @brief              Copy constructor
    ///
    /// @code{.cpp}
    ///                     Composite copiedComposite(composite) ;
    /// @endcode
    ///
    /// @param              [in] aComposite A composite
    Composite(const Composite& aComposite);

    /// @brief              Clone composite
    ///
    /// @code{.cpp}
    ///                     Composite* clonePtr = composite.clone() ;
    /// @endcode
    ///
    /// @return             Pointer to cloned composite
    virtual Composite* clone() const override;

    /// @brief              Copy assignment operator
    ///
    /// @code{.cpp}
    ///                     Composite compositeB = compositeA ;
    /// @endcode
    ///
    /// @param              [in] aComposite A composite
    /// @return             Reference to composite
    Composite& operator=(const Composite& aComposite);

    /// @brief              Equal to operator
    ///
    /// @code{.cpp}
    ///                     compositeA == compositeB ; // True
    /// @endcode
    ///
    /// @param              [in] aComposite A composite object
    /// @return             True if composites are equal
    bool operator==(const Composite& aComposite) const;

    /// @brief              Not equal to operator
    ///
    /// @code{.cpp}
    ///                     compositeA != compositeB ; // True
    /// @endcode
    ///
    /// @param              [in] aComposite A composite object
    /// @return             True if composites are not equal
    bool operator!=(const Composite& aComposite) const;

    /// @brief              Addition operator (composite concatenation)
    ///
    /// @code{.cpp}
    ///                     Composite compositeC = compositeA + compositeB ;
    /// @endcode
    ///
    ///                     Concatenate (merge) composite with another composite.
    ///
    /// @param              [in] aComposite A composite
    /// @return             Concatenated composite
    Composite operator+(const Composite& aComposite) const;

    /// @brief              Addition assignment operator (composite concatenation)
    ///
    /// @code{.cpp}
    ///                     compositeA += compositeB ;
    /// @endcode
    ///
    ///                     Concatenate (merge) composite with another composite.
    ///
    /// @param              [in] aComposite A composite
    /// @return             Reference to concatenated composite
    Composite& operator+=(const Composite& aComposite);

    /// @brief              Check if composite is defined
    ///
    /// @code
    ///                     Composite(...).isDefined() ;
    /// @endcode
    ///
    /// @return             True if composite is defined
    virtual bool isDefined() const override;

    /// @brief              Check if composite is empty
    ///
    /// @code
    ///                     Composite(...).isEmpty() ;
    /// @endcode
    ///
    /// @return             True if composite is empty
    bool isEmpty() const;

    /// @brief              Returns true if composite can be converted to underlying object
    ///
    /// @code{.cpp}
    ///                     Composite composite(Point(0.0, 0.0)) ;
    ///                     bool isPoint = composite.is<Point>() ; // True
    /// @endcode
    ///
    ///                     Only valid if the composite only contains one object.
    ///
    /// @return             True if composite can be converted to underlying object
    template <class Type>
    bool is() const
    {
        if (!this->isDefined())
        {
            throw ostk::core::error::runtime::Undefined("Composite");
        }

        return (objects_.getSize() == 1) && (dynamic_cast<const Type*>(objects_.accessFirst().get()) != nullptr);
    }

    /// @brief              Access composite as its underlying object
    ///
    /// @code{.cpp}
    ///                     Composite composite(Point(0.0, 0.0)) ;
    ///                     const Point& point = composite.as<Point>() ;
    /// @endcode
    ///
    ///                     Only valid if the composite only contains one object.
    ///
    /// @return             Reference to underlying object
    template <class Type>
    const Type& as() const
    {
        if (!this->isDefined())
        {
            throw ostk::core::error::runtime::Undefined("Composite");
        }

        if (objects_.getSize() != 1)
        {
            throw ostk::core::error::RuntimeError("Cannot convert composite: it is complex.");
        }

        const Type* objectPtr = dynamic_cast<const Type*>(objects_.accessFirst().get());

        if (objectPtr == nullptr)
        {
            throw ostk::core::error::RuntimeError("Cannot convert composite: wrong type.");
        }

        return *objectPtr;
    }

    /// @brief              Check if composite intersects object
    ///
    /// @code{.cpp}
    ///                     composite.intersects(Point(0.0, 0.0)) ;
    /// @endcode
    ///
    /// @param              [in] anObject An object
    /// @return             True if composite intersects object
    bool intersects(const Object& anObject) const;

    /// @brief              Check if composite intersects composite
    ///
    /// @code{.cpp}
    ///                     compositeA.intersects(compositeB) ;
    /// @endcode
    ///
    /// @param              [in] aComposite A composite
    /// @return             True if composite intersects composite
    bool intersects(const Composite& aComposite) const;

    /// @brief              Check if composite contains object
    ///
    /// @code{.cpp}
    ///                     composite.contains(Point(0.0, 0.0)) ;
    /// @endcode
    ///
    /// @param              [in] anObject An object
    /// @return             True if composite contains object
    bool contains(const Object& anObject) const;

    /// @brief              Check if composite contains composite
    ///
    /// @code{.cpp}
    ///                     compositeA.contains(compositeB) ;
    /// @endcode
    ///
    /// @param              [in] aComposite A composite
    /// @return             True if composite contains composite
    bool contains(const Composite& aComposite) const;

    /// @brief              Check if composite contains object
    ///
    /// @code{.cpp}
    ///                     composite.anyContains(Point(0.0, 0.0)) ;
    /// @endcode
    ///
    /// @param              [in] anObject An object
    /// @return             True if any objects in composite contains object
    bool anyContains(const Object& anObject) const;

    /// @brief              Check if composite contains composite
    ///
    /// @code{.cpp}
    ///                     compositeA.anyContains(compositeB) ;
    /// @endcode
    ///
    /// @param              [in] aComposite A composite
    /// @return             True if any objects in composite contains composite
    bool anyContains(const Composite& aComposite) const;

    /// @brief              Access object at index
    ///
    /// @code{.cpp}
    ///                     const Object& object = composite.accessObjectAt(0) ;
    /// @endcode
    ///
    /// @param              [in] anIndex An object index
    /// @return             Reference to object
    const Object& accessObjectAt(const Index& anIndex) const;

    /// @brief              Access objects in composite
    ///
    /// @code{.cpp}
    ///                     const Array<Unique<Object>>& objects = composite.accessObjects() ;
    /// @endcode
    ///
    /// @return             Reference to objects in composite
    const Array<Unique<Object>>& accessObjects() const;

    /// @brief              Get number of objects in composite
    ///
    /// @code{.cpp}
    ///                     Size count = composite.getObjectCount() ;
    /// @endcode
    ///
    /// @return             Number of objects in composite
    Size getObjectCount() const;

    /// @brief              Compute intersection of composite with object
    ///
    /// @code{.cpp}
    ///                     // Intersection intersection = composite.intersectionWith(anObject) ;
    /// @endcode
    ///
    /// @param              [in] anObject An object
    /// @return             Intersection of composite with object
    // Intersection            intersectionWith                            (   const   Object& anObject ) const ;

    // /// @brief              Compute intersection of composite with composite
    // ///
    // /// @param              [in] aComposite A composite
    // /// @return             Intersection of composite with composite

    // Intersection            intersectionWith                            (   const   Composite& aComposite ) const ;

    /// @brief              Get const iterator to begin
    ///
    /// @code{.cpp}
    ///                     auto it = composite.begin() ;
    /// @endcode
    ///
    /// @return             Const iterator to begin
    Composite::ConstIterator begin() const;

    /// @brief              Get const iterator to end
    ///
    /// @code{.cpp}
    ///                     auto it = composite.end() ;
    /// @endcode
    ///
    /// @return             Const iterator to end
    Composite::ConstIterator end() const;

    /// @brief              Get string representation
    ///
    /// @code{.cpp}
    ///                     String str = composite.toString() ;
    /// @endcode
    ///
    /// @param              [in] aFormat A format
    /// @return             String representation
    virtual String toString(
        const Object::Format& aFormat = Object::Format::Standard, const Integer& aPrecision = Integer::Undefined()
    ) const override;

    /// @brief              Print composite
    ///
    /// @code{.cpp}
    ///                     composite.print(std::cout, true) ;
    /// @endcode
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] (optional) displayDecorators If true, display decorators
    virtual void print(std::ostream& anOutputStream, bool displayDecorators = true) const override;

    /// @brief              Apply transformation to composite
    ///
    /// @code{.cpp}
    ///                     composite.applyTransformation(aTransformation) ;
    /// @endcode
    ///
    /// @param              [in] aTransformation A transformation
    virtual void applyTransformation(const Transformation& aTransformation) override;

    /// @brief              Constructs an undefined composite
    ///
    /// @code
    ///                     Composite composite = Composite::Undefined() ; // Undefined
    /// @endcode
    ///
    /// @return             Undefined composite
    static Composite Undefined();

    /// @brief              Constructs an empty composite
    ///
    /// @code
    ///                     Composite composite = Composite::Empty() ;
    /// @endcode
    ///
    /// @return             Empty composite
    static Composite Empty();

   private:
    bool defined_;
    Array<Unique<Object>> objects_;
};

}  // namespace object
}  // namespace d2
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
