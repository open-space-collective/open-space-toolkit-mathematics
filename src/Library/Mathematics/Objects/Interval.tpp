////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Objects/Interval.tpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Objects/Interval.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
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
        throw library::core::error::RuntimeError("Lower bound greater than upper bound.") ;
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

    library::core::utils::Print::Header(anOutputStream, "Interval") ;

    library::core::utils::Print::Line(anOutputStream) << "Type:" << Interval<U>::StringFromType(anInterval.type_) ;
    library::core::utils::Print::Line(anOutputStream) << "Lower Bound:" << anInterval.lowerBound_ ;
    library::core::utils::Print::Line(anOutputStream) << "Upper Bound:" << anInterval.upperBound_ ;

    library::core::utils::Print::Footer(anOutputStream) ;

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
        throw library::core::error::runtime::Undefined("Interval") ;
    }

    return lowerBound_ == upperBound_ ;

}

                                template <class T>
bool                            Interval<T>::intersects                     (   const   Interval&                   anInterval                                  ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Interval") ;
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
        throw library::core::error::runtime::Undefined("Value") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Interval") ;
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
            throw library::core::error::runtime::Wrong("Type") ;
            break ;

    }
    
    return false ;

}

                                template <class T>
bool                            Interval<T>::contains                       (   const   Interval&                   anInterval                                  ) const
{

    if (!anInterval.isDefined())
    {
        throw library::core::error::runtime::Undefined("Interval") ;
    }
    
    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Interval") ;
    }

    return this->contains(anInterval.lowerBound_) && this->contains(anInterval.upperBound_) ;

}

                                template <class T>
const T&                        Interval<T>::accessLowerBound               ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Interval") ;
    }
    
    return lowerBound_ ;

}

                                template <class T>
const T&                        Interval<T>::accessUpperBound               ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Interval") ;
    }
    
    return upperBound_ ;

}

                                template <class T>
typename Interval<T>::Type      Interval<T>::getType                        ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Interval") ;
    }
    
    return type_ ;

}

                                template <class T>
T                               Interval<T>::getLowerBound                  ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Interval") ;
    }
    
    return lowerBound_ ;

}

                                template <class T>
T                               Interval<T>::getUpperBound                  ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Interval") ;
    }
    
    return upperBound_ ;

}

//                                 template <class T>
// Interval<T>                     Interval<T>::getIntersectionWith            (   const   Interval&                   anInterval                                  ) const
// {
//     return Interval<T>::Undefined() ; // [TBI]
// }

//                                 template <class T>
// Interval<T>                     Interval<T>::getUnionWith                   (   const   Interval&                   anInterval                                  ) const
// {
//     return Interval<T>::Undefined() ; // [TBI]
// }

                                template <class T>
                                template <class U>
ctnr::Array<T>                  Interval<T>::generateArrayWithStep          (   const   U&                          aStep                                       ) const
{
    
    using library::core::types::Index ;
    using library::core::types::Size ;

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Interval") ;
    }

    if (!aStep.isDefined())
    {
        throw library::core::error::runtime::Undefined("Step") ;
    }
    
    if (aStep.isZero())
    {
        throw library::core::error::RuntimeError("Step is zero.") ;
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
        throw library::core::error::runtime::Wrong("Array size") ;
    }

    const T step = (this->accessUpperBound() - this->accessLowerBound()) / static_cast<T>(anArraySize - 1) ;

    ctnr::Array<T> array(anArraySize, T::Undefined()) ;

    T value = T::Undefined() ;
    typename ctnr::Array<T>::Iterator arrayIt ;

    for (arrayIt = array.begin(), value = this->accessLowerBound(); arrayIt != array.end(); ++arrayIt, value += step)
    {
        *arrayIt = value ;
    }

    return array ;
    
}

//                                 template <class T>
// types::String                   Interval<T>::toString                      ( ) const
// {

//     if (!this->isDefined())
//     {
//         throw library::core::error::runtime::Undefined("Interval") ;
//     }

//     switch (type_)
//     {

//         case Interval<T>::Type::Closed:
//             return "[" + lowerBound_.toString() + ", " + upperBound_.toString() + "]" ;

//         case Interval<T>::Type::Open:
//             return "]" + lowerBound_.toString() + ", " + upperBound_.toString() + "[" ;

//         case Interval<T>::Type::HalfOpenLeft:
//             return "]" + lowerBound_.toString() + ", " + upperBound_.toString() + "]" ;

//         case Interval<T>::Type::HalfOpenRight:
//             return "[" + lowerBound_.toString() + ", " + upperBound_.toString() + "[" ;

//         default:
//             break ;

//     }

//     throw library::core::error::runtime::Wrong("Type") ;
    
//     return types::String::Empty() ;

// }

                                template <class T>
void                            Interval<T>::setType                        (   const   Interval<T>::Type&          aType                                       )
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Interval") ;
    }

    type_ = aType ;

}

                                template <class T>
void                            Interval<T>::setLowerBound                  (   const   T&                          aLowerBound                                 )
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Interval") ;
    }

    if (aLowerBound.isDefined() && upperBound_.isDefined() && (aLowerBound > upperBound_))
    {
        throw library::core::error::RuntimeError("Lower bound greater than upper bound.") ;
    }
    
    lowerBound_ = aLowerBound ;

}

                                template <class T>
void                            Interval<T>::setUpperBound                  (   const   T&                          anUpperBound                                )
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Interval") ;
    }

    if (anUpperBound.isDefined() && lowerBound_.isDefined() && (anUpperBound < lowerBound_))
    {
        throw library::core::error::RuntimeError("Upper bound lower than lower bound.") ;
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

    throw library::core::error::runtime::Wrong("Type") ;

    return types::String::Empty() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////