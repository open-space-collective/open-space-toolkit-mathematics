/// Apache License 2.0

#include <OpenSpaceToolkitMathematicsPy/Geometry/Planetodetic/Object.cpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_Planetodetic(pybind11::module& aModule)
{
    // Create "planetodetic" python submodule
    auto planetodetic = aModule.def_submodule("planetodetic");

    // Add object to python "planetodetic" submodules
    OpenSpaceToolkitMathematicsPy_Geometry_Planetodetic_Object(planetodetic);
}
