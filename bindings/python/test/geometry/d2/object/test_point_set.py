# Apache License 2.0

from collections.abc import Iterator, Iterable

import ostk.mathematics as mathematics


Object = mathematics.geometry.d2.Object
Point = mathematics.geometry.d2.object.Point
PointSet = mathematics.geometry.d2.object.PointSet


class TestPointSet:
    def test_constructor_success(self):
        point_1: Point = Point(1.0, 2.0)
        point_2: Point = Point(3.0, 4.0)

        # Construction using python list
        point_set: PointSet = PointSet([point_1, point_2])

        assert point_set is not None
        assert isinstance(point_set, PointSet)
        assert isinstance(point_set, Object)
        assert point_set.is_defined()

        # Construction using python tuple
        point_set = PointSet((point_1, point_2))

        assert point_set is not None
        assert isinstance(point_set, PointSet)
        assert isinstance(point_set, Object)
        assert point_set.is_defined()

        point_set = PointSet((point_1,))

        assert point_set is not None
        assert isinstance(point_set, PointSet)
        assert isinstance(point_set, Object)
        assert point_set.is_defined()

    def test_empty_success(self):
        point_set: Pointset = PointSet.empty()

        assert point_set is not None
        assert isinstance(point_set, PointSet)
        assert isinstance(point_set, Object)
        assert point_set.is_defined() is False
        assert point_set.is_empty()

    def test_comparators_success(self):
        point_1: Point = Point(1.0, 2.0)
        point_2: Point = Point(3.0, 4.0)

        point_set_1: PointSet = PointSet([point_1, point_2])
        point_set_2: PointSet = PointSet((point_2, point_1))
        point_set_3: PointSet = PointSet([point_2])

        assert point_set_1 == point_set_2
        assert point_set_1 == point_set_2
        assert point_set_3 != point_set_1
        assert point_set_2 != point_set_3

    def test_get_size_success(self):
        point_1: Point = Point(1.0, 2.0)
        point_2: Point = Point(3.0, 4.0)

        point_set_1: PointSet = PointSet([point_1, point_2])
        point_set_2: PointSet = PointSet((point_2, point_1))
        point_set_3: PointSet = PointSet([point_2])
        point_set_4: PointSet = PointSet.empty()
        point_set_5: PointSet = PointSet([point_1, point_1])

        assert point_set_1.get_size() == 2
        assert point_set_2.get_size() == 2
        assert point_set_3.get_size() == 1
        assert point_set_4.get_size() == 0
        assert point_set_5.get_size() == 1

    def test_distance_to_success_point(self, point_set: PointSet):
        assert point_set.distance_to(Point(1.0, 2.0)) == 0.0

    def test_len_success(self, point_set: PointSet):
        assert len(point_set) == 2
        assert len(PointSet.empty()) == 0

    def test_iter_success(self, point_set: PointSet):
        for point in point_set:
            assert isinstance(point, Point)

        assert iter(point_set) is not None
        assert isinstance(iter(point_set), Iterator)
        assert isinstance(iter(point_set), Iterable)

    def test_get_item_success(self, point_set: PointSet):
        assert point_set[0] is not None

    # def test_is_near_success(self):

    # def test_get_point_closest_to_success(self):

    # def test_to_string_success(self):

    # def test_apply_transformation_success(self):
