// Copyright © Loft Orbital Solutions Inc.

#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Intersection.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Transformation.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Objects.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry/2D/Object.cpp>


inline void                     OpenSpaceToolkitMathematicsPy_Geometry_2D   (           pybind11::module&           aModule                                     )
{

    // Create "d2" python submodule
    auto d2 = aModule.def_submodule("d2") ;

    // Add __path__ attribute for "d2" submodule
    d2.attr("__path__") = "ostk.mathematics.geometry.d2" ;

    // Add objects to python "d2" submodules
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Object(d2) ; // Cannot be binded without including Transformation.cpp (uses forward declaration for Transformation)
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Objects(d2) ;
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Transformation(d2) ;
    OpenSpaceToolkitMathematicsPy_Geometry_2D_Intersection(d2) ;

}

