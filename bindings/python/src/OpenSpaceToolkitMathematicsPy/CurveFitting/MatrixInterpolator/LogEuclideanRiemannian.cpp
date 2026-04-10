/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/CurveFitting/MatrixInterpolator/LogEuclideanRiemannian.hpp>

inline void OpenSpaceToolkitMathematicsPy_CurveFitting_MatrixInterpolator_LogEuclideanRiemannian(
    pybind11::module& aModule
)
{
    using namespace pybind11;

    using ostk::core::container::Array;

    using ostk::mathematics::object::MatrixXd;
    using ostk::mathematics::object::VectorXd;

    using ostk::mathematics::curvefitting::matrixinterpolator::LogEuclideanRiemannian;

    class_<LogEuclideanRiemannian>(aModule, "LogEuclideanRiemannian")

        .def(
            init<const VectorXd&, const Array<MatrixXd>&>(),
            R"doc(
                Create a Log-Euclidean Riemannian interpolator for symmetric positive definite matrices.

                Performs interpolation on the Riemannian manifold of symmetric positive definite (SPD)
                matrices using the Log-Euclidean metric. Matrices are mapped to the tangent space via
                the matrix logarithm, linearly interpolated, and mapped back via the matrix exponential.

                The input matrices must be symmetric positive definite (SPD). A matrix M is SPD if:
                - M is symmetric: M = M^T
                - All eigenvalues of M are strictly positive

                The matrix logarithms are precomputed at construction time for efficient interpolation.

                Args:
                    x (np.array): The x-coordinates of data points (must be strictly monotonically increasing).
                    matrices (list[np.ndarray]): List of symmetric positive definite matrices (all same dimensions).

                Example:
                    >>> import numpy as np
                    >>> x = np.array([0.0, 1.0])
                    >>> P0 = np.eye(3)
                    >>> P1 = np.diag([4.0, 9.0, 16.0])
                    >>> interpolator = LogEuclideanRiemannian(x, [P0, P1])
            )doc",
            arg("x"),
            arg("matrices")
        )

        .def(
            "evaluate",
            overload_cast<const double&>(&LogEuclideanRiemannian::evaluate, const_),
            R"doc(
                Evaluate the interpolation at a single point.

                Returns the interpolated symmetric positive definite matrix at the given x value.
                Values outside the x range are clamped to the nearest endpoint matrix.

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
            overload_cast<const VectorXd&>(&LogEuclideanRiemannian::evaluate, const_),
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

        .def(
            "get_matrices",
            &LogEuclideanRiemannian::getMatrices,
            R"doc(
                Get the symmetric positive definite matrices provided at construction.

                Returns:
                    list[np.ndarray]: The list of symmetric positive definite matrices.

                Example:
                    >>> matrices = interpolator.get_matrices()
            )doc"
        )

        ;
}
