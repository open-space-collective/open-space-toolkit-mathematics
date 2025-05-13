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

        .def(init<const VectorXd&, const VectorXd&>(), arg("x"), arg("y"))
        .def(init<const VectorXd&, const Real&, const Real&>(), arg("y"), arg("x_0"), arg("h"))

        .def("evaluate", overload_cast<const VectorXd&>(&CubicSpline::evaluate, const_), arg("x"))
        .def("evaluate", overload_cast<const double&>(&CubicSpline::evaluate, const_), arg("x"))
        .def("compute_derivative", overload_cast<const double&>(&CubicSpline::computeDerivative, const_), arg("x"))
        .def("compute_derivative", overload_cast<const VectorXd&>(&CubicSpline::computeDerivative, const_), arg("x"))

        ;
}
