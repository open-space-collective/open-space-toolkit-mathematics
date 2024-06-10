/// Apache License 2.0

#include <gmock/gmock.h>

#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <Global.test.hpp>

using ostk::core::type::Real;
using ostk::core::type::Shared;

using ostk::mathematics::curvefitting::Interpolator;
using ostk::mathematics::object::VectorXd;

class MockInterpolator : public Interpolator
{
   public:
    MockInterpolator(const Interpolator::Type& aType)
        : Interpolator(aType)
    {
    }

    MOCK_METHOD(VectorXd, evaluate, (const VectorXd&), (const, override));
    MOCK_METHOD(double, evaluate, (const double&), (const, override));
};

class OpenSpaceToolkit_Mathematics_Interpolator : public ::testing::Test
{
   protected:
    const Interpolator::Type defaulttype_ = Interpolator::Type::BarycentricRational;
    const MockInterpolator defaultInterpolator_ {defaulttype_};
};

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator, Constructor)
{
    EXPECT_NO_THROW(MockInterpolator mockInterpolator(defaulttype_));
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator, GetInterpolationType)
{
    EXPECT_EQ(defaulttype_, defaultInterpolator_.getInterpolationType());
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator, GenerateInterpolator)
{
    VectorXd x(6);
    x << 0.0, 1.0, 2.0, 3.0, 4.0, 5.0;

    VectorXd y(6);
    y << 0.0, 3.0, 5.0, 6.0, 9.0, 15.0;

    {
        const Shared<const Interpolator> interpolatorSPtr =
            Interpolator::GenerateInterpolator(Interpolator::Type::BarycentricRational, x, y);
        EXPECT_TRUE(interpolatorSPtr != nullptr);
        EXPECT_EQ(Interpolator::Type::BarycentricRational, interpolatorSPtr->getInterpolationType());
    }

    {
        const Shared<const Interpolator> interpolatorSPtr =
            Interpolator::GenerateInterpolator(Interpolator::Type::CubicSpline, x, y);
        EXPECT_TRUE(interpolatorSPtr != nullptr);
        EXPECT_EQ(Interpolator::Type::CubicSpline, interpolatorSPtr->getInterpolationType());
    }

    {
        const Shared<const Interpolator> interpolatorSPtr =
            Interpolator::GenerateInterpolator(Interpolator::Type::Linear, x, y);
        EXPECT_TRUE(interpolatorSPtr != nullptr);
        EXPECT_EQ(Interpolator::Type::Linear, interpolatorSPtr->getInterpolationType());
    }
}
