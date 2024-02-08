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

        .def(init<const VectorXd&, const VectorXd&>(), arg("x"), arg("y"))

        .def("evaluate", overload_cast<const VectorXd&>(&Linear::evaluate, const_), arg("x"))
        .def("evaluate", overload_cast<const double&>(&Linear::evaluate, const_), arg("x"));
}
