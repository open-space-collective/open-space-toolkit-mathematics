/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/CardinalQuinticSpline.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <Global.test.hpp>

using ostk::core::type::Real;

using ostk::mathematics::curvefitting::Interpolator;
using ostk::mathematics::curvefitting::interpolator::CardinalQuinticSpline;
using ostk::mathematics::object::VectorXd;

// Reference data sampled from f(x) = x^4 - 3 * x^2 + 2, which a quintic spline reproduces exactly.

class OpenSpaceToolkit_Mathematics_Interpolator_CardinalQuinticSpline : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        x_.resize(10);
        x_ << 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0;

        y_.resize(10);
        y_ << 2.0, 0.0, 6.0, 56.0, 210.0, 552.0, 1190.0, 2256.0, 3906.0, 6320.0;
    }

    VectorXd x_;
    VectorXd y_;
};

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_CardinalQuinticSpline, Constructor)
{
    {
        EXPECT_NO_THROW(CardinalQuinticSpline(x_, y_));
    }

    {
        // At least 8 data points are required

        EXPECT_THROW(CardinalQuinticSpline(x_.head(7), y_.head(7)), ostk::core::error::runtime::Wrong);
    }

    {
        EXPECT_THROW(CardinalQuinticSpline(x_.head(9), y_), ostk::core::error::runtime::Wrong);
    }

    {
        VectorXd nonUniformX(10);
        nonUniformX << 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0;

        EXPECT_THROW(CardinalQuinticSpline(nonUniformX, y_), ostk::core::error::runtime::Wrong);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_CardinalQuinticSpline, SecondConstructor)
{
    {
        EXPECT_NO_THROW(CardinalQuinticSpline(y_, 0.0, 1.0));
    }

    {
        EXPECT_THROW(CardinalQuinticSpline(y_.head(7), 0.0, 1.0), ostk::core::error::runtime::Wrong);
    }

    {
        EXPECT_THROW(CardinalQuinticSpline(y_, 0.0, 0.0), ostk::core::error::runtime::Wrong);
    }

    {
        EXPECT_THROW(CardinalQuinticSpline(y_, 0.0, -1.0), ostk::core::error::runtime::Wrong);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_CardinalQuinticSpline, GetInterpolationType)
{
    const CardinalQuinticSpline interpolator = {x_, y_};

    EXPECT_EQ(Interpolator::Type::CardinalQuinticSpline, interpolator.getInterpolationType());
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_CardinalQuinticSpline, Evaluate)
{
    const CardinalQuinticSpline interpolator = {x_, y_};

    {
        EXPECT_NEAR(interpolator.evaluate(1.5), 0.3125, 1e-6);
        EXPECT_NEAR(interpolator.evaluate(3.5), 115.3125, 1e-6);

        // Nodes are reproduced exactly

        EXPECT_NEAR(interpolator.evaluate(0.0), 2.0, 1e-6);
        EXPECT_NEAR(interpolator.evaluate(9.0), 6320.0, 1e-6);
    }

    {
        VectorXd query(2);
        query << 1.5, 3.5;

        const VectorXd values = interpolator.evaluate(query);

        EXPECT_EQ(2, values.size());
        EXPECT_NEAR(values(0), 0.3125, 1e-6);
        EXPECT_NEAR(values(1), 115.3125, 1e-6);
    }

    {
        // Both constructors describe the same interpolant

        const CardinalQuinticSpline otherInterpolator = {y_, 0.0, 1.0};

        EXPECT_NEAR(interpolator.evaluate(1.5), otherInterpolator.evaluate(1.5), 1e-12);
    }

    {
        EXPECT_THROW(interpolator.evaluate(-1.0), std::domain_error);
        EXPECT_THROW(interpolator.evaluate(100.0), std::domain_error);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_CardinalQuinticSpline, ComputeDerivative)
{
    const CardinalQuinticSpline interpolator = {x_, y_};

    {
        // f'(x) = 4 * x^3 - 6 * x

        EXPECT_NEAR(interpolator.computeDerivative(1.5), 4.5, 1e-6);
        EXPECT_NEAR(interpolator.computeDerivative(3.5), 150.5, 1e-6);
    }

    {
        VectorXd query(2);
        query << 1.5, 3.5;

        const VectorXd derivatives = interpolator.computeDerivative(query);

        EXPECT_EQ(2, derivatives.size());
        EXPECT_NEAR(derivatives(0), 4.5, 1e-6);
        EXPECT_NEAR(derivatives(1), 150.5, 1e-6);
    }

    {
        EXPECT_THROW(interpolator.computeDerivative(-1.0), std::domain_error);
        EXPECT_THROW(interpolator.computeDerivative(100.0), std::domain_error);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_CardinalQuinticSpline, ComputeSecondDerivative)
{
    const CardinalQuinticSpline interpolator = {x_, y_};

    {
        // f''(x) = 12 * x^2 - 6

        EXPECT_NEAR(interpolator.computeSecondDerivative(1.5), 21.0, 1e-5);
        EXPECT_NEAR(interpolator.computeSecondDerivative(3.5), 141.0, 1e-5);
    }

    {
        VectorXd query(2);
        query << 1.5, 3.5;

        const VectorXd secondDerivatives = interpolator.computeSecondDerivative(query);

        EXPECT_EQ(2, secondDerivatives.size());
        EXPECT_NEAR(secondDerivatives(0), 21.0, 1e-5);
        EXPECT_NEAR(secondDerivatives(1), 141.0, 1e-5);
    }

    {
        EXPECT_THROW(interpolator.computeSecondDerivative(-1.0), std::domain_error);
        EXPECT_THROW(interpolator.computeSecondDerivative(100.0), std::domain_error);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_CardinalQuinticSpline, NonUnitSpacing)
{
    // Same reference function, sampled every 2.0 rather than every 1.0

    VectorXd x(10);
    x << 0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0;

    VectorXd y(10);
    y << 2.0, 6.0, 210.0, 1190.0, 3906.0, 9702.0, 20306.0, 37830.0, 64770.0, 104006.0;

    const CardinalQuinticSpline interpolator = {x, y};

    EXPECT_NEAR(interpolator.evaluate(3.0), 56.0, 1e-5);
    EXPECT_NEAR(interpolator.computeDerivative(3.0), 90.0, 1e-5);
    EXPECT_NEAR(interpolator.computeSecondDerivative(3.0), 102.0, 1e-5);

    EXPECT_NEAR(interpolator.evaluate(7.0), 2256.0, 1e-5);
    EXPECT_NEAR(interpolator.computeDerivative(7.0), 1330.0, 1e-5);
    EXPECT_NEAR(interpolator.computeSecondDerivative(7.0), 582.0, 1e-5);
}
