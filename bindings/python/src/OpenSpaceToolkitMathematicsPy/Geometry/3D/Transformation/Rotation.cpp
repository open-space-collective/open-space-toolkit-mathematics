/// Apache License 2.0

#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformation/Rotation/Quaternion.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformation/Rotation/RotationMatrix.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformation/Rotation/RotationVector.cpp>

inline void OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformation_Rotation(pybind11::module& aModule)
{
    // Create "rotation" python submodule
    auto rotation = aModule.def_submodule("rotation");

    // Add __path__ attribute for "rotation" submodule
    rotation.attr("__path__") = "ostk.mathematics.geometry.d3.transformation.rotation";

    // Add object to python "rotation" submodules
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformation_Rotation_Quaternion(rotation);
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformation_Rotation_RotationVector(rotation);
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformation_Rotation_RotationMatrix(rotation);
}
