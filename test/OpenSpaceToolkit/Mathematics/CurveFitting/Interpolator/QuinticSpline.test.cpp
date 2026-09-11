/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/QuinticSpline.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <Global.test.hpp>

using ostk::core::type::Real;

using ostk::mathematics::curvefitting::Interpolator;
using ostk::mathematics::curvefitting::interpolator::QuinticSpline;
using ostk::mathematics::object::VectorXd;

// Reference data sampled from f(x) = x^4 - 3 * x^2 + 2, which a quintic spline reproduces
// exactly, whether or not its nodes are uniformly spaced.

class OpenSpaceToolkit_Mathematics_Interpolator_QuinticSpline : public ::testing::Test
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

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_QuinticSpline, Constructor)
{
    {
        EXPECT_NO_THROW(QuinticSpline(x_, y_));
    }

    {
        // At least 8 data points are required

        EXPECT_THROW(QuinticSpline(x_.head(7), y_.head(7)), ostk::core::error::runtime::Wrong);
    }

    {
        EXPECT_THROW(QuinticSpline(x_.head(9), y_), ostk::core::error::runtime::Wrong);
    }

    {
        // Nodes need not be uniformly spaced

        VectorXd nonUniformX(10);
        nonUniformX << 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0;

        VectorXd nonUniformY(10);
        nonUniformY << 2.0, 0.0, 6.0, 56.0, 210.0, 552.0, 1190.0, 2256.0, 3906.0, 9702.0;

        EXPECT_NO_THROW(QuinticSpline(nonUniformX, nonUniformY));
    }

    {
        // Nodes must be sorted in strictly ascending order

        VectorXd unsortedX(10);
        unsortedX << 0.0, 1.0, 2.0, 4.0, 3.0, 5.0, 6.0, 7.0, 8.0, 9.0;

        EXPECT_THROW(QuinticSpline(unsortedX, y_), ostk::core::error::runtime::Wrong);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_QuinticSpline, SecondConstructor)
{
    {
        EXPECT_NO_THROW(QuinticSpline(y_, 0.0, 1.0));
    }

    {
        EXPECT_THROW(QuinticSpline(y_.head(7), 0.0, 1.0), ostk::core::error::runtime::Wrong);
    }

    {
        EXPECT_THROW(QuinticSpline(y_, 0.0, 0.0), ostk::core::error::runtime::Wrong);
    }

    {
        EXPECT_THROW(QuinticSpline(y_, 0.0, -1.0), ostk::core::error::runtime::Wrong);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_QuinticSpline, GetInterpolationType)
{
    const QuinticSpline interpolator = {x_, y_};

    EXPECT_EQ(Interpolator::Type::QuinticSpline, interpolator.getInterpolationType());
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_QuinticSpline, Evaluate)
{
    const QuinticSpline interpolator = {x_, y_};

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

        const QuinticSpline otherInterpolator = {y_, 0.0, 1.0};

        EXPECT_NEAR(interpolator.evaluate(1.5), otherInterpolator.evaluate(1.5), 1e-12);
    }

    {
        EXPECT_THROW(interpolator.evaluate(-1.0), std::domain_error);
        EXPECT_THROW(interpolator.evaluate(100.0), std::domain_error);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_QuinticSpline, ComputeDerivative)
{
    const QuinticSpline interpolator = {x_, y_};

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

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_QuinticSpline, ComputeSecondDerivative)
{
    const QuinticSpline interpolator = {x_, y_};

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

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_QuinticSpline, NonUnitSpacing)
{
    // Same reference function, sampled every 2.0 rather than every 1.0

    VectorXd x(10);
    x << 0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0;

    VectorXd y(10);
    y << 2.0, 6.0, 210.0, 1190.0, 3906.0, 9702.0, 20306.0, 37830.0, 64770.0, 104006.0;

    const QuinticSpline interpolator = {x, y};

    EXPECT_NEAR(interpolator.evaluate(3.0), 56.0, 1e-5);
    EXPECT_NEAR(interpolator.computeDerivative(3.0), 90.0, 1e-5);
    EXPECT_NEAR(interpolator.computeSecondDerivative(3.0), 102.0, 1e-5);

    EXPECT_NEAR(interpolator.evaluate(7.0), 2256.0, 1e-5);
    EXPECT_NEAR(interpolator.computeDerivative(7.0), 1330.0, 1e-5);
    EXPECT_NEAR(interpolator.computeSecondDerivative(7.0), 582.0, 1e-5);
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_QuinticSpline, NonUniformNodes)
{
    // The same reference function, sampled on a deliberately ragged grid. Nodes that are not
    // uniformly spaced are interpolated with the general implementation, which must describe
    // the same curve.

    VectorXd x(10);
    x << 0.0, 0.5, 1.0, 2.5, 3.0, 5.0, 5.5, 7.0, 8.0, 10.0;

    VectorXd y(10);
    y << 2.0, 1.3125, 0.0, 22.3125, 56.0, 552.0, 826.3125, 2256.0, 3906.0, 9702.0;

    const QuinticSpline interpolator = {x, y};

    {
        // f(x) = x^4 - 3 * x^2 + 2 is reproduced exactly across the ragged spacing

        EXPECT_NEAR(interpolator.evaluate(1.5), 0.3125, 1e-7);
        EXPECT_NEAR(interpolator.evaluate(4.0), 210.0, 1e-7);
        EXPECT_NEAR(interpolator.evaluate(9.0), 6320.0, 1e-7);

        // Nodes are reproduced exactly

        EXPECT_NEAR(interpolator.evaluate(0.0), 2.0, 1e-9);
        EXPECT_NEAR(interpolator.evaluate(3.0), 56.0, 1e-9);
        EXPECT_NEAR(interpolator.evaluate(10.0), 9702.0, 1e-9);
    }

    {
        // f'(x) = 4 * x^3 - 6 * x, f''(x) = 12 * x^2 - 6

        EXPECT_NEAR(interpolator.computeDerivative(1.5), 4.5, 1e-6);
        EXPECT_NEAR(interpolator.computeDerivative(4.0), 232.0, 1e-6);

        EXPECT_NEAR(interpolator.computeSecondDerivative(1.5), 21.0, 1e-5);
        EXPECT_NEAR(interpolator.computeSecondDerivative(4.0), 186.0, 1e-5);
    }

    {
        EXPECT_THROW(interpolator.evaluate(-1.0), std::domain_error);
        EXPECT_THROW(interpolator.evaluate(100.0), std::domain_error);

        EXPECT_THROW(interpolator.computeDerivative(-1.0), std::domain_error);
        EXPECT_THROW(interpolator.computeSecondDerivative(100.0), std::domain_error);
    }
}
