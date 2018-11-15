////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           LibraryMathematicsPy/Geometry/3D/Objects/Segment.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/3D/Objects/Segment.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_3D_Objects_Segment ( )
{

    using namespace boost::python ;

    using library::math::geom::d3::Object ;
    using library::math::geom::d3::objects::Point ;
    using library::math::geom::d3::objects::Segment ;
    using library::math::geom::d3::objects::Sphere ;
    using library::math::geom::d3::objects::Ellipsoid ;

    scope in_Segment = class_<Segment, bases<Object>>("Segment", init<const Point&, const Point&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &Segment::isDefined)
        .def("isDegenerate", &Segment::isDegenerate)
        .def("intersectsSphere", +[] (const Segment& aSegment, const Sphere& aSphere) -> bool { return aSegment.intersects(aSphere) ; })
        .def("intersectsEllipsoid", +[] (const Segment& aSegment, const Ellipsoid& anEllipsoid) -> bool { return aSegment.intersects(anEllipsoid) ; })
        .def("containsPoint", +[] (const Segment& aSegment, const Point& aPoint) -> bool { return aSegment.contains(aPoint) ; })

        .def("getFirstPoint", &Segment::getFirstPoint)
        .def("getSecondPoint", &Segment::getSecondPoint)
        .def("getCenter", &Segment::getCenter)
        .def("getDirection", &Segment::getDirection)
        .def("getLength", &Segment::getLength)
        .def("applyTransformation", &Segment::applyTransformation)
        
        .def("Undefined", &Segment::Undefined).staticmethod("Undefined")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////