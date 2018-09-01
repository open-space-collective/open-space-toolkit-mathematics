////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Mathematics
/// @file           LibraryMathematicsPy/Geometry/2D/Transformation.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Mathematics/Geometry/2D/Transformation.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryMathematicsPy_Geometry_2D_Transformation ( )
{

    using namespace boost::python ;

    using library::math::obj::Vector2d ;
    using library::math::obj::Matrix3d ;
    using library::math::geom::d2::objects::Point ;
    using library::math::geom::d2::Transformation ;

    scope in_Transformation = class_<Transformation>("Transformation", init<const Matrix3d&>())

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))
        
        .def("isDefined", &Transformation::isDefined)

        .def("getType", &Transformation::getType)
        .def("getMatrix", &Transformation::getMatrix)
        .def("getInverse", &Transformation::getInverse)
        .def("applyToPoint", + [] (const Transformation& aTransformation, const Point& aPoint) -> Point { return aTransformation.applyTo(aPoint) ; })
        .def("applyToVector", + [] (const Transformation& aTransformation, const Vector2d& aVector) -> Vector2d { return aTransformation.applyTo(aVector) ; })
        
        .def("Undefined", &Transformation::Undefined).staticmethod("Undefined")
        .def("Identity", &Transformation::Identity).staticmethod("Identity")
        .def("Translation", &Transformation::Translation).staticmethod("Translation")
        .def("Rotation", &Transformation::Rotation).staticmethod("Rotation")
        
        .def("StringFromType", &Transformation::StringFromType).staticmethod("StringFromType")
        .def("TypeOfMatrix", &Transformation::TypeOfMatrix).staticmethod("TypeOfMatrix")

    ;

    enum_<Transformation::Type>("Type")
    
        .value("Undefined", Transformation::Type::Undefined)
        .value("Identity", Transformation::Type::Identity)
        .value("Translation", Transformation::Type::Translation)
        .value("Rotation", Transformation::Type::Rotation)
    
    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////