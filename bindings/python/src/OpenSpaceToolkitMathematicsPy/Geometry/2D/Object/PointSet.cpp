/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/2D/Object/PointSet.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_2D_Object_PointSet(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::container::Array;
    using ostk::core::type::Integer;

    using ostk::mathematics::geometry::d2::Object;
    using ostk::mathematics::geometry::d2::object::Point;
    using ostk::mathematics::geometry::d2::object::PointSet;

    class_<PointSet, Object>(aModule, "PointSet")

        .def(
            init<const Array<Point>&>(),
            R"doc(
                Create a 2D point set from an array of points.

                Args:
                    points (list[Point]): List of Point objects to include in the set.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0), Point(2.0, 2.0)]
                    >>> point_set = PointSet(points)
            )doc",
            arg("points")
        )

        .def(self == self)
        .def(self != self)

        .def("__str__", &(shiftToString<PointSet>))
        .def("__repr__", &(shiftToString<PointSet>))

        .def(
            "is_defined",
            &PointSet::isDefined,
            R"doc(
                Check if the point set is defined.

                Returns:
                    bool: True if the point set is defined, False otherwise.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0)]
                    >>> point_set = PointSet(points)
                    >>> point_set.is_defined()  # True
            )doc"
        )
        .def(
            "is_empty",
            &PointSet::isEmpty,
            R"doc(
                Check if the point set is empty (contains no points).

                Returns:
                    bool: True if the point set is empty, False otherwise.

                Example:
                    >>> empty_set = PointSet.empty()
                    >>> empty_set.is_empty()  # True
                    >>> points = [Point(0.0, 0.0)]
                    >>> point_set = PointSet(points)
                    >>> point_set.is_empty()  # False
            )doc"
        )
        .def(
            "is_near",
            &PointSet::isNear,
            R"doc(
                Check if this point set is near another point set within tolerance.

                Args:
                    point_set (PointSet): The point set to compare with.
                    tolerance (float): The tolerance for comparison.

                Returns:
                    bool: True if point sets are within tolerance, False otherwise.

                Example:
                    >>> points1 = [Point(0.0, 0.0), Point(1.0, 1.0)]
                    >>> points2 = [Point(0.1, 0.1), Point(1.1, 1.1)]
                    >>> set1 = PointSet(points1)
                    >>> set2 = PointSet(points2)
                    >>> set1.is_near(set2, 0.2)  # True
            )doc",
            arg("point_set"),
            arg("tolerance")
        )

        .def(
            "get_size",
            &PointSet::getSize,
            R"doc(
                Get the number of points in the set.

                Returns:
                    int: The number of points in the set.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0), Point(2.0, 2.0)]
                    >>> point_set = PointSet(points)
                    >>> point_set.get_size()  # 3
            )doc"
        )
        .def(
            "distance_to",
            overload_cast<const Point&>(&PointSet::distanceTo, const_),
            R"doc(
                Calculate the distance from the point set to a point.

                Args:
                    point (Point): The point to calculate distance to.

                Returns:
                    float: The minimum distance from any point in the set to the given point.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(2.0, 0.0)]
                    >>> point_set = PointSet(points)
                    >>> distance = point_set.distance_to(Point(1.0, 0.0))  # 1.0
            )doc",
            arg("point")
        )
        .def(
            "get_point_closest_to",
            &PointSet::getPointClosestTo,
            R"doc(
                Get the point in the set that is closest to a given point.

                Args:
                    point (Point): The reference point.

                Returns:
                    Point: The closest point in the set to the given point.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(2.0, 0.0), Point(4.0, 0.0)]
                    >>> point_set = PointSet(points)
                    >>> closest = point_set.get_point_closest_to(Point(1.5, 0.0))  # Point(2.0, 0.0)
            )doc",
            arg("point")
        )
        .def(
            "to_string",
            &PointSet::toString,
            R"doc(
                Convert the point set to a string representation.

                Args:
                    format (Object.Format, optional): The output format. Defaults to Standard.
                    precision (int, optional): The precision for floating point numbers. Defaults to undefined.

                Returns:
                    str: String representation of the point set.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0)]
                    >>> point_set = PointSet(points)
                    >>> point_set.to_string()
            )doc",
            arg("format") = Object::Format::Standard,
            arg("precision") = Integer::Undefined()
        )
        .def(
            "apply_transformation",
            &PointSet::applyTransformation,
            R"doc(
                Apply a transformation to all points in the set.

                Args:
                    transformation (Transformation): The 2D transformation to apply.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0)]
                    >>> point_set = PointSet(points)
                    >>> transformation = Translation([1.0, 1.0])
                    >>> point_set.apply_transformation(transformation)
            )doc",
            arg("transformation")
        )

        .def_static(
            "empty",
            &PointSet::Empty,
            R"doc(
                Create an empty point set.

                Returns:
                    PointSet: An empty point set containing no points.

                Example:
                    >>> empty_set = PointSet.empty()
                    >>> empty_set.is_empty()  # True
                    >>> empty_set.get_size()  # 0
            )doc"
        )

        .def(
            "__len__",
            &PointSet::getSize,
            R"doc(
                Get the number of points in the set (Python len() function).

                Returns:
                    int: The number of points in the set.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0)]
                    >>> point_set = PointSet(points)
                    >>> len(point_set)  # 2
            )doc"
        )
        .def(
            "__iter__",
            [](const PointSet& aPointSet)
            {
                return make_iterator(aPointSet.begin(), aPointSet.end());
            },
            R"doc(
                Make the point set iterable (Python for loop support).

                Returns:
                    iterator: An iterator over the points in the set.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0)]
                    >>> point_set = PointSet(points)
                    >>> for point in point_set:
                    ...     print(point)
            )doc",
            keep_alive<0, 1>()
        )  // Keep vector alive while iterator is used
        .def(
            "__getitem__",
            [](const PointSet& aPointSet, size_t index) -> Point
            {
                if (index >= aPointSet.getSize())
                {
                    throw std::out_of_range("Index out of range");
                }
                auto it = aPointSet.begin();
                std::advance(it, index);
                return *it;
            },
            R"doc(
                Access a point by index (Python indexing support).

                Args:
                    index (int): The index of the point to access.

                Returns:
                    Point: The point at the specified index.

                Raises:
                    IndexError: If the index is out of range.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0)]
                    >>> point_set = PointSet(points)
                    >>> first_point = point_set[0]  # Point(0.0, 0.0)
            )doc"
        )

        ;
}
