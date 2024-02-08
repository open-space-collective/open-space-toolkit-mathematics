/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Table.hpp>
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
}

TEST(OpenSpaceToolkit_Mathematics_Interpolator_CubicSpline, SecondConstructor)
{
    VectorXd y(6);
    y << 0.0, 3.0, 5.0, 6.0, 9.0, 15.0;

    {
        EXPECT_NO_THROW(CubicSpline(y, 1.0, 1.0));
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
