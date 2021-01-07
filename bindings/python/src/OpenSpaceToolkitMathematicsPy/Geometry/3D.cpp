////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/Geometry/3D.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkitMathematicsPy/Utilities/ArrayCasting.hpp>

#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Intersection.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformations.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Transformation.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Objects.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/3D/Object.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_Geometry_3D                     (          pybind11::module&                     aModule         )
{

    // Create "d3" python submodule
    auto d3 = aModule.def_submodule("d3") ;

    // Add __path__ attribute for "d3" submodule
    d3.attr("__path__") = "ostk.mathematics.geometry.d3" ;

    // Add objects to python "d3" submodules
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Object(d3) ; // Cannot be binded without including Objects.cpp
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Objects(d3) ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformation(d3) ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Transformations(d3) ;
    OpenSpaceToolkitMathematicsPy_Geometry_3D_Intersection(d3) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
