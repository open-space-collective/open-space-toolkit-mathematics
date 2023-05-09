// Copyright © Loft Orbital Solutions Inc.

#include <OpenSpaceToolkitMathematicsPy/CurveFitting/Interpolator/BarycentricRational.cpp>
#include <OpenSpaceToolkitMathematicsPy/CurveFitting/Interpolator/CubicSpline.cpp>
#include <OpenSpaceToolkitMathematicsPy/CurveFitting/Interpolator/Linear.cpp>


inline void                     OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolator (           pybind11::module&           aModule                         )
{

    // Create "interpolator" python submodule
    auto interpolator = aModule.def_submodule("interpolator") ;

    // Add __path__ attribute for "interpolator" submodule
    interpolator.attr("__path__") = "ostk.mathematics.curve_fitting.interpolator" ;

    // Add objects to python "interpolator" submodules
    OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolator_BarycentricRational(interpolator) ;
    OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolator_CubicSpline(interpolator) ;
    OpenSpaceToolkitMathematicsPy_CurveFitting_Interpolator_Linear(interpolator) ;

}

