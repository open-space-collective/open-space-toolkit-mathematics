/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Transformation.hpp>
// #include <OpenSpaceToolkit/Mathematics/Geometry/2D/Intersection.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Composite.hpp>

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

Composite::Composite(const Object& anObject)
    : Object(),
      defined_(true),
      object_(Array<Unique<Object>>::Empty())
{
    object_.emplace_back(Unique<Object>(anObject.clone()));
}

Composite::Composite(const Unique<Object>& anObjectUPtr)
    : Object(),
      defined_(true),
      object_(Array<Unique<Object>>::Empty())
{
    object_.emplace_back(Unique<Object>(anObjectUPtr->clone()));
}

Composite::Composite(Array<Unique<Object>>&& anObjectArray)
    : Object(),
      defined_(true),
      object_(Array<Unique<Object>>::Empty())
{
    object_.reserve(anObjectArray.getSize());

    std::transform(
        anObjectArray.begin(),
        anObjectArray.end(),
        std::back_inserter(object_),
        [](const Unique<Object>& anObjectUPtr) -> Unique<Object>
        {
            return Unique<Object>(anObjectUPtr->clone());
        }
    );
}

Composite::Composite(const Composite& aComposite)
    : Object(),
      defined_(aComposite.defined_),
      object_(Array<Unique<Object>>::Empty())
{
    object_.reserve(aComposite.object_.getSize());

    std::transform(
        aComposite.object_.begin(),
        aComposite.object_.end(),
        std::back_inserter(object_),
        [](const Unique<Object>& anObjectUPtr) -> Unique<Object>
        {
            return Unique<Object>(anObjectUPtr->clone());
        }
    );
}

Composite* Composite::clone() const
{
    return new Composite(*this);
}

Composite& Composite::operator=(const Composite& aComposite)
{
    if (this != &aComposite)
    {
        defined_ = aComposite.defined_;

        object_.clear();

        object_.reserve(aComposite.object_.getSize());

        std::transform(
            aComposite.object_.begin(),
            aComposite.object_.end(),
            std::back_inserter(object_),
            [](const Unique<Object>& anObjectUPtr) -> Unique<Object>
            {
                return Unique<Object>(anObjectUPtr->clone());
            }
        );
    }

    return *this;
}

bool Composite::operator==(const Composite& aComposite) const
{
    if ((!this->isDefined()) || (!aComposite.isDefined()))
    {
        return false;
    }

    if (object_.getSize() != aComposite.object_.getSize())
    {
        return false;
    }

    for (const auto objectTuple : ostk::core::ctnr::iterators::Zip(object_, aComposite.object_))
    {
        if ((*std::get<0>(objectTuple)) != (*std::get<1>(objectTuple)))
        {
            return false;
        }
    }

    return true;
}

bool Composite::operator!=(const Composite& aComposite) const
{
    return !((*this) == aComposite);
}

Composite Composite::operator+(const Composite& aComposite) const
{
    if (!aComposite.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Composite");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Composite");
    }

    Composite composite = Composite::Empty();

    composite.object_.reserve(object_.getSize() + aComposite.object_.getSize());

    std::transform(
        object_.begin(),
        object_.end(),
        std::back_inserter(composite.object_),
        [](const Unique<Object>& anObjectUPtr) -> Unique<Object>
        {
            return Unique<Object>(anObjectUPtr->clone());
        }
    );
    std::transform(
        aComposite.object_.begin(),
        aComposite.object_.end(),
        std::back_inserter(composite.object_),
        [](const Unique<Object>& anObjectUPtr) -> Unique<Object>
        {
            return Unique<Object>(anObjectUPtr->clone());
        }
    );

    return composite;
}

Composite& Composite::operator+=(const Composite& aComposite)
{
    if (!aComposite.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Composite");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Composite");
    }

    object_.reserve(object_.getSize() + aComposite.object_.getSize());

    std::transform(
        aComposite.object_.begin(),
        aComposite.object_.end(),
        std::back_inserter(object_),
        [](const Unique<Object>& anObjectUPtr) -> Unique<Object>
        {
            return Unique<Object>(anObjectUPtr->clone());
        }
    );

    return *this;
}

bool Composite::isDefined() const
{
    return defined_ && std::all_of(
                           object_.begin(),
                           object_.end(),
                           [](const Unique<Object>& anObjectUPtr) -> bool
                           {
                               return anObjectUPtr->isDefined();
                           }
                       );
}

bool Composite::isEmpty() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Composite");
    }

    return object_.isEmpty();
}

bool Composite::intersects(const Object& anObject) const
{
    if (!anObject.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Object");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Composite");
    }

    return std::any_of(
        object_.begin(),
        object_.end(),
        [&anObject](const Unique<Object>& anObjectUPtr) -> bool
        {
            return anObjectUPtr->intersects(anObject);
        }
    );
}

bool Composite::intersects(const Composite& aComposite) const
{
    if (!aComposite.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Composite");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Composite");
    }

    return std::any_of(
        aComposite.object_.begin(),
        aComposite.object_.end(),
        [this](const Unique<Object>& anObjectUPtr) -> bool
        {
            return this->intersects(*anObjectUPtr);
        }
    );
}

bool Composite::contains(const Object& anObject) const
{
    if (!anObject.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Object");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Composite");
    }

    if (this->isEmpty())
    {
        return false;
    }

    return std::all_of(
        object_.begin(),
        object_.end(),
        [&anObject](const Unique<Object>& anObjectUPtr) -> bool
        {
            return anObjectUPtr->contains(anObject);
        }
    );
}

bool Composite::contains(const Composite& aComposite) const
{
    if (!aComposite.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Composite");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Composite");
    }

    if (this->isEmpty())
    {
        return false;
    }

    return std::all_of(
        aComposite.object_.begin(),
        aComposite.object_.end(),
        [this](const Unique<Object>& anObjectUPtr) -> bool
        {
            return this->contains(*anObjectUPtr);
        }
    );
}

bool Composite::anyContains(const Object& anObject) const
{
    if (!anObject.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Object");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Composite");
    }

    if (this->isEmpty())
    {
        return false;
    }

    return std::any_of(
        object_.begin(),
        object_.end(),
        [&anObject](const Unique<Object>& anObjectUPtr) -> bool
        {
            return anObjectUPtr->contains(anObject);
        }
    );
}

bool Composite::anyContains(const Composite& aComposite) const
{
    if (!aComposite.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Composite");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Composite");
    }

    if (this->isEmpty())
    {
        return false;
    }

    return std::any_of(
        aComposite.object_.begin(),
        aComposite.object_.end(),
        [this](const Unique<Object>& anObjectUPtr) -> bool
        {
            return this->contains(*anObjectUPtr);
        }
    );
}

const Object& Composite::accessObjectAt(const Index& anIndex) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Composite");
    }

    if (anIndex >= object_.getSize())
    {
        throw ostk::core::error::RuntimeError("Object index [{}] out of bounds [{}].", anIndex, object_.getSize());
    }

    return *(object_.at(anIndex).get());
}

const Array<Unique<Object>>& Composite::accessObject() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Composite");
    }

    return object_;
}

Size Composite::getObjectCount() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Composite");
    }

    return object_.getSize();
}

// Intersection                    Composite::intersectionWith                 (   const   Object& anObject ) const
// {

//     if (!anObject.isDefined())
//     {
//         throw ostk::core::error::runtime::Undefined("Object") ;
//     }

//     if (!this->isDefined())
//     {
//         throw ostk::core::error::runtime::Undefined("Composite") ;
//     }

//     Intersection intersection = Intersection::Empty() ;

//     for (const auto& objectUPtr : object_)
//     {

//         const Intersection objectToObjectIntersection = objectUPtr->intersectionWith(anObject) ;

//         if (objectToObjectIntersection.isDefined() && (!objectToObjectIntersection.isEmpty()))
//         {
//             intersection += objectToObjectIntersection ;
//         }

//     }

//     return intersection ;

// }

// Intersection                    Composite::intersectionWith                 (   const   Composite& aComposite ) const
// {

//     if (!aComposite.isDefined())
//     {
//         throw ostk::core::error::runtime::Undefined("Composite") ;
//     }

//     if (!this->isDefined())
//     {
//         throw ostk::core::error::runtime::Undefined("Composite") ;
//     }

//     Intersection intersection = Intersection::Empty() ;

//     for (const auto& objectUPtr : aComposite.object_)
//     {

//         const Intersection compositeToObjectIntersection = this->intersectionWith(*objectUPtr) ;

//         if (compositeToObjectIntersection.isDefined() && (!compositeToObjectIntersection.isEmpty()))
//         {
//             intersection += compositeToObjectIntersection ;
//         }

//     }

//     return intersection ;

// }

Composite::ConstIterator Composite::begin() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Composite");
    }

    return object_.begin();
}

Composite::ConstIterator Composite::end() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Composite");
    }

    return object_.end();
}

String Composite::toString(const Object::Format& aFormat, const Integer& aPrecision) const
{
    (void)aPrecision;

    switch (aFormat)
    {
        case Object::Format::Standard:
            return String::Empty();  // TBI

        default:
            throw ostk::core::error::runtime::Wrong("Format");
            break;
    }

    return String::Empty();
}

void Composite::print(std::ostream& anOutputStream, bool displayDecorators) const
{
    displayDecorators ? ostk::core::utils::Print::Header(anOutputStream, "Composite") : void();

    if (!object_.isEmpty())
    {
        ostk::core::utils::Print::Separator(anOutputStream, "Object");

        for (const auto& objectUPtr : object_)
        {
            anOutputStream << (*objectUPtr);
        }
    }
    else
    {
        ostk::core::utils::Print::Line(anOutputStream) << "Empty";
    }

    displayDecorators ? ostk::core::utils::Print::Footer(anOutputStream) : void();
}

void Composite::applyTransformation(const Transformation& aTransformation)
{
    if (!aTransformation.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Transformation");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Composite");
    }

    if (aTransformation.isIdentity())
    {
        return;
    }

    for (auto& objectUPtr : object_)
    {
        objectUPtr->applyTransformation(aTransformation);
    }
}

Composite Composite::Undefined()
{
    Composite composite = Composite::Empty();

    composite.defined_ = false;

    return composite;
}

Composite Composite::Empty()
{
    return Composite {Array<Unique<Object>>::Empty()};
}

}  // namespace object
}  // namespace d2
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk
