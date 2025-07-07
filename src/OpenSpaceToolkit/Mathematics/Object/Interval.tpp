/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Object/Interval.hpp>

namespace ostk
{
namespace mathematics
{
namespace object
{

using ostk::core::type::Size;

template <class T>
Interval<T>::Interval(const T& aLowerBound, const T& anUpperBound, const Interval::Type& anIntervalType)
    : type_(anIntervalType),
      lowerBound_(aLowerBound),
      upperBound_(anUpperBound)
{
    if (lowerBound_.isDefined() && upperBound_.isDefined())
    {
        if (lowerBound_ > upperBound_)
        {
            throw ostk::core::error::RuntimeError("Lower bound greater than upper bound.");
        }

        if (lowerBound_ == upperBound_ && type_ != Interval<T>::Type::Closed)
        {
            throw ostk::core::error::RuntimeError("Lower bound equal to upper bound in a non-closed Interval.");
        }
    }
}

template <class T>
bool Interval<T>::operator==(const Interval& anInterval) const
{
    if ((!this->isDefined()) || (!anInterval.isDefined()))
    {
        return false;
    }

    return (type_ == anInterval.type_) && (lowerBound_ == anInterval.lowerBound_) &&
           (upperBound_ == anInterval.upperBound_);
}

template <class T>
bool Interval<T>::operator!=(const Interval& anInterval) const
{
    return !((*this) == anInterval);
}

template <class U>
std::ostream& operator<<(std::ostream& anOutputStream, const Interval<U>& anInterval)
{
    ostk::core::utils::Print::Header(anOutputStream, "Interval");

    ostk::core::utils::Print::Line(anOutputStream) << "Type:" << Interval<U>::StringFromType(anInterval.type_);
    ostk::core::utils::Print::Line(anOutputStream) << "Lower Bound:" << anInterval.lowerBound_;
    ostk::core::utils::Print::Line(anOutputStream) << "Upper Bound:" << anInterval.upperBound_;

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

template <class T>
bool Interval<T>::isDefined() const
{
    return (type_ != Interval::Type::Undefined) && lowerBound_.isDefined() && upperBound_.isDefined();
}

template <class T>
bool Interval<T>::isDegenerate() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    return lowerBound_ == upperBound_;
}

template <class T>
bool Interval<T>::intersects(const Interval& anInterval) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    if (!anInterval.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    return (
        (this->checkAgainstLowerBound(
             anInterval.lowerBound_,
             anInterval.type_ == Interval<T>::Type::Open || anInterval.type_ == Interval<T>::Type::HalfOpenLeft,
             false
         ) ||
         this->checkAgainstLowerBound(
             anInterval.upperBound_,
             anInterval.type_ == Interval<T>::Type::Open || anInterval.type_ == Interval<T>::Type::HalfOpenRight,
             true
         )) &&
        (this->checkAgainstUpperBound(
             anInterval.lowerBound_,
             anInterval.type_ == Interval<T>::Type::Open || anInterval.type_ == Interval<T>::Type::HalfOpenLeft,
             true
         ) ||
         this->checkAgainstUpperBound(
             anInterval.upperBound_,
             anInterval.type_ == Interval<T>::Type::Open || anInterval.type_ == Interval<T>::Type::HalfOpenRight,
             false
         ))
    );
}

template <class T>
bool Interval<T>::contains(const T& aValue) const
{
    if (!aValue.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Value");
    }

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    return this->checkAgainstLowerBound(aValue, false, false) && this->checkAgainstUpperBound(aValue, false, false);
}

template <class T>
bool Interval<T>::contains(const Interval& anInterval) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    if (!anInterval.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    return this->checkAgainstLowerBound(
               anInterval.lowerBound_,
               anInterval.type_ == Interval<T>::Type::Open || anInterval.type_ == Interval<T>::Type::HalfOpenLeft,
               false
           ) &&
           this->checkAgainstUpperBound(
               anInterval.upperBound_,
               anInterval.type_ == Interval<T>::Type::Open || anInterval.type_ == Interval<T>::Type::HalfOpenRight,
               false
           );
}

template <class T>
const T& Interval<T>::accessLowerBound() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    return lowerBound_;
}

template <class T>
const T& Interval<T>::accessUpperBound() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    return upperBound_;
}

template <class T>
typename Interval<T>::Type Interval<T>::getType() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    return type_;
}

template <class T>
T Interval<T>::getLowerBound() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    return lowerBound_;
}

template <class T>
T Interval<T>::getUpperBound() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    return upperBound_;
}

template <class T>
Interval<T> Interval<T>::getIntersectionWith(const Interval& anInterval) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    if (!anInterval.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    const T lowerBound = std::max(lowerBound_, anInterval.lowerBound_);
    const T upperBound = std::min(upperBound_, anInterval.upperBound_);

    if (lowerBound > upperBound)
    {
        return Interval<T>::Undefined();
    }

    bool openLowerBound = false;
    if (lowerBound == lowerBound_)
    {
        if (type_ == Interval<T>::Type::Open || type_ == Interval<T>::Type::HalfOpenLeft)
        {
            openLowerBound = true;
        }
    }

    if (!openLowerBound && lowerBound == anInterval.lowerBound_)
    {
        if (anInterval.type_ == Interval<T>::Type::Open || anInterval.type_ == Interval<T>::Type::HalfOpenLeft)
        {
            openLowerBound = true;
        }
    }

    bool openUpperBound = false;
    if (upperBound == upperBound_)
    {
        if (type_ == Interval<T>::Type::Open || type_ == Interval<T>::Type::HalfOpenRight)
        {
            openUpperBound = true;
        }
    }

    if (!openUpperBound && upperBound == anInterval.upperBound_)
    {
        if (anInterval.type_ == Interval<T>::Type::Open || anInterval.type_ == Interval<T>::Type::HalfOpenRight)
        {
            openUpperBound = true;
        }
    }

    if (openLowerBound && openUpperBound)
    {
        if (lowerBound == upperBound)
        {
            return Interval<T>::Undefined();
        }

        return Interval<T>::Open(lowerBound, upperBound);
    }

    if (openLowerBound)
    {
        if (lowerBound == upperBound)
        {
            return Interval<T>::Undefined();
        }

        return Interval<T>::HalfOpenLeft(lowerBound, upperBound);
    }

    if (openUpperBound)
    {
        if (lowerBound == upperBound)
        {
            return Interval<T>::Undefined();
        }

        return Interval<T>::HalfOpenRight(lowerBound, upperBound);
    }

    return Interval<T>::Closed(lowerBound, upperBound);
}

template <class T>
Interval<T> Interval<T>::getUnionWith(const Interval& anInterval) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    if (!anInterval.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    if ((*this) == anInterval)
    {
        return Interval<T>(lowerBound_, upperBound_, type_);
    }

    if (this->contains(anInterval.lowerBound_) || this->contains(anInterval.upperBound_) ||
        anInterval.contains(lowerBound_) || anInterval.contains(upperBound_))
    {
        const T lowerBound = std::min(lowerBound_, anInterval.lowerBound_);
        const T upperBound = std::max(upperBound_, anInterval.upperBound_);

        bool openLowerBound = true;
        if (lowerBound == lowerBound_)
        {
            if (type_ == Interval<T>::Type::Closed || type_ == Interval<T>::Type::HalfOpenRight)
            {
                openLowerBound = false;
            }
        }

        if (openLowerBound && lowerBound == anInterval.lowerBound_)
        {
            if (anInterval.type_ == Interval<T>::Type::Closed || anInterval.type_ == Interval<T>::Type::HalfOpenRight)
            {
                openLowerBound = false;
            }
        }

        bool openUpperBound = true;
        if (upperBound == upperBound_)
        {
            if (type_ == Interval<T>::Type::Closed || type_ == Interval<T>::Type::HalfOpenLeft)
            {
                openUpperBound = false;
            }
        }

        if (openUpperBound && upperBound == anInterval.upperBound_)
        {
            if (anInterval.type_ == Interval<T>::Type::Closed || anInterval.type_ == Interval<T>::Type::HalfOpenLeft)
            {
                openUpperBound = false;
            }
        }

        return Interval<T>::buildInterval(lowerBound, openLowerBound, upperBound, openUpperBound);
    }

    return Interval<T>::Undefined();
}

template <class T>
template <class U>
ctnr::Array<T> Interval<T>::generateArrayWithStep(const U& aStep) const
{
    using ostk::core::type::Index;
    using ostk::core::type::Size;

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    if (!aStep.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Step");
    }

    if (aStep.isZero())
    {
        throw ostk::core::error::RuntimeError("Step is zero.");
    }

    ctnr::Array<T> grid = ctnr::Array<T>::Empty();

    if (aStep.isPositive())
    {
        T value = this->accessLowerBound();

        if ((type_ == Interval<T>::Type::Open) || (type_ == Interval<T>::Type::HalfOpenLeft))
        {
            value += aStep;
        }

        while (value < this->accessUpperBound())
        {
            grid.add(value);

            value += aStep;
        }

        if ((type_ == Interval<T>::Type::Closed) || (type_ == Interval<T>::Type::HalfOpenLeft))
        {
            grid.add(this->accessUpperBound());
        }
    }
    else
    {
        T value = this->accessUpperBound();

        if ((type_ == Interval<T>::Type::Open) || (type_ == Interval<T>::Type::HalfOpenRight))
        {
            value += aStep;
        }

        while (value > this->accessLowerBound())
        {
            grid.add(value);

            value += aStep;
        }

        if ((type_ == Interval<T>::Type::Closed) || (type_ == Interval<T>::Type::HalfOpenRight))
        {
            grid.add(this->accessLowerBound());
        }
    }

    return grid;
}

template <class T>
ctnr::Array<T> Interval<T>::generateArrayWithSize(const types::Size& anArraySize) const
{
    if (anArraySize < 2)
    {
        throw ostk::core::error::runtime::Wrong("Array size");
    }

    T step = T::Undefined();
    T value = T::Undefined();

    switch (type_)
    {
        case Interval<T>::Type::Closed:
            step = (this->accessUpperBound() - this->accessLowerBound()) / static_cast<T>(anArraySize - 1);
            value = this->accessLowerBound();
            break;

        case Interval<T>::Type::Open:
            step = (this->accessUpperBound() - this->accessLowerBound()) / static_cast<T>(anArraySize + 1);
            value = this->accessLowerBound() + step;
            break;

        case Interval<T>::Type::HalfOpenLeft:
            step = (this->accessUpperBound() - this->accessLowerBound()) / static_cast<T>(anArraySize);
            value = this->accessLowerBound() + step;
            break;

        case Interval<T>::Type::HalfOpenRight:
            step = (this->accessUpperBound() - this->accessLowerBound()) / static_cast<T>(anArraySize);
            value = this->accessLowerBound();
            break;

        default:
            throw ostk::core::error::runtime::Wrong("Type");
            break;
    }

    ctnr::Array<T> array(anArraySize, T::Undefined());

    typename ctnr::Array<T>::Iterator arrayIt;

    for (arrayIt = array.begin(); arrayIt != array.end(); ++arrayIt, value += step)
    {
        *arrayIt = value;
    }

    return array;
}

template <class T>
types::String Interval<T>::toString() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    switch (type_)
    {
        case Interval<T>::Type::Closed:
            return types::String::Format("[{}, {}]", lowerBound_.toString(), upperBound_.toString());

        case Interval<T>::Type::Open:
            return types::String::Format("]{}, {}[", lowerBound_.toString(), upperBound_.toString());

        case Interval<T>::Type::HalfOpenLeft:
            return types::String::Format("]{}, {}]", lowerBound_.toString(), upperBound_.toString());

        case Interval<T>::Type::HalfOpenRight:
            return types::String::Format("[{}, {}[", lowerBound_.toString(), upperBound_.toString());

        default:
            break;
    }

    throw ostk::core::error::runtime::Wrong("Type");

    return types::String::Empty();
}

template <class T>
void Interval<T>::setType(const Interval<T>::Type& aType)
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    type_ = aType;
}

template <class T>
void Interval<T>::setLowerBound(const T& aLowerBound)
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    if (aLowerBound.isDefined() && upperBound_.isDefined() && (aLowerBound > upperBound_))
    {
        throw ostk::core::error::RuntimeError("Lower bound greater than upper bound.");
    }

    lowerBound_ = aLowerBound;
}

template <class T>
void Interval<T>::setUpperBound(const T& anUpperBound)
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    if (anUpperBound.isDefined() && lowerBound_.isDefined() && (anUpperBound < lowerBound_))
    {
        throw ostk::core::error::RuntimeError("Upper bound lower than lower bound.");
    }

    upperBound_ = anUpperBound;
}

template <class T>
Interval<T> Interval<T>::Undefined()
{
    return Interval<T>(T::Undefined(), T::Undefined(), Interval::Type::Undefined);
}

template <class T>
Interval<T> Interval<T>::Closed(const T& aLowerBound, const T& anUpperBound)
{
    return Interval<T>(aLowerBound, anUpperBound, Interval::Type::Closed);
}

template <class T>
Interval<T> Interval<T>::Open(const T& aLowerBound, const T& anUpperBound)
{
    return Interval<T>(aLowerBound, anUpperBound, Interval::Type::Open);
}

template <class T>
Interval<T> Interval<T>::HalfOpenLeft(const T& aLowerBound, const T& anUpperBound)
{
    return Interval<T>(aLowerBound, anUpperBound, Interval::Type::HalfOpenLeft);
}

template <class T>
Interval<T> Interval<T>::HalfOpenRight(const T& aLowerBound, const T& anUpperBound)
{
    return Interval<T>(aLowerBound, anUpperBound, Interval::Type::HalfOpenRight);
}

template <class T>
ctnr::Array<Interval<T>> Interval<T>::Clip(
    const ctnr::Array<Interval<T>>& anIntervalArray, const Interval<T>& anInterval
)
{
    if (!anInterval.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    ctnr::Array<Interval<T>> clipped;

    for (Size i = 0; i < anIntervalArray.getSize(); ++i)
    {
        const auto checkIntersection = anIntervalArray[i].getIntersectionWith(anInterval);
        if (checkIntersection.isDefined())
        {
            clipped.add(checkIntersection);
        }
    }

    return clipped;
}

template <class T>
ctnr::Array<Interval<T>> Interval<T>::Sort(
    const ctnr::Array<Interval<T>>& anIntervalArray, const bool& byLowerBound, const bool& ascending
)
{
    ctnr::Array<Interval<T>> sorted = anIntervalArray;

    if (anIntervalArray.size() == 1 && !anIntervalArray[0].isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Interval");
    }

    const auto comparator = [byLowerBound, ascending](const Interval<T>& anInterval, const Interval<T>& anotherInterval)
    {
        if (!anInterval.isDefined() || !anotherInterval.isDefined())
        {
            throw ostk::core::error::runtime::Undefined("Interval");
        }

        if (byLowerBound)
        {
            return ascending ? anInterval.lowerBound_ < anotherInterval.lowerBound_
                             : anInterval.lowerBound_ > anotherInterval.lowerBound_;
        }

        return ascending ? anInterval.upperBound_ < anotherInterval.upperBound_
                         : anInterval.upperBound_ > anotherInterval.upperBound_;
    };

    std::sort(sorted.begin(), sorted.end(), comparator);

    return sorted;
}

template <class T>
ctnr::Array<Interval<T>> Interval<T>::Merge(const ctnr::Array<Interval<T>>& anIntervalArray)
{
    if (anIntervalArray.empty())
    {
        return {};
    }

    ctnr::Array<Interval<T>> sorted = Interval<T>::Sort(anIntervalArray);

    ctnr::Array<Interval<T>> merged;
    Interval<T> nextUnion = sorted[0];

    for (Size i = 1; i < sorted.size(); ++i)
    {
        auto checkUnion = nextUnion.getUnionWith(sorted[i]);
        if (checkUnion.isDefined())
        {
            nextUnion = checkUnion;
        }
        else
        {
            merged.add(nextUnion);
            nextUnion = sorted[i];
        }
    }

    merged.add(nextUnion);

    return merged;
}

template <class T>
ctnr::Array<Interval<T>> Interval<T>::GetGaps(
    const ctnr::Array<Interval<T>>& anIntervalArray, const Interval<T>& anInterval
)
{
    ctnr::Array<Interval<T>> sanitized = Interval<T>::Merge(anIntervalArray);
    if (anInterval.isDefined())
    {
        sanitized = Interval<T>::Clip(sanitized, anInterval);
    }

    if (sanitized.size() == 0)
    {
        if (anInterval.isDefined())
        {
            return {anInterval};
        }
        return {};
    }

    ctnr::Array<Interval<T>> gaps;

    // Deal with potential leading gap
    if (anInterval.isDefined() && sanitized[0].lowerBound_ > anInterval.lowerBound_)
    {
        const Interval<T> upperInterval = sanitized[0];
        const T lowerBound = anInterval.lowerBound_;
        const T upperBound = upperInterval.lowerBound_;

        bool openLowerBound = true;
        if (anInterval.type_ == Interval<T>::Type::Closed || anInterval.type_ == Interval<T>::Type::HalfOpenRight)
        {
            openLowerBound = false;
        }

        bool openUpperBound = false;
        if (upperInterval.type_ == Interval<T>::Type::Closed || upperInterval.type_ == Interval<T>::Type::HalfOpenRight)
        {
            openUpperBound = true;
        }

        gaps.add(Interval<T>::buildInterval(lowerBound, openLowerBound, upperBound, openUpperBound));
    }

    // Deal with intermediate gaps
    for (Size i = 1; i < sanitized.size(); ++i)
    {
        const Interval<T> lowerInterval = sanitized[i - 1];
        const Interval<T> upperInterval = sanitized[i];
        const T lowerBound = lowerInterval.upperBound_;
        const T upperBound = upperInterval.lowerBound_;

        bool openLowerBound = false;
        if (lowerInterval.type_ == Interval<T>::Type::Closed || lowerInterval.type_ == Interval<T>::Type::HalfOpenLeft)
        {
            openLowerBound = true;
        }

        bool openUpperBound = false;
        if (upperInterval.type_ == Interval<T>::Type::Closed || upperInterval.type_ == Interval<T>::Type::HalfOpenRight)
        {
            openUpperBound = true;
        }

        gaps.add(Interval<T>::buildInterval(lowerBound, openLowerBound, upperBound, openUpperBound));
    }

    // Deal with potential trailing gap
    if (anInterval.isDefined() && sanitized[sanitized.size() - 1].upperBound_ < anInterval.upperBound_)
    {
        const Interval<T> lowerInterval = sanitized[sanitized.size() - 1];
        const T lowerBound = lowerInterval.upperBound_;
        const T upperBound = anInterval.upperBound_;

        bool openLowerBound = false;
        if (lowerInterval.type_ == Interval<T>::Type::Closed || lowerInterval.type_ == Interval<T>::Type::HalfOpenLeft)
        {
            openLowerBound = true;
        }

        bool openUpperBound = true;
        if (anInterval.type_ == Interval<T>::Type::Closed || anInterval.type_ == Interval<T>::Type::HalfOpenLeft)
        {
            openUpperBound = false;
        }

        gaps.add(Interval<T>::buildInterval(lowerBound, openLowerBound, upperBound, openUpperBound));
    }

    return gaps;
}

template <class T>
ctnr::Array<Interval<T>> Interval<T>::LogicalOr(
    const ctnr::Array<Interval<T>>& anIntervalArray, const ctnr::Array<Interval<T>>& anotherIntervalArray
)
{
    ctnr::Array<Interval<T>> array;

    for (Size i = 0; i < anIntervalArray.size(); ++i)
    {
        array.add(anIntervalArray[i]);
    }

    for (Size i = 0; i < anotherIntervalArray.size(); ++i)
    {
        array.add(anotherIntervalArray[i]);
    }

    return Interval<T>::Merge(array);
}

template <class T>
ctnr::Array<Interval<T>> Interval<T>::LogicalAnd(
    const ctnr::Array<Interval<T>>& anIntervalArray, const ctnr::Array<Interval<T>>& anotherIntervalArray
)
{
    const ctnr::Array<Interval<T>> aSanitizedArray = Interval<T>::Merge(anIntervalArray);
    const ctnr::Array<Interval<T>> anotherSanitizedArray = Interval<T>::Merge(anotherIntervalArray);

    if (aSanitizedArray.size() == 0 or anotherSanitizedArray.size() == 0)
    {
        return {};
    }

    // Determine Span lower bound
    bool openLowerBound = true;
    T lowerBound = aSanitizedArray[0].lowerBound_;

    if (aSanitizedArray[0].lowerBound_ < anotherSanitizedArray[0].lowerBound_)
    {
        if (aSanitizedArray[0].type_ == Interval<T>::Type::Closed ||
            aSanitizedArray[0].type_ == Interval<T>::Type::HalfOpenRight)
        {
            openLowerBound = false;
        }
    }

    else if (aSanitizedArray[0].lowerBound_ > anotherSanitizedArray[0].lowerBound_)
    {
        lowerBound = anotherSanitizedArray[0].lowerBound_;

        if (anotherSanitizedArray[0].type_ == Interval<T>::Type::Closed ||
            anotherSanitizedArray[0].type_ == Interval<T>::Type::HalfOpenRight)
        {
            openLowerBound = false;
        }
    }

    else
    {
        if ((aSanitizedArray[0].type_ == Interval<T>::Type::Closed ||
             aSanitizedArray[0].type_ == Interval<T>::Type::HalfOpenRight) &&
            (anotherSanitizedArray[0].type_ == Interval<T>::Type::Closed ||
             anotherSanitizedArray[0].type_ == Interval<T>::Type::HalfOpenRight))
        {
            openLowerBound = false;
        }
    }

    // Determine Span upper bound
    bool openUpperBound = true;
    T upperBound = aSanitizedArray[aSanitizedArray.size() - 1].upperBound_;
    ;

    if (aSanitizedArray[aSanitizedArray.size() - 1].upperBound_ >
        anotherSanitizedArray[anotherSanitizedArray.size() - 1].upperBound_)
    {
        if (aSanitizedArray[aSanitizedArray.size() - 1].type_ == Interval<T>::Type::Closed ||
            aSanitizedArray[aSanitizedArray.size() - 1].type_ == Interval<T>::Type::HalfOpenLeft)
        {
            openUpperBound = false;
        }
    }

    else if (aSanitizedArray[aSanitizedArray.size() - 1].upperBound_ <
             anotherSanitizedArray[anotherSanitizedArray.size() - 1].upperBound_)
    {
        upperBound = anotherSanitizedArray[anotherSanitizedArray.size() - 1].upperBound_;

        if (anotherSanitizedArray[anotherSanitizedArray.size() - 1].type_ == Interval<T>::Type::Closed ||
            anotherSanitizedArray[anotherSanitizedArray.size() - 1].type_ == Interval<T>::Type::HalfOpenLeft)
        {
            openUpperBound = false;
        }
    }

    else
    {
        if ((aSanitizedArray[aSanitizedArray.size() - 1].type_ == Interval<T>::Type::Closed ||
             aSanitizedArray[aSanitizedArray.size() - 1].type_ == Interval<T>::Type::HalfOpenLeft) &&
            (anotherSanitizedArray[anotherSanitizedArray.size() - 1].type_ == Interval<T>::Type::Closed ||
             anotherSanitizedArray[anotherSanitizedArray.size() - 1].type_ == Interval<T>::Type::HalfOpenLeft))
        {
            openUpperBound = false;
        }
    }

    const Interval<T> span = Interval<T>::buildInterval(lowerBound, openLowerBound, upperBound, openUpperBound);

    return Interval<T>::GetGaps(
        Interval<T>::LogicalOr(
            Interval<T>::GetGaps(aSanitizedArray, span), Interval<T>::GetGaps(anotherSanitizedArray, span)
        ),
        span
    );
}

//                                 template <class T>
// Interval<T>                     Interval<T>::Parse                          (   const   types::String& aString )
// {
//     return Interval<T>::Undefined() ; // [TBI]
// }

template <class T>
types::String Interval<T>::StringFromType(const Interval::Type& anIntervalType)
{
    switch (anIntervalType)
    {
        case Interval<T>::Type::Undefined:
            return "Undefined";

        case Interval<T>::Type::Closed:
            return "Closed";

        case Interval<T>::Type::Open:
            return "Open";

        case Interval<T>::Type::HalfOpenLeft:
            return "Half Open Left";

        case Interval<T>::Type::HalfOpenRight:
            return "Half Open Right";
    }

    throw ostk::core::error::runtime::Wrong("Type");

    return types::String::Empty();
}

template <class T>
bool Interval<T>::checkAgainstLowerBound(const T& aValue, const bool& isOpen, const bool& isUpperBound) const
{
    switch (type_)
    {
        case Interval<T>::Type::Closed:
        case Interval<T>::Type::HalfOpenRight:
            if (isOpen && isUpperBound)
            {
                return lowerBound_ < aValue;
            }

            return lowerBound_ <= aValue;

        case Interval<T>::Type::HalfOpenLeft:
        case Interval<T>::Type::Open:
            if (isOpen && !isUpperBound)
            {
                return lowerBound_ <= aValue;
            }

            return lowerBound_ < aValue;

        default:
            throw ostk::core::error::runtime::Wrong("Type");
            break;
    }
}

template <class T>
bool Interval<T>::checkAgainstUpperBound(const T& aValue, const bool& isOpen, const bool& isLowerBound) const
{
    switch (type_)
    {
        case Interval<T>::Type::Closed:
        case Interval<T>::Type::HalfOpenLeft:
            if (isOpen && isLowerBound)
            {
                return upperBound_ > aValue;
            }

            return upperBound_ >= aValue;

        case Interval<T>::Type::HalfOpenRight:
        case Interval<T>::Type::Open:
            if (isOpen && !isLowerBound)
            {
                return upperBound_ >= aValue;
            }

            return upperBound_ > aValue;

        default:
            throw ostk::core::error::runtime::Wrong("Type");
            break;
    }
}

template <class T>
Interval<T> Interval<T>::buildInterval(
    const T& lowerBound, const bool& openLowerBound, const T& upperBound, const bool& openUpperBound
)
{
    if (openLowerBound && openUpperBound)
    {
        return Interval<T>::Open(lowerBound, upperBound);
    }

    if (openLowerBound)
    {
        return Interval<T>::HalfOpenLeft(lowerBound, upperBound);
    }

    if (openUpperBound)
    {
        return Interval<T>::HalfOpenRight(lowerBound, upperBound);
    }

    return Interval<T>::Closed(lowerBound, upperBound);
}

}  // namespace object
}  // namespace mathematics
}  // namespace ostk
