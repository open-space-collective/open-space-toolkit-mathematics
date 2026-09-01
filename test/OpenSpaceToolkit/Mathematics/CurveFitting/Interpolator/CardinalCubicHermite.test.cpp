/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/CardinalCubicHermite.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <Global.test.hpp>

using ostk::core::type::Real;

using ostk::mathematics::curvefitting::Interpolator;
using ostk::mathematics::curvefitting::interpolator::CardinalCubicHermite;
using ostk::mathematics::object::VectorXd;

// Reference data sampled from f(x) = x^3 - 2 * x^2 + 3 * x - 1, on a uniform grid.
// A cubic Hermite spline reproduces any cubic polynomial exactly.

class OpenSpaceToolkit_Mathematics_Interpolator_CardinalCubicHermite : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        x_.resize(6);
        x_ << 0.0, 1.0, 2.0, 3.0, 4.0, 5.0;

        y_.resize(6);
        y_ << -1.0, 1.0, 5.0, 17.0, 43.0, 89.0;

        dydx_.resize(6);
        dydx_ << 3.0, 2.0, 7.0, 18.0, 35.0, 58.0;
    }

    VectorXd x_;
    VectorXd y_;
    VectorXd dydx_;
};

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_CardinalCubicHermite, Constructor)
{
    {
        EXPECT_NO_THROW(CardinalCubicHermite(x_, y_, dydx_));
    }

    {
        VectorXd x(1);
        x << 0.0;

        VectorXd y(1);
        y << -1.0;

        VectorXd dydx(1);
        dydx << 3.0;

        EXPECT_THROW(CardinalCubicHermite(x, y, dydx), ostk::core::error::runtime::Wrong);
    }

    {
        EXPECT_THROW(CardinalCubicHermite(x_.head(5), y_, dydx_), ostk::core::error::runtime::Wrong);
    }

    {
        EXPECT_THROW(CardinalCubicHermite(x_, y_, dydx_.head(5)), ostk::core::error::runtime::Wrong);
    }

    {
        VectorXd nonUniformX(6);
        nonUniformX << 0.0, 1.0, 2.0, 4.0, 5.0, 7.0;

        EXPECT_THROW(CardinalCubicHermite(nonUniformX, y_, dydx_), ostk::core::error::runtime::Wrong);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_CardinalCubicHermite, SecondConstructor)
{
    {
        EXPECT_NO_THROW(CardinalCubicHermite(y_, dydx_, 0.0, 1.0));
    }

    {
        EXPECT_THROW(CardinalCubicHermite(y_, dydx_.head(5), 0.0, 1.0), ostk::core::error::runtime::Wrong);
    }

    {
        EXPECT_THROW(CardinalCubicHermite(y_, dydx_, 0.0, 0.0), ostk::core::error::runtime::Wrong);
    }

    {
        EXPECT_THROW(CardinalCubicHermite(y_, dydx_, 0.0, -1.0), ostk::core::error::runtime::Wrong);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_CardinalCubicHermite, GetInterpolationType)
{
    const CardinalCubicHermite interpolator = {x_, y_, dydx_};

    EXPECT_EQ(Interpolator::Type::CardinalCubicHermite, interpolator.getInterpolationType());
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_CardinalCubicHermite, Evaluate)
{
    const CardinalCubicHermite interpolator = {x_, y_, dydx_};

    {
        EXPECT_NEAR(interpolator.evaluate(1.5), 2.375, 1e-9);
        EXPECT_NEAR(interpolator.evaluate(3.5), 27.875, 1e-9);

        // Nodes are reproduced exactly

        EXPECT_NEAR(interpolator.evaluate(0.0), -1.0, 1e-9);
        EXPECT_NEAR(interpolator.evaluate(5.0), 89.0, 1e-9);
    }

    {
        VectorXd query(2);
        query << 1.5, 3.5;

        const VectorXd values = interpolator.evaluate(query);

        EXPECT_EQ(2, values.size());
        EXPECT_NEAR(values(0), 2.375, 1e-9);
        EXPECT_NEAR(values(1), 27.875, 1e-9);
    }

    {
        // Both constructors describe the same interpolant

        const CardinalCubicHermite otherInterpolator = {y_, dydx_, 0.0, 1.0};

        EXPECT_NEAR(interpolator.evaluate(1.5), otherInterpolator.evaluate(1.5), 1e-12);
    }

    {
        EXPECT_THROW(interpolator.evaluate(-1.0), std::domain_error);
        EXPECT_THROW(interpolator.evaluate(6.0), std::domain_error);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_CardinalCubicHermite, ComputeDerivative)
{
    const CardinalCubicHermite interpolator = {x_, y_, dydx_};

    {
        EXPECT_NEAR(interpolator.computeDerivative(1.5), 3.75, 1e-9);
        EXPECT_NEAR(interpolator.computeDerivative(3.5), 25.75, 1e-9);
    }

    {
        VectorXd query(2);
        query << 1.5, 3.5;

        const VectorXd derivatives = interpolator.computeDerivative(query);

        EXPECT_EQ(2, derivatives.size());
        EXPECT_NEAR(derivatives(0), 3.75, 1e-9);
        EXPECT_NEAR(derivatives(1), 25.75, 1e-9);
    }

    {
        EXPECT_THROW(interpolator.computeDerivative(-1.0), std::domain_error);
        EXPECT_THROW(interpolator.computeDerivative(6.0), std::domain_error);
    }
}
