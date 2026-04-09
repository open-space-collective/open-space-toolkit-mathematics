# Apache License 2.0

import numpy as np
import pytest

from ostk.mathematics.curve_fitting.matrix_interpolator import LogEuclideanRiemannian


@pytest.fixture
def identity_3x3() -> np.ndarray:
    return np.eye(3)


@pytest.fixture
def diagonal_spd() -> np.ndarray:
    return np.diag([4.0, 9.0, 16.0])


@pytest.fixture
def interpolator(
    identity_3x3: np.ndarray,
    diagonal_spd: np.ndarray,
) -> LogEuclideanRiemannian:
    return LogEuclideanRiemannian(
        x=np.array([0.0, 1.0]),
        matrices=[identity_3x3, diagonal_spd],
    )


class TestLogEuclideanRiemannian:
    def test_constructor_success(
        self,
        interpolator: LogEuclideanRiemannian,
    ):
        assert interpolator is not None
        assert isinstance(interpolator, LogEuclideanRiemannian)

    def test_constructor_mismatched_sizes(
        self,
        identity_3x3: np.ndarray,
    ):
        with pytest.raises(RuntimeError):
            LogEuclideanRiemannian(
                x=np.array([0.0, 1.0, 2.0]),
                matrices=[identity_3x3, identity_3x3],
            )

    def test_constructor_too_few_points(
        self,
        identity_3x3: np.ndarray,
    ):
        with pytest.raises(RuntimeError):
            LogEuclideanRiemannian(
                x=np.array([0.0]),
                matrices=[identity_3x3],
            )

    def test_constructor_non_monotonic_x(
        self,
        identity_3x3: np.ndarray,
    ):
        with pytest.raises(RuntimeError):
            LogEuclideanRiemannian(
                x=np.array([0.0, 2.0, 1.0]),
                matrices=[identity_3x3, identity_3x3, identity_3x3],
            )

    def test_constructor_duplicate_x(
        self,
        identity_3x3: np.ndarray,
    ):
        with pytest.raises(RuntimeError):
            LogEuclideanRiemannian(
                x=np.array([0.0, 1.0, 1.0]),
                matrices=[identity_3x3, identity_3x3, identity_3x3],
            )

    def test_constructor_non_positive_definite(
        self,
        identity_3x3: np.ndarray,
    ):
        not_pd = np.array([[1.0, 0.0], [0.0, -1.0]])
        with pytest.raises(RuntimeError):
            LogEuclideanRiemannian(
                x=np.array([0.0, 1.0]),
                matrices=[np.eye(2), not_pd],
            )

    def test_evaluate_endpoints(
        self,
        interpolator: LogEuclideanRiemannian,
        identity_3x3: np.ndarray,
        diagonal_spd: np.ndarray,
    ):
        result_0 = interpolator.evaluate(0.0)
        np.testing.assert_allclose(result_0, identity_3x3, atol=1e-10)

        result_1 = interpolator.evaluate(1.0)
        np.testing.assert_allclose(result_1, diagonal_spd, atol=1e-10)

    def test_evaluate_midpoint(
        self,
        interpolator: LogEuclideanRiemannian,
    ):
        result = interpolator.evaluate(0.5)
        expected = np.diag([2.0, 3.0, 4.0])
        np.testing.assert_allclose(result, expected, atol=1e-10)

    def test_evaluate_vector(
        self,
        interpolator: LogEuclideanRiemannian,
        identity_3x3: np.ndarray,
        diagonal_spd: np.ndarray,
    ):
        results = interpolator.evaluate(np.array([0.0, 0.5, 1.0]))

        assert len(results) == 3
        np.testing.assert_allclose(results[0], identity_3x3, atol=1e-10)
        np.testing.assert_allclose(results[1], np.diag([2.0, 3.0, 4.0]), atol=1e-10)
        np.testing.assert_allclose(results[2], diagonal_spd, atol=1e-10)

    def test_evaluate_result_is_spd(
        self,
    ):
        P0 = np.array([[4.0, 2.0, 1.0], [2.0, 5.0, 3.0], [1.0, 3.0, 6.0]])
        P1 = np.array([[10.0, 3.0, 2.0], [3.0, 8.0, 1.0], [2.0, 1.0, 7.0]])

        interpolator = LogEuclideanRiemannian(
            x=np.array([0.0, 1.0]),
            matrices=[P0, P1],
        )

        for alpha in np.arange(0.1, 1.0, 0.1):
            result = interpolator.evaluate(float(alpha))

            # Check symmetry
            np.testing.assert_allclose(result, result.T, atol=1e-10)

            # Check positive definiteness
            eigenvalues = np.linalg.eigvalsh(result)
            assert np.all(eigenvalues > 0)

    def test_get_matrices(
        self,
        interpolator: LogEuclideanRiemannian,
        identity_3x3: np.ndarray,
        diagonal_spd: np.ndarray,
    ):
        matrices = interpolator.get_matrices()

        assert len(matrices) == 2
        np.testing.assert_allclose(matrices[0], identity_3x3, atol=1e-10)
        np.testing.assert_allclose(matrices[1], diagonal_spd, atol=1e-10)
