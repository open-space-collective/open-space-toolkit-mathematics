////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           LibraryMathematicsPy/Geometry/Angle.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/Angle.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_Angle         ( )
{

    using namespace boost::python ;

    using library::core::types::Real ;
    using library::core::types::String ;
    
    using library::math::geom::Angle ;

    scope in_Angle = class_<Angle>("Angle", init<Real, Angle::Unit>())

        .def(self == self)
        .def(self != self)

        .def(self + self)
        .def(self - self)
        .def(self * double())
        .def(self / double())

		// +=
        // -=
        // *=
        // /=

        .def(self_ns::str(self_ns::self))

        .def("isDefined", &Angle::isDefined)
        .def("isZero", &Angle::isZero)
        
        .def("getUnit", &Angle::getUnit)
        .def("in", &Angle::in)
        .def("inRadians", +[] (const Angle& anAngle) -> Real { return anAngle.inRadians() ; })
        .def("inDegrees", +[] (const Angle& anAngle) -> Real { return anAngle.inDegrees() ; })
        .def("inArcminutes", +[] (const Angle& anAngle) -> Real { return anAngle.inArcminutes() ; })
        .def("inArcseconds", +[] (const Angle& anAngle) -> Real { return anAngle.inArcseconds() ; })
        .def("inRevolutions", &Angle::inRevolutions)
        .def("toString", &Angle::toString)
        
        .def("Undefined", &Angle::Undefined).staticmethod("Undefined")
        .def("Zero", &Angle::Zero).staticmethod("Zero")
        .def("Radians", &Angle::Radians).staticmethod("Radians")
        .def("Degrees", &Angle::Degrees).staticmethod("Degrees")
        .def("Arcminutes", &Angle::Arcminutes).staticmethod("Arcminutes")
        .def("Arcseconds", &Angle::Arcseconds).staticmethod("Arcseconds")
        .def("Revolutions", &Angle::Revolutions).staticmethod("Revolutions")
        // .def("Parse", &Angle::Parse).staticmethod("Parse")
        .def("StringFromUnit", &Angle::StringFromUnit).staticmethod("StringFromUnit")
        .def("SymbolFromUnit", &Angle::SymbolFromUnit).staticmethod("SymbolFromUnit")

    ;

    enum_<Angle::Unit>("Unit")
    
        .value("Undefined", Angle::Unit::Undefined)
        .value("Radian", Angle::Unit::Radian)
        .value("Degree", Angle::Unit::Degree)
        .value("Arcminute", Angle::Unit::Arcminute)
        .value("Arcsecond", Angle::Unit::Arcsecond)
        .value("Revolution", Angle::Unit::Revolution)
    
    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////