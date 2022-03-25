################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           bindings/python/test/geometry/d3/objects/test_composite.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

import ostk.mathematics as mathematics

################################################################################################################################################################

Point2d = mathematics.geometry.d2.objects.Point
Polygon2d = mathematics.geometry.d2.objects.Polygon
Object = mathematics.geometry.d3.Object
Composite = mathematics.geometry.d3.objects.Composite
Point3d = mathematics.geometry.d3.objects.Point
Segment = mathematics.geometry.d3.objects.Segment
Polygon3d = mathematics.geometry.d3.objects.Polygon

################################################################################################################################################################

def test_geometry_d3_objects_composite_constructor ():

    point_1: Point3d = Point3d(1.0, 2.0, 1.0)
    point_2: Point3d = Point3d(1.0, 1.0, 1.0)

    segment: Segment = Segment(point_1, point_2)

    composite_1 = Composite(segment)

    assert composite_1 is not None
    assert isinstance(composite_1, Composite)
    assert composite_1.is_defined()

    point_3: Point2d = Point2d(-1.0, 1.0)
    point_4: Point2d = Point2d(1.0, 1.0)
    point_5: Point2d = Point2d(1.0, -1.0)
    point_6: Point2d = Point2d(-1.0, -1.0)
    point_7: Point3d =  Point3d(1.0, 1.0, 1.0)
    vector_1 = (1.0, 0.0, 0.0)
    vector_2 = (0.0, 1.0, 0.0)

    polygon2d: Polygon2d = Polygon2d([point_3, point_4, point_5, point_6])
    polygon3d: Polygon3d = Polygon3d(polygon2d, point_7, vector_1, vector_2)

    composite_2: Composite = Composite(polygon3d)

    assert composite_2 is not None
    assert isinstance(composite_2, Composite)
    assert composite_2.is_defined()

def test_geometry_d3_objects_composite_empty ():

    composite: Composite = Composite.empty()

    assert composite is not None
    assert isinstance(composite, Composite)
    assert isinstance(composite, Object)
    assert composite.is_defined()
    assert composite.is_empty()

def test_geometry_d3_objects_composite_comparators ():

    point_1: Point3d = Point3d(1.0, 2.0, 1.0)
    point_2: Point3d = Point3d(1.0, 1.0, 1.0)
    point_3: Point3d = Point3d(1.0, 4.0, 1.0)

    segment_1: Segment = Segment(point_1, point_2)
    segment_2: Segment = Segment(point_1, point_3)
    segment_3: Segment = Segment(point_2, point_1)

    composite_1 = Composite(segment_1)
    composite_2 = Composite(segment_2)
    composite_3 = Composite(segment_3)

    assert composite_1 == composite_3
    assert composite_1 != composite_2
    assert composite_2 != composite_3

def tes_geometry_d3_objects_composite_addition_operator ():

    point_1: Point3d = Point3d(1.0, 2.0, 1.0)
    point_2: Point3d = Point3d(1.0, 1.0, 1.0)
    point_3: Point3d = Point3d(1.0, 4.0, 1.0)

    segment_1: Segment = Segment(point_1, point_2)
    segment_2: Segment = Segment(point_1, point_3)

    composite_1 = Composite(segment_1)
    composite_2 = Composite(segment_2)

    composite_3 = composite_1 + composite_2

    assert composite_3 is not None
    assert isinstance(composite_3, Composite)
    assert composite_3.is_defined()
    assert composite_3.get_object_count() == 2

    with pytest.raises(RuntimeError):
        composite = Composite.undefined() + composite_1

    with pytest.raises(RuntimeError):
        composite = composite_1 +  Composite.undefined()

    composite_3 += composite_1

    assert isinstance(composite_3, Composite)
    assert composite_3.is_defined()
    assert composite_3.get_object_count() == 3

    with pytest.raises(RuntimeError):
        composite_3 += Composite.undefined()

def test_geometry_d3_objects_composite_access_object_at ():

    point_1: Point3d = Point3d(1.0, 2.0, 1.0)
    point_2: Point3d = Point3d(1.0, 1.0, 1.0)

    segment: Segment = Segment(point_1, point_2)
    composite_1 = Composite(segment)

    object = composite_1.access_object_at(0)

    assert object is not None
    assert isinstance(object, Object)
    assert isinstance(object, Segment)

    point_3: Point2d = Point2d(-1.0, 1.0)
    point_4: Point2d = Point2d(1.0, 1.0)
    point_5: Point2d = Point2d(1.0, -1.0)
    point_6: Point2d = Point2d(-1.0, -1.0)
    point_7: Point3d =  Point3d(1.0, 1.0, 1.0)
    vector_1 = (1.0, 0.0, 0.0)
    vector_2 = (0.0, 1.0, 0.0)

    polygon2d: Polygon2d = Polygon2d([point_3, point_4, point_5, point_6])
    polygon3d: Polygon3d = Polygon3d(polygon2d, point_7, vector_1, vector_2)
    composite_2: Composite = Composite(polygon3d)

    composite_3 = composite_1 + composite_2

    object_1 = composite_3.access_object_at(0)
    object_2 = composite_3.access_object_at(1)

    assert object_1 == segment
    assert object_2 == polygon3d

    with pytest.raises(RuntimeError):
        composite_3.access_object_at(2)

################################################################################################################################################################
