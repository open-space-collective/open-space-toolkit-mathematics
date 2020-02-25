////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/MultiPolygon.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/MultiPolygon.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_MultiPolygon_toString_overloads, ostk::math::geom::d2::objects::MultiPolygon::toString, 0, 2)

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_MultiPolygon ( )
{

    using namespace boost::python ;

    using ostk::core::ctnr::Array ;

    using ostk::math::obj::Vector2d ;
    using ostk::math::geom::d2::Object ;
    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::PointSet ;
    using ostk::math::geom::d2::objects::Polygon ;
    using ostk::math::geom::d2::objects::MultiPolygon ;

    scope in_MultiPolygon = class_<MultiPolygon, bases<Object>>("MultiPolygon", init<const Array<Polygon>&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("is_defined", &MultiPolygon::isDefined)
        .def("contains_point", +[] (const MultiPolygon& aMultiPolygon, const Point& aPoint) -> bool { return aMultiPolygon.contains(aPoint) ; })
        .def("contains_point_set", +[] (const MultiPolygon& aMultiPolygon, const PointSet& aPointSet) -> bool { return aMultiPolygon.contains(aPointSet) ; })

        .def("get_polygon_count", &MultiPolygon::getPolygonCount)
        .def("get_polygons", &MultiPolygon::getPolygons)
        .def("get_convex_hull", &MultiPolygon::getConvexHull)
        .def("union_with", &MultiPolygon::unionWith)
        .def("to_string", &MultiPolygon::toString, OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_MultiPolygon_toString_overloads())
        .def("apply_transformation", &MultiPolygon::applyTransformation)

        .def("undefined", &MultiPolygon::Undefined).staticmethod("undefined")
        .def("polygon", &MultiPolygon::Polygon).staticmethod("polygon")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
