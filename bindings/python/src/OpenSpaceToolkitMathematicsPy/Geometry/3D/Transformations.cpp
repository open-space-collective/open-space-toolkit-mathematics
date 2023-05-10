/// Apache License 2.0 

#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformations/Rotations.cpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformations(pybind11::module& aModule)
{
    // Create "transformations" python submodule
    auto transformations = aModule.def_submodule("transformations");

    // Add __path__ attribute for "transformations" submodule
    transformations.attr("__path__") = "ostk.mathematics.geometry.d3.transformations";

    // Add objects to python "transformations" submodules
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformations_Rotations(transformations);
}
