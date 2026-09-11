/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Table.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/CubicSpline.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <Global.test.hpp>

using ostk::core::container::Array;
using ostk::core::container::Table;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;
using ostk::core::type::Real;
using ostk::core::type::Size;
using ostk::core::type::String;

using ostk::mathematics::curvefitting::interpolator::CubicSpline;
using ostk::mathematics::object::MatrixXd;
using ostk::mathematics::object::VectorXd;

TEST(OpenSpaceToolkit_Mathematics_Interpolator_CubicSpline, Constructor)
{
    VectorXd x(6);
    x << 0.0, 1.0, 2.0, 3.0, 4.0, 5.0;

    VectorXd y(6);
    y << 0.0, 3.0, 5.0, 6.0, 9.0, 15.0;

    {
        EXPECT_NO_THROW(CubicSpline(x, y));
    }

    {
        // At least 5 data points are required

        EXPECT_THROW(CubicSpline(x.head(4), y.head(4)), ostk::core::error::runtime::Wrong);
    }

    {
        EXPECT_THROW(CubicSpline(x.head(5), y), ostk::core::error::runtime::Wrong);
    }

    {
        // Nodes need not be uniformly spaced

        VectorXd nonUniformX(6);
        nonUniformX << 0.0, 1.0, 2.0, 4.0, 5.0, 7.0;

        EXPECT_NO_THROW(CubicSpline(nonUniformX, y));
    }

    {
        // Nodes must be sorted in strictly ascending order

        VectorXd unsortedX(6);
        unsortedX << 0.0, 2.0, 1.0, 3.0, 4.0, 5.0;

        EXPECT_THROW(CubicSpline(unsortedX, y), ostk::core::error::runtime::Wrong);
    }
}

TEST(OpenSpaceToolkit_Mathematics_Interpolator_CubicSpline, SecondConstructor)
{
    VectorXd y(6);
    y << 0.0, 3.0, 5.0, 6.0, 9.0, 15.0;

    {
        EXPECT_NO_THROW(CubicSpline(y, 1.0, 1.0));
    }

    {
        EXPECT_THROW(CubicSpline(y.head(4), 1.0, 1.0), ostk::core::error::runtime::Wrong);
    }

    {
        EXPECT_THROW(CubicSpline(y, 1.0, 0.0), ostk::core::error::runtime::Wrong);
    }

    {
        EXPECT_THROW(CubicSpline(y, 1.0, -1.0), ostk::core::error::runtime::Wrong);
    }
}

TEST(OpenSpaceToolkit_Mathematics_Interpolator_CubicSpline, Evaluate)
{
    const Table referenceData = Table::Load(
        File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/propagated_states.csv")
        ),
        Table::Format::CSV,
        true
    );

    const int testRowIncrement = 20;

    VectorXd referenceX(referenceData.getRowCount());
    MatrixXd referenceY(referenceData.getRowCount(), 6);

    for (Size i = 0; i < referenceData.getRowCount(); ++i)
    {
        const auto& referenceRow = referenceData[i];

        referenceX(i) = referenceRow[0].accessReal();

        for (Size j = 0; j < 6; ++j)
        {
            referenceY(i, j) = referenceRow[j + 1].accessReal();
        }
    }

    VectorXd testX = referenceX(Eigen::seq(0, Eigen::last, testRowIncrement));
    MatrixXd testY = referenceY(Eigen::seq(0, Eigen::last, testRowIncrement), Eigen::all);

    {
        const Size testRowCount = referenceX.size() - testRowIncrement;

        for (Size j = 0; j < 6; ++j)
        {
            CubicSpline spline = CubicSpline(testX, testY.col(j));

            VectorXd yEstimated = spline.evaluate(referenceX.head(testRowCount));
            VectorXd yTruth = referenceY.col(j).head(testRowCount);

            VectorXd residuals = (yEstimated - yTruth).array().abs();

            EXPECT_TRUE((residuals.array() < 5e-3).all()) << String::Format("Residual: {}", residuals.maxCoeff());
        }
    }
}

TEST(OpenSpaceToolkit_Mathematics_Interpolator_CubicSpline, ComputeDerivative)
{
    {
        VectorXd x(6);
        x << 0.0, 1.0, 2.0, 3.0, 4.0, 5.0;

        VectorXd y(6);
        y << 0.0, 3.0, 5.0, 6.0, 9.0, 15.0;

        CubicSpline interpolator(x, y);

        // Values taken from scipy
        EXPECT_NEAR(interpolator.computeDerivative(1.5), 2.03888889, 1e-1);
        EXPECT_NEAR(interpolator.computeDerivative(3.5), 2.98888889, 1e-1);
    }

    {
        VectorXd x(6);
        x << 0.0, 1.0, 2.0, 3.0, 4.0, 5.0;

        VectorXd y(6);
        y << 0.0, 3.0, 5.0, 6.0, 9.0, 15.0;

        CubicSpline interpolator(x, y);

        VectorXd query(2);
        query << 1.5, 3.5;

        VectorXd derivatives = interpolator.computeDerivative(query);

        // Values taken from scipy
        EXPECT_NEAR(derivatives(0), 2.03888889, 1e-1);
        EXPECT_NEAR(derivatives(1), 2.98888889, 1e-1);
    }
}

TEST(OpenSpaceToolkit_Mathematics_Interpolator_CubicSpline, NonUniformNodes)
{
    // Reference data sampled from f(x) = x^3 - 2 * x^2 + 3 * x - 1 on a deliberately ragged
    // grid. Nodes that are not uniformly spaced are interpolated with the general
    // implementation, which reproduces any cubic polynomial exactly just as the cardinal one
    // does on a uniform grid.

    VectorXd x(7);
    x << 0.0, 1.0, 2.0, 4.0, 5.0, 7.0, 8.0;

    VectorXd y(7);
    y << -1.0, 1.0, 5.0, 43.0, 89.0, 265.0, 407.0;

    const CubicSpline interpolator = {x, y};

    {
        EXPECT_NEAR(interpolator.evaluate(1.5), 2.375, 1e-9);
        EXPECT_NEAR(interpolator.evaluate(3.0), 17.0, 1e-9);
        EXPECT_NEAR(interpolator.evaluate(6.0), 161.0, 1e-9);

        // Nodes are reproduced exactly

        EXPECT_NEAR(interpolator.evaluate(0.0), -1.0, 1e-9);
        EXPECT_NEAR(interpolator.evaluate(8.0), 407.0, 1e-9);
    }

    {
        // f'(x) = 3 * x^2 - 4 * x + 3

        EXPECT_NEAR(interpolator.computeDerivative(1.5), 3.75, 1e-9);
        EXPECT_NEAR(interpolator.computeDerivative(3.0), 18.0, 1e-9);
        EXPECT_NEAR(interpolator.computeDerivative(6.0), 87.0, 1e-9);
    }

    {
        VectorXd query(2);
        query << 1.5, 3.0;

        const VectorXd values = interpolator.evaluate(query);

        EXPECT_EQ(2, values.size());
        EXPECT_NEAR(values(0), 2.375, 1e-9);
        EXPECT_NEAR(values(1), 17.0, 1e-9);

        const VectorXd derivatives = interpolator.computeDerivative(query);

        EXPECT_EQ(2, derivatives.size());
        EXPECT_NEAR(derivatives(0), 3.75, 1e-9);
        EXPECT_NEAR(derivatives(1), 18.0, 1e-9);
    }
}
