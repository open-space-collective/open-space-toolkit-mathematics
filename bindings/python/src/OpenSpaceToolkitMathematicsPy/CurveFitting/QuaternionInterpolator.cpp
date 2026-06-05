/// Apache License 2.0

#include <OpenSpaceToolkitMathematicsPy/CurveFitting/QuaternionInterpolator/SLERP.cpp>

inline void OpenSpaceToolkitMathematicsPy_CurveFitting_QuaternionInterpolator(pybind11::module& aModule)
{
    // Create "quaternion_interpolator" python submodule
    auto quaternion_interpolator = aModule.def_submodule("quaternion_interpolator");

    // Add object to python "quaternion_interpolator" submodules
    OpenSpaceToolkitMathematicsPy_CurveFitting_QuaternionInterpolator_SLERP(quaternion_interpolator);
}
