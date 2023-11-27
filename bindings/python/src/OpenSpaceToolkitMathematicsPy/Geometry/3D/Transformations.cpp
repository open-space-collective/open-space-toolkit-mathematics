/// Apache License 2.0

#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformations/Rotations.cpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformations(pybind11::module& aModule)
{
    // Create "transformation" python submodule
    auto transformation = aModule.def_submodule("transformation");

    // Add __path__ attribute for "transformation" submodule
    transformation.attr("__path__") = "ostk.mathematics.geometry.d3.transformation";

    // Add objects to python "transformation" submodules
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformations_Rotations(transformation);
}
