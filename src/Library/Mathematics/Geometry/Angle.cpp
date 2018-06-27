////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/Angle.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/Angle.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace math
{
namespace geom
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Angle::Angle                                (   const   Real&                       aValue,
                                                                                const   Angle::Unit&                aUnit                                       )
                                :   value_(aValue),
                                    unit_(aUnit)
{

}

bool                            Angle::operator ==                          (   const   Angle&                      anAngle                                     ) const
{

    if ((unit_ == Angle::Unit::Undefined) || (anAngle.unit_ == Angle::Unit::Undefined))
    {
        return false ;
    }

    switch (unit_)
    {

        case Angle::Unit::Radian:
            return value_ == Angle::ReduceRange(((anAngle.unit_ == Angle::Unit::Radian) ? anAngle.value_ : anAngle.in(Angle::Unit::Radian)), value_, value_ + Real::TwoPi()) ;

        case Angle::Unit::Degree:
            return value_ == Angle::ReduceRange(((anAngle.unit_ == Angle::Unit::Degree) ? anAngle.value_ : anAngle.in(Angle::Unit::Degree)), value_, value_ + 360.0) ;

        case Angle::Unit::Arcminute:
            return value_ == Angle::ReduceRange(((anAngle.unit_ == Angle::Unit::Arcminute) ? anAngle.value_ : anAngle.in(Angle::Unit::Arcminute)), value_, value_ + 21600.0) ;

        case Angle::Unit::Arcsecond:
            return value_ == Angle::ReduceRange(((anAngle.unit_ == Angle::Unit::Arcsecond) ? anAngle.value_ : anAngle.in(Angle::Unit::Arcsecond)), value_, value_ + 1296000.0) ;

        case Angle::Unit::Revolution:
            return value_ == Angle::ReduceRange(((anAngle.unit_ == Angle::Unit::Revolution) ? anAngle.value_ : anAngle.in(Angle::Unit::Revolution)), value_, value_ + 1.0) ;

        default:
            throw library::core::error::runtime::Wrong("Unit") ;
            break ;

    }

    return false ;

}

bool                            Angle::operator !=                          (   const   Angle&                      anAngle                                     ) const
{
    return !((*this) == anAngle) ;
}

Angle                           Angle::operator +                           (   const   Angle&                      anAngle                                     ) const
{

    if ((unit_ == Angle::Unit::Undefined) || (anAngle.unit_ == Angle::Unit::Undefined))
    {
        throw library::core::error::runtime::Undefined("Angle") ;
    }

    return Angle((value_ + ((unit_ == anAngle.unit_) ? anAngle.value_ : anAngle.in(unit_))), unit_) ;

}

Angle                           Angle::operator -                           (   const   Angle&                      anAngle                                     ) const
{

    if ((unit_ == Angle::Unit::Undefined) || (anAngle.unit_ == Angle::Unit::Undefined))
    {
        throw library::core::error::runtime::Undefined("Angle") ;
    }

    return Angle((value_ - ((unit_ == anAngle.unit_) ? anAngle.value_ : anAngle.in(unit_))), unit_) ;

}

Angle                           Angle::operator *                           (   const   Real&                       aReal                                       ) const
{

    if (unit_ == Angle::Unit::Undefined)
    {
        throw library::core::error::runtime::Undefined("Angle") ;
    }

    if (!aReal.isDefined())
    {
        throw library::core::error::runtime::Undefined("Real") ;
    }

    return Angle((value_ * aReal), unit_) ;

}

Angle                           Angle::operator /                           (   const   Real&                       aReal                                       ) const
{

    if (unit_ == Angle::Unit::Undefined)
    {
        throw library::core::error::runtime::Undefined("Angle") ;
    }

    if (!aReal.isDefined())
    {
        throw library::core::error::runtime::Undefined("Real") ;
    }

    if (aReal.isZero())
    {
        throw library::core::error::RuntimeError("Cannot divide by zero.") ;
    }

    return Angle((value_ / aReal), unit_) ;

}

Angle&                          Angle::operator +=                          (   const   Angle&                      anAngle                                     )
{

    if ((unit_ == Angle::Unit::Undefined) || (anAngle.unit_ == Angle::Unit::Undefined))
    {
        throw library::core::error::runtime::Undefined("Angle") ;
    }

    value_ += ((unit_ == anAngle.unit_) ? anAngle.value_ : anAngle.in(unit_)) ;

    return (*this) ;

}

Angle&                          Angle::operator -=                          (   const   Angle&                      anAngle                                     )
{

    if ((unit_ == Angle::Unit::Undefined) || (anAngle.unit_ == Angle::Unit::Undefined))
    {
        throw library::core::error::runtime::Undefined("Angle") ;
    }

    value_ -= ((unit_ == anAngle.unit_) ? anAngle.value_ : anAngle.in(unit_)) ;

    return (*this) ;

}

Angle&                          Angle::operator *=                          (   const   Real&                       aReal                                       )
{

    if (unit_ == Angle::Unit::Undefined)
    {
        throw library::core::error::runtime::Undefined("Angle") ;
    }

    if (!aReal.isDefined())
    {
        throw library::core::error::runtime::Undefined("Real") ;
    }

    value_ *= aReal ;

    return (*this) ;

}

Angle&                          Angle::operator /=                          (   const   Real&                       aReal                                       )
{

    if (unit_ == Angle::Unit::Undefined)
    {
        throw library::core::error::runtime::Undefined("Angle") ;
    }

    if (!aReal.isDefined())
    {
        throw library::core::error::runtime::Undefined("Real") ;
    }

    if (aReal.isZero())
    {
        throw library::core::error::RuntimeError("Cannot divide by zero.") ;
    }

    value_ /= aReal ;

    return (*this) ;

}

Angle                           operator *                                  (   const   Real&                       aReal,
                                                                                const   Angle&                      anAngle                                     )
{

    if (!aReal.isDefined())
    {
        throw library::core::error::runtime::Undefined("Real") ;
    }

    if (anAngle.unit_ == Angle::Unit::Undefined)
    {
        throw library::core::error::runtime::Undefined("Angle") ;
    }
    
    return Angle((anAngle.value_ * aReal), anAngle.unit_) ;

}

Angle                           Angle::operator +                           ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Angle") ;
    }
    
    return Angle(value_, unit_) ;

}
        
Angle                           Angle::operator -                           ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Angle") ;
    }
    
    return Angle(-value_, unit_) ;

}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Angle&                      anAngle                                     )
{

    library::core::utils::Print::Header(anOutputStream, "Angle") ;

    library::core::utils::Print::Line(anOutputStream) << "Value:" << anAngle.value_ ;
    library::core::utils::Print::Line(anOutputStream) << "Unit:" << Angle::StringFromUnit(anAngle.unit_) ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Angle::isDefined                            ( ) const
{
    return value_.isDefined() && (unit_ != Angle::Unit::Undefined) ;
}

Angle::Unit                     Angle::getUnit                              ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Angle") ;
    }
    
    return unit_ ;

}

Real                            Angle::in                                   (   const   Angle::Unit&                aUnit                                       ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Angle") ;
    }

    if (unit_ == aUnit)
    {
        return value_ ;
    }

    return value_ * Angle::SIRatio(unit_) / Angle::SIRatio(aUnit) ;

}

Real                            Angle::inRadians                            ( ) const
{
    return this->in(Angle::Unit::Radian) ;
}

// Real                            Angle::inRadians                            (   const    Real&                      aLowerBound,
//                                                                                 const    Real&                      anUpperBound                                ) const
// {

// }

Real                            Angle::inDegrees                            ( ) const
{
    return this->in(Angle::Unit::Degree) ;
}

// Real                            Angle::inDegrees                            (   const    Real&                      aLowerBound,
//                                                                                 const    Real&                      anUpperBound                                ) const
// {

// }

Real                            Angle::inArcminutes                         ( ) const
{
    return this->in(Angle::Unit::Arcminute) ;
}

// Real                            Angle::inArcminutes                         (   const    Real&                      aLowerBound,
//                                                                                 const    Real&                      anUpperBound                                ) const
// {

// }

Real                            Angle::inArcseconds                         ( ) const
{
    return this->in(Angle::Unit::Arcsecond) ;
}

// Real                            Angle::inArcseconds                         (   const    Real&                      aLowerBound,
//                                                                                 const    Real&                      anUpperBound                                ) const
// {

// }

Real                            Angle::inRevolutions                        ( ) const
{
    return this->in(Angle::Unit::Revolution) ;
}

String                          Angle::toString                             ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Angle") ;
    }

    return value_.getString() + " [" + Angle::SymbolFromUnit(unit_) + "]" ;

}

Angle                           Angle::Undefined                            ( )
{
    return Angle(Real::Undefined(), Angle::Unit::Undefined) ;
}

Angle                           Angle::Zero                                 ( )
{
    return Angle(Real::Zero(), Angle::Unit::Radian) ;
}

Angle                           Angle::Radians                              (   const   Real&                       aValue                                      )
{
    return Angle(aValue, Angle::Unit::Radian) ;
}

Angle                           Angle::Degrees                              (   const   Real&                       aValue                                      )
{
    return Angle(aValue, Angle::Unit::Degree) ;
}

Angle                           Angle::Arcminutes                           (   const   Real&                       aValue                                      )
{
    return Angle(aValue, Angle::Unit::Arcminute) ;
}

Angle                           Angle::Arcseconds                           (   const   Real&                       aValue                                      )
{
    return Angle(aValue, Angle::Unit::Arcsecond) ;
}

Angle                           Angle::Revolutions                          (   const   Real&                       aValue                                      )
{
    return Angle(aValue, Angle::Unit::Revolution) ;
}

// Angle                            Angle::Parse                               (   const   String&                     aString                                     )
// {

// }

String                          Angle::StringFromUnit                       (   const   Angle::Unit&                aUnit                                       )
{

    switch (aUnit)
    {

        case Angle::Unit::Undefined:
            return "Undefined" ;
            
        case Angle::Unit::Radian:
            return "Radian" ;
            
        case Angle::Unit::Degree:
            return "Degree" ;
            
        case Angle::Unit::Arcminute:
            return "Arcminute" ;
            
        case Angle::Unit::Arcsecond:
            return "Arcsecond" ;

        case Angle::Unit::Revolution:
            return "Revolution" ;
            
        default:
            throw library::core::error::runtime::Wrong("Unit") ;
            break ;

    }

    return String::Empty() ;

}

String                          Angle::SymbolFromUnit                       (   const   Angle::Unit&               aUnit                                       )
{

    switch (aUnit)
    {

        case Angle::Unit::Radian:
            return "rad" ;
            
        case Angle::Unit::Degree:
            return "deg" ;
            
        case Angle::Unit::Arcminute:
            return "amin" ;
            
        case Angle::Unit::Arcsecond:
            return "asec" ;
            
        case Angle::Unit::Revolution:
            return "rev" ;
            
        default:
            throw library::core::error::runtime::Wrong("Unit") ;
            break ;

    }

    return String::Empty() ;

}

Real                            Angle::SIRatio                              (   const   Angle::Unit&                aUnit                                       )
{

    switch (aUnit)
    {

        case Angle::Unit::Radian:
            return 1.0 ;

        case Angle::Unit::Degree:
            return Real::Pi() / 180.0 ;

        case Angle::Unit::Arcminute:
            return Real::Pi() / 10800.0 ;

        case Angle::Unit::Arcsecond:
            return Real::Pi() / 648000.0 ;

        case Angle::Unit::Revolution:
            return Real::TwoPi() ;

        default:
            throw library::core::error::runtime::Wrong("Unit") ;
            break ;

    }

    return Real::Undefined() ;

}

Real                            Angle::ReduceRange                          (   const    Real&                      aValue,
                                                                                const    Real&                      aRangeLowerBound,
                                                                                const    Real&                      aRangeUpperBound                            )
{

    if ((aValue >= aRangeLowerBound) && (aValue < aRangeUpperBound)) // Value already in range
    {
        return aValue ;
    }

    Real value = aValue ;

    const Real range = aRangeUpperBound - aRangeLowerBound ;

    while (value < aRangeLowerBound) // [TBM] This is a STUPID implementation: just used as a logic placeholder... should be improved ASAP
    {
        value += range ;
    }
    
    while (value >= aRangeUpperBound) // [TBM] This is a STUPID implementation: just used as a logic placeholder... should be improved ASAP
    {
        value -= range ;
    }

    return value ;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////