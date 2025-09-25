/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/CubicSpline.hpp>

inline void OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolator_CubicSpline(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Real;
    using ostk::core::type::Shared;

    using ostk::mathematics::curvefitting::Interpolator;
    using ostk::mathematics::object::VectorXd;

    using ostk::mathematics::curvefitting::interpolator::CubicSpline;

    class_<CubicSpline, Interpolator, Shared<CubicSpline>>(aModule, "CubicSpline")

        .def(
            init<const VectorXd&, const VectorXd&>(),
            R"doc(
                Create a cubic spline interpolator with data points.

                Args:
                    x (VectorXd): The x-coordinates of data points.
                    y (VectorXd): The y-coordinates of data points.

                Example:
                    >>> x = VectorXd([0.0, 1.0, 2.0, 3.0])
                    >>> y = VectorXd([0.0, 1.0, 4.0, 9.0])
                    >>> interpolator = CubicSpline(x, y)
            )doc",
            arg("x"),
            arg("y")
        )
        .def(
            init<const VectorXd&, const Real&, const Real&>(),
            R"doc(
                Create a cubic spline interpolator with uniform spacing.

                Args:
                    y (VectorXd): The y-coordinates of data points.
                    x_0 (float): The starting x-coordinate.
                    h (float): The uniform spacing between x-coordinates.

                Example:
                    >>> y = VectorXd([0.0, 1.0, 4.0, 9.0])
                    >>> interpolator = CubicSpline(y, 0.0, 1.0)  # x = [0, 1, 2, 3]
            )doc",
            arg("y"),
            arg("x_0"),
            arg("h")
        )

        .def(
            "evaluate",
            overload_cast<const VectorXd&>(&CubicSpline::evaluate, const_),
            R"doc(
                Evaluate the cubic spline interpolation at multiple points.

                Args:
                    x (VectorXd): The x-coordinates to evaluate at.

                Returns:
                    VectorXd: The interpolated y-values.

                Example:
                    >>> interpolator = CubicSpline([0.0, 1.0, 2.0], [0.0, 1.0, 4.0])
                    >>> result = interpolator.evaluate([0.5, 1.5])
            )doc",
            arg("x")
        )
        .def(
            "evaluate",
            overload_cast<const double&>(&CubicSpline::evaluate, const_),
            R"doc(
                Evaluate the cubic spline interpolation at a single point.

                Args:
                    x (float): The x-coordinate to evaluate at.

                Returns:
                    float: The interpolated y-value.

                Example:
                    >>> interpolator = CubicSpline([0.0, 1.0, 2.0], [0.0, 1.0, 4.0])
                    >>> result = interpolator.evaluate(0.5)
            )doc",
            arg("x")
        )
        .def(
            "compute_derivative",
            overload_cast<const double&>(&CubicSpline::computeDerivative, const_),
            R"doc(
                Compute the derivative of the cubic spline at a single point.

                Args:
                    x (float): The x-coordinate to compute derivative at.

                Returns:
                    float: The derivative value.

                Example:
                    >>> interpolator = CubicSpline([0.0, 1.0, 2.0], [0.0, 1.0, 4.0])
                    >>> derivative = interpolator.compute_derivative(0.5)
            )doc",
            arg("x")
        )
        .def(
            "compute_derivative",
            overload_cast<const VectorXd&>(&CubicSpline::computeDerivative, const_),
            R"doc(
                Compute the derivative of the cubic spline at multiple points.

                Args:
                    x (VectorXd): The x-coordinates to compute derivatives at.

                Returns:
                    VectorXd: The derivative values.

                Example:
                    >>> interpolator = CubicSpline([0.0, 1.0, 2.0], [0.0, 1.0, 4.0])
                    >>> derivatives = interpolator.compute_derivative([0.2, 0.8])
            )doc",
            arg("x")
        )

        ;
}
