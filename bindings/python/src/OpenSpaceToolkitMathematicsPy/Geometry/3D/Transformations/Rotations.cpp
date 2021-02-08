////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformations/Rotations.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformations/Rotations/Quaternion.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformations/Rotations/RotationVector.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformations/Rotations/RotationMatrix.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformations_Rotations ( pybind11::module& aModule                                 )
{

    // Create "rotations" python submodule
    auto rotations = aModule.def_submodule("rotations") ;

    // Add __path__ attribute for "rotations" submodule
    rotations.attr("__path__") = "ostk.mathematics.geometry.d3.transformations.rotations" ;

    // Add objects to python "rotations" submodules
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformations_Rotations_Quaternion(rotations) ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformations_Rotations_RotationVector(rotations) ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformations_Rotations_RotationMatrix(rotations) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
