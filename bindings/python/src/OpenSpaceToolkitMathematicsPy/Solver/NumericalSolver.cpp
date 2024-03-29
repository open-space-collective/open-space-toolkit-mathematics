/// Apache License 2.0

#include <OpenSpaceToolkit/Mathematics/Solver/NumericalSolver.hpp>

inline void OpenSpaceToolkitMathematicsPy_Solver_NumericalSolver(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::container::Array;
    using ostk::core::type::Integer;
    using ostk::core::type::Real;
    using ostk::core::type::String;

    using ostk::mathematics::solver::NumericalSolver;

    typedef std::function<NumericalSolver::StateVector(
        const NumericalSolver::StateVector& x, NumericalSolver::StateVector& dxdt, const double t
    )>
        pythonSystemOfEquationsSignature;

    {
        class_<NumericalSolver> numericalSolver(aModule, "NumericalSolver");

        numericalSolver

            .def(
                init<
                    const NumericalSolver::LogType&,
                    const NumericalSolver::StepperType&,
                    const Real&,
                    const Real&,
                    const Real&>(),
                arg("log_type"),
                arg("stepper_type"),
                arg("time_step"),
                arg("relative_tolerance"),
                arg("absolute_tolerance")
            )

            .def(self == self)
            .def(self != self)

            .def("__str__", &(shiftToString<NumericalSolver>))
            .def("__repr__", &(shiftToString<NumericalSolver>))

            .def("is_defined", &NumericalSolver::isDefined)

            .def("get_stepper_type", &NumericalSolver::getStepperType)
            .def("get_log_type", &NumericalSolver::getLogType)
            .def("get_time_step", &NumericalSolver::getTimeStep)
            .def("get_relative_tolerance", &NumericalSolver::getRelativeTolerance)
            .def("get_absolute_tolerance", &NumericalSolver::getAbsoluteTolerance)
            .def("get_observed_state_vectors", &NumericalSolver::getObservedStateVectors)

            .def(
                "integrate_duration",
                +[](NumericalSolver& aNumericalSolver,
                    const NumericalSolver::StateVector& aStateVector,
                    const Real& aDurationInSeconds,
                    const object& aSystemOfEquationsObject)
                {
                    const auto pythonDynamicsEquation =
                        pybind11::cast<pythonSystemOfEquationsSignature>(aSystemOfEquationsObject);

                    const NumericalSolver::SystemOfEquationsWrapper& systemOfEquations =
                        [&](const NumericalSolver::StateVector& x, NumericalSolver::StateVector& dxdt, const double t
                        ) -> void
                    {
                        dxdt = pythonDynamicsEquation(x, dxdt, t);
                    };

                    return aNumericalSolver.integrateDuration(aStateVector, aDurationInSeconds, systemOfEquations);
                }
            )

            .def(
                "integrate_duration",
                +[](NumericalSolver& aNumericalSolver,
                    const NumericalSolver::StateVector& aStateVector,
                    const Array<Real>& aDurationArray,
                    const object& aSystemOfEquationsObject)
                {
                    const auto pythonDynamicsEquation =
                        pybind11::cast<pythonSystemOfEquationsSignature>(aSystemOfEquationsObject);

                    const NumericalSolver::SystemOfEquationsWrapper& systemOfEquations =
                        [&](const NumericalSolver::StateVector& x, NumericalSolver::StateVector& dxdt, const double t
                        ) -> void
                    {
                        dxdt = pythonDynamicsEquation(x, dxdt, t);
                    };

                    return aNumericalSolver.integrateDuration(aStateVector, aDurationArray, systemOfEquations);
                }
            )

            .def(
                "integrate_time",
                +[](NumericalSolver& aNumericalSolver,
                    const NumericalSolver::StateVector& aStateVector,
                    const Real& aStartTime,
                    const Real& anEndTime,
                    const object& aSystemOfEquationsObject)
                {
                    const auto pythonDynamicsEquation =
                        pybind11::cast<pythonSystemOfEquationsSignature>(aSystemOfEquationsObject);

                    const NumericalSolver::SystemOfEquationsWrapper& systemOfEquations =
                        [&](const NumericalSolver::StateVector& x, NumericalSolver::StateVector& dxdt, const double t
                        ) -> void
                    {
                        dxdt = pythonDynamicsEquation(x, dxdt, t);
                    };

                    return aNumericalSolver.integrateTime(aStateVector, aStartTime, anEndTime, systemOfEquations);
                }
            )

            .def(
                "integrate_time",
                +[](NumericalSolver& aNumericalSolver,
                    const NumericalSolver::StateVector& aStateVector,
                    const Real& aStartTime,
                    const Array<Real>& aTimeArray,
                    const object& aSystemOfEquationsObject)
                {
                    const auto pythonDynamicsEquation =
                        pybind11::cast<pythonSystemOfEquationsSignature>(aSystemOfEquationsObject);

                    const NumericalSolver::SystemOfEquationsWrapper& systemOfEquations =
                        [&](const NumericalSolver::StateVector& x, NumericalSolver::StateVector& dxdt, const double t
                        ) -> void
                    {
                        dxdt = pythonDynamicsEquation(x, dxdt, t);
                    };

                    return aNumericalSolver.integrateTime(aStateVector, aStartTime, aTimeArray, systemOfEquations);
                }
            )

            .def_static("string_from_stepper_type", &NumericalSolver::StringFromStepperType, arg("stepper_type"))
            .def_static("string_from_log_type", &NumericalSolver::StringFromLogType, arg("log_type"))
            .def_static("default", &NumericalSolver::Default)
            .def_static("undefined", &NumericalSolver::Undefined)

            ;

        enum_<NumericalSolver::StepperType>(numericalSolver, "StepperType")

            .value("RungeKutta4", NumericalSolver::StepperType::RungeKutta4)
            .value("RungeKuttaCashKarp54", NumericalSolver::StepperType::RungeKuttaCashKarp54)
            .value("RungeKuttaFehlberg78", NumericalSolver::StepperType::RungeKuttaFehlberg78)
            .value("RungeKuttaDopri5", NumericalSolver::StepperType::RungeKuttaDopri5)

            ;

        enum_<NumericalSolver::LogType>(numericalSolver, "LogType")

            .value("NoLog", NumericalSolver::LogType::NoLog)
            .value("LogConstant", NumericalSolver::LogType::LogConstant)
            .value("LogAdaptive", NumericalSolver::LogType::LogAdaptive)

            ;
    }
}
