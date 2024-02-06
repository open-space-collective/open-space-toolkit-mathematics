/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Tuple.hpp>
#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>
#include <OpenSpaceToolkit/Mathematics/Solvers/NumericalSolver.hpp>

#include <Global.test.hpp>

using ostk::core::container::Array;
using ostk::core::container::Tuple;
using ostk::core::type::Integer;
using ostk::core::type::Real;
using ostk::core::type::String;
using ostk::core::type::Shared;

using ostk::math::object::VectorXd;

using ostk::math::solvers::NumericalSolver;

// Simple duration based condition

class OpenSpaceToolkit_Mathematics_Solvers_NumericalSolver : public ::testing::Test
{
    void SetUp() override
    {
        defaultStateVector_.resize(2);
        defaultStateVector_ << 0.0, 1.0;
    }

   protected:
    NumericalSolver defaultRK54_ = {
        NumericalSolver::LogType::NoLog,
        NumericalSolver::StepperType::RungeKuttaCashKarp54,
        5.0,
        1.0e-15,
        1.0e-15,
    };

    NumericalSolver defaultRKF78_ = {
        NumericalSolver::LogType::NoLog,
        NumericalSolver::StepperType::RungeKuttaFehlberg78,
        5.0,
        1.0e-15,
        1.0e-15,
    };

    NumericalSolver defaultRKD5_ = {
        NumericalSolver::LogType::NoLog,
        NumericalSolver::StepperType::RungeKuttaDopri5,
        1e-3,
        1.0e-15,
        1.0e-15,
    };

    NumericalSolver::StateVector defaultStateVector_;
    const Real defaultDuration_ = 10.0;
    const Real defaultStartTime_ = 0.0;

    const std::function<void(const NumericalSolver::StateVector &, NumericalSolver::StateVector &, const double)>
        systemOfEquations_ =
            [](const NumericalSolver::StateVector &x, NumericalSolver::StateVector &dxdt, const double) -> void
    {
        dxdt[0] = x[1];
        dxdt[1] = -x[0];
    };

    void validatePropagatedStates(
        const Array<Real> &aTimeArray, const Array<NumericalSolver::Solution> &aSolutionArray, const double &aTolerance
    )
    {
        for (size_t i = 0; i < aTimeArray.size(); i++)
        {
            const NumericalSolver::StateVector propagatedStateVector = aSolutionArray[i].first;

            EXPECT_GT(aTolerance, std::abs(propagatedStateVector[0] - std::sin(aTimeArray[i])));
            EXPECT_GT(aTolerance, std::abs(propagatedStateVector[1] - std::cos(aTimeArray[i])));
        }
    }

    NumericalSolver::StateVector getStateVector(const double &aTime)
    {
        VectorXd stateVector(2);
        stateVector << std::sin(aTime), std::cos(aTime);
        return stateVector;
    }
};

class OpenSpaceToolkit_Mathematics_Solvers_NumericalSolver_Parametrized
    : public OpenSpaceToolkit_Mathematics_Solvers_NumericalSolver,
      public ::testing::WithParamInterface<Tuple<NumericalSolver::StepperType>>
{
};

INSTANTIATE_TEST_SUITE_P(
    Integration,
    OpenSpaceToolkit_Mathematics_Solvers_NumericalSolver_Parametrized,
    ::testing::Values(
        std::make_tuple(NumericalSolver::StepperType::RungeKutta4),
        std::make_tuple(NumericalSolver::StepperType::RungeKuttaCashKarp54),
        std::make_tuple(NumericalSolver::StepperType::RungeKuttaFehlberg78),
        std::make_tuple(NumericalSolver::StepperType::RungeKuttaDopri5)
    )
);

TEST_F(OpenSpaceToolkit_Mathematics_Solvers_NumericalSolver, Constructor)
{
    {
        EXPECT_NO_THROW(NumericalSolver numericalsolver(
            NumericalSolver::LogType::NoLog, NumericalSolver::StepperType::RungeKuttaCashKarp54, 5.0, 1.0e-15, 1.0e-15
        ));
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Solvers_NumericalSolver, CopyConstructor)
{
    {
        EXPECT_NO_THROW(NumericalSolver numericalsolverCopy(defaultRK54_));
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Solvers_NumericalSolver, EqualToOperator)
{
    {
        EXPECT_TRUE(defaultRK54_ == defaultRK54_);

        // Test LogType
        const NumericalSolver numericalSolver_1 = {
            NumericalSolver::LogType::LogConstant,
            NumericalSolver::StepperType::RungeKuttaCashKarp54,
            5.0,
            1.0e-15,
            1.0e-15,
        };
        EXPECT_FALSE(defaultRK54_ == numericalSolver_1);

        // Test StepperType
        const NumericalSolver numericalSolver_2 = {
            NumericalSolver::LogType::NoLog,
            NumericalSolver::StepperType::RungeKuttaFehlberg78,
            5.0,
            1.0e-15,
            1.0e-15,
        };
        EXPECT_FALSE(defaultRK54_ == numericalSolver_2);

        // Test timeStep
        const NumericalSolver numericalSolver_3 = {
            NumericalSolver::LogType::NoLog,
            NumericalSolver::StepperType::RungeKuttaCashKarp54,
            4.0,
            1.0e-15,
            1.0e-15,
        };

        EXPECT_FALSE(defaultRK54_ == numericalSolver_3);

        // Test relativeTolerance
        const NumericalSolver numericalSolver_4 = {
            NumericalSolver::LogType::NoLog,
            NumericalSolver::StepperType::RungeKuttaCashKarp54,
            5.0,
            1.0e-14,
            1.0e-15,
        };

        EXPECT_FALSE(defaultRK54_ == numericalSolver_4);

        // Test absoluteTolerance
        const NumericalSolver numericalSolver_5 = {
            NumericalSolver::LogType::NoLog,
            NumericalSolver::StepperType::RungeKuttaCashKarp54,
            5.0,
            1.0e-15,
            1.0e-14,
        };

        EXPECT_FALSE(defaultRK54_ == numericalSolver_5);
    }

    {
        EXPECT_FALSE(NumericalSolver::Undefined() == defaultRK54_);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Solvers_NumericalSolver, NotEqualToOperator)
{
    {
        EXPECT_FALSE(defaultRK54_ != defaultRK54_);

        // Test LogType
        const NumericalSolver numericalSolver_1 = {
            NumericalSolver::LogType::LogConstant,
            NumericalSolver::StepperType::RungeKuttaCashKarp54,
            5.0,
            1.0e-15,
            1.0e-15,
        };

        EXPECT_TRUE(defaultRK54_ != numericalSolver_1);

        // Test StepperType
        const NumericalSolver numericalSolver_2 = {
            NumericalSolver::LogType::NoLog,
            NumericalSolver::StepperType::RungeKuttaFehlberg78,
            5.0,
            1.0e-15,
            1.0e-15,
        };
        EXPECT_TRUE(defaultRK54_ != numericalSolver_2);

        // Test timeStep
        const NumericalSolver numericalSolver_3 = {
            NumericalSolver::LogType::NoLog,
            NumericalSolver::StepperType::RungeKuttaCashKarp54,
            4.0,
            1.0e-15,
            1.0e-15,
        };

        EXPECT_TRUE(defaultRK54_ != numericalSolver_3);

        // Test relativeTolerance
        const NumericalSolver numericalSolver_4 = {
            NumericalSolver::LogType::NoLog,
            NumericalSolver::StepperType::RungeKuttaCashKarp54,
            5.0,
            1.0e-14,
            1.0e-15,
        };

        EXPECT_TRUE(defaultRK54_ != numericalSolver_4);

        // Test absoluteTolerance
        const NumericalSolver numericalSolver_5 = {
            NumericalSolver::LogType::NoLog,
            NumericalSolver::StepperType::RungeKuttaCashKarp54,
            5.0,
            1.0e-15,
            1.0e-14,
        };

        EXPECT_TRUE(defaultRK54_ != numericalSolver_5);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Solvers_NumericalSolver, IsDefined)
{
    {
        EXPECT_TRUE(defaultRK54_.isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Solvers_NumericalSolver, StreamOperator)
{
    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << defaultRK54_ << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Solvers_NumericalSolver, Print)
{
    {
        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(defaultRK54_.print(std::cout, true));
        EXPECT_NO_THROW(defaultRK54_.print(std::cout, false));
        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Solvers_NumericalSolver, Accessors)
{
    {
        EXPECT_NO_THROW(defaultRK54_.accessObservedStateVectors());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Solvers_NumericalSolver, GetType)
{
    {
        EXPECT_EQ(defaultRK54_.getLogType(), NumericalSolver::LogType::NoLog);

        const NumericalSolver numericalSolver_LogConstant = {
            NumericalSolver::LogType::LogConstant,
            NumericalSolver::StepperType::RungeKuttaCashKarp54,
            5.0,
            1.0e-15,
            1.0e-15,
        };
        EXPECT_EQ(numericalSolver_LogConstant.getLogType(), NumericalSolver::LogType::LogConstant);

        const NumericalSolver numericalSolver_LogAdaptive = {
            NumericalSolver::LogType::LogAdaptive,
            NumericalSolver::StepperType::RungeKuttaCashKarp54,
            5.0,
            1.0e-15,
            1.0e-15,
        };
        EXPECT_EQ(numericalSolver_LogAdaptive.getLogType(), NumericalSolver::LogType::LogAdaptive);

        EXPECT_THROW(NumericalSolver::Undefined().getLogType(), ostk::core::error::runtime::Undefined);
    }

    {
        EXPECT_EQ(defaultRK54_.getStepperType(), NumericalSolver::StepperType::RungeKuttaCashKarp54);
        EXPECT_EQ(defaultRKF78_.getStepperType(), NumericalSolver::StepperType::RungeKuttaFehlberg78);
        EXPECT_THROW(NumericalSolver::Undefined().getStepperType(), ostk::core::error::runtime::Undefined);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Solvers_NumericalSolver, GetNumbers)
{
    {
        EXPECT_EQ(defaultRK54_.getTimeStep(), 5.0);
        EXPECT_EQ(defaultRK54_.getRelativeTolerance(), 1.0e-15);
        EXPECT_EQ(defaultRK54_.getAbsoluteTolerance(), 1.0e-15);
    }

    {
        EXPECT_THROW(NumericalSolver::Undefined().getTimeStep(), ostk::core::error::runtime::Undefined);
        EXPECT_THROW(NumericalSolver::Undefined().getRelativeTolerance(), ostk::core::error::runtime::Undefined);
        EXPECT_THROW(NumericalSolver::Undefined().getAbsoluteTolerance(), ostk::core::error::runtime::Undefined);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Solvers_NumericalSolver, GetObservedStates)
{
    {
        EXPECT_NO_THROW(defaultRK54_.getObservedStateVectors());
    }

    {
        EXPECT_TRUE(defaultRK54_.getObservedStateVectors().isEmpty());
    }

    {
        EXPECT_ANY_THROW(NumericalSolver::Undefined().getObservedStateVectors());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Solvers_NumericalSolver, StringFromType)
{
    {
        EXPECT_TRUE(NumericalSolver::StringFromStepperType(NumericalSolver::StepperType::RungeKutta4) == "RungeKutta4");
        EXPECT_TRUE(
            NumericalSolver::StringFromStepperType(NumericalSolver::StepperType::RungeKuttaCashKarp54) ==
            "RungeKuttaCashKarp54"
        );
        EXPECT_TRUE(
            NumericalSolver::StringFromStepperType(NumericalSolver::StepperType::RungeKuttaFehlberg78) ==
            "RungeKuttaFehlberg78"
        );
        EXPECT_TRUE(
            NumericalSolver::StringFromStepperType(NumericalSolver::StepperType::RungeKuttaDopri5) == "RungeKuttaDopri5"
        );
    }

    {
        EXPECT_TRUE(NumericalSolver::StringFromLogType(NumericalSolver::LogType::NoLog) == "NoLog");
        EXPECT_TRUE(NumericalSolver::StringFromLogType(NumericalSolver::LogType::LogConstant) == "LogConstant");
        EXPECT_TRUE(NumericalSolver::StringFromLogType(NumericalSolver::LogType::LogAdaptive) == "LogAdaptive");
    }
}

TEST_P(OpenSpaceToolkit_Mathematics_Solvers_NumericalSolver_Parametrized, integrateDuration)
{
    const auto parameters = GetParam();

    NumericalSolver numericalSolver = {
        NumericalSolver::LogType::NoLog,
        std::get<0>(parameters),
        1e-3,
        1.0e-15,
        1.0e-15,
    };

    {
        const Array<Real> durations = {
            defaultDuration_,
            -defaultDuration_,
        };

        for (const Real &duration : durations)
        {
            const NumericalSolver::StateVector propagatedStateVector =
                numericalSolver.integrateDuration(defaultStateVector_, duration, systemOfEquations_).first;

            // Validate the output against an analytical function

            EXPECT_GT(2e-8, std::abs(propagatedStateVector[0] - std::sin(duration)));
            EXPECT_GT(2e-8, std::abs(propagatedStateVector[1] - std::cos(duration)));
        }
    }

    {
        const NumericalSolver::Solution solution =
            numericalSolver.integrateDuration(defaultStateVector_, 0.0, systemOfEquations_);

        EXPECT_DOUBLE_EQ(defaultStateVector_[0], solution.first[0]);
        EXPECT_DOUBLE_EQ(defaultStateVector_[1], solution.first[1]);
        EXPECT_DOUBLE_EQ(0.0, solution.second);
    }
}

TEST_P(OpenSpaceToolkit_Mathematics_Solvers_NumericalSolver_Parametrized, IntegrateDuration_Comparison)
{
    const auto parameters = GetParam();

    // Performance test comparing results of integrate_adaptive and integrate_const for RungeKuttaCashKarp54
    {
        NumericalSolver numericalSolver_1 = {
            NumericalSolver::LogType::LogAdaptive,
            std::get<0>(parameters),
            1e-3,
            1.0e-15,
            1.0e-15,
        };
        NumericalSolver numericalSolver_2 = {
            NumericalSolver::LogType::LogConstant,
            std::get<0>(parameters),
            1e-3,
            1.0e-15,
            1.0e-15,
        };

        testing::internal::CaptureStdout();
        const NumericalSolver::StateVector propagatedStateVector_1 =
            numericalSolver_1.integrateDuration(defaultStateVector_, defaultDuration_, systemOfEquations_).first;
        const NumericalSolver::StateVector propagatedStateVector_2 =
            numericalSolver_2.integrateDuration(defaultStateVector_, defaultDuration_, systemOfEquations_).first;
        String output = testing::internal::GetCapturedStdout();

        EXPECT_FALSE(output.empty());

        // Validate the output against an analytical function

        // Ensure state error between integrate_const and integrate_adaptive is within a reasonable tolerance
        EXPECT_GT(1e-9, std::abs(propagatedStateVector_1[0] - propagatedStateVector_2[0]));
        EXPECT_GT(1e-9, std::abs(propagatedStateVector_1[1] - propagatedStateVector_2[1]));
    }
}

TEST_P(OpenSpaceToolkit_Mathematics_Solvers_NumericalSolver_Parametrized, IntegrateDuration_Array)
{
    const auto parameters = GetParam();

    NumericalSolver numericalSolver = {
        NumericalSolver::LogType::NoLog,
        std::get<0>(parameters),
        1e-3,
        1.0e-15,
        1.0e-15,
    };

    const Array<Array<Real>> durationArrays = {
        {10.0, 40.0, 70.0, 1000.0},
        {-10.0, -40.0, -70.0, -1000.0},
    };

    for (const Array<Real> &durationArray : durationArrays)
    {
        const Array<NumericalSolver::Solution> propagatedStateVectorArray =
            numericalSolver.integrateDuration(defaultStateVector_, durationArray, systemOfEquations_);

        validatePropagatedStates(durationArray, propagatedStateVectorArray, 2e-8);
    }
}

TEST_P(OpenSpaceToolkit_Mathematics_Solvers_NumericalSolver_Parametrized, IntegrateTime)
{
    const auto parameters = GetParam();

    NumericalSolver numericalSolver = {
        NumericalSolver::LogType::NoLog,
        std::get<0>(parameters),
        1e-3,
        1.0e-15,
        1.0e-15,
    };

    const Array<Real> endTimes = {
        defaultStartTime_ + defaultDuration_,
        defaultStartTime_ - defaultDuration_,
    };

    for (const Real &endTime : endTimes)
    {
        const NumericalSolver::StateVector propagatedStateVector =
            numericalSolver.integrateTime(defaultStateVector_, defaultStartTime_, endTime, systemOfEquations_).first;

        // Validate the output against an analytical function

        EXPECT_GT(2e-8, std::abs(propagatedStateVector[0] - std::sin(endTime)));
        EXPECT_GT(2e-8, std::abs(propagatedStateVector[1] - std::cos(endTime)));
    }
}

TEST_P(OpenSpaceToolkit_Mathematics_Solvers_NumericalSolver_Parametrized, IntegrateTime_Comparison)
{
    const auto parameters = GetParam();
    // Performance test comparing results of integrate_adaptive and integrate_const
    {
        NumericalSolver numericalSolver_1 = {
            NumericalSolver::LogType::LogAdaptive,
            std::get<0>(parameters),
            1e-3,
            1.0e-15,
            1.0e-15,
        };
        NumericalSolver numericalSolver_2 = {
            NumericalSolver::LogType::LogConstant,
            std::get<0>(parameters),
            1e-3,
            1.0e-15,
            1.0e-15,
        };

        testing::internal::CaptureStdout();
        const NumericalSolver::StateVector propagatedStateVector_1 =
            numericalSolver_1
                .integrateTime(
                    defaultStateVector_, defaultStartTime_, defaultStartTime_ + defaultDuration_, systemOfEquations_
                )
                .first;
        const NumericalSolver::StateVector propagatedStateVector_2 =
            numericalSolver_2
                .integrateTime(
                    defaultStateVector_, defaultStartTime_, defaultStartTime_ + defaultDuration_, systemOfEquations_
                )
                .first;
        String output = testing::internal::GetCapturedStdout();

        EXPECT_FALSE(output.empty());

        // Validate the output against an analytical function
        // Ensure state error between integrate_const and integrate_adaptive is within a reasonable tolerance
        EXPECT_GT(1e-9, std::abs(propagatedStateVector_1[0] - propagatedStateVector_2[0]));
        EXPECT_GT(1e-9, std::abs(propagatedStateVector_1[1] - propagatedStateVector_2[1]));
    }
}

TEST_P(OpenSpaceToolkit_Mathematics_Solvers_NumericalSolver_Parametrized, IntegrateTime_Array)
{
    const auto parameters = GetParam();

    NumericalSolver numericalSolver = {
        NumericalSolver::LogType::NoLog,
        std::get<0>(parameters),
        1e-3,
        1.0e-15,
        1.0e-15,
    };

    const Array<Array<Real>> timeArrays = {
        {100.0, 400.0, 700.0, 1000.0},
        {-100.0, -400.0, -700.0, -1000.0},
    };

    for (const Array<Real> &timeArray : timeArrays)
    {
        const Array<NumericalSolver::Solution> propagatedStateVectorArray =
            numericalSolver.integrateTime(defaultStateVector_, defaultStartTime_, timeArray, systemOfEquations_);

        validatePropagatedStates(timeArray, propagatedStateVectorArray, 2e-8);
    }

    {
        EXPECT_THROW(
            numericalSolver.integrateTime(defaultStateVector_, defaultStartTime_, Array<Real> {}, systemOfEquations_),
            ostk::core::error::RuntimeError
        );
    }

    {
        const NumericalSolver::Solution solution = numericalSolver.integrateTime(
            defaultStateVector_, defaultStartTime_, {defaultStartTime_}, systemOfEquations_
        );

        EXPECT_DOUBLE_EQ(defaultStateVector_[0], solution.first[0]);
        EXPECT_DOUBLE_EQ(defaultStateVector_[1], solution.first[1]);
        EXPECT_DOUBLE_EQ(defaultStartTime_, solution.second);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Solvers_NumericalSolver, Undefined)
{
    {
        EXPECT_NO_THROW(NumericalSolver::Undefined());
    }

    {
        EXPECT_FALSE(NumericalSolver::Undefined().isDefined());
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Solvers_NumericalSolver, Default)
{
    {
        EXPECT_NO_THROW(NumericalSolver::Default());
    }

    {
        EXPECT_TRUE(NumericalSolver::Default().isDefined());
    }
}
