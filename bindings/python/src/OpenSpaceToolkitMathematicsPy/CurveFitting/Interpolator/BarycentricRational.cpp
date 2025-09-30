/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/BarycentricRational.hpp>

inline void OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolator_BarycentricRational(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Shared;

    using ostk::mathematics::curvefitting::Interpolator;
    using ostk::mathematics::object::VectorXd;

    using ostk::mathematics::curvefitting::interpolator::BarycentricRational;

    class_<BarycentricRational, Interpolator, Shared<BarycentricRational>>(aModule, "BarycentricRational")

        .def(
            init<const VectorXd&, const VectorXd&>(),
            R"doc(
                Create a barycentric rational interpolator with data points.

                Args:
                    x (np.array): The x-coordinates of data points.
                    y (np.array): The y-coordinates of data points.

                Example:
                    >>> x = np.array([0.0, 1.0, 2.0, 3.0])
                    >>> y = np.array([1.0, 2.0, 0.5, 3.0])
                    >>> interpolator = BarycentricRational(x, y)
            )doc",
            arg("x"),
            arg("y")
        )

        .def(
            "evaluate",
            overload_cast<const VectorXd&>(&BarycentricRational::evaluate, const_),
            R"doc(
                Evaluate the barycentric rational interpolation at multiple points.

                Args:
                    x (np.array): The x-coordinates to evaluate at.

                Returns:
                    (np.array): The interpolated y-values.

                Example:
                    >>> interpolator = BarycentricRational([0.0, 1.0, 2.0], [1.0, 2.0, 0.5])
                    >>> result = interpolator.evaluate([0.5, 1.5])
            )doc",
            arg("x")
        )
        .def(
            "evaluate",
            overload_cast<const double&>(&BarycentricRational::evaluate, const_),
            R"doc(
                Evaluate the barycentric rational interpolation at a single point.

                Args:
                    x (float): The x-coordinate to evaluate at.

                Returns:
                    float: The interpolated y-value.

                Example:
                    >>> interpolator = BarycentricRational([0.0, 1.0, 2.0], [1.0, 2.0, 0.5])
                    >>> result = interpolator.evaluate(0.5)
            )doc",
            arg("x")
        )
        .def(
            "compute_derivative",
            overload_cast<const double&>(&BarycentricRational::computeDerivative, const_),
            R"doc(
                Compute the derivative of the barycentric rational interpolation at a single point.

                Args:
                    x (float): The x-coordinate to compute derivative at.

                Returns:
                    float: The derivative value.

                Example:
                    >>> interpolator = BarycentricRational([0.0, 1.0, 2.0], [1.0, 2.0, 0.5])
                    >>> derivative = interpolator.compute_derivative(0.5)
            )doc",
            arg("x")
        )
        .def(
            "compute_derivative",
            overload_cast<const VectorXd&>(&BarycentricRational::computeDerivative, const_),
            R"doc(
                Compute the derivative of the barycentric rational interpolation at multiple points.

                Args:
                    x (np.array): The x-coordinates to compute derivatives at.

                Returns:
                    (np.array): The derivative values.

                Example:
                    >>> interpolator = BarycentricRational([0.0, 1.0, 2.0], [1.0, 2.0, 0.5])
                    >>> derivatives = interpolator.compute_derivative([0.2, 0.8])
            )doc",
            arg("x")
        )

        ;
}
