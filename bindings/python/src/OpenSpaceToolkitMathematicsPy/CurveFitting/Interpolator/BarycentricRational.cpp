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

        .def(init<const VectorXd&, const VectorXd&>(), arg("x"), arg("y"))

        .def("evaluate", overload_cast<const VectorXd&>(&BarycentricRational::evaluate, const_), arg("x"))
        .def("evaluate", overload_cast<const double&>(&BarycentricRational::evaluate, const_), arg("x"))
        .def(
            "compute_derivative",
            overload_cast<const double&>(&BarycentricRational::computeDerivative, const_),
            arg("x")
        )
        .def(
            "compute_derivative",
            overload_cast<const VectorXd&>(&BarycentricRational::computeDerivative, const_),
            arg("x")
        )

        ;
}
