/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Object_Interval__
#define __OpenSpaceToolkit_Mathematics_Object_Interval__

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

namespace ostk
{
namespace mathematics
{
namespace object
{

namespace types = ostk::core::type;
namespace ctnr = ostk::core::container;

/// @brief                      Interval base (used to avoid having a templated enum)

class IntervalBase
{
   public:
    /// @brief              Interval type

    enum class Type
    {

        Undefined,     ///< Undefined interval type
        Closed,        ///< Closed interval type [a, b]
        Open,          ///< Open interval type ]a, b[
        HalfOpenLeft,  ///< Half-open left interval type ]a, b]
        HalfOpenRight  ///< Half-open right interval type [a, b[

    };
};

/// @brief                      Set of numbers with the property that any number that lies between two numbers in the
/// set is also included in the set
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

    Interval(const T& aLowerBound, const T& anUpperBound, const Interval::Type& anIntervalType);

    /// @brief              Equal to operator
    ///
    /// @code
    ///                     Interval<Real>::Closed(0.0, 1.0) == Interval<Real>::Closed(0.0, 1.0) ; // True
    /// @endcode
    ///
    /// @param              [in] anInterval An interval
    /// @return             True if intervals are equal

    bool operator==(const Interval& anInterval) const;

    /// @brief              Not equal to operator
    ///
    /// @code
    ///                     Interval<Real>::Closed(0.0, 1.0) != Interval<Real>::Open(0.0, 1.0) ; // True
    /// @endcode
    ///
    /// @param              [in] anInterval An interval
    /// @return             True if intervals are not equal

    bool operator!=(const Interval& anInterval) const;

    /// @brief              Output stream operator
    ///
    /// @code
    ///                     Interval<Real> interval(0.0, 1.0, Interval::Type::Closed) ;
    ///                     std::cout << interval ;
    /// @endcode
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] anInterval An interval
    /// @return             A reference to output stream

    template <class U>
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Interval<U>& anInterval);

    /// @brief              Check if interval is defined
    ///
    /// @code
    ///                     Interval<Real>::Closed(0.0, 1.0).isDefined() ; // True
    /// @endcode
    ///
    /// @return             True if interval is defined

    bool isDefined() const;

    /// @brief              Check if interval is degenerate, i.e. its lower and upper bounds are the equal
    ///
    /// @code
    ///                     Interval<Real>::Closed(1.0, 1.0).isDegenerate() ; // True
    /// @endcode
    ///
    /// @return             True if interval is degenerate

    bool isDegenerate() const;

    /// @brief              Check if interval is intersecting with another interval
    ///
    /// @code
    ///                     Interval<Real>::Closed(0.0, 1.0).intersects(Interval<Real>::Closed(0.5, 1.5)) ; // True
    /// @endcode
    ///
    /// @param              [in] anInterval An interval
    /// @return             True if intervals are intersecting

    bool intersects(const Interval& anInterval) const;

    /// @brief              Check if interval contains value
    ///
    /// @code
    ///                     Interval<Real>::Closed(0.0, 1.0).contains(0.5) ; // True
    /// @endcode
    ///
    /// @param              [in] aValue A value
    /// @return             True if interval contains value

    bool contains(const T& aValue) const;

    /// @brief              Check if interval contains another interval
    ///
    /// @code
    ///                     Interval<Real>::Closed(0.0, 1.0).contains(Interval<Real>::Open(0.2, 0.8)) ; // True
    /// @endcode
    ///
    /// @param              [in] anInterval An interval
    /// @return             True if interval contains another interval

    bool contains(const Interval& anInterval) const;

    /// @brief              Get reference to lower bound
    ///
    /// @code
    ///                     Interval<Real> interval = Interval<Real>::Closed(0.0, 1.0) ;
    ///                     interval.accessLowerBound() ; // &0.0
    /// @endcode
    ///
    /// @return             Reference to lower bound

    const T& accessLowerBound() const;

    /// @brief              Get reference to upper bound
    ///
    /// @code
    ///                     Interval<Real> interval = Interval<Real>::Closed(0.0, 1.0) ;
    ///                     interval.accessUpperBound() ; // &1.0
    /// @endcode
    ///
    /// @return             Reference to upper bound

    const T& accessUpperBound() const;

    /// @brief              Get interval type
    ///
    /// @code
    ///                     Interval<Real> interval = Interval<Real>::Closed(0.0, 1.0) ;
    ///                     interval.getType() ; // Interval<Real>::Type::Closed
    /// @endcode
    ///
    /// @return             Interval type

    Interval::Type getType() const;

    /// @brief              Get lower bound
    ///
    /// @code
    ///                     Interval<Real> interval = Interval<Real>::Closed(0.0, 1.0) ;
    ///                     interval.getLowerBound() ; // 0.0
    /// @endcode
    ///
    /// @return             Lower bound

    T getLowerBound() const;

    /// @brief              Get upper bound
    ///
    /// @code
    ///                     Interval<Real> interval = Interval<Real>::Closed(0.0, 1.0) ;
    ///                     interval.getUpperBound() ; // 1.0
    /// @endcode
    ///
    /// @return             Upper bound

    T getUpperBound() const;

    /// @brief              Get intersecting interval with another interval
    ///
    /// @code
    ///                     Interval<Real> firstInterval = Interval<Real>::Closed(0.0, 1.0) ;
    ///                     Interval<Real> secondInterval = Interval<Real>::Closed(0.5, 1.5) ;
    ///                     Interval<Real> intersection = firstInterval.getIntersectionWith(secondInterval) ; //
    ///                     [0.5, 1.0]
    /// @endcode
    ///
    /// @param              [in] anInterval An interval
    /// @return             Intersecting interval

    Interval<T> getIntersectionWith(const Interval& anInterval) const;

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

    Interval<T> getUnionWith(const Interval& anInterval) const;

    /// @brief              Generate array from a given step
    ///
    /// @code
    ///                     Interval<Real> interval = Interval<Real>::Closed(0.0, 1.0) ;
    ///                     Array<Real> array = interval.generateArrayWithStep(0.5) ; // [0.0, 0.5, 1.0]
    /// @endcode
    ///
    /// @param              [in] aStep A step
    /// @return             Array of values

    template <class U>
    ctnr::Array<T> generateArrayWithStep(const U& aStep) const;

    /// @brief              Generate array with a given size
    ///
    /// @code
    ///                     Interval<Real> interval = Interval<Real>::Closed(0.0, 1.0) ;
    ///                     Array<Real> array = interval.generateArrayWithSize(3) ; // [0.0, 0.5, 1.0]
    /// @endcode
    ///
    /// @param              [in] anArraySize An array size
    /// @return             Array of values

    ctnr::Array<T> generateArrayWithSize(const types::Size& anArraySize) const;

    /// @brief              Get serialized interval
    ///
    /// @code
    ///                     Interval<Real>::HalfOpenLeft(0.0, 1.0).toString() ; // ]0.0, 1.0]
    /// @endcode
    ///
    /// @return             Serialized interval

    types::String toString() const;

    /// @brief              Interval type setter
    ///
    /// @param              [in] aType An interval type

    void setType(const Interval::Type& aType);

    /// @brief              Interval lower bound setter
    ///
    /// @param              [in] aLowerBound A lower bound

    void setLowerBound(const T& aLowerBound);

    /// @brief              Interval upper bound setter
    ///
    /// @param              [in] anUpperBound An upper bound

    void setUpperBound(const T& anUpperBound);

    /// @brief              Constructs an undefined interval
    ///
    /// @code
    ///                     Interval<Real> interval = Interval<Real>::Undefined() ; // Undefined
    /// @endcode
    ///
    /// @return             Undefined interval

    static Interval<T> Undefined();

    /// @brief              Constructs a closed interval
    ///
    /// @code
    ///                     Interval<Real> interval = Interval<Real>::Closed(0.0, 1.0) ; // [0.0, 1.0]
    /// @endcode
    ///
    /// @return             Closed interval

    static Interval<T> Closed(const T& aLowerBound, const T& anUpperBound);

    /// @brief              Constructs an open interval
    ///
    /// @code
    ///                     Interval<Real> interval = Interval<Real>::Open(0.0, 1.0) ; // ]0.0, 1.0[
    /// @endcode
    ///
    /// @return             Open interval

    static Interval<T> Open(const T& aLowerBound, const T& anUpperBound);

    /// @brief              Constructs an half-open left interval
    ///
    /// @code
    ///                     Interval<Real> interval = Interval<Real>::HalfOpenLeft(0.0, 1.0) ; // ]0.0, 1.0]
    /// @endcode
    ///
    /// @return             Half-open left interval

    static Interval<T> HalfOpenLeft(const T& aLowerBound, const T& anUpperBound);

    /// @brief              Constructs an half-open right interval
    ///
    /// @code
    ///                     Interval<Real> interval = Interval<Real>::HalfOpenRight(0.0, 1.0) ; // [0.0, 1.0[
    /// @endcode
    ///
    /// @return             Half-open right interval

    static Interval<T> HalfOpenRight(const T& aLowerBound, const T& anUpperBound);

    /// @brief              Creates a new array of Intervals clipped by the provided Interval
    ///
    /// @code
    ///                     Array<Interval<Real>> unclipped = {
    ///                         Interval<Real>::Closed(-1.0, 1.0),
    ///                         Interval<Real>::Closed(2.0, 4.0),
    ///                     };
    ///                     const Interval<Real> clipper = Interval<Real>::Closed(0.0, 3.0);
    ///                     Array<Interval<Real>> clipped = Interval<Real>::Clip(unclipped, clipper);
    ///                     // {[0.0, 1.0], [2.0, 3.0]}
    /// @endcode
    ///
    /// @return             Clipped array

    static ctnr::Array<Interval<T>> Clip(
        const ctnr::Array<Interval<T>>& anIntervalArray, const Interval<T>& anInterval
    );

    /// @brief              Creates a new sorted array, the order based on the inputted parameters
    ///
    /// @code
    ///                     Array<Interval<Real>> unsorted = {
    ///                         Interval<Real>::Closed(-1.0, 1.0),
    ///                         Interval<Real>::Closed(-3.0, 0.0),
    ///                     };
    ///                     Array<Interval<Real>> sorted = Interval<Real>::Sort(unsorted); // {[-3.0, 0.0], [-1.0, 1.0]}
    /// @endcode
    ///
    /// @return             Sorted array

    static ctnr::Array<Interval<T>> Sort(
        const ctnr::Array<Interval<T>>& anIntervalArray, const bool& byLowerBound = true, const bool& ascending = true
    );

    /// @brief              Creates a new array without any overlaps and sorted by their lower bound
    ///
    /// @code
    ///                     Array<Interval<Real>> array = {
    ///                         Interval<Real>::Closed(-1.0, 1.0),
    ///                         Interval<Real>::Closed(-2.0, 0.0),
    ///                         Interval<Real>::Closed(3.0, 4.0),
    ///                     };
    ///                     Array<Interval<Real>> merged = Interval<Real>::Merge(array); // {[-2.0, 1.0], [3.0, 4.0]}
    /// @endcode
    ///
    /// @return             Merged array

    static ctnr::Array<Interval<T>> Merge(const ctnr::Array<Interval<T>>& anIntervalArray);

    /// @brief              Creates a new array that contains the gaps between an array of intervals. If
    ///                     an interval is actually defined, only intervals intersecting with the interval are
    ///                     considered and potential leading and trailing gaps w.r.t. the interval boundaries are
    ///                     included. The intervals are previously merged and sorted.
    /// @code
    ///                     Array<Interval<Real>> intervals = {
    ///                         Interval<Real>::Closed(-1.0, 1.0),
    ///                         Interval<Real>::Closed(2.0, 4.0),
    ///                     };
    ///                     const Interval<Real> bounds = Interval<Real>::Closed(1.5, 4.5)
    ///                     Array<Interval<Real>> gaps = Interval<Real>::GetGaps(intervals, bounds);
    ///                     // {[1.5, 2.0], [4.0, 4.5]}
    /// @endcode
    ///
    /// @return             Gaps array

    static ctnr::Array<Interval<T>> GetGaps(
        const ctnr::Array<Interval<T>>& anIntervalArray, const Interval<T>& anInterval = Interval::Undefined()
    );

    /// @brief              Creates a new array that contains the intervals representing a logical 'OR' conjunction
    ///                     between the two arrays.
    /// @code
    ///                     Array<Interval<Real>> anIntervalArray = {
    ///                         Interval<Real>::Closed(-1.0, 1.0),
    ///                         Interval<Real>::Closed(2.0, 4.0),
    ///                     };
    ///
    ///                     Array<Interval<Real>> anotherIntervalArray = {
    ///                         Interval<Real>::Open(0.5, 1.5),
    ///                         Interval<Real>::Open(3.0, 5.0),
    ///                         Interval<Real>::Open(7.0, 8.0),
    ///                     };
    ///
    ///                     Array<Interval<Real>> logicalOr = Interval<Real>::LogicalOr(anIntervalArray,
    ///                     anotherIntervalArray);
    ///                     // {[-1.0, 1.5), [2.0, 5.0), (7.0, 8.0)}
    /// @endcode
    ///
    /// @return             Logical 'OR' array

    static ctnr::Array<Interval<T>> LogicalOr(
        const ctnr::Array<Interval<T>>& anIntervalArray, const ctnr::Array<Interval<T>>& anotherIntervalArray
    );

    /// @brief              Constructs an interval from a given string
    ///
    /// @code
    ///                     Interval<Real> interval = Interval<Real>::Parse("[0.0, 1.0]") ; // [0.0, 1.0]
    /// @endcode
    ///
    /// @param              [in] aString A string
    /// @return             Interval

    static Interval<T> Parse(const types::String& aString);

    /// @brief              Converts interval type to string
    ///
    /// @code
    ///                     Interval<Real>::StringFromType(Interval<Real>::Type::Closed) ; // "Closed"
    /// @endcode
    ///
    /// @param              [in] anIntervalType An interval type
    /// @return             String

    static types::String StringFromType(const Interval::Type& anIntervalType);

   private:
    bool checkAgainstLowerBound(const T& aValue, const bool& isOpen, const bool& isUpperBound) const;
    bool checkAgainstUpperBound(const T& aValue, const bool& isOpen, const bool& isLowerBound) const;
    static Interval<T> buildInterval(
        const T& lowerBound, const bool& openLowerBound, const T& upperBound, const bool& openUpperBound
    );

    Interval::Type type_;

    T lowerBound_;
    T upperBound_;
};

}  // namespace object
}  // namespace mathematics
}  // namespace ostk

#include <OpenSpaceToolkit/Mathematics/Object/Interval.tpp>

#endif
