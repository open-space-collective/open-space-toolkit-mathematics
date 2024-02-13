/// Apache License 2.0

#include <OpenSpaceToolkitMathematicsPy/Solver/NumericalSolver.cpp>

inline void OpenSpaceToolkitMathematicsPy_Solver(pybind11::module& aModule)
{
    // Create "object" python submodule
    auto solver = aModule.def_submodule("solver");


    // Add object to python "interpolators" submodules
    OpenSpaceToolkitMathematicsPy_Solver_NumericalSolver(solver);
}
