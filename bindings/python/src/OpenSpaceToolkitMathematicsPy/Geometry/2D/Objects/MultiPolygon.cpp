////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/MultiPolygon.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/MultiPolygon.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_MultiPolygon  ( pybind11::module& aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::types::Integer ;
    using ostk::core::ctnr::Array ;

    using ostk::math::obj::Vector2d ;
    using ostk::math::geom::d2::Object ;
    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::PointSet ;
    using ostk::math::geom::d2::objects::Polygon ;
    using ostk::math::geom::d2::objects::MultiPolygon ;

    class_<MultiPolygon, Object>(aModule, "MultiPolygon")

        .def(init<const Array<Polygon>&>())

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<MultiPolygon>))
        .def("__repr__", &(shiftToString<MultiPolygon>))

        .def("is_defined", &MultiPolygon::isDefined)
        .def("contains_point", +[] (const MultiPolygon& aMultiPolygon, const Point& aPoint) -> bool { return aMultiPolygon.contains(aPoint) ; })
        .def("contains_point_set", +[] (const MultiPolygon& aMultiPolygon, const PointSet& aPointSet) -> bool { return aMultiPolygon.contains(aPointSet) ; })

        .def("get_polygon_count", &MultiPolygon::getPolygonCount)
        .def("get_polygons", &MultiPolygon::getPolygons)
        .def("get_convex_hull", &MultiPolygon::getConvexHull)
        .def("union_with", &MultiPolygon::unionWith)
        // .def("to_string", &MultiPolygon::toString, OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_MultiPolygon_toString_overloads())
        .def("to_string", &MultiPolygon::toString, "aFormat"_a=Object::Format::Standard, "aPrecision"_a=Integer::Undefined())
        .def("apply_transformation", &MultiPolygon::applyTransformation)

        .def_static("undefined", &MultiPolygon::Undefined)
        .def_static("polygon", &MultiPolygon::Polygon)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
