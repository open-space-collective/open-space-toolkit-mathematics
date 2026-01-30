/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/ZeroOrder.hpp>

inline void OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolator_ZeroOrder(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;

    using ostk::mathematics::curvefitting::Interpolator;
    using ostk::mathematics::object::VectorXd;

    using ostk::mathematics::curvefitting::interpolator::ZeroOrder;

    class_<ZeroOrder, Interpolator, Shared<ZeroOrder>>(aModule, "ZeroOrder")

        .def(
            init<const VectorXd&, const VectorXd&>(),
            R"doc(
                Create a zero-order hold (step) interpolator with data points.

                For any query value x, returns the y value of the largest data point
                x_i where x_i <= x. Also known as "step" or "previous value" interpolation.

                Args:
                    x (np.array): The x-coordinates of data points.
                    y (np.array): The y-coordinates of data points.

                Example:
                    >>> x = np.array([0.0, 1.0, 2.0])
                    >>> y = np.array([0.0, 2.0, 4.0])
                    >>> interpolator = ZeroOrder(x, y)
                    >>> interpolator.evaluate(0.5)  # Returns 0.0 (value at x=0)
                    >>> interpolator.evaluate(1.5)  # Returns 2.0 (value at x=1)
            )doc",
            arg("x"),
            arg("y")
        )

        .def(
            "evaluate",
            overload_cast<const VectorXd&>(&ZeroOrder::evaluate, const_),
            R"doc(
                Evaluate the zero-order hold interpolation at multiple points.

                Args:
                    x (np.array): The x-coordinates to evaluate at.

                Returns:
                    (np.array): The interpolated y-values (previous data point values).

                Example:
                    >>> interpolator = ZeroOrder([0.0, 1.0, 2.0], [0.0, 2.0, 4.0])
                    >>> result = interpolator.evaluate([0.5, 1.5])  # [0.0, 2.0]
            )doc",
            arg("x")
        )
        .def(
            "evaluate",
            overload_cast<const double&>(&ZeroOrder::evaluate, const_),
            R"doc(
                Evaluate the zero-order hold interpolation at a single point.

                Args:
                    x (float): The x-coordinate to evaluate at.

                Returns:
                    float: The y-value of the previous data point.

                Example:
                    >>> interpolator = ZeroOrder([0.0, 1.0, 2.0], [0.0, 2.0, 4.0])
                    >>> result = interpolator.evaluate(0.5)  # 0.0
            )doc",
            arg("x")
        )
        .def(
            "compute_derivative",
            overload_cast<const double&>(&ZeroOrder::computeDerivative, const_),
            R"doc(
                Compute the derivative of the zero-order hold interpolation at a single point.

                Note: The derivative of a step function is always 0.0 (except at discontinuities).

                Args:
                    x (float): The x-coordinate to compute derivative at.

                Returns:
                    float: The derivative value (always 0.0).

                Example:
                    >>> interpolator = ZeroOrder([0.0, 1.0, 2.0], [0.0, 2.0, 4.0])
                    >>> derivative = interpolator.compute_derivative(0.5)  # 0.0
            )doc",
            arg("x")
        )
        .def(
            "compute_derivative",
            overload_cast<const VectorXd&>(&ZeroOrder::computeDerivative, const_),
            R"doc(
                Compute the derivative of the zero-order hold interpolation at multiple points.

                Note: The derivative of a step function is always 0.0 (except at discontinuities).

                Args:
                    x (np.array): The x-coordinates to compute derivatives at.

                Returns:
                    (np.array): The derivative values (always 0.0).

                Example:
                    >>> interpolator = ZeroOrder([0.0, 1.0, 2.0], [0.0, 2.0, 4.0])
                    >>> derivatives = interpolator.compute_derivative([0.2, 0.8])  # [0.0, 0.0]
            )doc",
            arg("x")
        )

        ;
}
