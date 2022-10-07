################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           bindings/python/test/geometry/d2/objects/test_multipolygon.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

import numpy as np

import ostk.mathematics as mathematics

from ostk.core.types import String

################################################################################################################################################################

Object = mathematics.geometry.d2.Object
Polygon = mathematics.geometry.d2.objects.Polygon
MultiPolygon = mathematics.geometry.d2.objects.MultiPolygon

################################################################################################################################################################

class TestMultipolygon:

    def test_constructor_success (
        self,
        square_1: Polygon,
        square_2: Polygon
    ):

        # Construction using a python list of polygons
        multipolygon: MultiPolygon = MultiPolygon([square_1, square_2])

        assert multipolygon is not None
        assert isinstance(multipolygon, MultiPolygon)
        assert isinstance(multipolygon, Object)
        assert multipolygon.is_defined()

        # Construction using a python tuple of polygons
        multipolygon: MultiPolygon = MultiPolygon((square_1, square_2))

        assert multipolygon is not None
        assert isinstance(multipolygon, MultiPolygon)
        assert isinstance(multipolygon, Object)
        assert multipolygon.is_defined()

        # Construction using a python numpy array of polygons
        multipolygon: MultiPolygon = MultiPolygon(np.array((square_1, square_2)))

        assert multipolygon is not None
        assert isinstance(multipolygon, MultiPolygon)
        assert isinstance(multipolygon, Object)
        assert multipolygon.is_defined()

        # Construction using polygon static constructor
        multipolygon: MultiPolygon = MultiPolygon.polygon(square_1)

        assert multipolygon is not None
        assert isinstance(multipolygon, MultiPolygon)
        assert isinstance(multipolygon, Object)
        assert multipolygon.is_defined()

        # Construction using an array of one polygon
        multipolygon: MultiPolygon = MultiPolygon([square_1])

        assert multipolygon is not None
        assert isinstance(multipolygon, MultiPolygon)
        assert isinstance(multipolygon, Object)
        assert multipolygon.is_defined()

    def test_comparators_success (
        self,
        square_1: Polygon,
        square_2: Polygon
    ):

        # Multiple MultiPolygons
        multipolygon_1: MultiPolygon = MultiPolygon([square_1, square_2])
        multipolygon_2: MultiPolygon = MultiPolygon([square_1])
        multipolygon_3: MultiPolygon = MultiPolygon.polygon(square_1)

        assert multipolygon_1 == multipolygon_1
        assert multipolygon_1 != multipolygon_2
        assert multipolygon_1 != multipolygon_3
        assert multipolygon_2 == multipolygon_3

    def test_undefined_constructor_success (self):

        multipolygon: MultiPolygon = MultiPolygon.undefined()

        assert multipolygon is not None
        assert isinstance(multipolygon, MultiPolygon)
        assert isinstance(multipolygon, Object)
        assert multipolygon.is_defined() is False

    def test_getters_success (
        self,
        square_1: Polygon,
        square_2: Polygon,
    ):

        # Multiple Polygons
        multipolygon: MultiPolygon = MultiPolygon([square_1, square_2])

        assert multipolygon.get_polygon_count() == 2
        assert multipolygon.get_polygons()[0] == square_1
        assert multipolygon.get_polygons()[-1] == square_2

        # One Polygon
        multipolygon: MultiPolygon = MultiPolygon.polygon(square_1)

        assert multipolygon.get_polygon_count() == 1
        assert multipolygon.get_polygons()[0] == square_1
        assert multipolygon.get_convex_hull() == square_1

    # def test_union_with_success (self) :

    # def test_to_string_success (self):

    # def test_apply_transformation_success (self):

################################################################################################################################################################
