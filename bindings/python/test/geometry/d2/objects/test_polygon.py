################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           bindings/python/test/geometry/d2/objects/test_polygon.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

import numpy as np

import ostk.mathematics as mathematics

from ostk.core.types import String

################################################################################################################################################################

Object = mathematics.geometry.d2.Object
Point = mathematics.geometry.d2.objects.Point
PointSet = mathematics.geometry.d2.objects.PointSet
Polygon = mathematics.geometry.d2.objects.Polygon
MultiPolygon = mathematics.geometry.d2.objects.MultiPolygon
LineString = mathematics.geometry.d2.objects.LineString
Segment = mathematics.geometry.d2.objects.Segment
Transformation = mathematics.geometry.d2.Transformation

################################################################################################################################################################

def test_geometry_d2_objects_polygon_constructor_empty_inner_ring ():

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

def test_geometry_d2_objects_polygon_constructor_nonempty_inner_ring ():

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

def test_geometry_d2_objects_polygon_comparators ():

    point_1: Point = Point(-1.0, 1.0)
    point_2: Point = Point(1.0, 1.0)
    point_3: Point = Point(1.0, -1.0)
    point_4: Point = Point(-1.0, -1.0)

    polygon_1: Polygon = Polygon((point_1, point_2, point_3, point_4))
    polygon_2: Polygon = Polygon((point_1, point_2, point_3))

    assert polygon_1 == polygon_1
    assert polygon_2 == polygon_2
    assert polygon_1 != polygon_2

def test_geometry_d2_objects_polygon_intersects_polygon ():


    def square (center: Point) -> Polygon:
        '''
        Creates and Return a Square centered in center
        and with length 1.0 with no inner rings.
        '''
        point_1: Point = center + [0.5, 0.5]
        point_2: Point = center + [0.5, -0.5]
        point_3: Point = center + [-0.5, -0.5]
        point_4: Point = center + [-0.5, 0.5]

        return Polygon([point_1, point_2, point_3, point_4])

    square_1: Polygon = square(Point(0.0, 0.0))
    square_2: Polygon = square(Point(0.1, 0.1))
    square_3: Polygon = square(Point(10.0, 10.0))
    square_4: Polygon = square(Point(1.0, 0.0))

    # [TBI]
    with pytest.raises(RuntimeError):

        assert square_1.intersects(square_2)
        assert square_1.intersects(square_3) is False
        assert square_1.intersects(square_4) is False

def test_geometry_d2_objects_polygon_contains ():

    point_1: Point = Point(-1.0, 1.0)
    point_2: Point = Point(1.0, 1.0)
    point_3: Point = Point(1.0, -1.0)
    point_4: Point = Point(-1.0, -1.0)

    pointset: PointSet = PointSet([Point(0.0, 0.0)])
    polygon: Polygon = Polygon((point_1, point_2, point_3, point_4))

    assert polygon.contains_point(Point.origin())
    assert polygon.contains_point(point_1)
    assert polygon.contains_point(point_2)
    assert polygon.contains_point(point_3)
    assert polygon.contains_point(point_4)
    assert polygon.contains_point(Point(10.0, 10.0)) is False

    assert polygon.contains_point_set(pointset)

def test_geometry_d2_objects_polygon_getters ():

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

def test_geometry_d2_objects_polygon_union_with ():

    def square (center: Point) -> Polygon:
        '''
        Creates and Return a Square centered in center
        and with length 1.0 with no inner rings.
        '''
        point_1: Point = center + [0.5, 0.5]
        point_2: Point = center + [0.5, -0.5]
        point_3: Point = center + [-0.5, -0.5]
        point_4: Point = center + [-0.5, 0.5]

        return Polygon([point_1, point_2, point_3, point_4])

    square_1: Polygon = square(Point(0.0, 0.0))
    square_2: Polygon = square(Point(1.0, 0.0))

    multipolygon: MultiPolygon = square_1.union_with(square_2)

    assert multipolygon is not None
    assert isinstance(multipolygon, MultiPolygon)
    assert multipolygon.is_defined()

################################################################################################################################################################
