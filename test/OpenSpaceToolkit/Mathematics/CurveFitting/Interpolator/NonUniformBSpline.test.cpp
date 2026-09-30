/// Apache License 2.0

#include <cmath>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/CubicSpline.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/NonUniformBSpline.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/QuadraticSpline.hpp>
#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/QuinticSpline.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <Global.test.hpp>

using ostk::core::type::Size;

using ostk::mathematics::curvefitting::interpolator::CubicSpline;
using ostk::mathematics::curvefitting::interpolator::NonUniformBSpline;
using ostk::mathematics::curvefitting::interpolator::QuadraticSpline;
using ostk::mathematics::curvefitting::interpolator::QuinticSpline;
using ostk::mathematics::object::VectorXd;

// NonUniformBSpline is the library-private engine that the spline interpolators fall back to
// when their nodes are not uniformly spaced. It is exercised through those interpolators
// elsewhere; these tests pin down the properties the interpolators rely on.

class OpenSpaceToolkit_Mathematics_Interpolator_NonUniformBSpline : public ::testing::Test
{
   protected:
    void SetUp() override
    {
        // A deliberately ragged grid, with both very short and very long intervals

        raggedX_.resize(12);
        raggedX_ << 0.0, 0.3, 1.1, 1.15, 2.7, 3.0, 4.9, 5.0, 6.6, 8.0, 8.1, 10.0;

        uniformX_.resize(14);

        for (int i = 0; i < uniformX_.size(); ++i)
        {
            uniformX_(i) = 0.5 * double(i);
        }

        uniformY_.resize(uniformX_.size());

        for (int i = 0; i < uniformX_.size(); ++i)
        {
            uniformY_(i) = std::exp(-0.2 * uniformX_(i)) * std::sin(uniformX_(i));
        }
    }

    VectorXd raggedX_;
    VectorXd uniformX_;
    VectorXd uniformY_;
};

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_NonUniformBSpline, ReproducesPolynomialsOfItsOwnDegree)
{
    // A spline of degree p reproduces any polynomial of degree p exactly, however ragged the
    // spacing of its nodes. Both derivatives must come out exactly too.

    for (const Size degree : {Size(2), Size(3), Size(5)})
    {
        const auto value = [degree](const double x)
        {
            return std::pow(x - 3.0, int(degree)) + 2.0 * x - 1.0;
        };
        const auto derivative = [degree](const double x)
        {
            return double(degree) * std::pow(x - 3.0, int(degree) - 1) + 2.0;
        };
        const auto secondDerivative = [degree](const double x)
        {
            return double(degree) * double(degree - 1) * std::pow(x - 3.0, int(degree) - 2);
        };

        VectorXd y(raggedX_.size());

        for (int i = 0; i < raggedX_.size(); ++i)
        {
            y(i) = value(raggedX_(i));
        }

        const NonUniformBSpline spline =
            NonUniformBSpline::Interpolate(raggedX_, y, degree, NonUniformBSpline::DomainBehavior::Throw);

        for (const double x : {0.0, 0.17, 1.13, 2.0, 4.95, 7.3, 8.05, 10.0})
        {
            EXPECT_NEAR(spline.evaluate(x), value(x), 1e-7) << "degree " << degree << " at x = " << x;
            EXPECT_NEAR(spline.computeDerivative(x), derivative(x), 1e-6) << "degree " << degree << " at x = " << x;
            EXPECT_NEAR(spline.computeSecondDerivative(x), secondDerivative(x), 1e-5)
                << "degree " << degree << " at x = " << x;
        }
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_NonUniformBSpline, PassesThroughEveryNode)
{
    VectorXd y(raggedX_.size());

    for (int i = 0; i < raggedX_.size(); ++i)
    {
        y(i) = std::sin(0.7 * raggedX_(i)) + 0.3 * raggedX_(i);
    }

    for (const Size degree : {Size(2), Size(3), Size(5)})
    {
        const NonUniformBSpline spline =
            NonUniformBSpline::Interpolate(raggedX_, y, degree, NonUniformBSpline::DomainBehavior::Throw);

        for (int i = 0; i < raggedX_.size(); ++i)
        {
            EXPECT_NEAR(spline.evaluate(raggedX_(i)), y(i), 1e-10) << "degree " << degree << " at node " << i;
        }
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_NonUniformBSpline, AgreesWithTheCardinalImplementation)
{
    // The point of the merge: on uniformly spaced nodes the general implementation must
    // describe the same curve as the cardinal one that is used in its place, so that which of
    // the two an interpolator picks is not observable.

    const QuadraticSpline cardinalQuadratic = {uniformX_, uniformY_};
    const CubicSpline cardinalCubic = {uniformX_, uniformY_};
    const QuinticSpline cardinalQuintic = {uniformX_, uniformY_};

    const NonUniformBSpline quadratic =
        NonUniformBSpline::Interpolate(uniformX_, uniformY_, 2, NonUniformBSpline::DomainBehavior::Throw);
    const NonUniformBSpline cubic =
        NonUniformBSpline::Interpolate(uniformX_, uniformY_, 3, NonUniformBSpline::DomainBehavior::Throw);
    const NonUniformBSpline quintic =
        NonUniformBSpline::Interpolate(uniformX_, uniformY_, 5, NonUniformBSpline::DomainBehavior::Throw);

    for (double x = 0.0; x <= 6.5; x += 0.017)
    {
        EXPECT_NEAR(quadratic.evaluate(x), cardinalQuadratic.evaluate(x), 1e-12) << "at x = " << x;
        EXPECT_NEAR(quadratic.computeDerivative(x), cardinalQuadratic.computeDerivative(x), 1e-11) << "at x = " << x;

        EXPECT_NEAR(cubic.evaluate(x), cardinalCubic.evaluate(x), 1e-12) << "at x = " << x;
        EXPECT_NEAR(cubic.computeDerivative(x), cardinalCubic.computeDerivative(x), 1e-11) << "at x = " << x;

        EXPECT_NEAR(quintic.evaluate(x), cardinalQuintic.evaluate(x), 1e-12) << "at x = " << x;
        EXPECT_NEAR(quintic.computeDerivative(x), cardinalQuintic.computeDerivative(x), 1e-11) << "at x = " << x;
        EXPECT_NEAR(quintic.computeSecondDerivative(x), cardinalQuintic.computeSecondDerivative(x), 1e-10)
            << "at x = " << x;
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_NonUniformBSpline, DomainBehavior)
{
    VectorXd y(raggedX_.size());

    for (int i = 0; i < raggedX_.size(); ++i)
    {
        y(i) = 2.0 * raggedX_(i) + 1.0;
    }

    {
        const NonUniformBSpline spline =
            NonUniformBSpline::Interpolate(raggedX_, y, 3, NonUniformBSpline::DomainBehavior::Throw);

        EXPECT_NO_THROW(spline.evaluate(0.0));
        EXPECT_NO_THROW(spline.evaluate(10.0));

        EXPECT_THROW(spline.evaluate(-0.1), std::domain_error);
        EXPECT_THROW(spline.evaluate(10.1), std::domain_error);
        EXPECT_THROW(spline.computeDerivative(-0.1), std::domain_error);
        EXPECT_THROW(spline.computeSecondDerivative(10.1), std::domain_error);
    }

    {
        // Extrapolating extends the polynomial of the nearest end span, which for this linear
        // reference data continues the same line

        const NonUniformBSpline spline =
            NonUniformBSpline::Interpolate(raggedX_, y, 3, NonUniformBSpline::DomainBehavior::Extrapolate);

        EXPECT_NO_THROW(spline.evaluate(-0.1));
        EXPECT_NO_THROW(spline.evaluate(10.1));

        EXPECT_NEAR(spline.evaluate(-0.1), 0.8, 1e-8);
        EXPECT_NEAR(spline.evaluate(10.1), 21.2, 1e-8);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_NonUniformBSpline, RejectsNodesThatDoNotAscend)
{
    VectorXd x(6);

    VectorXd y(6);
    y << 0.0, 1.0, 2.0, 3.0, 4.0, 5.0;

    {
        x << 0.0, 2.0, 1.0, 3.0, 4.0, 5.0;

        EXPECT_THROW(
            NonUniformBSpline::Interpolate(x, y, 3, NonUniformBSpline::DomainBehavior::Throw),
            ostk::core::error::runtime::Wrong
        );
    }

    {
        // Repeated nodes leave the interpolation problem singular

        x << 0.0, 1.0, 1.0, 3.0, 4.0, 5.0;

        EXPECT_THROW(
            NonUniformBSpline::Interpolate(x, y, 3, NonUniformBSpline::DomainBehavior::Throw),
            ostk::core::error::runtime::Wrong
        );
    }
}
