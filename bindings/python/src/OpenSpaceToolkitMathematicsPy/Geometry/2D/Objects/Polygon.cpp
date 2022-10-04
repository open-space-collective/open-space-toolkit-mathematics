////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/Polygon.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Polygon.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_Polygon  (     pybind11::module&  aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::types::Integer ;
    using ostk::core::ctnr::Array ;

    using ostk::math::obj::Vector2d ;
    using ostk::math::geom::d2::Object ;
    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::PointSet ;
    using ostk::math::geom::d2::objects::Polygon ;

    class_<Polygon, Object>(aModule, "Polygon")

        .def(init<const Array<Point>&, const Array<Array<Point>>&>())

        .def(init<const Array<Point>&>())

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Polygon>))
        .def("__repr__", &(shiftToString<Polygon>))

        .def("is_defined", &Polygon::isDefined)
        .def("is_near", &Polygon::isNear)
        .def("intersects", overload_cast<const Polygon&>(&Polygon::intersects, const_))
        .def("intersects_polygon", +[] (const Polygon& aPolygon, const Polygon& anotherPolygon) -> bool { return aPolygon.intersects(anotherPolygon) ; }) // TBR
        .def("intersection_with", overload_cast<const Polygon&>(&Polygon::intersectionWith, const_))
        .def("difference_with", overload_cast<const Polygon&>(&Polygon::differenceWith, const_))
        .def("contains", overload_cast<const Point&>(&Polygon::contains, const_))
        .def("contains", overload_cast<const PointSet&>(&Polygon::contains, const_))
        .def("contains_point", +[] (const Polygon& aPolygon, const Point& aPoint) -> bool { return aPolygon.contains(aPoint) ; })
        .def("contains_point_set", +[] (const Polygon& aPolygon, const PointSet& aPointSet) -> bool { return aPolygon.contains(aPointSet) ; })

        .def("get_inner_ring_count", &Polygon::getInnerRingCount)
        .def("get_edge_count", &Polygon::getEdgeCount)
        .def("get_vertex_count", &Polygon::getVertexCount)
        .def("get_outer_ring", &Polygon::getOuterRing)
        .def("get_inner_ring_at", &Polygon::getInnerRingAt)
        .def("get_edge_at", &Polygon::getEdgeAt)
        .def("get_vertex_at", &Polygon::getVertexAt)
        .def("get_edges", &Polygon::getEdges)
        .def("get_vertices", &Polygon::getVertices)
        .def("get_convex_hull", &Polygon::getConvexHull)
        .def("union_with", &Polygon::unionWith)
        .def("to_string", &Polygon::toString, "aFormat"_a=Object::Format::Standard, "aPrecision"_a=Integer::Undefined())
        .def("apply_transformation", &Polygon::applyTransformation)

        .def_static("undefined", &Polygon::Undefined)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
