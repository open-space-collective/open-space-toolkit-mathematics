/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/CurveFitting/QuaternionInterpolator/SLERP.hpp>

inline void OpenSpaceToolkitMathematicsPy_CurveFitting_QuaternionInterpolator_SLERP(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::container::Array;

    using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;
    using ostk::mathematics::object::VectorXd;

    using ostk::mathematics::curvefitting::quaternioninterpolator::SLERP;

    class_<SLERP>(aModule, "SLERP")

        .def(
            init<const VectorXd&, const Array<Quaternion>&>(),
            R"doc(
                Create a Spherical Linear Interpolation (SLERP) interpolator for quaternions.

                Performs interpolation of unit quaternions (orientations) using Spherical Linear
                Interpolation (SLERP). The interpolated quaternion is computed along the shortest
                great-circle arc on the unit hypersphere, ensuring a constant angular velocity
                between the two bracketing orientations.

                The input quaternions are normalized at construction time.

                Args:
                    x (np.array): The x-coordinates of data points (must be strictly monotonically increasing).
                    quaternions (list[Quaternion]): List of quaternions (all defined).

                Example:
                    >>> import numpy as np
                    >>> x = np.array([0.0, 1.0])
                    >>> interpolator = SLERP(x, [q0, q1])
            )doc",
            arg("x"),
            arg("quaternions")
        )

        .def(
            "evaluate",
            overload_cast<const double&>(&SLERP::evaluate, const_),
            R"doc(
                Evaluate the interpolation at a single point.

                Returns the interpolated (normalized) quaternion at the given x value.
                Values outside the x range are clamped to the nearest endpoint quaternion.

                Args:
                    x (float): The x-coordinate to evaluate at.

                Returns:
                    Quaternion: The interpolated quaternion.

                Example:
                    >>> result = interpolator.evaluate(0.5)
            )doc",
            arg("x")
        )
        .def(
            "evaluate",
            overload_cast<const VectorXd&>(&SLERP::evaluate, const_),
            R"doc(
                Evaluate the interpolation at multiple points.

                Args:
                    x (np.array): The x-coordinates to evaluate at.

                Returns:
                    list[Quaternion]: List of interpolated quaternions.

                Example:
                    >>> results = interpolator.evaluate(np.array([0.0, 0.5, 1.0]))
            )doc",
            arg("x")
        )

        .def(
            "get_quaternions",
            &SLERP::getQuaternions,
            R"doc(
                Get the (normalized) quaternions used by the interpolator.

                Returns:
                    list[Quaternion]: The list of quaternions.

                Example:
                    >>> quaternions = interpolator.get_quaternions()
            )doc"
        )

        ;
}
