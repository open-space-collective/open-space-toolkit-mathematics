/// Apache License 2.0

#include <OpenSpaceToolkitMathematicsPy/CurveFitting/MatrixInterpolator/LogEuclideanRiemannian.cpp>

inline void OpenSpaceToolkitMathematicsPy_CurveFitting_MatrixInterpolator(pybind11::module& aModule)
{
    // Create "matrix_interpolator" python submodule
    auto matrix_interpolator = aModule.def_submodule("matrix_interpolator");

    // Add object to python "matrix_interpolator" submodules
    OpenSpaceToolkitMathematicsPy_CurveFitting_MatrixInterpolator_LogEuclideanRiemannian(matrix_interpolator);
}
