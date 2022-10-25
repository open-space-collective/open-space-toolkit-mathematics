################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           bindings/python/test/geometry/d2/objects/test_polygon.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

import numpy as np

import ostk.mathematics as mathematics

################################################################################################################################################################

Object = mathematics.geometry.d2.Object
Point = mathematics.geometry.d2.objects.Point
PointSet = mathematics.geometry.d2.objects.PointSet
Polygon = mathematics.geometry.d2.objects.Polygon
MultiPolygon = mathematics.geometry.d2.objects.MultiPolygon
LineString = mathematics.geometry.d2.objects.LineString
Segment = mathematics.geometry.d2.objects.Segment
Intersection = mathematics.geometry.d2.Intersection

################################################################################################################################################################

class TestPolygon:

    def test_constructor_empty_inner_ring (self):

        point_1: Point = Point(-1.0, 1.0)
        point_2: Point = Point(1.0, 1.0)
        point_3: Point = Point(1.0, -1.0)
        point_4: Point = Point(-1.0, -1.0)

        # Default constructor with Array of Points using python list
        polygon: Polygon = Polygon([point_1, point_2, point_3, point_4])

        assert polygon is not None
        assert isinstance(polygon, Polygon)
        assert isinstance(polygon, Object)
        assert polygon.is_defined()

        # Default constructor with Array of Points using python tuple
        polygon: Polygon = Polygon((point_1, point_2, point_3, point_4))

        assert polygon is not None
        assert isinstance(polygon, Polygon)
        assert isinstance(polygon, Object)
        assert polygon.is_defined()

        # Default constructor with Array of Points using python numpy array
        polygon: Polygon = Polygon((point_1, point_2, point_3, point_4))

        assert polygon is not None
        assert isinstance(polygon, Polygon)
        assert isinstance(polygon, Object)
        assert polygon.is_defined()

        # Defaut constructor with 3 points (minimum)
        polygon: Polygon = Polygon((point_1, point_2, point_3))

        assert polygon is not None
        assert isinstance(polygon, Polygon)
        assert isinstance(polygon, Object)
        assert polygon.is_defined()

        # Invalid constructions
        with pytest.raises(RuntimeError):

            polygon: Polygon = Polygon([point_1, point_2])

        with pytest.raises(RuntimeError):

            polygon: Polygon = Polygon((point_1, point_2))

        with pytest.raises(RuntimeError):

            polygon: Polygon = Polygon([point_1])

    def test_constructor_nonempty_inner_ring (self):

        # Outer Ring Vertices
        point_1: Point = Point(-1.0, 1.0)
        point_2: Point = Point(1.0, 1.0)
        point_3: Point = Point(1.0, -1.0)
        point_4: Point = Point(-1.0, -1.0)

        # Inner Ring Vertices
        point_5: Point = Point(-0.5, 0.5)
        point_6: Point = Point(0.5, 0.5)
        point_7: Point = Point(0.5, -0.5)
        point_8: Point = Point(-0.5, -0.5)

        # Outer Ring Definitions
        outer_ring_list = [point_1, point_2, point_3, point_4]
        outer_ring_tuple = (point_1, point_2, point_3, point_4)
        outer_ring_numpy = np.array(outer_ring_tuple)

        # Inner Ring Definitions
        inner_ring_list = [point_5, point_6, point_7, point_8]
        inner_ring_tuple = (point_5, point_6, point_7, point_8)
        inner_ring_numpy = np.array(inner_ring_tuple)

        # Inner Rings Definitions
        inner_rings_list_list = [inner_ring_list,]
        inner_rings_list_tuple = (inner_ring_list,)
        inner_rings_tuple_list = [inner_ring_tuple,]
        inner_rings_tuple_tuple = (inner_ring_tuple,)
        inner_rings_numpy = np.array(inner_rings_list_list)

        # Default constructor with Inner Ring using Python list
        polygon: Polyon = Polygon(outer_ring_list, inner_rings_list_list)

        assert polygon is not None
        assert isinstance(polygon, Polygon)
        assert isinstance(polygon, Object)
        assert polygon.is_defined()

        # Default constructor with Inner Ring using Python tuples
        polygon: Polyon = Polygon(outer_ring_tuple, inner_rings_tuple_tuple)

        assert polygon is not None
        assert isinstance(polygon, Polygon)
        assert isinstance(polygon, Object)
        assert polygon.is_defined()

        # Default constructor with Inner Ring using Python numpy arrays
        polygon: Polygon = Polygon(outer_ring_numpy, inner_rings_numpy)

        assert polygon is not None
        assert isinstance(polygon, Polygon)
        assert isinstance(polygon, Object)
        assert polygon.is_defined()

        # Default constructor with Inner Ring multiple types 1
        polygon: Polygon = Polygon(outer_ring_numpy, inner_rings_list_list)

        assert polygon is not None
        assert isinstance(polygon, Polygon)
        assert isinstance(polygon, Object)
        assert polygon.is_defined()

        # Default constructor with Inner Ring multiple types 2
        polygon: Polygon = Polygon(outer_ring_tuple, inner_rings_numpy)

        assert polygon is not None
        assert isinstance(polygon, Polygon)
        assert isinstance(polygon, Object)
        assert polygon.is_defined()

        # Default constructor with Inner Ring multiple types 3
        polygon: Polygon = Polygon(outer_ring_list, inner_rings_numpy)

        assert polygon is not None
        assert isinstance(polygon, Polygon)
        assert isinstance(polygon, Object)
        assert polygon.is_defined()

        # Default constructor with Inner Ring multiple types 4
        polygon: Polygon = Polygon(outer_ring_list, inner_rings_tuple_tuple)

        assert polygon is not None
        assert isinstance(polygon, Polygon)
        assert isinstance(polygon, Object)
        assert polygon.is_defined()

        # Default constructor with Inner Ring multiple types 5
        polygon: Polygon = Polygon(outer_ring_numpy, inner_rings_tuple_tuple)

        assert polygon is not None
        assert isinstance(polygon, Polygon)
        assert isinstance(polygon, Object)
        assert polygon.is_defined()

        # Default constructor with Inner Ring multiple types 6
        polygon: Polygon = Polygon(outer_ring_numpy, inner_rings_list_tuple)

        assert polygon is not None
        assert isinstance(polygon, Polygon)
        assert isinstance(polygon, Object)
        assert polygon.is_defined()

        # Default constructor with Inner Ring multiple types 7
        polygon: Polygon = Polygon(outer_ring_numpy, inner_rings_tuple_list)

        assert polygon is not None
        assert isinstance(polygon, Polygon)
        assert isinstance(polygon, Object)
        assert polygon.is_defined()

        # Default constructor with Inner Ring multiple types 8
        polygon: Polygon = Polygon(outer_ring_tuple, inner_rings_list_list)

        assert polygon is not None
        assert isinstance(polygon, Polygon)
        assert isinstance(polygon, Object)
        assert polygon.is_defined()

        # ...

    def test_comparators (self):

        point_1: Point = Point(-1.0, 1.0)
        point_2: Point = Point(1.0, 1.0)
        point_3: Point = Point(1.0, -1.0)
        point_4: Point = Point(-1.0, -1.0)

        polygon_1: Polygon = Polygon((point_1, point_2, point_3, point_4))
        polygon_2: Polygon = Polygon((point_1, point_2, point_3))

        assert polygon_1 == polygon_1
        assert polygon_2 == polygon_2
        assert polygon_1 != polygon_2

    def test_intersects_polygon (
        self,
        square_1: Polygon,
        square_2: Polygon,
        square_3: Polygon,
        square_4: Polygon,
    ):

        assert square_1.intersects(square_2) is False
        assert square_1.intersects(square_3) is True
        assert square_1.intersects(square_4) is True
        assert square_2.intersects(square_4) is False
        assert square_2.intersects(square_3) is False

    def test_contains (self):

        point_1: Point = Point(-1.0, 1.0)
        point_2: Point = Point(1.0, 1.0)
        point_3: Point = Point(1.0, -1.0)
        point_4: Point = Point(-1.0, -1.0)

        point_set: PointSet = PointSet([Point(0.0, 0.0)])
        polygon: Polygon = Polygon((point_1, point_2, point_3, point_4))

        assert polygon.contains(Point.origin())
        assert polygon.contains(point_1)
        assert polygon.contains(point_2)
        assert polygon.contains(point_3)
        assert polygon.contains(point_4)
        assert polygon.contains(Point(10.0, 10.0)) is False

        assert polygon.contains(point_set)

    def test_getters (self):

        # Outer Ring Vertices
        point_1: Point = Point(-1.0, 1.0)
        point_2: Point = Point(1.0, 1.0)
        point_3: Point = Point(1.0, -1.0)
        point_4: Point = Point(-1.0, -1.0)

        # Inner Ring Vertices
        point_5: Point = Point(-0.5, 0.5)
        point_6: Point = Point(0.5, -0.5)
        point_7: Point = Point(0.5, 0.5)
        point_8: Point = Point(-0.5, -0.5)

        # Rings Definitions
        outer_ring = [point_1, point_2, point_3, point_4]
        inner_rings = [[point_5, point_6, point_7, point_8],]

        # Define polygon
        polygon: Polygon = Polygon(outer_ring, inner_rings)

        # get_inner_rings_count
        assert polygon.get_inner_ring_count() == 1

        # get_edge_count
        assert polygon.get_edge_count() == 8

        # get_vertex_count
        assert polygon.get_vertex_count() == 8

        # get_outer_ring
        assert isinstance(polygon.get_outer_ring(), LineString)
        assert polygon.get_outer_ring() == LineString([point_1, point_2, point_3, point_4, point_1])

        # get_inner_ring_at
        assert isinstance(polygon.get_inner_ring_at(0), LineString)
        assert polygon.get_inner_ring_at(0) == LineString([point_5, point_6, point_7, point_8, point_5])

        with pytest.raises(RuntimeError):

            polygon.get_inner_ring_at(1)

        # get_edge_at
        edge_0 = polygon.get_edge_at(0)
        edge_1 = polygon.get_edge_at(1)
        edge_2 = polygon.get_edge_at(2)

        assert isinstance(edge_0, Segment)
        assert isinstance(edge_1, Segment)
        assert isinstance(edge_2, Segment)

        assert edge_0.get_first_point() == point_1
        assert edge_0.get_second_point() == point_2
        assert edge_1.get_first_point() == point_2
        assert edge_1.get_second_point() == point_3
        assert edge_2.get_first_point() == point_3

        # get_vertex_at
        vertex_0 = polygon.get_vertex_at(0)
        vertex_1 = polygon.get_vertex_at(1)

        assert isinstance(vertex_0, Point)
        assert isinstance(vertex_1, Point)
        assert vertex_0 == point_1
        assert vertex_1 == point_2

        # get_edges

        # get_vertices

        # get_convex_hull

    def test_union_with (
        self,
        square_1: Polygon,
        square_4: Polygon,
    ):

        multipolygon: MultiPolygon = square_1.union_with(square_4)

        assert multipolygon is not None
        assert isinstance(multipolygon, MultiPolygon)
        assert multipolygon.is_defined()

    def test_intersection_with (
        self,
        square_1: Polygon,
        square_4: Polygon,
    ):

        intersection: Intersection = square_1.intersection_with(square_1)

        assert intersection is not None
        assert isinstance(intersection, Intersection)
        assert intersection.is_defined()
        assert intersection.is_polygon()

        assert intersection.as_polygon() == square_1

        intersection_2: Intersection = square_1.intersection_with(square_4)

        assert intersection_2 is not None
        assert isinstance(intersection_2, Intersection)
        assert intersection_2.is_defined()
        assert intersection_2.is_line_string()
        assert intersection_2.as_line_string() == LineString([Point(0.5, 0.5), Point(0.5, -0.5)])
        assert intersection_2.get_type() == Intersection.Type.LineString

    def test_difference_with (
        self,
        square_1: Polygon,
        square_3: Polygon,
    ):

        difference: Intersection = square_1.difference_with(square_1)

        assert difference is not None
        assert isinstance(difference, Intersection)
        assert difference.is_defined()
        assert difference.is_empty()

        difference_2: Intersection = square_1.difference_with(square_3)

        assert difference_2 is not None
        assert isinstance(difference_2, Intersection)
        assert difference_2.is_defined()
        assert difference_2.is_polygon()
        assert difference_2.as_polygon() == Polygon([Point(0.0, 0.5), Point(-0.5, 0.5), Point(-0.5, -0.5), Point(0.0, -0.5)])
        assert difference_2.get_type() == Intersection.Type.Polygon

################################################################################################################################################################
