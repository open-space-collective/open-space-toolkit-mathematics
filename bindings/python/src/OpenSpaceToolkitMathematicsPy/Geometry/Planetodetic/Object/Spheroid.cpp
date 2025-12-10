/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/Planetodetic/Object/Spheroid.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_Planetodetic_Object_Spheroid(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;
    using ostk::core::type::String;

    using ostk::mathematics::geometry::planetodetic::Object;
    using ostk::mathematics::geometry::planetodetic::object::Spheroid;

    class_<Spheroid, Object>(aModule, "Spheroid")

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Spheroid>))
        .def(
            "__repr__",
            +[](const Spheroid& aSpheroid) -> std::string
            {
                return aSpheroid.toString();
            }
        )

        .def(
            "is_defined",
            &Spheroid::isDefined,
            R"doc(
                Check if the spheroid is defined.

                Returns:
                    bool: True if the spheroid is defined, False otherwise.

                Example:
                    >>> spheroid = Spheroid.from_equatorial_radius_and_flattening(6378137.0, 1.0 / 298.257223563)
                    >>> spheroid.is_defined()  # True
            )doc"
        )

        .def(
            "get_equatorial_radius",
            &Spheroid::getEquatorialRadius,
            R"doc(
                Get the equatorial radius of the spheroid.

                Returns:
                    float: The equatorial radius (a).

                Example:
                    >>> spheroid = Spheroid.from_equatorial_radius_and_flattening(6378137.0, 1.0 / 298.257223563)
                    >>> spheroid.get_equatorial_radius()  # 6378137.0
            )doc"
        )

        .def(
            "get_polar_radius",
            &Spheroid::getPolarRadius,
            R"doc(
                Get the polar radius of the spheroid.

                The polar radius is computed from: c = a * (1 - f)

                Returns:
                    float: The polar radius (c).

                Example:
                    >>> spheroid = Spheroid.from_equatorial_radius_and_flattening(6378137.0, 1.0 / 298.257223563)
                    >>> spheroid.get_polar_radius()  # ~6356752.3142
            )doc"
        )

        .def(
            "get_flattening",
            &Spheroid::getFlattening,
            R"doc(
                Get the flattening of the spheroid.

                Returns:
                    float: The flattening (f).

                Example:
                    >>> spheroid = Spheroid.from_equatorial_radius_and_flattening(6378137.0, 1.0 / 298.257223563)
                    >>> spheroid.get_flattening()  # ~0.00335281
            )doc"
        )

        .def(
            "get_eccentricity",
            &Spheroid::getEccentricity,
            R"doc(
                Get the eccentricity of the spheroid.

                The eccentricity is computed from: e = sqrt(2*f - f^2)

                Returns:
                    float: The eccentricity (e).

                Example:
                    >>> spheroid = Spheroid.from_equatorial_radius_and_flattening(6378137.0, 1.0 / 298.257223563)
                    >>> spheroid.get_eccentricity()  # ~0.0818191908
            )doc"
        )

        .def(
            "is_oblate",
            &Spheroid::isOblate,
            R"doc(
                Check if the spheroid is oblate (f > 0, equatorial radius > polar radius).

                Returns:
                    bool: True if the spheroid is oblate, False otherwise.

                Example:
                    >>> spheroid = Spheroid.from_equatorial_radius_and_flattening(6378137.0, 1.0 / 298.257223563)
                    >>> spheroid.is_oblate()  # True
            )doc"
        )

        .def(
            "is_prolate",
            &Spheroid::isProlate,
            R"doc(
                Check if the spheroid is prolate (f < 0, equatorial radius < polar radius).

                Returns:
                    bool: True if the spheroid is prolate, False otherwise.

                Example:
                    >>> spheroid = Spheroid.from_equatorial_radius_and_flattening(6378137.0, -0.1)
                    >>> spheroid.is_prolate()  # True
            )doc"
        )

        .def(
            "is_sphere",
            &Spheroid::isSphere,
            R"doc(
                Check if the spheroid is a sphere (f = 0, equatorial radius = polar radius).

                Returns:
                    bool: True if the spheroid is a sphere, False otherwise.

                Example:
                    >>> spheroid = Spheroid.sphere(6378137.0)
                    >>> spheroid.is_sphere()  # True
            )doc"
        )

        .def_static(
            "from_equatorial_radius_and_flattening",
            &Spheroid::FromEquatorialRadiusAndFlattening,
            R"doc(
                Create a spheroid from equatorial radius and flattening.

                Args:
                    equatorial_radius (float): The equatorial radius (a), must be > 0.
                    flattening (float): The flattening (f = (a - c) / a), must be > -1.0.

                Returns:
                    Spheroid: The constructed spheroid.

                Example:
                    >>> # WGS84 ellipsoid
                    >>> spheroid = Spheroid.from_equatorial_radius_and_flattening(6378137.0, 1.0 / 298.257223563)
            )doc",
            arg("equatorial_radius"),
            arg("flattening")
        )

        .def_static(
            "undefined",
            &Spheroid::Undefined,
            R"doc(
                Create an undefined spheroid.

                Returns:
                    Spheroid: An undefined spheroid.

                Example:
                    >>> spheroid = Spheroid.undefined()
                    >>> spheroid.is_defined()  # False
            )doc"
        )

        .def_static(
            "sphere",
            &Spheroid::Sphere,
            R"doc(
                Create a spherical spheroid (f = 0).

                Args:
                    radius (float): The radius of the sphere.

                Returns:
                    Spheroid: A spherical spheroid.

                Example:
                    >>> spheroid = Spheroid.sphere(6378137.0)
                    >>> spheroid.is_sphere()  # True
                    >>> spheroid.get_equatorial_radius()  # 6378137.0
                    >>> spheroid.get_polar_radius()  # 6378137.0
            )doc",
            arg("radius")
        )

        .def_static(
            "wgs84",
            &Spheroid::WGS84,
            R"doc(
                Create a WGS84 spheroid.

                Returns:
                    Spheroid: The WGS84 spheroid (a = 6378137.0 m, f = 1/298.257223563).

                Example:
                    >>> spheroid = Spheroid.wgs84()
                    >>> spheroid.get_equatorial_radius()  # 6378137.0
                    >>> spheroid.get_flattening()  # ~0.00335281
            )doc"
        )

        ;
}
