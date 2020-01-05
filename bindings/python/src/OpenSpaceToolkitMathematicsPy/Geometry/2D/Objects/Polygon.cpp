////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/Polygon.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Polygon.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_Polygon_toString_overloads, ostk::math::geom::d2::objects::Polygon::toString, 0, 2)

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_Polygon ( )
{

    using namespace boost::python ;

    using ostk::core::ctnr::Array ;

    using ostk::math::obj::Vector2d ;
    using ostk::math::geom::d2::Object ;
    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::PointSet ;
    using ostk::math::geom::d2::objects::Polygon ;

    scope in_Polygon = class_<Polygon, bases<Object>>("Polygon", init<const Array<Point>&, const Array<Array<Point>>&>())

        .def(init<const Array<Point>&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &Polygon::isDefined)
        .def("intersectsPolygon", +[] (const Polygon& aPolygon, const Polygon& anotherPolygon) -> bool { return aPolygon.intersects(anotherPolygon) ; })
        .def("containsPoint", +[] (const Polygon& aPolygon, const Point& aPoint) -> bool { return aPolygon.contains(aPoint) ; })
        .def("containsPointSet", +[] (const Polygon& aPolygon, const PointSet& aPointSet) -> bool { return aPolygon.contains(aPointSet) ; })

        .def("getInnerRingCount", &Polygon::getInnerRingCount)
        .def("getEdgeCount", &Polygon::getEdgeCount)
        .def("getVertexCount", &Polygon::getVertexCount)
        .def("getOuterRing", &Polygon::getOuterRing)
        .def("getInnerRingAt", &Polygon::getInnerRingAt)
        .def("getEdgeAt", &Polygon::getEdgeAt)
        .def("getVertexAt", &Polygon::getVertexAt)
        .def("getEdges", &Polygon::getEdges)
        .def("getVertices", &Polygon::getVertices)
        .def("toString", &Polygon::toString, OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_Polygon_toString_overloads())
        // .def("unionWith", &Polygon::unionWith)
        .def("applyTransformation", &Polygon::applyTransformation)

        .def("Undefined", &Polygon::Undefined).staticmethod("Undefined")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
