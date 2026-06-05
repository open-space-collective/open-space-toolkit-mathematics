/// Apache License 2.0

#include <OpenSpaceToolkitMathematicsPy/CurveFitting/Interpolator.cpp>
#include <OpenSpaceToolkitMathematicsPy/CurveFitting/MatrixInterpolator.cpp>
#include <OpenSpaceToolkitMathematicsPy/CurveFitting/QuaternionInterpolator.cpp>

inline void OpenSpaceToolkitMathematicsPy_CurveFitting(pybind11::module& aModule)
{
    // Create "curve fitting" python submodule
    auto curve_fitting = aModule.def_submodule("curve_fitting");

    // Add object to python "interpolators" submodules
    OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolator(curve_fitting);
    OpenSpaceToolkitMathematicsPy_CurveFitting_MatrixInterpolator(curve_fitting);
    OpenSpaceToolkitMathematicsPy_CurveFitting_QuaternionInterpolator(curve_fitting);
}
