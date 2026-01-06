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
                R"doc(
                    Create a numerical solver with specified parameters.

                    Args:
                        log_type (NumericalSolver.LogType): The logging type for the solver.
                        stepper_type (NumericalSolver.StepperType): The stepper algorithm to use.
                        time_step (float): The time step for integration.
                        relative_tolerance (float): The relative tolerance for adaptive steppers.
                        absolute_tolerance (float): The absolute tolerance for adaptive steppers.

                    Example:
                        >>> solver = NumericalSolver(
                        ...     NumericalSolver.LogType.NoLog,
                        ...     NumericalSolver.StepperType.RungeKutta4,
                        ...     1.0, 1e-12, 1e-12
                        ... )
                )doc",
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

            .def(
                "is_defined",
                &NumericalSolver::isDefined,
                R"doc(
                    Check if the numerical solver is defined.

                    Returns:
                        bool: True if the solver is defined, False otherwise.

                    Example:
                        >>> solver = NumericalSolver.default()
                        >>> solver.is_defined()  # True
                )doc"
            )

            .def(
                "get_stepper_type",
                &NumericalSolver::getStepperType,
                R"doc(
                    Get the stepper type of the solver.

                    Returns:
                        NumericalSolver.StepperType: The stepper type.

                    Example:
                        >>> solver = NumericalSolver.default()
                        >>> stepper_type = solver.get_stepper_type()
                )doc"
            )
            .def(
                "get_log_type",
                &NumericalSolver::getLogType,
                R"doc(
                    Get the log type of the solver.

                    Returns:
                        NumericalSolver.LogType: The log type.

                    Example:
                        >>> solver = NumericalSolver.default()
                        >>> log_type = solver.get_log_type()
                )doc"
            )
            .def(
                "get_time_step",
                &NumericalSolver::getTimeStep,
                R"doc(
                    Get the time step of the solver.

                    Returns:
                        float: The time step value.

                    Example:
                        >>> solver = NumericalSolver.default()
                        >>> time_step = solver.get_time_step()
                )doc"
            )
            .def(
                "get_relative_tolerance",
                &NumericalSolver::getRelativeTolerance,
                R"doc(
                    Get the relative tolerance of the solver.

                    Returns:
                        float: The relative tolerance value.

                    Example:
                        >>> solver = NumericalSolver.default()
                        >>> rel_tol = solver.get_relative_tolerance()
                )doc"
            )
            .def(
                "get_absolute_tolerance",
                &NumericalSolver::getAbsoluteTolerance,
                R"doc(
                    Get the absolute tolerance of the solver.

                    Returns:
                        float: The absolute tolerance value.

                    Example:
                        >>> solver = NumericalSolver.default()
                        >>> abs_tol = solver.get_absolute_tolerance()
                )doc"
            )
            .def(
                "get_observed_state_vectors",
                &NumericalSolver::getObservedStateVectors,
                R"doc(
                    Get the observed state vectors from the last integration.

                    Returns:
                        list: List of observed state vectors during integration.

                    Example:
                        >>> solver = NumericalSolver.default()
                        >>> # After performing integration...
                        >>> states = solver.get_observed_state_vectors()
                )doc"
            )

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
                },
                R"doc(
                    Integrate a system of differential equations for a specified duration.

                    Args:
                        state_vector (StateVector): Initial state vector.
                        duration_in_seconds (float): Integration duration in seconds.
                        system_of_equations (callable): Function defining the system of ODEs.
                                                       Signature: f(x, dxdt, t) -> StateVector

                    Returns:
                        StateVector: Final state vector after integration.

                    Example:
                        >>> def equations(x, dxdt, t):
                        ...     dxdt[0] = x[1]  # dx/dt = v
                        ...     dxdt[1] = -x[0]  # dv/dt = -x (harmonic oscillator)
                        ...     return dxdt
                        >>> solver = NumericalSolver.default()
                        >>> initial_state = [1.0, 0.0]  # x=1, v=0
                        >>> final_state = solver.integrate_duration(initial_state, 1.0, equations)
                )doc"
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
                },
                R"doc(
                    Integrate a system of differential equations at multiple duration points.

                    Args:
                        state_vector (StateVector): Initial state vector.
                        duration_array (list): Array of duration values in seconds.
                        system_of_equations (callable): Function defining the system of ODEs.
                                                       Signature: f(x, dxdt, t) -> StateVector

                    Returns:
                        list: State vectors at each duration point.

                    Example:
                        >>> def equations(x, dxdt, t):
                        ...     dxdt[0] = x[1]  # dx/dt = v
                        ...     dxdt[1] = -x[0]  # dv/dt = -x (harmonic oscillator)
                        ...     return dxdt
                        >>> solver = NumericalSolver.default()
                        >>> initial_state = [1.0, 0.0]
                        >>> durations = [0.5, 1.0, 1.5]
                        >>> states = solver.integrate_duration(initial_state, durations, equations)
                )doc"
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
                },
                R"doc(
                    Integrate a system of differential equations from start to end time.

                    Args:
                        state_vector (StateVector): Initial state vector.
                        start_time (float): Integration start time.
                        end_time (float): Integration end time.
                        system_of_equations (callable): Function defining the system of ODEs.
                                                       Signature: f(x, dxdt, t) -> StateVector

                    Returns:
                        StateVector: Final state vector at end time.

                    Example:
                        >>> def equations(x, dxdt, t):
                        ...     dxdt[0] = x[1]  # dx/dt = v
                        ...     dxdt[1] = -x[0]  # dv/dt = -x (harmonic oscillator)
                        ...     return dxdt
                        >>> solver = NumericalSolver.default()
                        >>> initial_state = [1.0, 0.0]
                        >>> final_state = solver.integrate_time(initial_state, 0.0, 2.0, equations)
                )doc"
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
                },
                R"doc(
                    Integrate a system of differential equations at specified time points.

                    Args:
                        state_vector (StateVector): Initial state vector.
                        start_time (float): Integration start time.
                        time_array (list): Array of time points to evaluate at.
                        system_of_equations (callable): Function defining the system of ODEs.
                                                       Signature: f(x, dxdt, t) -> StateVector

                    Returns:
                        list: State vectors at each time point.

                    Example:
                        >>> def equations(x, dxdt, t):
                        ...     dxdt[0] = x[1]  # dx/dt = v
                        ...     dxdt[1] = -x[0]  # dv/dt = -x (harmonic oscillator)
                        ...     return dxdt
                        >>> solver = NumericalSolver.default()
                        >>> initial_state = [1.0, 0.0]
                        >>> times = [0.5, 1.0, 1.5, 2.0]
                        >>> states = solver.integrate_time(initial_state, 0.0, times, equations)
                )doc"
            )

            .def_static(
                "string_from_stepper_type",
                &NumericalSolver::StringFromStepperType,
                R"doc(
                    Get string representation of a stepper type.

                    Args:
                        stepper_type (NumericalSolver.StepperType): The stepper type.

                    Returns:
                        str: String representation of the stepper type.

                    Example:
                        >>> NumericalSolver.string_from_stepper_type(NumericalSolver.StepperType.RungeKutta4)
                )doc",
                arg("stepper_type")
            )
            .def_static(
                "string_from_log_type",
                &NumericalSolver::StringFromLogType,
                R"doc(
                    Get string representation of a log type.

                    Args:
                        log_type (NumericalSolver.LogType): The log type.

                    Returns:
                        str: String representation of the log type.

                    Example:
                        >>> NumericalSolver.string_from_log_type(NumericalSolver.LogType.NoLog)
                )doc",
                arg("log_type")
            )
            .def_static(
                "default",
                &NumericalSolver::Default,
                R"doc(
                    Create a default numerical solver.

                    Returns:
                        NumericalSolver: A solver with default settings.

                    Example:
                        >>> solver = NumericalSolver.default()
                        >>> solver.is_defined()  # True
                )doc"
            )
            .def_static(
                "undefined",
                &NumericalSolver::Undefined,
                R"doc(
                    Create an undefined numerical solver.

                    Returns:
                        NumericalSolver: An undefined solver.

                    Example:
                        >>> solver = NumericalSolver.undefined()
                        >>> solver.is_defined()  # False
                )doc"
            )

            ;

        enum_<NumericalSolver::StepperType>(numericalSolver, "StepperType")

            .value("RungeKutta4", NumericalSolver::StepperType::RungeKutta4, "Runge-Kutta 4th order")
            .value(
                "RungeKuttaCashKarp54",
                NumericalSolver::StepperType::RungeKuttaCashKarp54,
                "Runge-Kutta Cash-Karp 5th order"
            )
            .value(
                "RungeKuttaFehlberg78",
                NumericalSolver::StepperType::RungeKuttaFehlberg78,
                "Runge-Kutta Fehlberg 7th order"
            )
            .value(
                "RungeKuttaDopri5",
                NumericalSolver::StepperType::RungeKuttaDopri5,
                "Runge-Kutta Dormand-Prince 5th order"
            )
            .value(
                "AdamsBashforthMoulton5",
                NumericalSolver::StepperType::AdamsBashforthMoulton5,
                "Adams-Bashforth-Moulton 5th order"
            )
            .value(
                "AdamsBashforthMoulton8",
                NumericalSolver::StepperType::AdamsBashforthMoulton8,
                "Adams-Bashforth-Moulton 8th order"
            )
            .value("BulirschStoer", NumericalSolver::StepperType::BulirschStoer, "Bulirsch-Stoer")

            ;

        enum_<NumericalSolver::LogType>(numericalSolver, "LogType")

            .value("NoLog", NumericalSolver::LogType::NoLog)
            .value("LogConstant", NumericalSolver::LogType::LogConstant)
            .value("LogAdaptive", NumericalSolver::LogType::LogAdaptive)

            ;
    }
}
