/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/QuinticSpline.hpp>

inline void OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolator_QuinticSpline(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;
    using ostk::core::type::Shared;

    using ostk::mathematics::curvefitting::Interpolator;
    using ostk::mathematics::object::VectorXd;

    using ostk::mathematics::curvefitting::interpolator::QuinticSpline;

    class_<QuinticSpline, Interpolator, Shared<QuinticSpline>>(aModule, "QuinticSpline")

        .def(
            init<const VectorXd&, const VectorXd&>(),
            R"doc(
                Create a quintic spline interpolator with data points.

                Args:
                    x (np.array): The x-coordinates of data points, sorted in strictly ascending order. They need not be equally spaced.
                    y (np.array): The y-coordinates of data points. At least 8 are required.

                Example:
                    >>> x = np.arange(8.0)
                    >>> y = np.array([2.0, 0.0, 6.0, 56.0, 210.0, 552.0, 1190.0, 2256.0])
                    >>> interpolator = QuinticSpline(x, y)
            )doc",
            arg("x"),
            arg("y")
        )
        .def(
            init<const VectorXd&, const Real&, const Real&>(),
            R"doc(
                Create a quintic spline interpolator with uniform spacing.

                Args:
                    y (np.array): The y-coordinates of data points. At least 8 are required.
                    x_0 (float): The starting x-coordinate.
                    h (float): The uniform spacing between x-coordinates.

                Example:
                    >>> y = np.array([2.0, 0.0, 6.0, 56.0, 210.0, 552.0, 1190.0, 2256.0])
                    >>> interpolator = QuinticSpline(y, 0.0, 1.0)  # x = [0, 1, ..., 7]
            )doc",
            arg("y"),
            arg("x_0"),
            arg("h")
        )

        .def(
            "evaluate",
            overload_cast<const VectorXd&>(&QuinticSpline::evaluate, const_),
            R"doc(
                Evaluate the quintic spline interpolation at multiple points.

                Args:
                    x (np.array): The x-coordinates to evaluate at. Must lie within the interpolation domain.

                Returns:
                    (np.array): The interpolated y-values.

                Example:
                    >>> interpolator = QuinticSpline(y, 0.0, 1.0)
                    >>> result = interpolator.evaluate([1.5, 3.5])
            )doc",
            arg("x")
        )
        .def(
            "evaluate",
            overload_cast<const double&>(&QuinticSpline::evaluate, const_),
            R"doc(
                Evaluate the quintic spline interpolation at a single point.

                Args:
                    x (float): The x-coordinate to evaluate at. Must lie within the interpolation domain.

                Returns:
                    float: The interpolated y-value.

                Example:
                    >>> interpolator = QuinticSpline(y, 0.0, 1.0)
                    >>> result = interpolator.evaluate(1.5)
            )doc",
            arg("x")
        )
        .def(
            "compute_derivative",
            overload_cast<const double&>(&QuinticSpline::computeDerivative, const_),
            R"doc(
                Compute the derivative of the quintic spline at a single point.

                Args:
                    x (float): The x-coordinate to compute derivative at. Must lie within the interpolation domain.

                Returns:
                    float: The derivative value.

                Example:
                    >>> interpolator = QuinticSpline(y, 0.0, 1.0)
                    >>> derivative = interpolator.compute_derivative(1.5)
            )doc",
            arg("x")
        )
        .def(
            "compute_derivative",
            overload_cast<const VectorXd&>(&QuinticSpline::computeDerivative, const_),
            R"doc(
                Compute the derivative of the quintic spline at multiple points.

                Args:
                    x (np.array): The x-coordinates to compute derivatives at. Must lie within the interpolation domain.

                Returns:
                    (np.array): The derivative values.

                Example:
                    >>> interpolator = QuinticSpline(y, 0.0, 1.0)
                    >>> derivatives = interpolator.compute_derivative([1.5, 3.5])
            )doc",
            arg("x")
        )
        .def(
            "compute_second_derivative",
            overload_cast<const double&>(&QuinticSpline::computeSecondDerivative, const_),
            R"doc(
                Compute the second derivative of the quintic spline at a single point.

                Args:
                    x (float): The x-coordinate to compute the second derivative at. Must lie within the interpolation domain.

                Returns:
                    float: The second derivative value.

                Example:
                    >>> interpolator = QuinticSpline(y, 0.0, 1.0)
                    >>> second_derivative = interpolator.compute_second_derivative(1.5)
            )doc",
            arg("x")
        )
        .def(
            "compute_second_derivative",
            overload_cast<const VectorXd&>(&QuinticSpline::computeSecondDerivative, const_),
            R"doc(
                Compute the second derivative of the quintic spline at multiple points.

                Args:
                    x (np.array): The x-coordinates to compute the second derivatives at. Must lie within the interpolation domain.

                Returns:
                    (np.array): The second derivative values.

                Example:
                    >>> interpolator = QuinticSpline(y, 0.0, 1.0)
                    >>> second_derivatives = interpolator.compute_second_derivative([1.5, 3.5])
            )doc",
            arg("x")
        )

        ;
}
