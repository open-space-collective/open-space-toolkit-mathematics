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

        .def(init<const Interpolator::Type&>(), arg("interpolation_type"))

        .def("get_interpolation_type", &Interpolator::getInterpolationType)

        .def("evaluate", overload_cast<const VectorXd&>(&Interpolator::evaluate, const_), arg("x"))
        .def("evaluate", overload_cast<const double&>(&Interpolator::evaluate, const_), arg("x"))

        .def_static(
            "generate_interpolator", &Interpolator::GenerateInterpolator, arg("interpolation_type"), arg("x"), arg("y")
        )

        ;

    // Create "interpolator" python submodule
    auto interpolator = aModule.def_submodule("interpolator");


    // Add object to python "interpolator" submodules
    OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolator_BarycentricRational(interpolator);
    OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolator_CubicSpline(interpolator);
    OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolator_Linear(interpolator);
}
