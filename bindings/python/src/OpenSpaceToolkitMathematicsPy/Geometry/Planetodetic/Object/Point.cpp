/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/Angle.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/Planetodetic/Object/Point.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_Planetodetic_Object_Point(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::String;

    using ostk::mathematics::geometry::Angle;
    using ostk::mathematics::geometry::planetodetic::Object;
    using ostk::mathematics::geometry::planetodetic::object::Point;

    class_<Point, Object>(aModule, "Point")

        .def(
            init<const Angle&, const Angle&>(),
            R"doc(
                Create a planetodetic point with specified latitude and longitude.

                Args:
                    latitude (Angle): The latitude angle (must be in [-90, 90] degrees).
                    longitude (Angle): The longitude angle (will be normalized to [-180, 180) degrees).

                Example:
                    >>> from ostk.mathematics.geometry import Angle
                    >>> from ostk.mathematics.geometry.planetodetic.object import Point
                    >>> point = Point(Angle.degrees(45.0), Angle.degrees(-122.0))
                    >>> point.get_latitude().in_degrees()  # 45.0
                    >>> point.get_longitude().in_degrees()  # -122.0
            )doc",
            arg("latitude"),
            arg("longitude")
        )

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<Point>))
        .def(
            "__repr__",
            +[](const Point& aPoint) -> std::string
            {
                return aPoint.toString();
            }
        )

        .def(
            "is_defined",
            &Point::isDefined,
            R"doc(
                Check if the point is defined.

                Returns:
                    bool: True if the point is defined, False otherwise.

                Example:
                    >>> point = Point(Angle.degrees(45.0), Angle.degrees(-122.0))
                    >>> point.is_defined()  # True
            )doc"
        )

        .def(
            "is_collinear",
            &Point::isCollinear,
            R"doc(
                Check if three points are collinear (lie on the same great circle).

                Args:
                    point_1 (Point): The second point.
                    point_2 (Point): The third point.

                Returns:
                    bool: True if the three points are collinear, False otherwise.

                Example:
                    >>> p1 = Point(Angle.degrees(0.0), Angle.degrees(0.0))
                    >>> p2 = Point(Angle.degrees(0.0), Angle.degrees(90.0))
                    >>> p3 = Point(Angle.degrees(0.0), Angle.degrees(180.0))
                    >>> p1.is_collinear(p2, p3)  # True (all on equator)
            )doc",
            arg("point_1"),
            arg("point_2")
        )

        .def(
            "get_latitude",
            &Point::getLatitude,
            R"doc(
                Get the latitude of the point.

                Returns:
                    Angle: The latitude angle.

                Example:
                    >>> point = Point(Angle.degrees(45.0), Angle.degrees(-122.0))
                    >>> lat = point.get_latitude()
                    >>> lat.in_degrees()  # 45.0
            )doc"
        )

        .def(
            "get_longitude",
            &Point::getLongitude,
            R"doc(
                Get the longitude of the point.

                Returns:
                    Angle: The longitude angle.

                Example:
                    >>> point = Point(Angle.degrees(45.0), Angle.degrees(-122.0))
                    >>> lon = point.get_longitude()
                    >>> lon.in_degrees()  # -122.0
            )doc"
        )

        .def_static(
            "undefined",
            &Point::Undefined,
            R"doc(
                Create an undefined point.

                Returns:
                    Point: An undefined point.

                Example:
                    >>> point = Point.undefined()
                    >>> point.is_defined()  # False
            )doc"
        )

        ;
}
