/// Apache License 2.0

#include <utility>

#include <boost/numeric/odeint.hpp>
#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>
#include <boost/numeric/odeint/external/eigen/eigen.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utility.hpp>

#include <OpenSpaceToolkit/Mathematics/Solver/NumericalSolver.hpp>

#include <Eigen/Core>

namespace boost
{
namespace numeric
{
namespace odeint
{

// We create a specialized algebra that does element-wise operations required by the step-size PID controller
// used by multi-step adaptive steppers. This is because eigen *, / operations are matrix operations, not element-wise
// operations. https://www.boost.org/doc/libs/1_82_0/boost/numeric/odeint/algebra/vector_space_algebra.hpp

struct eigen_pid_algebra : public vector_space_algebra
{
    template <class S1, class S2, class Op>
    static void for_each2(S1& s1, S2& s2, Op op)
    {
        // Force Eigen into array mode for element-wise operations
        for (int i = 0; i < s1.size(); ++i)
            op(s1[i], s2[i]);
    }

    template <class S1, class S2, class S3, class S4, class Op>
    static void for_each4(S1& s1, S2& s2, S3& s3, S4& s4, Op op)
    {
        for (int i = 0; i < s1.size(); ++i)
            op(s1[i], s2[i], s3[i], s4[i]);
    }
};

}  // namespace odeint
}  // namespace numeric
}  // namespace boost

namespace ostk
{
namespace mathematics
{
namespace solver
{

using namespace boost::numeric::odeint;

using ostk::core::type::Index;

typedef runge_kutta4<NumericalSolver::StateVector> stepper_type_4;
typedef runge_kutta_cash_karp54<NumericalSolver::StateVector> error_stepper_type_54;
typedef runge_kutta_fehlberg78<NumericalSolver::StateVector> error_stepper_type_78;
typedef runge_kutta_dopri5<NumericalSolver::StateVector> dense_stepper_type_5;
typedef bulirsch_stoer<NumericalSolver::StateVector> bulirsch_stoer_stepper_type;

template <size_t Order>
auto make_controlled_adam_bashforth_moulton(double abs_tol, double rel_tol)
{
    // Define the underlying adaptive AdamsBashforthMoulton (using default template parameters)
    typedef adaptive_adams_bashforth_moulton<Order, NumericalSolver::StateVector> adaptive_stepper_type;

    // Define the Adjuster (where tolerances live)
    typedef detail::pid_step_adjuster<
        NumericalSolver::StateVector,
        double,
        NumericalSolver::StateVector,
        double,
        boost::numeric::odeint::eigen_pid_algebra>
        step_adjuster_type;

    // Define the controlled stepper
    typedef controlled_adams_bashforth_moulton<adaptive_stepper_type, step_adjuster_type> controlled_stepper_type;

    // Return the fully constructed controlled stepper
    return controlled_stepper_type(step_adjuster_type(abs_tol, rel_tol));
}

NumericalSolver::NumericalSolver(
    const NumericalSolver::LogType& aLogType,
    const NumericalSolver::StepperType& aStepperType,
    const Real& aTimeStep,
    const Real& aRelativeTolerance,
    const Real& anAbsoluteTolerance
)
    : logType_(aLogType),
      stepperType_(aStepperType),
      timeStep_(aTimeStep),
      relativeTolerance_(aRelativeTolerance),
      absoluteTolerance_(anAbsoluteTolerance),
      observedStateVectors_()
{
}

bool NumericalSolver::operator==(const NumericalSolver& aNumericalSolver) const
{
    if ((!this->isDefined()) || (!aNumericalSolver.isDefined()))
    {
        return false;
    }

    return (logType_ == aNumericalSolver.logType_) && (stepperType_ == aNumericalSolver.stepperType_) &&
           (timeStep_ == aNumericalSolver.timeStep_) && (relativeTolerance_ == aNumericalSolver.relativeTolerance_) &&
           (absoluteTolerance_ == aNumericalSolver.absoluteTolerance_);
}

bool NumericalSolver::operator!=(const NumericalSolver& aNumericalSolver) const
{
    return !((*this) == aNumericalSolver);
}

std::ostream& operator<<(std::ostream& anOutputStream, const NumericalSolver& aNumericalSolver)
{
    aNumericalSolver.print(anOutputStream);

    return anOutputStream;
}

bool NumericalSolver::isDefined() const
{
    return timeStep_.isDefined() && relativeTolerance_.isDefined() && absoluteTolerance_.isDefined();
}

void NumericalSolver::print(std::ostream& anOutputStream, bool displayDecorator) const
{
    displayDecorator ? ostk::core::utils::Print::Header(anOutputStream, "Numerical Solver") : void();

    ostk::core::utils::Print::Line(anOutputStream)
        << "Integration logging type:" << NumericalSolver::StringFromLogType(logType_);
    ostk::core::utils::Print::Line(anOutputStream)
        << "Integration stepper type:" << NumericalSolver::StringFromStepperType(stepperType_);
    ostk::core::utils::Print::Line(anOutputStream)
        << "Integration time step:" << (timeStep_.isDefined() ? timeStep_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Integration relative tolerance:"
        << (relativeTolerance_.isDefined() ? relativeTolerance_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Integration absolute tolerance:"
        << (absoluteTolerance_.isDefined() ? absoluteTolerance_.toString() : "Undefined");

    displayDecorator ? ostk::core::utils::Print::Footer(anOutputStream) : void();
}

const Array<NumericalSolver::Solution>& NumericalSolver::accessObservedStateVectors() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("NumericalSolver");
    }

    return this->observedStateVectors_;
}

NumericalSolver::LogType NumericalSolver::getLogType() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("NumericalSolver");
    }

    return this->logType_;
}

NumericalSolver::StepperType NumericalSolver::getStepperType() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("NumericalSolver");
    }

    return this->stepperType_;
}

Real NumericalSolver::getTimeStep() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("NumericalSolver");
    }

    return this->timeStep_;
}

Real NumericalSolver::getRelativeTolerance() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("NumericalSolver");
    }

    return this->relativeTolerance_;
}

Real NumericalSolver::getAbsoluteTolerance() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("NumericalSolver");
    }

    return this->absoluteTolerance_;
}

Array<NumericalSolver::Solution> NumericalSolver::getObservedStateVectors() const
{
    return Array<NumericalSolver::Solution>(this->accessObservedStateVectors());
}

Array<NumericalSolver::Solution> NumericalSolver::integrateTime(
    const StateVector& anInitialStateVector,
    const Real& aStartTime,
    const Array<Real>& aTimeArray,
    const NumericalSolver::SystemOfEquationsWrapper& aSystemOfEquations
)
{
    observedStateVectors_.clear();

    NumericalSolver::StateVector aStateVector = anInitialStateVector;

    // Check if time array has zero length
    if (aTimeArray.size() == 0)
    {
        throw ostk::core::error::RuntimeError("Time Array is empty");
    }

    // Check if the incoming time array is the same as the start time if it has length 1
    if ((aTimeArray.size() == 1) && (aTimeArray[0] == aStartTime))
    {
        return {
            {anInitialStateVector, aStartTime},
        };
    }

    // Ensure integration starts in the correct direction with the initial time step guess
    const double adjustedTimeStep = getSignedTimeStep(aTimeArray.accessLast());

    // Add start time to the start of array
    Array<double> durationArray(aTimeArray.begin(), aTimeArray.end());
    durationArray.insert(durationArray.begin(), aStartTime);

    const auto observer = [this](const NumericalSolver::StateVector& x, double t) -> void
    {
        this->observeNumericalIntegration(x, t);
    };

    switch (stepperType_)
    {
        case NumericalSolver::StepperType::RungeKutta4:
        {
            integrate_times(
                stepper_type_4(), aSystemOfEquations, aStateVector, durationArray, adjustedTimeStep, observer
            );
            break;
        }

        case NumericalSolver::StepperType::RungeKuttaCashKarp54:
        {
            integrate_times(
                make_controlled(absoluteTolerance_, relativeTolerance_, error_stepper_type_54()),
                aSystemOfEquations,
                aStateVector,
                durationArray,
                adjustedTimeStep,
                observer
            );
            break;
        }

        case NumericalSolver::StepperType::RungeKuttaFehlberg78:
        {
            integrate_times(
                make_controlled(absoluteTolerance_, relativeTolerance_, error_stepper_type_78()),
                aSystemOfEquations,
                aStateVector,
                durationArray,
                adjustedTimeStep,
                observer
            );
            break;
        }

        case NumericalSolver::StepperType::RungeKuttaDopri5:
        {
            integrate_times(
                make_controlled(absoluteTolerance_, relativeTolerance_, dense_stepper_type_5()),
                aSystemOfEquations,
                aStateVector,
                durationArray,
                adjustedTimeStep,
                observer
            );
            break;
        }

        case NumericalSolver::StepperType::AdamsBashforthMoulton5:
        {
            integrate_times(
                make_controlled_adam_bashforth_moulton<5>(absoluteTolerance_, relativeTolerance_),
                aSystemOfEquations,
                aStateVector,
                durationArray,
                adjustedTimeStep,
                observer
            );
            break;
        }

        case NumericalSolver::StepperType::AdamsBashforthMoulton8:
        {
            integrate_times(
                make_controlled_adam_bashforth_moulton<8>(absoluteTolerance_, relativeTolerance_),
                aSystemOfEquations,
                aStateVector,
                durationArray,
                adjustedTimeStep,
                observer
            );
            break;
        }

        case NumericalSolver::StepperType::BulirschStoer:
        {
            integrate_times(
                bulirsch_stoer_stepper_type(absoluteTolerance_, relativeTolerance_),
                aSystemOfEquations,
                aStateVector,
                durationArray,
                adjustedTimeStep,
                observer
            );
            break;
        }

        default:
            throw ostk::core::error::runtime::Wrong("Stepper type");
    }

    // Return array of StateVectors excluding first element which is a repeat of the startState
    Array<NumericalSolver::Solution> solutions = std::move(observedStateVectors_);
    solutions.erase(solutions.begin());

    return solutions;
}

NumericalSolver::Solution NumericalSolver::integrateDuration(
    const StateVector& anInitialStateVector,
    const Real& aDurationInSeconds,
    const NumericalSolver::SystemOfEquationsWrapper& aSystemOfEquations
)
{
    NumericalSolver::StateVector aStateVector = anInitialStateVector;

    observedStateVectors_.clear();

    if (aDurationInSeconds.isZero())  // If integration duration is zero seconds long, skip integration
    {
        return {anInitialStateVector, 0.0};
    }

    // Ensure integration starts in the correct direction with the initial time step guess
    const double adjustedTimeStep = getSignedTimeStep(aDurationInSeconds);

    const auto observer = [this](const NumericalSolver::StateVector& x, double t) -> void
    {
        this->observeNumericalIntegration(x, t);
    };

    switch (stepperType_)
    {
        case NumericalSolver::StepperType::RungeKutta4:
        {
            // Integrate_adaptive uses constant step size under the hood
            // for a stepper without error control like RK4.
            // Using integrate_adaptive ensures that the last step is exactly at the end time.
            switch (logType_)
            {
                case NumericalSolver::LogType::NoLog:
                case NumericalSolver::LogType::LogAdaptive:
                case NumericalSolver::LogType::LogConstant:
                {
                    integrate_adaptive(
                        stepper_type_4(),
                        aSystemOfEquations,
                        aStateVector,
                        (0.0),
                        (double)aDurationInSeconds,
                        adjustedTimeStep,
                        observer
                    );
                    return {aStateVector, aDurationInSeconds};
                }
                default:
                    throw ostk::core::error::runtime::Wrong("Log type");
            }
        }

        case NumericalSolver::StepperType::RungeKuttaCashKarp54:
        {
            switch (logType_)
            {
                case NumericalSolver::LogType::NoLog:
                case NumericalSolver::LogType::LogAdaptive:
                {
                    integrate_adaptive(
                        make_controlled(absoluteTolerance_, relativeTolerance_, error_stepper_type_54()),
                        aSystemOfEquations,
                        aStateVector,
                        (0.0),
                        (double)aDurationInSeconds,
                        adjustedTimeStep,
                        observer
                    );
                    return {aStateVector, aDurationInSeconds};
                }

                case NumericalSolver::LogType::LogConstant:
                {
                    integrate_const(
                        make_controlled(absoluteTolerance_, relativeTolerance_, error_stepper_type_54()),
                        aSystemOfEquations,
                        aStateVector,
                        (0.0),
                        (double)aDurationInSeconds,
                        adjustedTimeStep,
                        observer
                    );
                    return {aStateVector, aDurationInSeconds};
                }
                default:
                    throw ostk::core::error::runtime::Wrong("Log type");
            }
        }

        case NumericalSolver::StepperType::RungeKuttaFehlberg78:
        {
            switch (logType_)
            {
                case NumericalSolver::LogType::NoLog:
                case NumericalSolver::LogType::LogAdaptive:
                {
                    integrate_adaptive(
                        make_controlled(absoluteTolerance_, relativeTolerance_, error_stepper_type_78()),
                        aSystemOfEquations,
                        aStateVector,
                        (0.0),
                        (double)aDurationInSeconds,
                        adjustedTimeStep,
                        observer
                    );
                    return {aStateVector, aDurationInSeconds};
                }

                case NumericalSolver::LogType::LogConstant:
                {
                    integrate_const(
                        make_controlled(absoluteTolerance_, relativeTolerance_, error_stepper_type_78()),
                        aSystemOfEquations,
                        aStateVector,
                        (0.0),
                        (double)aDurationInSeconds,
                        adjustedTimeStep,
                        observer
                    );
                    return {aStateVector, aDurationInSeconds};
                }
                default:
                    throw ostk::core::error::runtime::Wrong("Log type");
            }
        }

        case NumericalSolver::StepperType::RungeKuttaDopri5:
        {
            switch (logType_)
            {
                case NumericalSolver::LogType::NoLog:
                case NumericalSolver::LogType::LogAdaptive:
                {
                    integrate_adaptive(
                        make_controlled(absoluteTolerance_, relativeTolerance_, dense_stepper_type_5()),
                        aSystemOfEquations,
                        aStateVector,
                        (0.0),
                        (double)aDurationInSeconds,
                        adjustedTimeStep,
                        observer
                    );
                    return {aStateVector, aDurationInSeconds};
                }

                case NumericalSolver::LogType::LogConstant:
                {
                    integrate_const(
                        make_controlled(absoluteTolerance_, relativeTolerance_, dense_stepper_type_5()),
                        aSystemOfEquations,
                        aStateVector,
                        (0.0),
                        (double)aDurationInSeconds,
                        adjustedTimeStep,
                        observer
                    );
                    return {aStateVector, aDurationInSeconds};
                }
                default:
                    throw ostk::core::error::runtime::Wrong("Log type");
            }
        }

        case NumericalSolver::StepperType::AdamsBashforthMoulton5:
        {
            switch (logType_)
            {
                case NumericalSolver::LogType::NoLog:
                case NumericalSolver::LogType::LogAdaptive:
                {
                    integrate_adaptive(
                        make_controlled_adam_bashforth_moulton<5>(absoluteTolerance_, relativeTolerance_),
                        aSystemOfEquations,
                        aStateVector,
                        (0.0),
                        (double)aDurationInSeconds,
                        adjustedTimeStep,
                        observer
                    );
                    return {aStateVector, aDurationInSeconds};
                }

                case NumericalSolver::LogType::LogConstant:
                {
                    integrate_const(
                        make_controlled_adam_bashforth_moulton<5>(absoluteTolerance_, relativeTolerance_),
                        aSystemOfEquations,
                        aStateVector,
                        (0.0),
                        (double)aDurationInSeconds,
                        adjustedTimeStep,
                        observer
                    );
                    return {aStateVector, aDurationInSeconds};
                }
                default:
                    throw ostk::core::error::runtime::Wrong("Log type");
            }
        }

        case NumericalSolver::StepperType::AdamsBashforthMoulton8:
        {
            switch (logType_)
            {
                case NumericalSolver::LogType::NoLog:
                case NumericalSolver::LogType::LogAdaptive:
                {
                    integrate_adaptive(
                        make_controlled_adam_bashforth_moulton<8>(absoluteTolerance_, relativeTolerance_),
                        aSystemOfEquations,
                        aStateVector,
                        (0.0),
                        (double)aDurationInSeconds,
                        adjustedTimeStep,
                        observer
                    );
                    return {aStateVector, aDurationInSeconds};
                }

                case NumericalSolver::LogType::LogConstant:
                {
                    integrate_const(
                        make_controlled_adam_bashforth_moulton<8>(absoluteTolerance_, relativeTolerance_),
                        aSystemOfEquations,
                        aStateVector,
                        (0.0),
                        (double)aDurationInSeconds,
                        adjustedTimeStep,
                        observer
                    );
                    return {aStateVector, aDurationInSeconds};
                }
                default:
                    throw ostk::core::error::runtime::Wrong("Log type");
            }
        }
        case NumericalSolver::StepperType::BulirschStoer:
        {
            switch (logType_)
            {
                case NumericalSolver::LogType::NoLog:
                case NumericalSolver::LogType::LogAdaptive:
                {
                    integrate_adaptive(
                        bulirsch_stoer_stepper_type(absoluteTolerance_, relativeTolerance_),
                        aSystemOfEquations,
                        aStateVector,
                        (0.0),
                        (double)aDurationInSeconds,
                        adjustedTimeStep,
                        observer
                    );
                    return {aStateVector, aDurationInSeconds};
                }

                case NumericalSolver::LogType::LogConstant:
                {
                    integrate_const(
                        bulirsch_stoer_stepper_type(absoluteTolerance_, relativeTolerance_),
                        aSystemOfEquations,
                        aStateVector,
                        (0.0),
                        (double)aDurationInSeconds,
                        adjustedTimeStep,
                        observer
                    );
                    return {aStateVector, aDurationInSeconds};
                }
                default:
                    throw ostk::core::error::runtime::Wrong("Log type");
            }
        }

        default:
            throw ostk::core::error::runtime::Wrong("Stepper type");
    }

    throw ostk::core::error::RuntimeError("No State Vector returned from Odeint.");

    return {anInitialStateVector, 0.0};
}

NumericalSolver::Solution NumericalSolver::integrateTime(
    const StateVector& anInitialStateVector,
    const Real& aStartTime,
    const Real& anEndTime,
    const NumericalSolver::SystemOfEquationsWrapper& aSystemOfEquations
)
{
    return this->integrateDuration(anInitialStateVector, (anEndTime - aStartTime), aSystemOfEquations);
}

Array<NumericalSolver::Solution> NumericalSolver::integrateDuration(
    const NumericalSolver::StateVector& anInitialStateVector,
    const Array<Real>& aDurationArray,
    const NumericalSolver::SystemOfEquationsWrapper& aSystemOfEquations
)
{
    return integrateTime(anInitialStateVector, 0.0, aDurationArray, aSystemOfEquations);
}

String NumericalSolver::StringFromLogType(const NumericalSolver::LogType& aLogType)
{
    switch (aLogType)
    {
        case NumericalSolver::LogType::NoLog:
            return "NoLog";

        case NumericalSolver::LogType::LogConstant:
            return "LogConstant";

        case NumericalSolver::LogType::LogAdaptive:
            return "LogAdaptive";

        default:
            throw ostk::core::error::runtime::Wrong("Log Type");
    }
}

String NumericalSolver::StringFromStepperType(const NumericalSolver::StepperType& aStepperType)
{
    switch (aStepperType)
    {
        case NumericalSolver::StepperType::RungeKutta4:
            return "RungeKutta4";

        case NumericalSolver::StepperType::RungeKuttaCashKarp54:
            return "RungeKuttaCashKarp54";

        case NumericalSolver::StepperType::RungeKuttaFehlberg78:
            return "RungeKuttaFehlberg78";

        case NumericalSolver::StepperType::RungeKuttaDopri5:
            return "RungeKuttaDopri5";

        case NumericalSolver::StepperType::AdamsBashforthMoulton8:
            return "AdamsBashforthMoulton8";

        case NumericalSolver::StepperType::AdamsBashforthMoulton5:
            return "AdamsBashforthMoulton5";

        case NumericalSolver::StepperType::BulirschStoer:
            return "BulirschStoer";

        default:
            throw ostk::core::error::runtime::Wrong("Stepper Type");
    }
}

NumericalSolver NumericalSolver::Undefined()
{
    return {
        LogType::NoLog,
        StepperType::RungeKuttaCashKarp54,
        Real::Undefined(),
        Real::Undefined(),
        Real::Undefined(),
    };
}

NumericalSolver NumericalSolver::Default()
{
    return {
        NumericalSolver::LogType::NoLog,
        NumericalSolver::StepperType::RungeKuttaFehlberg78,
        5.0,
        1.0e-12,
        1.0e-12,
    };
}

void NumericalSolver::observeNumericalIntegration(const NumericalSolver::StateVector& x, const double t)
{
    observedStateVectors_.add({x, t});

    switch (logType_)
    {
        case NumericalSolver::LogType::LogAdaptive:
        case NumericalSolver::LogType::LogConstant:
        {
            std::cout.precision(3);
            std::cout.setf(std::ios::fixed, std::ios::floatfield);

            std::cout << std::left << std::setw(15) << t;

            std::cout.precision(15);
            std::cout.setf(std::ios::scientific, std::ios::floatfield);
            for (Size i = 0; i < (Size)x.size(); i++)
            {
                std::cout << std::internal << std::setw(16) << x[i] << "     ";
            }
            std::cout << std::endl;

            std::cout.setf(std::ios::fixed, std::ios::floatfield);

            break;
        }

        default:
        {
            break;
        }
    }
}

double NumericalSolver::getSignedTimeStep(const Real& aReal) const
{
    const Real durationSign = (aReal > 0.0) - (aReal < 0.0);
    return timeStep_ * durationSign;
}

}  // namespace solver
}  // namespace mathematics
}  // namespace ostk
