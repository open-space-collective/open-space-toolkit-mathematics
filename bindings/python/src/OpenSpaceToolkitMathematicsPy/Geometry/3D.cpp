/// Apache License 2.0

#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Intersection.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Object.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformation.cpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D(pybind11::module& aModule)
{
    // Create "d3" python submodule
    auto d3 = aModule.def_submodule("d3");

    // Add object to python "d3" submodules
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Object(d3);
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformation(d3);
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Intersection(d3);
}
