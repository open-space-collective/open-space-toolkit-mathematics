////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects/Line.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Objects/Line.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects_Line (         pybind11::module&  aModule                                     )
{

    using namespace pybind11 ;

    using ostk::math::obj::Vector2d ;
    using ostk::math::geom::d2::Object ;
    using ostk::math::geom::d2::objects::Point ;
    using ostk::math::geom::d2::objects::PointSet ;
    using ostk::math::geom::d2::objects::Line ;

    class_<Line, Object>(aModule, "Line")

        .def(init<const Point&, const Vector2d&>())

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Line>))
        .def("__repr__", &(shiftToString<Line>))

        .def("is_defined", &Line::isDefined)
        .def("intersects_point", +[] (const Line& aLine, const Point& aPoint) -> bool { return aLine.intersects(aPoint) ; })
        .def("contains_point", +[] (const Line& aLine, const Point& aPoint) -> bool { return aLine.contains(aPoint) ; })
        .def("contains_point_set", +[] (const Line& aLine, const PointSet& aPointSet) -> bool { return aLine.contains(aPointSet) ; })

        .def("get_origin", &Line::getOrigin)
        .def("get_direction", &Line::getDirection)
        .def("distance_to_point", +[] (const Line& aLine, const Point& aPoint) -> bool { return aLine.distanceTo(aPoint) ; })
        .def("apply_transformation", &Line::applyTransformation)

        .def_static("undefined", &Line::Undefined)
        .def_static("points", &Line::Points)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
