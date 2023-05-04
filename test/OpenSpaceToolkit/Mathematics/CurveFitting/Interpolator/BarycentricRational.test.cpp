////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/Interpolator/BarycentricRational.test.cpp
/// @author         Vishwa Shah <vishwa@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Table.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/BarycentricRational.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::Real ;
using ostk::core::types::Size ;
using ostk::core::types::String ;
using ostk::core::ctnr::Array ;
using ostk::core::ctnr::Table ;
using ostk::core::fs::Path ;
using ostk::core::fs::File ;

using ostk::math::obj::VectorXd ;
using ostk::math::obj::MatrixXd ;
using ostk::math::curvefitting::interp::BarycentricRational ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Mathematics_Interpolator_BarycentricRational, Constructor)
{

    VectorXd x(6) ;
    x << 0.0, 1.0, 2.0, 3.0, 4.0, 5.0 ;

    VectorXd y(6) ;
    y << 0.0, 3.0, 5.0, 6.0, 9.0, 15.0 ;

    {
        EXPECT_NO_THROW(BarycentricRational(x, y)) ;
    }

}

TEST (OpenSpaceToolkit_Mathematics_Interpolator_BarycentricRational, Evaluate)
{

    const Table referenceData = Table::Load(File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/propagated_states.csv")), Table::Format::CSV, true) ;

    const int testRowIncrement = 20 ;

    VectorXd referenceX(referenceData.getRowCount()) ;
    MatrixXd referenceY(referenceData.getRowCount(), 6) ;

    for (Size i = 0 ; i < referenceData.getRowCount() ; ++i)
    {

        const auto& referenceRow = referenceData[i] ;

        referenceX(i) = referenceRow[0].accessReal() ;

        for (Size j = 0 ; j < 6 ; ++j)
        {
            referenceY(i, j) = referenceRow[j + 1].accessReal() ;
        }

    }

    VectorXd testX = referenceX(Eigen::seq(0, Eigen::last, testRowIncrement)) ;
    MatrixXd testY = referenceY(Eigen::seq(0, Eigen::last, testRowIncrement), Eigen::all) ;

    {

        const Size testRowCount = referenceX.size() - testRowIncrement ;

        for (Size j = 0 ; j < 6 ; ++j)
        {

            BarycentricRational spline = BarycentricRational(testX, testY.col(j)) ;

            VectorXd yEstimated = spline.evaluate(referenceX.head(testRowCount)) ;
            VectorXd yTruth = referenceY.col(j).head(testRowCount) ;

            VectorXd residuals = (yEstimated - yTruth).array().abs() ;

            EXPECT_TRUE((residuals.array() < 5e-2).all()) << String::Format("Residual: {}", residuals.maxCoeff()) ;

        }

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
