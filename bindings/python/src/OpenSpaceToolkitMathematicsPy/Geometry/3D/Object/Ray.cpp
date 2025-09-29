/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Ray.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Ray(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::mathematics::geometry::d3::Intersection;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Ellipsoid;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Sphere;
    using ostk::mathematics::object::Vector3d;

    class_<Ray, Object>(aModule, "Ray")

        .def(
            init<const Point&, const Vector3d&>(),
            R"doc(
                Create a 3D ray with specified origin and direction.

                Args:
                    origin (Point): The origin point of the ray.
                    direction (np.array): The direction vector of the ray.

                Example:
                    >>> origin = Point(0.0, 0.0, 0.0)
                    >>> direction = np.array([1.0, 0.0, 0.0])
                    >>> ray = Ray(origin, direction)
            )doc",
            arg("origin"),
            arg("direction")
        )

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Ray>))
        .def("__repr__", &(shiftToString<Ray>))

        .def(
            "is_defined",
            &Ray::isDefined,
            R"doc(
                Check if the ray is defined.

                Returns:
                    bool: True if the ray is defined, False otherwise.

                Example:
                    >>> ray = Ray(Point(0.0, 0.0, 0.0), np.array([1.0, 0.0, 0.0]))
                    >>> ray.is_defined()  # True
            )doc"
        )
        .def("intersects", overload_cast<const Point&>(&Ray::intersects, const_), arg("point"))
        .def("intersects", overload_cast<const Plane&>(&Ray::intersects, const_), arg("plane"))
        .def("intersects", overload_cast<const Sphere&>(&Ray::intersects, const_), arg("sphere"))
        .def("intersects", overload_cast<const Ellipsoid&>(&Ray::intersects, const_), arg("ellipsoid"))
        .def(
            "contains",
            overload_cast<const Point&>(&Ray::contains, const_),
            R"doc(
                Check if the ray contains a point.

                Args:
                    point (Point): The point to check.

                Returns:
                    bool: True if the ray contains the point, False otherwise.

                Example:
                    >>> ray = Ray(Point(0.0, 0.0, 0.0), np.array([1.0, 0.0, 0.0]))
                    >>> ray.contains(Point(2.0, 0.0, 0.0))  # True (point on ray)
            )doc",
            arg("point")
        )
        .def(
            "contains",
            overload_cast<const PointSet&>(&Ray::contains, const_),
            R"doc(
                Check if the ray contains a point set.

                Args:
                    point_set (PointSet): The point set to check.

                Returns:
                    bool: True if the ray contains the point set, False otherwise.
            )doc",
            arg("point_set")
        )

        .def(
            "get_origin",
            &Ray::getOrigin,
            R"doc(
                Get the origin point of the ray.

                Returns:
                    Point: The origin point of the ray.

                Example:
                    >>> ray = Ray(Point(1.0, 2.0, 3.0), np.array([1.0, 0.0, 0.0]))
                    >>> origin = ray.get_origin()  # Point(1.0, 2.0, 3.0)
            )doc"
        )
        .def(
            "get_direction",
            &Ray::getDirection,
            R"doc(
                Get the direction vector of the ray.

                Returns:
                    Vector3d: The normalized direction vector of the ray.

                Example:
                    >>> ray = Ray(Point(0.0, 0.0, 0.0), np.array([1.0, 0.0, 0.0]))
                    >>> direction = ray.get_direction()  # [1.0, 0.0, 0.0]
            )doc"
        )
        .def(
            "distance_to",
            overload_cast<const Point&>(&Ray::distanceTo, const_),
            R"doc(
                Calculate the distance from the ray to a point.

                Args:
                    point (Point): The point to calculate distance to.

                Returns:
                    float: The minimum distance from the ray to the point.

                Example:
                    >>> ray = Ray(Point(0.0, 0.0, 0.0), np.array([1.0, 0.0, 0.0]))
                    >>> distance = ray.distance_to(Point(1.0, 1.0, 0.0))  # 1.0
            )doc",
            arg("point")
        )
        .def(
            "intersection_with",
            overload_cast<const Plane&>(&Ray::intersectionWith, const_),
            arg("plane"),
            R"doc(
                Compute the intersection of the ray with a plane.

                Args:
                    plane (Plane): The plane to intersect with.

                Returns:
                    Intersection: The intersection of the ray with the plane.
                
                Example:
                    >>> ray = Ray(Point(0.0, 0.0, 0.0), np.array([0.0, 0.0, -1.0]))
                    >>> plane = Plane(Point(0.0, 0.0, 0.0), np.array([0.0, 0.0, 1.0]))
                    >>> intersection = ray.intersection_with(plane)
                    >>> intersection.get_point()  # Point(0.0, 0.0, 0.0)
            )doc"
        )
        .def(
            "intersection_with",
            overload_cast<const Sphere&, const bool>(&Ray::intersectionWith, const_),
            R"doc(
                Compute the intersection of the ray with a sphere.

                Args:
                    sphere (Sphere): The sphere to intersect with.
                    only_in_sight (bool, optional): If true, only return intersection points that are in sight. Defaults to True.

                Returns:
                    Intersection: The intersection of the ray with the sphere.

                Example:
                    >>> ray = Ray(Point(0.0, 0.0, 0.0), np.array([1.0, 0.0, 0.0]))
                    >>> sphere = Sphere(Point(0.0, 0.0, 0.0), 1.0)
                    >>> intersection = ray.intersection_with(sphere)
                    >>> intersection.get_point()  # Point(0.0, 0.0, 0.0)
            )doc",
            arg("sphere"),
            arg("only_in_sight") = DEFAULT_ONLY_IN_SIGHT
        )
        .def(
            "intersection_with",
            overload_cast<const Ellipsoid&, const bool>(&Ray::intersectionWith, const_),
            R"doc(
                Compute the intersection of the ray with an ellipsoid.

                Args:
                    ellipsoid (Ellipsoid): The ellipsoid to intersect with.
                    only_in_sight (bool, optional): If true, only return intersection points that are in sight. Defaults to True.

                Returns:
                    Intersection: The intersection of the ray with the ellipsoid.

                Example:
                    >>> ray = Ray(Point(0.0, 0.0, 0.0), np.array([1.0, 0.0, 0.0]))
                    >>> ellipsoid = Ellipsoid(Point(0.0, 0.0, 0.0), 1.0, 1.0, 1.0)
                    >>> intersection = ray.intersection_with(ellipsoid)
                    >>> intersection.get_point()  # Point(0.0, 0.0, 0.0)
            )doc",
            arg("ellipsoid"),
            arg("only_in_sight") = DEFAULT_ONLY_IN_SIGHT
        )
        .def(
            "apply_transformation",
            &Ray::applyTransformation,
            R"doc(
                Apply a transformation to the ray.

                Args:
                    transformation (Transformation): The transformation to apply.

                Example:
                    >>> ray = Ray(Point(0.0, 0.0, 0.0), np.array([1.0, 0.0, 0.0]))
                    >>> transformation = Transformation.translation([1.0, 0.0])
                    >>> ray.apply_transformation(transformation)
            )doc",
            arg("transformation")
        )

        .def_static(
            "undefined",
            &Ray::Undefined,
            R"doc(
                Create an undefined ray.

                Returns:
                    Ray: An undefined ray object.

                Example:
                    >>> undefined_ray = Ray.undefined()
                    >>> undefined_ray.is_defined()  # False
            )doc"
        )

        ;
}
