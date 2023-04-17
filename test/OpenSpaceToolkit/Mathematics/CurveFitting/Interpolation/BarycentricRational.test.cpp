////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           OpenSpaceToolkit/Mathematics/Interpolation/BarycentricRational.test.cpp
/// @author         Vishwa Shah <vishwa@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Table.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolation/BarycentricRational.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Mathematics_Interpolator_BarycentricRational, Constructor)
{

    using ostk::core::types::Real ;

    using ostk::math::obj::VectorXd ;
    using ostk::math::curvefitting::interp::BarycentricRational ;

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
        EXPECT_NO_THROW(BarycentricRational(x, y)) ;
    }

}

TEST (OpenSpaceToolkit_Mathematics_Interpolator_BarycentricRational, Evaluate)
{

    using ostk::core::types::Real ;
    using ostk::core::types::Size ;
    using ostk::core::ctnr::Array ;
    using ostk::core::ctnr::Table ;
    using ostk::core::fs::Path ;
    using ostk::core::fs::File ;

    using ostk::math::obj::VectorXd ;
    using ostk::math::obj::MatrixXd ;
    using ostk::math::curvefitting::interp::BarycentricRational ;

    const Table referenceData = Table::Load(File::Path(Path::Parse("/app/test/OpenSpaceToolkit/Mathematics/CurveFitting/Interpolation/propagated_states.csv")), Table::Format::CSV, true) ;

    const int testRowIncrement = 20 ;

    VectorXd referenceX(referenceData.getRowCount()) ;
    MatrixXd referenceY(referenceData.getRowCount(), referenceData.getColumnCount()) ;

    int i = 0 ;
    for (const auto& referenceRow : referenceData)
    {

        referenceX(i) = Real::Integer(i) ;

        for (Size j = 0 ; j < referenceData.getColumnCount() ; ++j)
        {
            referenceY(i, j) = referenceRow[j].accessReal() ;
        }

        ++i ;

    }

    VectorXd testX = referenceX(Eigen::seq(0, Eigen::last, testRowIncrement)) ;
    MatrixXd testY = referenceY(Eigen::seq(0, Eigen::last, testRowIncrement), Eigen::all) ;

    {

        const Size testRowCount = referenceX.size() - testRowIncrement ;

        for (Size j = 0 ; j < referenceData.getColumnCount() ; ++j)
        {
            BarycentricRational spline = BarycentricRational(testX, testY.col(j)) ;
            VectorXd yEstimated = spline.evaluate(referenceX.head(testRowCount)) ;
            VectorXd residuals = (yEstimated - referenceY.col(j).head(testRowCount)).array().abs() ;
            EXPECT_TRUE(residuals.unaryExpr([](double x) { return x < 1e-1 ; }).all()) ;
        }

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
