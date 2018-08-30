////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           LibraryMathematicsPy/Geometry/3D/Objects/Line.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Objects/Line.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_3D_Objects_Line ( )
{

    using namespace boost::python ;

    using library::math::obj::Vector3d ;
    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Line ;
    using library::math::geom::d3::objects::Ellipsoid ;

    scope in_Line = class_<Line, bases<Object>>("Line", init<const Point&, const Vector3d&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &Line::isDefined)
        .def("intersectsPoint", +[] (const Line& aLine, const Point& aPoint) -> bool { return aLine.intersects(aPoint) ; })
        .def("intersectsEllipsoid", +[] (const Line& aLine, const Ellipsoid& anEllipsoid) -> bool { return aLine.intersects(anEllipsoid) ; })
        .def("containsPoint", +[] (const Line& aLine, const Point& aPoint) -> bool { return aLine.contains(aPoint) ; })

        .def("getOrigin", &Line::getOrigin)
        .def("getDirection", &Line::getDirection)
        .def("translate", &Line::translate)
        .def("rotate", &Line::rotate)
        
        .def("Undefined", &Line::Undefined).staticmethod("Undefined")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////