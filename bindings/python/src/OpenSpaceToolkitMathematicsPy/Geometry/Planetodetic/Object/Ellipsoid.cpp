/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/Planetodetic/Object/Ellipsoid.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_Planetodetic_Object_Ellipsoid(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;
    using ostk::core::type::String;

    using ostk::mathematics::geometry::planetodetic::Object;
    using ostk::mathematics::geometry::planetodetic::object::Ellipsoid;

    class_<Ellipsoid, Object>(aModule, "Ellipsoid")

        .def(
            init<const Real&, const Real&, const Real&>(),
            arg("equatorial_radius_a"),
            arg("equatorial_radius_b"),
            arg("polar_radius"),
            R"doc(
                Create an ellipsoid.

                Args:
                    equatorial_radius_a (float): First equatorial radius (a).
                    equatorial_radius_b (float): Second equatorial radius (b).
                    polar_radius (float): Polar radius (c).

                Example:
                    >>> ellipsoid = Ellipsoid(6378137.0, 6378137.0, 6356752.3142)
            )doc"
        )

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Ellipsoid>))
        .def(
            "__repr__",
            +[](const Ellipsoid& anEllipsoid) -> std::string
            {
                return anEllipsoid.toString();
            }
        )

        .def(
            "is_defined",
            &Ellipsoid::isDefined,
            R"doc(
                Check if the ellipsoid is defined.

                Returns:
                    bool: True if the ellipsoid is defined, False otherwise.

                Example:
                    >>> ellipsoid = Ellipsoid(6378137.0, 6378137.0, 6356752.3142)
                    >>> ellipsoid.is_defined()  # True
            )doc"
        )

        .def(
            "get_equatorial_radius_a",
            &Ellipsoid::getEquatorialRadiusA,
            R"doc(
                Get the first equatorial radius of the ellipsoid.

                Returns:
                    float: The first equatorial radius (a).

                Example:
                    >>> ellipsoid = Ellipsoid(6378137.0, 6378137.0, 6356752.3142)
                    >>> ellipsoid.get_equatorial_radius_a()  # 6378137.0
            )doc"
        )

        .def(
            "get_equatorial_radius_b",
            &Ellipsoid::getEquatorialRadiusB,
            R"doc(
                Get the second equatorial radius of the ellipsoid.

                Returns:
                    float: The second equatorial radius (b).

                Example:
                    >>> ellipsoid = Ellipsoid(6378137.0, 6378137.0, 6356752.3142)
                    >>> ellipsoid.get_equatorial_radius_b()  # 6378137.0
            )doc"
        )

        .def(
            "get_polar_radius",
            &Ellipsoid::getPolarRadius,
            R"doc(
                Get the polar radius of the ellipsoid.

                Returns:
                    float: The polar radius (c).

                Example:
                    >>> ellipsoid = Ellipsoid(6378137.0, 6378137.0, 6356752.3142)
                    >>> ellipsoid.get_polar_radius()  # 6356752.3142
            )doc"
        )

        .def_static(
            "undefined",
            &Ellipsoid::Undefined,
            R"doc(
                Create an undefined ellipsoid.

                Returns:
                    Ellipsoid: An undefined ellipsoid.

                Example:
                    >>> ellipsoid = Ellipsoid.undefined()
                    >>> ellipsoid.is_defined()  # False
            )doc"
        )

        .def_static(
            "sphere",
            &Ellipsoid::Sphere,
            R"doc(
                Create a spherical ellipsoid (a = b = c).

                Args:
                    radius (float): The radius of the sphere.

                Returns:
                    Ellipsoid: A spherical ellipsoid.

                Example:
                    >>> ellipsoid = Ellipsoid.sphere(6378137.0)
                    >>> ellipsoid.get_equatorial_radius_a()  # 6378137.0
                    >>> ellipsoid.get_equatorial_radius_b()  # 6378137.0
                    >>> ellipsoid.get_polar_radius()  # 6378137.0
            )doc",
            arg("radius")
        )

        .def_static(
            "spheroid",
            &Ellipsoid::Spheroid,
            R"doc(
                Create an ellipsoid of revolution (spheroid) around the polar axis (a = b).

                Only 2 out of 3 parameters should be defined. Providing all 3 or less than 2 will raise an error.

                Args:
                    equatorial_radius (float, optional): The equatorial radius (a).
                    flattening (float, optional): The flattening (f = (a - c) / a).
                    polar_radius (float, optional): The polar radius (c).

                Returns:
                    Ellipsoid: A spheroid (axisymmetric ellipsoid).

                Example:
                    >>> # Using equatorial radius and flattening
                    >>> ellipsoid = Ellipsoid.spheroid(equatorial_radius=6378137.0, flattening=1.0/298.257223563)
                    >>> # Using equatorial radius and polar radius
                    >>> ellipsoid = Ellipsoid.spheroid(equatorial_radius=6378137.0, polar_radius=6356752.3142)
                    >>> # Using polar radius and flattening
                    >>> ellipsoid = Ellipsoid.spheroid(polar_radius=6356752.3142, flattening=1.0/298.257223563)
            )doc",
            arg_v("equatorial_radius", Real::Undefined(), "Real.undefined()"),
            arg_v("flattening", Real::Undefined(), "Real.undefined()"),
            arg_v("polar_radius", Real::Undefined(), "Real.undefined()")
        )

        .def_static(
            "wgs84",
            &Ellipsoid::WGS84,
            R"doc(
                Create a WGS84 ellipsoid (in meters).

                Returns:
                    Ellipsoid: The WGS84 ellipsoid (a = 6378137.0 m, f = 1/298.257223563).

                Example:
                    >>> ellipsoid = Ellipsoid.wgs84()
                    >>> ellipsoid.get_equatorial_radius_a()  # 6378137.0
                    >>> ellipsoid.get_equatorial_radius_b()  # 6378137.0
            )doc"
        )

        ;
}
