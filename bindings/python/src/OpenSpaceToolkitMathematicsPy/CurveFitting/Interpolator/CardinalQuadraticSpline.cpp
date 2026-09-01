/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/CardinalQuadraticSpline.hpp>

inline void OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolator_CardinalQuadraticSpline(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;
    using ostk::core::type::Shared;

    using ostk::mathematics::curvefitting::Interpolator;
    using ostk::mathematics::object::VectorXd;

    using ostk::mathematics::curvefitting::interpolator::CardinalQuadraticSpline;

    class_<CardinalQuadraticSpline, Interpolator, Shared<CardinalQuadraticSpline>>(aModule, "CardinalQuadraticSpline")

        .def(
            init<const VectorXd&, const VectorXd&>(),
            R"doc(
                Create a cardinal quadratic spline interpolator with data points.

                Args:
                    x (np.array): The x-coordinates of data points, sorted in ascending order and equally spaced.
                    y (np.array): The y-coordinates of data points. At least 3 are required.

                Example:
                    >>> x = np.array([0.0, 1.0, 2.0, 3.0])
                    >>> y = np.array([2.0, 0.0, 0.0, 2.0])
                    >>> interpolator = CardinalQuadraticSpline(x, y)
            )doc",
            arg("x"),
            arg("y")
        )
        .def(
            init<const VectorXd&, const Real&, const Real&>(),
            R"doc(
                Create a cardinal quadratic spline interpolator with uniform spacing.

                Args:
                    y (np.array): The y-coordinates of data points. At least 3 are required.
                    x_0 (float): The starting x-coordinate.
                    h (float): The uniform spacing between x-coordinates.

                Example:
                    >>> y = np.array([2.0, 0.0, 0.0, 2.0])
                    >>> interpolator = CardinalQuadraticSpline(y, 0.0, 1.0)  # x = [0, 1, 2, 3]
            )doc",
            arg("y"),
            arg("x_0"),
            arg("h")
        )

        .def(
            "evaluate",
            overload_cast<const VectorXd&>(&CardinalQuadraticSpline::evaluate, const_),
            R"doc(
                Evaluate the cardinal quadratic spline interpolation at multiple points.

                Args:
                    x (np.array): The x-coordinates to evaluate at. Must lie within the interpolation domain.

                Returns:
                    (np.array): The interpolated y-values.

                Example:
                    >>> interpolator = CardinalQuadraticSpline([2.0, 0.0, 0.0, 2.0], 0.0, 1.0)
                    >>> result = interpolator.evaluate([0.5, 1.5])
            )doc",
            arg("x")
        )
        .def(
            "evaluate",
            overload_cast<const double&>(&CardinalQuadraticSpline::evaluate, const_),
            R"doc(
                Evaluate the cardinal quadratic spline interpolation at a single point.

                Args:
                    x (float): The x-coordinate to evaluate at. Must lie within the interpolation domain.

                Returns:
                    float: The interpolated y-value.

                Example:
                    >>> interpolator = CardinalQuadraticSpline([2.0, 0.0, 0.0, 2.0], 0.0, 1.0)
                    >>> result = interpolator.evaluate(1.5)
            )doc",
            arg("x")
        )
        .def(
            "compute_derivative",
            overload_cast<const double&>(&CardinalQuadraticSpline::computeDerivative, const_),
            R"doc(
                Compute the derivative of the cardinal quadratic spline at a single point.

                Args:
                    x (float): The x-coordinate to compute derivative at. Must lie within the interpolation domain.

                Returns:
                    float: The derivative value.

                Example:
                    >>> interpolator = CardinalQuadraticSpline([2.0, 0.0, 0.0, 2.0], 0.0, 1.0)
                    >>> derivative = interpolator.compute_derivative(1.5)
            )doc",
            arg("x")
        )
        .def(
            "compute_derivative",
            overload_cast<const VectorXd&>(&CardinalQuadraticSpline::computeDerivative, const_),
            R"doc(
                Compute the derivative of the cardinal quadratic spline at multiple points.

                Args:
                    x (np.array): The x-coordinates to compute derivatives at. Must lie within the interpolation domain.

                Returns:
                    (np.array): The derivative values.

                Example:
                    >>> interpolator = CardinalQuadraticSpline([2.0, 0.0, 0.0, 2.0], 0.0, 1.0)
                    >>> derivatives = interpolator.compute_derivative([0.5, 1.5])
            )doc",
            arg("x")
        )

        ;
}
