/// Apache License 2.0

#include <vector>

#include <gmock/gmock.h>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Shared.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <Global.test.hpp>

using ostk::core::type::Real;
using ostk::core::type::Shared;
using ostk::core::type::Size;

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
    MOCK_METHOD(double, computeDerivative, (const double&), (const, override));
    MOCK_METHOD(VectorXd, computeDerivative, (const VectorXd&), (const, override));

    // IsUniformlySpaced is protected, as it exists for derived classes to pick an
    // implementation with; reach it through a derived class to test it directly

    static bool CallIsUniformlySpaced(const VectorXd& anXVector)
    {
        return Interpolator::IsUniformlySpaced(anXVector);
    }
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

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator, IsUniformlySpaced)
{
    // Getting this wrong in the permissive direction is the dangerous one: a grid wrongly
    // called uniform is interpolated on the reconstructed grid x0 + i * h, and the result is
    // then wrong rather than merely slower.

    const auto vectorFrom = [](const std::vector<double>& aValueArray)
    {
        VectorXd vector(aValueArray.size());

        for (Size i = 0; i < aValueArray.size(); ++i)
        {
            vector(i) = aValueArray[i];
        }

        return vector;
    };

    {
        EXPECT_TRUE(MockInterpolator::CallIsUniformlySpaced(vectorFrom({0.0, 1.0, 2.0, 3.0, 4.0, 5.0})));
        EXPECT_TRUE(MockInterpolator::CallIsUniformlySpaced(vectorFrom({-3.0, -1.0, 1.0, 3.0})));
    }

    {
        // Two nodes are uniformly spaced by construction

        EXPECT_TRUE(MockInterpolator::CallIsUniformlySpaced(vectorFrom({0.0, 7.0})));
    }

    {
        // A spacing that is not exactly representable still counts as uniform

        std::vector<double> values;

        for (Size i = 0; i < 40; ++i)
        {
            values.push_back(0.1 * double(i));
        }

        EXPECT_TRUE(MockInterpolator::CallIsUniformlySpaced(vectorFrom(values)));
    }

    {
        // So does an epoch-like abscissa, where the nodes themselves are only representable
        // to about 1e-7

        std::vector<double> values;

        for (Size i = 0; i < 40; ++i)
        {
            values.push_back(1.4e9 + 60.0 * double(i));
        }

        EXPECT_TRUE(MockInterpolator::CallIsUniformlySpaced(vectorFrom(values)));
    }

    {
        EXPECT_FALSE(MockInterpolator::CallIsUniformlySpaced(vectorFrom({0.0, 1.0, 2.0, 4.0, 5.0, 7.0})));

        // A single node off the grid is enough

        EXPECT_FALSE(MockInterpolator::CallIsUniformlySpaced(vectorFrom({0.0, 1.0, 2.0, 3.01, 4.0, 5.0})));
    }

    {
        // Nodes that do not ascend are never uniform, and are left to the implementation that
        // rejects them

        EXPECT_FALSE(MockInterpolator::CallIsUniformlySpaced(vectorFrom({0.0, 2.0, 1.0, 3.0})));
        EXPECT_FALSE(MockInterpolator::CallIsUniformlySpaced(vectorFrom({5.0, 4.0, 3.0, 2.0})));
        EXPECT_FALSE(MockInterpolator::CallIsUniformlySpaced(vectorFrom({1.0, 1.0, 1.0, 1.0})));
    }
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

    {
        const Shared<const Interpolator> interpolatorSPtr =
            Interpolator::GenerateInterpolator(Interpolator::Type::QuadraticSpline, x, y);
        EXPECT_TRUE(interpolatorSPtr != nullptr);
        EXPECT_EQ(Interpolator::Type::QuadraticSpline, interpolatorSPtr->getInterpolationType());
    }

    {
        // The quintic spline requires at least 8 points

        VectorXd longX(10);
        longX << 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0;

        VectorXd longY(10);
        longY << 0.0, 3.0, 5.0, 6.0, 9.0, 15.0, 18.0, 20.0, 25.0, 33.0;

        const Shared<const Interpolator> interpolatorSPtr =
            Interpolator::GenerateInterpolator(Interpolator::Type::QuinticSpline, longX, longY);
        EXPECT_TRUE(interpolatorSPtr != nullptr);
        EXPECT_EQ(Interpolator::Type::QuinticSpline, interpolatorSPtr->getInterpolationType());
    }

    {
        // The Hermite interpolators additionally require derivative data, and so cannot be generated here

        for (const Interpolator::Type& type : {
                 Interpolator::Type::CubicHermite,
                 Interpolator::Type::QuinticHermite,
             })
        {
            EXPECT_THROW(Interpolator::GenerateInterpolator(type, x, y), ostk::core::error::RuntimeError);
        }
    }
}
