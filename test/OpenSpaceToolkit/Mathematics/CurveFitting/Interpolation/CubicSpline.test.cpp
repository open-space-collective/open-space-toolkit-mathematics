////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/Interpolation/CubicSpline.test.cpp
/// @author         Vishwa Shah <vishwa@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Table.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolation/CubicSpline.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Mathematics_Interpolator_CubicSpline, Constructor)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::VectorXd ;
    using ostk::math::curvefitting::interp::CubicSpline ;

    VectorXd x(6) ;
    x(0) = 0.0 ;
    x(1) = 1.0 ;
    x(2) = 2.0 ;
    x(3) = 3.0 ;
    x(4) = 4.0 ;
    x(5) = 5.0 ;

    VectorXd y(6) ;
    y(0) = 0.0 ;
    y(1) = 3.0 ;
    y(2) = 5.0 ;
    y(3) = 6.0 ;
    y(4) = 9.0 ;
    y(5) = 15.0 ;

    {
        EXPECT_NO_THROW(CubicSpline(x, y)) ;
    }

}

TEST (OpenSpaceToolkit_Mathematics_Interpolator_CubicSpline, SecondConstructor)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::VectorXd ;
    using ostk::math::curvefitting::interp::CubicSpline ;

    VectorXd y(6) ;
    y(0) = 0.0 ;
    y(1) = 3.0 ;
    y(2) = 5.0 ;
    y(3) = 6.0 ;
    y(4) = 9.0 ;
    y(5) = 15.0 ;

    {
        EXPECT_NO_THROW(CubicSpline(y, 1.0, 1.0)) ;
    }

}

TEST (OpenSpaceToolkit_Mathematics_Interpolator_CubicSpline, Evaluate)
{

    using ostk::core::types::Real ;
    using ostk::core::types::Size ;
    using ostk::core::types::String ;
    using ostk::core::ctnr::Array ;
    using ostk::core::ctnr::Table ;
    using ostk::core::fs::Path ;
    using ostk::core::fs::File ;

    using ostk::math::obj::VectorXd ;
    using ostk::math::obj::MatrixXd ;
    using ostk::math::curvefitting::interp::CubicSpline ;

    const Table referenceData = Table::Load(File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Mathematics/CurveFitting/Interpolation/propagated_states.csv")), Table::Format::CSV, true) ;

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

            CubicSpline spline = CubicSpline(testX, testY.col(j)) ;

            VectorXd yEstimated = spline.evaluate(referenceX.head(testRowCount)) ;
            VectorXd yTruth = referenceY.col(j).head(testRowCount) ;

            EXPECT_TRUE(yEstimated.isApprox(yTruth, 1e-2)) << String::Format("Residual: {}", (yEstimated - yTruth).array().abs().maxCoeff()) ;

        }

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
