// Copyright © Loft Orbital Solutions Inc.

#include <OpenSpaceToolkitMathematicsPy/CurveFitting/Interpolator.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitMathematicsPy_CurveFitting               (           pybind11::module&           aModule                       )
{

    // Create "objects" python submodule
    auto curve_fitting = aModule.def_submodule("curve_fitting") ;

    // Add __path__ attribute for "interpolators" submodule
    curve_fitting.attr("__path__") = "ostk.mathematics.curve_fitting" ;

    // Add objects to python "interpolators" submodules
    OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolator(curve_fitting) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
