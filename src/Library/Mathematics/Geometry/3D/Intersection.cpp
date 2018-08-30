////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/3D/Intersection.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Intersection.hpp>

#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace math
{
namespace geom
{
namespace d3
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Intersection::Intersection                  (   const   Array<Unique<Object>>&      anObjectArray                               )
                                :   type_(Intersection::TypeFromObjects(anObjectArray)),
                                    objects_(Array<Unique<Object>>::Empty())
{

    objects_.reserve(anObjectArray.getSize()) ;
    std::transform(anObjectArray.begin(), anObjectArray.end(), std::back_inserter(objects_), [] (const Unique<Object>& anObjectUPtr) -> Unique<Object> { return Unique<Object>(anObjectUPtr->clone()) ; }) ;

}

                                Intersection::Intersection                  (   const   Intersection&               anIntersection                              )
                                :   type_(anIntersection.type_),
                                    objects_(Array<Unique<Object>>::Empty())
{

    objects_.reserve(anIntersection.objects_.getSize()) ;
    std::transform(anIntersection.objects_.begin(), anIntersection.objects_.end(), std::back_inserter(objects_), [] (const Unique<Object>& anObjectUPtr) -> Unique<Object> { return Unique<Object>(anObjectUPtr->clone()) ; }) ;

}

                                Intersection::~Intersection                 ( )
{

}

Intersection&                   Intersection::operator =                    (   const   Intersection&               anIntersection                              )
{

    if (this != &anIntersection)
    {

        type_ = anIntersection.type_ ;

        objects_.clear() ;
        objects_.reserve(anIntersection.objects_.getSize()) ;
        std::transform(anIntersection.objects_.begin(), anIntersection.objects_.end(), std::back_inserter(objects_), [] (const Unique<Object>& anObjectUPtr) -> Unique<Object> { return Unique<Object>(anObjectUPtr->clone()) ; }) ;

    }

    return *this ;

}

bool                            Intersection::operator ==                   (   const   Intersection&               anIntersection                              ) const
{

    if ((!this->isDefined()) || (!anIntersection.isDefined()))
    {
        return false ;
    }

    if (type_ != anIntersection.type_)
    {
        return false ;
    }

    // [TBI]

    throw library::core::error::runtime::ToBeImplemented("Intersection :: operator ==") ;

    return false ;

}

bool                            Intersection::operator !=                   (   const   Intersection&               anIntersection                              ) const
{
    return !((*this) == anIntersection) ;
}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Intersection&               anIntersection                              )
{

    library::core::utils::Print::Header(anOutputStream, "Intersection") ;

    library::core::utils::Print::Line(anOutputStream) << "Type:"                << Intersection::StringFromType(anIntersection.type_) ;

    if (!anIntersection.objects_.isEmpty())
    {

        library::core::utils::Print::Separator(anOutputStream, "Objects") ;

        for (const auto& objectUPtr : anIntersection.objects_)
        {
            anOutputStream << (*objectUPtr) ;
        }

    }

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Intersection::isDefined                     ( ) const
{
    return type_ != Intersection::Type::Undefined ;
}

bool                            Intersection::isEmpty                       ( ) const
{
    return type_ == Intersection::Type::Empty ;
}

Intersection::Type              Intersection::getType                       ( ) const
{
    return type_ ;
}

Intersection                    Intersection::Undefined                     ( )
{
    
    Intersection intersection ;

    intersection.type_ = Intersection::Type::Undefined ;

    return intersection ;

}

Intersection                    Intersection::Empty                         ( )
{
    return Intersection(Array<Unique<Object>>::Empty()) ;
}

Intersection                    Intersection::Point                         (   const   objects::Point&             aPoint                                      )
{

    Intersection intersection ;

    intersection.type_ = Intersection::Type::Point ;

    intersection.objects_.emplace_back(Unique<Object>(aPoint.clone())) ;

    return intersection ;

}

Intersection                    Intersection::PointSet                      (   const   objects::PointSet&          aPointSet                                   )
{

    Intersection intersection ;

    intersection.type_ = Intersection::Type::PointSet ;
    
    intersection.objects_.emplace_back(Unique<Object>(aPointSet.clone())) ;

    return intersection ;

}

Intersection                    Intersection::LineString                    (   const   objects::LineString&        aLineString                                 )
{

    Intersection intersection ;

    intersection.type_ = Intersection::Type::LineString ;
    
    intersection.objects_.emplace_back(Unique<Object>(aLineString.clone())) ;

    return intersection ;

}

String                          Intersection::StringFromType                (   const   Intersection::Type&         aType                                       )
{

    switch (aType)
    {

        case Intersection::Type::Undefined:
            return "Undefined" ;

        case Intersection::Type::Empty:
            return "Empty" ;

        case Intersection::Type::Point:
            return "Point" ;

        case Intersection::Type::PointSet:
            return "PointSet" ;

        case Intersection::Type::Line:
            return "Line" ;

        case Intersection::Type::LineString:
            return "LineString" ;

        case Intersection::Type::Ray:
            return "Ray" ;

        case Intersection::Type::Segment:
            return "Segment" ;

        case Intersection::Type::Plane:
            return "Plane" ;

        case Intersection::Type::Sphere:
            return "Sphere" ;

        case Intersection::Type::Ellipsoid:
            return "Ellipsoid" ;

        case Intersection::Type::Complex:
            return "Complex" ;

        default:
            throw library::core::error::runtime::Wrong("Type") ;
            break ;

    }

    return String::Empty() ;

}

                                Intersection::Intersection                  ( )
                                :   type_(Intersection::Type::Undefined),
                                    objects_(Array<Unique<Object>>::Empty())
{

}

Intersection::Type              Intersection::TypeFromObjects               (   const   Array<Unique<Object>>&      anObjectArray                               )
{

    if (anObjectArray.isEmpty())
    {
        return Intersection::Type::Empty ;
    }

    Intersection::Type type = Intersection::Type::Undefined ;

    for (const auto& objectUPtr : anObjectArray)
    {

        const Intersection::Type objectType = Intersection::TypeFromObject(objectUPtr) ;

        if (type == Intersection::Type::Undefined)
        {
            type = objectType ;
        }
        else if (type != objectType)
        {
            return Intersection::Type::Complex ;
        }

    }

    return type ;

}

Intersection::Type              Intersection::TypeFromObject                (   const   Unique<Object>&             anObjectUPtr                                )
{

    if (dynamic_cast<const objects::Point*>(anObjectUPtr.get()))
    {
        return Intersection::Type::Point ;
    }

    // if (dynamic_cast<const objects::PointSet*>(anObjectUPtr.get()))
    // {
    //     return Intersection::Type::PointSet ;
    // }

    // [TBI]

    if (dynamic_cast<const objects::Segment*>(anObjectUPtr.get()))
    {
        return Intersection::Type::Segment ;
    }

    if (dynamic_cast<const objects::Sphere*>(anObjectUPtr.get()))
    {
        return Intersection::Type::Sphere ;
    }

    if (dynamic_cast<const objects::Ellipsoid*>(anObjectUPtr.get()))
    {
        return Intersection::Type::Ellipsoid ;
    }

    return Intersection::Type::Undefined ;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////