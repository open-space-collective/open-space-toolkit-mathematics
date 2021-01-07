////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/2D/Object.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Types/Integer.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// The following trampolin function might be used if the virtual functions defined in C++ are to be overriden in Python
// Probably not needed for now. To be included if writing python extension classes

// using ostk::math::geom::d2::Object ;
// using ostk::math::geom::d2::Transformation ;
// using ostk::core::types::String ;
// using ostk::core::types::Integer ;

// // Not to be confused with PyObject Python C API class used to represent any python object in C++
// class PyObject2D : public Object {
// public:
//     /* Inherit the constructors */
//     using ostk::math::geom::d2::Object::Object;

//     /* Trampoline (need one for each virtual function) */
//     virtual Object* clone() const override {
//         PYBIND11_OVERRIDE_PURE(
//             Object*,        /* Return type */
//             Object,         /* Parent class */
//             clone,          /* Name of function in C++ (must match Python name) */
//                             /* Argument(s) */
//         );
//     }

//     virtual bool isDefined() const override {
//         PYBIND11_OVERRIDE_PURE(
//             bool,              /* Return type */
//             Object,            /* Parent class */
//             isDefined,          /* Name of function in C++ (must match Python name) */
//                                /* Argument(s) */
//         );
//     }

//     virtual String toString (   const   Object::Format&             aFormat
//                                                                                 const   Integer&                    aPrecision                                  ) const override {
//         PYBIND11_OVERRIDE_PURE(
//             String,             /* Return type */
//             Object,             /* Parent class */
//             toString,            /* Name of function in C++ (must match Python name) */
//             aFormat,
//             aPrecision,                    /* Argument(s) */
//         );
//     }

//     virtual void print                                            (           std::ostream&               anOutputStream,
//                                                                                         bool                        displayDecorators) const override {
//         PYBIND11_OVERRIDE_PURE(
//             void,             /* Return type */
//             Object,             /* Parent class */
//             print,            /* Name of function in C++ (must match Python name) */
//             anOutputStream,
//             displayDecorators,   /* Argument(s) */
//         );
//     }

//     virtual void            applyTransformation                         (   const   Transformation&             aTransformation                             ) override {
//         PYBIND11_OVERRIDE_PURE(
//             void,               /* Return type */
//             Object,             /* Parent class */
//             applyTransformation,            /* Name of function in C++ (must match Python name) */
//             aTransformation,     /* Argument(s) */
//         );
//     }
// };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_2D_Object                     (              pybind11::module&    aModule               )
{

    using namespace pybind11 ;

    using ostk::math::geom::d2::Object ;

    // noncopyable class with Boost, removed in Pybind11
    class_<Object> ob(aModule, "Object");

    ob.def("__eq__", [](const Object &self, const Object &other){ return self == other; })
        .def("__ne__", [](const Object &self, const Object &other){ return self != other; })
        // Equivalent to ...
        // ob.def(self == self)
        //   .def(self != self) ;

        .def("__str__", &(shift_to_string<Object>))
        .def("__repr__", &(shift_to_string<Object>))
        // Equivalent to ...
        // .def(self_ns::str(self_ns::self))
        // .def(self_ns::repr(self_ns::self))

        .def("is_defined", &Object::isDefined)
        .def("intersects", &Object::intersects)
        .def("contains", &Object::contains)

        // .def("to_string", &Object::toString)
        .def("apply_transformation", &Object::applyTransformation)

    ;

    enum_<Object::Format>(ob, "Format")

        .value("Undefined", Object::Format::Undefined)
        .value("Standard", Object::Format::Standard)
        .value("WKT", Object::Format::WKT)
        .export_values()

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
