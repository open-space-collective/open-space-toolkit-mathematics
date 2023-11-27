/// Apache License 2.0

#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformations/Rotations/Quaternion.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformations/Rotations/RotationMatrix.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformations/Rotations/RotationVector.cpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformations_Rotations(pybind11::module& aModule)
{
    // Create "rotation" python submodule
    auto rotation = aModule.def_submodule("rotation");

    // Add __path__ attribute for "rotation" submodule
    rotation.attr("__path__") = "ostk.mathematics.geometry.d3.transformation.rotation";

    // Add objects to python "rotation" submodules
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformations_Rotations_Quaternion(rotation);
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformations_Rotations_RotationVector(rotation);
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformations_Rotations_RotationMatrix(rotation);
}
