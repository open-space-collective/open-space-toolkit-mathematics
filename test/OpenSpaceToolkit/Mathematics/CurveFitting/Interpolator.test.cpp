/// Apache License 2.0

#include <gmock/gmock.h>

#include <OpenSpaceToolkit/Core/Type/Real.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator.hpp>

#include <Global.test.hpp>

using ostk::core::type::Real;

using ostk::math::object::VectorXd;
using ostk::math::curvefitting::Interpolator;

class MockInterpolator : public Interpolator
{
   public:
    MockInterpolator(const Interpolator::InterpolationType& anInterpolationType)
        : Interpolator(anInterpolationType)
    {
    }

    MOCK_METHOD(VectorXd, evaluate, (const VectorXd&), (const, override));
    MOCK_METHOD(double, evaluate, (const double&), (const, override));
};

class OpenSpaceToolkit_Mathematics_Interpolator : public ::testing::Test
{
   protected:
    const Interpolator::InterpolationType defaultInterpolationType_ =
        Interpolator::InterpolationType::BarycentricRational;
    const MockInterpolator defaultInterpolator_ {defaultInterpolationType_};
};

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator, Constructor)
{
    EXPECT_NO_THROW(MockInterpolator mockInterpolator(defaultInterpolationType_));
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator, GetInterpolationType)
{
    EXPECT_EQ(defaultInterpolationType_, defaultInterpolator_.getInterpolationType());
}
