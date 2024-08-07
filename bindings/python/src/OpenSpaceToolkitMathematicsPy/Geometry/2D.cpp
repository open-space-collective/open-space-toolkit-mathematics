/// Apache License 2.0

#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Intersection.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Object.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Transformation.cpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_2D(pybind11::module& aModule)
{
    // Create "d2" python submodule
    auto d2 = aModule.def_submodule("d2");

    // Add object to python "d2" submodules
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Object(d2);
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Transformation(d2);
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Intersection(d2);
}
