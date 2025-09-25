/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/Point.hpp>

using ostk::core::container::Array;
using ostk::mathematics::geometry::d2::object::Point;
using ostk::mathematics::object::VectorXd;

void set_point_array(const Array<Point>& anArray)
{
    (void)anArray;
}

void set_point_2_array(const Array<Array<Point>>& anArray)
{
    (void)anArray;
}

inline void OpenSpaceToolkitMathematicsPy_Geometry_2D_Object_Point(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Integer;
    using ostk::core::type::Real;

    using ostk::mathematics::geometry::d2::Object;
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::object::Vector2d;

    class_<Point, Object>(aModule, "Point")

        .def(
            init<const Real&, const Real&>(),
            R"doc(
                Create a 2D point with specified coordinates.

                Args:
                    x (float): The x-coordinate.
                    y (float): The y-coordinate.

                Example:
                    >>> point = Point(1.0, 2.0)
                    >>> point.x()  # 1.0
                    >>> point.y()  # 2.0
            )doc",
            arg("x"),
            arg("y")
        )

        .def(self == self)
        .def(self != self)

        .def(self - self)

        .def(self + Vector2d())
        .def(self - Vector2d())

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
                    >>> point = Point(1.0, 2.0)
                    >>> point.is_defined()  # True
            )doc"
        )
        .def(
            "is_near",
            &Point::isNear,
            R"doc(
                Check if this point is near another point within a tolerance.

                Args:
                    point (Point): The point to compare with.
                    tolerance (float): The tolerance for comparison.

                Returns:
                    bool: True if points are within tolerance, False otherwise.

                Example:
                    >>> point1 = Point(1.0, 2.0)
                    >>> point2 = Point(1.1, 2.1)
                    >>> point1.is_near(point2, 0.2)  # True
            )doc",
            arg("point"),
            arg("tolerance")
        )

        .def(
            "x",
            &Point::x,
            R"doc(
                Get the x-coordinate of the point.

                Returns:
                    float: The x-coordinate.

                Example:
                    >>> point = Point(1.0, 2.0)
                    >>> point.x()  # 1.0
            )doc",
            return_value_policy::reference
        )
        .def(
            "y",
            &Point::y,
            R"doc(
                Get the y-coordinate of the point.

                Returns:
                    float: The y-coordinate.

                Example:
                    >>> point = Point(1.0, 2.0)
                    >>> point.y()  # 2.0
            )doc",
            return_value_policy::reference
        )
        .def(
            "as_vector",
            &Point::asVector,
            R"doc(
                Convert the point to a 2D vector.

                Returns:
                    Vector2d: The point as a 2D vector.

                Example:
                    >>> point = Point(1.0, 2.0)
                    >>> vector = point.as_vector()  # Vector2d([1.0, 2.0])
            )doc"
        )
        .def(
            "distance_to",
            &Point::distanceTo,
            R"doc(
                Calculate the distance to another point.

                Args:
                    point (Point): The other point.

                Returns:
                    float: The distance between the points.

                Example:
                    >>> point1 = Point(0.0, 0.0)
                    >>> point2 = Point(3.0, 4.0)
                    >>> point1.distance_to(point2)  # 5.0
            )doc",
            arg("point")
        )
        .def(
            "to_string",
            &Point::toString,
            R"doc(
                Convert the point to a string representation.

                Args:
                    format (Object.Format, optional): The output format. Defaults to Standard.
                    precision (int, optional): The precision for floating point numbers. Defaults to undefined.

                Returns:
                    str: String representation of the point.

                Example:
                    >>> point = Point(1.0, 2.0)
                    >>> point.to_string()  # "(1.0, 2.0)"
            )doc",
            arg("format") = Object::Format::Standard,
            arg("precision") = Integer::Undefined()
        )
        .def(
            "apply_transformation",
            &Point::applyTransformation,
            R"doc(
                Apply a transformation to the point.

                Args:
                    transformation (Transformation): The transformation to apply.

                Returns:
                    Point: The transformed point.

                Example:
                    >>> point = Point(1.0, 2.0)
                    >>> transformation = Translation([1.0, 1.0])
                    >>> transformed = point.apply_transformation(transformation)
            )doc",
            arg("transformation")
        )

        .def_static(
            "undefined",
            &Point::Undefined,
            R"doc(
                Create an undefined point.

                Returns:
                    Point: An undefined point.

                Example:
                    >>> undefined_point = Point.undefined()
                    >>> undefined_point.is_defined()  # False
            )doc"
        )
        .def_static(
            "origin",
            &Point::Origin,
            R"doc(
                Create a point at the origin (0, 0).

                Returns:
                    Point: A point at coordinates (0, 0).

                Example:
                    >>> origin = Point.origin()
                    >>> origin.x()  # 0.0
                    >>> origin.y()  # 0.0
            )doc"
        )
        .def_static(
            "vector",
            &Point::Vector,
            R"doc(
                Create a point from a 2D vector.

                Args:
                    vector (Vector2d): The vector to convert to a point.

                Returns:
                    Point: A point with coordinates from the vector.

                Example:
                    >>> vector = Vector2d([1.0, 2.0])
                    >>> point = Point.vector(vector)  # Point(1.0, 2.0)
            )doc",
            arg("vector")
        )

        ;

    aModule.def("set_point_array", overload_cast<const Array<Point>&>(&set_point_array));
    aModule.def("set_point_2_array", overload_cast<const Array<Array<Point>>&>(&set_point_2_array));
}
