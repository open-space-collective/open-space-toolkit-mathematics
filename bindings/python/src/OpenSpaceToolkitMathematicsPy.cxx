/// Apache License 2.0 

#include <OpenSpaceToolkitMathematicsPy/Utilities/ArrayCasting.hpp>
#include <OpenSpaceToolkitMathematicsPy/Utilities/ShiftToString.hpp>
#include <pybind11/eigen.h>
#include <pybind11/numpy.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>

#include <OpenSpaceToolkitMathematicsPy/CurveFitting.cpp>
#include <OpenSpaceToolkitMathematicsPy/Geometry.cpp>
#include <OpenSpaceToolkitMathematicsPy/Objects.cpp>

PYBIND11_MODULE(OpenSpaceToolkitMathematicsPy, m)
{
    // Add optional docstring for package OpenSpaceToolkitMathematicsPy
    m.doc() = "Geometry, curve fitting, optimization for OpenSpaceToolkit";

    // Add __path__ attribute to python package
    m.attr("__path__") = "ostk.mathematics";

    // Change attribute __name__ to make OpenSpaceToolkitMathematicsPy invisible in modules path
    m.attr("__name__") = "ostk.mathematics";

// Package version information
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif

    // Add python submodules to OpenSpaceToolkitMathematicsPy
    OpenSpaceToolkitMathematicsPy_Objects(m);
    OpenSpaceToolkitMathematicsPy_Geometry(m);
    OpenSpaceToolkitMathematicsPy_CurveFitting(m);
}
