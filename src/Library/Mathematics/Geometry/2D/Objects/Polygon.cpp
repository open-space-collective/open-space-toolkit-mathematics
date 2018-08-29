////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           Library/Mathematics/Geometry/2D/Objects/Polygon.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/2D/Objects/Polygon.hpp>

#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Size.hpp>
#include <Library/Core/Types/Index.hpp>
#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <boost/geometry/io/wkt/wkt.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry.hpp>

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

using boost::geometry::model::point ;
using boost::geometry::model::polygon ;
using boost::geometry::model::ring ;
using boost::geometry::cs::cartesian ;

using library::core::types::Index ;
using library::core::types::Size ;
using library::core::types::String ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Polygon::Impl
{

    public:

                                Impl                                        (   const   Array<Point>&               anOuterRing,
                                                                                const   Array<Array<Point>>&        anInnerRingArray                            ) ;

                                ~Impl                                       ( ) = default ;

        bool                    operator ==                                 (   const   Polygon::Impl&              aPolygon                                    ) const ;

        bool                    isDefined                                   ( ) const ;

        Size                    getInnerRingCount                           ( ) const ;

        Array<Point>            getOuterRingVertices                        ( ) const ;

        Array<Point>            getInnerRingVerticesAt                      (   const   Index&                      aRingIndex                                  ) const ;
        
        Array<Point>            getVertices                                 ( ) const ;

        String                  toString                                    (   const   Object::Format&             aFormat,
                                                                                const   Integer&                    aPrecision                                  ) const ;
        
        void                    translate                                   (   const   Vector2d&                   aTranslation                                ) ;

    private:

        typedef                 point<double, 2, cartesian>                     BoostPoint ;
        typedef                 ring<Impl::BoostPoint>                          BoostRing ;
        typedef                 polygon<Impl::BoostPoint>                       BoostPolygon ;

        Impl::BoostPolygon      polygon_ ;

        static Impl::BoostPolygon BoostPolygonFromPoints                    (   const   Array<Point>&               aPointArray                                 ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Polygon::Impl::Impl                         (   const   Array<Point>&               anOuterRing,
                                                                                const   Array<Array<Point>>&        anInnerRingArray                            )
                                :   polygon_(Polygon::Impl::BoostPolygonFromPoints(anOuterRing))
{

    for (const auto& innerRing : anInnerRingArray) // [TBM] This is temporary, should construct inline instead
    {

        Polygon::Impl::BoostRing ring ;

        for (const auto& innerRingPoint : innerRing)
        {
            boost::geometry::append(ring, Polygon::Impl::BoostPoint(innerRingPoint.x(), innerRingPoint.y())) ;
        }

        polygon_.inners().push_back(ring) ;

    }

}

bool                            Polygon::Impl::operator ==                  (   const   Polygon::Impl&              aPolygon                                    ) const
{
    return boost::geometry::equals(polygon_, aPolygon.polygon_) ;
}

bool                            Polygon::Impl::isDefined                    ( ) const
{
    return polygon_.outer().size() >= 3 ;
}

Size                            Polygon::Impl::getInnerRingCount            ( ) const
{
    return polygon_.inners().size() ;
}

Array<Point>                    Polygon::Impl::getOuterRingVertices         ( ) const
{

    if (polygon_.outer().size() == 0)
    {
        return Array<Point>::Empty() ;
    }

    Array<Point> outerRingVertices = Array<Point>::Empty() ;

    for (size_t vertexIdx = 0; vertexIdx < (polygon_.outer().size() - 1); ++vertexIdx)
    {
        outerRingVertices.add(Point(boost::geometry::get<0>(polygon_.outer().at(vertexIdx)), boost::geometry::get<1>(polygon_.outer().at(vertexIdx)))) ;
    }

    return outerRingVertices ;

}

Array<Point>                    Polygon::Impl::getInnerRingVerticesAt       (   const   Index&                      aRingIndex                                  ) const
{

    if (aRingIndex >= this->getInnerRingCount())
    {
        throw library::core::error::RuntimeError("Inner ring index [{}] out of bounds [{}].", aRingIndex, this->getInnerRingCount()) ;
    }

    if (polygon_.inners().at(aRingIndex).size() == 0)
    {
        return Array<Point>::Empty() ;
    }

    Array<Point> innerRingVertices = Array<Point>::Empty() ;

    for (size_t vertexIdx = 0; vertexIdx < (polygon_.inners().at(aRingIndex).size() - 1); ++vertexIdx)
    {
        innerRingVertices.add(Point(boost::geometry::get<0>(polygon_.inners().at(aRingIndex).at(vertexIdx)), boost::geometry::get<1>(polygon_.inners().at(aRingIndex).at(vertexIdx)))) ;
    }

    return innerRingVertices ;

}

Array<Point>                    Polygon::Impl::getVertices                  ( ) const
{

    Array<Point> vertices = Array<Point>::Empty() ;

    for (const auto& vertex : this->getOuterRingVertices())
    {
        vertices.add(vertex) ;
    }

    for (Index innerRingIndex = 0; innerRingIndex < this->getInnerRingCount(); ++innerRingIndex) 
    {
        for (const auto& vertex : this->getInnerRingVerticesAt(innerRingIndex))
        {
            vertices.add(vertex) ;
        }
    }

    return vertices ;

}

String                          Polygon::Impl::toString                     (   const   Object::Format&             aFormat,
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
                stringStream << std::fixed << std::setprecision(aPrecision) << boost::geometry::wkt(polygon_) ;
            }
            else
            {
                stringStream << boost::geometry::wkt(polygon_) ;
            }

            return stringStream.str() ;

        }

        default:
            throw library::core::error::runtime::Wrong("Format") ;
            break ;

    }

    return String::Empty() ;

}

void                            Polygon::Impl::translate                    (   const   Vector2d&                   aTranslation                                )
{

    Polygon::Impl::BoostPolygon transformedPolygon ;

    boost::geometry::strategy::transform::translate_transformer<double, 2, 2> translate(aTranslation.x(), aTranslation.y()) ;
    
    boost::geometry::transform(polygon_, transformedPolygon, translate) ;

    polygon_ = transformedPolygon ;

}

Polygon::Impl::BoostPolygon     Polygon::Impl::BoostPolygonFromPoints       (   const   Array<Point>&               aPointArray                                 )
{

    Polygon::Impl::BoostPolygon polygon ;

    for (const auto& point : aPointArray)
    {
        boost::geometry::append(polygon, Polygon::Impl::BoostPoint(point(0), point(1))) ;
    }

    boost::geometry::correct(polygon) ;

    return polygon ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Polygon::Polygon                            (   const   Array<Point>&               anOuterRing,
                                                                                const   Array<Array<Point>>&        anInnerRingArray                            )
                                :   Object(),
                                    implUPtr_(std::make_unique<Polygon::Impl>(anOuterRing, anInnerRingArray))
{
    
}

                                Polygon::Polygon                            (   const   Polygon&                    aPolygon                                    )
                                :   Object(aPolygon),
                                    implUPtr_((aPolygon.implUPtr_ != nullptr) ? new Polygon::Impl(*aPolygon.implUPtr_) : nullptr)
{

}

                                Polygon::~Polygon                           ( )
{

}

Polygon&                        Polygon::operator =                         (   const   Polygon&                    aPolygon                                    )
{

    if (this != &aPolygon)
    {

        Object::operator = (aPolygon) ;
        
        implUPtr_.reset((aPolygon.implUPtr_ != nullptr) ? new Polygon::Impl(*aPolygon.implUPtr_) : nullptr) ;

    }

    return *this ;

}

Polygon*                        Polygon::clone                              ( ) const
{
    return new Polygon(*this) ;
}

bool                            Polygon::operator ==                        (   const   Polygon&                    aPolygon                                    ) const
{

    if ((!this->isDefined()) && (!aPolygon.isDefined()))
    {
        return false ;
    }

    return (*implUPtr_) == (*aPolygon.implUPtr_) ;

}

bool                            Polygon::operator !=                        (   const   Polygon&                    aPolygon                                    ) const
{
    return !((*this) == aPolygon) ;
}

bool                            Polygon::isDefined                          ( ) const
{
    return (implUPtr_ != nullptr) && implUPtr_->isDefined() ;
}

Array<Point>                    Polygon::getVertices                        ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Polygon") ;
    }

    return implUPtr_->getVertices() ;

}

void                            Polygon::print                              (           std::ostream&               anOutputStream,
                                                                                        bool                        displayDecorators                           ) const
{

    displayDecorators ? library::core::utils::Print::Header(anOutputStream, "Polygon") : void () ;

    library::core::utils::Print::Separator(anOutputStream, "Outer Ring") ;

    if (implUPtr_ != nullptr)
    {

        for (const auto& point : implUPtr_->getOuterRingVertices())
        {
            library::core::utils::Print::Line(anOutputStream) << String::Format("- {}", point.toString()) ;
        }

    }
    else
    {
        library::core::utils::Print::Line(anOutputStream) << "Undefined" ;
    }
    
    library::core::utils::Print::Separator(anOutputStream, "Inner Rings") ;

    if (implUPtr_ != nullptr)
    {

        for (Index innerRingIndex = 0; innerRingIndex < implUPtr_->getInnerRingCount(); ++innerRingIndex)
        {

            library::core::utils::Print::Separator(anOutputStream, String::Format("Inner Ring @ {}", innerRingIndex)) ;

            for (const auto& point : implUPtr_->getInnerRingVerticesAt(innerRingIndex))
            {
                library::core::utils::Print::Line(anOutputStream) << String::Format("- {}", point.toString()) ;
            }

        }

    }
    else
    {
        library::core::utils::Print::Line(anOutputStream) << "Undefined" ;
    }

    displayDecorators ? library::core::utils::Print::Footer(anOutputStream) : void () ;

}

String                          Polygon::toString                           (   const   Object::Format&             aFormat,
                                                                                const   Integer&                    aPrecision                                  ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Polygon") ;
    }

    return implUPtr_->toString(aFormat, aPrecision) ;

}

void                            Polygon::translate                          (   const   Vector2d&                   aTranslation                                )
{

    if (!aTranslation.isDefined())
    {
        throw library::core::error::runtime::Undefined("Translation") ;
    }

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("Polygon") ;
    }

    implUPtr_->translate(aTranslation) ;

}

Polygon                         Polygon::Undefined                          ( )
{
    return { Array<Point>::Empty() } ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////