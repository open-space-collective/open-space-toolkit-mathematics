/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Table.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/BarycentricRational.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <Global.test.hpp>

using ostk::core::container::Array;
using ostk::core::container::Table;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;
using ostk::core::type::Real;
using ostk::core::type::Size;
using ostk::core::type::String;

using ostk::mathematics::curvefitting::interpolator::BarycentricRational;
using ostk::mathematics::object::MatrixXd;
using ostk::mathematics::object::VectorXd;

TEST(OpenSpaceToolkit_Mathematics_Interpolator_BarycentricRational, Constructor)
{
    VectorXd x(6);
    x << 0.0, 1.0, 2.0, 3.0, 4.0, 5.0;

    VectorXd y(6);
    y << 0.0, 3.0, 5.0, 6.0, 9.0, 15.0;

    {
        EXPECT_NO_THROW(BarycentricRational(x, y));
    }
}

TEST(OpenSpaceToolkit_Mathematics_Interpolator_BarycentricRational, Evaluate)
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
            BarycentricRational spline = BarycentricRational(testX, testY.col(j));

            VectorXd yEstimated = spline.evaluate(referenceX.head(testRowCount));
            VectorXd yTruth = referenceY.col(j).head(testRowCount);

            VectorXd residuals = (yEstimated - yTruth).array().abs();

            EXPECT_TRUE((residuals.array() < 5e-2).all()) << String::Format("Residual: {}", residuals.maxCoeff());
        }
    }
}

TEST(OpenSpaceToolkit_Mathematics_Interpolator_BarycentricRational, ComputeDerivative)
{
    {
        VectorXd x(6);
        x << 0.0, 1.0, 2.0, 3.0, 4.0, 5.0;

        VectorXd y(6);
        y << 0.0, 3.0, 5.0, 6.0, 9.0, 15.0;

        BarycentricRational interpolator(x, y);

        // Values taken from scipy
        EXPECT_NEAR(interpolator.computeDerivative(1.5), 1.9765624999999993, 1e-1);
        EXPECT_NEAR(interpolator.computeDerivative(3.5), 2.9348958333333335, 1e-1);
    }

    {
        VectorXd x(6);
        x << 0.0, 1.0, 2.0, 3.0, 4.0, 5.0;

        VectorXd y(6);
        y << 0.0, 3.0, 5.0, 6.0, 9.0, 15.0;

        BarycentricRational interpolator(x, y);

        VectorXd query(2);
        query << 1.5, 3.5;

        VectorXd derivatives = interpolator.computeDerivative(query);

        // Values taken from scipy
        EXPECT_NEAR(derivatives(0), 1.9765624999999993, 1e-1);
        EXPECT_NEAR(derivatives(1), 2.9348958333333335, 1e-1);
    }
}
