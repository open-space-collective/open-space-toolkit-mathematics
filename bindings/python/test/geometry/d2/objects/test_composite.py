################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           bindings/python/test/geometry/d2/objects/test_composite.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

import ostk.mathematics as mathematics

################################################################################################################################################################

Object = mathematics.geometry.d2.Object
Point = mathematics.geometry.d2.objects.Point
Polygon = mathematics.geometry.d2.objects.Polygon
Composite = mathematics.geometry.d2.objects.Composite

################################################################################################################################################################

class TestComposite:

    def test_geometry_d2_objects_composite_constructor (
        self,
        polygon: Polygon
    ):

        composite: Composite = Composite(polygon)

        assert composite is not None
        assert isinstance(composite, Composite)
        assert composite.is_defined()

    def test_geometry_d2_objects_composite_empty (self):

        composite: Composite = Composite.empty()

        assert composite is not None
        assert isinstance(composite, Composite)
        assert isinstance(composite, Object)
        assert composite.is_defined()
        assert composite.is_empty()

    def test_geometry_d2_objects_composite_defined (self):

        composite: Composite = Composite.undefined()

        assert composite is not None
        assert isinstance(composite, Composite)
        assert isinstance(composite, Object)
        assert composite.is_defined() is False

    def test_geometry_d2_objects_composite_comparators (
        self,
        composite: Composite,
        polygon: Polygon
    ):

        other_composite: Composite = Composite(polygon)

        assert composite == composite
        assert composite != other_composite
        assert other_composite != composite

    def tes_geometry_d2_objects_composite_addition_operator (
        self,
        composite: Composite,
        polygon: Polygon
    ):

        assert composite is not None
        assert isinstance(composite, Composite)
        assert composite.is_defined()
        assert composite.get_object_count() == 2

        with pytest.raises(RuntimeError):
            other_composite = Composite.undefined() + composite

        with pytest.raises(RuntimeError):
            other_composite = composite +  Composite.undefined()

        composite += composite

        assert isinstance(composite, Composite)
        assert composite.is_defined()
        assert composite.get_object_count() == 4

        with pytest.raises(RuntimeError):
            composite += Composite.undefined()

    def test_geometry_d2_objects_composite_is (
        self,
        composite: Composite,
        polygon: Polygon
    ):

        assert composite.is_point() is False
        assert composite.is_polygon() is False

        assert Composite(polygon).is_polygon()

    def test_geometry_d2_objects_composite_access_object_at (
        self,
        composite: Composite,
        polygon: Polygon,
        point: Point
    ):

        assert composite.get_object_count() == 2
        assert composite.access_object_at(0) == polygon
        assert composite.access_object_at(1) == point

        with pytest.raises(RuntimeError):
            composite.access_object_at(2)

################################################################################################################################################################
