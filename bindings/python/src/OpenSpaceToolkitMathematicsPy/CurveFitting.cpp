/// Apache License 2.0

#include <OpenSpaceToolkitMathematicsPy/CurveFitting/Interpolator.cpp>

inline void OpenSpaceToolkitMathematicsPy_CurveFitting(pybind11::module& aModule)
{
    // Create "curve fitting" python submodule
    auto curve_fitting = aModule.def_submodule("curve_fitting");


    // Add object to python "interpolators" submodules
    OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolator(curve_fitting);
}
