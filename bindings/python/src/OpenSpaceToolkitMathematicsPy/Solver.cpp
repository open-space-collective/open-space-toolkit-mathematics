/// Apache License 2.0

#include <OpenSpaceToolkitMathematicsPy/Solvers/NumericalSolver.cpp>

inline void OpenSpaceToolkitMathematicsPy_Solvers(pybind11::module& aModule)
{
    // Create "object" python submodule
    auto solvers = aModule.def_submodule("solvers");

    // Add __path__ attribute for "interpolators" submodule
    solvers.attr("__path__") = "ostk.mathematics.solvers";

    // Add object to python "interpolators" submodules
    OpenSpaceToolkitMathematicsPy_Solvers_NumericalSolver(solvers);
}
