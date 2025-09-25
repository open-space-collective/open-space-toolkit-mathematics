/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Intersection.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/Cuboid.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_Cuboid(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;

    using ostk::mathematics::geometry::d3::Intersection;
    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Cuboid;
    using ostk::mathematics::geometry::d3::object::Line;
    using ostk::mathematics::geometry::d3::object::Plane;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;
    using ostk::mathematics::geometry::d3::object::Pyramid;
    using ostk::mathematics::geometry::d3::object::Ray;
    using ostk::mathematics::geometry::d3::object::Segment;
    using ostk::mathematics::geometry::d3::object::Sphere;
    using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;
    using ostk::mathematics::object::Vector3d;

    //     scope in_Cuboid = class_<Cuboid, Shared<Cuboid>, bases<Object>>("Cuboid", no_init)
    class_<Cuboid, Object>(aModule, "Cuboid")

        .def(
            "__init__",
            [](Cuboid& aCuboid, const Point& aCenter, const pybind11::list& anAxisList, const pybind11::list& anExtent)
            {
                const std::array<Vector3d, 3> axes = {
                    pybind11::cast<Vector3d>(anAxisList[0]),
                    pybind11::cast<Vector3d>(anAxisList[1]),
                    pybind11::cast<Vector3d>(anAxisList[2])
                };
                const std::array<Real, 3> extent = {
                    pybind11::cast<Real>(anExtent[0]),
                    pybind11::cast<Real>(anExtent[1]),
                    pybind11::cast<Real>(anExtent[2])
                };

                new (&aCuboid) Cuboid(aCenter, axes, extent);
                // Default policy is unique pointer
                // return std::make_shared<Cuboid>(aCenter, axes, extent) ;
                // return std::shared_ptr<Cuboid>(new Cuboid(aCenter, axes, extent)) ;  // Check if that one provides
                // the correct behavior
            },
            R"doc(
                Create a 3D cuboid with specified center, axes, and extents.

                Args:
                    center (Point): The center point of the cuboid.
                    axes (list): List of three Vector3d objects defining the cuboid's orientation.
                    extent (list): List of three float values defining the half-extents along each axis.

                Example:
                    >>> center = Point(0.0, 0.0, 0.0)
                    >>> axes = [Vector3d([1.0, 0.0, 0.0]), Vector3d([0.0, 1.0, 0.0]), Vector3d([0.0, 0.0, 1.0])]
                    >>> extent = [1.0, 2.0, 3.0]
                    >>> cuboid = Cuboid(center, axes, extent)
            )doc",
            arg("center"),
            arg("axes"),
            arg("extent")
        )

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Cuboid>))
        .def("__repr__", &(shiftToString<Cuboid>))

        .def(
            "is_defined",
            &Cuboid::isDefined,
            R"doc(
                Check if the cuboid is defined.

                Returns:
                    bool: True if the cuboid is defined, False otherwise.

                Example:
                    >>> cuboid = Cuboid(center, axes, extent)
                    >>> cuboid.is_defined()  # True
            )doc"
        )
        .def(
            "is_near",
            &Cuboid::isNear,
            R"doc(
                Check if this cuboid is near another cuboid.

                Args:
                    cuboid (Cuboid): The cuboid to compare with.
                    tolerance (float): The tolerance for comparison.

                Returns:
                    bool: True if cuboids are within tolerance, False otherwise.

                Example:
                    >>> cuboid1 = Cuboid(center1, axes1, extent1)
                    >>> cuboid2 = Cuboid(center2, axes2, extent2)
                    >>> cuboid1.is_near(cuboid2, 1e-6)
            )doc"
        )

        .def("intersects", overload_cast<const Point&>(&Cuboid::intersects, const_), arg("point"))
        .def("intersects", overload_cast<const PointSet&>(&Cuboid::intersects, const_), arg("point_set"))
        .def("intersects", overload_cast<const Line&>(&Cuboid::intersects, const_), arg("line"))
        .def("intersects", overload_cast<const Cuboid&>(&Cuboid::intersects, const_), arg("cuboid"))

        .def(
            "get_center",
            &Cuboid::getCenter,
            R"doc(
                Get the center point of the cuboid.

                Returns:
                    Point: The center point of the cuboid.

                Example:
                    >>> cuboid = Cuboid(Point(1.0, 2.0, 3.0), axes, extent)
                    >>> center = cuboid.get_center()  # Point(1.0, 2.0, 3.0)
            )doc"
        )
        .def(
            "get_first_axis",
            &Cuboid::getFirstAxis,
            R"doc(
                Get the first axis vector of the cuboid.

                Returns:
                    Vector3d: The first axis direction vector.

                Example:
                    >>> cuboid = Cuboid(center, axes, extent)
                    >>> first_axis = cuboid.get_first_axis()
            )doc"
        )
        .def(
            "get_second_axis",
            &Cuboid::getSecondAxis,
            R"doc(
                Get the second axis vector of the cuboid.

                Returns:
                    Vector3d: The second axis direction vector.

                Example:
                    >>> cuboid = Cuboid(center, axes, extent)
                    >>> second_axis = cuboid.get_second_axis()
            )doc"
        )
        .def(
            "get_third_axis",
            &Cuboid::getThirdAxis,
            R"doc(
                Get the third axis vector of the cuboid.

                Returns:
                    Vector3d: The third axis direction vector.

                Example:
                    >>> cuboid = Cuboid(center, axes, extent)
                    >>> third_axis = cuboid.get_third_axis()
            )doc"
        )
        .def(
            "get_first_extent",
            &Cuboid::getFirstExtent,
            R"doc(
                Get the first half-extent of the cuboid.

                Returns:
                    float: The half-extent along the first axis.

                Example:
                    >>> cuboid = Cuboid(center, axes, [1.0, 2.0, 3.0])
                    >>> first_extent = cuboid.get_first_extent()  # 1.0
            )doc"
        )
        .def(
            "get_second_extent",
            &Cuboid::getSecondExtent,
            R"doc(
                Get the second half-extent of the cuboid.

                Returns:
                    float: The half-extent along the second axis.

                Example:
                    >>> cuboid = Cuboid(center, axes, [1.0, 2.0, 3.0])
                    >>> second_extent = cuboid.get_second_extent()  # 2.0
            )doc"
        )
        .def(
            "get_third_extent",
            &Cuboid::getThirdExtent,
            R"doc(
                Get the third half-extent of the cuboid.

                Returns:
                    float: The half-extent along the third axis.

                Example:
                    >>> cuboid = Cuboid(center, axes, [1.0, 2.0, 3.0])
                    >>> third_extent = cuboid.get_third_extent()  # 3.0
            )doc"
        )
        .def(
            "get_vertices",
            &Cuboid::getVertices,
            R"doc(
                Get all vertices of the cuboid.

                Returns:
                    list: Array of Point objects representing the 8 vertices of the cuboid.

                Example:
                    >>> cuboid = Cuboid(center, axes, extent)
                    >>> vertices = cuboid.get_vertices()  # 8 corner points
            )doc"
        )
        .def("apply_transformation", &Cuboid::applyTransformation, arg("transformation"))

        .def_static(
            "undefined",
            &Cuboid::Undefined,
            R"doc(
                Create an undefined cuboid.

                Returns:
                    Cuboid: An undefined cuboid object.

                Example:
                    >>> undefined_cuboid = Cuboid.undefined()
                    >>> undefined_cuboid.is_defined()  # False
            )doc"
        )
        .def_static(
            "cube",
            &Cuboid::Cube,
            R"doc(
                Create a cube (equal extents along all axes) centered at a point.

                Args:
                    center (Point): The center point of the cube.
                    extent (float): The half-extent along all axes.

                Returns:
                    Cuboid: A cuboid representing a cube.

                Example:
                    >>> center = Point(0.0, 0.0, 0.0)
                    >>> cube = Cuboid.cube(center, 1.0)  # 2x2x2 cube
            )doc",
            arg("center"),
            arg("extent")
        )

        ;
}
