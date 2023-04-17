////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Mathematics
/// @file           bindings/python/src/OpenSpaceToolkitMathematicsPy/CurveFitting/Interpolation.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkitMathematicsPy/CurveFitting/Interpolation/BarycentricRational.cpp>
#include <OpenSpaceToolkitMathematicsPy/CurveFitting/Interpolation/CubicSpline.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolation (           pybind11::module&           aModule                       )
{

    // Create "interpolation" python submodule
    auto interpolation = aModule.def_submodule("interpolation") ;

    // Add __path__ attribute for "interpolation" submodule
    interpolation.attr("__path__") = "ostk.mathematics.curve_fitting.interpolation" ;

    // Add objects to python "interpolation" submodules
    OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolation_BarycentricRational(interpolation) ;
    OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolation_CubicSpline(interpolation) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
