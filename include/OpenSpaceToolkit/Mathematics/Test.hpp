/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Mathematics_Test__
#define __OpenSpaceToolkit_Mathematics_Test__

#include <OpenSpaceToolkit/Mathematics/Objects/Vector.hpp>

#include <Global.test.hpp>

using ostk::math::obj::VectorXd;

bool VectorEquality(const VectorXd& aFirstVector, const VectorXd& aSecondVector, const double& aTolerance)
{
    return aFirstVector.isApprox(aSecondVector, aTolerance);
}

#define EXPECT_VECTOR_EQUALITY(aFirstVector, aSecondVector, aTolerance) \
    EXPECT_PRED3(VectorEquality, aFirstVector, aSecondVector, aTolerance);

#define ASSERT_VECTOR_EQUALITY(aFirstVector, aSecondVector, aTolerance) \
    ASSERT_PRED3(VectorEquality, aFirstVector, aSecondVector, aTolerance);

#endif
