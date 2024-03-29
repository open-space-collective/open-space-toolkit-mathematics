/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Intersection.hpp>

namespace ostk
{
namespace mathematics
{
namespace geometry
{
namespace d2
{

Intersection::Intersection(Array<Unique<Object>>&& anObjectArray)
    : type_(Intersection::TypeFromObjects(anObjectArray)),
      composite_(std::move(anObjectArray))
{
}

Intersection::Intersection(const Intersection& anIntersection)
    : type_(anIntersection.type_),
      composite_(anIntersection.composite_)
{
}

Intersection::~Intersection() {}

Intersection& Intersection::operator=(const Intersection& anIntersection)
{
    if (this != &anIntersection)
    {
        type_ = anIntersection.type_;
        composite_ = anIntersection.composite_;
    }

    return *this;
}

bool Intersection::operator==(const Intersection& anIntersection) const
{
    if ((!this->isDefined()) || (!anIntersection.isDefined()))
    {
        return false;
    }

    return (type_ == anIntersection.type_) && (composite_ == anIntersection.composite_);
}

bool Intersection::operator!=(const Intersection& anIntersection) const
{
    return !((*this) == anIntersection);
}

Intersection Intersection::operator+(const Intersection& anIntersection) const
{
    if (!anIntersection.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Intersection");
    }

    Intersection intersection;

    intersection.composite_ = composite_ + anIntersection.composite_;

    intersection.type_ = Intersection::TypeFromObjects(intersection.composite_.accessObjects());

    return intersection;
}

Intersection& Intersection::operator+=(const Intersection& anIntersection)
{
    if (!anIntersection.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Intersection");
    }

    composite_ += anIntersection.composite_;

    type_ = Intersection::TypeFromObjects(composite_.accessObjects());

    return *this;
}

std::ostream& operator<<(std::ostream& anOutputStream, const Intersection& anIntersection)
{
    ostk::core::utils::Print::Header(anOutputStream, "Intersection");

    ostk::core::utils::Print::Line(anOutputStream) << "Type:" << Intersection::StringFromType(anIntersection.type_);

    ostk::core::utils::Print::Line(anOutputStream) << "Composite:";

    anIntersection.composite_.print(anOutputStream, false);

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool Intersection::isDefined() const
{
    return type_ != Intersection::Type::Undefined;
}

bool Intersection::isEmpty() const
{
    return type_ == Intersection::Type::Empty;
}

bool Intersection::isComplex() const
{
    return type_ == Intersection::Type::Complex;
}

const Composite& Intersection::accessComposite() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Intersection");
    }

    return composite_;
}

Intersection::Type Intersection::getType() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Intersection");
    }

    return type_;
}

Intersection Intersection::Undefined()
{
    Intersection intersection;

    intersection.type_ = Intersection::Type::Undefined;

    return intersection;
}

Intersection Intersection::Empty()
{
    return {Array<Unique<Object>>::Empty()};
}

Intersection Intersection::Point(const object::Point& aPoint)
{
    Intersection intersection;

    intersection.type_ = Intersection::Type::Point;

    intersection.composite_ = Composite {aPoint};

    return intersection;
}

Intersection Intersection::PointSet(const object::PointSet& aPointSet)
{
    Intersection intersection;

    intersection.type_ = Intersection::Type::PointSet;

    intersection.composite_ = Composite {aPointSet};

    return intersection;
}

Intersection Intersection::LineString(const object::LineString& aLineString)
{
    Intersection intersection;

    intersection.type_ = Intersection::Type::LineString;

    intersection.composite_ = Composite {aLineString};

    return intersection;
}

Intersection Intersection::Line(const object::Line& aLine)
{
    Intersection intersection;

    intersection.type_ = Intersection::Type::Line;

    intersection.composite_ = Composite {aLine};

    return intersection;
}

Intersection Intersection::Segment(const object::Segment& aSegment)
{
    Intersection intersection;

    intersection.type_ = Intersection::Type::Segment;

    intersection.composite_ = Composite {aSegment};

    return intersection;
}

Intersection Intersection::Polygon(const object::Polygon& aPolygon)
{
    Intersection intersection;

    intersection.type_ = Intersection::Type::Polygon;

    intersection.composite_ = Composite {aPolygon};

    return intersection;
}

String Intersection::StringFromType(const Intersection::Type& aType)
{
    switch (aType)
    {
        case Intersection::Type::Undefined:
            return "Undefined";

        case Intersection::Type::Empty:
            return "Empty";

        case Intersection::Type::Point:
            return "Point";

        case Intersection::Type::PointSet:
            return "PointSet";

        case Intersection::Type::Line:
            return "Line";

        case Intersection::Type::Segment:
            return "Segment";

        case Intersection::Type::LineString:
            return "LineString";

        case Intersection::Type::Polygon:
            return "Polygon";

        case Intersection::Type::Complex:
            return "Complex";

        default:
            throw ostk::core::error::runtime::Wrong("Type");
            break;
    }

    return String::Empty();
}

Intersection::Intersection()
    : type_(Intersection::Type::Undefined),
      composite_(Composite::Undefined())
{
}

Intersection::Type Intersection::TypeFromObjects(const Array<Unique<Object>>& anObjectArray)
{
    if (anObjectArray.isEmpty())
    {
        return Intersection::Type::Empty;
    }

    Intersection::Type type = Intersection::Type::Undefined;

    for (const auto& objectUPtr : anObjectArray)
    {
        const Intersection::Type objectType = Intersection::TypeFromObjects(objectUPtr);

        if (type == Intersection::Type::Undefined)
        {
            type = objectType;
        }
        else if (type != objectType)
        {
            return Intersection::Type::Complex;
        }
    }

    return type;
}

Intersection::Type Intersection::TypeFromObjects(const Unique<Object>& anObjectUPtr)
{
    if (dynamic_cast<const object::Point*>(anObjectUPtr.get()))
    {
        return Intersection::Type::Point;
    }

    if (dynamic_cast<const object::PointSet*>(anObjectUPtr.get()))
    {
        return Intersection::Type::PointSet;
    }

    if (dynamic_cast<const object::Line*>(anObjectUPtr.get()))
    {
        return Intersection::Type::Line;
    }

    if (dynamic_cast<const object::Segment*>(anObjectUPtr.get()))
    {
        return Intersection::Type::Segment;
    }

    if (dynamic_cast<const object::LineString*>(anObjectUPtr.get()))
    {
        return Intersection::Type::LineString;
    }

    if (dynamic_cast<const object::Polygon*>(anObjectUPtr.get()))
    {
        return Intersection::Type::Polygon;
    }

    return Intersection::Type::Undefined;
}

}  // namespace d2
}  // namespace geometry
}  // namespace mathematics
}  // namespace ostk
