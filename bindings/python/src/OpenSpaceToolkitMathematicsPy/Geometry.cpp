/// Apache License 2.0 

#include <OpenSpaceToolkitMathematicsPy/Geometry/2D.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/Angle.cpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry(pybind11::module& aModule)
{
    // Create "geometry" python submodule
    auto geometry = aModule.def_submodule("geometry");

    // Add __path__ attribute for "geometry" submodule
    geometry.attr("__path__") = "ostk.mathematics.geometry";

    // Add objects to python "geometry" submodules
    OpenSpaceToolkitMathematicsPy_Geometry_2D(geometry);
    OpenSpaceToolkitMathematicsPy_Geometry_3D(geometry);
    OpenSpaceToolkitMathematicsPy_Geometry_Angle(geometry);
}
