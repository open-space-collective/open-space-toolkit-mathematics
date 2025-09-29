/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Object/PointSet.hpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Object_PointSet(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::container::Array;

    using ostk::mathematics::geometry::d3::Object;
    using ostk::mathematics::geometry::d3::object::Point;
    using ostk::mathematics::geometry::d3::object::PointSet;

    class_<PointSet, Object>(
        aModule,
        "PointSet",
        R"doc(
                A collection of 3D points.

                A PointSet is an unordered collection of unique points in 3D space.
            )doc"
    )

        .def(
            init<const Array<Point>&>(),
            R"doc(
                Construct a point set from an array of points.

                Args:
                    points (list[Point]): Array of 3D points.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0)]
                    >>> point_set = PointSet(points)
                    >>> point_set.is_defined()  # True
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
                    bool: True if the point set is defined.

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
                Check if the point set is empty.

                Returns:
                    bool: True if the point set contains no points.
            )doc"
        )
        .def(
            "is_near",
            &PointSet::isNear,
            R"doc(
                Check if another point set is near this one within a tolerance.

                Args:
                    point_set (PointSet): The point set to compare against.
                    tolerance (float): The maximum distance for points to be considered near.

                Returns:
                    bool: True if the point sets are near each other.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0)]
                    >>> point_set = PointSet(points)
                    >>> point_set.is_near(PointSet(points), 0.1)  # True
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
                    int: The number of points.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0)]
                    >>> point_set = PointSet(points)
                    >>> point_set.get_size()  # 2
            )doc"
        )
        .def(
            "distance_to",
            overload_cast<const Point&>(&PointSet::distanceTo, const_),
            R"doc(
                Calculate the minimum distance from the point set to a point.

                Args:
                    point (Point): The point to measure distance to.

                Returns:
                    float: The minimum distance to any point in the set.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0)]
                    >>> point_set = PointSet(points)
                    >>> point_set.distance_to(Point(0.5, 0.5))  # 0.5
            )doc",
            arg("point")
        )
        .def(
            "get_point_closest_to",
            &PointSet::getPointClosestTo,
            R"doc(
                Get the point in the set closest to a given point.

                Args:
                    point (Point): The reference point.

                Returns:
                    Point: The closest point in the set.

                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0)]
                    >>> point_set = PointSet(points)
                    >>> point_set.get_point_closest_to(Point(0.5, 0.5))  # Point(0.5, 0.5)
            )doc",
            arg("point")
        )
        .def(
            "apply_transformation",
            &PointSet::applyTransformation,
            R"doc(
                Apply a transformation to all points in the set.
                
                Args:
                    transformation (Transformation): The transformation to apply.
                
                Example:
                    >>> points = [Point(0.0, 0.0), Point(1.0, 1.0)]
                    >>> point_set = PointSet(points)
                    >>> transformation = Transformation(Transformation.Type.Translation, [1.0, 1.0])
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
                    PointSet: An empty point set.

                Example:
                    >>> empty_set = PointSet.empty()
                    >>> empty_set.is_empty()  # True
                    >>> empty_set.get_size()  # 0
            )doc"
        )

        .def("__len__", &PointSet::getSize)
        .def(
            "__iter__",
            [](const PointSet& aPointSet)
            {
                return make_iterator(aPointSet.begin(), aPointSet.end());
            },
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
            }
        )

        ;
}
