// Copyright © Loft Orbital Solutions Inc.

#include <OpenSpaceToolkit/Mathematics/Objects/Interval.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace math
{
namespace obj
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                template <class T>
                                Interval<T>::Interval                       (   const   T&                          aLowerBound,
                                                                                const   T&                          anUpperBound,
                                                                                const   Interval::Type&             anIntervalType                              )
                                :   type_(anIntervalType),
                                    lowerBound_(aLowerBound),
                                    upperBound_(anUpperBound)
{

    if (lowerBound_.isDefined() && upperBound_.isDefined() && (lowerBound_ > upperBound_))
    {
        throw ostk::core::error::RuntimeError("Lower bound greater than upper bound.") ;
    }

}

                                template <class T>
bool                            Interval<T>::operator ==                    (   const   Interval&                   anInterval                                  ) const
{

    if ((!this->isDefined()) || (!anInterval.isDefined()))
    {
        return false ;
    }

    return (type_ == anInterval.type_) && (lowerBound_ == anInterval.lowerBound_) && (upperBound_ == anInterval.upperBound_) ;

}

                                template <class T>
bool                            Interval<T>::operator !=                    (   const   Interval&                   anInterval                                  ) const
{
    return !((*this) == anInterval) ;
}

                                template <class U>
std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Interval<U>&                anInterval                                  )
{

    ostk::core::utils::Print::Header(anOutputStream, "Interval") ;

    ostk::core::utils::Print::Line(anOutputStream) << "Type:" << Interval<U>::StringFromType(anInterval.type_) ;
    ostk::core::utils::Print::Line(anOutputStream) << "Lower Bound:" << anInterval.lowerBound_ ;
    ostk::core::utils::Print::Line(anOutputStream) << "Upper Bound:" << anInterval.upperBound_ ;

    ostk::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

                                template <class T>
bool                            Interval<T>::isDefined                      ( ) const
{
    return (type_ != Interval::Type::Undefined) && lowerBound_.isDefined() && upperBound_.isDefined() ;
}

                                template <class T>
bool                            Interval<T>::isDegenerate                   ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval") ;
    }

    return lowerBound_ == upperBound_ ;

}

                                template <class T>
bool                            Interval<T>::intersects                     (   const   Interval&                   anInterval                                  ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval") ;
    }

    return this->contains(anInterval.lowerBound_)
        || this->contains(anInterval.upperBound_)
        || anInterval.contains(lowerBound_)
        || anInterval.contains(upperBound_)
        || (*this) == anInterval ;

}

                                template <class T>
bool                            Interval<T>::contains                       (   const   T&                          aValue                                      ) const
{

    if (!aValue.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Value") ;
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval") ;
    }

    switch (type_)
    {

        case Interval<T>::Type::Closed:
            return (lowerBound_ <= aValue) && (aValue <= upperBound_) ;

        case Interval<T>::Type::Open:
            return (lowerBound_ < aValue) && (aValue < upperBound_) ;

        case Interval<T>::Type::HalfOpenLeft:
            return (lowerBound_ < aValue) && (aValue <= upperBound_) ;

        case Interval<T>::Type::HalfOpenRight:
            return (lowerBound_ <= aValue) && (aValue < upperBound_) ;

        default:
            throw ostk::core::error::runtime::Wrong("Type") ;
            break ;

    }

    return false ;

}

                                template <class T>
bool                            Interval<T>::contains                       (   const   Interval&                   anInterval                                  ) const
{

    if (!anInterval.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval") ;
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval") ;
    }

    return this->contains(anInterval.lowerBound_) && this->contains(anInterval.upperBound_) ;

}

                                template <class T>
const T&                        Interval<T>::accessLowerBound               ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval") ;
    }

    return lowerBound_ ;

}

                                template <class T>
const T&                        Interval<T>::accessUpperBound               ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval") ;
    }

    return upperBound_ ;

}

                                template <class T>
typename Interval<T>::Type      Interval<T>::getType                        ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval") ;
    }

    return type_ ;

}

                                template <class T>
T                               Interval<T>::getLowerBound                  ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval") ;
    }

    return lowerBound_ ;

}

                                template <class T>
T                               Interval<T>::getUpperBound                  ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval") ;
    }

    return upperBound_ ;

}

                                template <class T>
Interval<T>                     Interval<T>::getIntersectionWith            (   const   Interval&                   anInterval                                  ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval") ;
    }

    if (!anInterval.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval") ;
    }

    if (anInterval.getType() != type_)
    {
        throw ostk::core::error::runtime::ToBeImplemented("Intersection between different Interval::Type of interval.") ;
    }

    const T lowerBound = std::max(lowerBound_, anInterval.getLowerBound()) ;
    const T upperBound = std::min(upperBound_, anInterval.getUpperBound()) ;

    if (lowerBound > upperBound)
    {
        return Interval<T>::Undefined() ;
    }

    return Interval<T>(lowerBound, upperBound, type_) ;

}

                                template <class T>
Interval<T>                     Interval<T>::getUnionWith                   (   const   Interval&                   anInterval                                  ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval") ;
    }

    if (!anInterval.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval") ;
    }

    if (anInterval.getType() != type_)
    {
        throw ostk::core::error::runtime::ToBeImplemented("Union between different Interval::Type of interval.") ;
    }

    if (!this->intersects(anInterval))
    {
        return Interval<T>::Undefined() ;
    }

    const T lowerBound = std::min(lowerBound_, anInterval.getLowerBound()) ;
    const T upperBound = std::max(upperBound_, anInterval.getUpperBound()) ;

    if (lowerBound > upperBound)
    {
        return Interval<T>::Undefined() ;
    }

    return Interval<T>(lowerBound, upperBound, type_) ;

}

                                template <class T>
                                template <class U>
ctnr::Array<T>                  Interval<T>::generateArrayWithStep          (   const   U&                          aStep                                       ) const
{

    using ostk::core::types::Index ;
    using ostk::core::types::Size ;

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval") ;
    }

    if (!aStep.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Step") ;
    }

    if (aStep.isZero())
    {
        throw ostk::core::error::RuntimeError("Step is zero.") ;
    }

    ctnr::Array<T> grid = ctnr::Array<T>::Empty() ;

    if (aStep.isPositive())
    {

        T value = this->accessLowerBound() ;

        while (value <= this->accessUpperBound())
        {

            grid.add(value) ;

            value += aStep ;

        }

        if (grid.accessLast() < this->accessUpperBound())
        {
            grid.add(this->accessUpperBound()) ;
        }

    }
    else
    {

        T value = this->accessUpperBound() ;

        while (value >= this->accessLowerBound())
        {

            grid.add(value) ;

            value += aStep ;

        }

        if (grid.accessLast() > this->accessLowerBound())
        {
            grid.add(this->accessLowerBound()) ;
        }

    }

    return grid ;

}

                                template <class T>
ctnr::Array<T>                  Interval<T>::generateArrayWithSize          (   const   types::Size&                anArraySize                                 ) const
{

    if (anArraySize < 2)
    {
        throw ostk::core::error::runtime::Wrong("Array size") ;
    }

    T step = T::Undefined() ;
    T value = T::Undefined() ;

    switch (type_)
    {

        case Interval<T>::Type::Closed:
            step = (this->accessUpperBound() - this->accessLowerBound()) / static_cast<T>(anArraySize - 1) ;
            value = this->accessLowerBound() ;
            break ;

        case Interval<T>::Type::Open:
            step = (this->accessUpperBound() - this->accessLowerBound()) / static_cast<T>(anArraySize + 1) ;
            value = this->accessLowerBound() + step ;
            break ;

        case Interval<T>::Type::HalfOpenLeft:
            step = (this->accessUpperBound() - this->accessLowerBound()) / static_cast<T>(anArraySize) ;
            value = this->accessLowerBound() + step ;
            break ;

        case Interval<T>::Type::HalfOpenRight:
            step = (this->accessUpperBound() - this->accessLowerBound()) / static_cast<T>(anArraySize) ;
            value = this->accessLowerBound() ;
            break ;

        default:
            throw ostk::core::error::runtime::Wrong("Type") ;
            break ;

    }

    ctnr::Array<T> array(anArraySize, T::Undefined()) ;

    typename ctnr::Array<T>::Iterator arrayIt ;

    for (arrayIt = array.begin(); arrayIt != array.end(); ++arrayIt, value += step)
    {
        *arrayIt = value ;
    }

    return array ;

}

                                template <class T>
types::String                   Interval<T>::toString                      ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval") ;
    }

    switch (type_)
    {

        case Interval<T>::Type::Closed:
            return types::String::Format("[{}, {}]", lowerBound_.toString(), upperBound_.toString()) ;

        case Interval<T>::Type::Open:
            return types::String::Format("]{}, {}[", lowerBound_.toString(), upperBound_.toString()) ;

        case Interval<T>::Type::HalfOpenLeft:
            return types::String::Format("]{}, {}]", lowerBound_.toString(), upperBound_.toString()) ;

        case Interval<T>::Type::HalfOpenRight:
            return types::String::Format("[{}, {}[", lowerBound_.toString(), upperBound_.toString()) ;

        default:
            break ;

    }

    throw ostk::core::error::runtime::Wrong("Type") ;

    return types::String::Empty() ;

}

                                template <class T>
void                            Interval<T>::setType                        (   const   Interval<T>::Type&          aType                                       )
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval") ;
    }

    type_ = aType ;

}

                                template <class T>
void                            Interval<T>::setLowerBound                  (   const   T&                          aLowerBound                                 )
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval") ;
    }

    if (aLowerBound.isDefined() && upperBound_.isDefined() && (aLowerBound > upperBound_))
    {
        throw ostk::core::error::RuntimeError("Lower bound greater than upper bound.") ;
    }

    lowerBound_ = aLowerBound ;

}

                                template <class T>
void                            Interval<T>::setUpperBound                  (   const   T&                          anUpperBound                                )
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval") ;
    }

    if (anUpperBound.isDefined() && lowerBound_.isDefined() && (anUpperBound < lowerBound_))
    {
        throw ostk::core::error::RuntimeError("Upper bound lower than lower bound.") ;
    }

    upperBound_ = anUpperBound ;

}

                                template <class T>
Interval<T>                     Interval<T>::Undefined                      ( )
{
    return Interval<T>(T::Undefined(), T::Undefined(), Interval::Type::Undefined) ;
}

                                template <class T>
Interval<T>                     Interval<T>::Closed                         (   const   T&                          aLowerBound,
                                                                                const   T&                          anUpperBound                                )
{
    return Interval<T>(aLowerBound, anUpperBound, Interval::Type::Closed) ;
}

                                template <class T>
Interval<T>                     Interval<T>::Open                           (   const   T&                          aLowerBound,
                                                                                const   T&                          anUpperBound                                )
{
    return Interval<T>(aLowerBound, anUpperBound, Interval::Type::Open) ;
}

                                template <class T>
Interval<T>                     Interval<T>::HalfOpenLeft                   (   const   T&                          aLowerBound,
                                                                                const   T&                          anUpperBound                                )
{
    return Interval<T>(aLowerBound, anUpperBound, Interval::Type::HalfOpenLeft) ;
}

                                template <class T>
Interval<T>                     Interval<T>::HalfOpenRight                  (   const   T&                          aLowerBound,
                                                                                const   T&                          anUpperBound                                )
{
    return Interval<T>(aLowerBound, anUpperBound, Interval::Type::HalfOpenRight) ;
}

//                                 template <class T>
// Interval<T>                     Interval<T>::Parse                          (   const   types::String&              aString                                     )
// {
//     return Interval<T>::Undefined() ; // [TBI]
// }

                                template <class T>
types::String                   Interval<T>::StringFromType                 (   const   Interval::Type&             anIntervalType                              )
{

    switch (anIntervalType)
    {

        case Interval<T>::Type::Undefined:
            return "Undefined" ;

        case Interval<T>::Type::Closed:
            return "Closed" ;

        case Interval<T>::Type::Open:
            return "Open" ;

        case Interval<T>::Type::HalfOpenLeft:
            return "Half Open Left" ;

        case Interval<T>::Type::HalfOpenRight:
            return "Half Open Right" ;

    }

    throw ostk::core::error::runtime::Wrong("Type") ;

    return types::String::Empty() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
