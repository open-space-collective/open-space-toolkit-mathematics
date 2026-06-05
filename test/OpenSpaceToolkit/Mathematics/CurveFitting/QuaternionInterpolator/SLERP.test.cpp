/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/QuaternionInterpolator/SLERP.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/Angle.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/Quaternion.hpp>
#include <OpenSpaceToolkit/Mathematics/Geometry/3D/Transformation/Rotation/RotationVector.hpp>
#include <OpenSpaceToolkit/Mathematics/Object/Vector.hpp>

#include <Global.test.hpp>

using ostk::core::container::Array;
using ostk::core::type::Real;
using ostk::core::type::Size;

using ostk::mathematics::curvefitting::quaternioninterpolator::SLERP;
using ostk::mathematics::geometry::Angle;
using ostk::mathematics::geometry::d3::transformation::rotation::Quaternion;
using ostk::mathematics::geometry::d3::transformation::rotation::RotationVector;
using ostk::mathematics::object::Vector3d;
using ostk::mathematics::object::VectorXd;

class OpenSpaceToolkit_Mathematics_QuaternionInterpolator_SLERP : public ::testing::Test
{
   protected:
    // Rotation about the +Z axis by a given angle (degrees)
    Quaternion makeZRotation(const double& anAngleInDegrees) const
    {
        return Quaternion::RotationVector(RotationVector({0.0, 0.0, 1.0}, Angle::Degrees(anAngleInDegrees)));
    }

    const Angle tolerance_ = Angle::Degrees(1e-9);
};

TEST_F(OpenSpaceToolkit_Mathematics_QuaternionInterpolator_SLERP, Constructor)
{
    // Success
    {
        VectorXd x(2);
        x << 0.0, 1.0;

        Array<Quaternion> quaternions = {makeZRotation(0.0), makeZRotation(90.0)};

        EXPECT_NO_THROW(SLERP(x, quaternions));
    }

    // Too few points
    {
        VectorXd x(1);
        x << 0.0;

        Array<Quaternion> quaternions = {Quaternion::Unit()};

        EXPECT_THROW(SLERP(x, quaternions), ostk::core::error::runtime::Wrong);
    }

    // Mismatched sizes
    {
        VectorXd x(3);
        x << 0.0, 1.0, 2.0;

        Array<Quaternion> quaternions = {makeZRotation(0.0), makeZRotation(90.0)};

        EXPECT_THROW(SLERP(x, quaternions), ostk::core::error::runtime::Wrong);
    }

    // Non-monotonic x (decreasing)
    {
        VectorXd x(3);
        x << 0.0, 2.0, 1.0;

        Array<Quaternion> quaternions = {makeZRotation(0.0), makeZRotation(45.0), makeZRotation(90.0)};

        EXPECT_THROW(SLERP(x, quaternions), ostk::core::error::runtime::Wrong);
    }

    // Non-monotonic x (duplicate values)
    {
        VectorXd x(3);
        x << 0.0, 1.0, 1.0;

        Array<Quaternion> quaternions = {makeZRotation(0.0), makeZRotation(45.0), makeZRotation(90.0)};

        EXPECT_THROW(SLERP(x, quaternions), ostk::core::error::runtime::Wrong);
    }

    // Undefined quaternion
    {
        VectorXd x(2);
        x << 0.0, 1.0;

        Array<Quaternion> quaternions = {Quaternion::Unit(), Quaternion::Undefined()};

        EXPECT_THROW(SLERP(x, quaternions), ostk::core::error::runtime::Undefined);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_QuaternionInterpolator_SLERP, Evaluate_Endpoints)
{
    const Quaternion q0 = makeZRotation(0.0);
    const Quaternion q1 = makeZRotation(90.0);

    VectorXd x(2);
    x << 0.0, 1.0;

    Array<Quaternion> quaternions = {q0, q1};
    SLERP interpolator(x, quaternions);

    EXPECT_TRUE(interpolator.evaluate(0.0).isNear(q0, tolerance_));
    EXPECT_TRUE(interpolator.evaluate(1.0).isNear(q1, tolerance_));
}

TEST_F(OpenSpaceToolkit_Mathematics_QuaternionInterpolator_SLERP, Evaluate_Midpoint)
{
    // SLERP halfway between a 0 deg and a 90 deg rotation about the same axis is a 45 deg rotation
    const Quaternion q0 = makeZRotation(0.0);
    const Quaternion q1 = makeZRotation(90.0);

    VectorXd x(2);
    x << 0.0, 1.0;

    Array<Quaternion> quaternions = {q0, q1};
    SLERP interpolator(x, quaternions);

    const Quaternion result = interpolator.evaluate(0.5);

    EXPECT_TRUE(result.isNear(makeZRotation(45.0), tolerance_));
}

TEST_F(OpenSpaceToolkit_Mathematics_QuaternionInterpolator_SLERP, Evaluate_ConstantAngularVelocity)
{
    // SLERP traverses the great-circle arc at constant angular velocity:
    // the interpolated rotation angle should grow linearly with the query value
    const Quaternion q0 = makeZRotation(0.0);
    const Quaternion q1 = makeZRotation(90.0);

    VectorXd x(2);
    x << 0.0, 1.0;

    Array<Quaternion> quaternions = {q0, q1};
    SLERP interpolator(x, quaternions);

    for (double ratio = 0.0; ratio <= 1.0; ratio += 0.1)
    {
        const Quaternion result = interpolator.evaluate(ratio);

        EXPECT_TRUE(result.isNear(makeZRotation(90.0 * ratio), tolerance_)) << "Mismatch at ratio=" << ratio;

        // Result must be a unit quaternion
        EXPECT_NEAR(result.toVector().norm(), 1.0, 1e-12);
    }
}

TEST_F(OpenSpaceToolkit_Mathematics_QuaternionInterpolator_SLERP, Evaluate_MultipleSegments)
{
    VectorXd x(3);
    x << 0.0, 1.0, 2.0;

    Array<Quaternion> quaternions = {makeZRotation(0.0), makeZRotation(40.0), makeZRotation(120.0)};
    SLERP interpolator(x, quaternions);

    // Within first segment
    EXPECT_TRUE(interpolator.evaluate(0.5).isNear(makeZRotation(20.0), tolerance_));

    // Within second segment
    EXPECT_TRUE(interpolator.evaluate(1.5).isNear(makeZRotation(80.0), tolerance_));
}

TEST_F(OpenSpaceToolkit_Mathematics_QuaternionInterpolator_SLERP, Evaluate_Vector)
{
    const Quaternion q0 = makeZRotation(0.0);
    const Quaternion q1 = makeZRotation(90.0);

    VectorXd x(2);
    x << 0.0, 1.0;

    Array<Quaternion> quaternions = {q0, q1};
    SLERP interpolator(x, quaternions);

    VectorXd query(3);
    query << 0.0, 0.5, 1.0;

    const Array<Quaternion> results = interpolator.evaluate(query);

    EXPECT_EQ(results.getSize(), Size(3));
    EXPECT_TRUE(results[0].isNear(q0, tolerance_));
    EXPECT_TRUE(results[1].isNear(makeZRotation(45.0), tolerance_));
    EXPECT_TRUE(results[2].isNear(q1, tolerance_));
}

TEST_F(OpenSpaceToolkit_Mathematics_QuaternionInterpolator_SLERP, Evaluate_Extrapolation)
{
    const Quaternion q0 = makeZRotation(0.0);
    const Quaternion q1 = makeZRotation(90.0);

    VectorXd x(2);
    x << 0.0, 1.0;

    Array<Quaternion> quaternions = {q0, q1};
    SLERP interpolator(x, quaternions);

    // Before range: clamp to first
    EXPECT_TRUE(interpolator.evaluate(-1.0).isNear(q0, tolerance_));

    // After range: clamp to last
    EXPECT_TRUE(interpolator.evaluate(2.0).isNear(q1, tolerance_));
}

TEST_F(OpenSpaceToolkit_Mathematics_QuaternionInterpolator_SLERP, GetQuaternions)
{
    const Quaternion q0 = makeZRotation(0.0);
    const Quaternion q1 = makeZRotation(90.0);

    VectorXd x(2);
    x << 0.0, 1.0;

    Array<Quaternion> quaternions = {q0, q1};
    SLERP interpolator(x, quaternions);

    const Array<Quaternion> result = interpolator.getQuaternions();

    EXPECT_EQ(result.getSize(), Size(2));
    EXPECT_TRUE(result[0].isNear(q0, tolerance_));
    EXPECT_TRUE(result[1].isNear(q1, tolerance_));
}
