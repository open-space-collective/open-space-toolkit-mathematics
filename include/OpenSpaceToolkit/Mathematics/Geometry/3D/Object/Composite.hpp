/// Apache License 2.0
#ifndef __OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Composite__
#define __OpenSpaceToolkit_Mathematics_Geometry_3D_Object_Composite__

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>
#include <OpenSpaceToolkit/Core/Type/Unique.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object.hpp>

namespace ostk
{
namespace mathematics
{
namespace geometry
{
namespace d3
{
namespace object
{

using ostk::core::container::Array;
using ostk::core::type::Index;
using ostk::core::type::Size;
using ostk::core::type::Unique;

using ostk::mathematics::geometry::d3::Object;

/// @brief                      Composite object
///
/// @code{.cpp}
///                             Composite composite(Unique<Object>(new Point(0.0, 0.0, 0.0)));
/// @endcode
class Composite : public Object
{
   public:
    typedef Array<Unique<Object>>::ConstIterator ConstIterator;

    /// @brief              Constructor
    ///
    /// @code{.cpp}
    ///                     Point point = { 0.0, 0.0, 0.0 } ;
    ///                     Composite composite = Composite(point) ;
    /// @endcode
    ///
    /// @param              [in] anObject An object
    explicit Composite(const Object& anObject);

    /// @brief              Constructor
    ///
    /// @code{.cpp}
    ///                     Unique<Object> objectPtr = std::make_unique<Point>(0.0, 0.0, 0.0) ;
    ///                     Composite composite = Composite(objectPtr) ;
    /// @endcode
    ///
    /// @param              [in] anObjectUPtr A unique pointer to object
    explicit Composite(const Unique<Object>& anObjectUPtr);

    /// @brief              Constructor
    ///
    /// @code{.cpp}
    ///                     Array<Unique<Object>> objects ;
    ///                     objects.emplace_back(std::make_unique<Point>(0.0, 0.0, 0.0)) ;
    ///                     Composite composite = Composite(std::move(objects)) ;
    /// @endcode
    ///
    /// @param              [in] anObjectArray An array of unique pointers to object
    explicit Composite(Array<Unique<Object>>&& anObjectArray);

    /// @brief              Copy constructor
    ///
    /// @code{.cpp}
    ///                     Composite composite = Composite(Point(0.0, 0.0, 0.0)) ;
    ///                     Composite copy = Composite(composite) ;
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
    ///                     Composite compositeA = Composite(Point(0.0, 0.0, 0.0)) ;
    ///                     Composite compositeB = Composite::Undefined() ;
    ///                     compositeB = compositeA ;
    /// @endcode
    ///
    /// @param              [in] aComposite A composite
    /// @return             Reference to composite
    Composite& operator=(const Composite& aComposite);

    /// @brief              Equal to operator
    ///
    /// @code{.cpp}
    ///                     Composite composite = Composite(Point(0.0, 0.0, 0.0)) ;
    ///                     composite == composite ; // True
    /// @endcode
    ///
    /// @param              [in] aComposite A composite object
    /// @return             True if composites are equal
    bool operator==(const Composite& aComposite) const;

    /// @brief              Not equal to operator
    ///
    /// @code{.cpp}
    ///                     Composite compositeA = Composite(Point(0.0, 0.0, 0.0)) ;
    ///                     Composite compositeB = Composite(Point(1.0, 0.0, 0.0)) ;
    ///                     compositeA != compositeB ; // True
    /// @endcode
    ///
    /// @param              [in] aComposite A composite object
    /// @return             True if composites are not equal
    bool operator!=(const Composite& aComposite) const;

    /// @brief              Addition operator (composite concatenation)
    ///
    ///                     Concatenate (merge) composite with another composite.
    ///
    /// @code{.cpp}
    ///                     Composite compositeA = Composite(Point(0.0, 0.0, 0.0)) ;
    ///                     Composite compositeB = Composite(Point(1.0, 0.0, 0.0)) ;
    ///                     Composite merged = compositeA + compositeB ;
    /// @endcode
    ///
    /// @param              [in] aComposite A composite
    /// @return             Concatenated composite
    Composite operator+(const Composite& aComposite) const;

    /// @brief              Addition assignment operator (composite concatenation)
    ///
    ///                     Concatenate (merge) composite with another composite.
    ///
    /// @code{.cpp}
    ///                     Composite compositeA = Composite(Point(0.0, 0.0, 0.0)) ;
    ///                     Composite compositeB = Composite(Point(1.0, 0.0, 0.0)) ;
    ///                     compositeA += compositeB ;
    /// @endcode
    ///
    /// @param              [in] aComposite A composite
    /// @return             Reference to concatenated composite
    Composite& operator+=(const Composite& aComposite);

    /// @brief              Check if composite is defined
    ///
    /// @code{.cpp}
    ///                     Composite(...).isDefined() ;
    /// @endcode
    ///
    /// @return             True if composite is defined
    virtual bool isDefined() const override;

    /// @brief              Check if composite is empty
    ///
    /// @code{.cpp}
    ///                     Composite(...).isEmpty() ;
    /// @endcode
    ///
    /// @return             True if composite is empty
    bool isEmpty() const;

    /// @brief              Returns true if composite can be converted to underlying object
    ///
    ///                     Only valid if the composite only contains one object.
    ///
    /// @code{.cpp}
    ///                     Composite composite = Composite(Point(0.0, 0.0, 0.0)) ;
    ///                     bool isPoint = composite.is<Point>() ; // True
    /// @endcode
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
    ///                     Only valid if the composite only contains one object.
    ///
    /// @code{.cpp}
    ///                     Composite composite = Composite(Point(0.0, 0.0, 0.0)) ;
    ///                     const Point& point = composite.as<Point>() ;
    /// @endcode
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
    ///                     Composite composite = Composite(Point(0.0, 0.0, 0.0)) ;
    ///                     Point point = { 0.0, 0.0, 0.0 } ;
    ///                     composite.intersects(point) ;
    /// @endcode
    ///
    /// @param              [in] anObject An object
    /// @return             True if composite intersects object
    bool intersects(const Object& anObject) const;

    /// @brief              Check if composite intersects composite
    ///
    /// @code{.cpp}
    ///                     Composite compositeA = Composite(Point(0.0, 0.0, 0.0)) ;
    ///                     Composite compositeB = Composite(Point(0.0, 0.0, 0.0)) ;
    ///                     compositeA.intersects(compositeB) ;
    /// @endcode
    ///
    /// @param              [in] aComposite A composite
    /// @return             True if composite intersects composite
    bool intersects(const Composite& aComposite) const;

    /// @brief              Check if composite contains object
    ///
    /// @code{.cpp}
    ///                     Composite composite = Composite(Sphere({ 0.0, 0.0, 0.0 }, 1.0)) ;
    ///                     Point point = { 0.0, 0.0, 0.0 } ;
    ///                     composite.contains(point) ;
    /// @endcode
    ///
    /// @param              [in] anObject An object
    /// @return             True if composite contains object
    bool contains(const Object& anObject) const;

    /// @brief              Check if composite contains composite
    ///
    /// @code{.cpp}
    ///                     Composite compositeA = Composite(Sphere({ 0.0, 0.0, 0.0 }, 1.0)) ;
    ///                     Composite compositeB = Composite(Point(0.0, 0.0, 0.0)) ;
    ///                     compositeA.contains(compositeB) ;
    /// @endcode
    ///
    /// @param              [in] aComposite A composite
    /// @return             True if composite contains composite
    bool contains(const Composite& aComposite) const;

    /// @brief              Access object at index
    ///
    /// @code{.cpp}
    ///                     Composite composite = Composite(Point(0.0, 0.0, 0.0)) ;
    ///                     const Object& object = composite.accessObjectAt(0) ;
    /// @endcode
    ///
    /// @param              [in] anIndex An object index
    /// @return             Reference to object
    const Object& accessObjectAt(const Index& anIndex) const;

    /// @brief              Access objects in composite
    ///
    /// @code{.cpp}
    ///                     Composite composite = Composite(Point(0.0, 0.0, 0.0)) ;
    ///                     const Array<Unique<Object>>& objects = composite.accessObjects() ;
    /// @endcode
    ///
    /// @return             Reference to objects in composite
    const Array<Unique<Object>>& accessObjects() const;

    /// @brief              Get number of objects in composite
    ///
    /// @code{.cpp}
    ///                     Composite composite = Composite(Point(0.0, 0.0, 0.0)) ;
    ///                     Size count = composite.getObjectCount() ; // 1
    /// @endcode
    ///
    /// @return             Number of objects in composite
    Size getObjectCount() const;

    /// @brief              Compute intersection of composite with object
    ///
    /// @code{.cpp}
    ///                     Composite composite = Composite(Sphere({ 0.0, 0.0, 0.0 }, 1.0)) ;
    ///                     Line line = Line({ 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }) ;
    ///                     Intersection intersection = composite.intersectionWith(line) ;
    /// @endcode
    ///
    /// @param              [in] anObject An object
    /// @return             Intersection of composite with object
    Intersection intersectionWith(const Object& anObject) const;

    /// @brief              Compute intersection of composite with composite
    ///
    /// @code{.cpp}
    ///                     Composite compositeA = Composite(Sphere({ 0.0, 0.0, 0.0 }, 1.0)) ;
    ///                     Composite compositeB = Composite(Sphere({ 0.5, 0.0, 0.0 }, 1.0)) ;
    ///                     Intersection intersection = compositeA.intersectionWith(compositeB) ;
    /// @endcode
    ///
    /// @param              [in] aComposite A composite
    /// @return             Intersection of composite with composite
    Intersection intersectionWith(const Composite& aComposite) const;

    /// @brief              Get const iterator to begin
    ///
    /// @code{.cpp}
    ///                     Composite composite = Composite(Point(0.0, 0.0, 0.0)) ;
    ///                     Composite::ConstIterator it = composite.begin() ;
    /// @endcode
    ///
    /// @return             Const iterator to begin
    Composite::ConstIterator begin() const;

    /// @brief              Get const iterator to end
    ///
    /// @code{.cpp}
    ///                     Composite composite = Composite(Point(0.0, 0.0, 0.0)) ;
    ///                     Composite::ConstIterator it = composite.end() ;
    /// @endcode
    ///
    /// @return             Const iterator to end
    Composite::ConstIterator end() const;

    /// @brief              Print composite
    ///
    /// @code{.cpp}
    ///                     Composite composite = Composite(Point(0.0, 0.0, 0.0)) ;
    ///                     composite.print(std::cout, true) ;
    /// @endcode
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] (optional) displayDecorators If true, display decorators
    virtual void print(std::ostream& anOutputStream, bool displayDecorators = true) const override;

    /// @brief              Apply transformation to composite
    ///
    /// @code{.cpp}
    ///                     Composite composite = Composite(Point(0.0, 0.0, 0.0)) ;
    ///                     composite.applyTransformation(Transformation::Translation({ 1.0, 0.0, 0.0 })) ;
    /// @endcode
    ///
    /// @param              [in] aTransformation A transformation
    virtual void applyTransformation(const Transformation& aTransformation) override;

    /// @brief              Constructs an undefined composite
    ///
    /// @code{.cpp}
    ///                     Composite composite = Composite::Undefined() ; // Undefined
    /// @endcode
    ///
    /// @return             Undefined composite
    static Composite Undefined();

    /// @brief              Constructs an empty composite
    ///
    /// @code{.cpp}
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
}  // namespace d3
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk

#endif
