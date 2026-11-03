# Apache License 2.0

"""Round-trip tests for the Eigen <-> NumPy conversions at the binding boundary.

Every dense Eigen type that crosses the boundary is covered (Vector2d, Vector3d, Vector4d, VectorXd, Matrix3d,
Matrix4d, MatrixXd), for inputs (NumPy arrays of any memory order or stride, int dtype, read-only arrays, lists)
and outputs (dtype, shape, ownership).
"""

import gc

import pytest

import numpy as np

import ostk.mathematics as mathematics

Point2d = mathematics.geometry.d2.object.Point
Line2d = mathematics.geometry.d2.object.Line
Transformation2d = mathematics.geometry.d2.Transformation
Point3d = mathematics.geometry.d3.object.Point
Transformation3d = mathematics.geometry.d3.Transformation
Quaternion = mathematics.geometry.d3.transformation.rotation.Quaternion
RotationMatrix = mathematics.geometry.d3.transformation.rotation.RotationMatrix
Linear = mathematics.curve_fitting.interpolator.Linear
LogEuclideanRiemannian = (
    mathematics.curve_fitting.matrix_interpolator.LogEuclideanRiemannian
)
NumericalSolver = mathematics.solver.NumericalSolver


def _assert_owned_float64(array: np.ndarray, shape: tuple) -> None:
    assert isinstance(array, np.ndarray)
    assert array.dtype == np.float64
    assert array.shape == shape
    assert array.flags.writeable


class TestVector2d:
    def test_round_trip(self):
        vector = np.array([0.6, -0.8])

        line = Line2d(Point2d(0.0, 0.0), vector)

        direction = line.get_direction()

        _assert_owned_float64(direction, (2,))
        assert np.array_equal(direction, vector)

    def test_returned_array_is_a_copy(self):
        line = Line2d(Point2d(0.0, 0.0), np.array([1.0, 0.0]))

        direction = line.get_direction()
        direction[0] = 42.0

        assert np.array_equal(line.get_direction(), np.array([1.0, 0.0]))

    def test_input_array_is_copied(self):
        vector = np.array([1.0, 0.0])

        line = Line2d(Point2d(0.0, 0.0), vector)
        vector[0] = 42.0

        assert np.array_equal(line.get_direction(), np.array([1.0, 0.0]))

    def test_operator(self):
        assert Point2d(1.0, 2.0) + np.array([1.0, 1.0]) == Point2d(2.0, 3.0)
        assert Point2d(1.0, 2.0) + [1.0, 1.0] == Point2d(2.0, 3.0)
        assert np.array_equal(Point2d(1.0, 2.0) - Point2d(0.0, 1.0), np.array([1.0, 1.0]))

    def test_transformation_apply_to(self):
        transformation = Transformation2d.translation([1.0, 2.0])

        assert np.array_equal(
            transformation.apply_to(np.array([1.0, 1.0])), np.array([1.0, 1.0])
        )


class TestVector3d:
    @pytest.mark.parametrize(
        "vector",
        [
            np.array([1.0, 2.0, 3.0]),
            np.array([1, 2, 3]),  # int dtype: converted
            np.array([1.0, 2.0, 3.0], dtype=np.float32),  # other float dtype: converted
            np.array([1.0, 0.0, 2.0, 0.0, 3.0, 0.0])[::2],  # non-contiguous view: copied
            [1.0, 2.0, 3.0],  # list: converted (as with pybind11)
            (1, 2, 3),  # tuple: converted (as with pybind11)
            np.array(
                [[1.0], [2.0], [3.0]]
            ),  # (3, 1) column: flattened (as with pybind11)
        ],
    )
    def test_accepted_inputs(self, vector):
        point = Point3d.vector(vector)

        result = point.as_vector()

        _assert_owned_float64(result, (3,))
        assert np.array_equal(result, np.array([1.0, 2.0, 3.0]))

    def test_read_only_input(self):
        vector = np.array([1.0, 2.0, 3.0])
        vector.flags.writeable = False

        assert np.array_equal(Point3d.vector(vector).as_vector(), vector)

    @pytest.mark.parametrize(
        "vector",
        [
            np.array([1.0, 2.0]),
            np.array([1.0, 2.0, 3.0, 4.0]),
            np.array([[1.0, 2.0], [3.0, 4.0]]),
            np.array([[1.0, 2.0, 3.0]]),  # (1, 3) row: rejected (as with pybind11)
            np.array(
                [1.0j, 2.0, 3.0]
            ),  # complex: rejected (pybind11 dropped the imaginary part)
            [1.0, 2.0],
            ["a", "b", "c"],
            "abc",
            [[1.0], [2.0, 3.0]],
        ],
    )
    def test_rejected_inputs(self, vector):
        with pytest.raises(TypeError):
            Point3d.vector(vector)

    def test_returned_array_is_a_copy(self):
        point = Point3d(1.0, 2.0, 3.0)

        vector = point.as_vector()
        vector[0] = 42.0

        assert point.x() == 1.0

    def test_returned_array_outlives_its_source(self):
        vector = Point3d(1.0, 2.0, 3.0).as_vector()

        gc.collect()

        assert np.array_equal(vector, np.array([1.0, 2.0, 3.0]))

    def test_operators(self):
        point = Point3d(1.0, 2.0, 3.0)

        assert point + np.array([1.0, 1.0, 1.0]) == Point3d(2.0, 3.0, 4.0)
        assert point - [1.0, 1.0, 1.0] == Point3d(0.0, 1.0, 2.0)
        assert np.array_equal(point - Point3d(1.0, 1.0, 1.0), np.array([0.0, 1.0, 2.0]))

    def test_rotation(self):
        quaternion = Quaternion.unit()
        rotation_matrix = RotationMatrix.unit()

        vector = np.array([1.0, 2.0, 3.0])

        assert np.array_equal(quaternion * vector, vector)
        assert np.array_equal(quaternion.rotate_vector(vector), vector)
        assert np.array_equal(rotation_matrix * vector, vector)
        assert np.array_equal(rotation_matrix * [1.0, 2.0, 3.0], vector)

        _assert_owned_float64(rotation_matrix.get_row_at(0), (3,))
        _assert_owned_float64(rotation_matrix.get_column_at(0), (3,))


class TestVector4d:
    def test_round_trip(self):
        vector = np.array([0.0, 0.0, 0.0, 1.0])

        quaternion = Quaternion(vector, Quaternion.Format.XYZS)

        result = quaternion.to_vector(Quaternion.Format.XYZS)

        _assert_owned_float64(result, (4,))
        assert np.array_equal(result, vector)

        assert Quaternion([0.0, 0.0, 0.0, 1.0], Quaternion.Format.XYZS) == quaternion


class TestVectorXd:
    def test_round_trip(self):
        x = np.array([0.0, 1.0, 2.0])
        y = np.array([0.0, 2.0, 4.0])

        interpolator = Linear(x, y)

        result = interpolator.evaluate(np.array([0.5, 1.5]))

        _assert_owned_float64(result, (2,))
        assert np.allclose(result, np.array([1.0, 3.0]))

    def test_list_and_scalar_overloads(self):
        interpolator = Linear([0.0, 1.0, 2.0], [0, 2, 4])

        assert isinstance(interpolator.evaluate(0.5), float)
        assert isinstance(interpolator.evaluate(1), float)
        assert np.allclose(interpolator.evaluate([0.5, 1.5]), np.array([1.0, 3.0]))

    def test_empty(self):
        interpolator = Linear([0.0, 1.0, 2.0], [0.0, 2.0, 4.0])

        result = interpolator.evaluate(np.array([]))

        _assert_owned_float64(result, (0,))

    def test_large_vector(self):
        # Dynamic vectors >= 1 KB are moved into a capsule-owned buffer rather than copied.
        x = np.linspace(0.0, 1.0, 1000)

        interpolator = Linear(x, 2.0 * x)

        result = interpolator.evaluate(x)

        _assert_owned_float64(result, (1000,))
        assert np.allclose(result, 2.0 * x)

        del interpolator
        assert np.allclose(result, 2.0 * x)

    def test_numerical_solver_callback(self):
        # The state vector goes C++ -> Python -> C++ on every step of the integration.
        numerical_solver = NumericalSolver.default()

        states = []

        def oscillator(x, dxdt, t):
            assert isinstance(x, np.ndarray)
            assert x.dtype == np.float64
            assert x.shape == (2,)

            # Arguments are copies, so keeping them beyond the call is safe.
            states.append(x)

            dxdt[0] = x[1]
            dxdt[1] = -x[0]

            return dxdt

        state_vector, _ = numerical_solver.integrate_duration(
            np.array([0.0, 1.0]), 1.0, oscillator
        )

        _assert_owned_float64(state_vector, (2,))
        assert np.allclose(state_vector, [np.sin(1.0), np.cos(1.0)], atol=1e-6)

        assert len(states) > 2
        assert np.array_equal(states[0], [0.0, 1.0])
        assert not np.array_equal(states[0], states[-1])


class TestMatrix3d:
    def test_round_trip_preserves_layout(self):
        matrix = np.array(
            [
                [0.0, -1.0, 0.0],
                [1.0, 0.0, 0.0],
                [0.0, 0.0, 1.0],
            ]
        )

        for array in (matrix, np.asfortranarray(matrix), matrix.T.copy().T):
            rotation_matrix = RotationMatrix(array)

            result = rotation_matrix.get_matrix()

            _assert_owned_float64(result, (3, 3))
            assert np.array_equal(result, matrix)
            assert np.array_equal(rotation_matrix.get_row_at(0), matrix[0, :])
            assert np.array_equal(rotation_matrix.get_column_at(0), matrix[:, 0])

    def test_list_input(self):
        rotation_matrix = RotationMatrix([[1, 0, 0], [0, 1, 0], [0, 0, 1]])

        assert rotation_matrix == RotationMatrix.unit()

    def test_returned_array_is_a_copy(self):
        rotation_matrix = RotationMatrix.unit()

        matrix = rotation_matrix.get_matrix()
        matrix[0, 0] = 42.0

        assert rotation_matrix.get_matrix()[0, 0] == 1.0

    def test_rejected_shape(self):
        with pytest.raises(TypeError):
            RotationMatrix(np.eye(4))

    def test_transformation_2d(self):
        # The translation sits in the last column, so a transposed copy would put it in the last row.
        translation = Transformation2d.translation([2.0, 3.0])

        matrix = translation.get_matrix()

        _assert_owned_float64(matrix, (3, 3))
        assert np.array_equal(matrix[0:2, 2], np.array([2.0, 3.0]))
        assert np.array_equal(matrix[2, :], np.array([0.0, 0.0, 1.0]))
        assert translation.apply_to(Point2d(0.0, 0.0)) == Point2d(2.0, 3.0)

        assert Transformation2d(np.eye(3)) == Transformation2d.identity()
        assert (
            Transformation2d([[1, 0, 0], [0, 1, 0], [0, 0, 1]])
            == Transformation2d.identity()
        )


class TestMatrix4d:
    def test_round_trip(self):
        translation = Transformation3d.translation([1.0, 2.0, 3.0])

        matrix = translation.get_matrix()

        _assert_owned_float64(matrix, (4, 4))
        assert np.array_equal(matrix[0:3, 3], np.array([1.0, 2.0, 3.0]))
        assert np.array_equal(matrix[3, :], np.array([0.0, 0.0, 0.0, 1.0]))
        assert translation.apply_to(Point3d(0.0, 0.0, 0.0)) == Point3d(1.0, 2.0, 3.0)

        assert (
            Transformation3d(np.asfortranarray(np.eye(4))) == Transformation3d.identity()
        )


class TestMatrixXd:
    def test_round_trip(self):
        first = np.diag([1.0, 4.0])
        second = np.diag([4.0, 16.0])

        interpolator = LogEuclideanRiemannian(np.array([0.0, 1.0]), [first, second])

        result = interpolator.evaluate(0.0)

        _assert_owned_float64(result, (2, 2))
        assert np.allclose(result, first)

        results = interpolator.evaluate(np.array([0.0, 1.0]))

        assert len(results) == 2
        assert np.allclose(results[1], second)

    def test_layout(self):
        matrix = np.array([[2.0, 1.0], [1.0, 3.0]])

        for array in (matrix, np.asfortranarray(matrix), [[2, 1], [1, 3]]):
            interpolator = LogEuclideanRiemannian(np.array([0.0, 1.0]), [array, array])

            assert np.allclose(interpolator.evaluate(0.5), matrix)

    def test_non_square_input_reaches_the_library(self):
        # The (2, 3) shape crosses the boundary unchanged, so the library's own check rejects it.
        matrix = np.arange(6.0).reshape(2, 3)

        with pytest.raises(RuntimeError):
            LogEuclideanRiemannian(np.array([0.0, 1.0]), [matrix, matrix])
