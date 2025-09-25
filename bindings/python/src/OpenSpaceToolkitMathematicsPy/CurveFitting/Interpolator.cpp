/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator.hpp>

#include <OpenSpaceToolkitMathematicsPy/CurveFitting/Interpolator/BarycentricRational.cpp>
#include <OpenSpaceToolkitMathematicsPy/CurveFitting/Interpolator/CubicSpline.cpp>
#include <OpenSpaceToolkitMathematicsPy/CurveFitting/Interpolator/Linear.cpp>

using namespace pybind11;

using ostk::core::type::Shared;

using ostk::mathematics::curvefitting::Interpolator;
using ostk::mathematics::object::VectorXd;

// Trampoline class for virtual member functions
class PyInterpolator : public Interpolator
{
   public:
    using Interpolator::Interpolator;

    // Trampoline (need one for each virtual function)

    VectorXd evaluate(const VectorXd& aQueryVector) const override
    {
        PYBIND11_OVERRIDE_PURE(VectorXd, Interpolator, evaluate, aQueryVector);
    }

    double evaluate(const double& aQueryValue) const override
    {
        PYBIND11_OVERRIDE_PURE(double, Interpolator, evaluate, aQueryValue);
    }

    double computeDerivative(const double& aQueryValue) const override
    {
        PYBIND11_OVERRIDE_PURE(double, Interpolator, computeDerivative, aQueryValue);
    }

    VectorXd computeDerivative(const VectorXd& aQueryVector) const override
    {
        PYBIND11_OVERRIDE_PURE(VectorXd, Interpolator, computeDerivative, aQueryVector);
    }
};

inline void OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolator(pybind11::module& aModule)
{
    class_<Interpolator, PyInterpolator, Shared<Interpolator>> interpolator_class(aModule, "Interpolator");

    enum_<Interpolator::Type>(interpolator_class, "Type")

        .value("BarycentricRational", Interpolator::Type::BarycentricRational)
        .value("CubicSpline", Interpolator::Type::CubicSpline)
        .value("Linear", Interpolator::Type::Linear)

        ;

    interpolator_class

        .def(
            init<const Interpolator::Type&>(),
            R"doc(
                Create an interpolator of specified type.

                Args:
                    interpolation_type (Interpolator.Type): The type of interpolation method.

                Example:
                    >>> interpolator = Interpolator(Interpolator.Type.Linear)
            )doc",
            arg("interpolation_type")
        )

        .def(
            "get_interpolation_type",
            &Interpolator::getInterpolationType,
            R"doc(
                Get the interpolation type of this interpolator.

                Returns:
                    Interpolator.Type: The interpolation type.

                Example:
                    >>> interpolator = Interpolator(Interpolator.Type.CubicSpline)
                    >>> type = interpolator.get_interpolation_type()
            )doc"
        )

        .def(
            "evaluate",
            overload_cast<const VectorXd&>(&Interpolator::evaluate, const_),
            R"doc(
                Evaluate the interpolation at multiple points.

                Args:
                    x (VectorXd): The x-coordinates to evaluate at.

                Returns:
                    VectorXd: The interpolated y-values.

                Example:
                    >>> interpolator = Interpolator.generate_interpolator(
                    ...     Interpolator.Type.Linear, [0.0, 1.0], [0.0, 2.0]
                    ... )
                    >>> result = interpolator.evaluate([0.5, 1.5])
            )doc",
            arg("x")
        )
        .def(
            "evaluate",
            overload_cast<const double&>(&Interpolator::evaluate, const_),
            R"doc(
                Evaluate the interpolation at a single point.

                Args:
                    x (float): The x-coordinate to evaluate at.

                Returns:
                    float: The interpolated y-value.

                Example:
                    >>> interpolator = Interpolator.generate_interpolator(
                    ...     Interpolator.Type.Linear, [0.0, 1.0], [0.0, 2.0]
                    ... )
                    >>> result = interpolator.evaluate(0.5)  # 1.0
            )doc",
            arg("x")
        )
        .def(
            "compute_derivative",
            overload_cast<const double&>(&Interpolator::computeDerivative, const_),
            R"doc(
                Compute the derivative of the interpolation at a single point.

                Args:
                    x (float): The x-coordinate to compute derivative at.

                Returns:
                    float: The derivative value.

                Example:
                    >>> interpolator = Interpolator.generate_interpolator(
                    ...     Interpolator.Type.Linear, [0.0, 1.0], [0.0, 2.0]
                    ... )
                    >>> derivative = interpolator.compute_derivative(0.5)  # 2.0
            )doc",
            arg("x")
        )
        .def(
            "compute_derivative",
            overload_cast<const VectorXd&>(&Interpolator::computeDerivative, const_),
            R"doc(
                Compute the derivative of the interpolation at multiple points.

                Args:
                    x (VectorXd): The x-coordinates to compute derivatives at.

                Returns:
                    VectorXd: The derivative values.

                Example:
                    >>> interpolator = Interpolator.generate_interpolator(
                    ...     Interpolator.Type.Linear, [0.0, 1.0], [0.0, 2.0]
                    ... )
                    >>> derivatives = interpolator.compute_derivative([0.2, 0.8])
            )doc",
            arg("x")
        )

        .def_static(
            "generate_interpolator",
            &Interpolator::GenerateInterpolator,
            R"doc(
                Generate an interpolator of specified type with data points.

                Args:
                    interpolation_type (Interpolator.Type): The type of interpolation.
                    x (VectorXd): The x-coordinates of data points.
                    y (VectorXd): The y-coordinates of data points.

                Returns:
                    Interpolator: A shared pointer to the created interpolator.

                Example:
                    >>> x = VectorXd([0.0, 1.0, 2.0])
                    >>> y = VectorXd([0.0, 2.0, 4.0])
                    >>> interpolator = Interpolator.generate_interpolator(
                    ...     Interpolator.Type.CubicSpline, x, y
                    ... )
            )doc",
            arg("interpolation_type"),
            arg("x"),
            arg("y")
        )

        ;

    // Create "interpolator" python submodule
    auto interpolator = aModule.def_submodule("interpolator");

    // Add object to python "interpolator" submodules
    OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolator_BarycentricRational(interpolator);
    OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolator_CubicSpline(interpolator);
    OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolator_Linear(interpolator);
}
