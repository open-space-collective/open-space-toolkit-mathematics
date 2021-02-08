################################################################################################################################################################

# @project        Open Space Toolkit ▸ Mathematics
# @file           bindings/python/test/geometry/d2/test_transformation.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import numpy as np

import pytest

import ostk.mathematics as mathematics

################################################################################################################################################################

Transformation = mathematics.geometry.d2.Transformation
Type = Transformation.Type
Point = mathematics.geometry.d2.objects.Point

################################################################################################################################################################

def test_geometry_d2_transformation_type ():

    enum_members = Type.__members__

    list_keys = [
        'Undefined',
        'Identity',
        'Translation',
        'Rotation',
        'Scaling',
        'Reflection',
        'Shear',
        'Affine'
    ]

    list_values = [
        Type.Undefined,
        Type.Identity,
        Type.Translation,
        Type.Rotation,
        Type.Scaling,
        Type.Reflection,
        Type.Shear,
        Type.Affine
    ]

    assert list(enum_members.keys()) == list_keys
    assert list(enum_members.values()) == list_values

def test_geometry_d2_transformation_constructor ():

    # Construction using python matrix
    M = [[1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 1.0]]
    transformation: Transformation = Transformation(M)

    assert transformation is not None
    assert isinstance(transformation, Transformation)
    assert transformation.is_defined()

    # Construction using python numpy array
    M = np.array(M)
    transformation: Transformation = Transformation(M)

    assert transformation is not None
    assert isinstance(transformation, Transformation)
    assert transformation.is_defined()

def test_geometry_d2_transformation_comparators ():

    M1 = [[1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 1.0]]

    transformation: Transformation = Transformation(M1)

def test_geometry_d2_transformation_defined ():

    transformation: Transformation = Transformation.undefined()

    assert transformation is not None
    assert isinstance(transformation, Transformation)
    assert transformation.is_defined() is False

# def test_geometry_d2_transformation_getters ():

# def test_geometry_d2_transformation_identity ():

# def test_geometry_d2_transformation_translation ():

# def test_geometry_d2_transformation_rotation ():

# def test_geometry_d2_transformation_rotation_around ():

################################################################################################################################################################
