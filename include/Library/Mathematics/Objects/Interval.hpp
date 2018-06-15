////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Objects/Interval.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Mathematics_Objects_Interval__
#define __Library_Mathematics_Objects_Interval__

#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Types/String.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace math
{
namespace obj
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace types = library::core::types ;
namespace ctnr = library::core::ctnr ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Set of numbers with the property that any number that lies between two numbers in the set is also included in the set
///
/// @ref                        https://en.wikipedia.org/wiki/Interval_(mathematics)

template <class T>
class Interval
{

    public:

        enum class Type
        {

            Undefined,
            Closed,
            Open,
            HalfOpenLeft,
            HalfOpenRight

        } ;

        /// @brief              Constructor
        ///
        /// @code
        ///                     Interval<Real> interval(0.0, 1.0, Interval::Type::Closed) ;
        /// @endcode
        ///
        /// @param              [in] aLowerBound A lower bound
        /// @param              [in] anUpperBound An upper bound
        /// @param              [in] anIntervalType An interval type

                                Interval                                    (   const   T&                          aLowerBound,
                                                                                const   T&                          anUpperBound,
                                                                                const   Interval::Type&             anIntervalType                              ) ;

        bool                    operator ==                                 (   const   Interval&                   anInterval                                  ) const ;

        bool                    operator !=                                 (   const   Interval&                   anInterval                                  ) const ;

        template <class U>
        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Interval<U>&                anInterval                                  ) ;

        bool                    isDefined                                   ( ) const ;

        bool                    isDegenerate                                ( ) const ;

        bool                    isIntersectingWith                          (   const   Interval&                   anInterval                                  ) const ;

        bool                    contains                                    (   const   T&                          aValue                                      ) const ;

        bool                    contains                                    (   const   Interval&                   anInterval                                  ) const ;

        const T&                accessLowerBound                            ( ) const ;

        const T&                accessUpperBound                            ( ) const ;

        Interval::Type          getType                                     ( ) const ;

        T                       getLowerBound                               ( ) const ;

        T                       getUpperBound                               ( ) const ;

        Interval<T>             getIntersectionWith                         (   const   Interval&                   anInterval                                  ) const ;

        Interval<T>             getUnionWith                                (   const   Interval&                   anInterval                                  ) const ;

        ctnr::Array<T>          generateArrayWithStep                       (   const   T&                          aStep                                       ) const ;

        ctnr::Array<T>          generateArrayWithSize                       (   const   uint&                       aStepCount                                  ) const ;

        types::String           getString                                   ( ) const ;

        void                    setType                                     (   const   Interval::Type&             aType                                       ) ;

        void                    setLowerBound                               (   const   T&                          aLowerBound                                 ) ;

        void                    setUpperBound                               (   const   T&                          anUpperBound                                ) ;

        static Interval<T>      Undefined                                   ( ) ;

        static Interval<T>      Closed                                      (   const   T&                          aLowerBound,
                                                                                const   T&                          anUpperBound                                ) ;

        static Interval<T>      Open                                        (   const   T&                          aLowerBound,
                                                                                const   T&                          anUpperBound                                ) ;

        static Interval<T>      HalfOpenLeft                                (   const   T&                          aLowerBound,
                                                                                const   T&                          anUpperBound                                ) ;

        static Interval<T>      HalfOpenRight                               (   const   T&                          aLowerBound,
                                                                                const   T&                          anUpperBound                                ) ;

        static Interval<T>      Parse                                       (   const   types::String&              aString                                     ) ;

        static types::String    StringFromType                              (   const   Interval::Type&             anIntervalType                              ) ;

    private:

        Interval::Type          type_ ;

        T                       lowerBound_ ;
        T                       upperBound_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Objects/Interval.tpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////