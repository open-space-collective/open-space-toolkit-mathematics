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
            },
            R"doc(
                Check if two 2D objects are equal.

                Args:
                    other (Object): The object to compare with.

                Returns:
                    bool: True if objects are equal, False otherwise.

                Example:
                    >>> point1 = Point(1.0, 2.0)
                    >>> point2 = Point(1.0, 2.0)
                    >>> point1 == point2  # True
            )doc"
        )
        .def(
            "__ne__",
            [](const Object &self, const Object &other)
            {
                return self != other;
            },
            R"doc(
                Check if two 2D objects are not equal.

                Args:
                    other (Object): The object to compare with.

                Returns:
                    bool: True if objects are not equal, False otherwise.

                Example:
                    >>> point1 = Point(1.0, 2.0)
                    >>> point2 = Point(3.0, 4.0)
                    >>> point1 != point2  # True
            )doc"
        )

        .def("__str__", &(shiftToString<Object>))
        .def("__repr__", &(shiftToString<Object>))

        .def(
            "is_defined",
            &Object::isDefined,
            R"doc(
                Check if the 2D object is defined.

                Returns:
                    bool: True if the object is defined, False otherwise.

                Example:
                    >>> point = Point(1.0, 2.0)
                    >>> point.is_defined()  # True
            )doc"
        )
        .def(
            "intersects",
            &Object::intersects,
            R"doc(
                Check if this 2D object intersects with another object.

                Args:
                    object (Object): The object to check intersection with.

                Returns:
                    bool: True if objects intersect, False otherwise.

                Example:
                    >>> line1 = Line(Point(0.0, 0.0), np.array([1.0, 0.0]))
                    >>> line2 = Line(Point(0.0, -1.0), np.array([0.0, 1.0]))
                    >>> line1.intersects(line2)  # True
            )doc",
            arg("object")
        )
        .def(
            "contains",
            &Object::contains,
            R"doc(
                Check if this 2D object contains another object.

                Args:
                    object (Object): The object to check containment for.

                Returns:
                    bool: True if this object contains the other, False otherwise.

                Example:
                    >>> polygon = Polygon([Point(0.0, 0.0), Point(2.0, 0.0), Point(2.0, 2.0)])
                    >>> point = Point(1.0, 1.0)
                    >>> polygon.contains(point)  # True
            )doc",
            arg("object")
        )

        // .def("to_string", &Object::toString)
        .def(
            "apply_transformation",
            &Object::applyTransformation,
            R"doc(
                Apply a transformation to the 2D object in place.

                Args:
                    transformation (Transformation): The 2D transformation to apply.

                Example:
                    >>> point = Point(1.0, 2.0)
                    >>> transformation = Translation([1.0, 1.0])
                    >>> point.apply_transformation(transformation)
            )doc",
            arg("transformation")
        )

        ;

    enum_<Object::Format>(ob, "Format")

        .value("Undefined", Object::Format::Undefined)
        .value("Standard", Object::Format::Standard)
        .value("WKT", Object::Format::WKT)

        ;

    // Create "object" python submodule
    auto object = aModule.def_submodule("object");

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
