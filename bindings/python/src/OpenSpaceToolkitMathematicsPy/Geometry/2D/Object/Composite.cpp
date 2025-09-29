/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Type/Shared.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Composite.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_2D_Object_Composite(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;
    using ostk::core::type::Shared;

    using ostk::mathematics::geometry::d2::Intersection;
    using ostk::mathematics::geometry::d2::Object;
    using ostk::mathematics::geometry::d2::object::Composite;
    using ostk::mathematics::geometry::d2::object::Line;
    using ostk::mathematics::geometry::d2::object::LineString;
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::PointSet;
    using ostk::mathematics::geometry::d2::object::Polygon;
    using ostk::mathematics::geometry::d2::object::Segment;

    class_<Composite, Object>(aModule, "Composite")

        .def(
            init<const Object&>(),
            R"doc(
                Create a 2D composite object from a single geometric object.

                Args:
                    object (Object): The 2D geometric object to wrap in the composite.

                Example:
                    >>> point = Point(1.0, 2.0)
                    >>> composite = Composite(point)
            )doc",
            arg("object")
        )

        .def(self == self)
        .def(self != self)

        .def(self + self)
        .def(self += self)

        .def("__str__", &(shiftToString<Composite>))
        .def("__repr__", &(shiftToString<Composite>))

        .def(
            "is_defined",
            &Composite::isDefined,
            R"doc(
                Check if the 2D composite is defined.

                Returns:
                    bool: True if the composite is defined, False otherwise.

                Example:
                    >>> composite = Composite(Point(1.0, 2.0))
                    >>> composite.is_defined()  # True
            )doc"
        )
        .def(
            "is_empty",
            &Composite::isEmpty,
            R"doc(
                Check if the 2D composite is empty (contains no objects).

                Returns:
                    bool: True if the composite is empty, False otherwise.

                Example:
                    >>> empty_composite = Composite.empty()
                    >>> empty_composite.is_empty()  # True
            )doc"
        )

        .def(
            "is_point",
            +[](const Composite& aComposite) -> bool
            {
                return aComposite.is<Point>();
            },
            R"doc(
                Check if the composite contains a 2D Point object.

                Returns:
                    bool: True if the composite contains a Point, False otherwise.

                Example:
                    >>> composite = Composite(Point(1.0, 2.0))
                    >>> composite.is_point()  # True
            )doc"
        )
        .def(
            "is_point_set",
            +[](const Composite& aComposite) -> bool
            {
                return aComposite.is<PointSet>();
            },
            R"doc(
                Check if the composite contains a 2D PointSet object.

                Returns:
                    bool: True if the composite contains a PointSet, False otherwise.

                Example:
                    >>> point_set = PointSet([Point(1.0, 2.0), Point(3.0, 4.0)])
                    >>> composite = Composite(point_set)
                    >>> composite.is_point_set()  # True
            )doc"
        )
        .def(
            "is_line",
            +[](const Composite& aComposite) -> bool
            {
                return aComposite.is<Line>();
            },
            R"doc(
                Check if the composite contains a 2D Line object.

                Returns:
                    bool: True if the composite contains a Line, False otherwise.

                Example:
                    >>> line = Line(Point(0.0, 0.0), np.array([1.0, 1.0]))
                    >>> composite = Composite(line)
                    >>> composite.is_line()  # True
            )doc"
        )
        .def(
            "is_segment",
            +[](const Composite& aComposite) -> bool
            {
                return aComposite.is<Segment>();
            },
            R"doc(
                Check if the composite contains a 2D Segment object.

                Returns:
                    bool: True if the composite contains a Segment, False otherwise.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0), Point(1.0, 1.0))
                    >>> composite = Composite(segment)
                    >>> composite.is_segment()  # True
            )doc"
        )
        .def(
            "is_line_string",
            +[](const Composite& aComposite) -> bool
            {
                return aComposite.is<LineString>();
            },
            R"doc(
                Check if the composite contains a 2D LineString object.

                Returns:
                    bool: True if the composite contains a LineString, False otherwise.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0), Point(2.0, 2.0)]
                    >>> line_string = LineString(points)
                    >>> composite = Composite(line_string)
                    >>> composite.is_line_string()  # True
            )doc"
        )
        .def(
            "is_polygon",
            +[](const Composite& aComposite) -> bool
            {
                return aComposite.is<Polygon>();
            },
            R"doc(
                Check if the composite contains a 2D Polygon object.

                Returns:
                    bool: True if the composite contains a Polygon, False otherwise.

                Example:
                    >>> vertices = [Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0)]
                    >>> polygon = Polygon(vertices)
                    >>> composite = Composite(polygon)
                    >>> composite.is_polygon()  # True
            )doc"
        )
        .def(
            "is_composite",
            +[](const Composite& aComposite) -> bool
            {
                return aComposite.is<Composite>();
            },
            R"doc(
                Check if the composite contains another 2D Composite object.

                Returns:
                    bool: True if the composite contains a Composite, False otherwise.

                Example:
                    >>> inner_composite = Composite(Point(1.0, 2.0))
                    >>> outer_composite = Composite(inner_composite)
                    >>> outer_composite.is_composite()  # True
            )doc"
        )

        .def(
            "intersects",
            overload_cast<const Object&>(&Composite::intersects, const_),
            R"doc(
                Check if the 2D composite intersects with another geometric object.

                Args:
                    object (Object): The 2D object to check intersection with.

                Returns:
                    bool: True if the composite intersects the object, False otherwise.

                Example:
                    >>> composite = Composite(Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0)]))
                    >>> point = Point(0.5, 0.5)
                    >>> composite.intersects(point)  # True
            )doc",
            arg("object")
        )
        .def(
            "intersects",
            overload_cast<const Composite&>(&Composite::intersects, const_),
            R"doc(
                Check if the 2D composite intersects with another composite.

                Args:
                    composite (Composite): The composite to check intersection with.

                Returns:
                    bool: True if the composites intersect, False otherwise.

                Example:
                    >>> composite1 = Composite(Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0)]))
                    >>> composite2 = Composite(Polygon([Point(0.5, 0.5), Point(1.5, 0.5), Point(1.5, 1.5)]))
                    >>> composite1.intersects(composite2)  # True
            )doc",
            arg("composite")
        )
        .def(
            "contains",
            overload_cast<const Object&>(&Composite::contains, const_),
            R"doc(
                Check if the 2D composite contains another geometric object.

                Args:
                    object (Object): The 2D object to check containment for.

                Returns:
                    bool: True if the composite contains the object, False otherwise.

                Example:
                    >>> composite = Composite(Polygon([Point(0.0, 0.0), Point(2.0, 0.0), Point(2.0, 2.0)]))
                    >>> point = Point(1.0, 1.0)
                    >>> composite.contains(point)  # True
            )doc",
            arg("object")
        )
        .def(
            "contains",
            overload_cast<const Composite&>(&Composite::contains, const_),
            R"doc(
                Check if the 2D composite contains another composite.

                Args:
                    composite (Composite): The composite to check containment for.

                Returns:
                    bool: True if this composite contains the other composite, False otherwise.

                Example:
                    >>> outer_composite = Composite(Polygon([Point(0.0, 0.0), Point(3.0, 0.0), Point(3.0, 3.0)]))
                    >>> inner_composite = Composite(Polygon([Point(1.0, 1.0), Point(2.0, 1.0), Point(2.0, 2.0)]))
                    >>> outer_composite.contains(inner_composite)  # True
            )doc",
            arg("composite")
        )
        .def(
            "any_contains",
            overload_cast<const Object&>(&Composite::anyContains, const_),
            R"doc(
                Check if any object in the 2D composite contains another geometric object.

                Args:
                    object (Object): The 2D object to check containment for.

                Returns:
                    bool: True if any object in the composite contains the object, False otherwise.

                Example:
                    >>> polygon1 = Polygon([Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0)])
                    >>> polygon2 = Polygon([Point(2.0, 2.0), Point(3.0, 2.0), Point(3.0, 3.0)])
                    >>> composite = Composite(polygon1) + Composite(polygon2)
                    >>> point = Point(0.5, 0.5)
                    >>> composite.any_contains(point)  # True
            )doc",
            arg("object")
        )
        .def(
            "any_contains",
            overload_cast<const Composite&>(&Composite::anyContains, const_),
            R"doc(
                Check if any object in the 2D composite contains another composite.

                Args:
                    composite (Composite): The composite to check containment for.

                Returns:
                    bool: True if any object in this composite contains the other composite, False otherwise.

                Example:
                    >>> outer_polygon = Polygon([Point(0.0, 0.0), Point(3.0, 0.0), Point(3.0, 3.0)])
                    >>> composite1 = Composite(outer_polygon)
                    >>> inner_composite = Composite(Point(1.5, 1.5))
                    >>> composite1.any_contains(inner_composite)  # True
            )doc",
            arg("composite")
        )

        .def(
            "as_point",
            +[](const Composite& aComposite) -> Point
            {
                return aComposite.as<Point>();
            },
            R"doc(
                Convert the composite to a 2D Point object.

                Returns:
                    Point: The point object contained in the composite.

                Raises:
                    RuntimeError: If the composite does not contain a Point.

                Example:
                    >>> composite = Composite(Point(1.0, 2.0))
                    >>> point = composite.as_point()
            )doc"
        )
        .def(
            "as_point_set",
            +[](const Composite& aComposite) -> PointSet
            {
                return aComposite.as<PointSet>();
            },
            R"doc(
                Convert the composite to a 2D PointSet object.

                Returns:
                    PointSet: The point set object contained in the composite.

                Raises:
                    RuntimeError: If the composite does not contain a PointSet.

                Example:
                    >>> point_set = PointSet([Point(1.0, 2.0), Point(3.0, 4.0)])
                    >>> composite = Composite(point_set)
                    >>> extracted_set = composite.as_point_set()
            )doc"
        )
        .def(
            "as_line",
            +[](const Composite& aComposite) -> Line
            {
                return aComposite.as<Line>();
            },
            R"doc(
                Convert the composite to a 2D Line object.

                Returns:
                    Line: The line object contained in the composite.

                Raises:
                    RuntimeError: If the composite does not contain a Line.

                Example:
                    >>> line = Line(Point(0.0, 0.0), np.array([1.0, 1.0]))
                    >>> composite = Composite(line)
                    >>> extracted_line = composite.as_line()
            )doc"
        )
        .def(
            "as_segment",
            +[](const Composite& aComposite) -> Segment
            {
                return aComposite.as<Segment>();
            },
            R"doc(
                Convert the composite to a 2D Segment object.

                Returns:
                    Segment: The segment object contained in the composite.

                Raises:
                    RuntimeError: If the composite does not contain a Segment.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0), Point(1.0, 1.0))
                    >>> composite = Composite(segment)
                    >>> extracted_segment = composite.as_segment()
            )doc"
        )
        .def(
            "as_line_string",
            +[](const Composite& aComposite) -> LineString
            {
                return aComposite.as<LineString>();
            },
            R"doc(
                Convert the composite to a 2D LineString object.

                Returns:
                    LineString: The line string object contained in the composite.

                Raises:
                    RuntimeError: If the composite does not contain a LineString.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0), Point(2.0, 2.0)]
                    >>> line_string = LineString(points)
                    >>> composite = Composite(line_string)
                    >>> extracted_line_string = composite.as_line_string()
            )doc"
        )
        .def(
            "as_polygon",
            +[](const Composite& aComposite) -> Polygon
            {
                return aComposite.as<Polygon>();
            },
            R"doc(
                Convert the composite to a 2D Polygon object.

                Returns:
                    Polygon: The polygon object contained in the composite.

                Raises:
                    RuntimeError: If the composite does not contain a Polygon.

                Example:
                    >>> vertices = [Point(0.0, 0.0), Point(1.0, 0.0), Point(1.0, 1.0)]
                    >>> polygon = Polygon(vertices)
                    >>> composite = Composite(polygon)
                    >>> extracted_polygon = composite.as_polygon()
            )doc"
        )
        .def(
            "as_composite",
            +[](const Composite& aComposite) -> Composite
            {
                return aComposite.as<Composite>();
            },
            R"doc(
                Convert the composite to a 2D Composite object.

                Returns:
                    Composite: The composite object contained in the composite.

                Raises:
                    RuntimeError: If the composite does not contain a Composite.

                Example:
                    >>> inner_composite = Composite(Point(1.0, 2.0))
                    >>> outer_composite = Composite(inner_composite)
                    >>> extracted_composite = outer_composite.as_composite()
            )doc"
        )

        .def(
            "access_object_at",
            &Composite::accessObjectAt,
            R"doc(
                Access the object at a specific index in the 2D composite.

                Args:
                    index (int): The index of the object to access.

                Returns:
                    Object: Reference to the object at the specified index.

                Raises:
                    IndexError: If the index is out of bounds.

                Example:
                    >>> composite = Composite(Point(1.0, 2.0))
                    >>> obj = composite.access_object_at(0)
            )doc",
            return_value_policy::reference,
            arg("index")
        )

        .def(
            "get_object_count",
            &Composite::getObjectCount,
            R"doc(
                Get the number of objects contained in the 2D composite.

                Returns:
                    int: The number of objects in the composite.

                Example:
                    >>> composite = Composite(Point(1.0, 2.0))
                    >>> count = composite.get_object_count()  # 1
            )doc"
        )
        // .def("intersection_with", overload_cast<const Object&>(&Composite::intersectionWith, const_))
        // .def("intersection_with", overload_cast<const Composite&>(&Composite::intersectionWith, const_))

        .def(
            "apply_transformation",
            &Composite::applyTransformation,
            R"doc(
                Apply a transformation to all objects in the 2D composite in place.

                Args:
                    transformation (Transformation): The 2D transformation to apply.

                Example:
                    >>> composite = Composite(Point(1.0, 2.0))
                    >>> transformation = Translation([1.0, 1.0])
                    >>> composite.apply_transformation(transformation)
            )doc",
            arg("transformation")
        )

        .def_static(
            "undefined",
            &Composite::Undefined,
            R"doc(
                Create an undefined 2D composite.

                Returns:
                    Composite: An undefined composite object.

                Example:
                    >>> undefined_composite = Composite.undefined()
                    >>> undefined_composite.is_defined()  # False
            )doc"
        )
        .def_static(
            "empty",
            &Composite::Empty,
            R"doc(
                Create an empty 2D composite (containing no objects).

                Returns:
                    Composite: An empty composite object.

                Example:
                    >>> empty_composite = Composite.empty()
                    >>> empty_composite.is_empty()  # True
                    >>> empty_composite.get_object_count()  # 0
            )doc"
        )

        ;
}
