/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Pyramid.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Pyramid(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;
    using ostk::core::type::Size;

    using ostk::mathematics::geometry::d3::Intersection;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Ellipsoid;
    using ostk::mathematics::geometry::d3::object::Line;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Polygon;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::geometry::d3::object::Sphere;
    using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;

    class_<Pyramid, Object>(
        aModule,
        "Pyramid",
        R"doc(
                A pyramid in 3D space.

                A Pyramid is defined by a polygonal base and an apex point, with triangular lateral faces connecting the base edges to the apex.
            )doc"
    )

        .def(
            init<const Polygon&, const Point&>(),
            arg("base"),
            arg("apex"),
            R"doc(
                Construct a pyramid from a base polygon and apex point.

                Args:
                    base (Polygon): The polygonal base of the pyramid.
                    apex (Point): The apex point of the pyramid.
                
                Example:
                    >>> base = Polygon([Point2d(0.0, 0.0), Point2d(1.0, 0.0), Point2d(1.0, 1.0), Point2d(0.0, 1.0)])
                    >>> apex = Point(0.0, 0.0, 1.0)
                    >>> pyramid = Pyramid(base, apex)
            )doc"
        )

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Pyramid>))
        .def("__repr__", &(shiftToString<Pyramid>))

        .def(
            "is_defined",
            &Pyramid::isDefined,
            R"doc(
                Check if the pyramid is defined.

                Returns:
                    bool: True if the pyramid is defined.
                
                Example:
                    >>> base = Polygon([Point2d(0.0, 0.0), Point2d(1.0, 0.0), Point2d(1.0, 1.0), Point2d(0.0, 1.0)])
                    >>> apex = Point(0.0, 0.0, 1.0)
                    >>> pyramid = Pyramid(base, apex)
                    >>> pyramid.is_defined()
            )doc"
        )
        .def(
            "intersects",
            overload_cast<const Ellipsoid&, const Size>(&Pyramid::intersects, const_),
            arg("ellipsoid"),
            arg("discretization_level") = DEFAULT_DISCRETIZATION_LEVEL,
            R"doc(
                Check if the pyramid intersects an ellipsoid.

                Args:
                    ellipsoid (Ellipsoid): The ellipsoid to check intersection with.
                    discretization_level (int): The level of discretization for the check.

                Returns:
                    bool: True if the pyramid intersects the ellipsoid.
            )doc"
        )
        .def(
            "contains",
            overload_cast<const Point&>(&Pyramid::contains, const_),
            arg("point"),
            R"doc(
                Check if the pyramid contains a point.

                Args:
                    point (Point): The point to check.

                Returns:
                    bool: True if the pyramid contains the point.
                
                Example:
                    >>> base = Polygon([Point2d(0.0, 0.0), Point2d(1.0, 0.0), Point2d(1.0, 1.0), Point2d(0.0, 1.0)])
                    >>> apex = Point(0.0, 0.0, 1.0)
                    >>> pyramid = Pyramid(base, apex)
                    >>> pyramid.contains(Point(0.5, 0.5, 0.5))
            )doc"
        )
        .def(
            "contains",
            overload_cast<const PointSet&>(&Pyramid::contains, const_),
            arg("point_set"),
            R"doc(
                Check if the pyramid contains all points in a point set.

                Args:
                    point_set (PointSet): The point set to check.

                Returns:
                    bool: True if the pyramid contains all points.
                
                Example:
                    >>> base = Polygon([Point2d(0.0, 0.0), Point2d(1.0, 0.0), Point2d(1.0, 1.0), Point2d(0.0, 1.0)])
                    >>> apex = Point(0.0, 0.0, 1.0)
                    >>> pyramid = Pyramid(base, apex)
                    >>> pyramid.contains(PointSet([Point(0.5, 0.5, 0.5), Point(0.6, 0.6, 0.6)]))
            )doc"
        )
        .def(
            "contains",
            overload_cast<const Segment&>(&Pyramid::contains, const_),
            arg("segment"),
            R"doc(
                Check if the pyramid contains a segment.

                Args:
                    segment (Segment): The segment to check.

                Returns:
                    bool: True if the pyramid contains the segment.
                
                Example:
                    >>> base = Polygon([Point2d(0.0, 0.0), Point2d(1.0, 0.0), Point2d(1.0, 1.0), Point2d(0.0, 1.0)])
                    >>> apex = Point(0.0, 0.0, 1.0)
                    >>> pyramid = Pyramid(base, apex)
                    >>> pyramid.contains(Segment(Point(0.5, 0.5, 0.5), Point(0.6, 0.6, 0.6)))
            )doc"
        )
        .def(
            "contains",
            overload_cast<const Ellipsoid&>(&Pyramid::contains, const_),
            arg("ellipsoid"),
            R"doc(
                Check if the pyramid contains an ellipsoid.

                Args:
                    ellipsoid (Ellipsoid): The ellipsoid to check.

                Returns:
                    bool: True if the pyramid contains the ellipsoid.
                
                Example:
                    >>> base = Polygon([Point2d(0.0, 0.0), Point2d(1.0, 0.0), Point2d(1.0, 1.0), Point2d(0.0, 1.0)])
                    >>> apex = Point(0.0, 0.0, 1.0)
                    >>> pyramid = Pyramid(base, apex)
                    >>> pyramid.contains(Ellipsoid(Point(0.0, 0.0, 0.0), 1.0, 1.0, 1.0))
            )doc"
        )

        .def(
            "get_base",
            &Pyramid::getBase,
            R"doc(
                Get the base polygon of the pyramid.

                Returns:
                    Polygon: The base polygon.
                
                Example:
                    >>> base = Polygon([Point2d(0.0, 0.0), Point2d(1.0, 0.0), Point2d(1.0, 1.0), Point2d(0.0, 1.0)])
                    >>> apex = Point(0.0, 0.0, 1.0)
                    >>> pyramid = Pyramid(base, apex)
                    >>> pyramid.get_base()
            )doc"
        )
        .def(
            "get_apex",
            &Pyramid::getApex,
            R"doc(
                Get the apex point of the pyramid.

                Returns:
                    Point: The apex point.
                
                Example:
                    >>> base = Polygon([Point2d(0.0, 0.0), Point2d(1.0, 0.0), Point2d(1.0, 1.0), Point2d(0.0, 1.0)])
                    >>> apex = Point(0.0, 0.0, 1.0)
                    >>> pyramid = Pyramid(base, apex)
                    >>> pyramid.get_apex()
            )doc"
        )
        .def(
            "get_lateral_face_count",
            &Pyramid::getLateralFaceCount,
            R"doc(
                Get the number of lateral faces.

                Returns:
                    int: The number of lateral faces.
                
                Example:
                    >>> base = Polygon([Point2d(0.0, 0.0), Point2d(1.0, 0.0), Point2d(1.0, 1.0), Point2d(0.0, 1.0)])
                    >>> apex = Point(0.0, 0.0, 1.0)
                    >>> pyramid = Pyramid(base, apex)
                    >>> pyramid.get_lateral_face_count()
            )doc"
        )
        .def(
            "get_lateral_face_at",
            &Pyramid::getLateralFaceAt,
            arg("index"),
            R"doc(
                Get the lateral face at a given index.

                Args:
                    index (int): The index of the lateral face.

                Returns:
                    Polygon: The lateral face polygon.
                
                Example:
                    >>> base = Polygon([Point2d(0.0, 0.0), Point2d(1.0, 0.0), Point2d(1.0, 1.0), Point2d(0.0, 1.0)])
                    >>> apex = Point(0.0, 0.0, 1.0)
                    >>> pyramid = Pyramid(base, apex)
                    >>> pyramid.get_lateral_face_at(0)
            )doc"
        )
        .def(
            "get_rays_of_lateral_face_at",
            &Pyramid::getRaysOfLateralFaceAt,
            arg("lateral_face_index"),
            arg("ray_count") = 2,
            R"doc(
                Get rays from the apex through a specific lateral face.

                Args:
                    lateral_face_index (int): The index of the lateral face.
                    ray_count (int): The number of rays to generate (default: 2).

                Returns:
                    list[Ray]: Array of rays.
                
                Example:
                    >>> base = Polygon([Point2d(0.0, 0.0), Point2d(1.0, 0.0), Point2d(1.0, 1.0), Point2d(0.0, 1.0)])
                    >>> apex = Point(0.0, 0.0, 1.0)
                    >>> pyramid = Pyramid(base, apex)
                    >>> pyramid.get_rays_of_lateral_face_at(0)
            )doc"
        )
        .def(
            "get_rays_of_lateral_faces",
            &Pyramid::getRaysOfLateralFaces,
            arg("ray_count") = 0,
            R"doc(
                Get rays from the apex through all lateral faces.

                Args:
                    ray_count (int, optional): The number of rays per face. Defaults to 0.

                Returns:
                    list[Ray]: Array of rays.
                
                Example:
                    >>> base = Polygon([Point2d(0.0, 0.0), Point2d(1.0, 0.0), Point2d(1.0, 1.0), Point2d(0.0, 1.0)])
                    >>> apex = Point(0.0, 0.0, 1.0)
                    >>> pyramid = Pyramid(base, apex)
                    >>> pyramid.get_rays_of_lateral_faces(ray_count=1)
            )doc"
        )
        .def(
            "intersection_with",
            overload_cast<const Sphere&, const bool, const Size>(&Pyramid::intersectionWith, const_),
            arg("sphere"),
            arg("only_in_sight") = DEFAULT_ONLY_IN_SIGHT,
            arg("discretization_level") = DEFAULT_DISCRETIZATION_LEVEL,
            R"doc(
                Compute the intersection of the pyramid with a sphere.

                Args:
                    sphere (Sphere): The sphere to intersect with.
                    only_in_sight (bool): Only compute intersection in sight of the apex.
                    discretization_level (int): The level of discretization for the computation.

                Returns:
                    Intersection: The intersection result.
                
                Example:
                    >>> base = Polygon([Point2d(0.0, 0.0), Point2d(1.0, 0.0), Point2d(1.0, 1.0), Point2d(0.0, 1.0)])
                    >>> apex = Point(0.0, 0.0, 1.0)
                    >>> pyramid = Pyramid(base, apex)
                    >>> pyramid.intersection_with(Sphere(Point(0.0, 0.0, 0.0), 1.0))
            )doc"
        )
        .def(
            "intersection_with",
            overload_cast<const Ellipsoid&, const bool, const Size>(&Pyramid::intersectionWith, const_),
            arg("ellipsoid"),
            arg("only_in_sight") = DEFAULT_ONLY_IN_SIGHT,
            arg("discretization_level") = DEFAULT_DISCRETIZATION_LEVEL,
            R"doc(
                Compute the intersection of the pyramid with an ellipsoid.

                Args:
                    ellipsoid (Ellipsoid): The ellipsoid to intersect with.
                    only_in_sight (bool): Only compute intersection in sight of the apex.
                    discretization_level (int): The level of discretization for the computation.

                Returns:
                    Intersection: The intersection result.
                
                Example:
                    >>> base = Polygon([Point2d(0.0, 0.0), Point2d(1.0, 0.0), Point2d(1.0, 1.0), Point2d(0.0, 1.0)])
                    >>> apex = Point(0.0, 0.0, 1.0)
                    >>> pyramid = Pyramid(base, apex)
                    >>> pyramid.intersection_with(Ellipsoid(Point(0.0, 0.0, 0.0), 1.0, 1.0, 1.0))
            )doc"
        )
        .def(
            "apply_transformation",
            &Pyramid::applyTransformation,
            arg("transformation"),
            R"doc(
                Apply a transformation to the pyramid.

                Args:
                    transformation (Transformation): The transformation to apply.
                
                Example:
                    >>> base = Polygon([Point2d(0.0, 0.0), Point2d(1.0, 0.0), Point2d(1.0, 1.0), Point2d(0.0, 1.0)])
                    >>> apex = Point(0.0, 0.0, 1.0)
                    >>> pyramid = Pyramid(base, apex)
                    >>> transformation = Transformation.identity()
                    >>> pyramid.apply_transformation(transformation)
            )doc"
        )

        .def_static(
            "undefined",
            &Pyramid::Undefined,
            R"doc(
                Create an undefined pyramid.

                Returns:
                    Pyramid: An undefined pyramid.
                
                Example:
                    >>> undefined_pyramid = Pyramid.undefined()
                    >>> undefined_pyramid.is_defined()  # False
            )doc"
        )

        ;
}
