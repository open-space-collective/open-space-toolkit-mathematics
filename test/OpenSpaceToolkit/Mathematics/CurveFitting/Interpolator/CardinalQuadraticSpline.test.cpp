/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/CardinalQuadraticSpline.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <Global.test.hpp>

using ostk::core::type::Real;

using ostk::mathematics::curvefitting::Interpolator;
using ostk::mathematics::curvefitting::interpolator::CardinalQuadraticSpline;
using ostk::mathematics::object::VectorXd;

// Reference data sampled from f(x) = x^2 - 3 * x + 2, which a quadratic spline reproduces exactly.

class OpenSpaceToolkit_Mathematics_Interpolator_CardinalQuadraticSpline : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        x_.resize(6);
        x_ << 0.0, 1.0, 2.0, 3.0, 4.0, 5.0;

        y_.resize(6);
        y_ << 2.0, 0.0, 0.0, 2.0, 6.0, 12.0;
    }

    VectorXd x_;
    VectorXd y_;
};

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_CardinalQuadraticSpline, Constructor)
{
    {
        EXPECT_NO_THROW(CardinalQuadraticSpline(x_, y_));
    }

    {
        // At least 3 data points are required

        EXPECT_THROW(CardinalQuadraticSpline(x_.head(2), y_.head(2)), ostk::core::error::runtime::Wrong);
    }

    {
        EXPECT_THROW(CardinalQuadraticSpline(x_.head(5), y_), ostk::core::error::runtime::Wrong);
    }

    {
        VectorXd nonUniformX(6);
        nonUniformX << 0.0, 1.0, 2.0, 4.0, 5.0, 7.0;

        EXPECT_THROW(CardinalQuadraticSpline(nonUniformX, y_), ostk::core::error::runtime::Wrong);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_CardinalQuadraticSpline, SecondConstructor)
{
    {
        EXPECT_NO_THROW(CardinalQuadraticSpline(y_, 0.0, 1.0));
    }

    {
        EXPECT_THROW(CardinalQuadraticSpline(y_.head(2), 0.0, 1.0), ostk::core::error::runtime::Wrong);
    }

    {
        EXPECT_THROW(CardinalQuadraticSpline(y_, 0.0, 0.0), ostk::core::error::runtime::Wrong);
    }

    {
        EXPECT_THROW(CardinalQuadraticSpline(y_, 0.0, -1.0), ostk::core::error::runtime::Wrong);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_CardinalQuadraticSpline, GetInterpolationType)
{
    const CardinalQuadraticSpline interpolator = {x_, y_};

    EXPECT_EQ(Interpolator::Type::CardinalQuadraticSpline, interpolator.getInterpolationType());
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_CardinalQuadraticSpline, Evaluate)
{
    const CardinalQuadraticSpline interpolator = {x_, y_};

    {
        // f(1.5) = -0.25, f(3.5) = 3.75

        EXPECT_NEAR(interpolator.evaluate(1.5), -0.25, 1e-9);
        EXPECT_NEAR(interpolator.evaluate(3.5), 3.75, 1e-9);

        // Nodes are reproduced exactly

        EXPECT_NEAR(interpolator.evaluate(0.0), 2.0, 1e-9);
        EXPECT_NEAR(interpolator.evaluate(4.0), 6.0, 1e-9);
    }

    {
        VectorXd query(2);
        query << 1.5, 3.5;

        const VectorXd values = interpolator.evaluate(query);

        EXPECT_EQ(2, values.size());
        EXPECT_NEAR(values(0), -0.25, 1e-9);
        EXPECT_NEAR(values(1), 3.75, 1e-9);
    }

    {
        // Both constructors describe the same interpolant

        const CardinalQuadraticSpline otherInterpolator = {y_, 0.0, 1.0};

        EXPECT_NEAR(interpolator.evaluate(1.5), otherInterpolator.evaluate(1.5), 1e-12);
    }

    {
        EXPECT_THROW(interpolator.evaluate(-1.0), std::domain_error);
        EXPECT_THROW(interpolator.evaluate(100.0), std::domain_error);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_CardinalQuadraticSpline, ComputeDerivative)
{
    const CardinalQuadraticSpline interpolator = {x_, y_};

    {
        // f'(x) = 2 * x - 3

        EXPECT_NEAR(interpolator.computeDerivative(1.5), 0.0, 1e-9);
        EXPECT_NEAR(interpolator.computeDerivative(3.5), 4.0, 1e-9);
    }

    {
        VectorXd query(2);
        query << 1.5, 3.5;

        const VectorXd derivatives = interpolator.computeDerivative(query);

        EXPECT_EQ(2, derivatives.size());
        EXPECT_NEAR(derivatives(0), 0.0, 1e-9);
        EXPECT_NEAR(derivatives(1), 4.0, 1e-9);
    }

    {
        EXPECT_THROW(interpolator.computeDerivative(-1.0), std::domain_error);
        EXPECT_THROW(interpolator.computeDerivative(100.0), std::domain_error);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_CardinalQuadraticSpline, NonUnitSpacing)
{
    // Same reference function, sampled every 2.0 rather than every 1.0

    VectorXd x(6);
    x << 0.0, 2.0, 4.0, 6.0, 8.0, 10.0;

    VectorXd y(6);
    y << 2.0, 0.0, 6.0, 20.0, 42.0, 72.0;

    const CardinalQuadraticSpline interpolator = {x, y};

    EXPECT_NEAR(interpolator.evaluate(3.0), 2.0, 1e-8);
    EXPECT_NEAR(interpolator.computeDerivative(3.0), 3.0, 1e-8);

    EXPECT_NEAR(interpolator.evaluate(7.0), 30.0, 1e-8);
    EXPECT_NEAR(interpolator.computeDerivative(7.0), 11.0, 1e-8);
}
