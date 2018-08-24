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
#include <Library/Core/Types/Size.hpp>

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

/// @brief                      Interval base (used to avoid having a templated enum)

class IntervalBase
{

    public:

        /// @brief              Interval type

        enum class Type
        {

            Undefined,          ///< Undefined interval type
            Closed,             ///< Closed interval type [a, b]
            Open,               ///< Open interval type ]a, b[
            HalfOpenLeft,       ///< Half-open left interval type ]a, b]
            HalfOpenRight       ///< Half-open right interval type [a, b[

        } ;

} ;

/// @brief                      Set of numbers with the property that any number that lies between two numbers in the set is also included in the set
///
/// @ref                        https://en.wikipedia.org/wiki/Interval_(mathematics)

template <class T>
class Interval : public IntervalBase
{

    public:

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

        /// @brief              Equal to operator
        ///
        /// @code
        ///                     Interval<Real>::Closed(0.0, 1.0) == Interval<Real>::Closed(0.0, 1.0) ; // True
        /// @endcode
        ///
        /// @param              [in] anInterval An interval
        /// @return             True if intervals are equal

        bool                    operator ==                                 (   const   Interval&                   anInterval                                  ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     Interval<Real>::Closed(0.0, 1.0) != Interval<Real>::Open(0.0, 1.0) ; // True
        /// @endcode
        ///
        /// @param              [in] anInterval An interval
        /// @return             True if intervals are not equal

        bool                    operator !=                                 (   const   Interval&                   anInterval                                  ) const ;

        /// @brief              Output stream operator
        ///
        /// @code
        ///                     Interval<Real> interval(0.0, 1.0, Interval::Type::Closed) ;
        ///                     std::cout << interval ;
        /// @endcode
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] anInterval An interval
        /// @return             An output stream

        template <class U>
        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Interval<U>&                anInterval                                  ) ;

        /// @brief              Check if interval is defined
        ///
        /// @code
        ///                     Interval<Real>::Closed(0.0, 1.0).isDefined() ; // True
        /// @endcode
        ///
        /// @return             True if interval is defined

        bool                    isDefined                                   ( ) const ;

        /// @brief              Check if interval is degenerate, i.e. its lower and upper bounds are the equal
        ///
        /// @code
        ///                     Interval<Real>::Closed(1.0, 1.0).isDegenerate() ; // True
        /// @endcode
        ///
        /// @return             True if interval is degenerate

        bool                    isDegenerate                                ( ) const ;

        /// @brief              Check if interval is intersecting with another interval
        ///
        /// @code
        ///                     Interval<Real>::Closed(0.0, 1.0).intersects(Interval<Real>::Closed(0.5, 1.5)) ; // True
        /// @endcode
        ///
        /// @param              [in] anInterval An interval
        /// @return             True if intervals are intersecting

        bool                    intersects                                  (   const   Interval&                   anInterval                                  ) const ;

        /// @brief              Check if interval contains value
        ///
        /// @code
        ///                     Interval<Real>::Closed(0.0, 1.0).contains(0.5) ; // True
        /// @endcode
        ///
        /// @param              [in] aValue A value
        /// @return             True if interval contains value

        bool                    contains                                    (   const   T&                          aValue                                      ) const ;

        /// @brief              Check if interval contains another interval
        ///
        /// @code
        ///                     Interval<Real>::Closed(0.0, 1.0).contains(Interval<Real>::Open(0.2, 0.8)) ; // True
        /// @endcode
        ///
        /// @param              [in] anInterval An interval
        /// @return             True if interval contains another interval

        bool                    contains                                    (   const   Interval&                   anInterval                                  ) const ;

        /// @brief              Get reference to lower bound
        ///
        /// @code
        ///                     Interval<Real> interval = Interval<Real>::Closed(0.0, 1.0) ;
        ///                     interval.accessLowerBound() ; // &0.0
        /// @endcode
        ///
        /// @return             Reference to lower bound

        const T&                accessLowerBound                            ( ) const ;

        /// @brief              Get reference to upper bound
        ///
        /// @code
        ///                     Interval<Real> interval = Interval<Real>::Closed(0.0, 1.0) ;
        ///                     interval.accessUpperBound() ; // &1.0
        /// @endcode
        ///
        /// @return             Reference to upper bound

        const T&                accessUpperBound                            ( ) const ;

        /// @brief              Get interval type
        ///
        /// @code
        ///                     Interval<Real> interval = Interval<Real>::Closed(0.0, 1.0) ;
        ///                     interval.getType() ; // Interval<Real>::Type::Closed
        /// @endcode
        ///
        /// @return             Interval type

        Interval::Type          getType                                     ( ) const ;

        /// @brief              Get lower bound
        ///
        /// @code
        ///                     Interval<Real> interval = Interval<Real>::Closed(0.0, 1.0) ;
        ///                     interval.getLowerBound() ; // 0.0
        /// @endcode
        ///
        /// @return             Lower bound

        T                       getLowerBound                               ( ) const ;

        /// @brief              Get upper bound
        ///
        /// @code
        ///                     Interval<Real> interval = Interval<Real>::Closed(0.0, 1.0) ;
        ///                     interval.getUpperBound() ; // 1.0
        /// @endcode
        ///
        /// @return             Upper bound

        T                       getUpperBound                               ( ) const ;

        /// @brief              Get intersecting interval with another interval
        ///
        /// @code
        ///                     Interval<Real> firstInterval = Interval<Real>::Closed(0.0, 1.0) ;
        ///                     Interval<Real> secondInterval = Interval<Real>::Closed(0.5, 1.5) ;
        ///                     Interval<Real> intersection = firstInterval.getIntersectionWith(secondInterval) ; // [0.5, 1.0]
        /// @endcode
        ///
        /// @param              [in] anInterval An interval
        /// @return             Intersecting interval

        Interval<T>             getIntersectionWith                         (   const   Interval&                   anInterval                                  ) const ;

        /// @brief              Get union interval with another interval
        ///
        /// @code
        ///                     Interval<Real> firstInterval = Interval<Real>::Closed(0.0, 1.0) ;
        ///                     Interval<Real> secondInterval = Interval<Real>::Closed(0.5, 1.5) ;
        ///                     Interval<Real> union = firstInterval.getUnionWith(secondInterval) ; // [0.0, 1.5]
        /// @endcode
        ///
        /// @param              [in] anInterval An interval
        /// @return             Union interval

        Interval<T>             getUnionWith                                (   const   Interval&                   anInterval                                  ) const ;

        /// @brief              Generate array from a given step
        ///
        /// @code
        ///                     Interval<Real> interval = Interval<Real>::Closed(0.0, 1.0) ;
        ///                     Array<Real> array = interval.generateArrayWithStep(0.5) ; // [0.0, 0.5, 1.0]
        /// @endcode
        ///
        /// @param              [in] aStep A step
        /// @return             Array of values

        ctnr::Array<T>          generateArrayWithStep                       (   const   T&                          aStep                                       ) const ;

        /// @brief              Generate array with a given size
        ///
        /// @code
        ///                     Interval<Real> interval = Interval<Real>::Closed(0.0, 1.0) ;
        ///                     Array<Real> array = interval.generateArrayWithSize(3) ; // [0.0, 0.5, 1.0]
        /// @endcode
        ///
        /// @param              [in] anArraySize An array size
        /// @return             Array of values

        ctnr::Array<T>          generateArrayWithSize                       (   const   types::Size&                anArraySize                                 ) const ;

        /// @brief              Get serialized interval
        ///
        /// @code
        ///                     Interval<Real>::HalfOpenLeft(0.0, 1.0).toString() ; // ]0.0, 1.0]
        /// @endcode
        ///
        /// @return             Serialized interval

        types::String           toString                                    ( ) const ;

        /// @brief              Interval type setter
        ///
        /// @param              [in] aType An interval type

        void                    setType                                     (   const   Interval::Type&             aType                                       ) ;

        /// @brief              Interval lower bound setter
        ///
        /// @param              [in] aLowerBound A lower bound

        void                    setLowerBound                               (   const   T&                          aLowerBound                                 ) ;

        /// @brief              Interval upper bound setter
        ///
        /// @param              [in] anUpperBound An upper bound

        void                    setUpperBound                               (   const   T&                          anUpperBound                                ) ;

        /// @brief              Constructs an undefined interval
        ///
        /// @code
        ///                     Interval<Real> interval = Interval<Real>::Undefined() ; // Undefined
        /// @endcode
        ///
        /// @return             Undefined interval

        static Interval<T>      Undefined                                   ( ) ;

        /// @brief              Constructs a closed interval
        ///
        /// @code
        ///                     Interval<Real> interval = Interval<Real>::Closed(0.0, 1.0) ; // [0.0, 1.0]
        /// @endcode
        ///
        /// @return             Closed interval

        static Interval<T>      Closed                                      (   const   T&                          aLowerBound,
                                                                                const   T&                          anUpperBound                                ) ;

        /// @brief              Constructs an open interval
        ///
        /// @code
        ///                     Interval<Real> interval = Interval<Real>::Open(0.0, 1.0) ; // ]0.0, 1.0[
        /// @endcode
        ///
        /// @return             Open interval

        static Interval<T>      Open                                        (   const   T&                          aLowerBound,
                                                                                const   T&                          anUpperBound                                ) ;

        /// @brief              Constructs an half-open left interval
        ///
        /// @code
        ///                     Interval<Real> interval = Interval<Real>::HalfOpenLeft(0.0, 1.0) ; // ]0.0, 1.0]
        /// @endcode
        ///
        /// @return             Half-open left interval

        static Interval<T>      HalfOpenLeft                                (   const   T&                          aLowerBound,
                                                                                const   T&                          anUpperBound                                ) ;

        /// @brief              Constructs an half-open right interval
        ///
        /// @code
        ///                     Interval<Real> interval = Interval<Real>::HalfOpenRight(0.0, 1.0) ; // [0.0, 1.0[
        /// @endcode
        ///
        /// @return             Half-open right interval

        static Interval<T>      HalfOpenRight                               (   const   T&                          aLowerBound,
                                                                                const   T&                          anUpperBound                                ) ;

        /// @brief              Constructs an interval from a given string
        ///
        /// @code
        ///                     Interval<Real> interval = Interval<Real>::Parse("[0.0, 1.0]") ; // [0.0, 1.0]
        /// @endcode
        ///
        /// @param              [in] aString A string
        /// @return             Interval

        static Interval<T>      Parse                                       (   const   types::String&              aString                                     ) ;

        /// @brief              Converts interval type to string
        ///
        /// @code
        ///                     Interval<Real>::StringFromType(Interval<Real>::Type::Closed) ; // "Closed"
        /// @endcode
        ///
        /// @param              [in] anIntervalType An interval type
        /// @return             String

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