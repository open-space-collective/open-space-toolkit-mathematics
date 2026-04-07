# Apache License 2.0

import numpy as np
import pytest

from ostk.mathematics.curve_fitting.interpolator import LogEuclidean


@pytest.fixture
def identity_3x3() -> np.ndarray:
    return np.eye(3)


@pytest.fixture
def diagonal_spd() -> np.ndarray:
    return np.diag([4.0, 9.0, 16.0])


@pytest.fixture
def interpolator(identity_3x3, diagonal_spd) -> LogEuclidean:
    return LogEuclidean(
        x=np.array([0.0, 1.0]),
        matrices=[identity_3x3, diagonal_spd],
    )


class TestLogEuclidean:
    def test_constructor_success(self, interpolator: LogEuclidean):
        assert interpolator is not None
        assert isinstance(interpolator, LogEuclidean)

    def test_constructor_mismatched_sizes(self, identity_3x3):
        with pytest.raises(RuntimeError):
            LogEuclidean(
                x=np.array([0.0, 1.0, 2.0]),
                matrices=[identity_3x3, identity_3x3],
            )

    def test_constructor_too_few_points(self, identity_3x3):
        with pytest.raises(RuntimeError):
            LogEuclidean(
                x=np.array([0.0]),
                matrices=[identity_3x3],
            )

    def test_constructor_non_monotonic_x(self, identity_3x3):
        with pytest.raises(RuntimeError):
            LogEuclidean(
                x=np.array([0.0, 2.0, 1.0]),
                matrices=[identity_3x3, identity_3x3, identity_3x3],
            )

    def test_constructor_duplicate_x(self, identity_3x3):
        with pytest.raises(RuntimeError):
            LogEuclidean(
                x=np.array([0.0, 1.0, 1.0]),
                matrices=[identity_3x3, identity_3x3, identity_3x3],
            )

    def test_constructor_not_positive_definite(self):
        not_pd = np.array([[1.0, 0.0], [0.0, -1.0]])
        with pytest.raises(RuntimeError):
            LogEuclidean(
                x=np.array([0.0, 1.0]),
                matrices=[np.eye(2), not_pd],
            )

    def test_constructor_semi_definite(self):
        semi_def = np.array([[1.0, 0.0], [0.0, 0.0]])
        with pytest.raises(RuntimeError):
            LogEuclidean(
                x=np.array([0.0, 1.0]),
                matrices=[np.eye(2), semi_def],
            )

    def test_evaluate_endpoints(self, interpolator, identity_3x3, diagonal_spd):
        result_0 = interpolator.evaluate(0.0)
        np.testing.assert_allclose(result_0, identity_3x3, atol=1e-10)

        result_1 = interpolator.evaluate(1.0)
        np.testing.assert_allclose(result_1, diagonal_spd, atol=1e-10)

    def test_evaluate_midpoint(self, interpolator):
        result = interpolator.evaluate(0.5)
        expected = np.diag([2.0, 3.0, 4.0])
        np.testing.assert_allclose(result, expected, atol=1e-10)

    def test_evaluate_vector(self, interpolator, identity_3x3, diagonal_spd):
        results = interpolator.evaluate(np.array([0.0, 0.5, 1.0]))

        assert len(results) == 3
        np.testing.assert_allclose(results[0], identity_3x3, atol=1e-10)
        np.testing.assert_allclose(results[1], np.diag([2.0, 3.0, 4.0]), atol=1e-10)
        np.testing.assert_allclose(results[2], diagonal_spd, atol=1e-10)

    def test_evaluate_result_is_spd(self):
        P0 = np.array([[4.0, 2.0, 1.0], [2.0, 5.0, 3.0], [1.0, 3.0, 6.0]])
        P1 = np.array([[10.0, 3.0, 2.0], [3.0, 8.0, 1.0], [2.0, 1.0, 7.0]])

        interpolator = LogEuclidean(
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

    def test_matrix_log_spd(self):
        # log(I) = 0
        result = LogEuclidean.matrix_log_spd(np.eye(3))
        np.testing.assert_allclose(result, np.zeros((3, 3)), atol=1e-10)

    def test_matrix_exp_symmetric(self):
        # exp(0) = I
        result = LogEuclidean.matrix_exp_symmetric(np.zeros((3, 3)))
        np.testing.assert_allclose(result, np.eye(3), atol=1e-10)

    def test_log_exp_round_trip(self):
        P = np.array([[4.0, 2.0, 1.0], [2.0, 5.0, 3.0], [1.0, 3.0, 6.0]])
        log_P = LogEuclidean.matrix_log_spd(P)
        result = LogEuclidean.matrix_exp_symmetric(log_P)
        np.testing.assert_allclose(result, P, atol=1e-10)

    def test_interpolate_static(self):
        P0 = np.eye(3)
        P1 = np.diag([4.0, 9.0, 16.0])

        result = LogEuclidean.interpolate(P0, P1, 0.5)
        expected = np.diag([2.0, 3.0, 4.0])
        np.testing.assert_allclose(result, expected, atol=1e-10)
