/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/LogEuclidean.hpp>

inline void OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolator_LogEuclidean(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::container::Array;

    using ostk::mathematics::object::MatrixXd;
    using ostk::mathematics::object::VectorXd;

    using ostk::mathematics::curvefitting::interpolator::LogEuclidean;

    class_<LogEuclidean>(aModule, "LogEuclidean")

        .def(
            init<const VectorXd&, const Array<MatrixXd>&>(),
            R"doc(
                Create a Log-Euclidean interpolator for symmetric positive definite matrices.

                Performs interpolation on the Riemannian manifold of SPD matrices using the
                Log-Euclidean metric. Matrices are mapped to the tangent space via the matrix
                logarithm, linearly interpolated, and mapped back via the matrix exponential.

                Args:
                    x (np.array): The x-coordinates of data points (must be sorted ascending).
                    matrices (list[np.ndarray]): List of symmetric positive definite matrices.

                Example:
                    >>> import numpy as np
                    >>> x = np.array([0.0, 1.0])
                    >>> P0 = np.eye(3)
                    >>> P1 = np.diag([4.0, 9.0, 16.0])
                    >>> interpolator = LogEuclidean(x, [P0, P1])
            )doc",
            arg("x"),
            arg("matrices")
        )

        .def(
            "evaluate",
            overload_cast<const double&>(&LogEuclidean::evaluate, const_),
            R"doc(
                Evaluate the interpolation at a single point.

                Args:
                    x (float): The x-coordinate to evaluate at.

                Returns:
                    np.ndarray: The interpolated symmetric positive definite matrix.

                Example:
                    >>> result = interpolator.evaluate(0.5)
            )doc",
            arg("x")
        )
        .def(
            "evaluate",
            overload_cast<const VectorXd&>(&LogEuclidean::evaluate, const_),
            R"doc(
                Evaluate the interpolation at multiple points.

                Args:
                    x (np.array): The x-coordinates to evaluate at.

                Returns:
                    list[np.ndarray]: List of interpolated symmetric positive definite matrices.

                Example:
                    >>> results = interpolator.evaluate(np.array([0.0, 0.5, 1.0]))
            )doc",
            arg("x")
        )

        .def_static(
            "matrix_log_spd",
            &LogEuclidean::MatrixLogSPD,
            R"doc(
                Compute the matrix logarithm of a symmetric positive definite matrix.

                Uses spectral decomposition: log(P) = Q * log(Lambda) * Q^T

                Args:
                    matrix (np.ndarray): A symmetric positive definite matrix.

                Returns:
                    np.ndarray: The matrix logarithm.

                Example:
                    >>> log_m = LogEuclidean.matrix_log_spd(np.eye(3))  # Returns zero matrix
            )doc",
            arg("matrix")
        )
        .def_static(
            "matrix_exp_symmetric",
            &LogEuclidean::MatrixExpSymmetric,
            R"doc(
                Compute the matrix exponential of a symmetric matrix.

                Uses spectral decomposition: exp(S) = Q * exp(Lambda) * Q^T

                Args:
                    matrix (np.ndarray): A symmetric matrix.

                Returns:
                    np.ndarray: The matrix exponential (symmetric positive definite).

                Example:
                    >>> exp_m = LogEuclidean.matrix_exp_symmetric(np.zeros((3, 3)))  # Returns identity
            )doc",
            arg("matrix")
        )
        .def_static(
            "interpolate",
            &LogEuclidean::Interpolate,
            R"doc(
                Interpolate between two SPD matrices using the Log-Euclidean metric.

                Args:
                    first_matrix (np.ndarray): First symmetric positive definite matrix.
                    second_matrix (np.ndarray): Second symmetric positive definite matrix.
                    ratio (float): Interpolation ratio in [0, 1].

                Returns:
                    np.ndarray: Interpolated symmetric positive definite matrix.

                Example:
                    >>> result = LogEuclidean.interpolate(np.eye(3), 4.0 * np.eye(3), 0.5)
            )doc",
            arg("first_matrix"),
            arg("second_matrix"),
            arg("ratio")
        )

        ;
}
