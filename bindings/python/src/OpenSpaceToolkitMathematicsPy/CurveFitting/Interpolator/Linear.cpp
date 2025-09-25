/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/Linear.hpp>

inline void OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolator_Linear(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;

    using ostk::mathematics::curvefitting::Interpolator;
    using ostk::mathematics::object::VectorXd;

    using ostk::mathematics::curvefitting::interpolator::Linear;

    class_<Linear, Interpolator, Shared<Linear>>(aModule, "Linear")

        .def(
            init<const VectorXd&, const VectorXd&>(),
            R"doc(
                Create a linear interpolator with data points.

                Args:
                    x (VectorXd): The x-coordinates of data points.
                    y (VectorXd): The y-coordinates of data points.

                Example:
                    >>> x = VectorXd([0.0, 1.0, 2.0])
                    >>> y = VectorXd([0.0, 2.0, 4.0])
                    >>> interpolator = Linear(x, y)
            )doc",
            arg("x"),
            arg("y")
        )

        .def(
            "evaluate",
            overload_cast<const VectorXd&>(&Linear::evaluate, const_),
            R"doc(
                Evaluate the linear interpolation at multiple points.

                Args:
                    x (VectorXd): The x-coordinates to evaluate at.

                Returns:
                    VectorXd: The interpolated y-values.

                Example:
                    >>> interpolator = Linear([0.0, 1.0], [0.0, 2.0])
                    >>> result = interpolator.evaluate([0.5, 1.5])
            )doc",
            arg("x")
        )
        .def(
            "evaluate",
            overload_cast<const double&>(&Linear::evaluate, const_),
            R"doc(
                Evaluate the linear interpolation at a single point.

                Args:
                    x (float): The x-coordinate to evaluate at.

                Returns:
                    float: The interpolated y-value.

                Example:
                    >>> interpolator = Linear([0.0, 1.0], [0.0, 2.0])
                    >>> result = interpolator.evaluate(0.5)  # 1.0
            )doc",
            arg("x")
        )
        .def(
            "compute_derivative",
            overload_cast<const double&>(&Linear::computeDerivative, const_),
            R"doc(
                Compute the derivative of the linear interpolation at a single point.

                Args:
                    x (float): The x-coordinate to compute derivative at.

                Returns:
                    float: The derivative value.

                Example:
                    >>> interpolator = Linear([0.0, 1.0], [0.0, 2.0])
                    >>> derivative = interpolator.compute_derivative(0.5)  # 2.0
            )doc",
            arg("x")
        )
        .def(
            "compute_derivative",
            overload_cast<const VectorXd&>(&Linear::computeDerivative, const_),
            R"doc(
                Compute the derivative of the linear interpolation at multiple points.

                Args:
                    x (VectorXd): The x-coordinates to compute derivatives at.

                Returns:
                    VectorXd: The derivative values.

                Example:
                    >>> interpolator = Linear([0.0, 1.0], [0.0, 2.0])
                    >>> derivatives = interpolator.compute_derivative([0.2, 0.8])
            )doc",
            arg("x")
        )

        ;
}
