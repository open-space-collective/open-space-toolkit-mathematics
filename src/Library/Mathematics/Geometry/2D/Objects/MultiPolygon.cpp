////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           Library/Mathematics/Geometry/2D/Objects/MultiPolygon.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/2D/Transformation.hpp>
#include <Library/Mathematics/Geometry/2D/Objects/MultiPolygon.hpp>

#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Size.hpp>
#include <Library/Core/Types/Index.hpp>
#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <boost/geometry/io/wkt/wkt.hpp>
#include <boost/geometry/strategies/transform/matrix_transformers.hpp>
#include <boost/geometry/strategies/transform.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry.hpp>
#include <boost/numeric/ublas/matrix.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace math
{
namespace geom
{
namespace d2
{
namespace objects
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using boost::geometry::cs::cartesian ;
using boost::geometry::model::point ;
using boost::geometry::model::ring ;
using boost::geometry::model::polygon ;
using boost::geometry::model::multi_polygon ;

using library::core::types::Index ;
using library::core::types::Size ;
using library::core::types::String ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MultiPolygon::Impl
{

    public:

                                Impl                                        ( ) ;

                                Impl                                        (   const   Array<Polygon>&             aPolygonArray                               ) ;

                                ~Impl                                       ( ) = default ;

        bool                    operator ==                                 (   const   MultiPolygon::Impl&         aMultiPolygon                               ) const ;

        bool                    isDefined                                   ( ) const ;

        bool                    contains                                    (   const   Point&                      aPoint                                      ) const ;

        bool                    contains                                    (   const   PointSet&                   aPointSet                                   ) const ;

        Size                    getPolygonCount                             ( ) const ;

        Array<Polygon>          getPolygons                                 ( ) const ;

        MultiPolygon::Impl      unionWith                                   (   const   MultiPolygon::Impl&         aMultiPolygon                               ) const ;

        String                  toString                                    (   const   Object::Format&             aFormat,
                                                                                const   Integer&                    aPrecision                                  ) const ;

        void                    applyTransformation                         (   const   Transformation&             aTransformation                             ) ;

    private:

        typedef                 point<double, 2, cartesian>                     BoostPoint ;
        typedef                 ring<Impl::BoostPoint>                          BoostRing ;
        typedef                 polygon<Impl::BoostPoint>                       BoostPolygon ;
        typedef                 multi_polygon<Impl::BoostPolygon>               BoostMultiPolygon ;

    Impl::BoostMultiPolygon multiPolygon_ ;

        static Impl::BoostMultiPolygon BoostMultiPolygonFromPolygons        (   const   Array<Polygon>&             aPolygonArray                               ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                MultiPolygon::Impl::Impl                    ( )
                                :   multiPolygon_()
{

}

                                MultiPolygon::Impl::Impl                    (   const   Array<Polygon>&             aPolygonArray                               )
                                :   multiPolygon_(MultiPolygon::Impl::BoostMultiPolygonFromPolygons(aPolygonArray))
{

}

bool                            MultiPolygon::Impl::operator ==             (   const   MultiPolygon::Impl&         aMultiPolygon                               ) const
{
    return boost::geometry::equals(multiPolygon_, aMultiPolygon.multiPolygon_) ;
}

bool                            MultiPolygon::Impl::isDefined               ( ) const
{
    return !multiPolygon_.empty() ;
}

bool                            MultiPolygon::Impl::contains                (   const   Point&                      aPoint                                      ) const
{

    try
    {
        return boost::geometry::covered_by(MultiPolygon::Impl::BoostPoint(aPoint.x(), aPoint.y()), multiPolygon_) ;
    }
    catch (const std::exception& anException)
    {
        throw library::core::error::RuntimeError("Error when checking if multi-polygon contains point: [{}]", anException.what()) ;
    }

    return false ;

}

bool                            MultiPolygon::Impl::contains                (   const   PointSet&                   aPointSet                                   ) const
{

    (void) aPointSet ;

    throw library::core::error::runtime::ToBeImplemented("MultiPolygon::contains (PointSet&)") ;

    return false ;

}

Size                            MultiPolygon::Impl::getPolygonCount         ( ) const
{
    return multiPolygon_.size() ;
}

// Array<Polygon>                  MultiPolygon::Impl::getPolygons             ( ) const
// {

//     Array<Polygon> polygons = Array<Polygon>::Empty() ;

//     for (const auto& polygon : multiPolygon_)
//     {

//         Array<Point> outerRing =
//         Array<Array<Point>> innerRings =

//         const Polygon polygon = { outerRing, innerRings } ;

//         polygons.add(polygon) ;

//     }

//     return polygons ;

// }

MultiPolygon::Impl              MultiPolygon::Impl::unionWith               (   const   MultiPolygon::Impl&         aMultiPolygon                               ) const
{

    try
    {

        MultiPolygon::Impl multiPolygonUnion ;

        boost::geometry::union_(multiPolygon_, aMultiPolygon.multiPolygon_, multiPolygonUnion.multiPolygon_) ;

        return multiPolygonUnion ;

    }
    catch (const std::exception& anException)
    {
        throw library::core::error::RuntimeError("Cannot compute union of multi-polyons: [{}].", anException.what()) ;
    }

}

String                          MultiPolygon::Impl::toString                (   const   Object::Format&             aFormat,
                                                                                const   Integer&                    aPrecision                                  ) const
{

    switch (aFormat)
    {

        case Object::Format::Standard:
        case Object::Format::WKT:
        {

            std::stringstream stringStream ;

            if (aPrecision.isDefined())
            {
                stringStream << std::fixed << std::setprecision(aPrecision) << boost::geometry::wkt(multiPolygon_) ;
            }
            else
            {
                stringStream << boost::geometry::wkt(multiPolygon_) ;
            }

            return stringStream.str() ;

        }

        default:
            throw library::core::error::runtime::Wrong("Format") ;
            break ;

    }

    return String::Empty() ;

}

void                            MultiPolygon::Impl::applyTransformation     (   const   Transformation&             aTransformation                             )
{

    using library::math::obj::Matrix3d ;

    MultiPolygon::Impl::BoostMultiPolygon transformedMultiPolygon ;

    const Matrix3d transformationMatrix = aTransformation.getMatrix() ;

    const boost::geometry::strategy::transform::matrix_transformer<double, 2, 2> transform = { transformationMatrix(0, 0), transformationMatrix(0, 1), transformationMatrix(0, 2),
                                                                                               transformationMatrix(1, 0), transformationMatrix(1, 1), transformationMatrix(1, 2),
                                                                                               transformationMatrix(2, 0), transformationMatrix(2, 1), transformationMatrix(2, 2) } ;

    boost::geometry::transform(multiPolygon_, transformedMultiPolygon, transform) ;

    multiPolygon_ = transformedMultiPolygon ;

}

MultiPolygon::Impl::BoostMultiPolygon MultiPolygon::Impl::BoostMultiPolygonFromPolygons ( const Array<Polygon>&     aPolygonArray                               )
{

    MultiPolygon::Impl::BoostMultiPolygon boostMultiPolygon ;

    for (const auto& polygon : aPolygonArray)
    {

        MultiPolygon::Impl::BoostPolygon boostPolygon ;

        for (const auto& point : polygon.getOuterRing())
        {
            boost::geometry::append(boostPolygon, MultiPolygon::Impl::BoostPoint(point.x(), point.y())) ;
        }

        for (Index innerRingIndex = 0; innerRingIndex < polygon.getInnerRingCount(); ++innerRingIndex)
        {

            const auto innerRing = polygon.getInnerRingAt(innerRingIndex) ;

            MultiPolygon::Impl::BoostRing boostRing ;

            for (const auto& innerRingPoint : innerRing)
            {
                boost::geometry::append(boostRing, MultiPolygon::Impl::BoostPoint(innerRingPoint.x(), innerRingPoint.y())) ;
            }

            boost::geometry::correct(boostRing) ;

            boostPolygon.inners().push_back(boostRing) ;

        }

        boostMultiPolygon.push_back(boostPolygon) ;

    }

    boost::geometry::correct(boostMultiPolygon) ;

    return boostMultiPolygon ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                MultiPolygon::MultiPolygon                  (   const   Array<Polygon>&             aPolygonArray                               )
                                :   Object(),
                                    implUPtr_(std::make_unique<MultiPolygon::Impl>(aPolygonArray))
{

}

                                MultiPolygon::MultiPolygon                  (   const   MultiPolygon&               aMultiPolygon                               )
                                :   Object(aMultiPolygon),
                                    implUPtr_((aMultiPolygon.implUPtr_ != nullptr) ? new MultiPolygon::Impl(*aMultiPolygon.implUPtr_) : nullptr)
{

}

                                MultiPolygon::~MultiPolygon                 ( )
{

}

MultiPolygon&                   MultiPolygon::operator =                    (   const   MultiPolygon&               aMultiPolygon                               )
{

    if (this != &aMultiPolygon)
    {

        Object::operator = (aMultiPolygon) ;

        implUPtr_.reset((aMultiPolygon.implUPtr_ != nullptr) ? new MultiPolygon::Impl(*aMultiPolygon.implUPtr_) : nullptr) ;

    }

    return *this ;

}

MultiPolygon*                   MultiPolygon::clone                         ( ) const
{
    return new MultiPolygon(*this) ;
}

bool                            MultiPolygon::operator ==                   (   const   MultiPolygon&               aMultiPolygon                               ) const
{

    if ((!this->isDefined()) || (!aMultiPolygon.isDefined()))
    {
        return false ;
    }

    return (*implUPtr_) == (*aMultiPolygon.implUPtr_) ;

}

bool                            MultiPolygon::operator !=                   (   const   MultiPolygon&               aMultiPolygon                               ) const
{
    return !((*this) == aMultiPolygon) ;
}

bool                            MultiPolygon::isDefined                     ( ) const
{
    return (implUPtr_ != nullptr) && implUPtr_->isDefined() ;
}

bool                            MultiPolygon::contains                      (   const   Point&                      aPoint                                      ) const
{

    if (!aPoint.isDefined())
    {
        throw library::core::error::runtime::Undefined("Point") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Multi-polygon") ;
    }

    return implUPtr_->contains(aPoint) ;

}

bool                            MultiPolygon::contains                      (   const   PointSet&                   aPointSet                                   ) const
{

    if (!aPointSet.isDefined())
    {
        throw library::core::error::runtime::Undefined("Point set") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Multi-polygon") ;
    }

    return implUPtr_->contains(aPointSet) ;

}

Size                            MultiPolygon::getPolygonCount               ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Multi-polygon") ;
    }

    return implUPtr_->getPolygonCount() ;

}

void                            MultiPolygon::print                         (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           ) const
{

    displayDecorators ? library::core::utils::Print::Header(anOutputStream, "Multi-polygon") : void () ;

    if (implUPtr_ != nullptr)
    {

        // [TBI]

    }
    else
    {
        library::core::utils::Print::Line(anOutputStream) << "Undefined" ;
    }

    displayDecorators ? library::core::utils::Print::Footer(anOutputStream) : void () ;

}

MultiPolygon                    MultiPolygon::unionWith                     (   const   MultiPolygon&               aMultiPolygon                               ) const
{

    if (!aMultiPolygon.isDefined())
    {
        throw library::core::error::runtime::Undefined("Multi-polygon") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Multi-polygon") ;
    }

    // [TBM] Could be improved to avoid unnecessary copies

    MultiPolygon unionMultiPolygon = MultiPolygon::Undefined() ;

    unionMultiPolygon.implUPtr_ = std::make_unique<MultiPolygon::Impl>(implUPtr_->unionWith(*aMultiPolygon.implUPtr_)) ;

    return unionMultiPolygon ;

}

String                          MultiPolygon::toString                      (   const   Object::Format&             aFormat,
                                                                                const   Integer&                    aPrecision                                  ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Multi-polygon") ;
    }

    return implUPtr_->toString(aFormat, aPrecision) ;

}

void                            MultiPolygon::applyTransformation           (   const   Transformation&             aTransformation                             )
{

    if (!aTransformation.isDefined())
    {
        throw library::core::error::runtime::Undefined("Transformation") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Multi-polygon") ;
    }

    implUPtr_->applyTransformation(aTransformation) ;

}

MultiPolygon                    MultiPolygon::Undefined                     ( )
{
    return { Array<Polygon>::Empty() } ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
