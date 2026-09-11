/// Apache License 2.0

#include <boost/version.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/QuinticHermite.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <Global.test.hpp>

using ostk::core::type::Real;

using ostk::mathematics::curvefitting::Interpolator;
using ostk::mathematics::curvefitting::interpolator::QuinticHermite;
using ostk::mathematics::object::VectorXd;

// Reference data sampled from f(x) = x^4 - 3 * x^2 + 2, on a non-uniform grid unless stated
// otherwise. A quintic Hermite spline reproduces any polynomial of degree up to 5 exactly,
// whether or not its nodes are uniformly spaced.

class OpenSpaceToolkit_Mathematics_Interpolator_QuinticHermite : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        x_.resize(6);
        x_ << 0.0, 1.0, 2.0, 4.0, 5.0, 7.0;

        y_.resize(6);
        y_ << 2.0, 0.0, 6.0, 210.0, 552.0, 2256.0;

        dydx_.resize(6);
        dydx_ << 0.0, -2.0, 20.0, 232.0, 470.0, 1330.0;

        d2ydx2_.resize(6);
        d2ydx2_ << -6.0, 6.0, 42.0, 186.0, 294.0, 582.0;
    }

    VectorXd x_;
    VectorXd y_;
    VectorXd dydx_;
    VectorXd d2ydx2_;
};

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_QuinticHermite, Constructor)
{
    {
        EXPECT_NO_THROW(QuinticHermite(x_, y_, dydx_, d2ydx2_));
    }

    {
        VectorXd x(1);
        x << 0.0;

        VectorXd y(1);
        y << 2.0;

        VectorXd dydx(1);
        dydx << 0.0;

        VectorXd d2ydx2(1);
        d2ydx2 << -6.0;

        EXPECT_THROW(QuinticHermite(x, y, dydx, d2ydx2), ostk::core::error::runtime::Wrong);
    }

    {
        EXPECT_THROW(QuinticHermite(x_.head(5), y_, dydx_, d2ydx2_), ostk::core::error::runtime::Wrong);
    }

    {
        EXPECT_THROW(QuinticHermite(x_, y_, dydx_.head(5), d2ydx2_), ostk::core::error::runtime::Wrong);
    }

    {
        EXPECT_THROW(QuinticHermite(x_, y_, dydx_, d2ydx2_.head(5)), ostk::core::error::runtime::Wrong);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_QuinticHermite, SecondConstructor)
{
    {
        EXPECT_NO_THROW(QuinticHermite(y_, dydx_, d2ydx2_, 0.0, 1.0));
    }

    {
        EXPECT_THROW(
            QuinticHermite(y_.head(1), dydx_.head(1), d2ydx2_.head(1), 0.0, 1.0), ostk::core::error::runtime::Wrong
        );
    }

    {
        EXPECT_THROW(QuinticHermite(y_, dydx_.head(5), d2ydx2_, 0.0, 1.0), ostk::core::error::runtime::Wrong);
    }

    {
        EXPECT_THROW(QuinticHermite(y_, dydx_, d2ydx2_.head(5), 0.0, 1.0), ostk::core::error::runtime::Wrong);
    }

    {
        EXPECT_THROW(QuinticHermite(y_, dydx_, d2ydx2_, 0.0, 0.0), ostk::core::error::runtime::Wrong);
    }

    {
        EXPECT_THROW(QuinticHermite(y_, dydx_, d2ydx2_, 0.0, -1.0), ostk::core::error::runtime::Wrong);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_QuinticHermite, GetInterpolationType)
{
    const QuinticHermite interpolator = {x_, y_, dydx_, d2ydx2_};

    EXPECT_EQ(Interpolator::Type::QuinticHermite, interpolator.getInterpolationType());
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_QuinticHermite, Evaluate)
{
    const QuinticHermite interpolator = {x_, y_, dydx_, d2ydx2_};

    {
        EXPECT_NEAR(interpolator.evaluate(1.5), 0.3125, 1e-9);
        EXPECT_NEAR(interpolator.evaluate(3.0), 56.0, 1e-9);
        EXPECT_NEAR(interpolator.evaluate(6.0), 1190.0, 1e-9);

        // Nodes are reproduced exactly

        EXPECT_NEAR(interpolator.evaluate(0.0), 2.0, 1e-9);
        EXPECT_NEAR(interpolator.evaluate(7.0), 2256.0, 1e-9);
    }

    {
        VectorXd query(3);
        query << 1.5, 3.0, 6.0;

        const VectorXd values = interpolator.evaluate(query);

        EXPECT_EQ(3, values.size());
        EXPECT_NEAR(values(0), 0.3125, 1e-9);
        EXPECT_NEAR(values(1), 56.0, 1e-9);
        EXPECT_NEAR(values(2), 1190.0, 1e-9);
    }

    {
        EXPECT_THROW(interpolator.evaluate(-1.0), std::domain_error);
        EXPECT_THROW(interpolator.evaluate(8.0), std::domain_error);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_QuinticHermite, ComputeDerivative)
{
    const QuinticHermite interpolator = {x_, y_, dydx_, d2ydx2_};

    {
        EXPECT_NEAR(interpolator.computeDerivative(1.5), 4.5, 1e-9);
        EXPECT_NEAR(interpolator.computeDerivative(3.0), 90.0, 1e-9);
        EXPECT_NEAR(interpolator.computeDerivative(6.0), 828.0, 1e-9);
    }

    {
        VectorXd query(3);
        query << 1.5, 3.0, 6.0;

        const VectorXd derivatives = interpolator.computeDerivative(query);

        EXPECT_EQ(3, derivatives.size());
        EXPECT_NEAR(derivatives(0), 4.5, 1e-9);
        EXPECT_NEAR(derivatives(1), 90.0, 1e-9);
        EXPECT_NEAR(derivatives(2), 828.0, 1e-9);
    }

    {
        EXPECT_THROW(interpolator.computeDerivative(-1.0), std::domain_error);
        EXPECT_THROW(interpolator.computeDerivative(8.0), std::domain_error);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_QuinticHermite, ComputeSecondDerivative)
{
    const QuinticHermite interpolator = {x_, y_, dydx_, d2ydx2_};

    {
        EXPECT_NEAR(interpolator.computeSecondDerivative(1.5), 21.0, 1e-8);
        EXPECT_NEAR(interpolator.computeSecondDerivative(3.0), 102.0, 1e-8);
        EXPECT_NEAR(interpolator.computeSecondDerivative(6.0), 426.0, 1e-8);
    }

    {
        VectorXd query(3);
        query << 1.5, 3.0, 6.0;

        const VectorXd secondDerivatives = interpolator.computeSecondDerivative(query);

        EXPECT_EQ(3, secondDerivatives.size());
        EXPECT_NEAR(secondDerivatives(0), 21.0, 1e-8);
        EXPECT_NEAR(secondDerivatives(1), 102.0, 1e-8);
        EXPECT_NEAR(secondDerivatives(2), 426.0, 1e-8);
    }

    {
        EXPECT_THROW(interpolator.computeSecondDerivative(-1.0), std::domain_error);
        EXPECT_THROW(interpolator.computeSecondDerivative(8.0), std::domain_error);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_QuinticHermite, UniformNodes)
{
    // The same reference function, sampled on a uniform grid. Uniformly spaced nodes are
    // interpolated with the cardinal implementation, which must describe the same curve.

    VectorXd x(6);
    x << 0.0, 1.0, 2.0, 3.0, 4.0, 5.0;

    VectorXd y(6);
    y << 2.0, 0.0, 6.0, 56.0, 210.0, 552.0;

    VectorXd dydx(6);
    dydx << 0.0, -2.0, 20.0, 90.0, 232.0, 470.0;

    VectorXd d2ydx2(6);
    d2ydx2 << -6.0, 6.0, 42.0, 102.0, 186.0, 294.0;

    const QuinticHermite interpolator = {x, y, dydx, d2ydx2};

    {
        EXPECT_NEAR(interpolator.evaluate(1.5), 0.3125, 1e-9);
        EXPECT_NEAR(interpolator.evaluate(3.5), 115.3125, 1e-9);

        EXPECT_NEAR(interpolator.computeDerivative(1.5), 4.5, 1e-9);
        EXPECT_NEAR(interpolator.computeDerivative(3.5), 150.5, 1e-9);
    }

    {
        // Both constructors describe the same interpolant

        const QuinticHermite otherInterpolator = {y, dydx, d2ydx2, 0.0, 1.0};

        EXPECT_NEAR(interpolator.evaluate(1.5), otherInterpolator.evaluate(1.5), 1e-12);
        EXPECT_NEAR(interpolator.computeDerivative(1.5), otherInterpolator.computeDerivative(1.5), 1e-12);
    }

    {
        EXPECT_THROW(interpolator.evaluate(-1.0), std::domain_error);
        EXPECT_THROW(interpolator.evaluate(6.0), std::domain_error);

        EXPECT_THROW(interpolator.computeDerivative(-1.0), std::domain_error);
        EXPECT_THROW(interpolator.computeDerivative(6.0), std::domain_error);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_QuinticHermite, NonUnitSpacing)
{
    // The same reference function, sampled on a uniform grid with a spacing other than 1

    VectorXd x(6);
    x << 0.0, 2.0, 4.0, 6.0, 8.0, 10.0;

    VectorXd y(6);
    y << 2.0, 6.0, 210.0, 1190.0, 3906.0, 9702.0;

    VectorXd dydx(6);
    dydx << 0.0, 20.0, 232.0, 828.0, 2000.0, 3940.0;

    VectorXd d2ydx2(6);
    d2ydx2 << -6.0, 42.0, 186.0, 426.0, 762.0, 1194.0;

    const QuinticHermite interpolator = {x, y, dydx, d2ydx2};

    EXPECT_NEAR(interpolator.evaluate(3.0), 56.0, 1e-8);
    EXPECT_NEAR(interpolator.computeDerivative(3.0), 90.0, 1e-8);

    EXPECT_NEAR(interpolator.evaluate(7.0), 2256.0, 1e-8);
    EXPECT_NEAR(interpolator.computeDerivative(7.0), 1330.0, 1e-8);

    {
        // Both constructors describe the same interpolant

        const QuinticHermite otherInterpolator = {y, dydx, d2ydx2, 0.0, 2.0};

        EXPECT_NEAR(interpolator.evaluate(3.0), otherInterpolator.evaluate(3.0), 1e-12);
        EXPECT_NEAR(interpolator.computeDerivative(3.0), otherInterpolator.computeDerivative(3.0), 1e-12);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_QuinticHermite, ComputeSecondDerivativeUniformNodes)
{
    // boost::math::interpolators::cardinal_quintic_hermite::double_prime is wrong for a spacing other than 1 up to
    // Boost 1.92 (boostorg/math#1101). The second derivative of uniformly spaced nodes is therefore withheld until
    // the fix ships with Boost 1.93.

    VectorXd x(6);
    x << 0.0, 2.0, 4.0, 6.0, 8.0, 10.0;

    VectorXd y(6);
    y << 2.0, 6.0, 210.0, 1190.0, 3906.0, 9702.0;

    VectorXd dydx(6);
    dydx << 0.0, 20.0, 232.0, 828.0, 2000.0, 3940.0;

    VectorXd d2ydx2(6);
    d2ydx2 << -6.0, 42.0, 186.0, 426.0, 762.0, 1194.0;

    const QuinticHermite interpolator = {x, y, dydx, d2ydx2};
    const QuinticHermite otherInterpolator = {y, dydx, d2ydx2, 0.0, 2.0};

    VectorXd query(2);
    query << 3.0, 7.0;

#if BOOST_VERSION < 109300

    {
        EXPECT_THROW(interpolator.computeSecondDerivative(3.0), ostk::core::error::RuntimeError);
        EXPECT_THROW(interpolator.computeSecondDerivative(query), ostk::core::error::RuntimeError);

        EXPECT_THROW(otherInterpolator.computeSecondDerivative(3.0), ostk::core::error::RuntimeError);
        EXPECT_THROW(otherInterpolator.computeSecondDerivative(query), ostk::core::error::RuntimeError);
    }

    {
        // A unit spacing is not special-cased

        const QuinticHermite unitSpacingInterpolator = {y_, dydx_, d2ydx2_, 0.0, 1.0};

        EXPECT_THROW(unitSpacingInterpolator.computeSecondDerivative(1.5), ostk::core::error::RuntimeError);
    }

    {
        // The error names the Boost version to update to

        try
        {
            interpolator.computeSecondDerivative(3.0);

            FAIL() << "Expected ostk::core::error::RuntimeError";
        }
        catch (const ostk::core::error::RuntimeError& anError)
        {
            EXPECT_NE(std::string::npos, std::string(anError.getMessage()).find("Boost 1.93"));
        }
    }

#else

    {
        EXPECT_NEAR(interpolator.computeSecondDerivative(3.0), 102.0, 1e-7);
        EXPECT_NEAR(interpolator.computeSecondDerivative(7.0), 582.0, 1e-7);

        const VectorXd secondDerivatives = interpolator.computeSecondDerivative(query);

        EXPECT_EQ(2, secondDerivatives.size());
        EXPECT_NEAR(secondDerivatives(0), 102.0, 1e-7);
        EXPECT_NEAR(secondDerivatives(1), 582.0, 1e-7);
    }

    {
        // Both constructors describe the same interpolant

        EXPECT_NEAR(interpolator.computeSecondDerivative(3.0), otherInterpolator.computeSecondDerivative(3.0), 1e-12);
    }

    {
        EXPECT_THROW(interpolator.computeSecondDerivative(-1.0), std::domain_error);
        EXPECT_THROW(interpolator.computeSecondDerivative(11.0), std::domain_error);
    }

#endif
}
