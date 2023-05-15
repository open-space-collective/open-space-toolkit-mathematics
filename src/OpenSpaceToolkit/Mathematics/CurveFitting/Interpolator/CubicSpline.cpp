/// Apache License 2.0

#include <iostream>

#include <OpenSpaceToolkit/Core/Error.hpp>

#include <OpenSpaceToolkit/Mathematics/CurveFitting/Interpolator/CubicSpline.hpp>

namespace ostk
{
namespace math
{
namespace curvefitting
{
namespace interp
{

CubicSpline::CubicSpline(const VectorXd& anXVector, const VectorXd& aYVector)
{
    if (aYVector.size() < 5)
    {
        throw ostk::core::error::runtime::Wrong("y");
    }

    if (anXVector.size() != aYVector.size())
    {
        throw ostk::core::error::runtime::Wrong("x and y");
    }

    const double h = anXVector(1) - anXVector(0);

    const VectorXd diff = anXVector.segment(1, anXVector.size() - 1) - anXVector.segment(0, anXVector.size() - 1);

    if (!diff.isConstant(h, 1e-6))
    {
        throw ostk::core::error::runtime::Wrong("x must be uniformly spaced");
    }

    interpolator_ =
        boost::math::interpolators::cardinal_cubic_b_spline<double>(aYVector.begin(), aYVector.end(), anXVector(0), h);
}

CubicSpline::CubicSpline(const VectorXd& aYVector, const Real& x0, const Real& h)
{
    if (aYVector.size() < 5)
    {
        throw ostk::core::error::runtime::Wrong("y");
    }

    interpolator_ =
        boost::math::interpolators::cardinal_cubic_b_spline<double>(aYVector.begin(), aYVector.end(), x0, h);
}

CubicSpline* CubicSpline::clone() const
{
    return new CubicSpline(*this);
}

VectorXd CubicSpline::evaluate(const VectorXd& aQueryVector) const
{
    VectorXd yOutput(aQueryVector.size());

    for (int i = 0; i < aQueryVector.size(); ++i)
    {
        yOutput(i) = interpolator_(aQueryVector(i));
    }

    return yOutput;
}

double CubicSpline::evaluate(const double& aQueryValue) const
{
    return interpolator_(aQueryValue);
}

}  // namespace interp
}  // namespace curvefitting
}  // namespace math
}  // namespace ostk
