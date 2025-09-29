/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Type/Shared.hpp>

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Composite.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Cone.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Composite(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;
    using ostk::core::type::Shared;

    using ostk::mathematics::geometry::d3::Intersection;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Composite;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Cuboid;
    using ostk::mathematics::geometry::d3::object::Ellipsoid;
    using ostk::mathematics::geometry::d3::object::Line;
    using ostk::mathematics::geometry::d3::object::LineString;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::geometry::d3::object::Sphere;
    using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;
    using ostk::mathematics::object::Vector3d;

    class_<Composite, Object>(aModule, "Composite")

        .def(
            init<const Object&>(),
            R"doc(
                Create a composite object from a single geometric object.

                Args:
                    object (Object): The geometric object to wrap in the composite.

                Example:
                    >>> point = Point(1.0, 2.0, 3.0)
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
                Check if the composite is defined.

                Returns:
                    bool: True if the composite is defined, False otherwise.

                Example:
                    >>> composite = Composite(Point(1.0, 2.0, 3.0))
                    >>> composite.is_defined()  # True
            )doc"
        )
        .def(
            "is_empty",
            &Composite::isEmpty,
            R"doc(
                Check if the composite is empty (contains no objects).

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
                Check if the composite contains a Point object.

                Returns:
                    bool: True if the composite contains a Point, False otherwise.

                Example:
                    >>> composite = Composite(Point(1.0, 2.0, 3.0))
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
                Check if the composite contains a PointSet object.

                Returns:
                    bool: True if the composite contains a PointSet, False otherwise.

                Example:
                    >>> point_set = PointSet([Point(1.0, 2.0, 3.0), Point(4.0, 5.0, 6.0)])
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
                Check if the composite contains a Line object.

                Returns:
                    bool: True if the composite contains a Line, False otherwise.

                Example:
                    >>> line = Line(Point(0.0, 0.0, 0.0), np.array([1.0, 0.0, 0.0]))
                    >>> composite = Composite(line)
                    >>> composite.is_line()  # True
            )doc"
        )
        .def(
            "is_ray",
            +[](const Composite& aComposite) -> bool
            {
                return aComposite.is<Ray>();
            },
            R"doc(
                Check if the composite contains a Ray object.

                Returns:
                    bool: True if the composite contains a Ray, False otherwise.

                Example:
                    >>> ray = Ray(Point(0.0, 0.0, 0.0), np.array([1.0, 0.0, 0.0]))
                    >>> composite = Composite(ray)
                    >>> composite.is_ray()  # True
            )doc"
        )
        .def(
            "is_segment",
            +[](const Composite& aComposite) -> bool
            {
                return aComposite.is<Segment>();
            },
            R"doc(
                Check if the composite contains a Segment object.

                Returns:
                    bool: True if the composite contains a Segment, False otherwise.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0, 0.0), Point(1.0, 1.0, 1.0))
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
                Check if the composite contains a LineString object.

                Returns:
                    bool: True if the composite contains a LineString, False otherwise.

                Example:
                    >>> points = [Point(0.0, 0.0, 0.0), Point(1.0, 1.0, 1.0), Point(2.0, 2.0, 2.0)]
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
                Check if the composite contains a Polygon object.

                Returns:
                    bool: True if the composite contains a Polygon, False otherwise.

                Example:
                    >>> vertices = [Point(0.0, 0.0, 0.0), Point(1.0, 0.0, 0.0), Point(1.0, 1.0, 0.0)]
                    >>> polygon = Polygon(vertices)
                    >>> composite = Composite(polygon)
                    >>> composite.is_polygon()  # True
            )doc"
        )
        .def(
            "is_plane",
            +[](const Composite& aComposite) -> bool
            {
                return aComposite.is<Plane>();
            },
            R"doc(
                Check if the composite contains a Plane object.

                Returns:
                    bool: True if the composite contains a Plane, False otherwise.

                Example:
                    >>> plane = Plane(Point(0.0, 0.0, 0.0), np.array([0.0, 0.0, 1.0]))
                    >>> composite = Composite(plane)
                    >>> composite.is_plane()  # True
            )doc"
        )
        .def(
            "is_sphere",
            +[](const Composite& aComposite) -> bool
            {
                return aComposite.is<Sphere>();
            },
            R"doc(
                Check if the composite contains a Sphere object.

                Returns:
                    bool: True if the composite contains a Sphere, False otherwise.

                Example:
                    >>> sphere = Sphere(Point(0.0, 0.0, 0.0), 1.0)
                    >>> composite = Composite(sphere)
                    >>> composite.is_sphere()  # True
            )doc"
        )
        .def(
            "is_ellipsoid",
            +[](const Composite& aComposite) -> bool
            {
                return aComposite.is<Ellipsoid>();
            },
            R"doc(
                Check if the composite contains an Ellipsoid object.

                Returns:
                    bool: True if the composite contains an Ellipsoid, False otherwise.

                Example:
                    >>> ellipsoid = Ellipsoid(Point(0.0, 0.0, 0.0), 1.0, 0.8, 0.6)
                    >>> composite = Composite(ellipsoid)
                    >>> composite.is_ellipsoid()  # True
            )doc"
        )
        .def(
            "is_pyramid",
            +[](const Composite& aComposite) -> bool
            {
                return aComposite.is<Pyramid>();
            },
            R"doc(
                Check if the composite contains a Pyramid object.

                Returns:
                    bool: True if the composite contains a Pyramid, False otherwise.

                Example:
                    >>> apex = Point(0.0, 0.0, 1.0)
                    >>> base = Polygon([Point(0.0, 0.0, 0.0), Point(1.0, 0.0, 0.0), Point(1.0, 1.0, 0.0)])
                    >>> pyramid = Pyramid(base, apex)
                    >>> composite = Composite(pyramid)
                    >>> composite.is_pyramid()  # True
            )doc"
        )
        .def(
            "is_cone",
            +[](const Composite& aComposite) -> bool
            {
                return aComposite.is<Cone>();
            },
            R"doc(
                Check if the composite contains a Cone object.

                Returns:
                    bool: True if the composite contains a Cone, False otherwise.

                Example:
                    >>> cone = Cone(Point(0.0, 0.0, 0.0), np.array([0.0, 0.0, 1.0]), Angle.degrees(30.0))
                    >>> composite = Composite(cone)
                    >>> composite.is_cone()  # True
            )doc"
        )
        .def(
            "is_composite",
            +[](const Composite& aComposite) -> bool
            {
                return aComposite.is<Composite>();
            },
            R"doc(
                Check if the composite contains another Composite object.

                Returns:
                    bool: True if the composite contains a Composite, False otherwise.

                Example:
                    >>> inner_composite = Composite(Point(1.0, 2.0, 3.0))
                    >>> outer_composite = Composite(inner_composite)
                    >>> outer_composite.is_composite()  # True
            )doc"
        )

        .def(
            "intersects",
            overload_cast<const Object&>(&Composite::intersects, const_),
            R"doc(
                Check if the composite intersects with another geometric object.

                Args:
                    object (Object): The object to check intersection with.

                Returns:
                    bool: True if the composite intersects the object, False otherwise.

                Example:
                    >>> composite = Composite(Sphere(Point(0.0, 0.0, 0.0), 1.0))
                    >>> point = Point(0.5, 0.0, 0.0)
                    >>> composite.intersects(point)  # True
            )doc",
            arg("object")
        )
        .def(
            "intersects",
            overload_cast<const Composite&>(&Composite::intersects, const_),
            R"doc(
                Check if the composite intersects with another composite.

                Args:
                    composite (Composite): The composite to check intersection with.

                Returns:
                    bool: True if the composites intersect, False otherwise.

                Example:
                    >>> composite1 = Composite(Sphere(Point(0.0, 0.0, 0.0), 1.0))
                    >>> composite2 = Composite(Sphere(Point(1.5, 0.0, 0.0), 1.0))
                    >>> composite1.intersects(composite2)  # True
            )doc",
            arg("composite")
        )
        .def(
            "contains",
            overload_cast<const Object&>(&Composite::contains, const_),
            R"doc(
                Check if the composite contains another geometric object.

                Args:
                    object (Object): The object to check containment for.

                Returns:
                    bool: True if the composite contains the object, False otherwise.

                Example:
                    >>> composite = Composite(Sphere(Point(0.0, 0.0, 0.0), 2.0))
                    >>> point = Point(0.5, 0.0, 0.0)
                    >>> composite.contains(point)  # True
            )doc",
            arg("object")
        )
        .def(
            "contains",
            overload_cast<const Composite&>(&Composite::contains, const_),
            R"doc(
                Check if the composite contains another composite.

                Args:
                    composite (Composite): The composite to check containment for.

                Returns:
                    bool: True if this composite contains the other composite, False otherwise.

                Example:
                    >>> outer_composite = Composite(Sphere(Point(0.0, 0.0, 0.0), 2.0))
                    >>> inner_composite = Composite(Sphere(Point(0.0, 0.0, 0.0), 1.0))
                    >>> outer_composite.contains(inner_composite)  # True
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
                Convert the composite to a Point object.

                Returns:
                    Point: The point object contained in the composite.

                Raises:
                    RuntimeError: If the composite does not contain a Point.

                Example:
                    >>> composite = Composite(Point(1.0, 2.0, 3.0))
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
                Convert the composite to a PointSet object.

                Returns:
                    PointSet: The point set object contained in the composite.

                Raises:
                    RuntimeError: If the composite does not contain a PointSet.

                Example:
                    >>> point_set = PointSet([Point(1.0, 2.0, 3.0), Point(4.0, 5.0, 6.0)])
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
                Convert the composite to a Line object.

                Returns:
                    Line: The line object contained in the composite.

                Raises:
                    RuntimeError: If the composite does not contain a Line.

                Example:
                    >>> line = Line(Point(0.0, 0.0, 0.0), np.array([1.0, 0.0, 0.0]))
                    >>> composite = Composite(line)
                    >>> extracted_line = composite.as_line()
            )doc"
        )
        .def(
            "as_ray",
            +[](const Composite& aComposite) -> Ray
            {
                return aComposite.as<Ray>();
            },
            R"doc(
                Convert the composite to a Ray object.

                Returns:
                    Ray: The ray object contained in the composite.

                Raises:
                    RuntimeError: If the composite does not contain a Ray.

                Example:
                    >>> ray = Ray(Point(0.0, 0.0, 0.0), np.array([1.0, 0.0, 0.0]))
                    >>> composite = Composite(ray)
                    >>> extracted_ray = composite.as_ray()
            )doc"
        )
        .def(
            "as_segment",
            +[](const Composite& aComposite) -> Segment
            {
                return aComposite.as<Segment>();
            },
            R"doc(
                Convert the composite to a Segment object.

                Returns:
                    Segment: The segment object contained in the composite.

                Raises:
                    RuntimeError: If the composite does not contain a Segment.

                Example:
                    >>> segment = Segment(Point(0.0, 0.0, 0.0), Point(1.0, 1.0, 1.0))
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
                Convert the composite to a LineString object.

                Returns:
                    LineString: The line string object contained in the composite.

                Raises:
                    RuntimeError: If the composite does not contain a LineString.

                Example:
                    >>> points = [Point(0.0, 0.0, 0.0), Point(1.0, 1.0, 1.0), Point(2.0, 2.0, 2.0)]
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
                Convert the composite to a Polygon object.

                Returns:
                    Polygon: The polygon object contained in the composite.

                Raises:
                    RuntimeError: If the composite does not contain a Polygon.

                Example:
                    >>> vertices = [Point(0.0, 0.0, 0.0), Point(1.0, 0.0, 0.0), Point(1.0, 1.0, 0.0)]
                    >>> polygon = Polygon(vertices)
                    >>> composite = Composite(polygon)
                    >>> extracted_polygon = composite.as_polygon()
            )doc"
        )
        .def(
            "as_plane",
            +[](const Composite& aComposite) -> Plane
            {
                return aComposite.as<Plane>();
            },
            R"doc(
                Convert the composite to a Plane object.

                Returns:
                    Plane: The plane object contained in the composite.

                Raises:
                    RuntimeError: If the composite does not contain a Plane.

                Example:
                    >>> plane = Plane(Point(0.0, 0.0, 0.0), np.array([0.0, 0.0, 1.0]))
                    >>> composite = Composite(plane)
                    >>> extracted_plane = composite.as_plane()
            )doc"
        )
        .def(
            "as_sphere",
            +[](const Composite& aComposite) -> Sphere
            {
                return aComposite.as<Sphere>();
            },
            R"doc(
                Convert the composite to a Sphere object.

                Returns:
                    Sphere: The sphere object contained in the composite.

                Raises:
                    RuntimeError: If the composite does not contain a Sphere.

                Example:
                    >>> sphere = Sphere(Point(0.0, 0.0, 0.0), 1.0)
                    >>> composite = Composite(sphere)
                    >>> extracted_sphere = composite.as_sphere()
            )doc"
        )
        .def(
            "as_ellipsoid",
            +[](const Composite& aComposite) -> Ellipsoid
            {
                return aComposite.as<Ellipsoid>();
            },
            R"doc(
                Convert the composite to an Ellipsoid object.

                Returns:
                    Ellipsoid: The ellipsoid object contained in the composite.

                Raises:
                    RuntimeError: If the composite does not contain an Ellipsoid.

                Example:
                    >>> ellipsoid = Ellipsoid(Point(0.0, 0.0, 0.0), 1.0, 0.8, 0.6)
                    >>> composite = Composite(ellipsoid)
                    >>> extracted_ellipsoid = composite.as_ellipsoid()
            )doc"
        )
        .def(
            "as_pyramid",
            +[](const Composite& aComposite) -> Pyramid
            {
                return aComposite.as<Pyramid>();
            },
            R"doc(
                Convert the composite to a Pyramid object.

                Returns:
                    Pyramid: The pyramid object contained in the composite.

                Raises:
                    RuntimeError: If the composite does not contain a Pyramid.

                Example:
                    >>> apex = Point(0.0, 0.0, 1.0)
                    >>> base = Polygon([Point(0.0, 0.0, 0.0), Point(1.0, 0.0, 0.0), Point(1.0, 1.0, 0.0)])
                    >>> pyramid = Pyramid(base, apex)
                    >>> composite = Composite(pyramid)
                    >>> extracted_pyramid = composite.as_pyramid()
            )doc"
        )
        .def(
            "as_cone",
            +[](const Composite& aComposite) -> Cone
            {
                return aComposite.as<Cone>();
            },
            R"doc(
                Convert the composite to a Cone object.

                Returns:
                    Cone: The cone object contained in the composite.

                Raises:
                    RuntimeError: If the composite does not contain a Cone.

                Example:
                    >>> cone = Cone(Point(0.0, 0.0, 0.0), np.array([0.0, 0.0, 1.0]), Angle.degrees(30.0))
                    >>> composite = Composite(cone)
                    >>> extracted_cone = composite.as_cone()
            )doc"
        )
        .def(
            "as_composite",
            +[](const Composite& aComposite) -> Composite
            {
                return aComposite.as<Composite>();
            },
            R"doc(
                Convert the composite to a Composite object.

                Returns:
                    Composite: The composite object contained in the composite.

                Raises:
                    RuntimeError: If the composite does not contain a Composite.

                Example:
                    >>> inner_composite = Composite(Point(1.0, 2.0, 3.0))
                    >>> outer_composite = Composite(inner_composite)
                    >>> extracted_composite = outer_composite.as_composite()
            )doc"
        )

        .def(
            "access_object_at",
            &Composite::accessObjectAt,
            R"doc(
                Access the object at a specific index in the composite.

                Args:
                    index (int): The index of the object to access.

                Returns:
                    Object: Reference to the object at the specified index.

                Raises:
                    IndexError: If the index is out of bounds.

                Example:
                    >>> composite = Composite(Point(1.0, 2.0, 3.0))
                    >>> obj = composite.access_object_at(0)
            )doc",
            arg("index"),
            return_value_policy::reference
        )

        .def(
            "get_object_count",
            &Composite::getObjectCount,
            R"doc(
                Get the number of objects contained in the composite.

                Returns:
                    int: The number of objects in the composite.

                Example:
                    >>> composite = Composite(Point(1.0, 2.0, 3.0))
                    >>> count = composite.get_object_count()  # 1
            )doc"
        )
        .def(
            "intersection_with",
            overload_cast<const Object&>(&Composite::intersectionWith, const_),
            R"doc(
                Compute the intersection of the composite with another geometric object.

                Args:
                    object (Object): The object to compute intersection with.

                Returns:
                    Intersection: The intersection result.

                Example:
                    >>> composite = Composite(Sphere(Point(0.0, 0.0, 0.0), 1.0))
                    >>> line = Line(Point(-2.0, 0.0, 0.0), np.array([1.0, 0.0, 0.0]))
                    >>> intersection = composite.intersection_with(line)
            )doc",
            arg("object")
        )
        .def(
            "intersection_with",
            overload_cast<const Composite&>(&Composite::intersectionWith, const_),
            R"doc(
                Compute the intersection of the composite with another composite.

                Args:
                    composite (Composite): The composite to compute intersection with.

                Returns:
                    Intersection: The intersection result.

                Example:
                    >>> composite1 = Composite(Sphere(Point(0.0, 0.0, 0.0), 1.0))
                    >>> composite2 = Composite(Sphere(Point(1.5, 0.0, 0.0), 1.0))
                    >>> intersection = composite1.intersection_with(composite2)
            )doc",
            arg("composite")
        )

        .def(
            "apply_transformation",
            &Composite::applyTransformation,
            R"doc(
                Apply a transformation to all objects in the composite in place.

                Args:
                    transformation (Transformation): The transformation to apply.

                Example:
                    >>> composite = Composite(Point(1.0, 2.0, 3.0))
                    >>> transformation = Translation([1.0, 1.0, 1.0])
                    >>> composite.apply_transformation(transformation)
            )doc",
            arg("transformation")
        )

        .def_static(
            "undefined",
            &Composite::Undefined,
            R"doc(
                Create an undefined composite.

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
                Create an empty composite (containing no objects).

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
