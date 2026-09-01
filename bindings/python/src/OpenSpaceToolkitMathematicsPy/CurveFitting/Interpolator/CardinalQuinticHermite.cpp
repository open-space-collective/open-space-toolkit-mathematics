/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/CardinalQuinticHermite.hpp>

inline void OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolator_CardinalQuinticHermite(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;
    using ostk::core::type::Shared;

    using ostk::mathematics::curvefitting::Interpolator;
    using ostk::mathematics::object::VectorXd;

    using ostk::mathematics::curvefitting::interpolator::CardinalQuinticHermite;

    class_<CardinalQuinticHermite, Interpolator, Shared<CardinalQuinticHermite>>(aModule, "CardinalQuinticHermite")

        .def(
            init<const VectorXd&, const VectorXd&, const VectorXd&, const VectorXd&>(),
            R"doc(
                Create a cardinal quintic Hermite interpolator with data points and their first and second derivatives.

                Args:
                    x (np.array): The x-coordinates of data points, sorted in ascending order and equally spaced.
                    y (np.array): The y-coordinates of data points.
                    dydx (np.array): The first derivatives at the data points.
                    d2ydx2 (np.array): The second derivatives at the data points.

                Example:
                    >>> x = np.array([0.0, 1.0, 2.0, 3.0])
                    >>> y = np.array([0.0, 1.0, 4.0, 9.0])
                    >>> dydx = np.array([0.0, 2.0, 4.0, 6.0])
                    >>> d2ydx2 = np.array([2.0, 2.0, 2.0, 2.0])
                    >>> interpolator = CardinalQuinticHermite(x, y, dydx, d2ydx2)
            )doc",
            arg("x"),
            arg("y"),
            arg("dydx"),
            arg("d2ydx2")
        )
        .def(
            init<const VectorXd&, const VectorXd&, const VectorXd&, const Real&, const Real&>(),
            R"doc(
                Create a cardinal quintic Hermite interpolator with uniform spacing.

                Args:
                    y (np.array): The y-coordinates of data points.
                    dydx (np.array): The first derivatives at the data points.
                    d2ydx2 (np.array): The second derivatives at the data points.
                    x_0 (float): The starting x-coordinate.
                    h (float): The uniform spacing between x-coordinates.

                Example:
                    >>> y = np.array([0.0, 1.0, 4.0, 9.0])
                    >>> dydx = np.array([0.0, 2.0, 4.0, 6.0])
                    >>> d2ydx2 = np.array([2.0, 2.0, 2.0, 2.0])
                    >>> interpolator = CardinalQuinticHermite(y, dydx, d2ydx2, 0.0, 1.0)  # x = [0, 1, 2, 3]
            )doc",
            arg("y"),
            arg("dydx"),
            arg("d2ydx2"),
            arg("x_0"),
            arg("h")
        )

        .def(
            "evaluate",
            overload_cast<const VectorXd&>(&CardinalQuinticHermite::evaluate, const_),
            R"doc(
                Evaluate the cardinal quintic Hermite interpolation at multiple points.

                Args:
                    x (np.array): The x-coordinates to evaluate at. Must lie within the interpolation domain.

                Returns:
                    (np.array): The interpolated y-values.

                Example:
                    >>> interpolator = CardinalQuinticHermite([0.0, 1.0], [0.0, 2.0], [2.0, 2.0], 0.0, 1.0)
                    >>> result = interpolator.evaluate([0.25, 0.75])
            )doc",
            arg("x")
        )
        .def(
            "evaluate",
            overload_cast<const double&>(&CardinalQuinticHermite::evaluate, const_),
            R"doc(
                Evaluate the cardinal quintic Hermite interpolation at a single point.

                Args:
                    x (float): The x-coordinate to evaluate at. Must lie within the interpolation domain.

                Returns:
                    float: The interpolated y-value.

                Example:
                    >>> interpolator = CardinalQuinticHermite([0.0, 1.0], [0.0, 2.0], [2.0, 2.0], 0.0, 1.0)
                    >>> result = interpolator.evaluate(0.5)
            )doc",
            arg("x")
        )
        .def(
            "compute_derivative",
            overload_cast<const double&>(&CardinalQuinticHermite::computeDerivative, const_),
            R"doc(
                Compute the derivative of the cardinal quintic Hermite interpolation at a single point.

                Args:
                    x (float): The x-coordinate to compute derivative at. Must lie within the interpolation domain.

                Returns:
                    float: The derivative value.

                Example:
                    >>> interpolator = CardinalQuinticHermite([0.0, 1.0], [0.0, 2.0], [2.0, 2.0], 0.0, 1.0)
                    >>> derivative = interpolator.compute_derivative(0.5)
            )doc",
            arg("x")
        )
        .def(
            "compute_derivative",
            overload_cast<const VectorXd&>(&CardinalQuinticHermite::computeDerivative, const_),
            R"doc(
                Compute the derivative of the cardinal quintic Hermite interpolation at multiple points.

                Args:
                    x (np.array): The x-coordinates to compute derivatives at. Must lie within the interpolation domain.

                Returns:
                    (np.array): The derivative values.

                Example:
                    >>> interpolator = CardinalQuinticHermite([0.0, 1.0], [0.0, 2.0], [2.0, 2.0], 0.0, 1.0)
                    >>> derivatives = interpolator.compute_derivative([0.25, 0.75])
            )doc",
            arg("x")
        )
        .def(
            "compute_second_derivative",
            overload_cast<const double&>(&CardinalQuinticHermite::computeSecondDerivative, const_),
            R"doc(
                Compute the second derivative of the cardinal quintic Hermite interpolation at a single point.

                Args:
                    x (float): The x-coordinate to compute the second derivative at. Must lie within the interpolation domain.

                Returns:
                    float: The second derivative value.

                Example:
                    >>> interpolator = CardinalQuinticHermite([0.0, 1.0], [0.0, 2.0], [2.0, 2.0], 0.0, 1.0)
                    >>> second_derivative = interpolator.compute_second_derivative(0.5)
            )doc",
            arg("x")
        )
        .def(
            "compute_second_derivative",
            overload_cast<const VectorXd&>(&CardinalQuinticHermite::computeSecondDerivative, const_),
            R"doc(
                Compute the second derivative of the cardinal quintic Hermite interpolation at multiple points.

                Args:
                    x (np.array): The x-coordinates to compute the second derivatives at. Must lie within the interpolation domain.

                Returns:
                    (np.array): The second derivative values.

                Example:
                    >>> interpolator = CardinalQuinticHermite([0.0, 1.0], [0.0, 2.0], [2.0, 2.0], 0.0, 1.0)
                    >>> second_derivatives = interpolator.compute_second_derivative([0.25, 0.75])
            )doc",
            arg("x")
        )

        ;
}
