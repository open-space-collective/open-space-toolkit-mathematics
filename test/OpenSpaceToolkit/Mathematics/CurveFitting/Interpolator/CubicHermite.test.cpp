/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/CubicHermite.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <Global.test.hpp>

using ostk::core::type::Real;

using ostk::mathematics::curvefitting::Interpolator;
using ostk::mathematics::curvefitting::interpolator::CubicHermite;
using ostk::mathematics::object::VectorXd;

// Reference data sampled from f(x) = x^3 - 2 * x^2 + 3 * x - 1, on a non-uniform grid.
// A cubic Hermite spline reproduces any cubic polynomial exactly.

class OpenSpaceToolkit_Mathematics_Interpolator_CubicHermite : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        x_.resize(6);
        x_ << 0.0, 1.0, 2.0, 4.0, 5.0, 7.0;

        y_.resize(6);
        y_ << -1.0, 1.0, 5.0, 43.0, 89.0, 265.0;

        dydx_.resize(6);
        dydx_ << 3.0, 2.0, 7.0, 35.0, 58.0, 122.0;
    }

    VectorXd x_;
    VectorXd y_;
    VectorXd dydx_;
};

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_CubicHermite, Constructor)
{
    {
        EXPECT_NO_THROW(CubicHermite(x_, y_, dydx_));
    }

    {
        VectorXd x(1);
        x << 0.0;

        VectorXd y(1);
        y << -1.0;

        VectorXd dydx(1);
        dydx << 3.0;

        EXPECT_THROW(CubicHermite(x, y, dydx), ostk::core::error::runtime::Wrong);
    }

    {
        EXPECT_THROW(CubicHermite(x_.head(5), y_, dydx_), ostk::core::error::runtime::Wrong);
    }

    {
        EXPECT_THROW(CubicHermite(x_, y_, dydx_.head(5)), ostk::core::error::runtime::Wrong);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_CubicHermite, GetInterpolationType)
{
    const CubicHermite interpolator = {x_, y_, dydx_};

    EXPECT_EQ(Interpolator::Type::CubicHermite, interpolator.getInterpolationType());
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_CubicHermite, Evaluate)
{
    const CubicHermite interpolator = {x_, y_, dydx_};

    {
        EXPECT_NEAR(interpolator.evaluate(1.5), 2.375, 1e-9);
        EXPECT_NEAR(interpolator.evaluate(3.0), 17.0, 1e-9);
        EXPECT_NEAR(interpolator.evaluate(6.0), 161.0, 1e-9);

        // Nodes are reproduced exactly

        EXPECT_NEAR(interpolator.evaluate(0.0), -1.0, 1e-9);
        EXPECT_NEAR(interpolator.evaluate(7.0), 265.0, 1e-9);
    }

    {
        VectorXd query(3);
        query << 1.5, 3.0, 6.0;

        const VectorXd values = interpolator.evaluate(query);

        EXPECT_EQ(3, values.size());
        EXPECT_NEAR(values(0), 2.375, 1e-9);
        EXPECT_NEAR(values(1), 17.0, 1e-9);
        EXPECT_NEAR(values(2), 161.0, 1e-9);
    }

    {
        EXPECT_THROW(interpolator.evaluate(-1.0), std::domain_error);
        EXPECT_THROW(interpolator.evaluate(8.0), std::domain_error);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_CubicHermite, ComputeDerivative)
{
    const CubicHermite interpolator = {x_, y_, dydx_};

    {
        EXPECT_NEAR(interpolator.computeDerivative(1.5), 3.75, 1e-9);
        EXPECT_NEAR(interpolator.computeDerivative(3.0), 18.0, 1e-9);
        EXPECT_NEAR(interpolator.computeDerivative(6.0), 87.0, 1e-9);
    }

    {
        VectorXd query(3);
        query << 1.5, 3.0, 6.0;

        const VectorXd derivatives = interpolator.computeDerivative(query);

        EXPECT_EQ(3, derivatives.size());
        EXPECT_NEAR(derivatives(0), 3.75, 1e-9);
        EXPECT_NEAR(derivatives(1), 18.0, 1e-9);
        EXPECT_NEAR(derivatives(2), 87.0, 1e-9);
    }

    {
        EXPECT_THROW(interpolator.computeDerivative(-1.0), std::domain_error);
        EXPECT_THROW(interpolator.computeDerivative(8.0), std::domain_error);
    }
}
