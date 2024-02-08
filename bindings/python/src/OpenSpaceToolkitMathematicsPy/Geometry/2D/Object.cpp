/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object.hpp>

#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Object/Composite.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Object/Line.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Object/LineString.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Object/MultiPolygon.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Object/Point.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Object/PointSet.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Object/Polygon.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Object/Segment.cpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_2D_Object(pybind11::module &aModule)
{
    using namespace pybind11;

    using ostk::mathematics::geometry::d2::Object;

    class_<Object> ob(aModule, "Object");

    ob

        .def(
            "__eq__",
            [](const Object &self, const Object &other)
            {
                return self == other;
            }
        )
        .def(
            "__ne__",
            [](const Object &self, const Object &other)
            {
                return self != other;
            }
        )

        .def("__str__", &(shiftToString<Object>))
        .def("__repr__", &(shiftToString<Object>))

        .def("is_defined", &Object::isDefined)
        .def("intersects", &Object::intersects, arg("object"))
        .def("contains", &Object::contains, arg("object"))

        // .def("to_string", &Object::toString)
        .def("apply_transformation", &Object::applyTransformation, arg("transformation"))

        ;

    enum_<Object::Format>(ob, "Format")

        .value("Undefined", Object::Format::Undefined)
        .value("Standard", Object::Format::Standard)
        .value("WKT", Object::Format::WKT)

        ;

    // Create "object" python submodule
    auto object = aModule.def_submodule("object");

    // Add __path__ attribute for "object" submodule
    object.attr("__path__") = "ostk.mathematics.geometry.d2.object";

    // Add object to python "object" submodules
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Object_Point(object);
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Object_PointSet(object);
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Object_Line(object);
    // OpenSpaceToolkitMathematicsPy_Geometry_2D_Object_Ray(object) ;
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Object_Segment(object);
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Object_LineString(object);
    // OpenSpaceToolkitMathematicsPy_Geometry_2D_Object_MultiLineString(object) ;
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Object_Polygon(object);
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Object_MultiPolygon(object);
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Object_Composite(object);
}
