/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/ZeroOrder.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <Global.test.hpp>

using ostk::core::type::Real;
using ostk::core::type::Size;

using ostk::mathematics::curvefitting::interpolator::ZeroOrder;
using ostk::mathematics::object::VectorXd;

TEST(OpenSpaceToolkit_Mathematics_Interpolator_ZeroOrder, Constructor)
{
    VectorXd x(6);
    x << 0.0, 1.0, 2.0, 3.0, 4.0, 5.0;

    VectorXd y(6);
    y << 0.0, 3.0, 5.0, 6.0, 9.0, 15.0;

    {
        EXPECT_NO_THROW(ZeroOrder(x, y));
    }

    // Single point should work
    {
        VectorXd x1(1);
        x1 << 1.0;
        VectorXd y1(1);
        y1 << 5.0;

        EXPECT_NO_THROW(ZeroOrder(x1, y1));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Interpolator_ZeroOrder, Evaluate_Scalar)
{
    VectorXd x(6);
    x << 0.0, 1.0, 2.0, 3.0, 4.0, 5.0;

    VectorXd y(6);
    y << 0.0, 3.0, 5.0, 6.0, 9.0, 15.0;

    ZeroOrder interpolator(x, y);

    // Query at exact data points should return that point's value
    EXPECT_DOUBLE_EQ(interpolator.evaluate(0.0), 0.0);
    EXPECT_DOUBLE_EQ(interpolator.evaluate(1.0), 3.0);
    EXPECT_DOUBLE_EQ(interpolator.evaluate(2.0), 5.0);
    EXPECT_DOUBLE_EQ(interpolator.evaluate(3.0), 6.0);
    EXPECT_DOUBLE_EQ(interpolator.evaluate(4.0), 9.0);
    EXPECT_DOUBLE_EQ(interpolator.evaluate(5.0), 15.0);

    // Query between data points should return the previous point's value
    EXPECT_DOUBLE_EQ(interpolator.evaluate(0.5), 0.0);
    EXPECT_DOUBLE_EQ(interpolator.evaluate(1.5), 3.0);
    EXPECT_DOUBLE_EQ(interpolator.evaluate(2.5), 5.0);
    EXPECT_DOUBLE_EQ(interpolator.evaluate(3.5), 6.0);
    EXPECT_DOUBLE_EQ(interpolator.evaluate(4.5), 9.0);

    // Query beyond last point should return last point's value
    EXPECT_DOUBLE_EQ(interpolator.evaluate(6.0), 15.0);
    EXPECT_DOUBLE_EQ(interpolator.evaluate(100.0), 15.0);

    // Query before first point should return first point's value
    EXPECT_DOUBLE_EQ(interpolator.evaluate(-1.0), 0.0);
}

TEST(OpenSpaceToolkit_Mathematics_Interpolator_ZeroOrder, Evaluate_Vector)
{
    VectorXd x(6);
    x << 0.0, 1.0, 2.0, 3.0, 4.0, 5.0;

    VectorXd y(6);
    y << 0.0, 3.0, 5.0, 6.0, 9.0, 15.0;

    ZeroOrder interpolator(x, y);

    VectorXd query(5);
    query << 0.5, 1.5, 2.5, 3.5, 4.5;

    VectorXd result = interpolator.evaluate(query);

    EXPECT_DOUBLE_EQ(result(0), 0.0);
    EXPECT_DOUBLE_EQ(result(1), 3.0);
    EXPECT_DOUBLE_EQ(result(2), 5.0);
    EXPECT_DOUBLE_EQ(result(3), 6.0);
    EXPECT_DOUBLE_EQ(result(4), 9.0);
}

TEST(OpenSpaceToolkit_Mathematics_Interpolator_ZeroOrder, ComputeDerivative)
{
    VectorXd x(6);
    x << 0.0, 1.0, 2.0, 3.0, 4.0, 5.0;

    VectorXd y(6);
    y << 0.0, 3.0, 5.0, 6.0, 9.0, 15.0;

    ZeroOrder interpolator(x, y);

    // Derivative should always be 0 for step function
    EXPECT_DOUBLE_EQ(interpolator.computeDerivative(0.5), 0.0);
    EXPECT_DOUBLE_EQ(interpolator.computeDerivative(1.5), 0.0);
    EXPECT_DOUBLE_EQ(interpolator.computeDerivative(2.5), 0.0);

    // Vector derivative
    VectorXd query(3);
    query << 0.5, 1.5, 2.5;

    VectorXd derivatives = interpolator.computeDerivative(query);

    EXPECT_DOUBLE_EQ(derivatives(0), 0.0);
    EXPECT_DOUBLE_EQ(derivatives(1), 0.0);
    EXPECT_DOUBLE_EQ(derivatives(2), 0.0);
}

TEST(OpenSpaceToolkit_Mathematics_Interpolator_ZeroOrder, GetInterpolationType)
{
    VectorXd x(2);
    x << 0.0, 1.0;

    VectorXd y(2);
    y << 0.0, 1.0;

    ZeroOrder interpolator(x, y);

    EXPECT_EQ(interpolator.getInterpolationType(), ostk::mathematics::curvefitting::Interpolator::Type::ZeroOrder);
}
