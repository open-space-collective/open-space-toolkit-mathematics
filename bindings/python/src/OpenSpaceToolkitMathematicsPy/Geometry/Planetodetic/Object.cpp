/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/Planetodetic/Object.hpp>

#include <OpenSpaceToolkitMathematicsPy/Geometry/Planetodetic/Object/Point.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/Planetodetic/Object/Polygon.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/Planetodetic/Object/Spheroid.cpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_Planetodetic_Object(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::mathematics::geometry::planetodetic::Object;

    class_<Object> ob(aModule, "Object");

    ob

        .def(
            "__eq__",
            [](const Object& self, const Object& other)
            {
                return self == other;
            },
            R"doc(
                Check if two planetodetic objects are equal.

                Args:
                    other (Object): The object to compare with.

                Returns:
                    bool: True if objects are equal, False otherwise.

                Example:
                    >>> point1 = Point(Angle.degrees(45.0), Angle.degrees(-122.0))
                    >>> point2 = Point(Angle.degrees(45.0), Angle.degrees(-122.0))
                    >>> point1 == point2  # True
            )doc"
        )
        .def(
            "__ne__",
            [](const Object& self, const Object& other)
            {
                return self != other;
            },
            R"doc(
                Check if two planetodetic objects are not equal.

                Args:
                    other (Object): The object to compare with.

                Returns:
                    bool: True if objects are not equal, False otherwise.

                Example:
                    >>> point1 = Point(Angle.degrees(45.0), Angle.degrees(-122.0))
                    >>> point2 = Point(Angle.degrees(30.0), Angle.degrees(100.0))
                    >>> point1 != point2  # True
            )doc"
        )

        .def("__str__", &(shiftToString<Object>))
        .def("__repr__", &(shiftToString<Object>))

        .def(
            "is_defined",
            &Object::isDefined,
            R"doc(
                Check if the planetodetic object is defined.

                Returns:
                    bool: True if the object is defined, False otherwise.

                Example:
                    >>> point = Point(Angle.degrees(45.0), Angle.degrees(-122.0))
                    >>> point.is_defined()  # True
            )doc"
        )
        .def(
            "intersects",
            &Object::intersects,
            R"doc(
                Check if this planetodetic object intersects with another object.

                Args:
                    object (Object): The object to check intersection with.

                Returns:
                    bool: True if objects intersect, False otherwise.

                Example:
                    >>> spheroid = Spheroid.sphere(6378137.0)
                    >>> polygon = Polygon.simple(spheroid, [
                    ...     Point(Angle.degrees(-10.0), Angle.degrees(-10.0)),
                    ...     Point(Angle.degrees(-10.0), Angle.degrees(10.0)),
                    ...     Point(Angle.degrees(10.0), Angle.degrees(10.0))
                    ... ])
                    >>> point = Point(Angle.degrees(0.0), Angle.degrees(0.0))
                    >>> polygon.intersects(point)  # True
            )doc",
            arg("object")
        )
        .def(
            "contains",
            &Object::contains,
            R"doc(
                Check if this planetodetic object contains another object.

                Args:
                    object (Object): The object to check containment for.

                Returns:
                    bool: True if this object contains the other, False otherwise.

                Example:
                    >>> spheroid = Spheroid.sphere(6378137.0)
                    >>> polygon = Polygon.simple(spheroid, [
                    ...     Point(Angle.degrees(-10.0), Angle.degrees(-10.0)),
                    ...     Point(Angle.degrees(-10.0), Angle.degrees(10.0)),
                    ...     Point(Angle.degrees(10.0), Angle.degrees(10.0)),
                    ...     Point(Angle.degrees(10.0), Angle.degrees(-10.0))
                    ... ])
                    >>> point = Point(Angle.degrees(0.0), Angle.degrees(0.0))
                    >>> polygon.contains(point)  # True
            )doc",
            arg("object")
        )

        ;

    enum_<Object::Format>(ob, "Format")

        .value("Undefined", Object::Format::Undefined)
        .value("Standard", Object::Format::Standard)

        ;

    // Create "object" python submodule
    auto object = aModule.def_submodule("object");

    // Add object to python "object" submodules
    OpenSpaceToolkitMathematicsPy_Geometry_Planetodetic_Object_Point(object);
    OpenSpaceToolkitMathematicsPy_Geometry_Planetodetic_Object_Spheroid(object);
    OpenSpaceToolkitMathematicsPy_Geometry_Planetodetic_Object_Polygon(object);
}
