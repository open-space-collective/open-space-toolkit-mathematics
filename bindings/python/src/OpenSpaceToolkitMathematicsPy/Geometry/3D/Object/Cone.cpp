/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Cone.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Cone(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;
    using ostk::core::type::Size;

    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::d3::Intersection;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Cone;
    using ostk::mathematics::geometry::d3::object::Ellipsoid;
    using ostk::mathematics::geometry::d3::object::Line;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::geometry::d3::object::Sphere;
    using ostk::mathematics::object::Vector3d;

    class_<Cone, Object>(aModule, "Cone")

        .def(
            init<const Point&, const Vector3d&, const Angle&>(),
            R"doc(
                Create a 3D cone with specified apex, axis, and angle.

                Args:
                    apex (Point): The apex (tip) point of the cone.
                    axis (np.array): The axis direction vector of the cone.
                    angle (Angle): The half-angle of the cone opening.

                Example:
                    >>> apex = Point(0.0, 0.0, 0.0)
                    >>> axis = np.array([0.0, 0.0, 1.0])
                    >>> angle = Angle.degrees(30.0)
                    >>> cone = Cone(apex, axis, angle)
            )doc",
            arg("apex"),
            arg("axis"),
            arg("angle")
        )

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Cone>))
        .def("__repr__", &(shiftToString<Cone>))

        .def(
            "is_defined",
            &Cone::isDefined,
            R"doc(
                Check if the cone is defined.

                Returns:
                    bool: True if the cone is defined, False otherwise.

                Example:
                    >>> cone = Cone(Point(0.0, 0.0, 0.0), np.array([0.0, 0.0, 1.0]), Angle.degrees(30.0))
                    >>> cone.is_defined()  # True
            )doc"
        )
        .def(
            "intersects",
            overload_cast<const Sphere&, const Size>(&Cone::intersects, const_),
            R"doc(
                Check if the cone intersects with a sphere.

                Args:
                    sphere (Sphere): The sphere to check intersection with.
                    discretization_level (int): Level of discretization for intersection calculation.

                Returns:
                    bool: True if the cone intersects the sphere, False otherwise.

                Example:
                    >>> cone = Cone(Point(0.0, 0.0, 0.0), np.array([0.0, 0.0, 1.0]), Angle.degrees(30.0))
                    >>> sphere = Sphere(Point(1.0, 0.0, 1.0), 0.5)
                    >>> cone.intersects(sphere)
            )doc",
            arg("sphere"),
            arg("discretization_level") = DEFAULT_DISCRETIZATION_LEVEL
        )
        .def(
            "intersects",
            overload_cast<const Ellipsoid&, const Size>(&Cone::intersects, const_),
            R"doc(
                Check if the cone intersects with an ellipsoid.

                Args:
                    ellipsoid (Ellipsoid): The ellipsoid to check intersection with.
                    discretization_level (int): Level of discretization for intersection calculation.

                Returns:
                    bool: True if the cone intersects the ellipsoid, False otherwise.

                Example:
                    >>> cone = Cone(Point(0.0, 0.0, 0.0), np.array([0.0, 0.0, 1.0]), Angle.degrees(30.0))
                    >>> ellipsoid = Ellipsoid(Point(1.0, 0.0, 1.0), 1.0, 0.8, 0.6)
                    >>> cone.intersects(ellipsoid)
            )doc",
            arg("ellipsoid"),
            arg("discretization_level") = DEFAULT_DISCRETIZATION_LEVEL
        )
        .def(
            "contains",
            overload_cast<const Point&>(&Cone::contains, const_),
            R"doc(
                Check if the cone contains a point.

                Args:
                    point (Point): The point to check.

                Returns:
                    bool: True if the cone contains the point, False otherwise.

                Example:
                    >>> cone = Cone(Point(0.0, 0.0, 0.0), np.array([0.0, 0.0, 1.0]), Angle.degrees(30.0))
                    >>> cone.contains(Point(0.1, 0.1, 1.0))  # True for point inside cone
            )doc",
            arg("point")
        )
        .def(
            "contains",
            overload_cast<const PointSet&>(&Cone::contains, const_),
            R"doc(
                Check if the cone contains a point set.

                Args:
                    point_set (PointSet): The point set to check.

                Returns:
                    bool: True if the cone contains the point set, False otherwise.

                Example:
                    >>> cone = Cone(Point(0.0, 0.0, 0.0), np.array([0.0, 0.0, 1.0]), Angle.degrees(30.0))
                    >>> cone.contains(PointSet([Point(0.1, 0.1, 1.0), Point(0.2, 0.2, 1.0)]))  # True for points inside cone
            )doc",
            arg("point_set")
        )
        .def(
            "contains",
            overload_cast<const Segment&>(&Cone::contains, const_),
            R"doc(
                Check if the cone contains a segment.

                Args:
                    segment (Segment): The segment to check.
            
                Returns:
                    bool: True if the cone contains the segment, False otherwise.

                Example:
                    >>> cone = Cone(Point(0.0, 0.0, 0.0), np.array([0.0, 0.0, 1.0]), Angle.degrees(30.0))
                    >>> cone.contains(Segment(Point(0.1, 0.1, 1.0), Point(0.2, 0.2, 1.0)))  # True for segment inside cone
            )doc",
            arg("segment")
        )
        .def(
            "contains",
            overload_cast<const Ray&>(&Cone::contains, const_),
            R"doc(
                Check if the cone contains a ray.

                Args:
                    ray (Ray): The ray to check.

                Returns:
                    bool: True if the cone contains the ray, False otherwise.

                Example:
                    >>> cone = Cone(Point(0.0, 0.0, 0.0), np.array([0.0, 0.0, 1.0]), Angle.degrees(30.0))
                    >>> cone.contains(Ray(Point(0.1, 0.1, 1.0), np.array([0.0, 0.0, 1.0])))  # True for ray inside cone
            )doc",
            arg("ray")
        )
        .def(
            "contains",
            overload_cast<const Sphere&>(&Cone::contains, const_),
            R"doc(
                Check if the cone contains a sphere.

                Args:
                    sphere (Sphere): The sphere to check.

                Returns:
                    bool: True if the cone contains the sphere, False otherwise.

                Example:
                    >>> cone = Cone(Point(0.0, 0.0, 0.0), np.array([0.0, 0.0, 1.0]), Angle.degrees(30.0))
                    >>> cone.contains(Sphere(Point(0.1, 0.1, 1.0), 0.1))  # True for sphere inside cone
            )doc",
            arg("sphere")
        )
        .def(
            "contains",
            overload_cast<const Ellipsoid&>(&Cone::contains, const_),
            R"doc(
                Check if the cone contains an ellipsoid.
                Args:
                    ellipsoid (Ellipsoid): The ellipsoid to check.

                Returns:
                    bool: True if the cone contains the ellipsoid, False otherwise.
                
                Example:
                    >>> cone = Cone(Point(0.0, 0.0, 0.0), np.array([0.0, 0.0, 1.0]), Angle.degrees(30.0))
                    >>> cone.contains(Ellipsoid(Point(0.1, 0.1, 1.0), 0.1, 0.1, 0.1))  # True for ellipsoid inside cone
            )doc",
            arg("ellipsoid")
        )

        .def(
            "get_apex",
            &Cone::getApex,
            R"doc(
                Get the apex (tip) point of the cone.

                Returns:
                    Point: The apex point of the cone.

                Example:
                    >>> cone = Cone(Point(1.0, 2.0, 3.0), np.array([0.0, 0.0, 1.0]), Angle.degrees(30.0))
                    >>> apex = cone.get_apex()  # Point(1.0, 2.0, 3.0)
            )doc"
        )
        .def(
            "get_axis",
            &Cone::getAxis,
            R"doc(
                Get the axis direction vector of the cone.

                Returns:
                    Vector3d: The axis direction vector.

                Example:
                    >>> cone = Cone(Point(0.0, 0.0, 0.0), np.array([0.0, 0.0, 1.0]), Angle.degrees(30.0))
                    >>> axis = cone.get_axis()  # [0.0, 0.0, 1.0]
            )doc"
        )
        .def(
            "get_angle",
            &Cone::getAngle,
            R"doc(
                Get the half-angle of the cone opening.

                Returns:
                    Angle: The half-angle of the cone.

                Example:
                    >>> cone = Cone(Point(0.0, 0.0, 0.0), np.array([0.0, 0.0, 1.0]), Angle.degrees(30.0))
                    >>> angle = cone.get_angle()  # 30 degrees
            )doc"
        )
        .def(
            "get_rays_of_lateral_surface",
            &Cone::getRaysOfLateralSurface,
            R"doc(
                Get rays representing the lateral surface of the cone.

                Args:
                    ray_count (int): Number of rays to generate around the surface.

                Returns:
                    list: Array of Ray objects representing the lateral surface.

                Example:
                    >>> cone = Cone(Point(0.0, 0.0, 0.0), np.array([0.0, 0.0, 1.0]), Angle.degrees(30.0))
                    >>> rays = cone.get_rays_of_lateral_surface(8)
            )doc",
            arg("ray_count") = DEFAULT_RAY_COUNT
        )
        .def(
            "distance_to",
            overload_cast<const Point&>(&Cone::distanceTo, const_),
            R"doc(
                Calculate the distance from the cone to a point.

                Args:
                    point (Point): The point to calculate distance to.

                Returns:
                    float: The minimum distance from the cone surface to the point.

                Example:
                    >>> cone = Cone(Point(0.0, 0.0, 0.0), np.array([0.0, 0.0, 1.0]), Angle.degrees(30.0))
                    >>> distance = cone.distance_to(Point(2.0, 0.0, 0.0))
            )doc",
            arg("point")
        )
        .def(
            "intersection_with",
            overload_cast<const Sphere&, const bool, const Size>(&Cone::intersectionWith, const_),
            R"doc(
                Compute intersection of cone with sphere.

                Args:
                    sphere (Sphere): The sphere to intersect with.
                    only_in_sight (bool): If true, only return intersection points that are in sight.
                    discretization_level (int): The discretization level for the intersection.

                Returns:
                    Intersection: The intersection of the cone with the sphere.

                Example:
                    >>> cone = Cone(Point(0.0, 0.0, 0.0), np.array([0.0, 0.0, 1.0]), Angle.degrees(30.0))
                    >>> sphere = Sphere(Point(2.0, 0.0, 0.0), 1.0)
                    >>> intersection = cone.intersection_with(sphere)
                    >>> intersection.get_point()  # Point(2.0, 0.0, 0.0)
            )doc",
            arg("sphere"),
            arg("only_in_sight") = false,
            arg("discretization_level") = DEFAULT_DISCRETIZATION_LEVEL
        )
        .def(
            "intersection_with",
            overload_cast<const Ellipsoid&, const bool, const Size>(&Cone::intersectionWith, const_),
            R"doc(
                Compute intersection of cone with ellipsoid.

                Args:
                    ellipsoid (Ellipsoid): The ellipsoid to intersect with.
                    only_in_sight (bool): If true, only return intersection points that are in sight.
                    discretization_level (int): The discretization level for the intersection.

                Returns:
                    Intersection: The intersection of the cone with the ellipsoid.

                Example:
                    >>> cone = Cone(Point(0.0, 0.0, 0.0), np.array([0.0, 0.0, 1.0]), Angle.degrees(30.0))
                    >>> ellipsoid = Ellipsoid(Point(2.0, 0.0, 0.0), 1.0, 1.0, 1.0)
                    >>> intersection = cone.intersection_with(ellipsoid)
                    >>> intersection.get_point()  # Point(2.0, 0.0, 0.0)
            )doc",
            arg("ellipsoid"),
            arg("only_in_sight") = false,
            arg("discretization_level") = DEFAULT_DISCRETIZATION_LEVEL
        )
        .def(
            "apply_transformation",
            &Cone::applyTransformation,
            R"doc(
                Apply a transformation to the cone in place.

                Args:
                    transformation (Transformation): The transformation to apply.

                Example:
                    >>> cone = Cone(Point(0.0, 0.0, 0.0), np.array([0.0, 0.0, 1.0]), Angle.degrees(30.0))
                    >>> transformation = Translation([1.0, 2.0, 3.0])
                    >>> cone.apply_transformation(transformation)
            )doc",
            arg("transformation")
        )

        .def_static(
            "undefined",
            &Cone::Undefined,
            R"doc(
                Create an undefined cone.

                Returns:
                    Cone: An undefined cone object.

                Example:
                    >>> undefined_cone = Cone.undefined()
                    >>> undefined_cone.is_defined()  # False
            )doc"
        );
}
