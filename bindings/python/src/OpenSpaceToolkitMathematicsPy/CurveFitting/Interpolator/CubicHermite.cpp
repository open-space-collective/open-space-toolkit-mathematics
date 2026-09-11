/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/CubicHermite.hpp>

inline void OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolator_CubicHermite(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;
    using ostk::core::type::Shared;

    using ostk::mathematics::curvefitting::Interpolator;
    using ostk::mathematics::object::VectorXd;

    using ostk::mathematics::curvefitting::interpolator::CubicHermite;

    class_<CubicHermite, Interpolator, Shared<CubicHermite>>(aModule, "CubicHermite")

        .def(
            init<const VectorXd&, const VectorXd&, const VectorXd&>(),
            R"doc(
                Create a cubic Hermite interpolator with data points and their first derivatives.

                Args:
                    x (np.array): The x-coordinates of data points, sorted in strictly ascending order.
                    y (np.array): The y-coordinates of data points.
                    dydx (np.array): The first derivatives at the data points.

                Example:
                    >>> x = np.array([0.0, 1.0, 2.0, 3.0])
                    >>> y = np.array([0.0, 1.0, 4.0, 9.0])
                    >>> dydx = np.array([0.0, 2.0, 4.0, 6.0])
                    >>> interpolator = CubicHermite(x, y, dydx)
            )doc",
            arg("x"),
            arg("y"),
            arg("dydx")
        )
        .def(
            init<const VectorXd&, const VectorXd&, const Real&, const Real&>(),
            R"doc(
                Create a cubic Hermite interpolator with uniform spacing.

                Args:
                    y (np.array): The y-coordinates of data points.
                    dydx (np.array): The first derivatives at the data points.
                    x_0 (float): The starting x-coordinate.
                    h (float): The uniform spacing between x-coordinates.

                Example:
                    >>> y = np.array([0.0, 1.0, 4.0, 9.0])
                    >>> dydx = np.array([0.0, 2.0, 4.0, 6.0])
                    >>> interpolator = CubicHermite(y, dydx, 0.0, 1.0)  # x = [0, 1, 2, 3]
            )doc",
            arg("y"),
            arg("dydx"),
            arg("x_0"),
            arg("h")
        )

        .def(
            "evaluate",
            overload_cast<const VectorXd&>(&CubicHermite::evaluate, const_),
            R"doc(
                Evaluate the cubic Hermite interpolation at multiple points.

                Args:
                    x (np.array): The x-coordinates to evaluate at. Must lie within the interpolation domain.

                Returns:
                    (np.array): The interpolated y-values.

                Example:
                    >>> interpolator = CubicHermite([0.0, 1.0], [0.0, 1.0], [0.0, 2.0])
                    >>> result = interpolator.evaluate([0.25, 0.75])
            )doc",
            arg("x")
        )
        .def(
            "evaluate",
            overload_cast<const double&>(&CubicHermite::evaluate, const_),
            R"doc(
                Evaluate the cubic Hermite interpolation at a single point.

                Args:
                    x (float): The x-coordinate to evaluate at. Must lie within the interpolation domain.

                Returns:
                    float: The interpolated y-value.

                Example:
                    >>> interpolator = CubicHermite([0.0, 1.0], [0.0, 1.0], [0.0, 2.0])
                    >>> result = interpolator.evaluate(0.5)
            )doc",
            arg("x")
        )
        .def(
            "compute_derivative",
            overload_cast<const double&>(&CubicHermite::computeDerivative, const_),
            R"doc(
                Compute the derivative of the cubic Hermite interpolation at a single point.

                Args:
                    x (float): The x-coordinate to compute derivative at. Must lie within the interpolation domain.

                Returns:
                    float: The derivative value.

                Example:
                    >>> interpolator = CubicHermite([0.0, 1.0], [0.0, 1.0], [0.0, 2.0])
                    >>> derivative = interpolator.compute_derivative(0.5)
            )doc",
            arg("x")
        )
        .def(
            "compute_derivative",
            overload_cast<const VectorXd&>(&CubicHermite::computeDerivative, const_),
            R"doc(
                Compute the derivative of the cubic Hermite interpolation at multiple points.

                Args:
                    x (np.array): The x-coordinates to compute derivatives at. Must lie within the interpolation domain.

                Returns:
                    (np.array): The derivative values.

                Example:
                    >>> interpolator = CubicHermite([0.0, 1.0], [0.0, 1.0], [0.0, 2.0])
                    >>> derivatives = interpolator.compute_derivative([0.25, 0.75])
            )doc",
            arg("x")
        )

        ;
}
