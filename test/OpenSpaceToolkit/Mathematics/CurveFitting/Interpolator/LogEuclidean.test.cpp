/// Apache License 2.0

#include <cmath>

#include <Eigen/Eigenvalues>

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/LogEuclidean.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <Global.test.hpp>

using ostk::core::container::Array;
using ostk::core::type::Real;
using ostk::core::type::Size;

using ostk::mathematics::curvefitting::interpolator::LogEuclidean;
using ostk::mathematics::object::MatrixXd;
using ostk::mathematics::object::VectorXd;

class OpenSpaceToolkit_Mathematics_Interpolator_LogEuclidean : public ::testing::Test
{
   protected:
    MatrixXd makeIdentity(int size) const
    {
        return MatrixXd::Identity(size, size);
    }

    MatrixXd makeSPD(int size, double scale) const
    {
        return MatrixXd::Identity(size, size) * scale;
    }

    MatrixXd makeSPD3x3() const
    {
        MatrixXd m(3, 3);
        // A known SPD matrix: [[4, 2, 1], [2, 5, 3], [1, 3, 6]]
        m << 4.0, 2.0, 1.0, 2.0, 5.0, 3.0, 1.0, 3.0, 6.0;
        return m;
    }
};

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_LogEuclidean, Constructor)
{
    {
        VectorXd x(2);
        x << 0.0, 1.0;

        Array<MatrixXd> matrices = {makeIdentity(3), makeSPD(3, 2.0)};

        EXPECT_NO_THROW(LogEuclidean(x, matrices));
    }

    // Mismatched sizes
    {
        VectorXd x(3);
        x << 0.0, 1.0, 2.0;

        Array<MatrixXd> matrices = {makeIdentity(3), makeSPD(3, 2.0)};

        EXPECT_THROW(LogEuclidean(x, matrices), ostk::core::error::runtime::Wrong);
    }

    // Too few points
    {
        VectorXd x(1);
        x << 0.0;

        Array<MatrixXd> matrices = {makeIdentity(3)};

        EXPECT_THROW(LogEuclidean(x, matrices), ostk::core::error::runtime::Wrong);
    }

    // Non-square matrix
    {
        VectorXd x(2);
        x << 0.0, 1.0;

        MatrixXd rect(2, 3);
        rect << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0;

        Array<MatrixXd> matrices = {rect, rect};

        EXPECT_THROW(LogEuclidean(x, matrices), ostk::core::error::runtime::Wrong);
    }

    // Inconsistent matrix dimensions
    {
        VectorXd x(2);
        x << 0.0, 1.0;

        Array<MatrixXd> matrices = {makeIdentity(3), makeIdentity(4)};

        EXPECT_THROW(LogEuclidean(x, matrices), ostk::core::error::runtime::Wrong);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_LogEuclidean, Evaluate_Endpoints)
{
    const MatrixXd P0 = makeIdentity(3);
    const MatrixXd P1 = makeSPD(3, 4.0);

    VectorXd x(2);
    x << 0.0, 1.0;

    Array<MatrixXd> matrices = {P0, P1};
    LogEuclidean interpolator(x, matrices);

    // At x=0, should return P0
    {
        MatrixXd result = interpolator.evaluate(0.0);
        EXPECT_TRUE(result.isApprox(P0, 1e-10));
    }

    // At x=1, should return P1
    {
        MatrixXd result = interpolator.evaluate(1.0);
        EXPECT_TRUE(result.isApprox(P1, 1e-10));
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_LogEuclidean, Evaluate_Midpoint_Diagonal)
{
    // For diagonal SPD matrices, log-euclidean midpoint should be the geometric mean
    // P0 = diag(1, 1, 1), P1 = diag(4, 9, 16)
    // Midpoint = diag(exp(0.5*ln(1) + 0.5*ln(4)), ...) = diag(2, 3, 4)

    MatrixXd P0 = makeIdentity(3);

    MatrixXd P1(3, 3);
    P1 << 4.0, 0.0, 0.0, 0.0, 9.0, 0.0, 0.0, 0.0, 16.0;

    VectorXd x(2);
    x << 0.0, 1.0;

    Array<MatrixXd> matrices = {P0, P1};
    LogEuclidean interpolator(x, matrices);

    MatrixXd result = interpolator.evaluate(0.5);

    MatrixXd expected(3, 3);
    expected << 2.0, 0.0, 0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 4.0;

    EXPECT_TRUE(result.isApprox(expected, 1e-10));
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_LogEuclidean, Evaluate_ResultIsSPD)
{
    const MatrixXd P0 = makeSPD3x3();

    MatrixXd P1(3, 3);
    P1 << 10.0, 3.0, 2.0, 3.0, 8.0, 1.0, 2.0, 1.0, 7.0;

    VectorXd x(2);
    x << 0.0, 1.0;

    Array<MatrixXd> matrices = {P0, P1};
    LogEuclidean interpolator(x, matrices);

    // Test multiple interpolation points
    for (double alpha = 0.1; alpha <= 0.9; alpha += 0.1)
    {
        MatrixXd result = interpolator.evaluate(alpha);

        // Check symmetry
        EXPECT_TRUE(result.isApprox(result.transpose(), 1e-10))
            << "Result is not symmetric at alpha=" << alpha;

        // Check positive definiteness via eigenvalues
        Eigen::SelfAdjointEigenSolver<MatrixXd> solver(result);
        EXPECT_TRUE((solver.eigenvalues().array() > 0.0).all())
            << "Result is not positive definite at alpha=" << alpha;
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_LogEuclidean, Evaluate_MultipleSegments)
{
    VectorXd x(3);
    x << 0.0, 1.0, 2.0;

    MatrixXd P0 = makeIdentity(2);

    MatrixXd P1(2, 2);
    P1 << 4.0, 0.0, 0.0, 4.0;

    MatrixXd P2(2, 2);
    P2 << 16.0, 0.0, 0.0, 16.0;

    Array<MatrixXd> matrices = {P0, P1, P2};
    LogEuclidean interpolator(x, matrices);

    // At x=0.5, interpolate between P0 and P1
    {
        MatrixXd result = interpolator.evaluate(0.5);
        MatrixXd expected(2, 2);
        expected << 2.0, 0.0, 0.0, 2.0;
        EXPECT_TRUE(result.isApprox(expected, 1e-10));
    }

    // At x=1.5, interpolate between P1 and P2
    {
        MatrixXd result = interpolator.evaluate(1.5);
        MatrixXd expected(2, 2);
        expected << 8.0, 0.0, 0.0, 8.0;
        EXPECT_TRUE(result.isApprox(expected, 1e-10));
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_LogEuclidean, Evaluate_Vector)
{
    VectorXd x(2);
    x << 0.0, 1.0;

    MatrixXd P0 = makeIdentity(2);
    MatrixXd P1(2, 2);
    P1 << 4.0, 0.0, 0.0, 9.0;

    Array<MatrixXd> matrices = {P0, P1};
    LogEuclidean interpolator(x, matrices);

    VectorXd query(3);
    query << 0.0, 0.5, 1.0;

    Array<MatrixXd> results = interpolator.evaluate(query);

    EXPECT_EQ(results.getSize(), Size(3));
    EXPECT_TRUE(results[0].isApprox(P0, 1e-10));
    EXPECT_TRUE(results[2].isApprox(P1, 1e-10));

    // Midpoint should be geometric mean of diagonal entries
    MatrixXd expectedMid(2, 2);
    expectedMid << 2.0, 0.0, 0.0, 3.0;
    EXPECT_TRUE(results[1].isApprox(expectedMid, 1e-10));
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_LogEuclidean, Evaluate_Extrapolation)
{
    VectorXd x(2);
    x << 0.0, 1.0;

    MatrixXd P0 = makeIdentity(2);
    MatrixXd P1(2, 2);
    P1 << 4.0, 0.0, 0.0, 4.0;

    Array<MatrixXd> matrices = {P0, P1};
    LogEuclidean interpolator(x, matrices);

    // Before range: clamp to first
    {
        MatrixXd result = interpolator.evaluate(-1.0);
        EXPECT_TRUE(result.isApprox(P0, 1e-10));
    }

    // After range: clamp to last
    {
        MatrixXd result = interpolator.evaluate(2.0);
        EXPECT_TRUE(result.isApprox(P1, 1e-10));
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_LogEuclidean, MatrixLogSPD)
{
    // log(I) = 0
    {
        MatrixXd identity = makeIdentity(3);
        MatrixXd result = LogEuclidean::MatrixLogSPD(identity);
        EXPECT_TRUE(result.isApprox(MatrixXd::Zero(3, 3), 1e-10));
    }

    // log(diag(e, e^2, e^3)) = diag(1, 2, 3)
    {
        MatrixXd diag(3, 3);
        diag << std::exp(1.0), 0.0, 0.0, 0.0, std::exp(2.0), 0.0, 0.0, 0.0, std::exp(3.0);

        MatrixXd expected(3, 3);
        expected << 1.0, 0.0, 0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 3.0;

        MatrixXd result = LogEuclidean::MatrixLogSPD(diag);
        EXPECT_TRUE(result.isApprox(expected, 1e-10));
    }

    // Non-positive-definite matrix should throw
    {
        MatrixXd notPD(2, 2);
        notPD << 1.0, 0.0, 0.0, -1.0;

        EXPECT_THROW(LogEuclidean::MatrixLogSPD(notPD), ostk::core::error::RuntimeError);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_LogEuclidean, MatrixExpSymmetric)
{
    // exp(0) = I
    {
        MatrixXd zero = MatrixXd::Zero(3, 3);
        MatrixXd result = LogEuclidean::MatrixExpSymmetric(zero);
        EXPECT_TRUE(result.isApprox(makeIdentity(3), 1e-10));
    }

    // exp(diag(1, 2, 3)) = diag(e, e^2, e^3)
    {
        MatrixXd diag(3, 3);
        diag << 1.0, 0.0, 0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 3.0;

        MatrixXd expected(3, 3);
        expected << std::exp(1.0), 0.0, 0.0, 0.0, std::exp(2.0), 0.0, 0.0, 0.0, std::exp(3.0);

        MatrixXd result = LogEuclidean::MatrixExpSymmetric(diag);
        EXPECT_TRUE(result.isApprox(expected, 1e-10));
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_LogEuclidean, LogExpRoundTrip)
{
    const MatrixXd P = makeSPD3x3();

    MatrixXd logP = LogEuclidean::MatrixLogSPD(P);
    MatrixXd result = LogEuclidean::MatrixExpSymmetric(logP);

    EXPECT_TRUE(result.isApprox(P, 1e-10));
}

TEST_F(OpenSpaceToolkit_Mathematics_Interpolator_LogEuclidean, Interpolate_Static)
{
    MatrixXd P0 = makeIdentity(3);
    MatrixXd P1(3, 3);
    P1 << 4.0, 0.0, 0.0, 0.0, 9.0, 0.0, 0.0, 0.0, 16.0;

    // alpha=0 returns P0
    {
        MatrixXd result = LogEuclidean::Interpolate(P0, P1, 0.0);
        EXPECT_TRUE(result.isApprox(P0, 1e-10));
    }

    // alpha=1 returns P1
    {
        MatrixXd result = LogEuclidean::Interpolate(P0, P1, 1.0);
        EXPECT_TRUE(result.isApprox(P1, 1e-10));
    }

    // alpha=0.5 returns geometric mean for diagonal matrices
    {
        MatrixXd result = LogEuclidean::Interpolate(P0, P1, 0.5);

        MatrixXd expected(3, 3);
        expected << 2.0, 0.0, 0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 4.0;

        EXPECT_TRUE(result.isApprox(expected, 1e-10));
    }
}
